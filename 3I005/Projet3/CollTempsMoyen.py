# -*- coding: utf-8 -*-
from Collector import Collector
import time
from Oie import Oie
import numpy as np
from CdMSampler import CdMSampler


class CollTempsMoyen(Collector):
    def __init__(self, etat):
        self.etat = etat

    def initialize(self, cdm, max_iter):
        self.t0 = time.time()
        self.it0 = 0
        self.temps = []
        self.iters = []
        self.max_iter = max_iter
    
    def receive(self, cdm, it, state):
        """
        Fonction appelee à chaque iteration d'une simulation
        :param cdm: la CdM simulee
        :param iter: l'indice de l'iteration
        :param state: l'etat dans l'iteration courante
        :return: True si on doit arrêter la simulation
        """
        if state == self.etat:
            self.iters.append(it - self.it0)
            self.temps.append(time.time() - self.t0)
            self.it0 = it
            self.t0 = time.time()
            
            if np.mean(self.iters)*2 + it > self.max_iter:
                return True
        
        return False

    def finalize(self, cdm, iteration):
        """
        Fonction appelee à la fin de la simulation
        :param iteration: l'indice de la dernière iteration
        """
        pass

    def get_results(self, cdm):
        """
        Fonction appelee après la simulation afin de collecter les resultats
        :return: None si pas de resultats,
        sinon un dictionnaire contenant une cle et comme valeur un type simple ou un dictionnaire.
        """
        # cle = 0, choisi arbitrairement
        return {0: (self.temps, self.iters)}

o = Oie(20, 0.0, 0.0, 2)
sampler = CdMSampler(o)
sampler.add_collector(CollTempsMoyen(1))
res = sampler.run(100000).get(0)
print("taille", len(res[0]))
print("temps", np.mean(res[0]), np.std(res[0]))
print("nb iter", np.mean(res[1]), np.std(res[1]))
