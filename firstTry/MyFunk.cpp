#include "MyFunk.h"

int my_getline(char* buffer, unsigned char lenght) {
	std::cin.getline(buffer, lenght, '\n');
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
}