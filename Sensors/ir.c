#ifndef FTC_IR
#define FTC_IR

#include "../drivers/hitechnic-irseeker-v2.h"

int readIR() {
	return HTIRS2readACDir(IRSeeker);
}

bool irValid(int seeker) {
	if (seeker < 1) {
		return false;
	} else if (seeker > 8) {
		return false;
	}
	return true;
}

#endif
