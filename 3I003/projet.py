#!/usr/bin/env python3

"""
Projet Algo programmaiton
Auteur: BEROUKHIM Keyvan & FONTAINE Ulysse

Utilisation :
    <Python version 3>
    ./ projet.py <enumeration|testvecrec_ligne|propagation> <path/to/instance_name.tom>

"""
import sys
import time
import signal


def Compare_seq_ligne(i):
    """
    Fonction de comparaison d'une séquence avec une ligne.
    Complexité: O(n)
    """
    _L = L[i][:]
    _V = M[i]

    index = 0

    # élimination des cases blanches
    while (index < len(_V)) and _V[index] == 1:
        index += 1

    # pour chaques bloc de la sequence
    for b in _L:
        count = 0
        # compter le nombre de cases noire
        while (index < len(_V)) and _V[index] == 2:
            count += 1
            index += 1

        # Si le compte n'est pas bon la séquence n'est pas respectér
        if b != count:
            return False

        #passer les autres cases blanches.
        while (index < len(_V)) and _V[index] == 1:
            index += 1
    return True

def Compare_seq_col(i):
    """
    Fonction de comparaison d'une séquence avec une colonne.
    Complexité: O(n)
    """

    _C = C[i][:]
    _V = [line[i] for line in M]

    index = 0

    # élimination des cases blanches
    while (index < len(_V)) and _V[index] == 1:
        index += 1

    # pour chaques bloc de la sequence
    for b in _C:
        count = 0
        # compter le nombre de cases noire
        while (index < len(_V)) and _V[index] == 2:
            count += 1
            index += 1

        # Si le compte n'est pas bon la séquence n'est pas respectér
        if b != count:
            return False

        #passer les autres cases blanches.
        while (index < len(_V)) and _V[index] == 1:
            index += 1
    return True

def Enumeration(k, c):
    """ Fonction Enumeration """
    n = len(M)
    m = len(M[0])

    i = k // m
    j = k % m

    if M[i][j] == 0:
        M[i][j] = c
        raz = True
    else:
        if M[i][j] != c:
            return False
        else:
            raz = False
    ok = True
    if i == (n-1):
        ok = Compare_seq_col(j)
    if ok and j == (m-1):
        ok = Compare_seq_ligne(i)
    if ok:
        if i == n-1 and j == m-1:
            return True
        ok = (Enumeration(k+1, 1) or Enumeration(k+1,2))
    if not ok and raz:
        M[i][j] = 0
    return ok


def loadfile(_f):
    """ Fonction de chargement d'une instance """
    global n
    global m
    global L
    L = []
    global C
    C = []
    global M
    M = []
    with open(_f, 'r') as f:
        nm = f.readline().strip().split()
        n = int(nm[0])
        m = int(nm[1])

        for line in f:
            line = line.strip().split()
            if len(line) == 0:
                break
            L.append([int(x) for x in line[1:]])
        for line in f:
            line = line.strip().split()
            if len(line) == 0:
                break
            C.append([int(x) for x in line[1:]])

        M = [ [ 0 for j in range(m)] for i in range(n)]
    f.close()

def TestSiAucun(V, i, j, c):
    """ Fonction TestSiAucuni """
    for x in V[i:j+1]:
        if x == c:
            return False
    return True

def TestVecteur_Rec(V, _L, j, l, TT):
    """ Fonction TestVecteur_Rec """
    if l == 0:
        return TestSiAucun(V, 0, j, 2)
    if l == 1 and j == _L[l-1] - 1:
        return TestSiAucun(V, 0, j, 1)
    if j <= _L[l-1] - 1:
        return False
    if TT[j][l-1] != None:
        return TT[j][l-1]
    if V[j] == 2:
        c1 = False
    else:
        c1 = TestVecteur_Rec(V, _L, j-1, l, TT)
    if not TestSiAucun(V,j-(_L[l-1]-1),j,1):
        c2 = False
    else:
        if V[j-_L[l-1]] == 2:
            c2 = False
        else:
            c2 = TestVecteur_Rec(V, _L, j-_L[l-1]-1, l-1, TT)
    TT[j][l-1] = c1 or c2
    return TT[j][l-1]

def TestVecteurLigne_Rec(i):
    _V = M[i] # recuperation de la ligne
    _L = L[i] # récuperation de la sequence
    j = len(_V) - 1
    l = len(_L)

    # initialisation du talbeau TT
    TT = [[None for _ in range(l)] for __ in range(m)]

    return TestVecteur_Rec(_V, _L, j, l, TT)

def TestVecteurColonne_Rec(i):
    _V = [line[i] for line in M] # recuperation de la ligne
    _C = C[i] # récuperation de la séquence
    j = len(_V) - 1
    l = len(_C)

    # initialisation du talbeau TT
    TT = [[None for _ in range(l)] for __ in range(n)]

    return TestVecteur_Rec(_V, _C, j, l, TT)


def PropagLigne(i, marque):
    nb = 0
    for j in range(m):
        if M[i][j] == 0:
            M[i][j] = 1
            c1 = TestVecteurLigne_Rec(i)
            M[i][j] = 2
            c2 = TestVecteurLigne_Rec(i)
            M[i][j] = 0
            if (not c1) and (not c2):
                return (False,nb)
            if c1 and (not c2):
                M[i][j] = 1
                if not marque[j] :
                    marque[j] = True
                    nb += 1
            if (not c1) and c2:
                M[i][j] = 2
                if not marque[j] :
                    marque[j] = True
                    nb += 1
    return (True,nb)

def PropagCol(j, marque):
    nb = 0
    for i in range(n):
        if M[i][j] == 0:
            M[i][j] = 1
            c1 = TestVecteurColonne_Rec(j)
            M[i][j] = 2
            c2 = TestVecteurColonne_Rec(j)
            M[i][j] = 0
            if (not c1) and (not c2):
                return (False, nb)
            if c1 and (not c2):
                M[i][j] = 1
                if not marque[i] :
                    marque[i] = True
                    nb += 1
            if (not c1) and c2:
                M[i][j] = 2
                if not marque[i] :
                    marque[i] = True
                    nb += 1
    return (True,nb)

def Propagation():
    nb = 0
    nbmL = n
    nbmC = m
    marqueL = [True for _ in range(n)]
    marqueC = [True for _ in range(m)]
    ok = True

    while ok and ((nbmL != 0) or (nbmC !=0)):
        i = 0
        while ok and (i < n):
            if marqueL[i]:
                (ok, nb) = PropagLigne(i, marqueC)
                nbmC += nb
                marqueL[i] = False
                nbmL -= 1
            i += 1
        j = 0
        while ok and (j < m):
            if marqueC[j] :
                (ok,nb) = PropagCol(j,marqueL)
                nbmL += nb
                marqueC[j] = False
                nbmC -= 1
            j += 1
    return ok


def dump_results(res):
    """ Fonction permettant d'écrir les résultats dans un fichier """
    with open('results.txt', 'a') as f:
        f.write(repr(res) + '\n')
    f.close()

def sig_handler(signum, frame):
    """ Fonction de gestion du signal (lors de l'appel a alarm.alarm(temps en seconde) """
    res = sys.argv[1] + ' ' + repr(n*m) + ' OVER '
    with open('results-propa.txt', 'a') as f:
        f.write(repr(res) + '\n')
    f.close()
    raise Exception("STOP")

""" Main """
if __name__ == '__main__':

    mods = ['enumeration','testvecrec_ligne','propagation']

    signal.signal(signal.SIGALRM, sig_handler)

    if len(sys.argv) != 3:
        print("Usage: ./projet.py <enumeration|testvecrec_ligne|propagation> <instance_name.tom>")
        sys.exit()

    if sys.argv[1].lower() not in mods:
        print("Usage: ./projet.py <enumeration|testvecrec_ligne|propagation> <instance_name.tom>")
        sys.exit()

    loadfile(sys.argv[2])

    #print("m: %s | n: %s" % (n,m))
    #print("M: " + repr(M))
    #print("L: " + repr(L))
    #print("C: " + repr(C))

    sys.setrecursionlimit(1000000) # augmenter la stack 
    signal.alarm(60*30) # arret a 30 min


    if(sys.argv[1] == mods[0]): #enumeration
        start = time.process_time()
        a = (Enumeration(0,1) or Enumeration(0,2))
    if(sys.argv[1] == mods[1]): #testvecrec_ligne
        start = time.process_time()
        a = TestVecteurLigne_Rec(0)
    if(sys.argv[1] == mods[2]): #Propagation
        start = time.process_time()
        a = Propagation()
    elapsed  = time.process_time() - start
    dump_results(sys.argv[1] + ' ' + repr(n*m) + ' ' + repr(elapsed) + ' ' + repr(a) )
    print(sys.argv[1] + ' ' + repr(n*m) + '\t' + repr(elapsed) + '\t' + repr(a))

