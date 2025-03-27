#include <stdio.h>
#include "vector_utils.h"
 
#define WIDTH 512
#define HEIGHT 512
 
int main()
{
  int x_s = 382;
  int y_s = 255;
 
  vector_t pw;
 
  pw.x = 382;
  pw.y = 255;
  pw.z = 0;
 
  printf("(%d,%d) -> %s\n", x_s, y_s, vector_str(&pw));
     
  return 0;
}