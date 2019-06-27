#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arm_neon.h>

using namespace std;

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
	float32_t Y;
	float32_t U;
	float32_t V;
};

int menu( int argc, char **argv, char **in_file, char **out_file){
	int option_index = 0;
	*in_file = NULL;
	*out_file = NULL;
	while (( option_index = getopt(argc, argv, "i:o:ha")) != -1){
		switch (option_index) {
			case 'i':
				*in_file = optarg;
				printf("RGB file name: %s\n", optarg);
				break;
			case 'o':
				*out_file = optarg;
				printf("YUV file name: %s\n", optarg);
				break;
			case 'a':
				printf("Authors of the program:\n\tLeonardo Araya\n\tGabriel Loria\n\tAlvaro Salazar\n");
				break;
			case 'h':
				printf("Use '-i RGBfile' where RGBfile is the name of the file in RGB "
				"format to convert [REQUIRED].\nUse '-o YUVfile' where YUVfile is the "
				"name of the output file in YUV format [REQUIRED].\nUse '-a' to display "
				"information of the author of the program.\nUse '-h' to display this "
				"help guide.\n");
				return 1;
				break;
			default:
				printf("Not recognized option. Please use '-h' for help.\n");
				return 1;
		}
	}
	return 0;
}

// Function that converts a pixel from RGB to YUV format
int pixel_rgb2yuv(struct RGB rgb, struct YUV *yuv){
	float32_t const_1;
	float32_t const_2;
	float32x2_t tmp_1;
	float32x2_t tmp_2;
	float32x2_t tmp_3;
	float32x2_t tmp_4;

	// --------------------------------------------------------------------------
	// Generate the Y
	// yuv->Y = rgb.R * .299000 + rgb.G * .587000 + rgb.B * .114000;
	// --------------------------------------------------------------------------
	const_1 = 0.299000;
	const_2 = rgb.R;
	tmp_1 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	const_1 = 0.587000;
	const_2 = rgb.G;
	tmp_2 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	const_1 = 0.114000;
	const_2 = rgb.B;
	tmp_3 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	tmp_4 = vadd_f32(tmp_1, tmp_2);
	tmp_4 = vadd_f32(tmp_4, tmp_3);

	// Get the value from the vector
	vst1_f32(&(yuv->Y), tmp_4);

	// --------------------------------------------------------------------------
	// Generate the U
	// yuv->U = rgb.R * -.168736 + rgb.G * -.331264 + rgb.B * .500000 + 128;
	// --------------------------------------------------------------------------
	const_1 = -0.168736;
	const_2 = rgb.R;
	tmp_1 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	const_1 = -0.331264;
	const_2 = rgb.G;
	tmp_2 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	const_1 = 0.500000;
	const_2 = rgb.B;
	tmp_3 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));
	const_1 = 128;
	tmp_3 = vadd_f32(tmp_3, vld1_dup_f32(&const_1));

	tmp_4 = vadd_f32(tmp_1, tmp_2);
	tmp_4 = vadd_f32(tmp_4, tmp_3);

	// Get the value from the vector
	vst1_f32(&(yuv->U), tmp_4);

	// --------------------------------------------------------------------------
	// Generate the V
	// yuv->V = rgb.R * .500000 + rgb.G * -.418688 + rgb.B * -.081312 + 128;
	// --------------------------------------------------------------------------
	const_1 = 0.500000;
	const_2 = rgb.R;
	tmp_1 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	const_1 = -0.418688;
	const_2 = rgb.G;
	tmp_2 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));

	const_1 = -0.081312;
	const_2 = rgb.B;
	tmp_3 = vmul_f32(vld1_dup_f32(&const_2), vld1_dup_f32(&const_1));
	const_1 = 128;
	tmp_3 = vadd_f32(tmp_3, vld1_dup_f32(&const_1));

	tmp_4 = vadd_f32(tmp_1, tmp_2);
	tmp_4 = vadd_f32(tmp_4, tmp_3);

	// Get the value from the vector
	vst1_f32(&(yuv->V), tmp_4);

	return 0;
}

// Function that converts a pixel from RGB to YUV format
int rgb2yuv(char *input_img_name, char *output_img_name){
	ifstream input;
	ofstream output;
	char output_pixels[640*480*3];
	char input_read[3];
	char converted_output[3];
	struct RGB data;
	struct YUV value;
	int i = 0;
	int status = 0;

	input.open(input_img_name, ios::in | ios::binary);
	output.open(output_img_name, ios::out | ios::binary);

	input.read(input_read, sizeof(input_read));

	while (input.read(input_read, sizeof(input_read))) {
			// Convert the pixel from RGB to YUV
			data.R = input_read[0];
			data.G = input_read[1];
			data.B = input_read[2];
			status = pixel_rgb2yuv(data, &value);
			if (status) {
				fprintf(stderr, "status :%d\n", status);
				return status;
			}
			converted_output[0]= (char)value.Y;
			converted_output[1]= (char)value.U;
			converted_output[2]= (char)value.V;

			memcpy(&output_pixels[i], converted_output, sizeof(converted_output));
			i = i + 3;
	}

	input.close();
	output.close();

	return 0;
}

// Main code starts here
int main(int argc, char **argv){
	char *RGB_file_name;
	char *YUV_file_name;
	int status = 0;

	status = menu(argc,argv, &RGB_file_name, &YUV_file_name);
	if (status) {
		fprintf(stderr, "status :%d\n", status);
		return status;
	}

	// Start the time count
	clock_t begin = clock();

	// Start the convertion
	rgb2yuv(RGB_file_name, YUV_file_name);

	// Finish the time count
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Elapsed time: \t%fs\n", time_spent);

  return 0;
}
