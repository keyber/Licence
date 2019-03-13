#!/bin/bash

for s in ".7" "1" "1.3"
do
for k in "0.1" "0.4" "0.9" #intensite blanc <=> seuil
do
./harris.sh cameraman.inr.gz camharris $k $s
./maxloc.sh camharris cammax .1
name="S$s""_K$k"
./croix cameraman.inr.gz cammax $name

echo $name
xvis -nu camharris &
xvis -nu cammax &
xvis -nu $name &

read _
done
done

rm S*

echo -1 -1 -1 -1 8 -1 -1 -1 -1 | cim filtredetect -x 3 -y 3
conv -dir cameraman.inr.gz filtredetect camdetect
mh -n $(carflo 92) camdetect > camdetectbin


echo "killall xvis ? Y/n"
read answer
if ! [ "$answer" = n ]
then
killall xvis
fi

