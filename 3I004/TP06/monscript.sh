 #!/bin/bash
a=2
echo "$a"
echo "$((1<<$a))" 
echo $((1<<$a))  
echo $((1<<$a))" 

for i in {0..10}
    do
       echo "Welcome $i times"
 done
#simul_almo_generic YS sys.bin -APP app.bin -NICACHE 1024 -NDCACHE $((1<<i)) -STATS stats -NCYCLES 2500
#echo grep total time proc0_term0 cut-d' ' -5
