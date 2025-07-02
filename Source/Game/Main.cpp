#include "Math/Math.h"
#include "Core/Random.h"
#include <iostream>

#define NAME "Ray\n"

using namespace viper;

int main(){
	//const float deg = RadToDeg(viper::pi);
	//min(5, 3);
	//clamp(2, 3, 5);

	std::cout << NAME;
	std::cout << "Hello, World!\n";
	std::cout << pi << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << viper::random::getRandomFloat() << std::endl;
	}
}