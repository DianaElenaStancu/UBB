//
// Created by Diana-Elena Stancu on 10.10.2023.
//
#include <iostream>
using namespace std;

int main()
{
    int radius;
    cin >> radius;

    float pi;
    pi = 3.1415926;

    float perimeter;
    float area;
    perimeter = 2 * pi * radius;
    area = pi * radius ^ 2; // 1

    cout << perimeter;
    cout << " ";
    cout << area // 2

    return 0;
}