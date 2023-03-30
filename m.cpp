#include <iostream>
using namespace std;
int main()
{
    int n, a[100];
    cin >> n;
    a[1] = n / 100;
    a[2] = (n % 100) / 10;
    a[3] = n % 10;
    cout << (a[1] + a[2] + a[3]);
}