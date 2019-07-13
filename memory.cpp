#include "memory.h"

#include <stdint.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>

#include <sys/time.h>
#include <sys/select.h>


#define OK 0
#define BAD_FILE_PATH 1


Memory::Memory(): status(OK){

}

Memory::~Memory(){

}

/*
 *Swap16 helper func
 */
uint16_t Swap16(uint16_t val){
	return (val<<8) | (val>>8);
}

void Memory::LoadImage(const std::string& image_path){
	/*Read image*/
	FILE* file = fopen(image_path.c_str(), "rb");
	if(file==nullptr){
		status = BAD_FILE_PATH;
		return;
	}
	/*first 16 bits of LC3 executables give us the location to place the image*/
	uint16_t origin = 0;
	fread(&origin, sizeof(origin), 1, file);
	origin = Swap16(origin);
	/*Read rest of image*/
	uint16_t max_read = size - origin;
	uint16_t* p = &memory[0] + origin;
	size_t read = fread(p, sizeof(uint16_t), max_read, file);
	/*swap to litten endian*/
	while(read-- > 0){
		*p = Swap16(*p);
		++p;
	}
}

/*
 * key checking helper func
 */
int CheckKey(){
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	return select(1, &readfds, NULL, NULL, &timeout) != 0;
}

uint16_t& Memory::operator[](int addr){
	if(addr==KBSR){
		if(CheckKey()!=0){
			memory[KBSR] = 1<<15;
			memory[KBDR] = getchar();
		}else{
			memory[KBSR] = 0;
		}
	}
	return memory.at(i);
}

void Memory::PrintContent() const{
	for(int i=0; i<size; ++i){
		std::cout<<memory[i]<<" ";
	}
	std::cout<<"\n";
}
