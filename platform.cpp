#include "platform.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


Platform::Platform(){
	/*original tio*/
	tcgetattr(STDIN_FILENO, &original_tio);
	/*new tio*/
	new_tio = original_tio;
	new_tio.c_lflag &= ~ICANON & ~ECHO;
}

Platform::~Platform(){

}

/*
 *Put stdio in non-canonical mode
 */
void Platform::DisableInputBuffering(){
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

/*
 *restore standard stdio
 */
void Platform::RestoreInputBuffering(){
	tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}
