/**
 * @file camlann_system.h
 * @brief Camlann compatibility shim for NIOS2 system.h.
 * @author Charles Daniels
 */


#ifndef CAMLANN_SYTEM_H
#define CAMLANN_SYTEM_H

#ifdef USE_CAMLANN
#define   KEYS_BASE       100
#define   SWITCHES_BASE   101
#define   LEDS_BASE       200
#define   HEX0_BASE       300
#define   HEX1_BASE       301
#define   HEX2_BASE       302
#define   HEX3_BASE       303
#define   HEX4_BASE       304
#define   HEX5_BASE       305
#define   HEX6_BASE       306
#define   HEX7_BASE       307
#endif

#define CHAR_BUFFER_DEV 0;
#define PIXEL_BUFFER_DEV 0;

#define CAMLANN_MAX_PIOS 512

#endif
