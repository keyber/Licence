# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

import utils
from CdM import CdM
import pyAgrum.lib.ipython as gnb
import random


class Oie(CdM):
    def __init__(self, n, p=0.04, q=0.02, d=6):
        if 2 * p + q > 0.1 or q >= p or n<=d:
            print("erreur param n,p,q,d : ", n, p, q, d)
            #on continue quand meme
        self.n = n
        self.p = p
        self.q = q
        self.d = d

        # tableau indice par indice=(etat-1) entrant
        # contenant indice sortant
        # indice+2n si puits

        # constant pour la plupart des cases
        c = [i for i in range(0, n)]

        # depart et arrivee ne sont pas speciaux
        for i in range(1, n-1):

            r = random.random()
            if r < p:  # recule de 2 cases minimum
                j = i - 2
                # retombe sur le terrain sur une case normale
                while j >= 0 and c[j] != j:
                    j -= 1
                if j >= 0:
                    c[i] = j

            else :
                r -= p
                if r < p:  # avance de 2 cases minimum
                    j = i + 2
                    # retombe sur le terrain
                    # sans rebondir
                    # sur une case normale
                    # ne gagne pas
                    while j <= n - 2 and c[j] != j:
                        j += 1
                    if j <= n - 2:
                        c[i] = j

                else:
                    r -= p
                    if r < q:  # puits
                        c[i] = i + 2 * n

        self.carte = c
        #print(self.carte)
        super().__init__()

    def get_states(self):
        res = []
        for i in range(len(self.carte)):
            ci = self.carte[i]
            
            #cases normales
            if ci == i:
                res.append(i+1)
            
            # etats du puits
            if ci >= self.n: 
                res.append(ci+1)
                res.append(ci+1 - self.n)
                res.append(ci+1 - 2 * self.n)
            
            #les cases de saut ne sont pas des etats, seule leur destination compte
            #les sauts menent forcement a une case normale
            #donc la dest sera ajoutee avec les cases normales
                
        return res

    def get_initial_distribution(self):
        return {1: 1}

    def get_transition_distribution(self, state):
        # passe un tour dans le puits
        if state > self.n:
            return {state - self.n : 1}

        # a la fin retourne au debut
        if state == self.n:
            return {1 : 1}

        res = {}
        #pour tout resultat au de possible:
        for i in range(self.d):
            # passage aux indices
            target = state + i

            # rebondi si depasse
            if target > self.n - 1:
                target = 2 * (self.n-1) - target

            # check pieges puis repasse en etat
            res[self.carte[target] + 1] = res.get(self.carte[target] + 1, 0) + 1/self.d

        return res

    def show_distribution(self, distribution):
        fig, ax = plt.subplots()
        fig.set_size_inches(4, 1)
        ax.set_xticks([])
        ax.set_yticklabels(self.get_states())
        ax.set_yticks(range(self.n))
        ax.imshow(self.distribution_to_vector(distribution).reshape(self.n, 1), cmap=utils.ProbaMap)
        

