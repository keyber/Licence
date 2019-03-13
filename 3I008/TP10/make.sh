ocamlfind ocamlc -package js_of_ocaml.ppx -linkpkg ex1.ml -o ex1.bytes
js_of_ocaml ex1.bytes
rm ex1.bytes ex1.cmi ex1.cmo
