 set terminal png
 set output sprintf('%s.png', filename)
 #set title ""
 #ancho de barra
 set bars 1.0
  set xrange [0:7<*]
 set style fill empty
 unset key 
 plot filename using 1:3:2:6:5 with candlesticks title 'Quartiles' whiskerbars, filename using 1:4:4:4:4 with candlesticks lt -1 notitle
