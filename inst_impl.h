#ifndef INST_IMPL_H
#define INST_IMPL_H

#include <stdint.h>

typedef void (*InstFuncPtr)(uint16_t);

void InstBR(uint16_t);
void InstADD(uint16_t);
void InstLD(uint16_t);
void InstST(uint16_t);
void InstJSR(uint16_t);
void InstAND(uint16_t);
void InstLDR(uint16_t);
void InstSTR(uint16_t);
void InstRTI(uint16_t);
void InstNOT(uint16_t);
void InstLDI(uint16_t);
void InstSTI(uint16_t);
void InstJMP(uint16_t);
void InstRES(uint16_t);
void InstLEA(uint16_t);
void InstTRAP(uint16_t);

#endif
