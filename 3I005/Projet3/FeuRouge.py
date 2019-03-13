# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

import utils
from CdM import CdM


# feu rouge herite de CdM
class FeuRouge(CdM):
    def __init__(self):
        super().__init__()

    def get_states(self):
        return ['Rouge', 'Orange', 'Vert']

    def get_transition_distribution(self, state):
        if state == 'Rouge':
            return {'Rouge': 0.8, 'Vert': 0.2}
        elif state == 'Orange':
            return {'Orange': 0.7, 'Rouge': 0.3}
        elif state == 'Vert':
            return {'Vert': 0.8, 'Orange': 0.2}
        else:
            raise IndexError

    def get_initial_distribution(self):
        return {'Vert': 0.3, 'Rouge': 0.7}

    def show_distribution(self, distribution):
        fig, ax = plt.subplots()
        fig.set_size_inches(4, 1)
        ax.set_xticks([])
        ax.set_yticklabels(self.get_states())
        ax.set_yticks([0, 1, 2])
        ax.imshow(self.distribution_to_vector(distribution).reshape(3, 1), cmap=utils.ProbaMap)

