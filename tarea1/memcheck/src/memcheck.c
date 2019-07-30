#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc -shared -fPIC -o inject.so inject.c
// gcc example.c -o example
// make clean all
// ./memcheck -p file

static void init(int argc, char **argv, char **envp) {
    printf("\nAT THE BEGINNING OF THE PROGRAM\n");
}

static void fini(void) {
    printf("\nAT THE END OF THE PROGRAM\n");
}

__attribute__((section(".init_array"), used)) static typeof(init) *init_p = init;
__attribute__((section(".fini_array"), used)) static typeof(fini) *fini_p = fini;

int menu( int argc, char **argv, char **in_file){
	int option_index = 0;
  char buf[32];
	while (( option_index = getopt(argc, argv, "p:ha")) != -1){
		switch (option_index) {
			case 'p':
				printf("Program START: %s\n", optarg);
        system("gcc -shared -fPIC -o inject.so inject.c");
        sprintf(buf, "gcc %s -o example", optarg);
        system(buf);
        system("LD_PRELOAD=$PWD/inject.so ./example");
				break;
			case 'a':
				printf("Authors of the program:\n\tLeonardo Araya\n\tGabriel Loria\n\tAlvaro Salazar\n");
				break;
			case 'h':
				printf("Use '-p file_location to indicate the location of the file to be "
				"checked [REQUIRED].\nUse '-a' to display "
				"information of the authors of the program.\nUse '-h' to display this "
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

// Main code starts here
int main(int argc, char **argv){
	int status = 0;
  char *memcheck_file_name;
	status = menu(argc,argv, &memcheck_file_name);
	if (status) {
		fprintf(stderr, "status :%d\n", status);
		return status;
	}
	// Start the convertion
	// rgb2yuv(RGB_file_name, YUV_file_name);


  return 0;
}
