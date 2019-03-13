/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class Producteur implements Runnable {

	private EnsembleDonnee e;
	public Producteur(EnsembleDonnee ens) {
		e=ens;
	}
	@Override
	public void run() {
		for(int j=0; j<3; j++){
			for (int i = 0; i < 4; i++) {
				e.ajout((int)(Math.random()*3));
				Thread.yield();
			}
			try {
				Thread.sleep(200);
			} catch (InterruptedException e1) {
				e1.printStackTrace();
			}
		}
	}

}
