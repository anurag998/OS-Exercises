
import java.net.*;
import java.io.*;
import java.time.LocalDate;
import java.time.Month;


public class QOTDServer
{
	public static void main(String[] args)  {
		String[] quotes = new String[]{"Quote1", "Quote2", "Quote3"};
		LocalDate currentDate = LocalDate.now();
		int currDay = currentDate.getDayOfMonth();
		int index = currDay%3;		
		
		try {
			ServerSocket sock = new ServerSocket(6017);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				// we have a connection
				
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				// write the Date to the socket
				pout.println(quotes[index]);

				// close the socket and resume listening for more connections
				client.close();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
	}
}
