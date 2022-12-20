#include "util.h"

static block blocks[] = {
	/* Command to run */ /*  NULL, 0 */ /*delim*/	/*Repitition time in 100ms*/
	{"music_playing",	"\0", 0,	"",	1},
	{"packages",		"\0", 0,	" | ",	10*60},
	{"nettraf",		"\0", 0,	" | ",	1},
	{"cpu",			"\0", 0,	" | ",	1},
	{"ram",			"\0", 0,	" | ",	1},
	{"wetter",		"\0", 0,	" | ",	30*60},
	{"volume",		"\0", 0,	" | ",	5},
	{"date '+%b, %d %A %H:%M:%S'", "\0", 0,	" | ",	1}
};

/* Global delimiter that gets applied before every block */
static const char* delim_global = "\0";

/* Sets if the delimiter should be hidden when the output of the block is empty. false: hidden*/
static const int delim_empty = false;
/* Same thing but for global delim. false: hidden */
static const int delim_global_empty = false;
