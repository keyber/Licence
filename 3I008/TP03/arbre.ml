type node = Lettre of char * bool * arbre_lex
 and arbre_lex = node list
let existe arbre mot =
  let rec aux n = function
      Lettre (a, b, children) ->
      if n < String.length mot -1
      then
	a = mot.[n] && (List.exists (aux (n+1)) children)
      else if n = String.length mot -1 then
	a = mot.[n] && b
      else false
  in List.exists (aux 0) arbre;;

exception Deja_def of string
			
let ajoute dico mot =
  let rec traverse n nodes =
    if n < String.length mot then
      match nodes with
      |[] -> [Lettre (mot.[n], n = String.length mot - 1, [])]
      |Lettre(a, true, children) :: l
	   when a = mot.[n] && n = String.length mot - 1
       -> raise (Deja_def mot)
      |Lettre(a, b, children):: l
	   when a = mot.[n]
       -> Lettre(a, b || n = String.length mot - 1, traverse (n+1) children) :: l
      |lettre_tete :: l -> lettre_tete :: (traverse n l)
    else []
  in
  traverse 0 dico
	   
let construit = List.fold_left ajoute []

let to_list dico =
  let rec gen mot = function
    |[] -> []
    |Lettre(a, b, children)::l when b ->
      let nouveau_mot = mot ^ String.make 1 a in
      nouveau_mot :: (gen nouveau_mot children) @ (gen mot l)
    |Lettre (a, b, children) :: l ->
      (gen (mot ^ String.make 1 a) children) @ (gen mot l)
  in gen "" dico
(*
^ concatene str
@           list
String.make n crée str de n charactères
 *)
	 
let affiche = 1;;

  construit ["abc"; "abcd"; "acd"; "b"];;
    
