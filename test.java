class Person {
}

class Student extends Person {
    void study() {
        System.out.println("study");
    }
}

public class test {
    public static void main(String[] args) {
        Person p = new Person();
        Student s = (Student)p;
        s.study();
    }
}