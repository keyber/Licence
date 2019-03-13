#!/bin/sh

rdf $1 $2 $3
chmod 755 $2
chmod 755 $3
ri $2 $3
ce $2 $2
ce $3 $3
norma $2 | xvis -nu  &
extg $2 -iy 65 -y 1 | tpr -c -l 1 | nl | xgraph
