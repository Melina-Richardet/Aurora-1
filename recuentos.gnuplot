a=578;b=-0.4274;c=-0.003
f(x)=a * x**b * exp(-c*x)
fit f(x) "recuentosVacas-D-L" u 1:2  via a,b,c
set print "parametrosRecuentosVacas.txt"
print a, b , c 

quit
