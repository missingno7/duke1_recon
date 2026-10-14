/* Port replacement: preserve priority handling and attach the reviewed source position. */
void pascal request_priority_sound_effect(int sound_effect_id, int sound_source_x)
{
    disable();
    if (sound_effect_priority_table[sound_effect_id] >= current_sound_priority) {
        current_sound_priority = sound_effect_priority_table[sound_effect_id];
        pending_sound_priority_flag = 1;
        pending_sound_effect_index = sound_effect_id;
        sound_interrupt_active_state = 0;
        pc_speaker_set_source_world_x((int16_t)sound_source_x, level_scroll_x);
    }
    enable();
}
