/* GAME1.C - first translation unit of Duke Nukum v2.0: startup, main loop, levels, actors, files.

   Functions, initialised data and literals stay in the order of the original object
   file: Turbo C 2.0 emits code, string literals and data in source order, so this
   order is part of what makes the build byte-identical.  Sections below group the
   functions by subsystem as far as that order allows. */

#define UNIT 1      /* selects this unit's declarations in duke.h */
#include "duke.h"

#undef abs
#define ACTOR_TILE_OFFSETS(i) (*((struct actor_tile_graphic_offsets *)&multi_tile_actor_sprite_offsets[(i) * 6]))

#if EPISODE == 1
#define F_BORDER0 "border.dn1"
#define F_FONT1 "font1.dn1"
#define F_FONT2 "font2.dn1"
#define F_NUMBERS "numbers.dn1"
#define F_OBJECT0 "object0.dn1"
#define F_OBJECT1 "object1.dn1"
#define F_OBJECT2 "object2.dn1"
#define F_USERDEMO "USERDEMO.DN1"
#define F_MYDEMO "MY_DEMO.DN1"
#define F_MAN0 "man0.dn1"
#define F_MAN1 "man1.dn1"
#define F_MAN2 "man2.dn1"
#define F_MAN3 "man3.dn1"
#define F_BACK0 "back0.dn1"
#define F_BACK1 "back1.dn1"
#define F_BACK2 "back2.dn1"
#define F_BACK3 "back3.dn1"
#define F_SOLID0 "solid0.dn1"
#define F_SOLID1 "solid1.dn1"
#define F_SOLID2 "solid2.dn1"
#define F_SOLID3 "solid3.dn1"
#define F_ANIM0 "anim0.dn1"
#define F_ANIM1 "anim1.dn1"
#define F_ANIM2 "anim2.dn1"
#define F_ANIM3 "anim3.dn1"
#define F_ANIM4 "anim4.dn1"
#define F_ANIM5 "anim5.dn1"
#elif EPISODE == 2
#define F_BORDER0 "border.dn2"
#define F_FONT1 "font1.dn2"
#define F_FONT2 "font2.dn2"
#define F_NUMBERS "numbers.dn2"
#define F_OBJECT0 "object0.dn2"
#define F_OBJECT1 "object1.dn2"
#define F_OBJECT2 "object2.dn2"
#define F_USERDEMO "USERDEMO.dn2"
#define F_MYDEMO "MY_DEMO.dn2"
#define F_MAN0 "man0.dn2"
#define F_MAN1 "man1.dn2"
#define F_MAN2 "man2.dn2"
#define F_MAN3 "man3.dn2"
#define F_BACK0 "back0.dn2"
#define F_BACK1 "back1.dn2"
#define F_BACK2 "back2.dn2"
#define F_BACK3 "back3.dn2"
#define F_SOLID0 "solid0.dn2"
#define F_SOLID1 "solid1.dn2"
#define F_SOLID2 "solid2.dn2"
#define F_SOLID3 "solid3.dn2"
#define F_ANIM0 "anim0.dn2"
#define F_ANIM1 "anim1.dn2"
#define F_ANIM2 "anim2.dn2"
#define F_ANIM3 "anim3.dn2"
#define F_ANIM4 "anim4.dn2"
#define F_ANIM5 "anim5.dn2"
#else
#define F_BORDER0 "border.dn3"
#define F_FONT1 "font1.dn3"
#define F_FONT2 "font2.dn3"
#define F_NUMBERS "numbers.dn3"
#define F_OBJECT0 "object0.dn3"
#define F_OBJECT1 "object1.dn3"
#define F_OBJECT2 "object2.dn3"
#define F_USERDEMO "USERDEMO.dn3"
#define F_MYDEMO "MY_DEMO.DN3"
#define F_MAN0 "man0.dn3"
#define F_MAN1 "man1.dn3"
#define F_MAN2 "man2.dn3"
#define F_MAN3 "man3.dn3"
#define F_BACK0 "back0.dn3"
#define F_BACK1 "back1.dn3"
#define F_BACK2 "back2.dn3"
#define F_BACK3 "back3.dn3"
#define F_SOLID0 "solid0.dn3"
#define F_SOLID1 "solid1.dn3"
#define F_SOLID2 "solid2.dn3"
#define F_SOLID3 "solid3.dn3"
#define F_ANIM0 "anim0.dn3"
#define F_ANIM1 "anim1.dn3"
#define F_ANIM2 "anim2.dn3"
#define F_ANIM3 "anim3.dn3"
#define F_ANIM4 "anim4.dn3"
#define F_ANIM5 "anim5.dn3"
#endif

/* ---- uninitialised data (BSS) ---- */

/* G1 BSS definitions in ascending DN1 address order. The six-byte configure_joystick_axes struct-return static precedes these globals at 0x4eca. */

int game_speed_setting;
int current_weapon_state;
int title_graphic_frame_index;
int level_play_state;
int hidden_object_state;
int actor_300e_object_state_table[100];
long high_score_values[1];
long high_score_entry_1_alias[1];
long high_score_entry_2_alias[1];
long high_score_entry_3_alias[1];
long high_score_entry_4_alias[7];
char sound_effect_priority_table[24];
char secondary_sound_priority_table[26];
int secret_block_state;
int player_animation_lock_state;
int level_hazard_count;
int level_loading_state;
char high_score_player_names[10][11];
/* UNREFERENCED: [0x5076,0x5081), 11 bytes after the 110-byte high_score_player_names[10][11] table; no accepted symbol starts or direct or based DS references land here. */
char high_score_name_edit_buffer[11];
int actor_300c_object_marker_table[100];
int actor_3035_state;
void (far *level_update_callback_table[100])(void);
int actor_3035_animation_state;
struct projectile_record projectile_records[5];
int credits_text_position;
int actor_3035_active_state;
int actor_3037_object_count;
char pending_sound_priority_flag;
int actor_3037_animation_state;
char user_demo_recording_state;
char secret_block_collision_state;
int actor_3013_formation_state;
int actor_303b_update_state;
int exit_lock_animation_state;
int secret_block_animation_state;
char game_session_abort_flag;
int actor_3048_object_count;
char pending_sound_effect_index;
int actor_302a_update_state;
int level_object_pool_531e_count;
struct contact_flash_effect_record level_collision_sound_records[17];
struct animated_actor_pool_record animated_actor_pool_records[7];
int actor_3048_entity_count;
int actor_3042_interaction_state;
char selected_save_slot;
int keyboard_hotkey_count;
char control_hint_up_flag;
char control_hint_down_flag;
char control_hint_left_flag;
char control_hint_right_flag;
char hint_revealed_object_1;
char hint_revealed_object_2;
char hint_revealed_object_3;
void interrupt far (*saved_keyboard_interrupt_vector)(void);
char hint_revealed_object_4;
char hint_revealed_object_5;
char hint_revealed_object_6;
struct actor_3012_record actor_3012_records[100];
char far *user_demo_buffer;
char hint_revealed_object_7;
struct actor_3015_record actor_3015_records[100];
char hint_revealed_object_8;
char hint_revealed_object_9;
struct falling_hazard_record falling_hazard_records[100];
char far *player_sprite_resource_buffer;
char hint_revealed_object_10;
struct actor_3022_record actor_3022_records[100];
char active_sprite_draw_flag;
char far *sprite_graphics_buffer;
char hint_revealed_object_11;
struct actor_300b_record actor_300b_records[100];
struct actor_3000_record actor_3000_records[100];
char transporter_hint_pending;
long player_score;
struct actor_3024_record actor_3024_records[100];
char far *font_glyph_data_buffer;
struct actor_3044_record actor_3044_records[15];
struct actor_3007_record actor_3007_records[100];
char draw_page_index;
struct actor_302e_record actor_302e_records[100];
struct actor_3029_record actor_3029_records[20];
struct actor_3014_record actor_3014_records[100];
struct actor_3021_record actor_3021_records[100];
struct actor_303b_record actor_303b_records[100];
char keyboard_key_d_pressed;
int joystick_x_axis_threshold_low[3];
int joystick_y_axis_threshold_low[3];
char keyboard_key_g_pressed;
unsigned int far *level_tile_map;
char keyboard_key_o_pressed;
struct actor_3009_record actor_3009_records[100];
char far *vga_lower_page_pointer;
int access_card_or_door_state;
struct actor_301b_record actor_301b_records[100];
struct actor_3023_record actor_3023_records[100];
int actor_3034_active_state;
struct animated_level_tile_record animated_level_tile_records[1000];
int joystick_x_axis_threshold_high[3];
int joystick_y_axis_threshold_high[3];
int alternate_sprite_draw_offset;
char far *saved_demo_buffer;
struct actor_302c_record actor_302c_records[100];
struct actor_301f_record actor_301f_records[100];
int episode_sprite_resource_table;
struct actor_300a_record actor_300a_records[100];
int actor_3040_world_x;
int actor_3040_world_y;
int actor_3034_world_x;
char fire_button_latch;
struct actor_301d_record actor_301d_records[100];
int actor_3034_world_y;
char far *duke_graphics_buffer;
struct actor_3037_record actor_3037_records[6];
char far *object_sprite_buffer;
char jump_button_latch;

/* ---- initialised data ---- */

/* G1 initialised data, DGROUP 0x0094..0x03a3, in definition order (rule DATA-LAYOUT).
   Proven with tail.c by `python tools/tubuild.py G1_TEXT --data`. */
char menu_action_state = 0x00;

int demo_mode_enabled = 0;

char sound_enabled = 0x00;

char demo_mode_state = 0x00;

int player_screen_x = 16;

int player_screen_y = 64;

int level_scroll_x = 0;

int level_map_y_offset = 0;

struct keyboard_character_map_entry keyboard_character_map_entries[85] = {
    { 0x4e, 0x55, 0x4c, 0x4c, 0x00, 0x00, 0x00 },
    { 0x45, 0x53, 0x43, 0x00, 0x00, 0x00, 0x00 },
    { 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x42, 0x4b, 0x53, 0x50, 0x00, 0x00, 0x00 },
    { 0x54, 0x41, 0x42, 0x00, 0x00, 0x00, 0x00 },
    { 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x45, 0x4e, 0x54, 0x52, 0x00, 0x00, 0x00 },
    { 0x43, 0x54, 0x52, 0x4c, 0x00, 0x00, 0x00 },
    { 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4c, 0x53, 0x48, 0x46, 0x54, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x52, 0x53, 0x48, 0x46, 0x54, 0x00, 0x00 },
    { 0x50, 0x52, 0x54, 0x53, 0x43, 0x00, 0x00 },
    { 0x41, 0x4c, 0x54, 0x00, 0x00, 0x00, 0x00 },
    { 0x53, 0x50, 0x41, 0x43, 0x45, 0x00, 0x00 },
    { 0x43, 0x41, 0x50, 0x4c, 0x4b, 0x00, 0x00 },
    { 0x46, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00 },
    { 0x4e, 0x55, 0x4d, 0x4c, 0x4b, 0x00, 0x00 },
    { 0x53, 0x43, 0x52, 0x4c, 0x4b, 0x00, 0x00 },
    { 0x48, 0x4f, 0x4d, 0x45, 0x00, 0x00, 0x00 },
    { 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x47, 0x55, 0x50, 0x00, 0x00, 0x00 },
    { 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x45, 0x4e, 0x44, 0x00, 0x00, 0x00, 0x00 },
    { 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x47, 0x44, 0x4e, 0x00, 0x00, 0x00 },
    { 0x49, 0x4e, 0x53, 0x00, 0x00, 0x00, 0x00 },
    { 0x44, 0x45, 0x4c, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

char key_binding_up = 0x48;

char key_binding_down = 0x50;

char key_binding_left = 0x4b;

char key_binding_right = 0x4d;

char key_binding_fire = 0x38;

char key_binding_jump = 0x1d;

char current_level_index = 0x00;

int timer_tick_counter = 0;

int formation_x_delta_table[40] = {
    0, -1, -1, -2, -2, -2, -1, -1,
    0, 1, 1, 2, 2, 2, 1, 1,
    1, 1, 1, 1, 1, 2, 1, 1,
    0, -1, -1, -2, -2, -2, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

int formation_y_delta_table[40] = {
    1, 1, 1, 1, 0, -1, -1, -1,
    -2, -1, -1, -1, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 0, -1, -1,
    -2, -1, -1, -1, 0, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0
};

int chain_keyboard_interrupt = 0;

int credit_scroll_delay = 0;

int title_graphic_animation_state = 0;

char restore_saved_game_requested = 0x00;

/* ============================================================================================
   Menus, text entry, saving and joystick setup
   In-game menus and prompts, the save-game writer, high-score entry and the joystick
   calibration screens.
   ============================================================================================ */

/* Looks up the display string for one key code and draws its first character at the requested
   position. */
void pascal draw_text_character(char scan_code, int character_x, int character_y)
{
    char character_buffer[2];

    character_buffer[0] = keyboard_character_map_entries[(unsigned char)scan_code].display_label[0];
    character_buffer[1] = 0;
    draw_text_string(character_buffer, character_x, character_y);
}

/* Queues the requested sound effect when its priority is at least the priority of the current
   sound. */
void pascal request_priority_sound_effect(int sound_effect_id)
{
    disable();
    if (sound_effect_priority_table[sound_effect_id] >= current_sound_priority) {
        current_sound_priority = sound_effect_priority_table[sound_effect_id];
        pending_sound_priority_flag = 1;
        pending_sound_effect_index = sound_effect_id;
        sound_interrupt_active_state = 0;
    }
    enable();
}

/* Opens joystick setup and runs the calibration flow for the selected setup screen. */
void select_joystick_configuration(int text_x)
{
    show_joystick_mode_status(text_x);
    calibrate_joystick_controls(1, text_x);
}

/* Displays game setup choices and dispatches joystick, keyboard, sound, or hint changes. */
void pascal handle_game_setup_input(register int text_x)
{
    draw_framed_dialog_box(text_x, 2, 4);
    outport(0x3ce, 5);
    draw_game_setup_menu(text_x);
    delay(100);
    do {
        wait_input_animated_sprite(text_x + 0x18, 0x0c);
        if (last_keyboard_scan_code == 0x24) {
            select_joystick_configuration(text_x);
            return;
        }
        if (last_keyboard_scan_code == 0x25) {
            remap_keyboard_action(text_x);
            return;
        }
        if (last_keyboard_scan_code == 0x1f) {
            toggle_sound_setting(text_x);
            return;
        }
        if (last_keyboard_scan_code == 0x23) {
            toggle_hint_mode(text_x);
            return;
        }
    } while (last_keyboard_scan_code != 0x1c && last_keyboard_scan_code != 1 && last_keyboard_scan_code != 0x39);
}

/* Reads a restore-slot choice and accepts the scan codes for slots 1 through 9. */
unsigned char pascal read_restore_slot_digit(int text_x)
{
    prompt_for_restore_slot(text_x);
    if (last_keyboard_scan_code >= 2 && last_keyboard_scan_code <= 10) {
        selected_save_slot = last_keyboard_scan_code + 0x2f;
        return 1;
    }
    return 0;
}

/* Save the game state to SAVEDn.DNx (n = slot character). */
/* Writes the current game state to the selected SAVED slot file. */
void pascal save_game_state_to_slot(char slot_character)
{
    FILE *stream;
    char *save_filename;
#if EPISODE == 1
    save_filename = "saved .dn1";
#elif EPISODE == 2
    save_filename = "saved .dn2";
#else
    save_filename = "saved .dn3";
#endif
    save_filename[5] = slot_character;
    stream = fopen(save_filename, "wb");
    putw(level_scroll_x, stream);
    putw(level_map_y_offset, stream);
    putw(player_screen_x, stream);
    putw(player_screen_y, stream);
    putw(current_level_index, stream);
    putw(world_actor_count, stream);
    putw(access_card_or_door_state, stream);
    putw(player_contact_state, stream);
    putw(title_graphic_frame_index, stream);
    putw(actor_3020_active_state, stream);
    putw(hint_revealed_object_7, stream);
    putw(hint_revealed_object_9, stream);
    putw(hint_revealed_object_2, stream);
    putw(hint_revealed_object_11, stream);
    putw(hint_revealed_object_10, stream);
    putw(hint_revealed_object_4, stream);
    putw(hint_revealed_object_5, stream);
    putw(transporter_hint_pending, stream);
    putw(hint_revealed_object_6, stream);
    putw(hint_revealed_object_1, stream);
    putw(hint_revealed_object_3, stream);
    putw(hint_revealed_object_8, stream);
    fprintf(stream, "%ld\n", player_score);
    fclose(stream);
}

/* Prompts for a save slot and saves the current game when the input is valid. */
char pascal prompt_and_save_game(int text_x)
{
    prompt_for_save_slot(text_x);
    if (last_keyboard_scan_code >= 2 && last_keyboard_scan_code <= 10) {
        save_game_state_to_slot(last_keyboard_scan_code + 0x2f);
        return 1;
    }
    return 0;
}

/* Displays the in-game help menu and handles its input and page changes. */
void pascal handle_in_game_help_menu(register int text_x)
{
    outport(0x3ce, 0x105);
    for (;;) {
        draw_framed_dialog_box(text_x, 1, 5);
        outport(0x3ce, 5);
        draw_in_game_help_menu(text_x);
        delay(100);
        for (;;) {
            wait_input_animated_sprite(0x1a, 0x0c);
            if (last_keyboard_scan_code == 1 || last_keyboard_scan_code == 0x39 || last_keyboard_scan_code == 0x1c) {
                timer_tick_counter = 0;
                return;
            }
            if (last_keyboard_scan_code == 0x1f) {
                if (current_level_index % 2 == 0) {
                    show_save_location_warning(text_x);
                    timer_tick_counter = 0;
                    return;
                }
                if (prompt_and_save_game(text_x)) {
                    show_save_success_message();
                    timer_tick_counter = 0;
                    return;
                }
                show_save_failure_message();
                break;
            }
            if (last_keyboard_scan_code == 0x23) {
                draw_high_score_table(text_x);
                while (last_keyboard_scan_code == 0x23)
                    ;
                wait_input_animated_sprite(text_x + 0x18, 0x14);
                timer_tick_counter = 0;
                return;
            }
            if (last_keyboard_scan_code == 0x17) {
                show_instruction_screen(text_x);
                timer_tick_counter = 0;
                return;
            }
            if (last_keyboard_scan_code == 1 || last_keyboard_scan_code == 0x10 || last_keyboard_scan_code == 0x39) {
                last_keyboard_scan_code = 0;
                timer_tick_counter = 0;
                return;
            }
            if (last_keyboard_scan_code == 0x22) {
                handle_game_setup_input(text_x);
                timer_tick_counter = 0;
                return;
            }
            if (last_keyboard_scan_code == 0x44) {
                menu_action_state = 1;
                timer_tick_counter = 0;
                return;
            }
        }
    }
}

/* Gotos preserve the original 981-byte timer-loop layout; structured variants differed. */
/* Shows the title screen (dn.dnX), the credits and ordering pages while idle, then the main
   menu; returns the chosen action (0 quit, 1 start, 4 record demo, 5 play the demo after the
   idle timeout). */
int pascal title_screen_and_menu(register int menu_x)
{
    unsigned long elapsed_ticks;
    unsigned char joystick_button_1_state;
    unsigned char joystick_button_2_state;

    elapsed_ticks = 0;
    joystick_button_1_state = inportb(0x201) & 0x10;
    joystick_button_2_state = inportb(0x201) & 0x20;
    if (joystick_enabled == 0) {
        joystick_button_1_state = 1;
        joystick_button_2_state = 1;
    }
    clear_video_page();

    for (;;) {
        clear_palette_entries(20);
        display_title_screen();
        restore_ega_palette(20);
        elapsed_ticks = 0;
        last_keyboard_scan_code = 0;
        while (last_keyboard_scan_code == 0 && joystick_button_1_state != 0 && joystick_button_2_state != 0) {
            if (joystick_enabled != 0) {
                joystick_button_1_state = inportb(0x201) & 0x10;
                joystick_button_2_state = inportb(0x201) & 0x20;
            }
            if (timer_tick_counter % 2 != 0) {
                ++elapsed_ticks;
                if (elapsed_ticks == 1500000UL) {
                    last_keyboard_scan_code = 0;
                    return 5;
                }
                if (elapsed_ticks == 1000000UL) {
                    clear_palette_entries(20);
                    wait_for_pause_key_release();
                    show_ordering_page_one();
                    restore_ega_palette(20);
                }
                if (elapsed_ticks == 500000UL) {
                    clear_palette_entries(20);
                    display_credits_bitmap();
                    restore_ega_palette(20);
                }
            }
        }

        if ((last_keyboard_scan_code == 0x10 || last_keyboard_scan_code == 1) && elapsed_ticks < 500000UL) {
            while (last_keyboard_scan_code == 0x10) {
            }
            if (confirm_quit_to_dos(7) != 0)
                return 0;
        }
        elapsed_ticks = 0;
        outport(0x3ce, 0x105);
        for (;;) {
            while (joystick_button_1_state == 0 || joystick_button_2_state == 0) {
                if (joystick_enabled != 0) {
                    joystick_button_1_state = inportb(0x201) & 0x10;
                    joystick_button_2_state = inportb(0x201) & 0x20;
                }
            }
            elapsed_ticks = 0;
            draw_framed_dialog_box(menu_x, 2, 8);
            outport(0x3ce, 5);
            draw_main_menu(menu_x);
            restore_ega_palette(15);
            L_064b:
            last_keyboard_scan_code = 0;
            goto L_067b;

            L_0652:
            ++elapsed_ticks;
            if (elapsed_ticks <= 12300000UL)
                goto L_067b;
            last_keyboard_scan_code = 0;
            clear_palette_entries(20);
            return 5;

            L_067b:
            if (joystick_enabled != 0) {
                joystick_button_1_state = inportb(0x201) & 0x10;
                joystick_button_2_state = inportb(0x201) & 0x20;
            }
            if (last_keyboard_scan_code == 0 && joystick_button_1_state != 0 && joystick_button_2_state != 0)
                goto L_0652;
            if (last_keyboard_scan_code == 0x1f || last_keyboard_scan_code == 0x39 || last_keyboard_scan_code == 0x1c)
                return 1;
            if (joystick_button_1_state == 0 || joystick_button_2_state == 0) {
                while (joystick_button_1_state == 0 || joystick_button_2_state == 0) {
                    if (joystick_enabled != 0) {
                        joystick_button_1_state = inportb(0x201) & 0x10;
                        joystick_button_2_state = inportb(0x201) & 0x20;
                    }
                }
                if (control_confirmation_state == 0 && joystick_enabled != 0)
                    select_joystick_configuration(menu_x);
                if (control_confirmation_state == 0)
                    continue;
                clear_palette_entries(20);
                return 1;
            }

            if (last_keyboard_scan_code == 0xc0 && control_fire_pressed != 0 && demo_mode_enabled != 0)
                return 4;
            if (last_keyboard_scan_code == 0x2e) {
                while (last_keyboard_scan_code == 0x2e) {
                }
                clear_palette_entries(15);
                display_credits_bitmap();
                restore_ega_palette(15);
                last_keyboard_scan_code = 0;
                while (last_keyboard_scan_code == 0) {
                }
            } else if (last_keyboard_scan_code == 0x23) {
                draw_high_score_table(menu_x);
                while (last_keyboard_scan_code == 0x23) {
                }
                wait_input_animated_sprite(menu_x + 0x18, 20);
            } else if (last_keyboard_scan_code == 0x2f) {
                if (user_demo_recording_state != 0) {
                    show_save_unavailable_message();
                } else {
                    return 2;
                }
            } else if (last_keyboard_scan_code == 0x13) {
                return 3;
            } else if (last_keyboard_scan_code == 0x19) {
                return 5;
            } else if (last_keyboard_scan_code == 0x17) {
                clear_palette_entries(15);
                show_story_game_instructions();
            } else if (last_keyboard_scan_code == 1 || last_keyboard_scan_code == 0x10) {
                while (last_keyboard_scan_code == 0x10) {
                }
                if (confirm_quit_to_dos(7) != 0)
                    return 0;
            } else if (last_keyboard_scan_code == 0x22) {
                handle_game_setup_input(menu_x);
            } else if (last_keyboard_scan_code == 0x14) {
                break;
            } else if (last_keyboard_scan_code == 0x18) {
                clear_palette_entries(15);
                wait_for_pause_key_release();
                show_ordering_page_one();
                wait_input_animated_sprite(0x27, 0x18);
                clear_video_page();
                show_ordering_page_two();
                wait_input_animated_sprite(0x27, 0x18);
            } else {
                goto L_064b;
            }
            clear_palette_entries(15);
            display_title_screen();
        }
    }
}

/* Keep the volatile parameters in sync with the declaration in DUKE.H. */
/* Reads a line of player-name text from the keyboard into the supplied buffer. */
void pascal read_text_entry(volatile int text_x, volatile int text_y, char far *text_buffer)
{
    register int i = 0;

    last_keyboard_scan_code = 0;
    for (;;) {
        wait_input_animated_sprite(text_x + i + 1, text_y);
        if (last_keyboard_scan_code == 0x1c) {
            text_buffer[i] = 0;
            return;
        }
        if (last_keyboard_scan_code == 0x0e) {
            if (i > 0)
                --i;
        } else if (i < 10) {
            if ((last_keyboard_scan_code >= 0x10 && last_keyboard_scan_code <= 0x19) ||
                (last_keyboard_scan_code >= 0x2c && last_keyboard_scan_code <= 0x32) ||
                (last_keyboard_scan_code >= 0x1e && last_keyboard_scan_code <= 0x26)) {
                text_buffer[i] = keyboard_character_map_entries[(unsigned char)last_keyboard_scan_code].display_label[0];
                ++i;
                draw_text_character(last_keyboard_scan_code, text_x + i, text_y);
            } else if (last_keyboard_scan_code == 0x39) {
                text_buffer[i] = ' ';
                ++i;
            }
        }
    }
}

/* Goto retains the pre-test loop entry; structured loop forms emitted different code. */
/* Inserts the current score into the high-score table and prompts for the player's name when it
   qualifies. */
void insert_score_into_high_scores(void)
{
    register int entry;
    register int slot;

    slot = 0;
    goto test;
    do {
        if ((unsigned long)high_score_values[slot] < (unsigned long)player_score) {
            entry = 10;
            while (entry > slot) {
                high_score_values[entry] = high_score_values[entry - 1];
                strcpy(high_score_player_names[entry], high_score_player_names[entry - 1]);
                --entry;
            }
            high_score_player_names[slot][0] = 0;
            high_score_values[slot] = player_score;
            draw_framed_dialog_box(7, 2, 5);
            request_priority_sound_effect(0x18);
            draw_high_score_name_screen();
            while (last_keyboard_scan_code == 0x15) {
            }
            read_text_entry(0x0e, 0x0b, high_score_player_names[slot]);
            return;
        }
        ++slot;
        test:
        ;
    } while (slot < 8);
}

/* Draws the current title-screen graphic frame on both video pages. */
void draw_title_screen_graphic(void)
{
    register int i;
    for (i = 0; i < 8; ++i) {
        select_draw_page(draw_page_index);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x26c0, i + 0x1e, 0x3c);
        if (title_graphic_frame_index - 1 > i)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2620, i + 0x1e, 0x3c);
        select_draw_page(!draw_page_index);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x26c0, i + 0x1e, 0x3c);
        if (title_graphic_frame_index - 1 > i)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2620, i + 0x1e, 0x3c);
        title_graphic_animation_state = 0;
    }
}

/* Advances the title-screen graphic frame and redraws it. */
void advance_title_screen_animation(void)
{
    if (title_graphic_frame_index < 9)
        title_graphic_frame_index++;
    draw_title_screen_graphic();
}

/* Advances and draws the active buffered screen effects. */
void draw_buffered_screen_effect(void)
{
    register int effect_index;

    for (effect_index = 0; effect_index < world_actor_count; effect_index++) {
        select_draw_page(draw_page_index);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1ae0, 0x21, 0x60);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x500, effect_index * 2 + 0x1e, 0x6c);
        select_draw_page(!draw_page_index);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1ae0, 0x21, 0x60);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x500, effect_index * 2 + 0x1e, 0x6c);
    }
}

/* Add to the score and redraw it on both pages (resets display on wrap to 0). */
/* Adds the supplied amount to the player's score and redraws the score display. */
void pascal add_and_draw_player_score(long value)
{
    outport(0x3ce, 5);
    player_score += value;
    if (player_score == 0L) {
        select_draw_page(0);
        draw_unsigned_score_value(10000000L, 0x25, 3);
        draw_unsigned_score_value(0L, 0x1e, 3);
        select_draw_page(1);
        draw_unsigned_score_value(10000000L, 0x25, 3);
        draw_unsigned_score_value(0L, 0x1e, 3);
    }
    select_draw_page(0);
    draw_unsigned_score_value(player_score, 0x25, 3);
    select_draw_page(1);
    draw_unsigned_score_value(player_score, 0x25, 3);
}

/* Samples joystick axes, maps them to directional controls, and returns the two button states. */
struct joystick_button_sample configure_joystick_axes(register int joystick_mode)
{
    int axis_x_reading;
    int axis_y_reading;
    int x_direction;
    int y_direction;
    struct joystick_button_sample button_state;
    register int port_value;

    axis_x_reading = 0;
    axis_y_reading = 0;
    x_direction = 0;
    y_direction = 0;

    sample_joystick_axes(joystick_mode, &axis_x_reading, &axis_y_reading);
    if ((axis_x_reading > 500) | (axis_y_reading > 500)) {
        axis_x_reading = joystick_x_axis_threshold_high[joystick_mode] + 1;
        axis_y_reading = joystick_y_axis_threshold_high[joystick_mode] + 1;
    }

    if (joystick_x_axis_threshold_low[joystick_mode] < axis_x_reading)
        x_direction = 1;
    else if (joystick_x_axis_threshold_high[joystick_mode] > axis_x_reading)
        x_direction = -1;

    if (joystick_y_axis_threshold_low[joystick_mode] < axis_y_reading)
        y_direction = 1;
    else if (joystick_y_axis_threshold_high[joystick_mode] > axis_y_reading)
        y_direction = -1;

    /* Map the joystick axes to the four screen-direction flags. */
    switch (y_direction * 3 + x_direction) {
    case -4:
        control_up_pressed = 1;
        control_left_pressed = 1;
        control_right_pressed = 0;
        control_down_pressed = 0;
        break;
    case -3:
        control_up_pressed = 1;
        control_left_pressed = 0;
        control_right_pressed = 0;
        control_down_pressed = 0;
        break;
    case -2:
        control_up_pressed = 1;
        control_left_pressed = 0;
        control_right_pressed = 1;
        control_down_pressed = 0;
        break;
    case -1:
        control_up_pressed = 0;
        control_left_pressed = 1;
        control_right_pressed = 0;
        control_down_pressed = 0;
        break;
    case  0:
        control_up_pressed = 0;
        control_left_pressed = 0;
        control_right_pressed = 0;
        control_down_pressed = 0;
        break;
    case  1:
        control_up_pressed = 0;
        control_left_pressed = 0;
        control_right_pressed = 1;
        control_down_pressed = 0;
        break;
    case  2:
        control_up_pressed = 0;
        control_left_pressed = 1;
        control_right_pressed = 0;
        control_down_pressed = 1;
        break;
    case  3:
        control_up_pressed = 0;
        control_left_pressed = 0;
        control_right_pressed = 0;
        control_down_pressed = 1;
        break;
    case  4:
        control_up_pressed = 0;
        control_left_pressed = 0;
        control_right_pressed = 1;
        control_down_pressed = 1;
        break;
    }

    port_value = inportb(0x201);
    if (joystick_mode == 1) {
        button_state.first_button_pressed = ((port_value & 0x10) == 0) ? 1 : 0;
        button_state.second_button_pressed = ((port_value & 0x20) == 0) ? 1 : 0;
    } else {
        button_state.first_button_pressed = ((port_value & 0x40) == 0) ? 1 : 0;
        button_state.second_button_pressed = ((port_value & 0x80) == 0) ? 1 : 0;
    }
    if (joystick_configuration_mode != 0) {
        port_value = button_state.first_button_pressed;
        button_state.first_button_pressed = button_state.second_button_pressed;
        button_state.second_button_pressed = port_value;
    }

    return button_state;
}

/* ---- initialised data, placed here for the literal pool ---- */

/* G1 initialised data, DGROUP 0x03a4..0x0721.  Defined after save_game_state_to_slot and before calibrate_joystick_controls so the
   strings of the level-file table episode_level_filename_table land at their original place in the literal pool. */
#if EPISODE == 1

char far *episode_level_filename_table[21] = {

    "worldal1.dn1",
    "worldal2.dn1",
    "worldal3.dn1",
    "worldal2.dn1",
    "worldal4.dn1",
    "worldal2.dn1",
    "worldal5.dn1",
    "worldal2.dn1",
    "worldal6.dn1",
    "worldal2.dn1",
    "worldal7.dn1",
    "worldal2.dn1",
    "worldal8.dn1",
    "worldal2.dn1",
    "worldal9.dn1",
    "worldal2.dn1",
    "worldala.dn1",
    "worldal2.dn1",
    "worldalb.dn1",
    "worldal2.dn1",
    "worldalc.dn1"

};

#elif EPISODE == 2

char far *episode_level_filename_table[21] = {

    "worldal1.dn2",
    "worldal2.dn2",
    "worldal3.dn2",
    "worldal2.dn2",
    "worldal4.dn2",
    "worldal2.dn2",
    "worldal5.dn2",
    "worldal2.dn2",
    "worldal6.dn2",
    "worldal2.dn2",
    "worldal7.dn2",
    "worldal2.dn2",
    "worldal8.dn2",
    "worldal2.dn2",
    "worldal9.dn2",
    "worldal2.dn2",
    "worldala.dn2",
    "worldal2.dn2",
    "worldalb.dn2",
    "worldal2.dn2",
    "worldalc.dn2"

};

#elif EPISODE == 3

char far *episode_level_filename_table[21] = {

    "worldal1.dn3",
    "worldal2.dn3",
    "worldal3.dn3",
    "worldal2.dn3",
    "worldal4.dn3",
    "worldal2.dn3",
    "worldal5.dn3",
    "worldal2.dn3",
    "worldal6.dn3",
    "worldal2.dn3",
    "worldal7.dn3",
    "worldal2.dn3",
    "worldal8.dn3",
    "worldal2.dn3",
    "worldal9.dn3",
    "worldal2.dn3",
    "worldala.dn3",
    "worldal2.dn3",
    "worldalb.dn3",
    "worldal2.dn3",
    "worldalc.dn3"

};

#endif

int d_03f8[10] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0
};

int menu_selection_state = 0;

int user_demo_input_length = 0;

int saved_demo_input_length = 0;

int actor_motion_delta_table[18] = {
    -64, -32, -16, -8, 0, 8, 16, 16,
    32, 32, 32, 64, 64, 128, 128, 128,
    128, 128
};

char interaction_cooldown_state = 0x00;

int world_animation_phase = 0;

char player_death_state = 0x00;

char player_action_state = 0x04;

char player_animation_phase = 0x00;

int actor_3000_count = 0;

int collision_sound_record_count = 10;

int contact_flash_delta_table_a[27] = {
    0, 0, -71, 0, -59, 0, -45, 0,
    -33, -1, -25, 0, -10, 0, -1, 0,
    13, 0, 16, -1, 19, 0, 31, 0,
    54, 0, 66
};

int contact_flash_delta_table_b[27] = {
    0, 0, -50, 1, -47, 0, -33, 1,
    -23, 0, -10, 1, 8, 0, 21, 0,
    33, 0, 46, 1, 19, 0, 29, 0,
    38, 0, 50
};

int contact_flash_delta_table_c[27] = {
    0, 0, 1, -1, 8, -1, 17, -1,
    29, -1, 32, -1, 45, -1, 51, -1,
    65, -1, 79, -1, 79, -1, 99, -1,
    99, 0, 99
};

int contact_flash_delta_table_d[27] = {
    0, 0, 1, 1, 3, 1, 7, 1,
    9, 1, 12, 1, 15, 1, 21, 1,
    25, 1, 29, 1, 36, 1, 40, 1,
    40, 0, 40
};

int ambient_object_count = 19;

int animated_actor_count = 4;

int projectile_count = 3;

int moving_object_count = 5;

int pickup_object_count = 10;

int moving_actor_count = 8;

int actor_3001_count = 0;

int actor_3002_count = 0;

int actor_3006_world_x = 0;

int actor_3006_world_y = 0;

int actor_3006_state = 0;

int actor_3008_state = 0;

int actor_3020_world_x = 0;

int actor_3020_world_y = 0;

int actor_3020_state = 0;

int actor_3033_world_x = 0;

int actor_3033_world_y = 0;

int actor_3033_state = 0;

int actor_3033_enabled = 0;

int actor_3007_count = 0;

int actor_3009_count = 0;

int actor_300a_count = 0;

int actor_300b_count = 0;

int moving_item_path_delta_table_a[24] = {
    0, -64, 1, -32, 1, -16, 0, -1,
    0, 0, 1, 12, 1, 24, 0, 46,
    1, 128, 0, 128, 1, 256, 0, 0
};

int moving_item_path_delta_table_b[24] = {
    0, -64, -1, -32, -1, -16, 0, -1,
    0, 0, -1, 12, -1, 24, 0, 46,
    -1, 128, -1, 128, -1, 256, 0, 0
};

int actor_300b_screen_anim_offset = 0;

int actor_300b_animation_frame = 0;

int actor_300c_count = 0;

int actor_300d_count = 0;

int actor_300e_animation_state = 0;

int actor_300e_animation_counter = 0;

int actor_300e_count = 0;

int actor_300f_count = 0;

int actor_3010_count = 0;

int actor_3012_count = 0;

int actor_3014_count = 0;

int actor_3015_count = 0;

int actor_3016_count = 0;

int actor_3018_count = 0;

int actor_301a_count = 0;

int actor_301b_count = 0;

int actor_301d_count = 0;

int actor_301e_count = 0;

int actor_301f_count = 0;

int actor_3021_count = 0;

int actor_3022_count = 0;

int actor_3023_count = 0;

int actor_3024_count = 0;

int actor_3025_count = 0;

int actor_3029_count = 0;

int actor_302a_count = 0;

int actor_302c_count = 0;

int actor_302d_count = 0;

int actor_302e_count = 0;

int actor_3031_count = 0;

int level_vertical_motion_table[14] = {
    128, 96, 64, 32, 8, 4, 1, -1,
    -4, -8, -32, -64, -96, -128
};

int actor_303c_count = 0;

int actor_303b_count = 0;

int actor_3042_animation_frame_0 = 0;

int actor_3042_animation_frame_1 = 0;

int actor_3042_animation_frame_2 = 0;

int actor_3042_animation_frame_3 = 0;

int actor_3042_animation_frame_4 = 0;

int actor_3042_animation_frame_5 = 10;

int gameplay_animation_flag = 0;

char player_airborne_state = 0x01;

char player_damage_immunity_state = 0x00;

char player_jump_frame = 0x00;

struct player_jump_motion_row player_jump_motion_rows[2] = {
    { { 0x0d, 0x0b, 0x09, 0x07, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { { 0x0f, 0x0d, 0x0b, 0x09, 0x07, 0x05, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00 } }
};

int d_062b[12] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};

char keyboard_modifier_state = 0x00;

char player_sprite_draw_state = 0x00;

/* not referenced by any code */
char d_0645 = 0x50;

int world_effect_sprite_offset = 0;

int projectile_flash_sprite_offset = 0;

int ambient_object_sprite_offset = 0;

int contact_flash_cycle_index = 0;

int actor_3002_animation_phase = 0;

int multi_tile_actor_sprite_offsets[36] = {
    -1, -1, 160, 320, 480, 640, -1, -1,
    160, 320, 800, 960, 1120, 1280, 1440, 1600,
    1760, 1920, -1, -1, 2080, 2240, 2400, 2560,
    -1, -1, 2080, 2240, 2720, 2880, 3040, 3200,
    3360, 3520, 3680, 3840
};

int actor_300c_motion_delta_table[34] = {
    1, 256, 2, 128, 0, 64, 1, 32,
    0, 16, 1, 8, 0, 4, 1, 2,
    0, 1, 1, -1, 0, -2, 1, -4,
    0, -8, 1, -16, 0, -32, 1, -64,
    0, -128
};

int actor_300d_animation_phase = 0;

int actor_300d_animation_counter = 0;

int actor_3010_sprite_offset = 0;

char door_interaction_phase = 0x00;

int actor_3013_sprite_offset = 0;

int actor_3014_sprite_offset = 0;

int actor_3015_sprite_offset = 0;

int actor_3016_upper_sprite_offset = 0;

int actor_3016_lower_sprite_offset = 640;

int actor_301a_sprite_offset = 0;

int actor_3021_sprite_offset = 0;

int actor_3022_animation_phase = 0;

int actor_3023_sprite_offset = 0;

int actor_3024_sprite_offset = 0;

int actor_3029_sprite_offset = 0;

int actor_302a_sprite_offset = 0;

int actor_302b_sprite_offset = 0;

char actor_302c_animation_phase = 0x00;

int actor_302d_sprite_offset = 0;

int actor_303c_animation_phase = 0;

int actor_3042_motion_delta_table[12] = {
    128, 92, 64, 32, 16, 8, -8, -16,
    -32, -64, -92, -128
};

int actor_3041_sprite_frame = 0;

int actor_3041_animation_counter = 0;

int actor_3041_event_pending = 0;

int actor_3041_sprite_offset = 0;

/* Guides joystick calibration and records the measured axis thresholds. */
void calibrate_joystick_controls(register int joystick_mode, int text_x)
{
    int x_threshold_margin, y_threshold_margin;
    int first_x_reading, first_y_reading, second_x_reading, second_y_reading;
    struct joystick_button_sample button_state;
    register int i;

    for (;;) {
        do {
            button_state = configure_joystick_axes(joystick_mode);
        } while (button_state.first_button_pressed == 1 || button_state.second_button_pressed == 1);
        prompt_joystick_calibration(text_x);
        while (last_keyboard_scan_code == 0x24) {
        }
        i = 0x0f;
        do {
            if (++i == 0x17)
                i = 0x0f;
            sample_joystick_axes(joystick_mode, &first_x_reading, &first_y_reading);
            button_state = configure_joystick_axes(joystick_mode);
            wait_for_keyboard_or_joystick(text_x + 9, 0x0b);
            if (last_keyboard_scan_code != 0)
                return;
        } while (button_state.first_button_pressed != 1 && button_state.second_button_pressed != 1);
        do {
            button_state = configure_joystick_axes(joystick_mode);
        } while (button_state.first_button_pressed == 1 || button_state.second_button_pressed == 1);
        draw_text_string(" Hold the joystick in the", text_x, 0x0d);
        draw_text_string(" bottom right and press a", text_x, 0x0e);
        draw_text_string(" button.", text_x, 0x0f);
        do {
            if (++i == 0x17)
                i = 0x0f;
            sample_joystick_axes(joystick_mode, &second_x_reading, &second_y_reading);
            button_state = configure_joystick_axes(joystick_mode);
            wait_for_keyboard_or_joystick(text_x + 9, 0x0f);
            if (last_keyboard_scan_code != 0)
                return;
        } while (button_state.first_button_pressed != 1 && button_state.second_button_pressed != 1);
        do {
            button_state = configure_joystick_axes(joystick_mode);
        } while (button_state.first_button_pressed == 1 || button_state.second_button_pressed == 1);
        x_threshold_margin = (second_x_reading - first_x_reading) / 6;
        y_threshold_margin = (second_y_reading - first_y_reading) / 6;
        joystick_x_axis_threshold_high[joystick_mode] = first_x_reading + x_threshold_margin;
        joystick_x_axis_threshold_low[joystick_mode] = second_x_reading - x_threshold_margin;
        joystick_y_axis_threshold_high[joystick_mode] = first_y_reading + y_threshold_margin;
        joystick_y_axis_threshold_low[joystick_mode] = second_y_reading - y_threshold_margin;
        draw_text_string(" Should button 1 (S)hoot", text_x, 0x11);
        draw_text_string(" or (J)ump?", text_x, 0x12);
        wait_input_animated_sprite(text_x + 0x0c, 0x12);
        if (last_keyboard_scan_code == 1)
            return;
        if (last_keyboard_scan_code == 0x1f)
            joystick_configuration_mode = 1;
        else
            joystick_configuration_mode = 0;
        control_confirmation_state = 1;
        joystick_enabled = 1;
        while (last_keyboard_scan_code == 0x1f || last_keyboard_scan_code == 0x24) {
        }
        return;
    }
}

/* Joystick buttons from game port 0x201: 1 = button A, 2 = button B, 0 = none. */
/* Reads the joystick game-port button bits and returns the selected button state. */
int read_joystick_button(void)
{
    register int port_value = inportb(0x201);

    if (!(port_value & 0x10))
        return 1;
    if (!(port_value & 0x20))
        return 2;
    return 0;
}

/* Samples the joystick until both reported buttons have been released. */
void wait_joystick_button_release(void)
{
    struct joystick_button_sample button_state;

    do {
        button_state = configure_joystick_axes(1);
    } while (button_state.first_button_pressed == 1 || button_state.second_button_pressed == 1);
}

/* Reads the joystick button port and updates the game's fire and jump control flags. */
void update_joystick_axis_state(void)
{
    char port_value;

    port_value = inportb(0x201);
    if (joystick_configuration_mode != 0) {
        control_jump_pressed = !(port_value & 0x10);
        control_fire_pressed = !(port_value & 0x20);
    } else {
        control_jump_pressed = !(port_value & 0x20);
        control_fire_pressed = !(port_value & 0x10);
    }
}

/* Reads a planar image resource and uploads its four data planes to the requested VGA memory
   offset. */
void pascal load_planar_image_file(char far *filename, register int offset, int count)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    if (filename[0] != 0) {
        vga_lower_page_pointer = MK_FP(0xa000, 0);
        vga_upper_page_pointer = MK_FP(0xa000, 0x4000);
        count /= 4;
        fgetc(stream);
        fgetc(stream);
        fgetc(stream);
        for (i = 0; i < count; ++i) {
            fgetc(stream);
            /* TC 2.0 emits different code for subscripting this far pointer. */
            outport(0x3c4, 0x0102);
            *(vga_upper_page_pointer + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0202);
            *(vga_upper_page_pointer + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0402);
            *(vga_upper_page_pointer + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0802);
            *(vga_upper_page_pointer + i + offset) = fgetc(stream);
        }
        fclose(stream);
    }
}

/* ============================================================================================
   Player collision probes
   Tests of the tiles around the player against the level map.
   ============================================================================================ */

/* Tests the player floor clearance and returns the result to its caller. */
char test_player_floor_clearance(void)
{
    unsigned int far *base_tile_pointer;
    unsigned int far *above_tile_pointer;
    unsigned int far *below_tile_pointer;

    base_tile_pointer = level_tile_map + ((player_screen_x + level_scroll_x - 3) >> 1) + level_map_y_offset + (((player_screen_y - 16) >> 4) * 128);
    below_tile_pointer = base_tile_pointer;
    above_tile_pointer = base_tile_pointer - 128;
    if ((player_screen_y >> 3) & 1)
        below_tile_pointer += 128;
    if (base_tile_pointer[0] > 0x17ffU)
        return 0;
    if (above_tile_pointer[0] > 0x17ffU)
        return 0;
    if (below_tile_pointer[0] > 0x17ffU)
        return 0;
    return 1;
}

/* Tests the player body clearance and returns the result to its caller. */
unsigned char test_player_body_clearance(void)
{
    unsigned int far *tile_pointer;
    unsigned int far *above_tile_pointer;
    unsigned int far *below_tile_pointer;

    tile_pointer = level_tile_map + ((level_scroll_x + player_screen_x) >> 1) + level_map_y_offset
        + (((player_screen_y - 16) >> 4) * 128);
    below_tile_pointer = tile_pointer;
    above_tile_pointer = tile_pointer - 128;
    if ((player_screen_y >> 3) & 1)
        below_tile_pointer += 128;
    if (*tile_pointer > 0x17ff || *above_tile_pointer > 0x17ff || *below_tile_pointer > 0x17ff)
        return 0;
    return 1;
}

/* Tests the map cells above the player's head and updates damage or sound state when the space
   is blocked. */
char test_player_head_clearance(void)
{
    unsigned int far *head_tile_pointer;
    unsigned int far *adjacent_head_tile_pointer;

    head_tile_pointer = level_tile_map + ((player_screen_x + level_scroll_x - 2) >> 1) + level_map_y_offset
        + (((player_screen_y - 40) >> 4) * 128);
    adjacent_head_tile_pointer = head_tile_pointer;

    if ((player_screen_x + level_scroll_x) & 1)
        ++adjacent_head_tile_pointer;

    if (*head_tile_pointer >= 0x2ee0 || *adjacent_head_tile_pointer >= 0x2ee0 ||
        (*head_tile_pointer >= 0x1b80 && *head_tile_pointer <= 0x1ca0) ||
        (*adjacent_head_tile_pointer >= 0x1b80 && *adjacent_head_tile_pointer <= 0x1ca0)) {
        if (player_invulnerability_state != 0)
            return 0;
        if (player_damage_immunity_state != 0)
            return 0;
        if (player_death_state == 0)
            player_animation_phase = 0;
        if (player_contact_state != 0) {
            player_death_state = 1;
            player_sprite_draw_state = 1;
            request_priority_sound_effect(0x1b);
        }
        else {
            request_priority_sound_effect(0x26);
        }
        return 0;
    }

    player_death_state = 0;
    if (*head_tile_pointer > 0x17ff || *adjacent_head_tile_pointer > 0x17ff) {
        if (player_death_state == 0)
            request_priority_sound_effect(0x26);
        return 0;
    }
    return 1;
}

/* Gotos preserve the branch layout; structured returns emitted a 113-byte near match. */
/* Tests the player level clearance and returns the result to its caller. */
char test_player_level_clearance(void)
{
    unsigned int far *player_tile_pointer;
    unsigned int far *adjacent_player_tile_pointer;

    if (player_invulnerability_state)
        goto zero_result;

    player_tile_pointer = level_tile_map + ((player_screen_x + level_scroll_x - 2) >> 1) + level_map_y_offset + ((player_screen_y >> 4) * 128);
    adjacent_player_tile_pointer = player_tile_pointer;
    if ((player_screen_x + level_scroll_x) & 1)
        adjacent_player_tile_pointer++;

    if (*player_tile_pointer > 0x17ff)
        goto zero_result;
    if (*adjacent_player_tile_pointer <= 0x17ff)
        goto one_result;

zero_result:
    return 0;

one_result:
    return 1;
}

/* Draws the visible level strip from the tile map and advances its animated-tile phase. */
void draw_animated_level_strip(void)
{
    register int screen_offset;
    register int strip_column_index;
    unsigned int far *tile_map_pointer;
    int bitmap_offset;

    screen_offset = 0x282 - (level_scroll_x & 1);
    strip_column_index = 0;
    tile_map_pointer = level_tile_map + (level_scroll_x >> 1) + level_map_y_offset;
    bitmap_offset = 0x4000;
    outport(0x3ce, 0x105);
    world_animation_phase += 0x20;
    if (world_animation_phase == 0x80)
        world_animation_phase = 0;
    do {
        if (level_scroll_x & 1) {
            if (*tile_map_pointer == 0 || tile_map_pointer[1] == 0)
                blit_bitmap_to_video_page(bitmap_offset, screen_offset + 1);
            else if (*tile_map_pointer == 0x20 || tile_map_pointer[1] == 0x20)
                blit_bitmap_to_video_page(bitmap_offset + 0x4100, screen_offset + 1);
        } else {
            if (*tile_map_pointer == 0)
                blit_bitmap_to_video_page(bitmap_offset, screen_offset);
            else if (*tile_map_pointer == 0x20)
                blit_bitmap_to_video_page(bitmap_offset + 0x4100, screen_offset);
        }
        if (*tile_map_pointer > 0x20) {
            if (*tile_map_pointer < 0x5e0)
                blit_bitmap_to_video_page(*tile_map_pointer + world_animation_phase, screen_offset);
            else
                blit_bitmap_to_video_page(*tile_map_pointer, screen_offset);
        }
        ++tile_map_pointer;
        screen_offset += 2;
        if (++strip_column_index == 14) {
            screen_offset += 0x264;
            tile_map_pointer += 0x72;
            strip_column_index = 0;
        } else {
            bitmap_offset += 0x20;
        }
    } while (screen_offset < 0x191c);
    outport(0x3ce, 5);
}

/* ============================================================================================
   Keyboard interrupt
   INT 9 handler: reads the scan code from port 0x60 and keeps the key-state flags.
   ============================================================================================ */

/* Handles keyboard IRQ 9 scan codes, updates held-key state, acknowledges the controller, and
   chains when requested. */
void interrupt keyboard_interrupt_handler(void)
{
    last_keyboard_scan_code = inportb(0x60);

    if (player_animation_lock_state == 0 && current_weapon_state == 0 && control_confirmation_state == 0 &&
        player_level_transition_state == 0 && actor_302f_interaction_state == 0 && actor_3030_interaction_state == 0) {
        if (last_keyboard_scan_code == key_binding_up) {
            control_up_pressed = 1;
        }
        if (last_keyboard_scan_code == (key_binding_up | 0x80)) {
            control_up_pressed = 0;
        }
        if (last_keyboard_scan_code == key_binding_down) {
            control_down_pressed = 1;
        }
        if (last_keyboard_scan_code == (key_binding_down | 0x80)) {
            control_down_pressed = 0;
        }
        if (last_keyboard_scan_code == key_binding_left) {
            control_left_pressed = 1;
        }
        if (last_keyboard_scan_code == (key_binding_left | 0x80)) {
            control_left_pressed = 0;
        }
        if (last_keyboard_scan_code == key_binding_right) {
            control_right_pressed = 1;
        }
        if (last_keyboard_scan_code == (key_binding_right | 0x80)) {
            control_right_pressed = 0;
        }
        if (last_keyboard_scan_code == key_binding_jump) {
            control_jump_pressed = 1;
        }
        if (last_keyboard_scan_code == (key_binding_jump | 0x80)) {
            control_jump_pressed = 0;
        }
        if (last_keyboard_scan_code == key_binding_fire) {
            control_fire_pressed = 1;
        }
        if (last_keyboard_scan_code == (key_binding_fire | 0x80)) {
            control_fire_pressed = 0;
        }
    }

    if (last_keyboard_scan_code == 0x33) {
        keyboard_modifier_state = 1;
    }
    if (last_keyboard_scan_code == 0xb3) {
        keyboard_modifier_state = 0;
    }
    if (last_keyboard_scan_code == 0x34) {
        keyboard_control_lock_state = 1;
    }
    if (last_keyboard_scan_code == 0xb4) {
        keyboard_control_lock_state = 0;
    }
    if (last_keyboard_scan_code == 0x0e) {
        keyboard_backspace_pressed = 1;
    }
    if (last_keyboard_scan_code == 0x8e) {
        keyboard_backspace_pressed = 0;
    }
    if (last_keyboard_scan_code == 0x51) {
        keyboard_interrupt_state = 1;
    }
    if (last_keyboard_scan_code == 0xd1) {
        keyboard_interrupt_state = 0;
    }
    if (last_keyboard_scan_code == 0x22) {
        keyboard_key_g_pressed = 1;
    }
    if (last_keyboard_scan_code == 0xa2) {
        keyboard_key_g_pressed = 0;
    }
    if (last_keyboard_scan_code == 0x18) {
        keyboard_key_o_pressed = 1;
    }
    if (last_keyboard_scan_code == 0x98) {
        keyboard_key_o_pressed = 0;
    }
    if (last_keyboard_scan_code == 0x20) {
        keyboard_key_d_pressed = 1;
    }
    if (last_keyboard_scan_code == 0xa0) {
        keyboard_key_d_pressed = 0;
    }

    if (chain_keyboard_interrupt != 0)
        saved_keyboard_interrupt_vector();

    /* Acknowledge the keyboard IRQ at the controller and then the PIC. */
    outportb(0x61, inportb(0x61) | 0x80);
    outportb(0x61, inportb(0x61) & 0x7f);
    outportb(0x20, 0x20);
}

/* ============================================================================================
   Player, projectiles and contact effects
   Drawing the player, the shots and their collisions, the per-frame player and level update.
   ============================================================================================ */

/* Draws the player's current action sprite from the player sprite resource. */
void draw_player_action_sprite(int sprite_frame, int sprite_x, int sprite_y)
{
    register int sprite_offset;

    sprite_offset = sprite_frame * 4 * 0xa0;
    if (current_weapon_state >= 4)
        return;
    if (player_animation_lock_state != 0)
        return;
    if (player_projectile_state > 0)
        --player_projectile_state;
    if (sprite_y >= 0x20 && player_projectile_state % 2 == 0) {
        blit_planar_sprite_rows((player_sprite_resource_buffer+ sprite_offset), sprite_x - 1, sprite_y - 0x10);
        blit_planar_sprite_rows((player_sprite_resource_buffer+ sprite_offset + 0xa0), sprite_x + 1, sprite_y - 0x10);
    }
    if (sprite_y >= 0x10) {
        if (player_projectile_state % 2 == 0) {
            blit_planar_sprite_rows((player_sprite_resource_buffer+ sprite_offset + 0x140), sprite_x - 1, sprite_y);
            blit_planar_sprite_rows((player_sprite_resource_buffer+ sprite_offset + 0x1e0), sprite_x + 1, sprite_y);
        }
    } else {
        player_sprite_draw_state = 1;
    }
}

/* Adds a world actor record at the supplied coordinates with the requested actor state. */
void pascal spawn_world_actor(register int world_x, int world_y, int actor_state)
{
    register int i;
    struct world_actor_record far *actor_record;

    for (i = 0; i < world_actor_count; ++i) {
        actor_record = &world_actor_records[i];
        if (actor_record->state == 0) {
            request_priority_sound_effect(6);
            actor_record->contact_marker = 1;
            actor_record->state = actor_state + 1;
            actor_record->world_x = world_x;
            actor_record->world_y = world_y;
            return;
        }
    }
}

/* Moves and draws the active moving world effects and spawns follow-up actors when they hit
   special tiles. */
void update_moving_world_effects(void)
{
    register int i;
    struct world_actor_record far *actor_record;

    world_effect_sprite_offset += 0xa0;
    if (world_effect_sprite_offset == 0x140)
        world_effect_sprite_offset = 0;

    for (i = 0; i < world_actor_count; ++i) {
        actor_record = &world_actor_records[i];

        if (actor_record->state == 0)
            continue;

        if (actor_record->state == 1) {
            actor_record->world_x -= 2;
            secret_block_collision_state = 1;
            if (test_level_tile_special_state(actor_record->world_x + 1, actor_record->world_y)) {
                actor_record->state = 0;
                spawn_moving_actor(1, actor_record->world_x + 1, actor_record->world_y + 64);
                continue;
            }
            if (!is_world_position_outside_view(actor_record->world_x, actor_record->world_y)) {
                if (actor_record->contact_marker == 0)
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + world_effect_sprite_offset + 0x3c0,
                                            actor_record->world_x - level_scroll_x,
                                            ((actor_record->world_y - level_map_y_offset) >> 3) + 0x13);
            } else {
                actor_record->state = 0;
            }
            if (actor_record->contact_marker != 0) {
                actor_record->contact_marker = 0;
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1cc0,
                                        actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 0x13);
            }
        }

        if (actor_record->state == 5) {
            actor_record->world_x += 2;
            secret_block_collision_state = 1;
            if (test_level_tile_special_state(actor_record->world_x, actor_record->world_y)) {
                actor_record->state = 0;
                spawn_moving_actor(1, actor_record->world_x - 1, actor_record->world_y + 64);
                continue;
            }
            if (!is_world_position_outside_view(actor_record->world_x, actor_record->world_y)) {
                if (actor_record->contact_marker == 0)
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + world_effect_sprite_offset + 0x500,
                                            actor_record->world_x - level_scroll_x,
                                            ((actor_record->world_y - level_map_y_offset) >> 3) + 0x13);
            } else {
                actor_record->state = 0;
            }
            if (actor_record->contact_marker != 0) {
                actor_record->contact_marker = 0;
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1d60,
                                        actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 0x13);
            }
        }
    }
    secret_block_collision_state = 0;
}

/* Clears every projectile slot. */
void pascal clear_projectiles(void)
{
    register int i;

    for (i = 0; i < projectile_count; i++) {
        projectile_records[i].active = 0;
        projectile_records[i].projectile_marker = 0;
    }
}

/* Puts a projectile in the first free slot (direction, world position) and plays its sound when
   it is on screen. */
void pascal spawn_projectile(register int projectile_direction, int world_x, int world_y)
{
    register int i;
    struct projectile_record far *projectile_record;
    for (i = 0; i < projectile_count; ++i) {
        projectile_record = &projectile_records[i];
        if (projectile_record->active == 0) {
            projectile_record->active = projectile_direction;
            projectile_record->world_x = world_x;
            projectile_record->world_y = world_y;
            projectile_record->projectile_marker = 1;
            if (is_world_position_outside_view(projectile_record->world_x, projectile_record->world_y) == 0)
                request_priority_sound_effect(11);
            return;
        }
    }
}

/* Shared success/clear targets stay as gotos because direct updates changed code size. */
/* Checks active projectiles against level tiles and the player, then removes or updates
   colliding shots. */
void resolve_projectile_collisions(void)
{
    register int i;
    struct projectile_record far *projectile_record;

    projectile_flash_sprite_offset += 0xa0;
    if (projectile_flash_sprite_offset == 0x140)
        projectile_flash_sprite_offset = 0;

    for (i = 0; i < projectile_count; ++i) {
        projectile_record = &projectile_records[i];
        if (projectile_record->active == 0)
            continue;

        if (projectile_record->active == 1) {
            if (test_player_overlap_with_object(projectile_record->world_x, projectile_record->world_y)) {
                if (active_sprite_draw_flag != 0)
                    goto success_update;
                if (player_projectile_state != 0)
                    goto success_update;
                if (test_player_floor_clearance() == 0)
                    goto success_update;
                --player_screen_x;
                goto success_update;
            } else {
                --projectile_record->world_x;
                if (test_level_tile_special_state(projectile_record->world_x, projectile_record->world_y) != 0)
                    goto clear_record;
                if (test_level_tile_special_state(projectile_record->world_x, projectile_record->world_y + 64) != 0)
                    goto clear_record;
                if (is_world_position_outside_view(projectile_record->world_x, projectile_record->world_y) == 0) {
                    if (projectile_record->projectile_marker != 0) {
                        projectile_record->projectile_marker = 0;
                        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1e00,
                                                projectile_record->world_x - level_scroll_x,
                                                ((projectile_record->world_y - level_map_y_offset) >> 3) + 0x13);
                    } else {
                        blit_planar_sprite_rows(sprite_pixel_data_pointer + projectile_flash_sprite_offset + 0x1860,
                                                projectile_record->world_x - level_scroll_x,
                                                ((projectile_record->world_y - level_map_y_offset) >> 3) + 0x13);
                    }
                } else {
                    projectile_record->active = 0;
                }
            }
        }

        if (projectile_record->active == 2) {
            if (test_player_overlap_with_object(projectile_record->world_x, projectile_record->world_y)) {
                if (active_sprite_draw_flag == 0 && player_projectile_state == 0 && test_player_body_clearance())
                    ++player_screen_x;
                success_update:
                projectile_record->active = 0;
                active_sprite_draw_flag = 1;
            } else {
                ++projectile_record->world_x;
                if (test_level_tile_special_state(projectile_record->world_x + 1, projectile_record->world_y) != 0)
                    goto clear_record;
                if (test_level_tile_special_state(projectile_record->world_x + 1, projectile_record->world_y + 64) != 0)
                    goto clear_record;
                if (is_world_position_outside_view(projectile_record->world_x, projectile_record->world_y) != 0)
                    goto clear_record;
                if (projectile_record->projectile_marker != 0) {
                    projectile_record->projectile_marker = 0;
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1ea0,
                                            projectile_record->world_x - level_scroll_x,
                                            ((projectile_record->world_y - level_map_y_offset) >> 3) + 0x13);
                } else {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + projectile_flash_sprite_offset + 0x19a0,
                                            projectile_record->world_x - level_scroll_x,
                                            ((projectile_record->world_y - level_map_y_offset) >> 3) + 0x13);
                }
            }
        }
        goto loop_continue;
        clear_record:
        projectile_record->active = 0;
        loop_continue:
        ;
    }
}

/* Updates player movement, level scrolling, animation, and nearby level effects. */
void update_player_and_level_state(void)
{
    if (active_sprite_draw_flag != 0 && player_projectile_state != 0)
        active_sprite_draw_flag = 0;
    if (title_graphic_animation_state == 0) {
        if (test_player_level_clearance() != 0 && player_airborne_state != 0) {
            player_airborne_state = 0;
            player_damage_immunity_state = 1;
        }
        if (player_airborne_state == 0 && player_death_state == 0) {
            if (player_sprite_refresh_state != 0)
                ++player_sprite_animation_index;
            if (player_sprite_animation_index == 14) {
                player_sprite_animation_index = 0;
                player_sprite_refresh_state = 0;
            }
            if (test_player_head_clearance() == 0 && player_sprite_refresh_state != 0) {
                player_sprite_refresh_state = 0;
                player_sprite_animation_index = 0;
            }
            if (player_damage_immunity_state == 0 && player_jump_frame < 9 && test_player_head_clearance() != 0) {
                player_screen_y -= player_jump_motion_rows[access_card_or_door_state].vertical_displacements[player_jump_frame];
                ++player_jump_frame;
                player_sprite_draw_state = 0;
                if (test_player_level_clearance() == 0) {
                    player_airborne_state = 1;
                    player_sprite_draw_state = 1;
                    /* Snap the vertical position down to a 16-unit row boundary. */
                    player_screen_y = (player_screen_y >> 4) << 4;
                    allocate_collision_record(player_screen_x + level_scroll_x,
                                              (((player_screen_y - 16) >> 4) * 128) + level_map_y_offset);
                    request_priority_sound_effect(14);
                    player_sprite_refresh_state = 0;
                    player_sprite_animation_index = 0;
                }
            } else {
                player_damage_immunity_state = 1;
            }
            if (player_damage_immunity_state != 0) {
                if (test_player_level_clearance() == 0) {
                    player_airborne_state = 1;
                    player_sprite_draw_state = 1;
                    player_damage_immunity_state = 0;
                    player_sprite_refresh_state = 0;
                    player_sprite_animation_index = 0;
                    player_screen_y = (player_screen_y >> 4) << 4;
                    allocate_collision_record(player_screen_x + level_scroll_x,
                                              (((player_screen_y - 16) >> 4) * 128) + level_map_y_offset);
                    request_priority_sound_effect(14);
                } else {
                    player_screen_y += 8;
                }
                if (test_player_level_clearance() == 0) {
                    player_screen_y = (player_screen_y >> 4) << 4;
                    allocate_collision_record(player_screen_x + level_scroll_x,
                                              (((player_screen_y - 16) >> 4) * 128) + level_map_y_offset);
                    request_priority_sound_effect(14);
                    player_sprite_refresh_state = 0;
                    player_sprite_animation_index = 0;
                    player_sprite_draw_state = 1;
                }
                if (player_screen_y >= 132) {
                    player_screen_y += 8;
                    player_sprite_draw_state = 1;
                    if (test_player_level_clearance() == 0) {
                        player_airborne_state = 1;
                        player_jump_frame = 0;
                        player_damage_immunity_state = 0;
                        player_screen_y = (player_screen_y >> 4) << 4;
                        allocate_collision_record(player_screen_x + level_scroll_x,
                                                  (((player_screen_y - 16) >> 4) * 128) + level_map_y_offset);
                        request_priority_sound_effect(14);
                    }
                }
            }
        }
        if (control_up_pressed != 0 && player_death_state != 0 && player_invulnerability_state == 0) {
            player_screen_y -= 16;
            if (test_player_head_clearance() != 0) {
                player_screen_y -= 16;
                if (test_player_head_clearance() != 0) {
                    player_invulnerability_state = 3;
                    player_death_state = 0;
                }
                player_screen_y += 16;
            } else {
                player_invulnerability_state = 0;
                player_death_state = 1;
            }
            player_screen_y += 16;
        }
        if (control_down_pressed != 0 && player_death_state != 0) {
            player_animation_phase = 0;
            player_death_state = 0;
        }
        if ((player_death_state == 0 || control_fire_pressed == 0) && control_right_pressed == 0 &&
            control_left_pressed != 0 && player_invulnerability_state == 0) {
            if (player_action_state == 0 && test_player_floor_clearance() != 0)
                --player_screen_x;
            if (player_action_state != 0) {
                player_action_state = 0;
                player_animation_phase = 0;
                player_sprite_refresh_state = 0;
            } else if (world_animation_phase == 0 || world_animation_phase == 0x40) {
                if (test_player_level_clearance() == 0)
                    request_priority_sound_effect(0x16);
                if (player_animation_phase < 3)
                    ++player_animation_phase;
                else
                    player_animation_phase = 0;
            }
        }
        if (player_screen_x == 11) {
            if (level_scroll_x > 0) {
                --level_scroll_x;
                ++player_screen_x;
            }
        } else if (player_screen_x <= 10 && level_scroll_x > 1) {
            level_scroll_x -= 2;
            player_screen_x += 2;
            if (level_scroll_x == 1) {
                ++player_screen_x;
                --level_scroll_x;
            }
        }
        if ((player_death_state == 0 || control_fire_pressed == 0) && control_left_pressed == 0 &&
            control_right_pressed != 0 && player_invulnerability_state == 0) {
            if (player_action_state != 0 && test_player_body_clearance() != 0)
                ++player_screen_x;
            if (player_action_state == 0) {
                player_action_state = 4;
                player_animation_phase = 0;
                player_sprite_refresh_state = 0;
            } else if (world_animation_phase == 0 || world_animation_phase == 0x40) {
                if (test_player_level_clearance() == 0)
                    request_priority_sound_effect(0x16);
                if (player_animation_phase < 3)
                    ++player_animation_phase;
                else
                    player_animation_phase = 0;
            }
        }
        if (player_screen_x == 17) {
            if (level_scroll_x < 230) {
                ++level_scroll_x;
                --player_screen_x;
            }
        } else if (player_screen_x >= 18 && level_scroll_x < 230) {
            level_scroll_x += 2;
            player_screen_x -= 2;
            if (level_scroll_x == 229) {
                --player_screen_x;
                ++level_scroll_x;
            }
        }
        if (player_death_state != 0) {
            player_screen_y = (player_screen_y >> 4) << 4;
            player_damage_immunity_state = 1;
            player_airborne_state = 0;
            test_player_head_clearance();
        }
        if (control_jump_pressed != 0 && player_airborne_state != 0 && jump_button_latch == 0 &&
            player_death_state == 0 && player_invulnerability_state == 0) {
            player_airborne_state = 0;
            player_jump_frame = 0;
            player_damage_immunity_state = 0;
            if (access_card_or_door_state != 0 && world_animation_phase == 0) {
                if (control_left_pressed != 0 && test_player_floor_clearance() != 0)
                    player_sprite_refresh_state = 1;
                if (control_right_pressed != 0 && test_player_body_clearance() != 0)
                    player_sprite_refresh_state = 2;
            }
            request_priority_sound_effect(13);
        }
        if (control_jump_pressed != 0 && player_death_state == 0)
            jump_button_latch = 1;
        else
            jump_button_latch = 0;
    }
    draw_animated_level_strip();
    update_actor_3035();
    draw_animated_level_tile();
    update_actor_3024();
    handle_door_and_key_interaction();
    update_actor_3040();
    update_level_lock_or_exit();
    update_actor_3001();
    update_actor_3034();
    update_actor_3048();
    if (title_graphic_animation_state != 0)
        return;
    if (player_death_state != 0 && control_fire_pressed == 0 && player_invulnerability_state == 0 && active_sprite_draw_flag == 0) {
        if (player_action_state == 0)
            draw_player_action_sprite(0x1c + player_animation_phase, player_screen_x, player_screen_y);
        else
            draw_player_action_sprite(0x20 + player_animation_phase, player_screen_x, player_screen_y);
        if ((control_left_pressed == 0 && control_right_pressed != 0) ||
            (control_right_pressed == 0 && control_left_pressed != 0)) {
            if (world_animation_phase == 0x20 || world_animation_phase == 0x60)
                request_priority_sound_effect(0x1b);
        }
    }
    if (player_death_state != 0 && control_fire_pressed != 0 && player_invulnerability_state == 0 && active_sprite_draw_flag == 0) {
        if (player_action_state == 0)
            draw_player_action_sprite(0x24, player_screen_x, player_screen_y);
        else
            draw_player_action_sprite(0x25, player_screen_x, player_screen_y);
    }
    if (control_fire_pressed != 0 && control_left_pressed == 0 && control_right_pressed == 0 && player_death_state == 0 &&
        player_invulnerability_state == 0 && active_sprite_draw_flag == 0)
        player_animation_phase = 3;
    if (player_sprite_refresh_state == 0 && control_left_pressed == 0 && control_right_pressed == 0 && control_fire_pressed == 0 &&
        player_death_state == 0 && player_invulnerability_state == 0 && active_sprite_draw_flag == 0) {
        if (player_action_state == 0)
            player_animation_phase = 0x0c;
        else
            player_animation_phase = 9;
    }
    if (((player_damage_immunity_state == 0 && player_airborne_state != 0) || test_player_level_clearance() == 0) &&
        player_sprite_refresh_state == 0 &&
        player_death_state == 0 && player_invulnerability_state == 0 && active_sprite_draw_flag == 0)
        draw_player_action_sprite(player_action_state + player_animation_phase, player_screen_x, player_screen_y);
    if (player_airborne_state == 0 && test_player_level_clearance() != 0 && player_sprite_refresh_state == 0 && player_death_state == 0 &&
        player_invulnerability_state == 0 && active_sprite_draw_flag == 0) {
        if (player_damage_immunity_state == 0) {
            if (player_action_state == 0)
                draw_player_action_sprite(player_action_state + 8, player_screen_x, player_screen_y);
            else
                draw_player_action_sprite(player_action_state + 5, player_screen_x, player_screen_y);
        } else if (player_action_state == 0) {
            draw_player_action_sprite(player_action_state + 10, player_screen_x, player_screen_y);
        } else {
            draw_player_action_sprite(player_action_state + 7, player_screen_x, player_screen_y);
        }
    }
    if (player_invulnerability_state != 0 && active_sprite_draw_flag == 0) {
        --player_invulnerability_state;
        player_screen_y -= 16;
        if (player_action_state == 0)
            draw_player_action_sprite(0x28 - player_invulnerability_state, player_screen_x, player_screen_y);
        else
            draw_player_action_sprite(0x2b - player_invulnerability_state, player_screen_x, player_screen_y);
        if (player_invulnerability_state == 0)
            player_sprite_draw_state = 1;
    }
    if (player_sprite_refresh_state != 0 && player_death_state == 0 && player_invulnerability_state == 0 && active_sprite_draw_flag == 0) {
        if (player_sprite_refresh_state == 1) {
            switch (player_sprite_animation_index) {
                case 0:
                case 1:
                    draw_player_action_sprite(0x0e, player_screen_x, player_screen_y);
                    break;
                case 2:
                case 3:
                    draw_player_action_sprite(0x0f, player_screen_x, player_screen_y);
                    break;
                case 4:
                case 5:
                    draw_player_action_sprite(0x10, player_screen_x, player_screen_y);
                    break;
                case 6:
                case 7:
                    draw_player_action_sprite(0x11, player_screen_x, player_screen_y);
                    break;
                case 8:
                case 9:
                    draw_player_action_sprite(0x12, player_screen_x, player_screen_y);
                    break;
                case 10:
                case 11:
                    draw_player_action_sprite(0x13, player_screen_x, player_screen_y);
                    break;
                case 12:
                case 13:
                    draw_player_action_sprite(0x14, player_screen_x, player_screen_y);
                    break;
            }
        } else if (player_sprite_refresh_state == 2) {
            switch (player_sprite_animation_index) {
                case 0:
                case 1:
                    draw_player_action_sprite(0x15, player_screen_x, player_screen_y);
                    break;
                case 2:
                case 3:
                    draw_player_action_sprite(0x16, player_screen_x, player_screen_y);
                    break;
                case 4:
                case 5:
                    draw_player_action_sprite(0x17, player_screen_x, player_screen_y);
                    break;
                case 6:
                case 7:
                    draw_player_action_sprite(0x18, player_screen_x, player_screen_y);
                    break;
                case 8:
                case 9:
                    draw_player_action_sprite(0x19, player_screen_x, player_screen_y);
                    break;
                case 10:
                case 11:
                    draw_player_action_sprite(0x1a, player_screen_x, player_screen_y);
                    break;
                case 12:
                case 13:
                    draw_player_action_sprite(0x1b, player_screen_x, player_screen_y);
                    break;
            }
        }
    }
    if (control_fire_pressed != 0 && fire_button_latch == 0 && active_sprite_draw_flag == 0) {
        if (gameplay_animation_flag == 0)
            spawn_world_actor(player_screen_x + level_scroll_x,
                              (((player_screen_y - 29) >> 4) * 128) + level_map_y_offset, player_action_state);
        if (player_death_state != 0) {
            if (player_action_state != 0)
                player_animation_phase = 5;
            else
                player_animation_phase = 8;
        }
    }
    if (control_fire_pressed != 0) {
        fire_button_latch = 1;
    } else {
        fire_button_latch = 0;
    }
    if (active_sprite_draw_flag == 0 || player_projectile_state != 0) {
        return;
    }
    player_gameplay_state = 0;
    if (title_graphic_animation_state == 0) {
        --title_graphic_frame_index;
        draw_title_screen_graphic();
    }
    request_priority_sound_effect(15);
    active_sprite_draw_flag = 0;
    player_projectile_state = 0x15;
    player_jump_frame = 0;
    player_airborne_state = 0;
    player_death_state = 0;
    player_damage_immunity_state = 1;
    player_sprite_refresh_state = 0;
    player_sprite_animation_index = 0;
    if (player_action_state == 0)
        draw_player_action_sprite(0x2c, player_screen_x, player_screen_y);
    else
        draw_player_action_sprite(0x2d, player_screen_x, player_screen_y);
}

/* Moves the player and vertical map offset during a level transition animation. */
void advance_player_transition(void)
{
    if (player_animation_lock_state == 0 && player_sprite_draw_state != 0) {
        if (player_screen_y < 100 && level_map_y_offset > 0) {
            level_map_y_offset -= 128;
            player_screen_y += 16;
            if (player_screen_y >= 100)
                player_sprite_draw_state = 0;
        } else if (player_screen_y > 112) {
            level_map_y_offset += 128;
            player_screen_y -= 16;
            if (player_screen_y <= 112)
                player_sprite_draw_state = 0;
        }
    }
}

/* ============================================================================================
   Object pools and collision helpers
   Small fixed pools (moving actors, pickups, ambient sprites, flashes) and the tests
   shared by the actors: visibility, overlap with the player, blocked map cells.
   ============================================================================================ */

/* Skips the three-byte resource header and reads the requested byte block into a buffer. */
void read_file_block(char far *filename, void far *buffer, unsigned int count)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    fgetc(stream);
    fgetc(stream);
    fgetc(stream);
    fread(buffer, count, 1, stream);
    fclose(stream);
}

/* Adds a used coordinate record to the first free object-collision slot. */
void pascal allocate_collision_record(register int world_x, int world_y)
{
    register int i;
    struct collision_effect_record far *collision_effect_record;

    for (i = 0; i < moving_object_count; ++i) {
        collision_effect_record = &object_collision_pool_records[i];
        if (collision_effect_record->active == 0) {
            collision_effect_record->active = 1;
            collision_effect_record->world_x = world_x;
            collision_effect_record->world_y = world_y;
            break;
        }
    }
}

/* Clear the first word of every 8-byte actor_302a_record in table ambient_object_records[0..ambient_object_count). */
/* Clears the active flags in the ambient-object pool. */
void pascal clear_ambient_object_pool(void)
{
    register int i;

    for (i = 0; i < ambient_object_count; i++)
        ambient_object_records[i].active = 0;
}

/* Queues an ambient sprite animation with a resource offset and world coordinates. */
void pascal queue_ambient_sprite_animation(register int sprite_offset, int world_x, int world_y)
{
    register int i;
    struct ambient_object_record far *ambient_object_record;

    for (i = 0; i < ambient_object_count; i++) {
        ambient_object_record = &ambient_object_records[i];
        if (ambient_object_record->active == 0) {
            ambient_object_record->active = 1;
            ambient_object_record->world_x = world_x;
            ambient_object_record->world_y = world_y;
            ambient_object_record->sprite_offset = sprite_offset;
            break;
        }
    }
}

/* Advances, culls, and draws the queued ambient sprite animations. */
void animate_ambient_sprite_records(void)
{
    register int i;
    struct ambient_object_record far *ambient_object_record;

    ambient_object_sprite_offset += 0xa0;
    if (ambient_object_sprite_offset > 0xa0)
        ambient_object_sprite_offset = 0;

    for (i = 0; i < ambient_object_count; ++i) {
        ambient_object_record = &ambient_object_records[i];
        if (is_world_position_outside_view(ambient_object_record->world_x, ambient_object_record->world_y) != 0) {
            if (ambient_object_record->sprite_offset < 0x8c0) {
                ambient_object_record->active = 0;
                continue;
            }
        }
        if (ambient_object_record->active == 0)
            continue;

        ambient_object_record->world_y -= 8;
        if (is_world_position_outside_view(ambient_object_record->world_x, ambient_object_record->world_y) == 0) {
            blit_planar_sprite_rows(object_sprite_buffer + ambient_object_record->sprite_offset + ambient_object_sprite_offset,
                                    ambient_object_record->world_x - level_scroll_x,
                                    ((ambient_object_record->world_y - level_map_y_offset) >> 3) + 0x10);
        }
        ++ambient_object_record->active;
        if (ambient_object_record->sprite_offset < 0x8c0 && ambient_object_record->active == 0x28)
            ambient_object_record->active = 0;
        if (ambient_object_record->sprite_offset >= 0x8c0 && ambient_object_record->active == 0x2bc)
            ambient_object_record->active = 0;
    }
}

/* Creates a moving actor record with the supplied kind and world coordinates. */
void pascal spawn_moving_actor(register int actor_kind, int world_x, int world_y)
{
    register int i;
    struct moving_actor_record far *moving_actor;

    for (i = 0; i < moving_actor_count; i++) {
        moving_actor = &moving_actor_records[i];
        if (moving_actor->state == 0) {
            moving_actor->state = 1;
            moving_actor->world_x = world_x;
            moving_actor->world_y = world_y;
            moving_actor->actor_kind = actor_kind;
            break;
        }
    }
}

/* Advances and draws the moving-actor pool, removing actors blocked by level tiles. */
void update_moving_actor_pool(void)
{
    register int i;
    struct moving_actor_record far *moving_actor;

    for (i = 0; i < moving_actor_count; ++i) {
        moving_actor = &moving_actor_records[i];
        if (moving_actor->state != 0) {
            if (is_world_position_outside_view(moving_actor->world_x, moving_actor->world_y) == 0) {
                if (moving_actor->actor_kind == 3) {
                    ++moving_actor->state;
                    if (moving_actor->state == 2) {
                        blit_planar_sprite_rows(sprite_graphics_buffer + 0x8160,
                                                moving_actor->world_x - level_scroll_x,
                                                ((moving_actor->world_y - level_map_y_offset) >> 3) + 16);
                    }
                    if (moving_actor->state == 4) {
                        if (is_world_position_outside_view(moving_actor->world_x - 1, moving_actor->world_y - 64) == 0)
                            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8200,
                                                    moving_actor->world_x - level_scroll_x - 1,
                                                    ((moving_actor->world_y - level_map_y_offset) >> 3) + 8);
                        if (is_world_position_outside_view(moving_actor->world_x + 1, moving_actor->world_y - 64) == 0)
                            blit_planar_sprite_rows(sprite_graphics_buffer + 0x82a0,
                                                    moving_actor->world_x - level_scroll_x + 1,
                                                    ((moving_actor->world_y - level_map_y_offset) >> 3) + 8);
                        if (is_world_position_outside_view(moving_actor->world_x - 1, moving_actor->world_y + 64) == 0)
                            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8340,
                                                    moving_actor->world_x - level_scroll_x - 1,
                                                    ((moving_actor->world_y - level_map_y_offset) >> 3) + 24);
                        if (is_world_position_outside_view(moving_actor->world_x + 1, moving_actor->world_y + 64) == 0)
                            blit_planar_sprite_rows(sprite_graphics_buffer + 0x83e0,
                                                    moving_actor->world_x - level_scroll_x + 1,
                                                    ((moving_actor->world_y - level_map_y_offset) >> 3) + 24);
                        moving_actor->state = 0;
                    }
                } else {
                    if (moving_actor->actor_kind == 1) {
                        blit_planar_sprite_rows(sprite_graphics_buffer + moving_actor->state * 0xa0 + 0x19a0,
                                                moving_actor->world_x - level_scroll_x,
                                                ((moving_actor->world_y - level_map_y_offset) >> 3) + 16);
                    } else {
                        if (test_player_overlap_with_object(moving_actor->world_x, moving_actor->world_y) != 0)
                            active_sprite_draw_flag = 1;
                        blit_planar_sprite_rows(sprite_graphics_buffer + moving_actor->state * 0xa0 + 0x37a0,
                                                moving_actor->world_x - level_scroll_x,
                                                ((moving_actor->world_y - level_map_y_offset) >> 3) + 16);
                    }
                    ++moving_actor->state;
                    if (moving_actor->state == 7)
                        moving_actor->state = 0;
                }
            } else {
                moving_actor->state = 0;
            }
        }
    }
}

/* Creates a used level-object record at the supplied world coordinates. */
void pascal spawn_pickup_object(register int world_x, int world_y)
{
    register int i;
    struct pickup_object_record far *pickup_object;

    for (i = 0; i < pickup_object_count; i++) {
        pickup_object = &free_object_pool_records[i];
        if (pickup_object->active == 0) {
            pickup_object->active = 1;
            pickup_object->world_x = world_x;
            pickup_object->world_y = world_y;
            break;
        }
    }
}

/* Advances and draws active pickup-object records. */
void update_pickup_object_pool(void)
{
    register int i;
    struct pickup_object_record far *pickup_object;

    for (i = 0; i < pickup_object_count; i++) {
        pickup_object = &free_object_pool_records[i];
        if (pickup_object->active != 0) {
            if (is_world_position_outside_view(pickup_object->world_x, pickup_object->world_y) == 0) {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + pickup_object->active * 0xa0 + 0x14a0,
                                        pickup_object->world_x - level_scroll_x,
                                        ((pickup_object->world_y - level_map_y_offset) >> 3) + 16);
                pickup_object->active++;
                if (pickup_object->active == 6)
                    pickup_object->active = 0;
            } else {
                pickup_object->active = 0;
            }
        }
    }
}

/* Updates and draws active collision-effect records at their stored world positions. */
void update_collision_effect_pool(void)
{
    register int i;
    struct collision_effect_record far *collision_effect;

    for (i = 0; i < moving_object_count; ++i) {
        collision_effect = &object_collision_pool_records[i];
        if (collision_effect->active != 0) {
            if (is_world_position_outside_view(collision_effect->world_x, collision_effect->world_y) == 0) {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + collision_effect->active * 0xa0 + 0xb40,
                                        collision_effect->world_x - level_scroll_x,
                                        ((collision_effect->world_y - level_map_y_offset) >> 3) + 16);
                ++collision_effect->active;
                if (collision_effect->active != 6)
                    continue;
            }
            collision_effect->active = 0;
        }
    }
}

/* Creates an animated-actor record with the supplied sprite frame and vertical position. */
void pascal spawn_animated_actor_sprite(register int world_x, int world_y)
{
    register int i;
    struct animated_actor_pool_record far *animated_actor;

    for (i = 0; i < animated_actor_count; i++) {
        animated_actor = &animated_actor_pool_records[i];
        if (animated_actor->animation_state == 0) {
            animated_actor->animation_state = 1;
            animated_actor->sprite_frame_index = world_x;
            animated_actor->vertical_position = world_y;
            break;
        }
    }
}

/* Draws the two adjacent sprite cells for an actor when each cell is inside the view. */
void pascal draw_actor_sprite_pair(int frame, int world_x, int world_y)
{
    register int sprite_offset;

    sprite_offset = frame * 0x140 + 0x5b40;
    if (is_world_position_outside_view(world_x, world_y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset,
                                world_x - level_scroll_x,
                                ((world_y - level_map_y_offset) >> 3) + 16);
    }
    if (is_world_position_outside_view(world_x + 2, world_y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0xa0,
                                world_x - level_scroll_x + 2,
                                ((world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Advances active animated-actor records and draws their current sprite frames. */
void update_animated_actor_pool(void)
{
    register int i;
    struct animated_actor_pool_record far *animated_actor;

    for (i = 0; i < animated_actor_count; i++) {
        animated_actor = &animated_actor_pool_records[i];
        if (animated_actor->animation_state != 0) {
            animated_actor->animation_state++;
            animated_actor->vertical_position += actor_motion_delta_table[animated_actor->animation_state - 2];
            if (animated_actor->animation_state < 16) {
                draw_actor_sprite_pair((animated_actor->animation_state - 2) / 3, animated_actor->sprite_frame_index, animated_actor->vertical_position);
            }
            if (animated_actor->animation_state == 18)
                animated_actor->animation_state = 0;
        }
    }
}

/* Creates a four-part contact flash at the supplied world position and requests its sound
   effect. */
void pascal spawn_contact_flash_effect(int world_x, int world_y)
{
    register int i;
    struct contact_flash_effect_record far *contact_flash;

    contact_flash_cycle_index++;
    if (contact_flash_cycle_index > 3)
        contact_flash_cycle_index = 0;
    for (i = 0; i < collision_sound_record_count; i++) {
        contact_flash = &level_collision_sound_records[i];
        if (contact_flash->effect_values[0] == 0) {
            contact_flash->effect_values[0] = 1;
            contact_flash->effect_values[1] = world_x;
            contact_flash->effect_values[2] = world_y;
            contact_flash->effect_values[3] = world_x + 1;
            contact_flash->effect_values[4] = world_y;
            contact_flash->effect_values[5] = world_x;
            contact_flash->effect_values[6] = world_y + 8;
            contact_flash->effect_values[7] = world_x + 1;
            contact_flash->effect_values[8] = world_y + 8;
            switch (contact_flash_cycle_index) {
            case 0:
                contact_flash->effect_values[9] = 0xa0;
                contact_flash->effect_values[10] = 0x140;
                contact_flash->effect_values[11] = 0x1e0;
                contact_flash->effect_values[12] = 0x280;
                break;
            case 1:
                contact_flash->effect_values[9] = 0x280;
                contact_flash->effect_values[10] = 0xa0;
                contact_flash->effect_values[11] = 0x140;
                contact_flash->effect_values[12] = 0x1e0;
                break;
            case 2:
                contact_flash->effect_values[9] = 0x140;
                contact_flash->effect_values[10] = 0x280;
                contact_flash->effect_values[11] = 0x1e0;
                contact_flash->effect_values[12] = 0xa0;
                break;
            case 3:
                contact_flash->effect_values[9] = 0x1e0;
                contact_flash->effect_values[10] = 0x280;
                contact_flash->effect_values[11] = 0x140;
                contact_flash->effect_values[12] = 0xa0;
                break;
            }
            request_priority_sound_effect(10);
            return;
        }
    }
}

/* Returns nonzero when a world position lies outside the current horizontal or vertical view
   bounds. */
char pascal is_world_position_outside_view(int world_x, int world_y)
{
    if (world_x >= level_scroll_x &&
        level_scroll_x + 29 > world_x &&
        level_map_y_offset - 64 <= world_y &&
        level_map_y_offset + 1280 > world_y)
        return 0;
    return 1;
}

/* Advances and draws the four-part contact flash records. */
void animate_contact_flash_effects(void)
{
    register int i;
    struct contact_flash_effect_record far *contact_flash;

    for (i = 0; i < collision_sound_record_count; ++i) {
        contact_flash = &level_collision_sound_records[i];
        if (contact_flash->effect_values[0] != 0) {
            if (contact_flash->effect_values[0] != 0) {
                /* Delta tables interleave x/y values; keep the pointer offsets for TC output. */
                contact_flash->effect_values[1] += contact_flash_delta_table_a[contact_flash->effect_values[0]];
                contact_flash->effect_values[2] += (contact_flash_delta_table_a + 1)[contact_flash->effect_values[0]];
                contact_flash->effect_values[3] += contact_flash_delta_table_b[contact_flash->effect_values[0]];
                contact_flash->effect_values[4] += (contact_flash_delta_table_b + 1)[contact_flash->effect_values[0]];
                contact_flash->effect_values[5] += contact_flash_delta_table_c[contact_flash->effect_values[0]];
                contact_flash->effect_values[6] += (contact_flash_delta_table_c + 1)[contact_flash->effect_values[0]];
                contact_flash->effect_values[7] += contact_flash_delta_table_d[contact_flash->effect_values[0]];
                contact_flash->effect_values[8] += (contact_flash_delta_table_d + 1)[contact_flash->effect_values[0]];

                if (is_world_position_outside_view(contact_flash->effect_values[1], contact_flash->effect_values[2]) == 0 &&
                    is_world_position_outside_view(contact_flash->effect_values[1], contact_flash->effect_values[2] + 128) == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + contact_flash->effect_values[9],
                                            contact_flash->effect_values[1] - level_scroll_x,
                                            ((contact_flash->effect_values[2] - level_map_y_offset) >> 3) + 16);
                }
                if (is_world_position_outside_view(contact_flash->effect_values[3], contact_flash->effect_values[4]) == 0 &&
                    is_world_position_outside_view(contact_flash->effect_values[3], contact_flash->effect_values[4] + 128) == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + contact_flash->effect_values[10],
                                            contact_flash->effect_values[3] - level_scroll_x,
                                            ((contact_flash->effect_values[4] - level_map_y_offset) >> 3) + 16);
                }
                if (is_world_position_outside_view(contact_flash->effect_values[5], contact_flash->effect_values[6]) == 0 &&
                    is_world_position_outside_view(contact_flash->effect_values[5], contact_flash->effect_values[6] + 128) == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + contact_flash->effect_values[11],
                                            contact_flash->effect_values[5] - level_scroll_x,
                                            ((contact_flash->effect_values[6] - level_map_y_offset) >> 3) + 16);
                }
                if (is_world_position_outside_view(contact_flash->effect_values[7], contact_flash->effect_values[8]) == 0 &&
                    is_world_position_outside_view(contact_flash->effect_values[7], contact_flash->effect_values[8] + 128) == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + contact_flash->effect_values[12],
                                            contact_flash->effect_values[7] - level_scroll_x,
                                            ((contact_flash->effect_values[8] - level_map_y_offset) >> 3) + 16);
                }
                contact_flash->effect_values[0] += 2;
                if (contact_flash->effect_values[0] == 23)
                    contact_flash->effect_values[0] = 0;
            }
        }
    }
}

/* Returns whether the supplied world position overlaps the player's current position. */
int test_player_overlap_with_object(int world_x, int world_y)
{
    register int player_y_delta = player_screen_y;

    /* Convert the fixed-point scroll offset to 128-unit map rows. */
    player_y_delta >>= 4;
    player_y_delta <<= 7;
    player_y_delta += level_map_y_offset;
    player_y_delta -= world_y;
    player_y_delta++;
    player_y_delta++;

    if (abs(player_screen_x + level_scroll_x - world_x) < 2 && player_y_delta > 16 && player_y_delta < 384)
        return 1;
    return 0;
}

/* Finds and removes a world actor close to the supplied position, returning its former state. */
char pascal remove_world_actor_at_position(int world_x, register int world_y)
{
    register int i;
    struct world_actor_record far *world_actor;

    for (i = 0; i < world_actor_count; i++) {
        world_actor = &world_actor_records[i];
        if (world_actor->state != 0) {
            if (abs(world_actor->world_x - world_x) < 2 &&
                world_actor->world_y - world_y < 128 &&
                world_actor->world_y - world_y >= -128) {
                if (world_actor->state == 1) {
                    world_actor->state = 0;
                    return 1;
                }
                if (world_actor->state == 5) {
                    world_actor->state = 0;
                    return 2;
                }
                world_actor->state = 0;
            }
        }
    }
    return 0;
}

/* Tests the player vertical range and returns the result to its caller. */
int test_player_vertical_range(register int x_min, int x_max, int world_y)
{
    register int player_y_offset;
    player_y_offset = ((player_screen_y >> 4) << 7) + level_map_y_offset - world_y + 2;
    if (player_screen_x + level_scroll_x - x_min > x_min &&
        player_screen_x + level_scroll_x - x_min < x_max &&
        player_y_offset > 0 &&
        player_y_offset < 384)
        return 1;
    return 0;
}

/* Tests the player x alignment and returns the result to its caller. */
int test_player_x_alignment(int world_x, int world_y)
{
    register int player_y_delta = player_screen_y;

    /* Convert the fixed-point scroll offset to 128-unit map rows. */
    player_y_delta >>= 4;
    player_y_delta <<= 7;
    player_y_delta += level_map_y_offset;
    player_y_delta -= world_y;
    player_y_delta++;
    player_y_delta++;

    if (abs(player_screen_x + level_scroll_x - world_x) == 0 && player_y_delta > 0 && player_y_delta < 384)
        return 1;
    return 0;
}

/* Keep the goto so the collision check stays in the original code order. */
/* Checks the level tile at a position and handles the special breakable-tile case. */
int test_level_tile_special_state(register int world_x, register int world_y)
{
    int far *tile_ptr;

    tile_ptr = level_tile_map + (world_x >> 1) + ((world_y >> 7) << 7) - 1;
    if (secret_block_collision_state != 0) {
        if (*tile_ptr == 0x1800) {
            *tile_ptr = 0x17e0;
            spawn_pickup_object(world_x, world_y);
        } else if (tile_ptr[128] == 0x1800) {
            tile_ptr[128] = 0x17e0;
            spawn_pickup_object(world_x, world_y + 128);
        } else {
            goto check;
        }
        request_priority_sound_effect(42);
        add_and_draw_player_score(10L);
        return 1;
    }
check:
    if (*tile_ptr > 0x17ff)
        return 1;
    return 0;
}

/* Returns nonzero when either map cell covered by a position contains a blocking tile. */
int is_level_position_blocked(int world_x, int world_y)
{
    unsigned int far *tile_ptr;
    unsigned int far *adjacent_tile_ptr;

    tile_ptr = level_tile_map + (world_x >> 1) + ((world_y >> 7) << 7) - 1;
    adjacent_tile_ptr = tile_ptr;
    if (world_x & 1)
        adjacent_tile_ptr++;
    if (*tile_ptr > 0x17ff || *adjacent_tile_ptr > 0x17ff)
        return 1;
    return 0;
}

/* ============================================================================================
   Level actors
   One update routine per kind of object placed in the level map (the map word 0x30XX
   that spawns it is in each description), with the drawing helpers they share.
   create_objects_from_level_map registers the routines for the current level.
   ============================================================================================ */

/* Updates and draws records from level-map marker 0x3000; the concrete entity identity is not
   established by source. */
void update_actor_3000(void)
{
    register int i;
    struct actor_3000_record far *actor;

    for (i = 0; i < actor_3000_count; ++i) {
        actor = &actor_3000_records[i];
        if (actor->state != 0) {
            if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0) {
                if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0)
                    actor->world_y += 128;
                if (remove_world_actor_at_position(actor->world_x, actor->world_y) != 0) {
                    actor->state = 0;
                    spawn_contact_flash_effect(actor->world_x, actor->world_y);
                    if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0) {
                        add_and_draw_player_score(500L);
                        queue_ambient_sprite_animation(0x280, actor->world_x, actor->world_y);
                    }
                } else if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                            actor->world_x - level_scroll_x,
                                            ((actor->world_y - level_map_y_offset) >> 3) + 16);
                }
            }
        }
    }
}

/* Keep the backward jump: structured flow moves the shared draw and changes matching. */
/* Updates and draws records from level-map marker 0x3001; the concrete entity identity is not
   established by source. */
void update_actor_3001(void)
{
    register int i;
    struct actor_3001_record far *actor;

    for (i = 0; i < actor_3001_count; ++i) {
        actor = &actor_3001_records[i];
        if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0) {
            if (test_player_x_alignment(actor->world_x, actor->world_y - 32)) {
                if (hint_revealed_object_5) {
                    hint_revealed_object_5 = 0;
                    show_secret_tip_elevator();
                }
                if (!player_death_state) {
                    if (control_up_pressed) {
                        if (test_player_head_clearance()) {
                            if (!control_down_pressed) {
                                ++actor->active;
                                actor->world_y -= 128;
                                /* Keep this pointer form; direct subscripting changes Turbo C output. */
                                *((level_tile_map + actor->world_y) + (actor->world_x >> 1) - 1) = 0x1ae0;
                                player_screen_y -= 16;
                                request_priority_sound_effect(0x14);
                                if (player_screen_y <= 64)
                                    player_sprite_draw_state = 1;
                                player_death_state = 0;
                                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x320,
                                                        actor->world_x - level_scroll_x,
                                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
                            }
                        }
                    }
                }
draw_second:
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x320,
                                        actor->world_x - level_scroll_x,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
            } else if (actor->active > 1) {
                --actor->active;
                *((level_tile_map + actor->world_y) + (actor->world_x >> 1) - 1) = actor_3001_tile_below_records[i];
                actor->world_y += 128;
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x320,
                                        actor->world_x - level_scroll_x,
                                        (actor->world_y - level_map_y_offset) >> 3);
                continue;
            } else if (actor->active == 1) {
                goto draw_second;
            } else {
                continue;
            }
        } else if (actor->active > 1) {
            actor->active--;
            *((level_tile_map + actor->world_y) + (actor->world_x >> 1) - 1) = actor_3001_tile_below_records[i];
            actor->world_y += 128;
        }
    }
}

/* Keep the label loops to preserve Turbo C's original SI/DI register allocation. */
/* update_actor_3002 translation-unit declarations from skeleton2.c */
/* Updates and draws records from level-map marker 0x3002; the concrete entity identity is not
   established by source. */
void update_actor_3002(void)
{
    register int i;
    register int j;
    struct actor_3002_record far *actor;
    int actor_height;

    ++actor_3002_animation_phase;
    if (actor_3002_animation_phase == 4)
        actor_3002_animation_phase = 0;
    i = 0;
    goto otest;
obody:
    {
        actor = &actor_3002_records[i];
        actor_height = actor->object_height;
        j = 0;
        goto test;
    body:
        *(level_tile_map + actor->map_column + actor->map_row + (j >> 1) - 2) =
            0x1c00 + ((actor_3002_animation_phase & 1) << 5);
        ++j;
    test:
        if (j < actor_height)
            goto body;

        if (actor->object_state == 1) {
            *(level_tile_map + actor->map_column + actor->map_row - 2) =
                0x1b80 + (actor_3002_animation_phase << 5);
            *(level_tile_map + actor->map_column + actor->map_row + (actor_height >> 1) - 2) =
                0x1c40 + (actor_3002_animation_phase << 5);
        }

        if (actor->object_state == 0) {
            *(level_tile_map + actor->map_column + actor->map_row - 2) =
                0x1be0 - (actor_3002_animation_phase << 5);
            *(level_tile_map + actor->map_column + actor->map_row + (actor_height >> 1) - 2) =
                0x1ca0 - (actor_3002_animation_phase << 5);
        }

        if (test_player_vertical_range(actor->map_column - 2, actor->map_column + actor_height + 2,
                                       actor->map_row - 32)) {
            if (actor->object_state == 0 && test_player_floor_clearance())
                --player_screen_x;
            if (actor->object_state == 1 && test_player_body_clearance())
                ++player_screen_x;
        }

        if (player_death_state != 0) {
            if (test_player_vertical_range(actor->map_column - 2, actor->map_column + actor_height + 2,
                                           actor->map_row + 96)) {
                if (actor->object_state == 1 && test_player_floor_clearance())
                    --player_screen_x;
                if (actor->object_state == 0 && test_player_body_clearance())
                    ++player_screen_x;
            }
        }
    }
    i++;
otest:
    if (i < actor_3002_count)
        goto obody;
}

/* Updates and draws records from level-map marker 0x3006; the concrete entity identity is not
   established by source. */
void update_actor_3006(void)
{
    if (access_card_or_door_state != 0)
        return;

    if (is_world_position_outside_view(actor_3006_world_x, actor_3006_world_y) != 0)
        return;

    if (is_level_position_blocked(actor_3006_world_x, actor_3006_world_y + 128) == 0)
        actor_3006_world_y += 128;

    if (test_player_overlap_with_object(actor_3006_world_x, actor_3006_world_y) != 0 && actor_3006_state != 0) {
        access_card_or_door_state = 1;
        queue_ambient_sprite_animation(0x3c0, actor_3006_world_x, actor_3006_world_y);
        add_and_draw_player_score(1000L);
        draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x640);
        request_priority_sound_effect(0x0c);
        return;
    }

    if (actor_3006_state == 0) {
        if (remove_world_actor_at_position(actor_3006_world_x, actor_3006_world_y) != 0) {
            spawn_contact_flash_effect(actor_3006_world_x, actor_3006_world_y);
            actor_3006_state = 1;
            if (is_level_position_blocked(actor_3006_world_x, actor_3006_world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, actor_3006_world_x, actor_3006_world_y);
            }
        }
    }

    if (actor_3006_state == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                actor_3006_world_x - level_scroll_x,
                                ((actor_3006_world_y - level_map_y_offset) >> 3) + 16);
    } else {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x640,
                                actor_3006_world_x - level_scroll_x,
                                ((actor_3006_world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Updates and draws records from level-map marker 0x3007; the concrete entity identity is not
   established by source. */
void update_actor_3007(void)
{
    register int i;
    struct actor_3007_record far *actor;

    hidden_object_state = 1;
    for (i = 0; i < actor_3007_count; ++i) {
        actor = &actor_3007_records[i];
        if (actor->state == 0)
            continue;

        hidden_object_state = 0;
        if (remove_world_actor_at_position(actor->world_x, actor->world_y) != 0 && actor->state == 1) {
            actor->state = 2;
            request_priority_sound_effect(0x1e);
            add_and_draw_player_score(200L);
        }

        if (actor->state > 1 && actor->state < 10) {
            if (actor->state == 9) {
                /* Keep this address form; direct indexing changes Turbo C output. */
                *((&level_tile_map[actor->world_y] + (actor->world_x >> 1)) + 0x7f) =
                    *((&level_tile_map[actor->world_y] + (actor->world_x >> 1)) + 0xff);
                spawn_contact_flash_effect(actor->world_x, actor->world_y + 128);
            }

            if (actor->state == 3)
                spawn_moving_actor(3, actor->world_x, actor->world_y + 128);

            if ((actor->state & 1) != 0) {
                if (is_world_position_outside_view(actor->world_x, actor->world_y + 128) == 0)
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0xaa0,
                                            actor->world_x - level_scroll_x,
                                            ((actor->world_y - level_map_y_offset) >> 3) + 32);
            }
            ++actor->state;
        }

        if (actor->state == 10) {
            actor->world_y -= 128;
            if (actor->world_y % 256 != 0) {
                if (is_world_position_outside_view(actor->world_x, actor->world_y + 128) == 0)
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0xa00,
                                            actor->world_x - level_scroll_x,
                                            ((actor->world_y - level_map_y_offset) >> 3) + 32);
                if (is_world_position_outside_view(actor->world_x, actor->world_y + 256) == 0)
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0xaa0,
                                            actor->world_x - level_scroll_x,
                                            ((actor->world_y - level_map_y_offset) >> 3) + 48);
            }
        }

        if (is_world_position_outside_view(actor->world_x, actor->world_y - 384) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x6e0,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) - 32);
        if (is_world_position_outside_view(actor->world_x, actor->world_y - 254) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x780,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) - 16);
        if (is_world_position_outside_view(actor->world_x, actor->world_y - 128) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x780,
                                    actor->world_x - level_scroll_x,
                                    (actor->world_y - level_map_y_offset) >> 3);

        if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x820,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(actor->world_x - 2, actor->world_y) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x8c0,
                                    actor->world_x - level_scroll_x - 2,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(actor->world_x + 2, actor->world_y) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x960,
                                    actor->world_x - level_scroll_x + 2,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);

        if (is_level_position_blocked(actor->world_x, actor->world_y - 512) == 0)
            continue;
        if (actor->state != 10)
            continue;

        spawn_contact_flash_effect(actor->world_x - 3, actor->world_y - 512);
        spawn_contact_flash_effect(actor->world_x + 2, actor->world_y - 384);
        spawn_contact_flash_effect(actor->world_x + 1, actor->world_y - 384);
        spawn_contact_flash_effect(actor->world_x - 1, actor->world_y - 256);
        spawn_contact_flash_effect(actor->world_x, actor->world_y - 128);
        actor->state = 0;
        *((&level_tile_map[actor->world_y] + (actor->world_x >> 1)) - 0x201) =
            *((&level_tile_map[actor->world_y] + (actor->world_x >> 1)) - 0x181);
    }
}

/* Updates and draws records from level-map marker 0x3008; the concrete entity identity is not
   established by source. */
void update_actor_3008(void)
{
    if (player_contact_state != 0)
        return;
    if (is_world_position_outside_view(actor_3008_world_x, actor_3008_world_y) != 0)
        return;
    if (is_level_position_blocked(actor_3008_world_x, actor_3008_world_y + 128) == 0)
        actor_3008_world_y += 128;
    if (test_player_overlap_with_object(actor_3008_world_x, actor_3008_world_y) != 0 && actor_3008_state != 0) {
        player_contact_state = 1;
        draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0xb40);
        queue_ambient_sprite_animation(0x3c0, actor_3008_world_x, actor_3008_world_y);
        add_and_draw_player_score(1000L);
        return;
    }

    if (actor_3008_state == 0 && remove_world_actor_at_position(actor_3008_world_x, actor_3008_world_y) != 0) {
        spawn_contact_flash_effect(actor_3008_world_x, actor_3008_world_y);
        actor_3008_state = 1;
        if (is_level_position_blocked(actor_3008_world_x, actor_3008_world_y + 128) == 0) {
            add_and_draw_player_score(500L);
            queue_ambient_sprite_animation(0x280, actor_3008_world_x, actor_3008_world_y);
        }
    }

    if (actor_3008_state == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                actor_3008_world_x - level_scroll_x,
                                ((actor_3008_world_y - level_map_y_offset) >> 3) + 16);
        return;
    }
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0xb40,
                            actor_3008_world_x - level_scroll_x,
                            ((actor_3008_world_y - level_map_y_offset) >> 3) + 16);
}

/* Updates and draws records from level-map marker 0x3009; the concrete entity identity is not
   established by source. */
void update_actor_3009(void)
{
    register int i;
    struct actor_3009_record far *actor;

    for (i = 0; i < actor_3009_count; ++i) {
        actor = &actor_3009_records[i];
        if (actor->state == 0)
            continue;
        ++actor->state;
        if (actor->state >= 15) {
            if (actor->state == 15 && is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
                request_priority_sound_effect(0x2b);
            if (actor->state < 25) {
                if ((actor->state % 2) == 0)
                    continue;
                if (is_world_position_outside_view(actor->world_x, actor->world_y) != 0)
                    continue;
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x0f00,
                                        actor->world_x - level_scroll_x,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
                continue;
            }
            if (actor->state < 45) {
                if (is_world_position_outside_view(actor->world_x, actor->world_y) != 0)
                    continue;
                if (is_world_position_outside_view(actor->world_x + 6, actor->world_y) != 0)
                    continue;
                blit_planar_sprite_rows(sprite_pixel_data_pointer + ((actor->state % 2) * 0xa0) + 0xfa0,
                                        actor->world_x - level_scroll_x,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
                blit_planar_sprite_rows(sprite_pixel_data_pointer + ((actor->state % 2) * 0xa0) + 0xfa0,
                                        actor->world_x - level_scroll_x + 2,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
                blit_planar_sprite_rows(sprite_pixel_data_pointer + ((actor->state % 2) * 0xa0) + 0x10e0,
                                        actor->world_x - level_scroll_x + 4,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
                if (test_player_overlap_with_object(actor->world_x, actor->world_y) != 0) {
                    active_sprite_draw_flag = 1;
                    continue;
                }
                if (test_player_overlap_with_object(actor->world_x + 2, actor->world_y - 32) != 0) {
                    active_sprite_draw_flag = 1;
                    continue;
                }
                if (test_player_overlap_with_object(actor->world_x + 4, actor->world_y) == 0)
                    continue;
                active_sprite_draw_flag = 1;
            } else if (actor->state > 65) {
                actor->state = 1;
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x300A; the concrete entity identity is not
   established by source. */
void update_actor_300a(void)
{
    register int i;
    struct actor_300a_record far *actor;

    for (i = 0; i < actor_300a_count; ++i) {
        actor = &actor_300a_records[i];
        if (actor->state != 0) {
            ++actor->state;

            if (actor->state >= 15) {
                if (actor->state == 15 &&
                    is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
                    request_priority_sound_effect(0x2b);

                if (actor->state < 25) {
                    if (actor->state % 2 != 0 &&
                        is_world_position_outside_view(actor->world_x, actor->world_y) == 0) {
                        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1220,
                                                actor->world_x - level_scroll_x,
                                                ((actor->world_y - level_map_y_offset) >> 3) + 16);
                    }
                } else if (actor->state < 45) {
                    if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0 &&
                        is_world_position_outside_view(actor->world_x - 6, actor->world_y) == 0) {
                        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x12c0 + (actor->state % 2) * 0xa0,
                                                actor->world_x - level_scroll_x,
                                                ((actor->world_y - level_map_y_offset) >> 3) + 16);
                        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x12c0 + (actor->state % 2) * 0xa0,
                                                actor->world_x - level_scroll_x - 2,
                                                ((actor->world_y - level_map_y_offset) >> 3) + 16);
                        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1400 + (actor->state % 2) * 0xa0,
                                                actor->world_x - level_scroll_x - 4,
                                                ((actor->world_y - level_map_y_offset) >> 3) + 16);

                        if (test_player_overlap_with_object(actor->world_x, actor->world_y) != 0 ||
                            test_player_overlap_with_object(actor->world_x - 2, actor->world_y) != 0 ||
                            test_player_overlap_with_object(actor->world_x - 4, actor->world_y) != 0)
                            active_sprite_draw_flag = 1;
                    }
                } else if (actor->state > 65) {
                    actor->state = 1;
                }
                }
        }
    }
}

/* Keep the shared-tail jump because restructuring moves its call after rendering. */
/* Updates and draws records from level-map marker 0x300B; the concrete entity identity is not
   established by source. */
void update_actor_300b(void)
{
    register int i;
    struct actor_300b_record far *actor;

    ++actor_300b_animation_frame;
    if (actor_300b_animation_frame == 10)
        actor_300b_animation_frame = 0;
    actor_300b_screen_anim_offset += 160;
    if (actor_300b_screen_anim_offset == 640)
        actor_300b_screen_anim_offset = 0;

    for (i = 0; i < actor_300b_count; ++i) {
        actor = &actor_300b_records[i];
        if (actor->motion_state == 0xfe) {
            if (is_level_position_blocked(actor->world_x, actor->world_y + 128)) {
                spawn_contact_flash_effect(actor->world_x, actor->world_y);
                spawn_moving_actor(1, actor->world_x, actor->world_y);
                actor->motion_state = 0;
                continue;
            }
            if (actor->trajectory_step <= 20) {
                actor->world_x += moving_item_path_delta_table_a[actor->trajectory_step];
                actor->world_y += (moving_item_path_delta_table_a + 1)[actor->trajectory_step];
                actor->trajectory_step += 2;
            } else {
                actor->world_y += 128;
            }
            if (is_world_position_outside_view(actor->world_x, actor->world_y)) {
                actor->motion_state = 0;
                continue;
            }
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x3c0,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
            blit_planar_sprite_rows(sprite_graphics_buffer,
                                    actor->world_x - level_scroll_x,
                                    (actor->world_y - level_map_y_offset) >> 3);
        shared_animation_finish:
            spawn_pickup_object(actor->world_x, actor->world_y - 128);
            continue;
        }

        if (actor->motion_state == 0xff) {
            if (is_level_position_blocked(actor->world_x, actor->world_y + 128)) {
                spawn_contact_flash_effect(actor->world_x, actor->world_y);
                spawn_moving_actor(1, actor->world_x, actor->world_y);
                actor->motion_state = 0;
                continue;
            }
            if (actor->trajectory_step < 20) {
                actor->world_x += moving_item_path_delta_table_b[actor->trajectory_step];
                actor->world_y += (moving_item_path_delta_table_b + 1)[actor->trajectory_step];
                actor->trajectory_step += 2;
            } else {
                actor->world_y += 128;
            }
            if (is_world_position_outside_view(actor->world_x, actor->world_y)) {
                actor->motion_state = 0;
                continue;
            }
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x3c0,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x320,
                                    actor->world_x - level_scroll_x,
                                    (actor->world_y - level_map_y_offset) >> 3);
            goto shared_animation_finish;
        }

        if (actor->motion_state == 0)
            continue;
        if (is_world_position_outside_view(actor->world_x, actor->world_y))
            continue;
        if (is_world_position_outside_view(actor->world_x, actor->world_y - 128))
            continue;

        if (remove_world_actor_at_position(actor->world_x, actor->world_y - 128) ||
            test_player_overlap_with_object(actor->world_x, actor->world_y - 128)) {
            if (test_player_overlap_with_object(actor->world_x, actor->world_y))
                active_sprite_draw_flag = 1;
            if (world_animation_phase == 0)
                actor->motion_state = 0xfe;
            else if (world_animation_phase == 0x20)
                actor->motion_state = 0xfe;
            else
                actor->motion_state = 0xff;
            spawn_moving_actor(1, actor->world_x, actor->world_y);
            actor->trajectory_step = 0;
            add_and_draw_player_score(200L);
            request_priority_sound_effect(18);
            continue;
        }

        if (!is_level_position_blocked(actor->world_x, actor->world_y + 128))
            actor->world_y += 8;
        if (is_level_position_blocked(actor->world_x, actor->world_y + 128)) {
            actor->world_y -= 8;
            if (!is_level_position_blocked(actor->world_x, actor->world_y + 128) && actor_300b_screen_anim_offset == 0)
                allocate_collision_record(actor->world_x, actor->world_y);
        }

        if (actor_300b_screen_anim_offset == 0) {
            if (actor->world_x > player_screen_x + level_scroll_x) {
                if (actor->motion_state > 1) {
                    --actor->motion_state;
                } else if (!test_level_tile_special_state(actor->world_x - 1, actor->world_y - 5)) {
                    --actor->world_x;
                    if (actor_300b_animation_frame == 0)
                        spawn_projectile(1, actor->world_x - 1, actor->world_y - 160);
                }
            }
            if (actor->world_x < player_screen_x + level_scroll_x) {
                if (actor->motion_state < 6) {
                    ++actor->motion_state;
                } else if (!test_level_tile_special_state(actor->world_x + 2, actor->world_y - 5)) {
                    ++actor->world_x;
                    if (actor_300b_animation_frame == 0)
                        spawn_projectile(2, actor->world_x + 1, actor->world_y - 160);
                }
            }
        }

        blit_planar_sprite_rows(sprite_graphics_buffer + actor_300b_screen_anim_offset + 0x3c0,
                                actor->world_x - level_scroll_x,
                                ((actor->world_y - level_map_y_offset) >> 3) + 16);
        blit_planar_sprite_rows(sprite_graphics_buffer + (actor->motion_state - 1) * 0xa0,
                                actor->world_x - level_scroll_x,
                                (actor->world_y - level_map_y_offset) >> 3);
    }
}

/* Draws the six sprite cells that form a two-column, three-row actor graphic. */
void pascal draw_six_tile_actor_sprite(int sprite_index, int x_coord, register int world_y)
{
    register int world_x = x_coord;
    if (multi_tile_actor_sprite_offsets[sprite_index * 6] > 0 && is_world_position_outside_view(world_x, world_y - 256) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + multi_tile_actor_sprite_offsets[sprite_index * 6] + 0x5a0,
                                world_x - level_scroll_x,
                                ((world_y - level_map_y_offset) >> 3) - 16);

    if (multi_tile_actor_sprite_offsets[sprite_index * 6] > 0 && is_world_position_outside_view(world_x + 2, world_y - 256) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + ACTOR_TILE_OFFSETS(sprite_index).top_right_sprite_offset + 0x5a0,
                                world_x - level_scroll_x + 2,
                                ((world_y - level_map_y_offset) >> 3) - 16);

    if (is_world_position_outside_view(world_x, world_y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + ACTOR_TILE_OFFSETS(sprite_index).middle_left_sprite_offset + 0x5a0,
                                world_x - level_scroll_x,
                                (world_y - level_map_y_offset) >> 3);

    if (is_world_position_outside_view(world_x + 2, world_y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + ACTOR_TILE_OFFSETS(sprite_index).middle_right_sprite_offset + 0x5a0,
                                world_x - level_scroll_x + 2,
                                (world_y - level_map_y_offset) >> 3);

    if (is_world_position_outside_view(world_x, world_y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + ACTOR_TILE_OFFSETS(sprite_index).bottom_left_sprite_offset + 0x5a0,
                                world_x - level_scroll_x,
                                ((world_y - level_map_y_offset) >> 3) + 16);

    if (is_world_position_outside_view(world_x + 2, world_y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + ACTOR_TILE_OFFSETS(sprite_index).bottom_right_sprite_offset + 0x5a0,
                                world_x - level_scroll_x + 2,
                                ((world_y - level_map_y_offset) >> 3) + 16);

    if (test_player_overlap_with_object(world_x + 1, world_y) != 0 || test_player_overlap_with_object(world_x + 1, world_y - 128) != 0)
        active_sprite_draw_flag = 1;
}

/* Updates and draws records from level-map marker 0x300C; the concrete entity identity is not
   established by source. */
void update_actor_300c(void)
{
    register int i;
    struct actor_300c_record far *actor;

    for (i = 0; i < actor_300c_count; ++i) {
        actor = &actor_300c_records[i];
        if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0 && actor->marker_state == 0)
            actor->marker_state = 1;
        if (actor->state == 0 || actor->marker_state == 0)
            continue;

        while (1) {
            if (remove_world_actor_at_position(actor->world_x + 1, actor->world_y - 128) != 0 ||
                remove_world_actor_at_position(actor->world_x + 1, actor->world_y) != 0)
                ++actor_300c_object_marker_table[i];
            if (actor_300c_object_marker_table[i] == 3) {
                spawn_contact_flash_effect(actor->world_x + 1, actor->world_y - 256);
                spawn_contact_flash_effect(actor->world_x, actor->world_y - 128);
                spawn_contact_flash_effect(actor->world_x + 2, actor->world_y);
                spawn_moving_actor(1, actor->world_x + 1, actor->world_y - 128);
                spawn_moving_actor(1, actor->world_x + 2, actor->world_y - 64);
                spawn_moving_actor(1, actor->world_x + 2, actor->world_y - 128);
                spawn_moving_actor(1, actor->world_x + 1, actor->world_y);
                if (world_animation_phase == 0)
                    spawn_animated_actor_sprite(actor->world_x, actor->world_y);
                add_and_draw_player_score(2000L);
                actor->state = 0;
                break;
            }

            if (actor_300c_object_marker_table[i] == 1 && world_animation_phase == 0)
                spawn_pickup_object(actor->world_x, actor->world_y - 192);
            if (actor_300c_object_marker_table[i] == 2 && world_animation_phase == 0) {
                spawn_pickup_object(actor->world_x + 2, actor->world_y - 192);
                spawn_pickup_object(actor->world_x, actor->world_y - 192);
            }

            if (actor->state < 25) {
                if (is_level_position_blocked(actor->world_x + 1, actor->world_y + 128) == 0) {
                    if (actor->world_x > player_screen_x + level_scroll_x - 3)
                        draw_six_tile_actor_sprite(2, actor->world_x, actor->world_y);
                    else
                        draw_six_tile_actor_sprite(5, actor->world_x, actor->world_y);
                    actor->world_y += 128;
                    break;
                }

                if (actor->world_x > player_screen_x + level_scroll_x - 3) {
                    actor->marker_state = 1;
                    if (actor->state != 12)
                        draw_six_tile_actor_sprite(0, actor->world_x, actor->world_y);
                } else {
                    if (actor->state != 12)
                        draw_six_tile_actor_sprite(3, actor->world_x, actor->world_y);
                    actor->marker_state = 2;
                }
                ++actor->state;
                /* Align the vertical position to a 128-unit row boundary. */
                actor->world_y = (actor->world_y >> 7) << 7;
                if (actor->state == 13) {
                    if (actor->marker_state == 1) {
                        spawn_projectile(1, actor->world_x - 1, actor->world_y - 80);
                        draw_six_tile_actor_sprite(1, actor->world_x, actor->world_y);
                    }
                    if (actor->marker_state == 2) {
                        spawn_projectile(2, actor->world_x + 3, actor->world_y - 80);
                        draw_six_tile_actor_sprite(4, actor->world_x, actor->world_y);
                    }
                    ++actor->state;
                }
                break;
            }

            if (actor->state < 50) {
                if (actor->marker_state == 1) {
                    if (is_level_position_blocked(actor->world_x + 1, actor->world_y - 256) != 0) {
                        actor->world_y = (actor->world_y >> 7) << 7;
                        draw_six_tile_actor_sprite(2, actor->world_x, actor->world_y);
                        actor->state = 1;
                        break;
                    }
                    if (test_level_tile_special_state(actor->world_x - 1, actor->world_y) == 0) {
                        actor->world_x -= actor_300c_motion_delta_table[actor->state - 25];
                        actor->world_y -= actor_300c_motion_delta_table[actor->state - 24];
                    } else {
                        actor->world_y -= actor_300c_motion_delta_table[actor->state - 24];
                    }
                    draw_six_tile_actor_sprite(2, actor->world_x, actor->world_y);
                    actor->state += 2;
                    break;
                }
                if (actor->marker_state == 2) {
                    if (is_level_position_blocked(actor->world_x + 1, actor->world_y - 256) != 0) {
                        actor->world_y = (actor->world_y >> 7) << 7;
                        draw_six_tile_actor_sprite(5, actor->world_x, actor->world_y);
                        actor->state = 1;
                        break;
                    }
                    if (test_level_tile_special_state(actor->world_x + 4, actor->world_y) == 0) {
                        actor->world_x += actor_300c_motion_delta_table[actor->state - 25];
                        actor->world_y -= actor_300c_motion_delta_table[actor->state - 24];
                    } else {
                        actor->world_y -= actor_300c_motion_delta_table[actor->state - 24];
                    }
                    draw_six_tile_actor_sprite(5, actor->world_x, actor->world_y);
                    actor->state += 2;
                    break;
                }
            }

            actor->state = 1;
        }
    }
}

/* Draws a two-cell-wide actor row and marks player contact when the row overlaps Duke. */
void pascal draw_two_tile_wide_actor_sprite(int frame, int world_x, int world_y)
{
    register int sprite_offset;

    sprite_offset = frame * 0x140 + 0x1540;

    if (is_world_position_outside_view(world_x, world_y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset,
                                world_x - level_scroll_x,
                                ((world_y - level_map_y_offset) >> 3) + 16);

    if (is_world_position_outside_view(world_x + 2, world_y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0xa0,
                                world_x - level_scroll_x + 2,
                                ((world_y - level_map_y_offset) >> 3) + 16);

    if (test_player_overlap_with_object(world_x, world_y) || test_player_overlap_with_object(world_x + 2, world_y))
        active_sprite_draw_flag = 1;
}

/* Updates and draws records from level-map marker 0x300D; the concrete entity identity is not
   established by source. */
void update_actor_300d(void)
{
    register int i;
    struct actor_300d_record far *actor;

    ++actor_300d_animation_counter;
    if (actor_300d_animation_counter == 2) {
        actor_300d_animation_counter = 0;
        ++actor_300d_animation_phase;
    }
    if (actor_300d_animation_phase == 2)
        actor_300d_animation_phase = 0;

    for (i = 0; i < actor_300d_count; ++i) {
        actor = &actor_300d_records[i];
        if (actor->state == 0)
            continue;

        if (remove_world_actor_at_position(actor->world_x, actor->world_y) != 0 ||
            remove_world_actor_at_position(actor->world_x + 2, actor->world_y) != 0)
            ++actor_300d_auxiliary_states[i];

        if (actor_300d_auxiliary_states[i] == 2) {
            spawn_contact_flash_effect(actor->world_x + 2, actor->world_y);
            spawn_contact_flash_effect(actor->world_x, actor->world_y);
            spawn_moving_actor(1, actor->world_x + 1, actor->world_y);
            add_and_draw_player_score(2500L);
            request_priority_sound_effect(0x12);
            actor->state = 0;
            continue;
        }

        if (actor_300d_auxiliary_states[i] == 1 && world_animation_phase == 0) {
            spawn_pickup_object(actor->world_x + 2, actor->world_y - 64);
        }
        if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0) {
            actor->world_y += 32;
            draw_two_tile_wide_actor_sprite(0, actor->world_x, actor->world_y);
            continue;
        }

        if (actor->state == 1) {
            if (test_level_tile_special_state(actor->world_x, actor->world_y) != 0) {
                actor->state = 2;
                spawn_projectile(2, actor->world_x + 4, actor->world_y - 64);
            } else if (test_level_tile_special_state(actor->world_x, actor->world_y + 128) == 0) {
                actor->state = 2;
                spawn_projectile(2, actor->world_x + 4, actor->world_y - 64);
            } else {
                if (actor_300d_animation_counter == 0)
                    --actor->world_x;
                draw_two_tile_wide_actor_sprite(actor_300d_animation_phase, actor->world_x, actor->world_y);
            }
        }

        if (actor->state == 2) {
            if (test_level_tile_special_state(actor->world_x + 4, actor->world_y) != 0 ||
                test_level_tile_special_state(actor->world_x + 4, actor->world_y + 128) == 0) {
                actor->state = 1;
                spawn_projectile(1, actor->world_x - 2, actor->world_y - 64);
                draw_two_tile_wide_actor_sprite(actor_300d_animation_phase + 2, actor->world_x - 1, actor->world_y);
                continue;
            }
            if (actor_300d_animation_counter == 0)
                ++actor->world_x;
            draw_two_tile_wide_actor_sprite(actor_300d_animation_phase + 2, actor->world_x, actor->world_y);
        }
    }
}

/* Updates and draws records from level-map marker 0x3020; the concrete entity identity is not
   established by source. */
void update_actor_3020(void)
{
    if (actor_3020_active_state != 0)
        return;

    if (is_world_position_outside_view(actor_3020_world_x, actor_3020_world_y) != 0)
        return;

    if (is_level_position_blocked(actor_3020_world_x, actor_3020_world_y + 128) == 0)
        actor_3020_world_y += 128;

    if (test_player_overlap_with_object(actor_3020_world_x, actor_3020_world_y) != 0 && actor_3020_state != 0) {
        actor_3020_active_state = 1;
        queue_ambient_sprite_animation(0x3c0, actor_3020_world_x, actor_3020_world_y);
        add_and_draw_player_score(1000L);
        request_priority_sound_effect(12);
        draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x2760);
        return;
    }

    if (actor_3020_state == 0) {
        if (remove_world_actor_at_position(actor_3020_world_x, actor_3020_world_y) != 0) {
            spawn_contact_flash_effect(actor_3020_world_x, actor_3020_world_y);
            actor_3020_state = 1;
            if (is_level_position_blocked(actor_3020_world_x, actor_3020_world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, actor_3020_world_x, actor_3020_world_y);
            }
        }
    }

    if (actor_3020_state == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                actor_3020_world_x - level_scroll_x,
                                ((actor_3020_world_y - level_map_y_offset) >> 3) + 16);
        return;
    }

    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2760,
                            actor_3020_world_x - level_scroll_x,
                            ((actor_3020_world_y - level_map_y_offset) >> 3) + 16);
}

/* Updates and draws records from level-map marker 0x3033; the concrete entity identity is not
   established by source. */
void update_actor_3033(void)
{
    if (actor_3033_active_state != 0)
        return;
    if (actor_3033_enabled == 0)
        return;
    if (is_world_position_outside_view(actor_3033_world_x, actor_3033_world_y) != 0)
        return;

    if (is_level_position_blocked(actor_3033_world_x, actor_3033_world_y + 128) == 0)
        actor_3033_world_y += 128;

    if (test_player_overlap_with_object(actor_3033_world_x, actor_3033_world_y) != 0 && actor_3033_state != 0) {
        actor_3033_active_state = 1;
        queue_ambient_sprite_animation(0x3c0, actor_3033_world_x, actor_3033_world_y);
        add_and_draw_player_score(1000L);
        draw_current_planar_sprite();
        request_priority_sound_effect(12);
        return;
    }

    if (actor_3033_state == 0) {
        if (remove_world_actor_at_position(actor_3033_world_x, actor_3033_world_y) != 0) {
            spawn_contact_flash_effect(actor_3033_world_x, actor_3033_world_y);
            actor_3033_state = 1;
            if (is_level_position_blocked(actor_3033_world_x, actor_3033_world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, actor_3033_world_x, actor_3033_world_y);
            }
        }
    }

    if (actor_3033_state == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                actor_3033_world_x - level_scroll_x,
                                ((actor_3033_world_y - level_map_y_offset) >> 3) + 16);
    } else {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2800,
                                actor_3033_world_x - level_scroll_x,
                                ((actor_3033_world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Draws a two-column, two-row actor graphic and marks player contact when it overlaps Duke. */
void pascal draw_two_by_two_actor_sprite(int frame, int world_x, int world_y)
{
    register int sprite_offset;

    sprite_offset = frame * 0x280 + 0x1e00;

    if (is_world_position_outside_view(world_x, world_y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset,
                                world_x - level_scroll_x,
                                (world_y - level_map_y_offset) >> 3);

    if (is_world_position_outside_view(world_x + 2, world_y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0xa0,
                                world_x - level_scroll_x + 2,
                                (world_y - level_map_y_offset) >> 3);

    if (is_world_position_outside_view(world_x, world_y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0x140,
                                world_x - level_scroll_x,
                                ((world_y - level_map_y_offset) >> 3) + 16);

    if (is_world_position_outside_view(world_x + 2, world_y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0x1e0,
                                world_x - level_scroll_x + 2,
                                ((world_y - level_map_y_offset) >> 3) + 16);

    if (test_player_overlap_with_object(world_x + 1, world_y) != 0 ||
        test_player_overlap_with_object(world_x + 1, world_y - 64) != 0)
        active_sprite_draw_flag = 1;
}

/* Updates and draws records from level-map marker 0x300E; the concrete entity identity is not
   established by source. */
void update_actor_300e(void)
{
    register int i;
    struct actor_300e_record far *actor;

    ++actor_300e_animation_state;
    ++actor_300e_animation_counter;
    if (actor_300e_animation_counter == 60)
        actor_300e_animation_counter = 0;

    if (actor_300e_animation_counter < 25 && actor_300e_animation_state >= 4)
        actor_300e_animation_state = 0;
    if (actor_300e_animation_counter >= 25 && actor_300e_animation_state >= 8)
        actor_300e_animation_state = 4;

    for (i = 0; i < actor_300e_count; ++i) {
        actor = &actor_300e_records[i];
        if (actor->state != 0) {
            if ((remove_world_actor_at_position(actor->world_x, actor->world_y) != 0 ||
                 remove_world_actor_at_position(actor->world_x + 2, actor->world_y) != 0) && actor_300e_animation_counter < 25)
                ++actor_300e_object_state_table[i];

            if (actor_300e_object_state_table[i] == 2) {
                spawn_contact_flash_effect(actor->world_x + 2, actor->world_y);
                spawn_contact_flash_effect(actor->world_x, actor->world_y);
                spawn_pickup_object(actor->world_x + 2, actor->world_y - 128);
                spawn_moving_actor(1, actor->world_x + 1, actor->world_y);
                spawn_moving_actor(1, actor->world_x + 1, actor->world_y - 128);
                spawn_moving_actor(1, actor->world_x, actor->world_y - 128);
                add_and_draw_player_score(5000L);
                actor->state = 0;
                continue;
            }

            if (actor_300e_object_state_table[i] == 1 && world_animation_phase == 0)
                spawn_pickup_object(actor->world_x + 2, actor->world_y - 64);

            if (is_level_position_blocked(actor->world_x + 1, actor->world_y + 128) == 0) {
                actor->world_y += 128;
                draw_two_by_two_actor_sprite(actor_300e_animation_state, actor->world_x, actor->world_y);
                continue;
            }

            if (actor->state == 1) {
                if (test_level_tile_special_state(actor->world_x, actor->world_y + 128) == 0 || test_level_tile_special_state(actor->world_x, actor->world_y) != 0) {
                    actor->state = 2;
                } else {
                    if (world_animation_phase == 0x40 || world_animation_phase == 0)
                        --actor->world_x;
                    draw_two_by_two_actor_sprite(actor_300e_animation_state, actor->world_x, actor->world_y);
                    continue;
                }
            }

            if (actor->state == 2) {
                if (test_level_tile_special_state(actor->world_x + 3, actor->world_y + 128) == 0 || test_level_tile_special_state(actor->world_x + 3, actor->world_y) != 0)
                    actor->state = 1;
                else if (world_animation_phase == 0x40 || world_animation_phase == 0)
                    ++actor->world_x;
                draw_two_by_two_actor_sprite(actor_300e_animation_state, actor->world_x, actor->world_y);
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x300F; the concrete entity identity is not
   established by source. */
void update_actor_300f(void)
{
    register int i;
    struct actor_300f_record far *actor;

    for (i = 0; i < actor_300f_count; ++i) {
        actor = &actor_300f_records[i];
        if (actor->active != 0) {
            if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0) {
                if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0)
                    actor->world_y += 128;
                if (test_player_overlap_with_object(actor->world_x, actor->world_y) != 0 && actor->animation_state != 0) {
                    actor->active = 0;
                    if (world_actor_count < 4) {
                        ++world_actor_count;
                        draw_buffered_screen_effect();
                    }
                    request_priority_sound_effect(0xc);
                    add_and_draw_player_score(1000L);
                    queue_ambient_sprite_animation(0x3c0, actor->world_x, actor->world_y);
                    continue;
                }
                if (actor->animation_state == 0 && remove_world_actor_at_position(actor->world_x, actor->world_y) != 0) {
                    spawn_contact_flash_effect(actor->world_x, actor->world_y);
                    actor->animation_state = 1;
                    if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0) {
                        add_and_draw_player_score(500L);
                        queue_ambient_sprite_animation(0x280, actor->world_x, actor->world_y);
                    }
                }
                if (actor->animation_state == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                            actor->world_x - level_scroll_x,
                                            ((actor->world_y - level_map_y_offset) >> 3) + 16);
                } else {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1ae0,
                                            actor->world_x - level_scroll_x,
                                            ((actor->world_y - level_map_y_offset) >> 3) + 16);
                }
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x3010; the concrete entity identity is not
   established by source. */
void update_actor_3010(void)
{
    register int i;
    struct actor_3010_record far *actor;
    char removed_actor_state;

    actor_3010_sprite_offset += 0xa0;
    if (actor_3010_sprite_offset == 0x1e0)
        actor_3010_sprite_offset = 0;

    for (i = 0; i < actor_3010_count; i++) {
        actor = &actor_3010_records[i];
        if (actor->state == 0)
            continue;
        if (is_world_position_outside_view(actor->world_x, actor->world_y) != 0)
            continue;
        if (actor->state < 3) {
            if ((removed_actor_state = remove_world_actor_at_position(actor->world_x, actor->world_y)) != 0) {
                if (removed_actor_state == 1)
                    --actor->world_x;
                if (removed_actor_state == 2)
                    ++actor->world_x;
                request_priority_sound_effect(0x12);
                actor->state = 3;
            }
        }
        if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0)
            actor->world_y += 128;
        if (actor->state == 1) {
            if (test_level_tile_special_state(actor->world_x - 1, actor->world_y) != 0 ||
                test_level_tile_special_state(actor->world_x - 1, actor->world_y + 128) == 0) {
                actor->state = 2;
            } else if (actor_3010_sprite_offset == 0) {
                --actor->world_x;
            }
            if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
                blit_planar_sprite_rows(sprite_graphics_buffer + actor_3010_sprite_offset + 0x3200,
                                        actor->world_x - level_scroll_x,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
        } else if (actor->state == 2) {
            if (test_level_tile_special_state(actor->world_x + 2, actor->world_y) != 0 ||
                test_level_tile_special_state(actor->world_x + 2, actor->world_y + 128) == 0) {
                actor->state = 1;
            } else if (actor_3010_sprite_offset == 0) {
                ++actor->world_x;
            }
            if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
                blit_planar_sprite_rows(sprite_graphics_buffer + actor_3010_sprite_offset + 0x3200,
                                        actor->world_x - level_scroll_x,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
        } else if (actor->state >= 3) {
            if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
                blit_planar_sprite_rows(sprite_graphics_buffer + (actor->state - 3) * 0xa0 + 0x33e0,
                                        actor->world_x - level_scroll_x,
                                        ((actor->world_y - level_map_y_offset) >> 3) + 16);
            ++actor->state;
            if (actor->state == 10) {
                actor->state = 0;
                spawn_moving_actor(1, actor->world_x, actor->world_y);
                add_and_draw_player_score(100L);
            }
        }
        if (test_player_overlap_with_object(actor->world_x, actor->world_y) != 0) {
            if (actor->state > 0) {
                if (actor->state < 3)
                    active_sprite_draw_flag = 1;
            }
        }
    }
}

/* Draws a two-column, two-row actor graphic from the second sprite sheet region. */
void pascal draw_two_by_two_actor_variant(int frame, int world_x, int world_y)
{
    register int sprite_offset;

    sprite_offset = frame * 0x280 + 0x3c00;
    if (is_world_position_outside_view(world_x, world_y - 128) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset,
                                world_x - level_scroll_x,
                                (world_y - level_map_y_offset) >> 3);
    }
    if (is_world_position_outside_view(world_x + 2, world_y - 128) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0xa0,
                                world_x - level_scroll_x + 2,
                                (world_y - level_map_y_offset) >> 3);
    }
    if (is_world_position_outside_view(world_x, world_y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0x140,
                                world_x - level_scroll_x,
                                ((world_y - level_map_y_offset) >> 3) + 16);
    }
    if (is_world_position_outside_view(world_x + 2, world_y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_offset + 0x1e0,
                                world_x - level_scroll_x + 2,
                                ((world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Handles the door and key interaction using current game state and input. */
void handle_door_and_key_interaction(void)
{
    ++door_interaction_phase;
    if (door_interaction_phase == 1)
        door_interaction_phase = 0;

    if (door_or_key_interaction_state == 0)
        return;

    if (test_player_overlap_with_object(door_lock_world_x + 1, door_lock_world_y) ||
        test_player_overlap_with_object(door_lock_world_x + 1, door_lock_world_y - 128)) {
        if (hint_revealed_object_4) {
            show_secret_tip_open_door();
            hint_revealed_object_4 = 0;
        }
    }

    if (current_weapon_state == 0 && control_up_pressed != 0 && control_left_pressed == 0 && control_right_pressed == 0 && control_jump_pressed == 0 &&
        (test_player_overlap_with_object(door_lock_world_x + 1, door_lock_world_y) || test_player_overlap_with_object(door_lock_world_x + 1, door_lock_world_y - 128))) {
        current_weapon_state = 1;
        if (current_level_index % 2 != 0)
            request_priority_sound_effect(0x27);
        disable();
        control_up_pressed = 0;
        enable();
    }

    if (current_weapon_state == 0)
        draw_two_by_two_actor_variant(0, door_lock_world_x, door_lock_world_y);
    if (current_weapon_state == 0)
        return;

    if (door_interaction_phase == 0)
        ++current_weapon_state;
    if (current_weapon_state < 5) {
        if (current_weapon_state == 3 && current_level_index % 2 == 0)
            request_priority_sound_effect(0x13);
        draw_two_by_two_actor_variant(current_weapon_state - 1, door_lock_world_x, door_lock_world_y);
        return;
    }
    if (current_weapon_state < 5)
        return;

    switch (current_weapon_state) {
    case 4:
        draw_two_by_two_actor_variant(3, door_lock_world_x, door_lock_world_y);
        break;
    case 5:
        draw_two_by_two_actor_variant(2, door_lock_world_x, door_lock_world_y);
        break;
    case 6:
        draw_two_by_two_actor_variant(1, door_lock_world_x, door_lock_world_y);
        break;
    case 7:
        draw_two_by_two_actor_variant(0, door_lock_world_x, door_lock_world_y);
        break;
    case 8:
        draw_two_by_two_actor_variant(0, door_lock_world_x, door_lock_world_y);
        interaction_cooldown_state = 1;
        break;
    }
}

/* Updates and draws records from level-map marker 0x3012; the concrete entity identity is not
   established by source. */
void update_actor_3012(void)
{
    register int i;
    struct actor_3012_record far *actor;

    for (i = 0; i < actor_3012_count; ++i) {
        actor = &actor_3012_records[i];
        if (actor->state != 0) {
            if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0)
                actor->world_y += 128;

            if (actor->object_kind == 0) {
                if (remove_world_actor_at_position(actor->world_x, actor->world_y) != 0) {
                    spawn_contact_flash_effect(actor->world_x, actor->world_y);
                    actor->object_kind = 1;
                    if (is_level_position_blocked(actor->world_x, actor->world_y + 128) == 0) {
                        add_and_draw_player_score(500L);
                        queue_ambient_sprite_animation(0x280, actor->world_x, actor->world_y);
                    }
                }
            }

            if (actor->object_kind == 0) {
                if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0 && actor->state < 12) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer,
                            actor->world_x - level_scroll_x,
                            ((actor->world_y - level_map_y_offset) >> 3) + 16);
                    continue;
                }
            }

            if (actor->object_kind == 0) {
                continue;
            }

            ++actor->state;
            if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0) {
                if (actor->state < 12) {
                    blit_planar_sprite_rows(sprite_graphics_buffer + 0x4600,
                            actor->world_x - level_scroll_x,
                            ((actor->world_y - level_map_y_offset) >> 3) + 16);
                }
                if (actor->state % 2 != 0 && actor->state < 12) {
                    blit_planar_sprite_rows(sprite_graphics_buffer + 0x46a0,
                            actor->world_x - level_scroll_x,
                            ((actor->world_y - level_map_y_offset) >> 3) + 16);
                }
            }

            if (actor->state <= 12)
                continue;

            if (actor->state == 14) {
                spawn_moving_actor(2, actor->world_x, actor->world_y);
                request_priority_sound_effect(0x21);
            } else if (actor->state == 17) {
                if (test_level_tile_special_state(actor->world_x - 2, actor->world_y) == 0 &&
                    test_level_tile_special_state(actor->world_x - 2, actor->world_y + 128) != 0) {
                    spawn_moving_actor(2, actor->world_x - 2, actor->world_y);
                } else {
                    actor->unknown_flag_8 = 0;
                }
                if (test_level_tile_special_state(actor->world_x + 2, actor->world_y) == 0 &&
                    test_level_tile_special_state(actor->world_x + 2, actor->world_y + 128) != 0) {
                    spawn_moving_actor(2, actor->world_x + 2, actor->world_y);
                } else {
                    actor->unknown_flag_10 = 0;
                }
            } else if (actor->state == 19) {
                if (actor->unknown_flag_8 != 0) {
                    if (test_level_tile_special_state(actor->world_x - 4, actor->world_y) == 0 &&
                        test_level_tile_special_state(actor->world_x - 4, actor->world_y + 128) != 0) {
                        spawn_moving_actor(2, actor->world_x - 4, actor->world_y);
                    } else {
                        actor->unknown_flag_8 = 0;
                    }
                }
                if (actor->unknown_flag_10 != 0) {
                    if (test_level_tile_special_state(actor->world_x + 4, actor->world_y) == 0 &&
                        test_level_tile_special_state(actor->world_x + 4, actor->world_y + 128) != 0) {
                        spawn_moving_actor(2, actor->world_x + 4, actor->world_y);
                    } else {
                        actor->unknown_flag_10 = 0;
                    }
                }
            } else if (actor->state == 21) {
                if (actor->unknown_flag_8 != 0) {
                    if (test_level_tile_special_state(actor->world_x - 6, actor->world_y) == 0 &&
                        test_level_tile_special_state(actor->world_x - 6, actor->world_y + 128) != 0) {
                        spawn_moving_actor(2, actor->world_x - 6, actor->world_y);
                    } else {
                        actor->unknown_flag_8 = 0;
                    }
                }
                if (actor->unknown_flag_10 != 0) {
                    if (test_level_tile_special_state(actor->world_x + 6, actor->world_y) == 0 &&
                        test_level_tile_special_state(actor->world_x + 6, actor->world_y + 128) != 0) {
                        spawn_moving_actor(2, actor->world_x + 6, actor->world_y);
                    } else {
                        actor->unknown_flag_10 = 0;
                    }
                }
            } else if (actor->state == 23) {
                if (actor->unknown_flag_8 != 0 &&
                    test_level_tile_special_state(actor->world_x - 8, actor->world_y) == 0 &&
                    test_level_tile_special_state(actor->world_x - 8, actor->world_y + 128) != 0)
                    spawn_moving_actor(2, actor->world_x - 8, actor->world_y);
                if (actor->unknown_flag_10 != 0 &&
                    test_level_tile_special_state(actor->world_x + 8, actor->world_y) == 0 &&
                    test_level_tile_special_state(actor->world_x + 8, actor->world_y + 128) != 0)
                    spawn_moving_actor(2, actor->world_x + 8, actor->world_y);
            }

            if (actor->state == 24)
                actor->state = 0;
        }
    }
}

/* Updates and draws records from level-map marker 0x3013; the concrete entity identity is not
   established by source. */
void update_actor_3013(void)
{
    register int i;
    register int all_inactive;

    all_inactive = 1;
    if (formation_update_enabled != 0) {
        for (i = all_inactive; i < 10; ++i) {
            formation_object_x_positions[i - 1] = formation_object_x_positions[i];
            formation_object_y_positions[i - 1] = formation_object_y_positions[i];
            if (formation_object_active_flags[i] != 0)
                all_inactive = 0;
        }
        if (all_inactive != 0) {
            formation_update_enabled = 0;
            add_and_draw_player_score(10000L);
            actor_3013_formation_state = 1;
            return;
        }
    } else {
        return;
    }

    formation_world_x_accumulator += formation_x_delta_table[formation_active_object_count];
    formation_world_y_accumulator += formation_y_delta_table[formation_active_object_count] << 6;

    for (i = 1; i < 10; ++i) {
        if (is_world_position_outside_view(formation_object_x_positions[i], formation_object_y_positions[i]) == 0 && formation_object_active_flags[i] != 0) {
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3013_sprite_offset + 0x4b00,
                                    formation_object_x_positions[i] - level_scroll_x,
                                    ((formation_object_y_positions[i] - level_map_y_offset) >> 3) + 16);
            if (test_player_overlap_with_object(formation_object_x_positions[i], formation_object_y_positions[i]) != 0)
                active_sprite_draw_flag = 1;
        }

        if (world_animation_phase != 0)
            actor_3013_sprite_offset += 0xa0;
        if (actor_3013_sprite_offset == 0x460)
            actor_3013_sprite_offset = 0;
        if (formation_object_active_flags[i] != 0 &&
            remove_world_actor_at_position(formation_object_x_positions[i], formation_object_y_positions[i] - 128) != 0) {
            spawn_moving_actor(3, formation_object_x_positions[i], formation_object_y_positions[i]);
            add_and_draw_player_score(1000L);
            request_priority_sound_effect(10);
            spawn_contact_flash_effect(formation_object_x_positions[i], formation_object_y_positions[i] - 128);
            formation_object_active_flags[i] = 0;
        }
    }

    ++formation_active_object_count;
    if (formation_active_object_count == 39)
        formation_active_object_count = 0;
}

/* Updates and draws records from level-map marker 0x3014; the concrete entity identity is not
   established by source. */
void update_actor_3014(void)
{
    register int i;
    struct actor_3014_record far *actor;

    /* Select VGA graphics-controller register 5 with value 1. */
    outport(0x3ce, 0x105);
    actor_3014_sprite_offset += 40;
    if (actor_3014_sprite_offset > 40)
        actor_3014_sprite_offset = 0;
    for (i = 0; i < actor_3014_count; ++i) {
        actor = &actor_3014_records[i];
        if (is_world_position_outside_view(actor->world_x, actor->world_y) == 0)
            copy_planar_video_region(actor->world_x - level_scroll_x,
                                     ((actor->world_y - level_map_y_offset) >> 3) + 16,
                                     actor_3014_sprite_offset);
    }
}

/* Updates and draws records from level-map marker 0x3015; the concrete entity identity is not
   established by source. */
void update_actor_3015(void)
{
    register int i;
    struct actor_3015_record far *actor;

    if (world_animation_phase == 0)
        actor_3015_sprite_offset += 0xa0;

    if (actor_3015_sprite_offset == 0x280)
        actor_3015_sprite_offset = 0;
    i = 0;

    for (; i < actor_3015_count; ++i) {
        actor = &actor_3015_records[i];

        if (actor->state >= 3 && is_world_position_outside_view(actor->world_x, actor->world_y))
            actor->state = 0;

        if (actor->state == 0)
            continue;

        if (is_world_position_outside_view(actor->world_x, actor->world_y))
            continue;

        if (actor->state >= 3 && is_world_position_outside_view(actor->world_x, actor->world_y)) {
            actor->state = 0;
            continue;
        }

        if (!is_level_position_blocked(actor->world_x, actor->world_y + 128) && actor->state < 3)
            actor->world_y += 128;

        if (actor->state >= 3) {
            if (world_animation_phase != 0)
                actor->world_y -= 64;
            if (is_level_position_blocked(actor->world_x, actor->world_y - 64)) {
                spawn_moving_actor(1, actor->world_x, actor->world_y);
                actor->state = 0;
                continue;
            }
            if (test_player_overlap_with_object(actor->world_x, actor->world_y)) {
                actor->state = 0;
                add_and_draw_player_score(1000L);
                queue_ambient_sprite_animation(0x3c0, actor->world_x, actor->world_y);
                request_priority_sound_effect(0x10);
                continue;
            }
        }

        if (remove_world_actor_at_position(actor->world_x, actor->world_y)) {
            if (actor->state == 1) {
                spawn_contact_flash_effect(actor->world_x, actor->world_y);
                actor->state = 2;
                if (!is_level_position_blocked(actor->world_x, actor->world_y + 128)) {
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, actor->world_x, actor->world_y);
                }
            } else if (actor->state == 2) {
                actor->state = 3;
                request_priority_sound_effect(2);
            }
        }

        if (test_player_overlap_with_object(actor->world_x, actor->world_y) && actor->state == 2) {
            actor->state = 0;
            add_and_draw_player_score(200L);
            queue_ambient_sprite_animation(0x140, actor->world_x, actor->world_y);
            advance_title_screen_animation();
            request_priority_sound_effect(1);
            if (hint_revealed_object_2 != 0) {
                show_secret_tip_soda();
                hint_revealed_object_2 = 0;
            }
        }

        if (actor->state == 1)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3f20,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
        if (actor->state == 2)
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3015_sprite_offset + 0x5000,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
        if (actor->state >= 3)
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3015_sprite_offset + 0x5280,
                                    actor->world_x - level_scroll_x,
                                    ((actor->world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Updates and draws records from level-map marker 0x3016; the concrete entity identity is not
   established by source. */
void update_actor_3016(void)
{
    register int i;
    struct actor_3016_record far *actor_record;

    actor_3016_upper_sprite_offset += 0xa0;
    actor_3016_lower_sprite_offset -= 0xa0;
    if (actor_3016_lower_sprite_offset == -0xa0)
        actor_3016_lower_sprite_offset = 0x1e0;
    if (actor_3016_upper_sprite_offset == 0x280)
        actor_3016_upper_sprite_offset = 0;

    for (i = 0; i < actor_3016_count; ++i) {
        actor_record = &actor_3016_records[i];
        if (actor_record->state == 0)
            continue;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;

        if (actor_record->state == 1) {
            actor_record->world_y -= 8;
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3016_upper_sprite_offset + 0x5500,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (is_level_position_blocked(actor_record->world_x - 2, actor_record->world_y) == 0 ||
                is_level_position_blocked(actor_record->world_x, actor_record->world_y) != 0)
                actor_record->state = 2;
        } else if (actor_record->state == 2) {
            actor_record->world_y += 8;
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3016_lower_sprite_offset + 0x5500,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (is_level_position_blocked(actor_record->world_x - 2, actor_record->world_y + 128) == 0 ||
                is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) != 0)
                actor_record->state = 1;
        } else if (actor_record->state == 3) {
            actor_record->world_y -= 8;
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3016_upper_sprite_offset + 0x5780,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (is_level_position_blocked(actor_record->world_x + 2, actor_record->world_y) == 0 ||
                is_level_position_blocked(actor_record->world_x, actor_record->world_y) != 0)
                actor_record->state = 4;
        } else if (actor_record->state == 4) {
            actor_record->world_y += 8;
            blit_planar_sprite_rows(sprite_graphics_buffer + actor_3016_lower_sprite_offset + 0x5780,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (is_level_position_blocked(actor_record->world_x + 2, actor_record->world_y + 128) == 0 ||
                is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) != 0)
                actor_record->state = 3;
        }

        if (remove_world_actor_at_position(actor_record->world_x, actor_record->world_y) != 0) {
            spawn_moving_actor(1, actor_record->world_x, actor_record->world_y);
            spawn_pickup_object(actor_record->world_x, actor_record->world_y - 64);
            add_and_draw_player_score(100L);
            request_priority_sound_effect(18);
            actor_record->state = 0;
        }
        if (actor_record->state != 0 && test_player_overlap_with_object(actor_record->world_x, actor_record->world_y) != 0)
            active_sprite_draw_flag = 1;
    }
}

/* Updates and draws records from level-map marker 0x3018; the concrete entity identity is not
   established by source. */
void update_actor_3018(void)
{
    register int i;
    struct actor_3018_record far *actor_record;

    for (i = 0; i < actor_3018_count; i++) {
        actor_record = &actor_3018_records[i];
        if (actor_record->state == 0)
            continue;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;
        if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0)
            actor_record->world_y += 128;
        if (test_player_overlap_with_object(actor_record->world_x, actor_record->world_y)) {
            if (actor_record->state > 1 && hint_revealed_object_11 != 0) {
                hint_revealed_object_11 = 0;
                show_secret_tip_turkey();
            }
            if (actor_record->state == 2) {
                actor_record->state = 0;
                add_and_draw_player_score(100L);
                queue_ambient_sprite_animation(0, actor_record->world_x, actor_record->world_y);
                request_priority_sound_effect(1);
                advance_title_screen_animation();
                continue;
            }
            if (actor_record->state == 3) {
                actor_record->state = 0;
                add_and_draw_player_score(200L);
                queue_ambient_sprite_animation(0x140, actor_record->world_x, actor_record->world_y);
                request_priority_sound_effect(1);
                advance_title_screen_animation();
                advance_title_screen_animation();
                continue;
            }
        }
        if (actor_record->state != 3 && remove_world_actor_at_position(actor_record->world_x, actor_record->world_y)) {
            if (actor_record->state == 1) {
                spawn_contact_flash_effect(actor_record->world_x, actor_record->world_y);
                if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0) {
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, actor_record->world_x, actor_record->world_y);
                }
                actor_record->state = 2;
            } else if (actor_record->state == 2)
                actor_record->state = 3;
        }
        if (actor_record->state == 1) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3f20,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        } else {
            if (actor_record->state == 2) {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1b80,
                                        actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            }
            if (actor_record->state == 3) {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x1c20,
                                        actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            }
        }
        if (actor_record->state > 1 && hint_revealed_object_11 != 0 && test_player_overlap_with_object(actor_record->world_x, actor_record->world_y)) {
            hint_revealed_object_11 = 0;
            show_secret_tip_turkey();
        }
    }
}

/* Updates and draws records from level-map marker 0x3019; the concrete entity identity is not
   established by source. */
void update_actor_3019(void)
{
    register int tile_column;

    if (actor_3019_enabled == 0)
        return;
    if (test_player_vertical_range(actor_3019_world_x - 2, actor_3019_world_x + actor_3019_width, actor_3019_world_y - 32) != 0) {
        if (actor_3019_animation_state == 2) {
            for (tile_column = 0; tile_column < (actor_3019_width >> 1); tile_column++) {
                /* The row stride is 128 words; keep this pointer form for the match. */
                *((level_tile_map + actor_3019_screen_x + tile_column) + (actor_3019_map_row << 7) - 2) =
                    *((level_tile_map + actor_3019_screen_x + tile_column) + (actor_3019_map_row << 7) - 130);
                if (tile_column % 2 != 0)
                    spawn_contact_flash_effect(actor_3019_world_x * 2 + tile_column * 2, actor_3019_world_y);
                else
                    spawn_moving_actor(1, actor_3019_world_x * 2 + tile_column * 2, actor_3019_world_y);
            }
            actor_3019_enabled = 0;
            actor_3019_animation_state = 0;
            actor_3019_animation_state = 1;
            return;
        }
        actor_3019_animation_state = 1;
        return;
    }
    if (actor_3019_animation_state == 1)
        actor_3019_animation_state = 2;
}

/* Updates and draws records from level-map marker 0x301A; the concrete entity identity is not
   established by source. */
void update_actor_301a(void)
{
    register int i;
    struct actor_301a_record far *p;

    actor_301a_sprite_offset += 0xa0;
    if (actor_301a_sprite_offset == 0x280)
        actor_301a_sprite_offset = 0;

    for (i = 0; i < actor_301a_count; ++i) {
        p = &actor_301a_records[i];
        if (p->active != 0 && is_world_position_outside_view(p->world_x, p->world_y) == 0) {
            if (test_player_overlap_with_object(p->world_x, p->world_y) != 0) {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_301a_sprite_offset + 0x21c0,
                                        p->world_x - level_scroll_x,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
                active_sprite_draw_flag = 1;
            } else {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_301a_sprite_offset + 0x1f40,
                                        p->world_x - level_scroll_x,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
            }
            if (world_animation_phase == 0)
                request_priority_sound_effect(21);
        }
    }
}

/* Draws two vertically stacked sprite cells for an actor. */
void pascal draw_two_tile_tall_actor_sprite(int row, int horizontal, int vertical)
{
    register int index = row * 0x140 + 0x6180;

    if (is_world_position_outside_view(horizontal, vertical - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + index, horizontal - level_scroll_x,
                                (vertical - level_map_y_offset) >> 3);
    if (is_world_position_outside_view(horizontal, vertical) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + index + 0xa0, horizontal - level_scroll_x,
                                ((vertical - level_map_y_offset) >> 3) + 16);
}

/* Updates and draws records from level-map marker 0x301B; the concrete entity identity is not
   established by source. */
void update_actor_301b(void)
{
    register int i;
    struct actor_301b_record far *p;

    for (i = 0; i < actor_301b_count; i++) {
        p = &actor_301b_records[i];
        if (p->state != 0 &&
            (p->state <= 3 || p->state == 5 || p->state == 9 ||
             p->state == 15 || p->state == 25))
            p->animation_count++;

        if (p->animation_count == 4)
            p->animation_count = 0;

        if (is_world_position_outside_view(p->world_x, p->world_y) != 0 &&
            is_world_position_outside_view(p->world_x, p->world_y - 128) != 0)
            continue;

        if (remove_world_actor_at_position(p->world_x, p->world_y) != 0 ||
            remove_world_actor_at_position(p->world_x, p->world_y - 128) != 0) {
            if (p->state == 1 || p->state == 2)
                add_and_draw_player_score(1000L);
            p->state = 3;
            request_priority_sound_effect(18);
            spawn_pickup_object(p->world_x, p->world_y - 192);
        }

        if (p->state >= 3)
            p->state++;
        if (p->state == 26)
            p->state = 0;
        draw_two_tile_tall_actor_sprite(p->animation_count, p->world_x, p->world_y);

        if (p->state == 1) {
            if (test_player_overlap_with_object(p->world_x - 2, p->world_y - 64) ||
                test_player_overlap_with_object(p->world_x - 4, p->world_y - 64) ||
                test_player_overlap_with_object(p->world_x - 6, p->world_y - 64)) {
                if (test_player_floor_clearance())
                    player_screen_x--;
            }
        }

        if (p->state == 2) {
            if (test_player_overlap_with_object(p->world_x + 2, p->world_y - 64) ||
                test_player_overlap_with_object(p->world_x + 4, p->world_y - 64) ||
                test_player_overlap_with_object(p->world_x + 6, p->world_y - 64)) {
                if (test_player_body_clearance())
                    player_screen_x++;
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x301D; the concrete entity identity is not
   established by source. */
void update_actor_301d(void)
{
    register int i;
    struct actor_301d_record far *p;

    for (i = 0; i < actor_301d_count; i++) {
        p = &actor_301d_records[i];
        if (p->active != 0) {
            if (is_world_position_outside_view(p->world_x, p->world_y) == 0) {
                if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
                    p->world_y += 128;
                if (test_player_overlap_with_object(p->world_x, p->world_y) != 0 && p->animation_state != 0) {
                    p->active = 0;
                    queue_ambient_sprite_animation(0, p->world_x, p->world_y);
                    add_and_draw_player_score(100L);
                    request_priority_sound_effect(16);
                    continue;
                }
                if (p->animation_state == 0 && remove_world_actor_at_position(p->world_x, p->world_y) != 0) {
                    spawn_contact_flash_effect(p->world_x, p->world_y);
                    p->animation_state = 1;
                    if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0) {
                        add_and_draw_player_score(500L);
                        queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
                    }
                }
                if (p->animation_state == 0) {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3e80,
                                            p->world_x - level_scroll_x,
                                            ((p->world_y - level_map_y_offset) >> 3) + 16);
                } else {
                    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2440,
                                            p->world_x - level_scroll_x,
                                            ((p->world_y - level_map_y_offset) >> 3) + 16);
                }
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x301E; the concrete entity identity is not
   established by source. */
void update_actor_301e(void)
{
    register int i;
    struct actor_301e_record far *p;

    for (i = 0; i < actor_301e_count; ++i) {
        p = &actor_301e_records[i];
        if (p->state == 0)
            continue;
        if (is_world_position_outside_view(p->world_x, p->world_y) != 0)
            continue;
        if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
            p->world_y += 128;
        if (test_player_overlap_with_object(p->world_x, p->world_y) != 0 && p->animation_flag != 0) {
            p->state = 0;
            queue_ambient_sprite_animation(0x500, p->world_x, p->world_y);
            add_and_draw_player_score(2000L);
            request_priority_sound_effect(16);
            continue;
        }
        if (p->animation_flag == 0 && remove_world_actor_at_position(p->world_x, p->world_y) != 0) {
            spawn_contact_flash_effect(p->world_x, p->world_y);
            p->animation_flag = 1;
            if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
            }
        }
        if (p->animation_flag == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3e80,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
        else
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x24e0,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Updates and draws records from level-map marker 0x301F; the concrete entity identity is not
   established by source. */
void update_actor_301f(void)
{
    register int i;
    struct actor_301f_record far *p;

    for (i = 0; i < actor_301f_count; ++i) {
        p = &actor_301f_records[i];
        if (p->state == 0)
            continue;
        if (is_world_position_outside_view(p->world_x, p->world_y) != 0)
            continue;
        if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
            p->world_y += 128;
        if (test_player_overlap_with_object(p->world_x, p->world_y) != 0 && p->animation_flag != 0) {
            p->state = 0;
            queue_ambient_sprite_animation(0x640, p->world_x, p->world_y);
            add_and_draw_player_score(5000L);
            request_priority_sound_effect(16);
            continue;
        }
        if (p->animation_flag == 0 && remove_world_actor_at_position(p->world_x, p->world_y) != 0) {
            spawn_contact_flash_effect(p->world_x, p->world_y);
            if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
            }
            p->animation_flag = 1;
        }
        if (p->animation_flag == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3e80,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
        else
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2580,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Updates and draws records from level-map marker 0x3021; the concrete entity identity is not
   established by source. */
void update_actor_3021(void)
{
    register int i;
    struct actor_3021_record far *actor_record;

    actor_3021_sprite_offset += 0xa0;
    if (actor_3021_sprite_offset == 0x280)
        actor_3021_sprite_offset = 0;
    for (i = 0; i < actor_3021_count; ++i) {
        actor_record = &actor_3021_records[i];
        if (actor_record[1].world_x == 0) /* Keep this next-actor_302a_record access form for the match. */
            continue;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;
        remove_world_actor_at_position(actor_record->world_x, actor_record->world_y);
        if (test_player_overlap_with_object(actor_record->world_x + 1, actor_record->world_y) != 0 &&
            control_left_pressed != 0 && test_player_body_clearance() != 0)
            ++player_screen_x;
        if (test_player_overlap_with_object(actor_record->world_x - 1, actor_record->world_y) != 0 &&
            control_right_pressed != 0 && test_player_floor_clearance() != 0)
            --player_screen_x;
        blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_3021_sprite_offset + 0x28a0,
                                actor_record->world_x - level_scroll_x,
                                ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        if (world_animation_phase == 0)
            request_priority_sound_effect(21);
    }
}

/* Draws a four-cell-wide actor row and marks player contact in its center cells. */
void pascal draw_four_wide_actor_sprite(int frame, int x, int y)
{
    register int offset;

    offset = frame * 0x280;
    offset += 0x6680;

    if (is_world_position_outside_view(x, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset,
                                x - level_scroll_x,
                                ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 2, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0xa0,
                                x - level_scroll_x + 2,
                                ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 4, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0x140,
                                x - level_scroll_x + 4,
                                ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 6, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0x1e0,
                                x - level_scroll_x + 6,
                                ((y - level_map_y_offset) >> 3) + 16);

    if (test_player_overlap_with_object(x + 2, y - 64) != 0 ||
        test_player_overlap_with_object(x + 4, y - 64) != 0)
        active_sprite_draw_flag = 1;
}

/* Draws the wide actor sprite using the active page and graphics resources. */
void pascal draw_wide_actor_sprite(int frame, int x, int y)
{
    register int offset;

    offset = frame * 0x280 + 0x6e00;
    if (is_world_position_outside_view(x, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset, x - level_scroll_x, ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 2, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0xa0, x - level_scroll_x + 2, ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 4, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0x140, x - level_scroll_x + 4, ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 6, y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0x1e0, x - level_scroll_x + 6, ((y - level_map_y_offset) >> 3) + 16);
        request_priority_sound_effect(22);
    }
}

/* Updates and draws records from level-map marker 0x3022; the concrete entity identity is not
   established by source. */
void update_actor_3022(void)
{
    register int i;
    struct actor_3022_record far *actor_record;

    actor_3022_animation_phase = !actor_3022_animation_phase;
    for (i = 0; i < actor_3022_count; i++) {
        actor_record = &actor_3022_records[i];
        if (actor_record->movement_state == 0)
            continue;

        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) == 0 && actor_record->jump_timer == 0) {
            if (is_level_position_blocked(actor_record->world_x + 3, actor_record->world_y + 128))
                actor_record->jump_timer = 24;
            else
                actor_record->jump_timer = 1;
        }

        if (actor_record->jump_timer == 0)
            continue;

        if (actor_record->jump_timer > 2) {
            --actor_record->jump_timer;
            actor_record->world_y -= 16;
        }
        if (actor_record->fall_counter > 1 && actor_record->jump_timer <= 2) {
            actor_record->world_y += 16;
            ++actor_record->fall_counter;
            if (actor_record->fall_counter >= 24 || is_level_position_blocked(actor_record->world_x + 3, actor_record->world_y + 128)) {
                actor_record->jump_timer = 24;
                actor_record->fall_counter = 0;
            }
        }

        if (actor_record->world_x + 3 > player_screen_x + level_scroll_x) {
            actor_record->movement_state = 2;
            if (world_animation_phase == 0 || world_animation_phase == 0x40) {
                if (test_level_tile_special_state(actor_record->world_x - 2, actor_record->world_y) == 0)
                    --actor_record->world_x;
            }
        } else if (actor_record->world_x + 3 < player_screen_x + level_scroll_x) {
            actor_record->movement_state = 3;
            if (world_animation_phase == 0 || world_animation_phase == 0x40) {
                if (test_level_tile_special_state(actor_record->world_x + 8, actor_record->world_y) == 0)
                    ++actor_record->world_x;
            }
        } else {
            if (actor_record->jump_timer < 3 && actor_record->fall_counter == 0)
                actor_record->fall_counter = 2;
            actor_record->movement_state = 1;
        }

        if (remove_world_actor_at_position(actor_record->world_x, actor_record->world_y) ||
            remove_world_actor_at_position(actor_record->world_x + 8, actor_record->world_y) ||
            remove_world_actor_at_position(actor_record->world_x + 4, actor_record->world_y - 128)) {
            if (actor_record->hit_points != 0)
                --actor_record->hit_points;
        }
        if (actor_record->hit_points < 4 && world_animation_phase == 0)
            spawn_pickup_object(actor_record->world_x + 3, actor_record->world_y - 96);
        if (actor_record->hit_points < 3 && world_animation_phase == 0x20)
            spawn_pickup_object(actor_record->world_x, actor_record->world_y - 96);
        if (actor_record->hit_points < 2 && world_animation_phase == 0x40)
            spawn_pickup_object(actor_record->world_x + 2, actor_record->world_y - 128);

        if (actor_record->hit_points == 0) {
            if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) ||
                is_level_position_blocked(actor_record->world_x + 8, actor_record->world_y + 128)) {
                spawn_contact_flash_effect(actor_record->world_x, actor_record->world_y);
                spawn_contact_flash_effect(actor_record->world_x + 2, actor_record->world_y - 64);
                spawn_contact_flash_effect(actor_record->world_x + 4, actor_record->world_y);
                spawn_contact_flash_effect(actor_record->world_x + 6, actor_record->world_y - 64);
                spawn_contact_flash_effect(actor_record->world_x + 8, actor_record->world_y);
                spawn_animated_actor_sprite(actor_record->world_x + 1, actor_record->world_y - 32);
                spawn_animated_actor_sprite(actor_record->world_x + 5, actor_record->world_y - 128);
                spawn_moving_actor(1, actor_record->world_x + 1, actor_record->world_y - 32);
                spawn_moving_actor(1, actor_record->world_x + 7, actor_record->world_y - 64);
                spawn_moving_actor(1, actor_record->world_x + 1, actor_record->world_y - 32);
                spawn_moving_actor(1, actor_record->world_x + 2, actor_record->world_y - 128);
                spawn_moving_actor(1, actor_record->world_x + 3, actor_record->world_y - 128);
                spawn_moving_actor(1, actor_record->world_x + 5, actor_record->world_y - 32);
                actor_record->movement_state = 0;
                add_and_draw_player_score(5000L);
                continue;
            }
            actor_record->world_y += 32;
        }

        switch (actor_record->movement_state) {
        case 2:
            draw_wide_actor_sprite(actor_3022_animation_phase, actor_record->world_x, actor_record->world_y - 128);
            draw_four_wide_actor_sprite(0, actor_record->world_x, actor_record->world_y);
            break;
        case 1:
            draw_wide_actor_sprite(actor_3022_animation_phase + 2, actor_record->world_x, actor_record->world_y - 128);
            draw_four_wide_actor_sprite(1, actor_record->world_x, actor_record->world_y);
            break;
        case 3:
            draw_wide_actor_sprite(actor_3022_animation_phase + 4, actor_record->world_x, actor_record->world_y - 128);
            draw_four_wide_actor_sprite(2, actor_record->world_x, actor_record->world_y);
            break;
        }
    }
}

/* Updates and draws records from level-map marker 0x3023; the concrete entity identity is not
   established by source. */
void update_actor_3023(void)
{
    register int i;
    struct actor_3023_record far *actor_record;

    for (i = 0; i < actor_3023_count; i++) {
        actor_record = &actor_3023_records[i];
        if (actor_record->state == 0)
            continue;

        if (actor_record->state == 1) {
            if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0)
                actor_record->world_y += 64;
            if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) == 0) {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3e80,
                                        actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
                if (remove_world_actor_at_position(actor_record->world_x, actor_record->world_y) != 0) {
                    spawn_contact_flash_effect(actor_record->world_x, actor_record->world_y);
                    if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0) {
                        add_and_draw_player_score(500L);
                        queue_ambient_sprite_animation(0x280, actor_record->world_x, actor_record->world_y);
                    }
                    actor_record->state = 2;
                }
            }
            continue;
        }

        if (world_animation_phase == 0)
            actor_3023_sprite_offset += 0xa0;
        if (actor_3023_sprite_offset == 0x1e0)
            actor_3023_sprite_offset = 0;

        if (is_level_position_blocked(actor_record->world_x, actor_record->world_y - 128) == 0)
            actor_record->world_y -= 8;
        if (remove_world_actor_at_position(actor_record->world_x, actor_record->world_y - 128) != 0 || is_level_position_blocked(actor_record->world_x, actor_record->world_y - 128) != 0) {
            if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y - 128) == 0)
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2da0,
                                        actor_record->world_x - level_scroll_x,
                                        (actor_record->world_y - level_map_y_offset) >> 3);
            actor_record->state = 0;
            spawn_pickup_object(actor_record->world_x, actor_record->world_y - 128);
            continue;
        }
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y - 128) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2b20,
                                    actor_record->world_x - level_scroll_x,
                                    (actor_record->world_y - level_map_y_offset) >> 3);
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) == 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_3023_sprite_offset + 0x2bc0,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        if (test_player_overlap_with_object(actor_record->world_x, actor_record->world_y) != 0) {
            add_and_draw_player_score(10000L);
            queue_ambient_sprite_animation(0x780, actor_record->world_x, actor_record->world_y - 128);
            request_priority_sound_effect(3);
            actor_record->state = 0;
        }
    }
}

/* Updates and draws records from level-map marker 0x3024; the concrete entity identity is not
   established by source. */
void update_actor_3024(void)
{
    register int i;
    struct actor_3024_record far *actor_record;

    level_play_state = 1;
    for (i = 0; i < actor_3024_count; ++i) {
        actor_record = &actor_3024_records[i];
        if (actor_record->state == 0)
            continue;

        level_play_state = 0;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;

        if (actor_record->world_x - 2 > player_screen_x + level_scroll_x) {
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x7d00,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        } else if (actor_record->world_x + 2 < player_screen_x + level_scroll_x) {
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x7e40,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        } else {
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x7da0,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        }

        if (remove_world_actor_at_position(actor_record->world_x, actor_record->world_y) != 0) {
            queue_ambient_sprite_animation(0, actor_record->world_x, actor_record->world_y);
            add_and_draw_player_score(100L);
            spawn_moving_actor(1, actor_record->world_x, actor_record->world_y);
            actor_record->state = 0;
            request_priority_sound_effect(18);
        }
    }
}

/* Draws the animated level tile using the active page and graphics resources. */
void draw_animated_level_tile(void)
{
    register unsigned int i;
    struct animated_level_tile_record far *p;

    for (i = 0; i < actor_3025_count; ++i) {
        p = &animated_level_tile_records[i];
        if (is_world_position_outside_view(p->world_x, p->world_y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + p->sprite_resource_offset,
                    p->world_x - level_scroll_x,
                    ((p->world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Updates and draws records from level-map marker 0x3029; the concrete entity identity is not
   established by source. */
void update_actor_3029(void)
{
    register unsigned int actor_index;
    struct actor_3029_record far *actor_record;

    actor_3024_sprite_offset += 0xa0;
    if (actor_3024_sprite_offset == 0x5a0)
        actor_3024_sprite_offset = 0;

    for (actor_index = 0; actor_index < actor_3029_count; ++actor_index) {
        actor_record = &actor_3029_records[actor_index];
        if (actor_record->state == 0)
            continue;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;
        if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0)
            actor_record->world_y += 128;

        if (actor_record->state == 1) {
            if (remove_world_actor_at_position(actor_record->world_x, actor_record->world_y) != 0) {
                spawn_contact_flash_effect(actor_record->world_x, actor_record->world_y);
                actor_record->state = 2;
                if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0) {
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, actor_record->world_x, actor_record->world_y);
                }
            }
        }

        if (actor_record->state == 2 && test_player_overlap_with_object(actor_record->world_x, actor_record->world_y) != 0) {
            actor_record->state = 0;
            title_graphic_frame_index = 9;
            add_and_draw_player_score(1000L);
            queue_ambient_sprite_animation(0x3c0, actor_record->world_x, actor_record->world_y);
            draw_title_screen_graphic();
            request_priority_sound_effect(4);
            if (hint_revealed_object_10 != 0) {
                hint_revealed_object_10 = 0;
                show_secret_tip_nuclear();
            }
            continue;
        }

        if (actor_record->state == 1) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        } else {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_3024_sprite_offset + 0x2e40,
                                    actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* Updates and draws records from level-map marker 0x302A; the concrete entity identity is not
   established by source. */
void update_actor_302a(void)
{
    struct actor_302a_record far *p;
    register int i;

    actor_302a_update_state = 1;
    for (i = 0; i < actor_302a_count; ++i) {
        p = &actor_302a_records[i];
        if (p->state == 0)
            continue;
        actor_302a_update_state = 0;
        if (is_world_position_outside_view(p->world_x, p->world_y) && is_world_position_outside_view(p->world_x, p->world_y)) {
            if (p->state > 15) {
                p->state = 0;
                continue;
            } else {
                continue;
            }
        } else {
            if (p->state > 1) {
                if (is_level_position_blocked(p->world_x + 1, p->world_y + 128)) {
                    spawn_contact_flash_effect(p->world_x + 1, p->world_y);
                    spawn_pickup_object(p->world_x + 1, p->world_y);
                    p->state = 0;
                    continue;
                }
                ++p->state;
            }
            if (p->state < 2) {
                /* Scale the tile value by 128 before comparing world positions. */
                if (p->world_x - 1 <= player_screen_x + level_scroll_x &&
                    p->world_x + 3 >= player_screen_x + level_scroll_x &&
                    ((player_screen_y >> 4) << 7) + level_map_y_offset - p->world_y < 1024 &&
                    ((player_screen_y >> 4) << 7) + level_map_y_offset - p->world_y > 0)
                    p->state = 2;
            }
            if (p->state == 16)
                request_priority_sound_effect(32);
            if (p->state > 15) {
                p->world_y += 96;
                if (test_player_overlap_with_object(p->world_x, p->world_y) || test_player_overlap_with_object(p->world_x + 2, p->world_y))
                    active_sprite_draw_flag = 1;
                if (remove_world_actor_at_position(p->world_x, p->world_y - 64) ||
                    remove_world_actor_at_position(p->world_x + 2, p->world_y - 64)) {
                    spawn_contact_flash_effect(p->world_x + 1, p->world_y);
                    spawn_pickup_object(p->world_x + 1, p->world_y);
                    spawn_moving_actor(1, p->world_x + 1, p->world_y);
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, p->world_x + 1, p->world_y);
                    p->state = 0;
                    continue;
                }
            }
        }
        if (p->state == 1 || p->state >= 15) {
            if (!is_world_position_outside_view(p->world_x, p->world_y))
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x33e0,
                                        p->world_x - level_scroll_x,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
            if (!is_world_position_outside_view(p->world_x + 2, p->world_y))
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3480,
                                        p->world_x - level_scroll_x + 2,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
        }
        if (p->state >= 15)
            continue;
        if (!is_world_position_outside_view(p->world_x, p->world_y))
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x33e0,
                                    p->world_x - level_scroll_x,
                                    (p->state % 2) + ((p->world_y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(p->world_x + 2, p->world_y))
            continue;
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3480,
                                p->world_x - level_scroll_x + 2,
                                (p->state % 2) + ((p->world_y - level_map_y_offset) >> 3) + 16);
    }
}

/* Updates and draws records from level-map marker 0x302B; the concrete entity identity is not
   established by source. */
void update_actor_302b(void)
{
    register int i;
    register int event;

    event = 0;
    actor_3029_sprite_offset += 0xa0;
    if (actor_3029_sprite_offset == 0x320)
        actor_3029_sprite_offset = 0;
    if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y) != 0) {
        if (actor_302b_open_state < 2)
            return;
        actor_302b_open_state = 0;
        for (i = 0; i < actor_301a_count; ++i)
            actor_301a_records[i].active = 0;
        return;
    }

    if (actor_302b_active_state != 0 && actor_302b_open_state == 0)
        return;

    if (remove_world_actor_at_position(actor_302b_world_x, actor_302b_world_y) != 0) {
        --actor_302b_animation_counter;
        spawn_contact_flash_effect(actor_302b_world_x, actor_302b_world_y);
        if (actor_302b_animation_counter == 0)
            actor_302b_active_state = 1;
        event = 1;
        request_priority_sound_effect(10);
    }
    if (remove_world_actor_at_position(actor_302b_world_x, actor_302b_world_y - 128) != 0) {
        --actor_302b_animation_counter;
        spawn_contact_flash_effect(actor_302b_world_x, actor_302b_world_y - 128);
        if (actor_302b_animation_counter == 0)
            actor_302b_active_state = 1;
        event = 1;
        request_priority_sound_effect(10);
    }
    if (remove_world_actor_at_position(actor_302b_world_x, actor_302b_world_y - 256) != 0) {
        --actor_302b_animation_counter;
        spawn_contact_flash_effect(actor_302b_world_x, actor_302b_world_y - 256);
        if (actor_302b_animation_counter == 0)
            actor_302b_active_state = 1;
        event = 1;
        request_priority_sound_effect(10);
    }

    if (actor_302b_active_state == 0) {
        request_priority_sound_effect(36);
        if (event == 0) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_3029_sprite_offset + 0x3840,
                                    actor_302b_world_x - level_scroll_x,
                                    ((actor_302b_world_y - level_map_y_offset) >> 3) + 16);
            if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y - 128) == 0)
                blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_3029_sprite_offset + 0x3840,
                                        actor_302b_world_x - level_scroll_x,
                                        (actor_302b_world_y - level_map_y_offset) >> 3);
            if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y - 256) == 0)
                blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_3029_sprite_offset + 0x3840,
                                        actor_302b_world_x - level_scroll_x,
                                        ((actor_302b_world_y - level_map_y_offset) >> 3) - 16);
        } else {
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x9f60,
                                    actor_302b_world_x - level_scroll_x,
                                    ((actor_302b_world_y - level_map_y_offset) >> 3) + 16);
            if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y - 128) == 0)
                blit_planar_sprite_rows(sprite_graphics_buffer + 0x9f60,
                                        actor_302b_world_x - level_scroll_x,
                                        (actor_302b_world_y - level_map_y_offset) >> 3);
            if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y - 256) == 0)
                blit_planar_sprite_rows(sprite_graphics_buffer + 0x9f60,
                                        actor_302b_world_x - level_scroll_x,
                                        ((actor_302b_world_y - level_map_y_offset) >> 3) - 16);
        }
        if (test_player_overlap_with_object(actor_302b_world_x, actor_302b_world_y - 64) != 0) {
            if (title_graphic_frame_index > 0) {
                title_graphic_frame_index = 0;
                draw_title_screen_graphic();
            }
        }
        return;
    }

    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3840,
                            actor_302b_world_x - level_scroll_x,
                            ((actor_302b_world_y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y - 128) == 0)
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3840,
                                actor_302b_world_x - level_scroll_x,
                                (actor_302b_world_y - level_map_y_offset) >> 3);
    if (is_world_position_outside_view(actor_302b_world_x, actor_302b_world_y - 256) == 0)
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3840,
                                actor_302b_world_x - level_scroll_x,
                                ((actor_302b_world_y - level_map_y_offset) >> 3) - 16);
    ++actor_302b_open_state;
    if (world_animation_phase == 0)
        spawn_pickup_object(actor_302b_world_x - 1, actor_302b_world_y);
    if (world_animation_phase == 0x40)
        spawn_pickup_object(actor_302b_world_x + 1, actor_302b_world_y);
    if (actor_302b_open_state == 32) {
        actor_302b_open_state = 0;
        for (i = 0; i < actor_301a_count; ++i)
            actor_301a_records[i].active = 0;
        add_and_draw_player_score(20000L);
        request_priority_sound_effect(17);
        return;
    }
    if (world_animation_phase == 0)
        return;

    switch (actor_302b_open_state) {
    case 2:
        spawn_moving_actor(1, actor_302b_world_x - 1, actor_302b_world_y);
        break;
    case 8:
        spawn_moving_actor(1, actor_302b_world_x - 2, actor_302b_world_y - 128);
        break;
    case 10:
        spawn_moving_actor(1, actor_302b_world_x + 1, actor_302b_world_y + 256);
        break;
    case 13:
        spawn_moving_actor(1, actor_302b_world_x, actor_302b_world_y + 128);
        spawn_moving_actor(1, actor_302b_world_x - 1, actor_302b_world_y + 384);
        spawn_moving_actor(1, actor_302b_world_x, actor_302b_world_y - 384);
        spawn_moving_actor(3, actor_302b_world_x + 2, actor_302b_world_y);
        spawn_moving_actor(3, actor_302b_world_x, actor_302b_world_y + 128);
        break;
    case 15:
        spawn_moving_actor(1, actor_302b_world_x + 2, actor_302b_world_y - 128);
        break;
    case 17:
        spawn_moving_actor(1, actor_302b_world_x + 1, actor_302b_world_y + 256);
        spawn_moving_actor(1, actor_302b_world_x + 2, actor_302b_world_y);
        spawn_moving_actor(1, actor_302b_world_x - 3, actor_302b_world_y - 256);
        spawn_contact_flash_effect(actor_302b_world_x - 1, actor_302b_world_y);
        break;
    case 18:
        spawn_contact_flash_effect(actor_302b_world_x + 3, actor_302b_world_y - 256);
        spawn_moving_actor(1, actor_302b_world_x + 1, actor_302b_world_y + 256);
        break;
    case 23:
        spawn_animated_actor_sprite(actor_302b_world_x, actor_302b_world_y + 64);
        spawn_animated_actor_sprite(actor_302b_world_x - 1, actor_302b_world_y - 64);
        spawn_moving_actor(3, actor_302b_world_x, actor_302b_world_y + 128);
        spawn_contact_flash_effect(actor_302b_world_x + 2, actor_302b_world_y);
        spawn_contact_flash_effect(actor_302b_world_x - 1, actor_302b_world_y + 384);
        spawn_moving_actor(1, actor_302b_world_x - 1, actor_302b_world_y + 384);
        spawn_moving_actor(3, actor_302b_world_x, actor_302b_world_y - 384);
        spawn_moving_actor(3, actor_302b_world_x + 2, actor_302b_world_y - 128);
        spawn_moving_actor(1, actor_302b_world_x + 1, actor_302b_world_y + 256);
        break;
    case 24:
        spawn_contact_flash_effect(actor_302b_world_x + 1, actor_302b_world_y + 128);
        spawn_contact_flash_effect(actor_302b_world_x - 2, actor_302b_world_y - 256);
        spawn_moving_actor(1, actor_302b_world_x + 2, actor_302b_world_y);
        spawn_moving_actor(3, actor_302b_world_x - 3, actor_302b_world_y - 256);
        spawn_contact_flash_effect(actor_302b_world_x - 1, actor_302b_world_y);
        spawn_contact_flash_effect(actor_302b_world_x + 3, actor_302b_world_y - 256);
        spawn_moving_actor(1, actor_302b_world_x - 1, actor_302b_world_y);
        spawn_moving_actor(3, actor_302b_world_x - 2, actor_302b_world_y - 128);
        spawn_moving_actor(1, actor_302b_world_x + 1, actor_302b_world_y + 256);
        break;
    case 29:
        spawn_animated_actor_sprite(actor_302b_world_x + 3, actor_302b_world_y - 128);
        spawn_animated_actor_sprite(actor_302b_world_x + 2, actor_302b_world_y + 256);
        spawn_moving_actor(1, actor_302b_world_x, actor_302b_world_y + 128);
        spawn_contact_flash_effect(actor_302b_world_x + 2, actor_302b_world_y);
        spawn_contact_flash_effect(actor_302b_world_x - 1, actor_302b_world_y + 384);
        spawn_moving_actor(3, actor_302b_world_x - 1, actor_302b_world_y + 384);
        spawn_moving_actor(1, actor_302b_world_x, actor_302b_world_y - 384);
        spawn_moving_actor(3, actor_302b_world_x + 2, actor_302b_world_y - 128);
        spawn_moving_actor(1, actor_302b_world_x + 1, actor_302b_world_y + 256);
        break;
    case 31:
        spawn_animated_actor_sprite(actor_302b_world_x - 2, actor_302b_world_y - 384);
        spawn_contact_flash_effect(actor_302b_world_x + 1, actor_302b_world_y + 128);
        spawn_contact_flash_effect(actor_302b_world_x, actor_302b_world_y);
        spawn_moving_actor(3, actor_302b_world_x + 2, actor_302b_world_y);
        spawn_moving_actor(3, actor_302b_world_x - 3, actor_302b_world_y - 256);
        spawn_contact_flash_effect(actor_302b_world_x - 1, actor_302b_world_y);
        spawn_contact_flash_effect(actor_302b_world_x + 3, actor_302b_world_y - 256);
        spawn_moving_actor(1, actor_302b_world_x - 1, actor_302b_world_y);
        spawn_moving_actor(1, actor_302b_world_x - 2, actor_302b_world_y - 128);
        spawn_moving_actor(3, actor_302b_world_x + 1, actor_302b_world_y + 256);
        queue_ambient_sprite_animation(0x780, actor_302b_world_x - 1, actor_302b_world_y);
        queue_ambient_sprite_animation(0x780, actor_302b_world_x + 1, actor_302b_world_y);
        break;
    }
}

/* Updates and draws records from level-map marker 0x302C; the concrete entity identity is not
   established by source. */
void update_actor_302c(void)
{
    register int i;
    struct actor_302c_record far *p;

    for (i = 0; i < actor_302c_count; ++i) {
        p = &actor_302c_records[i];
        if (is_world_position_outside_view(p->world_x, p->world_y) == 0) {
            if (test_player_overlap_with_object(p->world_x, p->world_y)) {
                active_sprite_draw_flag = 1;
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3c00,
                                        p->world_x - level_scroll_x,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
            } else {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3b60,
                                        p->world_x - level_scroll_x,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x302D; the concrete entity identity is not
   established by source. */
void update_actor_302d(void)
{
    register int i;
    struct actor_302d_record far *p;

    actor_302a_sprite_offset += 0xa0;
    if (actor_302a_sprite_offset == 0x1e0)
        actor_302a_sprite_offset = 0;
    for (i = 0; i < actor_302d_count; i++) {
        p = &actor_302d_records[i];
        if (p->state == 0)
            continue;
        if (is_world_position_outside_view(p->world_x, p->world_y) != 0)
            continue;
        if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
            p->world_y += 128;
        if (p->state == 1 && remove_world_actor_at_position(p->world_x, p->world_y)) {
            spawn_contact_flash_effect(p->world_x, p->world_y);
            if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
            }
            p->state = 2;
        }
        if (p->state == 2 && test_player_overlap_with_object(p->world_x, p->world_y) != 0) {
            p->state = 0;
            request_priority_sound_effect(16);
            switch (world_animation_phase) {
            case 0:
                add_and_draw_player_score(100L);
                queue_ambient_sprite_animation(0, p->world_x, p->world_y);
                break;
            case 0x20:
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
                break;
            case 0x40:
                add_and_draw_player_score(2000L);
                queue_ambient_sprite_animation(0x500, p->world_x, p->world_y);
                break;
            case 0x60:
                add_and_draw_player_score(5000L);
                queue_ambient_sprite_animation(0x640, p->world_x, p->world_y);
                break;
            default:
                continue;
            }
            continue;
        }
        if (p->state == 1) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3e80,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
        } else {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_302a_sprite_offset + 0x3ca0,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* Updates and draws records from level-map marker 0x302E; the concrete entity identity is not
   established by source. */
void update_actor_302e(void)
{
    register int si;
    struct actor_302e_record far *p;

    actor_302b_sprite_offset += 0xa0;
    if (actor_302b_sprite_offset == 0x1e0)
        actor_302b_sprite_offset = 0;

    for (si = 0; si < actor_302e_count; ++si) {
        p = &actor_302e_records[si];
        if (p->state == 0)
            continue;
        if (is_world_position_outside_view(p->world_x, p->world_y) != 0)
            continue;
        if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
            p->world_y += 128;

        if (p->state == 1) {
            if (remove_world_actor_at_position(p->world_x, p->world_y) != 0) {
                spawn_contact_flash_effect(p->world_x, p->world_y);
                if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0) {
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
                }
                p->state = 2;
            }
        }

        if (p->state == 2) {
            if (test_player_overlap_with_object(p->world_x, p->world_y) != 0) {
                p->state = 0;
                request_priority_sound_effect(16);
                switch (world_animation_phase) {
                case 0:
                    add_and_draw_player_score(100L);
                    queue_ambient_sprite_animation(0, p->world_x, p->world_y);
                    break;
                case 0x20:
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, p->world_x, p->world_y);
                    break;
                case 0x40:
                    add_and_draw_player_score(2000L);
                    queue_ambient_sprite_animation(0x500, p->world_x, p->world_y);
                    break;
                case 0x60:
                    add_and_draw_player_score(5000L);
                    queue_ambient_sprite_animation(0x640, p->world_x, p->world_y);
                    break;
                }
                continue;
            }
        }

        if (p->state == 1) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3e80,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
        } else {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_302b_sprite_offset + 0x3fc0,
                                    p->world_x - level_scroll_x,
                                    ((p->world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* Draws the level object animation using the active page and graphics resources. */
void pascal draw_level_object_animation(int frame, register int x, register int y)
{
    ++actor_302c_animation_phase;
    if (actor_302c_animation_phase == 3)
        actor_302c_animation_phase = 0;

    if (is_world_position_outside_view(x, y - 256) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x8480, x - level_scroll_x,
                                ((y - level_map_y_offset) >> 3) - 16);
    if (is_world_position_outside_view(x + 4, y - 256) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x85c0, x - level_scroll_x + 4,
                                ((y - level_map_y_offset) >> 3) - 16);
    if (is_world_position_outside_view(x, y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x8660, x - level_scroll_x,
                                (y - level_map_y_offset) >> 3);
    if (is_world_position_outside_view(x + 2, y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x8700, x - level_scroll_x + 2,
                                (y - level_map_y_offset) >> 3);
    if (is_world_position_outside_view(x + 4, y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x87a0, x - level_scroll_x + 4,
                                (y - level_map_y_offset) >> 3);
    if (is_world_position_outside_view(x, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x8840, x - level_scroll_x,
                                ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 2, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x88e0, x - level_scroll_x + 2,
                                ((y - level_map_y_offset) >> 3) + 16);
    if (is_world_position_outside_view(x + 4, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + 0x8980, x - level_scroll_x + 4,
                                ((y - level_map_y_offset) >> 3) + 16);

    switch (actor_302c_animation_phase) {
    case 0:
        if (is_world_position_outside_view(x + 2, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8700, x - level_scroll_x + 2,
                                    (y - level_map_y_offset) >> 3);
        if (is_world_position_outside_view(x + 4, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x87a0, x - level_scroll_x + 4,
                                    (y - level_map_y_offset) >> 3);
        break;
    case 1:
        if (is_world_position_outside_view(x + 2, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8c00, x - level_scroll_x + 2,
                                    (y - level_map_y_offset) >> 3);
        if (is_world_position_outside_view(x + 4, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8d40, x - level_scroll_x + 4,
                                    (y - level_map_y_offset) >> 3);
        break;
    case 2:
        if (is_world_position_outside_view(x + 2, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8ca0, x - level_scroll_x + 2,
                                    (y - level_map_y_offset) >> 3);
        if (is_world_position_outside_view(x + 4, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8de0, x - level_scroll_x + 4,
                                    (y - level_map_y_offset) >> 3);
        break;
    }
    switch (frame) {
    case 0:
    case 2:
        if (is_world_position_outside_view(x + 2, y - 256) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8520, x - level_scroll_x + 2,
                                    ((y - level_map_y_offset) >> 3) - 16);
        break;
    case 1:
        if (is_world_position_outside_view(x + 2, y - 256) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8a20, x - level_scroll_x + 2,
                                    ((y - level_map_y_offset) >> 3) - 16);
        break;
    case 3:
        if (is_world_position_outside_view(x + 2, y - 256) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0x8ac0, x - level_scroll_x + 2,
                                    ((y - level_map_y_offset) >> 3) - 16);
        break;
    }
}

/* Activates the level object created from map marker 0x302F when its trigger condition is met. */
void activate_actor_302f(void)
{
    if (actor_302f_active_state != 0) {
        if (actor_302f_interaction_state == 1) {
            actor_302f_interaction_state = 0;
            level_scroll_x = actor_3030_world_x - player_screen_x + 2;
            level_map_y_offset = actor_3030_world_y - 768;
            player_sprite_draw_state = 1;
            control_up_pressed = 0;
            actor_302f_animation_phase = 8;
            actor_302f_interaction_phase = 0;
        }

        if (actor_302f_interaction_state > 1)
            --actor_302f_interaction_state;
        if (actor_302f_interaction_phase > 0) {
            draw_level_object_animation(actor_302f_interaction_phase % 4, actor_302f_world_x, actor_302f_world_y);
            --actor_302f_interaction_phase;
        } else {
            draw_level_object_animation(actor_302f_interaction_state % 4, actor_302f_world_x, actor_302f_world_y);
        }

        if (transporter_hint_pending != 0) {
            if (test_player_overlap_with_object(actor_302f_world_x + 2, actor_302f_world_y)) {
                transporter_hint_pending = 0;
                show_secret_tip_transporter();
            }
        }
        if (test_player_overlap_with_object(actor_302f_world_x + 2, actor_302f_world_y)) {
            if (control_up_pressed != 0 && actor_302f_interaction_state == 0 && control_left_pressed == 0 &&
                control_right_pressed == 0 && control_jump_pressed == 0) {
                actor_302f_interaction_state = 8;
                request_priority_sound_effect(7);
            }
        }
    }
}

/* Activates the level object created from map marker 0x3030 when its trigger condition is met. */
void activate_actor_3030(void)
{
    if (actor_3030_active_state == 0)
        return;

    if (actor_3030_interaction_state == 1) {
        actor_3030_interaction_state = 0;
        level_scroll_x = actor_302f_world_x - player_screen_x + 2;
        /* The 16-bit wrap applies the -768-pixel camera offset. */
        level_map_y_offset = actor_302f_world_y + 0xfd00;
        player_sprite_draw_state = 1;
        control_up_pressed = 0;
        actor_302f_interaction_phase = 8;
        actor_302f_animation_phase = 0;
    }

    if (actor_3030_interaction_state > 1)
        --actor_3030_interaction_state;

    if (actor_302f_animation_phase > 0) {
        draw_level_object_animation(actor_302f_animation_phase % 4, actor_3030_world_x, actor_3030_world_y);
        --actor_302f_animation_phase;
    } else {
        draw_level_object_animation(actor_3030_interaction_state % 4, actor_3030_world_x, actor_3030_world_y);
    }

    if (transporter_hint_pending != 0 && test_player_overlap_with_object(actor_3030_world_x + 2, actor_3030_world_y)) {
        transporter_hint_pending = 0;
        show_secret_tip_transporter();
    }

    if (!test_player_overlap_with_object(actor_3030_world_x + 2, actor_3030_world_y))
        return;

    if (control_up_pressed != 0 && actor_3030_interaction_state == 0 && control_left_pressed == 0 &&
        control_right_pressed == 0 && control_jump_pressed == 0) {
        actor_3030_interaction_state = 8;
        request_priority_sound_effect(7);
    }
}

/* Updates and draws records from level-map marker 0x3031; the concrete entity identity is not
   established by source. */
void update_actor_3031(void)
{
    register int i;
    struct actor_3031_record far *actor_record;

    for (i = 0; i < actor_3031_count; ++i) {
        actor_record = &actor_3031_records[i];
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) == 0) {
            actor_record->world_y -= level_vertical_motion_table[actor_record->state + 6];
            ++actor_record->state;
            if (actor_record->state == 8)
                actor_record->state = -6;
            if (actor_record->state == -6)
                request_priority_sound_effect(34);
            if (test_player_overlap_with_object(actor_record->world_x, actor_record->world_y))
                active_sprite_draw_flag = 1;
            remove_world_actor_at_position(actor_record->world_x, actor_record->world_y);
            if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) == 0)
                blit_planar_sprite_rows(sprite_graphics_buffer + 0x8b60,
                                        actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* Advances and draws falling hazards, applying player contact and spawning their impact effect. */
void update_falling_hazards(void)
{
    register int i;
    struct falling_hazard_record far *p;

    for (i = 0; i < level_hazard_count; ++i) {
        p = &falling_hazard_records[i];
        if (p->active != 0) {
            if (is_world_position_outside_view(p->world_x, p->world_y) == 0) {
                if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
                    p->world_y += 0x40;
                if (test_player_overlap_with_object(p->world_x, p->world_y) != 0) {
                    p->active = 0;
                    active_sprite_draw_flag = 1;
                    spawn_moving_actor(2, p->world_x, p->world_y);
                    request_priority_sound_effect(33);
                }
                blit_planar_sprite_rows(sprite_graphics_buffer + 0x8b60,
                                        p->world_x - level_scroll_x,
                                        ((p->world_y - level_map_y_offset) >> 3) + 16);
            }
        }
    }
}

/* Updates and draws records from level-map marker 0x3034; the concrete entity identity is not
   established by source. */
void update_actor_3034(void)
{
    register int i;

    if (actor_3034_active_state == -1)
        return;
    if (is_world_position_outside_view(actor_3034_world_x, actor_3034_world_y) != 0)
        return;

    if (actor_3034_active_state == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x46a0,
                                actor_3034_world_x - level_scroll_x,
                                ((actor_3034_world_y - level_map_y_offset) >> 3) + 16);
        return;
    }

    actor_302d_sprite_offset += 0xa0;
    if (actor_302d_sprite_offset == 0x500)
        actor_302d_sprite_offset = 0;

    blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_302d_sprite_offset + 0x41a0,
                            actor_3034_world_x - level_scroll_x,
                            ((actor_3034_world_y - level_map_y_offset) >> 3) + 16);

    if (test_player_overlap_with_object(actor_3034_world_x, actor_3034_world_y) != 0 && hint_revealed_object_1 != 0) {
        hint_revealed_object_1 = 0;
        show_secret_tip_access_card();
    }

    if (test_player_overlap_with_object(actor_3034_world_x, actor_3034_world_y) != 0 && actor_3033_active_state != 0 && control_up_pressed != 0) {
        for (i = 0; i < actor_3021_count; ++i)
            (&actor_3021_records[i].world_x)[2] = 0;      /* Direct next-record indexing changes output; this clears the following actor's world_x. */

        actor_3034_active_state = 0;
        draw_planar_sprite_frame();
        request_priority_sound_effect(31);
        actor_3033_enabled = 0;
        actor_3033_active_state = 0;
    }

    if (test_player_overlap_with_object(actor_3034_world_x, actor_3034_world_y) != 0 &&
        actor_3033_active_state == 0 && control_up_pressed != 0 &&
        actor_3034_active_state != 0 && hint_revealed_object_3 != 0)
        show_secret_tip_insert_card();
}

/* Updates and draws records from level-map marker 0x3035; the concrete entity identity is not
   established by source. */
void update_actor_3035(void)
{
    if (actor_3035_active_state == 0)
        return;

    if (is_world_position_outside_view(actor_3035_world_x - 2, actor_3035_world_y) == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4880,
                                actor_3035_world_x - level_scroll_x - 2,
                                ((actor_3035_world_y - level_map_y_offset) >> 3) + 16);
    }

    if (is_world_position_outside_view(actor_3035_world_x + 2, actor_3035_world_y) == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4920,
                                actor_3035_world_x - level_scroll_x + 2,
                                ((actor_3035_world_y - level_map_y_offset) >> 3) + 16);
    }

    if (is_world_position_outside_view(actor_3035_world_x, actor_3035_world_y) != 0) {
        actor_3035_animation_state = 0;
        return;
    }

    if (test_player_overlap_with_object(actor_3035_world_x, actor_3035_world_y) != 0 && hint_revealed_object_6 != 0) {
        hint_revealed_object_6 = 0;
        show_secret_tip_robohand();
    }

    if (test_player_overlap_with_object(actor_3035_world_x, actor_3035_world_y) != 0) {
        if (control_up_pressed != 0 && actor_3035_state == 0) {
            if (actor_3020_active_state != 0) {
                actor_3035_state = 1;
                secret_block_state = 1;
                request_priority_sound_effect(5);
            } else {
                actor_3035_animation_state = 1;
            }
        }
    }

    if (actor_3035_state == 0 && world_animation_phase == 0) {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4740,
                                actor_3035_world_x - level_scroll_x,
                                ((actor_3035_world_y - level_map_y_offset) >> 3) + 16);
    } else {
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x47e0,
                                actor_3035_world_x - level_scroll_x,
                                ((actor_3035_world_y - level_map_y_offset) >> 3) + 16);
    }

    if (actor_3035_animation_state != 0) {
        if (world_animation_phase == 0)
            spawn_projectile(1, actor_3035_world_x + 2, actor_3035_world_y - 36);
        if (world_animation_phase == 0x40)
            spawn_projectile(2, actor_3035_world_x - 2, actor_3035_world_y - 36);
    }
}

/* Updates the secret block state from its current state and inputs. */
void update_secret_block_state(void)
{
    if (secret_block_animation_state == 0)
        return;
    if (secret_block_state == 0)
        return;
    spawn_moving_actor(3, secret_block_world_x + 2, secret_block_world_y);
    /* Keep word-pointer arithmetic here for the matching access sequence. */
    if (*(level_tile_map + secret_block_world_y + (secret_block_world_x >> 1)) == 0x2fe0U) {
        secret_block_animation_state = 0;
        secret_block_state = 0;
    } else {
        *(level_tile_map + secret_block_world_y + (secret_block_world_x >> 1)) = 0x2fe0U;
    }
    secret_block_world_x += 2;
}

/* Updates and draws records from level-map marker 0x3037; the concrete entity identity is not
   established by source. */
void update_actor_3037(void)
{
    register int i;
    struct actor_3037_record far *actor_record;

    for (i = 0; i < actor_3037_object_count; i++) {
        actor_record = &actor_3037_records[i];
        if (actor_record->state == 0)
            continue;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;
        if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0)
            actor_record->world_y += 128;
        if (actor_record->animation_flag == 0 && remove_world_actor_at_position(actor_record->world_x, actor_record->world_y) != 0) {
            spawn_contact_flash_effect(actor_record->world_x, actor_record->world_y);
            if (is_level_position_blocked(actor_record->world_x, actor_record->world_y + 128) == 0) {
                add_and_draw_player_score(500L);
                queue_ambient_sprite_animation(0x280, actor_record->world_x, actor_record->world_y);
            }
            actor_record->animation_flag = 1;
        }
        if (actor_record->animation_flag != 0) {
            if (test_player_overlap_with_object(actor_record->world_x, actor_record->world_y) != 0) {
                if (actor_record->state != 'E') {
                    secret_code_character_0[actor_3037_bonus_state++] = actor_record->state;
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, actor_record->world_x, actor_record->world_y);
                    request_priority_sound_effect(16);
                } else if (actor_3037_bonus_state == 3 && secret_code_character_0[0] == 'D' &&
                           secret_code_character_1 == 'U' && secret_code_character_2 == 'K') {
                    add_and_draw_player_score(10000L);
                    queue_ambient_sprite_animation(0x780, actor_record->world_x, actor_record->world_y);
                    request_priority_sound_effect(37);
                    actor_3037_animation_state = 1;
                } else {
                    add_and_draw_player_score(500L);
                    queue_ambient_sprite_animation(0x280, actor_record->world_x, actor_record->world_y);
                    request_priority_sound_effect(16);
                }
                actor_record->state = 0;
            }
        }
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y) != 0)
            continue;
        if (actor_record->animation_flag == 0) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer, actor_record->world_x - level_scroll_x,
                                    ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        } else {
            if (actor_record->state == 'D')
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x49c0, actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (actor_record->state == 'U')
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4a60, actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (actor_record->state == 'K')
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4b00, actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
            if (actor_record->state == 'E')
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4ba0, actor_record->world_x - level_scroll_x,
                                        ((actor_record->world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* Draws the two sprite cells used by the climbing actor. */
void pascal draw_climbing_actor_sprite(int frame, register int x, int y)
{
    register int offset;

    if (frame <= 2)
        offset = frame * 0x140 + 0x4740;
    else
        offset = (frame - 3) * 0x140 + 0x8e80;

    if (is_world_position_outside_view(x, y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset,
                                x - level_scroll_x,
                                (y - level_map_y_offset) >> 3);

    if (is_world_position_outside_view(x, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + offset + 0xa0,
                                x - level_scroll_x,
                                ((y - level_map_y_offset) >> 3) + 16);
}

/* Updates and draws records from level-map marker 0x303B; the concrete entity identity is not
   established by source. */
void update_actor_303b(void)
{
    register int i;
    struct actor_303b_record far *p;

    actor_303b_update_state = 1;
    for (i = 0; i < actor_303b_count; ++i) {
        p = &actor_303b_records[i];
        if (p->state == 0)
            continue;

        actor_303b_update_state = 0;
        if (p->state > 2) {
            switch (p->object_kind) {
            case 0:
                draw_climbing_actor_sprite(0, p->world_x, p->world_y);
                break;
            case 1:
                draw_climbing_actor_sprite(6, p->world_x, p->world_y);
                break;
            case 2:
                draw_climbing_actor_sprite(3, p->world_x, p->world_y);
                break;
            case 3:
                draw_climbing_actor_sprite(7, p->world_x, p->world_y);
                break;
            }
            ++p->state;
            ++p->object_kind;
            if (p->object_kind == 4)
                p->object_kind = 0;
            if (p->state == 20) {
                p->state = 0;
                spawn_pickup_object(p->world_x, p->world_y);
                spawn_pickup_object(p->world_x, p->world_y - 128);
                spawn_pickup_object(p->world_x - 1, p->world_y - 64);
                spawn_pickup_object(p->world_x + 1, p->world_y - 64);
                spawn_pickup_object(p->world_x + 1, p->world_y - 192);
                spawn_pickup_object(p->world_x - 1, p->world_y);
                add_and_draw_player_score(5000L);
                queue_ambient_sprite_animation(0x640, p->world_x, p->world_y);
                continue;
            }
        } else {
            if (!is_level_position_blocked(p->world_x, p->world_y + 128)) {
                p->world_y += 0x40;
            } else {
                if (test_level_tile_special_state(p->world_x - 1, p->world_y) && p->state == 1) {
                    p->state = 2;
                    p->object_kind = 0;
                } else if (test_level_tile_special_state(p->world_x + 2, p->world_y) && p->state == 2) {
                    p->state = 1;
                    p->object_kind = 0;
                }
            }

            if (p->object_kind == 0) {
                if (p->state == 1)
                    draw_climbing_actor_sprite(6, p->world_x, p->world_y);
                if (p->state == 2)
                    draw_climbing_actor_sprite(7, p->world_x, p->world_y);
                if (world_animation_phase != 0x40 && world_animation_phase != 0)
                    continue;
                p->object_kind = 1;
                continue;
            }

            if (p->state == 1) {
                if (world_animation_phase == 0 || world_animation_phase == 0x40)
                    --p->world_x;
                if (p->object_kind < 3)
                    draw_climbing_actor_sprite(p->object_kind, p->world_x, p->world_y);
                else
                    draw_climbing_actor_sprite(5 - p->object_kind, p->world_x, p->world_y);
                if (world_animation_phase == 0 || world_animation_phase == 0x40) {
                    if (is_level_position_blocked(p->world_x, p->world_y + 128))
                        ++p->object_kind;
                    if (p->object_kind == 6)
                        p->object_kind = 1;
                }
            }

            if (p->state == 2) {
                if (world_animation_phase == 0 || world_animation_phase == 0x40)
                    ++p->world_x;
                if (p->object_kind < 3)
                    draw_climbing_actor_sprite(p->object_kind + 2, p->world_x, p->world_y);
                else
                    draw_climbing_actor_sprite(8 - p->object_kind, p->world_x, p->world_y);
                if (world_animation_phase == 0 || world_animation_phase == 0x40) {
                    if (is_level_position_blocked(p->world_x, p->world_y + 128))
                        ++p->object_kind;
                    if (p->object_kind == 6)
                        p->object_kind = 1;
                }
            }

            if (remove_world_actor_at_position(p->world_x, p->world_y)) {
                p->state = 0;
                spawn_pickup_object(p->world_x, p->world_y);
                spawn_pickup_object(p->world_x, p->world_y - 128);
                spawn_pickup_object(p->world_x - 1, p->world_y - 64);
                spawn_pickup_object(p->world_x + 1, p->world_y - 64);
                spawn_pickup_object(p->world_x + 1, p->world_y - 192);
                spawn_pickup_object(p->world_x - 1, p->world_y);
                request_priority_sound_effect(18);
                add_and_draw_player_score(200L);
                continue;
            }
            if (test_player_overlap_with_object(p->world_x, p->world_y)) {
                active_sprite_draw_flag = 1;
                request_priority_sound_effect(35);
                p->state = 3;
                p->object_kind = 0;
            }
        }
    }
}

/* Draws two vertically stacked effect cells from the actor sprite resource. */
void pascal draw_tall_effect_sprite(int frame, int x, int y)
{
    register int row;
    register int col;

    col = x;
    row = frame * 0x140;
    row += 0x9600;
    if (is_world_position_outside_view(x, y - 128) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + row, col - level_scroll_x, (y - level_map_y_offset) >> 3);
    if (is_world_position_outside_view(col, y) == 0)
        blit_planar_sprite_rows(sprite_graphics_buffer + row + 0xa0, col - level_scroll_x, ((y - level_map_y_offset) >> 3) + 16);
}

/* Updates and draws records from level-map marker 0x303C; the concrete entity identity is not
   established by source. */
void update_actor_303c(void)
{
    register int i;
    struct actor_303c_record far *p;

    if (world_animation_phase == 0 || world_animation_phase == 0x40)
        ++actor_303c_animation_phase;
    if (actor_303c_animation_phase == 3)
        actor_303c_animation_phase = 0;

    for (i = 0; i < actor_303c_count; ++i) {
        p = &actor_303c_records[i];
        if (p->state != 0) {
            if (is_level_position_blocked(p->world_x, p->world_y + 128) == 0)
                p->world_y += 0x40;
            if (test_level_tile_special_state(p->world_x - 1, p->world_y) != 0 ||
                is_level_position_blocked(p->world_x - 2, p->world_y + 128) == 0)
                p->state = 2;
            if (test_level_tile_special_state(p->world_x + 2, p->world_y) != 0 ||
                is_level_position_blocked(p->world_x + 2, p->world_y + 128) == 0)
                p->state = 1;

            if (p->state == 1) {
                if (world_animation_phase == 0 || world_animation_phase == 0x40)
                    --p->world_x;
                draw_tall_effect_sprite(actor_303c_animation_phase, p->world_x, p->world_y);
            }
            if (p->state == 2) {
                if (world_animation_phase == 0 || world_animation_phase == 0x40)
                    ++p->world_x;
                draw_tall_effect_sprite(actor_303c_animation_phase + 3, p->world_x, p->world_y);
            }
            remove_world_actor_at_position(p->world_x, p->world_y);
            if (test_player_overlap_with_object(p->world_x, p->world_y) != 0)
                active_sprite_draw_flag = 1;
        }
    }
}

/* Waits for the for level start condition or input event. */
void wait_for_level_start(void)
{
    register int si;

    si = current_level_index;
    si <<= 2;
    draw_framed_dialog_box(2, 1, 3);
    draw_text_string(episode_level_start_text_table[si], 3, 3);
    draw_text_string(episode_level_start_text_table[si + 1], 3, 4);
    draw_text_string(episode_level_start_text_table[si + 2], 3, 5);
    draw_text_string(episode_level_start_text_table[si + 3], 3, 6);
    draw_text_string("      Press ENTER:      ", 3, 8);
    enable();
    do {
        wait_input_animated_sprite(0x1a, 8);
    } while (last_keyboard_scan_code != 0x1c);
    control_right_pressed = 0;
    control_down_pressed = 0;
    disable();
    /* Update the sound hardware with interrupts disabled. */
    select_draw_page(!draw_page_index);
    show_video_page(draw_page_index);
    timer_tick_counter = 0;
}

/* Updates and draws records from level-map marker 0x3040; the concrete entity identity is not
   established by source. */
void update_actor_3040(void)
{
    if (actor_3040_active_state != 0) {
        if (is_world_position_outside_view(actor_3040_world_x, actor_3040_world_y) == 0) {
            if (hint_revealed_object_9 == 1 && test_player_overlap_with_object(actor_3040_world_x, actor_3040_world_y) != 0) {
                hint_revealed_object_9 = 0;
                show_secret_tip_read_notes();
            }
            if (test_player_overlap_with_object(actor_3040_world_x, actor_3040_world_y) != 0 && control_up_pressed != 0) {
                request_priority_sound_effect(28);
                wait_for_level_start();
            }
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4ce0,
                                    actor_3040_world_x - level_scroll_x,
                                    ((actor_3040_world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* Draws a two-by-two actor graphic selected by its animation variant and marks player contact. */
void pascal draw_actor_sprite_by_variant(int variant, register int x, register int y)
{
    if (variant < 2) {
        if (is_world_position_outside_view(x, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xa8c0,
                                    x - level_scroll_x,
                                    (y - level_map_y_offset) >> 3);
        if (is_world_position_outside_view(x + 2, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xa960,
                                    x + 2 - level_scroll_x,
                                    (y - level_map_y_offset) >> 3);
    } else {
        if (is_world_position_outside_view(x, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xac80,
                                    x - level_scroll_x,
                                    (y - level_map_y_offset) >> 3);
        if (is_world_position_outside_view(x + 2, y - 128) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xad20,
                                    x + 2 - level_scroll_x,
                                    (y - level_map_y_offset) >> 3);
    }

    switch (variant) {
    case 0:
        if (is_world_position_outside_view(x, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xaa00,
                                    x - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(x + 2, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xaaa0,
                                    x + 2 - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        break;
    case 1:
        if (is_world_position_outside_view(x, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xab40,
                                    x - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(x + 2, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xabe0,
                                    x + 2 - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        break;
    case 2:
        if (is_world_position_outside_view(x, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xadc0,
                                    x - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(x + 2, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xae60,
                                    x + 2 - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        break;
    case 3:
        if (is_world_position_outside_view(x, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xaf00,
                                    x - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        if (is_world_position_outside_view(x + 2, y) == 0)
            blit_planar_sprite_rows(sprite_graphics_buffer + 0xafa0,
                                    x + 2 - level_scroll_x,
                                    ((y - level_map_y_offset) >> 3) + 16);
        break;
    }

    if (test_player_overlap_with_object(x, y) != 0)
        active_sprite_draw_flag = 1;
}

/* Updates and draws records from level-map marker 0x3042; the concrete entity identity is not
   established by source. */
void update_actor_3042(void)
{
    if (actor_3042_interaction_state != 0) {
        ++actor_3042_interaction_state;
        if (actor_3042_interaction_state == 10)
            actor_3042_hint_state = 1;
        return;
    }

    actor_3042_animation_frame_0 = !actor_3042_animation_frame_0;
    if (actor_3042_active_state == 0)
        return;

    if (actor_3042_open_state != 2) {
        if (actor_3042_open_state != 0) {
            if (actor_3042_animation_frame_3 == 0) {
                ++actor_3042_animation_frame_1;
                if (actor_3042_animation_frame_1 == (actor_3042_animation_frame_5 >> 1)) {
                    if (player_screen_x + level_scroll_x - 2 < actor_3042_world_x)
                        spawn_projectile(1, actor_3042_world_x, actor_3042_world_y - 32);
                    else
                        spawn_projectile(2, actor_3042_world_x + 3, actor_3042_world_y - 32);
                }
                if (actor_3042_animation_frame_1 > actor_3042_animation_frame_5) {
                    actor_3042_animation_frame_1 = 0;
                    actor_3042_animation_frame_2 = 0;
                    actor_3042_animation_frame_3 = 1;
                    if (player_screen_x + level_scroll_x - 2 < actor_3042_world_x)
                        actor_3042_animation_frame_4 = 1;
                    else
                        actor_3042_animation_frame_4 = 0;
                }
            } else {
                actor_3042_world_y += actor_3042_motion_delta_table[actor_3042_animation_frame_2];
                if (actor_3042_animation_frame_4 != 0) {
                    if (!test_level_tile_special_state(actor_3042_world_x - 1, actor_3042_world_y - 64))
                        --actor_3042_world_x;
                } else {
                    if (!test_level_tile_special_state(actor_3042_world_x + 3, actor_3042_world_y - 64))
                        ++actor_3042_world_x;
                }
                ++actor_3042_animation_frame_2;
                if (actor_3042_animation_frame_2 == 12) {
                    actor_3042_animation_frame_3 = 0;
                    actor_3042_animation_frame_5 = (world_animation_phase >> 1) + 1;
                    actor_3042_animation_frame_1 = 0;
                }
            }
            if (player_screen_x + level_scroll_x - 2 < actor_3042_world_x)
                draw_actor_sprite_by_variant(actor_3042_animation_frame_0, actor_3042_world_x, actor_3042_world_y);
            else
                draw_actor_sprite_by_variant(actor_3042_animation_frame_0 + 2, actor_3042_world_x, actor_3042_world_y);
            if (remove_world_actor_at_position(actor_3042_world_x + 1, actor_3042_world_y - 64)) {
                spawn_moving_actor(3, actor_3042_world_x + 2, actor_3042_world_y - 92);
                --actor_3042_animation_counter;
            }
            if (world_animation_phase != 0 && actor_3042_animation_counter < 10) {
                if (actor_3042_animation_counter < 10)
                    spawn_pickup_object(actor_3042_world_x + 2, actor_3042_world_y - 32);
                if (actor_3042_animation_counter < 6)
                    spawn_pickup_object(actor_3042_world_x + 1, actor_3042_world_y - 64);
                if (actor_3042_animation_counter < 2)
                    spawn_pickup_object(actor_3042_world_x + 3, actor_3042_world_y - 64);
            }
            if (actor_3042_animation_counter == 1 && ending_sequence_enabled != 0)
                actor_3042_open_state = 0;
            else if (actor_3042_animation_counter == 0)
                actor_3042_open_state = 2;
        } else {
            if (!is_world_position_outside_view(actor_3042_world_x, actor_3042_world_y) && player_animation_lock_state == 0) {
                player_animation_lock_state = 1;
                request_priority_sound_effect(40);
                disable();
                control_fire_pressed = control_jump_pressed = control_left_pressed = control_right_pressed = control_up_pressed = control_down_pressed = 0;
                enable();
            }
            if (player_animation_lock_state > 30)
                actor_3042_hint_state = 1;
            if (player_animation_lock_state != 0)
                ++player_animation_lock_state;
            if (player_animation_lock_state != 0 && actor_3042_world_y > 0x100 && level_map_y_offset > 0x100) {
                actor_3042_world_y -= 0x80;
                level_map_y_offset -= 0x80;
                gameplay_animation_flag = 1;
            }
            if (player_screen_x + level_scroll_x - 2 < actor_3042_world_x)
                draw_actor_sprite_by_variant(actor_3042_animation_frame_0, actor_3042_world_x, actor_3042_world_y);
            else
                draw_actor_sprite_by_variant(actor_3042_animation_frame_0 + 2, actor_3042_world_x, actor_3042_world_y);
            return;
        }
    } else {
        actor_3042_world_y += 32;
        if (world_animation_phase == 0)
            spawn_contact_flash_effect(actor_3042_world_x + 2, actor_3042_world_y);
        if (world_animation_phase == 32)
            spawn_moving_actor(1, actor_3042_world_x + 2, actor_3042_world_y);
        if (world_animation_phase == 64)
            spawn_contact_flash_effect(actor_3042_world_x, actor_3042_world_y);
        if (world_animation_phase == 96)
            spawn_moving_actor(3, actor_3042_world_x + 2, actor_3042_world_y);
        if (player_screen_x + level_scroll_x - 2 < actor_3042_world_x)
            draw_actor_sprite_by_variant(0, actor_3042_world_x, actor_3042_world_y);
        else
            draw_actor_sprite_by_variant(2, actor_3042_world_x, actor_3042_world_y);
        if (is_level_position_blocked(actor_3042_world_x + 1, actor_3042_world_y)) {
            request_priority_sound_effect(41);
            actor_3042_interaction_state = 1;
        }
        return;
    }
}

/* Draws a large two-by-two actor graphic and clears its active flag when the right edge is
   outside the view. */
void pascal draw_large_actor_sprite(int sprite_frame, int actor_world_x, int actor_world_y)
{
    register int sprite_data_offset;

    sprite_data_offset = sprite_frame * 0x140 + 0xa140;
    if (is_world_position_outside_view(actor_world_x, actor_world_y - 0x80) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_data_offset,
                                actor_world_x - level_scroll_x,
                                (actor_world_y - level_map_y_offset) >> 3);
    }
    if (is_world_position_outside_view(actor_world_x + 2, actor_world_y - 0x80) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + sprite_data_offset + 0xa0,
                                actor_world_x + 2 - level_scroll_x,
                                (actor_world_y - level_map_y_offset) >> 3);
    }
    if (is_world_position_outside_view(actor_world_x, actor_world_y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + 0xa000,
                                actor_world_x - level_scroll_x,
                                ((actor_world_y - level_map_y_offset) >> 3) + 0x10);
    }
    if (is_world_position_outside_view(actor_world_x + 2, actor_world_y) == 0) {
        blit_planar_sprite_rows(sprite_graphics_buffer + 0xa0a0,
                                actor_world_x + 2 - level_scroll_x,
                                ((actor_world_y - level_map_y_offset) >> 3) + 0x10);
    } else {
        actor_3041_interaction_state = 0;
    }
}

/* Updates the level lock or exit from its current state and inputs. */
void update_level_lock_or_exit(void)
{
    register int unused_register;

    if (actor_3041_active_state == 0 || current_level_index == 0)
        return;

    ++actor_3041_sprite_frame;
    if (actor_3041_sprite_frame == 3)
        actor_3041_sprite_frame = 0;
    ++actor_3041_animation_counter;

    if (actor_3041_event_pending != 0) {
        wait_for_level_start();
        actor_3041_event_pending = 0;
        if (control_confirmation_state == 0) {
            enable();
            while ((last_keyboard_scan_code & 0x80) == 0) {
            }
            disable();
        }
    }

    if (actor_3041_animation_counter == 125)
        actor_3041_animation_counter = 0;

    if (actor_3041_interaction_state == 0 && exit_lock_animation_state == 0) {
        if (test_player_overlap_with_object(actor_3041_world_x - 6, actor_3041_world_y) != 0) {
            request_priority_sound_effect(0x1d);
            actor_3041_interaction_state = 1;
            exit_lock_animation_state = 1;
            actor_3041_event_pending = 1;
        } else if (test_player_overlap_with_object(actor_3041_world_x + 8, actor_3041_world_y) != 0) {
            request_priority_sound_effect(0x1d);
            actor_3041_interaction_state = 1;
            exit_lock_animation_state = 1;
            actor_3041_event_pending = 1;
        }
    }

    if (control_up_pressed != 0 &&
        (test_player_overlap_with_object(actor_3041_world_x, actor_3041_world_y) != 0 ||
         test_player_overlap_with_object(actor_3041_world_x + 2, actor_3041_world_y) != 0)) {
        actor_3041_interaction_state = 1;
        request_priority_sound_effect(0x1d);
        actor_3041_event_pending = 1;
        exit_lock_animation_state = 1;
    }

    if (actor_3041_interaction_state == 0) {
        draw_large_actor_sprite(actor_3041_sprite_frame, actor_3041_world_x, actor_3041_world_y);
    } else if (player_screen_x + level_scroll_x < actor_3041_world_x - 1) {
        draw_large_actor_sprite(3, actor_3041_world_x, actor_3041_world_y);
    } else if (player_screen_x + level_scroll_x > actor_3041_world_x + 3) {
        draw_large_actor_sprite(5, actor_3041_world_x, actor_3041_world_y);
    } else {
        draw_large_actor_sprite(4, actor_3041_world_x, actor_3041_world_y);
    }
}

/* Draws the four directional hint icons on the level screen using the current hint flags. */
void pascal draw_level_marker_tiles(void)
{
    register int page_index;
    register int draw_pass;

    page_index = draw_page_index;
    draw_pass = 0;
    do {
        ++draw_pass;
        select_draw_page(page_index);
        if (control_hint_up_flag != 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4d80, 0x1e, 0x90);
        else
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4c40, 0x1e, 0x90);
        if (control_hint_down_flag != 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4e20, 0x20, 0x90);
        else
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4c40, 0x20, 0x90);
        if (control_hint_left_flag != 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4ec0, 0x22, 0x90);
        else
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4c40, 0x22, 0x90);
        if (control_hint_right_flag != 0)
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4f60, 0x24, 0x90);
        else
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4c40, 0x24, 0x90);
        page_index = !page_index;
    } while (draw_pass == 1);
}

/* Updates and draws records from level-map marker 0x3044; the concrete entity identity is not
   established by source. */
void update_actor_3044(void)
{
    register int record_index;
    struct actor_3044_record far *actor_record;

    for (record_index = 0; record_index < actor_3044_entity_count; record_index++) {
        actor_record = &actor_3044_records[record_index];
        if (actor_record->state == 0)
            continue;
        if (is_world_position_outside_view(actor_record->world_x, actor_record->world_y))
            continue;
        if (test_player_overlap_with_object(actor_record->world_x, actor_record->world_y)) {
            switch (actor_record->state) {
            case 0x00a0:
                control_hint_up_flag = 1;
                break;
            case 0x0140:
                control_hint_down_flag = 1;
                break;
            case 0x01e0:
                control_hint_left_flag = 1;
                break;
            case 0x0280:
                control_hint_right_flag = 1;
                break;
            }
            request_priority_sound_effect(9);
            add_and_draw_player_score(1000L);
            queue_ambient_sprite_animation(0x03c0, actor_record->world_x, actor_record->world_y);
            draw_level_marker_tiles();
            actor_record->state = 0;
        } else {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + actor_record->state + 0x4ce0,
                                    actor_record->world_x - level_scroll_x,
                                    0x10 + ((actor_record->world_y - level_map_y_offset) >> 3));
        }
    }
}

/* Updates and draws records from level-map marker 0x3048; the concrete entity identity is not
   established by source. */
void update_actor_3048(void)
{
    register int i;
    register int j;
    struct level_tile_animation_record far *marker_record;

    if (world_animation_phase == 0)
        ++actor_3041_sprite_offset;
    if (actor_3041_sprite_offset == 320)
        actor_3041_sprite_offset = 0;

    for (j = 0; j < actor_3048_entity_count; ++j) {
        marker_record = &actor_3048_records[j];
        if (is_world_position_outside_view(marker_record->world_x, marker_record->world_y))
            continue;

        if (hint_revealed_object_7 != 0 && test_player_overlap_with_object(marker_record->world_x, marker_record->world_y)) {
            hint_revealed_object_7 = 0;
            show_secret_tip_card_key();
        }
        if (test_player_overlap_with_object(marker_record->world_x, marker_record->world_y) != 0 &&
            control_up_pressed != 0 && marker_record->sprite_resource_offset != 0) {
            if ((control_hint_up_flag != 0 && marker_record->sprite_resource_offset == 0x140) ||
                (control_hint_down_flag != 0 && marker_record->sprite_resource_offset == 0x1e0) ||
                (control_hint_left_flag != 0 && marker_record->sprite_resource_offset == 0x280) ||
                (control_hint_right_flag != 0 && marker_record->sprite_resource_offset == 0x320)) {
                for (i = 0; i < actor_3048_object_count; ++i) {
                    if (level_tile_animation_records[i].sprite_resource_offset != marker_record->sprite_resource_offset - 0xa0)
                        continue;
                    level_tile_animation_records[i].alternate_frame = 1;
                    *(level_tile_map + level_tile_animation_records[i].world_y + (level_tile_animation_records[i].world_x >> 1) - 1) =
                        *(level_tile_map + level_tile_animation_records[i].world_y + (level_tile_animation_records[i].world_x >> 1) - 2);
                }

                switch (marker_record->sprite_resource_offset - 0xa0) {
                case 0xa0:
                    control_hint_up_flag = 0;
                    break;
                case 0x140:
                    control_hint_down_flag = 0;
                    break;
                case 0x1e0:
                    control_hint_left_flag = 0;
                    break;
                case 0x280:
                    control_hint_right_flag = 0;
                    break;
                }
                draw_level_marker_tiles();
                marker_record->sprite_resource_offset = 0;
                request_priority_sound_effect(0x1f);
                add_and_draw_player_score(1000L);
                continue;
            }
            if (hint_revealed_object_8 != 0)
                show_secret_tip_lock_key();
        }
        if (marker_record->sprite_resource_offset == 0) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x5460 + marker_record->alternate_frame,
                                    marker_record->world_x - level_scroll_x,
                                    ((marker_record->world_y - level_map_y_offset) >> 3) + 0x10);
        } else if (actor_3041_sprite_offset % 2 != 0) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x5500,
                                    marker_record->world_x - level_scroll_x,
                                    ((marker_record->world_y - level_map_y_offset) >> 3) + 0x10);
        } else {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x5460 + marker_record->sprite_resource_offset,
                                    marker_record->world_x - level_scroll_x,
                                    ((marker_record->world_y - level_map_y_offset) >> 3) + 0x10);
        }
    }
}

/* Advances alternate tile-animation offsets and draws the visible level-tile animation records. */
void animate_level_tile_records(void)
{
    register int i;
    struct level_tile_animation_record far *animation_record;

    for (i = 0; i < actor_3048_object_count; ++i) {
        animation_record = &level_tile_animation_records[i];
        if (animation_record->sprite_resource_offset != 0 && is_world_position_outside_view(animation_record->world_x, animation_record->world_y) == 0) {
            if (animation_record->alternate_frame != 0) {
                if (world_animation_phase == 0 || world_animation_phase == 0x40)
                    animation_record->sprite_resource_offset += 0xa0;
                if (animation_record->sprite_resource_offset == 0x5a0) {
                    animation_record->sprite_resource_offset = 0;
                    continue;
                }
                blit_planar_sprite_rows(sprite_pixel_data_pointer + animation_record->sprite_resource_offset + 0x4f60,
                                        animation_record->world_x - level_scroll_x,
                                        ((animation_record->world_y - level_map_y_offset) >> 3) + 0x10);
            } else {
                blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x5000,
                                        animation_record->world_x - level_scroll_x,
                                        ((animation_record->world_y - level_map_y_offset) >> 3) + 0x10);
            }
        }
    }
}

/* Draws visible marker 0x3058 objects and marks player contact when one overlaps Duke. */
void draw_marker_3058_objects(void)
{
    register int i;
    struct actor_3058_record far *marker_record;

    for (i = 0; i < level_object_pool_531e_count; ++i) {
        marker_record = &actor_3058_records[i];
        if (is_world_position_outside_view(marker_record->world_x, marker_record->world_y) == 0) {
            if (test_player_overlap_with_object(marker_record->world_x, marker_record->world_y) != 0)
                active_sprite_draw_flag = 1;
            blit_planar_sprite_rows(sprite_pixel_data_pointer + marker_record->sprite_resource_offset,
                                    marker_record->world_x - level_scroll_x,
                                    ((marker_record->world_y - level_map_y_offset) >> 3) + 16);
        }
    }
}

/* ============================================================================================
   Level setup
   The per-level callback table and the walk over the level map that creates the actors.
   ============================================================================================ */

/* Registers a level-object update callback for execution by the gameplay loop. */
void pascal register_level_update_callback(void (far *update_callback)(void))
{
    register int i;

    for (i = 0; i < keyboard_hotkey_count; ++i) {
        if (level_update_callback_table[i] == update_callback)
            return;
    }
    level_update_callback_table[i] = update_callback;
    ++keyboard_hotkey_count;
}

/* Scans level-map marker values, initializes the corresponding object records, and registers
   their update callbacks. */
void pascal create_objects_from_level_map(unsigned int row_count)
{
    register unsigned int col;
    register unsigned int row;
    int k;
    unsigned int far *tile_cell;

    for (row = 0; row < row_count; ++row) {
        for (col = 0; col < 128; ++col) {
            tile_cell = level_tile_map + row * 128 + col;
            if (*tile_cell >= 0x3000) {
                switch (*tile_cell) {
                case 0x3000:
                    actor_3000_records[actor_3000_count].state = 1;
                    actor_3000_records[actor_3000_count].world_x = col * 2 + 2;
                    actor_3000_records[actor_3000_count].world_y = row * 128;
                    register_level_update_callback(update_actor_3000);
                    *tile_cell = tile_cell[-1];
                    ++actor_3000_count;
                    break;
                case 0x3001:
                    actor_3001_records[actor_3001_count].active = 1;
                    actor_3001_records[actor_3001_count].world_x = col * 2 + 2;
                    actor_3001_tile_below_records[actor_3001_count] = tile_cell[-128];
                    actor_3001_records[actor_3001_count].world_y = row * 128;
                    *tile_cell = 0x1ae0;
                    ++actor_3001_count;
                    break;
                case 0x3002:
                    actor_3002_records[actor_3002_count].reserved = 0;
                    actor_3002_records[actor_3002_count].map_column = col + 2;
                    actor_3002_records[actor_3002_count].map_row = row * 128;
                    k = 0;
                    while (tile_cell[k] != 0x3003)
                        ++k;
                    actor_3002_records[actor_3002_count].object_height = k * 2;
                    actor_3002_records[actor_3002_count].object_state = 0;
                    register_level_update_callback(update_actor_3002);
                    *tile_cell = 0x1820;
                    ++actor_3002_count;
                    break;
                case 0x3003:
                    break;
                case 0x3004:
                    actor_3002_records[actor_3002_count].reserved = 0;
                    actor_3002_records[actor_3002_count].map_column = col + 2;
                    actor_3002_records[actor_3002_count].map_row = row * 128;
                    k = 0;
                    while (tile_cell[k] != 0x3005)
                        ++k;
                    actor_3002_records[actor_3002_count].object_height = k * 2;
                    actor_3002_records[actor_3002_count].object_state = 1;
                    register_level_update_callback(update_actor_3002);
                    ++actor_3002_count;
                    break;
                case 0x3005:
                    break;
                case 0x3006:
                    actor_3006_world_x = col * 2 + 2;
                    actor_3006_world_y = row * 128;
                    actor_3006_state = 0;
                    register_level_update_callback(update_actor_3006);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3007:
                    actor_3007_records[actor_3007_count].state = 1;
                    actor_3007_records[actor_3007_count].world_x = col * 2 + 2;
                    actor_3007_records[actor_3007_count].world_y = row * 128;
                    register_level_update_callback(update_actor_3007);
                    level_loading_state = 1;
                    *tile_cell = tile_cell[-128];
                    ++actor_3007_count;
                    break;
                case 0x3008:
                    actor_3008_world_x = col * 2 + 2;
                    actor_3008_world_y = row * 128;
                    actor_3008_state = 0;
                    register_level_update_callback(update_actor_3008);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3009:
                    actor_3009_records[actor_3009_count].state = 1;
                    actor_3009_records[actor_3009_count].world_x = col * 2 + 2;
                    actor_3009_records[actor_3009_count].world_y = row * 128;
                    register_level_update_callback(update_actor_3009);
                    *tile_cell = tile_cell[1];
                    ++actor_3009_count;
                    break;
                case 0x300a:
                    actor_300a_records[actor_300a_count].state = 1;
                    actor_300a_records[actor_300a_count].world_x = col * 2 + 2;
                    actor_300a_records[actor_300a_count].world_y = row * 128;
                    register_level_update_callback(update_actor_300a);
                    *tile_cell = tile_cell[-1];
                    ++actor_300a_count;
                    break;
                case 0x300b:
                    actor_300b_records[actor_300b_count].motion_state = 1;
                    actor_300b_records[actor_300b_count].world_x = col * 2 + 2;
                    actor_300b_records[actor_300b_count].world_y = row * 128;
                    actor_300b_records[actor_300b_count].trajectory_step = 0;
                    register_level_update_callback(update_actor_300b);
                    *tile_cell = tile_cell[-1];
                    ++actor_300b_count;
                    break;
                case 0x300c:
                    actor_300c_records[actor_300c_count].state = 1;
                    actor_300c_records[actor_300c_count].world_x = col * 2 + 2;
                    actor_300c_records[actor_300c_count].world_y = row * 128;
                    actor_300c_records[actor_300c_count].marker_state = 0;
                    actor_300c_object_marker_table[actor_300c_count] = 0;
                    register_level_update_callback(update_actor_300c);
                    *tile_cell = tile_cell[-1];
                    ++actor_300c_count;
                    break;
                case 0x300d:
                    actor_300d_records[actor_300d_count].state = 1;
                    actor_300d_records[actor_300d_count].world_x = col * 2 + 2;
                    actor_300d_records[actor_300d_count].world_y = row * 128;
                    actor_300d_auxiliary_states[actor_300d_count] = 0;
                    register_level_update_callback(update_actor_300d);
                    *tile_cell = tile_cell[-1];
                    ++actor_300d_count;
                    break;
                case 0x300e:
                    actor_300e_records[actor_300e_count].state = 1;
                    actor_300e_records[actor_300e_count].world_x = col * 2 + 2;
                    actor_300e_records[actor_300e_count].world_y = row * 128;
                    actor_300e_object_state_table[actor_300e_count] = 0;
                    register_level_update_callback(update_actor_300e);
                    *tile_cell = tile_cell[-1];
                    ++actor_300e_count;
                    break;
                case 0x300f:
                    actor_300f_records[actor_300f_count].active = 1;
                    actor_300f_records[actor_300f_count].world_x = col * 2 + 2;
                    actor_300f_records[actor_300f_count].world_y = row * 128;
                    actor_300f_records[actor_300f_count].animation_state = 0;
                    register_level_update_callback(update_actor_300f);
                    *tile_cell = tile_cell[-1];
                    ++actor_300f_count;
                    break;
                case 0x3010:
                    actor_3010_records[actor_3010_count].state = 1;
                    actor_3010_records[actor_3010_count].world_x = col * 2 + 2;
                    actor_3010_records[actor_3010_count].world_y = row * 128;
                    actor_3010_records[actor_3010_count].animation_phase = 0;
                    register_level_update_callback(update_actor_3010);
                    *tile_cell = tile_cell[-1];
                    ++actor_3010_count;
                    break;
                case 0x3011:
                    current_weapon_state = 0;
                    door_or_key_interaction_state = 1;
                    door_lock_world_x = col * 2 + 2;
                    door_lock_world_y = row * 128 + 2;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3012:
                    actor_3012_records[actor_3012_count].state = 1;
                    actor_3012_records[actor_3012_count].world_x = col * 2 + 2;
                    actor_3012_records[actor_3012_count].world_y = row * 128;
                    actor_3012_records[actor_3012_count].object_kind = 0;
                    actor_3012_records[actor_3012_count].unknown_flag_8 = 1;
                    actor_3012_records[actor_3012_count].unknown_flag_10 = 1;
                    register_level_update_callback(update_actor_3012);
                    *tile_cell = tile_cell[-1];
                    ++actor_3012_count;
                    break;
                case 0x3013:
                    actor_3013_formation_state = 0;
                    formation_update_enabled = 1;
                    formation_active_object_count = 0;
                    for (k = 9; k > 0; --k) {
                        formation_object_x_positions[k] = col * 2 + k * 2;
                        formation_object_y_positions[k] = row * 128 + 2;
                        formation_object_active_flags[k] = 1;
                    }
                    register_level_update_callback(update_actor_3013);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3014:
                    actor_3014_records[actor_3014_count].world_x = col * 2 + 2;
                    actor_3014_records[actor_3014_count].world_y = row * 128;
                    ++actor_3014_count;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3015:
                case 0x3052:
                    if (*tile_cell == 0x3052)
                        actor_3015_records[actor_3015_count].state = 2;
                    else
                        actor_3015_records[actor_3015_count].state = 1;
                    actor_3015_records[actor_3015_count].world_x = col * 2 + 2;
                    actor_3015_records[actor_3015_count].world_y = row * 128;
                    ++actor_3015_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_3015);
                    break;
                case 0x3016:
                case 0x3017:
                    if (*tile_cell == 0x3016) {
                        actor_3016_records[actor_3016_count].state = 1;
                        *tile_cell = tile_cell[1];
                    } else {
                        actor_3016_records[actor_3016_count].state = 3;
                        *tile_cell = tile_cell[-1];
                    }
                    actor_3016_records[actor_3016_count].world_x = col * 2 + 2;
                    actor_3016_records[actor_3016_count].world_y = row * 128;
                    ++actor_3016_count;
                    register_level_update_callback(update_actor_3016);
                    break;
                case 0x3018:
                case 0x3051:
                    if (*tile_cell == 0x3051)
                        actor_3018_records[actor_3018_count].state = 2;
                    else
                        actor_3018_records[actor_3018_count].state = 1;
                    actor_3018_records[actor_3018_count].world_x = col * 2 + 2;
                    actor_3018_records[actor_3018_count].world_y = row * 128;
                    ++actor_3018_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_3018);
                    break;
                case 0x3019:
                    actor_3019_screen_x = col + 2;
                    actor_3019_map_row = row;
                    actor_3019_enabled = 1;
                    actor_3019_animation_state = 0;
                    actor_3019_world_x = col + 2;
                    actor_3019_world_y = row * 128;
                    k = 0;
                    /* Direct cell indexing changes this far-pointer access sequence. */
                    while (((struct level_map_cell_pair far *)(tile_cell + k))->second_tile_value < 0x1800) {
                        tile_cell[k] = 0x21a0;
                        ((struct level_map_cell_pair far *)(tile_cell + k))->second_tile_value = 0x21c0;
                        k += 2;
                    }
                    actor_3019_width = k * 2;
                    register_level_update_callback(update_actor_3019);
                    *tile_cell = 0x21a0;
                    break;
                case 0x301a:
                    actor_301a_records[actor_301a_count].world_x = col * 2 + 2;
                    actor_301a_records[actor_301a_count].world_y = row * 128;
                    actor_301a_records[actor_301a_count].active = 1;
                    register_level_update_callback(update_actor_301a);
                    ++actor_301a_count;
                    *tile_cell = tile_cell[-128];
                    break;
                case 0x301b:
                case 0x301c:
                    if (*tile_cell == 0x301b) {
                        actor_301b_records[actor_301b_count].state = 1;
                        *tile_cell = tile_cell[-1];
                    } else {
                        actor_301b_records[actor_301b_count].state = 2;
                        *tile_cell = tile_cell[1];
                    }
                    actor_301b_records[actor_301b_count].world_x = col * 2 + 2;
                    actor_301b_records[actor_301b_count].world_y = row * 128;
                    actor_301b_records[actor_301b_count].animation_count = 0;
                    register_level_update_callback(update_actor_301b);
                    ++actor_301b_count;
                    break;
                case 0x301d:
                case 0x3050:
                    actor_301d_records[actor_301d_count].active = 1;
                    actor_301d_records[actor_301d_count].world_x = col * 2 + 2;
                    actor_301d_records[actor_301d_count].world_y = row * 128;
                    if (*tile_cell == 0x3050)
                        actor_301d_records[actor_301d_count].animation_state = 1;
                    else
                        actor_301d_records[actor_301d_count].animation_state = 0;
                    ++actor_301d_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_301d);
                    break;
                case 0x301e:
                case 0x3054:
                    actor_301e_records[actor_301e_count].state = 1;
                    actor_301e_records[actor_301e_count].world_x = col * 2 + 2;
                    actor_301e_records[actor_301e_count].world_y = row * 128;
                    if (*tile_cell == 0x3054)
                        actor_301e_records[actor_301e_count].animation_flag = 1;
                    else
                        actor_301e_records[actor_301e_count].animation_flag = 0;
                    ++actor_301e_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_301e);
                    break;
                case 0x301f:
                case 0x3053:
                    actor_301f_records[actor_301f_count].state = 1;
                    actor_301f_records[actor_301f_count].world_x = col * 2 + 2;
                    actor_301f_records[actor_301f_count].world_y = row * 128;
                    if (*tile_cell == 0x3053)
                        actor_301f_records[actor_301f_count].animation_flag = 1;
                    else
                        actor_301f_records[actor_301f_count].animation_flag = 0;
                    ++actor_301f_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_301f);
                    break;
                case 0x3020:
                    actor_3020_world_x = col * 2 + 2;
                    actor_3020_world_y = row * 128;
                    actor_3020_state = 0;
                    register_level_update_callback(update_actor_3020);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3021:
                    actor_3021_records[actor_3021_count].world_x = col * 2 + 2;
                    actor_3021_records[actor_3021_count].world_y = row * 128;
                    /* Direct next-record indexing changes output; this sets the following actor's world_x. */
                    (&actor_3021_records[actor_3021_count].world_x)[2] = 1;
                    register_level_update_callback(update_actor_3021);
                    ++actor_3021_count;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3022:
                    actor_3022_records[actor_3022_count].movement_state = 1;
                    actor_3022_records[actor_3022_count].world_x = col * 2 + 2;
                    actor_3022_records[actor_3022_count].world_y = row * 128;
                    actor_3022_records[actor_3022_count].jump_timer = 0;
                    actor_3022_records[actor_3022_count].hit_points = 4;
                    actor_3022_records[actor_3022_count].fall_counter = 0;
                    register_level_update_callback(update_actor_3022);
                    ++actor_3022_count;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3023:
                    actor_3023_records[actor_3023_count].state = 1;
                    actor_3023_records[actor_3023_count].world_x = col * 2 + 2;
                    actor_3023_records[actor_3023_count].world_y = row * 128;
                    register_level_update_callback(update_actor_3023);
                    ++actor_3023_count;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3024:
                    level_progress_word = 1;
                    actor_3024_records[actor_3024_count].state = 1;
                    actor_3024_records[actor_3024_count].world_x = col * 2 + 2;
                    actor_3024_records[actor_3024_count].world_y = row * 128;
                    ++actor_3024_count;
                    *tile_cell = tile_cell[128];
                    break;
                case 0x3025:
                    animated_level_tile_records[actor_3025_count].sprite_resource_offset = 0x7ee0;
                    animated_level_tile_records[actor_3025_count].world_x = col * 2 + 2;
                    animated_level_tile_records[actor_3025_count].world_y = row * 128;
                    ++actor_3025_count;
                    *tile_cell = tile_cell[-128];
                    break;
                case 0x3026:
                case 0x3027:
                    animated_level_tile_records[actor_3025_count].sprite_resource_offset = (*tile_cell + 0xcfda) * 0xa0 + 0x7f80;
                    animated_level_tile_records[actor_3025_count].world_x = col * 2 + 2;
                    animated_level_tile_records[actor_3025_count].world_y = row * 128;
                    ++actor_3025_count;
                    if (*tile_cell == 0x3026)
                        *tile_cell = tile_cell[-1];
                    else
                        *tile_cell = tile_cell[1];
                    break;
                case 0x3028:
                    animated_level_tile_records[actor_3025_count].sprite_resource_offset = 0x80c0;
                    animated_level_tile_records[actor_3025_count].world_x = col * 2 + 2;
                    animated_level_tile_records[actor_3025_count].world_y = row * 128;
                    ++actor_3025_count;
                    *tile_cell = 0;
                    break;
                case 0x3029:
                    actor_3029_records[actor_3029_count].state = 1;
                    actor_3029_records[actor_3029_count].world_x = col * 2 + 2;
                    actor_3029_records[actor_3029_count].world_y = row * 128;
                    ++actor_3029_count;
                    register_level_update_callback(update_actor_3029);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x302a:
                    actor_302a_records[actor_302a_count].state = 1;
                    actor_302a_records[actor_302a_count].world_x = col * 2 + 2;
                    actor_302a_records[actor_302a_count].world_y = row * 128;
                    ++actor_302a_count;
                    register_level_update_callback(update_actor_302a);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x302b:
                    actor_302b_active_state = 0;
                    actor_302b_world_x = col * 2 + 2;
                    actor_302b_world_y = row * 128;
                    actor_302b_open_state = 1;
                    actor_302b_animation_counter = 10;
                    register_level_update_callback(update_actor_302b);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x302c:
                    actor_302c_records[actor_302c_count].world_x = col * 2 + 2;
                    actor_302c_records[actor_302c_count].world_y = row * 128;
                    register_level_update_callback(update_actor_302c);
                    ++actor_302c_count;
                    *tile_cell = tile_cell[-128];
                    break;
                case 0x302d:
                case 0x3055:
                    if (*tile_cell == 0x3055)
                        actor_302d_records[actor_302d_count].state = 2;
                    else
                        actor_302d_records[actor_302d_count].state = 1;
                    actor_302d_records[actor_302d_count].world_x = col * 2 + 2;
                    actor_302d_records[actor_302d_count].world_y = row * 128;
                    ++actor_302d_count;
                    register_level_update_callback(update_actor_302d);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x302e:
                case 0x3056:
                    if (*tile_cell == 0x3056)
                        actor_302e_records[actor_302e_count].state = 2;
                    else
                        actor_302e_records[actor_302e_count].state = 1;
                    actor_302e_records[actor_302e_count].world_x = col * 2 + 2;
                    actor_302e_records[actor_302e_count].world_y = row * 128;
                    ++actor_302e_count;
                    register_level_update_callback(update_actor_302e);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x302f:
                    actor_302f_active_state = 1;
                    actor_302f_world_x = col * 2 + 2;
                    actor_302f_world_y = row * 128;
                    actor_302f_interaction_state = 0;
                    actor_302f_interaction_phase = 0;
                    register_level_update_callback(activate_actor_302f);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3030:
                    actor_3030_active_state = 1;
                    actor_3030_world_x = col * 2 + 2;
                    actor_3030_world_y = row * 128;
                    actor_3030_interaction_state = 0;
                    actor_302f_animation_phase = 0;
                    register_level_update_callback(activate_actor_3030);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3031:
                    actor_3031_records[actor_3031_count].state = 0xfffa;
                    actor_3031_records[actor_3031_count].world_x = col * 2 + 2;
                    actor_3031_records[actor_3031_count].world_y = row * 128;
                    register_level_update_callback(update_actor_3031);
                    *tile_cell = tile_cell[-1];
                    ++actor_3031_count;
                    break;
                case 0x3032:
                    level_scroll_x = col * 2 - 14;
                    level_map_y_offset = row * 128 - 384;
                    player_screen_y = 64;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3033:
                    actor_3033_active_state = 0;
                    actor_3033_enabled = 1;
                    actor_3033_world_x = col * 2 + 2;
                    actor_3033_world_y = row * 128;
                    actor_3033_state = 0;
                    register_level_update_callback(update_actor_3033);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3034:
                    actor_3034_active_state = 1;
                    actor_3034_world_x = col * 2 + 2;
                    actor_3034_world_y = row * 128;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3035:
                    actor_3035_active_state = 1;
                    actor_3035_animation_state = 0;
                    actor_3035_state = 0;
                    actor_3035_world_x = col * 2 + 2;
                    actor_3035_world_y = row * 128;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3036:
                    secret_block_animation_state = 1;
                    secret_block_state = 0;
                    secret_block_world_x = col * 2 + 2;
                    secret_block_world_y = row * 128;
                    *tile_cell = 0x2fe0;
                    register_level_update_callback(update_secret_block_state);
                    break;
                case 0x3037:
                case 0x3038:
                case 0x3039:
                case 0x303a:
                    actor_3037_animation_state = 0;
                    switch (*tile_cell) {
                    case 0x3037:
                        actor_3037_records[actor_3037_object_count].state = 0x44;
                        break;
                    case 0x3038:
                        actor_3037_records[actor_3037_object_count].state = 0x55;
                        break;
                    case 0x3039:
                        actor_3037_records[actor_3037_object_count].state = 0x4b;
                        break;
                    case 0x303a:
                        actor_3037_records[actor_3037_object_count].state = 0x45;
                        break;
                    }
                    actor_3037_records[actor_3037_object_count].world_x = col * 2 + 2;
                    actor_3037_records[actor_3037_object_count].world_y = row * 128;
                    actor_3037_records[actor_3037_object_count].animation_flag = 0;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_3037);
                    ++actor_3037_object_count;
                    break;
                case 0x303b:
                    actor_303b_records[actor_303b_count].state = 1;
                    actor_303b_records[actor_303b_count].world_x = col * 2 + 2;
                    actor_303b_records[actor_303b_count].world_y = row * 128;
                    actor_303b_records[actor_303b_count].object_kind = 0;
                    ++actor_303b_count;
                    register_level_update_callback(update_actor_303b);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x303c:
                    actor_303c_records[actor_303c_count].state = 1;
                    actor_303c_records[actor_303c_count].world_x = col * 2 + 2;
                    actor_303c_records[actor_303c_count].world_y = row * 128;
                    ++actor_303c_count;
                    register_level_update_callback(update_actor_303c);
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x303d:
                case 0x303e:
                case 0x303f:
                    animated_level_tile_records[actor_3025_count].sprite_resource_offset = (*tile_cell + 0xcfc3) * 0xa0 + 0x9d80;
                    animated_level_tile_records[actor_3025_count].world_x = col * 2 + 2;
                    animated_level_tile_records[actor_3025_count].world_y = row * 128;
                    ++actor_3025_count;
                    *tile_cell = 0;
                    break;
                case 0x3040:
                    actor_3040_active_state = 1;
                    actor_3040_world_x = col * 2 + 2;
                    actor_3040_world_y = row * 128;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3041:
                    actor_3041_active_state = 1;
                    actor_3041_interaction_state = 0;
                    actor_3041_world_x = col * 2 + 2;
                    actor_3041_world_y = row * 128;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x3042:
                case 0x3043:
                    actor_3042_active_state = 1;
                    actor_3042_world_x = col * 2 + 2;
                    actor_3042_world_y = row * 128;
                    actor_3042_open_state = 1;
                    if (*tile_cell == 0x3043)
                        ending_sequence_enabled = 1;
                    else
                        ending_sequence_enabled = 0;
                    actor_3042_animation_counter = 10;
                    player_animation_lock_state = 0;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_3042);
                    break;
                case 0x3044:
                case 0x3045:
                case 0x3046:
                case 0x3047:
                    actor_3044_records[actor_3044_entity_count].state = (*tile_cell + 0xcfbd) * 0xa0;
                    actor_3044_records[actor_3044_entity_count].world_x = col * 2 + 2;
                    actor_3044_records[actor_3044_entity_count].world_y = row * 128;
                    ++actor_3044_entity_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_actor_3044);
                    break;
                case 0x3048:
                case 0x3049:
                case 0x304a:
                case 0x304b:
                    actor_3048_records[actor_3048_entity_count].sprite_resource_offset = (*tile_cell + 0xcfba) * 0xa0;
                    actor_3048_records[actor_3048_entity_count].world_x = col * 2 + 2;
                    actor_3048_records[actor_3048_entity_count].world_y = row * 128;
                    actor_3048_records[actor_3048_entity_count].alternate_frame = (*tile_cell + 0xcfba) * 0xa0;
                    ++actor_3048_entity_count;
                    *tile_cell = tile_cell[-1];
                    break;
                case 0x304c:
                case 0x304d:
                case 0x304e:
                case 0x304f:
                    level_tile_animation_records[actor_3048_object_count].sprite_resource_offset = (*tile_cell + 0xcfb5) * 0xa0;
                    level_tile_animation_records[actor_3048_object_count].world_x = col * 2 + 2;
                    level_tile_animation_records[actor_3048_object_count].world_y = row * 128;
                    level_tile_animation_records[actor_3048_object_count].alternate_frame = 0;
                    ++actor_3048_object_count;
                    *tile_cell = 0x1820;
                    register_level_update_callback(animate_level_tile_records);
                    break;
                case 0x3057:
                    falling_hazard_records[level_hazard_count].active = 1;
                    falling_hazard_records[level_hazard_count].world_x = col * 2 + 2;
                    falling_hazard_records[level_hazard_count].world_y = row * 128;
                    ++level_hazard_count;
                    *tile_cell = tile_cell[-1];
                    register_level_update_callback(update_falling_hazards);
                    break;
                case 0x3058:
                case 0x3059:
                    actor_3058_records[level_object_pool_531e_count].world_x = col * 2 + 2;
                    actor_3058_records[level_object_pool_531e_count].world_y = row * 128;
                    register_level_update_callback(draw_marker_3058_objects);
                    if (*tile_cell == 0x3058) {
                        actor_3058_records[level_object_pool_531e_count].sprite_resource_offset = 0x5c80;
                        *tile_cell = tile_cell[-128];
                    } else {
                        actor_3058_records[level_object_pool_531e_count].sprite_resource_offset = 0x5d20;
                        *tile_cell = tile_cell[128];
                    }
                    ++level_object_pool_531e_count;
                    break;
                case 0x305a:
                    break;
                case 0x305b:
                    break;
                case 0x305c:
                    break;
                case 0x305d:
                    break;
                case 0x305e:
                    break;
                case 0x305f:
                    break;
                default:
                    break;
                }
            }
        }
    }
}

/* ============================================================================================
   Files, demos and settings
   Level map, demo recordings, buffers, memory check and the game-speed setting.
   ============================================================================================ */

/* Reads the level's 16-bit tile map from the named file into the level-map buffer. */
void load_level_tile_map(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    fread(level_tile_map, 11520, 2, stream);
    fclose(stream);
}

/* load_user_demo_recording candidate 3 */
/* Reads the user-demo header and recorded input bytes into the supplied buffer. */
void load_user_demo_recording(char far *filename, char far *buffer)
{
    FILE *file_stream;

    file_stream = fopen(filename, "rb");
    if (file_stream == 0) {
        demo_file_load_success = 0;
        user_demo_recording_state = 1;
    } else {
        user_demo_recording_state = 0;
        user_demo_input_length = getw(file_stream);
        fread(buffer, 17000, 1, file_stream);
        demo_file_load_success = 1;
    }
    fclose(file_stream);
}

/* Reads the saved-demo header and recorded input bytes into the supplied buffer. */
void load_saved_demo_recording(char far *filename, char far *buffer)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    if (stream == NULL) {
        demo_file_load_success = 0;
    } else {
        saved_demo_input_length = getw(stream);
        fread(buffer, 17000, 1, stream);
        demo_file_load_success = 1;
    }
    fclose(stream);
}

/* Writes a user-demo header and recorded input bytes to the named file. */
void save_user_demo_recording(char far *filename, void far *buffer)
{
    FILE *stream;

    stream = fopen(filename, "wb");
    putw(user_demo_input_length, stream);
    fwrite(buffer, 17000, 1, stream);
    fclose(stream);
}

/* Writes the saved-demo header and recorded input bytes to the named file. */
void save_demo_recording(char far *filename, void far *buffer)
{
    FILE *stream;

    stream = fopen(filename, "wb");
    putw(saved_demo_input_length, stream);
    fwrite(buffer, 17000, 1, stream);
    fclose(stream);
}

/* Allocates the game buffers and initializes episode resource data needed by the first screens. */
void allocate_game_buffers_and_state(void)
{
    load_planar_image_file(F_BORDER0, 0x3000, 7680);
    level_tile_map = malloc(24000);
    font_glyph_data_buffer = malloc(4500);
    sprite_pixel_data_pointer = malloc(24010);
    object_sprite_buffer = malloc(8001);
    player_sprite_resource_buffer = malloc(34001);
    sprite_graphics_buffer = malloc(48001);
    saved_demo_buffer = malloc(18000);
    user_demo_buffer = malloc(18000);

    if (!font_glyph_data_buffer || !player_sprite_resource_buffer || !sprite_graphics_buffer || !sprite_pixel_data_pointer)
        exit(0);
    if (!saved_demo_buffer || !user_demo_buffer)
        exit(0);
    if (!saved_demo_buffer || !user_demo_buffer)
        exit(0);
    if (!object_sprite_buffer)
        exit(0);
    if (!level_tile_map)
        exit(0);

    read_file_block(F_FONT1, font_glyph_data_buffer, 2000);
    read_file_block(F_FONT2, font_glyph_data_buffer + 2000, 2000);
    clear_palette_entries(5);
    show_loading_status();
    restore_ega_palette(5);
    read_file_block(F_NUMBERS, object_sprite_buffer, 8000);
    read_file_block(F_OBJECT0, sprite_pixel_data_pointer, 8000);
    read_file_block(F_OBJECT1, sprite_pixel_data_pointer + 8000, 8000);
    read_file_block(F_OBJECT2, sprite_pixel_data_pointer + 16000, 8000);
    load_user_demo_recording(F_USERDEMO, saved_demo_buffer);
    load_saved_demo_recording(F_MYDEMO, user_demo_buffer);
    read_file_block(F_MAN0, player_sprite_resource_buffer, 7680);
    read_file_block(F_MAN1, player_sprite_resource_buffer + 7680, 7680);
    read_file_block(F_MAN2, player_sprite_resource_buffer + 15360, 7680);
    read_file_block(F_MAN3, player_sprite_resource_buffer + 23040, 7680);
    load_planar_image_file(F_BACK0, 0, 7680);
    load_planar_image_file(F_BACK1, 0x600, 7680);
    load_planar_image_file(F_BACK2, 0xc00, 7680);
    load_planar_image_file(F_BACK3, 0x1200, 7680);
    clear_palette_entries(5);
    clear_video_page();
    load_planar_image_file(F_SOLID0, 0x1800, 7680);
    load_planar_image_file(F_SOLID1, 7680, 7680);
    show_credit_screen();
    restore_ega_palette(5);
    load_planar_image_file(F_SOLID2, 0x2400, 7680);
    load_planar_image_file(F_SOLID3, 0x2a00, 7680);
    load_planar_image_file(F_BORDER0, 0x3000, 7680);
    read_file_block(F_ANIM0, sprite_graphics_buffer, 7680);
    read_file_block(F_ANIM1, sprite_graphics_buffer + 7680, 7680);
    read_file_block(F_ANIM2, sprite_graphics_buffer + 15360, 7680);
    read_file_block(F_ANIM3, sprite_graphics_buffer + 23040, 7680);
    read_file_block(F_ANIM4, sprite_graphics_buffer + 0x7800, 7680);
    read_file_block(F_ANIM5, sprite_graphics_buffer + 38400, 7680);
    clear_palette_entries(5);
}

/* Resets level runtime state, loads the tile map and drop graphics, creates map objects, and
   draws their marker tiles. */
void pascal load_level_and_init_objects(char far *level_filename)
{
    clear_projectiles();
    interaction_cooldown_state = 0;
    world_animation_phase = 0;
    gameplay_animation_flag = 0;
    player_death_state = 0;
    player_action_state = 4;
    player_animation_phase = 0;
    player_invulnerability_state = 0;
    actor_3000_count = 0;
    collision_sound_record_count = 12;
    projectile_count = 3;
    moving_object_count = 7;
    pickup_object_count = 0x12;
    moving_actor_count = 8;
    actor_3001_count = 0;
    actor_3002_count = 0;
    actor_3007_count = 0;
    actor_3009_count = 0;
    actor_300a_count = 0;
    actor_300b_count = 0;
    actor_300b_screen_anim_offset = 0;
    actor_300b_animation_frame = 0;
    actor_300c_count = 0;
    actor_300d_count = 0;
    actor_300e_count = 0;
    keyboard_hotkey_count = 0;
    actor_300f_count = 0;
    actor_3010_count = 0;
    current_weapon_state = 0;
    door_or_key_interaction_state = 0;
    actor_3012_count = 0;
    formation_update_enabled = 0;
    actor_3014_count = 0;
    actor_3015_count = 0;
    actor_3016_count = 0;
    actor_3018_count = 0;
    actor_3019_enabled = 0;
    actor_301a_count = 0;
    actor_301b_count = 0;
    actor_301d_count = 0;
    actor_301e_count = 0;
    actor_301f_count = 0;
    actor_3021_count = 0;
    actor_3022_count = 0;
    actor_3023_count = 0;
    actor_3024_count = 0;
    actor_3025_count = 0;
    actor_3029_count = 0;
    actor_302a_count = 0;
    actor_302c_count = 0;
    actor_302b_active_state = 1;
    actor_302b_open_state = 0;
    actor_302d_count = 0;
    actor_302e_count = 0;
    actor_3031_count = actor_3030_active_state = actor_3030_interaction_state = actor_302f_active_state = actor_302f_interaction_state = 0;
    actor_3034_active_state = -1;
    actor_3042_active_state = actor_3041_active_state = actor_3040_active_state = actor_303c_count = actor_303b_count = actor_3037_bonus_state = actor_3037_object_count = secret_block_animation_state = actor_3035_active_state = 0;
    active_sprite_draw_flag = 0;
    player_projectile_state = 0x15;
    exit_lock_animation_state = actor_3048_object_count = actor_3044_entity_count = actor_3048_entity_count = actor_3033_enabled = actor_3033_active_state = 0;
    actor_302b_animation_counter = 10;
    actor_3042_animation_frame_4 = actor_3042_animation_frame_3 = actor_3042_animation_frame_2 = actor_3042_animation_frame_1 = actor_3042_animation_frame_0 = level_hazard_count = 0;
    actor_3042_animation_frame_5 = 10;
    actor_3042_interaction_state = level_object_pool_531e_count = ending_sequence_enabled = player_animation_lock_state = 0;

    load_level_tile_map(level_filename);
    outport(0x3ce, 5);

    if (current_level_index % 2 == 0) {
        load_planar_image_file(episode_drop_filename_table[(int)current_level_index],
                               0x4000, 0x5140);
        load_planar_image_file(episode_drop_filename_table[(int)current_level_index + 1],
                               0x8100, 0x5140);
    }

    if (current_level_index % 2 == 0) {
        player_gameplay_state = 1;
        actor_303b_update_state = 0;
        clear_ambient_object_pool();
    }

    create_objects_from_level_map(90);
    player_sprite_draw_state = 1;
    player_sprite_refresh_state = 0;
    player_sprite_animation_index = 0;
    control_hint_up_flag = 0;
    control_hint_down_flag = 0;
    control_hint_left_flag = 0;
    control_hint_right_flag = 0;
    draw_level_marker_tiles();
}

/* player_score_upper_word_alias is byte 2 of accepted player_score (long): use player_score */
/* sprite_pixel_segment_alias is byte 2 of accepted sprite_pixel_data_pointer (char far*): use sprite_pixel_data_pointer */
/* Initializes player and level-entry state, restores a save when requested, then loads the
   selected level. */
void init_player_and_level_state(void)
{
    long saved_score;

    actor_300e_animation_state = 0;
    actor_300e_animation_counter = 0;
    player_action_state = 4;
    player_animation_phase = 0;
    player_invulnerability_state = 0;
    actor_3006_world_x = 0;
    actor_3006_world_y = 0;
    access_card_or_door_state = 0;
    actor_3006_state = 0;
    actor_3008_state = 0;
    player_contact_state = 0;
    actor_3020_world_x = 0;
    actor_3020_world_y = 0;
    actor_3020_active_state = 0;
    actor_3020_state = 0;
    actor_3033_world_x = 0;
    actor_3033_world_y = 0;
    actor_3033_active_state = 0;
    actor_3033_state = 0;
    alternate_sprite_draw_offset = 0;
    episode_sprite_resource_table = 0;
    actor_3013_formation_state = 0;
    actor_3037_animation_state = 0;
    world_actor_count = 1;
    level_loading_state = 0;
    player_airborne_state = 1;
    player_damage_immunity_state = 0;
    player_jump_frame = 0;
    player_screen_x = 0x10;
    player_screen_y = 0x30;
    level_scroll_x = 0;
    level_map_y_offset = 0;
    player_score = 0L;
    level_progress_word = 0;
    level_play_state = 0;
    actor_302a_update_state = 0;
    current_level_index = 0;
    title_graphic_frame_index = 9;

    if (restore_saved_game_requested) {
        restore_game_state_from_slot(selected_save_slot);
        if (game_session_abort_flag) {
            return;
        }
        set_palette_entries_to_23(0x14);
        clear_video_page();
        restore_saved_game_requested = 0;
        if (access_card_or_door_state) {
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x640);
        }
        if (player_contact_state) {
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0xb40);
        }
        if (actor_3020_active_state) {
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x2760);
        }
    } else {
        clear_video_page();
    }

    draw_page_frame_template();
    draw_get_ready_message();
    draw_video_page_template();
    restore_ega_palette(0x14);

    if (demo_mode_state == 2 || player_level_transition_state == 2) {
        current_level_index = 0x14;
    }
    load_level_and_init_objects(episode_level_filename_table[current_level_index]);
    saved_score = player_score;
    player_score = 0L;
    add_and_draw_player_score(0L);
    player_score = saved_score;
    add_and_draw_player_score(0L);
    draw_buffered_screen_effect();
    draw_title_screen_graphic();
}

/* Checks that DOS reports the minimum required free memory and exits with a message when it does
   not. */
void check_minimum_available_memory(void)
{
    unsigned long available_bytes;

    available_bytes = coreleft();
    if (available_bytes < 360000UL) {
        printf("Not enough memory to run Duke Nukum!\n");
        printf("(There needs to be at least 520k available.)\n");
        printf("Try unloading TSRs or exiting from a shell\n");
        printf("and then try running the game again.  Thanks!\n");
        _exit(0);
    }
}

/* Reads the saved game-speed word from the named file, using zero when the file is absent. */
void pascal load_game_speed_setting(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    if (stream == NULL) {
        game_speed_setting = 0;
    } else {
        game_speed_setting = getw(stream);
    }
    fclose(stream);
}

/* Writes the current game-speed word to the named file. */
void pascal save_game_speed_setting(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "wb");
    putw(game_speed_setting, stream);
    fclose(stream);
}

/* ============================================================================================
   Game flow
   Timing, level transitions, start-up and shut-down, the main loop, the title menu and main().
   ============================================================================================ */

/* Busy-wait until the timer-interrupt tick counter reaches n (pascal). */
/* Waits until the timer interrupt counter reaches the requested number of ticks. */
void pascal wait_for_timer_ticks(register int target_ticks)
{
    timer_tick_counter = 0;
    while (timer_tick_counter < target_ticks)
        ;
}

/* goto kept: timeout skips the first fade-in wait; structured attempts change emission. */
/* Runs the level-transition presentation sequence using the active episode graphics and text. */
void play_level_transition_sequence(void)
{
    register int i;
    register int frame_toggle;
    long timeout_counter;
    int joystick_button_1;
    int joystick_button_2;

    timeout_counter = 0L;
    frame_toggle = 0;
    add_and_draw_player_score(100000L);
    if (ending_sequence_enabled != 0) {
        clear_palette_entries(10);
        display_ending_bitmap();
        restore_ega_palette(10);
        for (i = 0; i < 52; ++i) {
            frame_toggle = !frame_toggle;
            blit_planar_sprite_rows(sprite_pixel_data_pointer + (frame_toggle % 2) * 0xa0 + 0x5820,
                                    26, 125 - i);
            wait_for_timer_ticks(10);
        }
        for (i = 0; i < 50; ++i) {
            frame_toggle = !frame_toggle;
            blit_planar_sprite_rows(sprite_pixel_data_pointer + (frame_toggle % 2) * 0xa0 + 0x5820,
                                    26, 74);
            wait_for_timer_ticks(10);
        }
        for (i = 0; i < 5; ++i) {
            blit_planar_sprite_rows(sprite_pixel_data_pointer + i * 0xa0 + 0x5960,
                                    26, 75 - i);
            wait_for_timer_ticks(14);
        }

        timeout_counter = 0L;
        last_keyboard_scan_code = 0;
        /* Read the two joystick button lines from the game port. */
        if (joystick_enabled != 0) {
            joystick_button_1 = inportb(0x201) & 0x10;
            joystick_button_2 = inportb(0x201) & 0x20;
        } else {
            joystick_button_1 = joystick_button_2 = 1;
        }
        while (last_keyboard_scan_code == 0 && joystick_button_1 != 0 && joystick_button_2 != 0) {
            if (joystick_enabled != 0) {
                joystick_button_1 = inportb(0x201) & 0x10;
                joystick_button_2 = inportb(0x201) & 0x20;
            } else {
                joystick_button_1 = joystick_button_2 = 1;
            }
            if (timer_tick_counter % 2 != 0) {
                ++timeout_counter;
                if (timeout_counter == 1500000L) {
                    clear_palette_entries(10);
                    display_badguy_bitmap();
                    restore_ega_palette(10);
                    goto stage_after_first;
                }
                if (timeout_counter == 300000L)
                    wait_controller_button();
            }
        }

        clear_palette_entries(10);
        display_badguy_bitmap();
        restore_ega_palette(10);
        if (control_confirmation_state == 0) {
            do {
            } while ((last_keyboard_scan_code & 0x80) == 0);
        }

    stage_after_first:
        show_proton_level_end_dialogue();
        timer_tick_counter = 0;

        clear_palette_entries(10);
        display_duke_bitmap();
        restore_ega_palette(10);
        if (control_confirmation_state == 0) {
            do {
            } while ((last_keyboard_scan_code & 0x80) == 0);
        }
        show_proton_transition_dialogue();
        timer_tick_counter = 0;

        clear_palette_entries(10);
        display_badguy_bitmap();
        restore_ega_palette(10);
        if (control_confirmation_state == 0) {
            do {
            } while ((last_keyboard_scan_code & 0x80) == 0);
        }
        show_proton_future_dialogue();
        timer_tick_counter = 0;

        clear_palette_entries(10);
        display_duke_bitmap();
        restore_ega_palette(10);
        if (control_confirmation_state == 0) {
            do {
            } while ((last_keyboard_scan_code & 0x80) == 0);
        }
        show_duke_level_end_dialogue();
        clear_palette_entries(10);
    } else {
        timer_tick_counter = 0;
        while (timer_tick_counter < 500) {
        }
        clear_palette_entries(20);
        clear_video_page();
        display_duke_bitmap();
        restore_ega_palette(20);
        if (control_confirmation_state == 0) {
            do {
            } while ((last_keyboard_scan_code & 0x80) == 0);
        }
        show_game_completion_message();
        clear_palette_entries(20);
    }
    timer_tick_counter = 0;
    show_next_episode_promotion(7);
}
/* Checks memory, selects video mode, loads settings and assets, installs the keyboard IRQ, and
   starts the timer IRQ. */
void pascal init_video_keyboard_and_assets(void)
{
    check_minimum_available_memory();
    detect_joystick_connection();
    set_video_mode(0);
    select_draw_page(0);
    show_video_page(0);
#if EPISODE == 1
    load_keyboard_bindings("KEYS.DN1");
#elif EPISODE == 2
    load_keyboard_bindings("KEYS.dn2");
#else
    load_keyboard_bindings("KEYS.DN3");
#endif
    load_high_score_table();
    allocate_game_buffers_and_state();
#if EPISODE == 1
    load_primary_sound_bank("duke1.dn1");
    load_secondary_sound_bank("duke1-b.dn1");
    load_title_screen("dn.dn1");
    load_ending_graphics("end.dn1");
    load_badguy_graphics("badguy.dn1");
    load_duke_graphics("duke.dn1");
    load_credits_graphics("credits.dn1");
#elif EPISODE == 2
    load_primary_sound_bank("duke1.dn2");
    load_secondary_sound_bank("duke1-b.dn2");
    load_title_screen("dn.dn2");
    load_ending_graphics("end.dn2");
    load_badguy_graphics("badguy.dn2");
    load_duke_graphics("duke.dn2");
    load_credits_graphics("credits.dn2");
#else
    load_primary_sound_bank("duke1.dn3");
    load_secondary_sound_bank("duke1-b.dn3");
    load_title_screen("dn.dn3");
    load_ending_graphics("end.dn3");
    load_badguy_graphics("badguy.dn3");
    load_duke_graphics("duke.dn3");
    load_credits_graphics("credits.dn3");
#endif
    disable();
    saved_keyboard_interrupt_vector = getvect(9);
    setvect(9, keyboard_interrupt_handler);
    enable();
    install_timer_interrupt();
#if EPISODE == 1
    load_game_speed_setting("SPEED.DN1");
#elif EPISODE == 2
    load_game_speed_setting("SPEED.dn2");
#else
    load_game_speed_setting("SPEED.DN3");
#endif
}

/* goto kept (STRUCTURING BACKLOG): the main game loop's shared exits and state tails; the
   structured forms measured 3900 and 4128 bytes, switch variants 3952 and 3983 (original 3985). */
/* sprite_pixel_segment_alias is byte 2 of accepted sprite_pixel_data_pointer (char far*): use sprite_pixel_data_pointer */
/* Runs the timer-paced gameplay loop for player input, demo playback, level callbacks,
   rendering, and menus. */
void run_game_loop(void)
{
    int level_advanced;
    register int sprite_offset;
    register int j;

    level_advanced = 0;
    credits_scroll_position = 0;
    credits_text_position = 0;
    credit_scroll_delay = 0;
    timer_tick_counter = 0;
    actor_3042_hint_state = 0;
    disable();
    control_fire_pressed = control_jump_pressed = control_left_pressed = control_right_pressed = control_up_pressed = control_down_pressed = 0;
    enable();

    if (player_level_transition_state != 0)
        last_keyboard_scan_code = 0;
    for (;;) {
        while (game_speed_setting + 9 > timer_tick_counter) {
            /* Wait for the next game tick. */
        }
        timer_tick_counter = 0;
        advance_player_transition();
        if (control_confirmation_state != 0) {
            if (actor_302f_interaction_state == 0 && actor_3030_interaction_state == 0)
                configure_joystick_axes(1);
            update_joystick_axis_state();
        }
        disable();

        /* Demo snapshots contain six bytes of player state. */
        if (player_level_transition_state == 1) {
            control_up_pressed = saved_demo_buffer[menu_selection_state];
            control_down_pressed = saved_demo_buffer[menu_selection_state + 1];
            control_left_pressed = saved_demo_buffer[menu_selection_state + 2];
            control_right_pressed = saved_demo_buffer[menu_selection_state + 3];
            control_fire_pressed = saved_demo_buffer[menu_selection_state + 4];
            control_jump_pressed = saved_demo_buffer[menu_selection_state + 5];
            menu_selection_state += 6;
            if (menu_selection_state >= 0x425a || menu_selection_state >= user_demo_input_length) {
                enable();
                goto reset_c683_exit;
            }
        }
        if (demo_mode_state == 1 && menu_selection_state != 0x425a) {
            saved_demo_buffer[menu_selection_state] = control_up_pressed;
            saved_demo_buffer[menu_selection_state + 1] = control_down_pressed;
            saved_demo_buffer[menu_selection_state + 2] = control_left_pressed;
            saved_demo_buffer[menu_selection_state + 3] = control_right_pressed;
            saved_demo_buffer[menu_selection_state + 4] = control_fire_pressed;
            saved_demo_buffer[menu_selection_state + 5] = control_jump_pressed;
            menu_selection_state += 6;
            if (menu_selection_state >= 0x4259) {
                demo_mode_state = 0;
                user_demo_input_length = menu_selection_state;
            }
        }
        if (player_level_transition_state == 2) {
            control_up_pressed = user_demo_buffer[menu_selection_state];
            control_down_pressed = user_demo_buffer[menu_selection_state + 1];
            control_left_pressed = user_demo_buffer[menu_selection_state + 2];
            control_right_pressed = user_demo_buffer[menu_selection_state + 3];
            control_fire_pressed = user_demo_buffer[menu_selection_state + 4];
            control_jump_pressed = user_demo_buffer[menu_selection_state + 5];
            menu_selection_state += 6;
            if (menu_selection_state >= 0x425a || menu_selection_state >= saved_demo_input_length) {
                enable();
                goto reset_c683_exit;
            }
        }
        if (demo_mode_state == 2 && menu_selection_state != 0x425a) {
            user_demo_buffer[menu_selection_state] = control_up_pressed;
            user_demo_buffer[menu_selection_state + 1] = control_down_pressed;
            user_demo_buffer[menu_selection_state + 2] = control_left_pressed;
            user_demo_buffer[menu_selection_state + 3] = control_right_pressed;
            user_demo_buffer[menu_selection_state + 4] = control_fire_pressed;
            user_demo_buffer[menu_selection_state + 5] = control_jump_pressed;
            menu_selection_state += 6;
            saved_demo_input_length = menu_selection_state;
            if (menu_selection_state >= 0x4259)
                demo_mode_state = 0;
        }

        update_player_and_level_state();
        enable();
        animate_ambient_sprite_records();
        animate_contact_flash_effects();
        update_collision_effect_pool();
        update_pickup_object_pool();
        update_moving_world_effects();
        resolve_projectile_collisions();
        update_animated_actor_pool();
        j = 0;
        while (j < keyboard_hotkey_count) {
            level_update_callback_table[j]();
            ++j;
        }

        if (player_level_transition_state == 2) {
            if (world_animation_phase == 0 || world_animation_phase == 0x20)
                draw_text_string("Press any key.", 8, 10);
            animate_credits_scroll();
        }
        if (keyboard_key_g_pressed != 0 && keyboard_key_o_pressed != 0 && keyboard_key_d_pressed != 0 && demo_mode_enabled != 0) {
            actor_3033_active_state = access_card_or_door_state = player_contact_state = actor_3020_active_state = 1;
            actor_3033_enabled = 0;
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x640);
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0xb40);
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x2760);
            draw_current_planar_sprite();
            title_graphic_frame_index = 9;
            draw_title_screen_graphic();
            control_hint_up_flag = control_hint_down_flag = control_hint_left_flag = control_hint_right_flag = 1;
            draw_level_marker_tiles();
            world_actor_count = 4;
            draw_buffered_screen_effect();
            timer_tick_counter = 0;
            alternate_sprite_draw_offset = 0;
        }
        if (keyboard_backspace_pressed == 1 && keyboard_interrupt_state == 1) {
            request_priority_sound_effect(0x19);
            draw_framed_dialog_box(2, 1, 2);
            show_cheat_mode_message();
            while (keyboard_backspace_pressed != 0 || keyboard_interrupt_state != 0)
                ;
            wait_input_animated_sprite(0x1a, 6);
            control_hint_up_flag = control_hint_down_flag = control_hint_left_flag = control_hint_right_flag = 1;
            draw_level_marker_tiles();
            world_actor_count = 4;
            draw_buffered_screen_effect();
            timer_tick_counter = 0;
            control_right_pressed = 0;
            control_down_pressed = 0;
        }
        update_moving_actor_pool();
        update_actor_3014();
        draw_video_page_template();
        if (demo_mode_state != 0)
            blit_bitmap_to_video_page(0x3200, 2);
        if (player_level_transition_state != 0 && world_animation_phase == 0)
            blit_bitmap_to_video_page(0x3180, 2);
        if (keyboard_backspace_pressed == 1 && keyboard_key_g_pressed != 0) {
            while (keyboard_backspace_pressed == 1 || keyboard_key_g_pressed != 0)
                ;
            while (keyboard_backspace_pressed == 0 && keyboard_key_g_pressed == 0)
                ;
        }
        if (last_keyboard_scan_code == 0x11 && keyboard_key_g_pressed != 0 && keyboard_key_o_pressed != 0 && demo_mode_enabled != 0)
            interaction_cooldown_state = 1;
        if (last_keyboard_scan_code == 0x23) {
            while (last_keyboard_scan_code == 0x23)
                ;
            toggle_hint_mode(2);
            timer_tick_counter = 0;
            select_draw_page(!draw_page_index);
            show_video_page(draw_page_index);
            control_right_pressed = 0;
            control_down_pressed = 0;
        }
        if (last_keyboard_scan_code == 0x19) {
            pause_until_resume_input(2);
            while (last_keyboard_scan_code == 0x19)
                ;
            timer_tick_counter = 0;
            select_draw_page(!draw_page_index);
            show_video_page(draw_page_index);
            control_right_pressed = 0;
            control_down_pressed = 0;
        }
        if (last_keyboard_scan_code == 0x3b && player_level_transition_state == 0) {
            menu_action_state = 0;
            handle_in_game_help_menu(2);
            if (menu_action_state != 0) {
                menu_action_state = 0;
                confirm_level_restart();
                if (last_keyboard_scan_code == 0x15) {
                    if (current_level_index == 0 && demo_mode_state != 0) {
                        demo_mode_state = 0;
                        user_demo_input_length = menu_selection_state;
                    }
                    control_right_pressed = 0;
                    control_down_pressed = 0;
                    timer_tick_counter = 0;
                    goto mode_tail;
                }
                timer_tick_counter = 0;
                select_draw_page(!draw_page_index);
                show_video_page(draw_page_index);
            }
            while (last_keyboard_scan_code == 1)
                ;
            control_right_pressed = 0;
            control_down_pressed = 0;
            timer_tick_counter = 0;
            select_draw_page(!draw_page_index);
            show_video_page(draw_page_index);
        }
        if (last_keyboard_scan_code == 0x1f && player_level_transition_state == 0) {
            toggle_sound_setting(2);
            while (last_keyboard_scan_code == 0x1f)
                ;
            timer_tick_counter = 0;
            select_draw_page(!draw_page_index);
            show_video_page(draw_page_index);
            control_right_pressed = 0;
            control_down_pressed = 0;
        }

        if (keyboard_control_lock_state != 0 && game_speed_setting > 0) {
            --game_speed_setting;
            blit_bitmap_to_video_page(0x3500, 4);
        }
        if (keyboard_modifier_state != 0 && game_speed_setting <= 8) {
            ++game_speed_setting;
            blit_bitmap_to_video_page(0x3520, 4);
        }
        select_draw_page(draw_page_index);
        show_video_page(draw_page_index = !draw_page_index);
        if (interaction_cooldown_state == 1) {
            if (demo_mode_state == 1) {
                demo_mode_state = 0;
                user_demo_input_length = menu_selection_state;
            }
            if (demo_mode_state == 2) {
                demo_mode_state = 0;
                saved_demo_input_length = menu_selection_state;
                return;
            }
            if (player_level_transition_state != 0)
                level_advanced = 1;
            ++current_level_index;
            load_level_and_init_objects(episode_level_filename_table[current_level_index]);
            if (current_level_index % 2 != 0) {
                sprite_offset = 0;
                if (player_gameplay_state != 0) {
                    /* Scale each 16-pixel tile row to its 128-byte screen stride. */
                    queue_ambient_sprite_animation(0xb40, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0xc80, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    sprite_offset += 0x100;
                    add_and_draw_player_score(10000L);
                }
                if (level_play_state != 0 && level_progress_word != 0) {
                    queue_ambient_sprite_animation(0x8c0, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0xa00, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    sprite_offset += 0x100;
                    add_and_draw_player_score(10000L);
                    level_play_state = 0;
                    level_progress_word = 0;
                }
                if (actor_302a_update_state != 0) {
                    queue_ambient_sprite_animation(0xdc0, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0xf00, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    add_and_draw_player_score(10000L);
                    actor_302a_update_state = 0;
                }
                player_gameplay_state = 1;
                if (hidden_object_state != 0 && level_loading_state != 0) {
                    queue_ambient_sprite_animation(0x1040, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0x1180, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    sprite_offset += 0x100;
                    add_and_draw_player_score(10000L);
                    hidden_object_state = 0;
                }
                if (actor_3037_animation_state != 0) {
                    queue_ambient_sprite_animation(0x12c0, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0x1400, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    add_and_draw_player_score(10000L);
                    sprite_offset += 0x100;
                    actor_3037_animation_state = 0;
                }
                if (actor_3013_formation_state != 0) {
                    queue_ambient_sprite_animation(0x1540, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0x1680, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    add_and_draw_player_score(10000L);
                    sprite_offset += 0x100;
                    actor_3013_formation_state = 0;
                }
                if (actor_303b_update_state != 0) {
                    queue_ambient_sprite_animation(0x17c0, player_screen_x + level_scroll_x + 4,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    queue_ambient_sprite_animation(0x1900, player_screen_x + level_scroll_x + 6,
                                                   (((player_screen_y - 29) >> 4) << 7) + sprite_offset + level_map_y_offset + 0x300);
                    add_and_draw_player_score(10000L);
                    sprite_offset += 0x100;
                    actor_303b_update_state = 0;
                }
                save_game_state_to_slot('T');
            }
        }
        if (title_graphic_frame_index < 2) {
            if (draw_page_index == 0) {
                blit_bitmap_to_video_page(0x3540, 0x660);
                blit_bitmap_to_video_page(0x3560, 0x662);
            } else {
                blit_bitmap_to_video_page(0x3480, 0x660);
                blit_bitmap_to_video_page(0x34a0, 0x662);
            }
        } else {
            /* Select VGA graphics-controller write mode 1. */
            outport(0x3ce, 0x0105);
            blit_bitmap_to_video_page(0x3480, 0x660);
            blit_bitmap_to_video_page(0x34a0, 0x662);
        }
        if (title_graphic_animation_state != 0) {
            ++title_graphic_animation_state;
            if (title_graphic_animation_state < 15)
                request_priority_sound_effect(10);
            switch (title_graphic_animation_state) {
            case 1:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                /* The jump preserves TC 2.0's shared tail for cases 2 and 7. */
                goto case_two_seven;
            case 3:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x - 2,
                                           128 - (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
            case 4:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x + 2,
                                           128 - (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                break;
            case 5:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x - 3,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
            case 6:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x + 3,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                break;
            case_two_seven:
            case 2:
            case 7:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset + 128);
                break;
            case 8:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                break;
            case 10:
            case 15:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x - 2,
                                           128 - (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
            case 11:
            case 16:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x + 3,
                                           128 - (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                break;
            case 12:
            case 17:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x - 3,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                break;
            case 13:
            case 18:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x + 2,
                                           (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
            case 9:
            case 14:
            case 19:
                spawn_contact_flash_effect(player_screen_x + level_scroll_x,
                                           128 - (((player_screen_y - 16) >> 4) << 7) + level_map_y_offset);
                break;
            }
        }

        if (title_graphic_frame_index == 0 && title_graphic_animation_state == 0)
            title_graphic_animation_state = 1;
        if ((title_graphic_frame_index == 0 && player_level_transition_state == 0 && title_graphic_animation_state == 30) ||
            (last_keyboard_scan_code == 0x44 && current_level_index % 2 == 0)) {
            if (last_keyboard_scan_code == 0x44) {
                confirm_level_restart();
                if (last_keyboard_scan_code == 0x15) {
                    if (current_level_index == 0 && demo_mode_state != 0) {
                        demo_mode_state = 0;
                        user_demo_input_length = menu_selection_state;
                    }
                    goto mode_tail;
                } else {
                    timer_tick_counter = 0;
                    select_draw_page(!draw_page_index);
                    show_video_page(draw_page_index);
                }
                goto post_mode;
            } else {
                request_priority_sound_effect(0);
                if (current_level_index != 0) {
                    draw_framed_dialog_box(2, 1, 2);
                    show_player_death_message();
                    while (timer_tick_counter < 100)
                        ;
                    timer_tick_counter = 0;
                    do {
                        last_keyboard_scan_code = 0;
                        wait_input_animated_sprite(0x1a, 6);
                    } while (last_keyboard_scan_code != 0x1c);
                    control_down_pressed = 0;
                    control_right_pressed = 0;
                }
            }
        } else {
            goto post_mode;
        }
    /* Shared cleanup keeps the mode exits on TC 2.0's matching path. */
    mode_tail:
        last_keyboard_scan_code = 0;
        select_draw_page(0);
        draw_video_page_template();
        select_draw_page(1);
        draw_video_page_template();
        draw_page_index = 0;
        select_draw_page(draw_page_index);
        show_video_page(draw_page_index);
        title_graphic_animation_state = 0;
        game_session_abort_flag = 0;
        restore_saved_game_requested = 1;
        selected_save_slot = 'T';
        if (demo_mode_state != 0)
            user_demo_input_length = menu_selection_state;
        demo_mode_state = 0;
        draw_video_page_template();
        init_player_and_level_state();
        alternate_sprite_draw_offset = 0;
        episode_sprite_resource_table = 0;
        if (access_card_or_door_state != 0)
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x640);
        if (player_contact_state != 0)
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0xb40);
        if (actor_3020_active_state != 0)
            draw_alternate_planar_sprite(sprite_pixel_data_pointer + 0x2760);
        actor_3033_active_state = 0;

    /* These paths skip the mode-change cleanup above. */
    post_mode:
        if (level_advanced == 1)
            goto state_tail;
        if (player_level_transition_state == 0)
            goto state_c293;
        if (last_keyboard_scan_code != 0)
            goto state_tail;
        if (title_graphic_frame_index == 0)
            goto state_tail;
    /* The player_level_transition_state == 0 path joins the timed demo path here. */
    state_c293:
        if (actor_3042_hint_state == 0)
            goto state_event;
        play_level_transition_sequence();
        select_draw_page(draw_page_index);
        show_video_page(!draw_page_index);
        draw_page_index = 0;
        select_draw_page(0);
        clear_video_page();
        goto post_state_g1;
    /* Keep the event check separate from the demo-frame path. */
    state_event:
        if (last_keyboard_scan_code != 1 && last_keyboard_scan_code != 0x10)
            continue;
        while (last_keyboard_scan_code == 0x10)
            ;
    /* Shared tail keeps the timer and input exits in TC 2.0's layout. */
    state_tail:
        if (player_level_transition_state != 0)
            goto reset_c683_exit;
        if (confirm_quit_to_dos(2) == 0) {
            timer_tick_counter = 0;
            select_draw_page(draw_page_index);
            show_video_page(!draw_page_index);
            control_right_pressed = 0;
            control_down_pressed = 0;
            continue;
        }
        request_priority_sound_effect(8);
        if (level_advanced == 0) {
            if (demo_mode_state == 2)
                saved_demo_input_length = menu_selection_state;
            if (demo_mode_state == 1)
                user_demo_input_length = menu_selection_state;
        }
        draw_page_index = 0;
        select_draw_page(0);
        clear_video_page();
    /* The demo event path resumes after the state-tail checks. */
    post_state_g1:
        show_video_page(0);
        insert_score_into_high_scores();
        while ((last_keyboard_scan_code & 0x80) == 0)
            ;
        last_keyboard_scan_code = 0;
        draw_high_score_table(7);
        delay(300);
        wait_input_animated_sprite(0x1f, 0x14);
        timer_tick_counter = 0;
        demo_mode_state = 0;
    /* Shared exit is required for TC 2.0's return layout. */
    reset_c683_exit:
        player_level_transition_state = 0;
        return;
    }
}

/* start_gameplay_session candidate, attempt 2: char stub matches the observed low-byte argument setup. */
/* Initializes a gameplay session, writes its start marker, and enters the main gameplay loop
   unless cancelled. */
void pascal start_gameplay_session(void)
{
    init_player_and_level_state();
    if (!game_session_abort_flag) {
        save_game_state_to_slot('T');
        run_game_loop();
    }
}

/* Saves settings and demos, restores timer and keyboard services, returns to text mode, and
   exits to DOS. */
void shut_down_game_to_dos(void)
{
    textmode(3);
#if EPISODE == 1
    save_keyboard_bindings("KEYS.DN1");
    save_user_demo_recording("USERDEMO.DN1", saved_demo_buffer);
    save_demo_recording("MY_DEMO.DN1", user_demo_buffer);
    save_game_speed_setting("SPEED.DN1");
#elif EPISODE == 2
    save_keyboard_bindings("KEYS.dn2");
    save_user_demo_recording("USERDEMO.dn2", saved_demo_buffer);
    save_demo_recording("MY_DEMO.dn2", user_demo_buffer);
    save_game_speed_setting("SPEED.dn2");
#else
    save_keyboard_bindings("KEYS.DN3");
    save_user_demo_recording("USERDEMO.dn3", saved_demo_buffer);
    save_demo_recording("MY_DEMO.DN3", user_demo_buffer);
    save_game_speed_setting("SPEED.DN3");
#endif
    save_high_score_table();
    print_ordering_information();
    disable();
    setvect(9, saved_keyboard_interrupt_vector);
    restore_timer_interrupt_vector();
    enable();
    _exit(0);
}

/* Runs the title and main-menu state loop and dispatches the selected menu action. */
void pascal run_title_and_main_menu(void)
{
    register int menu_action;

    for (;;) {
        clear_video_page();
        menu_action = title_screen_and_menu(7);

        hint_revealed_object_7 = 0;
        hint_revealed_object_9 = 0;
        hint_revealed_object_2 = 0;
        hint_revealed_object_11 = 0;
        hint_revealed_object_10 = 0;
        hint_revealed_object_4 = 0;
        hint_revealed_object_6 = 0;
        hint_revealed_object_1 = 0;
        hint_revealed_object_5 = 0;
        transporter_hint_pending = 0;
        hint_revealed_object_3 = 0;
        hint_revealed_object_8 = 0;

        if (menu_action == 1) {
            player_level_transition_state = 0;
            demo_file_load_success = 1;
            menu_selection_state = 0;
            demo_mode_state = 1;
            restore_saved_game_requested = 0;
            clear_palette_entries(0x14);
            display_badguy_bitmap();
            restore_ega_palette(0x14);
            if (control_confirmation_state == 0) {
                while ((last_keyboard_scan_code & 0x80) == 0) {
                }
            }
            show_proton_episode_dialogue();
            clear_palette_entries(0x14);
            display_duke_bitmap();
            restore_ega_palette(0x14);
            if (control_confirmation_state == 0) {
                while ((last_keyboard_scan_code & 0x80) == 0) {
                }
            }
            show_duke_episode_dialogue();
            user_demo_recording_state = 0;
            set_palette_entries_to_23(0x14);
            if (hint_mode_enabled == 1) {
                hint_revealed_object_7 = 1;
                hint_revealed_object_9 = 1;
                hint_revealed_object_2 = 1;
                hint_revealed_object_11 = 1;
                hint_revealed_object_10 = 1;
                hint_revealed_object_4 = 1;
                hint_revealed_object_6 = 1;
                hint_revealed_object_1 = 1;
                hint_revealed_object_5 = 1;
                transporter_hint_pending = 1;
                hint_revealed_object_3 = 1;
                hint_revealed_object_8 = 1;
            }
            request_priority_sound_effect(0x1a);
            return;
        }

        if (menu_action == 2) {
            if (demo_file_load_success == 0)
                continue;
            player_level_transition_state = 1;
            demo_mode_state = 0;
            menu_selection_state = 0;
            restore_saved_game_requested = 0;
            set_palette_entries_to_23(0x14);
            return;
        }

        if (menu_action == 3 && read_restore_slot_digit(7) != 0) {
            restore_saved_game_requested = 1;
            player_level_transition_state = 0;
            demo_mode_state = 0;
            if (hint_mode_enabled == 1) {
                hint_revealed_object_7 = 1;
                hint_revealed_object_9 = 1;
                hint_revealed_object_2 = 1;
                hint_revealed_object_11 = 1;
                hint_revealed_object_10 = 1;
                hint_revealed_object_4 = 1;
                hint_revealed_object_6 = 1;
                hint_revealed_object_1 = 1;
                hint_revealed_object_5 = 1;
                transporter_hint_pending = 1;
                hint_revealed_object_3 = 1;
                hint_revealed_object_8 = 1;
            }
            return;
        }

        if (menu_action == 4) {
            player_level_transition_state = 0;
            demo_file_load_success = 1;
            menu_selection_state = 0;
            demo_mode_state = 2;
            restore_saved_game_requested = 0;
            set_palette_entries_to_23(0x14);
            return;
        }

        if (menu_action == 5) {
            if (demo_file_load_success == 0)
                continue;
            player_level_transition_state = 2;
            demo_mode_state = 0;
            menu_selection_state = 0;
            restore_saved_game_requested = 0;
            set_palette_entries_to_23(0x14);
            return;
        }

        if (menu_action == 0) {
            clear_palette_entries(0x14);
            shut_down_game_to_dos();
            continue;
        }
    }
}

/* Parses the command-line options, initializes the game, and repeatedly runs the menu and
   gameplay session. */
void main(int argc, char **argv)
{
    if (argv[1][0] == 'a' && argv[1][1] == 's' && argv[1][2] == 'p') {
        demo_mode_enabled = 1;
        if (argv[2][0] == 'g')
            chain_keyboard_interrupt = 1;
    }
    init_video_keyboard_and_assets();
    for (;;) {
        run_title_and_main_menu();
        start_gameplay_session();
        clear_palette_entries(15);
        game_session_abort_flag = 0;
    }
}

