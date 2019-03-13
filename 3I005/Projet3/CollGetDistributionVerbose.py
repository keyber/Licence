# -*- coding: utf-8 -*-
from Collector import Collector


def max_diff_vec(p, p2):
    return max([abs(p[i] - p2[i]) for i in range(len(p))])


class CollGetDistributionVerbose(Collector):
    def __init__(self, epsilon):
        self.epsilon = epsilon
        self.cpt_etats = []
        self.ind_max = 0
        self.nb_iter = 0
        self.err = []
        self.nb_non_nul = 0

    def initialize(self, cdm, max_iter):
        self.cpt_etats = [0] * len(cdm.get_states())

    def receive(self, cdm, num, state):
        """
        Fonction appelee à chaque iteration d'une simulation
        :param cdm: la CdM simulee
        :param num: l'indice de l'iteration
        :param state: l'etat dans l'iteration courante
        :return: True si on doit arrêter la simulation
        """
        ind = cdm.stateToIndex[state]

        if num == 0:
            err = 1
        else :
            #l'erreur maximale est soit avec la coordonnee qui vient de changer
            #soit avec l'etat le plus souvent visite
            #il n'est pas necessaire de parcourir tout le vecteur
            #la complexite est en O(1)
            err = max(self.cpt_etats[self.ind_max], num - self.cpt_etats[ind])
            err /= num * (num + 1)

        #compte le nombre de composantes non nulles
        if self.cpt_etats[ind] == 0:
            self.nb_non_nul += 1

        # comptabilise l'etat de cette etape
        self.cpt_etats[ind] += 1

        #mise a jour de l'etat le plus visite
        if self.cpt_etats[ind] > self.cpt_etats[self.ind_max]:
            self.ind_max = ind

        #stocke l'erreur actuelle dans la liste
        self.err.append(err)

        # recquiert un nombre minimal d'iteration afin d'eviter de quitter trop tot
        # par ex car on a eu deux fois le meme etat au debut
        # plusieurs compossantes non nulles
        if self.nb_non_nul < 2:
            return False

        # on continue si une composante change de plus d'epsilon
        if err > self.epsilon:
            return False

        # on s'arrete
        return True

    def finalize(self, cdm, iteration):
        """
        Fonction appelee à la fin de la simulation
        :param cdm: la CdM simulee
        :param iteration: l'indice de la dernière iteration
        """
        # divise par taille totale pour obtenir proba
        self.cpt_etats = [self.cpt_etats[i] / (iteration + 1) for i in range(len(self.cpt_etats))]
        self.nb_iter = iteration

    def get_results(self, cdm):
        """
        Fonction appelee après la simulation afin de collecter les resultats
        :return: None si pas de resultats,
        sinon un dictionnaire contenant une cle et comme valeur un type simple ou un dictionnaire.
        """
        # cle = 0,choisi arbitrairement
        return {0: {"distrib": self.cpt_etats, "nb_iter": self.nb_iter, "err": self.err}}
