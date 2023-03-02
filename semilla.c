#include <stdlib.h>

void verificarSemilla(long idum){
FILE *seed;
seed=fopen("semilla.inp","w");
char line[1024];
if (fgets(line, sizeof(line), seed) == NULL){
    fprintf(seed,"%ld\n", idum);
   // fprintf(stderr,"semilla nueva %ld\n", idum);
} 
fclose(seed);
}

void nuevasemilla(long idum){
FILE *seed;
while(idum==0) {idum=rand();}
seed=fopen("semilla.inp","w");
fprintf(seed,"%ld\n", idum);
//fprintf(stderr,"semilla nueva %ld\n", idum);
fclose(seed);
}


long  leesemilla(){
long semilla_leida;
FILE *seed;
seed=fopen("semilla.inp","r");
fscanf(seed,"%ld", &semilla_leida);
// nueva semilla es un entero-largo (long integer)
fclose(seed);
//printf("\n -leyendo semilla: %ld",semilla_leida);
return semilla_leida;
// nueva_semilla es la semilla de rand (supongo que estas usando rand para generar numeros al azar)
}

