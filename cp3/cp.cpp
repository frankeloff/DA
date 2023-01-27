#include <iostream>
#include <vector>
#include <fstream> 

const char E = ' ';

class Node{
public:
    int shift;
    int size;
    char last;
    Node(int _shift, int _size, char _last): shift(_shift), size(_size), last(_last){}
};

void Encode(std:: string& word, std:: vector<Node*>& result){
    int global_pos = 0;
    while (global_pos < word.size()){
        Node* node = new Node(0, 0, word[global_pos]);
        if(global_pos == 0){
            result.emplace_back(node);
            global_pos += 1;
        }
        else {
            int max_size = 0;
            int shift = 0;
            for(int i = 0; i < global_pos; ++i){
                int j = i;
                int local_size = 0;
                while((j - i + global_pos) < word.size() && word[j] == word[global_pos + j - i]){
                    ++local_size;
                    ++j;
                }
                if(local_size >= max_size && local_size > 0){
                    max_size = local_size;
                    shift = global_pos - i;
                }
            }
            if(global_pos + max_size > word.size() - 1){
                node->shift = shift;
                node->size = max_size;
                node->last = E;
                result.emplace_back(node);
            }
            else{
                node->shift = shift;
                node->size = max_size;
                node->last = word[global_pos + max_size];
                result.emplace_back(node);
            }
            global_pos += max_size + 1;
        }
    }
}

void Decode(std::string& res, std:: vector<Node*>& result){
    int j = 0;
    for(int i = 0; i < result.size(); ++i){
        if(result[i]->shift > 0){
            for(int k = 0; k < result[i]->size; ++k){
                res.push_back(res[j - result[i]->shift]);
                ++j;
            }
            res.push_back(result[i]->last);
            ++j;
        }
        else{
            res.push_back(result[i]->last);
            ++j;
        }
    }
    std::cout << res << "\n";
}

int main(){
    std:: ios:: sync_with_stdio(false);
    std:: cin.tie(0);
    std:: cout.tie(0);
    unsigned int start_time =  clock();
    std:: string action;
    std:: string word;
    std::ifstream fin("test.txt");
    std:: vector<Node*> result;
    fin >> action;
    if(action == "compress"){
        fin >> word;
        std::cout << word << "\n";
        Encode(word, result);
        // for (int i = 0; i < result.size(); ++i) {
            // std:: cout << result[i]->shift << " " << result[i]->size << " " << result[i]->last << "\n";
        // }
    }
    else if (action == "decompress"){
        int shift, size;
        char last = E;
        while (fin >> shift >> size) {
            if(fin >> last){
            Node* input = new Node(shift, size, last);
            result.emplace_back(input);
            }
            else{
                last = E;
                Node* input = new Node(shift, size, last);
                result.emplace_back(input);
            }
        }
        Decode(word, result);
    }
    for (int i = 0; i < result.size(); ++i) {
        delete result[i];
    }
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << search_time << "\n";
    return 0;
}