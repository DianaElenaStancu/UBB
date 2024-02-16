flex flexy.l && g++ -w lex.yy.c && a.exe < in.txt

bison -d lab4.y
flex lab4.l
gcc lab4.tab.c lex.yy.c
./a.out in.txt

bison -d activitate.y
flex activitate.l
gcc activitate.tab.c lex.yy.c
./a.out in.txt



#include <iostream> using namespace std; int main()
{
    int radius;
    cin >> radius;
    float pi;
    pi = 1234;

    float perim;
    float area;
    perim = 2 * pi * radius;
    area = pi * radius * radius;

    cout << perim;
    cout << area;

    return 0;
}