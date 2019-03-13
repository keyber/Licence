let n = Array.length Sys.argv - 1
  
let rec f n r =
  if n=0 then
    r
  else
    f (n-1) (r +. float_of_string Sys.argv.(n));;
    
print_string (string_of_float (f n 0.) ^ "\n");;
