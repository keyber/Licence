/*
 * Léonie THIRIAT
 */

public class Dechargeur implements Runnable{
	private Chariot chariot;

	public Dechargeur(Chariot chariot) {
		super();
		this.chariot = chariot;
	}

	@Override
	public synchronized void run() {
		while (!chariot.chargeurVide || !chariot.getContenu().isEmpty()){
			while(!chariot.getContenu().isEmpty())
				chariot.remove();
			synchronized (chariot) {
				chariot.notifyAll();		
				try {
					chariot.wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		System.out.println("fin dechargeur");

	}

}
