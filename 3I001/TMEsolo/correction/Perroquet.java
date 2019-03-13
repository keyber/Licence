

import java.util.Random;


public class Perroquet implements Runnable {
	
	private String prenom;
	private Synchroniseur sync;
	private boolean aEteReveille;
	private Random gen;
	
	public Perroquet (String prenom, Synchroniseur sync) {
		this.prenom = prenom;
		this.sync = sync;
		aEteReveille = false;
		gen = new Random();
	}
	
	public synchronized void attendre() throws InterruptedException {
		while (!aEteReveille) {
			this.wait();
		}
		aEteReveille = false;
	}
	
	public synchronized void reveiller() {
		aEteReveille = true;
		this.notifyAll();
	}

	public void run() {
		sync.enregistrer(this);
		try {
			System.out.println(prenom + " avant barrière");
			sync.barriere();
			System.out.println(prenom + " après barrière");
			while (true) {
				attendre();
				System.out.println(prenom);
				Thread.sleep((gen.nextInt(3) + 1) * 1000);
				sync.reveillerUnPerroquet();
			}
		} catch (InterruptedException e) {
			System.out.println("fin de " + prenom);
		}
	}
}
