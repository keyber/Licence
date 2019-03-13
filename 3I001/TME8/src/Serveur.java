
/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Serveur implements Runnable {

	private ReentrantLock l = new ReentrantLock();
	private Condition attReq = l.newCondition();
	private Condition traiterReq = l.newCondition();

	private int requete=-1;
	private Client c;

	public void soumettre(Client c, int pRequete) throws InterruptedException{
		l.lock();
		try {
			while(requete!=-1) {
				traiterReq.await();
			}
			requete=pRequete;
			this.c=c;
			attReq.signalAll();
		}
		finally {
			l.unlock();
		}
	}


	public void run() {
		try {
			while (true) {
				attendreRequete();
				new Thread(new CalculServeur(c, requete)).start();
				requete=-1;
				c=null;
				l.lock();
				traiterReq.signalAll();
			}
		} catch (InterruptedException e) {
			System.out.println("Serveur interrompu");
		}
		finally {
			if(l.isHeldByCurrentThread())
				l.unlock();
		}
	}

	private void attendreRequete() throws InterruptedException{
		l.lock();
		try {
			while(requete==-1) {
				attReq.await();
			}
		}
		finally {
			l.unlock();
		}
	}

	
	private static class CalculServeur implements Runnable {
		private final Client mClient;
		private final int mRequete;
		private CalculServeur(Client mClient, int mRequete) {
			this.mClient = mClient;
			this.mRequete = mRequete;
		}

		public void run() {
			try {
				traiterRequete();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		private void traiterRequete() throws InterruptedException{
				if(mRequete%3==0)
					while(true)
						Thread.sleep((int)(100*Math.random()));
				Thread.sleep((int)(100*Math.random()));
				mClient.requeteServie(new ReponseRequete(mRequete));
		}
	}


}
