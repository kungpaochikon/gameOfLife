#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*
int main(int argc, char** argv){
  char *buffer;
  int size = read_file("test.txt",&buffer);
  int i;
  for(i = 0;i<size;i++){
    printf("-)%c\n",buffer[i]);
  }
  return 0;
}
*/
//File Size Reading code gotten from: https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
//Extra guidance provided by classmate: Sean Aubrey
int read_file( char* filename, char **buffer ){
  FILE *in;
  in = fopen(filename, "r");
  if(in == NULL){
    printf("File not found, shutting down...");
    exit(1);
  }
  fseek(in,0L,SEEK_END);
  int size = ftell(in);
  rewind(in);
  *buffer = (char*) malloc(size*sizeof(char));
  fseek(in,0L,SEEK_SET);
  fread(*buffer,sizeof(char),size,in);
  fclose(in);
  return size;
}


int write_file( char* filename, char *buffer, int size){
  FILE *out;
  out = fopen(filename, "w");
  if(out == NULL){
    printf("File not working, shutting down...");
    exit(1);
  }
  fclose(out);
  return 0;
}



