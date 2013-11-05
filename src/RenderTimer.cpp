#include "../include/RenderTimer.hpp"

RenderTimer::RenderTimer(GraphPanel* pane) : wxTimer()
{
    RenderTimer::pane = pane;
}
 
void RenderTimer::Notify()
{
    pane->paintNow();
}
 
void RenderTimer::start()
{
    wxTimer::Start(40);
}