echo GRAFICOS

gnuplot  -e "filename='"$1"/datos/quinc_EvolucionLactancia'" grafica_quinc.gnuplot
echo quinc_EvolucionLactancia
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionPreniadas'" grafica_quinc.gnuplot
echo quinc_EvolucionPreniadas
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionDescarteAbo'" grafica_quinc.gnuplot
echo quinc_EvolucionDescarteAbo
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionDescarteInf'" grafica_quinc.gnuplot
echo quinc_EvolucionDescarteInf
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionDescarteMue'" grafica_quinc.gnuplot
echo quinc_EvolucionDescarteMue
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionDescarteVie'" grafica_quinc.gnuplot
echo quinc_EvolucionDescarteVie
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionMC'" grafica_quinc.gnuplot
echo quinc_EvolucionMClinica
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionMSC'" grafica_quinc.gnuplot
echo quinc_EvolucionMSubclinica
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionSaludNuevaMC'" grafica_quinc.gnuplot
echo quinc_EvolucionSaludNuevaMC
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionSaludNuevaMSC'" grafica_quinc.gnuplot
echo quinc_EvolucionSaludNuevaMSC
gnuplot  -e "filename='"$1"/datos/quinc_EvolucionSaludCronicaMSC'" grafica_quinc.gnuplot
echo  quinc_EvolucionSaludCronicaMSC

#gnuplot  -e "filename='"$1"/datos/'" grafica_quinc.gnuplot


gnuplot  -e "filename='"$1"/datos/lact_EvolucionMC'" grafica_lact.gnuplot
echo lact_EvolucionMClinica
gnuplot  -e "filename='"$1"/datos/lact_EvolucionMSC'" grafica_lact.gnuplot
echo lact_EvolucionMSubclinica
gnuplot  -e "filename='"$1"/datos/lact_EvolucionPerdidaTotalMC'" grafica_lact.gnuplot
echo lact_EvolucionPerdidaTotalMClinica
gnuplot  -e "filename='"$1"/datos/lact_EvolucionPerdidaTotalMSC'" grafica_lact.gnuplot
echo  lact_EvolucionPerdidaTotalMSubclinica
gnuplot  -e "filename='"$1"/datos/lact_EvolucionPerdidaPromedioMC'" grafica_lact.gnuplot
echo lact_EvolucionPerdidaPromedioMClinica
gnuplot  -e "filename='"$1"/datos/lact_EvolucionPerdidaPromedioMSC'" grafica_lact.gnuplot
echo lact_EvolucionPerdidaPromedioMSubclinica
gnuplot  -e "filename='"$1"/datos/lact_EvolucionSaludNuevaMC'" grafica_lact.gnuplot
echo lact_EvolucionSaludNuevaMC
gnuplot  -e "filename='"$1"/datos/lact_EvolucionSaludNuevaMSC'" grafica_lact.gnuplot
echo lact_EvolucionSaludNuevaMSC
gnuplot  -e "filename='"$1"/datos/lact_EvolucionSaludCronicaMSC'" grafica_lact.gnuplot
echo  lact_EvolucionSaludCronicaMSC
gnuplot  -e "filename='"$1"/datos/lact_EvolucionDescAborto'" grafica_lact.gnuplot
echo lact_EvolucionDescAborto

#gnuplot  -e "filename='"$1"/datos/'" grafica_lact.gnuplot

gnuplot  -e "filename='"$1"/datos/anual_PerdidaMC'" grafica_anual.gnuplot
echo anual_PerdidaMC
gnuplot  -e "filename='"$1"/datos/anual_PerdidaMSC'" grafica_anual.gnuplot
echo anual_PerdidaMSC
gnuplot  -e "filename='"$1"/datos/anual_PerdidaMTot'" grafica_anual.gnuplot
echo anual_PerdidaMTot
gnuplot  -e "filename='"$1"/datos/anual_DescarteMC'" grafica_anual.gnuplot
echo anual_DescarteMC
gnuplot  -e "filename='"$1"/datos/anual_DescarteMSC'" grafica_anual.gnuplot
echo anual_DescarteMSC
gnuplot  -e "filename='"$1"/datos/anual_DescarteMTot'" grafica_anual.gnuplot
echo anual_DescarteMTot
gnuplot  -e "filename='"$1"/datos/anual_PrenezMC'" grafica_anual.gnuplot
echo anual_PrenezMC
gnuplot  -e "filename='"$1"/datos/anual_PrenezMSC'" grafica_anual.gnuplot
echo anual_PrenezMSC
gnuplot  -e "filename='"$1"/datos/anual_PrenezMTot'" grafica_anual.gnuplot
echo  anual_PrenezMTot
gnuplot  -e "filename='"$1"/datos/anual_CantidadMC'" grafica_anual.gnuplot
echo  anual_CantidadMC
gnuplot  -e "filename='"$1"/datos/anual_CantidadMSC'" grafica_anual.gnuplot
echo anual_CantidadMSC
gnuplot  -e "filename='"$1"/datos/anual_CantidadMTot'" grafica_anual.gnuplot
echo anual_CantidadMTot
gnuplot  -e "filename='"$1"/datos/anual_RcsTambo'" grafica_anual.gnuplot
echo anual_RcsTambo
gnuplot  -e "filename='"$1"/datos/anual_Mes17'" grafica_anual.gnuplot
echo anual_Mes17
gnuplot  -e "filename='"$1"/datos/anual_GastoTotal'" grafica_anual.gnuplot
echo anual_GastoTotal
gnuplot  -e "filename='"$1"/datos/anual_PerdTotal'" grafica_anual.gnuplot
echo anual_PerdTotal
gnuplot  -e "filename='"$1"/datos/anual_CostoTotal'" grafica_anual.gnuplot
echo anual_CostoTotal

#gnuplot  -e "filename='"$1"/datos/'" grafica_anual.gnuplot


