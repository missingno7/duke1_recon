/* GAME2.C - second translation unit of Duke Nukum v2.0: menus, text screens, high scores,
   timer and PC-speaker sound.

   Functions, initialised data and literals stay in the order of the original object
   file: Turbo C 2.0 emits code, string literals and data in source order, so this
   order is part of what makes the build byte-identical.  Sections below group the
   functions by subsystem as far as that order allows. */

#define UNIT 2      /* selects this unit's declarations in duke.h */
#include "duke.h"

/* ---- uninitialised data (BSS) ---- */

/* G2 BSS objects in ascending DN1 address order. Each typed array spans to the next object start. */






















/* 0xa0f4; accepted scalar type. */
void interrupt far (*previous_timer_interrupt_vector)(void);
/* 0xa0f8; accepted scalar type. */
int player_contact_state;
/* 0xa0fa; accepted scalar type. */
char last_keyboard_scan_code;
/* 0xa0fb; accepted scalar type. */
char far *sprite_pixel_data_pointer;
/* 0xa0ff; array extent from address gap. */
struct wheeled_techbot_record wheeled_techbot_records[100];
/* 0xa357; array extent from address gap. */
struct joystick_box_record joystick_box_records[100];
/* 0xa677; accepted scalar type. */
int message_sign_active_state;
/* 0xa679; accepted scalar type. */
int player_sprite_refresh_state;
/* 0xa67b; accepted scalar type. */
int ceiling_clinger_box_world_x;
/* 0xa67d; accepted scalar type. */
char keyboard_backspace_pressed;
/* 0xa67e; accepted scalar type. */
int ceiling_clinger_box_world_y;
/* 0xa680; array extent from address gap. */
struct fire_creature_record fire_creature_records[100];
/* 0xa8d8; accepted scalar type. */
char sound_interrupt_active_state;
/* 0xa8d9; accepted scalar type. */
char keyboard_interrupt_state;
/* 0xa8da; array extent from address gap. */
struct elevator_record elevator_records[100];
/* 0xab32; array extent from address gap. */
struct ammo_box_record ammo_box_records[20];
/* 0xabd2; accepted scalar type. */
int formation_active_object_count;
/* 0xabd4; array extent from address gap. */
int formation_object_x_positions[9];
/* 0xabe6; accepted scalar type. */
int formation_world_x_accumulator;
/* UNREFERENCED: [0xabe8,0xabec) has no accepted object start or direct DS reference. */
char formation_x_auxiliary_bytes[4];
/* 0xabec; array extent from address gap. */
struct fire_wheel_techbot_record fire_wheel_techbot_records[100];
/* 0xae44; array extent from address gap. */
struct red_bomb_record red_bomb_records[100];
/* 0xb09c; array extent from address gap. */
int formation_object_y_positions[9];
/* 0xb0ae; accepted scalar type. */
int formation_world_y_accumulator;
/* UNREFERENCED: [0xb0b0,0xb0b4) has no accepted object start or direct DS reference. */
char formation_y_auxiliary_bytes[4];
/* 0xb0b4; array extent from address gap. */
struct robot_techbot_record robot_techbot_records[100];
/* 0xb3d4; accepted scalar type. */
int access_card_box_active_state;
/* 0xb3d6; array extent from address gap. */
struct horizontal_force_field_record horizontal_force_field_records[100];
/* 0xb62e; accepted scalar type. */
int collapsing_bridge_world_x;
/* 0xb630; accepted scalar type. */
int dr_proton_world_x;
/* 0xb632; accepted scalar type. */
int collapsing_bridge_world_y;
/* 0xb634; accepted scalar type. */
int dr_proton_world_y;
/* 0xb636; accepted scalar type. */
int formation_update_enabled;
/* 0xb638; accepted scalar type. */
char far *title_screen_buffer;
/* 0xb63c; array extent from address gap. */
struct moving_actor_record moving_actor_records[16];
/* 0xb6bc; array extent from address gap. */
struct jumping_techbot_record jumping_techbot_records[100];
/* 0xb9dc; accepted scalar type. */
int ending_sequence_enabled;
/* 0xb9de; array extent from address gap. */
struct level_tile_animation_record level_tile_animation_records[200];
/* 0xc01e; array extent from address gap. */
struct turkey_bonus_record turkey_bonus_records[100];
/* 0xc276; accepted scalar type. */
int proton_display_world_x;
/* 0xc278; accepted scalar type. */
char demo_file_load_success;
/* 0xc279; accepted scalar type. */
int teleporter_entry_world_x;
/* 0xc27b; accepted scalar type. */
int teleporter_exit_world_x;
/* 0xc27d; accepted scalar type. */
char far *badguy_graphics_buffer;
/* 0xc281; accepted scalar type. */
int collapsing_bridge_enabled;
/* 0xc283; accepted scalar type. */
int dr_proton_active_state;
/* 0xc285; accepted scalar type. */
char far *credits_graphics_buffer;
/* 0xc289; accepted scalar type. */
int proton_display_world_y;
/* 0xc28b; accepted scalar type. */
int teleporter_entry_world_y;
/* 0xc28d; accepted scalar type. */
int teleporter_exit_world_y;
/* 0xc28f; accepted scalar type. */
char far *ending_graphics_buffer;
/* 0xc293; accepted scalar type. */
int dr_proton_hint_state;
/* 0xc295; accepted scalar type. */
int world_actor_count;
/* 0xc297; accepted scalar type. */
int joystick_configuration_mode;
/* 0xc299; array extent from address gap. */
struct conveyor_belt_record conveyor_belt_records[100];
/* 0xc681; accepted scalar type. */
int proton_display_active_state;
/* 0xc683; accepted scalar type. */
char player_level_transition_state;
/* 0xc684; accepted scalar type. */
int teleporter_entry_active_state;
/* 0xc686; accepted scalar type. */
int tele_in_interaction_phase;
/* 0xc688; accepted scalar type. */
int teleporter_exit_active_state;
/* 0xc68a; accepted scalar type. */
int tele_in_animation_phase;
/* 0xc68c; accepted scalar type. */
char control_up_pressed;
/* 0xc68d; accepted scalar type. */
int reactor_world_x;
/* 0xc68f; accepted scalar type. */
int reactor_world_y;
/* 0xc691; array extent from address gap. */
struct falling_sign_record falling_sign_records[100];
/* 0xc8e9; accepted scalar type. */
int reactor_active_state;
/* 0xc8eb; array extent from address gap. */
struct collision_effect_record object_collision_pool_records[7];
/* 0xc915; array extent from address gap. */
struct magenta_flag_box_record magenta_flag_box_records[100];
/* 0xcb6d; array extent from address gap. */
struct world_actor_record world_actor_records[9];
/* 0xcbb5; array extent from address gap. */
char far *sound_sample_pointer_table[50];
/* 0xcc7d; accepted scalar type. */
char far *vga_upper_page_pointer;
/* 0xcc81; accepted scalar type. */
char control_confirmation_state;
/* 0xcc82; accepted scalar type. */
int robohand_box_active_state;
/* 0xcc84; array extent from address gap. */
struct spike_hazard_record spike_hazard_records[200];
/* 0xd134; accepted scalar type. */
char control_down_pressed;
/* 0xd135; accepted scalar type. */
char control_fire_pressed;
/* 0xd136; accepted scalar type. */
int collapsing_bridge_width;
/* 0xd138; accepted scalar type. */
char control_jump_pressed;
/* 0xd139; accepted scalar type. */
int tele_in_interaction_state;
/* 0xd13b; accepted scalar type. */
int tele_out_interaction_state;
/* 0xd13d; accepted scalar type. */
int robohand_switch_world_x;
/* 0xd13f; accepted scalar type. */
char control_left_pressed;
/* 0xd140; accepted scalar type. */
int robohand_switch_world_y;
/* 0xd142; accepted scalar type. */
int dr_proton_animation_counter;
/* 0xd144; accepted scalar type. */
unsigned int player_sprite_animation_index;
/* 0xd146; accepted scalar type. */
int proton_screen_interaction_state;
/* 0xd148; accepted scalar type. */
char keyboard_control_lock_state;
/* 0xd149; array extent from address gap. */
int secret_code_character_0[1];
/* 0xd14b; accepted scalar type. */
int secret_code_character_1;
/* 0xd14d; accepted scalar type. */
int secret_code_character_2;
/* UNREFERENCED: [0xd14f,0xd155) has no accepted object start or direct DS reference. */
char secret_code_input_buffer[6];
/* 0xd155; accepted scalar type. */
int weak_bridge_animation_state;
/* 0xd157; array extent from address gap. */
struct level_tile_animation_record door_lock_records[15];
/* 0xd1cf; array extent from address gap. */
struct pickup_object_record free_object_pool_records[20];
/* 0xd247; accepted scalar type. */
int player_gameplay_state;
/* 0xd249; array extent from address gap. */
int formation_object_active_flags[12];
/* 0xd261; array extent from address gap. */
struct wallcrawler_record wallcrawler_records[100];
/* 0xd4b9; accepted scalar type. */
int collapsing_bridge_screen_x;
/* 0xd4bb; accepted scalar type. */
int collapsing_bridge_map_row;
/* 0xd4bd; accepted scalar type. */
int door_lock_world_x;
/* 0xd4bf; accepted scalar type. */
char player_projectile_state;
/* 0xd4c0; accepted scalar type. */
char control_right_pressed;
/* 0xd4c1; accepted scalar type. */
int door_lock_world_y;
/* 0xd4c3; array extent from address gap. */
struct ambient_object_record ambient_object_records[21];
/* 0xd56b; accepted scalar type. */
char joystick_enabled;
/* 0xd56c; accepted scalar type. */
int dr_proton_open_state;
/* 0xd56e; accepted scalar type. */
int reactor_animation_counter;
/* 0xd570; accepted scalar type. */
int door_or_key_interaction_state;
/* 0xd572; accepted scalar type. */
int reactor_open_state;
/* 0xd574; accepted scalar type. */
int secret_block_world_x;
/* 0xd576; accepted scalar type. */
char player_invulnerability_state;
/* 0xd577; accepted scalar type. */
int secret_block_world_y;
/* 0xd579; accepted scalar type. */
char current_sound_priority;
/* 0xd57a; accepted scalar type. */
int letter_bonus_state;
/* 0xd57c; accepted scalar type. */
int level_progress_word;
/* 0xd57e; array extent from address gap. */
int wheelbot_auxiliary_states[100];
/* 0xd646; array extent from address gap. */
int elevator_tile_below_records[100];
/* 0xd70e; accepted scalar type. */
int door_key_count;
/* 0xd710; accepted scalar type. */
char far *secondary_sound_bank_buffer;
/* 0xd714; accepted scalar type. */
char far *primary_sound_bank_buffer;
/* 0xd718; accepted scalar type. */
int bios_timer_chain_divider;

/* ---- initialised data ---- */

/* Initialised data of this unit (DGROUP 0x0b46..0x0f2b in every episode), in definition
   order.  Defined before the first function so that the strings of the two pointer
   tables open the unit's literal pool (docs/turbo-c.md).  unused_0cd1 is not
   referenced by any code. */
#if EPISODE == 1
char hint_mode_enabled = 1;
#elif EPISODE == 2
char hint_mode_enabled = 0;
#else
char hint_mode_enabled = 0;
#endif
#if EPISODE == 1
char far *episode_drop_filename_table[22] = {
    "drop0.dn1",
    "drop3.dn1",
    "drop0.dn1",
    "drop3.dn1",
    "drop7.dn1",
    "drop3.dn1",
    "drop3.dn1",
    "drop5.dn1",
    "drop7.dn1",
    "drop7.dn1",
    "drop2.dn1",
    "drop2.dn1",
    "drop1.dn1",
    "drop2.dn1",
    "drop3.dn1",
    "drop3.dn1",
    "drop5.dn1",
    "drop2.dn1",
    "drop0.dn1",
    "drop11.dn1",
    "drop13.dn1",
    "drop9.dn1"
};
#elif EPISODE == 2
char far *episode_drop_filename_table[22] = {
    "drop8.dn2",
    "drop9.dn2",
    "drop9.dn2",
    "drop9.dn2",
    "drop8.dn2",
    "drop5.dn2",
    "drop11.dn2",
    "drop2.dn2",
    "drop3.dn2",
    "drop9.dn2",
    "drop3.dn2",
    "drop3.dn2",
    "drop5.dn2",
    "drop8.dn2",
    "drop1.dn2",
    "drop1.dn2",
    "drop5.dn2",
    "drop2.dn2",
    "drop8.dn2",
    "drop11.dn2",
    "drop13.dn2",
    "drop9.dn2"
};
#elif EPISODE == 3
char far *episode_drop_filename_table[22] = {
    "drop0.dn3",
    "drop10.dn3",
    "drop10.dn3",
    "drop3.dn3",
    "drop6.dn3",
    "drop5.dn3",
    "drop12.dn3",
    "drop12.dn3",
    "drop12.dn3",
    "drop13.dn3",
    "drop1.dn3",
    "drop1.dn3",
    "drop0.dn3",
    "drop0.dn3",
    "drop2.dn3",
    "drop6.dn3",
    "drop2.dn3",
    "drop2.dn3",
    "drop13.dn3",
    "drop2.dn3",
    "drop13.dn3",
    "drop9.dn3"
};
#endif
int credits_scroll_position = 0;
#if EPISODE == 1
char far *episode_level_start_text_table[76] = {
    "\0",
    "\0",
    "\0",
    "\0",
    "You are entering the",
    "next level.  Now is a",
    "good time to SAVE your",
    "game.               ",
    "Surprise Duke, I'll be  ",
    "tracking your every move",
    "with my security camera ",
    "system!                 ",
    "On the next level you'll",
    "need to find a special",
    "access card that looks",
    "like a computer board.",
    "",
    "",
    "",
    "",
    "If you find the boots on",
    "the next level you'll be",
    "able to jump higher!",
    "SAVE your game now.   ",
    "I see you're still      ",
    "trying Duke. Never mind,",
    "my robot drones will    ",
    "soon be the end of you! ",
    "The next level is very",
    "tough--but there's also",
    "a secret shortcut!",
    "Don't forget to SAVE.",
    "Hmmm...  I see you've   ",
    "survived my Maze of     ",
    "Madness.  I might have  ",
    "underestimated you.     ",
    "You are doing quite well",
    "so far...let's see if   ",
    "you can keep it up. Also",
    "remember to SAVE.       ",
    "Duke, in spite of your  ",
    "persistance, my plan to ",
    "rule Earth will not be  ",
    "stopped.  Ah, ha, ha!   ",
    "Find the GRAPPLING HOOKS",
    "to beat the next level. ",
    "Use them to grab on to  ",
    "special grated ceilings.",
    "Why bother Duke?  Not   ",
    "even Commander Keen     ",
    "could survive the perils",
    "of my Mercury Mines!    ",
    "There are several secret",
    "bonuses you can earn on",
    "each level!  Register to",
    "get the complete list.",
    "I hate heroes! Your luck",
    "is about to run out.    ",
    "Perhaps now would be a  ",
    "good time to flee, Duke!",
    "Secret Bonus Hint:      ",
    "Collect the letters     ",
    "D, U, K, E in order to  ",
    "earn bonus number five. ",
    "Duke, join me now and   ",
    "live, or continue this  ",
    "foolishness and I'll    ",
    "squash you myself!      ",
    "You are about to enter",
    "the secret Bubble City",
    "fortress of Dr. Proton.",
    "There's no turning back!",
    "I'm coming down to crush",
    "you, Duke.  It's just   ",
    "you and me now.         ",
    "                        "
};
#elif EPISODE == 2
char far *episode_level_start_text_table[76] = {
    "\0",
    "\0",
    "\0",
    "\0",
    "You are about to enter  ",
    "the next level.  Don't  ",
    "forget to SAVE your     ",
    "game.  Good luck!       ",
    "Ah ha, Duke.  I see even",
    "with your stunted       ",
    "abilities you managed to",
    "find my moonbase.       ",
    "Hint:  You'll need to   ",
    "collect the robot hand  ",
    "to help you survive the ",
    "next level!             ",
    "You lose, Duke Pukem,   ",
    "I'm sending my newly    ",
    "improved Techbots to    ",
    "dispense with you!      ",
    "You might find that the ",
    "next level is too windy ",
    "for you...!             ",
    "                        ",
    "Duke, you make me laugh!",
    "Which is why it's almost",
    "sad to know you'll soon ",
    "be moon dust...         ",
    "You might find your     ",
    "super jump boots on the ",
    "next level if you look  ",
    "hard enough...          ",
    "Duke, you used to make  ",
    "me laugh--but now you're",
    "beginning to upset me.  ",
    "You will not last long! ",
    "Now entering an ancient ",
    "underground lunar city! ",
    "Beware of the snake     ",
    "Techbot!                ",
    "                        ",
    "                        ",
    "                        ",
    "                        ",
    "Hint:  The grappling    ",
    "hooks will \"lift\" your  ",
    "chances of completing   ",
    "the next level.         ",
    "                        ",
    "                        ",
    "                        ",
    "                        ",
    "You are about to enter  ",
    "the next level.  Don't  ",
    "forget to SAVE your     ",
    "game.                   ",
    "Tell me Duke, is all of ",
    "that lava down there as ",
    "hot as it looks?        ",
    "Ha, ha, ha, haaa...     ",
    "Dr. Proton's lunar hide-",
    "out is very, very close!",
    "Be prepared for any     ",
    "surprises or traps...   ",
    "Confused Duke?  Your    ",
    "perilously low intellect",
    "will accelerate your    ",
    "demise in my maze!      ",
    "The final challenge is  ",
    "ahead--Dr. Proton's     ",
    "secret lunar fortress!  ",
    "                        ",
    "Are you ready to lose,  ",
    "Duke?  Then enter my    ",
    "secret chamber...       ",
    "                        "
};
#elif EPISODE == 3
char far *episode_level_start_text_table[76] = {
    "\0",
    "\0",
    "\0",
    "\0",
    "You are about to enter  ",
    "the next level.  Be sure",
    "to SAVE your game.      ",
    "",
    "Duke, you've tracked me ",
    "to the Moon and into    ",
    "Earth's future.  Don't  ",
    "you ever take a break?  ",
    "You are about to enter  ",
    "the next level.  Be sure",
    "to SAVE your game.      ",
    "",
    "",
    "",
    "",
    "",
    "HINT:  You will need to ",
    "find your super jump    ",
    "boots on the next level.",
    "",
    "Duke, I see you where-  ",
    "ever you go.  And I have",
    "devised many traps that ",
    "will end your mission.  ",
    "Hint:  Look for the time",
    "transport machine to    ",
    "help you solve the next ",
    "level.                 ",
    "",
    "",
    "",
    "",
    "Hint:  The robot hand is",
    "very well hidden--but   ",
    "must be found!          ",
    "",
    "I am warning you, Duke. ",
    "It is about time I show ",
    "you the awesome power of",
    "Dr. Proton!             ",
    "You have done well to   ",
    "survive this far, but   ",
    "what lies ahead may be  ",
    "your match!",
    "",
    "",
    "",
    "",
    "You are about to enter  ",
    "the next level.  Be sure",
    "to SAVE your game.      ",
    "",
    "So Duke, did you enjoy  ",
    "my killer rabbitoids?   ",
    "Nothing will out last   ",
    "them...Ah, ha, ha...!   ",
    "Keep going Duke, we're  ",
    "counting on you...!     ",
    "                        ",
    "                        ",
    "",
    "",
    "",
    "",
    "Unless you can stop Dr. ",
    "Proton, Earth will be   ",
    "helpless against his    ",
    "mindless Techbots.",
    "Duke, I'm coming to     ",
    "crush you myself!  Earth",
    "is mine, and so will be ",
    "victory over you!       "
};
#endif
unsigned char unused_0cd1[16] = { 0 };
unsigned char credits_glyph_color_sequence[35] = { 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 0, 0, 0, 0 };
char credits_scroll_text[550] = "                           DUKE NUKUM is one of the best, feature-packed games ever made for an IBM PC! It beats Nintendo easily!    DUKE NUKUM features:     Incredible animation,   One megabyte of graphics, dual scrolling playfields,  arcade sound effects,     and much, much more...! A built in Hint Mode makes learning the game easy!    Supports joystick, too.   You'll find dozens of    secret rooms with prizes. Duke can somersault and   cling onto ceilings with     his special hooks.       GET DUKE NUKUM NOW!                             ";
int current_sound_sample_position = 0;

/* ============================================================================================
   Palette, video pages and joystick sampling
   ============================================================================================ */

/* Visits all 16 palette registers in order, setting each to color value 23 with the requested
   delay. */
void pascal set_palette_entries_to_23(int delay_ticks)
{
    register int i;

    for (i = 0; i < 16; ++i) {
        delay(delay_ticks);
        set_vga_mode_with_parameters(i, 0x17);
    }
}

/* Restores the 16 EGA palette registers to the source's default color values, with a delay
   between writes. */
void pascal restore_ega_palette(register int delay_ticks)
{
    set_vga_mode_with_parameters(0, 0);
    delay(delay_ticks);
    set_vga_mode_with_parameters(1, 1);
    delay(delay_ticks);
    set_vga_mode_with_parameters(2, 2);
    delay(delay_ticks);
    set_vga_mode_with_parameters(3, 3);
    delay(delay_ticks);
    set_vga_mode_with_parameters(4, 4);
    delay(delay_ticks);
    set_vga_mode_with_parameters(5, 5);
    delay(delay_ticks);
    set_vga_mode_with_parameters(6, 6);
    delay(delay_ticks);
    set_vga_mode_with_parameters(7, 7);
    delay(delay_ticks);
    set_vga_mode_with_parameters(8, 16);
    delay(delay_ticks);
    set_vga_mode_with_parameters(9, 17);
    delay(delay_ticks);
    set_vga_mode_with_parameters(10, 18);
    delay(delay_ticks);
    set_vga_mode_with_parameters(11, 19);
    delay(delay_ticks);
    set_vga_mode_with_parameters(12, 20);
    delay(delay_ticks);
    set_vga_mode_with_parameters(13, 21);
    delay(delay_ticks);
    set_vga_mode_with_parameters(14, 22);
    delay(delay_ticks);
    set_vga_mode_with_parameters(15, 23);
    delay(delay_ticks);
}

/* clear_palette_entries candidate */
/* Clears all 16 palette registers to color value zero, with the requested delay between writes. */
void pascal clear_palette_entries(int delay_ticks)
{
    register int i;

    for (i = 0; i < 16; ++i) {
        delay(delay_ticks);
        set_vga_mode_with_parameters(i, 0);
    }
}

/* Selects the requested drawing page and makes that page visible. */
void select_and_show_video_page(void)
{
    select_draw_page(!draw_page_index);
    show_video_page(draw_page_index);
}

/* Measures the two selected joystick-axis discharge times and stores the counts through the
   output pointers. */
void pascal sample_joystick_axes(int joystick_number, int far *x_axis_count, int far *y_axis_count)
{
    int y_axis_pressed;
    int x_axis_mask;
    int y_axis_mask;
    register int joystick_port_state;
    register int x_axis_pressed;

    if (joystick_number == 1) {
        x_axis_mask = 1;
        y_axis_mask = 2;
    } else {
        x_axis_mask = 4;
        y_axis_mask = 8;
    }
    *x_axis_count = 0;
    *y_axis_count = 0;
    disable();
    /* Discharge the game-port timing capacitors before joystick_button_sample the axes. */
    outportb(0x201, inportb(0x201));
    do {
        joystick_port_state = inportb(0x201);
        x_axis_pressed = (joystick_port_state & x_axis_mask) != 0;
        y_axis_pressed = (joystick_port_state & y_axis_mask) != 0;
        *x_axis_count += x_axis_pressed;
        *y_axis_count += y_axis_pressed;
    } while (x_axis_pressed + y_axis_pressed != 0 && *x_axis_count < 500 && *y_axis_count < 500);
    enable();
}

/* Clears a rectangular region of the selected planar video page. */
void pascal clear_video_page_region(int bitmap_offset)
{
    register int column_offset;
    register int row_offset;

    /* Select all VGA planes and write mode 1 for the clear. */
    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    select_draw_page(0);
    show_video_page(0);
    for (row_offset = 0; row_offset < 25; row_offset++) {
        for (column_offset = 0; column_offset < 20; column_offset++) {
            blit_bitmap_to_video_page(bitmap_offset, column_offset * 2 + row_offset * 640);
        }
    }
}

/* ============================================================================================
   Information screens, hints and dialogs
   Ordering and story pages, save/restore messages, the hint (secret tip) cards, help,
   key bindings, high scores and the timer/sound interrupt.
   ============================================================================================ */

/* Displays the ordering page one screen or message and waits for the associated input when
   required. */
void show_ordering_page_one(void)
{
    clear_palette_entries(20);
    clear_video_page_region(0x1710);
    draw_text_string("          ORDERING INFORMATION          ", 0, 0);
    draw_text_string("      Duke Nukum consists of three      ", 0, 2);
    draw_text_string("    unique and challenging episodes!    ", 0, 3);
    draw_text_string("                                        ", 0, 4);
    draw_text_string(" Episode ONE:    Shrapnel City          ", 0, 5);
    draw_text_string(" Episode TWO:    Mission: Moonbase      ", 0, 6);
    draw_text_string(" Episode THREE:  Trapped in the Future! ", 0, 7);
    draw_text_string("                                        ", 0, 8);
    draw_text_string("  You can order each episode for $15.   ", 0, 9);
    draw_text_string("  Or for only $30, you'll receive all   ", 0, 10);
    draw_text_string("     three episodes, and also get:      ", 0, 11);
    draw_text_string("                                        ", 0, 12);
    draw_text_string(" 1) The \"Secret Hints and Tips\" sheet!  ", 0, 13);
    draw_text_string(" 2) A \"Cheat Mode\" password that will   ", 0, 14);
    draw_text_string("    give you FULL FIREPOWER and ALL THE ", 0, 15);
    draw_text_string("    KEYS to each level!                 ", 0, 16);
    draw_text_string(" 3) Several HOT new bonus games!        ", 0, 17);
    draw_text_string("                                        ", 0, 18);
    draw_text_string("   Each episode is set in an entirely   ", 0, 19);
    draw_text_string(" new location, with exciting challenges ", 0, 20);
    draw_text_string(" and of course, more adventure than any ", 0, 21);
    draw_text_string("       human can possibly handle!       ", 0, 22);
    draw_text_string("  Press any key for more information... ", 0, 24);
    restore_ega_palette(20);
}

/* Displays the ordering page two screen or message and waits for the associated input when
   required. */
void show_ordering_page_two(void)
{
    clear_video_page_region(0x1710);
    draw_text_string("          ORDERING INFORMATION          ", 0, 0);
    draw_text_string("  Order NOW by sending a check or money ", 0, 2);
    draw_text_string("   order for $30 (add $3 shipping) to:  ", 0, 3);
    draw_text_string("                                        ", 0, 4);
    draw_text_string("            Apogee Software             ", 0, 5);
    draw_text_string("            P.O. Box 476389             ", 0, 6);
    draw_text_string("         Garland, TX  75047  (USA)      ", 0, 7);
    draw_text_string("                                        ", 0, 8);
    draw_text_string("  Order NOW toll free:  1-800-852-5659  ", 0, 9);
    draw_text_string("    (Visa and MasterCard accepted!)     ", 0, 10);
    draw_text_string("                                        ", 0, 11);
    draw_text_string("   Specify disk size:  5.25\" or 3.5\".   ", 0, 12);
    draw_text_string("                                        ", 0, 13);
    draw_text_string("  Foreign orders: Please read the file  ", 0, 14);
    draw_text_string("    FOREIGN.DOC to place your order.    ", 0, 15);
    draw_text_string("                                        ", 0, 16);
    draw_text_string(" Order today and continue your exciting ", 0, 17);
    draw_text_string(" adventures as Duke Nukum.  Once again, ", 0, 18);
    draw_text_string("  for $33 (including shipping) you'll   ", 0, 19);
    draw_text_string("  get all three updated episodes, the   ", 0, 20);
    draw_text_string("     cheat mode, and the hints and      ", 0, 21);
    draw_text_string("       tricks sheet.  Thank you!        ", 0, 22);
    draw_text_string("             Press any key.             ", 0, 24);
    if (control_confirmation_state == 0) {
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    }
}

/* show_story_game_instructions candidate */
/* Displays the story game instructions screen or message and waits for the associated input when
   required. */
void show_story_game_instructions(void)
{
    clear_palette_entries(20);
    clear_video_page_region(0x1710);
    draw_text_string("                THE STORY               ", 0, 0);
    draw_text_string("The year is 1997.  Doctor Proton and his", 0, 2);
    draw_text_string(" army of Techbots have taken control of ", 0, 3);
    draw_text_string("Earth's largest city.   Once a respected", 0, 4);
    draw_text_string("    genius and scientist, Dr. Proton    ", 0, 5);
    draw_text_string(" (he changed his name from Blunderwitz  ", 0, 6);
    draw_text_string(" early in his career) decided he could  ", 0, 7);
    draw_text_string("   rule Earth with a new world order.   ", 0, 8);
    draw_text_string("                                        ", 0, 9);
    draw_text_string("After a terrible radiation accident that", 0, 10);
    draw_text_string(" altered his brain,  Dr. Proton took to ", 0, 11);
    draw_text_string("  the underworld and developed an army  ", 0, 12);
    draw_text_string(" of advanced robots -- called Techbots. ", 0, 13);
    draw_text_string("  The Techbots are extremely dangerous, ", 0, 14);
    draw_text_string(" and guard Dr. Proton's secret hideout. ", 0, 15);
    draw_text_string("    Every attempt by the military to    ", 0, 16);
    draw_text_string(" overcome Dr. Proton ended in disaster. ", 0, 17);
    draw_text_string("   It seems Dr. Proton's plan to rule   ", 0, 18);
    draw_text_string("        Earth is well underway...       ", 0, 19);
    draw_text_string("             Press any key.             ", 0, 24);
    restore_ega_palette(20);
    if (control_confirmation_state == 0)
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    wait_input_animated_sprite(39, 24);
    clear_video_page_region(0x1710);
    draw_text_string("                THE STORY               ", 0, 0);
    draw_text_string("   Self-proclaimed hero Duke Nukum is   ", 0, 2);
    draw_text_string("   Earth's final chance. Hired by the   ", 0, 3);
    draw_text_string("    CIA, Duke has orders to stop Dr.    ", 0, 4);
    draw_text_string("    Proton and rid the world of this    ", 0, 5);
    draw_text_string("  latest madman.  Armed only with his   ", 0, 6);
    draw_text_string("  pistol and his can-do attitude, Duke  ", 0, 7);
    draw_text_string("  is the one person who might stand a   ", 0, 8);
    draw_text_string("            chance of success.          ", 0, 9);
    show_episode_story_intro();
    if (control_confirmation_state == 0)
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    wait_input_animated_sprite(39, 24);
    clear_video_page_region(0x1710);
    draw_text_string("           KEYBOARD CONTROLS            ", 0, 0);
    draw_text_string("                                        ", 0, 1);
    draw_text_string(" The following keys control Duke:       ", 0, 2);
    draw_text_string("   LEFT ARROW  - Move Left              ", 0, 3);
    draw_text_string("   RIGHT ARROW - Move Right             ", 0, 4);
    draw_text_string("   CTRL        - Jump Upward            ", 0, 5);
    draw_text_string("   ALT         - Fire Nuclear Pistol    ", 0, 6);
    draw_text_string("                                        ", 0, 7);
    draw_text_string(" The UP ARROW is the ACTION KEY, which  ", 0, 8);
    draw_text_string(" will enable Duke to:                   ", 0, 9);
    draw_text_string("                                        ", 0, 10);
    draw_text_string("   1) Activate elevators, teleporters,  ", 0, 11);
    draw_text_string("      and time machines.                ", 0, 12);
    draw_text_string("   2) Read notes or monitors.           ", 0, 13);
    draw_text_string("   3) Open doors.                       ", 0, 14);
    draw_text_string("   4) Insert access cards, keys, and    ", 0, 15);
    draw_text_string("      other useful objects.             ", 0, 16);
    draw_text_string("                                        ", 0, 17);
    draw_text_string(" Note: When Duke has the grappling      ", 0, 18);
    draw_text_string(" hooks the UP ARROW will swing him      ", 0, 19);
    draw_text_string(" above a ledge if there is room.        ", 0, 20);
    draw_text_string("                                        ", 0, 21);
    draw_text_string(" Keyboard controls can be altered       ", 0, 22);
    draw_text_string(" within the \"Game Setup\" menu option.   ", 0, 23);
    draw_text_string("             Press any key.             ", 0, 24);
    if (control_confirmation_state == 0)
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    wait_input_animated_sprite(39, 24);
    clear_video_page_region(0x1710);
    draw_text_string("         IMPORTANT INFORMATION          ", 0, 0);
    draw_text_string("Duke Nukum needs food and soft drinks   ", 0, 2);
    draw_text_string("to keep him healthy!  Grab all the food ", 0, 3);
    draw_text_string("and drinks you can find (sometimes      ", 0, 4);
    draw_text_string("hidden in boxes).                       ", 0, 5);
    draw_text_string("Duke is armed with a CIA prototype      ", 0, 7);
    draw_text_string("Nuclear Pistol, which has proved to be  ", 0, 8);
    draw_text_string("extremely powerful in field tests. Let's", 0, 9);
    draw_text_string("hope it works in an actual mission!     ", 0, 10);
    draw_text_string("Dr. Proton has built several nuclear    ", 0, 12);
    draw_text_string("reactors to provide power for all of    ", 0, 13);
    draw_text_string("his Techbots and traps.  Duke should    ", 0, 14);
    draw_text_string("consider destroying these reactors a    ", 0, 15);
    draw_text_string("high priority.                          ", 0, 16);
    draw_text_string("It's possible that Duke will find many  ", 0, 18);
    draw_text_string("useful objects.  For example, keys can  ", 0, 19);
    draw_text_string("open doors, boots can help Duke jump    ", 0, 20);
    draw_text_string("higher, and extra pistols will increase ", 0, 21);
    draw_text_string("Duke's firepower. ", 0, 22);
    draw_text_string("             Press any key.             ", 0, 24);
    if (control_confirmation_state == 0)
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    wait_input_animated_sprite(39, 24);
    clear_video_page_region(0x1710);
    draw_text_string("         IMPORTANT INFORMATION          ", 0, 0);
    draw_text_string("Duke has unlimited chances (lives) to   ", 0, 2);
    draw_text_string("complete his mission, but every time    ", 0, 3);
    draw_text_string("Duke dies he will have to restart the   ", 0, 4);
    draw_text_string("current level from the beginning.  Duke ", 0, 5);
    draw_text_string("should consume drinks and food to keep  ", 0, 6);
    draw_text_string("his health high.                        ", 0, 7);
    draw_text_string("Each level Duke completes will bring    ", 0, 9);
    draw_text_string("him closer to finding Dr. Proton.  But  ", 0, 10);
    draw_text_string("Dr. Proton will watch Duke's every move ", 0, 11);
    draw_text_string("with an advanced security system (notice", 0, 12);
    draw_text_string("the video cameras that follow your every", 0, 13);
    draw_text_string("move!).  Destroying every camera on a   ", 0, 14);
    draw_text_string("level will earn you a secret bonus.     ", 0, 15);
    draw_text_string("There are several other secret bonuses  ", 0, 16);
    draw_text_string("you might discover.                     ", 0, 17);
    draw_text_string("You can only save and restore Duke's    ", 0, 19);
    draw_text_string("progress in the small hallways between  ", 0, 20);
    draw_text_string("levels.  Hint:  You should save after   ", 0, 21);
    draw_text_string("each level you complete.                ", 0, 22);
    draw_text_string("             Press any key.             ", 0, 24);
    if (control_confirmation_state == 0)
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    wait_input_animated_sprite(39, 24);
    clear_palette_entries(10);
}

/* Displays the save success message screen or message and waits for the associated input when
   required. */
void show_save_success_message(void)
{
    draw_framed_dialog_box(2, 3, 1);
    draw_text_string("   Your game is SAVED.  ", 3, 7);
    draw_text_string("      Press ENTER:      ", 3, 8);
    do {
        wait_input_animated_sprite(26, 8);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the save failure message screen or message and waits for the associated input when
   required. */
void show_save_failure_message(void)
{
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("   Incorrect number.    ", 3, 7);
    draw_text_string("Your game was NOT saved.", 3, 8);
    draw_text_string("                        ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the save unavailable message screen or message and waits for the associated input
   when required. */
void show_save_unavailable_message(void)
{
    draw_framed_dialog_box(7, 3, 2);
    draw_text_string("This option will be     ", 8, 7);
    draw_text_string("available after you play", 8, 8);
    draw_text_string("the first level.        ", 8, 9);
    draw_text_string("      Press ENTER:      ", 8, 10);
    do {
        wait_input_animated_sprite(31, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about card key and waits for player input. */
void show_secret_tip_card_key(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Find the key", 3, 7);
    draw_text_string("that goes here and press", 3, 8);
    draw_text_string("the UP ARROW.           ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about read notes and waits for player input. */
void show_secret_tip_read_notes(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Press the UP", 3, 7);
    draw_text_string("ARROW to read the notes.", 3, 8);
    draw_text_string("                        ", 3, 8);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about elevator and waits for player input. */
void show_secret_tip_elevator(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Press the UP", 3, 7);
    draw_text_string("ARROW to activate the   ", 3, 8);
    draw_text_string("ELEVATORS.              ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Toggles the sound setting, redraws its status, and waits for the toggle key to be released. */
void pascal toggle_sound_setting(register int text_x)
{
    draw_framed_dialog_box(text_x, 3, 2);
    outport(0x3ce, 5);
    while (last_keyboard_scan_code == 0x1f) {
    }
    draw_text_string("       Sound toggle", text_x, 7);
    if (sound_enabled = !sound_enabled) {
        draw_text_string("     The sound is ON", text_x, 9);
    } else {
        draw_text_string("     The sound is OFF", text_x, 9);
        outportb(0x61, inportb(0x61) & 0xfd);
    }
    delay(300);
    wait_input_animated_sprite(text_x + 24, 10);
    while (last_keyboard_scan_code == 0x1f) {
    }
}

/* Toggles hint mode and updates the displayed hint state. */
void pascal toggle_hint_mode(register int text_x)
{
    draw_framed_dialog_box(text_x, 3, 2);
    outport(0x3ce, 5);
    while (last_keyboard_scan_code == 0x23) {
    }
    draw_text_string("       Hint toggle ", text_x, 7);
    hint_mode_enabled = !hint_mode_enabled;
    if (hint_mode_enabled) {
        draw_text_string("     Hint mode is ON", text_x, 9);
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
    } else {
        draw_text_string("     Hint mode is OFF", text_x, 9);
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
    }
    wait_input_animated_sprite(text_x + 24, 10);
    while (last_keyboard_scan_code == 0x23) {
    }
}

/* Displays the paused state and waits for the player to resume or select another input. */
void pascal pause_until_resume_input(register int text_x)
{
    draw_framed_dialog_box(text_x, 3, 1);
    outport(0x3ce, 5);
    draw_text_string("       Game PAUSED. ", text_x, 7);
    while (last_keyboard_scan_code == 0x19) {
    }
    wait_input_animated_sprite(text_x + 24, 8);
}

/* Prompts the player for the for save slot and records the response. */
void pascal prompt_for_save_slot(register int text_x)
{
    draw_framed_dialog_box(text_x, 3, 2);
    draw_text_string("      Save a game.      ", text_x, 7);
    draw_text_string("    Which game number   ", text_x, 8);
    draw_text_string("  do you want to save?  ", text_x, 9);
    draw_text_string("      Choose (1-9):     ", text_x, 10);
    while (last_keyboard_scan_code == 0x1f) {
    }
    wait_input_animated_sprite(text_x + 20, 10);
}

/* Prompts the player for the for restore slot and records the response. */
void pascal prompt_for_restore_slot(register int text_x)
{
    draw_framed_dialog_box(text_x, 3, 2);
    draw_text_string("      Restore a game.   ", text_x, 7);
    draw_text_string("    Which game number   ", text_x, 8);
    draw_text_string("  do you want to load?  ", text_x, 9);
    draw_text_string("      Choose (1-9):     ", text_x, 10);
    while (last_keyboard_scan_code == 0x13) {
    }
    wait_input_animated_sprite(text_x + 20, 10);
}

/* Restores the prior timer vector, reprograms PIT channel zero, and silences the PC speaker. */
void restore_timer_interrupt_vector(void)
{
    outportb(0x43, 0x36);
    outportb(0x40, 0);
    outportb(0x40, 0);
    setvect(8, previous_timer_interrupt_vector);
    outportb(0x61, inportb(0x61) & 0xfd);
}

/* Waits for the for keyboard or joystick condition or input event. */
void pascal wait_for_keyboard_or_joystick(register int sprite_x, register int text_row)
{
    char button_1_state;
    char button_2_state;

    last_keyboard_scan_code = 0;
    button_1_state = inportb(0x201) & 0x10;
    button_2_state = inportb(0x201) & 0x20;
    while (last_keyboard_scan_code == 0 && button_1_state != 0 && button_2_state != 0) {
        button_1_state = inportb(0x201) & 0x10;
        button_2_state = inportb(0x201) & 0x20;
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3520, sprite_x, text_row * 8);
        delay(5);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x35c0, sprite_x, text_row * 8);
        delay(5);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3660, sprite_x, text_row * 8);
        delay(5);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3700, sprite_x, text_row * 8);
        delay(5);
    }
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x37a0, sprite_x, text_row * 8);
}

/* Draws the get ready message using the active page and graphics resources. */
void draw_get_ready_message(void)
{
    draw_page_index = 0;
    draw_framed_dialog_box(2, 5, 1);
    draw_text_string("     Get ready Duke,    ", 3, 11);
    draw_text_string("    you're going in!!   ", 3, 12);
}

/* Draws the game setup menu using the active page and graphics resources. */
void pascal draw_game_setup_menu(register int text_x)
{
    draw_text_string("        GAME SETUP", text_x, 6);
    draw_text_string("      J)oystick mode", text_x, 8);
    draw_text_string("      K)eyboard mode", text_x, 9);
    draw_text_string("      S)ound toggle", text_x, 10);
    draw_text_string("      H)int toggle", text_x, 11);
}

/* Displays the level restart prompt and returns the player's choice. */
void confirm_level_restart(void)
{
    do {
    } while (last_keyboard_scan_code == 0x44);
    draw_framed_dialog_box(2, 1, 1);
    draw_text_string("Are you sure you want to", 3, 3);
    draw_text_string("RESTART the level(Y/N)? ", 3, 4);
    wait_input_animated_sprite(26, 4);
    control_right_pressed = 0;
    control_down_pressed = 0;
}

/* Displays the secret-tip card about soda and waits for player input. */
void show_secret_tip_soda(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Drink soda  ", 3, 7);
    draw_text_string("to increase your health!", 3, 8);
    draw_text_string("                        ", 3, 8);
    draw_text_string("      Press ENTER:      ", 3, 10);
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about turkey and waits for player input. */
void show_secret_tip_turkey(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Eat turkey  ", 3, 7);
    draw_text_string("to increase your health!", 3, 8);
    draw_text_string("                        ", 3, 8);
    draw_text_string("      Press ENTER:      ", 3, 10);
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about nuclear and waits for player input. */
void show_secret_tip_nuclear(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: The nuclear ", 3, 7);
    draw_text_string("molecule increases your ", 3, 8);
    draw_text_string("health to maximum!      ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about open door and waits for player input. */
void show_secret_tip_open_door(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Press the UP", 3, 7);
    draw_text_string("ARROW to open the DOOR.", 3, 8);
    draw_text_string("                        ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about robohand and waits for player input. */
void show_secret_tip_robohand(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Press the UP", 3, 7);
    draw_text_string("ARROW here after you   ", 3, 8);
    draw_text_string("have found the ROBOHAND.", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about access card and waits for player input. */
void show_secret_tip_access_card(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Find the    ", 3, 7);
    draw_text_string("ACCESS CARD and press   ", 3, 8);
    draw_text_string("the UP ARROW here.      ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about transporter and waits for player input. */
void show_secret_tip_transporter(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Press the UP", 3, 7);
    draw_text_string("ARROW to activate the   ", 3, 8);
    draw_text_string("TRANSPORTER.            ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Draws the keyboard binding values using the active page and graphics resources. */
void pascal draw_keyboard_binding_values(register int text_x)
{
    draw_text_string(keyboard_character_map_entries[(unsigned char)key_binding_up].display_label, text_x + 17, 9);
    draw_text_string(keyboard_character_map_entries[(unsigned char)key_binding_down].display_label, text_x + 17, 10);
    draw_text_string(keyboard_character_map_entries[(unsigned char)key_binding_left].display_label, text_x + 17, 11);
    draw_text_string(keyboard_character_map_entries[(unsigned char)key_binding_right].display_label, text_x + 17, 12);
    draw_text_string(keyboard_character_map_entries[(unsigned char)key_binding_fire].display_label, text_x + 17, 13);
    draw_text_string(keyboard_character_map_entries[(unsigned char)key_binding_jump].display_label, text_x + 17, 14);
}

/* Draws the in game help menu using the active page and graphics resources. */
void pascal draw_in_game_help_menu(register int text_x)
{
    draw_text_string("      DUKE HELP MENU", text_x, 4);
    draw_text_string("      --------------", text_x, 5);
    draw_text_string("      S)ave a game", text_x, 7);
    draw_text_string("      I)nstructions", text_x, 8);
    draw_text_string("      G)ame Setup", text_x, 9);
    draw_text_string("      H)igh scores", text_x, 10);
    draw_text_string("    F10) Restart Level", text_x, 11);
}

/* Displays the secret-tip card about insert card and waits for player input. */
void show_secret_tip_insert_card(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: Find the    ", 3, 7);
    draw_text_string("ACCESS CARD first and   ", 3, 8);
    draw_text_string("then insert it in here. ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the secret-tip card about lock key and waits for player input. */
void show_secret_tip_lock_key(void)
{
    last_keyboard_scan_code = 0;
    request_priority_sound_effect(0x19);
    draw_framed_dialog_box(2, 3, 2);
    draw_text_string("Secret Tip: You need the", 3, 7);
    draw_text_string("correct key before      ", 3, 8);
    draw_text_string("you can use this lock.  ", 3, 9);
    draw_text_string("      Press ENTER:      ", 3, 10);
    enable();
    do {
        wait_input_animated_sprite(26, 10);
        control_right_pressed = 0;
        control_down_pressed = 0;
    } while (last_keyboard_scan_code != 0x1c);
    disable();
    last_keyboard_scan_code = 0;
    timer_tick_counter = 0;
    select_and_show_video_page();
}

/* Displays the save location warning screen or message and waits for the associated input when
   required. */
void pascal show_save_location_warning(register int text_x)
{
    draw_framed_dialog_box(text_x, 2, 2);
    draw_text_string(" You can only save a game", text_x, 6);
    draw_text_string("  in the main hallways.", text_x, 7);
    do {
    } while (last_keyboard_scan_code == 0x1f);
    wait_input_animated_sprite(text_x + 24, 7);
}

/* Displays the keyboard controls help screen or message and waits for the associated input when
   required. */
void pascal show_keyboard_controls_help(register int text_x)
{
    draw_text_string("Important Keys:         ", text_x + 1, 4);
    draw_text_string("  CTRL - Jump           ", text_x + 1, 5);
    draw_text_string("  ALT  - Fire           ", text_x + 1, 6);
    draw_text_string("  Cursor Keys - Move Man", text_x + 1, 7);
    draw_text_string("  Up Cursor - Action Key", text_x + 1, 8);
    draw_text_string("                        ", text_x + 1, 9);
    draw_text_string("Change keys by choosing ", text_x + 1, 10);
    draw_text_string("option \"K\" in HELP MENU.", text_x + 1, 11);
    draw_text_string("                        ", text_x + 1, 12);
    draw_text_string("  \"S\" - Toggle Sound    ", text_x + 1, 13);
    draw_text_string("  \"H\" - Toggle Hint Mode", text_x + 1, 14);
    draw_text_string("  F10 - Restart Level   ", text_x + 1, 15);
    draw_text_string("  ESC - Quit Game       ", text_x + 1, 16);
    draw_text_string("  \"<\" - Decrease Speed  ", text_x + 1, 17);
    draw_text_string("  \">\" - Increase Speed  ", text_x + 1, 18);
    draw_text_string("                        ", text_x + 1, 19);
    draw_text_string("     Press any key.     ", text_x + 1, 20);
    while ((last_keyboard_scan_code & 0x80) == 0) {
    }
}

/* Draws the high score table using the active page and graphics resources. */
void pascal draw_high_score_table(int text_x)
{
    char number_text[20];
    register int i;

    draw_text_panel_background(text_x);
    draw_text_string(" --- HIGH  SCORES ---", text_x + 2, 3);
    for (i = 0; i < 8; ++i) {
        ltoa((long)i + 1L, number_text, 10);
        draw_text_string(number_text, text_x + 2, i * 2 + 5);
        draw_text_string(".", text_x + 3, i * 2 + 5);
        ltoa(high_score_values[i], number_text, 10);
        draw_text_string(number_text, text_x + 6, i * 2 + 5);
        draw_text_string(high_score_player_names[i], text_x + 14, i * 2 + 5);
    }
}

/* Writes the high score table to the game's selected file or data buffer. */
void save_high_score_table(void)
{
    FILE *score_file;
    register int i;

#if EPISODE == 1
    score_file = fopen("HIGHS.DN1", "w+");
#elif EPISODE == 2
    score_file = fopen("HIGHS.dn2", "w+");
#else
    score_file = fopen("HIGHS.dn3", "w+");
#endif
    for (i = 0; i < 10; i++) {
        fprintf(score_file, "%lu", high_score_values[i]);
        fprintf(score_file, "%s\n", high_score_player_names[i]);
    }
    fclose(score_file);
}

/* Programs PIT channel zero and installs the timer-and-sound handler at interrupt vector 8. */
void install_timer_interrupt(void)
{
    outportb(0x43, 0x36);
    outportb(0x40, 0x51);
    outportb(0x40, 0x20);
    disable();
    sound_interrupt_active_state = 0;
    current_sound_priority = 0;
    timer_tick_counter = 0;
    sound_enabled = 1;
    previous_timer_interrupt_vector = getvect(8);
    setvect(8, timer_sound_interrupt_handler);
    enable();
}

/* Displays the instruction screen screen or message and waits for the associated input when
   required. */
void pascal show_instruction_screen(int text_x)
{
    draw_text_panel_background(text_x);
    outport(0x3ce, 5);
    draw_text_string("       Instructions ", text_x, 3);
    show_keyboard_controls_help(text_x);
    wait_input_animated_sprite(26, 20);
}

/* Displays the loading status screen or message and waits for the associated input when
   required. */
void show_loading_status(void)
{
    draw_framed_dialog_box(7, 5, 1);
    draw_text_string("   Loading Duke Nukum,", 8, 11);
    draw_text_string("      please wait...  ", 8, 12);
}

/* Displays the joystick mode status screen or message and waits for the associated input when
   required. */
void pascal show_joystick_mode_status(int text_x)
{
    draw_framed_dialog_box(text_x, 3, 7);
    outport(0x3ce, 5);
    draw_text_string("      Joystick mode", text_x, 7);
    delay(100);
}

/* Draws the current planar sprite using the active page and graphics resources. */
void draw_current_planar_sprite(void)
{
    select_draw_page(draw_page_index);
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2800, 0x24, episode_sprite_resource_table + 0xa0);
    select_draw_page(!draw_page_index);
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x2800, 0x24, episode_sprite_resource_table + 0xa0);
}

/* Draws the alternate planar sprite using the active page and graphics resources. */
void pascal draw_alternate_planar_sprite(char far* bitmap)
{
    select_draw_page(draw_page_index);
    blit_planar_sprite_rows(bitmap, alternate_sprite_draw_offset + 0x1e, episode_sprite_resource_table + 0xa0);
    select_draw_page(!draw_page_index);
    blit_planar_sprite_rows(bitmap, alternate_sprite_draw_offset + 0x1e, episode_sprite_resource_table + 0xa0);
    alternate_sprite_draw_offset += 2;
}

/* Writes the keyboard bindings to the game's selected file or data buffer. */
void save_keyboard_bindings(char far *filename)
{
    FILE *bindings_file;

    bindings_file = fopen(filename, "wb");
    fputc(key_binding_up, bindings_file);
    fputc(key_binding_down, bindings_file);
    fputc(key_binding_left, bindings_file);
    fputc(key_binding_right, bindings_file);
    fputc(key_binding_fire, bindings_file);
    fputc(key_binding_jump, bindings_file);
    fclose(bindings_file);
}

/* Loads the keyboard bindings from the caller-selected file or resource. */
void load_keyboard_bindings(char far *filename)
{
    FILE *bindings_file;

    bindings_file = fopen(filename, "rb");
    if (bindings_file) {
        key_binding_up = fgetc(bindings_file);
        key_binding_down = fgetc(bindings_file);
        key_binding_left = fgetc(bindings_file);
        key_binding_right = fgetc(bindings_file);
        key_binding_fire = fgetc(bindings_file);
        key_binding_jump = fgetc(bindings_file);
    }
    fclose(bindings_file);
}

/* Restores the game state from slot from its saved state. */
void pascal restore_game_state_from_slot(char slot_number)
{
    char previous_scan_code;
    FILE *save_file;
    char far *save_filename;

    previous_scan_code = last_keyboard_scan_code;
#if EPISODE == 1
    save_filename = "saved .dn1";
#elif EPISODE == 2
    save_filename = "saved .dn2";
#else
    save_filename = "saved .dn3";
#endif
    save_filename[5] = slot_number;
    save_file = fopen(save_filename, "rb");
    if (save_file == 0) {
        draw_framed_dialog_box(7, 2, 1);
        draw_text_string("     Game not found!!", 7, 5);
        fclose(save_file);
        while (last_keyboard_scan_code == previous_scan_code) {
        }
        last_keyboard_scan_code = 0;
        while (last_keyboard_scan_code == 0) {
        }
        game_session_abort_flag = 1;
        return;
    }
    game_session_abort_flag = 0;
    level_scroll_x = getw(save_file);
    level_map_y_offset = getw(save_file);
    player_screen_x = getw(save_file);
    player_screen_y = getw(save_file);
    current_level_index = getw(save_file);
    world_actor_count = getw(save_file);
    access_card_or_door_state = getw(save_file);
    player_contact_state = getw(save_file);
    title_graphic_frame_index = getw(save_file);
    robohand_box_active_state = getw(save_file);
    hint_revealed_object_7 = getw(save_file);
    hint_revealed_object_9 = getw(save_file);
    hint_revealed_object_2 = getw(save_file);
    hint_revealed_object_11 = getw(save_file);
    hint_revealed_object_10 = getw(save_file);
    hint_revealed_object_4 = getw(save_file);
    hint_revealed_object_5 = getw(save_file);
    transporter_hint_pending = getw(save_file);
    hint_revealed_object_6 = getw(save_file);
    hint_revealed_object_1 = getw(save_file);
    hint_revealed_object_3 = getw(save_file);
    hint_revealed_object_8 = getw(save_file);
    if (hint_mode_enabled == 0) {
        hint_revealed_object_7 = hint_revealed_object_9 = hint_revealed_object_2 = hint_revealed_object_11 = hint_revealed_object_10 = hint_revealed_object_4 = hint_revealed_object_5 = transporter_hint_pending = hint_revealed_object_6 = hint_revealed_object_1 = hint_revealed_object_3 = hint_revealed_object_8 = 0;
    }
    fscanf(save_file, "%ld", &player_score);
    fclose(save_file);
}

/* Draws the high score name screen using the active page and graphics resources. */
void draw_high_score_name_screen(void)
{
    draw_text_string("       High Score       ", 8, 5);
    draw_text_string("------------------------", 8, 6);
    draw_text_string("                        ", 8, 7);
    draw_text_string("Enter your name into the", 8, 8);
    draw_text_string("Duke Nukum Hame of FAME.", 8, 9);
    draw_text_string("       ----------       ", 8, 11);
    draw_text_string(" Press ENTER when done. ", 8, 13);
}

/* Waits for the controller button condition or input event. */
void wait_controller_button(void)
{
    draw_framed_dialog_box(7, 0, 1);
    if (control_confirmation_state != 0) {
        draw_text_string("\040\040\040\040\040Press a button..\040\040\040", 7, 1);
    } else {
        draw_text_string("\040\040\040\040\040\040Press any key.\040\040\040\040", 7, 1);
    }
}

/* Loads the high score table from the caller-selected file or resource. */
void load_high_score_table(void)
{
    FILE *score_file;
    register int i;

#if EPISODE == 1
    score_file = fopen("HIGHS.DN1", "r");
#elif EPISODE == 2
    score_file = fopen("HIGHS.dn2", "r");
#else
    score_file = fopen("HIGHS.dn3", "r");
#endif
    if (score_file == 0) {
        high_score_values[0] = 40000L;
        strcpy(high_score_player_names[0], "TODD");
        high_score_entry_1_alias[0] = 30000L;
        strcpy(high_score_player_names[1], "SCOTT");
        high_score_entry_2_alias[0] = 20000L;
        strcpy(high_score_player_names[2], "GEORGE");
        high_score_entry_3_alias[0] = 10000L;
        strcpy(high_score_player_names[3], "AL");
        high_score_entry_4_alias[0] = 500L;
        strcpy(high_score_player_names[4], "JOHN");
    } else {
        for (i = 0; i < 10; i++) {
            fscanf(score_file, "%lu", &high_score_values[i]);
            fscanf(score_file, "%[^\n]s", high_score_player_names[i]);
        }
    }
    fclose(score_file);
}

/* Samples joystick button bits and marks the joystick connected only when both tested buttons
   are released. */
void detect_joystick_connection(void)
{
    char button_1_state;
    char button_2_state;

    joystick_enabled = 1;
    button_1_state = inportb(0x201) & 0x10;
    button_2_state = inportb(0x201) & 0x20;
    if (button_1_state == 0) {
        joystick_enabled = 0;
    } else if (button_2_state == 0) {
        joystick_enabled = 0;
    }
}

/* Advances the game tick, plays the next queued PC-speaker period, and chains the BIOS timer at
   its divider. */
void interrupt timer_sound_interrupt_handler(void)
{
    register unsigned int period;

    if (pending_sound_priority_flag != 0) {
        pending_sound_priority_flag = 0;
        current_sound_sample_position = 0;
        sound_interrupt_active_state = 1;
    }

    /* The table holds byte-addressed sample bases; the timer reads word periods. */
    if (((int far *)sound_sample_pointer_table[(unsigned char)pending_sound_effect_index])[current_sound_sample_position] == -1) {
        sound_interrupt_active_state = 0;
        current_sound_priority = 0;
        outportb(0x61, inportb(0x61) & 0xfd);
    }

    if (sound_interrupt_active_state != 0) {
        period = ((int far *)sound_sample_pointer_table[(unsigned char)pending_sound_effect_index])[current_sound_sample_position];
        if (period == 0 && sound_enabled != 0) {
            outportb(0x61, inportb(0x61) & 0xfc);
        } else if (sound_enabled != 0) {
            outportb(0x43, 0xb6);
            outportb(0x42, period & 0x100);
            outportb(0x42, period >> 8);
            outportb(0x61, inportb(0x61) | 3);
        }
        ++current_sound_sample_position;
    } else {
        outportb(0x61, inportb(0x61) & 0xfd);
    }

    ++timer_tick_counter;
    ++bios_timer_chain_divider;
    if (bios_timer_chain_divider == 8) {
        bios_timer_chain_divider = 0;
        previous_timer_interrupt_vector();
    } else {
        outportb(0x20, 0x20);
    }
}

/* Displays the episode story intro screen or message and waits for the associated input when
   required. */
void show_episode_story_intro(void)
{
#if EPISODE == 1
    draw_text_string("      EPISODE ONE:  SHRAPNEL CITY       ", 0, 12);
    draw_text_string("  Your mission as Duke Nukum:  A plane  ", 0, 14);
    draw_text_string(" will fly over Dr. Proton's sieged city ", 0, 15);
    draw_text_string("   and drop Duke on a huge skyscraper.  ", 0, 16);
    draw_text_string(" Duke must proceed to Dr. Proton's well ", 0, 17);
    draw_text_string(" guarded hideout believed to be hidden  ", 0, 18);
    draw_text_string("  deep underground. Dr. Proton must be  ", 0, 19);
    draw_text_string("    stopped or the world is doomed!     ", 0, 20);
    draw_text_string("             Press any key.             ", 0, 24);
#elif EPISODE == 2
    draw_text_string("    EPISODE TWO - MISSION: MOONBASE     ", 0, 11);
    draw_text_string("   When we last saw Duke he had just    ", 0, 13);
    draw_text_string("   barely survived an encounter with    ", 0, 14);
    draw_text_string("  Dr. Proton. Somehow, Duke managed to  ", 0, 15);
    draw_text_string(" penetrate Proton's captured city, beat ", 0, 16);
    draw_text_string(" his Techbot guards,  and forced Proton ", 0, 17);
    draw_text_string("     to flee to his moonbase. Using    ", 0, 18);
    draw_text_string("  Dr. Proton's time transport machine,  ", 0, 19);
    draw_text_string("  Duke has decided to chase him to the  ", 0, 20);
    draw_text_string("   Moon, and stop him cold...  (well,   ", 0, 21);
    draw_text_string("      at least that's the plan!)        ", 0, 22);
    draw_text_string("             Press any key.             ", 0, 24);
#else
    draw_text_string(" EPISODE THREE:  TRAPPED IN THE FUTURE! ", 0, 11);
    draw_text_string("    Again, Duke foiled the mad plans    ", 0, 12);
    draw_text_string("    of Dr. Proton.  His secret lunar    ", 0, 13);
    draw_text_string("  fortress now wrecked, Dr. Proton has  ", 0, 14);
    draw_text_string(" transported himself back to Earth, and ", 0, 15);
    draw_text_string("  used his time machine to hide in the  ", 0, 16);
    draw_text_string("   Earth's future. There he will once   ", 0, 17);
    draw_text_string("  again create a huge army of Techbots  ", 0, 18);
    draw_text_string("   that will allow him to control the   ", 0, 19);
    draw_text_string(" world.  Of course, Duke will not stand ", 0, 20);
    draw_text_string("   for this, and although he'd rather   ", 0, 21);
    draw_text_string("   watch Oprah,  he heads off to stop   ", 0, 22);
    draw_text_string("       Dr. Proton one more time...      ", 0, 23);
    draw_text_string("             Press any key.             ", 0, 24);
#endif
}

/* Wait out an 0xE0 extended-key prefix in the keyboard byte, then return it
   with the release bit cleared (interrupts left disabled). */
/* Consumes an extended-key prefix and returns the normalized keyboard scan code. */
char normalize_extended_key_code(void)
{
    if (last_keyboard_scan_code == 0xe0) {
        while (last_keyboard_scan_code == 0xe0) {
        }
        disable();
        return last_keyboard_scan_code & 0x7f;
    }
    return last_keyboard_scan_code;
}

/* Converts an unsigned score to digits and draws it with the numeric glyph resource. */
void pascal draw_unsigned_score_value(long score, int score_x, int text_row)
{
    char score_digits[16];
    register int digit_index;
    register int digit_count;

    ultoa(score, score_digits, 10);
    digit_count = strlen(score_digits);
    digit_index = digit_count - 1;
    for (; digit_index >= 0; --digit_index) {
        select_draw_page(1);
        blit_planar_masked_glyph(font_glyph_data_buffer + (score_digits[digit_count - digit_index - 1] - '0') * 40 + 0x410,
                                 score_x - digit_index, text_row * 8);
        select_draw_page(0);
        blit_planar_masked_glyph(font_glyph_data_buffer + (score_digits[digit_count - digit_index - 1] - '0') * 40 + 0x410,
                                 score_x - digit_index, text_row * 8);
    }
    select_draw_page(!draw_page_index);
}

/* Wait for a key or joystick button, cycling a 4-frame animation at (x, y). */
/* Waits for keyboard or joystick input while cycling the four-frame sprite animation at the
   requested position. */
void pascal wait_input_animated_sprite(register int sprite_x, register int text_row)
{
    char button_1_state = 1;
    char button_2_state = 1;

    last_keyboard_scan_code = 0;
    if (joystick_enabled != 0) {
        wait_joystick_button_release();
        button_1_state = inportb(0x201) & 0x10;
        button_2_state = inportb(0x201) & 0x20;
    }
    while (last_keyboard_scan_code == 0 && button_1_state != 0 && button_2_state != 0) {
        if (joystick_enabled != 0) {
            button_1_state = inportb(0x201) & 0x10;
            button_2_state = inportb(0x201) & 0x20;
        }
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3520, sprite_x, text_row * 8);
        delay(5);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x35c0, sprite_x, text_row * 8);
        delay(5);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3660, sprite_x, text_row * 8);
        delay(5);
        blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x3700, sprite_x, text_row * 8);
        delay(5);
    }
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x37a0, sprite_x, text_row * 8);
}

/* ============================================================================================
   Screen templates, bitmaps and text
   Full-screen backgrounds and frames, the title/credits/ending bitmaps, text output,
   sound banks, episode dialogues and the keyboard remapping screen.
   ============================================================================================ */

/* Draws the fixed planar background and border template into the selected video page. */
void draw_video_page_template(void)
{
    register int video_offset;

    video_offset = 0x280;
    outport(0x3ce, 0x105);
    do {
        blit_bitmap_to_video_page(0x3000, video_offset);
        blit_bitmap_to_video_page(0x3020, video_offset + 0x1c);
        video_offset += 0x280;
    } while (video_offset < 0x1b80);
    video_offset = 2;
    do {
        blit_bitmap_to_video_page(0x3040, video_offset);
        blit_bitmap_to_video_page(0x3060, video_offset + 0x1b80);
        video_offset += 2;
    } while (video_offset < 0x1c);
    blit_bitmap_to_video_page(0x31c0, 0x141c);
    blit_bitmap_to_video_page(0x31c0, 0x065c);
    blit_bitmap_to_video_page(0x31c0, 0x0c9c);
    blit_bitmap_to_video_page(0x3080, 0);
    blit_bitmap_to_video_page(0x30a0, 0x001c);
    blit_bitmap_to_video_page(0x30c0, 0x1b9c);
    blit_bitmap_to_video_page(0x30e0, 0x1b80);
    blit_bitmap_to_video_page(0x3340, 0x1b8b);
    blit_bitmap_to_video_page(0x3360, 0x1b8d);
    blit_bitmap_to_video_page(0x3380, 0x1b8f);
    blit_bitmap_to_video_page(0x33a0, 0x1b91);
}

/* Draws the framed page template on both video pages before a menu or dialog is shown. */
void draw_page_frame_template(void)
{
    register int row_offset;
    register int page_index;

    page_index = 0;
    outport(0x3ce, 0x0105);
    draw_video_page_template();
    do {
        ++page_index;
        select_draw_page(page_index - 1);
        blit_bitmap_to_video_page(0x3080, 0);
        blit_bitmap_to_video_page(0x30a0, 0x001c);
        blit_bitmap_to_video_page(0x30c0, 0x1b9c);
        blit_bitmap_to_video_page(0x30e0, 0x1b80);
        blit_bitmap_to_video_page(0x3100, 0x001e);
        blit_bitmap_to_video_page(0x3100, 0x0020);
        blit_bitmap_to_video_page(0x3100, 0x0022);
        blit_bitmap_to_video_page(0x3100, 0x0024);
        blit_bitmap_to_video_page(0x3120, 0x0026);
        blit_bitmap_to_video_page(0x3160, 0x1ba6);
        for (row_offset = 0x0280; row_offset < 0x1b80; row_offset += 0x0280)
            blit_bitmap_to_video_page(0x3140, row_offset + 0x0026);
        blit_bitmap_to_video_page(0x3100, 0x141e);
        blit_bitmap_to_video_page(0x3100, 0x0c9e);
        blit_bitmap_to_video_page(0x3100, 0x1420);
        blit_bitmap_to_video_page(0x3100, 0x0ca0);
        blit_bitmap_to_video_page(0x3100, 0x1422);
        blit_bitmap_to_video_page(0x3100, 0x0ca2);
        blit_bitmap_to_video_page(0x3100, 0x1424);
        blit_bitmap_to_video_page(0x3100, 0x0ca4);
        blit_bitmap_to_video_page(0x31e0, 0x1426);
        blit_bitmap_to_video_page(0x31e0, 0x0ca6);
        blit_bitmap_to_video_page(0x3100, 0x1b9e);
        blit_bitmap_to_video_page(0x3100, 0x1ba0);
        blit_bitmap_to_video_page(0x3100, 0x1ba2);
        blit_bitmap_to_video_page(0x3100, 0x1ba4);
        blit_bitmap_to_video_page(0x3100, 0x065e);
        blit_bitmap_to_video_page(0x3480, 0x0660);
        blit_bitmap_to_video_page(0x34a0, 0x0662);
        blit_bitmap_to_video_page(0x3100, 0x0664);
        blit_bitmap_to_video_page(0x34c0, 0x0020);
        blit_bitmap_to_video_page(0x34e0, 0x0022);
        blit_bitmap_to_video_page(0x33c0, 0x141f);
        blit_bitmap_to_video_page(0x33e0, 0x1421);
        blit_bitmap_to_video_page(0x3400, 0x1423);
        blit_bitmap_to_video_page(0x3420, 0x0c9f);
        blit_bitmap_to_video_page(0x3440, 0x0ca1);
        blit_bitmap_to_video_page(0x3460, 0x0ca3);
        blit_bitmap_to_video_page(0x31e0, 0x0666);
    } while (page_index == 1);
}

/* Draws the text panel background using the active page and graphics resources. */
void pascal draw_text_panel_background(int x_offset)
{
    register int video_offset;
    register int column_offset;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    if (x_offset == 2)
        select_draw_page(draw_page_index);
    else
        select_draw_page(0);

    for (video_offset = 0; video_offset < 10; video_offset++) {
        for (column_offset = x_offset; column_offset < x_offset + 26; column_offset += 2)
            blit_bitmap_to_video_page(0x3220, video_offset * 640 + column_offset + 640);
    }

    blit_bitmap_to_video_page(0x3240, x_offset + 640);
    blit_bitmap_to_video_page(0x3260, x_offset + 664);
    blit_bitmap_to_video_page(0x3280, x_offset + 0x1900);
    blit_bitmap_to_video_page(0x32a0, x_offset + 0x1918);

    for (video_offset = 0x500; video_offset < 0x16a8; video_offset += 640) {
        blit_bitmap_to_video_page(0x32c0, video_offset + x_offset);
        blit_bitmap_to_video_page(0x32e0, video_offset + x_offset + 24);
    }

    for (video_offset = 0x282; video_offset < 0x298; video_offset += 2) {
        blit_bitmap_to_video_page(0x3300, video_offset + x_offset);
        blit_bitmap_to_video_page(0x3320, video_offset + x_offset + 0x1680);
    }
}

/* Writes the supplied text and attribute bytes directly to the requested B800 text-memory
   position. */
void pascal draw_text_at_video_address(char x, char y, char far *text, char attribute)
{
    register int i = 0;
    char far *screen = (char far *)MK_FP(0xB800, 0);

    while (text[i] != 0) {
        *(screen + i * 2 + x * 2 + y * 160) = text[i];
        *(screen + i * 2 + x * 2 + y * 160 + 1) = attribute;
        ++i;
    }
}

/* print_ordering_information reconstructed candidate */
/* Prints the episode-specific ordering information and license text in text mode. */
void print_ordering_information(void)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#if EPISODE == 1
    draw_text_at_video_address(0, 0, "\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", 31);
    draw_text_at_video_address(0, 1, "\xB0\xB0\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF", 31);
    draw_text_at_video_address(0, 2, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(9, 2, "\x48\x4F\x57\x20\x54\x4F\x20\x4F\x52\x44\x45\x52\x20\x54\x48\x45\x20\x52\x45\x4D\x41\x49\x4E\x49\x4E\x47\x20\x54\x57\x4F\x20\x49\x4E\x43\x52\x45\x44\x49\x42\x4C\x45\x20\x45\x50\x49\x53\x4F\x44\x45\x53\x20\x4F\x46\x20\x44\x55\x4B\x45\x20\x4E\x55\x4B\x55\x4D", 30);
    draw_text_at_video_address(0, 3, "\xB0\xB0\xC6\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB5", 31);
    draw_text_at_video_address(0, 4, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 5, "\xB0\xB0\xB3\x20\x54\x68\x65\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x76\x6F\x6C\x75\x6D\x65\x73\x20\x6F\x66\x20\x44\x55\x4B\x45\x20\x4E\x55\x4B\x55\x4D\x20\x68\x61\x76\x65\x20\x6D\x6F\x72\x65\x20\x6E\x65\x77\x20\x67\x72\x61\x70\x68\x69\x63\x73\x20\x74\x68\x61\x6E\x20\x61\x6C\x6C\x20\x62\x75\x74\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 6, "\xB0\xB0\xB3\x20\x74\x68\x65\x20\x6C\x61\x72\x67\x65\x73\x74\x20\x63\x6F\x6D\x6D\x65\x72\x63\x69\x61\x6C\x20\x67\x61\x6D\x65\x73\x21\x20\x20\x49\x6E\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x74\x77\x6F\x20\x79\x6F\x75\x27\x6C\x6C\x20\x74\x72\x61\x76\x65\x6C\x20\x74\x6F\x20\x74\x68\x65\x20\x6D\x6F\x6F\x6E\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 7, "\xB0\xB0\xB3\x20\x61\x6E\x64\x20\x62\x61\x74\x74\x6C\x65\x20\x44\x72\x2E\x20\x50\x72\x6F\x74\x6F\x6E\x20\x61\x73\x20\x68\x65\x20\x70\x6C\x61\x6E\x73\x20\x68\x69\x73\x20\x73\x65\x63\x6F\x6E\x64\x20\x61\x73\x73\x61\x75\x6C\x74\x20\x6F\x6E\x20\x45\x61\x72\x74\x68\x2E\x20\x20\x41\x6E\x64\x20\x69\x6E\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 8, "\xB0\xB0\xB3\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x74\x68\x72\x65\x65\x20\x79\x6F\x75\x27\x6C\x6C\x20\x77\x61\x72\x70\x20\x74\x6F\x20\x74\x68\x65\x20\x45\x61\x72\x74\x68\x27\x73\x20\x66\x75\x74\x75\x72\x65\x20\x74\x6F\x20\x73\x74\x6F\x70\x20\x44\x72\x2E\x20\x50\x72\x6F\x74\x6F\x6E\x20\x66\x72\x6F\x6D\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 9, "\xB0\xB0\xB3\x20\x63\x6F\x6D\x70\x6C\x65\x74\x69\x6E\x67\x20\x68\x69\x73\x20\x6D\x61\x6E\x69\x61\x63\x61\x6C\x20\x70\x6C\x61\x6E\x20\x74\x6F\x20\x72\x75\x6C\x65\x20\x74\x68\x65\x20\x77\x6F\x72\x6C\x64\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 10, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 11, "\xB0\xB0\xB3\x20\x59\x6F\x75\x20\x6D\x61\x79\x20\x6F\x72\x64\x65\x72\x20\x74\x68\x65\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x76\x6F\x6C\x75\x6D\x65\x73\x20\x6F\x66\x20\x44\x55\x4B\x45\x20\x4E\x55\x4B\x55\x4D\x20\x66\x6F\x72\x20\x6F\x6E\x6C\x79\x20\x24\x33\x30\x20\x28\x70\x6C\x75\x73\x20\x24\x33\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 12, "\xB0\xB0\xB3\x20\x73\x68\x69\x70\x70\x69\x6E\x67\x20\x70\x6C\x65\x61\x73\x65\x29\x2E\x20\x20\x59\x6F\x75\x27\x6C\x6C\x20\x61\x6C\x73\x6F\x20\x67\x65\x74\x20\x74\x68\x65\x20\x63\x75\x72\x72\x65\x6E\x74\x20\x76\x65\x72\x73\x69\x6F\x6E\x20\x6F\x66\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x6E\x65\x2C\x20\x74\x68\x65\x20\xB3", 31);
    draw_text_at_video_address(0, 13, "\xB0\xB0\xB3\x20\x73\x65\x63\x72\x65\x74\x20\x63\x68\x65\x61\x74\x20\x63\x6F\x64\x65\x2C\x20\x74\x68\x65\x20\x68\x69\x6E\x74\x73\x20\x61\x6E\x64\x20\x74\x72\x69\x63\x6B\x73\x20\x73\x68\x65\x65\x74\x2C\x20\x70\x6C\x75\x73\x20\x61\x63\x63\x65\x73\x73\x20\x74\x6F\x20\x74\x68\x65\x20\x41\x70\x6F\x67\x65\x65\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 14, "\xB0\xB0\xB3\x20\x68\x69\x6E\x74\x73\x20\x6C\x69\x6E\x65\x21\x20\x20\x50\x4C\x55\x53\x2C\x20\x79\x6F\x75\x27\x6C\x6C\x20\x67\x65\x74\x20\x73\x65\x76\x65\x72\x61\x6C\x20\x6F\x66\x20\x41\x70\x6F\x67\x65\x65\x27\x73\x20\x61\x6D\x61\x7A\x69\x6E\x67\x20\x6E\x65\x77\x20\x67\x61\x6D\x65\x73\x21\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 15, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 16, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(4, 16, "\x4F\x72\x64\x65\x72\x20\x4E\x4F\x57\x20\x62\x79\x20\x63\x61\x6C\x6C\x69\x6E\x67\x20\x54\x4F\x4C\x4C\x20\x46\x52\x45\x45\x3A\x20\x20\x31\x2D\x38\x30\x30\x2D\x38\x35\x32\x2D\x35\x36\x35\x39\x20\x20\x28\x56\x69\x73\x61\x20\x61\x6E\x64\x20\x4D\x61\x73\x74\x65\x72\x43\x61\x72\x64\x29", 30);
    draw_text_at_video_address(0, 17, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 18, "\xB0\xB0\xB3\x20\x4F\x72\x20\x6D\x61\x69\x6C\x20\x6F\x72\x64\x65\x72\x20\x74\x6F\x3A\x20\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x07\x20\x50\x2E\x4F\x2E\x20\x42\x6F\x78\x20\x34\x37\x36\x33\x38\x39\x20\x07\x20\x47\x61\x72\x6C\x61\x6E\x64\x2C\x20\x54\x58\x20\x37\x35\x30\x34\x37\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 19, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(2, 20, "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9", 31);
#elif EPISODE == 2
    draw_text_at_video_address(0, 0, "\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", 31);
    draw_text_at_video_address(0, 1, "\xB0\xB0\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF", 31);
    draw_text_at_video_address(0, 2, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(9, 2, "\x4E\x4F\x54\x49\x43\x45\x3A\x20\x20\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x49\x53\x20\x4E\x4F\x54\x20\x53\x48\x41\x52\x45\x57\x41\x52\x45\x2C\x20\x46\x52\x45\x45\x57\x41\x52\x45\x20\x4F\x52\x20\x50\x55\x42\x4C\x49\x43\x20\x44\x4F\x4D\x41\x49\x4E\x21", 30);
    draw_text_at_video_address(0, 3, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(8, 3, "\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x4D\x41\x59\x20\x4F\x4E\x4C\x59\x20\x42\x45\x20\x44\x49\x53\x54\x52\x49\x42\x55\x54\x45\x44\x20\x42\x59\x20\x41\x50\x4F\x47\x45\x45\x20\x53\x4F\x46\x54\x57\x41\x52\x45\x20\x50\x52\x4F\x44\x55\x43\x54\x49\x4F\x4E\x53\x2E", 30);
    draw_text_at_video_address(0, 4, "\xB0\xB0\xC6\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB5", 31);
    draw_text_at_video_address(0, 5, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 6, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x4F\x6E\x6C\x79\x20\x74\x68\x65\x20\x66\x69\x72\x73\x74\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x69\x73\x20\x61\x76\x61\x69\x6C\x61\x62\x6C\x65\x20\x61\x73\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x2E\x20\x54\x68\x65\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 7, "\xB0\xB0\xB3\x20\x20\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x28\x69\x6E\x63\x6C\x75\x64\x69\x6E\x67\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x29\x20\x61\x72\x65\x20\x6F\x6E\x6C\x79\x20\x73\x6F\x6C\x64\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 8, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x63\x6F\x6D\x6D\x65\x72\x63\x69\x61\x6C\x6C\x79\x20\x62\x79\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x6F\x72\x20\x61\x6E\x20\x61\x75\x74\x68\x6F\x72\x69\x7A\x65\x64\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x6F\x72\x2E\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 9, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 10, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x42\x75\x6C\x6C\x65\x74\x69\x6E\x20\x62\x6F\x61\x72\x64\x73\x2C\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x20\x76\x65\x6E\x64\x6F\x72\x73\x2C\x20\x75\x73\x65\x72\x73\x20\x67\x72\x6F\x75\x70\x73\x20\x61\x6E\x64\x20\x63\x6C\x75\x62\x73\x20\x6D\x61\x79\x20\x6E\x6F\x74\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 11, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x65\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 12, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 13, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x63\x6F\x6E\x73\x69\x73\x74\x73\x20\x6F\x66\x20\x74\x68\x72\x65\x65\x20\x75\x6E\x69\x71\x75\x65\x20\x61\x6E\x64\x20\x65\x78\x63\x69\x74\x69\x6E\x67\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x3A\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 14, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x53\x68\x72\x61\x70\x6E\x65\x6C\x20\x43\x69\x74\x79\x20\x20\x07\x20\x20\x4D\x69\x73\x73\x69\x6F\x6E\x3A\x20\x4D\x6F\x6F\x6E\x62\x61\x73\x65\x20\x20\x07\x20\x20\x54\x72\x61\x70\x70\x65\x64\x20\x69\x6E\x20\x74\x68\x65\x20\x46\x75\x74\x75\x72\x65\x21\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 15, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 16, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x54\x6F\x20\x6F\x72\x64\x65\x72\x20\x74\x68\x65\x20\x63\x6F\x6D\x70\x6C\x65\x74\x65\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x74\x72\x69\x6C\x6F\x67\x79\x2C\x20\x63\x61\x6C\x6C\x20\x31\x2D\x38\x30\x30\x2D\x38\x35\x32\x2D\x35\x36\x35\x39\x2E\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 17, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 18, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x4F\x72\x20\x77\x72\x69\x74\x65\x3A\x20\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x07\x20\x50\x2E\x4F\x2E\x20\x42\x6F\x78\x20\x34\x37\x36\x33\x38\x39\x20\x07\x20\x47\x61\x72\x6C\x61\x6E\x64\x2C\x20\x54\x58\x20\x37\x35\x30\x34\x37\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 19, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(2, 20, "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9", 31);
#elif EPISODE == 3
    draw_text_at_video_address(0, 0, "\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", 31);
    draw_text_at_video_address(0, 1, "\xB0\xB0\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF", 31);
    draw_text_at_video_address(0, 2, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(9, 2, "\x4E\x4F\x54\x49\x43\x45\x3A\x20\x20\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x49\x53\x20\x4E\x4F\x54\x20\x53\x48\x41\x52\x45\x57\x41\x52\x45\x2C\x20\x46\x52\x45\x45\x57\x41\x52\x45\x20\x4F\x52\x20\x50\x55\x42\x4C\x49\x43\x20\x44\x4F\x4D\x41\x49\x4E\x21", 30);
    draw_text_at_video_address(0, 3, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(8, 3, "\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x4D\x41\x59\x20\x4F\x4E\x4C\x59\x20\x42\x45\x20\x44\x49\x53\x54\x52\x49\x42\x55\x54\x45\x44\x20\x42\x59\x20\x41\x50\x4F\x47\x45\x45\x20\x53\x4F\x46\x54\x57\x41\x52\x45\x20\x50\x52\x4F\x44\x55\x43\x54\x49\x4F\x4E\x53\x2E", 30);
    draw_text_at_video_address(0, 4, "\xB0\xB0\xC6\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB5", 31);
    draw_text_at_video_address(0, 5, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 6, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x4F\x6E\x6C\x79\x20\x74\x68\x65\x20\x66\x69\x72\x73\x74\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x69\x73\x20\x61\x76\x61\x69\x6C\x61\x62\x6C\x65\x20\x61\x73\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x2E\x20\x54\x68\x65\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 7, "\xB0\xB0\xB3\x20\x20\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x28\x69\x6E\x63\x6C\x75\x64\x69\x6E\x67\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x29\x20\x61\x72\x65\x20\x6F\x6E\x6C\x79\x20\x73\x6F\x6C\x64\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 8, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x63\x6F\x6D\x6D\x65\x72\x63\x69\x61\x6C\x6C\x79\x20\x62\x79\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x6F\x72\x20\x61\x6E\x20\x61\x75\x74\x68\x6F\x72\x69\x7A\x65\x64\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x6F\x72\x2E\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 9, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 10, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x42\x75\x6C\x6C\x65\x74\x69\x6E\x20\x62\x6F\x61\x72\x64\x73\x2C\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x20\x76\x65\x6E\x64\x6F\x72\x73\x2C\x20\x75\x73\x65\x72\x73\x20\x67\x72\x6F\x75\x70\x73\x20\x61\x6E\x64\x20\x63\x6C\x75\x62\x73\x20\x6D\x61\x79\x20\x6E\x6F\x74\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 11, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x65\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 12, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 13, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x63\x6F\x6E\x73\x69\x73\x74\x73\x20\x6F\x66\x20\x74\x68\x72\x65\x65\x20\x75\x6E\x69\x71\x75\x65\x20\x61\x6E\x64\x20\x65\x78\x63\x69\x74\x69\x6E\x67\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x3A\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 14, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x53\x68\x72\x61\x70\x6E\x65\x6C\x20\x43\x69\x74\x79\x20\x20\x07\x20\x20\x4D\x69\x73\x73\x69\x6F\x6E\x3A\x20\x4D\x6F\x6F\x6E\x62\x61\x73\x65\x20\x20\x07\x20\x20\x54\x72\x61\x70\x70\x65\x64\x20\x69\x6E\x20\x74\x68\x65\x20\x46\x75\x74\x75\x72\x65\x21\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 15, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 16, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x54\x6F\x20\x6F\x72\x64\x65\x72\x20\x74\x68\x65\x20\x63\x6F\x6D\x70\x6C\x65\x74\x65\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x74\x72\x69\x6C\x6F\x67\x79\x2C\x20\x63\x61\x6C\x6C\x20\x31\x2D\x38\x30\x30\x2D\x38\x35\x32\x2D\x35\x36\x35\x39\x2E\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 17, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 18, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x4F\x72\x20\x77\x72\x69\x74\x65\x3A\x20\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x07\x20\x50\x2E\x4F\x2E\x20\x42\x6F\x78\x20\x34\x37\x36\x33\x38\x39\x20\x07\x20\x47\x61\x72\x6C\x61\x6E\x64\x2C\x20\x54\x58\x20\x37\x35\x30\x34\x37\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(0, 19, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    draw_text_at_video_address(2, 20, "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9", 31);
#endif
}

/* Loads the credits bitmap into an allocated planar-image buffer. */
void pascal load_credits_graphics(char far *filename)
{
    FILE *bitmap_file;

    bitmap_file = fopen(filename, "rb");
    credits_graphics_buffer = malloc(32001);
    if (credits_graphics_buffer)
        fread(credits_graphics_buffer, 32000, 1, bitmap_file);
    fclose(bitmap_file);
}

/* Clears the video page so it can be reused. */
void clear_video_page(void)
{
    register int x;
    register int y;

    outport(0x3c4, 0x0f02);
    select_draw_page(0);
    for (y = 0; y < 25; y++) {
        for (x = 0; x < 40; x += 2) {
            blit_bitmap_to_video_page(0, y * 640 + x);
        }
    }
}

/* Copies the loaded credits bitmap planes into video memory and displays the resulting page. */
void display_credits_bitmap(void)
{
    char far *video = (char far *)0xa0000000L;
    register int i;

    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (i = 0; i < 8000; ++i)
        video[i] = credits_graphics_buffer[i];
    outport(0x3c4, 0x0202);
    for (i = 0; i < 8000; ++i)
        video[i] = credits_graphics_buffer[i + 8000];
    outport(0x3c4, 0x0402);
    for (i = 0; i < 8000; ++i)
        video[i] = credits_graphics_buffer[i + 16000];
    outport(0x3c4, 0x0802);
    for (i = 0; i < 8000; ++i)
        video[i] = credits_graphics_buffer[i + 24000];
    show_video_page(0);
}

/* Loads the title screen bitmap (dn.dnX) into title_screen_buffer. */
void pascal load_title_screen(char far *filename)
{
    FILE *bitmap_file;

    bitmap_file = fopen(filename, "rb");
    title_screen_buffer = malloc(32001);
    if (title_screen_buffer != 0) {
        fread(title_screen_buffer, 32000, 1, bitmap_file);
    }
    fclose(bitmap_file);
}

/* Copies the title screen bitmap plane by plane into video memory. */
void display_title_screen(void)
{
    char far *screen = (char far *)MK_FP(0xa000, 0);
    register int byte_offset;

    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        screen[byte_offset] = title_screen_buffer[byte_offset];
    outport(0x3c4, 0x0202);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        screen[byte_offset] = title_screen_buffer[byte_offset + 8000];
    outport(0x3c4, 0x0402);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        screen[byte_offset] = title_screen_buffer[byte_offset + 16000];
    outport(0x3c4, 0x0802);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        screen[byte_offset] = title_screen_buffer[byte_offset + 24000];
    show_video_page(0);
}

/* Loads the bad-guy bitmap into its allocated planar-image buffer. */
void pascal load_badguy_graphics(char far *filename)
{
    FILE *bitmap_file;

    bitmap_file = fopen(filename, "rb");
    badguy_graphics_buffer = malloc(32001);
    if (badguy_graphics_buffer != 0) {
        fread(badguy_graphics_buffer, 32000, 1, bitmap_file);
    }
    fclose(bitmap_file);
}

/* Copies the loaded bad-guy bitmap planes into video memory and displays the resulting page. */
void display_badguy_bitmap(void)
{
    register int byte_offset;
    char far *video = (char far *)MK_FP(0xA000, 0);

    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        video[byte_offset] = badguy_graphics_buffer[byte_offset];
    outport(0x3c4, 0x0202);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        video[byte_offset] = badguy_graphics_buffer[byte_offset + 8000];
    outport(0x3c4, 0x0402);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        video[byte_offset] = badguy_graphics_buffer[byte_offset + 16000];
    outport(0x3c4, 0x0802);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        video[byte_offset] = badguy_graphics_buffer[byte_offset + 24000];
    show_video_page(0);
}

/* Loads the Duke bitmap into its allocated planar-image buffer. */
void pascal load_duke_graphics(char far *filename)
{
    FILE *bitmap_file;

    bitmap_file = fopen(filename, "rb");
    duke_graphics_buffer = malloc(32001);
    if (duke_graphics_buffer != 0) {
        fread(duke_graphics_buffer, 32000, 1, bitmap_file);
    }
    fclose(bitmap_file);
}

/* Copies the loaded Duke bitmap planes into video memory and displays the resulting page. */
void display_duke_bitmap(void)
{
    register int i;
    char far *video = (char far *)MK_FP(0xa000, 0);

    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (i = 0; i < 8000; ++i) {
        video[i] = duke_graphics_buffer[i];
    }
    outport(0x3c4, 0x0202);
    for (i = 0; i < 8000; ++i) {
        video[i] = duke_graphics_buffer[i + 8000];
    }
    outport(0x3c4, 0x0402);
    for (i = 0; i < 8000; ++i) {
        video[i] = duke_graphics_buffer[i + 16000];
    }
    outport(0x3c4, 0x0802);
    for (i = 0; i < 8000; ++i) {
        video[i] = duke_graphics_buffer[i + 24000];
    }
    show_video_page(0);
}

/* Loads the ending bitmap into its allocated planar-image buffer. */
void pascal load_ending_graphics(char far *filename)
{
    FILE *bitmap_file;

    bitmap_file = fopen(filename, "rb");
    ending_graphics_buffer = malloc(32001);
    if (ending_graphics_buffer) {
        fread(ending_graphics_buffer, 32000, 1, bitmap_file);
    }
    fclose(bitmap_file);
}

/* Copies the loaded ending bitmap planes into video memory and displays the resulting page. */
void display_ending_bitmap(void)
{
    char far *video_memory;
    register int byte_offset;

    video_memory = MK_FP(0xa000, 0);
    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (byte_offset = 0; byte_offset < 8000; byte_offset++)
        video_memory[byte_offset] = ending_graphics_buffer[byte_offset];
    outport(0x3c4, 0x0202);
    for (byte_offset = 0; byte_offset < 8000; byte_offset++)
        video_memory[byte_offset] = ending_graphics_buffer[byte_offset + 8000];
    outport(0x3c4, 0x0402);
    for (byte_offset = 0; byte_offset < 8000; byte_offset++)
        video_memory[byte_offset] = ending_graphics_buffer[byte_offset + 16000];
    outport(0x3c4, 0x0802);
    for (byte_offset = 0; byte_offset < 8000; byte_offset++)
        video_memory[byte_offset] = ending_graphics_buffer[byte_offset + 24000];
    show_video_page(0);
}

/* Draws a null-terminated text string with the EGA font glyphs at the requested position. */
void pascal draw_text_string(char far *text, register int x, int y)
{
    register int i;

    i = 0;
    outport(0x3ce, 5);
    for (; text[i] != 0; ++i) {
        if (text[i] >= 'a') {
            draw_ega_glyph(font_glyph_data_buffer + (text[i] - 'a') * 40 + 0xac8,
                           x + i, y * 8);
        } else {
            draw_ega_glyph(font_glyph_data_buffer + (text[i] - ' ') * 40 + 0x190,
                           x + i, y * 8);
        }
    }
}

/* Draws one mapped character glyph at the requested text position. */
void pascal draw_text_character_at_position(char character, int pixel_x, int pixel_y)
{
    if (character >= 'a') {
        draw_ega_glyph(font_glyph_data_buffer + (character - 'a') * 40 + 0xac8, pixel_x, pixel_y);
    } else {
        draw_ega_glyph(font_glyph_data_buffer + (character - ' ') * 40 + 0x190, pixel_x, pixel_y);
    }
}

#if EPISODE == 1 || EPISODE == 2
/* draw_main_menu: at this place in the DN1, DN2 source */
/* Draws the main menu; the source has a DN3-specific menu body and a shared DN1/DN2 body. */
void pascal draw_main_menu(register int text_x)
{
    draw_text_string("      DUKE MAIN MENU", text_x, 6);
    draw_text_string("      --------------", text_x, 7);
    draw_text_string("   S)tart a new game", text_x, 9);
    draw_text_string("   R)estore an old game", text_x, 10);
    draw_text_string("   I)nstructions", text_x, 11);
    draw_text_string("   O)rdering information", text_x, 12);
    draw_text_string("   G)ame setup", text_x, 13);
    draw_text_string("   H)igh scores", text_x, 14);
    draw_text_string("   P)reviews/Main Demo!", text_x, 15);
    draw_text_string("   V)iew user demo", text_x, 16);
    draw_text_string("   T)itle screen", text_x, 17);
    draw_text_string("   C)redits", text_x, 18);
    draw_text_string("   Q)uit to DOS", text_x, 19);
}
#endif

/* Loads the primary sound bank and builds the first 24 sample pointers and sound priorities. */
void pascal load_primary_sound_bank(char far *filename)
{
    FILE *sound_file;
    register int i;

    sound_file = fopen(filename, "rb");
    primary_sound_bank_buffer = malloc(9300);
    fread(primary_sound_bank_buffer, 9300, 1, sound_file);
    fclose(sound_file);
    /* Header words follow each 16-byte falling_sign_record. */
    /* Keep the nested shifts; i * 16 changes Turbo C output. */
    for (i = 0; i < 24; ++i) {
        sound_sample_pointer_table[i] = primary_sound_bank_buffer + (((struct sound_bank_index_record far *)(primary_sound_bank_buffer + ((((i << 1) << 1) << 1) << 1)))->index_words[8] >> 1 << 1);
        sound_effect_priority_table[i] = ((struct sound_bank_index_record far *)(primary_sound_bank_buffer + ((((i << 1) << 1) << 1) << 1)))->index_words[9];
    }
}

/* Loads the secondary sound bank and builds the next 24 sample pointers and sound priorities. */
void pascal load_secondary_sound_bank(char far *filename)
{
    FILE *sound_file;
    register int i;

    sound_file = fopen(filename, "rb");
    secondary_sound_bank_buffer = malloc(8500);
    fread(secondary_sound_bank_buffer, 8000, 1, sound_file);
    fclose(sound_file);
    /* Header words follow each 16-byte falling_sign_record. */
    /* Keep the nested shifts; i * 16 changes Turbo C output. */
    for (i = 0; i < 24; ++i) {
        sound_sample_pointer_table[i + 24] = secondary_sound_bank_buffer + (((*((unsigned int far *)((char far *)secondary_sound_bank_buffer + ((((i << 1) << 1) << 1) << 1) + 16))) >> 1) << 1);
        secondary_sound_priority_table[i] = *((unsigned char far *)((char far *)secondary_sound_bank_buffer + ((((i << 1) << 1) << 1) << 1) + 16));
    }
}

/* Displays the credit screen screen or message and waits for the associated input when required. */
void show_credit_screen(void)
{
    draw_framed_dialog_box(7, 3, 6);
    draw_text_string("     APOGEE SOFTWARE    ", 8, 8);
    draw_text_string("       PRODUCTIONS      ", 8, 9);
    draw_text_string("          - - -         ", 8, 10);
    draw_text_string("        A game by       ", 8, 12);
    draw_text_string("      Todd Replogle     ", 8, 13);
    draw_text_string("       Version 2.0      ", 8, 15);
#if EPISODE == 3
    draw_text_string("   Copyright  (c) 1991   ", 8, 17);
#else
    draw_text_string("   Copyright  (c) 1991  ", 8, 17);
#endif
}

/* Draws the planar sprite frame using the active page and graphics resources. */
void draw_planar_sprite_frame(void)
{
    select_draw_page(draw_page_index);
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4c40, 0x24, episode_sprite_resource_table + 0xa0);
    select_draw_page(!draw_page_index);
    blit_planar_sprite_rows(sprite_pixel_data_pointer + 0x4c40, 0x24, episode_sprite_resource_table + 0xa0);
}

/* Displays the proton episode dialogue screen or message and waits for the associated input when
   required. */
void show_proton_episode_dialogue(void)
{
    draw_framed_dialog_box(0, 9, 2);
#if EPISODE == 1
    draw_text_string("So you're the pitiful   ", 1, 19);
    draw_text_string("hero they sent to stop  ", 1, 20);
    draw_text_string("me.  I, Dr. Proton, will", 1, 21);
    draw_text_string("soon rule the world!    ", 1, 22);
#elif EPISODE == 2
    draw_text_string("So Duke, you managed to ", 1, 19);
    draw_text_string("find my secret moonbase.", 1, 20);
    draw_text_string("My Techbots will soon", 1, 21);
    draw_text_string("be the end of you.", 1, 22);
#else
    draw_text_string("Now that I've warped to ", 1, 19);
    draw_text_string("Earth's future, Duke the", 1, 20);
    draw_text_string("Fluke cannot stop me.", 1, 21);
#endif
    wait_input_animated_sprite(24, 22);
}

/* Displays the duke episode dialogue screen or message and waits for the associated input when
   required. */
void show_duke_episode_dialogue(void)
{
    draw_framed_dialog_box(10, 9, 2);
#if EPISODE == 1
    draw_text_string("You're wrong, Proton    ", 11, 19);
    draw_text_string("breath.  I'll be done   ", 11, 20);
    draw_text_string("with you and still have ", 11, 21);
    draw_text_string("time to watch Oprah!    ", 11, 22);
#elif EPISODE == 2
    draw_text_string("Your Techbots were", 11, 19);
    draw_text_string("beaten on Earth and I'll", 11, 20);
    draw_text_string("defeat them here. Your", 11, 21);
    draw_text_string("terror will soon end.", 11, 22);
#else
    draw_text_string("I need to find Dr.", 11, 19);
    draw_text_string("Proton's time machine", 11, 20);
    draw_text_string("or Earth is doomed!", 11, 21);
#endif
    wait_input_animated_sprite(34, 22);
}

/* Displays the player death message screen or message and waits for the associated input when
   required. */
void show_player_death_message(void)
{
    draw_text_string("     You have died.", 3, 3);
    draw_text_string("Bringing you back to the", 3, 4);
    draw_text_string("   last main hallway.", 3, 5);
    draw_text_string("      Press ENTER:", 3, 6);
}

/* Displays the cheat mode message screen or message and waits for the associated input when
   required. */
void show_cheat_mode_message(void)
{
    draw_text_string("You are now cheating.", 3, 3);
    draw_text_string("You have full fire power", 3, 4);
    draw_text_string("and all the keys.", 3, 5);
    draw_text_string("Have Fun!", 3, 6);
}

#if EPISODE == 3
/* draw_main_menu: at this place in the DN3 source */
/* Draws the main menu; the source has a DN3-specific menu body and a shared DN1/DN2 body. */
void pascal draw_main_menu(register int text_x)
{
    draw_text_string("      DUKE MAIN MENU", text_x, 6);
    draw_text_string("      --------------", text_x, 7);
    draw_text_string("   S)tart a new game", text_x, 9);
    draw_text_string("   R)estore an old game", text_x, 10);
    draw_text_string("   I)nstructions", text_x, 11);
    draw_text_string("   O)rdering information", text_x, 12);
    draw_text_string("   G)ame setup", text_x, 13);
    draw_text_string("   H)igh scores", text_x, 14);
    draw_text_string("   P)reviews/Main Demo!", text_x, 15);
    draw_text_string("   V)iew user demo", text_x, 16);
    draw_text_string("   T)itle screen", text_x, 17);
    draw_text_string("   C)redits", text_x, 18);
    draw_text_string("   Q)uit to DOS", text_x, 19);
}
#endif

/* Displays the quit confirmation and returns whether the player chose to exit to DOS. */
void pascal confirm_quit_to_dos(register int text_x)
{
    draw_framed_dialog_box(text_x, 5, 1);
    draw_text_string("Are you sure you want to", text_x + 1, 11);
    draw_text_string("         quit?          ", text_x + 1, 12);
    while (last_keyboard_scan_code == 1) {
    }
    wait_input_animated_sprite(text_x + 16, 12);
    control_right_pressed = 0;
    control_down_pressed = 0;
    if (last_keyboard_scan_code == 0x15)
        return 1;
    last_keyboard_scan_code = 0;
    return 0;
}

/* Draws a framed dialog panel from the border-tile graphics (blit_bitmap_to_video_page). */
void pascal draw_framed_dialog_box(int left_offset, int top_offset, int height_rows)
{
    register int vertical_offset;
    register int horizontal_offset;

    /* Select all VGA planes before drawing the border. */
    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    if (left_offset == 2)
        select_draw_page(draw_page_index);
    else
        select_draw_page(0);

    /* Keep the 16 * 40 row products; folded multipliers change Turbo C output. */
    for (vertical_offset = 0; height_rows * 16 * 40 > vertical_offset; vertical_offset += 640) {
        blit_bitmap_to_video_page(0x32c0, top_offset * 16 * 40 + (vertical_offset + left_offset));
        blit_bitmap_to_video_page(0x32e0, top_offset * 16 * 40 + (vertical_offset + left_offset) + 24);
    }
    for (horizontal_offset = 2; horizontal_offset < 23; horizontal_offset += 2)
        for (vertical_offset = 0; height_rows * 16 * 40 > vertical_offset; vertical_offset += 640)
            blit_bitmap_to_video_page(0x3220, top_offset * 16 * 40 + left_offset + horizontal_offset + vertical_offset);

    blit_bitmap_to_video_page(0x3240, top_offset * 16 * 40 + left_offset);
    blit_bitmap_to_video_page(0x3260, top_offset * 16 * 40 + left_offset + 24);
    blit_bitmap_to_video_page(0x3280, (top_offset * 16 * 40 + left_offset) + height_rows * 16 * 40);
    blit_bitmap_to_video_page(0x32a0, (top_offset * 16 * 40 + left_offset) + height_rows * 16 * 40 + 24);

    for (horizontal_offset = 0; horizontal_offset < 22; horizontal_offset += 2) {
        blit_bitmap_to_video_page(0x3300, top_offset * 16 * 40 + (horizontal_offset + left_offset) + 2);
        blit_bitmap_to_video_page(0x3320, (height_rows * 16 * 40 + horizontal_offset + left_offset) + top_offset * 16 * 40 + 2);
    }
}

/* Advances the credits scroll position and draws the next row of credits text with its color
   sequence. */
void animate_credits_scroll(void)
{
    register int i;

    if (credits_scroll_position < 40)
        ++credits_scroll_position;
    if (credits_scroll_position == 40) {
        credits_text_position += 2;
        if (credits_text_position % 26 == 0)
            credits_scroll_position = 0;
        if (credits_text_position > 494)
            credits_text_position = 0;
    }
    ++credit_scroll_delay;
    if (credit_scroll_delay == 4)
        credit_scroll_delay = 0;
    for (i = 0; i < 26; ++i)
        draw_text_character_at_position(credits_scroll_text[credits_text_position + i], i + 2,
                                        credits_glyph_color_sequence[credit_scroll_delay + i] + 0xa2);
}

/* Waits for the for pause key release condition or input event. */
void wait_for_pause_key_release(void)
{
    while (last_keyboard_scan_code == 0x18) {
    }
#if EPISODE != 3
    clear_video_page();
#endif
}

/* Displays the instructions heading screen or message and waits for the associated input when
   required. */
void show_instructions_heading(void)
{
    while (last_keyboard_scan_code == 0x17) {
    }
    clear_video_page();
    draw_text_string("Instructions", 14, 0);
}

/* Prompts for a replacement scan code for one keyboard action and redraws its binding label. */
void pascal remap_keyboard_action(register int text_x)
{
    control_confirmation_state = 0;
    for (;;) {
#if EPISODE == 1
        last_keyboard_scan_code = 0;
#endif
        draw_framed_dialog_box(text_x, 3, 7);
        outport(0x3ce, 5);
        draw_keyboard_mode_settings(text_x);
        draw_keyboard_binding_values(text_x);
        draw_text_string("Modify which action?", text_x + 1, 15);
        draw_text_string("choose(1-6):", text_x + 1, 16);
        draw_text_string("  Press 'ESC' to exit.", text_x + 1, 20);
        for (;;) {
            while (last_keyboard_scan_code == 0x25) {
            }
            wait_input_animated_sprite(text_x + 14, 16);
            if (last_keyboard_scan_code == 1)
                return;
            switch (last_keyboard_scan_code) {
            case 2:
                draw_text_string("Modifying UP.          ", text_x + 1, 18);
                draw_text_string("  Hit new key:            ", text_x + 1, 19);
                while (last_keyboard_scan_code == 2) {
                }
                wait_input_animated_sprite(text_x + 16, 19);
                if (last_keyboard_scan_code != 1) {
                    last_keyboard_scan_code = normalize_extended_key_code();
                    key_binding_up = last_keyboard_scan_code;
                    enable();
                    break;
                }
                break;
            case 3:
                draw_text_string("Modifying DOWN.          ", text_x + 1, 18);
                draw_text_string("  Hit new key:            ", text_x + 1, 19);
                while (last_keyboard_scan_code == 3) {
                }
                wait_input_animated_sprite(text_x + 16, 19);
                if (last_keyboard_scan_code != 1) {
                    last_keyboard_scan_code = normalize_extended_key_code();
                    key_binding_down = last_keyboard_scan_code;
                    enable();
                    break;
                }
                break;
            case 4:
                draw_text_string("Modifying LEFT.          ", text_x + 1, 18);
                draw_text_string("  Hit new key:            ", text_x + 1, 19);
                while (last_keyboard_scan_code == 4) {
                }
                wait_input_animated_sprite(text_x + 16, 19);
                if (last_keyboard_scan_code != 1) {
                    last_keyboard_scan_code = normalize_extended_key_code();
                    key_binding_left = last_keyboard_scan_code;
                    enable();
                    break;
                }
                break;
            case 5:
                draw_text_string("Modifying RIGHT.          ", text_x + 1, 18);
                draw_text_string("  hit new key:            ", text_x + 1, 19);
                while (last_keyboard_scan_code == 5) {
                }
                wait_input_animated_sprite(text_x + 16, 19);
                if (last_keyboard_scan_code != 1) {
                    last_keyboard_scan_code = normalize_extended_key_code();
                    key_binding_right = last_keyboard_scan_code;
                    enable();
                    break;
                }
                break;
            case 6:
                draw_text_string("Modifying FIRE.          ", text_x + 1, 18);
                draw_text_string("  Hit new key:            ", text_x + 1, 19);
                while (last_keyboard_scan_code == 6) {
                }
                wait_input_animated_sprite(text_x + 16, 19);
                if (last_keyboard_scan_code != 1) {
                    last_keyboard_scan_code = normalize_extended_key_code();
                    key_binding_fire = last_keyboard_scan_code;
                    enable();
                    break;
                }
                break;
            case 7:
                draw_text_string("Modifying JUMP.          ", text_x + 1, 18);
                draw_text_string("  Hit new key:            ", text_x + 1, 19);
                while (last_keyboard_scan_code == 7) {
                }
                wait_input_animated_sprite(text_x + 16, 19);
                if (last_keyboard_scan_code != 1) {
                    last_keyboard_scan_code = normalize_extended_key_code();
                    key_binding_jump = last_keyboard_scan_code;
                    enable();
                    break;
                }
                break;
            }
            break;
        }
    }
}

/* Draws the keyboard mode settings using the active page and graphics resources. */
void pascal draw_keyboard_mode_settings(register int text_x)
{
    draw_text_string("      KEYBOARD MODE", text_x, 7);
    draw_text_string("                        ", text_x + 1, 8);
    draw_text_string("  1.  Up     :", text_x + 1, 9);
    draw_text_string("  2.  Down   :", text_x + 1, 10);
    draw_text_string("  3.  Left   :", text_x + 1, 11);
    draw_text_string("  4.  Right  :", text_x + 1, 12);
    draw_text_string("  5.  Fire   :", text_x + 1, 13);
    draw_text_string("  6.  Jump   :", text_x + 1, 14);
}

/* Dr. Proton taunt shown at the end of a level; text differs per episode. */
/* Displays the proton level end dialogue screen or message and waits for the associated input
   when required. */
void show_proton_level_end_dialogue(void)
{
    draw_framed_dialog_box(0, 9, 2);
#if EPISODE == 1
    draw_text_string("You may have defeated me", 1, 19);
    draw_text_string("on Earth, but on the    ", 1, 20);
    draw_text_string("Moon I can make plans   ", 1, 21);
    draw_text_string("for my ulimate attack!  ", 1, 22);
#elif EPISODE == 2
    draw_text_string("Duke, your lucky ways   ", 1, 19);
    draw_text_string("annoy me.  I see now    ", 1, 20);
    draw_text_string("how best to be rid of", 1, 21);
    draw_text_string("of your pesky presence.", 1, 22);
#else
    draw_text_string("You will never get me,  ", 1, 19);
    draw_text_string("Duke!  Watch your self", 1, 20);
    draw_text_string("you here!.", 1, 21);
#endif
    wait_input_animated_sprite(24, 22);
}

/* Displays the proton transition dialogue screen or message and waits for the associated input
   when required. */
void show_proton_transition_dialogue(void)
{
    draw_framed_dialog_box(10, 9, 2);
#if EPISODE == 1
    draw_text_string("Proton, you coward!  You", 11, 19);
    draw_text_string("can run but you can't   ", 11, 20);
    draw_text_string("hide!                   ", 11, 21);
    draw_text_string("                        ", 11, 22);
#elif EPISODE == 2
    draw_text_string("There's IS no place to", 11, 19);
    draw_text_string("hide from me.  Running", 11, 20);
    draw_text_string("back to Earth will not", 11, 21);
    draw_text_string("save you.", 11, 22);
#else
    draw_text_string("You'll not get away", 11, 19);
    draw_text_string("butthead!", 11, 20);
    draw_text_string("", 11, 21);
#endif
    wait_input_animated_sprite(34, 22);
}

/* Displays the proton future dialogue screen or message and waits for the associated input when
   required. */
void show_proton_future_dialogue(void)
{
    draw_framed_dialog_box(0, 9, 2);
#if EPISODE == 1
    draw_text_string("Once my forces are     ", 1, 19);
    draw_text_string("together, I'll be back ", 1, 20);
    draw_text_string("to rule Earth.         ", 1, 21);
#elif EPISODE == 2
    draw_text_string("But escaping to Earth's", 1, 19);
    draw_text_string("future will!  Then my", 1, 20);
    draw_text_string("Techbot army can build", 1, 21);
    draw_text_string("and return victorious!", 1, 22);
#else
    draw_text_string("Butthead, it's buthead!!", 1, 19);
    draw_text_string("                     ", 1, 20);
    draw_text_string("     ", 1, 21);
#endif
    wait_input_animated_sprite(24, 22);
}

/* Displays the duke level end dialogue screen or message and waits for the associated input when
   required. */
void show_duke_level_end_dialogue(void)
{
    draw_framed_dialog_box(10, 9, 2);
#if EPISODE == 1
    draw_text_string("Not if I can stop you ", 11, 19);
    draw_text_string("first...              ", 11, 20);
    draw_text_string("                      ", 11, 21);
    draw_text_string("     Here I come!     ", 11, 22);
#elif EPISODE == 2
    draw_text_string("Not if I can find a way", 11, 19);
    draw_text_string("to stop you...even if", 11, 20);
    draw_text_string("I have to follow you", 11, 21);
    draw_text_string("into the future...!", 11, 22);
#else
    draw_text_string("The spelling of yours", 11, 19);
    draw_text_string("is getting better!", 11, 20);
    draw_text_string("", 11, 21);
#endif
    wait_input_animated_sprite(34, 22);
}

/* Displays the game completion message screen or message and waits for the associated input when
   required. */
void show_game_completion_message(void)
{
    draw_framed_dialog_box(10, 9, 2);
#if EPISODE == 1 || EPISODE == 2
    draw_text_string("I won it all!!!!!!!", 11, 19);
    draw_text_string("         ", 11, 20);
    draw_text_string("", 11, 21);
#else
    draw_text_string("Finally, Earth is free", 11, 19);
    draw_text_string("from Dr. Proton and", 11, 20);
    draw_text_string("his Techbot menace.", 11, 21);
    draw_text_string("", 11, 22);
#endif
    wait_input_animated_sprite(34, 22);
}

/* Prompts the player for the joystick calibration and records the response. */
void pascal prompt_joystick_calibration(register int text_x)
{
    draw_text_string(" Hold the joystick in the", text_x, 9);
    draw_text_string(" upper left and press a", text_x, 10);
    draw_text_string(" button.", text_x, 11);
}

/* Displays the next episode promotion screen or message and waits for the associated input when
   required. */
void pascal show_next_episode_promotion(register int text_x)
{
    clear_video_page();
    request_priority_sound_effect(0x2c);
#if EPISODE == 1
    draw_framed_dialog_box(text_x, 2, 7);
    draw_text_string("     TO BE CONTINUED     ", text_x + 1, 5);
    draw_text_string("------------------------", text_x + 1, 6);
    draw_text_string("In episode two, Duke     ", text_x + 1, 8);
    draw_text_string("rockets to the moon to   ", text_x + 1, 9);
    draw_text_string("infiltrate Dr. Proton's  ", text_x + 1, 10);
    draw_text_string("massive lunar fortress.  ", text_x + 1, 11);
    draw_text_string("                         ", text_x + 1, 12);
    draw_text_string("Continue your adventure  ", text_x + 1, 13);
    draw_text_string("in \"Mission: Moonbase\",  ", text_x + 1, 14);
    draw_text_string("where you'll encounter:  ", text_x + 1, 15);
    draw_text_string("New levels, new puzzles,", text_x + 1, 16);
    draw_text_string("new graphics, and more   ", text_x + 1, 17);
    draw_text_string("non-stop action.         ", text_x + 1, 18);
#elif EPISODE == 2
    draw_framed_dialog_box(text_x, 2, 7);
    draw_text_string("     TO BE CONTINUED    ", text_x + 1, 5);
    draw_text_string("------------------------", text_x + 1, 6);
    draw_text_string("Once again you've given ", text_x + 1, 8);
    draw_text_string("Dr. Proton a major set- ", text_x + 1, 9);
    draw_text_string("back, by destroying his ", text_x + 1, 10);
    draw_text_string("lunar fortress.         ", text_x + 1, 11);
    draw_text_string("                        ", text_x + 1, 12);
    draw_text_string("Continue your adventure ", text_x + 1, 13);
    draw_text_string("in \"Trapped in the      ", text_x + 1, 14);
    draw_text_string("Future\"!  Duke must     ", text_x + 1, 15);
    draw_text_string("chase Dr. Proton into   ", text_x + 1, 16);
    draw_text_string("Earth's future to stop  ", text_x + 1, 17);
    draw_text_string("the largest threat yet! ", text_x + 1, 18);
#else
    draw_framed_dialog_box(text_x, 1, 10);
    draw_text_string("    CONGRATULATIONS     ", text_x + 1, 3);
    draw_text_string("------------------------", text_x + 1, 4);
    draw_text_string(" Dr. Proton is finally  ", text_x + 1, 6);
    draw_text_string("       defeated!        ", text_x + 1, 7);
    draw_text_string("                        ", text_x + 1, 8);
    draw_text_string("Using Proton's time warp", text_x + 1, 9);
    draw_text_string(" device Duke returns to ", text_x + 1, 10);
    draw_text_string(" Earth's present and is ", text_x + 1, 11);
    draw_text_string("presented the key to the", text_x + 1, 12);
    draw_text_string(" city he saved. (Yeah.) ", text_x + 1, 13);
    draw_text_string(" Did you locate all the ", text_x + 1, 15);
    draw_text_string("  hidden rooms on each  ", text_x + 1, 16);
    draw_text_string("  level?  On your next  ", text_x + 1, 17);
    draw_text_string("   Apogee games order   ", text_x + 1, 18);
    draw_text_string("please tell us your best", text_x + 1, 19);
    draw_text_string(" Duke Nukum high score. ", text_x + 1, 20);
    draw_text_string("                        ", text_x + 1, 21);
    draw_text_string(" Thank you for playing! ", text_x + 1, 22);
#endif
    restore_ega_palette(15);
    if (control_confirmation_state == 0) {
        while ((last_keyboard_scan_code & 0x80) == 0) {
        }
    }
#if EPISODE == 3
    wait_input_animated_sprite(text_x + 24, 22);
#else
    wait_input_animated_sprite(text_x + 24, 18);
#endif
    clear_palette_entries(15);
    wait_for_pause_key_release();
    show_ordering_page_one();
    wait_input_animated_sprite(39, 24);
    clear_video_page();
    show_ordering_page_two();
    wait_input_animated_sprite(39, 24);
    wait_input_animated_sprite(39, 24);
}

