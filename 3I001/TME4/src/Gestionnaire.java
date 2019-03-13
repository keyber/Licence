/*
 * Léonie THIRIAT
 */
public class Gestionnaire {
	public static void main(String[] args) {
		MoteurVitre v1 = new MoteurVitre(MoteurVitre.Cote.GAUCHE);
		MoteurVitre.Position p1 = v1.getPosition();
		Thread t1 = new Thread(v1);
		t1.start();

		MoteurVitre v2 = new MoteurVitre(MoteurVitre.Cote.DROITE);
		MoteurVitre.Position p2 = v2.getPosition();
		Thread t2 = new Thread(v2);
		t2.start();

		final Object mutex = new Object();

		synchronized (mutex) {//permet d'atteindre le mutex.wait avant qu'un autre thread fasse mutex.notify
			v1.demander(MoteurVitre.Operation.DESCENDRE, mutex);
			v2.demander(MoteurVitre.Operation.DESCENDRE, mutex);

			while(v1.getPosition()!=MoteurVitre.Position.BASSE || v2.getPosition()!=MoteurVitre.Position.BASSE) {
				try {
					mutex.wait();
				} catch (InterruptedException e) {
					System.out.println("fin d'attente du main 1");
				}
			}
		}

		System.out.println("OUVERTURE (" + v1.getPosition()+", "+v2.getPosition()+")");

		synchronized (mutex) {//permet d'atteindre le mutex.wait avant qu'un autre thread fasse mutex.notify
			boolean attendre=false;
			if(p1==MoteurVitre.Position.HAUTE) {
				v1.demander(MoteurVitre.Operation.MONTER,mutex);
				attendre=true;
			}
			if(p2==MoteurVitre.Position.HAUTE) {
				v2.demander(MoteurVitre.Operation.MONTER,mutex);
				attendre=true;
			}
			if(attendre) {
				try {
					mutex.wait();
				} catch (InterruptedException e) {
					System.out.println("fin d'attente du main 2");
				}
			}
		}
		t1.interrupt();
		t2.interrupt();
		System.out.println("fin main");

	}
}
