/* DUKE.H - declarations shared by both translation units of Duke Nukum v2.0.

   Names are logical ids: g1_XXXX / g2_XXXX / asm_XXXX are functions at frame
   offset XXXX in DN1; d_XXXX is the global at DN1 DGROUP offset XXXX, d_XXXX_ an
   uninitialised (BSS) one.  Turbo C orders a unit's BSS by a hash of the name,
   ties by first appearance (docs: rule BSS-ORDER): the BSS declarations below
   are therefore kept in address order. */

#ifndef DUKE_H
#define DUKE_H

#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloc.h>
#include <conio.h>

/* ---- data structures ---- */

/* Stores the display string used to label a keyboard scan code or configured key. */
struct keyboard_character_map_entry { char display_label[7]; };
/* Returns the two sampled joystick-button states; the first integer is not assigned by the
   current reader. */
struct joystick_button_sample {
    int reserved_value;
    int first_button_pressed;
    int second_button_pressed;
};
/* Stores one moving world actor's state, world position, and contact marker. */
struct world_actor_record { int state, world_x, world_y, contact_marker; };
/* Stores one projectile's active state, world position, and marker value. */
struct projectile_record { int active, world_x, world_y, projectile_marker; };
/* Stores the vertical displacement sequence selected by the player's jump state. */
struct player_jump_motion_row { unsigned char vertical_displacements[12]; };
/* Stores a short-lived collision-effect animation state and its world position. */
struct collision_effect_record { int active, world_x, world_y; };
/* Stores an ambient sprite effect's active flag, world position, and sprite-resource offset. */
struct ambient_object_record { int active, world_x, world_y, sprite_offset; };
/* Stores a moving actor's state, world position, and actor kind. */
struct moving_actor_record { int state, world_x, world_y, actor_kind; };
/* Stores a pickup object's active flag and world position. */
struct pickup_object_record { int active, world_x, world_y; };
/* Stores an animated actor's frame index and vertical position. */
struct animated_actor_pool_record { int animation_state, sprite_frame_index, vertical_position; };
/* Stores the active contact-flash state, four world-coordinate pairs, and their sprite offsets. */
struct contact_flash_effect_record { int effect_values[15]; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3000. */
struct actor_3000_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3001. */
struct actor_3001_record { int active, world_x, world_y; };
/* Stores map coordinates, object height, state, and one reserved word for marker type 0x3002. */
struct actor_3002_record {
    int reserved;
    int map_column;
    int map_row;
    int object_height;
    int object_state;
};
/* Stores world coordinates and type-specific data for level objects created from marker 0x3007. */
struct actor_3007_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3009. */
struct actor_3009_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x300A. */
struct actor_300a_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x300B. */
struct actor_300b_record { int motion_state; int world_x; int world_y; int trajectory_step; };
/* Stores the six sprite-resource offsets for a two-column by three-row actor graphic. */
struct actor_tile_graphic_offsets { int top_left_sprite_offset, top_right_sprite_offset, middle_left_sprite_offset, middle_right_sprite_offset, bottom_left_sprite_offset, bottom_right_sprite_offset; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x300C. */
struct actor_300c_record { int state, world_x, world_y, marker_state; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x300D. */
struct actor_300d_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x300E. */
struct actor_300e_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x300F. */
struct actor_300f_record { int active, world_x, world_y, animation_state; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3010. */
struct actor_3010_record { int state, world_x, world_y, animation_phase; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3012. */
struct actor_3012_record {
    int state;
    int world_x;
    int world_y;
    int object_kind;
    int unknown_flag_8;
    int unknown_flag_10;
};
/* Stores world coordinates and type-specific data for level objects created from marker 0x3014. */
struct actor_3014_record { int world_x; int world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3015. */
struct actor_3015_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3016. */
struct actor_3016_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3018. */
struct actor_3018_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x301A. */
struct actor_301a_record { int world_x, world_y, active; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x301B. */
struct actor_301b_record { int state, world_x, world_y, animation_count; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x301D. */
struct actor_301d_record { int active, world_x, world_y, animation_state; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x301E. */
struct actor_301e_record { int state, world_x, world_y, animation_flag; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x301F. */
struct actor_301f_record { int state, world_x, world_y, animation_flag; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3021. */
struct actor_3021_record { int world_x, world_y; };
/* Stores type 0x3022 actor movement, position, health, and movement counters. */
struct actor_3022_record { int movement_state, world_x, world_y, jump_timer, hit_points, fall_counter; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3023. */
struct actor_3023_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3024. */
struct actor_3024_record { int state, world_x, world_y; };
/* Stores a sprite-resource offset and world position for one animated level tile. */
struct animated_level_tile_record { int sprite_resource_offset; int world_x; unsigned int world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3029. */
struct actor_3029_record { int state, world_x; unsigned int world_y; };
/* Stores the state and world position of one level-object type 0x302a record. */
struct actor_302a_record {
    int state;
    int world_x;
    int world_y;
};
/* Stores world coordinates and type-specific data for level objects created from marker 0x302C. */
struct actor_302c_record { int world_x; int world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x302D. */
struct actor_302d_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x302E. */
struct actor_302e_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3031. */
struct actor_3031_record { int state, world_x, world_y; };
/* Stores the active flag and world position of one falling hazard. */
struct falling_hazard_record { int active; int world_x; int world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3037. */
struct actor_3037_record { int state, world_x, world_y, animation_flag; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x303B. */
struct actor_303b_record { int state, world_x, world_y, object_kind; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x303C. */
struct actor_303c_record { int state, world_x, world_y; };
/* Stores world coordinates and type-specific data for level objects created from marker 0x3044. */
struct actor_3044_record { int state, world_x, world_y; };
/* Stores sprite offset, world position, and alternate-frame state for animated tiles and marker
   0x3048 objects. */
struct level_tile_animation_record { int sprite_resource_offset, world_x, world_y, alternate_frame; };
/* Stores a sprite-resource offset and world position for one marker 0x3058 object. */
struct actor_3058_record {
    int sprite_resource_offset;
    int world_x;
    int world_y;
};
/* Stores the two adjacent tile values examined by a level-map collision check. */
struct level_map_cell_pair { unsigned int first_tile_value, second_tile_value; };
/* Stores words from a primary sound-bank index record; the loader reads its offsets and priority
   fields. */
struct sound_bank_index_record { unsigned int index_words[8]; };

/* ---- functions of the first unit (GAME1.C) ---- */

void pascal draw_text_character(char a0, int a1, int a2);
void pascal request_priority_sound_effect(int a0);
void select_joystick_configuration(int a);
void pascal handle_game_setup_input(int a0);
unsigned char pascal read_restore_slot_digit(int a0);
void pascal save_game_state_to_slot(char a0);
char pascal prompt_and_save_game(int a0);
void pascal handle_in_game_help_menu(int a0);
int pascal poll_player_controls_and_events(int a0);
void pascal read_text_entry(volatile int a2, volatile int a1, char far *a0);
void insert_score_into_high_scores(void);
void draw_title_screen_graphic(void);
void advance_title_screen_animation(void);
void draw_buffered_screen_effect(void);
void pascal add_and_draw_player_score(long value);
struct joystick_button_sample configure_joystick_axes(int mode);
void calibrate_joystick_controls(int a0, int a1);
int read_joystick_button(void);
void wait_joystick_button_release(void);
void update_joystick_axis_state(void);
void pascal load_planar_image_file(char far *filename, int offset, int count);
char test_player_floor_clearance(void);
unsigned char test_player_body_clearance(void);
char test_player_head_clearance(void);
char test_player_level_clearance(void);
void draw_animated_level_strip(void);
void interrupt keyboard_interrupt_handler(void);
void draw_player_action_sprite(int a0, int a1, int a2);
void pascal spawn_world_actor(int a0, int a1, int a2);
void update_moving_world_effects(void);
void pascal clear_projectile_pool_051c(void);
void pascal update_projectile_pool_051c(int a0, int a1, int a2);
void resolve_projectile_collisions(void);
void update_player_and_level_state(void);
void advance_player_transition(void);
void read_file_block(char far *filename, void far *buffer, unsigned int count);
void pascal allocate_collision_record(int a0, int a1);
void pascal clear_ambient_object_pool(void);
void pascal queue_ambient_sprite_animation(int a0, int a1, int a2);
void animate_ambient_sprite_records(void);
void pascal spawn_moving_actor(int a0, int a1, int a2);
void update_moving_actor_pool(void);
void pascal spawn_pickup_object(int a0, int a1);
void update_pickup_object_pool(void);
void update_collision_effect_pool(void);
void pascal spawn_animated_actor_sprite(int a0, int a1);
void pascal draw_actor_sprite_pair(int a0, int a1, int a2);
void update_animated_actor_pool(void);
void pascal spawn_contact_flash_effect(int a0, int a1);
char pascal is_world_position_outside_view(int a0, int a1);
void animate_contact_flash_effects(void);
int test_player_overlap_with_object(int a0, int a1);
char pascal remove_world_actor_at_position(int a0, int a1);
int test_player_vertical_range(int a0, int a1, int a2);
int test_player_x_alignment(int a0, int a1);
int test_level_tile_special_state(int a0, int a1);
int is_level_position_blocked(int a0, int a1);
void update_actor_3000(void);
void update_actor_3001(void);
void update_actor_3002(void);
void update_actor_3006(void);
void update_actor_3007(void);
void update_actor_3008(void);
void update_actor_3009(void);
void update_actor_300a(void);
void update_actor_300b(void);
void pascal draw_six_tile_actor_sprite(int a2, int p1, int a0);
void update_actor_300c(void);
void pascal draw_two_tile_wide_actor_sprite(int a0, int a1, int a2);
void update_actor_300d(void);
void update_actor_3020(void);
void update_actor_3033(void);
void pascal draw_two_by_two_actor_sprite(int a0, int a1, int a2);
void update_actor_300e(void);
void update_actor_300f(void);
void update_actor_3010(void);
void pascal draw_two_by_two_actor_variant(int a0, int a1, int a2);
void handle_door_and_key_interaction(void);
void update_actor_3012(void);
void update_actor_3013(void);
void update_actor_3014(void);
void update_actor_3015(void);
void update_actor_3016(void);
void update_actor_3018(void);
void update_actor_3019(void);
void update_actor_301a(void);
void pascal draw_two_tile_tall_actor_sprite(int row, int horizontal, int vertical);
void update_actor_301b(void);
void update_actor_301d(void);
void update_actor_301e(void);
void update_actor_301f(void);
void update_actor_3021(void);
void pascal draw_four_wide_actor_sprite(int a0, int a1, int a2);
void pascal draw_wide_actor_sprite(int a0, int a1, int a2);
void update_actor_3022(void);
void update_actor_3023(void);
void update_actor_3024(void);
void draw_animated_level_tile(void);
void update_actor_3029(void);
void update_actor_302a(void);
void update_actor_302b(void);
void update_actor_302c(void);
void update_actor_302d(void);
void update_actor_302e(void);
void pascal draw_level_object_animation(int a2, int a1, int a0);
void activate_actor_302f(void);
void activate_actor_3030(void);
void update_actor_3031(void);
void update_falling_hazards(void);
void update_actor_3034(void);
void update_actor_3035(void);
void update_secret_block_state(void);
void update_actor_3037(void);
void pascal draw_climbing_actor_sprite(int a0, int a1, int a2);
void update_actor_303b(void);
void pascal draw_tall_effect_sprite(int a2, int a1, int a0);
void update_actor_303c(void);
void wait_for_level_start(void);
void update_actor_3040(void);
void pascal draw_actor_sprite_by_variant(int a0, int a1, int a2);
void update_actor_3042(void);
void pascal draw_large_actor_sprite(int a0, int a1, int a2);
void update_level_lock_or_exit(void);
void pascal draw_level_marker_tiles(void);
void update_actor_3044(void);
void update_actor_3048(void);
void animate_level_tile_records(void);
void draw_marker_3058_objects(void);
void pascal register_level_update_callback(void(far *key)(void));
void pascal create_objects_from_level_map(unsigned int a0);
void load_level_tile_map(char far *filename);
void load_user_demo_recording(char far *filename, char far *buffer);
void load_saved_demo_recording(char far *filename, char far *buffer);
void save_user_demo_recording(char far *filename, void far *buffer);
void save_demo_recording(char far *filename, void far *buffer);
void allocate_game_buffers_and_state(void);
void pascal load_level_and_init_objects(char far *a0);
void init_player_and_level_state(void);
void check_minimum_available_memory(void);
void pascal load_game_speed_setting(char far *filename);
void pascal save_game_speed_setting(char far *filename);
void pascal wait_for_timer_ticks(int n);
void play_level_transition_sequence(void);
void pascal init_video_keyboard_and_assets(void);
void run_game_loop(void);
void pascal start_gameplay_session(void);
void shut_down_game_to_dos(void);
void pascal run_title_and_main_menu(void);

/* ---- functions of the second unit (GAME2.C) ---- */

void pascal set_palette_entries_to_23(int a0);
void pascal restore_ega_palette(int a0);
void pascal clear_palette_entries(int value);
void select_and_show_video_page(void);
void pascal sample_joystick_axes(int mode, int far *a1, int far *a2);
void pascal clear_video_page_region(int a0);
void show_ordering_page_one(void);
void show_ordering_page_two(void);
void show_story_game_instructions(void);
void show_save_success_message(void);
void show_save_failure_message(void);
void show_save_unavailable_message(void);
void show_secret_tip_card_key(void);
void show_secret_tip_read_notes(void);
void show_secret_tip_elevator(void);
void pascal toggle_sound_setting(int a0);
void pascal toggle_hint_mode(int a0);
void pascal pause_until_resume_input(int a0);
void pascal prompt_for_save_slot(int a0);
void pascal prompt_for_restore_slot(int a0);
void restore_timer_interrupt_vector(void);
void pascal wait_for_keyboard_or_joystick(int a0, int a1);
void draw_get_ready_message(void);
void pascal draw_game_setup_menu(int a0);
void confirm_level_restart(void);
void show_secret_tip_soda(void);
void show_secret_tip_turkey(void);
void show_secret_tip_nuclear(void);
void show_secret_tip_open_door(void);
void show_secret_tip_robohand(void);
void show_secret_tip_access_card(void);
void show_secret_tip_transporter(void);
void pascal draw_keyboard_binding_values(int a0);
void pascal draw_in_game_help_menu(int a0);
void show_secret_tip_insert_card(void);
void show_secret_tip_lock_key(void);
void pascal show_save_location_warning(int a0);
void pascal show_keyboard_controls_help(int a0);
void pascal draw_high_score_table(int a0);
void save_high_score_table(void);
void install_timer_interrupt(void);
void pascal show_instruction_screen(int a0);
void show_loading_status(void);
void pascal show_joystick_mode_status(int a0);
void draw_current_planar_sprite(void);
void pascal draw_alternate_planar_sprite(char far *bitmap);
void save_keyboard_bindings(char far *filename);
void load_keyboard_bindings(char far *filename);
void pascal restore_game_state_from_slot(char a0);
void draw_high_score_name_screen(void);
void wait_controller_button(void);
void load_high_score_table(void);
void detect_joystick_connection(void);
void interrupt timer_sound_interrupt_handler(void);
void show_episode_story_intro(void);
char normalize_extended_key_code(void);
void pascal draw_unsigned_score_value(long value, int x, int page);
void pascal wait_input_animated_sprite(int a0, int a1);
void draw_video_page_template(void);
void draw_page_frame_template(void);
void pascal draw_text_panel_background(int a0);
void pascal draw_text_at_video_address(char x, char y, char far *text, char attribute);
void print_ordering_information(void);
void pascal load_credits_graphics(char far *filename);
void clear_video_page(void);
void display_credits_bitmap(void);
void pascal load_episode_graphics_b638(char far *filename);
void display_episode_bitmap_b638(void);
void pascal load_badguy_graphics(char far *filename);
void display_badguy_bitmap(void);
void pascal load_duke_graphics(char far *filename);
void display_duke_bitmap(void);
void pascal load_ending_graphics(char far *filename);
void display_ending_bitmap(void);
void pascal draw_text_string(char far *text, int x, int y);
void pascal draw_text_character_at_position(char a0, int a1, int a2);
void pascal draw_main_menu(int a0);
void pascal load_primary_sound_bank(char far *filename);
void pascal load_secondary_sound_bank(char far *filename);
void show_credit_screen(void);
void draw_planar_sprite_frame(void);
void show_proton_episode_dialogue(void);
void show_duke_episode_dialogue(void);
void show_player_death_message(void);
void show_cheat_mode_message(void);
#if UNIT == 1
int pascal confirm_quit_to_dos(int);
#else
void pascal confirm_quit_to_dos(int a0);
#endif
void pascal draw_framed_dialog_box(int a2, int a1, int a0);
void animate_credits_scroll(void);
void wait_for_pause_key_release(void);
void show_instructions_heading(void);
void pascal remap_keyboard_action(int a0);
void pascal draw_keyboard_mode_settings(int a0);
void show_proton_level_end_dialogue(void);
void show_proton_transition_dialogue(void);
void show_proton_future_dialogue(void);
void show_duke_level_end_dialogue(void);
void show_game_completion_message(void);
void pascal prompt_joystick_calibration(int a0);
void pascal show_next_episode_promotion(int a0);

/* ---- ProGraphx EGA/VGA Toolbox (TOOLBOX.ASM) ---- */

void set_video_mode(int);
void set_vga_mode_with_parameters(int, int);
void blit_bitmap_to_video_page(int, int);
void copy_planar_video_region(int, int, int);
void blit_planar_sprite_rows(char far*, int, int);
void draw_ega_glyph(char far*, int, int);
void blit_planar_masked_glyph(char far*, int, int);
void select_draw_page(int);
void show_video_page(int);

/* ---- runtime library functions declared without their header ---- */

extern int abs(int);

/* ---- names of the uninitialised globals ----
   Turbo C 2.0 lays out a unit's uninitialised data by a hash of each name
   (first character + 4 * last character + 32 * length, mod 1024; equal hashes
   in order of first appearance).  The original names are lost, so the objects
   keep storage names that all hash alike (d_ + DN1 address + _) and therefore
   lie in declaration order; the program refers to them by these names. */
#define game_speed_setting              d_4ed0_
#define current_weapon_state            d_4ed2_
#define title_graphic_frame_index       d_4ed4_
#define level_play_state                d_4ed6_
#define hidden_object_state             d_4ed8_
#define actor_300e_object_state_table   d_4eda_
#define high_score_values               d_4fa2_
#define high_score_entry_1_alias        d_4fa6_
#define high_score_entry_2_alias        d_4faa_
#define high_score_entry_3_alias        d_4fae_
#define high_score_entry_4_alias        d_4fb2_
#define sound_effect_priority_table     d_4fce_
#define secondary_sound_priority_table  d_4fe6_
#define secret_block_state              d_5000_
#define player_animation_lock_state     d_5002_
#define level_hazard_count              d_5004_
#define level_loading_state             d_5006_
#define high_score_player_names         d_5008_
#define high_score_name_edit_buffer     d_5076_
#define actor_300c_object_marker_table  d_5081_
#define actor_3035_state                d_5149_
#define level_update_callback_table     d_514b_
#define actor_3035_animation_state      d_52db_
#define projectile_records              d_52dd_
#define credits_text_position           d_5305_
#define actor_3035_active_state         d_5307_
#define actor_3037_object_count         d_5309_
#define pending_sound_priority_flag     d_530b_
#define actor_3037_animation_state      d_530c_
#define user_demo_recording_state       d_530e_
#define secret_block_collision_state    d_530f_
#define actor_3013_formation_state      d_5310_
#define actor_303b_update_state         d_5312_
#define exit_lock_animation_state       d_5314_
#define secret_block_animation_state    d_5316_
#define game_session_abort_flag         d_5318_
#define actor_3048_object_count         d_5319_
#define pending_sound_effect_index      d_531b_
#define actor_302a_update_state         d_531c_
#define level_object_pool_531e_count    d_531e_
#define level_collision_sound_records   d_5320_
#define animated_actor_pool_records     d_551e_
#define actor_3048_entity_count         d_5548_
#define actor_3042_interaction_state    d_554a_
#define selected_save_slot              d_554c_
#define keyboard_hotkey_count           d_554d_
#define control_hint_up_flag            d_554f_
#define control_hint_down_flag          d_5550_
#define control_hint_left_flag          d_5551_
#define control_hint_right_flag         d_5552_
#define hint_revealed_object_1          d_5553_
#define hint_revealed_object_2          d_5554_
#define hint_revealed_object_3          d_5555_
#define saved_keyboard_interrupt_vector d_5556_
#define hint_revealed_object_4          d_555a_
#define hint_revealed_object_5          d_555b_
#define hint_revealed_object_6          d_555c_
#define actor_3012_records              d_555d_
#define user_demo_buffer                d_5a0d_
#define hint_revealed_object_7          d_5a11_
#define actor_3015_records              d_5a12_
#define hint_revealed_object_8          d_5c6a_
#define hint_revealed_object_9          d_5c6b_
#define falling_hazard_records          d_5c6c_
#define player_sprite_resource_buffer   d_5ec4_
#define hint_revealed_object_10         d_5ec8_
#define actor_3022_records              d_5ec9_
#define active_sprite_draw_flag         d_6379_
#define sprite_graphics_buffer          d_637a_
#define hint_revealed_object_11         d_637e_
#define actor_300b_records              d_637f_
#define actor_3000_records              d_669f_
#define transporter_hint_pending        d_68f7_
#define player_score                    d_68f8_
#define actor_3024_records              d_68fc_
#define font_glyph_data_buffer          d_6b54_
#define actor_3044_records              d_6b58_
#define actor_3007_records              d_6bb2_
#define draw_page_index                 d_6e0a_
#define actor_302e_records              d_6e0b_
#define actor_3029_records              d_7063_
#define actor_3014_records              d_70db_
#define actor_3021_records              d_726b_
#define actor_303b_records              d_73fb_
#define keyboard_key_d_pressed          d_771b_
#define joystick_x_axis_threshold_low   d_771c_
#define joystick_y_axis_threshold_low   d_7722_
#define keyboard_key_g_pressed          d_7728_
#define level_tile_map                  d_7729_
#define keyboard_key_o_pressed          d_772d_
#define actor_3009_records              d_772e_
#define vga_lower_page_pointer          d_7986_
#define access_card_or_door_state       d_798a_
#define actor_301b_records              d_798c_
#define actor_3023_records              d_7cac_
#define actor_3034_active_state         d_7f04_
#define animated_level_tile_records     d_7f06_
#define joystick_x_axis_threshold_high  d_9676_
#define joystick_y_axis_threshold_high  d_967c_
#define alternate_sprite_draw_offset    d_9682_
#define saved_demo_buffer               d_9684_
#define actor_302c_records              d_9688_
#define actor_301f_records              d_9818_
#define episode_sprite_resource_table   d_9b38_
#define actor_300a_records              d_9b3a_
#define actor_3040_world_x              d_9d92_
#define actor_3040_world_y              d_9d94_
#define actor_3034_world_x              d_9d96_
#define fire_button_latch               d_9d98_
#define actor_301d_records              d_9d99_
#define actor_3034_world_y              d_a0b9_
#define duke_graphics_buffer            d_a0bb_
#define actor_3037_records              d_a0bf_
#define object_sprite_buffer            d_a0ef_
#define jump_button_latch               d_a0f3_
#define previous_timer_interrupt_vector d_a0f4_
#define player_contact_state            d_a0f8_
#define last_keyboard_scan_code         d_a0fa_
#define sprite_pixel_data_pointer       d_a0fb_
#define actor_300d_records              d_a0ff_
#define actor_301e_records              d_a357_
#define actor_3040_active_state         d_a677_
#define player_sprite_refresh_state     d_a679_
#define actor_3008_world_x              d_a67b_
#define keyboard_backspace_pressed      d_a67d_
#define actor_3008_world_y              d_a67e_
#define actor_303c_records              d_a680_
#define sound_interrupt_active_state    d_a8d8_
#define keyboard_interrupt_state        d_a8d9_
#define actor_3001_records              d_a8da_
#define actor_300f_records              d_ab32_
#define formation_active_object_count   d_abd2_
#define formation_object_x_positions    d_abd4_
#define formation_world_x_accumulator   d_abe6_
#define formation_x_auxiliary_bytes     d_abe8_
#define actor_300e_records              d_abec_
#define actor_3031_records              d_ae44_
#define formation_object_y_positions    d_b09c_
#define formation_world_y_accumulator   d_b0ae_
#define formation_y_auxiliary_bytes     d_b0b0_
#define actor_3010_records              d_b0b4_
#define actor_3033_active_state         d_b3d4_
#define actor_301a_records              d_b3d6_
#define actor_3019_world_x              d_b62e_
#define actor_3042_world_x              d_b630_
#define actor_3019_world_y              d_b632_
#define actor_3042_world_y              d_b634_
#define formation_update_enabled        d_b636_
#define episode_graphics_buffer         d_b638_
#define moving_actor_records            d_b63c_
#define actor_300c_records              d_b6bc_
#define ending_sequence_enabled         d_b9dc_
#define level_tile_animation_records    d_b9de_
#define actor_3018_records              d_c01e_
#define actor_3041_world_x              d_c276_
#define demo_file_load_success          d_c278_
#define actor_302f_world_x              d_c279_
#define actor_3030_world_x              d_c27b_
#define badguy_graphics_buffer          d_c27d_
#define actor_3019_enabled              d_c281_
#define actor_3042_active_state         d_c283_
#define credits_graphics_buffer         d_c285_
#define actor_3041_world_y              d_c289_
#define actor_302f_world_y              d_c28b_
#define actor_3030_world_y              d_c28d_
#define ending_graphics_buffer          d_c28f_
#define actor_3042_hint_state           d_c293_
#define world_actor_count               d_c295_
#define joystick_configuration_mode     d_c297_
#define actor_3002_records              d_c299_
#define actor_3041_active_state         d_c681_
#define player_level_transition_state   d_c683_
#define actor_302f_active_state         d_c684_
#define actor_302f_interaction_phase    d_c686_
#define actor_3030_active_state         d_c688_
#define actor_302f_animation_phase      d_c68a_
#define control_up_pressed              d_c68c_
#define actor_302b_world_x              d_c68d_
#define actor_302b_world_y              d_c68f_
#define actor_302a_records              d_c691_
#define actor_302b_active_state         d_c8e9_
#define object_collision_pool_records   d_c8eb_
#define actor_302d_records              d_c915_
#define world_actor_records             d_cb6d_
#define sound_sample_pointer_table      d_cbb5_
#define vga_upper_page_pointer          d_cc7d_
#define control_confirmation_state      d_cc81_
#define actor_3020_active_state         d_cc82_
#define actor_3058_records              d_cc84_
#define control_down_pressed            d_d134_
#define control_fire_pressed            d_d135_
#define actor_3019_width                d_d136_
#define control_jump_pressed            d_d138_
#define actor_302f_interaction_state    d_d139_
#define actor_3030_interaction_state    d_d13b_
#define actor_3035_world_x              d_d13d_
#define control_left_pressed            d_d13f_
#define actor_3035_world_y              d_d140_
#define actor_3042_animation_counter    d_d142_
#define player_sprite_animation_index   d_d144_
#define actor_3041_interaction_state    d_d146_
#define keyboard_control_lock_state     d_d148_
#define secret_code_character_0         d_d149_
#define secret_code_character_1         d_d14b_
#define secret_code_character_2         d_d14d_
#define secret_code_input_buffer        d_d14f_
#define actor_3019_animation_state      d_d155_
#define actor_3048_records              d_d157_
#define free_object_pool_records        d_d1cf_
#define player_gameplay_state           d_d247_
#define formation_object_active_flags   d_d249_
#define actor_3016_records              d_d261_
#define actor_3019_screen_x             d_d4b9_
#define actor_3019_map_row              d_d4bb_
#define door_lock_world_x               d_d4bd_
#define player_projectile_state         d_d4bf_
#define control_right_pressed           d_d4c0_
#define door_lock_world_y               d_d4c1_
#define ambient_object_records          d_d4c3_
#define joystick_enabled                d_d56b_
#define actor_3042_open_state           d_d56c_
#define actor_302b_animation_counter    d_d56e_
#define door_or_key_interaction_state   d_d570_
#define actor_302b_open_state           d_d572_
#define secret_block_world_x            d_d574_
#define player_invulnerability_state    d_d576_
#define secret_block_world_y            d_d577_
#define current_sound_priority          d_d579_
#define actor_3037_bonus_state          d_d57a_
#define level_progress_word             d_d57c_
#define actor_300d_auxiliary_states     d_d57e_
#define actor_3001_tile_below_records   d_d646_
#define actor_3044_entity_count         d_d70e_
#define secondary_sound_bank_buffer     d_d710_
#define primary_sound_bank_buffer       d_d714_
#define bios_timer_chain_divider        d_d718_

/* ---- global data (by DN1 DGROUP offset) ---- */

extern char menu_action_state;               /* Stores the menu action selected by the main-menu input handler. */
extern int demo_mode_enabled;  /* Enables demo-mode behavior when the matching command-line option is present. */
extern char sound_enabled;                   /* Stores whether PC-speaker sound playback is enabled. */
extern char demo_mode_state;                 /* Selects the active demo playback or recording mode. */
extern int player_screen_x;                  /* Stores the player's horizontal screen coordinate. */
extern int player_screen_y;                  /* Stores the player's vertical screen coordinate. */
extern int level_scroll_x;  /* Stores the horizontal world-map scroll offset added to the player's screen coordinate. */
extern int level_map_y_offset;               /* Stores the vertical level-map scroll offset. */
/* Maps keyboard scan codes to the display strings used by text input and the key-binding menu. */
extern struct keyboard_character_map_entry keyboard_character_map_entries[];
/* Maps level-tile values to the tile behavior used by collision and interaction checks. */
extern int level_tile_attribute_table[];
/* The header declares this integer array, but the checked-in GAME1 and GAME2 sources do not
   reference it, so its role is unknown. */
extern int unreferenced_integer_table[];
extern char key_binding_up;                  /* Stores the scan code assigned to the up action. */
extern char key_binding_down;                /* Stores the scan code assigned to the down action. */
extern char key_binding_left;                /* Stores the scan code assigned to the left action. */
extern char key_binding_right;               /* Stores the scan code assigned to the right action. */
extern char key_binding_fire;                /* Stores the scan code assigned to the fire action. */
extern char key_binding_jump;                /* Stores the scan code assigned to the jump action. */
#if UNIT == 1
/* Selects the current level entry in the episode filename table; GAME1 and GAME2 declare
   different integer widths. */
extern char current_level_index;
#else
/* Selects the current level entry in the episode filename table; GAME1 and GAME2 declare
   different integer widths. */
extern int current_level_index;
#endif
extern int timer_tick_counter;               /* Counts timer interrupts for gameplay waits and timing checks. */
/* Provides the horizontal displacement values used by the moving enemy formation. */
extern int formation_x_delta_table[];
/* Provides the vertical displacement values used by the moving enemy formation. */
extern int formation_y_delta_table[];
/* When set, the keyboard interrupt handler chains scan codes to the previously installed vector. */
extern int chain_keyboard_interrupt;
extern int credit_scroll_delay;              /* Controls the delay between updates while credits text scrolls. */
extern int title_graphic_animation_state;    /* Tracks the current state of title graphic animation. */
extern char restore_saved_game_requested;    /* Requests restoration of the selected saved game during level entry. */
/* Holds episode-specific level-map filenames selected by the current level index. */
extern char far *episode_level_filename_table[];
extern int menu_selection_state;             /* Tracks the current state of menu selection. */
extern int user_demo_input_length;  /* Stores the number of recorded input bytes available in the user-demo buffer. */
extern int saved_demo_input_length;  /* Stores the number of recorded input bytes available in the saved-demo buffer. */
extern int actor_motion_delta_table[];       /* Provides per-step position changes for animated actor records. */
extern char interaction_cooldown_state;      /* Tracks the current state of interaction cooldown. */
extern int world_animation_phase;  /* Tracks the current animation or interaction phase for world animation. */
extern char player_death_state;              /* Tracks the current state of player death. */
extern char player_action_state;             /* Tracks the current state of player action. */
extern char player_animation_phase;  /* Tracks the current animation or interaction phase for player animation. */
extern int actor_3000_count;  /* Stores the current count or capacity for level object marker 0x3000 records. */
extern int collision_sound_record_count;  /* Stores the current count or capacity for collision sound record records. */
/* Provides coordinate changes used to animate the first pair of contact-flash points. */
extern int contact_flash_delta_table_a[];
/* Provides coordinate changes used to animate the second pair of contact-flash points. */
extern int contact_flash_delta_table_b[];
/* Provides coordinate changes used to animate the third pair of contact-flash points. */
extern int contact_flash_delta_table_c[];
/* Provides coordinate changes used to animate the fourth pair of contact-flash points. */
extern int contact_flash_delta_table_d[];
extern int ambient_object_count;             /* Stores the current count or capacity for ambient object records. */
extern int animated_actor_count;             /* Stores the current count or capacity for animated actor records. */
extern int projectile_count;                 /* Stores the current count or capacity for projectile records. */
extern int moving_object_count;              /* Stores the current count or capacity for moving object records. */
extern int pickup_object_count;              /* Stores the current count or capacity for pickup object records. */
extern int moving_actor_count;               /* Stores the current count or capacity for moving actor records. */
extern int actor_3001_count;  /* Stores the current count or capacity for level object marker 0x3001 records. */
extern int actor_3002_count;  /* Stores the current count or capacity for level object marker 0x3002 records. */
extern int actor_3006_world_x;  /* Stores the X-coordinate or X-related value for level object marker 0x3006 world. */
extern int actor_3006_world_y;  /* Stores the Y-coordinate or Y-related value for level object marker 0x3006 world. */
extern int actor_3006_state;                 /* Tracks the current state of level object marker 0x3006. */
extern int actor_3008_state;                 /* Tracks the current state of level object marker 0x3008. */
extern int actor_3020_world_x;  /* Stores the X-coordinate or X-related value for level object marker 0x3020 world. */
extern int actor_3020_world_y;  /* Stores the Y-coordinate or Y-related value for level object marker 0x3020 world. */
extern int actor_3020_state;                 /* Tracks the current state of level object marker 0x3020. */
extern int actor_3033_world_x;  /* Stores the X-coordinate or X-related value for level object marker 0x3033 world. */
extern int actor_3033_world_y;  /* Stores the Y-coordinate or Y-related value for level object marker 0x3033 world. */
extern int actor_3033_state;                 /* Tracks the current state of level object marker 0x3033. */
extern int actor_3033_enabled;               /* Tracks whether level object marker 0x3033 is active. */
extern int actor_3007_count;  /* Stores the current count or capacity for level object marker 0x3007 records. */
extern int actor_3009_count;  /* Stores the current count or capacity for level object marker 0x3009 records. */
extern int actor_300a_count;  /* Stores the current count or capacity for level object marker 0x300A records. */
extern int actor_300b_count;  /* Stores the current count or capacity for level object marker 0x300B records. */
/* Stores paired horizontal and vertical movement deltas for one moving-item trajectory. */
extern int moving_item_path_delta_table_a[];
/* Stores paired horizontal and vertical movement deltas for a second moving-item trajectory. */
extern int moving_item_path_delta_table_b[];
extern int actor_300b_screen_anim_offset;  /* Stores the current sprite or map offset for marker 0x300B screen anim. */
/* Selects the animation frame for the object records created from marker type 0x300B. */
extern int actor_300b_animation_frame;
extern int actor_300c_count;  /* Stores the current count or capacity for level object marker 0x300C records. */
extern int actor_300d_count;  /* Stores the current count or capacity for level object marker 0x300D records. */
extern int actor_300e_animation_state;       /* Tracks the current state of marker 0x300E animation. */
extern int actor_300e_animation_counter;     /* Counts updates for marker 0x300E animation. */
extern int actor_300e_count;  /* Stores the current count or capacity for level object marker 0x300E records. */
extern int actor_300f_count;  /* Stores the current count or capacity for level object marker 0x300F records. */
extern int actor_3010_count;  /* Stores the current count or capacity for level object marker 0x3010 records. */
extern int actor_3012_count;  /* Stores the current count or capacity for level object marker 0x3012 records. */
extern int actor_3014_count;  /* Stores the current count or capacity for level object marker 0x3014 records. */
extern int actor_3015_count;  /* Stores the current count or capacity for level object marker 0x3015 records. */
extern int actor_3016_count;  /* Stores the current count or capacity for level object marker 0x3016 records. */
extern int actor_3018_count;  /* Stores the current count or capacity for level object marker 0x3018 records. */
extern int actor_301a_count;  /* Stores the current count or capacity for level object marker 0x301A records. */
extern int actor_301b_count;  /* Stores the current count or capacity for level object marker 0x301B records. */
extern int actor_301d_count;  /* Stores the current count or capacity for level object marker 0x301D records. */
extern int actor_301e_count;  /* Stores the current count or capacity for level object marker 0x301E records. */
extern int actor_301f_count;  /* Stores the current count or capacity for level object marker 0x301F records. */
extern int actor_3021_count;  /* Stores the current count or capacity for level object marker 0x3021 records. */
extern int actor_3022_count;  /* Stores the current count or capacity for level object marker 0x3022 records. */
extern int actor_3023_count;  /* Stores the current count or capacity for level object marker 0x3023 records. */
extern int actor_3024_count;  /* Stores the current count or capacity for level object marker 0x3024 records. */
extern int actor_3025_count;  /* Stores the current count or capacity for level object marker 0x3025 records. */
extern int actor_3029_count;  /* Stores the current count or capacity for level object marker 0x3029 records. */
extern int actor_302a_count;  /* Stores the current count or capacity for level object marker 0x302A records. */
extern int actor_302c_count;  /* Stores the current count or capacity for level object marker 0x302C records. */
extern int actor_302d_count;  /* Stores the current count or capacity for level object marker 0x302D records. */
extern int actor_302e_count;  /* Stores the current count or capacity for level object marker 0x302E records. */
extern int actor_3031_count;  /* Stores the current count or capacity for level object marker 0x3031 records. */
extern int level_vertical_motion_table[];    /* Provides vertical movement values for a level-object animation. */
extern int actor_303c_count;  /* Stores the current count or capacity for level object marker 0x303C records. */
extern int actor_303b_count;  /* Stores the current count or capacity for level object marker 0x303B records. */
extern int actor_3042_animation_frame_0;     /* Stores one frame value in the marker type 0x3042 animation sequence. */
extern int actor_3042_animation_frame_1;     /* Stores one frame value in the marker type 0x3042 animation sequence. */
extern int actor_3042_animation_frame_2;     /* Stores one frame value in the marker type 0x3042 animation sequence. */
extern int actor_3042_animation_frame_3;     /* Stores one frame value in the marker type 0x3042 animation sequence. */
extern int actor_3042_animation_frame_4;     /* Stores one frame value in the marker type 0x3042 animation sequence. */
extern int actor_3042_animation_frame_5;     /* Stores one frame value in the marker type 0x3042 animation sequence. */
extern int gameplay_animation_flag;          /* Tracks whether gameplay animation is active. */
extern char player_airborne_state;           /* Tracks the current state of player airborne. */
extern char player_damage_immunity_state;    /* Tracks the current state of player damage immunity. */
extern char player_jump_frame;  /* Selects the next vertical displacement in the player's jump-motion row. */
/* Provides two jump-motion displacement rows selected by the player's jump state. */
extern struct player_jump_motion_row player_jump_motion_rows[];
extern char keyboard_modifier_state;         /* Tracks the current state of keyboard modifier. */
extern char player_sprite_draw_state;        /* Tracks the current state of player sprite draw. */
extern int world_effect_sprite_offset;       /* Selects successive sprite cells while moving world effects are drawn. */
/* Selects successive sprite cells while projectile contact effects are drawn. */
extern int projectile_flash_sprite_offset;
/* Selects successive sprite cells while ambient object animations are drawn. */
extern int ambient_object_sprite_offset;
extern int contact_flash_cycle_index;  /* Cycles the palette or sprite phase assigned to a new contact-flash record. */
extern int actor_3002_animation_phase;       /* Tracks the animation phase of level-map marker type 0x3002. */
/* Stores six sprite-resource offsets for each multi-tile actor graphic. */
extern int multi_tile_actor_sprite_offsets[];
extern int actor_300c_motion_delta_table[];  /* Provides movement deltas used by level-map marker type 0x300C. */
extern int actor_300d_animation_phase;       /* Tracks one animation phase for marker type 0x300D. */
extern int actor_300d_animation_counter;     /* Counts animation updates for marker type 0x300D. */
extern int actor_3010_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3010 sprite. */
extern char door_interaction_phase;  /* Tracks the current animation or interaction phase for door interaction. */
extern int actor_3013_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3013 sprite. */
extern int actor_3014_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3014 sprite. */
extern int actor_3015_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3015 sprite. */
extern int actor_3016_upper_sprite_offset;  /* Stores the current sprite or map offset for marker 0x3016 upper sprite. */
extern int actor_3016_lower_sprite_offset;  /* Stores the current sprite or map offset for marker 0x3016 lower sprite. */
extern int actor_301a_sprite_offset;         /* Stores the current sprite or map offset for marker 0x301A sprite. */
extern int actor_3021_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3021 sprite. */
extern int actor_3022_animation_phase;       /* Alternates the sprite variant selected by marker type 0x3022. */
extern int actor_3023_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3023 sprite. */
extern int actor_3024_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3024 sprite. */
extern int actor_3029_sprite_offset;         /* Stores the current sprite or map offset for marker 0x3029 sprite. */
extern int actor_302a_sprite_offset;         /* Stores the current sprite or map offset for marker 0x302A sprite. */
extern int actor_302b_sprite_offset;         /* Stores the current sprite or map offset for marker 0x302B sprite. */
/* Tracks the current animation or interaction phase for marker 0x302C animation. */
extern char actor_302c_animation_phase;
extern int actor_302d_sprite_offset;         /* Stores the current sprite or map offset for marker 0x302D sprite. */
/* Tracks the current animation or interaction phase for marker 0x303C animation. */
extern int actor_303c_animation_phase;
extern int actor_3042_motion_delta_table[];  /* Provides paired movement deltas used by marker type 0x3042. */
extern int actor_3041_sprite_frame;          /* Selects the sprite frame drawn for marker type 0x3041. */
extern int actor_3041_animation_counter;     /* Counts animation updates for marker type 0x3041. */
extern int actor_3041_event_pending;         /* Signals that marker type 0x3041 has a pending state change. */
extern int actor_3041_sprite_offset;         /* Stores the sprite-resource offset selected by marker type 0x3041. */
extern char hint_mode_enabled;  /* Stores hint-mode state; its initial value is on in DN1 and off in DN2 and DN3. */
/* Holds the episode-specific drop-asset filename list used when a level is loaded. */
extern char far *episode_drop_filename_table[];
extern int credits_scroll_position;          /* Tracks the current horizontal scroll position of the credits screen. */
/* Holds episode-specific level-start text lines shown before gameplay. */
extern char far *episode_level_start_text_table[];
/* Provides the repeating glyph-color sequence used while drawing credits. */
extern unsigned char credits_glyph_color_sequence[];
extern unsigned char credits_scroll_text[];  /* Holds the text string scrolled through the credits screen. */
/* Indexes the current period in the active sound sample sequence handled by the timer interrupt. */
extern int current_sound_sample_position;
extern int game_speed_setting;               /* Stores the game-speed setting loaded from and saved to SPEED.DN?. */
extern int current_weapon_state;             /* Tracks the current state of current weapon. */
extern int title_graphic_frame_index;        /* Stores the current index for title graphic frame. */
extern int level_play_state;                 /* Tracks the current state of level play. */
extern int hidden_object_state;              /* Tracks the current state of hidden object. */
extern int actor_300e_object_state_table[];  /* Holds the lookup or pointer table for marker 0x300E object state. */
extern long high_score_values[];  /* Stores the high-score values as 32-bit entries used by the score table. */
/* Aliases the second long-score entry in the contiguous high-score table beginning at d_4fa2. */
extern long high_score_entry_1_alias[];
/* Aliases the third long-score entry in the contiguous high-score table beginning at d_4fa2. */
extern long high_score_entry_2_alias[];
/* Aliases the fourth long-score entry in the contiguous high-score table beginning at d_4fa2. */
extern long high_score_entry_3_alias[];
/* Aliases the fifth long-score entry in the contiguous high-score table beginning at d_4fa2. */
extern long high_score_entry_4_alias[];
extern char sound_effect_priority_table[];   /* Stores the primary sound-bank priority byte for each sound effect. */
/* Stores the secondary sound-bank priority bytes; this table is loaded from the second sound
   bank. */
extern char secondary_sound_priority_table[];
extern int secret_block_state;               /* Tracks the current state of secret block. */
extern int player_animation_lock_state;      /* Tracks the current state of player animation lock. */
extern int level_hazard_count;               /* Stores the current count or capacity for level hazard records. */
extern int level_loading_state;              /* Tracks the current state of level loading. */
extern char high_score_player_names[10][11];  /* Stores the ten player-name strings paired with the high-score table. */
/* Provides an additional high-score name buffer adjacent to the ten saved name rows; its direct
   use is not established. */
extern char high_score_name_edit_buffer[11];
extern int actor_300c_object_marker_table[];  /* Holds the lookup or pointer table for marker 0x300C object marker. */
extern int actor_3035_state;                 /* Tracks the current state of marker 0x3035. */
extern void (far *level_update_callback_table[])(void);
extern int actor_3035_animation_state;       /* Tracks the current state of marker 0x3035 animation. */
extern struct projectile_record projectile_records[];  /* Holds the record array for projectile. */
extern int credits_text_position;            /* Tracks the current character offset in the credits scroll text. */
extern int actor_3035_active_state;          /* Tracks the current state of marker 0x3035 active. */
extern int actor_3037_object_count;  /* Stores the current count or capacity for marker 0x3037 object records. */
extern char pending_sound_priority_flag;     /* Tracks whether pending sound priority is active. */
extern int actor_3037_animation_state;       /* Tracks the current state of marker 0x3037 animation. */
extern char user_demo_recording_state;       /* Tracks the current state of user demo recording. */
extern char secret_block_collision_state;    /* Tracks the current state of secret block collision. */
extern int actor_3013_formation_state;       /* Tracks the current state of marker 0x3013 formation. */
extern int actor_303b_update_state;          /* Tracks the current state of marker 0x303B update. */
extern int exit_lock_animation_state;        /* Tracks the current state of exit lock animation. */
extern int secret_block_animation_state;     /* Tracks the current state of secret block animation. */
extern char game_session_abort_flag;         /* Tracks whether game session abort is active. */
extern int actor_3048_object_count;  /* Stores the current count or capacity for marker 0x3048 object records. */
extern char pending_sound_effect_index;      /* Stores the current index for pending sound effect. */
extern int actor_302a_update_state;          /* Tracks the current state of marker 0x302A update. */
extern int level_object_pool_531e_count;  /* Stores the current count or capacity for level object pool 531e records. */
/* Holds the record array for level collision sound. */
extern struct contact_flash_effect_record level_collision_sound_records[];
/* Holds the record array for animated actor pool. */
extern struct animated_actor_pool_record animated_actor_pool_records[];
extern int actor_3048_entity_count;  /* Stores the current count or capacity for marker 0x3048 entity records. */
extern int actor_3042_interaction_state;     /* Tracks the current state of marker 0x3042 interaction. */
extern char selected_save_slot;  /* Stores the save-slot character selected for save or restore operations. */
extern int keyboard_hotkey_count;            /* Stores the current count or capacity for keyboard hotkey records. */
extern char control_hint_up_flag;            /* Tracks whether control hint up is active. */
extern char control_hint_down_flag;          /* Tracks whether control hint down is active. */
extern char control_hint_left_flag;          /* Tracks whether control hint left is active. */
extern char control_hint_right_flag;         /* Tracks whether control hint right is active. */
extern char hint_revealed_object_1;          /* Indicates whether the first hidden-object hint has been revealed. */
extern char hint_revealed_object_2;          /* Indicates whether the second hidden-object hint has been revealed. */
extern char hint_revealed_object_3;          /* Indicates whether the third hidden-object hint has been revealed. */
/* Stores the previous keyboard interrupt vector; d_5558 is its segment-word alias. */
extern void interrupt far (*saved_keyboard_interrupt_vector)(void);
extern char hint_revealed_object_4;          /* Indicates whether the fourth hidden-object hint has been revealed. */
extern char hint_revealed_object_5;          /* Indicates whether the fifth hidden-object hint has been revealed. */
extern char hint_revealed_object_6;          /* Indicates whether the sixth hidden-object hint has been revealed. */
extern struct actor_3012_record actor_3012_records[];  /* Holds the record array for level object marker 0x3012. */
extern char far *user_demo_buffer;  /* Points to the user-demo recording buffer; d_5a0f is its segment-word alias. */
extern char hint_revealed_object_7;          /* Indicates whether the seventh hidden-object hint has been revealed. */
extern struct actor_3015_record actor_3015_records[];  /* Holds the record array for level object marker 0x3015. */
extern char hint_revealed_object_8;          /* Indicates whether the eighth hidden-object hint has been revealed. */
extern char hint_revealed_object_9;          /* Indicates whether the ninth hidden-object hint has been revealed. */
extern struct falling_hazard_record falling_hazard_records[];  /* Holds the record array for falling hazard. */
/* Points to the player sprite resource buffer; d_5ec6 is its segment-word alias. */
extern char far *player_sprite_resource_buffer;
extern char hint_revealed_object_10;         /* Indicates whether the tenth hidden-object hint has been revealed. */
extern struct actor_3022_record actor_3022_records[];  /* Holds the record array for level object marker 0x3022. */
extern char active_sprite_draw_flag;         /* Tracks whether active sprite draw is active. */
extern char far *sprite_graphics_buffer;     /* Points to sprite graphics data; d_637c is its segment-word alias. */
extern char hint_revealed_object_11;         /* Indicates whether the eleventh hidden-object hint has been revealed. */
extern struct actor_300b_record actor_300b_records[];  /* Holds the record array for level object marker 0x300B. */
extern struct actor_3000_record actor_3000_records[];  /* Holds the record array for level object marker 0x3000. */
extern char transporter_hint_pending;        /* Signals that the transporter hint should be displayed. */
extern long player_score;                    /* Stores the player's 32-bit score; d_68fa is its upper-word alias. */
extern struct actor_3024_record actor_3024_records[];  /* Holds the record array for level object marker 0x3024. */
/* Points to the font glyph data used by text rendering; d_6b56 is its segment-word alias. */
extern char far *font_glyph_data_buffer;
extern struct actor_3044_record actor_3044_records[];  /* Holds the record array for level object marker 0x3044. */
extern struct actor_3007_record actor_3007_records[];  /* Holds the record array for level object marker 0x3007. */
/* Selects the current draw/display page, toggled while the game renders alternating pages. */
extern char draw_page_index;
extern struct actor_302e_record actor_302e_records[];  /* Holds the record array for level object marker 0x302E. */
extern struct actor_3029_record actor_3029_records[];  /* Holds the record array for level object marker 0x3029. */
extern struct actor_3014_record actor_3014_records[];  /* Holds the record array for level object marker 0x3014. */
extern struct actor_3021_record actor_3021_records[];  /* Holds the record array for level object marker 0x3021. */
extern struct actor_303b_record actor_303b_records[];  /* Holds the record array for level object marker 0x303B. */
extern char keyboard_key_d_pressed;          /* Records whether the keyboard D scan code is currently held. */
extern int joystick_x_axis_threshold_low[];  /* Stores the lower joystick X-axis threshold for each calibration mode. */
extern int joystick_y_axis_threshold_low[];  /* Stores the lower joystick Y-axis threshold for each calibration mode. */
extern char keyboard_key_g_pressed;          /* Records whether the keyboard G scan code is currently held. */
/* Points to the loaded 16-bit level tile map; d_772b is its segment-word alias. */
extern unsigned int far *level_tile_map;
extern char keyboard_key_o_pressed;          /* Records whether the keyboard O scan code is currently held. */
extern struct actor_3009_record actor_3009_records[];  /* Holds the record array for level object marker 0x3009. */
extern char far *vga_lower_page_pointer;     /* Points to the vga lower page data used by the game. */
extern int access_card_or_door_state;        /* Tracks the current state of access card or door. */
extern struct actor_301b_record actor_301b_records[];  /* Holds the record array for level object marker 0x301B. */
extern struct actor_3023_record actor_3023_records[];  /* Holds the record array for level object marker 0x3023. */
extern int actor_3034_active_state;          /* Tracks the current state of marker 0x3034 active. */
/* Holds the record array for animated level tile. */
extern struct animated_level_tile_record animated_level_tile_records[];
extern int joystick_x_axis_threshold_high[];  /* Stores the upper joystick X-axis threshold for each calibration mode. */
extern int joystick_y_axis_threshold_high[];  /* Stores the upper joystick Y-axis threshold for each calibration mode. */
#if UNIT == 1
extern int alternate_sprite_draw_offset;     /* Stores the current sprite or map offset for alternate sprite draw. */
#else
extern char alternate_sprite_draw_offset;    /* Stores the current sprite or map offset for alternate sprite draw. */
#endif
extern char far *saved_demo_buffer;  /* Points to the saved-demo playback buffer; d_9686 is its segment-word alias. */
extern struct actor_302c_record actor_302c_records[];  /* Holds the record array for level object marker 0x302C. */
extern struct actor_301f_record actor_301f_records[];  /* Holds the record array for level object marker 0x301F. */
extern int episode_sprite_resource_table;    /* Holds the lookup or pointer table for episode sprite resource. */
extern struct actor_300a_record actor_300a_records[];  /* Holds the record array for level object marker 0x300A. */
extern int actor_3040_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3040 world. */
extern int actor_3040_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3040 world. */
extern int actor_3034_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3034 world. */
/* Latches the last processed fire-button state to prevent repeated edge-triggered actions. */
extern char fire_button_latch;
extern struct actor_301d_record actor_301d_records[];  /* Holds the record array for level object marker 0x301D. */
extern int actor_3034_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3034 world. */
extern char far *duke_graphics_buffer;       /* Holds the buffer used for duke graphics. */
extern struct actor_3037_record actor_3037_records[];  /* Holds the record array for level object marker 0x3037. */
extern char far *object_sprite_buffer;       /* Points to the object sprite buffer; d_a0f1 is its segment-word alias. */
/* Latches the last processed jump-button state to prevent repeated edge-triggered actions. */
extern char jump_button_latch;
/* Stores the previous timer interrupt vector; d_a0f6 is its segment-word alias. */
extern void interrupt far (*previous_timer_interrupt_vector)(void);
extern int player_contact_state;             /* Tracks the current state of player contact. */
/* Stores the most recent keyboard scan code read by the keyboard interrupt handler. */
extern char last_keyboard_scan_code;
/* Points to the current sprite pixel data; d_a0fd is its segment-word alias. */
extern char far *sprite_pixel_data_pointer;
extern struct actor_300d_record actor_300d_records[];  /* Holds the record array for level object marker 0x300D. */
extern struct actor_301e_record actor_301e_records[];  /* Holds the record array for level object marker 0x301E. */
extern int actor_3040_active_state;          /* Tracks the current state of marker 0x3040 active. */
extern int player_sprite_refresh_state;      /* Tracks the current state of player sprite refresh. */
extern int actor_3008_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3008 world. */
extern char keyboard_backspace_pressed;      /* Records whether the Backspace scan code is currently held. */
extern int actor_3008_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3008 world. */
extern struct actor_303c_record actor_303c_records[];  /* Holds the record array for level object marker 0x303C. */
extern char sound_interrupt_active_state;    /* Tracks the current state of sound interrupt active. */
extern char keyboard_interrupt_state;        /* Tracks the current state of keyboard interrupt. */
extern struct actor_3001_record actor_3001_records[];  /* Holds the record array for level object marker 0x3001. */
extern struct actor_300f_record actor_300f_records[];  /* Holds the record array for level object marker 0x300F. */
/* Stores the current count or capacity for formation active object records. */
extern int formation_active_object_count;
extern int formation_object_x_positions[];  /* Stores the horizontal positions of the active enemy-formation members. */
extern int formation_world_x_accumulator;  /* Accumulates horizontal movement deltas for the active enemy formation. */
/* Provides four auxiliary bytes beside the formation state; the checked-in sources do not show
   their use. */
extern char formation_x_auxiliary_bytes[4];
extern struct actor_300e_record actor_300e_records[];  /* Holds the record array for level object marker 0x300E. */
extern struct actor_3031_record actor_3031_records[];  /* Holds the record array for level object marker 0x3031. */
extern int formation_object_y_positions[];   /* Stores the vertical positions of the active enemy-formation members. */
extern int formation_world_y_accumulator;    /* Accumulates vertical movement deltas for the active enemy formation. */
/* Provides four auxiliary bytes beside the formation state; the checked-in sources do not show
   their use. */
extern char formation_y_auxiliary_bytes[4];
extern struct actor_3010_record actor_3010_records[];  /* Holds the record array for level object marker 0x3010. */
extern int actor_3033_active_state;          /* Tracks the current state of marker 0x3033 active. */
extern struct actor_301a_record actor_301a_records[];  /* Holds the record array for level object marker 0x301A. */
extern int actor_3019_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3019 world. */
extern int actor_3042_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3042 world. */
extern int actor_3019_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3019 world. */
extern int actor_3042_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3042 world. */
extern int formation_update_enabled;         /* Tracks whether formation update is active. */
extern char far *episode_graphics_buffer;    /* Holds the buffer used for episode graphics. */
extern struct moving_actor_record moving_actor_records[];  /* Holds the record array for moving actor. */
extern struct actor_300c_record actor_300c_records[];  /* Holds the record array for level object marker 0x300C. */
extern int ending_sequence_enabled;          /* Tracks whether ending sequence is active. */
/* Holds the record array for level tile animation. */
extern struct level_tile_animation_record level_tile_animation_records[];
extern struct actor_3018_record actor_3018_records[];  /* Holds the record array for level object marker 0x3018. */
extern int actor_3041_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3041 world. */
extern char demo_file_load_success;          /* Records whether the requested demo file was loaded successfully. */
extern int actor_302f_world_x;               /* Stores the X-coordinate or X-related value for marker 0x302F world. */
extern int actor_3030_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3030 world. */
extern char far *badguy_graphics_buffer;     /* Holds the buffer used for badguy graphics. */
extern int actor_3019_enabled;               /* Tracks whether level object marker 0x3019 is active. */
extern int actor_3042_active_state;          /* Tracks the current state of marker 0x3042 active. */
extern char far *credits_graphics_buffer;    /* Holds the buffer used for credits graphics. */
extern int actor_3041_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3041 world. */
extern int actor_302f_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x302F world. */
extern int actor_3030_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3030 world. */
extern char far *ending_graphics_buffer;     /* Holds the buffer used for ending graphics. */
extern int actor_3042_hint_state;            /* Tracks the current state of marker 0x3042 hint. */
extern int world_actor_count;                /* Stores the current count or capacity for world actor records. */
extern int joystick_configuration_mode;      /* Selects which joystick axis and button mapping is active. */
extern struct actor_3002_record actor_3002_records[];  /* Holds the record array for level object marker 0x3002. */
extern int actor_3041_active_state;          /* Tracks the current state of marker 0x3041 active. */
extern char player_level_transition_state;   /* Tracks the current state of player level transition. */
extern int actor_302f_active_state;          /* Tracks the current state of marker 0x302F active. */
/* Tracks the current animation or interaction phase for marker 0x302F interaction. */
extern int actor_302f_interaction_phase;
extern int actor_3030_active_state;          /* Tracks the current state of marker 0x3030 active. */
/* Tracks the current animation or interaction phase for marker 0x302F animation. */
extern int actor_302f_animation_phase;
extern char control_up_pressed;              /* Records whether the up control is currently pressed. */
extern int actor_302b_world_x;               /* Stores the X-coordinate or X-related value for marker 0x302B world. */
extern int actor_302b_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x302B world. */
extern struct actor_302a_record actor_302a_records[];  /* Holds the record array for level object marker 0x302A. */
extern int actor_302b_active_state;          /* Tracks the current state of marker 0x302B active. */
/* Holds the record array for object collision pool. */
extern struct collision_effect_record object_collision_pool_records[];
extern struct actor_302d_record actor_302d_records[];  /* Holds the record array for level object marker 0x302D. */
extern struct world_actor_record world_actor_records[];  /* Holds the record array for world actor. */
/* Holds pointers to sound sample sequences used by the timer interrupt handler. */
extern char far *sound_sample_pointer_table[];
extern char far *vga_upper_page_pointer;     /* Points to the vga upper page data used by the game. */
extern char control_confirmation_state;      /* Tracks the current state of control confirmation. */
extern int actor_3020_active_state;          /* Tracks the current state of marker 0x3020 active. */
extern struct actor_3058_record actor_3058_records[];  /* Holds the record array for level object marker 0x3058. */
extern char control_down_pressed;            /* Records whether the down control is currently pressed. */
extern char control_fire_pressed;            /* Records whether the fire control is currently pressed. */
extern int actor_3019_width;  /* Stores the width used by level-map marker type 0x3019 collision checks. */
extern char control_jump_pressed;            /* Records whether the jump control is currently pressed. */
extern int actor_302f_interaction_state;     /* Tracks the current state of marker 0x302F interaction. */
extern int actor_3030_interaction_state;     /* Tracks the current state of marker 0x3030 interaction. */
extern int actor_3035_world_x;               /* Stores the X-coordinate or X-related value for marker 0x3035 world. */
extern char control_left_pressed;            /* Records whether the left control is currently pressed. */
extern int actor_3035_world_y;               /* Stores the Y-coordinate or Y-related value for marker 0x3035 world. */
extern int actor_3042_animation_counter;     /* Counts updates for marker 0x3042 animation. */
extern unsigned int player_sprite_animation_index;  /* Stores the current index for player sprite animation. */
extern int actor_3041_interaction_state;     /* Tracks the current state of marker 0x3041 interaction. */
extern char keyboard_control_lock_state;     /* Tracks the current state of keyboard control lock. */
extern int secret_code_character_0[];        /* Stores the first character entered for the secret-code sequence. */
extern int secret_code_character_1;          /* Stores the second character entered for the secret-code sequence. */
extern int secret_code_character_2;          /* Stores the third character entered for the secret-code sequence. */
extern char secret_code_input_buffer[6];     /* Holds the buffer used for secret code input. */
extern int actor_3019_animation_state;       /* Tracks the current state of marker 0x3019 animation. */
/* Holds the record array for level object marker 0x3048. */
extern struct level_tile_animation_record actor_3048_records[];
extern struct pickup_object_record free_object_pool_records[];  /* Holds the record array for free object pool. */
extern int player_gameplay_state;            /* Tracks the current state of player gameplay. */
extern int formation_object_active_flags[];  /* Stores active-state flags for the members of the enemy formation. */
extern struct actor_3016_record actor_3016_records[];  /* Holds the record array for level object marker 0x3016. */
extern int actor_3019_screen_x;              /* Stores the X-coordinate or X-related value for marker 0x3019 screen. */
extern int actor_3019_map_row;               /* Stores the map row of the level-map marker type 0x3019 object. */
extern int door_lock_world_x;                /* Stores the X-coordinate or X-related value for door lock world. */
extern char player_projectile_state;         /* Tracks the current state of player projectile. */
extern char control_right_pressed;           /* Records whether the right control is currently pressed. */
extern int door_lock_world_y;                /* Stores the Y-coordinate or Y-related value for door lock world. */
extern struct ambient_object_record ambient_object_records[];  /* Holds the record array for ambient object. */
extern char joystick_enabled;                /* Tracks whether joystick is active. */
extern int actor_3042_open_state;            /* Tracks the current state of marker 0x3042 open. */
extern int actor_302b_animation_counter;     /* Counts updates for marker 0x302B animation. */
extern int door_or_key_interaction_state;    /* Tracks the current state of door or key interaction. */
extern int actor_302b_open_state;            /* Tracks the current state of marker 0x302B open. */
extern int secret_block_world_x;             /* Stores the X-coordinate or X-related value for secret block world. */
extern char player_invulnerability_state;    /* Tracks the current state of player invulnerability. */
extern int secret_block_world_y;             /* Stores the Y-coordinate or Y-related value for secret block world. */
extern char current_sound_priority;          /* Stores the priority of the currently playing sound effect. */
extern int actor_3037_bonus_state;           /* Tracks the current state of marker 0x3037 bonus. */
extern int level_progress_word;              /* Stores the current level-progress word written to saved-game data. */
/* Stores auxiliary state bytes for the level-map marker type 0x300D objects. */
extern int actor_300d_auxiliary_states[];
extern int actor_3001_tile_below_records[];  /* Holds the record array for marker 0x3001 tile below. */
extern int actor_3044_entity_count;  /* Stores the current count or capacity for marker 0x3044 entity records. */
extern char far *secondary_sound_bank_buffer;  /* Holds the buffer used for secondary sound bank. */
extern char far *primary_sound_bank_buffer;  /* Holds the buffer used for primary sound bank. */
/* Counts timer interrupts between calls to the prior BIOS timer handler; the handler chains
   every eight ticks. */
extern int bios_timer_chain_divider;

#endif
