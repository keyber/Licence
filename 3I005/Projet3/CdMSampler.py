# -*- coding: utf-8 -*-
import random


class CdMSampler:
    def __init__(self, cdm):
        self.cdm = cdm
        self.collectors = []
        # simulation effectuee
        self.done = False

    def add_collector(self, collector):
        """
        Ajoute un nouveau collector (instance d'une classe qui herite de Collector)
        :param collector: le nouveau collector
        """
        self.collectors.append(collector)

    def notify_initialize(self, nbr_iter):
        """
        Notifie tout collector qu'une simulation de taille maximum nbr_iter va commencer
        :param nbr_iter: nombre maximum d'iterations de la simulation
        """
        for collector in self.collectors:
            collector.initialize(self.cdm, nbr_iter)

    def notify_receive(self, iteration, state):
        """
        Notifie à tout collector le passage de la simulation à l'etat `state` dans l'iteration `iteration`.

        :param iteration: indice de l'iteration courante
        :param state: etat atteint dans cette iteration
        :return: True : si un collector a indique qu'il voulait que la simulation s'arrête
                 False : si tout collector est OK pour continuer la simulation
        """
        res = False
        for collector in self.collectors:
            if collector.receive(self.cdm, iteration, state):
                res = True
        return res

    def notify_finalize(self, nbr_iteration):
        """
        Notifie tout collector que la simulation se termine à l'iteration `nbr_iteration`
        :param nbr_iteration: l'indice de la dernière iteration
        """
        for collector in self.collectors:
            collector.finalize(self.cdm, nbr_iteration)

    def collect_results(self, nbr_iteration):
        """
        Integre dans un seul dictionnaire l'ensemble des resutalts des collectors
        :param nbr_iteration: l'indice de la dernière iteration
        :return: le dictionnaire des resultats
        """
        if not self.done:
            return None

        res = {'nbr_iterations': nbr_iteration}
        for collector in self.collectors:
            r = collector.get_results(self.cdm)
            if r is not None:
                for key, val in r.items():
                    # plusieurs fois la même cle (cf. CollSingleStateCounter) => on cree un dictionnaire avec toutes les
                    # valeurs engrangees
                    if key in res:
                        if type(res[key]) is not dict:
                            res[key] = {0: res[key]}

                        if type(val) is dict:
                            res[key].update(val)
                        else:
                            res[key][1 + max(res[key].keys())] = val
                    else:
                        res[key] = val
        return res

    @staticmethod
    def draw_from_distribution(distribution):
        """
        tire aleatoirement un etat suivant la distribution
        :param distribution: la distribution de tirage
        :return: l'etat tire aleatoirement suivant la distribution
        """
        r = random.random()
        n = 0
        for key, value in distribution.items():
            n += value
        for key, value in distribution.items():
            if r < value / n:
                return key
            r -= value / n
        raise AssertionError("erreur random")

    def run(self, max_iter):
        """
        Effectue une simulation complète, de taille maximum max_iter
        :param max_iter: nombre maximum d'iterations
        :return: le dictionnaire des resultats collectes par les collector
        """
        """2) Fournir le corps de la methode CdMSampler.run(max_iter). Elle appellera les notify_* pour communiquer avec
    les collectors et doit :
    a. initialiser les collectors et la generation
    b. generer aleatoirement la sequence d'etats en notifiant à chaque fois les collecters et en s'arrêtant
    si un collector le demande ou si le nombre d'iterations maximum est atteint.
    c. finaliser les collectors
    d. retourner le resultat calcule par collect_results()"""

        self.done = False
        self.notify_initialize(max_iter)

        d = self.draw_from_distribution(self.cdm.get_initial_distribution())
        i = 0
        if not self.notify_receive(i, d):
            for i in range(1, max_iter + 1):
                d = self.draw_from_distribution(self.cdm.get_transition_distribution(d))
                if self.notify_receive(i, d):
                    break

        self.notify_finalize(i)
        self.done = True
        return self.collect_results(i)
        

