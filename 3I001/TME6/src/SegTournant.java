/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class SegTournant implements Runnable {

	private ReentrantLock l = new ReentrantLock();

	/**
	 * {@link #attendreAppel()}
	 * this attend que qqun appel {@link #posTarget}
	 * {@link #appeler(int)}
	 */
	private Condition appel = l.newCondition();


	/**
	 * {@link #appeler(int)}
	 * locos attendent que this soit libre pour l'appeler au début (bLibre)
	 * {@link #sortir()}
	 */
	private Condition libre = l.newCondition();
	private boolean bLibre=true;


	/**
	 * {@link #attendrePositionOK()}
	 * loco attend que this ai fini de se déplacer pour y monter ou en descendre (boonePos)
	 * {@link #seDeplacer()}
	 */
	private Condition deplacer = l.newCondition();


	/**
	 * {@link #attendreEntree()}
	 * this attend que qqun monte pour bouger (idOccupant)
	 * {@link #entrer(int)}
	 */
	private Condition entree = l.newCondition();


	private static final int NO_TARGET = -1, NO_OCCUPANT = -1;

	private int position, posTarget = NO_TARGET;
	private int idOccupant = NO_OCCUPANT;
	private boolean bonnePos;
	private PoolHangars ph;

	public void run() {
		try {
			while (true) {
				attendreAppel();
				seDeplacer();
				attendreEntree();
				seDeplacer();
				attendreVide();
			}
		} catch (InterruptedException e) {
			System.out.println("Terminaison sur interruption du segment tournant");
		}
	}

	public void appeler(int i) throws InterruptedException {//0 pour seg accueil
		if (i < 0 || i > ph.getPool().length)
			throw new RuntimeException("id pb " + i);

		l.lock();
		System.out.println("appeler deb " + this);
		try {
			//attend qu'il ai fini ce qu'il est en train de faire
			while (!bLibre) {
				System.out.println("appeler await");
				libre.await();
			}
			posTarget = i;
			bLibre = false;
			appel.signalAll();
			System.out.println("appeler fin " + this);
		} finally {
			l.unlock();
		}
	}

	private void attendreAppel() throws InterruptedException {
		l.lock();
		System.out.println("attAppel deb " + this);
		try {
			while (posTarget == NO_TARGET) {
				System.out.println("attAppel await");
				appel.await();
			}
			System.out.println("attAppel fin " + this);
		} finally {
			l.unlock();
		}
	}

	private void seDeplacer() throws InterruptedException {
		l.lock();
		System.out.println("seDep deb " + this);
		try {
			Thread.sleep(10);
			position = posTarget;
			bonnePos = true;
			posTarget = NO_TARGET;
			deplacer.signalAll();
			System.out.println("seDep fin " + this);
		} finally {
			l.unlock();
		}
	}

	public void attendrePositionOK() throws InterruptedException {
		System.out.println("attPos deb " + this);
		l.lock();
		try {
			while (!bonnePos) {
				System.out.println("attPos await");
				deplacer.await();
			}
			System.out.println("attPos fin " + this);
			bonnePos=false;
		} finally {
			l.unlock();
		}
	}

	public void sortir(int id) throws InterruptedException {
		l.lock();
		System.out.println("sortir deb " + this);
		try {
			Thread.sleep(10);
			idOccupant = NO_OCCUPANT;
			bLibre=true;
			libre.signalAll();
			System.out.println("sortir fin " + this);
		} finally {
			l.unlock();
		}
	}

	private void attendreVide() throws InterruptedException {
		l.lock();
		System.out.println("attVide deb " + this);
		try {
			while (idOccupant != NO_OCCUPANT) {
				System.out.println("attVide await " + this);
				libre.await();
			}
			System.out.println("attVide fin " + this);
		} finally {
			l.unlock();
		}
	}


	private void attendreEntree() throws InterruptedException {
		l.lock();
		System.out.println("attEntre deb " + this);
		try {
			while (idOccupant == NO_OCCUPANT) {
				System.out.println("attEntre await");
				entree.await();
			}
			posTarget = ph.firstFree();
			System.out.println("attEntre fin " + this);
		} finally {
			l.unlock();
		}

	}

	public void entrer(int id) throws InterruptedException {
		if (idOccupant != NO_OCCUPANT)
			throw new RuntimeException("deja qqun");
		l.lock();
		System.out.println("entrer deb " + this);
		try {
			Thread.sleep(10);
			idOccupant = id;
			entree.signalAll();
			System.out.println("entrer fin " + this);
		} finally {
			l.unlock();
		}
	}

	public int getPosition() {
		l.lock();
		try {
			System.out.println(this);
			return position;
		}
		finally {
			l.unlock();
		}
	}

	public SegTournant(PoolHangars ph) {
		this.ph = ph;
	}

	@Override
	public String toString() {
		return "SegTournant (position, posTarget, occupant) = (" + position + ", " + posTarget + ", " + idOccupant+")";
	}

}
