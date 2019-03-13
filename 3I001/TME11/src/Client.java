/*BEROUKHIM Keyvan
  THIRIAT Leonie*/
import java.util.concurrent.BrokenBarrierException;

public class Client implements Runnable {

	GroupeClients groupeClients;
	Restaurant restaurant;
	public Client(GroupeClients g, Restaurant r) {
		this.groupeClients = g;
		restaurant = r;
	}

	@Override
	public void run() {
		try {
			groupeClients.reserver(this);
		} catch (InterruptedException e) {
			return;
		}
		
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			System.out.println(this+" "+groupeClients.id +" "+e);
		}
		
		try {
			groupeClients.barriereTousArrives();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
	}

}
