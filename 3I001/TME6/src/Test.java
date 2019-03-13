/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class Test {

	private static int n=5;
	public static void main(String[] args) {
		final Hangar[] tab = new Hangar[n];
		for (int i = 0; i < tab.length; i++) {
			tab[i]=new Hangar();
		}
		final PoolHangars ph = new PoolHangars(tab);
		
		final SegTournant tournant = new SegTournant(ph);
		final Thread threadTournant = new Thread(tournant);
		threadTournant.start();
		
		final SegAccueil accueil = new SegAccueil();
		
		final Loco[] locos = new Loco[n];
		final Thread[] threads = new Thread[n];
		for (int i = 0; i < locos.length; i++) {
			locos[i] = new Loco(accueil, tournant, ph);
			threads[i] = new Thread(locos[i]);
			threads[i].start();
		}
		
		for (int i = 0; i < threads.length; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		threadTournant.interrupt();
		System.out.println("fin main");
		

	}

}
