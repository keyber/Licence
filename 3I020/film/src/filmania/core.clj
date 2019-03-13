(ns filmania.core
  (require [clojure.data.csv :as csv]
    [clojure.java.io :as io]
    [clojure.pprint]))
;;BEROUKHIM Keyvan 3506789


(defn csv-seq
  "Retourne une séquence à partir d'un fichier CSV."
  [filename]
  (with-open [in-file (io/reader filename)]
    (doall
      (csv/read-csv in-file))))


(defn parse-movie
  "Construit un enregistrement de films depuis une entrée lue depuis CSV."
  [title-year genres]
  (let [r (re-seq #"(.+) \((\d\d\d\d)\)$" title-year)
        title (get (first r) 1)]
    (try
      (let [year (Integer/parseInt (get (first r) 2))]
        {:title title
         :year year
         :genres (set (filter #(not= % "(no genres listed)") (clojure.string/split genres #"\|")))})
      (catch Exception _ nil))))

(defn movie-map
  "Construit une map de films à partir d'une base en CSV."
  [csv]
  (reduce (fn [m [movie-id title-year genres]]
            (if-let [movie (parse-movie title-year genres)]
              (assoc m (Integer/parseInt movie-id) movie)
              m))
    {} csv))

;; Attention: gros fichier
(def movie-filename "resources/ml-latest-small/movies.csv")

(def movies (movie-map (rest (csv-seq movie-filename))))


(take 10 movies)
;;question 1
(defn total []
  (count movies))

(defn genre? [genre film]
  (some #(= % genre) (get (val film) :genres)))

(defn sf []
  (count (filter (partial genre? "Sci-Fi") movies)))

(defn romance []
  (count (filter #(genre? "Romance" %) movies)))

;;question 2
(defn all-genres []
  (reduce into (map #(get (val %) :genres) movies)))

(defn films-by-genre [genre]
  (filter #(genre? genre %) movies))

;;question 3
(defn card-genres []
  (loop [lgenres (all-genres)
         res {}]
    (if (seq lgenres)
      (recur
        (rest lgenres)
        (assoc res (first lgenres) (count (films-by-genre (first lgenres)))))
      res)))

(defn min-max-represente []
  ;calcule cardinalite de chaque genre

  (let [card (card-genres)]
    ;parcourt la map et garde les vals min et max
    (loop [card (rest card)
           gmin (first card)
           gmax (first card)]
      (if (seq card)

        ;nouveau min
        (if (< (val (first card)) (val gmin))
          (recur (rest card) (first card) gmax)

          ;nouveau max
          (if (> (val (first card)) (val gmax))
            (recur (rest card) gmin (first card))
            (recur (rest card) gmin gmax)))

        ;retourne min et max
        (list gmin gmax)))))

;partie 2
;question 1
(defn mapratings [liste]
  "return map<userId, map<filmId, note>>"
  (loop [liste liste
         uId (first (first liste))
         filmMap {}
         res {}]

    (if (seq liste)
      (let [ligne (first liste)
            nId (Integer/parseInt (first ligne))]

        (if (= nId uId)
          ;meme utilisateur
          (recur
            (rest liste)
            uId
            (assoc filmMap (Integer/parseInt(nth ligne 1)) (Double/parseDouble (nth ligne 2)))
            res)

          ;nouvel utilisateur
          (recur
            liste;n'avance pas dans la liste
            nId;change utilisateur
            {}
            (assoc res uId filmMap))))
      res)))

(def list-ratings (rest (csv-seq "resources/ml-latest-small/ratings.csv")))
(def map-ratings (mapratings list-ratings))

;question2
(defn get-map [mapparam keyparam]
  (if (contains? mapparam keyparam)
    (get mapparam keyparam)
    0))

(defn movie-avg-rating []
  "return map<filmId, avgPoints>"
  (loop [liste list-ratings
         ;;map<filmId, nbOccurence>
         nb {}
         ;;map<filmId, sommePoints>
         res {}]

    (if (seq liste)
      (let [ligne (first liste)
            idFilm (Integer/parseInt(nth ligne 1))]
        (recur
          (rest liste)
          (assoc nb idFilm (inc (get-map nb idFilm)))
          (assoc res idFilm (+ (get-map res idFilm) (Double/parseDouble(nth ligne 2))))))

      (loop [listnb nb
             res res]
        (if (seq listnb)
          (let [id (first (first listnb))]
            (recur
              (rest listnb)
              (assoc res id (/ (get res id) (get nb id)))))
          res
          )))))


(defn avg-minmax [avg]
  "return ([id, minAvg][id, maxAvg])"

  ;parcourt la map et garde les vals min et max
  (loop [avg (rest avg)
         gmin (first avg)
         gmax (first avg)]
    (if (seq avg)

      ;nouveau min
      (if (< (val (first avg)) (val gmin))
        (recur (rest avg) (first avg) gmax)

        ;nouveau max
        (if (> (val (first avg)) (val gmax))
          (recur (rest avg) gmin (first avg))
          (recur (rest avg) gmin gmax)))

      ;retourne min et max
      (list gmin gmax))))

;question3
(defn user-minmax []
  "input : map<userId, map<filmId, note>>
output: [userId, minUserAvg] [userId, maxUserAvg])"
  ;parcourt la map
  (loop [ratings (seq map-ratings)
         ;min&max initialises en dehors des bornes
         gmin (list -1 6.0)
         gmax (list -1 -1.0)]

    (if (seq ratings)
        (if (zero? (count (second (first ratings))))
          (recur (rest ratings) gmin gmax)
          (let [;utilisateur de cette iteration
                user-id (first (first ratings))

                ;liste de ses eval
                user-ratings (map #(second %) (second (first ratings)))

                ;moyenne de ses notes
                avg (/ (reduce + 0 user-ratings) (count user-ratings))

                ;nouveaux min et max
                gmin (if (< avg (second gmin)) (list user-id avg) gmin)
                gmax (if (> avg (second gmax)) (list user-id avg) gmax)]
          (recur (rest ratings) gmin gmax))
          )


      ;fin
      (list gmin gmax))))


(defn genre-minmax-film [genre]
  "return ([id, noteMin][id, noteMax])"
  (let [avg-rating (movie-avg-rating)]
    (loop [l (films-by-genre genre)
           fmin [-1 6.0]
           fmax [-1 -1.0]]

      (println (count l) fmin fmax)
      (if (seq l)
        (let [idFilm (first (first l))
              _ (println idFilm
              fmoy (get avg-rating idFilm)
              fmin (if (< fmoy (second fmin)) (list idFilm fmoy) fmin)
              fmax (if (> fmoy (second fmax)) (list idFilm fmoy) fmax)]
          (println idFilm fmin fmax)
          (recur (rest l) fmin fmax))
        [fmin, fmax]))))

(defn tests[]
  (println "TESTS VALIDES : "
           (and
             (= 8918 (total))
             (= 19 (count (all-genres)))
             (let [[[nomMin, nbMin], [nomMax, nbMax]] (min-max-represente)]
               (and (= nomMin "Film-Noir")
                    (= nbMin 111)
                    (= nomMax "Drama")
                    (= nbMax 4310)))
             (let [[[idMin, nbMin], [idMax, nbMax]] (avg-minmax (movie-avg-rating))]
               (and (= idMin 5591)
                    (= nbMin 0.5)
                    (= idMax 94735)
                    (= nbMax 5.0)))

             )))


(defn -main []
  (tests)
  (println "entrer code :")
  (println "0:nb total film - 1:liste genres - 2: film by genre - 3: cardinalites - 4: cardinalites min&max")
  (println "5:10 premieres evals - 6:film avg min&max - 7: moyenne des moyennes - 8: user avg mi&max - 9: genre min&max")

  (loop [n (read-string (read-line))]
    (cond
  ;;;partie1
  ;;question 0
  ;(println "10 premiers films de la liste" (take 2 movies))

  ;;question 1
  (= n 0) (println "nb film total" (total))
  ;(println "nb sci-fi" (sf))
  ;(println "nb romance" (romance))

  ;;question 2
  (= n 1) (println "liste des genres" (all-genres))
  (= n 2) (do
            (println "films-by-genre rentrer un nom")
            (let [genre (read-line)]
              (println (films-by-genre genre))
              (println "fin")))

  ;;question 3
  (= n 3) (println "cardinalites" (card-genres))
  (= n 4) (println "categories min et max representees" (min-max-represente))

  ;;;partie2
  ;;question1
  (= n 5) (println "10 premieres evals" (take 10 (map #(take 3 %) list-ratings)))

  ;;question2
  (= n 6) (println "films avg min&max" (avg-minmax (movie-avg-rating)))

  (= n 7) (let [avg (movie-avg-rating)] (println "moyenne des moyennes (et non moyenne des evals)" (/ (reduce + 0 (map #(second %) avg)) (count avg))))

  ;;question3
  (= n 8) (println "user avg min&max" (user-minmax))

  (= n 9) (do
            (println "min&max films of genre. rentrer un nom")
            (let [genre (read-line)]
              (println (genre-minmax-film genre))))

  :else (println "mauvais code")
  )
    (recur (read-string(read-line)))))

