#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> 

class SuffTree{
public:
    class Node{
    public:
        int num_list;
        int l, r;
        Node *suff_link = nullptr;
        std::unordered_map<char, Node*> edges;
        Node(int _l,int _r, int _num_list) : l(_l), r(_r), num_list(_num_list){}

        ~Node(){
            for(auto &i: edges){
                delete i.second;
            }   
        }
        void ListsNums(std::vector<int> &ans){
            if(num_list == -1){
                for(auto &i:edges){
                    i.second->ListsNums(ans);
                }
            } else {
                ans.push_back(num_list);
            }
        }

        // void Print(int lvl, std::string &text){
        //     for(int i = 0; i < lvl; ++i){
        //         std::cout << "\t";
        //     }
        //     for(int i = l; i<=r;++i){
        //         std::cout << text[i];
        //     }
        //     std::cout << "\n";
        //     for(auto &i:edges){
        //         i.second->Print(lvl + 1,text);
        //     }
        // }
    };

    Node *root;
    Node *cur_node;
    int cur_edge;
    int pos = 0; //позиция на ребре, предположительный разрыв

    Node *last_add = nullptr;

    std::string text;

    int count_suff = 0;
    int count_lists = 0;

    void Add(int inpos){
        last_add = nullptr;
        ++count_suff;
        while(count_suff){
            //если мы в узле, то выбираем ребро
            if(pos == 0){
                cur_edge = inpos;
            }
            //проверяем существование ребра
            if(cur_node->edges.find(text[cur_edge])==cur_node->edges.end()){
                //если такого нет, то создаем новый лист и пробуем создать суфф ссылку
                CreateList(inpos, cur_node);
                CreateSufflink(cur_node);
            } else {
                //если позиция длинее ребра, то переходим дальше и все перепроверяем
                if(EdgeFault()){
                    continue;
                }
                //если символ существует, то переходим в него, создаем суфф ссылку и ничего больше не делаем
                Node *edge = cur_node->edges[text[cur_edge]];
                if(text[edge->l+pos] == text[inpos]){
                    CreateSufflink(cur_node);
                    ++pos;
                    break;
                } else {
                    //разрываем вершину, создаем новый лист, привязываем суфф ссылку
                    BreakCreationNode(inpos);
                }
            }
            --count_suff;
            GoToSuffLink();
        }
    }

    void CreateList(int inpos, Node *node){
        ++count_lists;
        Node *list = new Node(inpos, text.size() - 1, count_lists);
        node->edges[text[inpos]] = list;
    }

    bool EdgeFault(){
        Node *edge = cur_node->edges[text[cur_edge]];
        int len_edge = edge->r - edge->l + 1;
        if(pos >= len_edge){
            cur_edge += len_edge;
            pos -= len_edge;
            cur_node = edge;
            return true;
        }
        return false;
    }

    void CreateSufflink(Node *Node){
        if(last_add != nullptr){
            last_add->suff_link = Node;
            last_add = nullptr;
        }
    }

    void BreakCreationNode(int inpos){
        Node *edge = cur_node->edges[text[cur_edge]]; // разделяем существующую и прикрепляем еще одну к split_node
        Node *split_node = new Node(edge->l,edge->l + pos - 1, -1);
        cur_node->edges[text[cur_edge]] = split_node;
        edge->l += pos;
        split_node->edges[text[edge->l]] = edge;
        CreateList(inpos, split_node);
        CreateSufflink(split_node);
        last_add = split_node;
    }

    void GoToSuffLink(){
        if(cur_node == root){
            if(pos > 0){
                --pos;
                ++cur_edge;
            }
        } else {

            if(cur_node->suff_link != nullptr){
                cur_node = cur_node->suff_link;
            }
            else{
                cur_node = root;
            }
        }
    }

    SuffTree(std::string &str){
        text = str + "$";

        int size = text.size();
        root = new Node(-1, -1, -1);
        cur_node = root;
        for(int i = 0; i < size; ++i){
            Add(i);
        }
    }

    ~SuffTree(){
        delete root;
    }

    void Find(std::string &pattern, std::vector<int> &ans){
        ans.clear();
        int size = pattern.size();
        Node *cur = root;
        for(int i = 0; i < size;){
            if(cur->edges.find(pattern[i]) != cur->edges.end()){
                cur = cur->edges[pattern[i]];
                for(int j = cur->l; j <= cur->r && i < size; ++i,++j){
                    if(text[j] != pattern[i]){
                        return;
                    }
                return;
                }
            } else { 
                return;
            }
        }
        cur->ListsNums(ans);
        std::sort(ans.begin(), ans.end());
    }   
    
    // void Print(){
    //     root->Print(0, text);
    // }
};

// int main(){
    // std::string str;
    // std::cin >> str;
    // SuffTree tree(str);
    // int i = 1;
    // while(std::cin >> str){
        // std::vector<int> ans;
        // tree.Find(str, ans);
        // if(!ans.empty()){
        //     std::cout << i << ": " << ans[0];
        //     for(int j = 1; j < ans.size(); ++j){
        //         std::cout << ", " << ans[j];
        //     }
        //     std::cout << "\n";
        // }
        // ++i;
    // }
    // return 0;
// }
int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::string str;
    std::ifstream file("tests.txt");
    getline(file, str);
    SuffTree tree(str);
    int i = 1;
    unsigned int start_time =  clock();
    while(getline(file, str)){
        std::vector<int> ans;
        tree.Find(str, ans);
        // if(!ans.empty()){
        //     std::cout << i << ": " << ans[0];
        //     for(int j = 1; j < ans.size(); ++j){
        //         std::cout << ", " << ans[j];
        //     }
        //     std::cout << "\n";
        // }
        // ++i;
    }
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << search_time << "\n";
    return 0;
    file.close(); 
}
