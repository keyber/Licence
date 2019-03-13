import math
import matplotlib.pyplot as plt
from multiprocessing import Pool, Manager
from functools import partial

#var globales de la matrice
L = 48   # nb col
M = 5643 # nb lig

Q = 21 # nb d'acides differents
acides = "ACDEFGHIKLMNPQRSTVWY-"

def creematrice(fname):
    matrice = []
    with open(fname, 'r') as f:
        for line in f:
            if line[0] != ">":
                matrice.append(line)
    return matrice

def nbOcc(a, i):
    """string acide a * int position i -> int nbOcc"""
    cpt = 0
    for line in matrice:
        if line[i]==a:
            cpt+=1
    return cpt

def poids(a,i):
    """string acide a * int position i -> float poids"""
    return (nbOcc(a, i)+1)/(M+Q)

def entropie(i):
    """int position i -> float entropie relative"""
    s=0
    for a in acides:
        w = poids(a, i)
        s += w*math.log2(w)
    s += math.log2(Q)
    
    return s
    
def f0():
    """liste des frequences de chaque acide dans matrice (= DTrain)"""
    res=[]
    for a in acides:
        s=0
        for i in range(L):
            s+=nbOcc(a, i)
        res.append(s/(L*M))
    return res

def logVraisemblance(ssSeq, f):
    s=0
    for i in range(len(ssSeq)):
        s+=math.log2(poids(ssSeq[i], i)/f[acides.index(ssSeq[i])])
    return s

def nbOcc2(a, i, b, j, matrice):
    """string acide * int position **2 
    -> (nbOccA, nbOccB, nbOccAB)"""
    cpta = 0
    cptb = 0
    cptab = 0
    
    for line in matrice:
        if line[i]==a:
            cpta+=1
            
        if line[j]==b:
            cptb+=1
            if line[i]==a:
                cptab+=1
                
    return (cpta, cptb, cptab)

def poids2(a, i, b, j, matrice):
    """string acide * int position **2 
    -> (poids a, poids b, poids ab)"""
    (a, b, ab) = nbOcc2(a, i, b, j, matrice)
    #print(i,j,a,b,ab)
    MQ = M+Q
    return ((a+1)/MQ, (b+1)/MQ, (ab+1/Q)/(MQ))

def infoMutuelle(i, j, matrice):
    """int positionA i * int positionB j -> correlation entre les deux positions"""
    s=0
    for a in acides:
        for b in acides:
            (pa, pb, pab) = poids2(a, i, b, j, matrice) 
            s += pab*math.log2(pab/(pa*pb))

    return s
    
def addIMtoDict(i, dictionnaire, matrice):
    """pour tout j inferieur a i
    ajoute dans le dictionnaire la cle ((i,j), infoMutuelle(i,j))
    les appels a cette fonction peuvent etre parallelises"""
    for j in range(i):
        dictionnaire[(i,j)] = infoMutuelle(i, j, matrice)
    print("fin",i,"/48")
    
def main():
    #PARTIE II
    #question 1
    print("tableau donnant le nombre d'occurence et le poids pour toutes les colonnes et tous les acides")
    for a in acides:
        print(a, end="  ")
        for i in range(L):
            s = str(nbOcc(a, i)).rjust(8)
            s = s + str(round(10000*poids(a,i))).rjust(5)
            print(s, end="")
        print()
    
    #question2
    plt.plot([entropie(i) for i in range(L)])
    plt.title("entropie en fonction de la position")
    plt.show()
    plt.close()
   
    #question3
    f = f0()
    
    #question4
    t = creematrice("test_seq.txt")[0]
    plt.plot([logVraisemblance(t[i:i+L], f) for i in range(len(t)-L)])
    plt.title("log-vraisemblance en fonction de la premiere position")
    plt.show()
    plt.close()
    
    
    #PARTIE III
    
    #creation dictionnaire threadsafe
    iMut=Manager().dict()
    
    #creation pool de 8 threads
    pool = Pool(processes=8)
    
    #application partielle de la fonction pour passage des arguments constants
    #puis execute la fonction avec les differents threads
    pool.map_async(partial(addIMtoDict, dictionnaire=iMut, matrice=matrice), range(1,L))
    
    #lecture fichier distance
    dist={}
    with open("distances.txt") as fDist:
        for line in fDist:
            l = line.split(" ")
            #inversion de x et y pour avoir x<y comme dans iMut
            dist[((int) (l[1]),(int) (l[0]))]=(float)(l[2])
        
        
    #attend la fin d'execution de tous les threads pour continuer
    pool.close()
    pool.join()
    
    #tri par correlation decroissante
    l = sorted(iMut.items(), key = lambda x : x[1], reverse=True)
    print(l)
    
    fractions=[]
    cpt=0
    for i in range(50):
        #l[i]:ieme plus grande valeur
        #l[i][0] recupere ses coordonnees
        #dist[l[i][0]] obtient la distance correspondant a ces coord
        if dist[l[i][0]]<8:
            cpt+=1
        fractions.append(cpt/(i+1))    
    
    plt.plot(fractions)
    plt.title("fraction des paires ayant une distance inferieure a 8")
    plt.xlabel('nombre de paires considerees')
    plt.show()
    
#pour multiprocessing:
#si on ne met pas le if, la matrice sera creee plusieurs fois
if __name__ == '__main__':  
    matrice = creematrice("Dtrain.txt")  
    main()
    
    
    
    
    
    