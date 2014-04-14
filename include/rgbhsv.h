#pragma once
#include "wx/wx.h"

namespace colors {
  class hsv;
  class rgb;
  void rgb2hsv(unsigned char r, unsigned char g, unsigned char b, double &h, double &s, double &v);
  void hsv2rgb(double h, double s, double v, unsigned char &r, unsigned char &g, unsigned char &b);
  
  class rgb {
  public:
      unsigned char r;       // percent
      unsigned char g;       // percent
      unsigned char b;       // percent
  	rgb();
  	rgb(unsigned char, unsigned char, unsigned char);
  	rgb(int, int, int);
  	rgb(const hsv&);
      rgb& operator = (const hsv&);
      operator hsv();

    #ifdef _WX_COLOUR_H_
	  rgb(const wxColour&);
	  operator wxColour();
    #endif
   
  };
  class hsv {
  public:
      double h;       // angle in degrees
      double s;       // percent
      double v;       // percent
  	hsv();
  	hsv(double, double, double);
  	hsv(const rgb&);
      hsv& operator = (const rgb&);
      operator rgb();
  };
}