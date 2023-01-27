#include <iostream>
#include <vector>
#include <fstream> 

void dfs(int u, const std::vector<std::vector<int>>& g, std::vector<int>& components, int cur_comp) {
    components[u] = cur_comp;
    for(int v : g[u]){
        if(components[v] ==  -1){
            dfs(v, g, components, cur_comp);
        }
    }
}

int main() {
    int n,m;
    // std::cin >> n >> m;
    std::ifstream fin("test.txt"); // открыли файл для чтения
    unsigned int start_time =  clock(); // начальное время
    fin >> n >> m; // считали первое слово из файла
    std::vector<std::vector<int>> g(n);
    std::vector<int> comp_number(n, -1);
    for(int i = 0; i < m; ++i){
        int a;
        int b;
        fin >> a >> b;
        --a;
        --b;
        g[b].push_back(a);
        g[a].push_back(b);
    }

    int cur_comp = 0;
    for(int i = 0; i < n; ++i){
        if(comp_number[i] == -1){
            dfs(i, g, comp_number, cur_comp);
            ++cur_comp;
        }
    }

    std::vector<std::vector<int>> result(cur_comp);
    for(int i = 0; i < comp_number.size(); ++i){
        result[comp_number[i]].push_back(i);
    }

    // for(int i = 0; i < result.size(); ++i){
    //     for(int v : result[i]) {
    //         std::cout << v + 1 << " ";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << clock() - start_time <<'\n';

    return 0;
}