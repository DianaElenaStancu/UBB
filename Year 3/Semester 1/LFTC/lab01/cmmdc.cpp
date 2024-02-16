//
// Created by Diana-Elena Stancu on 10.10.2023.
//
#include <iostream> using namespace std; int main()
{
    int a;
    int b;
    cin >> a;
    cin >> b;
    int r;
    r = a % b;
    while(r > 0)
    {
        a = b;
        b = r;
        r = a % b;
    }

    cout << b;

    return 0;
}
