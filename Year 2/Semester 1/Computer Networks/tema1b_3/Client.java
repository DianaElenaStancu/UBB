/*
Un client trimite unui server un sir de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).
*/

import java.io.*;
import java.net.*;
public class Client{



	public static void main(String[] args) throws Exception {

		Socket s = new Socket("127.0.0.1",8888);

		DataInputStream in=new DataInputStream(s.getInputStream());
		DataOutputStream out=new DataOutputStream(s.getOutputStream());

		//trimit datele
		int dimensiune=args[0].getBytes().length;
		out.writeShort(dimensiune);
		for(byte b : args[0].getBytes()){
			out.writeByte(b);
		}
		out.writeByte(0); //terminatorul

		out.flush();

		//primesc rezultatul
		byte[] rez=new byte[dimensiune];
		for(int i=0;i<rez.length;i++){
			rez[i]=in.readByte();
		}	
		byte terminator = in.readByte();
		
		String string_rez=new String(rez);
		System.out.println("Rezultat = " + string_rez);
	
		s.close();	
	}

}
