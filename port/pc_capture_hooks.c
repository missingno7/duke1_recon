/* Width adapters keep DOS 16-bit values exact at the generated-code boundary. */
#include "game_hooks.h"

/* These older capture entry points retain their platform-side int signatures. */
extern int port_is_world_position_outside_wide_view(int world_x, int world_y,
                                                    int original_result);
extern int port_is_world_position_outside_wide_if_active(int world_x, int world_y,
                                                          int original_result);

void capture_set_modal_capture_active(int active);   /* scene.c */

void pc_capture_set_modal_capture_active(int16_t active)
{
    capture_set_modal_capture_active((int)active);
}

int16_t pc_capture_is_world_position_outside_wide_view(int16_t world_x, int16_t world_y,
                                                        int16_t original_result)
{
    return (int16_t)port_is_world_position_outside_wide_view((int)world_x, (int)world_y,
                                                              (int)original_result);
}

int16_t pc_capture_is_world_position_outside_wide_if_active(int16_t world_x, int16_t world_y,
                                                              int16_t original_result)
{
    return (int16_t)port_is_world_position_outside_wide_if_active((int)world_x, (int)world_y,
                                                                   (int)original_result);
}
