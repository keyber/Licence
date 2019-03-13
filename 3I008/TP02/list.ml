let suivant l =
  let rec aux cpt elt l = match l with
  | [] -> [cpt; elt]
  | h::t when h = elt -> aux (cpt + 1) elt t
  | h::t -> cpt::elt::(aux 1 h t)
  in
  aux 1 (List.hd l) (List.tl l);;

let conway n =
  let rec aux n l ll =
    print_newline (List.iter print_int l);
    if n > 1 then
      aux (n - 1)
	  (suivant l)
	  (l::ll)
    else
      ll
  in aux n [1] [];;

conway 16;;

let cherche_char str c =
  let rec aux n =
    if n = String.length str
    then -1
    else
      if str.[n] = c
      then n
      else aux (n+1)
  in aux 0;;
cherche_char "bla" 'a';;
(*
let rec calc_prefixe list =
  match list with
  |[] -> 0
  |x::y::l when x=y -> 1 + calc_prefixe (y::l)
  |x -> 1;;

		      
calc_prefixe [] = 0 &&
calc_prefixe [0] =1 &&
calc_prefixe [1] =1 &&
calc_prefixe [1;1]=2&&
calc_prefixe [1;2]=1&&
calc_prefixe [2;1;1]=1&&
calc_prefixe [1;1;2]=2&&
calc_prefixe [1;1;1;3]=3;;
*)			      
