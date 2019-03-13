
public enum Position {
	SUD(0), NORD(1);
	private	Position(int index) {
		this.index = index;
	}
	private final int index;
	public int index(){return index;}
}
