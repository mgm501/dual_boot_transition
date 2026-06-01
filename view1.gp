! ./orbit > o.dat

set size square

unset object
set title "satellite in earth orbit"
unset label
set xlabel "time [hrs]"
set ylabel "distance [km from surface]"
unset key

plot "o.dat" using 1:2 w l

pause -1

set ylabel "polar angle [radians]"
plot "o.dat" using 1:3 w l

pause -1

set object 1 rect from -100,-100 to 100,100 fc lt 1 lw 0
set xlabel "x position [km]"
set ylabel "y position [km]"
plot "o.dat" using ($2*cos($3)):($2*sin($3)) w l

pause -1