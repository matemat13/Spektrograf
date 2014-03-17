#include "include/UVStatusPanel.hpp"

UVStatusPanel::UVStatusPanel(wxFrame* parent, int pos) :
wxPanel(parent)
{
 painting = false;
 xpos = pos;
 SetBackgroundColour(wxColor(80,100,255));
 SetDoubleBuffered(true);
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 SetSize(200, 48);
 Align();
 //SetToolTip(_("Status UV"));


 Connect(wxEVT_LEFT_UP, wxMouseEventHandler(UVStatusPanel::onClick));

 
 //EVT_LEFT_UP(UVStatusPanel::onClick);

 /*Connect(this->m_windowId, wxEVT_COMMAND_LEFT_CLICK, 
          wxCommandEventHandler(UVStatusPanel::onClick));*/
 //EVT_COMMAND_LEFT_CLICK(this->m_windowId,UVStatusPanel::onFocus);
}
 
 /**Vykresli objekt kdyz je to treba (treba pri obnoveni z minimalizace)**/
void UVStatusPanel::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 if (!painting)
 {
  wxPaintDC dc(this);
  render(dc);
 }
}
 /*Vykresli objekt na vyzadani programu (treba pri zmene stavu)**/
void UVStatusPanel::paintNow()
{
 if (!painting)
 {
  wxClientDC dc(this);
  render(dc);
 }
}

void UVStatusPanel::Align() {
	SetPosition(wxPoint(GetParent()->GetSize().GetWidth()/2+UV_STATUS_P_PADDING-this->GetSize().GetWidth()/2, /*GetParent()->GetSize().GetHeight()-UV_STATUS_P_PADDING-this->GetSize().GetHeight()*/7));
	//Centre();
	Show();
}

void UVStatusPanel::render(wxDC &dc) 
{
	dc.SetBackground(wxBrush (wxColor(230,230,246)));
	//dc.SetPen(wxPen(wxColour(0,255,0),1,wxPENSTYLE_DOT));
	dc.Clear();

	dc.SetFont(wxFont(17, wxDEFAULT, wxNORMAL, wxBOLD));
	if(!state) 
	{
        dc.SetTextForeground(*wxRED);
		wxSize size = dc.GetTextExtent(_("!"));
		dc.DrawText(_("!"), UV_STATUS_P_PADDING*2+44, (this->GetSize().GetHeight()-size.GetHeight())/2);
	}
	else
	{
        dc.SetTextForeground(wxColor(0,128,0));
		wxSize size = dc.GetTextExtent(_("OK"));
		dc.DrawText(_("OK"), UV_STATUS_P_PADDING*2+44, (this->GetSize().GetHeight()-size.GetHeight())/2);
	}
	DrawLed(dc, state);
	/*if(state) {
	    //dc.SetPen(wxPen(wxColor(111,0,177)));
	    //dc.SetBrush(wxBrush (wxColor(111,0,177)));
	    //dc.DrawRectangle(0,0,this->GetSize().GetWidth(), this->GetSize().GetHeight());
		unsigned char end[] = {230,230,246};
        unsigned char start[] = {111,0,177};
		unsigned char current[] = {0,0,0};

		for(unsigned char i=0; i<UV_STATUS_P_PADDING; i++) 
		{
			for(unsigned char j=0; j<3; j++) 
			{
				current[j] = end[j]+((float)(start[j]-end[j])/((float)UV_STATUS_P_PADDING))*i;
			}
	        dc.SetPen(wxPen(wxColour(current[0],current[1],current[2])));
	        dc.SetBrush(wxBrush (wxColour(current[0],current[1],current[2])));
	        dc.DrawRectangle(0+i,0+i,this->GetSize().GetWidth()-2*i, this->GetSize().GetHeight()-2*i);
		}
	}
	else
	{
	    dc.SetPen(wxPen(wxColor(230,230,246)));
	    dc.SetBrush(wxBrush (wxColor(230,230,246)));
	    dc.DrawRectangle(0,0,this->GetSize().GetWidth(), this->GetSize().GetHeight());
	}

	dc.SetPen(wxPen(wxColor(0,0,0),1));
	dc.SetBrush(wxBrush (wxColor(164,164,164)));
	dc.DrawRectangle(UV_STATUS_P_PADDING,UV_STATUS_P_PADDING,this->GetSize().GetWidth()-UV_STATUS_P_PADDING*2, this->GetSize().GetHeight()-UV_STATUS_P_PADDING*2);

	dc.SetFont(wxFont(17, wxDEFAULT, wxNORMAL, wxBOLD));
	if(state) 
	{
        dc.SetTextForeground(*wxRED);
		wxSize size = dc.GetTextExtent(_("!"));
		dc.DrawText(_("!"), UV_STATUS_P_PADDING*2, (this->GetSize().GetHeight()-size.GetHeight())/2);
	}
	else
	{
        dc.SetTextForeground(wxColor(0,128,0));
		wxSize size = dc.GetTextExtent(_("OK"));
		dc.DrawText(_("OK"), UV_STATUS_P_PADDING*2, (this->GetSize().GetHeight()-size.GetHeight())/2);
	}
	state = !state;*/
}

bool UVStatusPanel::State(bool st) {
	bool changed = state!=st;
	state = st;
	if(changed) {
		wxClientDC dc(this);
		render(dc);
	}
	return st;
}
bool UVStatusPanel::State() {
	return state;
}

void UVStatusPanel::onClick(wxMouseEvent& WXUNUSED(event)) {
	//state=!state;
	paintNow();
	return;
}
/**drawing functions**/
void UVStatusPanel::DrawLed(wxDC &dc, bool status, int x, int y) {
	static const wxColour cerna_f = wxColor(15,0,30);
	static const wxColour tmava_f = wxColor(70,0,130);
    static const wxColour normal_f = wxColor(170, 80, 210);
	static const wxColour svetla_f = wxColor(205,145,223);
	static const wxColour bila_f = wxColor(180, 60, 160);
    if (status == true) //UV is ok if true
    {
     dc.SetBrush(wxBrush(tmava_f));
     dc.SetPen(wxPen(cerna_f));
	 dc.DrawCircle(x+22,y+22,12);
	 dc.GradientFillConcentric(wxRect(x+14, y+14, 12, 12), normal_f, tmava_f, wxPoint(6, 6));
    }
    else
    {
	 /**Svitici okoli**/
     dc.SetBrush(wxBrush(svetla_f));
     dc.SetPen(wxPen(wxColor(230,230,246), 0, wxPENSTYLE_TRANSPARENT));
     dc.GradientFillConcentric(wxRect(x, y, 44, 44), normal_f, wxColor(230,230,246), wxPoint(22, 22));
	 /**Ledka**/
     dc.SetBrush(wxBrush(normal_f));
     dc.SetPen(wxPen(wxColor(180, 20, 180)));
     dc.DrawCircle(x+22,y+22,12);
     dc.GradientFillConcentric(wxRect(14, 14, 12, 12), svetla_f, normal_f, wxPoint(6, 6));
    }
}