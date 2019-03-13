/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
package ex3;

public class CalculElem implements Runnable {

	private final int i, j;
	private final MatriceEntiere m, m1, m2;
	public CalculElem(int i, int j, MatriceEntiere m, MatriceEntiere m1, MatriceEntiere m2) {
		this.i = i;
		this.j = j;
		this.m = m;
		this.m1 = m1;
		this.m2 = m2;
	}
	
	@Override
	public void run() {
		m.setElem(i, j, MatriceEntiere.produitLigneColonne(m1, i, m2, j));
	}

}
