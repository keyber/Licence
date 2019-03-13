
public class Synchroniseur {

	private Perroquet [] perroquets;
	private int i;
	private int cpt;
	private int nbPerroquets;
	private int nbAffichage = 0;
	
	public Synchroniseur (int n) {
		perroquets = new Perroquet[n];
		nbPerroquets = n;
		i = 0;
		cpt = 0;
	}
	
	public synchronized void enregistrer(Perroquet perroquet) {
		perroquets[i] = perroquet;
		i = (i + 1) % nbPerroquets;
	}
	
	public synchronized void barriere () throws InterruptedException {
		cpt++;
		if (cpt == nbPerroquets + 1) {
			notifyAll();
		}
		else {
			wait();
		}
	}

	public synchronized void reveillerUnPerroquet() {
		perroquets[i].reveiller();
		i = (i + 1) % nbPerroquets;
	}

}
