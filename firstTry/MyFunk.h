#pragma once
#include <iostream>

int my_getline(char* buffer, unsigned char lenght);

template <typename T>
int my_atoi(const char* buffer, T lowest, T highest, T* number) {
	*number = atoi(buffer);
	if (*number > highest) {
		std::cout << "Number is too high" << '\n';
		return 1;
	}
	else {
		if (*number < lowest) {
			std::cout << "Number is too low or incorrect input" << '\n';
			return 2;
		}
	}
	return 0;
}