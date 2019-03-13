# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np

from matplotlib import colors

c = np.zeros((100, 4))
c[:, -1] = np.linspace(0, 1, 100)  # gradient de transparence
c[:, 0] = 0.3  # rouge
c[:, 1] = 0.5  # vert
c[:, 2] = 0.5  # bleu
# ProbaMap est une matplotlib.colormap qu'on utilisera pour afficher des valeurs de probabilites (de 0 à 1).
ProbaMap = colors.ListedColormap(c)


def show_matrix(matrix):
    """
    :warning: ne devrait pas être surcharge
    presente la matrice de transition
    :param matrix: np.array qui devrait être une matrice stochasique
    """
    plt.matshow(matrix, cmap=ProbaMap)
    plt.grid(False)
    plt.show()


def pgcd(a, b):
    """pgcd(a,b): calcul du 'Plus Grand Commun Diviseur' entre les 2 nombres entiers a et b"""
    while b != 0:
        a, b = b, a % b

    return a


def dfs(g):
    """
    Depth-first search dans le graphe g.
    Cette fonction n'est qu'un prototype de code : elle ne fait rien à part le parcours en profondeur d'abord dans
    pyAgrum.DiGraph.
    :param g:
    :return:
    """
    mark = dict()
    liste = []

    def _dfs(node):
        if node in mark:  # deja visite
            return

        mark[node] = True
        liste.append(node)
        for fils in g.children(node):
            _dfs(fils)

    for i in g.ids():
        if i not in mark:
            _dfs(i)

    return liste


def kosaraju(g):
    """l'algorithme de kosaraju trouve les composantes fortement connexes d'un graphe"""
    # permier parcourt
    p = dfs(g)

    # deuxieme "parcourt" dans l'autre sens
    p.reverse()

    def _dfs(node, curr_scc):
        if node in p:
            # ajoute le noeud a la scc actuelle
            curr_scc.append(node)

            # enleve les sommets parcourus au fur et a mesure
            p.remove(node)

            for fils in g.children(node):
                _dfs(fils, curr_scc)
        return curr_scc

    list_css = []
    # ajoute une scc tant que p n'est pas vide
    while p:
        list_css.append(_dfs(p[0], []))

    return list_css
