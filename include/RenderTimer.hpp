#pragma once
#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include "GraphPanel.hpp"


class RenderTimer : public wxTimer
{
    GraphPanel* pane;
public:
    RenderTimer(GraphPanel* pane);
    void Notify();
    void start();
};
 