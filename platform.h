#ifndef PLATFORM_H
#define PLATFORM_H

#include <termios.h>

class Platform{
	private:
		struct termios original_tio;
		struct termios new_tio;

	public:
		Platform();
		~Platform();
	private:
		Platform(const Platform&) = delete;
		Platform& operator=(const Platform&) = delete;
		
	public:
		void DisableInputBuffering();
		void RestoreInputBuffering();
};

#endif
