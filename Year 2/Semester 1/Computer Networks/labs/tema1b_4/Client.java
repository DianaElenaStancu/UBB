/*
Un client trimite unui server doua siruri de caractere ordonate. Serverul va interclasa cele doua siruri si va returna clientului sirul rezultat interclasat.
*/

import java.util.Scanner;
import java.net.*;
import java.io.*;

public class Client{

	public static void trimite_sir(String sir,DataOutputStream out) throws Exception{

		//trimit byte cu byte
		int lungime=sir.getBytes().length;
		out.writeShort(lungime);
		for(byte b : sir.getBytes()){
			out.writeByte(b);
		}
		out.writeByte(0); //terminatorul
	}

	public static String citire_sir(DataInputStream in) throws Exception{
		int lungime=in.readShort();
		byte[] b = new byte[lungime];
		for(int i=0;i<lungime;i++){
			b[i]=in.readByte();
		}
		byte terminator=in.readByte();
		return new String(b);
	}

	public static void main(String[] args) throws Exception{
		Scanner scanner=new Scanner(System.in);
	
		System.out.println("Dati primul sir");
		String sir1=scanner.nextLine();

		System.out.println("Dati al doilea sir");
		String sir2=scanner.nextLine();

		System.out.println(sir1+" "+sir2);

		Socket s=new Socket("127.0.0.1",8888);

		DataInputStream in = new DataInputStream(s.getInputStream());
		DataOutputStream out=new DataOutputStream(s.getOutputStream());

		trimite_sir(sir1,out);
		trimite_sir(sir2,out);
		out.flush();

		String rezultat=citire_sir(in);
		System.out.println(rezultat);

		s.close();
	}
}
