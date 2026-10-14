#ifndef DUKE_PORT_CONFIG_H
#define DUKE_PORT_CONFIG_H

#include <stddef.h>

enum pc_renderer_kind { PC_RENDERER_CLASSIC, PC_RENDERER_ENHANCED };
enum pc_aspect_kind { PC_ASPECT_AUTO, PC_ASPECT_4_3, PC_ASPECT_16_10, PC_ASPECT_16_9,
                      PC_ASPECT_21_9, PC_ASPECT_32_9 };
enum pc_pixel_aspect_kind { PC_PIXEL_ASPECT_4_3, PC_PIXEL_ASPECT_SQUARE };
enum pc_filter_kind { PC_FILTER_SHARP, PC_FILTER_NEAREST, PC_FILTER_LINEAR };

struct pc_settings {
    enum pc_renderer_kind renderer;
    int fullscreen;
    int window_width;
    int window_height;
    enum pc_aspect_kind aspect;
    enum pc_pixel_aspect_kind pixel_aspect;
    int integer_scale;
    enum pc_filter_kind filter;
    int volume;
    int stereo;
    int widescreen;
    int wide_activity;
    int smooth_camera;
    int interpolation;
    int frame_cap;
};

enum pc_setting_row {
    PC_SETTING_RENDERER,
    PC_SETTING_FULLSCREEN,
    PC_SETTING_ASPECT,
    PC_SETTING_PIXEL_ASPECT,
    PC_SETTING_INTEGER_SCALE,
    PC_SETTING_FILTER,
    PC_SETTING_VOLUME,
    PC_SETTING_STEREO,
    PC_SETTING_ENHANCED_SECTION,
    PC_SETTING_WIDESCREEN,
    PC_SETTING_WIDE_ACTIVITY,
    PC_SETTING_SMOOTH_CAMERA,
    PC_SETTING_INTERPOLATION,
    PC_SETTING_FRAME_CAP,
    PC_SETTING_COUNT
};

extern struct pc_settings pc_settings;

void pc_config_load(void);
void pc_config_save(void);
int pc_config_count(void);
const char *pc_config_label(int row);
void pc_config_value_text(int row, char *buffer, size_t capacity);
void pc_config_change(int row, int direction);
int pc_config_is_section(int row);

#endif
