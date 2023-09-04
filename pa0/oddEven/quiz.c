#include <stdio.h>
#include <float.h>

int main() {

  printf( 1/DBL_MIN < DBL_MAX ? "representable, " : "overflow, ");
  printf( DBL_MIN < 1/DBL_MAX ? "normalized\n" : "denormalized\n");

}