let rec f n l =
  if n=max_int then
    l
  else
    f (n+1) l::n;;
    
f (0);;
