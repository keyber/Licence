void echange(int * tab, int i, int j) {
    int tmp;
    tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

void tri(int * tab, int taille) {
    int valmax;
    int i, imax;

    // cas terminal : fin de recursivite
    if (taille < 2) {
        return;
    }

    // cas général :  taille > 1
    valmax = 0;
    for (i = 0; i < taille; i++) {
        if (tab[i] > valmax) {
            valmax = tab[i];
            imax = i;
        }
    } // fin for
    echange(tab, imax, taille - 1);
    tri(tab, taille - 1);
}

int main(void) {
    int tab[5] = { 3, 33, 49, 4, 23 };
    tri(tab, 5);
}
