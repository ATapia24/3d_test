//VVC VIRTUAL SANDBOX
//6-20-2017
//ADRIAN TAPIA
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <thread>
#include "Window.h"

int main() {
	Window window(1280, 720, "sandbox", false);
	std::thread windowThread(&Window::draw, std::ref(window));


	while(window.isOpen()){

	}

	windowThread.join();
    return 0;
}
