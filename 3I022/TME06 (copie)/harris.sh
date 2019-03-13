#!/bin/sh

echo -1 0 1 -2 0 2 -1 0 1 | cim sobelX -x 3 -y 3
echo -1 -2 -1 0 0 0 1 2 1 | cim sobelY -x 3 -y 3
conv -dir $1 sobelX ix
conv -dir $1 sobelY iy
./gauss $4*$4 > noyau
mu ix ix ix2
mu iy iy iy2
conv -dir ix2 noyau a11
conv -dir iy2 noyau a22
mu a11 a22 a11a22

mu ix iy ixy
conv -dir ixy noyau a12
mu a12 a12 a12a21

so a11 a22 a11ma22
mu a11ma22 a11ma22 a11ma22c

chmod 777 a11ma22c
sc a11ma22c a11ma22c -n $3
so a11a22 a12a21 | so - a11ma22c $2

rm sobelX sobelY ix iy ix2 iy2 a11 a22 a11a22 ixy a12 a12a21 a11ma22 a11ma22c
