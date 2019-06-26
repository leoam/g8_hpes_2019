#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <arm_neon.h>
using namespace std;

int rgb2yuv (file, out_file_name, *arr)
{
	uint16_t w = 640;
	uint16_t h = 480;
	uint32_t n = w * h * 3;
	uint8x3_t Y[], U[], V[];
	int i, j;
	int r, g, b;
	int RGB[], YUV[];
	RGB[] = file;
	
	for (i=0; i < n; i+=1)
	{
		//Pendiente revisar si los i son correctos para los colores (i.e. si para rojo es i, i+1 o i+2)
		r = 3*(i);
		g = 3*(i)+1;
		b = 3*(i)+2;
		Y[i] = 0.299 * RGB[r] + 0.587 * RGB[g] + 0.114 * RGB[b];
		U[i] = -0.147 * RGB[r] - 0.289 * RGB[g] + 0.436 * RGB[b];
		V[i] = 0.615 * RGB[r] - 0.515 * RGB[g] - 0.100 * RGB[b];
		YUV[3*i] = U[i];
		YUV[3*i+1] = Y[i];
		YUV[3*i+2] = V[i];
		
		
		}
	
	
		
	float F[]=fopen(out_file_name, "w");
	float fclose(out_file_name);
	//float fclose(F[]);
}

void RGB2YUV444_neon<Strategies::NEON_INTRINSICS>(unsigned char * __restrict__ yuv, unsigned char * __restrict__ rgb, const int pixel_num, const int rgbChannelNum)
        {
            const uint8x8_t u8_zero = vdup_n_u8(0);
            const uint16x8_t u16_rounding = vdupq_n_u16(128);
            const int16x8_t s16_rounding = vdupq_n_s16(128);
            const int8x16_t s8_rounding = vdupq_n_s8(128);

            int count = pixel_num / 16;

            int i;
            for (i = 0; i < count; ++i) {
                // Load rgb
                uint8x16x3_t pixel_rgb;
                //if (rgbChannelNum == 3) {
                    pixel_rgb = vld3q_u8(rgb);
                /*} else {
                    uint8x16x4_t pixel_argb = vld4q_u8(rgb);
                    pixel_rgb.val[0] = pixel_argb.val[0];
                    pixel_rgb.val[1] = pixel_argb.val[1];
                    pixel_rgb.val[2] = pixel_argb.val[2];
                }*/
                rgb += rgbChannelNum * 16;

                uint8x8_t high_r = vget_high_u8(pixel_rgb.val[2]);
                uint8x8_t low_r = vget_low_u8(pixel_rgb.val[2]);
                uint8x8_t high_g = vget_high_u8(pixel_rgb.val[1]);
                uint8x8_t low_g = vget_low_u8(pixel_rgb.val[1]);
                uint8x8_t high_b = vget_high_u8(pixel_rgb.val[0]);
                uint8x8_t low_b = vget_low_u8(pixel_rgb.val[0]);
                int16x8_t signed_high_r = vreinterpretq_s16_u16(vaddl_u8(high_r, u8_zero));
                int16x8_t signed_low_r = vreinterpretq_s16_u16(vaddl_u8(low_r, u8_zero));
                int16x8_t signed_high_g = vreinterpretq_s16_u16(vaddl_u8(high_g, u8_zero));
                int16x8_t signed_low_g = vreinterpretq_s16_u16(vaddl_u8(low_g, u8_zero));
                int16x8_t signed_high_b = vreinterpretq_s16_u16(vaddl_u8(high_b, u8_zero));
                int16x8_t signed_low_b = vreinterpretq_s16_u16(vaddl_u8(low_b, u8_zero));

                // NOTE:
                // declaration may not appear after executable statement in block
                uint16x8_t high_y;
                uint16x8_t low_y;
                uint8x8_t scalar = vdup_n_u8(76);
                int16x8_t high_u;
                int16x8_t low_u;
                int16x8_t signed_scalar = vdupq_n_s16(-43);
                int16x8_t high_v;
                int16x8_t low_v;
                uint8x16x3_t pixel_yuv;
                int8x16_t u;
                int8x16_t v;

                // 1. Multiply transform matrix (Y′: unsigned, U/V: signed)
                high_y = vmull_u8(high_r, scalar);
                low_y = vmull_u8(low_r, scalar);

                high_u = vmulq_s16(signed_high_r, signed_scalar);
                low_u = vmulq_s16(signed_low_r, signed_scalar);

                signed_scalar = vdupq_n_s16(127);
                high_v = vmulq_s16(signed_high_r, signed_scalar);
                low_v = vmulq_s16(signed_low_r, signed_scalar);

                scalar = vdup_n_u8(150);
                high_y = vmlal_u8(high_y, high_g, scalar);
                low_y = vmlal_u8(low_y, low_g, scalar);

                signed_scalar = vdupq_n_s16(-84);
                high_u = vmlaq_s16(high_u, signed_high_g, signed_scalar);
                low_u = vmlaq_s16(low_u, signed_low_g, signed_scalar);

                signed_scalar = vdupq_n_s16(-106);
                high_v = vmlaq_s16(high_v, signed_high_g, signed_scalar);
                low_v = vmlaq_s16(low_v, signed_low_g, signed_scalar);

                scalar = vdup_n_u8(29);
                high_y = vmlal_u8(high_y, high_b, scalar);
                low_y = vmlal_u8(low_y, low_b, scalar);

                signed_scalar = vdupq_n_s16(127);
                high_u = vmlaq_s16(high_u, signed_high_b, signed_scalar);
                low_u = vmlaq_s16(low_u, signed_low_b, signed_scalar);

                signed_scalar = vdupq_n_s16(-21);
                high_v = vmlaq_s16(high_v, signed_high_b, signed_scalar);
                low_v = vmlaq_s16(low_v, signed_low_b, signed_scalar);
                // 2. Scale down (">>8") to 8-bit values with rounding ("+128") (Y′: unsigned, U/V: signed)
                // 3. Add an offset to the values to eliminate any negative values (all results are 8-bit unsigned)

                high_y = vaddq_u16(high_y, u16_rounding);
                low_y = vaddq_u16(low_y, u16_rounding);

                high_u = vaddq_s16(high_u, s16_rounding);
                low_u = vaddq_s16(low_u, s16_rounding);

                high_v = vaddq_s16(high_v, s16_rounding);
                low_v = vaddq_s16(low_v, s16_rounding);

                pixel_yuv.val[0] = vcombine_u8(vqshrn_n_u16(low_y, 8), vqshrn_n_u16(high_y, 8));

                u = vcombine_s8(vqshrn_n_s16(low_u, 8), vqshrn_n_s16(high_u, 8));

                v = vcombine_s8(vqshrn_n_s16(low_v, 8), vqshrn_n_s16(high_v, 8));

                u = vaddq_s8(u, s8_rounding);
                pixel_yuv.val[1] = vreinterpretq_u8_s8(u);

                v = vaddq_s8(v, s8_rounding);
                pixel_yuv.val[2] = vreinterpretq_u8_s8(v);

                // Store
                vst3q_u8(yuv, pixel_yuv);

                yuv += 3 * 16;
            }

            // Handle leftovers
            for (i = count * 16; i < pixel_num; ++i) {
                uint8_t r = rgb[i * rgbChannelNum + 2];
                uint8_t g = rgb[i * rgbChannelNum + 1];
                uint8_t b = rgb[i * rgbChannelNum + 0];

                uint16_t y_tmp = 76 * r + 150 * g + 29 * b;
                int16_t u_tmp = -43 * r - 84 * g + 127 * b;
                int16_t v_tmp = 127 * r - 106 * g - 21 * b;

                y_tmp = (y_tmp + 128) >> 8;
                u_tmp = (u_tmp + 128) >> 8;
                v_tmp = (v_tmp + 128) >> 8;

                yuv[i * 3] = (uint8_t) y_tmp;
                yuv[i * 3 + 1] = (uint8_t) (u_tmp + 128);
                yuv[i * 3 + 2] = (uint8_t) (v_tmp + 128);
            }
        }

			
// Main formula with options.  Sientanse libres de agregar comentarios, sobre todo en la parte de help.
int main( int argc, char **argv) {
	clock_t begin = clock();  //Inicio contador de tiempo
	
	{
		size = file.tellg();
    	memblock = new char [size];
    	file.seekg (0, ios::beg);
    	file.read (memblock, size);
    	file.close();
	  	int option_index = 0;
		char *user_name = NULL;
		char *in_file_name;
		char *out_file_name;
		out_file_name = NULL;
		while (( option_index = getopt(argc, argv, "i:o:ah")) != -1){
			switch (option_index) {
					case 'i':
					in_file_name = optarg;
					printf("RGB file name: %s\n", in_file_name);
					//Codigo del convertidor
					break;
				case 'o':
					out_file_name = optarg;
					printf("YUV file name: %s\n", out_file_name);
					break;
				case 'a':
					printf("Authors of the program:\n\tLeonardo Araya\n\tGabriel Loria\n\tAlvaro Salazar\n");
					break;
				case 'h':
					printf("Use '-i RGBfile' where RGBfile is the name of the file in RGB format to convert [REQUIRED].\nUse '-o YUVfile' where YUVfile is the name of the output file in YUV format [REQUIRED].\nUse '-a' to display information of the author of the program.\nUse '-h' to display this help guide.\n");
					break;
				default:
					printf("Not recognized option. Please use '-h' for help.\n");
					return 1;
			} //end block for switch
		}  //end block for while
	
		streampos size;
  		char * memblock;

  		ifstream file ("image2.bgr", ios::in|ios::binary|ios::ate);
  		if (file.is_open())
		{
			size = file.tellg();
    		memblock = new char [size];
    		file.seekg (0, ios::beg);
    		file.read (memblock, size);
    		file.close();
			rgb2yuv(in_file, out_file_name, *arr);
    		delete[] memblock;
		}
		else cout << "Unable to open file" << endl;
	
	printf("End of conversion.\n");
	
	clock_t end = clock();	//Fin de contador de tiempo
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tiempo transcurrido:\t%fs\n", time_spent);
	return 0;
} // end main block
