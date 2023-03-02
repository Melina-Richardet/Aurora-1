#include <stdio.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include "estadisticas_lactancia.c"



// Los calculos de estadisticas de este archivo son por quincena.
float costoLitro(int rcs){
	if(rcs<25)  	return (float)0.465;
	else if(rcs<50)  	return (float)0.458;
	else if(rcs<75)  	return (float)0.449;
	else if(rcs<100)  	return (float)0.436;
	else if(rcs<150)  	return (float)0.413;
	else if(rcs<200)  	return (float)0.384;
	return (float)0.325;
}

void calcularVacasEnLactanciaYSecas_PreniadasYVacias_DescarteYMuertas(char nombre[40],int ejecuciones, int it){
    printf("\nLACTANCIA VS SECAS - PRENIADAS VS VACIAS - EN RODEO, DESCARTE Y MUERTAS\n");
    FILE *archivo=fopen(nombre,"r");
    int ejec=0,mes=0,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt,anio;
    int salAnt;
	unsigned int nop,infGral,infMC,infMSC;
	int prenez,qel;
    int i,j;
    unsigned int cantLSxMes[ejecuciones][it][2];	 memset(cantLSxMes, 0, sizeof(cantLSxMes)); //Lactancia-0 //Secas-1
    int cantPVxMes[ejecuciones][it][2];				 memset(cantPVxMes, 0, sizeof(cantPVxMes)); //Pre�adas-0 //Vacias-1
    int cantRDMxMes[ejecuciones][it][5];   			 memset(cantRDMxMes, 0, sizeof(cantRDMxMes)); //Rodeo-0 //Descarte - Infertilidad-1 //Muertas -2 //Aborto-3 //Vejez-4
    int esc=-1;
    char line[1024];
    fgets(line, sizeof(line), archivo);

    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
              &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
    /* sl 1= en lactancia; 2= seca*/
        cantLSxMes[(ejec)][(mes)][(sl-1)]= cantLSxMes[(ejec)][(mes)][(sl-1)]+1;//Lactancia vs secas
        cantPVxMes[(ejec)][(mes)][(pv-1)]= cantPVxMes[(ejec)][(mes)][(pv-1)]+1;//Preniadas vs vacias
        cantRDMxMes[(ejec)][(mes)][(descarte-1)]= cantRDMxMes[(ejec)][(mes)][(descarte-1)]+1;//Rodeo descarte y muertas
    }

   // printf(" Ejec\tMes\tLact.\tSecas\tPren.\tVacias\tRodeo\tInfer.\tAbortadas\tViejas\tMuertas\tDesc. Total\n");

    FILE *datosGrafico=fopen(rutaArchivo(carp,1,"tablaQuinc_EvolucionRodeo.csv"),"w+");
   // FILE *datosGrafico=fopen("./ArchivosTambo/datos/tablaQuinc_EvolucionRodeo.csv","w+");
    fprintf(datosGrafico,"Ejec;Mes;Lactancia;;Preniadas;;Infertilidad;Abortadas;Viejas;Muertas;Descarte Total\n");

    FILE *datosGraficoLact=fopen(rutaArchivo(carp,1,"quinc_EvolucionLactancia"),"w");
    FILE *datosGraficoPren=fopen(rutaArchivo(carp,1,"quinc_EvolucionPreniadas"),"w");
    FILE *datosGraficoDescInf=fopen(rutaArchivo(carp,1,"quinc_EvolucionDescarteInf"),"w");
	FILE *datosGraficoDescAbo=fopen(rutaArchivo(carp,1,"quinc_EvolucionDescarteAbo"),"w");
	FILE *datosGraficoDescVie=fopen(rutaArchivo(carp,1,"quinc_EvolucionDescarteVie"),"w");
	FILE *datosGraficoDescMue=fopen(rutaArchivo(carp,1,"quinc_EvolucionDescarteMue"),"w");
    //omitimos quincena 0 por no tener datos
    for(i=1;i<it;i++){
		float calculosLact[ejecuciones];
		float calculosPren[ejecuciones];
		float calculosDInf[ejecuciones];
		float calculosDAbo[ejecuciones];
		float calculosDVie[ejecuciones];
		float calculosDMue[ejecuciones];

		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices por eso empiezo el ciclo en 1.
	    for(j=1;j<ejecuciones;j++){
	        int totVacas= cantLSxMes[j][i][0]+cantLSxMes[j][i][1];
	        float porcLact= (float)cantLSxMes[j][i][0]/(float)totVacas;
	        calculosLact[j]=porcLact;

	        int totVacas2= cantPVxMes[j][i][0]+cantPVxMes[j][i][1];
	        float porcPre= (float)cantPVxMes[j][i][0]/(float)totVacas2;
	        calculosPren[j]=porcPre;

	        int totVacas3= cantRDMxMes[j][i][0]+cantRDMxMes[j][i][1]+cantRDMxMes[j][i][2]+cantRDMxMes[j][i][3]+cantRDMxMes[j][i][4];
	        float porcInf= (float)cantRDMxMes[j][i][1]/(float)totVacas3;
	        float porcMue= (float)cantRDMxMes[j][i][2]/(float)totVacas3;
	        float porcAbo= (float)cantRDMxMes[j][i][3]/(float)totVacas3;
	        float porcVie= (float)cantRDMxMes[j][i][4]/(float)totVacas3;
	        float porcDescTot= (porcInf + porcMue + porcAbo + porcVie)*100;
			calculosDInf[j]=porcInf;
			calculosDMue[j]=porcMue;
			calculosDAbo[j]=porcAbo;
			calculosDVie[j]=porcVie;
	      //  printf("  %d\t %d\t %.3f\t %.3f\t %.3f\t %.3f\t %.3f\t %.3f\t %.3f\t\n",(j),(i),porcLact,porcPre,porcInf,porcAbo,porcVie,porcMue,porcDescTot);
	       fprintf(datosGrafico,"%d;%d;%.3f;;%.3f;;%.3f;%.3f;%.3f;%.3f;%.3f\n",(j),(i),porcLact,porcPre,porcInf,porcAbo,porcVie,porcMue,porcDescTot);
	      //  fprintf(datosGrafico,"%d  \t %.2f  \t %.2f   \t %.2f  \t %.2f  \t %.2f  \t %.2f  \t %.2f  \t %.2f  \t %.2f  \t %.2f\n",(j),porcLact,porcSecas,porcPre,porcVac,porcRod,porcDes,porcAbo,porcVie,porcMue,porcDescTot);
		}
	escribirDatosGrafico(datosGraficoLact,calculosLact,ejecuciones,i);
	escribirDatosGrafico(datosGraficoPren,calculosPren,ejecuciones,i);
	escribirDatosGrafico(datosGraficoDescInf,calculosDInf,ejecuciones,i);
	escribirDatosGrafico(datosGraficoDescMue,calculosDMue,ejecuciones,i);
	escribirDatosGrafico(datosGraficoDescAbo,calculosDAbo,ejecuciones,i);
  escribirDatosGrafico(datosGraficoDescVie,calculosDVie,ejecuciones,i);
	}
    fclose(datosGraficoLact);
    fclose(datosGraficoPren);
    fclose(datosGraficoDescAbo);
    fclose(datosGraficoDescVie);
    fclose(datosGraficoDescInf);
    fclose(datosGraficoDescMue);
    fclose(archivo);
  //crearArchivoHTML(carp,"tablaQuinc_EvolucionRodeo.html",datosGrafico,"Datos Rodeo");
    fclose(datosGrafico);
}

//Resultados en fecha_estadisticas.csv
void calcularVacasEnMesLactancia(char nombre[40],char arch_salida[40], int it, int mesLactMax){
    printf("\nMES DE LACTANCIA\n");
    FILE *archivo=fopen(nombre,"r");
    char line[1024];
    fgets(line, sizeof(line), archivo);
    int ejec=0,mes,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt,anio;
    int salAnt;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel;
    int i,j,k,m;
     int esc=-1;
    int cantLSxMes[it][mesLactMax];  	memset(cantLSxMes, 0, sizeof(cantLSxMes));//1 Iterac 2 posib valores del mes de lactancia
   	//it - iteracion 0 - 36  mesLactMax - mes lactancia 0 - 23

    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
               &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
        cantLSxMes[(mes)][(indiceQel(del))]= cantLSxMes[(mes)][(indiceQel(del))]+1;
    }
    FILE *salida=fopen(arch_salida,"w");
    fprintf(salida,"\nMes It;");
 //   printf("\tMes I");
    for(m=0;m<mesLactMax;m++){
       fprintf(salida,"Mes %d;",m);
     //  printf("\tMes %d ",(m));
    }
    fprintf(salida,"\n");
  //  printf(" \n");
    for(j=0;j<it;j++){
        int totVacas=0;
        for(m=0;m<mesLactMax;m++){
             totVacas += cantLSxMes[j][m];
        }
        fprintf(salida,"%d;",(j));
        //printf("\t %d ",(j));
        for(m=0;m<mesLactMax;m++){
			float porcMes= ((float)cantLSxMes[j][m]*100 )/(float)totVacas;
			fprintf(salida,"%.2f;",porcMes);
		//	printf("\t %.2f ",porcMes);
        }
        fprintf(salida,"\n");
       // printf(" \n");
    }
    fclose(archivo);
    fclose(salida);
}

 void calcularServiciosPorVacaYRodeo(char nombre[40],char arch_salida[40],int ejecuciones){
    printf("\nSERVICIOS POR VACA\n");
    FILE *archivo=fopen(nombre,"r");

    FILE *salida=fopen(arch_salida,"a");
    fprintf(salida,"\nEjec;Id;Servicios\n");
  //  printf("\tEjec\tId\tServicios\n");
     int esc=-1;
	char line[1024];
    fgets(line, sizeof(line), archivo);
    unsigned int cantServxVaca[MaxVacas][3];  //Id-0 //Cant Serv-1 //Cod Descarte-2
    float promServRodeo[ejecuciones];
	promServRodeo[0]=0;
    unsigned int i,j;
    unsigned int tope=1;
    long aaa;
    for(j=1;j<ejecuciones;j++){  //J=0 no existe ejecucion 0
        memset(cantServxVaca, 0, sizeof(cantServxVaca));
    	int ejec=0,mes,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
	    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
	    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt,anio;
	    int salAnt;
	    unsigned int nop,infGral,infMC,infMSC;
	    int prenez,qel;
    	int lim=0;
    	while ((tope==1) && (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
        &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc))){
			if(ejec==j){  //aca levanto solo las vacas de la ejecucion que estoy analizando
				aaa=ftell(archivo);
				if((prenez==0) || (prenez==1)){
					int pos=-1;
					for(i=0;i<lim && (pos==-1);i++){
						if(cantServxVaca[i][0]==id){
							pos=i;
						}
					}
					if(pos!=-1){
						cantServxVaca[pos][1]= cantServxVaca[pos][1]+1;
						if((prenez==0) && (descarte==descarte_infertilidad || descarte==descarte_muerta || descarte==descarte_vejez))
							cantServxVaca[pos][2]=descarte;
					}else{
						cantServxVaca[lim][0]= id;
						cantServxVaca[lim][1]= 1;
						lim++;
						if((prenez==0) && (descarte==descarte_infertilidad || descarte==descarte_muerta || descarte==descarte_vejez))
							cantServxVaca[lim][2]=descarte;
						else
							cantServxVaca[lim][2]=descarte_rodeo;
					}
				}
	    	}else{
	    		tope=0;
		    }
    	}
    	fseek(archivo,aaa,SEEK_SET);
    	tope=1;
    	int servTotales=0;
	    for(i=0;i<lim;i++){
			if(cantServxVaca[i][1]!=0 && cantServxVaca[i][2]==descarte_rodeo){
				fprintf(salida,"%d;%d;%d\n",j,cantServxVaca[i][0],cantServxVaca[i][1]);
			//	printf("\t %d\t %d\t %d\n",j,cantServxVaca[i][0],cantServxVaca[i][1]);
				servTotales=servTotales+cantServxVaca[i][1];
			}
	    }
		promServRodeo[j] = ( (float)servTotales/(float)lim)/1.5;   //Ver ajuste
	}
    fprintf(salida,"\nEjec;SERVxRODEO\n");
//	printf("\tEjec\tSERVxRODEO\n");
	for(j=1;j<ejecuciones;j++){  //Ej 0 no tiene datos
		fprintf(salida,"%d;%.3f\n",j,promServRodeo[j]);
	//	printf("\t  %d %.3f\n",j,promServRodeo[j]);
	}
	float min, q1, med, q3, max;
	organizarYGenerarDatos(promServRodeo,ejecuciones,&min,&q1,&med,&q3,&max);
	fprintf(salida, "%.3f;%.3f;%.3f;%.3f;%.3f\n",min,q1,med,q3,max);
//	printf("%.3f \t %.3f \t %.3f \t %.3f \t %.3f \t \n",min,q1,med,q3,max);
    fclose(archivo);
    fclose(salida);
}

void calcularDatosAnuales(char nombre[40],int ejecuciones, int it){
    printf("\nDATOS ANUALES\n\n");
    FILE *archivo=fopen(nombre,"r");
    char line[1024];
    fgets(line, sizeof(line), archivo);
    int ejec=0,mes,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt;
    int salAnt;
    int anio=-1;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel=1;
    int i,j,k,m;
    int esc=-1;
    int longitud=indice24(it,0);
    float datosAnuales_perdMC[ejecuciones][longitud]; 			memset(datosAnuales_perdMC, 0, sizeof(datosAnuales_perdMC));
	float datosAnuales_perdMSC[ejecuciones][longitud];		 	memset(datosAnuales_perdMSC, 0, sizeof(datosAnuales_perdMSC));
	int datosAnuales_descMC[ejecuciones][longitud]; 			memset(datosAnuales_descMC, 0, sizeof(datosAnuales_descMC));
	int datosAnuales_descMSC[ejecuciones][longitud]; 			memset(datosAnuales_descMSC, 0, sizeof(datosAnuales_descMSC));
	int datosAnuales_preniezMC[ejecuciones][longitud]; 			memset(datosAnuales_preniezMC, 0, sizeof(datosAnuales_preniezMC));
	int datosAnuales_preniezMSC[ejecuciones][longitud]; 		memset(datosAnuales_preniezMSC, 0, sizeof(datosAnuales_preniezMSC));
	int datosAnuales_preniez17[ejecuciones][longitud]; 			memset(datosAnuales_preniez17, 0, sizeof(datosAnuales_preniez17));
	int datosAnuales_saluc_sana[ejecuciones][longitud];			memset(datosAnuales_saluc_sana, 0, sizeof(datosAnuales_saluc_sana));
	int datosAnuales_saluc_mc[ejecuciones][longitud]; 			memset(datosAnuales_saluc_mc, 0, sizeof(datosAnuales_saluc_mc));
    int datosAnuales_saluc_msc[ejecuciones][longitud];  		memset(datosAnuales_saluc_msc, 0, sizeof(datosAnuales_saluc_msc));
    int datosAnuales_prodDiaria_rcs[ejecuciones][longitud];  	memset(datosAnuales_prodDiaria_rcs, 0, sizeof(datosAnuales_prodDiaria_rcs));
    int datosAnuales_prodDiaria[ejecuciones][longitud];  		memset(datosAnuales_prodDiaria, 0, sizeof(datosAnuales_prodDiaria));
    int datosAnuales_bonifTanque[ejecuciones][longitud];  		memset(datosAnuales_bonifTanque, 0, sizeof(datosAnuales_bonifTanque));
    int datosAnuales_bonifTanqueSinMC[ejecuciones][longitud];  	memset(datosAnuales_bonifTanqueSinMC, 0, sizeof(datosAnuales_bonifTanqueSinMC));
    int datosAnuales_sl_lactancia[ejecuciones][longitud];  	    memset(datosAnuales_sl_lactancia, 0, sizeof(datosAnuales_sl_lactancia));
    int datosAnuales_gastos_insumos[ejecuciones][longitud]; 	memset(datosAnuales_gastos_insumos, 0, sizeof(datosAnuales_gastos_insumos));

	int escenarios[longitud];
	memset(escenarios, -1, sizeof(escenarios));
	float cantVacasRodeo=0.0;

		int costoTernero=CostoTerneroMacho*PorcMacho+CostoTerneroHembra*PorcHembra;
		int costoTotalDescarte = PrecioVaq-PrecioVaca-costoTernero;
		float costoMensualDescarte=costoTotalDescarte/((1-(pow((1+tazaInteres),-expectativaVida_Meses)))/tazaInteres);
		printf("costoTernero %d costoTotalDesc %d costoMensual %.2f\n",costoTernero,costoTotalDescarte,costoMensualDescarte);
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
               &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
        if(ejec==1 && mes==1)
	   		cantVacasRodeo=cantVacasRodeo+1.0;
		int ind=indice24(mes,1);
		if(escenarios[ind]==-1){
			escenarios[ind]=esc;
		}
      //  printf("mes %d indice %d",mes , ind);
		datosAnuales_perdMC[ejec][ind]= datosAnuales_perdMC[(ejec)][ind]+resultPerdidaMC;
        datosAnuales_perdMSC[ejec][ind]= datosAnuales_perdMSC[(ejec)][ind]+resultPerdidaMSC;
		if(descarte==descarte_mc)
			datosAnuales_descMC[ejec][ind]= datosAnuales_descMC[(ejec)][ind]+1;
		if(descarte==descarte_msc)
			datosAnuales_descMSC[ejec][ind]= datosAnuales_descMSC[(ejec)][ind]+1;
		if(prenez==(-6))
			datosAnuales_preniezMC[ejec][ind]= datosAnuales_preniezMC[(ejec)][ind]+1;
		if(prenez==(-7))
			datosAnuales_preniezMSC[ejec][ind]= datosAnuales_preniezMSC[(ejec)][ind]+1;
		if(prenez==(17))
			datosAnuales_preniez17[ejec][ind]= datosAnuales_preniez17[(ejec)][ind]+1;
		if(sl==sl_lactancia){
			datosAnuales_sl_lactancia[ejec][ind]= datosAnuales_sl_lactancia[(ejec)][ind]+1;
			if(salud==salud_mc)
				datosAnuales_saluc_mc[ejec][ind]= datosAnuales_saluc_mc[(ejec)][ind]+1;
			if(salud==salud_msc)
				datosAnuales_saluc_msc[ejec][ind]= datosAnuales_saluc_msc[(ejec)][ind]+1;
			if(salud==salud_sana)
				datosAnuales_saluc_sana[ejec][ind]= datosAnuales_saluc_sana[(ejec)][ind]+1;

			float valorBonif=producdiaria*costoLitro(rcs);
			datosAnuales_bonifTanque[ejec][ind]= datosAnuales_bonifTanque[(ejec)][ind]+valorBonif;
			if(salud!=salud_mc)
    		 	datosAnuales_bonifTanqueSinMC[ejec][ind]= datosAnuales_bonifTanqueSinMC[(ejec)][ind]+valorBonif;
		}
		float prodD_rcs=producdiaria*(float)rcs;
		datosAnuales_prodDiaria_rcs[ejec][ind]= datosAnuales_prodDiaria_rcs[(ejec)][ind]+prodD_rcs;
		datosAnuales_prodDiaria[ejec][ind]= datosAnuales_prodDiaria[(ejec)][ind]+producdiaria;

		//en funcion del nro del parto y el qel
		float melDesc = (float)qel/(float)2;
		float mesesPerdidos=expectativaVida_Meses-(IntervaloParto_Meses*(partos-1))-melDesc;
		float costoDescfinal=costoMensualDescarte*mesesPerdidos;

		if(descarte==descarte_mc){
			//printf("MC qel %d partos%d melDesc %.2f mesesPerdidos %.2f costoDescfinal %.2f\n",qel,partos,melDesc,mesesPerdidos,costoDescfinal);
		datosAnuales_gastos_insumos[ejec][ind]=datosAnuales_gastos_insumos[ejec][ind]+costoDescfinal;
		}
		if(descarte==descarte_msc){
			//printf("MSC  qel %d partos%d melDesc %.2f mesesPerdidos %.2f costoDescfinal %.2f\n",qel,partos,melDesc,mesesPerdidos,costoDescfinal);
		datosAnuales_gastos_insumos[ejec][ind]=datosAnuales_gastos_insumos[ejec][ind]+costoDescfinal;
		}
    }

    FILE *datosGraficoPerdidas=fopen(rutaArchivo(carp,1,"tablaAnual_Perdidas.csv"),"w+");
	FILE *datosGraficoDescarte=fopen(rutaArchivo(carp,1,"tablaAnual_DescarteM.csv"),"w+");
	FILE *datosGraficoPreniez =fopen(rutaArchivo(carp,1,"tablaAnual_PreniezM.csv"),"w+");
	FILE *datosGraficoPreniez17 =fopen(rutaArchivo(carp,1,"tablaAnual_Preniez17.csv"),"w+");
    FILE *datosGraficoSalud =fopen(rutaArchivo(carp,1,"tablaAnual_Salud.csv"),"w+");
    FILE *datosGraficoRcsT =fopen(rutaArchivo(carp,1,"tablaAnual_RcsTambo.csv"),"w+");

    fprintf(datosGraficoPerdidas,"Anio;Ejec;MC;MSC;Total\n");
	fprintf(datosGraficoDescarte,"Anio;Ejec;MC;MSC;Total\n");
	fprintf(datosGraficoPreniez,"Anio;Ejec;MC;MSC;Total\n");
    fprintf(datosGraficoPreniez17,"Anio;Ejec;Cantidad\n");
    fprintf(datosGraficoSalud,"Anio;Ejec;CantidadMC;CantidadMSC\n");
    fprintf(datosGraficoRcsT,"Anio;Ejec;CantidadRcsT\n");

    //Datos Graficos
    FILE *datosGraficoPerdMC =fopen(rutaArchivo(carp,1,"anual_PerdidaMC"),"w");
	FILE *datosGraficoPerdMSC=fopen(rutaArchivo(carp,1,"anual_PerdidaMSC"),"w");
	FILE *datosGraficoPerdTot=fopen(rutaArchivo(carp,1,"anual_PerdidaMTot"),"w");

    FILE *datosGraficoDescMC=fopen(rutaArchivo(carp,1,"anual_DescarteMC"),"w");
    FILE *datosGraficoDescMSC=fopen(rutaArchivo(carp,1,"anual_DescarteMSC"),"w");
    FILE *datosGraficoDescTot=fopen(rutaArchivo(carp,1,"anual_DescarteMTot"),"w");

    FILE *datosGraficoPrenMC=fopen(rutaArchivo(carp,1,"anual_PrenezMC"),"w");
    FILE *datosGraficoPrenMSC=fopen(rutaArchivo(carp,1,"anual_PrenezMSC"),"w");
    FILE *datosGraficoPrenTot=fopen(rutaArchivo(carp,1,"anual_PrenezMTot"),"w");

    FILE *datosGraficoCantMC=fopen(rutaArchivo(carp,1,"anual_CantidadMC"),"w");
    FILE *datosGraficoCantMSC=fopen(rutaArchivo(carp,1,"anual_CantidadMSC"),"w");
    FILE *datosGraficoCantMTot=fopen(rutaArchivo(carp,1,"anual_CantidadMTot"),"w");

    FILE *datosGraficoMes17=fopen(rutaArchivo(carp,1,"anual_Mes17"),"w");
    FILE *datosGraficoRcsTambo=fopen(rutaArchivo(carp,1,"anual_RcsTambo"),"w");

    FILE *datosGraficoGastoTotal=fopen(rutaArchivo(carp,1,"anual_GastoTotal"),"w");
    FILE *datosGraficoPerdTotal=fopen(rutaArchivo(carp,1,"anual_PerdTotal"),"w");
    FILE *datosGraficoCostoTotal=fopen(rutaArchivo(carp,1,"anual_CostoTotal"),"w");

	float totalM=0;
    int totalD=0;
    int totalP=0;
    int totalS=0;
    	FILE *datosGraficoPorcAnuales =fopen(rutaArchivo(carp,1,"tablaAnual_Porcentajes.csv"),"w+");
    	fprintf(datosGraficoPorcAnuales,"Anio;Esc;Perd MC;Perd MSC;Tot Perd;Desc MC;Desc MSC;Tot Desc;Pre�ez MC;Pre�ez MSC;Tot Pren;VO;Mes 17;Cant MC;Cant MSC;Tot Salud;RcsT;Bonif Total T.;Bonif Total T. Sin MC;Prom Bonif Tanq;Prom Bonif T Sin MC;Gasto MObra;Gasto Insumos;Gastos Total;Perd $Litros;Perd $Ciclo;Perd $Total;Costo Total;Gastos Total/VO;Gastos Total/VT;Perd $Total/VO;Perd $Total/VT;Costo Total/VO;Costo Total/VT\n");

    for(j=0;j<longitud;j++){ //por a�o
    //Calculo por ejecucion
    	float datosPerdMc[ejecuciones]; 	memset(datosPerdMc, 0, sizeof(datosPerdMc));
    	float datosPerdMsc[ejecuciones]; 	memset(datosPerdMsc, 0, sizeof(datosPerdMsc));
    	float datosPerdTot[ejecuciones]; 	memset(datosPerdTot, 0, sizeof(datosPerdTot));

    	float datosDescMc[ejecuciones]; 	memset(datosDescMc, 0, sizeof(datosDescMc));
    	float datosDescMsc[ejecuciones]; 	memset(datosDescMsc, 0, sizeof(datosDescMsc));
    	float datosDescTot[ejecuciones]; 	memset(datosDescTot, 0, sizeof(datosDescTot));

    	float datosPrenMc[ejecuciones]; 	memset(datosPrenMc, 0, sizeof(datosPrenMc));
    	float datosPrenMsc[ejecuciones]; 	memset(datosPrenMsc, 0, sizeof(datosPrenMsc));
    	float datosPrenTot[ejecuciones]; 	memset(datosPrenTot, 0, sizeof(datosPrenTot));

    	float datosCantMc[ejecuciones]; 	memset(datosCantMc, 0, sizeof(datosCantMc));
    	float datosCantMsc[ejecuciones]; 	memset(datosCantMsc, 0, sizeof(datosCantMsc));
    	float datosCantMTot[ejecuciones]; 	memset(datosCantMTot, 0, sizeof(datosCantMTot));

    	float datosMes17[ejecuciones];	 	memset(datosMes17, 0, sizeof(datosMes17));
    	float datosRcsT[ejecuciones]; 		memset(datosRcsT, 0, sizeof(datosRcsT));

    	float datosCantBonifTanque[ejecuciones]; 		memset(datosCantBonifTanque, 0, sizeof(datosCantBonifTanque));
    	float datosCantBonifTanqueSinMC[ejecuciones]; 	memset(datosCantBonifTanqueSinMC, 0, sizeof(datosCantBonifTanqueSinMC));
    	float datosPromBonifTanque[ejecuciones]; 		memset(datosPromBonifTanque, 0, sizeof(datosPromBonifTanque));
    	float datosPromBonifTanqueSinMC[ejecuciones]; 	memset(datosPromBonifTanqueSinMC, 0, sizeof(datosPromBonifTanqueSinMC));
    	float datosPromQuinSlLact[ejecuciones]; 		memset(datosPromQuinSlLact, 0, sizeof(datosPromQuinSlLact));

    	float datosGastoMObra[ejecuciones]; 		memset(datosGastoMObra, 0, sizeof(datosGastoMObra));
    	float datosGastoInsumos[ejecuciones]; 		memset(datosGastoInsumos, 0, sizeof(datosGastoInsumos));
		float datosGastoTotal[ejecuciones]; 		memset(datosGastoTotal, 0, sizeof(datosGastoTotal));
		float datosPerdLitro[ejecuciones]; 			memset(datosPerdLitro, 0, sizeof(datosPerdLitro));
		float datosPerdCiclo[ejecuciones]; 			memset(datosPerdCiclo, 0, sizeof(datosPerdCiclo));
		float datosPerdTotal[ejecuciones]; 			memset(datosPerdTotal, 0, sizeof(datosPerdTotal));
		float datosCostoTotal[ejecuciones]; 		memset(datosCostoTotal, 0, sizeof(datosCostoTotal));

		for(i=1;i<ejecuciones;i++){
			//calculo por ejecucion
			datosPerdMc[i]=(datosAnuales_perdMC[i][j]*(float)costo_litro);
			datosPerdMsc[i]=(datosAnuales_perdMSC[i][j]*(float)costo_litro);
			datosPerdTot[i]=datosPerdMc[i]+datosPerdMsc[i];

			datosDescMc[i]=(datosAnuales_descMC[i][j]);
			datosDescMsc[i]=(datosAnuales_descMSC[i][j]);
			datosDescTot[i]=datosDescMc[i]+datosDescMsc[i];

			datosPrenMc[i]=(datosAnuales_preniezMC[i][j]);
			datosPrenMsc[i]=(datosAnuales_preniezMSC[i][j]);
			datosPrenTot[i]=datosPrenMc[i]+datosPrenMsc[i];

			datosCantMc[i]=(datosAnuales_saluc_mc[i][j]);
			datosCantMsc[i]=(datosAnuales_saluc_msc[i][j]);
			datosCantMTot[i]=datosCantMc[i]+datosCantMsc[i];

			datosMes17[i]=(datosAnuales_preniez17[i][j]);
			datosRcsT[i] = (float)datosAnuales_prodDiaria_rcs[i][j]/(float)datosAnuales_prodDiaria[i][j];

			datosCantBonifTanque[i]=datosAnuales_bonifTanque[i][j];
			datosCantBonifTanqueSinMC[i]=datosAnuales_bonifTanqueSinMC[i][j];
			datosPromBonifTanque[i]=datosCantBonifTanque[i]/(float)(datosAnuales_saluc_mc[i][j]+datosAnuales_saluc_msc[i][j]+datosAnuales_saluc_sana[i][j]);
    		datosPromBonifTanqueSinMC[i]=datosCantBonifTanqueSinMC[i]/(float)(datosAnuales_saluc_msc[i][j]+datosAnuales_saluc_sana[i][j]);
    		datosPromQuinSlLact[i] = (datosAnuales_sl_lactancia[i][j]/24);

    		/*datosPromQuinSlLact[i] = (datosAnuales_sl_lactancia[i][j]/it);
    		datosPromQuinSlLact[i] = (datosAnuales_sl_lactancia[i][j]/it);
    		datosPromQuinSlLact[i] = (datosAnuales_sl_lactancia[i][j]/it);
    		datosPromQuinSlLact[i] = (datosAnuales_sl_lactancia[i][j]/it);*/

    	float gastoIns_Descarte=	datosAnuales_gastos_insumos[i][j];
		if(escenarios[j]==1){//PMTD
			datosGastoMObra[i]=NroOrdenios_dia*Dias_anio*Horas_tambero_PMTD_VO*Precio_MOB_tambero_hora*datosPromQuinSlLact[i];
			datosGastoInsumos[i]=NroOrdenios_dia*Dias_anio*Litros_desinfectante_VO*Precio_litro_desinfectante*datosPromQuinSlLact[i];
		} else if(escenarios[j]==2){ //DCT
			datosGastoMObra[i]=Horas_tambero_pomos_VS*Precio_MOB_tambero_hora*datosMes17[i];
			datosGastoInsumos[i]=NroPezones_vaca*Precio_pomo_secado*datosMes17[i];
		} else if(escenarios[j]==3){//CMO
			datosGastoMObra[i]=0;
			datosGastoInsumos[i]=Precio_chequeo_MO*NroChequeoMO_anio;
		} else if(escenarios[j]==4){ //TMC
			datosGastoMObra[i]=Horas_tambero_pomo_MC*datosCantMc[i];
			datosGastoInsumos[i]=Precio_pomo_MC*datosCantMc[i];
		} else if(escenarios[j]==5){ //4 medidas
			float datoEscG1=(NroOrdenios_dia*Dias_anio*Horas_tambero_PMTD_VO*Precio_MOB_tambero_hora*datosPromQuinSlLact[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;///CAMBIO OCT 2021 para dar diferentes aumentos o dismi del plan basico . factores mayores o menores a 1, en porcentaje;
			float datoEscG2=(Horas_tambero_pomos_VS*Precio_MOB_tambero_hora*datosMes17[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//CAMBIO OCT 2021 ;
			float datoEscG3=0;
			float datoEscG4=(Horas_tambero_pomo_MC*datosCantMc[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//CAMBIO OCT 2021 ;
			datosGastoMObra[i]=datoEscG1+datoEscG2+datoEscG3+datoEscG4;

			float datoEscI1=((620)+NroOrdenios_dia*Dias_anio*Litros_desinfectante_VO*Precio_litro_desinfectante*datosPromQuinSlLact[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//CAMBIO OCT 2021 ;
			float datoEscI2=(NroPezones_vaca*Precio_pomo_secado*datosMes17[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//CAMBIO OCT 2021 ;
			float datoEscI3=(Precio_chequeo_MO*NroChequeoMO_anio)*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//CAMBIO OCT 2021 ;
			float datoEscI4=(Precio_pomo_MC*datosCantMc[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//CAMBIO OCT 2021 ;
			datosGastoInsumos[i]=datoEscI1+datoEscI2+datoEscI3+datoEscI4;
		} else if(escenarios[j]==6){//segregacion - ver seteo de valores linea 135 progTambo.c datosCantMTot[i]
			datosGastoMObra[i]=0;
			datosGastoInsumos[i]= (datosPromQuinSlLact[i]*Factor_segregacion) + (datosCantMTot[i]*costo_seg_VI*Coef_Seg);//
datosCantMTot[i]*Factor_segregacion;///2022= SI SEGREGO SOLO VACAS CON MC, USAR = (datosCantMc[i]*costo_seg_VI); cambio mayo 2019////datosPromQuinSlLact[i]*Factor_segregacion;//(PrecioVaq-PrecioVaca)*Factor_segregacion;
		} else if(escenarios[j]==7){ //Descarte - ver seteo de valores
			datosGastoMObra[i]=0;
			datosGastoInsumos[i]=(PrecioVaq-PrecioVaca)*datosDescTot[i];

		} else if(escenarios[j]==8){ //4 medidas+segregacion
			float datoEscG1=(NroOrdenios_dia*Dias_anio*Horas_tambero_PMTD_VO*Precio_MOB_tambero_hora*datosPromQuinSlLact[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscG2=(Horas_tambero_pomos_VS*Precio_MOB_tambero_hora*datosMes17[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscG3=0;
			float datoEscG4=(Horas_tambero_pomo_MC*datosCantMc[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			datosGastoMObra[i]=datoEscG1+datoEscG2+datoEscG3+datoEscG4;

			float datoEscI1=((620)+NroOrdenios_dia*Dias_anio*Litros_desinfectante_VO*Precio_litro_desinfectante*datosPromQuinSlLact[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI2=(NroPezones_vaca*Precio_pomo_secado*datosMes17[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI3=(Precio_chequeo_MO*NroChequeoMO_anio)*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI4=(Precio_pomo_MC*datosCantMc[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI6= (datosPromQuinSlLact[i]*Factor_segregacion) + (datosCantMc[i]*costo_seg_VI);//(datosCantMTot[i]*costo_seg_VI*Coef_Seg);//2022= SI SEGREGO SOLO VACAS CON MC, USAR = (datosCantMc[i]*costo_seg_VI);//datosCantMTot[i]*Factor_segregacion;//cambio mayo 2019//datosPromQuinSlLact[i]*Factor_segregacion;//(PrecioVaq-PrecioVaca)*Factor_segregacion; // *datosDescTot[i];//cambia Meli datosDesc por factor segreg //hay "costo fijo" por VO y costo variable dependiendo del numero de vacas segregadas
			datosGastoInsumos[i]=datoEscI1+datoEscI2+datoEscI3+datoEscI4+datoEscI6;

		} else if(escenarios[j]==9){ //4 medidas+descarte
			float datoEscG1=(NroOrdenios_dia*Dias_anio*Horas_tambero_PMTD_VO*Precio_MOB_tambero_hora*datosPromQuinSlLact[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscG2=(Horas_tambero_pomos_VS*Precio_MOB_tambero_hora*datosMes17[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscG3=0;
			float datoEscG4=(Horas_tambero_pomo_MC*datosCantMc[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			datosGastoMObra[i]=datoEscG1+datoEscG2+datoEscG3+datoEscG4;

			float datoEscI1=((620)+NroOrdenios_dia*Dias_anio*Litros_desinfectante_VO*Precio_litro_desinfectante*datosPromQuinSlLact[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI2=(NroPezones_vaca*Precio_pomo_secado*datosMes17[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI3=(Precio_chequeo_MO*NroChequeoMO_anio)*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI4=(Precio_pomo_MC*datosCantMc[i])*1;//0.83;//PA:1.17;//PB=0.83;//DEFAULT=1;//
			float datoEscI6=(PrecioVaq-PrecioVaca)*datosDescTot[i];
			datosGastoInsumos[i]=datoEscI1+datoEscI2+datoEscI3+datoEscI4+datoEscI6;
		}

		datosGastoInsumos[i]=datosGastoInsumos[i]+gastoIns_Descarte;
		datosGastoTotal[i]=datosGastoMObra[i]+datosGastoInsumos[i];

		datosPerdLitro[i]=datosPerdTot[i]*PrecioLitroLeche;
		datosPerdCiclo[i]=datosPrenTot[i]*PrecioIA;
		datosPerdTotal[i]=datosPerdLitro[i]+datosPerdCiclo[i];

		datosCostoTotal[i]=datosGastoTotal[i]+datosPerdTotal[i];


			fprintf(datosGraficoPerdidas,"%d;%d;%.2f;%.2f;%.2f\n",(j+1),i,datosAnuales_perdMC[i][j],datosAnuales_perdMSC[i][j],totalM);
			fprintf(datosGraficoDescarte,"%d;%d;%d;%d;%d\n",(j+1),i,datosAnuales_descMC[i][j],datosAnuales_descMSC[i][j],totalD);
			fprintf(datosGraficoPreniez,"%d;%d;%d;%d;%d\n",(j+1),i,datosAnuales_preniezMC[i][j],datosAnuales_preniezMSC[i][j],totalP);
			fprintf(datosGraficoPreniez17,"%d;%d;%d\n",(j+1),i,datosAnuales_preniez17[i][j]);
			fprintf(datosGraficoSalud,"%d;%d;%d;%d\n",(j+1),i,datosAnuales_saluc_mc[i][j],datosAnuales_saluc_msc[i][j]);
			float valorrRcsT = (float)datosAnuales_prodDiaria_rcs[i][j]/(float)datosAnuales_prodDiaria[i][j];//esta igual en linea 447
			fprintf(datosGraficoRcsT,"%d;%d;%.0f\n",(j+1),i,valorrRcsT);
	    }

	    escribirDatosGrafico(datosGraficoPerdMC,datosPerdMc,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoPerdMSC,datosPerdMsc,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoPerdTot,datosPerdTot,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoDescMC,datosDescMc,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoDescMSC,datosDescMsc,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoDescTot,datosDescTot,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoPrenMC,datosPrenMc,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoPrenMSC,datosPrenMsc,ejecuciones,(j+1));
		escribirDatosGrafico(datosGraficoPrenTot,datosPrenTot,ejecuciones,(j+1));
		escribirDatosGrafico(datosGraficoCantMC,datosCantMc,ejecuciones,(j+1));
		escribirDatosGrafico(datosGraficoCantMSC,datosCantMsc,ejecuciones,(j+1));
		escribirDatosGrafico(datosGraficoCantMTot,datosCantMTot,ejecuciones,(j+1));
		escribirDatosGrafico(datosGraficoMes17,datosMes17,ejecuciones,(j+1));
		escribirDatosGrafico(datosGraficoRcsTambo,datosRcsT,ejecuciones,(j+1));

	    escribirDatosGrafico(datosGraficoGastoTotal,datosGastoTotal,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoPerdTotal,datosPerdTotal,ejecuciones,(j+1));
	    escribirDatosGrafico(datosGraficoCostoTotal,datosCostoTotal,ejecuciones,(j+1));

		float vo=sumayPromVectorFloat(datosPromQuinSlLact,ejecuciones,1);
		float gastoTot=sumayPromVectorFloat(datosGastoTotal,ejecuciones,1);
		float perdPTot=sumayPromVectorFloat(datosPerdTotal,ejecuciones,1);
		float costoTot=sumayPromVectorFloat(datosCostoTotal,ejecuciones,1);

		fprintf(datosGraficoPorcAnuales,"%d;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.0f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",
		(j+1),escenarios[j],
		sumayPromVectorFloat(datosPerdMc,ejecuciones,1),sumayPromVectorFloat(datosPerdMsc,ejecuciones,1), sumayPromVectorFloat(datosPerdTot,ejecuciones,1),
		sumayPromVectorFloat(datosDescMc,ejecuciones,1), sumayPromVectorFloat(datosDescMsc,ejecuciones,1), sumayPromVectorFloat(datosDescTot,ejecuciones,1),
		sumayPromVectorFloat(datosPrenMc,ejecuciones,1), sumayPromVectorFloat(datosPrenMsc,ejecuciones,1), sumayPromVectorFloat(datosPrenTot,ejecuciones,1),
		vo,sumayPromVectorFloat(datosMes17,ejecuciones,1),
		sumayPromVectorFloat(datosCantMc,ejecuciones,1), sumayPromVectorFloat(datosCantMsc,ejecuciones,1), sumayPromVectorFloat(datosCantMTot,ejecuciones,1), sumayPromVectorFloat(datosRcsT,ejecuciones,1),
		sumayPromVectorFloat(datosCantBonifTanque,ejecuciones,1),sumayPromVectorFloat(datosCantBonifTanqueSinMC,ejecuciones,1),
		sumayPromVectorFloat(datosPromBonifTanque,ejecuciones,1),sumayPromVectorFloat(datosPromBonifTanqueSinMC,ejecuciones,1),
		sumayPromVectorFloat(datosGastoMObra,ejecuciones,1),sumayPromVectorFloat(datosGastoInsumos,ejecuciones,1),gastoTot,
		sumayPromVectorFloat(datosPerdLitro,ejecuciones,1),sumayPromVectorFloat(datosPerdCiclo,ejecuciones,1),perdPTot,
		costoTot,
		gastoTot/vo,gastoTot/cantVacasRodeo,perdPTot/vo,perdPTot/cantVacasRodeo,costoTot/vo,costoTot/cantVacasRodeo);
	}

	// crearArchivoHTML(carp,"tablaAnual_Perdidas.html",datosGraficoPerdidas,"Datos Perdida Anual");
	// crearArchivoHTML(carp,"tablaAnual_DescarteM.html",datosGraficoDescarte,"Datos Descarte Anual");
	// crearArchivoHTML(carp,"tablaAnual_PreniezM.html",datosGraficoPreniez,"Datos Pre�ez Anual");
	// crearArchivoHTML(carp,"tablaAnual_Preniez17.html",datosGraficoPreniez17,"Datos Pre�ez Anual mes 17");
	// crearArchivoHTML(carp,"tablaAnual_Salud.html",datosGraficoSalud,"Datos Salud");
	// crearArchivoHTML(carp,"tablaAnual_RcsTambo.html",datosGraficoRcsT,"Datos Rcs Tambo");
	// crearArchivoHTML(carp,"tablaAnual_Porcentajes.html",datosGraficoPorcAnuales,"Datos Anuales Promedio");

    fclose(datosGraficoPerdidas);
    fclose(datosGraficoDescarte);
    fclose(datosGraficoPreniez);
    fclose(datosGraficoPreniez17);
    fclose(datosGraficoPorcAnuales);
    fclose(datosGraficoRcsT);
    fclose(datosGraficoPerdMC);
	fclose(datosGraficoPerdTot);
	fclose(datosGraficoPerdMSC);
	fclose(datosGraficoDescMC);
	fclose(datosGraficoDescTot);
	fclose(datosGraficoDescMSC);
	fclose(datosGraficoPrenMC);
	fclose(datosGraficoPrenTot);
	fclose(datosGraficoPrenMSC);
	fclose(datosGraficoCantMC);
	fclose(datosGraficoCantMTot);
	fclose(datosGraficoCantMSC);
	fclose(datosGraficoMes17);
	fclose(datosGraficoRcsTambo);
	fclose(datosGraficoGastoTotal);
	fclose(datosGraficoPerdTotal);
	fclose(datosGraficoCostoTotal);
}

void calcularPromedioIntervPP(char nombre[40],char arch_salida[40]){
    printf("\nPROMEDIO INTERVALO PARTO PARTO\n");
    FILE *archivo=fopen(nombre,"r");
    char line[1024];
    fgets(line, sizeof(line), archivo);
    int cantidadTotal=0;
    calculo_pp calculos[MaxVacasEstad];
    int i,j,k,x;
    int esc=-1;
    int ejec=0,mes,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt,anio;
    int salAnt;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel;
    int lim=0;
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
               &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){

		int pos=-1;
		for(i=0;i<cantidadTotal && (pos==-1);i++){
			if(id==calculos[i].id)
			pos=i;
		}
		if(pos!=-1){  //La Modifico
			calculo_pp calcpp=calculos[pos];
			calcpp.prenez[calcpp.mes]=prenez;
			calcpp.mes=calcpp.mes+1;
			calculos[pos]=calcpp;
			//         printf("\nMOD DATO %d - %d \n",id,pos);
		}else{ //La agrego
			calculo_pp calcpp;
			calcpp.id=id;
			calcpp.prenez[0]=prenez;
			calcpp.mes=1;
			calculos[cantidadTotal]=calcpp;
			cantidadTotal++;
		//        printf("\nAGREGO DATO %d - %d\n",id,cantidadTotal);
		}
    }
    int cantVacas=0;  //Aca se sumar�a doble por vacas con 2 ciclos
    int sumaMeses=0; //Aca se sumar�an los meses totales de todas las vacas.
    for(x=0;x<cantidadTotal;x++){  //Recorro el vector Calculo_P_P hasta cantidadTotal
		calculo_pp calcpp=calculos[x];
		int cant_2=0;
		printf("\nID= %d: ",calcpp.id);
		for( i=0; i<calcpp.mes;i++){
			if(calcpp.prenez[i]==-3)
            	printf("\t%d ",calcpp.prenez[i]);
            else
            	printf("%d ",calcpp.prenez[i]);
        	if(calcpp.prenez[i]==-2){
            	cant_2++;
        	}
      	}
      	if(cant_2>1){
		    int pos_2[cant_2];
		    int posic=0;
		    for( i=0; i<calcpp.mes;i++){
          		if(calcpp.prenez[i]==-2){
					pos_2[posic]=i;
					posic++;
          		}
        	}
	        for(j=0;j<(cant_2-1);j++){
				int interv=pos_2[j+1] - pos_2[j];
				if(interv>10){ //interv -2 a -2 ideal es de 11
					cantVacas++;
					sumaMeses = sumaMeses+interv;
					printf("\n\tID= %d:   == cv %d int %d - ",calcpp.id,cantVacas,interv);
	          	}
	        }
    	}
  //    printf("\nPASA ANALISIS FINAL\n");
    }
    int promedio=sumaMeses/cantVacas;
    int servTotales=0;
    FILE *salida=fopen(arch_salida,"a");
    printf("\tPromedio: %d\n",promedio);
    fprintf(salida,"\nIntervalo Parto-Parto\n");
    fprintf(salida,"Promedio:;%d\n",promedio);
    fclose(archivo);
    fclose(salida);
}

void calcularvariacionMC_MSC_Quincena(char nombre[40],int ejecuciones, int it){
    printf("\nCALCULOS MC MSC POR QUINCENA\n");
    FILE *archivo=fopen(nombre,"r");
    int ejec=0,mes=0,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt,anio;
    int salAnt;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel;
    int calcMc_Msc[ejecuciones][it][3];		memset(calcMc_Msc, 0, sizeof(calcMc_Msc));//LACTANCIA -0 //MC  -1 //MSC-2
    int i,j;
	int esc=-1;
    char line[1024];
    fgets(line, sizeof(line), archivo);
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
              &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
    /* sl 1= en lactancia; 2= seca*/
        if(sl==1)
            calcMc_Msc[(ejec)][(mes)][0] +=1;
        if(salud==2)
            calcMc_Msc[(ejec)][(mes)][1] +=1;
        if(salud==3)
            calcMc_Msc[(ejec)][(mes)][2] +=1;
    }
    FILE *datosGrafico=fopen(rutaArchivo(carp,1,"tablaQuinc_EvolucionMastitis.csv"),"w+");
    fprintf(datosGrafico,"Ejec;Quincena;MC;MSC\n");

    FILE *datosGraficoMC =fopen(rutaArchivo(carp,1,"quinc_EvolucionMC"),"w");
    FILE *datosGraficoMSC=fopen(rutaArchivo(carp,1,"quinc_EvolucionMSC"),"w");

//    #x min     Q1          median      q3          max     width   label
    for(i=1;i<it;i++){
		               //Para cada quincena debo almacenar los resultados de MC/MSC correspndiente a la cantidad de ejecuciones
		float calculosMC[ejecuciones];
		float calculosMSC[ejecuciones];
		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices.
		calculosMC[0]=0;
		calculosMSC[0]=0;
		for(j=1;j<ejecuciones;j++){  //Ejecucion cero no da resultados, luego cuento de
		//	printf("\n\t ej= %d\t it=%d lact=%d mc=%d msc=%d - ",j,i,calcMc_Msc[j][i][0],calcMc_Msc[j][i][1],calcMc_Msc[j][i][2]);
			float calcMc= ((float) calcMc_Msc[j][i][1])/((float) calcMc_Msc[j][i][0]);
			float calcMsc= ((float) calcMc_Msc[j][i][2])/((float) calcMc_Msc[j][i][0]);
			calculosMC[j]=calcMc;
			calculosMSC[j]=calcMsc;
			fprintf(datosGrafico,"%d;%d;%.3f;%.3f \n",(j),(i),calcMc,calcMsc);
		}
		escribirDatosGrafico(datosGraficoMC,calculosMC,ejecuciones,(i));
		escribirDatosGrafico(datosGraficoMSC,calculosMSC,ejecuciones,(i));
    }
    fclose(archivo);
    fclose(datosGraficoMC);
    fclose(datosGraficoMSC);
  //  crearArchivoHTML(carp,"tablaQuinc_EvolucionMastitis.html",datosGrafico,"Datos Mastitis Por Quincena");
    fclose(datosGrafico);
}

void calcularConteoCambioMastitis(char nombre[40],int ejecuciones, int it){
    printf("\nCONTEO DE VARIACION DE MASTITIS\n");
    FILE *archivo=fopen(nombre,"r");
    FILE *salida;
    salida=fopen(rutaArchivo(carp,1,"tablaQuinc_ConteoVariacionMastitis.csv"),"w+");
    fprintf(salida,"Ejec;Quinc;1  1;1  2;1  3;2  1;2  2;2  3;3  1;3  2;3  3;Cant. Vacas\n");
  //  printf("\tEjec\tId\tServicios\n");
    char line[1024];
    fgets(line, sizeof(line), archivo);//lee la linea de titulos
    unsigned int i,j,k,l;
    unsigned int datosVariacion[ejecuciones][it][9];    memset(datosVariacion, 0, sizeof(datosVariacion));
	unsigned int limVacas[ejecuciones][it];				memset(limVacas, 0, sizeof(limVacas));
	int ejec=0,mes,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir;
	float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
	int pat,salAu,salAg,salSCN,salOStr,salECo,salOt,anio;
	int salAnt;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel;
     int esc=-1;
	int lim=0;
	while ((EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
    &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc))){
		if(sl==1){
			if(salAnt!=salud_inic){
				unsigned int cod=codCambioSalud(salAnt,salud); //codCambioSalud retorna la posicion a sumar en base al cambio
				datosVariacion[ejec][mes][cod]++;
				limVacas[ejec][mes]++;
			}
	    }
	}

    //Fin del analisis de todas las ejecuciones	-las imprimo a un archivo
    for(j=1;j<ejecuciones;j++){
        for(i=1;i<it;i++){
		    fprintf(salida,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",j,i,datosVariacion[j][i][0],datosVariacion[j][i][1],datosVariacion[j][i][2],datosVariacion[j][i][3],datosVariacion[j][i][4],datosVariacion[j][i][5],datosVariacion[j][i][6],datosVariacion[j][i][7],datosVariacion[j][i][8],limVacas[j][i]);
	    }
    }

    FILE *datosGraficoLact=fopen(rutaArchivo(carp,1,"quinc_EvolucionSaludNuevaMC"),"w");
    FILE *datosGraficoPren=fopen(rutaArchivo(carp,1,"quinc_EvolucionSaludNuevaMSC"),"w");
    FILE *datosGraficoDesc=fopen(rutaArchivo(carp,1,"quinc_EvolucionSaludCronicaMSC"),"w");

 	for(i=1;i<it;i++){
		//Para cada quincena debo almacenar los resultados de MC/MSC correspndiente a la cantidad de ejecuciones
		float calculos1_2[ejecuciones];
		float calculos1_3[ejecuciones];
		float calculos3_3[ejecuciones];
		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices.
		calculos1_2[0]=0;
		calculos1_3[0]=0;
		calculos3_3[0]=0;
		for(j=1;j<ejecuciones;j++){
		     //printf("\nlimite ej %d it %d valor %d \n",(j),(i),limVacas[j][i]);
			calculos1_2[j]=((float)datosVariacion[j][i][1])/((float)limVacas[j][i]);
			calculos1_3[j]=((float)datosVariacion[j][i][2])/((float)limVacas[j][i]);
			calculos3_3[j]=((float)datosVariacion[j][i][8])/((float)limVacas[j][i]);
//			fprintf(datosGrafico,"%d;%d;%.3f;%.3f \n",(j),(i),calcMc,calcMsc);
		}
		escribirDatosGrafico(datosGraficoLact,calculos1_2,ejecuciones,(i));
		escribirDatosGrafico(datosGraficoPren,calculos1_3,ejecuciones,(i));
		escribirDatosGrafico(datosGraficoDesc,calculos3_3,ejecuciones,(i));
    }
   	fclose(datosGraficoLact);
 	fclose(datosGraficoPren);
 	fclose(datosGraficoDesc);
    fclose(archivo);
   // crearArchivoHTML(carp,"tablaQuinc_ConteoVariacionMastitis.html",salida,"Datos Variacion Salud");
    fclose(salida);
}

void estadisticasEstimacion() {
	char nombre[30];
    fprintf(stdout,"\n --> Nombre del archivo de datos(max. 20 caracteres) ");
    scanf("%s",nombre);
    char arch_ingreso[40];
    strcpy(arch_ingreso,"./ArchivosTambo/");
    strcat(arch_ingreso, nombre);
            //80_4med_descarte.csv
  //  char carp[10];
    fprintf(stdout,"\n --> Nombre de salida(max. 10 caracteres sin espacios) ");
    scanf("%s",carp);

    char carpetas[90];
    strcpy(carpetas,"./datosEstadisticos.sh ");
    strcat(carpetas,"ArchivosTambo/");
    strcat(carpetas, carp);
    strcat(carpetas, " ArchivosTambo/");
    strcat(carpetas, nombre);
  //  strcat(carpetas, "'");
  //	printf("carpetas '%s' \n",carpetas);
    system(carpetas);

    struct tm *tiempo;
	time_t fecha_sistema;
    time(&fecha_sistema);
	tiempo=localtime(&fecha_sistema);
	int anio=tiempo->tm_year + 1900;
    int mes=tiempo->tm_mon + 1;
    int dia=tiempo->tm_mday;
    unsigned char hr =tiempo->tm_hour;
	unsigned char min=tiempo->tm_min;
	unsigned char seg=tiempo->tm_sec;
    printf("Inicio estadisticas %d:%d:%d\n",hr,min,seg);

    FILE *archivo=fopen(arch_ingreso,"r");
    char line[1024];
    if (fgets(line, sizeof(line), archivo) == NULL)  {       // Waste the first line (headers).
        printf("El archivo '%s' esta vacio\n", nombre);
        fclose(archivo);
        return;
    }
     // crearArchivoHTML(carp,"tablaEntrada.html",archivo,"Datos Estimacion");
    fclose(archivo);

	char fecha [30];
    sprintf(fecha, "%d-%d-%d",anio,mes,dia);
    strcat(fecha, "_estadisticas.csv");
    char* arch_salida=(rutaArchivo(carp,0,fecha));
  //  printf("El archivo '%s' es en\n", arch_salida);

	// Estadisticas por quincena
	calcularVacasEnLactanciaYSecas_PreniadasYVacias_DescarteYMuertas(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
	calcularVacasEnMesLactancia(arch_ingreso,arch_salida,MAX_QUINCENA+1,MesesDeEspera+(16)); //Son las 14 quincenas hasta el mes 7 de pre�ez, y -1 porque al llegar al ultimo mes de espera lo descarta
	calcularvariacionMC_MSC_Quincena(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
	calcularConteoCambioMastitis(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);

	// Estadicticas por lactancia
    calcularVacasInfPorLactancia(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
    calcularPerdidaLitrosMC_MSC_Lactancia(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
    calcularvariacionMC_MSC_Lactancia(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
    calcularConteoCambioMastitis_Lactancia(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
    calcularDescarteAborto_Lactancia(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA+1);
    //Estadisticas anuales
    calcularDatosAnuales(arch_ingreso,MAX_EJECUCION+1,MAX_QUINCENA);
   //  calcularPromedioIntervPP(arch_ingreso,arch_salida);
   // calcularServiciosPorVacaYRodeo(arch_ingreso,arch_salida,MAX_EJECUCION+1);

    char archivoD[50];
    strcpy(archivoD,"./archivosEstadisticos.sh ");
    strcat(archivoD,"ArchivosTambo/");
    strcat(archivoD, carp);
    system(archivoD);

    time(&fecha_sistema);
	tiempo=localtime(&fecha_sistema);
	hr =tiempo->tm_hour;
	min=tiempo->tm_min;
	seg=tiempo->tm_sec;
	printf("Fin estadisticas %d:%d:%d\n",hr,min,seg);
}
