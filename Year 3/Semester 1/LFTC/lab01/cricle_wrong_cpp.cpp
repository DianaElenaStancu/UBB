#include <iostream> using namespace std; int main()
{
    int radius;
    cin >> radius;

    float pi;
    pi = 3.1415926;

    float perimeter;
    float area;
    perimeter = (2 * pi) * radius; // 1
    area = pi * radius * radius;

    cout << perimeter << endl << area; // 2

    return 0;
}