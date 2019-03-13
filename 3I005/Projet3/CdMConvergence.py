import numpy as np
from CdMSampler import CdMSampler
from CollGetDistributionVerbose import CollGetDistributionVerbose
from FeuRouge import FeuRouge
from MouseInMaze import MouseInMaze
from MonoBestiole import MonoBestiole
from Oie import Oie
import scipy.sparse.linalg as linalg
import time
import math


def max_diff_vec(p, p2):
    return max([abs(p[i] - p2[i]) for i in range(len(p))])


def is_proba(p, epsilon):
    for i in p:
        if i < -epsilon or i > 1+epsilon:
            return False
    return True


def method0(CdM, epsilon):
    """iteration simulation"""
    t = time.time()
    sampler = CdMSampler(CdM)
    sampler.add_collector(CollGetDistributionVerbose(epsilon))

    # lance puis recupere le resultat de CollGetDistribution
    res = sampler.run(1000000).get(0)#limite a 1M iterations

    return (res.get("distrib"),
            time.time() - t,
            res.get("nb_iter"),
            res.get("err"))


def method1(CdM, epsilon):
    """iteration distribution
    retourne :
    distribution asymptotique,
    temps,
    nombre d'iteration,
    tableau des erreurs : max(abs(difference))),
    tableau des erreurs : distance"""
    # mesure temps et nombre d'etapes
    t = time.time()
    cpt = 0

    # stocke erreur a chaque etape
    err = []

    # distribution initiale et matrice de transition
    p = np.array(CdM.distribution_to_vector(CdM.get_initial_distribution()))
    m = CdM.get_transition_matrix()

    while True:
        pOld = p
        p = np.dot(p, m)
        cpt += 1

        mdiff = max_diff_vec(p, pOld)

        # sauvegarde erreur
        err.append(mdiff)

        if mdiff < epsilon:
            break
    # print(cpt, "iterations")
    # print("temps : ", time.time()-t)
    return p, time.time() - t, cpt, err


def method2(CdM, epsilon):
    """iteration matrice"""
    # mesure temps et nombre d'etapes
    t = time.time()
    cpt = 0

    # stocke erreur a chaque etape
    err = []

    # matrice de transition
    m = CdM.get_transition_matrix()
    mi = m

    while True:
        cpt += 1

        mi_old = mi
        mi = np.dot(mi, m)  # on peut faire mi*mi si on sait que la matrice converge

        mdiff = 0
        for i in range(len(m)):
            for j in range(len(m)):
                mdiff = max(mdiff, abs(mi[i][j]-mi_old[i][j]))
        err.append(mdiff)

        if mdiff < epsilon:
            break

    # print(cpt, "iterations")
    # print("temps : ", time.time()-t)
    p = np.dot(np.array(CdM.distribution_to_vector(CdM.get_initial_distribution())), mi)
    return p, time.time() - t, cpt, err


def method3(CdM):
    """pas iteration : calcul du point fixe"""
    t = time.time()
    m = CdM.get_transition_matrix()
    """#pM=p <=> p(M-I) = 0
    #la resolution ne marche pas car le vecteur nul convient toujours
    for i in range(len(m)):
      m[i][i]-=1
    p = np.linalg.solve(m,[0]*len(m))"""
    """
    #calcule toutes les valeurs propres et les vecteurs propres associes
    vals, vecs = np.linalg.eig(m)
    print(vals)
    #print(vecs)
    #renvoyer le vecteur propre correspondant a la valeur propre 1
    for i in range(len(vals)):
      if abs(vals[i]-1)<0.1:
        res = vecs[:,i]
        res = (res/res.sum()).real
        
        if is_proba(res):
          print(res)
          print("max diff", max_diff_vec(res, np.dot(res, m)))
          return (res, time.time()-t)
    """
    # recherche au maximum len(m)-2 vp
    # marche sauf quand on specifie recherche autour de vp 1 ou which="SI" (smallest imaginar)
    # pourrait calculer seulement une vp mais ca ne marche pas
    transposee = np.array([[m[j][i] for j in range(len(m))] for i in range(len(m))])
    vals, vectors = linalg.eigs(transposee, k=len(transposee) - 2)

    for i in range(len(vals)):
        if abs(vals[i] - 1) < 1:
            try:
                res = np.array(vectors[:, i])
                res = (res / res.sum()).real

                if is_proba(res, .1):
                    return res, time.time() - t, max_diff_vec(res, np.dot(res, m))
            except RuntimeWarning:
                continue

    print("ERROR NOT FOUND")
    #retourne "None"

def mystd(vals):
    return np.std(vals)/math.sqrt(len(vals))

def run4methods(CdM, nb_run=2):
    def _traite_iter(lres, epsilon=1.0e-9):
        """un element est un tuple (distribution, temps, nb_iter, list_err)
        retourne errelalog, err, errlog, temps, tempslog, nbiter, nbiterlog"""
        lres = np.array(lres)
        m = CdM.get_transition_matrix()
        #distribution
        print(lres[0][0])

        l=[math.log10(max(lres[i][3][-1], epsilon)) for i in range(len(lres))]
        print("errelalog", np.mean(l), mystd(l))

        erreel = np.array([max_diff_vec(x[0], np.dot(x[0], m)) for x in lres])
        #erreel = np.array([max_diff_vec(x[0], [3/8,2/8,3/8]) for x in lres])
        print("err", np.mean(erreel), mystd(erreel))
        print("errlog",
              np.mean([math.log10(x) for x in erreel]),
              mystd( [math.log10(x) for x in erreel]))

        #non irreductible
        #print([np.mean([lres[j][0][i] for j in range(len(lres))]) for i in range(len(lres[0][0]))])

        print("temps", np.mean(lres[:, 1]), mystd(lres[:, 1]))
        print("tempslog",
              np.mean([math.log10(x) for x in lres[:, 1]]),
              mystd([math.log10(x) for x in lres[:, 1]]))

        print("nb iter", np.mean(lres[:, 2]), mystd(lres[:, 2]))

    print("method0")
    _traite_iter([method0(CdM, epsilon=1.0e-4) for _ in range(nb_run)])

    print("\n\nmethod1")
    _traite_iter([method1(CdM, epsilon=1.0e-9) for _ in range(nb_run)])

    print("\n\nmethod2")
    _traite_iter([method2(CdM, epsilon=1.0e-9) for _ in range(nb_run)])
    print("\n\nmethod3")
    if CdM.is_ergodic():
        r = np.array([method3(CdM) for _ in range(nb_run)])
        # [],err errlog temps tempslog
        print ([], [], np.mean(r[:, 2]), mystd(r[:, 2]),
                np.mean([math.log10(x) for x in r[:, 2]]),
                mystd([math.log10(x) for x in r[:, 2]]),
                np.mean(r[:, 1]), mystd(r[:, 1]),
                np.mean([math.log10(x) for x in r[:, 1]]),
                mystd([math.log10(x) for x in r[:, 1]]))

    else:
        print("skipped")



etats=[10, 30, 50]
print("FEU ROUGE")
run4methods(FeuRouge())

print("\n--------------------------------\nMONO BESTIOLE")
for nb_etat in etats:
    print("nb etats :", nb_etat)
    run4methods(MonoBestiole(nb_etat, 0.4, 0.6), nb_run=3)

print("\n--------------------------------\nMOUSE IN MAZE")
run4methods(MouseInMaze())

print("\n--------------------------------\nOIE")
[run4methods(Oie(nb_etat, 0, 0), nb_run=3) for nb_etat in etats]
