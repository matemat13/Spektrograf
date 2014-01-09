#pragma once
#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include "BasicDrawPane.hpp"

class wxGLCanvasSubClass;

class RenderTimer : public wxTimer
{
private:
    wxGLCanvasSubClass *pane;
public:
    RenderTimer(wxGLCanvasSubClass* pane);
    void Notify();
    void start();
};
 