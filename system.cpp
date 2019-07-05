#include "system.h"

#include <stdint.h>
#include <array>


namespace System{
	std::array<uint16_t, RAM_UNIT_COUNT> memory = {};
	std::array<uint16_t, REG_COUNT> reg = {};
	std::array<InstFuncPtr, INST_TYPE_COUNT> instruction = {
		InstBR,
		InstADD,
		InstLD,
		InstST,
		InstJSR,
		InstAND,
		InstLDR,
		InstSTR,
		InstRTI,
		InstNOT,
		InstLDI,
		InstSTI,
		InstJMP,
		InstRES,
		InstLEA,
		InstTRAP
	};

}
