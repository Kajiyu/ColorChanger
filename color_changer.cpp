#include "color_changer.h"

using namespace std;

//デフォルトコンストラクタ
Color_Changer::Color_Changer(){
	RGB *rgb_default;
	rgb_default = new RGB;
	rgb_default->r = 0;
	rgb_default->g = 0;
	rgb_default->b = 0;
	Color_Changer::setRGB(rgb_default);
}; //初期設定は黒

//オーバーロード
Color_Changer::Color_Changer(RGB *rgb_input){
	Color_Changer::setRGB(rgb_input);
};
Color_Changer::Color_Changer(CMYK *cmyk_input){
	Color_Changer::setCMYK(cmyk_input);
};
Color_Changer::Color_Changer(HSV *hsv_input){
	Color_Changer::setHSV(hsv_input);
};

RGB *Color_Changer::rgb;
CMYK *Color_Changer::cmyk;
HSV *Color_Changer::hsv;

void Color_Changer::setRGB(RGB *rgb_input){
	*rgb = *rgb_input;
	*cmyk = *Color_Changer::rgb_to_cmyk(rgb_input);
	*hsv = *Color_Changer::rgb_to_hsv(rgb_input);
};
	
void Color_Changer::setCMYK(CMYK *cmyk_input){
	*cmyk = *cmyk_input;
	*rgb = *Color_Changer::cmyk_to_rgb(cmyk_input);
	*hsv = *Color_Changer::cmyk_to_hsv(cmyk_input);
};

void Color_Changer::setHSV(HSV *hsv_input){
	*hsv = *hsv_input;
	*rgb = *Color_Changer::hsv_to_rgb(hsv_input);
	*cmyk = *Color_Changer::hsv_to_cmyk(hsv_input);
};


RGB *Color_Changer::hsv_to_rgb(HSV *hsv_input) {
	float f = (hsv_input->h)/60;
	float c = (hsv_input->v) * (hsv_input->s);
	float x;
	float m;

	RGB *rgb_neo;

	rgb_neo = new RGB;

	float r1, g1, b1;

	if ((int)f%2 == 0)
	{
		x = 0;
	} else {
		x = c*(1 - ((int)f%2-1));
	}
	m = (hsv_input->v) - c;

	switch ((int)f) {
		default:
		case 0:
			r1 = c;
			g1 = x;
			b1 = 0;
			break;
		case 1:
			r1 = x;
			g1 = c;
			b1 = 0;
			break;
		case 2:
			r1 = 0;
			g1 = c;
			b1 = x;
		  break;
		case 3:
		  r1 = 0;
		  g1 = x;
		  b1 = c;
		  break;
		case 4:
			r1 = x;
			g1 = 0;
			b1 = c;
			break;
		case 5:
			r1 = c;
			g1 = 0;
			b1 = x;
			break;
	}

	(rgb_neo->r) = (r1 + m) * 255;
	(rgb_neo->g) = (g1 + m) * 255;
	(rgb_neo->b) = (b1 + m) * 255;

	return rgb_neo;

}

RGB *Color_Changer::cmyk_to_rgb(CMYK *cmyk_input){
	RGB *rgb_neo;
	rgb_neo = new RGB;

  (rgb_neo->r) = (float)((1 - min((float)1, (cmyk_input->c) * (1 - (cmyk_input->k)) + (cmyk_input->k))) * 255);
  (rgb_neo->g) = (float)((1 - min((float)1, (cmyk_input->m) * (1 - (cmyk_input->k)) + (cmyk_input->k))) * 255);
  (rgb_neo->b) = (float)((1 - min((float)1, (cmyk_input->y) * (1 - (cmyk_input->k)) + (cmyk_input->k))) * 255);
    
  return rgb_neo;

};

CMYK *Color_Changer::rgb_to_cmyk(RGB *rgb_input){
	CMYK *cmyk_neo;
	cmyk_neo = new CMYK;
	float black;

	(cmyk_neo->k) = (float)(min(1 - (rgb_input->r) / 255, min(1 - (rgb_input->g) / 255, 1 - (rgb_input->b) / 255)));
	black = (cmyk_neo->k);

	(cmyk_neo->c) = (float)((1 - ((rgb_input->r) / 255) - black) / (1 - black));
	(cmyk_neo->m) = (float)((1 - ((rgb_input->g) / 255) - black) / (1 - black));
	(cmyk_neo->y) = (float)((1 - ((rgb_input->b) / 255) - black) / (1 - black));

	return cmyk_neo;
};

HSV *Color_Changer::rgb_to_hsv(RGB *rgb_input){

	HSV *hsv_neo;
	hsv_neo = new HSV;
	float *max = max((rgb_input->r), max((rgb_input->g),(rgb_input->b)));
  float *min = min((rgb_input->r), min((rgb_input->g), (rgb_input->b)));
        
  // h
  if(*max == *min){
    (hsv_neo->h) = 0;
  } else if(*max == (rgb_input->r)){
    (hsv_neo->h) = (float)((60 * ((rgb_input->g) - (rgb_input->b)) / (*max - *min) + 360) % 360);
  } else if(*max == (rgb_input->g)){
    (hsv_neo->h) = (60 * ((rgb_input->b) - (rgb_input->r)) / (*max - *min)) + 120;
  } else if(*max == (rgb_input->b)){
    (hsv_neo->h) = (60 * ((rgb_input->r) - (rgb_input->g)) / (*max - *min)) + 240;
  }
  
  // s
  if(*max == 0){
  	(hsv_neo->s) = 0;
  } else{
  	(hsv_neo->s) = (255 * ((*max - *min) / *max));
  }
        
  // v
  (hsv_neo->v) = *max;

	return hsv_neo;
};

CMYK *Color_Changer::hsv_to_cmyk(HSV *hsv_input){
	RGB *rgb_tmp;  //変換用rgb
	rgb_tmp = new RGB;

	CMYK *cmyk_neo;
	cmyk_neo = new CMYK;

	rgb_tmp = Color_Changer::hsv_to_rgb(hsv_input);
	cmyk_neo = Color_Changer::rgb_to_cmyk(rgb_tmp);

	return cmyk_neo;

};

HSV *Color_Changer::cmyk_to_hsv(CMYK *cmyk_input){
	RGB *rgb_tmp; //変換用rgb
	rgb_tmp = new RGB;

	HSV *hsv_neo;
	hsv_neo = new HSV;

	rgb_tmp = Color_Changer::cmyk_to_rgb(cmyk_input);
	hsv_neo = Color_Changer::rgb_to_hsv(rgb_tmp);

	return hsv_neo;
};

void showRGB(){
	cout << R: << Color_Changer::rgb->r << endl;
	cout << G: << Color_Changer::rgb->g << endl;
	cout << B: << Color_Changer::rgb->b << endl;
 };
void showCNYK(){
	cout << C: << Color_Changer::cmyk->c << endl;
	cout << M: << Color_Changer::cmyk->m << endl;
	cout << Y: << Color_Changer::cmyk->y << endl;
	cout << K: << Color_Changer::cmyk->k << endl;
};
void showHSV(
	cout << H: << Color_Changer::hsv->h << endl;
	cout << S: << Color_Changer::hsv->s << endl;
	cout << V: << Color_Changer::hsv->v << endl;
	);

int main(){
	return 0;
}