/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class Lecteur implements Runnable {

	private EnsembleDonnee e;
	public Lecteur(EnsembleDonnee ens) {
		e=ens;
	}
	@Override
	public void run() {
		for (int i = 0; i < 3; i++) {
			e.afficher();
			try {
				Thread.sleep(100);
			} catch (InterruptedException e1) {
				e1.printStackTrace();
			}		
		}
	}
}
