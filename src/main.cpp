#include "random"
#include "MainWindow.hpp"
#include "Candies.hpp"
#include "iostream"

/*
done tasks:
1
2
11

*/

int main(int argc, char *argv[]) {
	srand(time(0));
	MainWindow window;
	window.show(argc, argv);
	return Fl::run();
}