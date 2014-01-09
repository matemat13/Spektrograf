#include "../include/RenderTimer.hpp"

RenderTimer::RenderTimer(wxGLCanvasSubClass* pane) : wxTimer()
{
    RenderTimer::pane = pane;
}
 
void RenderTimer::Notify()
{
	if(pane->IsShownOnScreen()&&pane->GetParent()->IsShownOnScreen())
      pane->paintNow();
	else 
	{
      //wxMessageBox("ble");
	  //Stop();
	}
}
 
void RenderTimer::start()
{
    wxTimer::Start(50);
}