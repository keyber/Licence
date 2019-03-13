# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

import utils
from CdM import CdM

# mouse herite de CdM
class MonoBestiole(CdM):
    def __init__(self, n, d, g):
        self.n = n
        self.g = g
        self.d = d
        super().__init__()

    def get_states(self):
        return range(1, self.n + 1)

    def get_transition_distribution(self, state):
        if state == 1:
            return {1: 1 - self.d, 2: self.d}
        if state == self.n:
            return {self.n - 1: self.g, self.n: 1 - self.g}
        return {state - 1: self.g, state: 1 - self.g - self.d, state + 1: self.d}

    def get_initial_distribution(self):
        return {self.n//2+1: 1.0}

    def show_distribution(self, distribution):
        fig, ax = plt.subplots()
        fig.set_size_inches(4, 4)
        ax.set_xticks([])
        ax.set_yticklabels(self.get_states())
        ax.set_yticks(range(self.n))
        ax.imshow(self.distribution_to_vector(distribution).reshape(self.n, 1), cmap=utils.ProbaMap)
