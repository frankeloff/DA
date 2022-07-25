#include <iostream>
#include <cstring>
#include <fstream> 
#include <sstream>
#include <vector>
#include <ctime>

const int T = 5; // характеристическое число
int Min(int left, int right) ;
void ToLower(char *key);

struct map{
    char key[257];
    unsigned long long value;
};

class BNode{
public:
    bool is_leaf = true;
    map keys[2 * T];
    BNode* child[2 * T + 1];
    int countKeys = 0; //кол-во ключей
    BNode(); // инициализация
};

BNode::BNode(){
    for(int i = 0; i < 2 * T + 1; ++i){
        child[i] = nullptr;
    }
}

int Min(int left, int right) {
    if (left < right) {
        return left;
    }
    return right;
}

bool operator==(map &left, char right[]) {
    int right_len = strlen(right);
    int left_len = strlen(left.key);
    if (left_len != right_len) {
        return false;
    }
    for (int i = 0; i < Min(right_len, left_len); ++i) {
        if (left.key[i] != right[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(map &left, map &right) {
    int right_len = strlen(right.key);
    int left_len = strlen(left.key);
    for (int i = 0; i < Min(right_len, left_len); ++i) {
        if (left.key[i] != right.key[i]) {
            return left.key[i] < right.key[i];
        }
    }
    return left_len < right_len;
}

bool operator<(map &left, char right[]) {
    int right_len = strlen(right);
    int left_len = strlen(left.key);
    for (int i = 0; i < Min(right_len, left_len); ++i) {
        if (left.key[i] != right[i]) {
            return left.key[i] < right[i];
        }
    }
    return left_len < right_len;
}

void ToLower(char *key) {
    int i = 0;
    while (key[i] != '\0') {
        if (key[i] >= 'A' && key[i] <= 'Z') {
            key[i] += 'a' - 'A';
        }
        ++i;
    }
}


void SearchNode(BNode* node, char* key, BNode *&result, int &pos);
void DeleteTree(BNode* node);
void FPrint(BNode* root);
void InsertNonfull(BNode* node, map& element);
void SplitChild(BNode* parent, int pos);
void DeleteNode(BNode* node, char* str);
int SearchInCurrentNode(BNode* node, char* str);
void Merge(BNode* parent, int pos);
void Rebalance(BNode* node, int &pos);
void DeleteFromCurrentNode(BNode* node, int pos);
void NodeToFile(BNode* node, std::ofstream &file);
void TreeFromFile(BNode* node, std::ifstream &file);

class BTree {
public:
    void Insert(map &element);
    void Search(char *key);
    // void PrintTree();
    void Delete(char* str);
    void Serialize(std::ofstream &file);
    void Deserialize(std::ifstream &file);
    BTree();
    ~BTree();
private:
    BNode *root;
};

BTree::BTree() {
        root = new BNode;
}

BTree::~BTree(){
        DeleteTree(root);
}

void BTree::Search(char *key){
    BNode* result;
    int pos;
    SearchNode(root, key, result, pos);
    if (result) {
        std::cout << "OK: " << result->keys[pos].value << "\n";
    } else {
        std::cout << "NoSuchWord" << "\n";
    }
    return;
}

void SearchNode(BNode* node, char* key, BNode *&result, int& pos) {
    pos = SearchInCurrentNode(node, key);
    if(pos >= 0){
        result = node;
    }
    else{
        if(node->is_leaf){
            result = nullptr;
        }
        else{
            pos = -pos - 1;
            SearchNode(node->child[pos], key, result, pos);
        }
    }
}

void DeleteTree(BNode* node){
    if(!node){
        return;
    }

    if(!node->is_leaf){
        for(int i = 0; i < 2 * T + 1; ++i){
            if(node->child[i]){
                DeleteTree(node->child[i]);
                node->child[i] = nullptr;
            }
        }
    }
    delete node;
}

void BTree::Insert(map &element){
    BNode* result;
    int pos;
    SearchNode(root, element.key, result, pos);
    if(result){ //проверка, есть ли нода в дереве
        std::cout << "Exist" << "\n";
        return;
    }
    //если корень насыщенный, нужно его разделить
    if(root->countKeys == 2 * T - 1){
        BNode* new_root = new BNode;
        new_root->is_leaf = false;
        new_root->child[0] = root;
        root = new_root;
        SplitChild(root, 0);
    }
    InsertNonfull(root, element);
    std::cout << "OK" << "\n";
}

void BTree::Delete(char* key){
    BNode* result;
    int res_pos;
    SearchNode(root, key, result, res_pos);
    if(!result){
        std::cout << "NoSuchWord" << "\n";
    } else{
        DeleteNode(root, key);
        std::cout << "OK" << "\n";
        //если корень пустой, то ребено должен стать новым корнем
        if (root->countKeys == 0 && !root->is_leaf) {
            BNode* node = root->child[0];
            delete root;
            root = node;
        }
    }
}

void DeleteNode(BNode* node, char* key){
    //смотрим, в текущем ли узле наша нода
    int pos = SearchInCurrentNode(node, key);
    
    // str в текущей листовой ноде
    if(pos >= 0 && node->is_leaf){
        DeleteFromCurrentNode(node, pos);
        return;
    }

    //str в текущей нелистовой ноде
    if(pos >= 0 && !node->is_leaf){
        BNode* left_child = node->child[pos];

        //левый сын достаточно большой - берем самый большой ключ левого поддерева
        if(left_child->countKeys >= T){
            while(!left_child->is_leaf){
                left_child = left_child->child[left_child->countKeys];
            }

            //вставляем найденный ключ в позицию, которую хотим удалить
            node->keys[pos] = left_child->keys[left_child->countKeys - 1];

            //удаляем самый большой ключ в левом поддереве
            char* new_str = new char[strlen(left_child->keys[left_child->countKeys - 1].key) + 1];
            strcpy(new_str, left_child->keys[left_child->countKeys - 1].key);
            DeleteNode(node->child[pos], new_str);
            delete[] new_str;
            return;
        }

        BNode* right_child = node->child[pos + 1];
        //левый сын достаточно большой - берем минимальный ключ левого поддерева
        if(right_child->countKeys >= T){
            while(!right_child->is_leaf){
                right_child = right_child->child[0];
            }

            //вставляем найденный ключ в позицию, которую хотим удалить
            node->keys[pos] = right_child->keys[0];

            //удаляем минимальный ключ из правого поддерева
            char* new_str = new char[strlen(right_child->keys[0].key) + 1];
            strcpy(new_str, right_child->keys[0].key);
            DeleteNode(node->child[pos + 1], new_str);
            delete[] new_str;
            return;
        }

        //оба ребенка имеют t-1 ключей => объединяем их
        Merge(node, pos);
        DeleteNode(node->child[pos], key);
        return;
    }
    
    pos = -pos - 1;
    // нет ключа в текущей ноде
    if(node->child[pos]->countKeys == T - 1){
        Rebalance(node, pos);
    }
    DeleteNode(node->child[pos], key);
}

//ребалансим дерево, если размер ноды t - 1
void Rebalance(BNode* node, int& pos){
    BNode* child = node->child[pos];

    if(pos - 1 >= 0 && node->child[pos - 1]->countKeys >= T){
        //левый племянник имеет оптимальный размер
        BNode* left_neighbour = node->child[pos - 1];

        //смещение ребенка вправо
        for(int i = child->countKeys - 1; i >= 0; --i){
            child->keys[i + 1] = child->keys[i];
        }

        if(!child->is_leaf){
            for(int i = child->countKeys; i >= 0; --i){
                child->child[i + 1] = child->child[i];
                child->child[i] = nullptr;
            }
        }

        // ключ переходит к ребенку
        child->keys[0] = node->keys[pos - 1];
        child->child[0] = left_neighbour->child[left_neighbour->countKeys];
        left_neighbour->child[left_neighbour->countKeys] = nullptr;
        ++child->countKeys;

        // последний ключ левого племянника переходит к родителю
        node->keys[pos - 1] = left_neighbour->keys[left_neighbour->countKeys - 1];

        --left_neighbour->countKeys;
    } else if (pos + 1 <= node->countKeys && node->child[pos + 1]->countKeys >= T) {
        // правый племянник имеет оптимальный размер
        BNode *right_neighbour = node->child[pos + 1];

        // ключ переходит к ребенку
        child->keys[child->countKeys] = node->keys[pos];
        child->child[child->countKeys + 1] = right_neighbour->child[0];
        right_neighbour->child[0] = nullptr;
        ++child->countKeys;

        // первый ключ правого племянника переходит к родителю
        node->keys[pos] = right_neighbour->keys[0];
        DeleteFromCurrentNode(right_neighbour, 0);

    } else if (pos - 1 >= 0 && node->child[pos - 1]->countKeys == T - 1) {
        // у левого племянника t - 1 => мерджим
        Merge(node, pos - 1);
        --pos;
    }
    else if (pos + 1 <= node->countKeys && node->child[pos + 1]->countKeys == T - 1) {
        // у правого племянника t - 1 => мерджим
        Merge(node, pos);
    }
}

//мерджим left_child, right_child и parent[pos]
void Merge(BNode* parent, int pos){
    BNode *left_child = parent->child[pos];
    BNode *right_child = parent->child[pos + 1];

    //копируем parent[pos] и right child keys в левого left_child
    left_child->keys[left_child->countKeys++] = parent->keys[pos];
    for(int i = 0; i < right_child->countKeys; ++i){
        left_child->keys[left_child->countKeys++] = right_child->keys[i];
    }

    //копируем детей правого ребенка, если они есть
    if(!right_child->is_leaf){
        for(int i = 0; i <= right_child->countKeys; ++i){
            left_child->child[T + i] = right_child->child[i];
            right_child->child[i] = nullptr;
        }
    }

    right_child->countKeys = 0;
    delete right_child;
    DeleteFromCurrentNode(parent, pos);
    parent->child[pos] = left_child;
}

void DeleteFromCurrentNode(BNode* node, int pos){
    for (int i = pos; i < node->countKeys - 1; ++i) {
        node->keys[i] = node->keys[i + 1];
    }
    if (!node->is_leaf) {
        for (int i = pos; i < node->countKeys; ++i) {
            node->child[i] = node->child[i + 1];
            node->child[i + 1] = nullptr;
        }
    }
    --node->countKeys;
}

int SearchInCurrentNode(BNode* node, char* key) {
    int left = -1;
    int right = node->countKeys;
    int middle = 0;
    while (right - left > 1) {
        middle = (left + right) / 2;
        if (node->keys[middle] < key) {
            left = middle;
        }
        else {
            right = middle;
        }
    }

    if (right < node->countKeys && node->keys[right] == key) { //нашли ключ
        return right;
    }

    // -i - 1 означает, что элемент находится в этом ребенке
    return -right - 1;
}

void InsertNonfull(BNode* node, map& element){
    int i = node->countKeys - 1;

    if(node->is_leaf){
        while(i >= 0 && element < node->keys[i]){
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = element;
        ++node->countKeys;
    }
    else{
        while (i >= 0 && element < node->keys[i]){
            --i;
        }
        ++i;
        if(node->child[i]->countKeys == 2 * T - 1){
            SplitChild(node, i);
            if(node->keys[i] < element){
                ++i;
            }
        }
        InsertNonfull(node->child[i], element);
    }
}


void SplitChild(BNode* parent, int pos){
    BNode* child = parent->child[pos];
    BNode* new_child = new BNode;
    new_child->is_leaf = child->is_leaf;
    new_child->countKeys = T - 1;

    //копируем половину ключей в нового ребенка
    for(int i = 0; i < T - 1; ++i){
        new_child->keys[i] = child->keys[i + T];
    }
    //копируем половину детей в нового ребенка, если он не лист
    if(!child->is_leaf){
        for(int i = 0; i < T; ++i){
            new_child->child[i] = child->child[i + T];
            child->child[i + T] = nullptr;
        }
    }

    child->countKeys = T - 1;

    //добавляем нового ребенка в родителя
    for(int i = parent->countKeys; i >= pos + 1; --i){
        parent->child[i + 1] = parent->child[i];
        parent->child[i] = nullptr;
    }

    if (parent->child[pos + 1]) {
        DeleteTree(parent->child[pos + 1]);
    }
    parent->child[pos + 1] = new_child;

    //добавляем серединный элемент в родителя
    for (int i = parent->countKeys - 1; i >= pos; --i) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[pos] = child->keys[T - 1];
    ++parent->countKeys;
}

void BTree::Serialize(std::ofstream &file) {
    NodeToFile(root, file);
}

void NodeToFile(BNode* node, std::ofstream &file){
    file.write((char *)&node->is_leaf, sizeof(bool));
    file.write((char *)&node->countKeys, sizeof(int));
    for (int i = 0; i < node->countKeys; ++i){
        int len = strlen(node->keys[i].key);
        file.write((char *)&len, sizeof(int));
        file.write((char *)&node->keys[i].key, len*sizeof(char));
        file.write((char *)&node->keys[i].value, sizeof(unsigned long long));
    }
    if(!node->is_leaf){
        for(int i = 0; i < node->countKeys + 1; ++i){
            NodeToFile(node->child[i], file);
        }
    }
}

void BTree::Deserialize(std::ifstream &file){
    TreeFromFile(root, file);
    std::cout << "OK" << "\n";
}

void TreeFromFile(BNode* node, std::ifstream &file){
    file.read((char *)&node->is_leaf, sizeof(bool));
    file.read((char *)&node->countKeys, sizeof(int));
    for (int i = 0; i < node->countKeys; ++i) {
        int len;
        file.read((char *)&len, sizeof(int));
        file.read(node->keys[i].key, len*sizeof(char));
        node->keys[i].key[len] = '\0';
        file.read((char *)&node->keys[i].value, sizeof(unsigned long long));
    }
    if (node->is_leaf) {
        for (int i = 0; i < 2 * T + 1; ++i) {
            if (node->child[i] != nullptr) {
                DeleteTree(node->child[i]);
                node->child[i] = nullptr;
            }
        }
    }
    else {
        for (int i = 0; i < node->countKeys + 1; ++i) {
            if (node->child[i] == nullptr) {
                node->child[i] = new BNode;
            }
            TreeFromFile(node->child[i], file);
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    BTree tree;
    char command[257];
    std::ifstream in("test.txt");
    std::ofstream out("out.txt");
    char space;
    int flag = 0;
    int count = 1;
    unsigned int start_time;
    std::string s;
    while(getline(in, s)){
        std::istringstream ss(s);
        if(s[0] == '+'){
            map new_el;
            ss >> space >> new_el.key >> new_el.value;
            ToLower(new_el.key);
            tree.Insert(new_el);
        }
        else if(s[0] =='-'){
            ss >> space >> command;
            ToLower(command);
            tree.Delete(command);
        }
        else if(strcmp(command, "!") == 0){
            std::cin >> command;
            if(strcmp(command, "Save") == 0){
                std::cin >> command;
                // FILE* file = fopen(command, "wb");
                std::ofstream file(command, std::ios::binary | std::ios::trunc);
                tree.Serialize(file);
                // fclose(file);
                file.close();
            }
            else if(strcmp(command, "Load") == 0){
                std::cin >> command;
                std::ifstream file(command, std::ios::binary);
                // FILE* file = fopen(command, "rb");
                tree.Deserialize(file);
                // fclose(file);
                file.close();
            }
        }
        else{
            if(flag == 0){
                start_time = clock();
                flag = 1;
            }
            ss >> command;
            ToLower(command);
            tree.Search(command);
        }
    }
    unsigned int end_time = clock(); // конечное время
    int search_time = end_time - start_time; // искомое время
    std::cout << "Time: " << search_time << "ms" << "\n";
}

