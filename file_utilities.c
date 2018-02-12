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
//Extra guidance(fread) provided by classmate: Sean Aubrey

/*
 *  read_file
 *  ---------
 *  Read File 
 */
int read_file( char* fileName, char **buffer ){
  FILE *in;
  in = fopen(fileName, "r");
  if(in == NULL){
    printf("File not found, shutting down...");
    exit(1);
  }
  fseek(in,0L,SEEK_END);
  int size = (int)ftell(in);
  *buffer = (char*) malloc(size*sizeof(char));
  fseek(in,0L,SEEK_SET);
  fread(*buffer,sizeof(char),size,in);
  fclose(in);
  return size;
}

//  write_file
//  ----------
//  Write file
int write_file( char *fileName, char *buffer, int size){
  FILE *out;
  out = fopen(fileName, "w");
  if(out == NULL){
    printf("File not working, shutting down...");
    exit(1);
  }
  fwrite(buffer,sizeof(char),size,out);
  fclose(out);
  return 0;
}



