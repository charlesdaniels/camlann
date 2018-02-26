/**
 * @file camlann_util.h
 * @brief Camlann general purpose internal utilities.
 * @author Charles Daniels
 */


#ifndef CAMLANN_UTIL_H
#define CAMLANN_UTIL_H

#include "camlann.h"
#include "camlann_system.h"
#include "camlann_pio_regs.h"
#include <stdio.h>

void camlann_log(char*);
void camlann_fixme(char*);
void camlann_verbose(char*);
void camlann_init();
void set_camlann_flag_verbose(int);

#endif /* CAMLANN_UTIL_H */
