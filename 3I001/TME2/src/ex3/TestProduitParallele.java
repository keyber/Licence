/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
package ex3;

import java.io.File;

public class TestProduitParallele {

	public static void main(String[] args) {

		File f = new File("donnees_produit1");
		MatriceEntiere m1 = new MatriceEntiere(f);
		f = new File("donnees_produit2");
		MatriceEntiere m2 = new MatriceEntiere(f);

		MatriceEntiere m = new MatriceEntiere(m1.getLignes(),m2.getColonnes());
		
		for (int i = 0; i < m.getLignes(); i++)
			for (int j = 0; j < m.getColonnes(); j++)
				new Thread(new CalculElem(i, j, m, m1, m2)).start();
		
		m.afficher();
	}

}
