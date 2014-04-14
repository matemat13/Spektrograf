#pragma once
#include "include\rgbhsv.h"
#include "..\include\GraphMemoryMan.hpp"
#include "wx/wx.h"

#define GRAPH_MEMORY_SIZE 20
#define GRAPH_MEMORY_MARGIN 5
#define GRAPH_MEMORY_START 80
class GraphMemoryMan;

class GraphMemory : public wxPanel
{
public:
	//GraphMemory(void);
	GraphMemory(wxWindow *, short*, int, GraphMemoryMan *);

    void Align();
	void Align(int new_order);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();

	void setColor(colors::hsv);
	colors::rgb getColor();

	int getGraphData(short*&thedata);

	void onClick(wxMouseEvent& event);

	void onSelect(bool state, bool multiselect=false);
	bool isSelected();


	~GraphMemory(void);
private:
	short* data;
	int data_len;
	int order;
	bool selected;

	GraphMemoryMan *owner;
	colors::hsv color;

	void render(wxDC &dc);
	
};

