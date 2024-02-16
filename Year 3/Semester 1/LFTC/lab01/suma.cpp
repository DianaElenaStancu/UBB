#include <iostream> using namespace std; int main()
{
    int sum;
    sum = 0;
    int x;
    int n;
    cin >> n;
    while(n > 0) {
        cin >> x;
        sum = sum + x;
        n = n-1;
    }
    cout << sum;

    return 0;
}