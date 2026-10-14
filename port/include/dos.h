#ifndef DUKE_PORT_DOS_H
#define DUKE_PORT_DOS_H

#include <stdint.h>
#include "platform.h"

#define MK_FP(segment, offset) pc_mk_fp((uint16_t)(segment), (uint16_t)(offset))

char *pc_ltoa(int32_t value, char *buffer, int base);
char *pc_ultoa(uint32_t value, char *buffer, int base);

#endif
