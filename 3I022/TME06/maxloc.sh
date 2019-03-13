#!/bin/sh

echo -1 1 0 | cim -x 3 -y 1 -r | conv -dir $1 | mh -n 0 > H.d1
echo 0 1 -1 | cim -x 3 -y 1 -r | conv -dir $1 | mh -n 0 > H.d2
echo -1 1 0 | cim -x 1 -y 3 -r | conv -dir $1 | mh -n 0 > H.d3
echo 0 1 -1 | cim -x 1 -y 3 -r | conv -dir $1 | mh -n 0 > H.d4

mh $1 -n $3 | logic -et H.d1 | logic -et H.d2 | logic -et H.d3 | logic -et H.d4 > $2

rm H.d1 H.d2 H.d3 H.d4
