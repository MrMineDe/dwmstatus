# dwmstatus
A fast extensible script-based dwm status bar.
Its highly inspired by dwmblocks, but speeds up the process of executing
bash scirpts by multithreading the execution. Its written in about 100 Lines of C and is therfor
easiely understandable and hackable.

# Installation
Clone the repository in a folder of your choice and install by running "make install"

```bash
git clone https://github.com/MrMineDe/dwmstatus.git
cd dwmstatus
sudo make install
```
# Usage & Configuration
Start by simply running `dwmstatus`
It is encouraged to autostart dwmstatus in your xinitrc / autostart file when starting dwm

To Configure dwmstatus you have to edit `config.h`. You can add and remove entries as you wish.
Example Configuration:
```
#include "util.h"

static block blocks[] = {
	/* Command to run */ /*"\0", 0*/  /*delim*/	/*Repitition time in 1000ms*/
	{"music_playing",	"\0", 0,	"",	        1},
	{"packages",	        "\0", 0,	" | ",	        10*60},
	{"nettraf",		"\0", 0,	" | ",	        1},
	{"cpu",	        "\0", 0,	" | ",	        1},
	{"ram",		"\0", 0,	" | ",	        1},
	{"weather",		"\0", 0,	" | ",	        30*60},
	{"volume",		"\0", 0,	" | ",	        5},
	{"date '+%b, %d %A %H:%M:%S'", "\0", 0,	" | ", 1}
};

/* Global delimiter that gets applied before every block */
static const char* delim_global = "\0";

/* Sets if the delimiter should be hidden when the output of the block is empty. false: hidden*/
static const int delim_empty = false;
/* Same thing but for global delim. false: hidden */
static const int delim_global_empty = false;

```
You should not change the second and third argument, these are used internally.

After changing safe the file and run `sudo make install`. The changes will take effect on the next restart of dwmstatus.

## Upcoming
- Repitiotion time configuration
- Add mouse support like dwmstatus
- Add Support for statusbar elements written in C similar to slstatus and a few other dwm statusbars
- Add a few other misc settings to config.h / provide patches for them
