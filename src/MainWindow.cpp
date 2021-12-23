#include "MainWindow.hpp"
#include "constantes.hpp"
#include "Fl/Fl.H"

MainWindow::MainWindow() : Fl_Window(WINDOWX, WINDOWY, WINDOWSIZE, WINDOWSIZE, "CandyClutch"), physicsEngine{}
{
	Fl::add_timeout(refreshRate, Timer_CB, this);
	resizable(NULL);
}

void MainWindow::draw()
{
	Fl_Window::draw();
	physicsEngine.refresh();
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
	case FL_RELEASE:
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			physicsEngine.undrag(Point{Fl::event_x(), Fl::event_y()});
		}
		break;
	case FL_DRAG:
		physicsEngine.drag(Point{Fl::event_x(), Fl::event_y()});
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