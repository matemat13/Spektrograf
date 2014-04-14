#include "..\include\GraphMemory.hpp"


GraphMemory::GraphMemory(wxWindow* parent, short* data, int data_lenn, GraphMemoryMan *ownern):wxPanel(parent)
{
	this->data = data;
	data_len = data_lenn;
	owner = ownern;
	order = 0;
	selected = false;

	SetCursor(wxCURSOR_HAND);

	Connect(wxEVT_LEFT_UP, wxMouseEventHandler(GraphMemory::onClick),NULL, this);
    //Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GraphMemory::onClick), NULL, this);

}
void GraphMemory::Align(int new_order) {
	order = new_order;
	Align();
}

void GraphMemory::Align() {
	SetSize(GRAPH_MEMORY_SIZE, GRAPH_MEMORY_SIZE);
	//SetPosition(wxPoint(40-GRAPH_MEMORY_SIZE/2, GRAPH_MEMORY_START+order*(GRAPH_MEMORY_SIZE+GRAPH_MEMORY_MARGIN)));
	SetPosition(wxPoint(250+order*(GRAPH_MEMORY_SIZE+GRAPH_MEMORY_MARGIN), 30-GRAPH_MEMORY_SIZE/2));
	Raise();
}
void GraphMemory::render(wxDC &dc) {
	colors::rgb tmp = colors::rgb(color);

	dc.SetBrush(wxBrush(wxColor(tmp.r, tmp.g, tmp.b)));

	dc.DrawRectangle(0,0,GRAPH_MEMORY_SIZE, GRAPH_MEMORY_SIZE);
}
///Color
void GraphMemory::setColor(colors::hsv ncolor) {
	color = ncolor;
	color.v = 0.8;
}
colors::rgb GraphMemory::getColor() {
	return (colors::rgb)color;
}

//Data
int GraphMemory::getGraphData(short*&thedata) {
	thedata = data;
	return data_len;
}
GraphMemory::~GraphMemory(void)
{
	delete[] data;
}

void GraphMemory::onClick(wxMouseEvent& event) {
	//owner->remove(this);
	if(!selected) {
      onSelect(true);
	}
	else {
	  owner->remove(this);
	}
}

 /**Vykresli objekt kdyz je to treba (treba pri obnoveni z minimalizace)**/
void GraphMemory::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 //if (!painting)
 //{
  wxPaintDC dc(this);
  render(dc);
 //}
}
 /*Vykresli objekt na vyzadani programu (treba pri zmene stavu)**/
void GraphMemory::paintNow()
{
 //if (!painting)
 //{
  wxClientDC dc(this);
  render(dc);
 //}
}
void GraphMemory::onSelect(bool state, bool multiselect) {
	if(state) {
		color.v = 1.0;
		selected = true;
		if(!multiselect)
		  owner->deselectExcept(this);
	}
	else {
		color.v = 0.7;
		selected = false;
	}
	paintNow();
}
bool GraphMemory::isSelected() {
    return selected;
}