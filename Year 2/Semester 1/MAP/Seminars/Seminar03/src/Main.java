import domain.Student;
import Map.MyMap;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hash set");
        Set<Student> hashStud = new HashSet<>();
        Student s1 = new Student ("Dan", 4.5f);
        Student s2 = new Student ("Ana", 8.5f);
        Student s3 = new Student ("Daniel", 4.5f);
        Student s4 = new Student ("Maria", 8.8f);
        Student s5 = new Student ("Bogdan", 9f);
        hashStud.addAll(Arrays.asList(s1, s2, s3));
        for (Student stud : hashStud) {
            System.out.println(stud);
        }

        System.out.println("\nTree set");
        TreeSet<Student> treeStud = new TreeSet<>(new NameComparator());
        treeStud.addAll(Arrays.asList(s1, s2, s3));
        for (Student stud : treeStud) {
            System.out.println(stud);
        }

        System.out.println("\nHash map");
        HashMap<String, Student> hashMapStud = new HashMap<>();
        hashMapStud.put(s1.getNume(), s1);
        hashMapStud.put(s2.getNume(), s2);
        hashMapStud.put(s3.getNume(), s3);
        for (Map.Entry<String, Student> pair : hashMapStud.entrySet()) {
            System.out.println(pair.getKey() + " " + pair.getValue());
        }

        System.out.println("\nTree map");
        TreeMap<String, Student> treeMapStud = new TreeMap<>();
        treeMapStud.put(s1.getNume(), s1);
        treeMapStud.put(s2.getNume(), s2);
        treeMapStud.put(s3.getNume(), s3);
        for (Map.Entry<String, Student> pair : treeMapStud.entrySet()) {
            System.out.println(pair.getKey() + " " + pair.getValue());
        }

        System.out.println("\nMy map");
        MyMap myMap = new MyMap();
        myMap.add(s1);
        myMap.add(s2);
        myMap.add(s3);
        myMap.add(s4);
        myMap.add(s5);
        myMap.printAll();

        System.out.println("\nSorted students");
        for (Map.Entry<Integer, List<Student>> entry : myMap.getEntries()) {
            List<Student> studentList = entry.getValue();
            studentList.sort(new NameComparator());
            System.out.println(entry.getKey()  + " " + studentList);
        }
    }
    static class NameComparator implements Comparator<Student>{
        @Override
        public int compare(Student o1, Student o2) {
            return o1.getNume().compareTo(o2.getNume());
        }
    }
}

