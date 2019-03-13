/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
public class Effaceur implements Runnable {

	private EnsembleDonnee e;
	public Effaceur(EnsembleDonnee ens) {
		e=ens;
	}
	@Override
	public void run() {
		for (int i = 0; i < 5; i++) {
			try {
				e.enlever((int)(Math.random()*3));
			}
			catch (Exception e){
				System.out.println("enlève vide");
			}
			
			try {
				Thread.sleep(100);
			} catch (InterruptedException e1) {
				e1.printStackTrace();
			}		
		}
	}
}
