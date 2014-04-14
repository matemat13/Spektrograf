#pragma once
#include "..\include\GraphMemory.hpp"
#include "include/BasicDrawPane.hpp"
#include <vector>
#include "wx/wx.h"
#include "include\rgbhsv.h"


class wxGLCanvasSubClass;
class GraphMemory;

class GraphMemoryMan
{
public:
	GraphMemoryMan(wxFrame *, wxGLCanvasSubClass* );

	GraphMemory* createNew();
	GraphMemory* createNew(short*, int);

	bool remove(GraphMemory* ref);
	void deselectExcept(GraphMemory*);

	colors::hsv nextColor();

	int count();
	GraphMemory* getMemory(int);

	void Align();
	int maxMembers;
private:
	std::vector<GraphMemory*> members;
	wxGLCanvasSubClass* graph;
	colors::hsv currentColor;
	double colorStep;
	wxFrame *parent;

	int findBestColor();

	static int angleDifference(int a, int b);
	
	//~GraphMemoryMan(void);
};

