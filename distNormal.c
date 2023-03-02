//=  Program to generate nomrally distributed random variables              =
//===========================================================================

#include <stdio.h>              // Needed for printf()
#include <stdlib.h>             // Needed for exit() and ato*()
#include <math.h>               // Needed for sqrt() and log()

//----- Defines -------------------------------------------------------------
#define PI         3.14159265   // The value of pi

//----- Function prototypes -------------------------------------------------
double norm(double mean, double std_dev);  // Returns a normal rv
double rand_val(int seed);                 // Jain's RNG

//===== Main program ========================================================

//Esta funcion la pruebo en enero 2021 - estaba comentada- volver a comentar si no se usa
double distNormal(int semilla, double mean,double std_dev,double limSup){

  double   norm_rv=0;             // The adjusted normal rv
  int      i;                     // Loop counter
  rand_val(semilla);              //Calculo con la semilla
  // Generate una normally distributed rv
  //norm_rv = norm(mean, std_dev);

    while (norm_rv<=0 || norm_rv>limSup){
    // Generate a normally distributed rv
    norm_rv = norm(mean, std_dev);

    // Output the norm_rv value
    //printf( " --- %f \n", norm_rv);
  }

  return norm_rv;
}

//===========================================================================
//=  Function to generate normally distributed random variable using the    =
//=  Box-Muller method                                                      =
//=    - Input: mean and standard deviation                                 =
//=    - Output: Returns with normally distributed random variable          =
//===========================================================================
double norm(double mean, double std_dev){
  double   u, r, theta;           // Variables for Box-Muller method
  double   x;                     // Normal(0, 1) rv
  double   norm_rv;               // The adjusted normal rv

  // Generate u
  u = 0.0;
  while (u == 0.0)
    u = rand_val(0);

  // Compute r
  r = sqrt(-2.0 * log(u));

  // Generate theta
  theta = 0.0;
  while (theta == 0.0)
    theta = 2.0 * PI * rand_val(0);

  // Generate x value
  x = r * cos(theta);

  // Adjust x value for specified mean and variance
  norm_rv = (x * std_dev) + mean;

  // Return the normally distributed RV value
  return(norm_rv);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - x_n = 7^5*x_(n-1)mod(2^31 - 1)                                    =
//=   - With x seeded to 1 the 10000th x value should be 1043618065       =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
double rand_val(int seed){
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Valor Aleatorio. Cambia en cada ejecuci�n. Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0){
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
 // printf("Aleat %d --> Result(0,1) %f - ",x,((double) x / m));
  return((double) x / m);
}

//usada solo en actualizar_perdida_mc
double distNormal_pert(int semilla, double inf,double masProb,double sup){
  double mean=(inf+4*masProb+sup)/6;
  double std_dev=(sup-inf)/6;
  double   norm_rv=0;             // The adjusted normal rv
  int      i;                     // Loop counter
  rand_val(semilla);              //Calculo con la semilla
  // Generate una normally distributed rv
  //norm_rv = norm(mean, std_dev);
  // while (norm_rv<=0 || norm_rv>limSup){
    while (norm_rv<=0){
    // Generate a normally distributed rv
    	norm_rv = norm(mean, std_dev);

    // Output the norm_rv value
    //    printf( " -distNormal_pert-- %f \n", norm_rv);
  	}
  return norm_rv;
}

double distPert_rcs(int semilla, double inf,double masProb,double sup){
  double mean=(inf+4*masProb+sup)/6;
  double std_dev=(sup-inf)/6;
  double   norm_rv=0;             // The adjusted normal rv
  int      i;                     // Loop counter
  rand_val(semilla);              //Calculo con la semilla
  // Generate una normally distributed rv
  //norm_rv = norm(mean, std_dev);
   while (norm_rv<inf || norm_rv>sup){
  //  while (norm_rv<=0){
    // Generate a normally distributed rv
    	norm_rv = norm(mean, std_dev);
     //   printf("En ciclo Pert valor %f, con inf %f y sup %f \n ",norm_rv,inf,sup);
    // Output the norm_rv value
       // printf( " --- %f \n", norm_rv);
  	}

  return norm_rv;
}

/*void main(void){
	double dist= distNormal(5, 0,20);
		printf( "%f \n", dist);
}*/
