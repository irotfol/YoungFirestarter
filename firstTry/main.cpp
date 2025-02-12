#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include <vector>
#include "Spichka.h"




int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	unsigned short int kolvo = 0;
	char buffer[29] = {};
	int i = 0;

	if (my_getline(buffer, 3) != 0) {
		return 1;
	}
	
	if (my_atoi<unsigned short int>(buffer, 1, 40, &kolvo) != 0) {
		return 2;
	}

	Vec_Spichka vec(kolvo);
	if (vec.input(buffer) != 0) {
		return 3;
	}
	if (vec.create_points() != 0) {
		return 4;
	}
	if (vec.ignite() != 0) {
		return 5;
	}
	if (vec.output() != 0) {
		return 6;
	}


	return 0;
}