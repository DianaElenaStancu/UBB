#include <iostream> using namespace std; int main()
{
    int radius;
    cin >> radius;

    float pi;
    pi = 3.1415926;

    float perimeter;
    float area;
    perimeter = 2 * pi * radius;
    area = pi * radius * radius;

    cout << perimeter;
    cout << " ";
    cout << area;

    return 0;
}