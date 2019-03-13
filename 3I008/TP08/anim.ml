class virtual ['a] with_timeline = object(self)
  method virtual on_time : int-> 'a
end


class ['a] constant valeur = object
  inherit ['a] with_timeline
  method on_time param = valeur
end

(*let minisleep (sec: float) =
  ignore (Unix.select [] [] [] sec)*)

let taille = 500
let boucle_principale
    (col : Graphics.color with_timeline)
    (title : string with_timeline)
    (shape : Affichage.forme with_timeline) =
  Graphics.open_graph "";
  let rec aux t =
    Graphics.set_window_title (title#on_time t);
    Graphics.set_color Graphics.white;
    Graphics.fill_rect 0 0 taille taille;

    for i=0 to taille -1 do
      for j=0 to taille -1 do
        if (shape#on_time t)# is_pixel_in (i, j) then begin
          Graphics.set_color (col#on_time t);
          Graphics.plot i j;
          end
      done;
    done;

    Unix.sleepf(0.1);
    aux (t + 1)
  in aux 0


class ctime = object
  inherit [Graphics.color] with_timeline
  method on_time t = Graphics.rgb (t mod 16) (t mod (2*16)) (t mod (3*16))
end

class stime = object
  inherit [string] with_timeline
  method on_time t = string_of_int t
end

class ftime = object
  inherit [Affichage.forme] with_timeline
  method on_time t = new Affichage.circle 250 250 t
end

let () =
  boucle_principale (new ctime) (new stime) (new ftime);
  ignore (read_line () : string)
