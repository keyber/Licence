#load "graphics.cma";;
type cell = Alive | Dead;;
type board = cell array array;;
let taille = 50;;
  
let init_gen() =
  Random.self_init ();
  let tab = Array.make_matrix taille taille Dead in
  for i=0 to taille - 1 do
    for j=0 to taille - 1 do
      if Random.int 3 = 0 then
	tab.(i).(j) <- Alive
    done;
  done;
  tab;;
	
	  
let next_gen b =				       
  let neighbours i j =    
    let exist_and_alive i j=
      let aux =
	if i<0 || i>= taille || j<0 || j>=taille then
	  false
	else match b.(i).(j) with
	     |Alive-> true
	     |_ -> false
      in
      if aux then 1 else 0
    in
    let l = ref 0 in
    l := !l + exist_and_alive (i - 1) j;
    l := !l + exist_and_alive i (j - 1);
    l := !l + exist_and_alive i (j + 1);
    !l + exist_and_alive (i + 1) j
  in
  let res = Array.make_matrix taille taille Dead in
  for i=0 to taille - 1 do
    for j=0 to taille - 1 do
      match neighbours i j with
      |a when a<2 -> res.(i).(j)<-Dead
      |a when a>3 -> res.(i).(j)<-Dead
      |a when a=3 -> res.(i).(j)<-Alive
      |_ -> res.(i).(j) <- b.(i).(j)
    done;
  done;
  if res = b then
    init_gen()
  else
    res
;;
	
let init_graph() =
  print_endline "graph ouvert";
  Graphics.open_graph "";;

let larg=8;;
let draw b =
  Graphics.set_color Graphics.black;
  Graphics.fill_rect 0 0 (taille*larg*10) (taille*larg*10);
  Graphics.set_color Graphics.green;
  for i=0 to taille - 1 do
    for j=0 to taille - 1 do
      match b.(i).(j) with
	Alive -> Graphics.fill_rect (larg*i*2) (larg*j*2) larg larg;
      |Dead -> ()
    done; done;;
  
let main() =
  init_graph();
  let rec boucle board =
    draw board;
    for i=0 to 10 do
      Graphics.read_key()
    done;
    
    boucle (next_gen (board));
  in
  boucle (init_gen())
;;

main();;
		  
							
