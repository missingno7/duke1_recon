#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "pc_internal.h"
#include "wide_pass.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pc_data_directory[4096];

void pc_delay(uint16_t milliseconds) { port_wide_pass_abandon("pc_delay"); SDL_Delay(milliseconds); }

uint32_t pc_coreleft(void) { return 2u * 1024u * 1024u; }

/* Far data in Turbo C's large model: a far pointer is segment:offset, and adding an int
   changes only the 16-bit offset, which wraps inside the 64 KB segment.  The game relies on
   it - e.g. sprite_graphics_buffer + offset with an int offset of 0x80C0 (-32576) means
   0x80C0 bytes forward.  So every block the game allocates gets its own 64 KB segment,
   mapped three times in a row (alias, segment, alias): p + (int16_t)x then lands where the
   wrapped offset would, for any expression, without touching the game source. */
#define SEGMENT_SIZE 0x10000u

typedef struct pc_allocation {
    uint8_t *segment;
    int episode_owned;
    struct pc_allocation *next;
} pc_allocation;

static pc_allocation *pc_allocations;
static int pc_episode_allocation_mode;

static void unmap_segment(uint8_t *segment)
{
    UnmapViewOfFile(segment - SEGMENT_SIZE);
    UnmapViewOfFile(segment);
    UnmapViewOfFile(segment + SEGMENT_SIZE);
}

void *pc_malloc(uint16_t size)
{
    port_wide_pass_abandon("pc_malloc");
    HANDLE section;
    if (size == 0 || size > SEGMENT_SIZE)
        return NULL;
    section = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SEGMENT_SIZE, NULL);
    if (!section)
        return NULL;
    for (int attempt = 0; attempt < 64; ++attempt) {
        uint8_t *base = (uint8_t *)VirtualAlloc(NULL, 3u * SEGMENT_SIZE, MEM_RESERVE, PAGE_NOACCESS);
        if (!base)
            break;
        VirtualFree(base, 0, MEM_RELEASE);          /* the address range is known free; claim it with views */
        uint8_t *v0 = MapViewOfFileEx(section, FILE_MAP_ALL_ACCESS, 0, 0, SEGMENT_SIZE, base);
        uint8_t *v1 = v0 ? MapViewOfFileEx(section, FILE_MAP_ALL_ACCESS, 0, 0, SEGMENT_SIZE, base + SEGMENT_SIZE) : NULL;
        uint8_t *v2 = v1 ? MapViewOfFileEx(section, FILE_MAP_ALL_ACCESS, 0, 0, SEGMENT_SIZE, base + 2u * SEGMENT_SIZE) : NULL;
        if (v0 && v1 && v2) {
            pc_allocation *allocation = (pc_allocation *)malloc(sizeof(*allocation));
            if (!allocation) {
                unmap_segment(v1);
                CloseHandle(section);
                return NULL;
            }
            CloseHandle(section);                     /* the views keep the section alive */
            allocation->segment = v1;
            allocation->episode_owned = pc_episode_allocation_mode;
            allocation->next = pc_allocations;
            pc_allocations = allocation;
            return v1;
        }
        if (v0) UnmapViewOfFile(v0);
        if (v1) UnmapViewOfFile(v1);                 /* another thread took part of the range: retry */
    }
    CloseHandle(section);
    return NULL;
}

void pc_free(void *block)
{
    port_wide_pass_abandon("pc_free");
    uint8_t *segment = (uint8_t *)block;
    pc_allocation **link = &pc_allocations;
    if (!segment)
        return;
    while (*link) {
        pc_allocation *allocation = *link;
        if (allocation->segment == segment) {
            *link = allocation->next;
            free(allocation);
            break;
        }
        link = &allocation->next;
    }
    unmap_segment(segment);
}

/* The 64 KB segments of the live blocks (the wide presentation pass check). */
int pc_allocation_segments(uint8_t **segments, int capacity)
{
    int count = 0;
    for (pc_allocation *a = pc_allocations; a && count < capacity; a = a->next)
        segments[count++] = a->segment;
    return count;
}

void pc_episode_allocations_begin(void)
{
    pc_episode_allocation_mode = 1;
}

void pc_episode_allocations_release(void)
{
    pc_allocation **link = &pc_allocations;
    pc_episode_allocation_mode = 0;
    while (*link) {
        pc_allocation *allocation = *link;
        if (allocation->episode_owned) {
            *link = allocation->next;
            unmap_segment(allocation->segment);
            free(allocation);
        } else {
            link = &allocation->next;
        }
    }
}

void pc_release_all_allocations(void)
{
    pc_allocation *allocation = pc_allocations;
    pc_episode_allocation_mode = 0;
    pc_allocations = NULL;
    while (allocation) {
        pc_allocation *next = allocation->next;
        unmap_segment(allocation->segment);
        free(allocation);
        allocation = next;
    }
}

void pc_textmode(int16_t mode) { port_wide_pass_abandon("pc_textmode"); bios_set_mode((uint8_t)mode); }

static int join_data_path(char *out, size_t capacity, const char *name) {
    WIN32_FIND_DATAA entry;
    HANDLE find;
    char pattern[8192];
    const char *base = name;
    const char *slash = strrchr(name, '/');
    const char *backslash = strrchr(name, '\\');
    if (slash && (!backslash || slash > backslash)) base = slash + 1;
    else if (backslash) base = backslash + 1;
    if (!pc_data_directory[0]) return 0;
    if (snprintf(pattern, sizeof(pattern), "%s\\*", pc_data_directory) >= (int)sizeof(pattern)) return 0;
    find = FindFirstFileA(pattern, &entry);
    if (find == INVALID_HANDLE_VALUE) return 0;
    do {
        if (_stricmp(entry.cFileName, base) == 0) {
            int written = snprintf(out, capacity, "%s\\%s", pc_data_directory, entry.cFileName);
            FindClose(find);
            return written >= 0 && (size_t)written < capacity;
        }
    } while (FindNextFileA(find, &entry));
    FindClose(find);
    return 0;
}

FILE *pc_fopen(const char *name, const char *mode) {
    port_wide_pass_abandon("pc_fopen");
    char resolved[8192];
    FILE *file;
    if (!name || !mode) return NULL;
    if (!join_data_path(resolved, sizeof(resolved), name)) {
        /* Windows itself resolves exact-case names; retain that behavior for new files. */
        if (snprintf(resolved, sizeof(resolved), "%s\\%s", pc_data_directory, name) >= (int)sizeof(resolved)) return NULL;
    }
    file = fopen(resolved, mode);
    pc_trace(PC_TRACE_FILES, "file %s %s -> %s", mode, name, file ? resolved : "not found");
    return file;
}

int16_t pc_getw(FILE *stream) {
    port_wide_pass_abandon("pc_getw");
    int low, high;
    if (!stream) return (int16_t)-1;
    low = fgetc(stream);
    if (low == EOF) return (int16_t)-1;
    high = fgetc(stream);
    if (high == EOF) return (int16_t)-1;
    return (int16_t)((uint16_t)(uint8_t)low | ((uint16_t)(uint8_t)high << 8));
}

int16_t pc_putw(int16_t word, FILE *stream) {
    port_wide_pass_abandon("pc_putw");
    uint16_t bits = (uint16_t)word;
    if (!stream) return (int16_t)-1;
    if (fputc((int)(bits & 0xffu), stream) == EOF) return (int16_t)-1;
    if (fputc((int)(bits >> 8), stream) == EOF) return (int16_t)-1;
    return 0;
}

static char *pc_utoa_base(uint32_t value, char *buffer, int base, int negative) {
    static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char reversed[34];
    size_t count = 0;
    if (!buffer || base < 2 || base > 36) return buffer;
    do {
        reversed[count++] = digits[value % (uint32_t)base];
        value /= (uint32_t)base;
    } while (value && count < sizeof(reversed));
    if (negative) reversed[count++] = '-';
    for (size_t i = 0; i < count; ++i) buffer[i] = reversed[count - i - 1];
    buffer[count] = '\0';
    return buffer;
}

char *pc_ltoa(int32_t value, char *buffer, int16_t base) {
    uint32_t magnitude = value < 0 ? (uint32_t)(-(int64_t)value) : (uint32_t)value;
    return pc_utoa_base(magnitude, buffer, base, value < 0 && base == 10);
}

char *pc_ultoa(uint32_t value, char *buffer, int16_t base) {
    return pc_utoa_base(value, buffer, base, 0);
}

