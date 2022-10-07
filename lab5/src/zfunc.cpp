#include <iostream>
#include <vector>
#include <fstream> 
#include <ctime>

std::vector<int> ZFunction (std::string& zF){
    int n = zF.size();
    int left = 0;
    int right = 0;
    std::vector<int>Res(n);
    Res[0] = zF.size();
    for(int i = 1; i < n; i++){
        if(i > right){
            int j = 0;
            while(zF[i + j] == zF[j] && j < n){
                ++j;
            }
            Res[i] = j;
            if(i + j > right){
                right = i + j - 1;
                left = i;
            }
        }
        else{
            if(Res[i - left] + i - 1 < right){
                Res[i] = Res[i - left];
            }
            else{
                int j = right - i + 1;
                while(zF[j] == zF[j + i] && j + i < n){
                    j++;
                    Res[i]++;
                }
                Res[i] += right - i + 1;
                if(Res[i] + i - 1 > right){
                    right = Res[i] + i - 1;
                    left = i;
                }
            }
        }
    }
    return Res;
}

std::vector<int> NaiveZF(std::string& text){
    int n = text.size();
    std::vector<int> Res(n);
    Res[0] = n;
    for(int i = 1; i < n; i++){
        int j = 0;
        while(text[0 + j] == text[i + j] && i + j < n){
            ++j;
        }
        Res[i] = j;
    }
    return Res;
}

void Result(std::string& text, std::string&pattern){
    std::string zF = pattern + "$" + text;
    std::vector<int> Res = NaiveZF(zF);
    // for(int i = 0; i < text.size(); i++){
    //     if(Res[pattern.size() + 1 + i] == pattern.size()){
    //         std::cout << i << "\n";
    //     }
    // }
}

int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::string text;
    std::string pattern;
    std::ifstream file("tests.txt");
    getline(file, text);
    unsigned int start_time =  clock();
    while(getline(file, pattern)){
        std::string zF = pattern + "$" + text;
        Result(text, pattern);
    } 
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << search_time << "\n";
    file.close();
}