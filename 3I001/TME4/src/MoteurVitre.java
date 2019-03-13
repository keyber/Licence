/*
 * Léonie THIRIAT
 */
public class MoteurVitre implements Runnable {

	public static enum Position {
		HAUTE, BASSE
	}

	public static enum Operation {
		MONTER, DESCENDRE, AUCUN
	}

	public static enum Cote {
		GAUCHE, DROITE
	}

	private final Cote cote;
	private Position position;
	private Operation operation;

	@Override
	public void run() {
		while (true) {
			if(operation==Operation.AUCUN) {
				synchronized (this) {
					try {
						this.wait();
					} catch (InterruptedException e) {
						System.out.println("fin d'attente du run "+this);
						return;//permet au thread de se terminer si le main le veut
					}
				}
			}
			checkOp();
			if(notified!=null) {
				synchronized (notified) {
					notified.notify();
				}
				notified=null;
			}
		}
	}

	private synchronized boolean checkOp() {
		System.out.println("d�but checkOp "+ this);
		if (operation == Operation.AUCUN
				|| operation == Operation.MONTER && position == Position.HAUTE
				|| operation == Operation.DESCENDRE && position == Position.BASSE) {
			operation = Operation.AUCUN;
			System.out.println("sans rien faire : fin op "+this);
			return false;
		}

		try {
			Thread.sleep((long) (Math.random() * 500));
		} catch (InterruptedException e) {
			System.out.println("interruption du sleep de checkOp");

		}
		position = operation == Operation.MONTER ? Position.HAUTE : Position.BASSE;
		operation = Operation.AUCUN;
		System.out.println("fin op "+this);
		return true;
	}


	private Object notified;
	public void demander(Operation operation, Object notified) {
		if(this.operation!=Operation.AUCUN || operation==Operation.AUCUN)
			return;
		this.operation = operation;
		synchronized (this) {			
			this.notify();
		}
		this.notified=notified;
	}

	public Position getPosition() {
		return position;
	}

	public MoteurVitre(Cote cote) {
		this.cote = cote;
		position = Math.random()<.5?Position.BASSE:Position.HAUTE;
		this.operation=Operation.AUCUN;
	}

	@Override
	public String toString() {
		return "Vitre cot� "+cote+" operation "+operation+" position "+position;
	}

}
