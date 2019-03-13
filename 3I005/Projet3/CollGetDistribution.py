# -*- coding: utf-8 -*-
from Collector import Collector


class CollGetDistribution(Collector):
    """version naive complexite lineaire avec nombre d'etats"""
    def __init__(self, epsilon, pas):
        self.epsilon = epsilon
        self.pas = pas
        self.cpt_etats = []

    def initialize(self, cdm, max_iter):
        # print("[debut]")
        self.cpt_etats = [0] * len(cdm.get_states())

    def receive(self, cdm, iter, state):
        """
        Fonction appelee à chaque iteration d'une simulation
        :param cdm: la CdM simulee
        :param iter: l'indice de l'iteration
        :param state: l'etat dans l'iteration courante
        :return: True si on doit arrêter la simulation
        """
        id = cdm.stateToIndex[state]
        # comptabilise l'etat de cette etape
        self.cpt_etats[id] += 1

        # affichage de distribution courrante
        if self.pas != 0 and iter != 0 and iter % self.pas == 0:
            cdm.show_distribution(cdm.vector_to_distribution(
                [self.cpt_etats[i] / (iter + 1) for i in range(len(self.cpt_etats))]))

        # recquiert un nombre minimal d'iteration afin d'eviter de quitter trop tot
        # par ex car on a eu deux fois le meme etat au debut
        if iter < 10 or iter < len(cdm.get_states()):  # iter==0
            return False

        # on continue si une composante change de plus d'epsilon
        for i in range(len(cdm.get_states())):
            if i == id:
                if abs((self.cpt_etats[i] - 1) / iter - self.cpt_etats[i] / (iter + 1)) > self.epsilon:
                    return False
            else:
                if abs(self.cpt_etats[i] / iter - self.cpt_etats[i] / (iter + 1)) > self.epsilon:
                    return False

        # on s'arrete
        return True

    def finalize(self, cdm, iteration):
        """
        Fonction appelee à la fin de la simulation
        :param iteration: l'indice de la dernière iteration
        """
        # divise par taille totale pour obtenir proba
        self.cpt_etats = [self.cpt_etats[i] / (iteration + 1) for i in range(len(self.cpt_etats))]

    def get_results(self, cdm):
        """
        Fonction appelee après la simulation afin de collecter les resultats
        :return: None si pas de resultats,
        sinon un dictionnaire contenant une cle et comme valeur un type simple ou un dictionnaire.
        """
        # cle = 0,choisi arbitrairement
        return {0: self.cpt_etats}
