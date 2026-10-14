/* Port replacement: preserve priority handling and attach the latest view-test pan. */
float pc_speaker_view_pan(int tick_counter);
void pc_speaker_set_next_pan(float pan);

void pascal request_priority_sound_effect(int sound_effect_id)
{
    disable();
    if (sound_effect_priority_table[sound_effect_id] >= current_sound_priority) {
        current_sound_priority = sound_effect_priority_table[sound_effect_id];
        pending_sound_priority_flag = 1;
        pending_sound_effect_index = sound_effect_id;
        sound_interrupt_active_state = 0;
        pc_speaker_set_next_pan(pc_speaker_view_pan(timer_tick_counter));
    }
    enable();
}
