#pragma once
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include "PhysicsEngine.hpp"





class MainWindow : public Fl_Window {
    PhysicsEngine physicsEngine;
    public:
    MainWindow() : Fl_Window(500, 500, 500, 500, "Lab 2") {
        Fl::add_timeout(1.0/60, Timer_CB, this);
        resizable(this);
    }
    void draw() override {
        Fl_Window::draw();
        physicsEngine.draw();
    }
    int handle(int event) override {
        switch (event) {
            case FL_MOVE:
                physicsEngine.mouseMove(Point{Fl::event_x(),Fl::event_y()});
                return 1;
            case FL_PUSH:
                physicsEngine.mouseClick(Point{Fl::event_x(),Fl::event_y()});
                return 1;                
            case FL_KEYDOWN:
                physicsEngine.keyPressed(Fl::event_key());
                return 1;
        }
        return 0;
    }
    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow*) userdata;
        o->redraw();
        Fl::repeat_timeout(1.0/60, Timer_CB, userdata);
    }
};