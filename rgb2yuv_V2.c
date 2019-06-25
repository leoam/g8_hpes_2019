#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void rgb2yuv (in_file, out_file_name)
{
	int w = 640;
	int h = 480;
	int Y, U, V;
	int i, j;
	int r, g, b;
	
	//Falta separar los datos del in_file en vectores R, G y B para aplicar las formulas a los datos
	
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
	
	//Unir los datos de Y, U, V
			
	fopen(out_file_name, "w");
}

//void rgb2yuv444( w, h, R, B, G) {
	/* w is width in pixels of the image.
	   h is height in pixels of the image.
	   R is data for Red.
	   B is data for Blue
	   G is data for Green
	   */
	
/*	int Y, U, V;
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
	}*/
			
// Main formula with options.  Sientanse libres de agregar comentarios, sobre todo en la parte de help.
void main( int argc, char **argv) {
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
	
	//Main converter code
/*	if (argc-optind != 2) error("give input and output files");
	file_in  = argv[optind++];
	file_out = argv[optind++];
	*/
	
	FILE *in_file  = fopen(in_file_name, "r");
	if (in_file == NULL) 
            {   
              printf("Error! Could not open file\n"); 
              exit(-1);
            } 
	
	rgb2yuv(in_file, out_file_name);
	
	int fclose(in_file_name);
	printf("End of conversion.\n");
	return;
} // end main block
