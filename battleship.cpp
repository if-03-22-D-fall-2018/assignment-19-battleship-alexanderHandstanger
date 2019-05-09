/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

static FILE* myStream;
static FILE* opStream;
static CellContent myContent[FIELDSIZE][FIELDSIZE];
static CellContent opContent[FIELDSIZE][FIELDSIZE];
static CellContent guesses[FIELDSIZE][FIELDSIZE];

void load_game(){
  myStream = fopen("battleship.my", "r");
  opStream = fopen("battleship.op", "r");

  fread(&myContent, sizeof(myContent), 1, myStream);
  fread(&opContent, sizeof(opContent), 1, opStream);
  for (int i = 0; i < FIELDSIZE; i++) {
    for (int j = 0; j < FIELDSIZE; j++) {
      guesses[i][j] = Unknown;
    }
  }
}

CellContent get_shot(int row, int col){
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1){
    return OutOfRange;
  }
  return myContent[row][col];
}

void FillWaterAround(int row, int col);

bool shoot(int row, int col){
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1){
    return false;
  }
  if(opContent[row][col] == Boat){
    FillWaterAround(row, col);
    return true;
  }
  return false;
}

void FillWaterAround(int row, int col){
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if((row-i > 0 && row-i < FIELDSIZE) && (col-j > 0 && col-j < FIELDSIZE)){
          guesses[row-i][col-j] = Water;
      }
    }
  }
  guesses[row][col] = Boat;
}

CellContent get_my_guess(int row, int col){
  return guesses[row][col];
}
