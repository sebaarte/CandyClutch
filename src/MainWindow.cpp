#include "MainWindow.hpp"
#include "constantes.hpp"

MainWindow::MainWindow() : Fl_Window(windowX, windowY, windowSize, windowSize, "CandyClutch"),physicsEngine{}
{
	Fl::add_timeout(refreshRate, Timer_CB, this);
	resizable(NULL);
}


void MainWindow::draw()
{
	Fl_Window::draw();
	physicsEngine.draw();
}


int MainWindow::handle(int event)
{
	switch (event)
	{
	case FL_MOVE:
		physicsEngine.mouseMove(Point{Fl::event_x(), Fl::event_y()});
		return 1;
	case FL_PUSH:
		physicsEngine.mouseClick(Point{Fl::event_x(), Fl::event_y()});
		return 1;
	case FL_KEYDOWN:
		physicsEngine.keyPressed(Fl::event_key());
		return 1;
	case FL_DRAG:
		physicsEngine.drag(Point{Fl::event_x(), Fl::event_y()});
		break;
	case FL_RELEASE:
		physicsEngine.undrag(Point{Fl::event_x(), Fl::event_y()});
		break;
		
	}
	return 0;
}

void MainWindow::Timer_CB(void *userdata)
{
	{
		MainWindow *o = (MainWindow *)userdata;
		o->redraw();
		Fl::repeat_timeout(refreshRate, Timer_CB, userdata);
	}
}