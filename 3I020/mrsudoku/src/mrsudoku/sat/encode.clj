(ns mrsudoku.sat.encode
  (:require [midje.sweet :refer [fact]]
            [mrsudoku.grid :as g]))

(def ex-grille @#'g/sudoku-grid)

(fact 
  (g/cell ex-grille 1 1) => {:status :init, :value 5}
  (g/cell ex-grille 4 2) => {:status :init, :value 1}
  (g/cell ex-grille 9 9) => {:status :init, :value 9}
  (g/cell ex-grille 4 5) => {:status :init, :value 8}
  (g/cell ex-grille 4 6) => {:status :empty})

;; <<A DEFINIR>>
(declare log-binary)

(fact
  (log-binary 5) => '(1 0 1)
  (log-binary 9) => '(1 0 0 1)
  (log-binary 42) => '(1 0 1 0 1 0))

;; <<A DEFINIR>>
(declare pad-seq)

(fact
  (pad-seq (log-binary 1) 0 4) => '(0 0 0 1)
  (pad-seq (log-binary 5) 0 4) => '(0 1 0 1)
  (pad-seq (log-binary 9) 0 4) => '(1 0 0 1)
  (pad-seq '(:a :b :c) :x 7) => '(:x :x :x :x :a :b :c))

(defn encode-value
  "Encode une valeur de cellule `n` (entre 1 et 9) en une séquence de 4 bits."
  [n]
  (pad-seq (log-binary n) 0 4))

(defn mkcellbit 
  "Créer la variable du `bit` spécifié (entre 0 poids faible
   et 3 poids fort) pour la cellule située en `cx` (colonne)
  et `cy` (ligne)." 
  [cx cy bit]
  (symbol (str "x" cx "y" cy "b" bit)))

(fact
  (mkcellbit 6 2 2) => 'x6y2b2
  (mkcellbit 4 3 0) => 'x4y3b0)

;; <<A DEFINIR>>
(declare encode-num)

(fact
  ;; bits '(0 1 0 1) donne x6y2b0 /\ (not x6y2b1) /\ x6y2b2 /\ (not x6y2 b3)
  (encode-num 6 2 5) => '(and x6y2b0 (and (not x6y2b1) (and x6y2b2 
                                                            (and (not x6y2b3) true))))
  ;; bits '(0 0 0 1) donne x6y2b0 /\ (not x6y2b1) /\ (not x6y2b2) /\ (not x6y2 b3)
  (encode-num 2 3 1) => '(and x2y3b0 (and (not x2y3b1) (and (not x2y3b2) 
                                                            (and (not x2y3b3) true))))
  ;; bits '(1 0 0 1) donne x6y2b0 /\ (not x6y2b1) /\ (not x6y2b2) /\ x6y2 b3)
  (encode-num 2 3 9) => '(and x2y3b0 (and (not x2y3b1) (and (not x2y3b2) 
                                                            (and x2y3b3 true)))))
(defn encode-inits 
  "Formule d'encodage des cellules déjà remplies dans la `grille`"
  [grille]
  (g/reduce-grid 
   (fn [acc cx cy cell]
     (if (= (:status cell) :empty)
       acc
       (list 'and (encode-num cx cy (:value cell)) acc))) true grille))

;; <<A DEFINIR>>
(declare encode-vide)

(fact
 (encode-vide 7 3) ;; encodage d'une cellule vide en cx=7 et cy=3
 => '(or (and 
          x7y3b0 
          (and (not x7y3b1) (and (not x7y3b2) (and x7y3b3 true)))) 
         (or (and (not x7y3b0) (and (not x7y3b1) (and (not x7y3b2) (and x7y3b3 true)))) 
             (or (and x7y3b0 (and x7y3b1 (and x7y3b2 (and (not x7y3b3) true)))) 
                 (or (and (not x7y3b0) (and x7y3b1 (and x7y3b2 (and (not x7y3b3) true)))) 
                     (or (and x7y3b0 (and (not x7y3b1) 
                                          (and x7y3b2 (and (not x7y3b3) true)))) 
                         (or (and (not x7y3b0) 
                                  (and (not x7y3b1) 
                                       (and x7y3b2 (and (not x7y3b3) true)))) 
                             (or (and x7y3b0 (and x7y3b1 
                                                  (and (not x7y3b2) 
                                                       (and (not x7y3b3) true)))) 
                                 (or (and (not x7y3b0) (and x7y3b1 
                                                            (and (not x7y3b2) 
                                                                 (and (not x7y3b3) true)))) 
                                     (or (and x7y3b0 (and (not x7y3b1) 
                                                          (and (not x7y3b2) 
                                                               (and (not x7y3b3) true))))
                                         false))))))))))

(defn encode-vides 
  "Formule d'encodage des cellules vides de la `grille`."
  [grille]
  (g/reduce-grid 
    (fn [acc cx cy cell]
      (if (= (:status cell) :empty)
        (list 'and (encode-vide cx cy) acc)
        acc)) true grille))

;; <<A DEFINIR>>
(declare distinct-empty-empty)

(fact
 ;; les cellules entre cx1=2,cy1=3 et cx2=2,cy=5 doivent être distinctes
 (distinct-empty-empty 2 3 2 5)
 => '(and (<=> l3c2b0 (not l5c2b0)) ; bits b0 distincts
          (and (<=> l3c2b1 (not l5c2b1)) ; b1
               (and (<=> l3c2b2 (not l5c2b2)) ; b2
                    (and (<=> l3c2b3 (not l5c2b3))  ; b3
                         true)))))

;; <<A DEFINIR>>
(declare distinct-filled-empty)

(fact
 ;; cval1=5  et cx2=3,cy2=6
 (distinct-filled-empty 5 3 6)
 => '(or (not x3y6b0) (or x3y6b1 (or (not x3y6b2) (or x3y6b3 false)))))

(defn distinct-pair [cx1 cy1 cell1 cx2 cy2 cell2]
  (cond 
    ;; cas 1 : deux cellules vides
    (and (= (:status cell1) :empty) (= (:status cell2) :empty))
    (distinct-empty-empty cx1 cy1 cx2 cy2)
    ;; cas 2a : la première est vide
    (= (:status cell1) :empty)
    (distinct-filled-empty (:value cell2) cx1 cy1)
    ;; cas 2b : la seconde est vide
    (= (:status cell2) :empty)
    (distinct-filled-empty (:value cell1) cx2 cy2)
    ;; cas 3 : la formule n'est pas satisfiable
    (= (:value cell1) (:value cell2))
    false
    ;; cas par défaut : contrainte satisfaite
    :else true))

(fact
 (distinct-pair 2 3 {:status :empty} 5 6 {:status :empty})
 => '(and (<=> l3c2b0 (not l6c5b0)) 
          (and (<=> l3c2b1 (not l6c5b1)) 
               (and (<=> l3c2b2 (not l6c5b2)) 
                    (and (<=> l3c2b3 (not l6c5b3)) true))))
 (distinct-pair 2 3 {:status :init :value 5} 5 6 {:status :empty})
 => '(or (not x5y6b0) (or x5y6b1 (or (not x5y6b2) (or x5y6b3 false))))
 (distinct-pair 5 6  {:status :empty} 2 3 {:status :init :value 5})
 => '(or (not x5y6b0) (or x5y6b1 (or (not x5y6b2) (or x5y6b3 false))))
 (distinct-pair 2 3 {:status :init :value 5} 5 6 {:status :init :value 6})
 => true
 (distinct-pair 2 3 {:status :init :value 5} 5 6 {:status :init :value 5})
 => false)

;; <<A DEFINIR>>
(declare distinc-cells)

(fact
 (distinct-cells '([1 1 {:status :empty}] 
                   [2 1 {:status :init :value 5}] 
                   [2 2 {:status :empty}]))
 => '(and true 
          (and (and (or (not x2y2b0) 
                        (or x2y2b1 (or (not x2y2b2) (or x2y2b3 false)))) true) 
               (and (and (and (<=> l1c1b0 (not l2c2b0)) 
                              (and (<=> l1c1b1 (not l2c2b1)) 
                                   (and (<=> l1c1b2 (not l2c2b2)) 
                                        (and (<=> l1c1b3 (not l2c2b3)) true)))) 
                         (and (or (not x1y1b0) (or x1y1b1 
                                                   (or (not x1y1b2) (or x1y1b3 false)))) 
                              true)) 
                    true))))

(defn fetch-row 
  "Récupère les cellules de la ligne `cy` de la `grille`."
  [grille cy] 
  (map (fn [cx cell]
         [cx cy cell]) (range 1 10) (g/row grille cy)))

(defn encode-rows 
  "Formule d'encodage des contraintes de ligne dans la grille."
  [grille]
  (loop [cy 1, phi true]
    (if (<= cy 9)
      (recur (inc cy) (list 'and (distinct-cells (fetch-row grille cy))
                            phi))
      phi)))

(defn fetch-col
  "Récupère les cellules de la colonne `cx` de la `grille`."
  [grille cx] 
  (map (fn [cy cell]
         [cx cy cell]) (range 1 10) (g/col grille cx)))

(defn encode-cols
  "Formule d'encodage des contraintes de colonne dans la grille."
  [grille]
  (loop [cx 1, phi true]
    (if (<= cx 9)
      (recur (inc cx) (list 'and (distinct-cells (fetch-col grille cx))
                            phi))
      phi)))

(defn block-rows 
  "Séquence des coordonnées de ligne des cellules du block `b`"
  [b]
  (map #(+ (* (mod (dec b) 3) 3)
           1 (mod % 3)) (range 0 9)))

(defn block-cols 
  [b]
  (map #(+ (quot % 3) 1
           (* (quot (dec b) 3) 3)) (range 0 9)))

(defn fetch-block 
  "Récupère les cellules du block `b` de la `grille`."
  [grille b]
   (map vector (block-rows b) (block-cols b) (g/block grille b)))

(defn encode-blocks 
  "Formule d'encodage des contraintes de bloc dans la grille."
  [grille]
  (loop [b 1, phi true]
    (if (<= b 9)
      (recur (inc b) (list 'and (distinct-cells (fetch-block grille b))
                           phi))
      phi)))

(defn encode-sudoku
  "Formule d'encodage de la grille du Sudoku."
  [grille]
  (list 'and
        (encode-inits grille)
        (list 'and (encode-vides grille)
              (list 'and (encode-rows grille)
                    (list 'and (encode-cols grille)
                          (list 'and (encode-blocks grille))))))),

;; (encode-sudoku ex-grille)
;; => .... attention : formule énorme ! ....

