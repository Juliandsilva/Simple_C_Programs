#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Of the many techniques for compressing the contents of a file,
one of the simplest and fastest is known as run-length encoding.
This technique compresses a file by replacing sequences of
identical bytes by a pair of bytes:
a repetition count followed by a byte to be repeated.
For example, suppose that the file to be compressed
begins with the following sequence of bytes (shown in hexadecimal):

46 6F 6F 20 62 61 72 21 21 21 20 20 20 20 20

The compressed file will contain the following bytes:

01 46 02 6F 01 20 01 62 01 61 01 72 03 21 05 20

Note that compress_file	will write the compressed version
of 'original-file', given as a command line argument, 
to 'original-file.rle'.	
*/


int main(int argc, char ** argv) {

  if (argc != 2) { //check if user passed in an argument
    fprintf(stderr, "two commandline arguments needed");
    exit(1);
  }

  FILE * fl = fopen(argv[1], "rb");

  if (fl == NULL) {
    perror("fopen");
    exit(1);
  }

  char s1[strlen(argv[1]) + 5]; //create the name of the compressed file 
  strcpy(s1, argv[1]);
  strncat(s1, ".rle", sizeof(s1) - strlen(s1) - 1);

  FILE * writing = fopen(s1, "wb");

  if (writing == NULL) {
    return 1;
  }

  unsigned char c;
  unsigned char counter = 0;
  unsigned char compare;
  int empty_file_flag = 0;

  while (fread( & c, sizeof(unsigned char), 1, fl) == 1) { // This loop implements the run-Length
                                                           // encoding algorithm
    if (counter > 0) {

      if (c != compare) {
        fwrite( & counter, sizeof(unsigned char), 1, writing);
        fwrite( & compare, sizeof(unsigned char), 1, writing);
        counter = 0;
      }
    }

    empty_file_flag++;
    compare = c;
    counter++;

  }

  if (empty_file_flag == 0) { // check if user entered file was empty

    if (fclose(fl) != 0) {
      exit(1);
    }

    if (fclose(writing) != 0) {
      exit(1);
    }
    return 0;
  }

  fwrite( & counter, sizeof(unsigned char), 1, writing);
  fwrite( & compare, sizeof(unsigned char), 1, writing);

  if (fclose(fl) != 0) {
    exit(1);
  }

  if (fclose(writing) != 0) {
    exit(1);
  }

  return 0;
}
