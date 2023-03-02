/* Programa para la simulacion de un tambo lechero
Melina Richardet, A Larriestra y otros
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#define MaxVacas 500 /* si hay mas cambiarlo, si hay menos no importa */
#define MaxVacasEstad 2000 /* si hay mas cambiarlo, si hay menos no importa */
#define MAX_PROBA 13

//definicion de corridas
#define Ejec_sinsecado 1
#define Ejec_consecado_rp 2
#define Ejec_consecado_sinrp 3
// lista de probabilidades
#define P_descarte 0.0045 // no se est� usando?
#define P_noPrenez 0.88       //P_prenez 0.12 quincenal nov 17(16% cada 21d)-antes en 0.14, o sea, 0.86
#define P_noPrenez_mc 0.07    //P_prenez_mc 0.08
#define P_noPrenez_msc 0.02   //P_prenez_msc 0.16 //prob tasa prenez disminuye 44% - Pinedo 2009//OR 1,22
#define P_noAbortar 0.99       // cambiamos esto en programaTambo.c nov_2017- chequear
#define P_noAbortar1 0.99  //para abortos mes prenez (1) 2 y 3 - para Tambo4_21_09_05.c
#define P_noAbortar2 1//0.75//0.95    //nuevo:para mes prenez 4 al 8- para Tambo4_21_09_05.c////antes: 0.99//ojo ver Utilidades: agregue funcion!! sep 2021 ProbNoAbortar2
#define P_noAbortar_mc 0.99
#define P_noAbortar_msc 0.99   // ver tasa aborto OR 1,22-no estamos usando esto

#define P_secado_m5 0 //cambio sept 2021 a 0 ; antes era 0.03
#define P_secado_m6 0//cambio sept 2021 a 0 ; antes era 0.05
#define P_secado_m7 1//cambio sept 2021 a 0 ; antes era 0.9

#define MesesDeEspera 20  //Es la cantidad de meses que se espera hasta que quede pre�ada (quicena)
#define MAX_QUINCENA 192//144//720//240//2//144//600//2//144//360//600//360//600//360//144// 360//144//360//144//96//72  //los datos del tambo iniciales son los del primer mes
#define MaximoNop 5
#define CantidadPatogeno 6
#define MAX_EJECUCION 500//100//500//300//50//100//10 //cambiar ////numero iteraciones

// lista de patogenos 0 es sin patogeno
#define SAureus 1
#define SAgalactiae 2
#define SCN 3
#define OtrosStrepto 4
#define EColi 5
#define Otros 6

//constantes - valores
#define vaquillona 1
#define pv_prenada 1
#define pv_vacia 2
#define sl_lactancia 1
#define sl_seca 2
#define salud_inic 0
#define salud_sana 1
#define salud_mc 2
#define salud_msc 3
#define descarte_rodeo 1
#define descarte_infertilidad 2
#define descarte_muerta 3
#define descarte_aborto 4
#define descarte_vejez 5
#define descarte_mc 6
//descarte_msc es para vacas que superen rcs-max
#define descarte_msc 7
#define rcs_max 200//2022: descarto vacas con 200//400//800//veeeeeer estaba en 400!!!!! ojo 400//800//400// 800// ori //para descarte a partir de determinado umbral

#define costo_litro 1
#define cte_B 0.50//0.75//0.25//0.50//0.25//0.50//estaba en defecto= 0.50//0.49//0.75//0.25//0.49 ori//0.50
#define minAnioEstLactancia 2
#define limiteRecuentos 400//800 // para elegir si tienen mas chances de enfermar las de mayor rcs en formula hernan

//Definicion precios
#define PrecioVaq 1300//PA:1521//PB:1079//default: 1300//1170//1430//1300//1500//1300 ori//1235  //para Formula culling VC
#define PrecioVaca 600//PA:702//PB:498//default: 600//setp2021=600//400//600//23 sept pruebo 600//400=ori//no 130//para Formula culling VC
#define PrecioLitroLeche 0.308//LA:0.357//LB:0.263//default= 0.308//0.28//0.19//0.28//0.37//0.28//0.325//0.25 //tachan junio 2019 //0.325 //ori
#define PrecioIA 92//122 //sept= cambio IDO a 4,60 * 20=92//antes: 6,11 (us$ ido) x 20 dias= 122,2 :usando formula cattaneo 2015 con 20 dias pasados los 120 del , incluyendo costos de su tabla//78// ojo es 7.8!!!!!!mayo 2019 detecto
#define Precio_MOB_tambero_hora 3.5
#define Precio_litro_desinfectante 2.5//5//2.5//ori ////// 6.6 //(10+)    //5.4 //(10-)
#define Precio_pomo_secado 1.5
#define Precio_chequeo_MO 93.75
#define Precio_pomo_MC 6//2$x3 pomos- prueba - 2//ori /////// 6.6 //(10+)    //5.4 //(10-)
#define NroOrdenios_dia 2
#define NroPezones_vaca 4
#define Dias_anio 365
#define Horas_tambero_PMTD_VO 0.0072// cambio sept 2021- yalcin 1999 preparacion ubre=15 seg y PMTD 11=26 seg % 60 seg y % 60 minutos= 0.0072 horas---  antes: 0.004
#define Horas_tambero_pomos_VS 0.0832
#define Horas_tambero_pomo_MC 0.0208
#define Litros_desinfectante_VO 0.0064
#define NroChequeoMO_anio 3

#define Factor_segregacion  3.07//PA:3.59//PB:2.55//default: 3.07//614 % 200 vacas= 3.07//2.763//3.377//3.07//x VO : huijs: costo FIJO. $200/65 VO: 3.07////146.5//de huijps, modificado para 200 V0 o Segregadas? //146.5 //es el costo de segreg x VO estimativo   //7.857 //relacionado a diferencia entre vaq y vaca �?
#define costo_seg_VI 109.5//PA:128.12//PB:90.89//default:109.5//98.55//120.45//109.5//sacado de huijs: para 20 casos MC (pag 78 tesis) gasta $2.190/a�o: o sea, 109.5/vaca segregada/ anio  /////365//73 //0.2 //us$/d (ADSA Victor Cabrera) *365 dias para Vaca infectada segregada!
#define Coef_Seg 0.30//0.20//0.30// 0.10//0.20//mayo 2022//marzo 2022: lo seteo en 0 porque anulo este coef y pruebo el efecto se segregar vacas con MC, poniendo PesoMC=0; si quiero afectar la segregacion de vacas con MSC de altos recuentos, definir el umbral de RCS en "limite Recuentos" y afectar el factor_ra)// 0.18//en el 2021:HICE UN CAMBIO. ESTE "COEF_SEG" DEBE SER IGUAL AL "COEF_SEGREG" SETEADO EN EL ESCENARIO 6 Y/U 8 (LOS QUE TIENEN SEGREGACION) PARA QUE PUEDA HACER EL CALCULO DE COSTOS EN ESTADISTICAS.C!!!! 2 FEBE 2021 MELI ////es proporcion de las infectadas que son segregadas
//el Coef_Segreg lo incorpore dentro de cada escenario - meli 2 feb 2021

#define CostoTerneroMacho 50//para Formula culling VC
#define PorcMacho 0.53//para Formula culling VC
#define CostoTerneroHembra 250//para Formula culling VC
#define PorcHembra 0.47//Complemento de PorcMacho   //para Formula culling VC
#define tazaDescarteRodeo 0.30  //para Formula culling VC
//tasaDescarteRodeo en porcentaje
#define IntervaloParto_Meses 14   //para Formula culling VC
#define tazaInteres 0.005 //porcentaje/mes  //para Formula culling VC
#define expectativaVida_Meses 111   //para Formula culling VC


typedef struct Vaca{ /* Datos de la vaca */
        unsigned int orden;
        unsigned int id;
        unsigned int partos; /* de 1 a 8 */
        unsigned int pv; /*categoria 1= prenada; 2= vacia*/
        int prenez; /* -2 a 9 segun el mes */
        unsigned int sl; /*categoria 1= en lactancia; 2= seca*/
        unsigned int del; /*D�a en lactancia */
		int qel; /* Mes de lactancia */
		float producdiaria;
		float produc; /* litros por mes */
		unsigned int merito; /* nivel de produccion */
		unsigned int sir; /* usado para calculo mc */
		unsigned int salud; /* 1=sana o 2 =mastitis clinica y 3=mastitis subclinica */
        unsigned int descarte; /* 1=en rodeo; 2=descarte 3=muerta*/
        unsigned int rcs; /*recuento celulas somaticas x 1000 */
		unsigned int nroCuartMCLactPrevia;
        unsigned int nroCuartMCLactActual;
        unsigned int patogeno;
        unsigned int saludAntSecado; /* 0=sin estado 1=sana o 2 =mastitis clinica y 3=mastitis subclinica */
		int meses; /* contador de tiempos */
        unsigned int mesEnf;
        unsigned int cantMC;  //se utiliza para los conteos de MC para el calculo de perdidas
        float resultPerdidaMC; /*salida en archivo de estimacion*/
        float resultPerdidaMSC; /*salida en archivo de estimacion*/
        unsigned int saludPat_SAureus;
        unsigned int saludPat_SAgalactiae;
        unsigned int saludPat_SCN;
        unsigned int saludPat_OtrosStrepto;
        unsigned int saludPat_EColi;
        unsigned int saludPat_Otros;
        unsigned int cantTotalMC;  //Usado para descarte
        unsigned int cantTotalMSC; //Usado para descarte
        unsigned int infGral; /* primer inf */
        unsigned int infMC;   /* primer inf MC */
        unsigned int infMSC;  /* primer inf MSC */
        } vaca;

typedef struct Calculo_p_p{
        int id;
        int prenez[MAX_QUINCENA+1];  //para que quede en 24
        int mes;
} calculo_pp;

/************ Calculos Estimacion ************/
void estimacion();
vaca actualizar_salud_EColi(vaca A);
vaca actualizar_salud_aureus(vaca A,float probInf,int semilla,int cod);
vaca actualizar_patogeno (vaca A);
vaca actualizar_preniez_vaca(vaca A);
vaca actualizar_lactancia (vaca A);
vaca actualizar_categoria_preniez (vaca A);
vaca actualizar_categoria_sl (vaca A);
vaca actualizar_descarte (vaca A);
vaca actualizar_prod_dia_mes (vaca A,char nombreArch[30]);
vaca actualizar_salud_EColi_Houben (vaca A);//houben
vaca actualizar_salud_rcs (vaca A,int semilla,int saludAnt,int rcsAnt);
vaca actualizar_perdida_mc (vaca A,int semilla);
vaca generarNuevaVaca();
void agregarAnimal();

/************ Calculos Wood ************/
float wood (float b0, float b1, float b2, int del);
void cargarParametros(int nop, int merito, float *b0, float *b1, float *b2,char nombreArch[30]);

/************ Calculos Houben ************/
void iniciarParamHouben(float *pexpos,float *drni,float *lt,float *propsub,float *spon);
int houben (float b0, float b1, float b2,float b3, float b4, float b5,float b6, int salud);
void cargarParametrosDeHouben(int lactancia, int nop, int merito, int nCuartInfPrevio, int nCuartInfActual, int salud, float *b0, float *b1, float *b2, float *b3, float *b4, float *b5, float *b6);
