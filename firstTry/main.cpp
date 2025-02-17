//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

#include <vector>
#include "Spichka.h"




int main(void) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	unsigned short int kolvo = 0;
	char buffer[29] = {};
	char i = 0;
	
	//Input number of matches
	if (my_getline(buffer, 3) != 0) {
		return 1;
	}
	//Validation of the correct input of the number of matches
	if (my_atoi<unsigned short int>(buffer, 1, 40, &kolvo) != 0) {
		return 2;
	}

	Vec_Spichka vec(kolvo);

	//Input of coordinates and burning time of the matches
	if (vec.input(buffer) != 0) {
		return 3;
	}
	//Creation a list of points
	if (vec.create_points() != 0) {
		return 4;
	}
	//Launching the calculation of burning time for each point
	if (vec.ignite() != 0) {
		return 5;
	}
	//Output of the result
	if (vec.output() != 0) {
		return 6;
	}
	//To exit the program, enter any character and/or press the ENTER
	i = getchar();
	return 0;
}