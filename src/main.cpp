#include "random"
#include "MainWindow.hpp"
#include "Candies.hpp"
#include "iostream"


int main(int argc, char *argv[]) {
	srand(time(0));
	MainWindow window;
	window.show(argc, argv);
	return Fl::run();
}