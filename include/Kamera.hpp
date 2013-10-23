#ifndef KAMERA_HPP
#define KAMERA_HPP

#include "wx/wx.h"
#include <windows.h>
#include <dshow.h>
#include <strmif.h>
#include <d3d9.h>
#include <Vmr9.h>
#include <vector>
#include <assert.h>
#pragma comment(lib, "strmiids")

class Kamera
{
public:
	Kamera();
	void Obrazek(wxImage *img);
private:
	//Moje fce
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void NastavKamery();

	//moje promenny
	int stav;
	//IBaseFilter *camera_filter;
	IBaseFilter *camera_filter;

};

#endif