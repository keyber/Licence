(ns sat.partie1)

(not true)
(not false)
(and true false)
(and true true)
(or true false)
(or false false)

;; a et b sont des variables propositionnelles
(defn xor [a b]
  (and (or a b)
       (not (and a b))))
(xor true false)
(xor true true)

(defn venum-aux [bools]
  (list (conj bools false) (conj bools true)))

(venum-aux [false, false, false])
(venum-aux [])

(defn venum
  "Retourne la partie gauche de la table de vérité pour `nb` variables."
  [nb]
  (cond
    (zero? nb) ()
    (= nb 1) (venum-aux [])
    :else
    (let [tbl (venum (dec nb))]
      (reduce concat (map venum-aux tbl)))))

(venum 1)
(venum 5)
(count (venum 10))

(defn partie-gauche [variables]
  (let [values (venum (count variables))
        vvalues (map (fn [enum]
                       (apply array-map
                              (interleave variables enum))) values)]
    vvalues))

(partie-gauche [:a :b :c])

(defn table-verite-aux [variables prop]
  (let [gauche (partie-gauche variables)]
    (map (fn [vmap]
           [vmap (apply prop (vals vmap))]) gauche)))

(table-verite-aux '[a b] xor)
(table-verite-aux '[a b] #(or %1 %2))

(defn table-verite [prop-var]
  (if-let [op-meta (meta prop-var)]
    (table-verite-aux (first (:arglists op-meta)) prop-var)
    (throw (ex-info "Impossible de construire la table: pas de meta" prop-var))))

(table-verite #'xor)

(defn nand [a b]
  (not (and a b)))

(table-verite #'nand)

(defn my-or [a b]
  (or a b))

(table-verite #'my-or)

(defn tiers-exclu [a]
  (or a (not a)))

(table-verite #'tiers-exclu)

(defn ==> [a b]
  (or (not a) b))

(defn modus-ponens [a b]
  (==> (and (==> a b) a)
       b))

(table-verite #'modus-ponens)

(defn tautologie-aux? [tbl]
  (every? true? (map second tbl)))

(tautologie-aux? (table-verite #'modus-ponens))

(defn tautologie? [prop]
  (tautologie-aux? (table-verite prop)))

(tautologie? #'tiers-exclu)
(tautologie? #'modus-ponens)
(tautologie? #'==>)

(defn neant [a]
  (and a (not a)))

(table-verite #'neant)

(defn satisfiable-aux? [tbl]
  (or (some true? (map second tbl))
      false))

(satisfiable-aux? (table-verite #'neant))
(satisfiable-aux? (table-verite #'modus-ponens))
(satisfiable-aux? (table-verite #'==>))

(defn satisfiable? [prop]
  (satisfiable-aux? (table-verite prop)))

(satisfiable? #'modus-ponens)



