#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "pc_internal.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pc_data_directory[4096];

void pc_delay(unsigned milliseconds) { SDL_Delay(milliseconds); }

uint32_t pc_coreleft(void) { return 2u * 1024u * 1024u; }

void pc_textmode(int mode) { bios_set_mode((uint8_t)mode); }

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
    int low, high;
    if (!stream) return (int16_t)-1;
    low = fgetc(stream);
    if (low == EOF) return (int16_t)-1;
    high = fgetc(stream);
    if (high == EOF) return (int16_t)-1;
    return (int16_t)((uint16_t)(uint8_t)low | ((uint16_t)(uint8_t)high << 8));
}

int16_t pc_putw(int16_t word, FILE *stream) {
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

char *pc_ltoa(int32_t value, char *buffer, int base) {
    uint32_t magnitude = value < 0 ? (uint32_t)(-(int64_t)value) : (uint32_t)value;
    return pc_utoa_base(magnitude, buffer, base, value < 0 && base == 10);
}

char *pc_ultoa(uint32_t value, char *buffer, int base) {
    return pc_utoa_base(value, buffer, base, 0);
}

