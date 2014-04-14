#include "..\include\GraphMemoryMan.hpp"
using namespace colors;

GraphMemoryMan::GraphMemoryMan(wxFrame *parent, wxGLCanvasSubClass* graphn)
{
	members = std::vector<GraphMemory*>();
	currentColor = colors::hsv(0, 1.0, 1.0);
	colorStep = 60;
	this->parent = parent;

	graph = graphn; 
}
GraphMemory* GraphMemoryMan::createNew() {
	short* pointer;
	int len = graph->getGraph(pointer);
	return createNew(pointer, len);
}

int GraphMemoryMan::count() {
	return (int)members.size();
}
GraphMemory* GraphMemoryMan::getMemory(int index) {
	return members[index];
}

GraphMemory* GraphMemoryMan::createNew(short* data, int data_len) {
	if(members.size()>maxMembers)
		return NULL;
	
	short* data2 = new short[data_len];
	memcpy(data2, data, sizeof(short)*data_len);

	GraphMemory *dalsi = new GraphMemory(parent, data2, data_len, this);

	

	dalsi->Align((int)members.size());
	dalsi->setColor(colors::hsv(currentColor));
	dalsi->onSelect(true);
	members.push_back(dalsi);

	currentColor.h=findBestColor();


	
	return dalsi;
}
int GraphMemoryMan::findBestColor() {
	if(members.size()==0) {
		return 0;
	}
	if(members.size()==1) {
		return ((colors::hsv)members[0]->getColor()).h+112;
	}

	colors::hsv tmp;
	std::vector<int> hues = std::vector<int>();
	//Najit vsechny barvy
	for(int i=0, l=members.size(); i<l; i++) {
		tmp = members[i]->getColor();
		hues.push_back((int)tmp.h);
	}
	//Seradit barvy podle uhlu
	std::sort(hues.begin(), hues.end());

	int largestDif = -1;
	int largestDifAngle[2];
	int tmpDif;

	for(int i=0, l=hues.size(); i<l; i++) {
		//Get the angle difference
		tmpDif = angleDifference(hues[i], hues[(i+1)%l]);
		if(tmpDif>largestDif) {
			//Remember which was the largest difference
			largestDif = tmpDif;
			//Remember the two angles
			largestDifAngle[0] = hues[i];
			largestDifAngle[1] = hues[(i+1)%l];
			if(i+1==l) {
				largestDifAngle[1] = 360+largestDifAngle[1];
			}
		}
	}
	//Debug

	//Calculate angle between the most distant angles
	return std::max(largestDifAngle[0],largestDifAngle[1]) - abs(largestDifAngle[0]-largestDifAngle[1])/2.0;
}
colors::hsv GraphMemoryMan::nextColor() {
	return currentColor;
}

bool GraphMemoryMan::remove(GraphMemory* ref) {
	bool removed = false;
	for(int i=0, l=members.size(); i<l; i++) {
		if(members[i]==ref) {
			members.erase(members.begin() + i);
			delete ref;
			removed = true;
			break;
		}
	}
	if(removed) {
		Align();
	}
	return removed;
}
void GraphMemoryMan::deselectExcept(GraphMemory* ref) {
	for(int i=0, l=members.size(); i<l; i++) {
		if(members[i]!=ref) {
			members[i]->onSelect(false);
		}
	}
}
void GraphMemoryMan::Align() {
	for(int i=0, l=members.size(); i<l; i++) {
		members[i]->Align(i);
	}
}

int GraphMemoryMan::angleDifference(int a, int b) {
	int res;
	res = a - b;
    res = (res + 180) % 360 - 180;
	return abs(res);
}
/*GraphMemoryMan::~GraphMemoryMan(void)
{
}*/
