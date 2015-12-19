#ifndef _COLORCHANGER_H_
#define _COLORCHANGER_H_

#include <iostream>
#include <cmath>
#include <algorithm>

typedef struct {
	float r;
	float g;
	float b;
} RGB;

typedef struct  {
	float c;
	float m;
	float y;
	float k;
} CMYK;

typedef struct {
	float h;
	float s;
	float v;
} HSV;

class Color_Changer 
{
public:
	//デフォルトコンストラクタ
	Color_Changer();
	///オーバーロード
	Color_Changer(RGB *rgb_input);
	Color_Changer(CMYK *cmyk_input);
	Color_Changer(HSV *hsv_input);

	//デコンストラクタ
	~Color_Changer();

	static RGB *rgb;
	static CMYK *cmyk;
	static HSV *hsv;

	void setRGB(RGB *rgb_input);
	void setCMYK(CMYK *cmyk_input);
	void setHSV(HSV *hsv_input);

	void showRGB();
	void showCNYK();
	void showHSV();

private:
	RGB *hsv_to_rgb(HSV *hsv_input);
	RGB *cmyk_to_rgb(CMYK *cmyk_input);

	CMYK *rgb_to_cmyk(RGB *rgb_input);
	CMYK *hsv_to_cmyk(HSV *hsv_to_input);

	HSV *rgb_to_hsv(RGB *rgb_input);
	HSV *cmyk_to_hsv(CMYK *cmyk_input);

	float rgb_max(RGB *rgb_input);
	float rgb_min(RGB *rgb_input);
};

#endif 