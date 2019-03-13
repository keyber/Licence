import matplotlib.pyplot as plt
import numpy as np

LARGEUR_BUT = 20
LARGEUR = 72
LONGUEUR = 116
BUT_Y = 26
BUT_X = LONGUEUR-1
ECARTS = [20,12,28,0]
NB_JOUEURS = [3,5,2,1,1]
COORDS_X = [34,66,98,114]
TIREUR_X = 10
RAYON_BALL = 2
RAYON_JOUEUR = 1
MIN_Y = [1,1,1,27]
MAX_Y = [LARGEUR - (NB_JOUEURS[i]-1)*ECARTS[i]-RAYON_JOUEUR for i in range(3)]+[45]


def get_config(l):
    """ liste des positions des joueurs a partir d'une liste
    de 4 entiers, la position des manettes (entre MIN_Y et MAX_Y) """
    res =[]
    for (i,e) in enumerate(l):
        for j in range(NB_JOUEURS[i]):
            res.append((COORDS_X[i],e+j*ECARTS[i]))
    return res


def dessine_baby(conf,traj = None):
    img = np.zeros((LONGUEUR,LARGEUR))
    for x,y in conf:
        img[(x-RAYON_JOUEUR):(x+RAYON_JOUEUR),(y-RAYON_JOUEUR):(y+RAYON_JOUEUR)]=1
    img[BUT_X,BUT_Y:(BUT_Y+LARGEUR_BUT)] = 0.5
    if traj is not None:
        for x,y in traj:
            img[(int(x)-RAYON_BALL):(int(x)+RAYON_BALL),(int(y)-RAYON_BALL):(int(y)+RAYON_BALL)]=0.8
    return img

def test_collision(coord,conf):
    for x,y in conf:
        if abs(x-coord[0])<=(RAYON_BALL+RAYON_JOUEUR) and abs(y-coord[1])<=(RAYON_JOUEUR+RAYON_BALL):
            return True
    return False

def simu_tir(tir,conf):
    x,y = TIREUR_X,tir[0]
    bx,by = BUT_X,tir[1]
    dy  = (by-y)/(bx-x)
    traj = []
    for i,dx in enumerate(range(x,bx)):
        traj.append((dx,i*dy+y))
        if test_collision(traj[-1],conf): 
            return traj,False
        if (i*dy+y)<=0 or (i*dy+y)>LARGEUR:
            return traj,False
    if traj[-1][1]<BUT_Y or traj[-1][1]>(BUT_Y+LARGEUR_BUT):
        return traj,False
    return traj,True

def get_tir():
    return (30,33)

conf = get_config([1,1,1,33])

cpt=0
for i in range(LARGEUR):
    for j in range(BUT_Y, BUT_Y + LARGEUR_BUT):
        traj,res = simu_tir((i,j),conf)
        if res:
            cpt+=1
print(cpt, cpt /(LARGEUR * LARGEUR_BUT))
plt.imshow(dessine_baby(conf,traj),extent = [0,LARGEUR,0,LONGUEUR],origin="lower")
plt.show()


















