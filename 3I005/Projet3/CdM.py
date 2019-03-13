# -*- coding: utf-8 -*-
import numpy as np
import pyAgrum as gum
# import pyAgrum.lib.ipython as gnb
import pyAgrum.lib.notebook as gnb
import utils


# import networkx as nx

class CdM:
    """
    Class virtuelle representant une Chaîne de Markov
    """

    def __init__(self):
        """
        Constructeur. En particulier, initalise le dictionaire stateToIndex

        :warning: doit être appele en fin de __init__ des classes filles
        avec ` super().__init__()`
        """
        s = self.get_states()
        self.stateToIndex = {s[i]: i for i in range(len(s))}

    def get_states(self):
        """
        :return: un ensemble d'etats enumerable (list, n-uple, etc.)
        """
        raise NotImplementedError

    def get_transition_distribution(self, state):
        """
        :param state: etat initial
        :return: un dictionnaire {etat:proba} representant l'ensemble des etats atteignables à partir de state et leurs
        probabilites
        """
        raise NotImplementedError

    def get_initial_distribution(self):
        """
        :return: un dictionnaire representant la distribution à t=0 {etat:proba}
        """
        raise NotImplementedError

    def __len__(self):
        """
        permet d'utiliser len(CdM) pour avoir le nombre d'etat d'un CdM

        :warning: peut être surchargee
        :return: le nombre d'etat
        """
        return len(self.get_states())

    def distribution_to_vector(self, distribution):
        return np.array([distribution.get(s, 0.0) for s in self.get_states()])

    def vector_to_distribution(self, vector):
        states = self.get_states()
        return {states[i]: vector[i] for i in range(len(vector)) if vector[i]}

    def show_distribution(self, distribution):
        print(distribution)

    def get_transition_matrix(self):
        """numpy.array des vecteurs de transition pour chaque etat"""
        return np.array([self.distribution_to_vector(self.get_transition_distribution(s))
                         for s in self.get_states()])

    def show_transition_matrix(self):
        utils.show_matrix(self.get_transition_matrix())

    def get_transition_graph(self):
        """appeler gnb.showDot(f.get_transition_graph().toDot()) pour afficher"""
        g = gum.DiGraph()
        l = len(self.get_states())

        # cree les noeuds
        for i in range(l):
            g.addNode()

        m = self.get_transition_matrix()
        # parcourt toute la matrice et ajoute un arc pour chaque case non nulle
        for i in range(l):
            for j in range(l):
                if m[i][j]:
                    g.addArc(i, j)
        return g

    def show_transition_graph(self, gnb):
        s = "digraph {\n"
        l = len(self.get_states())
        for i in range(l):
            s += str(i)
            s += " [label=\""
            s += str(i)
            s += "\"];\n"
        s += "\n"

        m = self.get_transition_matrix()
        # parcourt toute la matrice et ajoute un arc pour chaque case non nulle
        for i in range(l):
            for j in range(l):
                if m[i][j]:
                    s += str(i)
                    s += "->"
                    s += str(j)
                    s += " [label="
                    s += str(m[i][j])
                    s += "];\n"
        s += "}"
        gnb.showDot(s)

    def get_communication_classes(self):
        """retourne la liste des SCC (Strongly Connected Components)"""
        res = []
        g = self.get_states()
        # l'algorithme de kosaraju trouve les scc d'un graphe
        for scc in utils.kosaraju(self.get_transition_graph()):
            res.append([g[identif] for identif in scc])
        return res

    def get_absorbing_classes(self):
        """liste des SCC dont on ne peut pas ressortir"""
        res = []
        g = self.get_states()
        m = self.get_transition_matrix()

        # retourne vrai si un noeud d'une scc sort de celle-ci
        def _sort(scc):
            for i in scc:
                for j in range(len(m)):
                    if j not in scc and m[i][j]:
                        return True
            return False

        for scc in utils.kosaraju(self.get_transition_graph()):
            if not _sort(scc):
                res.append([g[identif] for identif in scc])

        return res

    def is_irreducible(self):
        return len(self.get_communication_classes()) == 1

    def get_periodicity_state(self, m, state):
        """la periode d'un état est le PGCD des longueurs des circuits passant par lui
        @:param m transition_matrix"""
        mi = m
        pgcd = 0
        for i in range(1, len(m) + 1):

            # on peut revenir en index en i sauts
            if mi[state][state]:

                # non initialise
                if 0 == pgcd:
                    pgcd = i

                # calcul du pgcd entre le pgcd actuel et la longueur trouvee
                else:
                    pgcd = utils.pgcd(pgcd, i)

                # si le pgcd tombe a 1, il ne changera pas
                if 1 == pgcd:
                    return 1

            # calcul de la puissance suivante de la matrice
            mi = np.dot(mi, m)

        return pgcd

    def get_periodicity(self):
        """doit etre irreductible
        la periode d'une scc est la période de ses etats"""
        return self.get_periodicity_state(self.get_transition_matrix(), 0)

    def is_aperiodic(self):
        return 1 == self.get_periodicity()

    def is_ergodic(self):
        #dans cet ordre
        return self.is_irreducible() and self.is_aperiodic()
