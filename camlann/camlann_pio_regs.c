#include "camlann_pio_regs.h"

#ifdef USE_CAMLANN
/* evil global state variable to maintain PIO state */
uint32_t* camlann_pio_state;


/**
 * @brief On the board, this would read from a physical PIO. In Camlann, it
 * simply returns the value corresponding to the base address in
 * camlann_pio_state.
 *
 * @param base Base address, must be one of those defined in camlann_system.h
 *
 * @return Value at said base address.
 */
alt_u32 IORD_ALTERA_AVALON_PIO_DATA(alt_u32 base) {
	char* msg;
	alt_u32 state;

	msg = malloc(1024 * sizeof(char));
	state = camlann_pio_state[base];
	sprintf(msg, "read PIO state at %x as %x\n", base, state);
	camlann_verbose(msg);
	return state;
}

/**
 * @brief On the board, this would route to a physical PIO. In Camlann, we
 * instead assume the base address will be one of those defined in
 * camlann_system.h, which is guaranteed to be a valid subscript into
 * camlann_pio_state.
 *
 * @param base Base address of the "PIO".
 * @param val Value to set "write" the "PIO".
 */
void IOWR_ALTERA_AVALON_PIO_DATA(alt_u32 base, alt_u32 val) {
	char* msg;
	msg = malloc(1024 * sizeof(char));
	sprintf(msg, "writing %x to PIO at %x\n", val, base);
	camlann_verbose(msg);
	camlann_pio_state[base] = val;
}

/**
 * @brief This gets called from camlann_init and sets up camlann_pio_state.
 */
void camlann_pio_init() {
	camlann_pio_state = (uint32_t*) \
		malloc(sizeof(uint32_t) * CAMLANN_MAX_PIOS);

	if (camlann_pio_state == NULL) {
		perror("Failed to allocate memory for camlann_pio_state.");
		exit(1);
	}
	int i;
	for (i = 0; i < CAMLANN_MAX_PIOS ; i++ ) {
		camlann_pio_state[i] = 0;
	}
}

#else

// dummy implementation for when we are not using Camlann
void camlann_pio_init() {
	// do nothing
}

#endif
