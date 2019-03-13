
public class Client implements Runnable{

	public static final int NB_REQUETE = 5;
	private Serveur s;
	public Client(Serveur s) {
		this.s = s;
	}
	
	@Override
	public void run() {
		for (int i = 0; i < NB_REQUETE; i++) {
			try {
				s.soumettre(this, (int)(Math.random()*1000));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void requeteServie(ReponseRequete r) {
		System.out.println("fin "+r);
	}

}
