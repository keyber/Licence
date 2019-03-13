/*
 * Léonie THIRIAT
 */

public class Client implements Runnable {
	private static int count;
	private final int id;

	private boolean enSalleDAttente = false;

	private boolean barbierOccupe = true;
	private Salle salle;

	public Client(Salle salle) {
		this.salle = salle;
		id = count++;
	}

	@Override
	public void run() {
		if(!salle.AjouteClient(this)) {
			System.out.println(this + " : La salle est pleine, je repars");
			return;
		}
		Thread.yield();//avec un peu de chance on s'occupera de nous avant qu'on s'endorme
		synchronized (this) {
			while (barbierOccupe) {
				System.out.println(this + " : je vais dormir en attendant qu'un barbier me r�veille");
				try {
					this.wait();
				} catch (InterruptedException e) {
					System.out.println("Client.run() : this.wait interrompu");
				}
			}
		}

		synchronized (this) {
			try {
				salle.enleveClient(this);	
				this.wait();
			} catch (InterruptedException e) {
			}
		}

		System.out.println(this + " : C'est fini je rentre chez moi");
	}

	public void setBarbierLibre() {
		synchronized (this) {
			//dans cet ordre ?
			barbierOccupe = false;
			this.notify();//si on ne s'est pas encore endormi ne fait rien
		}
	}

	public void setDansLaSalleDAttente(boolean dedans) {
		enSalleDAttente=dedans;
	}
	public boolean enSalleDAttente() {
		return enSalleDAttente;
	}

	@Override
	public String toString() {
		return getClass().getName() + id;
	}
	

}