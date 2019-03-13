#BEROUKHIM FONTAINE

from time import process_time
import sys

n=0
m=0

#matrice n*m contenant EMPTY, WHITE ou BLACK
M=[]

EMPTY=0
WHITE=1
BLACK=2

#liste de n listes de tailles quelconques d'entiers naturels strictement positifs
L=[]

#liste de m listes de tailles quelconques d'entiers naturels strictement positifs
C=[]

#cf enonce
#vrai pour les instances 1 a 16
#faux pour les instances vecteur
emptyMeansWhite=True


def main():
	#######################################
	#0 vect
	#1 matrice
	#2 vecteur propagation
	#3 matrice propagation
	
	mode = 3
	#######################################
	
	if mode==0:
		l=(20,30,35,40,45,50,55,60,100,1000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,110000,120000)
	elif mode==1:
		l=(0,1,11,2)#petites instances d'abord
	elif mode==2:
		l=(20,30,35,40,45,50,55,60,100,1000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,110000,120000)
	elif mode==3:
		l=range(17)
	sys.setrecursionlimit(1000000)
	
	for s in l:
		init("instances/"+("vec_" if mode%2==0 else'') +str(s)+".tom")
		
		print(n,m)
		
		t = process_time()
		
		if mode == 2:
			print("reussi", testVecteurLigne_Rec(0))
			print("temps",process_time()-t)
			continue
		
		if mode==3:
			propagation()
			print("temps",process_time()-t)
			nb = nbNotEmpty()
			printM()
			if nb == n*m:
				print("propagation fait tout le travail")
				continue
			else:
				print("taille",n*m, nb/(n*m))
		
		
		if mode==0:
			ok = enumerationRecVectLigne(0, 0, WHITE) or enumerationRecVectLigne(0, 0, BLACK)
		else:
			ok = enumerationRec(0, WHITE) or enumerationRec(0, BLACK)

		
		print("temps", process_time()-t)
		print ("reussi", ok)
		printM()
		print('\n\n')
		
	
def init(fileName):
	global n,m, L, C, M, emptyMeansWhite
	emptyMeansWhite = fileName[:14] != "instances/vec_"
	
	with open(fileName) as file:	#<=> finally f.close()
		#lecture premiere ligne
		n, m = [int(x) for x in next(file).split()]
		
		#reset L
		L=[]
		
		#lecture des n lignes
		for _ in range (n):		
			#coupe la ligne en deux au niveau des trois espaces
			#et garde la partie droite						 
			line = next(file).split('   ')[1]
			
			#recupere chaque nombre
			L.append([int(x) for x in line.split()])
		
		#si ce n'est pas un vecteur
		if emptyMeansWhite:	
			#saute la ligne vide de separation
			next(file)
			
			#reset C
			C=[]
			
			#lecture des m colonnes
			for _ in range (m): 
				line = next(file).split('   ')[1]
				C.append([int(x) for x in line.split()])
			
		#creation M
		M=[]
		for _ in range(n):
			line=[]
			for _ in range (m):
				line.append(EMPTY)
			M.append(line)
				
		
		
def compareSeqLin(lineIndex):
	#dans le cas d'un vecteur colonne retourne vrai
	if not emptyMeansWhite and m==1:
		return True	
	
	if lineIndex >= n:
		raise IndexError
	
	#curseur qui parcourt la ligne M[lineIndex]
	indexM = 0
	
	try:
		#prend les tailles des blocs de cases noires consecutives a respecter
		for tailleBloc in L[lineIndex]:
			
			#si entre deux blocs, laisse une case blanche
			if indexM != 0:
				
				#verifie blanc
				if M[lineIndex][indexM] != WHITE:
					return False #pas de case blanche
				
				#decale pointeur
				indexM +=1
			
			#deplace le curseur jusquau prochain bloc noir
			while M[lineIndex][indexM] != BLACK:
				indexM +=1
			
			#parcout le bloc
			#la premiere case est noire, on ne la re-regarde pas 
			for indexM in range(indexM+1, indexM + tailleBloc):
				
				if M[lineIndex][indexM] != BLACK:
					return False #pas de case noire
			
			#incremente index pour pointer la case suivant le bloc
			indexM +=1
			
	except IndexError:
		return False#depasse du tableau
	
	#verifie que le reste de la ligne est blanc
	for indexM in range(indexM, m):
		if M[lineIndex][indexM] == BLACK:
			return False
		
	return True


def compareSeqCol(colIndex):
	#dans le cas d'un vecteur ligne retourne vrai
	if ((not (emptyMeansWhite)) and n==1):
		return True	
	
	if colIndex >= m:
		raise IndexError
	
	#curseur qui parcourt la colonne M[][colIndex]
	indexM = 0
	
	try:
		#prend les tailles des blocs de cases noires consecutives a respecter
		for tailleBloc in C[colIndex]:
			
			#si entre deux blocs, laisse une case blanche
			if indexM != 0:
				
				#verifie blanc
				if M[indexM][colIndex] != WHITE:
					return False#pas de case blanche
				
				#decale pointeur
				indexM +=1
			
			#deplace le curseur jusquau prochain bloc noir
			while M[indexM][colIndex] != BLACK:
				indexM +=1
			
			#parcout le bloc
			#la premiere case est noire, on ne la re-regarde pas 
			for indexM in range(indexM+1, indexM + tailleBloc):
				
				if M[indexM][colIndex] != BLACK:
					return False#pas de case noire
			
			#incremente index pour pointer la case suivant le bloc
			indexM +=1
			
	except IndexError:
		return False#depasse du tableau
			
	#verifie que le reste de la colonne est blanc
	for indexM in range(indexM, n):
		if M[indexM][colIndex] == BLACK:
			return False
		
	return True


def enumerationRec(k,c):	
	#la duree d'execution est superieure a 5 minutes
	#sauf pour les instances 0,1 et 11 qui sont tres petites.

	ok=True
	raz=False
	i=k//m
	j=k%m
	
	if M[i][j] == EMPTY:
		M[i][j] = c
		raz=True
	elif M[i][j] != c:
		return False
		
	if i == n-1:
		ok = compareSeqCol(j)
	if ok and j == m-1:
		ok = compareSeqLin(i)
		
	if ok:
		if i == n-1 and j == m-1:
			return True
		ok = enumerationRec(k+1, WHITE) or enumerationRec(k+1, BLACK)
		
	if not ok and raz:
		M[i][j]=0
		
	return ok

def enumerationRecVectLigne(i, j, c):
	raz=False
	
	if M[i][j] == EMPTY:
		M[i][j] = c
		raz=True
	elif M[i][j] != c:
		return False
	
	ok=True
	if j == m-1:
		ok = compareSeqLin(i)
		
	if ok:
		if j == m-1:
			return True
		ok = enumerationRecVectLigne(i, j+1, WHITE) or enumerationRecVectLigne(i, j+1, BLACK)
	
	if not ok and raz:
		M[i][j]=EMPTY
		
	return ok

def testSiAucun(V, i, j, c):
	for i in V[i:j+1]:
		if i == c:
			return False
	return True

def testVecteur_Rec(V, L, j, l, TT):
	if l == 0:
		return testSiAucun(V, 0, j, 2)
	if l == 1 and j == L[l-1] - 1:
		return testSiAucun(V, 0, j, 1)
	if j <= L[l-1] - 1:
		return False
	if TT[j][l-1] != EMPTY:
		return TT[j][l-1]
	if V[j] == BLACK:
		c1 = False
	else:
		c1 = testVecteur_Rec(V, L, j-1, l, TT)
	if not testSiAucun(V,j-(L[l-1]-1),j,1):
		c2 = False
	else:
		if V[j-L[l-1]] == BLACK:
			c2 = False
		else:
			c2 = testVecteur_Rec(V, L, j-L[l-1]-1, l-1, TT)
	TT[j][l-1] = c1 or c2
	return TT[j][l-1]

def testVecteurLigne_Rec(i):
	_L = L[i]
	l = len(_L)
	TT = [[0 for _ in range(l)] for __ in range(m)]

	return testVecteur_Rec(M[i], _L, m-1, l, TT)

def testVecteurColonne_Rec(j):
	V = [M[i][j] for i in range(n)]
	_C = C[j]
	l = len(_C)
	TT = [[0 for _ in range(l)] for __ in range(n)]

	return testVecteur_Rec(V, _C, n-1, l, TT)


		
		
#retoune (boolean, int) = (remplissable, nb changement marque)
def propagLin(i, marque):
	nb=0
	for j in range(m):
		if M[i][j]==EMPTY:
			M[i][j]=WHITE
			c1 = testVecteurLigne_Rec(i)
			M[i][j]=BLACK
			c2 = testVecteurLigne_Rec(i)
			M[i][j] = EMPTY
						
			#non remplissable
			if not c1 and not c2:
				return (False, nb)
			
			#ca ne peut etre que blanc
			if c1 and not c2:
				M[i][j] = WHITE
				if not marque[j]:
					marque[j]=True
					nb +=1
					
			#ca ne peut etre que noir
			if not c1 and c2:
				M[i][j] = BLACK
				if not marque[j]:
					marque[j]=True
					nb +=1

	return (True, nb)
	
			
def propagCol(j, marque):
	nb=0
	for i in range(n):
		if M[i][j]==EMPTY:
			M[i][j]=WHITE
			c1 = testVecteurColonne_Rec(j)
			M[i][j]=BLACK
			c2 = testVecteurColonne_Rec(j)
			M[i][j]=EMPTY
			
			if not c1 and not c2:
				return (False, nb)
			
			if c1 and not c2:
				M[i][j] = WHITE
				if not marque[i]:
					marque[i]=True
					nb +=1
					
			if not c1 and c2:
				M[i][j] = BLACK
				if not marque[i]:
					marque[i]=True
					nb +=1
					
	return (True, nb)
			
	
def propagation():
	ok =True
	nbmL=n
	nbmC=m
	marqueL=[True for _ in range(n)]
	marqueC=[True for _ in range(m)]
	nb=0
	
	while ok and ((nbmL!=0) or (nbmC != 0)):
		i=0
		while ok and i<n:
			if marqueL[i]:
				(ok, nb) = propagLin(i, marqueC)
				nbmC +=nb
				marqueL[i] = False
				nbmL +=-1
			i +=1
		j=0
		while ok and j<m:
			if marqueC[j]:
				(ok, nb) = propagCol(j, marqueL)
				nbmL +=nb
				marqueC[j] = False
				nbmC +=-1######supp err dans ennonce
			j +=1
	return ok
				
	
	
def printM(showSpecification=True):
	if showSpecification:
		if emptyMeansWhite or n==1: 
			print("lignes", [L[i] for i in range(n)])
		if emptyMeansWhite or m==1: 
			print("colonnes", [C[j] for j in range(m)])
		
	for i in range(n):
		print([M[i][j] for j in range(m)])
		
def nbNotEmpty():
	cpt=0
	for i in range (n):
		for j in range(m):
			if M[i][j]!=EMPTY:
				cpt+=1
	return cpt

#permet de lancer le code
main()
