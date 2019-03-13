let n = Array.length Sys.argv - 1
  
let rec f n =
  print_string (Sys.argv.(n) ^ (string_of_int n) ^ "\n");
  if n>0 then
    f (n-1);;
    
f (n);;
