#include <stdio.h>
#include <stdlib.h>

// RGB pixel struct
struct RGB
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

// YUV pixel struct
struct YUV
{
	double Y;
	double U;
	double V;
};

// Function that converts a pixel from RGB to YUV format
int pixel_rgb2yuv(struct RGB rgb, struct YUV *yuv){
	yuv->Y = rgb.R * .299000 + rgb.G * .587000 + rgb.B * .114000;
	yuv->U = rgb.R * -.168736 + rgb.G * -.331264 + rgb.B * .500000 + 128;
	yuv->V = rgb.R * .500000 + rgb.G * -.418688 + rgb.B * -.081312 + 128;

	return 0;
}

int main(){
  struct RGB data = { 82, 0, 87 };
  struct YUV value;

	// Convert the pixel from RGB to YUV
	pixel_rgb2yuv(data, &value);

	fprintf(stderr, "%ff\n", value.Y);
	fprintf(stderr, "%ff\n", value.U);
	fprintf(stderr, "%ff\n", value.V);
  return 0;
}
