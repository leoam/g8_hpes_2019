#include <stdio.h>
#include <getopt.h>

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
	
	return;
} // end main block