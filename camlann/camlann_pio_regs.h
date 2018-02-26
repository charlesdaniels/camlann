#ifndef ALTERA_AVALON_PIO_REGS_H
#define ALTERA_AVALON_PIO_REGS_H

#include "camlann.h"
#include "camlann_system.h"
#include <SDL/SDL.h>

alt_u32 IORD_ALTERA_AVALON_PIO_DATA(alt_u32);
void IOWR_ALTERA_AVALON_PIO_DATA(alt_u32, alt_u32);
void camlann_pio_init();

#endif
