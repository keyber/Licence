(ns mastermind.core)

(declare code-secret)
(defn code-secret [n]
  "renvoie un code de n couleurs tirees aleatoirement"
  (let [ens ["rouge" "bleu" "vert" "jaune" "noir" "blanc"]]
    (loop [n n, res []]
      (if (zero? n)
        res
        (recur (dec n) (conj res (rand-nth ens)))))))

(declare good)
(declare color)
(declare fill-with-bad)
(declare indications)
(defn indications [code, essai]
  ;;rempli avec good
  (let [[res unused-code unused-essai] (good code essai)]
    ;;rajoute les color
    (let [res (concat res (color unused-code unused-essai))]

      ;;complete avec des bad
      (concat res (fill-with-bad (- (count code) (count res)))))))


(defn good [code, essai]
  "renvoie le triplet de vecteur
  :good pour chaque couleur bien placee
  les elements du code qui n'ont pas etes utilises
  ------------ de l'essai -------------"

  ;;parcourt le code et l'essai en meme temps
  (loop [code code, essai essai, res [], unused-code [], unused-essai []]
    (if (seq code)

      ;;compare
      (if (= (first code) (first essai))

        ;;bonne coul
        (recur
          (rest code)
          (rest essai)
          (conj res :good)
          unused-code
          unused-essai)

        ;;sinon
        (recur
          (rest code)
          (rest essai)
          res
          (conj unused-code (first code))
          (conj unused-essai (first essai))))

      ;;a la fin
      [res, unused-code, unused-essai])))


(defn enlever [vect elt]
  (loop [v vect, res []]
    (if (seq v)
      (if (= (first v) elt)
        (concat res (rest v) )
        (recur (rest v) (conj res (first v))))
      (throw (Exception. "element non trouve"))
      )))

(defn color [unused-code unused-essai]
  "renvoie :color pour chaque couleur mal placee"

  ;;parcourt unused-code uniquement et
  ;;enleve toutes les ressemblances dans unused-essai
  (loop [code unused-code, essai unused-essai, res []]
    (if (seq code)

      ;;test d'appartenance dans essai
      (if (some #(=(first code) %) essai)

        ;;couleur mal placee trouvee
        (recur
          (rest code)
          (enlever essai (first code))
          (conj res :color))

        ;;pas trouve
        (recur
          (rest code)
          essai
          res))

      res)))



(defn fill-with-bad [n]
  "renvoie n fois :bad"

  (loop [n n, res []]
    (if (zero? n)
      res
      (recur (dec n) (conj res :bad)))))

(defn entrer-code []
  (let [essai (read-line)]
    (let [essai (clojure.string/split essai #" " )]
      (if (= (count essai) 4)
        essai
        (entrer-code)))))

(defn continue? [indications]
  "continue tant qu'une couleur n'est pas bien placee"
  (some #(not= :good %) indications))


(defn -main []
  (let [code (code-secret 4)]
    (println "voici la solution que j'affiche pour faciliter vos tests (cache en temps normal)")
    (println code)
    (println "entrer code (exemple: vert vert bleu bleu)")
    (loop []
      (let [essai (entrer-code)]
        (let [indic (indications code essai)]
          (println "indication : ")
          (println indic)
          (if (continue? indic)
            (recur)
            (println "trouve" true)
            ))))))
