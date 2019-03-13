import graphique.Fenetre;
import java.awt.Point;

public class Segment {
	private Fenetre f;
	private final Point m, n;
	
	public Segment (Fenetre f, Point m, Point n) {
		this.f = f;
		this.m = m;
		this.n = n;
	}
	
	public static double longueur(Point m, Point n) {
		return Math.sqrt( Math.pow (m.y - n.y, 2.0) + Math.pow (m.x - n.x, 2.0) );
	}

	public static void tracer (Fenetre f, Point m, Point n) {
		f.tracerLignePointAPoint(m, n);
	}
}
