/**
 * @file camlann_main.c
 * @brief Camlann entry point.
 * @author Charles Daniels
 */


#include "camlann_main.h"

int main(int argc, char* argv[]) {

	#ifdef USE_CAMLANN
	char c;
	char* end;
	char* keystate_str;
	char* swstate_str;
	int keystate, swstate;
	int set_keystate, set_swstate;
	int flag_verbose;

	set_keystate = 0;
	flag_verbose = 0;

	keystate_str = NULL;

	while(( c = getopt( argc, argv, "hk:vs:" )) != -1 )
	switch ( c ) {

		case 'k':
			keystate_str = optarg;
			set_keystate = 1;
			break;
		case 's':
			swstate_str = optarg;
			set_swstate = 1;
			break;
		case 'h':
			fprintf(stderr, "Usage:\n\n");
			fprintf(stderr, "\t-k - specify key state\n\n");
			fprintf(stderr, "\t-h - show this message\n\n");
			fprintf(stderr, "\t-v - verbose output\n\n");
			exit(0);
			break;
		case 'v':
			flag_verbose = 1;
			break;
		case '?':
			fprintf( stderr, "Unrecognized option!\n" );
			fprintf( stderr, "Use -h for help.\n" );
			exit(1);
			break;

	}

	camlann_init();

	set_camlann_flag_verbose(flag_verbose);
	camlann_verbose("Camlann has been launched in verbose mode.\n");

	if (set_keystate) {
		keystate = strtol(keystate_str, &end, 10);
	} else {
		keystate = 7;
	}

	if (set_swstate) {
		swstate = strtol(swstate_str, &end, 10);
	} else {
		swstate = 0;
	}

	/* initialize PIOs to desired states */
	IOWR_ALTERA_AVALON_PIO_DATA(KEYS_BASE, keystate);
	IOWR_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE, swstate);
	#endif

	printf("FPS: %f INTERVAL: %f ms\n", CAMLANN_TARGET_FPS, CAMLANN_RENDER_INTERVAL);

	#ifndef CAMLANN_CI
	return USER_MAIN();
	#endif

}
