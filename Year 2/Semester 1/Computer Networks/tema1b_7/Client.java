/*
Un client trimite unui server un sir de caractere si doua numere (fie acestea s, i, l). Serverul va returna clientului subsirul de lungime l a lui s care incepe la pozitia i.
*/

import java.util.Scanner;
import java.io.*;
import java.net.*;

public class Client{

	public static void trimite_sir(DataOutputStream out,String sir) throws Exception{
		
		out.writeShort(sir.getBytes().length);
		for(byte b : sir.getBytes()){
			out.writeByte(b);
		}
		out.writeByte(0); //terminatorul
	}

	public static String citire_rezultat(DataInputStream in) throws Exception{
		int dimensiune=in.readShort();
		if(dimensiune==0){
			return null;
		}
		byte[] b = new byte[dimensiune];
		for(int i=0;i<dimensiune;i++){
			b[i]=in.readByte();
		}
		return new String(b);
	}

	public static void main(String[] args) throws Exception{

		Socket s = new Socket("127.0.0.1",8888);

		Scanner scanner=new Scanner(System.in);
		System.out.println("Dati sir");
		String sir=scanner.nextLine();

		System.out.println("Dati i");
		int i=Integer.parseInt(scanner.nextLine());
		System.out.println("Dati l");
		int l=Integer.parseInt(scanner.nextLine());

		DataInputStream in = new DataInputStream(s.getInputStream());
		DataOutputStream out=new DataOutputStream(s.getOutputStream());

		trimite_sir(out,sir);
		out.writeShort(i);
		out.writeShort(l);
			
		String rezultat=citire_rezultat(in);
		System.out.println(rezultat);

		s.close();
	}
}
