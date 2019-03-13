/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
package ex2;
import java.awt.Point;

import graphique.Fenetre;

public class testDebut {

	public static void main(String[] args) {
		Fenetre f = new Fenetre(400, 400, "NotreFenetre","orange");/*
		Point p = new Point(100,100);
		Point p2 = new Point(200,100);
		Point p3 = new Point(150,160);
		f.tracerLignePointAPoint(p, p2);
		f.tracerLignePointAPoint(p2, p3);
		f.tracerLignePointAPoint(p3, p);*/

		new Thread(new DessineLigne(100, 100, 200, 100, f)).start();
		new Thread(new DessineLigne(200, 100, 150, 160, f)).start();
		new Thread(new DessineLigne(150, 160, 100, 100, f)).start();
	}

}
