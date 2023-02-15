/*
Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de caractere spatiu din sir.
*/

import java.util.Scanner;
import java.io.*;
import java.net.*;

public class Client{



	public static void main(String[] args) throws Exception{

		Socket s=new Socket("127.0.0.1",8888);
				
		Scanner scanner=new Scanner(System.in);
		System.out.println("Dati sir");
		String x=scanner.nextLine();
		byte[] byteArray=x.getBytes();
		System.out.println(x);

		DataInputStream in=new DataInputStream(s.getInputStream());
		DataOutputStream out=new DataOutputStream(s.getOutputStream());

		int dimensiune=byteArray.length;
		System.out.println("Dimensiune = "+dimensiune);
		out.writeShort(dimensiune);	

		for(byte b : byteArray){
//			int bb = (int)b;
			out.writeShort(b);		
		}

		out.flush();

		int nr_spatii=in.readUnsignedShort();
		System.out.println("Nr spatii = "+nr_spatii);
		s.close();
	}
}
