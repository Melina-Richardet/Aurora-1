#include <stdlib.h>
#include <stdio.h>

void strcpy1 (char v[100], char w[100]){    
    int i;
    for(i=0;i<100;i++)
       v[i]=w[i];
}

char* rutaArchivo(char carpeta[10],int enDatos,char nombre[50]){
 	char arch_salida[100];
    strcpy(arch_salida,"./ArchivosTambo/");
    strcat(arch_salida, carpeta);
    strcat(arch_salida, "/");
    if(enDatos==1)
    	strcat(arch_salida, "datos/");
    strcat(arch_salida, nombre);
    //return arch_salida;// &arch_salida[0];
    
    char *q;
    q=malloc(100);
    strcpy1(q,arch_salida);
    //printf("ruta '%s' \n", q);
    return q;
}

float sumayPromVectorFloat(float datos[],int limDatos,int  exclO){
	int i=0;
	float result=0;
    for (i=0; i<limDatos; i++) {
   //     printf("dat %f",datos[i]);
        result +=datos[i];
    }
   //  printf("res %f",result);
     int lim=limDatos;
     if(exclO==1) lim=limDatos-1;
     float prom=result/lim;
   //  printf("res %f",prom);
     return prom;
}

int sumaVectorInt(int datos[],int limDatos){
	int i=0;
	int result=0;
    for (i=0; i<limDatos; i++) {
        printf("dat %d",datos[i]);
        result +=datos[i];
    }
     printf("res %d",result);
     return result;
}

int indice24(int nro,char esIndice){
	int indice=0;
	if(nro!=0){
		int resto=nro % 24;
	    indice= nro / 24;
	    if(resto != 0) indice++;
	    if(esIndice==1) indice--;
    }
    return indice;
}

int indiceQel(int del){  //Funcion para obtener a partir del del el valor del qel equivalente, va que la vble qel del obj Vaca representa otro valor
	int qel=0;
	if(del!=0) qel=del/15;
	return qel;
}

int generarAleatorio(int inicial,int final){
    int numero = rand () % (final-inicial+1) + inicial;
    return numero;
}

int probab_exito(float p){
    long int lim;
    lim=p*(RAND_MAX);
  //  printf("valor prob %f ",p);
    int aleat=rand();
    if (lim >= aleat)
		return 1; /* tuve suerte */
    else
	    return 0; /* mala suerte */
}
//Prob: Sana, Aureus, Agalactiae, Scn,Otros,OtrosEstrepto,eColi,Otros
unsigned int probab_Patogeno(float proba[]){
	int maximo=RAND_MAX;
   // printf("valor RAND %d ",maximo);
    float lim_0=(float)maximo*proba[0];
    float lim_1=(float)maximo*proba[1]+(float)lim_0;
    float lim_2=(float)maximo*proba[2]+(float)lim_1;
    float lim_3=(float)maximo*proba[3]+(float)lim_2;
    float lim_4=(float)maximo*proba[4]+(float)lim_3;
    float lim_5=(float)maximo*proba[5]+(float)lim_4;
    float lim_6=(float)maximo*proba[6]+(float)lim_5;
  /*  printf("\n --> limite 0: %f ",lim_0); 
    printf("\n --> limite 1: %f ",lim_1); 
    printf("\n --> limite 2: %f ",lim_2); 
    printf("\n --> limite 3: %f ",lim_3); 
    printf("\n --> limite 4: %f ",lim_4); 
    printf("\n --> limite 5: %f ",lim_5);
    printf("\n --> limite 6: %f ",lim_6);  */
    
    int aleat=rand();
   // printf("\n --> aleatorio: %d ",aleat); 

    int result=0;
    if (aleat <=lim_0)
	    result=0; 
    else if(aleat <=lim_1)
	    result=1; 
/*	else if(aleat <=lim_2)
        result=2;
    else if(aleat <=lim_3)
        result=3;
    else if(aleat <=lim_4)
        result=4;
    else if(aleat <=lim_5)
        result=5;
    else if(aleat <=lim_6)
        result=6;  */
    //printf("\n --> result: %d ",result);
    return result;
}

float probNoAbortar(int mesPreniez){
	float result=0;
	if(mesPreniez >2){ //verificar 17/11/2017
	if (mesPreniez <6)
	    result=0.942; 
    else if(mesPreniez <8)
	    result=0.959; 
	else if(mesPreniez <10)
        result=0.975;
    else if(mesPreniez <12)
        result=0.992;
    else if(mesPreniez <14)
        result=0.996;
    else 
        result=0.992;
    }
    return result;
}

//agrega meli esto el 2021_09_05:
float probNoAbortar2(int mesPreniez){//agrego probNoAbortar2  - meli sept 2021
	float result=0;
	if(mesPreniez >2){ //verificar 17/11/2017
	if (mesPreniez <6)
	    result=0.942; 
    else if(mesPreniez <8)
	    result=0.959; 
	else if(mesPreniez <10)
        result=0.975;
    else if(mesPreniez <12)
        result=0.992;
    else if(mesPreniez <14)

        result=0.996;
    else 
        result=0.992;
    }
    return result;
}

void qs(float lista[],int limite_izq,int limite_der){
    float temporal,pivote;
    int izq,der;
    izq=limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2];
    do{
        while(lista[izq]<pivote && izq<limite_der)izq++;
        while(pivote<lista[der] && der > limite_izq)der--;
        if(izq <=der){
            temporal= lista[izq];
            lista[izq]=lista[der];
            lista[der]=temporal;
            izq++;
            der--;
        }
    }while(izq<=der);
    if(limite_izq<der){qs(lista,limite_izq,der);}
    if(limite_der>izq){qs(lista,izq,limite_der);}
}

void quicksort(float lista[],int n){
    qs(lista,0,n-1);
}

//version 2 de split
char* SplitString2(char* str, char sep){
    return str;
}

void crearArchivoHTML(char carpeta[10],char nombreHTML[20],FILE *archivo,char title[30]){
/*	char arch_salida[45];
	strcpy(arch_salida,"./ArchivosTambo/datos/");
	strcat(arch_salida, nombreHTML);*/
	FILE *salida=fopen(rutaArchivo(carpeta,1,nombreHTML),"w");

	int aaa=ftell(archivo);
	rewind(archivo);
	int aaa2=ftell(archivo);
		
	fprintf(salida,"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
	fprintf(salida,"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fprintf(salida," <head>\n");
	fprintf(salida,"  <title>%s</title>\n",title);
	fprintf(salida,"  <meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' />\n");
	fprintf(salida,"  <link rel='shortcut icon' href='../infoEstadisticas/favicon.ico' type='image/x-icon' />\n");
	fprintf(salida,"  <script type='text/javascript' src='../infoEstadisticas/js/jquery-ui-1.10.4.custom/js/jquery-1.10.2.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' src='../infoEstadisticas/js/jquery-ui-1.10.4.custom/js/jquery-migrate-1.2.1.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' src='../infoEstadisticas/js/jquery-ui-1.10.4.custom/js/jquery-ui-1.10.4.custom.js'></script>\n");
	fprintf(salida,"  <link type='text/css' href='../infoEstadisticas/js/jquery-ui-1.10.4.custom/css/ui-lightness/jquery-ui-1.10.4.custom.css' rel='stylesheet' />\n");
	fprintf(salida,"  <link rel='stylesheet' href='../infoEstadisticas/js/jquery-ui-1.10.4.custom/development-bundle/themes/base/jquery.ui.all.css' type='text/css' media='all' />\n");
	fprintf(salida,"  <link href='../infoEstadisticas/estilos.css' rel='stylesheet' type='text/css' media='screen, projection' />\n");
	fprintf(salida,"  <style type='text/css' title='currentStyle'>\n");
	fprintf(salida,"	@import '../infoEstadisticas/js/DataTables/media/css/demo_page.css';\n"); 
	fprintf(salida,"	@import '../infoEstadisticas/js/DataTables/extras/TableTools/media/css/TableTools_JUI.css';\n");
	fprintf(salida," 	@import '../infoEstadisticas/js/DataTables/media/css/demo_table_jui.css';\n");
	fprintf(salida,"	.ui-tabs .ui-tabs-panel { padding: 10px };\n");
	fprintf(salida,"  </style>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/media/js/jquery.dataTables.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/TableTools/media/js/ZeroClipboard.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/TableTools/media/js/TableTools.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/ColVis/media/js/ColVis.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/FixedColumns/media/js/FixedColumns.js'></script>\n");
	fprintf(salida,"  <style type='text/css' title='currentStyle'>\n");
	fprintf(salida,"    .ColVis {\n");
	fprintf(salida,"	float: left;\n");
	fprintf(salida,"	float: left;\n");
	fprintf(salida,"	margin-bottom: 0;\n");
	fprintf(salida,"	padding: 3px 10px; \n");
	fprintf(salida,"	border: 1px solid #D3D3D3\n");
	fprintf(salida,"    }\n");
	fprintf(salida,"    .dataTables_length {\n");        
	fprintf(salida,"	width: auto;\n");
	fprintf(salida,"    }\n");        
	fprintf(salida,"    @import '../infoEstadisticas/js/DataTables/extras/ColVis/media/css/ColVis.css';\n");        
	fprintf(salida,"  </style>\n");
	fprintf(salida," </head>\n");     	
	fprintf(salida," <body >\n");
//Analisis CSV        
	fprintf(salida,"<script type=\"text/javascript\" charset=\"utf-8\">\n");
	fprintf(salida,"var asInitVals = new Array();\n");
	fprintf(salida,"   $(document).ready( function () {\n");			  
	fprintf(salida,"     var oTable =  $(\"#example2\").dataTable({\n");		  
	fprintf(salida,"           \"sScrollX\": \"100\037\",\n");
	fprintf(salida,"           \"sScrollInfinite\": true,\n");  //"sScrollXInner": "100%",
	fprintf(salida,"           \"bScrollCollapse\": true,\n");
	fprintf(salida,"		   \"bJQueryUI\": true,\n");
	fprintf(salida,"           \"iDisplayLength\": 25,\n");
	fprintf(salida,"           \"sPaginationType\": \"full_numbers\",\n");
	fprintf(salida,"           \"aaSorting\": [[ 0, \"asc\" ]],\n"); 
	fprintf(salida,"		   \"sDom\": '<\"H\"Tlr>t<\"F\"ip>',\n");
	fprintf(salida,"		   \"oTableTools\": {\n");
	fprintf(salida,"				\"sSwfPath\": \"../infoEstadisticas/js/DataTables/extras/TableTools/media/swf/copy_cvs_xls_pdf.swf\",\n");
	fprintf(salida,"				\"aButtons\": [\"print\"]\n");
	fprintf(salida,"			}\n");
	fprintf(salida,"       });\n");
	fprintf(salida,"$(\"tfoot input\").keyup( function () {\n");

    /* Filter on the column (the index) of this element */
    fprintf(salida,"oTable.fnFilter( this.value, $(\"tfoot input\").index(this) );\n");
	fprintf(salida,"} );\n");
    fprintf(salida,"    $(\"tfoot input\").each( function (i) { asInitVals[i] = this.value; } );\n");
    fprintf(salida,"$(\"tfoot input\").focus( function () {\n");
    fprintf(salida,"if ( this.className == \"search_init\" ) {\n");
    fprintf(salida,"    this.className = \"\";\n");
    fprintf(salida,"    this.value = \"\";\n");
    fprintf(salida,"}\n");
    fprintf(salida,"} );\n");
 
	fprintf(salida,"$(\"tfoot input\").blur( function (i) {\n");
    fprintf(salida,"if ( this.value == \"\" ) {\n");
    fprintf(salida,"    this.className = \"search_init\";\n");
    fprintf(salida,"    this.value = asInitVals[$(\"tfoot input\").index(this)];\n");
    fprintf(salida,"}\n");
	fprintf(salida,"} );\n");
	fprintf(salida,"    });\n");
	fprintf(salida,"</script>\n");
	fprintf(salida,"<div id=\"contenedor\" style=\"width:100\037\">\n");
	fprintf(salida,"       <table border=\"0\" id=\"example2\" width=\"100\037\" class=\"displaytabletools\" cellpadding=\"0\" cellspacing=\"0\" >\n");
	//Tabla cabecera
	int nroLinea=1;
	char sep = ';';
	char linea[1024];
	unsigned char cantColumnas=1;
    while (fgets(linea, sizeof(linea), archivo) != NULL)  {
		char *output, *temp;
		int done = 0;
		output = SplitString2(linea, sep);
		if(nroLinea==1){
			fprintf(salida,"       <thead>\n");
			fprintf(salida,"       <tr>");
		    char * temp;
		    char * field;
		    field = output;
		    for(temp = field; *temp; ++temp){ 
		       if (*temp == sep){
		          fprintf(salida,"<th > %.*s</th>",  (int)(temp-field), field);
		          field = temp+1;
		          cantColumnas++;
		       }
		    }
			fprintf(salida,"<th > %.*s</th>",  (int)(temp-field), field);
			fprintf(salida,"       </tr>\n");
			fprintf(salida,"       </thead>\n");
			fprintf(salida,"        <tbody>\n");
		}else{
			fprintf(salida,"       <tr>");
			char *temp;
		    char * field;
		    field = output;
		    for(temp = field; *temp; ++temp){ 
		       if (*temp == sep){
		          fprintf(salida,"<td > %.*s </td>", (int)(temp-field), field);
		          field = temp+1;
		       }
		    }
		    fprintf(salida,"<td > %.*s</td>", (int)(temp-field), field);
			fprintf(salida,"       </tr>\n");
		}
		nroLinea++;
	}
	//Fin de tabla.
	fprintf(salida,"        </tbody>\n");
	fprintf(salida,"<tfoot>\n");
	fprintf(salida,"<tr>\n");
	int k=0;
	for(k=0;k<cantColumnas;k++){
		fprintf(salida,"<th><input type=\"text\" name=\"search_%d\" value=\"Buscar\" class=\"search_init\" /></th>\n",k);
	}
	fprintf(salida,"</tr>\n");
	fprintf(salida,"</tfoot>\n");
	fprintf(salida,"     </table>\n"); 
	fprintf(salida,"     </div>\n"); 
	fprintf(salida," </body>\n");
	fprintf(salida,"</html>\n"); 
	fclose(salida);
}

unsigned int codCambioSalud(int saludAnt,int saludAct){
	if(saludAnt==1 && saludAct==1)	return 0;
	if(saludAnt==1 && saludAct==2)	return 1;
	if(saludAnt==1 && saludAct==3)	return 2;
	if(saludAnt==2 && saludAct==1)	return 3;
	if(saludAnt==2 && saludAct==2)	return 4;
	if(saludAnt==2 && saludAct==3)	return 5;
	if(saludAnt==3 && saludAct==1)	return 6;
	if(saludAnt==3 && saludAct==2)	return 7;
	if(saludAnt==3 && saludAct==3)	return 8;
}

void crearArchivoHTMLAnual(char carpeta[10],char nombreHTML[20],FILE *archivo,char title[30],int longitud,int iterac, int colsAnio){
/*	char arch_salida[45];
	strcpy(arch_salida,"./ArchivosTambo/datos/");
	strcat(arch_salida, nombreHTML);*/
	FILE *salida=fopen(rutaArchivo(carpeta,1,nombreHTML),"w");

	int aaa=ftell(archivo);
	rewind(archivo);
	int aaa2=ftell(archivo);
		
	fprintf(salida,"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
	fprintf(salida,"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fprintf(salida," <head>\n");
	fprintf(salida,"  <title>%s</title>\n",title);
	fprintf(salida,"  <meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' />\n");
	fprintf(salida,"  <link rel='intcut icon' href='../favicon.ico' type='image/x-icon' />\n");
	fprintf(salida,"  <script type='text/javascript' src='../infoEstadisticas/js/jquery-1.10.2.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' src='../infoEstadisticas/js/jquery-migrate-1.2.1.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' src='../infoEstadisticas/js/jquery-ui-1.10.4.custom/js/jquery-ui-1.10.4.custom.js'></script>\n");
	fprintf(salida,"  <link type='text/css' href='../infoEstadisticas/js/jquery-ui-1.10.4.custom/css/ui-lightness/jquery-ui-1.10.4.custom.css' rel='stylesheet' />\n");
	fprintf(salida,"  <link rel='stylesheet' href='../infoEstadisticas/js/jquery-ui-1.10.4.custom/development-bundle/themes/base/jquery.ui.all.css' type='text/css' media='all' />\n");
	fprintf(salida,"  <link href='../infoEstadisticas/estilos.css' rel='stylesheet' type='text/css' media='screen, projection' />\n");
	fprintf(salida,"  <style type='text/css' title='currentStyle'>\n");
	fprintf(salida,"	@import '../infoEstadisticas/js/DataTables/media/css/demo_page.css';\n"); 
	fprintf(salida,"	@import '../infoEstadisticas/js/DataTables/extras/TableTools/media/css/TableTools_JUI.css';\n");
	fprintf(salida," 	@import '../infoEstadisticas/js/DataTables/media/css/demo_table_jui.css';\n");
	fprintf(salida,"	.ui-tabs .ui-tabs-panel { padding: 10px };\n");
	fprintf(salida,"  </style>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/media/js/jquery.dataTables.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/TableTools/media/js/ZeroClipboard.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/TableTools/media/js/TableTools.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/ColVis/media/js/ColVis.js'></script>\n");
	fprintf(salida,"  <script type='text/javascript' charset='utf-8' src='../infoEstadisticas/js/DataTables/extras/FixedColumns/media/js/FixedColumns.js'></script>\n");
	fprintf(salida,"  <style type='text/css' title='currentStyle'>\n");
	fprintf(salida,"    .ColVis {\n");
	fprintf(salida,"	float: left;\n");
	fprintf(salida,"	float: left;\n");
	fprintf(salida,"	margin-bottom: 0;\n");
	fprintf(salida,"	padding: 3px 10px; \n");
	fprintf(salida,"	border: 1px solid #D3D3D3\n");
	fprintf(salida,"    }\n");
	fprintf(salida,"    .dataTables_length {\n");        
	fprintf(salida,"	width: auto;\n");
	fprintf(salida,"    }\n");        
	fprintf(salida,"    @import '../infoEstadisticas/js/DataTables/extras/ColVis/media/css/ColVis.css';\n");        
	fprintf(salida,"  </style>\n");
	fprintf(salida," </head>\n");     	
	fprintf(salida," <body >\n");
//Analisis CSV        
	fprintf(salida,"<script type=\"text/javascript\" charset=\"utf-8\">\n");
	fprintf(salida,"var asInitVals = new Array();\n");
	fprintf(salida,"   $(document).ready( function () {\n");			  
	fprintf(salida,"     var oTable =  $(\"#example2\").dataTable({\n");		  
	fprintf(salida,"           \"sScrollX\": \"100\037\",\n");
	fprintf(salida,"           \"sScrollInfinite\": true,\n");  
	fprintf(salida,"           \"bScrollCollapse\": true,\n");
	fprintf(salida,"		   \"bJQueryUI\": true,\n");
	fprintf(salida,"           \"iDisplayLength\": 25,\n");
	fprintf(salida,"           \"sPaginationType\": \"full_numbers\",\n");
	fprintf(salida,"           \"aaSorting\": [[ 1, \"asc\" ]],\n");  
	fprintf(salida,"		   \"sDom\": '<\"H\"Tlr>t<\"F\"ip>',\n");
	fprintf(salida,"		   \"oTableTools\": {\n");
	fprintf(salida,"				\"sSwfPath\": \"../infoEstadisticas/js/DataTables/extras/TableTools/media/swf/copy_cvs_xls_pdf.swf\",\n");
	fprintf(salida,"				\"aButtons\": [	\"print\"]\n");
	fprintf(salida,"			}\n");
	fprintf(salida,"       });\n");
	fprintf(salida,"$(\"tfoot input\").keyup( function () {\n");
    fprintf(salida,"oTable.fnFilter( this.value, $(\"tfoot input\").index(this) );\n");
	fprintf(salida,"} );\n");
    fprintf(salida,"    $(\"tfoot input\").each( function (i) { asInitVals[i] = this.value; } );\n");
    fprintf(salida,"$(\"tfoot input\").focus( function () {\n");
    fprintf(salida,"if ( this.className == \"search_init\" ) {\n");
    fprintf(salida,"    this.className = \"\";\n");
    fprintf(salida,"    this.value = \"\";\n");
    fprintf(salida,"}\n");
    fprintf(salida,"} );\n");
 
	fprintf(salida,"$(\"tfoot input\").blur( function (i) {\n");
    fprintf(salida,"if ( this.value == \"\" ) {\n");
    fprintf(salida,"    this.className = \"search_init\";\n");
    fprintf(salida,"    this.value = asInitVals[$(\"tfoot input\").index(this)];\n");
    fprintf(salida,"}\n");
	fprintf(salida,"} );\n");
	fprintf(salida,"    });\n");
	fprintf(salida,"</script>\n");
	fprintf(salida,"<div id=\"contenedor\" style=\"width:100\037\">\n");
	fprintf(salida,"       <table border=\"0\" id=\"example2\" width=\"100\037\" class=\"displaytabletools\" cellpadding=\"0\" cellspacing=\"0\" >\n");
	//Tabla cabecera
	int nroLinea=1;
	char sep = ';';
	char linea[1024];
	unsigned char cantColumnas=1;
    while (fgets(linea, sizeof(linea), archivo) != NULL)  {
		char *output, *temp;
		int done = 0;
		output = SplitString2(linea, sep);
		if(nroLinea==1){
			fprintf(salida,"       <thead>\n");
			fprintf(salida,"       <tr>");
			fprintf(salida,"<th > &nbsp; </th>");
		    int h=0;
			for(h=0;h<longitud;h++){
				fprintf(salida,"<th colspan=\"%d\" border=\"3\"> Anio %d </th>",colsAnio,(h+1));
			}
			fprintf(salida,"       </tr>");
			fprintf(salida,"       <tr>");
		    char *temp;
		    char * field;
		    field = output;
		    for(temp = field; *temp; ++temp){ 
		       if (*temp == sep){
		          fprintf(salida,"<th > %.*s</th>",  (int)(temp-field), field);
		          field = temp+1;
		          cantColumnas++;
		       }
		       
		    }
			fprintf(salida,"<th > %.*s</th>",  (int)(temp-field), field);
			fprintf(salida,"       </tr>\n");
			fprintf(salida,"       </thead>\n");
			fprintf(salida,"        <tbody>\n");
		}else{
			fprintf(salida,"       <tr>");
			char *temp;
		    char * field;
		    field = output;
		    for(temp = field; *temp; ++temp){ 
		       if (*temp == sep){
		          fprintf(salida,"<td > %.*s </td>",  (int)(temp-field), field);
		          field = temp+1;
		       }
		    }
		    fprintf(salida,"<td > %.*s</td>",  (int)(temp-field), field);
			fprintf(salida,"       </tr>\n");
		}
		nroLinea++;
	}
	//Fin de tabla.
	fprintf(salida,"        </tbody>\n");
	fprintf(salida,"<tfoot>\n");
	fprintf(salida,"<tr>\n");
	int k=0;
	for(k=0;k<cantColumnas;k++){
		fprintf(salida,"<th><input type=\"text\" name=\"search_%d\" value=\"Buscar\" class=\"search_init\" /></th>\n",k);
	}
		
	fprintf(salida,"</tr>\n");
	fprintf(salida,"</tfoot>\n");
	fprintf(salida,"     </table>\n"); 
	fprintf(salida,"     </div>\n"); 
	fprintf(salida," </body>\n");
	fprintf(salida,"</html>\n"); 
	fclose(salida);
}

//Funciones de verificacion de funciones
void TestSplit2(void){
    char* input = "Hello Word of C";
    char *output, *temp;
    char * field;
    char sep = ' ';
    int cnt = 1;
    output = SplitString2(input, sep);
    field = output;
    for(temp = field; *temp; ++temp){ 
       if (*temp == sep){
          printf("%d.) %.*s\n", cnt++,(int)(temp-field), field);
          field = temp+1;
       }
    }
    printf("%d.) %.*s\n", cnt++, (int)(temp-field), field);
}

void verificarOrdenamiento(float lista[],int size){
    printf("\nSin orden: ");
    int i=0;
    for (i=0; i<size; i++) {
        printf("%f",lista[i]);
        if(i<size-1)
            printf(", ");
    }
    quicksort(lista,size);
    printf("\nCon Orden: ");
    for (i=0; i<size; i++) {
        printf("%f",lista[i]);
        if(i<size-1)
            printf(", ");
    }
}
