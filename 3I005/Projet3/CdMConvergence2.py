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
import matplotlib.pyplot as plt


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
        """
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

        print("nb iter", np.mean(lres[:, 2]), mystd(lres[:, 2]))"""

        l=[math.log10(max(lres[i][3][-1], epsilon)) for i in range(len(lres))]
        erreel = np.array([max_diff_vec(x[0], np.dot(x[0], m)) for x in lres])
        return (np.mean(l), mystd(l),


                np.mean(erreel), mystd(erreel),

                np.mean([math.log10(x) for x in erreel]),
                mystd(  [math.log10(x) for x in erreel]),


                np.mean(lres[:, 1]), mystd(lres[:, 1]),

                np.mean([math.log10(x) for x in lres[:, 1]]),
                mystd(  [math.log10(x) for x in lres[:, 1]]),


                np.mean(lres[:, 2]), mystd(lres[:, 2]),

                np.mean([math.log10(x) for x in lres[:, 2]]),
                mystd(  [math.log10(x) for x in lres[:, 2]]))


    """print("\n\nmethod3")
    if CdM.is_ergodic():
        r = np.array([method3(CdM) for _ in range(nb_run)])
        #[],err errlog temps tempslog
        return ([],[],np.mean(r[:, 2]), mystd(r[:, 2]),
                np.mean([math.log10(x) for x in r[:, 2]]),
                mystd([math.log10(x) for x in r[:, 2]]),
                np.mean(r[:, 1]), mystd(r[:, 1]),
                np.mean([math.log10(x) for x in r[:, 1]]),
                mystd([math.log10(x) for x in r[:, 1]]))

    else:
        print("skipped")"""

    #print("method0")
    return _traite_iter([method0(CdM, epsilon=1.0e-12) for _ in range(nb_run)])

    #print("\n\nmethod1")
    #return _traite_iter([method1(CdM, epsilon=1.0e-9) for _ in range(nb_run)])

    #print("\n\nmethod2")
    #return _traite_iter([method2(CdM, epsilon=1.0e-9) for _ in range(nb_run)])


etats = [10, 50, 100, 300, 500, 750, 1000, 1500, 2000]

res = [
[ -9.0,	-9.0,	-9.0,	-9.0,	-9.0, -9.0,	-9.0,	-9.0,	-9.0,],
[ 0,0,0,0,0,0,0,0,0],
[ 5.616583725887025e-10,	7.782715652493444e-10,	7.824014908175414e-10,	9.5707475711998e-10,	9.821890180512771e-10,  9.939639675562995e-10,	9.925562990866638e-10,	9.993530111513521e-10,	9.988089080857979e-10 ],
[ 0,0,0,0,0,0,0,0,0],
[ -9.250527762744749,   	-9.108868836544536,	    -9.106570330698451,	    -9.019054138151398,	    -9.007804926065129,     -9.002629359038409,	    -9.003244850117259,	    -9.000281074622702, 	-9.000517592957399 ],
[ 3.243169037060329e-16,	3.9720546451956367e-16,	3.9720546451956367e-16,	3.9720546451956367e-16,	3.9720546451956367e-16      ,0,0,0,0 ],
[ 0.0005188544591267903,	0.008317947387695312,	0.07552909851074219,	2.0345388293266295,	    10.375664567947387,     35.93927526473999,	    121.34534215927124, 	620.8808133602142,	    1628.188369512558 ],
[ 0.00010762925778007041,	6.045455565958232e-05,	0.001606951415064296,	0.022221570298147843,	0.14072964870670623,        0,0,0,0 ],
[ -3.387222837372559,	    -2.08021001649381,	    -1.123655349770269,	    0.30795447920084856,	1.015288873086758,      1.5555693150740741,	    2.084023110595027,	    2.793008239358734,	    3.2117046481621476 ],
[ 0.04373026694803312,	    0.003123318095100521,	0.008547123476304305,	0.0046983916217885075,	0.0054896680133193635,      0,0,0,0 ],
[ 25.0,	                    276.0,	                1007.0,	                10324.0,	            31573.0,                75139.0,	            136841.0,	            310325.0,	            545442.0 ],
[ 0,0,0,0,0,0,0,0,0],
[ 1.3979400086720377,	    2.4409090820652177, 	3.0030294705536185,	    4.0138479958718305,	    4.499315849600332,      4.8758654108847805,	    5.1362162392407,	    5.491816764062082,	    5.736748576337463 ],
[ 0.0,              	    0.0,	                9.930136612989092e-17,	1.9860273225978183e-16,	1.9860273225978183e-16      ,0,0,0,0 ]]


#errelalog, err, errlog, temps, tempslog, nbiter, nbiterlog
#   0       2       4       6       8       10      12

#erreur *2 pour seuil a 95%
for i in range(len(res)//2):
    res[2*i+1] = [2*x for x in res[2*i+1]]

etatslog = [math.log10(x) for x in etats]

print("coef temps taille", (res[8][-1]-res[8][0])/(etatslog[-1]-etatslog[0]))

if len(res) >= 12:
    print("coef temps iter", (res[8][-1]-res[8][0])/(res[12][-1]-res[12][0]))

    print("coef iter taille", (res[12][-1]-res[12][0])/(etatslog[-1]-etatslog[0]))

plt.title("temps taille " + str((res[8][-1]-res[8][0])/(etatslog[-1]-etatslog[0])))
plt.errorbar(etatslog,res[8], res[9])
plt.show()
plt.close()

plt.title("temps iter " + str((res[8][-1]-res[8][0])/(res[12][-1]-res[12][0])))
plt.errorbar(res[12], res[8], res[9])
plt.show()
plt.close()

plt.title("iter taille " + str((res[12][-1]-res[12][0])/(etatslog[-1]-etatslog[0])))
plt.errorbar(etatslog, res[12], res[13])
plt.show()
plt.close()

etats=[10, 100]
print("\n--------------------------------\nOIE")
l=np.array([run4methods(Oie(nb_etat, 0, 0), nb_run=1) for nb_etat in etats])
for i in range(len(l[0])):
    print('[', ',\t'.join(map(str, l[:,i])), '],')

"""
print("FEU ROUGE")
run4methods(FeuRouge())
print("\n--------------------------------\nMONO BESTIOLE")
for nb_etat in [10, 50, 100]:
    print("nb etats :", nb_etat)
    run4methods(MonoBestiole(nb_etat, 0.4, 0.6), nb_run=2)


print("\n--------------------------------\nMOUSE IN MAZE")
run4methods(MouseInMaze())
"""

