#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
 
int main() {
    ifstream fin;
    fin.open("king2.in");
    long long n;
    n = 8;
    vector<vector<long long>> a(n, vector<long long>(n,0));
    vector<vector<long long>> d(n,vector<long long>(n,0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fin >> a[i][j];
        }
    }
    for(int i = n-1; i >= 0; i--) {
        for(int j = 0; j < n; j++) {
            d[i][j] = a[i][j];
            if (j-1 >= 0) {
                d[i][j] = a[i][j] + d[i][j-1];
            }
            if (i+1 < n) {
                d[i][j] = a[i][j] + d[i+1][j];
            }
            if ((j-1 >= 0) && (i+1 < n)) {
                d[i][j] = a[i][j] + min(d[i][j-1], min(d[i+1][j], d[i+1][j-1]));
            }
        }
    }
    ofstream fout;
    fout.open("king2.out");
    fout << d[0][n-1];
}