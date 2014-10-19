#include "include/Wavelength.hpp"


WavelengthPanel::WavelengthPanel(wxFrame* parent, SettingsManager *setMan, int pos, Kamera *kam) :
wxPanel(parent)
{
	painting = false;

	SetMan = setMan;
	this->kam = kam;

}
void WavelengthPanel::onClick(wxMouseEvent& WXUNUSED(event)) {
	paintNow();
	return;
}
void WavelengthPanel::render(wxDC &dc) {
 dc.SetBackground(wxBrush (APP_STYLE_MAINBG));
 dc.Clear();
 //Draw dark blue background
 //dc.SetBrush(wxColor(001,01,007));
 //dc.DrawRectangle (0, 0, cur_width, cur_height);
 //Draw dashed line
 //dc.SetPen(wxPen(wxColor(20,20,80), 1, wxLONG_DASH));

 //glPixelZoom(cur_width / (double) 640, cur_height / (double) 480);
 //dc.DrawLine(wxPoint(0, cur_height-1),wxPoint(cur_width, cur_height-1));

 //Draw the inportant shit
 if(!kam->isReady())
	 return;
 
 //Draw boundaries
 dc.SetPen(wxPen(wxColor(150,0,140), 3, wxSOLID));

 int uv = SetMan->GetSetting(SETT_LINE_UV);
 int ir = SetMan->GetSetting(SETT_LINE_RED);
 //Zjisteni otoceni a pote sirky grafu
 int width;
 //Jestli je graf zrcadlove - potom je treba od hodnot odecist width
 bool zrcadlovy = false;
 switch(SetMan->GetSetting(SETT_CAM_ROT)) {
   case 0 : width = kam->GetWidth();break;
   case 1 : width = kam->GetHeight();break;
   case 2 : width = kam->GetWidth();zrcadlovy=true;break;
   case 3 : width = kam->GetHeight();zrcadlovy=true;break;
 }

 if(width<=0||width>2048) {
   dc.SetTextForeground(wxColor(240,80,0));
   dc.DrawText(_("ERROR"),  0, 0);
   return;
 }
 //Transformace velikosti grafu na velikost okna
 float transform = cur_width/((float)width);
 if(zrcadlovy) {
	 uv = width-uv;
	 ir = width - ir;
	 
 }
 //Provedeni transformace
 uv = (uv)*transform;
 ir = (ir)*transform;

 //Sinusovka
 wxPoint last;
 wxPoint current;
 
 short distance = abs(uv-ir);
 short direction = sgn(-ir+uv);
 float percent;

 dc.SetPen(wxPen(wxColor(100,110,130), 1, wxSOLID));
 for(short i=0; i<distance; i++) {
	 percent = (i/(float)distance)*100;
	 current = wxPoint(i*direction+ir, cos(pow(percent+5,1.9)/15.0)*15+15);
	 if(i!=0) {
       dc.DrawLine(last,current);
	 }
	 //Skok o bod
	 last = current;
 }
 //Hranice UV a IR
 dc.SetPen(wxPen(wxColor(180,0,240), 2, wxSOLID));
 dc.DrawLine(wxPoint(uv, 0),wxPoint(uv, cur_height-17));
 dc.SetPen(wxPen(wxColor(250,30,0), 2, wxSOLID));
 
 dc.DrawLine(wxPoint(ir, 0),wxPoint(ir, cur_height-17));


 //Neser
 const int mezera = 30;
 const int tsirka = 50;
 const int rozdilnm = WAVELENGTH_IR-WAVELENGTH_UV;

 drawWavelengthAt(dc, uv, 380);
 drawWavelengthAt(dc, ir, 649);

 int sirka = abs(uv-ir);

 if(sirka<2)
	 return;


 sirka-= tsirka+mezera;

 int pocet = sirka/(mezera+tsirka);

 float kroknm = rozdilnm/(float)(pocet+1);

 float vzdalenosti = sirka/(float)pocet;

 int start = std::min(uv, ir);

 dc.SetPen(wxPen(wxColor(0,0,0), 1, wxSOLID));

 int x;

 for(int i=1; i<=pocet; i++) {
	 x = i*vzdalenosti + start;
	 dc.DrawLine(wxPoint(x, 0),wxPoint(x, cur_height-20));

	 if(uv<ir) {
		 
		 drawWavelengthAt(dc, x, WAVELENGTH_UV+(i)*kroknm);
	 }
	 else {
		 drawWavelengthAt(dc, x, WAVELENGTH_IR-i*kroknm);
	 }
 }
}
void WavelengthPanel::Align() {
 cur_width = GetParent()->GetSize().GetWidth() - 160;
 cur_height = 50;
 SetSize(cur_width, cur_height);  //nastav velikost
 SetPosition(wxPoint(79, GetParent()->GetSize().GetHeight()-58));
 //SetPosition(wxPoint(0,0));
 paintNow();
}
/** Vykras;i vlnovou delku centrovanou na bod **/
void WavelengthPanel::drawWavelengthAt(wxDC &dc, const int offset, int wavelength) {
	    std::string text = toString(wavelength);
		text.append("nm");

        dc.SetTextForeground(wxColor(0,100,200));
		wxSize size = dc.GetTextExtent(_(text.c_str()));
		dc.DrawText(_(text.c_str()), offset-size.x/2, cur_height-1-size.y);


}
 /**Vykresli objekt kdyz je to treba (treba pri obnoveni z minimalizace)**/
void WavelengthPanel::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 if (!painting)
 {
  wxPaintDC dc(this);
  render(dc);
 }
}
 /*Vykresli objekt na vyzadani programu (treba pri zmene stavu)**/
void WavelengthPanel::paintNow()
{
 if (!painting)
 {
  wxClientDC dc(this);
  render(dc);
 }
}
