/*
 * Léonie THIRIAT
 */

public class Chargeur implements Runnable {
	private AleaStock stock;
	private Chariot chariot;

	public Chargeur(AleaStock stock, Chariot chariot) {
		this.stock = stock;
		this.chariot=chariot;
	}

		int c=0;
	public boolean charger(){
		for(int i=c; i<stock.getTaille(); i++){
			if(!chariot.add(stock.get(i)))
				return false;
			c++;
		}
		
		return true;
	}

	@Override
	public synchronized void run() {
		while(stock.getTaille()>c){
			charger();
				synchronized (chariot) {
					chariot.notifyAll();
					try {
						chariot.wait();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}			
				
			}
		}
		chariot.setChargeurVide();
		synchronized (chariot) {
			chariot.notifyAll();
		}
		System.out.println(this+" stock vide");
	}

}
