/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class Hangar {
	private boolean occupe=false;
	private static int nb=1;
	private final int id;
	private int idOccupant=-1;
	
	Hangar(){
		id=nb++;
	}
	
	
	public void entrer(int id) {
		if(isOccupe())
			throw new RuntimeException("hangar deja occupe");
		occupe=true;
		idOccupant=id;
	}
	
	@Override
	public String toString() {
		return "Hangar"+id+ " occ"+idOccupant;
	}


	public boolean isOccupe() {
		return occupe;
	}
}
