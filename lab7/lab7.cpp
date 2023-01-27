#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

#define max 2147483647

int ConvertNum(int index, std::string my_str){
    if(my_str == "-1"){
        return index - 1;
    }
    else if(my_str == "/2"){
        return index/2;
    }
    else{
        return index/3;
    }
}

int main(){
    // int n;
    // std::cin >> n;
    std::ifstream fin("test.txt"); // открыли файл для чтения
    long long n;
    fin >> n; // считали первое слово из файла
    std::vector<int> ba(n + 1);
    std::vector<std::string> op(n + 1);
    ba[1] = 0;
    unsigned int start_time =  clock(); // начальное время
    for(int i = 2; i <= n; ++i){
        int minus_one = ba[i-1];
        int div_by_two = (i % 2 == 0 ? ba[i/2] : max);
        int div_by_three = (i % 3 == 0 ? ba[i/3] : max);
        ba[i] = std::min(minus_one, std::min(div_by_two, div_by_three));
        if(ba[i] == minus_one){
            op[i] = "-1";
        }
        else if (ba[i] == div_by_two){
            op[i] = "/2";
        }        
        else{
            op[i] = "/3";
        }
        ba[i] += i;
    }
    // std::cout << ba[n] << '\n';

    // int index = n;
    // while(index != 1){
    //     std::cout << op[index] << ' ';
    //     index = ConvertNum(index, op[index]);
    // }
    // std::cout << "\n";
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << search_time << "\n";
    return 0;
}