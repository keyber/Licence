/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class PoolHangars {
	private Hangar[] pool;
	
	public PoolHangars(Hangar[] pool) {
		this.pool = pool;
	}

	public int firstFree(){
		for (int i = 0; i < getPool().length; i++) {
			if(!getPool()[i].isOccupe()){
				return i+1;//son id n'est pas sa pos dans le tableau
			}
		}
		return -1;
	}

	public Hangar getHangar(int position) {
		return getPool()[position-1];
	}
	
	@Override
	public String toString() {
		StringBuilder s=new StringBuilder();
		for(Hangar h : getPool()) {
			s.append(h+" ");
		}
		return s.toString();
	}

	public Hangar[] getPool() {
		return pool;
	}

}
