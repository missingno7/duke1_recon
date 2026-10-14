/* Port replacement: keep the DOS view test and record its source for stereo audio. */
void pc_speaker_note_view_test(int world_x, int scroll_x, int tick_counter);

char pascal is_world_position_outside_view(int world_x, int world_y)
{
    pc_speaker_note_view_test(world_x, level_scroll_x, timer_tick_counter);
    if (world_x >= level_scroll_x &&
        level_scroll_x + 29 > world_x &&
        level_map_y_offset - 64 <= world_y &&
        level_map_y_offset + 1280 > world_y)
        return 0;
    return 1;
}
