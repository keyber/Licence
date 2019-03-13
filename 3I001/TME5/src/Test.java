/*
 * Léonie THIRIAT
 */

public class Test {

	public static void main(String[] args) {
		int n = 20;
		Chariot chariot = new Chariot(10, n/2);
		AleaStock stock = new AleaStock(n);
		Chargeur chargeur = new Chargeur(stock, chariot);
		new Thread(chargeur).start();
		Dechargeur dechargeur = new Dechargeur(chariot);
		new Thread(dechargeur).start();
		
		
	}

}
