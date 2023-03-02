/* parte principal del programa del tambo */
#include <sys/types.h>
#include <dirent.h>
#include "tambo.h"
#include "utilidades.c"
#include "estadisticas.c"
#include "semilla.c"
#include "distNormal.c"

// Escenario por defecto
float eficacia=0;
int DiasRetiro=0; //Dias de descarte de leche por mc
float Coef_Segreg=0;
float pesoMC=1;
float pesoMSC=1;

float probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //verificar tasa y prob. meli
float mcSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
float mcSecado_mc=0.01;
float mscSecado_sana=0.3; // ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
float mscSecado_mc=0.09;
float factor_rb =1;
float factor_ra =1;
float probInfSecado =0.02;

int opcionTipoEst=0;
int opcionAnioCorte=3;
int opcionTipoEstSeg=2;
int cant_total_mc=400;
int cant_total_msc=1200;
int opcionDescarte1=0;
int opcionDescarte1MC=0;
int opcionDescarte1MSC=0;
int opcionDescarte2=0;
int opcionDescarte2MC=0;
int opcionDescarte2MSC=0;

void setearValoresDescarte(int opcionTipoEst,int cantMC,int cantMSC){
	if(opcionTipoEst==0){  //sin
		cant_total_mc=400;
		cant_total_msc=1200;
	}
	if(opcionTipoEst==1){  //con
		cant_total_mc=4;
		cant_total_msc=12;
	}
	if(opcionTipoEst==2){  //con
		cant_total_mc=cantMC;
		cant_total_msc=cantMSC;
	}
}

void setearValoresTipoEstimacion(int opcionTipoEst){
	if(opcionTipoEst==0){  //DEFECTO
		eficacia=0;
		DiasRetiro=0; //Dias de descarte de leche por mc
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.30;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.30;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.02;
	}
	if(opcionTipoEst==1){  //PMTD
		eficacia=0.363;
		DiasRetiro=0; //Dias de descarte de leche por mc
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.30; // ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.30; // ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.02;
	}
	if(opcionTipoEst==2){ //DCT
		eficacia==0.2;
		DiasRetiro=0; //Dias de descarte de leche por mc
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.007;
	}
	if(opcionTipoEst==3){//CMO
		eficacia=0.084;
		DiasRetiro=0; //Dias de descarte de leche por mc
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.02;
	}
	if(opcionTipoEst==4){//TMC
		eficacia=0.093;
		DiasRetiro=6;//3; //ori//0; //Dias de descarte de leche por mc
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.35; //SIN POMO 0.03 //verificar tasa y prob. meli
		mcSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.02;
	}
	if(opcionTipoEst==5){//4medidas
		eficacia=0.55;//0.605;//0.495;//0.55;//0.57;//0.60;//0.50;//0.765;//0.50;//0.765;//0.74;//0.765;//0.54;//saco 0.20 de DCT//0.74;//0.31;//0.50;//0.27;//0.25;//0.44;//0.615;//0.50; //0.74;//orig
		DiasRetiro=6; //3;//ori//Dias de descarte de leche por mc
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.35;//0.50;//0.14;//0.35; //default:0.35; AS: lim inf=0.14;lim sup=0.50;//SIN POMO 0.03 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.007;
	}
	/*if(opcionTipoEst==99){//Segregacion mc y msc SOLA
		eficacia=0;
		DiasRetiro=3; //0; segregacion asume retiro???//Dias de descarte de leche por mc//
		Coef_Segreg=0;
		pesoMC=0;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;//0.6;
		factor_ra =0.815; //0.56;//0.9; //0.815 da una eficacia aprox de 19.9% segregando rcs>800
		probInfSecado =0.02;
	}*/
	if(opcionTipoEst==6){//Segregacion // ojo MSC SOLA
		eficacia=0;//0.19;//0;
		DiasRetiro=0; //Dias de descarte de leche por mc
		Coef_Segreg=0.18;//aca seteo la proporcion de vacas infectadas que quiero segregar
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;//0.65;//0.815;//1;
		probInfSecado =0.02;

	}
	if(opcionTipoEst==7){//DESCARTE SOLO //ELEGIR ESTE ESCENARIO CUANDO HAGO DESCARTE PARA QUE ME HAGA CALCULOS ECONOMICOS
		eficacia=0;
		DiasRetiro=0; //0; segregacion asume retiro???//Dias de descarte de leche por mc//
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.30;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.30;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;//0.6;
		factor_ra =1; //0.56;//0.9; //0.815 da una eficacia aprox de 19.9% segregando rcs>800
		probInfSecado =0.02;

	}
	if(opcionTipoEst==8){//4medidas + segre //orde�o mc y msc final?? ver tasas
		eficacia=0.55;//0.605;//0.495;//0.55;//0.57;//0.50;//0.765;//0.54; //sept 2021-antes era 0.74 pero saco efecto de DCT en lactanca=0.20//0.74;//0.42;//ori= 0.74;//ori//0.40;//0.74;//0.38;//0.90;//0.74 + 0.19 de seg; //deberia ser 0.93 ////
		DiasRetiro=6;//3; ori////Dias de descarte de leche por mc
		Coef_Segreg=0.30;//0.20;//marzo 2022 //0.18; //ACA ASIGNO LA PROPORCION DE VACASQUE QUIERO SEGREGRAR
		probMC_sana=0.35;//0.50;//0.14;//0.35; //default:0.35; AS: lim inf=0.14;lim sup=0.50;//SIN POMO 0.03 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		pesoMC=1;//0.001;//0.5;//0.001;//marzo 2022 // 1;
		pesoMSC=1;
		mcSecado_sana=0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.77;
		mscSecado_mc=0.09;
		factor_rb =1;//0.6;
		factor_ra =1;//0.001;//1;//0.815;//0.56;//0.8;//1//0.9;
		probInfSecado =0.007;
	}
	/*if(opcionTipoEst==8){//Defecto - Cambiar x 4 medidas+segregacion
		eficacia=0;
		DiasRetiro=0; //Dias de descarte de leche por mc
		Coef_Segreg=0;
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.03; //SIN POMO!!!! CON POMO: 0.35 ojo: zeconni 2006 dice 0,75 antes delos 30del//sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.3;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.02;

	}*/
	if(opcionTipoEst==9){//4 medidas+descarte
		eficacia=0.55;//0.605;//0.495;//0.55;//0.57;//0.50;//0.74;//0.765;//0.54; //sept 2021-antes era 0.74 pero saco efecto de DCT en lactanca=0.20//ori=0.74;//0.546;//0.54;//0.55;//0.74;//0.27;//0.53;//0.74;//0.74; //0.44; //0.74; //ORIGINAL
		DiasRetiro=6;//3; //ori //Dias de descarte de leche por mc
		Coef_Segreg=0;// probéo combinar segre y descarte con coef 0,18-ver escenario e89- sept2021
		pesoMC=1;
		pesoMSC=1;
		probMC_sana=0.35;//0.50;//0.14;//0.35; //default:0.35; AS: lim inf=0.14;lim sup=0.50;//SIN POMO 0.03 //sino pasa a MSC: 0.97 sin pomo y 0.65 con pomo//verificar tasa y prob. meli
		mcSecado_sana=0.77;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mcSecado_mc=0.01;
		mscSecado_sana=0.77;// ojo: halasa 2010: cura espontanea: 0.11; cura con DTC: 0.77;
		mscSecado_mc=0.09;
		factor_rb =1;
		factor_ra =1;
		probInfSecado =0.007;
	}
}

/************ CALCULO DE PARAMETROS PARA CURVA DE LACTANCIA DE VACAS  ************/
void calcularParamCurvaLact(char nombreVacas[30]){
	printf("\n\t CALCULO DE PARAMETROS PARA CURVA DE LACTANCIA DE VACAS\n");
	char archivoD[50];
	strcpy(archivoD,"./InicializaProdDiaria.sh ");
	strcat(archivoD,"ArchivosTambo/");
	strcat(archivoD, nombreVacas);
	//  printf("   %s",archivoD);
	system(archivoD);  //ejecuta en comando ./InicializaTambo.sh ArchivosTambo/nombreVacas
	//  printf("\n Calculo efectuado con exito!!! ");
}

/************ Calculos Estimacion ************/
void estimacion(char archivoEntrada[30],char archivoSalida[40],float probaMC[],float probaMSC800[],float probaMSCMayor[],char patog[],int cod){
	struct tm *tiempo;
	time_t fecha_sistema;
	time(&fecha_sistema);
	tiempo=localtime(&fecha_sistema);
	unsigned int anio=tiempo->tm_year + 1900;
	unsigned char mes=tiempo->tm_mon + 1;
	unsigned char dia=tiempo->tm_mday;
	unsigned char hr =tiempo->tm_hour;
	unsigned char min=tiempo->tm_min;
	unsigned char seg=tiempo->tm_sec;
	printf("Inicio estimacion %d:%d:%d\n",hr,min,seg);
	vaca aurora_inicial[MaxVacas];  /*Matriz conteniendo las vacas iniciales */
	vaca aurora_entrada[MaxVacas];  /*Matriz conteniendo las vacas a analizar*/
	vaca aurora_salida[MaxVacas];  /*Matriz conteniendo las vacas  resultantes*/
	FILE *archivo, *arch_sal; /* archivo es el archivo de entrada y arch_sal es el archivo de salida */
	unsigned int seed;
	int TengoVacas=0, i=0;
	char strIng[30];
	strcpy(strIng,"./ArchivosTambo/");
	strcat(strIng, archivoEntrada);
	i=0;
	vaca AA=aurora_inicial[i];
	archivo=fopen(strIng,"r"); /* Abre archivo de datos para lectura de las vacas */

	/* Lee el archivo de entrada y transfiere el contenido a la primer fila de la matriz (tambien levanta el maximo id en uso)*/
	int max_id=0;

	//Lee la cabecera del archivo
	char line[1024];
	if (fgets(line, sizeof(line), archivo) == NULL)  {
		printf("El archivo '%s' esta vacio\n", archivoEntrada);
		fclose(archivo);
		return;
	}

	seed=2;
  long semilla=leesemilla();
	srand(semilla);
	nuevasemilla(rand());
	unsigned int cantVacasLact=0;
	unsigned int cantVacasMC=0;
	unsigned int cantVacasMSC_rb=0;
	unsigned int cantVacasMSC_ra=0;

	unsigned int cantVacasLactIni=0;
	unsigned int cantVacasMCIni=0;
	unsigned int cantVacasMSC_rbIni=0;
	unsigned int cantVacasMSC_raIni=0;

	while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d",&(AA.orden),&(AA.id),&(AA.partos),
			        &(AA.pv),&(AA.prenez),&(AA.sl), &(AA.del),&(AA.qel),&(AA.producdiaria),&(AA.produc),&(AA.merito), &(AA.sir),&(AA.salud),&(AA.descarte), &(AA.rcs),&(AA.nroCuartMCLactPrevia),&(AA.nroCuartMCLactActual),&(AA.patogeno))){
		unsigned int valorPatog=0;
		AA.saludPat_SAgalactiae=salud_sana;
		AA.saludPat_SAureus=salud_sana;
		AA.saludPat_SCN=salud_sana;
		AA.saludPat_OtrosStrepto=salud_sana;
		AA.saludPat_EColi=salud_sana;
		AA.saludPat_Otros=salud_sana;
		if(AA.salud==2){
			valorPatog=probab_Patogeno(probaMC);
		}else {
			AA.mesEnf=0;
			AA.cantMC=0;
			//Verificar el valor de los recuentos para decir si la salud es 1 o 3
			if(AA.rcs<=200){
				AA.salud=salud_sana;
				//Asignar el patogeno para el estado de salud 1
				valorPatog=0;
			}else{
				AA.salud=salud_msc;
				//Asignar el patogeno para el estado de salud 3
				if(AA.rcs<=800){
					valorPatog=probab_Patogeno(probaMSC800);
				} else{
					valorPatog=probab_Patogeno(probaMSCMayor);
				}
				if(AA.rcs>2000){
					AA.rcs=2000;
				}
			}
		}
		//Asigna a la vaca un unico patogeno y al patogeno el estado de salud.
		AA.patogeno=valorPatog;
		if(valorPatog!=0){
			if(valorPatog==SAureus){
				AA.saludPat_SAureus=AA.salud;
			/* } else if(valorPatog==SAgalactiae){
				 AA.saludPat_SAgalactiae=AA.salud;
			} else if(valorPatog==SCN){
				AA.saludPat_SCN=AA.salud;
			} else if(valorPatog==OtrosStrepto){
				AA.saludPat_OtrosStrepto=AA.salud;*/
			} else if(valorPatog==EColi){
				AA.saludPat_EColi=AA.salud;
			/* } else if(valorPatog==Otros){
				AA.saludPat_Otros=AA.salud;*/
			}
		}else{
			AA.salud=salud_sana;
		}
		if(AA.salud==2){
			if(AA.sl==1){
				AA.mesEnf=1;
				AA.sir=2;
				AA.cantMC=1;
			} else{
				AA.mesEnf=0;
				AA.sir=1;
				AA.cantMC=0;
			}
		}
		// PROB infeccion
		if(AA.producdiaria!=0){
			cantVacasLactIni++;
			if(AA.saludPat_SAureus==salud_mc){
				cantVacasMCIni++;
			}else if(AA.saludPat_SAureus==salud_msc){
				if(AA.rcs<limiteRecuentos)
				  cantVacasMSC_rbIni++;
				else
				  cantVacasMSC_raIni++;
			}
		}
		// Fin PROB infeccion
		AA.cantTotalMC=0;	//Se inicializa en cero. no esta contabilizando los casos de la quincena 0
		AA.cantTotalMSC=0;
		aurora_inicial[i]=AA;
		if(AA.id>max_id)
			max_id=AA.id;
		i++;

		//Calculo infeccion
		if(AA.producdiaria!=0){
			AA.infGral=9;  //No es valido(9) contab inf cuando la vaca viene en lactaccia
			AA.infMC=9;
			AA.infMSC=9;
		}else{
			AA.infGral=1;  //inf estado para sana
			AA.infMC=1;
			AA.infMSC=1;
		}
	};
	fclose(archivo);
	/* Finaliza el analisis de los datos de entrada*/

	unsigned int cant_iteracion = 1;

	/*Generacion del nombre del archivo de salida*/
	char fecha [10];
	sprintf(fecha, "%d-%d-%d",anio,mes,dia);

	char str[30];
	strcpy(str,"./ArchivosTambo/");
	strcat(str, fecha);
	strcat(str, archivoSalida);
	arch_sal=fopen(str,"w");  /*  Abre archivo de salida para escritura */
	fprintf(arch_sal,"Ejec;Quincena;Anio;orden;id;partosNop;nop;pv;mesPrenez;sl;diaLactancia;mesLactancia;prodDiaria;prodMensual;merito;sir;salud;descarte;rcs;perdMC;perdMSC;patogeno;SAureus;SAgalactiae;SCN;Strepto;EColi;Otros;infGral;infMC;infMSC;saludAnt;esc.\n");

	fprintf(stderr,"Espere mientras se ejecuta la estimacion\n");
	float expo=(exp(cte_B) -1);
	while (cant_iteracion <= MAX_EJECUCION){
		//printf("Ejecucion %d\n",cant_iteracion);
		//semilla x iteracion
		semilla=leesemilla();
		srand(semilla);
		nuevasemilla(rand());

		TengoVacas = i ; /*Tengo vacas contiene la cantidad de vacas que tengo en el archivo de entrada*/
		unsigned int cantidad_descarte=0;  /*Lleva el conteo de todas las vacas que se descartan en todos los meses de la estimacion*/

		unsigned int iteracionActual=0;
		unsigned int cvi=0;
		setearValoresTipoEstimacion(opcionTipoEst);
		setearValoresDescarte(opcionDescarte1,opcionDescarte1MC,opcionDescarte1MSC);
		for(cvi=0;cvi<TengoVacas;cvi++){
			vaca AA=aurora_inicial[cvi];
			AA=actualizar_perdida_mc(AA,semilla);
			aurora_entrada[cvi]=AA;
			unsigned int nop=1; //para vacas en nop 0 y 1
			if(AA.partos>1)
			  nop=2;
			int anio=indice24(0,1)+1;
			fprintf(arch_sal,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",cant_iteracion,(0),anio,(AA.orden),(AA.id),(AA.partos),nop,
			(AA.pv),(AA.prenez),(AA.sl),(AA.del),(AA.qel),(AA.producdiaria),(AA.produc),(AA.merito),(AA.sir),(AA.salud), (AA.descarte), (AA.rcs),(AA.resultPerdidaMC),(AA.resultPerdidaMSC),(AA.patogeno),(AA.saludPat_SAureus),(AA.saludPat_SAgalactiae),(AA.saludPat_SCN),(AA.saludPat_OtrosStrepto),(AA.saludPat_EColi),(AA.saludPat_Otros),(AA.infGral),(AA.infMC),(AA.infMSC),salud_inic,opcionTipoEst);
		}
		cantVacasLact=cantVacasLactIni;
		cantVacasMC=cantVacasMCIni;
		cantVacasMSC_rb=cantVacasMSC_rbIni;
		cantVacasMSC_ra=cantVacasMSC_raIni;
		while (iteracionActual < MAX_QUINCENA){    /* cada iteracion genera una estimacion de datos en un archivo de salida */
		//printf("quinc %d\n",iteracionActual);
			int anio=indice24((iteracionActual+1),1)+1;
			int opcionEsc=opcionTipoEstSeg;
			if(anio >=0 && anio<=opcionAnioCorte){
				opcionEsc=opcionTipoEst;
				setearValoresDescarte(opcionDescarte1,opcionDescarte1MC,opcionDescarte1MSC);
			}else{
				setearValoresDescarte(opcionDescarte2,opcionDescarte2MC,opcionDescarte2MSC);
			}
			setearValoresTipoEstimacion(opcionEsc);

			//	fprintf(stderr,"Ejec: %d Anio: %d eficacia %f\n",cant_iteracion,anio,eficacia);

			unsigned int i=0;
			unsigned int cv=0;
			// PROB infeccion
			//Hernan vieja
			// float delta=expo*((float)(cantVacasMSC_rb*factor_rb) + (cantVacasMSC_ra*factor_ra) + (pesoMC/pesoMSC)*(float)cantVacasMC);
			// float probI=delta/(float)cantVacasLact;
			//Nueva Hernan
			float delta=((float)(cantVacasMSC_rb*factor_rb) + (cantVacasMSC_ra*factor_ra) + (pesoMC/pesoMSC)*(float)cantVacasMC);
			//agregué formulas abajo. probando sacar algunas infectadas tipo segregacion. meli 3 mayo 2019

			//printf("numero de infectadas %f\n",delta);//meli 3 mayo 2019
			//float coefSeg =1;//0.8;//meli 3 mayo 2019: ya está definido en tambo.h VER
			float deltados = delta * (1-Coef_Segreg);//meli 3 mayo 2019  //Coef_Segreg
			//printf("numero de infectadas %f\n",deltados);//meli 3 mayo 2019
			float probI=(cte_B*deltados)/((float)cantVacasLact);
			//float probI=(cte_B*delta)/((float)cantVacasLact); //original
			//printf("probabilidad de Infeccion sin eficacia 1 %f \n",probI);

			//  Halasa 2009
			//	float delta=((float)(cantVacasMSC_rb*factor_rb) + (cantVacasMSC_ra*factor_ra) + (pesoMC/pesoMSC)*(float)cantVacasMC);
			//	float probI=1 - (exp(-(cte_B*delta)/(float)cantVacasLact));

			float probInf=(probI*(-eficacia))+probI;

			//printf("probabilidad de Infeccion con eficacia 2 %f \n",probInf);

			if(probI==0){
				// printf("cantVacasMSC_rb %d  ",cantVacasMSC_rb);
				// printf("factor_rb %f  ",factor_rb);
				// printf("cantVacasMSC_ra %d  ",cantVacasMSC_ra);
				// printf("factor_ra %f  ",factor_ra);
				// printf("pesoMC %f  ",pesoMC);
				// printf("pesoMSC %f  ",pesoMSC);
				// printf("cantVacasMC %d  ",cantVacasMC);
				// printf("delta %f  ",delta);
				// printf("cantVacasLact %d \n ",cantVacasLact);
				//printf("Ej %d It %d Esc %d Prob. de Inf sin eficacia %f \n",cant_iteracion,iteracionActual+1,opcionEsc,probI);// acaaa
				//printf("Ej %d It %d Esc %d Prob. de Inf con eficacia %f \n",cant_iteracion,iteracionActual+1,opcionEsc,probInf);// acaaa
			}
			//Fin PROB infeccion
			cantVacasLact=0;
			cantVacasMC=0;
			cantVacasMSC_rb=0;
			cantVacasMSC_ra=0;
			for(cv=0;cv<TengoVacas;cv++){
				semilla=leesemilla();
				srand(semilla);
				nuevasemilla(rand());
				vaca AA=aurora_entrada[cv];
				if(AA.descarte==descarte_rodeo){ //Solo se analizan las vacas que no estan en descarte.
					int saludAnterior=AA.salud;
					int recuentoAnt=AA.rcs;
					//fprintf(stderr,"Quincena estimacion %d Vaca: %d\n",(iteracionActual+1),(i));
					//    fprintf(stderr,"\t Estado Inicial:\n\t\tMes de prenez: %d - Estado de lactancia: %d\n\t\tNOP: %d - Estado de prenez: %d (1=prenada; 2= vacia)\n\t\tEstado de lactancia: %d (1=lactancia; 2=seca) - RCS: %d\n",AA.prenez, AA.lactancia, AA.partos, AA.pv,AA.sl,AA.rcs);
					//    fprintf(stderr,"\t\tPatogeno: %d; SAureus: %d; SAgalactiae: %d; SCN: %d; OtrosStrepto: %d; EColi: %d; Otros: %d\n",(AA.patogeno),(AA.saludPat_SAureus),(AA.saludPat_SAgalactiae),(AA.saludPat_SCN),(AA.saludPat_OtrosStrepto),(AA.saludPat_EColi),(AA.saludPat_Otros));
					// AA=actualizar_perdida_mc(AA);  //Asi el calculo se muestra en el proximo mes de estimacion
					AA=actualizar_preniez_vaca(AA); //aca la vaca tiene los datos de la quincena anterior p calcular la prob de pre�ez en base al patogeno y el tipo de mc
					AA=actualizar_lactancia(AA);
					AA=actualizar_categoria_preniez (AA);
					AA=actualizar_categoria_sl (AA);
					AA=actualizar_descarte (AA);
					AA=actualizar_prod_dia_mes(AA,archivoEntrada);
					//Ver aca de actualizar la salud de cada patogeno del arreglo,
					// en funcion de lo resultante y de acuerdo a la prioridad obtenida cargar el patogeno y el estado de salud.
					if(patog=="coli")
						AA=actualizar_salud_EColi_Houben(AA);
					if(patog=="aureus")
						AA=actualizar_salud_aureus(AA,probInf,semilla,cod);
					AA=actualizar_patogeno(AA);
					AA=actualizar_salud_rcs(AA,semilla,saludAnterior,recuentoAnt);//Por ahora usa houben cambiar para que se actualice en funcion de los patogenos salud y rcs
					//Luego ela perdida debe calcularse en funcion de la salud y del patogeno
					AA=actualizar_perdida_mc(AA,semilla); //Asi te mostraria los datos de perdida con la estimacion actual
					//Falta actualizar el rcs en funcion de la salud y el patogeno.
					//   fprintf(stderr,"\t Estado Final:\n\t\tMes de prenez: %d - Dia en lactancia: %d - Estado de lactancia: %d\n\t\tNOP: %d - Estado de prenez: %d (1=prenada; 2= vacia)\n\t\tEstado de lactancia: %d (1=lactancia; 2=seca)\n",AA.prenez, AA.del, AA.lactancia,AA.partos,AA.pv,AA.sl);
					//Mod fprintf si agrego parametros a la vaca
					unsigned int nop=1; //para vacas en nop 0 y 1
					if(AA.partos>1)
					  nop=2;

					fprintf(arch_sal,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",(cant_iteracion),(iteracionActual+1),anio,(AA.orden),(AA.id),(AA.partos),nop,
					(AA.pv),(AA.prenez),(AA.sl),(AA.del),(AA.qel),(AA.producdiaria),(AA.produc),(AA.merito),(AA.sir),(AA.salud), (AA.descarte), (AA.rcs),(AA.resultPerdidaMC),(AA.resultPerdidaMSC),(AA.patogeno),(AA.saludPat_SAureus),(AA.saludPat_SAgalactiae),(AA.saludPat_SCN),(AA.saludPat_OtrosStrepto),(AA.saludPat_EColi),(AA.saludPat_Otros),(AA.infGral),(AA.infMC),(AA.infMSC),saludAnterior,opcionEsc);
					aurora_salida[i]=AA; //Los datos de la vaca se guardan en la proxima fila para la proxima estimaci\F3n
					i++;
				}else{
					cantidad_descarte++;
					vaca vNueva=generarNuevaVaca(max_id+(cantidad_descarte),patog);
					aurora_salida[i]=vNueva;
					unsigned int nop=1; //para vacas en nop 0 y 1
					if(vNueva.partos>1)
					  nop=2;
					fprintf(arch_sal,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",(cant_iteracion),(iteracionActual+1),anio,(vNueva.orden),(vNueva.id),(vNueva.partos),nop,
					(vNueva.pv),(vNueva.prenez),(vNueva.sl),(vNueva.del),(vNueva.qel),(vNueva.producdiaria),(vNueva.produc),(vNueva.merito),(vNueva.sir),(vNueva.salud), (vNueva.descarte), (vNueva.rcs),(vNueva.resultPerdidaMC),(vNueva.resultPerdidaMSC),(vNueva.patogeno),(vNueva.saludPat_SAureus),(vNueva.saludPat_SAgalactiae),(vNueva.saludPat_SCN),(vNueva.saludPat_OtrosStrepto),(vNueva.saludPat_EColi),(vNueva.saludPat_Otros),(vNueva.infGral),(vNueva.infMC),(vNueva.infMSC),salud_inic,opcionEsc);
					i++;
				}
				// PROB infeccion
				if(AA.producdiaria!=0){  //Si prodDiaria==0 la vaca esta seca
					cantVacasLact++;
					if(AA.saludPat_SAureus==salud_mc){
						cantVacasMC++;
					}else if(AA.saludPat_SAureus==salud_msc){
						if(AA.rcs<limiteRecuentos)
						cantVacasMSC_rb++;
						else
						cantVacasMSC_ra++;
					}
				}
			}  // Fin PROB infeccion
			//Fin del analisis de las quincenas
			int n=0;
			for(n=0;n<TengoVacas;n++){
				vaca AA = aurora_salida[n];
				aurora_entrada[n]=AA;
			}
			TengoVacas = i ;
			iteracionActual++;
		}
		//Fin del analisis de las iteraciones
		cant_iteracion++;
	}
	fclose(arch_sal);
	fprintf(stderr,"Estimacion completada\n");

	time(&fecha_sistema);
	tiempo=localtime(&fecha_sistema);
	hr =tiempo->tm_hour;
	min=tiempo->tm_min;
	seg=tiempo->tm_sec;
	printf("Fin estimacion %d:%d:%d\n",hr,min,seg);
}

	//Recalcular para cada caso el valor de A.patogeno
vaca actualizar_salud_EColi(vaca A){
	if(A.producdiaria>0){
		if(A.salud==salud_sana){
			if( A.producdiaria!=0){
				if(A.saludPat_EColi==salud_sana){
					unsigned int lim_Inf=RAND_MAX*0.02; //Prob de infectarse con E Coli x quincena
					unsigned int aleat=rand();
					if (aleat <=lim_Inf){ /* enferma */
						float probMSC=0.83;
						unsigned int lim_msc=RAND_MAX*0.15; //prob MSC
						unsigned int aleat_m=rand();
						if (aleat_m <=lim_msc)
						  A.saludPat_EColi=salud_msc;
						else
						  A.saludPat_EColi=salud_mc;
					}
				}else if(A.saludPat_EColi==salud_mc ){
					float probSana=0.8; //verificar tasa y prob. meli
					unsigned int lim_sana=RAND_MAX*probSana;
					unsigned int aleat_m=rand();
					if (aleat_m <=lim_sana)
					  A.saludPat_EColi=salud_sana;
					else
					  A.saludPat_EColi=salud_msc;
				}else if(A.saludPat_EColi==salud_msc ){
					unsigned int lim_sana=RAND_MAX*0.9;
					unsigned int lim_mc=RAND_MAX*(0.9+0.05);
					unsigned int aleat=rand();
					if (aleat <=lim_sana)
					  A.saludPat_EColi=salud_sana;
					else if(aleat <=lim_mc)
					  A.saludPat_EColi=salud_mc;
					else   /*msc*/
					  A.saludPat_EColi=salud_msc;
				}
			}else{
				A.saludPat_EColi=salud_sana; /* sana porque la produccion esta en cero*/
			}
		}
	}
	return A;
}

//Recalcular para cada caso el valor de A.patogeno
vaca actualizar_salud_aureus(vaca A,float probInf,int semilla,int cod){
	int ejecutarA=0;
	int ejecutarB=0;
	if(cod==Ejec_sinsecado){
		if(A.producdiaria>0) ejecutarA=1;
	}
	if(cod==Ejec_consecado_rp){
		if(A.producdiaria>0 && A.prenez!= -3) ejecutarA=1; //ojo cambio= A.prenez > -2
		//if(A.producdiaria>0 && A.prenez >-2) ejecutarA=1; //activé esta línea!! desactivar después y activar la de arriba-sep2021
		else ejecutarB=1;
	}
	if(cod==Ejec_consecado_sinrp){
		if(A.producdiaria>0) ejecutarA=1;
		else ejecutarB=1;
	}
	if(ejecutarA==1){ //en produccion sl=1  //infeccion en lactancia, se excluye -3 para que mantenga el valor de salud anterior (18)
		unsigned int max=RAND_MAX;
		if(A.saludPat_EColi==salud_sana){
			if( A.producdiaria!=0){
				if(A.saludPat_SAureus==salud_sana ){
					unsigned int lim_Inf=RAND_MAX*probInf;
					unsigned int aleat=rand();
					if (aleat <=lim_Inf){/* enferma */
						float probMSC=0.83;// default= 0.83; Up 0.88; low: 0.77
						unsigned int lim_msc=RAND_MAX*probMSC;
						unsigned int aleat_m=rand();
						if (aleat_m <=lim_msc)
						  A.saludPat_SAureus=salud_msc;
						else
						  A.saludPat_SAureus=salud_mc;
					}
				}else if(A.saludPat_SAureus==salud_mc ){
					unsigned int lim_sana=RAND_MAX*probMC_sana;
					unsigned int aleat_m=rand();
					if (aleat_m <=lim_sana)
					  A.saludPat_SAureus=salud_sana;
					else
					  A.saludPat_SAureus=salud_msc;
				}else if(A.saludPat_SAureus==salud_msc ){
					unsigned int lim_sana=RAND_MAX*0.10;//0.68;//0.06;//0.10;//default:0.1; AS up: 0.68; AS low:0.06;//
					unsigned int lim_mc=RAND_MAX*(0.10+0.12);//lim sup=0.13;lim inf= 0.08;default: 0.12(0.68+0.12);//default:(0.1+0.12);//acá también debor cambiar el limite OJO
					unsigned int aleat=rand();
					if (aleat <=lim_sana)
					  A.saludPat_SAureus=salud_sana;
					else if(aleat <=lim_mc)
					  A.saludPat_SAureus=salud_mc;
					else   /*msc*/
					  A.saludPat_SAureus=salud_msc;
				}
			}else{
				A.saludPat_SAureus=salud_sana; /* sana porque la produccion esta en cero*/
			}
		}
	}
	if(ejecutarB==1){ //si produccion es cero  sl=2 secas - no hay cambio en saludPat_SAureus
		if(A.producdiaria==0 && (A.prenez==18) ){  //infeccion en el secado, se hace solo en quincena 18 que siempre esta seca la vaca
			if(A.saludAntSecado==A.salud){
				if(A.saludAntSecado==salud_sana){
					unsigned int lim_Inf=RAND_MAX*probInfSecado; //MELI EN 0.02;//(ALLORE Y ERB)
					unsigned int aleat=rand();
					if (aleat <=lim_Inf){// enferma
						float probMSC=0.90;
						unsigned int lim_msc=RAND_MAX*probMSC;
						unsigned int aleat_m=rand();
						if (aleat_m <=lim_msc)
						  A.saludPat_SAureus=salud_msc;
						else
						  A.saludPat_SAureus=salud_mc;
					}else{
						A.saludPat_SAureus=salud_sana;
					}
				}
				if(A.saludAntSecado==salud_mc){
					unsigned int lim_sana=RAND_MAX*mcSecado_sana;
					unsigned int lim_mc=RAND_MAX*(mcSecado_sana+mcSecado_mc);
					unsigned int aleat=rand();
					if (aleat <=lim_sana)
					  A.saludPat_SAureus=salud_sana;
					else if(aleat <=lim_mc)
					  A.saludPat_SAureus=salud_mc;
					else   //msc
					  A.saludPat_SAureus=salud_msc;
				}
				if(A.saludAntSecado==salud_msc){
					unsigned int lim_sana=RAND_MAX*mscSecado_sana;
					unsigned int lim_mc=RAND_MAX*(mscSecado_sana+mscSecado_mc);
					unsigned int aleat=rand();
					if (aleat <=lim_sana)
					  A.saludPat_SAureus=salud_sana;
					else if(aleat <=lim_mc)
					  A.saludPat_SAureus=salud_mc;
					else   //msc
					  A.saludPat_SAureus=salud_msc;
				}
			} //ya cambio el valor de salud

		}
	}
	//if(A.prenez== -3 || A.prenez==18) fprintf(stderr,"\t Estado final:\n\t\t   - Mes de prenez: %d - salud_PAto: %d -salud glob: %d \n", A.prenez,A.saludPat_SAureus,A.salud);
	return A;
}

vaca actualizar_patogeno (vaca A){
	if (A.saludPat_EColi!=1){
		A.patogeno=5;
	} else if (A.saludPat_SAureus!=1){
		A.patogeno=1;
	} else{
		A.patogeno=0;
	}
	return A;
}

vaca actualizar_salud_rcs (vaca A,int semilla,int saludAnt,int rcsAnt) {
	//	unsigned int saludAnt=A.salud;
	if(A.producdiaria>0){
		if(A.patogeno==0){  //sana sana
			A.salud= salud_sana;
		}else if(A.patogeno==SAureus){
			A.salud= A.saludPat_SAureus;
		}else if(A.patogeno==EColi){
			A.salud= A.saludPat_EColi;
		}else {
			A.salud= salud_sana;//otro pat
		}
		if(saludAnt!=A.salud){
			if(saludAnt!=salud_mc && A.salud==salud_mc){
				A.sir=2;
				A.mesEnf=1;
				A.cantMC=A.cantMC+1;
			}
		}else{
			if(A.salud==salud_mc && A.prenez==-3){
				A.sir=2;
				A.mesEnf=1;
				A.cantMC=1;
			}
		}
		//		printf("Calculo rcs\n");
		if(saludAnt==salud_msc  && A.salud==salud_msc){ //inicio msc msc
			float limInf=100;
			float limSup=450;
			if((float)rcsAnt<=limInf){
				if(rcsAnt==0){
					rcsAnt=50;
				}

				A.rcs=rcsAnt*2;
			}
			else{
				A.rcs=exp(distNormal(semilla, 5.58,0.84,99));
	}

			/*if(limInf<(float)rcsAnt && (float)rcsAnt<limSup){
				int a=generarAleatorio(80,110);
				float calcRcs=(float)rcsAnt*((float)a/(float)100);
				float resultado = (float)(limInf+4*calcRcs+limSup)/(float)6;//funcion triangular
				A.rcs = (int) resultado;
			}
			if(limSup<=(float)rcsAnt){
				A.rcs=rcsAnt*0.8;
			}*/
			//Termina msc-P_prenez_msc
		}else{ //Generar Aleatorio
					int minAleat=0;
					int maxAleat=999;
					if(saludAnt==salud_sana && A.salud==salud_sana){minAleat=12; 	maxAleat=50;}
					if(saludAnt==salud_sana && A.salud==salud_mc){	minAleat=1000; 	maxAleat=1100;}
					if(saludAnt==salud_sana && A.salud==salud_msc){	minAleat=200; 	maxAleat=500;}
					if(saludAnt==salud_mc && A.salud==salud_sana){	minAleat=49; 	maxAleat=50;}
					if(saludAnt==salud_msc && A.salud==salud_sana){	minAleat=48; 	maxAleat=50;}
					if(saludAnt==salud_msc && A.salud==salud_mc){	minAleat=1100; 	maxAleat=3200;}

					A.rcs=generarAleatorio(minAleat,maxAleat);

				 	if(saludAnt==salud_mc && A.salud==salud_msc) {
						A.rcs=exp(distNormal(semilla, 6.4,0.54,99));
									}

				}


			//if(A.partos==1){ //vaq
			/*	if(A.del<60){
					if(saludAnt==salud_sana && A.salud==salud_sana){minAleat=12; 	maxAleat=50;}
					if(saludAnt==salud_sana && A.salud==salud_mc){	minAleat=1000; 	maxAleat=1100;}
					if(saludAnt==salud_sana && A.salud==salud_msc){	minAleat=200; 	maxAleat=500;}
					if(saludAnt==salud_mc && A.salud==salud_sana){	minAleat=49; 	maxAleat=50;}
					if(saludAnt==salud_mc && A.salud==salud_msc){	minAleat=640/*700*///; 	maxAleat=740/*1000*/;}
					/*if(saludAnt==salud_msc && A.salud==salud_sana){	minAleat=48; 	maxAleat=50;}
					if(saludAnt==salud_msc && A.salud==salud_mc){	minAleat=1100; 	maxAleat=3200;}
				} else if(A.del>=60){
					if(saludAnt==salud_sana && A.salud==salud_sana){minAleat=12; 	maxAleat=50;}
					if(saludAnt==salud_sana && A.salud==salud_mc){	minAleat=1000; 	maxAleat=1100;}
					if(saludAnt==salud_sana && A.salud==salud_msc){	minAleat=200; 	maxAleat=500;}
					if(saludAnt==salud_mc && A.salud==salud_sana){	minAleat=49; 	maxAleat=50;}
					if(saludAnt==salud_mc && A.salud==salud_msc){	minAleat=640/*700*///; 	maxAleat=740/*1000*/;}
			/*		if(saludAnt==salud_msc && A.salud==salud_sana){	minAleat=48; 	maxAleat=50;}
					if(saludAnt==salud_msc && A.salud==salud_mc){	minAleat=1100; 	maxAleat=3200;}
				}
			}else if(A.partos>1){ //vaca
				if(A.del<60){
					if(saludAnt==salud_sana && A.salud==salud_sana){minAleat=12; 	maxAleat=50;}
					if(saludAnt==salud_sana && A.salud==salud_mc){	minAleat=1000; 	maxAleat=1100;}
					if(saludAnt==salud_sana && A.salud==salud_msc){	minAleat=200; 	maxAleat=500;}
					if(saludAnt==salud_mc && A.salud==salud_sana){	minAleat=49; 	maxAleat=50;}
					if(saludAnt==salud_mc && A.salud==salud_msc){	minAleat=640/*700*///; 	maxAleat=740/*1000*/;}
				/*	if(saludAnt==salud_msc && A.salud==salud_sana){	minAleat=48; 	maxAleat=50;}
					if(saludAnt==salud_msc && A.salud==salud_mc){	minAleat=1100; 	maxAleat=3200;}
				} else if(A.del>=60){
					if(saludAnt==salud_sana && A.salud==salud_sana){minAleat=12; 	maxAleat=50;}
					if(saludAnt==salud_sana && A.salud==salud_mc){	minAleat=1000; 	maxAleat=1100;}
					if(saludAnt==salud_sana && A.salud==salud_msc){	minAleat=200; 	maxAleat=500;}
					if(saludAnt==salud_mc && A.salud==salud_sana){	minAleat=49; 	maxAleat=50;}
					if(saludAnt==salud_mc && A.salud==salud_msc){	minAleat=640/*700*///; 	maxAleat=740/*1000*/;}
				/*if(saludAnt==salud_msc && A.salud==salud_sana){	minAleat=48; 	maxAleat=50;}
					if(saludAnt==salud_msc && A.salud==salud_mc){	minAleat=1100; 	maxAleat=3200;}
				}
			}
			//			printf("Calculo rcs f 7 prim\n");
			A.rcs=generarAleatorio(minAleat,maxAleat);
		}*/
		/*	if(A.patogeno==EColi){
		if(A.saludPat_EColi==salud_msc)
		A.rcs=generarAleatorio(100,3200);
		else if(A.saludPat_EColi==salud_mc)
		A.rcs=generarAleatorio(6000,7000);
	}*/

	}else{
		A.rcs=0;
		if(A.patogeno==0){
			A.salud= salud_sana;
		}else if(A.patogeno==SAureus){
			A.salud= A.saludPat_SAureus;
		}else if(A.patogeno==EColi){
			A.salud= A.saludPat_EColi;
		}else {
			A.salud= salud_sana;
		}
	}

	//conteo para descarte
	if(A.producdiaria>0){
		if(A.infGral==0) A.infGral=9;
		if(A.infMC==0) A.infMC=9;
		if(A.infMSC==0) A.infMSC=9;
		if(A.salud==salud_mc){
			A.cantTotalMC=A.cantTotalMC+1; //Conteo total de MC de la vaca
			if(saludAnt!=salud_mc){ //Cambiar la salud
				//Calculo infeccion
				if(A.infMC==1){ //si esta sana marca infmc
					A.infMC=0;
				}
				if(A.infGral==1){ //si esta sana marca infGral
					A.infGral=0;
				}
			}
		}
		if(A.salud==salud_msc){ //salud 3
			// if(A.rcs>=rcs_max) // dejo para que cuente todas las msc indep del rcs_max
			A.cantTotalMSC=A.cantTotalMSC+1; //Conteo total de MSC de la vaca
			if(saludAnt!=salud_msc){ //Cambiar la salud
				//Calculo infeccion
				if(A.infMSC==1){ //si esta sana marca infmsc
					A.infMSC=0;
				}
				if(A.infGral==1){ //si esta sana marca infGral
					A.infGral=0;
				}
			}
		}
	}else{
		A.infGral=1;
		A.infMC=1;
		A.infMSC=1;
	}
	return A;
}


 /* Version anterior - con distNormal
 vaca actualizar_salud_rcs (vaca A,int semilla,int saludAnt,int rcsAnt) {  //de acuerdo a los patogeno
	unsigned int saludAnt=A.salud;
	if(A.producdiaria>0){
		if(A.patogeno==0){  //sana sana
			A.rcs=generarAleatorio(12,50);
		}else if(A.patogeno==SAureus){
			if(A.saludPat_SAureus==salud_msc)
				A.rcs=100*pow(2,((distNormal(semilla, 5.32,0.2,5.9)-3)));
			else if(A.saludPat_SAureus==salud_mc){
				if(DiasRetiro==0)
					A.rcs=100*pow(2,((distNormal(semilla, 7.8,0.2,8)-3)));
				else
					A.rcs=100*pow(2,((distNormal(semilla, 7.2,0.2,7.5)-3)));
			}

		}else if(A.patogeno==EColi){
			if(A.saludPat_EColi==salud_msc)
				A.rcs=generarAleatorio(100,3200);
			else if(A.saludPat_EColi==salud_mc)
				A.rcs=generarAleatorio(6000,7000);
		}
		if(A.patogeno==0){  //sana sana
			A.salud= salud_sana;
		}else if(A.patogeno==SAureus){
			A.salud= A.saludPat_SAureus;
		}else if(A.patogeno==EColi){
			A.salud= A.saludPat_EColi;
		}else {
			A.salud= salud_sana;
		}
		if(saludAnt!=A.salud){
			if(saludAnt!=salud_mc && A.salud==salud_mc){
				A.sir=2;
				A.mesEnf=1;
				A.cantMC=A.cantMC+1;
			}
		}else{
			if(A.salud==salud_mc && A.prenez==-3){
				A.sir=2;
				A.mesEnf=1;
				A.cantMC=1;
			}
		}
	}else{
		A.rcs=0;
		if(A.patogeno==0){
			A.salud= salud_sana;
		}else if(A.patogeno==SAureus){
			A.salud= A.saludPat_SAureus;
		}else if(A.patogeno==EColi){
			A.salud= A.saludPat_EColi;
		}else {
			A.salud= salud_sana;
		}
	}
	//conteo para descarte
	if(A.producdiaria>0){
		if(A.infGral==0) A.infGral=9;
		if(A.infMC==0) A.infMC=9;
		if(A.infMSC==0) A.infMSC=9;
		if(A.salud==salud_mc){
			A.cantTotalMC=A.cantTotalMC+1; //Conteo total de MC de la vaca
			if(saludAnt!=salud_mc){ //Cambiar la salud
			   //Calculo infeccion
				if(A.infMC==1){ //si esta sana marca infmc
					A.infMC=0;
				}
				if(A.infGral==1){ //si esta sana marca infGral
					A.infGral=0;
				}
			}
		}
		if(A.salud==salud_msc){ //salud 3
			// if(A.rcs>=rcs_max) // dejo para que cuente todas las msc indep del rcs_max
			A.cantTotalMSC=A.cantTotalMSC+1; //Conteo total de MSC de la vaca
			if(saludAnt!=salud_msc){ //Cambiar la salud
			   //Calculo infeccion
				if(A.infMSC==1){ //si esta sana marca infmsc
					A.infMSC=0;
				}
				if(A.infGral==1){ //si esta sana marca infGral
					A.infGral=0;
				}
			}
		}

	}else{
		A.infGral=1;
		A.infMC=1;
		A.infMSC=1;
	}
	return A;
}*/

	      //La vaca trae los datos de la quincena anterior - El calculo de pase a -6 -7 se hace con la salud de la quincena anterior
vaca actualizar_preniez_vaca(vaca A){
	int mesPreniez=A.prenez;
	//caso (mesPreniez==-4)  no existe
	if((mesPreniez==-5)){  //vaca abortada p entrar en servicio
		A.prenez=-2;
	}else if( (mesPreniez==-3) || (mesPreniez==-2)){
		A.prenez++;
	}else if((mesPreniez==-7) || (mesPreniez==-6) || (mesPreniez==-1) || (mesPreniez==0)){ //Caso perd msc o mc pasan derecho a servicio
		if(A.partos<MaximoNop){
			if(A.salud == salud_sana){
				if(probab_exito(P_noPrenez) == 1){ //tuvo exito ver q el calculo de la prob de exito dep de MC/MSC Aureus y coli
					A.prenez = 0;  //Vaca vacia en espera
				}else{
					A.prenez = 1;  //Vaca queda pre�ada
				}
			}else{
				if(A.salud == salud_mc) {
					if(probab_exito(P_noPrenez_mc) == 1){ //tuvo exito , no qued� pre�ada x mc
						A.prenez = -6;  //Vaca vacia culpa de mc
					}else{
						if(probab_exito(P_noPrenez)==1){ //tuvo exito
							A.prenez =0; // no pre�ada pero no es culpa mastitis
						} else{
							A.prenez =1; //pre�ada
						}
					}
				}
				if(A.salud == salud_msc) {
					if(probab_exito(P_noPrenez_msc) == 1){ //tuvo exito , sin pre�ez
						A.prenez = -7;  //Vaca vacia culpa de msc
					}else{
						if(probab_exito(P_noPrenez)==1){
							A.prenez =0;
						} else{
							A.prenez =1; //queda pre�ada
						}
					}
				}
			}
		}else{
			A.prenez = 0;  //Vaca en espera sin servicio
		}
	}else if((mesPreniez==1) || (mesPreniez==2) || (mesPreniez==3)) {
		if(A.salud == salud_sana){
			if(probab_exito(P_noAbortar1) == 0){  //sin exito//cambio para Tambo4_21_09_05.c
				int mesAntesAb=A.prenez;
				A.prenez = -5;// Vaca abortada ver si se cambiar el tratamiento por abortar en las primeras quincenas
				if((mesAntesAb >=10) || (A.del>=200)){ //Tomado de Vampp bovino
					A.partos+=1;
					/* A.lactancia=1; deberia hacerlo aqui y omitir de actualizar_lactancia la opcion de pre\F1ez -3 */
				}
			}else{
				A.prenez += 1; //La vaca sigue preniada
			}
		}else{
			if(A.salud == salud_mc) {
				if(probab_exito(P_noAbortar_mc) == 0){ //no tuvo exito
					A.prenez =-6;
				}else{
					A.prenez += 1; //La vaca sigue preniada
				}
			}
			if(A.salud == salud_msc) {
				if(probab_exito(P_noAbortar_msc) == 0){ //no tuvo exito
					A.prenez =-7; //analizar!!
				}else{
					A.prenez += 1; //La vaca sigue preniada
				}
			}
		}
	}else if(mesPreniez==18){
		A.prenez=-3;
		A.partos+=1;  //La vaca pare
		//	A.salud=salud_sana; //analizar ete estado de salud
		A.cantTotalMC=0;
		A.cantTotalMSC=0;
	}else{
		if(probab_exito(probNoAbortar2(mesPreniez)) == 0){ //cambio para Tambo4_21_09_05.c//
			int mesAntesAb=A.prenez;
			A.prenez = -5;// Vaca abortada
			if((mesAntesAb >=10) || (A.del>=200)){ //Tomado de Vampp bovino
				A.partos+=1;
				/* A.lactancia=1; deberia hacerlo aqui y omitir de actualizar_lactancia la opcion de pre�ez -3 */
			}
		}else{
			A.prenez += 1; //La vaca sigue preniada
		}
	}
	return A ;
}/* fin de act-vaca */

vaca actualizar_lactancia (vaca A){
	if((A.prenez==-5)){
		//A.qel = 0; //cambio meli 13 nov 2017
		A.del = 0;//(A.qel*15); //cambio meli 13 nov 2017
	} else if((A.prenez==-3)){
		A.qel=1;
		A.saludAntSecado=0;
		A.del = (A.qel*15);
	}else{
		if ((A.qel<=260)){//antes decía 26, no le pongo restriccion, por eso le pongo un cero=260
			if((A.prenez==90)||(A.prenez==100)){//era 9 y 10, les agrego 0 porque no me funciona y no quiero que se sequen
				if(A.qel!=0){
					if(probab_exito(P_secado_m5) == 1){ //tuvo exito
						A.qel +=1;
						A.saludAntSecado=A.salud;
						A.del = 0;
					}else{
						A.qel+=1;
						A.del = (A.qel*15);
					}
				}
			}else if((A.prenez==11)||(A.prenez==12)){
				if(A.qel!=0){
					if(probab_exito(P_secado_m6) == 1){ //tuvo exito
						A.qel +=1;
						A.saludAntSecado=A.salud;
						A.del = 0;
					}else{
						A.qel+=1;
						A.del = (A.qel*15);
					}
				}
			}else if((A.prenez==13)||(A.prenez==14)){
				if(A.qel!=0){
					if(probab_exito(P_secado_m6) == 1){ //tuvo exito //antes decia m7, cambio a m6
						A.qel += 1;
						A.saludAntSecado=A.salud;
						A.del = 0;
					}else{
						A.qel+=1;
						A.del = (A.qel*15);
					}
				}
			}else if((A.prenez==15)){//se secan acá todas
				if(A.qel!=0){
					if(probab_exito(P_secado_m7) == 1){ //tuvo exito
						A.qel +=1;
						A.saludAntSecado=A.salud;
						A.del = 0;
					}else{
						A.qel+=1;
						A.del = (A.qel*15);
					}
				}
			}else if((A.prenez==16) || (A.prenez==17) || (A.prenez==18)){
				A.qel +=1;
				A.saludAntSecado=A.salud;
				A.del = 0;
		}else{
			A.qel+=1;
			A.del = (A.qel*15);
		}
	}
		else if((A.prenez<=18)){
				A.qel +=1;
				A.saludAntSecado=A.salud;
				A.del = 0;
		}else{
			A.qel+=1;
			A.del = (A.qel*15);
		}

	}
	return A;
}

vaca actualizar_categoria_preniez (vaca A){
	if (A.prenez >=1){
		A.pv=pv_prenada;
	}else{
		A.pv=pv_vacia;
	}
	return A;
}

vaca actualizar_categoria_sl (vaca A){
	if (A.del >=1){
		A.sl=sl_lactancia;
	}else{
		A.sl=sl_seca;
	}
	return A;
}

vaca actualizar_descarte (vaca A){
	if(A.prenez==-5){
		A.descarte=descarte_aborto;
	} else{
		if (A.qel - A.prenez >=MesesDeEspera){
			if(A.partos==MaximoNop) A.descarte=descarte_vejez;
			else A.descarte=descarte_infertilidad;
		}else{
			/*int aux=probab_exito(P_descarte);
			if(aux==1){
			A.descarte=descarte_muerta;
		}*/
			float probMuerte=0;
			if(A.sl==1){
				if(A.partos==vaquillona){
					probMuerte=(0.000000002*pow(A.del,3) - 0.0000003*pow(A.del,2) - 0.00001 * A.del + 0.0112)/2.0;
				}else if((A.partos==2)||(A.partos==3)||(A.partos==4)){ //Vaca
					probMuerte=(0.0000000009*pow(A.del,3) + 0.0000007*pow(A.del,2) - 0.0002 * A.del + 0.0183)/2.0;
				}else{
					probMuerte=(0.0000000002*pow(A.del,3) + 0.000001*pow(A.del,2) - 0.0003 * A.del + 0.0266)/2.0;
				}
			}else{ //secas
				probMuerte=0;//0.091-0.007*A.partos+0.006*pow(A.partos,2);
			}
			int aux=probab_exito(probMuerte);
			if(aux==1){
				A.descarte=descarte_muerta;
			}else{
				if(A.cantTotalMSC==cant_total_msc){
					A.descarte=descarte_msc;
				}
				if(A.cantTotalMC==cant_total_mc) A.descarte=descarte_mc;
			}
		}
	}
	return A;
}

vaca actualizar_prod_dia_mes (vaca A,char nombreArch[30]){
	float b0;
	float b1;
	float b2;
	cargarParametros(A.partos, A.merito, &b0,&b1,&b2,nombreArch);
	float litrosDiarios=wood(b0,b1,b2, A.del);
	A.producdiaria=litrosDiarios;
	A.produc=(litrosDiarios*15);
	return A;
}

vaca actualizar_salud_EColi_Houben (vaca A){ //houben actualizar_salud
	if(A.producdiaria>0){
		float b0,b1,b2,b3,b4,b5,b6;
		cargarParametrosDeHouben(A.qel, A.partos, A.merito, A.nroCuartMCLactPrevia, A.nroCuartMCLactActual, A.salud, &b0, &b1, &b2, &b3, &b4, &b5, &b6);
		unsigned int nuevaSalud=houben ( b0,  b1,  b2, b3,  b4,  b5, b6, 2);
		unsigned int saludAnt=A.salud;
		A.saludPat_EColi=nuevaSalud;
		if(saludAnt!=nuevaSalud){  //Caso de pase de 1 o 3 a salud 2
			if(saludAnt!=salud_mc && nuevaSalud==salud_mc){
				A.sir=2;
				A.mesEnf=1;
				A.cantMC=A.cantMC+1;
			}
		}else{ //salud =anterior analizar caso desp mes 9 de pre�ez
			if(nuevaSalud==salud_mc && A.prenez==-3){
				A.sir=2;
				A.mesEnf=1;
				A.cantMC=1;
			}
		}
  }
	return A;
}

vaca actualizar_perdida_mc (vaca A, int semilla){
	// printf("Inicio actualizar_perdida_mc\n");
	float resultado=0;
	float Efic_Conv=0.59;//0.65:LA;//0.52:LB//default:0.59;para costo alimento=0,19$/kg//1;//0.59;//0.625;//070;//0.59;//1;//0.59;//1;//0.59;//para litro leche=0.28 y kg alim=0,175//0.64;//para ajustar menor consumo por la leche no producida: sólo para MSC y perd x MC durante curva. no incluye dias retiro
	if (A.sir==salud_mc){// && A.salud !=3){ //Perdida por MC   meli mete garra 29 mayo 2019
		if(A.sl==1){  // -3 a 14
			if(A.salud !=3){// int cantMesesFaltan=9-7-A.prenez;
				if(A.cantMC==1){ //Tabla de GROHN 2004
				//Dif x patogeno Aureus o Coli
				// primer caso realizado c los datos de aureus
				if(A.partos==vaquillona){
					if(A.mesEnf==1) resultado= (distNormal_pert(semilla,3.89,6.49,9.12) * (15-DiasRetiro)*Efic_Conv) + (A.producdiaria*DiasRetiro);//53.2+(A.producdiaria*DiasRetiro);
					else if(A.mesEnf==2) resultado= (distNormal_pert(semilla,22.61,63.9,105.32)*Efic_Conv);//31.5;
					else if(A.mesEnf==3) resultado=(distNormal_pert(semilla,11.31,53.07,95.20)*Efic_Conv);//21.7;
					else if(A.mesEnf==4) resultado=(distNormal_pert(semilla,6.55,48.43,89.85)*Efic_Conv);//18.2;
					else resultado=(19.6*Efic_Conv);//19.6; Dato de bar
				} else{ //Vaca
					if(A.mesEnf==1) resultado= (distNormal_pert(semilla,1.82,3.62,5.43) * (15-DiasRetiro) *Efic_Conv) + (A.producdiaria*DiasRetiro);//75.6+(A.producdiaria*DiasRetiro);
					else if(A.mesEnf==2) resultado=(distNormal_pert(semilla,11.9,41.06,70.21) *Efic_Conv);//43.4;
					else if(A.mesEnf==3) resultado=(distNormal_pert(semilla,16.66,48.43,79.73)*Efic_Conv);//24.5;
					else if(A.mesEnf==4) resultado=(11.9*Efic_Conv);	  // Dato de bar 2007
					else resultado=9.8; // Dato de bar 2007
				}
				//Fin de diff
			} else if(A.cantMC==2){ //Tabla de BAR 2007
				if(A.partos==vaquillona){
					if(A.mesEnf==1) resultado= (4.8 * (15-DiasRetiro) *Efic_Conv)+ (A.producdiaria*DiasRetiro);//72.1+(A.producdiaria*DiasRetiro);
					else if(A.mesEnf==2) resultado=(37.8*Efic_Conv);
					else if(A.mesEnf==3) resultado=(32.9*Efic_Conv);
					else if(A.mesEnf==4) resultado=(17.5*Efic_Conv);
					else              resultado=(1.4*Efic_Conv);
				} else{ //Vaca
					if(A.mesEnf==1) resultado= (5.4 * (15-DiasRetiro)*Efic_Conv) + (A.producdiaria*DiasRetiro);//80.5+(A.producdiaria*DiasRetiro);
					else if(A.mesEnf==2) resultado=(41.3*Efic_Conv);
					else if(A.mesEnf==3) resultado=(16.1*Efic_Conv);
					else if(A.mesEnf==4) resultado=(2.8*Efic_Conv);
					else              resultado=(4.2*Efic_Conv);
				}
			} else {  //Tabla de BAR 2007
				if(A.partos==vaquillona){
					if(A.mesEnf==1) resultado= (2.2 * (15-DiasRetiro) *Efic_Conv)+ (A.producdiaria*DiasRetiro);//33.6+(A.producdiaria*DiasRetiro);
					else if(A.mesEnf==2) resultado=(11.2*Efic_Conv);
					else if(A.mesEnf==3) resultado=(8.4*Efic_Conv);
					else if(A.mesEnf==4) resultado=(18.2*Efic_Conv);
					else              resultado=(14*Efic_Conv);
				} else{ //Vaca
					if(A.mesEnf==1) resultado= (4.2 * (15-DiasRetiro)*Efic_Conv) + (A.producdiaria*DiasRetiro);//63+(A.producdiaria*DiasRetiro);
					else if(A.mesEnf==2) resultado=(35.7*Efic_Conv);
					else if(A.mesEnf==3) resultado=(16.1*Efic_Conv);
					else if(A.mesEnf==4) resultado=(4.9*Efic_Conv);
					else              resultado=(1*Efic_Conv); //Valor inventado
				}
			}
			}
else{
			resultado=0;//meli (cambio lineas 1233 y 1282 - 29/05/2019)
}
		}else{

			A.sir=1;
		}
		//A.resultPerdidaMSC=0; //mari 2019 queda comentado

		A.resultPerdidaMC=resultado;
		A.mesEnf++;
	}
if (A.sl==1){//else{//si quiero no tener perd MS, activo lo comentado y saco el if....Mari 2019
		//Perdida por msc durr
		if(A.salud==salud_msc){ //Las vacas con recuentos menores a 200 no tienen perdidas
			unsigned int del=A.del;
			float coef;
			if(A.partos==vaquillona){
				if(del<=0) coef=0;
				else if(del<=15) coef=0.475;
				else if(del<=30) coef=0.43;
				else if(del<=45) coef=0.40;
				else if(del<=60) coef=0.38;
				else if(del<=75) coef=0.36;
				else if(del<=90) coef=0.35;
				else if(del<=105) coef=0.34;
				else if(del<=120) coef=0.34;
				else if(del<=135) coef=0.33;
				else if(del<=150) coef=0.33;
				else if(del<=165) coef=0.34;
				else if(del<=180) coef=0.35;
				else if(del<=195) coef=0.36;
				else if(del<=210) coef=0.38;
				else if(del<=225) coef=0.40;
				else if(del<=240) coef=0.42;
				else if(del<=255) coef=0.45;
				else if(del<=270) coef=0.48;
				else              coef=0.52;
			}else{  //Vaca
				if(del<=0) coef=0;
				else if(del<=15) coef=0.86;
				else if(del<=30) coef=0.80;
				else if(del<=45) coef=0.78;
				else if(del<=60) coef=0.76;
				else if(del<=75) coef=0.76;
				else if(del<=90) coef=0.76;
				else if(del<=105) coef=0.78;
				else if(del<=120) coef=0.81;
				else if(del<=135) coef=0.84;
				else if(del<=150) coef=0.89;
				else if(del<=165) coef=0.95;
				else if(del<=180) coef=1.02;
				else if(del<=195) coef=1.1;
				else if(del<=210) coef=1.19;
				else if(del<=225) coef=1.29;
				else if(del<=240) coef=1.4;
				else if(del<=255) coef=1.52;
				else if(del<=270) coef=1.66;
				else              coef=1.8;
			}
			float DML= ((log(A.rcs)-2)*coef)*15;
			if(0.0<DML){
				int a=generarAleatorio(90,110);
				A.resultPerdidaMSC=(DML*((float)a/(float)100)*Efic_Conv);//ver meli
			}
			else
			A.resultPerdidaMSC=0;
		}else{
			A.resultPerdidaMSC=0;
		}
	}else{ //sl==2; mari 2019
		A.resultPerdidaMSC=0;//mari 2019
}
//	printf("Fin actualizar_perdida_mc\n");
	return A;
}


vaca generarNuevaVaca(int id,char patog[]){
	//Mod si agrego parametros a la vaca
	vaca v;
	v.del = 0;
	v.descarte = descarte_rodeo;
	v.id = id;
	v.qel = 0;
	v.merito =generarAleatorio(1,3);
	v.orden = id;
	v.partos = 0;
	v.prenez = 18; // Las vacas que ingresan nuevas siempre estan por parir //generarAleatorio(12,18); // Esto puede variar
	v.produc = 0;
	v.producdiaria = 0;
	v.pv = pv_prenada;
	v.sl = sl_seca;
	//Analisis de q enferme HACERRRR

	/*si salud es  mc msc sana
	si esta enferma sele asigna la salud al patog se asigna el patog a la vaca
	se asigna el estado de salud de patog a la salud de la vaca.*/

	//falta v.saludAnt

	v.saludPat_SAgalactiae=salud_sana;
	v.saludPat_SCN=salud_sana;
	v.saludPat_OtrosStrepto=salud_sana;
	v.saludPat_Otros=salud_sana;
	if(patog=="coli"){
		v.saludPat_EColi = generarAleatorio(1,3); //1sana 2 mc 3 msc - hacer probabilidad
		if(v.saludPat_EColi==salud_mc || v.saludPat_EColi==salud_msc){
			v.patogeno=EColi;
			v.salud=v.saludPat_EColi;
		}else{
			v.patogeno=0;
			v.salud = salud_sana;
		}
	}else{
		v.saludPat_EColi=salud_sana;
	}

	if(patog=="aureus"){
		v.saludPat_SAureus =salud_sana;//generarAleatorio(1,3); //1sana 2 mc 3 msc - hacer probabilidad
		if(v.saludPat_SAureus==salud_mc || v.saludPat_SAureus==salud_msc){
			v.patogeno=SAureus;
			v.salud=v.saludPat_SAureus;
		}else{
			v.patogeno=0;
			v.salud = salud_sana;
		}
	}else{
		v.saludPat_SAureus=salud_sana;
	}
	v.saludAntSecado=v.salud;
	v.rcs = 0;
	v.sir=1;
	v.resultPerdidaMC=0;
	v.resultPerdidaMSC=0;
	v.infGral=1;
	v.infMC=1;
	v.infMSC=1;
	return v;
}
	/*********** Fin Calculos Estimacion ***********/

void agregarAnimal() {
	unsigned int indice;
	unsigned int indiceResp;
	unsigned int cant_partos;
	unsigned int est_prenez=0;
	int mes_prenez;
	unsigned int est_lactancia=0;
	int mes_lactancia;
	float prod_diaria;
	float prod_mensual;
	unsigned int merito=0;
	unsigned int sir=1;
	unsigned int salud=0;
	unsigned int descarte=0;
	unsigned int rcs;

	printf("\n --> Ingrese el orden del animal: ");
	scanf("%d",&indice);
	printf("\n --> Ingrese el id del animal: ");
	scanf("%d",&indiceResp);
	printf("\n --> Ingrese la cantidad de partos: ");
	scanf("%d",&cant_partos);
	while(est_prenez!=1 && est_prenez!=2){
		printf("\n --> Ingrese el estado de pre�ez (1=pre�ada; 2=vacia): ");
		scanf("%d",&est_prenez);
		if(est_prenez!=1 && est_prenez!=2)
			printf("\n       El numero ingresado no es correcto (1=pre�ada; 2=vacia)\n");
	}
	printf("\n --> Ingrese el mes de pre�ez: -2 a 9: ");
	scanf("%d",&mes_prenez);

	while(est_lactancia!=1 && est_lactancia!=2){
		printf("\n --> Ingrese el estado de lactancia (1= lactancia; 2=seca): ");
		scanf("%d",&est_lactancia);
		if(est_lactancia!=1 && est_lactancia!=2)
			printf("\n       El numero ingresado no es correcto (1= lactancia; 2=seca)\n");
	}

	printf("\n --> Ingrese el mes de lactancia: ");
	scanf("%d",&mes_lactancia);
	while(merito<1 || merito>3){
		printf("\n --> Ingrese el orddescarteen de merito (1=bajo; 2=medio y 3=mayor): ");
		scanf("%d",&merito);
		if(merito<1 || merito>3)
			printf("\n       El numero ingresado no es correcto (1=bajo; 2=medio y 3=mayor)\n");
	}
	while(salud!=1 && salud!=2){
		printf("\n --> Ingrese el estado de salud (1=sana; 2=mastitis clinica): ");
		scanf("%d",&salud);
		if(salud!=1 && salud!=2)
			printf("\n       El numero ingresado no es correcto (1=sana; 2=mastitis clinica)\n");
	}
	while(descarte!=1 && descarte!=2){
		printf("\n --> Ingrese el estado de descarte (1=sigue; 2=descarta): ");
		scanf("%d",&descarte);
		if(descarte!=1 && descarte!=2)
			printf("\n       El numero ingresado no es correcto (1=sigue; 2=descarta)\n");
	}
	printf("\n --> Ingrese el recuento de celulas somaticas RCS: ");
	scanf("%d",&rcs);

	FILE *archivo;
	char nombre[30];
	fprintf(stdout,"\n --> Nombre del archivo de datos ");
	scanf("%s",nombre);
	char strIng[30];
	strcpy(strIng,"./ArchivosTambo/");
	strcat(strIng, nombre);
	archivo=fopen(strIng,"a");
	unsigned int dia_lactancia=(mes_lactancia*30);

	float b0;
	float b1;
	float b2;
	cargarParametros(cant_partos,merito, &b0,&b1,&b2,nombre);
	prod_diaria=wood(b0,b1,b2, dia_lactancia);
	prod_mensual=(prod_diaria*30);
	fprintf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%.2f;%.2f;%d;%d;%d;%d;%d;%d;%d;%d\n",indice,indiceResp,cant_partos,est_prenez,mes_prenez,est_lactancia,dia_lactancia,mes_lactancia,prod_diaria,prod_mensual,merito,sir,salud,descarte,rcs,0,0,0);
	fclose(archivo);
}

	/************ Calculos Wood ************/
float wood (float b0, float b1, float b2, int del){
	return (b0*pow(del,b1)*exp(-b2*del));
}

void cargarParametros(int nop, int merito, float *b0, float *b1, float *b2,char nombreArch[30]){
	FILE *param;
	float valores_param[4];
	char nombre[32];
	if(nop<=1){ //Caso Vaquillona
		char *nom="_parametrosProdDiariaVaqs.txt";
		strcpy(nombre, nom);
	}else{ //Caso Vaca
		char *nom="_parametrosProdDiariaVacas.txt";
		strcpy(nombre, nom);
	}
	param = fopen(nombre, "r");
	if (param == NULL) {
		calcularParamCurvaLact(nombreArch);
		param = fopen(nombre, "r");
	}
	float valor;
	unsigned int i=0;
	while (EOF != fscanf(param,"%f",&valor)){
		valores_param[i]=valor;
		i++;
	};
	fclose(param);
	//  printf("Valores de los parametros 1 %f 2 %f 3 %f\n",valores_param[0],valores_param[1],valores_param[2]);
	if(merito==1){
		*b0=valores_param[0];
		*b1=valores_param[1];
		*b2=valores_param[2];
	} else if(merito==2){
		*b0=valores_param[0];
		*b1=valores_param[1];
		*b2=valores_param[2];
	} else if(merito==3){
		*b0=valores_param[0];
		*b1=valores_param[1];
		*b2=valores_param[2];
	}   //los parametros no tienen variacion respecto al merito
}
	/************ Fin Calculos Wood ************/

	/************ Calculos Houben ************/
void iniciarParamHouben(float *pexpos,float *drni,float *lt,float *propsub,float *spon){
	*pexpos=0.03;//(float)(10.0/generarAleatorio(11,99));
	*drni=(float)(10.0/generarAleatorio(11,99));
	*lt=0;//(float)(10.0/generarAleatorio(11,99));
	*propsub=0.2;//(float)(10.0/generarAleatorio(11,99));
	*spon=(float)(10.0/generarAleatorio(11,99));
}

int houben (float b0, float b1, float b2,float b3, float b4, float b5,float b6, int salud){
	float sumParam=b0+b1+b2+b3+b4+b5+b6;
	float subform=(exp(sumParam)/(1+exp(sumParam)));
	float lim_clinica= 0;
	float lim_subclinica= 0;
	float pexpos;
	float drni;
	float lt;
	float propsub;
	float spon;
	iniciarParamHouben(&pexpos,&drni,&lt,&propsub,&spon);
	if(salud==salud_sana){ //sana
		lim_clinica= pexpos * subform * (1-drni);
		lim_subclinica= pexpos * (1 - lim_clinica) * (1-drni);
	}
	if(salud==salud_mc){  //clinica
		lim_clinica= subform * (1-lt);
		lim_subclinica= (1 - lim_clinica) * propsub;
	}
	if(salud==salud_msc){  //subclinica
		lim_clinica= subform;
		lim_subclinica= (1 - lim_clinica) * spon;
	}
	//Sana-clinica-subclinica
	float lim_sana= 1 - lim_subclinica - lim_clinica;
	/* printf("\n --> sana: %f ",lim_sana);
	printf("\n --> clinica: %f ",lim_clinica);
	printf("\n --> subclinica: %f ",lim_subclinica); */

	//Valor de retorno 1=sana 2=MC 3=Msc
	unsigned int max=RAND_MAX;
	unsigned int lim_s=RAND_MAX*lim_sana;
	unsigned int lim_c=RAND_MAX*(lim_sana+lim_clinica);
	unsigned int aleat=rand();
	if (aleat <=lim_s)
		return 1; /* sana */
	else if(aleat <=lim_c)
		return 2; /* mc */
	else   /*msc*/
		return 3;
}

void cargarParametrosDeHouben(int lactancia, int nop, int merito, int nCuartInfPrevio, int nCuartInfActual, int salud, float *b0, float *b1, float *b2, float *b3, float *b4, float *b5, float *b6){
	if(lactancia==0){
		*b0=0;
		*b1=0;
		*b2=0;
		*b3=0;
		*b4=0;
		*b5=0;
		*b6=0;
	}else if((lactancia==1)||(lactancia==2)||(lactancia==3)||(lactancia==4)){
		*b0=-2.2713;
		*b1=0;
		*b2=0;
		*b3=0;
		*b4=0;
		*b5=0;
		if(salud==2)    *b6=0.7751;
		else            *b6=-0.7751;
		if(nop>1){ //Caso Vaca
			if(nCuartInfPrevio==0)          *b4=-0.5995;
			if(nCuartInfPrevio==1)          *b4=0.1548;
			if(nCuartInfPrevio==2)          *b4=0.1037;
			if(nCuartInfPrevio>=3)          *b4=0.3410;
		}
	}else{//>2
		*b0=-2.4239;
		//Calculo b1 con lactancia
		if((lactancia==5)||(lactancia==6)||(lactancia==7)||(lactancia==8))          *b1=0.7495;
		if((lactancia==9)||(lactancia==10)||(lactancia==11)||(lactancia==12))          *b1=0.5333;
		if((lactancia==13)||(lactancia==14)||(lactancia==15)||(lactancia==16))          *b1=0.3082;
		if((lactancia==17)||(lactancia==18)||(lactancia==19)||(lactancia==20))          *b1=0.0509;
		if((lactancia==21)||(lactancia==22)||(lactancia==23)||(lactancia==24))          *b1=0.1390;
		if((lactancia==25)||(lactancia==26)||(lactancia==27)||(lactancia==28))          *b1=-0.0837;
		if((lactancia==29)||(lactancia==30)||(lactancia==31)||(lactancia==32))          *b1=-0.5127;
		if((lactancia==33)||(lactancia==34)||(lactancia==35)||(lactancia==36))          *b1=-0.5131;
		if((lactancia>=37))     *b1=-0.6714;

		//Calculo b2 con nop
		if(nop==1)          *b2=-0.5370;
		if(nop==2)          *b2=-0.0359;
		if(nop==3)          *b2=0.0788;
		if(nop==4)          *b2=0.0825;
		if(nop>=5)          *b2=0.4116;

		//Calculo b3 con merito
		if(merito==1)          *b3=-0.4979;
		if(merito==2)          *b3=0.0349;
		if(merito==3)          *b3=0.4630;

		//Calculo b4 con nCuartInfPrevio
		if(nCuartInfPrevio==0)          *b4=-0.6722;
		if(nCuartInfPrevio==1)          *b4=0.0042;
		if(nCuartInfPrevio==2)          *b4=0.2705;
		if(nCuartInfPrevio>=3)          *b4=0.3975;

		//Calculo b5 con nCuartInfActual
		if(nCuartInfActual==0)          *b5=-0.6349;
		if(nCuartInfActual==1)          *b5=0.0218;
		if(nCuartInfActual==2)          *b5=0.3189;
		if(nCuartInfActual>=3)          *b5=0.2942;

		if(salud==salud_mc)    	*b6=0.7814;
		else            		*b6=-0.7814;
	}
}
	/************ Fin Calculos Houben ************/

/*******************************************************************************************************/
int main(){
	unsigned int opcion=0;
	char continuar;
	int it = MAX_QUINCENA;
	while(opcion!=4){
		printf("\n\n");
		printf("------------------------------------------------------------------------------\n");
		printf("|       MENU PRINCIPAL                                                       |\n");
		printf("|                                                                            |\n");
		printf("|        1 - ESTIMACION                                                      |\n");
		printf("|        2 - AGREGAR ANIMAL                                                  |\n");
		printf("|        3 - ESTADISTICAS DE LA ESTIMACION                                   |\n");
		printf("|        4 - SALIR                                                           |\n");
		printf("------------------------------------------------------------------------------\n");
		printf("\n --> Seleccione un numero de opcion: ");
		scanf("%d",&opcion);
		if(opcion==1){
			printf("\n\t ESTIMACION\n\n");
			char nombre[30];
			fprintf(stdout,"Nombre del archivo de datos CSV "); /*Solicita al usr el nombre del archivo de datos*/
			scanf("%s",nombre);
			char *aureus_ss = "_estimacion_aureus_sinsecado.csv";
			char *aureus_csrp = "_estimacion_aureus_consecadorp.csv";
			char *aureus_cs = "_estimacion_aureus_consecado_sinrp.csv";
			char *coli = "_estimacion_coli.csv";
			//Prob: Sana, Aureus, Agalactiae, Scn,Otros,OtrosEstrepto,eColi,Otros
			float probaMCAureus[7]={0.997,0.003,0,0,0,0,0};//{0.68,0.32,0,0,0,0,0};//cambio mayo 2022 -prev inicial MC aureus=0.0028=0.003
			float probaMSCAureus[7]={0.79,0.21,0,0,0,0,0};
			float probaMCColi[7]={0.915,0,0,0,0,0.085,0};
			float probaMSCColi[7]={0.979,0,0,0,0,0.021,0};

			printf("\n --> Seleccione tipo de estimacion para los primeros anios(0-DEFECTO 1-PMTD 2-DCT 3-CMO 4-PMC 5-COMPLETO 6-7-8-9): ");
			scanf("%d",&opcionTipoEst);

			printf("\n --> Seleccione tipo de descarte de la primer estimacion(0-Sin descarte 1-Con descarte 4MC 12MSC 2-Otros valores de descarte): ");
			scanf("%d",&opcionDescarte1);

			if(opcionDescarte1==2){
				printf("\n --> Ingrese descarte para MC: ");
				scanf("%d",&opcionDescarte1MC);
				printf("\n --> Ingrese descarte para MSC: ");
				scanf("%d",&opcionDescarte1MSC);
			}

			int anioLim=indice24((MAX_QUINCENA+1),1);
			printf("\n --> Ingrese el anio limite para el primer tipo de estimacion(0 ... %d): ",anioLim);
			scanf("%d",&opcionAnioCorte);

			printf("\n --> Seleccione tipo de estimacion para los anios siguientes(0-DEFECTO 1-PMTD 2-DCT 3-CMO 4-TMC 5-COMPLETO 6-7-8-9): ");
			scanf("%d",&opcionTipoEstSeg);

			printf("\n --> Seleccione tipo de descarte de la segunda estimacion(0-Sin descarte 1-Con descarte 4MC 12MSC 2-Otros valores de descarte): ");
			scanf("%d",&opcionDescarte2);

			if(opcionDescarte2==2){
				printf("\n --> Ingrese descarte para MC: ");
				scanf("%d",&opcionDescarte2MC);
				printf("\n --> Ingrese descarte para MSC: ");
				scanf("%d",&opcionDescarte2MSC);
			}

			int opcionEject=0;
			printf("\n --> Desea ejecutar estimacion sin secado (1-SI 2-NO): ");
			scanf("%d",&opcionEject);
			if(opcionEject==1)
			  estimacion(nombre,aureus_ss,probaMCAureus,probaMSCAureus,probaMSCAureus,"aureus",Ejec_sinsecado);
			printf("\n --> Desea ejecutar estimacion con secado rp (1-SI 2-NO): ");
			scanf("%d",&opcionEject);
			if(opcionEject==1)
			  estimacion(nombre,aureus_csrp,probaMCAureus,probaMSCAureus,probaMSCAureus,"aureus",Ejec_consecado_rp);
			printf("\n --> Desea ejecutar estimacion con secado sin rp (1-SI 2-NO): ");
			scanf("%d",&opcionEject);
			if(opcionEject==1)
			  estimacion(nombre,aureus_cs,probaMCAureus,probaMSCAureus,probaMSCAureus,"aureus",Ejec_consecado_sinrp);
			//    estimacion(nombre,coli,probaMCColi,probaMSCColi,probaMSCColi,"coli");
			printf("\n --> Pulse Enter para continuar ");
			scanf("%c",&continuar);
			getchar();
		}
		if(opcion==2){
			printf("\n\t AGREGAR ANIMAL\n");
			agregarAnimal();
			printf("\n --> Pulse Enter para continuar ");
			scanf("%c",&continuar);
			getchar();
		}
		if(opcion==3){
			printf("\n\t ESTADISTICAS DE LA ESTIMACION\n");
			estadisticasEstimacion();

			printf("\n --> Pulse Enter para continuar ");
			scanf("%c",&continuar);
			getchar();
		}
	}
	return 0;
}
