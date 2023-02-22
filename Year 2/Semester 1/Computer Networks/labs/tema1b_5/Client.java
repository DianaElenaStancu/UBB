import java.net.*;
import java.io.*;
 
public class Client {
 
public static void main(String args[]) throws Exception {
  //Socket c = new Socket("127.0.0.1", 1234);
  Socket c = new Socket(args[0], Integer.parseInt(args[1]));
  BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
  int a, lg, div;
  System.out.print("numar = ");
  a = Integer.parseInt(reader.readLine());
  
  DataInputStream socketIn = new DataInputStream(c.getInputStream());
  DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());
  
  socketOut.writeShort(a);
  socketOut.flush();
  
  lg = socketIn.readUnsignedShort();
  for (int i = 0; i < lg; i++) {
	div = socketIn.readUnsignedShort();
        System.out.println(div+" ");
  }
  
  reader.close();
  c.close();  
}
 
}
