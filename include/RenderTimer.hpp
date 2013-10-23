#pragma once
#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include "BasicDrawPane.hpp"


class RenderTimer : public wxTimer
{
    BasicDrawPane* pane;
public:
    RenderTimer(BasicDrawPane* pane);
    void Notify();
    void start();
};
 