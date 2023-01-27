#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

long long minCost(long long n){
    long long f, s, t;
    if(n == 1){
    return 0;
    }
    if(n%3==0){
    t = minCost(n/3);
    }
    else{
    t = 1e8;
    }
    if(n%2==0){
    s = minCost(n/2);
    }
    else{
    s = 1e8;
    }
    f = minCost(n-1);
    return std::min(f, std::min(s, t)) + n;
}

int main(){
    std::ifstream fin("test.txt"); // открыли файл для чтения
    long long n;
    fin >> n; // считали первое слово из файла
    unsigned int start_time =  clock(); // начальное время
    minCost(n);
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << search_time << "\n";
}