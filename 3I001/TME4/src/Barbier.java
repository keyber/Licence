/*
 * Léonie THIRIAT
 */

public class Barbier implements Runnable{
	private Salle salle;

	public Barbier(Salle salle) {
		this.salle=salle;
	}
	public void run() {
		while(true){
			synchronized (salle) {
				while(salle.salleVide()){
					try{
						salle.wait();
					}
					catch (Exception e){
						System.out.println("Barbier.run() : salle.wait() interrompu");
					}
				}
			}

			Client c = salle.getFirst();
			synchronized (c) {
				System.out.println(this+" : \""+c+" � toi\"");
				c.setBarbierLibre();				
			}

			//attend qu'il se  r�veille
			while(c.enSalleDAttente()){
				System.out.println(this+" : \"Je t'attends "+c+"\"");
				try {
					Thread.sleep(10);
				} catch (InterruptedException e) {
					System.out.println("Barbier.run() : sleep(10) interrompu");
				}
			}
			
			tailler(c);			
		}
	}
	
	public void tailler(Client c) {
		if(c.enSalleDAttente())
			throw new RuntimeException("On ne taille pas la barbe de ceux qui dorment !");

		synchronized (c) {
			c.notify();	
		}
	}
}
