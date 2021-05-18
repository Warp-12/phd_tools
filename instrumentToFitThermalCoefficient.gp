# A = (T1 + T2) / 2
# B = (T2 - T1) / 2 
# C = sqrt( 1 / 4 * lambda * t)

set print "lambda_150_450.dat"    

do for [I=1:100] {
reset
set encoding iso_8859_1
set termoption enhanced
set notitle 
set size 1.0,1.0
set tmargin 5
set lmargin 11
set bmargin 5
set rmargin 11

set key default
set key out vert
set key center top
set key spacing 1.5
set key font "Times New Roman, 14"

set xlabel "{/Bold z, {\305}}" font "Times New Roman,26" offset 33.0,-0.3,0
set xtics format "{/:Bold {/=24 %h}}"
set xtics  font "Times New Roman,24"
set xtics 0.1
set mxtics 3
set xtics out
set xtics nomirror
set x2tics in
set mx2tics 3
set x2tics 0.1
set format x2 ""
set xrange [0.0 : 1.0]

set ylabel "{/Bold T, K}"  font "Times New Roman, 26" offset 1.0,15.0,0 rotate by 0
set ytics format "{/:Bold {/=24 %h}}"
set ytics font "Times New Roman,24"
set ytics 20
set mytics 3
set ytics out
set ytics nomirror
set y2tics in
set my2tics 3
set y2tics 20
set format y2 ""
set yrange [1000.0 : 1650.0]
#--------------------------#
#Parameter for changing every timestep
#timestep in femtoseconds equal (I+1)*10000

ksi = 0.5
t=(I+1)*10000
fileName="./data/profile_".I.".data"
#--------------------------#

stats [0.0:0.3]fileName using 2:4 nooutput
T1 = STATS_mean_y
stats [0.7:1.0]fileName using 2:4 nooutput
T2 = STATS_mean_y
stats [0.0:1.0]fileName using 2:4 nooutput
T_AVE = STATS_mean_y

A = (T1 + T2) / 2
B = (T2 - T1)/sqrt(pi)

FIT_LIMIT = 1e-6
f(x) = A + B*((C*(ksi - x)) -  (C*(ksi -x))**3/3.0 + (C*(ksi-x))**5/10.0 - (C*(ksi - x))**7/42.0 + (C*(ksi - x))**9/216.0 )
fit f(x) fileName u 2:4 via A,B,C,ksi

set arrow 1 from ksi,(T_AVE-0.01*T_AVE) to ksi,(T_AVE+0.01*T_AVE) lw 3 lc rgb "black" nohead
set arrow 2 from (ksi-0.1),A to (ksi+0.1),A lw 3 lc rgb "black" nohead

L=(1/(4*C*C*t))

plot fileName u 2:4 w lp ls 1 lw 2 lc rgb "green" title sprintf('{/Symbol l}_{{/Symbol DT} = 150 K} =  %.4f W/mK, T_{avarage} = %d K', L, T_AVE),\
     f(x)     w l  ls 2 lw 2 lc rgb "red"   title  sprintf('c(x, %d fs), {/Symbol x} = %.3f, T_{left} = %d K, T_{right} = %d K', t, ksi, T1, T2)
     
set terminal postscript solid color eps enhanced 
set output "./pictures/kappa_".I.".ps"
replot
set output
set terminal x11
print t, T_AVE, L
}
set print
