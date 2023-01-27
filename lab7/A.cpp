#include <iostream>
using namespace std;
 
int main() {
 long long n, a[102], b;
 cin >> n >> a[1];
 a[0] = 0;
 
 if(n < 2) { 
 cout << a[1];
 return 0;
 }
 for(int i = 2; i <= n; i++) {
 cin >> b;
 a[i] = max( a[i-1], a[i-2] ) + b;
 }
 cout << a[n] << '\n';
 return 0;
}