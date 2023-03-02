#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utilidades.c" 

int main() {
 float vect[10]={49327.559, 53290.879, 54729.926, 55820.809, 50029.562, 49973.062, 58221.953, 51384.895, 54664.516, 55249.730};
 	verificarOrdenamiento(vect,10);
 	
 	float val = (float)1/3;
 	 printf("\n s--> %f",val);
 	val = redondear(val,4);
 	 printf("\n c --> %f",val);
 return 0;
 }
