/* Displays game setup choices and dispatches joystick, keyboard, sound, or hint changes. */
void pascal handle_game_setup_input(register int text_x)
{
    draw_framed_dialog_box(text_x, 2, 5);
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
        if (last_keyboard_scan_code == 0x19) {
            last_keyboard_scan_code = 0;
            platform_show_port_settings_dialog(EPISODE);
            last_keyboard_scan_code = 0;
            clear_palette_entries(15);
            display_title_screen();
            draw_framed_dialog_box(text_x, 2, 5);
            outport(0x3ce, 5);
            draw_game_setup_menu(text_x);
            restore_ega_palette(15);
            delay(100);
        }
    } while (last_keyboard_scan_code != 0x1c && last_keyboard_scan_code != 1 && last_keyboard_scan_code != 0x39);
}
