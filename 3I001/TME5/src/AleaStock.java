/*
 * Léonie THIRIAT
 */

public class AleaStock {
	private AleaObjet[] stock;
	public AleaStock(int taille){
		stock = new AleaObjet[taille];
		for (int i = 0; i < stock.length; i++) {
			stock[i]=new AleaObjet(1, 5);
		}
	}
	
	public int getTaille(){
		return stock.length;
	}
	
	public AleaObjet get(int i){
		return stock[i];
	}
}
