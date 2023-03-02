//Utilidades
//   #x min     Q1          median      q3          max     width   label
char carp[10]="Estad";

void organizarYGenerarDatos(float calculosMSC[],int tamanio,float *min,float *q1,float *med,float *q3,float *max){
	quicksort(calculosMSC,tamanio);
	//tamanio = cantElems+1 para efectuar mejor los calculos de la posicion de cada cuartilquicksort
//	printf("\n #Elem=%d ",(tamanio-1) );// Estoy decrementando en 1 ya que tomo un valor mas por dejar la pos 0 del vector en 0 para los caalculos de las pos de q1q2q3 sean mas faciles
	int posmedio= tamanio/2;
	int parmedio= tamanio % 2;
	int posq1=tamanio/4;
	int parq1=tamanio%4;
	int posq3=(tamanio*3)/4;
	int parq3=(tamanio*3)%4;
     
	if(parmedio==0){ //es par
		*med=(float)calculosMSC[posmedio];
	}else{
		*med=(float)((calculosMSC[posmedio]+calculosMSC[(posmedio+1)])/2);
	}           
	if(parq1==0){ //es par
		*q1=(float)calculosMSC[posq1];
	}else{
		*q1=(float)((calculosMSC[posq1]+calculosMSC[(posq1+1)])/2);
	}
	if(parq3==0){ //es par
		*q3=(float)calculosMSC[posq3];
	}else{
		*q3=(float)((calculosMSC[posq3]+calculosMSC[(posq3+1)])/2);
	}
	float ric=*q3-*q1;
	float limInf=(float)*q1-(float)ric*(float)1.5;
	float limSup=(float)*q3+(float)ric*(float)1.5;
	unsigned int i,j=0;
	unsigned char encInf='0';
 	unsigned char encSup='0';
    for (i=1; i<tamanio && encInf=='0'; i++) {
        if(calculosMSC[i]>=limInf){
            *min=calculosMSC[i];
            encInf='1';
        } 
    }
    for (j=tamanio-1; j>0 && encSup=='0'; j--) {
        if(calculosMSC[j]<=limSup){
            *max=calculosMSC[j];
            encSup='1';
        }    
    }
 //   printf(" q1=%.3f q2=%.3f q3=%.3f ric=%.3f limInf=%.3f limSup=%.3f min=%.3f max=%.3f",*q1,*med,*q3,ric,limInf,limSup,*min,*max);
}

void escribirDatosGrafico(FILE *archivo,float datos[],int limDatos,int indX){
	float minM, q1M, medM, q3M, maxM;
    organizarYGenerarDatos(datos,limDatos,&minM,&q1M,&medM,&q3M,&maxM);
	fprintf(archivo, " %.1f \t %.3f \t %.3f \t %.3f \t %.3f \t %.3f \t\n",((float)indX),minM,q1M,medM,q3M,maxM);
}

// Fin de utilidades

void calcularPerdidaLitrosMC_MSC_Lactancia(char nombre[40],int ejecuciones, int it){
	int maxQuincLact=MesesDeEspera+16; //Cambia de 13 a 16  por el secado c prob
    printf("\nPERDIDA DE LITROS\n");
	FILE *archivo=fopen(nombre,"r");
    int ejec=0,mes=0,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir; 
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt;
    int salAnt;
    int anio=-1;
     int esc=-1;
	unsigned int nop,infGral,infMC,infMSC;
	int prenez,qel;
    float cantPerdMc_Msc[ejecuciones][maxQuincLact][4]; //Cant MC-0 //Cant MSC-1 //Perdida MC-2 //Perdida MSC-3
    memset(cantPerdMc_Msc, 0, sizeof(cantPerdMc_Msc));
	int i,j;
    char line[1024];
    fgets(line, sizeof(line), archivo);
    
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
              &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
    /* sl 1= en lactancia; 2= seca*/
        if(anio>=minAnioEstLactancia){
        	if(resultPerdidaMC>0){
	        	cantPerdMc_Msc[(ejec)][(indiceQel(del))][0] +=1;
	        	cantPerdMc_Msc[(ejec)][(indiceQel(del))][2] +=resultPerdidaMC;    
	        }
	        if(resultPerdidaMSC>0){
	        	cantPerdMc_Msc[(ejec)][(indiceQel(del))][1] +=1;
	        	cantPerdMc_Msc[(ejec)][(indiceQel(del))][3] +=resultPerdidaMSC;    
	        }
        }   
    }  
    FILE *datosGrafico=fopen(rutaArchivo(carp,1,"tablaLact_EvolucionPerdida.csv"),"w+");
    fprintf(datosGrafico,"Ejec;QuincenaLactancia;Cant MC;Cant MSC;Perd Total MC;Perd Total MSC;Promedio Perd MC;Promedio Perd MSC\n");

    FILE *datosGraficoTMC =fopen(rutaArchivo(carp,1,"lact_EvolucionPerdidaTotalMC"),"w");
    FILE *datosGraficoTMSC=fopen(rutaArchivo(carp,1,"lact_EvolucionPerdidaTotalMSC"),"w");
	FILE *datosGraficoPMC =fopen(rutaArchivo(carp,1,"lact_EvolucionPerdidaPromedioMC"),"w");
    FILE *datosGraficoPMSC=fopen(rutaArchivo(carp,1,"lact_EvolucionPerdidaPromedioMSC"),"w");
    
//    #x min     Q1          median      q3          max     width   label
    for(i=1;i<maxQuincLact;i++){ 
		               //Para cada quincena debo almacenar los resultados de MC/MSC correspndiente a la cantidad de ejecuciones 
		float calculosTotalMC[ejecuciones];
		float calculosTotalMSC[ejecuciones];
		float calculosPromMC[ejecuciones];
		float calculosPromMSC[ejecuciones];
		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices.
		calculosTotalMC[0]=0;
		calculosTotalMSC[0]=0;
		calculosPromMC[0]=0;
		calculosPromMSC[0]=0;
		for(j=1;j<ejecuciones;j++){  //Ejecucion cero no da resultados, luego cuento de 
		//	printf("\n\t ej= %d\t qel=%d lact=%d mc=%d msc=%d - ",j,i,calcMc_Msc[j][i][0],calcMc_Msc[j][i][1],calcMc_Msc[j][i][2]);
			calculosTotalMC[j]= ((float) cantPerdMc_Msc[j][i][0]);
			calculosTotalMSC[j]= ((float) cantPerdMc_Msc[j][i][1]); 
			float result1=0,result2=0;
			if(cantPerdMc_Msc[j][i][0]>0){
				result1=((float) cantPerdMc_Msc[j][i][2])/((float) cantPerdMc_Msc[j][i][0]); 
			}
			if(cantPerdMc_Msc[j][i][1]>0){
				result2=((float) cantPerdMc_Msc[j][i][3])/((float) cantPerdMc_Msc[j][i][1]); 	
			}
			calculosPromMC[j]=result1;
			calculosPromMSC[j]=result2;
			fprintf(datosGrafico,"%d;%d;%.0f;%.0f;%.2f;%.2f;%.2f;%.2f\n",(j),(i),calculosTotalMC[j],calculosTotalMSC[j],((float) cantPerdMc_Msc[j][i][2]),((float) cantPerdMc_Msc[j][i][3]),calculosPromMC[j],calculosPromMSC[j]);
		} 
		escribirDatosGrafico(datosGraficoTMC,calculosTotalMC,ejecuciones,(i));
		escribirDatosGrafico(datosGraficoTMSC,calculosTotalMSC,ejecuciones,(i));
		escribirDatosGrafico(datosGraficoPMC,calculosPromMC,ejecuciones,(i));
		escribirDatosGrafico(datosGraficoPMSC,calculosPromMSC,ejecuciones,(i));
    } 
    fclose(archivo);
    fclose(datosGraficoTMC);
    fclose(datosGraficoTMSC);
	fclose(datosGraficoPMC);
    fclose(datosGraficoPMSC);
   // crearArchivoHTML(carp,"tablaLact_EvolucionPerdida.html",datosGrafico,"Datos Perdida Por Lactancia");
    fclose(datosGrafico);
}

void calcularvariacionMC_MSC_Lactancia(char nombre[40],int ejecuciones, int it){
	int maxQuincLact=MesesDeEspera+16; //Cambia de 13 a 16  por el secado c prob
    printf("\nCALCULOS MC MSC POR LACTANCIA\n");
	FILE *archivo=fopen(nombre,"r");
	int anio=-1;
	int esc=-1;
    int ejec=0,mes=0,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir; 
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt;
    int salAnt;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel;
    int calcMc_Msc[ejecuciones][maxQuincLact][3];//LACTANCIA -0 //MC  -1 //MSC-2
    memset(calcMc_Msc, 0, sizeof(calcMc_Msc));
    int i,j;
   
    char line[1024];
    fgets(line, sizeof(line), archivo);
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
              &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
    /* sl 1= en lactancia; 2= seca*/
  //  printf(" -- 1 -- %d",anio);
	     if(anio>=minAnioEstLactancia){
	    // 	printf(" -- 1 --");
	        if(sl==1) {
	    //    	printf(" -- sl --");
	        	calcMc_Msc[(ejec)][(indiceQel(del))][0] = calcMc_Msc[(ejec)][(indiceQel(del))][0] + 1;
	        }
	            
	        if(salud==2) {
	     //   	printf(" --s 2 --");
	        	calcMc_Msc[(ejec)][(indiceQel(del))][1] = calcMc_Msc[(ejec)][(indiceQel(del))][1] + 1;    
	        }
	            
	        if(salud==3) {
	     //   	printf(" -- s 3 --");
	        	calcMc_Msc[(ejec)][(indiceQel(del))][2] = calcMc_Msc[(ejec)][(indiceQel(del))][2] + 1; 
	        }
	               
        }
    }  
    FILE *datosGrafico=fopen(rutaArchivo(carp,1,"tablaLact_EvolucionMastitis.csv"),"w+");
    fprintf(datosGrafico,"Ejec;QuincenaLactancia;MC;MSC\n");

    FILE *datosGraficoMC=fopen(rutaArchivo(carp,1,"lact_EvolucionMC"),"w");
    FILE *datosGraficoMSC=fopen(rutaArchivo(carp,1,"lact_EvolucionMSC"),"w");

//    #x min     Q1          median      q3          max     width   label
    for(i=1;i<maxQuincLact;i++){ 
		               //Para cada quincena debo almacenar los resultados de MC/MSC correspndiente a la cantidad de ejecuciones 
		float calculosMC[ejecuciones];
		float calculosMSC[ejecuciones];
		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices.
		calculosMC[0]=0;
		calculosMSC[0]=0;
		for(j=1;j<ejecuciones;j++){  //Ejecucion cero no da resultados, luego cuento de 
		//printf("\n\t ej= %d\t qel=%d lact=%d mc=%d msc=%d - ",j,i,calcMc_Msc[j][i][0],calcMc_Msc[j][i][1],calcMc_Msc[j][i][2]);
			float calcMc= 0;
			float calcMsc= 0;
			if(calcMc_Msc[j][i][0]!=0){
				calcMc= ((float) calcMc_Msc[j][i][1])/((float) calcMc_Msc[j][i][0]); //cantMC/cantLactsl=1
				calcMsc= ((float) calcMc_Msc[j][i][2])/((float) calcMc_Msc[j][i][0]); 
			}
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
   // crearArchivoHTML(carp,"tablaLact_EvolucionMastitis.html",datosGrafico,"Datos Mastitis Por Lactancia");
    fclose(datosGrafico);   
}

void calcularVacasInfPorLactancia(char nombre[40],int ejecuciones, int it){
    printf("\nINFECCIONES EN MES LACTANCIA\n");
    FILE *archivo=fopen(nombre,"r");
    int ejec=0,mes=0,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir; 
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt;
    int salAnt;
    unsigned int nop;
    unsigned int infGral=4,infMC=5,infMSC=7;
    int prenez,qel;
    int anio=-1;
     int esc=-1;
	 int i=0;
    char line[1024];
    fgets(line, sizeof(line), archivo);
    //Pedir Memoria para seguimiento de vacas

	FILE *datosGrafico=fopen(rutaArchivo(carp,1,"tablaLact_InfecVaca.csv"),"w+");
    fprintf(datosGrafico,"id;PartosNop;Ejec;año;mesLactancia;infGral;infMC;infMSC\n");
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
              &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
        i++;
 		if(anio>=minAnioEstLactancia){
			if(indiceQel(del)>0 && indiceQel(del)<21){
			//	printf("id %d - ej %d - q %d - ",id,ejec,mes);
				if(infGral==0){
				//	printf("-> Aniog %d\n",anioo);
					fprintf(datosGrafico,"%d;%d;%d;%d;%d;%d;%d;%d\n",id,partos,ejec,anio,indiceQel(del),infGral,infMC,infMSC);
				}else if(infMC==0){
				//					printf("-> Anioc %d\n",anioo);
					fprintf(datosGrafico,"%d;%d;%d;%d;%d;%d;%d;%d\n",id,partos,ejec,anio,indiceQel(del),infGral,infMC,infMSC);
				}else if(infMSC==0){
				//					printf("-> Anios %d\n",anioo);
					fprintf(datosGrafico,"%d;%d;%d;%d;%d;%d;%d;%d\n",id,partos,ejec,anio,indiceQel(del),infGral,infMC,infMSC);
				}else if(infGral==1 && infMC==1 && infMSC==1){
					if(descarte!=descarte_rodeo || indiceQel(del)==20){
						fprintf(datosGrafico,"%d;%d;%d;%d;%d;%d;%d;%d\n",id,partos,ejec,anio,indiceQel(del),infGral,infMC,infMSC);
					}
					
				}
			}      
		}
    }  
    
    fclose(archivo);
  //  crearArchivoHTML(carp,"tablaLact_InfecVaca.html",datosGrafico,"Datos Infeccion por Lactancia");
    fclose(datosGrafico);
}

void calcularConteoCambioMastitis_Lactancia(char nombre[40],int ejecuciones, int it){
    printf("\nCONTEO DE VARIACION DE MASTITIS POR LACTANCIA\n");
    FILE *archivo=fopen(nombre,"r");
    int maxQuincLact=MesesDeEspera+16;
    FILE *salida;
   // char nombreDatosGrafico[60]="./ArchivosTambo/datos/tablaLact_ConteoVariacionMastitis.csv";
    salida=fopen(rutaArchivo(carp,1,"tablaLact_ConteoVariacionMastitis.csv"),"w+");
    fprintf(salida,"Ejec;QuincenaLactancia;1  1;1  2;1  3;2  1;2  2;2  3;3  1;3  2;3  3;Cant. Vacas\n");
  //  printf("\tEjec\tId\tServicios\n");
     int esc=-1;
    char line[1024];
    fgets(line, sizeof(line), archivo);//lee la linea de titulos
    unsigned int i,j,k,l;
    unsigned int datosVariacion[ejecuciones][maxQuincLact][9];
    memset(datosVariacion, 0, sizeof(datosVariacion));
    unsigned int limVacas[ejecuciones][maxQuincLact];
    memset(limVacas, 0, sizeof(limVacas));
    
	int ejec=0,mes,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir; 
	float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
	int pat,salAu,salAg,salSCN,salOStr,salECo,salOt;
	int anio=-1;
	int salAnt;
    unsigned int nop,infGral,infMC,infMSC;
    int prenez,qel;
	int lim=0;
	while ((EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
     &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc))){
		if(anio>=minAnioEstLactancia){
			if(sl==1){
				if(salAnt!=salud_inic){
					unsigned int cod=codCambioSalud(salAnt,salud); //codCambioSalud retorna la posicion a sumar en base al cambio
					datosVariacion[ejec][indiceQel(del)][cod]++;
					limVacas[ejec][indiceQel(del)]++;
				}
			}	
		}
	}

    //Fin del analisis de todas las ejecuciones	-las imprimo a un archivo
    for(j=1;j<ejecuciones;j++){
        for(i=1;i<maxQuincLact;i++){
		    fprintf(salida,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",j,i,datosVariacion[j][i][0],datosVariacion[j][i][1],datosVariacion[j][i][2],datosVariacion[j][i][3],datosVariacion[j][i][4],datosVariacion[j][i][5],datosVariacion[j][i][6],datosVariacion[j][i][7],datosVariacion[j][i][8],limVacas[j][i]);
	    }
    }
    
    FILE *datosGrafico1_2=fopen(rutaArchivo(carp,1,"lact_EvolucionSaludNuevaMC"),"w");    
    FILE *datosGrafico1_3=fopen(rutaArchivo(carp,1,"lact_EvolucionSaludNuevaMSC"),"w");    
    FILE *datosGrafico3_3=fopen(rutaArchivo(carp,1,"lact_EvolucionSaludCronicaMSC"),"w");

 	for(i=1;i<maxQuincLact;i++){ 
		               //Para cada quincena debo almacenar los resultados de MC/MSC correspndiente a la cantidad de ejecuciones 
		float calculos1_2[ejecuciones];
		float calculos1_3[ejecuciones];
		float calculos3_3[ejecuciones];
		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices.
		calculos1_2[0]=0;
		calculos1_3[0]=0;
		calculos3_3[0]=0;
		for(j=1;j<ejecuciones;j++){  //Ejecucion cero no da resultados, luego cuento de 
		     //printf("\nlimite ej %d it %d valor %d \n",(j),(i),limVacas[j][i]);
			calculos1_2[j]=((float)datosVariacion[j][i][1])/((float)limVacas[j][i]);
			calculos1_3[j]=((float)datosVariacion[j][i][2])/((float)limVacas[j][i]);  
			calculos3_3[j]=((float)datosVariacion[j][i][8])/((float)limVacas[j][i]);       
//			fprintf(datosGrafico,"%d;%d;%.3f;%.3f \n",(j),(i),calcMc,calcMsc);
		} 
		escribirDatosGrafico(datosGrafico1_2,calculos1_2,ejecuciones,(i));
		escribirDatosGrafico(datosGrafico1_3,calculos1_3,ejecuciones,(i));
		escribirDatosGrafico(datosGrafico3_3,calculos3_3,ejecuciones,(i));
    } 
  
 	fclose(datosGrafico1_2);
 	fclose(datosGrafico1_3);
 	fclose(datosGrafico3_3);
    fclose(archivo);
   // crearArchivoHTML(carp,"tablaLact_ConteoVariacionMastitis.html",salida,"Datos Variacion Salud Lactancia");
    fclose(salida);
}

void calcularDescarteAborto_Lactancia(char nombre[40],int ejecuciones, int it){
	int maxQuincLact=MesesDeEspera+16; //Cambia de 13 a 16  por el secado c prob
    printf("\nDESCARTE POR ABORTO LACTANCIA\n");
	FILE *archivo=fopen(nombre,"r");
    int ejec=0,mes=0,orden,id,partos,pv,sl,del,merito,salud,descarte,rcs,sir; 
    float producdiaria,producMens,resultPerdidaMC,resultPerdidaMSC;
    int pat,salAu,salAg,salSCN,salOStr,salECo,salOt;
    int salAnt;
    int anio=-1;
    int esc=-1;
	unsigned int nop,infGral,infMC,infMSC;
	int prenez,qel;
    int cantxMesLact[ejecuciones][maxQuincLact];   			 memset(cantxMesLact, 0, sizeof(cantxMesLact)); //Rodeo-0 //Descarte - Infertilidad-1 //Muertas -2 //Aborto-3 //Vejez-4
   
	int i,j;
    char line[1024];
    fgets(line, sizeof(line), archivo);
    
    while (EOF != fscanf(archivo,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
              &ejec,&mes,&anio,&orden,&id,&partos,&nop,&pv,&prenez,&sl,&del,&qel,&producdiaria,&producMens,&merito,&sir,&salud,&descarte,&rcs,&resultPerdidaMC,&resultPerdidaMSC,&pat,&salAu,&salAg,&salSCN,&salOStr,&salECo,&salOt,&infGral,&infMC,&infMSC,&salAnt,&esc)){
    /* sl 1= en lactancia; 2= seca*/
        if(anio>=minAnioEstLactancia){
        	if(descarte==descarte_aborto){
	        	cantxMesLact[(ejec)][qel]= cantxMesLact[(ejec)][qel]+1; 
	        }	        
        }   
    }  
    
    FILE *datosGrafico =fopen(rutaArchivo(carp,1,"lact_EvolucionDescAborto"),"w");
    
//    #x min     Q1          median      q3          max     width   label
    for(i=1;i<maxQuincLact;i++){ 
		               //Para cada quincena debo almacenar los resultados de MC/MSC correspndiente a la cantidad de ejecuciones 
		float calculosTotal[ejecuciones];
		//Se deja en los vectores la posicion 0 pero no se usa, solo que es necesario para el calculo de indices.
		calculosTotal[0]=0;
		for(j=1;j<ejecuciones;j++){  //Ejecucion cero no da resultados, luego cuento de 
			calculosTotal[j]= ((float) cantxMesLact[j][i]);
		} 
		escribirDatosGrafico(datosGrafico,calculosTotal,ejecuciones,(i));
	
    } 
    fclose(archivo);
    fclose(datosGrafico);
}

