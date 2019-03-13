let counter()=
    let c = ref 0 in
    let fres()=
        c:=!c+1;
        !c in
    let raz () = c:=0 in
    (fres, raz)

let win = Dom_html.window
            
let inc, raz = counter()
    
let btnC = Dom_html.getElementById("btn_click")
let click_handler = Dom_html.handler(fun event ->
    let nb = inc() in
    (Dom_html.getElementById "click_number")##.innerHTML:=
      Js.string(string_of_int nb);
    if nb>=10 then begin
      let btn = Dom_html.getElementById("btn_click") in
      let opt=Dom_html.CoerceTo.button btn in
      let b = Js.Opt.get opt (fun ()-> failwith "erreur") in
      b##.disabled:=Js._true end ;
    Js._true)
    
let ()=btnC##.onclick:=click_handler

            
let btnA = Dom_html.getElementById("btn_alert")
let alert_handler = Dom_html.handler(fun event ->
    win##alert(Js.string "Alerte!");
    Js._true)
let ()=btnA##.onclick:=alert_handler

