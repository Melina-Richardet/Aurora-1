a=15;b=0.19;c=0.002
f(x)=a * x**b * exp(-c*x)
fit f(x) "prodDiariaVacas-D-L" u 1:2  via a,b,c
set print "_parametrosProdDiariaVacas.txt"
print a, b , c 

fit f(x) "prodDiariaVaqs-D-L" u 1:2  via a,b,c
set print "_parametrosProdDiariaVaqs.txt"
print a, b , c 

quit
