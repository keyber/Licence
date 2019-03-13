/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class EnsembleDonnee {
	private ArrayList<Integer> list = new ArrayList<>();
	private ReentrantReadWriteLock l = new ReentrantReadWriteLock();

	public void ajout(int data){
		l.writeLock().lock();
		list.add(data);
		l.writeLock().unlock();
	}

	public void enlever(int data){
		l.writeLock().lock();

		try {
			final int index = list.lastIndexOf(data);

			if(index==-1)
				throw new MonException();

			list.remove(index);
		}
		finally {
			l.writeLock().unlock();
		}
	}

	public void afficher() {
		l.readLock().lock();
		System.out.println(list);
		l.readLock().unlock();
	}


	static class MonException extends RuntimeException{

	}
}

