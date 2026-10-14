/* Draws the game setup menu using the active page and graphics resources. */
void pascal draw_game_setup_menu(register int text_x)
{
    draw_text_string("        GAME SETUP", text_x, 6);
    draw_text_string("      J)oystick mode", text_x, 8);
    draw_text_string("      K)eyboard mode", text_x, 9);
    draw_text_string("      S)ound toggle", text_x, 10);
    draw_text_string("      H)int toggle", text_x, 11);
    draw_text_string("      P)ort settings", text_x, 12);
}
