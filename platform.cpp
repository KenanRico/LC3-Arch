#include "platform.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


Platform::Platform(){
	/*original tio*/
	tcgetattr(STDIN_FILENO, &original_tio);
	/*new tio*/
	struct termios new_tio = original_tio;
	new_tio.c_lflag &= ~ICANON & ~ECHO;
}

Platform::~Platform(){

}

void Platform::DisableInputBuffering(){
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void Platform::RestoreInputBuffering(){
	tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
	printf("\n");
}
