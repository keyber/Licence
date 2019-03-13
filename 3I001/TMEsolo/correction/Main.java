import java.util.Random;


public class Main {

	static int NB_PERROQUET = 3;
	
	public static void main(String[] args) {
		Thread [] perroquets = new Thread[NB_PERROQUET]; 
		int attente = new Random().nextInt(11) + 20;
		Synchroniseur sync = new Synchroniseur(NB_PERROQUET);
	
		perroquets[0] = new Thread(new Perroquet("Coco", sync));
		perroquets[1] = new Thread(new Perroquet("Jaco", sync));
		perroquets[2] = new Thread(new Perroquet("Rico", sync));
		
		try {
			for (int i = 0; i < NB_PERROQUET; i++) {
				perroquets[i].start();
			}	
			sync.barriere();
			sync.reveillerUnPerroquet();
			Thread.sleep(attente * 1000);
			for (int i = 0; i < NB_PERROQUET; i++) {
				perroquets[i].interrupt();
			}
			
			for (int i = 0; i < NB_PERROQUET; i++) {
				perroquets[i].join();
			}
			System.out.println("fin des trois perroquets");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

}
