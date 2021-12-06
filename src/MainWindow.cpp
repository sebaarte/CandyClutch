#include "MainWindow.hpp"

MainWindow::MainWindow() : Fl_Window(800, 500, 700, 700, "CandyClutch"),physicsEngine{}
{
	Fl::add_timeout(1.0 / 60, Timer_CB, this);
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
	/*case FL_DRAG:
		physicsEngine.draggedElement(Point{Fl::event_x(), Fl::event_y()});
		break;*/
	}
	return 0;
}

void MainWindow::Timer_CB(void *userdata)
{
	{
		MainWindow *o = (MainWindow *)userdata;
		o->redraw();
		Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);
	}
}