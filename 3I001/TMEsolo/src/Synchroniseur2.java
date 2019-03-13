//BEROUKHIM Keyvan 3506789
import java.util.concurrent.ArrayBlockingQueue;

public class Synchroniseur2 {
	
	private static int taille=3;
	ArrayBlockingQueue<Perroquet> abq = new ArrayBlockingQueue<>(taille);
	private int nb=0;


	public void enregistrer(Perroquet p){
		synchronized (this) {
			nb++;
			
			abq.add(p);
			
			if(nb==taille)
				this.notifyAll();
		}
	}

	public void barriere() throws InterruptedException{
		//attend que tout le monde soit la
		synchronized (this) {
			while(nb!=taille){
				this.wait();
			}
		}
	}

	
	public void reveillerUnPerroquet() {
		//prend le perroquet en tete
		Perroquet p = abq.poll();
		
		//le reveille
		p.reveiller();	
		
		//l'ajoute en queue
		abq.add(p);
	}
	
	public void reveilleRandom() throws InterruptedException{
		//attend que tout le monde soit la
		barriere();
		
		//reveille le premier (on pourrait faire avancer la file pour en prendre un au hazard dans la file)
		reveillerUnPerroquet();	
	}
}
