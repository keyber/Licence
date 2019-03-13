/*
 * Léonie THIRIAT
 */
public class Test extends Object {
	public static void main(String[] args) {
		Salle s = new Salle(3);

		Barbier b = new Barbier(s);
		s.addBarbier(b);
		Thread tBarbier = new Thread(b);
		tBarbier.start();

		Thread[] tClients = new Thread[16];
		for (int i = 0; i < tClients.length; i++) {
			tClients[i] = new Thread(new Client(s));
			tClients[i].start();
		}

		// on attend que tt le mde ai fini
		for (int i = 0; i < tClients.length; i++) {
			try {
				synchronized (tClients[i]) {
					tClients[i].join();
				}
			} catch (InterruptedException e) {
				System.out.println("Test.main() : client.join interrompu");
			}
		}

		System.out.println("tous les clients ont fini");
		// dit au b de fermer la boutique
		synchronized (tBarbier) {
			tBarbier.interrupt();
		}
		System.out.println("fin main");
	}
}
