/* Keep the original SAVE<n> filename format in writable storage. */
void pascal save_game_state_to_slot(char slot_character)
{
    FILE *stream;
#if EPISODE == 1
    char save_filename[] = "saved .dn1";
#elif EPISODE == 2
    char save_filename[] = "saved .dn2";
#else
    char save_filename[] = "saved .dn3";
#endif
    save_filename[5] = slot_character;
    stream = fopen(save_filename, "wb");
    if (!stream)
        return;
    putw(level_scroll_x, stream);
    putw(level_map_y_offset, stream);
    putw(player_screen_x, stream);
    putw(player_screen_y, stream);
    putw(current_level_index, stream);
    putw(world_actor_count, stream);
    putw(access_card_or_door_state, stream);
    putw(player_contact_state, stream);
    putw(title_graphic_frame_index, stream);
    putw(robohand_box_active_state, stream);
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
