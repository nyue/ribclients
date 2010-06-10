#include "functions.h"
#include <stdio.h>

void SingleFloat(float f)
{
  printf("Single float with value %f\n",f);
}

void FloatVector(float fv[3])
{
  printf("Float vector with value [%f,%f,%f]\n",fv[0],fv[1],fv[2]);
}

void FloatMatrix(float fv[4][4])
{
  printf("Float matrix with value \n");
}
