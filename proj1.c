#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file_utilities.h"

int **board = NULL;//Couldn't get a triple pointer working :(
int sizeX;//Bunch of globals, sorry
int sizeY;
char *fileName = "test.txt";
int main(int argc, char *argv[]){
  if(argc>2){
    sizeX = atoi(argv[1]);
    sizeY = atoi(argv[2]);
  }
  else{
    printf("Not enough arguments! Shutting down...\n");
    exit(1);
  }
  makeBoard();
  if(sizeX>7 && sizeY>7){
    board[5][5] = 1;
    board[5][6] = 1;
    board[5][7] = 1;
    board[6][6] = 1;
    board[0][0] = 1;
    board[1][0] = 1;
    board[1][1] = 1;
    board[2][0] = 1;
  }
  printBoard();
  //Input code from https://stackoverflow.com/questions/22065675/get-text-from-user-input-using-c
  char input[20];
  input[0] = '0';
  while(1){
    printf("What now?\n");
    printf("1.) Step\n");
    printf("2.) Save FILENAME\n");
    printf("3.) Load FILENAME\n");
    printf("4.) Quit\n");
    fgets(input,20,stdin);
    switch(input[0]){
      case '1':
	stepBoard();
	printBoard();
	break;
      case '2':
	saveBoard();
	break;
      case '3':
	loadBoard();
	break;
      case '4':
	printf("Shutting Down...\n");
	clearBoard();
	exit(1);
	break;
    }
  }
  return 0;
}

int makeBoard(){
  int row = sizeX;
  int col = sizeY;
  int i,j;
  board = (int **)malloc(row * sizeof(int*));
  for (i = 0;i < row; i++){
    board[i] = (int *)malloc(col * sizeof(int));
  }
  
  for (i = 0;i<row;i++){
    for(j = 0;j<col;j++){
      board[i][j] = 0;
    }
  }
  
  return 0;
}

int printBoard(){
  int i,j;
  char sym;
  printf("\n");
  for(i = 0;i<sizeX;i++){
    for(j = 0;j<sizeY;j++){
      switch(board[i][j]){
	case 0:
	  sym = '_';
	  break;
	case 1:
	  sym = 'O';
	  break;
      }
      printf("%c ",sym);
    }
    printf("\n");
  }
  return 0;
}

int stepBoard(){
  int marked[sizeX*sizeY];//marked for change
  int i,j;
  for(i = 0;i<sizeX*sizeY;i++){
    marked[i] = 0;
  }
  for(i = 0;i < sizeX;i++){
    for(j = 0;j < sizeY;j++){
      //Count Neighbors
      int neighbors = 0;
      int x,y;
      for(x = i-1;x<i+2;x++){
	for(y = j-1;y<j+2;y++){
	  //Check Bounds
	  if(x>=0 && x<sizeX && y>=0 && y<sizeY && (x!=i || y!=j)){
	    if(board[x][y] == 1){
	      neighbors = neighbors + 1;
	    }
	  }
	}
      }
      //If Living
      if(board[i][j] == 1 && (neighbors > 3 || neighbors < 2)){
	marked[sizeX*(j) + i] = 1;
      }
      //If dead
      if(board[i][j] == 0 && neighbors == 3){
	marked[sizeX*(j) + i] = 1;
      }
      
    }
  }
  //Change Marked
  for(i = 0;i<sizeX;i++){
    for(j = 0;j<sizeY;j++){
      if(marked[sizeX * (j) + i] == 1){
	if(board[i][j]==1){
	  board[i][j] = 0;
	}
	else{
	  board[i][j] = 1; 
	};//Flip
      }
    }
  }
  return 0;
}

int clearBoard(){
  int i;
  for(i = 0;i<sizeX;i++){
    free(board[i]);
  }
  free(board);
  return 0;
}

int newBoard(){
  int i,j;
  board = (int **)realloc(board,sizeX * sizeof(int*));
  for (i = 0;i<sizeX;i++){
    board[i] = (int *)realloc(board[i],sizeY * sizeof(int));
  }

  for (i = 0;i<sizeX;i++){
    for (j = 0;j<sizeY;j++){
      board[i][j] = 0;
    }
  }
  return 0;
}

int popBoard(char *mark){
  int i,j;
  for(i = 0;i<sizeX;i++){
    for(j = 0;j<sizeY;j++){
      if(mark[sizeX * (j) + i] == '1'){
	board[i][j] = 1;
      }
    }
  }
}

int loadBoard(){
  char *buffer;
  int size = read_file(fileName,&buffer);
  char *sX,*sY;
  int i,sizeSX,sizeSY;
  if(size<=1){
    printf("File Not Useable.\n");
    return -1;
  }
  //Parse Buffer
  //x
  sizeSX = 0;
  for(i = 0;i<size;i++){
    if(buffer[i]==':'){
      break;
    }
    sizeSX = sizeSX + 1;
  }
  sX = (char *)malloc(sizeSX * sizeof(char));
  for(i = 0;i<sizeSX;i++){
    sX[i] = buffer[i];
  }
  sizeX = atoi(sX);
  printf("SizeX: %i\n",sizeX);
  //y
  sizeSY = 0;
  for(i = sizeSX+1;i<size;i++){
    if(buffer[i]==':'){
      break;
    }
    sizeSY = sizeSY + 1;
  }
  sY = (char *)malloc(sizeSY * sizeof(char));
  for(i = 0;i<sizeSY;i++){
    sY[i] = buffer[sizeSX+1+i];
  }
  sizeY = atoi(sY);
  printf("sizeY: %i\n",sizeY);
  
  char *mark;
  mark = (char *)malloc(sizeX * sizeY * sizeof(char));
  for(i = 0;i<sizeX * sizeY;i++){
    mark[i] = buffer[sizeSX+sizeSY+2+i];
  }
  printf("\n");
  for(i = 0;i<sizeX*sizeY;i++){
    printf("%c",mark[i]);
  }
  makeBoard();
  popBoard(mark);
  printBoard();
  free(sY);
  free(sX);
  free(buffer);
  free(mark);
}

int saveBoard(){
  char *buffer;
  int i,j;
  int offset = 2;
  //https://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c
  //https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
  int sX = floor(log10(abs(sizeX))) + 1;
  int sY = floor(log10(abs(sizeY))) + 1;
  int size = sX+sY+offset+sizeX*sizeY;
  buffer =(char *)malloc(size * sizeof(char));
  for(i = 0;i<size;i++){
    buffer[i] = ' ';
  }
  char numX[5];
  char numY[5];
  sprintf(numX,"%d",sizeX);
  sprintf(numY,"%d",sizeY);
  for(i = 0;i<sX;i++){
    buffer[i] = numX[i];
  }
  buffer[sX]=':';
  for(i = 0;i<sY;i++){
    buffer[i+sX+1] = numY[i];
  }
  buffer[sX+sY+1] = ':';
  for(i = 0;i<sizeX;i++){
    for(j = 0;j<sizeY;j++){
      buffer[sX+sY+offset+(sizeX*(j) + i)] = board[i][j]+48;
    }
  }
  for(i = 0;i<size;i++){
    printf("%c",buffer[i]);
  }
  write_file(fileName,buffer,size);
  printBoard();
  return 0;
}
