/**
 * @file camlann_util.c
 * @brief Camlann general purpose internal functions.
 * @author Charles Daniels
 */


#include "camlann_util.h"

int camlann_flag_verbose;

/**
 * @brief Log a message somewhere.
 *
 * For now, this is just printf, but in the future it may do something clever.
 *
 * @param msg the message to log.
 */
void camlann_log(char* msg) {
	#ifdef USE_CAMLANN
	printf("[CAMLANN]: %s", msg);
	#endif /* USE_CAMLANN */
}

/**
 * @brief Wrapper for camlann_log to signal that a feature is missing or
 * broken.
 *
 * @param msg the message to log.
 */
void camlann_fixme(char* msg) {
	#ifdef USE_CAMLANN
	printf("[CAMLANN-FIXME]: %s", msg);
	#endif /* USE_CAMLANN */
}

/**
 * @brief Perform necessary steps to initialize Camlann.
 *
 * This needs to be called before USER_MAIN.
 */
void camlann_init() {
	camlann_log("camlann_util/camlann_init: initializing PIO states\n");
	camlann_pio_init();
}

void camlann_verbose(char* msg) {
	#ifdef USE_CAMLANN
	if (camlann_flag_verbose) { printf("[CAMLANN-VERBOSE]: %s", msg); }
	#endif /* USE_CAMLANN */
}

/**
 * @brief To avoid a global/extern, use this function to set the verbose flag.
 *
 * @param val
 */
void set_camlann_flag_verbose(int val){
	camlann_flag_verbose = val;
}
