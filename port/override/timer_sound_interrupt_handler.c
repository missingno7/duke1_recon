/* Port replacement: preserve the DOS timer/sound handler. */
void interrupt timer_sound_interrupt_handler(void)
{
    register unsigned int period;

    if (pending_sound_priority_flag != 0) {
        pending_sound_priority_flag = 0;
        current_sound_sample_position = 0;
        sound_interrupt_active_state = 1;
        pc_speaker_begin_sound();
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
