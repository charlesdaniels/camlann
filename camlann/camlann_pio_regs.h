#ifndef ALTERA_AVALON_PIO_REGS_H
#define ALTERA_AVALON_PIO_REGS_H

#include "camlann.h"
#include "camlann_system.h"
#include <stdint.h>

#ifdef USE_CAMLANN
alt_u32 IORD_ALTERA_AVALON_PIO_DATA(alt_u32);
void IOWR_ALTERA_AVALON_PIO_DATA(alt_u32, alt_u32);

#endif /* USE_CAMLANN */

void camlann_pio_init();

#endif /* ALTERA_AVALON_PIO_REGS_H */
