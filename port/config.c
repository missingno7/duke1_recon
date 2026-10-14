#include "config.h"
#include "pc_internal.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const struct pc_settings default_settings = {
    PC_RENDERER_CLASSIC, 0, 1280, 800, PC_ASPECT_AUTO, PC_PIXEL_ASPECT_4_3,
    0, PC_FILTER_SHARP, 80, 0, 0, 0, 0, 0, 0
};

struct pc_settings pc_settings = {
    PC_RENDERER_CLASSIC, 0, 1280, 800, PC_ASPECT_AUTO, PC_PIXEL_ASPECT_4_3,
    0, PC_FILTER_SHARP, 80, 0, 0, 0, 0, 0, 0
};

enum json_type { JSON_STRING, JSON_NUMBER, JSON_BOOLEAN };
struct json_value {
    enum json_type type;
    char string[65536];
    long long number;
    int integer;
    int boolean;
};

struct json_reader { const char *cursor; };

static int make_config_path(char *path, size_t capacity, const char *suffix)
{
    int n;
    if (!pc_data_directory[0]) return 0;
    n = snprintf(path, capacity, "%s/%s%s", pc_data_directory, "duke1.json", suffix ? suffix : "");
    return n >= 0 && (size_t)n < capacity;
}

static void skip_space(struct json_reader *reader)
{
    while (isspace((unsigned char)*reader->cursor)) ++reader->cursor;
}

static int hex_value(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int parse_string(struct json_reader *reader, char *out, size_t capacity)
{
    size_t length = 0;
    if (*reader->cursor++ != '"') return 0;
    while (*reader->cursor && *reader->cursor != '"') {
        unsigned char c = (unsigned char)*reader->cursor++;
        if (c < 0x20) return 0;
        if (c == '\\') {
            c = (unsigned char)*reader->cursor++;
            switch (c) {
            case '"': case '\\': case '/': break;
            case 'b': c = '\b'; break;
            case 'f': c = '\f'; break;
            case 'n': c = '\n'; break;
            case 'r': c = '\r'; break;
            case 't': c = '\t'; break;
            case 'u': {
                int code = 0;
                for (int i = 0; i < 4; ++i) {
                    int digit = hex_value(*reader->cursor++);
                    if (digit < 0) return 0;
                    code = (code << 4) | digit;
                }
                c = code > 0 && code <= 0x7f ? (unsigned char)code : '?';
                break;
            }
            default: return 0;
            }
        }
        if (length + 1 >= capacity) return 0;
        out[length++] = (char)c;
    }
    if (*reader->cursor != '"') return 0;
    ++reader->cursor;
    out[length] = 0;
    return 1;
}

static int parse_number(struct json_reader *reader, struct json_value *value)
{
    char token[96];
    size_t n = 0;
    char *end;
    const char *start = reader->cursor;
    if (*reader->cursor == '-') ++reader->cursor;
    if (*reader->cursor == '0') {
        ++reader->cursor;
        if (isdigit((unsigned char)*reader->cursor)) return 0;
    } else {
        if (*reader->cursor < '1' || *reader->cursor > '9') return 0;
        while (isdigit((unsigned char)*reader->cursor)) ++reader->cursor;
    }
    if (*reader->cursor == '.') {
        ++reader->cursor;
        if (!isdigit((unsigned char)*reader->cursor)) return 0;
        while (isdigit((unsigned char)*reader->cursor)) ++reader->cursor;
    }
    if (*reader->cursor == 'e' || *reader->cursor == 'E') {
        ++reader->cursor;
        if (*reader->cursor == '+' || *reader->cursor == '-') ++reader->cursor;
        if (!isdigit((unsigned char)*reader->cursor)) return 0;
        while (isdigit((unsigned char)*reader->cursor)) ++reader->cursor;
    }
    n = (size_t)(reader->cursor - start);
    if (n >= sizeof(token)) return 0;
    memcpy(token, start, n);
    token[n] = 0;
    value->type = JSON_NUMBER;
    value->integer = strchr(token, '.') == NULL && strchr(token, 'e') == NULL && strchr(token, 'E') == NULL;
    value->number = 0;
    if (value->integer) {
        errno = 0;
        value->number = strtoll(token, &end, 10);
        if (errno || *end) value->integer = 0;
    } else {
        (void)strtod(token, &end);
        if (*end) return 0;
    }
    return 1;
}

static int parse_value(struct json_reader *reader, struct json_value *value)
{
    skip_space(reader);
    memset(value, 0, sizeof(*value));
    if (*reader->cursor == '"') {
        value->type = JSON_STRING;
        return parse_string(reader, value->string, sizeof(value->string));
    }
    if (*reader->cursor == '-' || isdigit((unsigned char)*reader->cursor))
        return parse_number(reader, value);
    if (strncmp(reader->cursor, "true", 4) == 0) {
        value->type = JSON_BOOLEAN; value->boolean = 1; reader->cursor += 4; return 1;
    }
    if (strncmp(reader->cursor, "false", 5) == 0) {
        value->type = JSON_BOOLEAN; value->boolean = 0; reader->cursor += 5; return 1;
    }
    return 0;
}

static int parse_object(const char *text, void (*apply)(const char *, const struct json_value *))
{
    struct json_reader reader = { text };
    skip_space(&reader);
    if (*reader.cursor++ != '{') return 0;
    skip_space(&reader);
    if (*reader.cursor == '}') ++reader.cursor;
    else for (;;) {
        char key[65536];
        struct json_value value;
        skip_space(&reader);
        if (!parse_string(&reader, key, sizeof(key))) return 0;
        skip_space(&reader);
        if (*reader.cursor++ != ':') return 0;
        if (!parse_value(&reader, &value)) return 0;
        apply(key, &value);
        skip_space(&reader);
        if (*reader.cursor == '}') { ++reader.cursor; break; }
        if (*reader.cursor++ != ',') return 0;
    }
    skip_space(&reader);
    return *reader.cursor == 0;
}

static int get_bool(const struct json_value *v, int fallback)
{
    return v->type == JSON_BOOLEAN ? v->boolean : fallback;
}

static int get_int(const struct json_value *v, int minimum, int maximum, int fallback)
{
    if (v->type != JSON_NUMBER || !v->integer || v->number < minimum || v->number > maximum)
        return fallback;
    return (int)v->number;
}

static void apply_property(const char *key, const struct json_value *v)
{
    static const char *const renderer_values[] = { "classic", "enhanced" };
    static const char *const aspect_values[] = { "auto", "4:3", "16:10", "16:9", "21:9", "32:9" };
    static const char *const pixel_values[] = { "4:3", "square" };
    static const char *const filter_values[] = { "sharp", "nearest", "linear" };
    const char *const *values;
    if (strcmp(key, "renderer") == 0) {
        values = renderer_values; pc_settings.renderer = PC_RENDERER_CLASSIC;
        if (v->type == JSON_STRING) for (int i = 0; i < 2; ++i) if (!strcmp(v->string, values[i])) pc_settings.renderer = (enum pc_renderer_kind)i;
        return;
    }
    if (strcmp(key, "aspect") == 0) {
        values = aspect_values; pc_settings.aspect = PC_ASPECT_AUTO;
        if (v->type == JSON_STRING) for (int i = 0; i < 6; ++i) if (!strcmp(v->string, values[i])) pc_settings.aspect = (enum pc_aspect_kind)i;
        return;
    }
    if (strcmp(key, "pixel_aspect") == 0) {
        values = pixel_values; pc_settings.pixel_aspect = PC_PIXEL_ASPECT_4_3;
        if (v->type == JSON_STRING) for (int i = 0; i < 2; ++i) if (!strcmp(v->string, values[i])) pc_settings.pixel_aspect = (enum pc_pixel_aspect_kind)i;
        return;
    }
    if (strcmp(key, "filter") == 0) {
        values = filter_values; pc_settings.filter = PC_FILTER_SHARP;
        if (v->type == JSON_STRING) for (int i = 0; i < 3; ++i) if (!strcmp(v->string, values[i])) pc_settings.filter = (enum pc_filter_kind)i;
        return;
    }
    if (strcmp(key, "fullscreen") == 0) pc_settings.fullscreen = get_bool(v, default_settings.fullscreen);
    else if (strcmp(key, "window_width") == 0) pc_settings.window_width = get_int(v, 320, 7680, default_settings.window_width);
    else if (strcmp(key, "window_height") == 0) pc_settings.window_height = get_int(v, 200, 4320, default_settings.window_height);
    else if (strcmp(key, "integer_scale") == 0) pc_settings.integer_scale = get_bool(v, default_settings.integer_scale);
    else if (strcmp(key, "volume") == 0) pc_settings.volume = get_int(v, 0, 100, default_settings.volume);
    else if (strcmp(key, "stereo") == 0) pc_settings.stereo = get_bool(v, default_settings.stereo);
    else if (strcmp(key, "widescreen") == 0) pc_settings.widescreen = get_bool(v, default_settings.widescreen);
    else if (strcmp(key, "wide_activity") == 0) pc_settings.wide_activity = get_bool(v, default_settings.wide_activity);
    else if (strcmp(key, "smooth_camera") == 0) pc_settings.smooth_camera = get_bool(v, default_settings.smooth_camera);
    else if (strcmp(key, "interpolation") == 0) pc_settings.interpolation = get_bool(v, default_settings.interpolation);
    else if (strcmp(key, "frame_cap") == 0) pc_settings.frame_cap = get_int(v, 0, 1000, default_settings.frame_cap);
}

void pc_config_save(void)
{
    char path[8192];
    FILE *file;
    if (!make_config_path(path, sizeof(path), "")) {
        fprintf(stderr, "Could not save duke1.json: data directory path is too long.\n");
        return;
    }
    file = fopen(path, "w");
    if (!file) {
        fprintf(stderr, "Could not write %s (settings are active for this run only).\n", path);
        return;
    }
    fprintf(file,
        "{\n"
        "  \"renderer\": \"%s\",\n"
        "  \"fullscreen\": %s,\n"
        "  \"window_width\": %d,\n"
        "  \"window_height\": %d,\n"
        "  \"aspect\": \"%s\",\n"
        "  \"pixel_aspect\": \"%s\",\n"
        "  \"integer_scale\": %s,\n"
        "  \"filter\": \"%s\",\n"
        "  \"volume\": %d,\n"
        "  \"stereo\": %s,\n"
        "  \"widescreen\": %s,\n"
        "  \"wide_activity\": %s,\n"
        "  \"smooth_camera\": %s,\n"
        "  \"interpolation\": %s,\n"
        "  \"frame_cap\": %d\n"
        "}\n",
        pc_settings.renderer == PC_RENDERER_ENHANCED ? "enhanced" : "classic",
        pc_settings.fullscreen ? "true" : "false", pc_settings.window_width, pc_settings.window_height,
        (const char *[]) { "auto", "4:3", "16:10", "16:9", "21:9", "32:9" }[pc_settings.aspect],
        pc_settings.pixel_aspect == PC_PIXEL_ASPECT_SQUARE ? "square" : "4:3",
        pc_settings.integer_scale ? "true" : "false",
        (const char *[]) { "sharp", "nearest", "linear" }[pc_settings.filter],
        pc_settings.volume, pc_settings.stereo ? "true" : "false",
        pc_settings.widescreen ? "true" : "false", pc_settings.wide_activity ? "true" : "false",
        pc_settings.smooth_camera ? "true" : "false", pc_settings.interpolation ? "true" : "false",
        pc_settings.frame_cap);
    int failed = ferror(file);
    if (fclose(file) != 0) failed = 1;
    if (failed)
        fprintf(stderr, "Could not finish writing %s.\n", path);
}

void pc_config_load(void)
{
    char path[8192], bad_path[8192];
    char *text = NULL;
    FILE *file;
    int broken = 0;
    pc_settings = default_settings;
    if (!make_config_path(path, sizeof(path), "")) {
        fprintf(stderr, "Could not load duke1.json: data directory path is too long.\n");
        pc_speaker_set_volume(pc_settings.volume);
        return;
    }
    errno = 0;
    file = fopen(path, "rb");
    if (!file) {
        if (errno != ENOENT) broken = 1;
    } else {
        long size;
        if (fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) < 0 || size > 65535 ||
            fseek(file, 0, SEEK_SET) != 0) {
            broken = 1;
        } else {
            text = (char *)malloc((size_t)size + 1);
            if (!text || fread(text, 1, (size_t)size, file) != (size_t)size || ferror(file)) broken = 1;
            else {
                text[size] = 0;
                if (!parse_object(text, apply_property)) broken = 1;
            }
        }
        fclose(file);
    }
    free(text);
    if (broken) {
        if (make_config_path(bad_path, sizeof(bad_path), ".bad")) {
            (void)remove(bad_path);
            if (rename(path, bad_path) == 0)
                fprintf(stderr, "duke1.json could not be read; renamed to duke1.json.bad and using defaults.\n");
            else
                fprintf(stderr, "duke1.json could not be read and could not be renamed; using defaults.\n");
        } else {
            fprintf(stderr, "duke1.json could not be read; using defaults.\n");
        }
        pc_settings = default_settings;
    }
    pc_config_save();
    pc_speaker_set_volume(pc_settings.volume);
}

int pc_config_count(void)
{
    return PC_SETTING_COUNT;
}

const char *pc_config_label(int row)
{
    static const char *const labels[PC_SETTING_COUNT] = {
        "Renderer", "Fullscrn", "Aspect", "Pixels", "Integer", "Filter", "Volume", "Stereo",
        "ENHANCED RENDERER", "Widescrn", "Wide act", "Smooth", "Interp", "FPS cap"
    };
    return row >= 0 && row < PC_SETTING_COUNT ? labels[row] : "";
}

void pc_config_value_text(int row, char *buffer, size_t capacity)
{
    static const char *const aspects[] = { "auto", "4:3", "16:10", "16:9", "21:9", "32:9" };
    if (!buffer || !capacity) return;
    switch (row) {
    case PC_SETTING_RENDERER: snprintf(buffer, capacity, "%s", pc_settings.renderer == PC_RENDERER_ENHANCED ? "Enhanced" : "Classic"); break;
    case PC_SETTING_FULLSCREEN: snprintf(buffer, capacity, "%s", pc_settings.fullscreen ? "On" : "Off"); break;
    case PC_SETTING_ASPECT: snprintf(buffer, capacity, "%s", aspects[pc_settings.aspect]); break;
    case PC_SETTING_PIXEL_ASPECT: snprintf(buffer, capacity, "%s", pc_settings.pixel_aspect == PC_PIXEL_ASPECT_SQUARE ? "Square" : "4:3"); break;
    case PC_SETTING_INTEGER_SCALE: snprintf(buffer, capacity, "%s", pc_settings.integer_scale ? "On" : "Off"); break;
    case PC_SETTING_FILTER: snprintf(buffer, capacity, "%s", (const char *[]) { "Sharp", "Nearest", "Linear" }[pc_settings.filter]); break;
    case PC_SETTING_VOLUME: snprintf(buffer, capacity, "%d%%", pc_settings.volume); break;
    case PC_SETTING_STEREO: snprintf(buffer, capacity, "%s", pc_settings.stereo ? "On" : "Off"); break;
    case PC_SETTING_WIDESCREEN: snprintf(buffer, capacity, "%s", pc_settings.widescreen ? "On" : "Off"); break;
    case PC_SETTING_WIDE_ACTIVITY: snprintf(buffer, capacity, "%s", pc_settings.wide_activity ? "On" : "Off"); break;
    case PC_SETTING_SMOOTH_CAMERA: snprintf(buffer, capacity, "%s", pc_settings.smooth_camera ? "On" : "Off"); break;
    case PC_SETTING_INTERPOLATION: snprintf(buffer, capacity, "%s", pc_settings.interpolation ? "On" : "Off"); break;
    case PC_SETTING_FRAME_CAP: snprintf(buffer, capacity, "%d", pc_settings.frame_cap); break;
    default: buffer[0] = 0; break;
    }
}

void pc_config_change(int row, int direction)
{
    int step = direction < 0 ? -1 : 1;
#define TOGGLE(field) pc_settings.field = !pc_settings.field
#define CYCLE(field, count) pc_settings.field = (int)((pc_settings.field + step + count) % count)
    switch (row) {
    case PC_SETTING_RENDERER: CYCLE(renderer, 2); break;
    case PC_SETTING_FULLSCREEN: TOGGLE(fullscreen); break;
    case PC_SETTING_ASPECT: CYCLE(aspect, 6); break;
    case PC_SETTING_PIXEL_ASPECT: CYCLE(pixel_aspect, 2); break;
    case PC_SETTING_INTEGER_SCALE: TOGGLE(integer_scale); break;
    case PC_SETTING_FILTER: CYCLE(filter, 3); break;
    case PC_SETTING_VOLUME:
        pc_settings.volume += step * 5;
        if (pc_settings.volume < 0) pc_settings.volume = 100;
        if (pc_settings.volume > 100) pc_settings.volume = 0;
        break;
    case PC_SETTING_STEREO: TOGGLE(stereo); break;
    case PC_SETTING_WIDESCREEN: TOGGLE(widescreen); break;
    case PC_SETTING_WIDE_ACTIVITY: TOGGLE(wide_activity); break;
    case PC_SETTING_SMOOTH_CAMERA: TOGGLE(smooth_camera); break;
    case PC_SETTING_INTERPOLATION: TOGGLE(interpolation); break;
    case PC_SETTING_FRAME_CAP: {
        static const int caps[] = { 0, 30, 60, 120, 240 };
        int index = -1;
        for (int i = 0; i < 5; ++i) if (caps[i] == pc_settings.frame_cap) index = i;
        if (index < 0) {
            if (step > 0) {
                index = 4;
                for (int i = 0; i < 5; ++i) if (caps[i] > pc_settings.frame_cap) { index = i - 1; break; }
            } else {
                index = 0;
                for (int i = 4; i >= 0; --i) if (caps[i] < pc_settings.frame_cap) { index = i + 1; break; }
            }
        }
        index = (index + step + 5) % 5;
        pc_settings.frame_cap = caps[index];
        break;
    }
    default: break;
    }
#undef CYCLE
#undef TOGGLE
}

int pc_config_is_section(int row)
{
    return row == PC_SETTING_ENHANCED_SECTION;
}
