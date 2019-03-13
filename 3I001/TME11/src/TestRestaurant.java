/*BEROUKHIM THIRIAT*/
import java.util.LinkedList;
import java.util.List;

public class TestRestaurant {
	public static void main(String[] args) {
		Restaurant restaurant = new Restaurant();
		List<GroupeClients> groupeClients = new LinkedList<GroupeClients>();
		groupeClients.add(new GroupeClients(5, restaurant));
		groupeClients.add(new GroupeClients(6, restaurant));
		groupeClients.add(new GroupeClients(10, restaurant));
		groupeClients.add(new GroupeClients(2, restaurant));
		
	}
}
