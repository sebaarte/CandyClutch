#pragma once
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include "PhysicsEngine.hpp"


class MainWindow : public Fl_Window {
        PhysicsEngine physicsEngine;
    public:
        MainWindow();
        void draw() override;
        int handle(int event) override;
        static void Timer_CB(void *userdata);
};