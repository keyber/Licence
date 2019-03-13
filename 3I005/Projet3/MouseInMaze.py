# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

import utils
from CdM import CdM

# mouse herite de CdM
class MouseInMaze(CdM):
    def __init__(self):
        super().__init__()

    def get_states(self):
        return range(1, 7)

    def get_transition_distribution(self, state):
        if state == 1:
            return {1: .5, 2: .5}
        elif state == 2:
            return {1: .5, 4: .5}
        elif state == 3:
            return {1: .25, 2: .25, 5: .25, 6: .25, }
        elif state == 4:
            return {3: 1.0}
        elif state == 5:
            return {5: 1.0}
        elif state == 6:
            return {6: 1.0}
        else:
            raise IndexError

    def get_initial_distribution(self):
        return {1: 1.0}

    def show_distribution(self, distribution):
        fig, ax = plt.subplots()
        fig.set_size_inches(4, 1)
        ax.set_xticks([])
        ax.set_yticklabels(self.get_states())
        ax.set_yticks([0, 1, 2, 3, 4, 5])
        ax.imshow(self.distribution_to_vector(distribution).reshape(6, 1), cmap=utils.ProbaMap)
