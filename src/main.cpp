#include <iostream>
#include <vector>
#include <thread>
#include "physics/particule.hpp"
#include "graphics/render.hpp"

int main() {
	std::jthread t(initWindow);
	std::cout << "Test\n";
	return 0;
}
