#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

int rgb2yuv (file, out_file_name, *arr)
{
	int w = 640;
	int h = 480;
	int n = w * h * 3;
	float Y[], U[], V[];
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
