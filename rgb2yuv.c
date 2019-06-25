#include <stdio.h>
#include <getopt.h>

//Converter from RGB to YUV
//Ejemplo tomado de Internet
void pixel_rgb_to_yuyv (rgb_t * rgb_pixel, yuyv_t * yuyv_pixel)
{
	unsigned int pR, pG, pB;
		
	/* Transform (0-255) components to (0-100) */
	pR = rgb_pixel->r * 100 / 255;
	pG = rgb_pixel->g * 100 / 255;
	pB = rgb_pixel->b * 100 / 255;

	/* Calculate YUV values (0-255) from RGB beetween 0-100 */
	yuyv_pixel->y1 = yuyv_pixel->y2 = 209 * (pR + pG + pB) / 300 + 16;
	yuyv_pixel->Cb = pB - (pR / 4) - (pG * 3 / 4) + 128;
	yuyv_pixel->Cr = pR - (pG * 3 / 4) - (pB / 4) + 128;
	
	return;
}

//Convertidor
//Tomado de Internet intentando tropicalizar.
void rgb2yuv() {
	//Faltan inicio y variables
	for(int i = 0, j=0; i < 1280 * 720 * 3; i+=6, j+=4)
	{
		m_RGB->imageData[i] = pData[j] + pData[j+3]*((1 - 0.299)/0.615);
    	m_RGB->imageData[i+1] = pData[j] - pData[j+1]*((0.114*(1-0.114))/(0.436*0.587)) - pData[j+3]*((0.299*(1 - 0.299))/(0.615*0.587));
    	m_RGB->imageData[i+2] = pData[j] + pData[j+1]*((1 - 0.114)/0.436);
    	m_RGB->imageData[i+3] = pData[j+2] + pData[j+3]*((1 - 0.299)/0.615);
    	m_RGB->imageData[i+4] = pData[j+2] - pData[j+1]*((0.114*(1-0.114))/(0.436*0.587)) - pData[j+3]*((0.299*(1 - 0.299))/(0.615*0.587));
    	m_RGB->imageData[i+5] = pData[j+2] + pData[j+1]*((1 - 0.114)/0.436);
	}
	//Falta salida
}

//A implementar basado en ejemplo anterior, adaptando para YUV444.
void rgb2yuv444( w, h, R, B, G) {
	/* w is width in pixels of the image.
	   h is height in pixels of the image.
	   R is data for Red.
	   B is data for Blue
	   G is data for Green
	   */
	
	int Y, U, V;
	int i, j;
	int r, g, b;
	for (i=0, i < w * h * 3; i+=3)
	{
		//Pendiente revisar si los i son correctos para los colores (i.e. si para rojo es i, i+1 o i+2)
		r = i;
		g = i+1;
		b = i+2;
		Y[i] = 0.299 * R[r] + 0.587 * G[g] + 0.114 * B[b];
		U[i[ = -0.147 * R[r] - 0.289 * G[g] + 0.436 * B[b];
		V[i[ = 0.615 * R[r] - 0.515 * G[g] - 0.100 * B[b];
		}
	}
			
// Main formula with options.  Sientanse libres de agregar comentarios, sobre todo en la parte de help.
void main( int argc, char **argv) {
	int option_index = 0;
	char *user_name = NULL;
	char in_file;
	char out_file;
	out_file = NULL;
	while (( option_index = getopt(argc, argv, ":io::ah")) != -1){
		switch (option_index) {
			case 'i':
				in_file = optarg;
				printf("RGB file name: %s\n", in_file);
				//Codigo del convertidor
				break;
			case 'o':
				out_file = optarg;
				printf("YUV file name: %s\n", out_file);
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
	
	//Main converter code
	if (argc-optind != 2) error("give input and output files");
	file_in  = argv[optind++];
	file_out = argv[optind++];
	
	rgb2yuv();
	
	
	return;
} // end main block
