/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
package ex2;

import java.awt.Point;

import graphique.Fenetre;

public class DessineLigne implements Runnable{

	private final int x1,x2,y1,y2;
	private final Fenetre f;
	public DessineLigne(int x1, int y1, int x2, int y2, Fenetre f) {
		this.x1 = x1;
		this.x2 = x2;
		this.y1 = y1;
		this.y2 = y2;
		this.f = f;
	}

	
	@Override
	public void run() {
		f.tracerLignePointAPoint(new Point(x1,y1), new Point(x2,y2));
	}

}
