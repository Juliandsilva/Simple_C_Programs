#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv) {

	if (argc != 2){
		return 1;
	}

	FILE *fl = fopen(argv[1], "rb");

	if(fl == NULL){
		return 1;
	}

	char *valid = strstr(argv[1],".rle");

	if (valid == NULL){
		fclose(fl);
		fprintf(stderr,"Invalid file extension\n");
        	return 1;	
        }
        
	char other_file[strlen(argv[1]) - 3];
        strncpy(other_file,argv[1],strlen(argv[1]) - 4);
        other_file[strlen(argv[1]) - 4] = '\0';

	FILE *writing = fopen(other_file,"wb");

	if (writing == NULL){
		return 1;
	}

        unsigned char c;
        unsigned char counter = 0;
        int value;

	while (fread(&c,sizeof(unsigned char),1,fl) == 1){
               
                counter ++;
                if (counter == 2){
                        int counting;
                        for(counting = 0; counting < value; counting++){
                                fwrite(&c,sizeof(unsigned char),1,writing);
                        }
                        counter =0;
                        }

                value = c;
	}

	if(fclose(fl) != 0){
		return 1;
	}

	if(fclose(writing) != 0){
		return 1;
	}

	return 0;
	}

