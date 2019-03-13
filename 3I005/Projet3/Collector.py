# -*- coding: utf-8 -*-


class Collector:
    def initialize(self, cdm, max_iter):
        """
        :param max_iter: le nombre max d'iteration de la simulation
        Fonction appelee en debut de simulation
        """
        raise NotImplementedError

    def receive(self, cdm, iter, state):
        """
        Fonction appelee à chaque iteration d'une simulation
        :param cdm: la CdM simulee
        :param iter: l'indice de l'iteration
        :param state: l'etat dans l'iteration courante
        :return: True si on doit arrêter la simulation
        """
        raise NotImplementedError

    def finalize(self, cdm, iteration):
        """
        Fonction appelee à la fin de la simulation
        :param iteration: l'indice de la dernière iteration
        """
        raise NotImplementedError

    def get_results(self, cdm):
        """
        Fonction appelee après la simulation afin de collecter les resultats
        :return: None si pas de resultats, sinon un dictionnaire contenant une cle et comme valeur un type simple ou un
        dictionnaire.
        """
        raise NotImplementedError
