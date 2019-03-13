#! /bin/bash
# ce script construit l'image atlas.inr



# couleur des regions
CRANE_COL=255
MGG_COL=80
MGD_COL=140
MBG_COL=180
MBD_COL=200

# crane
cat > el.xv <<EOF
##!draw(z 1,a 5 3 259 323)
##!dump(test.inr)
##!EXIT
EOF

#imref=IRM.inr.gz
#dims=`par -x -y $imref`
dims="-x 270 -y 330"

raz $dims | xvis -xsh el.xv
extg -v 1 test.inr | anac -fc - os.chn
fillc os.chn -pos $dims -fv $CRANE_COL > atlas.inr

cat > el.xv <<EOF
##!draw(z 1,a 16 14 238 303)
##!dump(test.inr)
##!EXIT
EOF

raz $dims | xvis -xsh el.xv 
extg -v 1 test.inr | anac -fc - os.chn
fillc os.chn -neg -add atlas.inr

# MG gauche: demi ellipse
cat > el.xv <<EOF
##!draw(z 1,a 25 25 215 280 90 180)
##!draw(L 132 25 132 305)
##!dump(test.inr)
##!EXIT
EOF

raz $dims | xvis -xsh el.xv
extg -v 1 test.inr | anac -fc - os.chn 
fillc os.chn -pos -add atlas.inr -fv $MGG_COL

# MG droit: demi ellipse
cat > el.xv <<EOF
##!draw(z 1,a 30 25 215 280 270 180)
##!draw(L 138 25 138 305 )
##!dump(test.inr)
##!EXIT
EOF

raz $dims | xvis -xsh el.xv
extg -v 1 test.inr | anac -fc - os.chn 
fillc os.chn -pos -add atlas.inr -fv $MGD_COL

# MB gauche
cat > el.xv <<EOF
##!draw(z 1,a 84 100 29 130)
##!dump(test.inr)
##!EXIT
EOF

raz $dims | xvis -xsh el.xv
extg -v 1 test.inr | anac -fc - os.chn 
fillc os.chn -pos -add atlas.inr -fv $MBG_COL

# MB droit
cat > el.xv <<EOF
##!draw(z 1,a 154 100 29 130)
##!dump(test.inr)
##!EXIT
EOF

raz $dims | xvis -xsh el.xv
extg -v 1 test.inr | anac -fc - os.chn 
fillc os.chn -pos -add atlas.inr -fv $MBD_COL

rm -f atlas.inr.gz
gzip atlas.inr
rm -f os.chn test.inr el.xv
