import java.util.concurrent.ArrayBlockingQueue;


public class Synchroniseur2 {
	private ArrayBlockingQueue<Perroquet2> perroquets;
	private int cpt;
	private int nbPerroquets;
	
	public Synchroniseur2 (int n) {
		perroquets = new ArrayBlockingQueue<Perroquet2>(n);
		nbPerroquets = n;
		cpt = 0;
	}
	
	public void enregistrer(Perroquet2 perroquet) {
		perroquets.add(perroquet);
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

	public void reveillerUnPerroquet() throws InterruptedException {
		Perroquet2 p = perroquets.take();
		p.reveiller();
		perroquets.add(p);
	}

}
