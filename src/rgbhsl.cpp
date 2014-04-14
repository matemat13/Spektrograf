#include "include\rgbhsv.h"
namespace colors {
rgb::rgb()
{
 r = 0;
 g = 0;
 b = 0;
}
rgb::rgb(unsigned char r_i, unsigned char g_i, unsigned char b_i)
{
 r = r_i;
 g = g_i;
 b = b_i;
}
rgb::rgb(int r_i, int g_i, int b_i)
{
 r = (unsigned char)r_i;
 g = (unsigned char)g_i;
 b = (unsigned char)b_i;
}

rgb::rgb(const hsv& inp)
{
	//takhle to jde taky...
	hsv2rgb(inp.h, inp.s, inp.v, r, g, b);
}

 
#ifdef _WX_COLOUR_H_
  rgb::rgb(const wxColour &c) {
	  r = c.Red();
	  g = c.Green();
	  b = c.Blue();
  }

#endif
rgb& rgb::operator= (const hsv& in)
{
 /*r = in.h * 0.5; //vypocet!!
 g = 0; //vypocet!!
 b = 250; //vypocet!!*/

 //rgb2hsv(r,g,b,out.h,out.s,out.v);
 hsv2rgb(in.h, in.s, in.v, r, g, b);
 return *this;
}

rgb::operator hsv()
{
 hsv out;
 rgb2hsv(r,g,b,out.h,out.s,out.v);
 return out;
}

#ifdef _WX_COLOUR_H_
  rgb::operator wxColour() {
	  return wxColour(r,g,b);
  }

#endif

hsv::hsv()
{
 h = 0;
 s = 0;
 v = 0;
}
hsv::hsv(double r_i, double g_i, double b_i)
{
 h = r_i;
 s = g_i;
 v = b_i;
}

hsv::hsv(const rgb& inp)
{
	//takhle to jde taky...
	rgb2hsv(inp.r, inp.g, inp.g, h, s, v);
}

hsv& hsv::operator= (const rgb& in)
{
 /*r = in.h * 0.5; //vypocet!!
 g = 0; //vypocet!!
 b = 250; //vypocet!!*/

 //rgb2hsv(r,g,b,out.h,out.s,out.v);
 rgb2hsv(in.r, in.g, in.b, h, s, v);
 return *this;
}

hsv::operator rgb()
{
 rgb out;
 hsv2rgb(h,s,v, out.r,out.g,out.b);
 return out;
}








	
void rgb2hsv(unsigned char r, unsigned char g, unsigned char b, double &h, double &s, double &v)
{
    //hsv out;
    double      min, max, delta;

    min = r < g ? r : g;
    min = min  < b ? min  : b;

    max = r > g ? r : g;
    max = max  > b ? max  : b;

    v = max/((float)255);                                // v
    delta = max - min;
    if( max > 0.0 ) {
        s = (delta / max);                  // s
    } 
	else {
        // r = g = b = 0                        // s = 0, v is undefined
        s = 0.0;
        h = -1;                            // its now undefined
        return;
    }
    if( r >= max )                           // > is bogus, just keeps compilor happy
        h = ( g - b ) / delta;        // between yellow & magenta
    else
    if( g >= max )
        h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
    else
        h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

    h *= 60.0;                              // degrees

    if( h < 0.0 )
        h += 360.0;

    return;
}




void hsv2rgb(double h, double s, double v, unsigned char &r, unsigned char &g, unsigned char &b)
{
    double      hh, p, q, t, ff;
    long        i;


    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        if(h==-1) {   // in.h == NAN
            r = (unsigned char)v*255;
            g = (unsigned char)v*255;
            b = (unsigned char)v*255;
            return;
        }
        // error - should never happen
        r = (unsigned char)0;
        g = (unsigned char)0;
        b = (unsigned char)0;
		//std::cout<<"Some friggin error!\n";
        return;
    }
    hh = h;
    if(hh >= 360.0) hh = (int)hh%360;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        r = (unsigned char)(v*255);
        g = (unsigned char)(t*255);
        b = (unsigned char)(p*255);
        break;
    case 1:
        r = (unsigned char)(q*255);
        g = (unsigned char)(v*255);
        b = (unsigned char)(p*255);
        break;
    case 2:
        r = (unsigned char)(p*255);
        g = (unsigned char)(v*255);
        b = (unsigned char)(t*255);
        break;

    case 3:
        r = (unsigned char)(p*255);
        g = (unsigned char)(q*255);
        b = (unsigned char)(v*255);
        break;
    case 4:
        r = (unsigned char)(t*255);
        g = (unsigned char)(p*255);
        b = (unsigned char)(v*255);
        break;
    case 5:
    default:
        r = (unsigned char)(v*255);
        g = (unsigned char)(p*255);
        b = (unsigned char)(q*255);
        break;
    }
    return;     
}

}
