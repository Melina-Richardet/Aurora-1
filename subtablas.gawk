gawk '{FS=";";if($7*$9 > 0) if ($3 > 1) print $7  "\t" $9}' $1 > prodDiariaVacas-D-L
gawk '{FS=";";if($7*$9 > 0) if ($3 == 1) print $7  "\t" $9}' $1 > prodDiariaVaqs-D-L
