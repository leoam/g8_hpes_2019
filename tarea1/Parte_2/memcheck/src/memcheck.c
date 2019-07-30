#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc -shared -fPIC -o inject.so inject.c
// gcc example.c -o example
// make clean all
// ./memcheck -p file

int menu( int argc, char **argv, char **in_file){
	int option_index = 0;
  char buf[32];

	while (( option_index = getopt(argc, argv, "p:ha")) != -1){
		switch (option_index) {
			case 'p':
				fprintf(stderr,"Program START: %s\n", optarg);
        system("gcc -shared -fPIC -o inject.so inject.c -ldl");
        sprintf(buf, "LD_PRELOAD=$PWD/inject.so %s", optarg);
        system(buf);
				break;
			case 'a':
				fprintf(stderr,"Authors of the program:\n\tLeonardo Araya\n\tGabriel Loria\n\tAlvaro Salazar\n");
				break;
			case 'h':
				fprintf(stderr,"Use '-p file_location to indicate the location of the file to be "
				"checked [REQUIRED].\nUse '-a' to display "
				"information of the authors of the program.\nUse '-h' to display this "
				"help guide.\n");
				return 1;
				break;
			default:
				fprintf(stderr,"Not recognized option. Please use '-h' for help.\n");
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
  return 0;
}
