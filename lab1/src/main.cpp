#include <iostream>
#include <vector>

using namespace std;

struct Map {
    uint64_t key;
    string value;
};

void InsertionSort(vector<Map*>& buckets){
    for(int16_t i = 1; i < buckets.size(); i++){
        for(int16_t j = i; j > 0; --j){
            if (buckets[j - 1]->key > buckets[j]->key) {
                swap(buckets[j - 1], buckets[j]);
            }
        }
    }
}

void BucketSort(vector<Map*>& inputed){
    uint64_t maxElemen = inputed[0]->key;
    uint64_t minElemen = inputed[0]->key;
    for(const auto &item: inputed){
        if (item->key > maxElemen) maxElemen = item->key;
        if (item->key < minElemen) minElemen = item->key;
    }
    const long double interval = (maxElemen - minElemen) / inputed.size();
    vector<vector<Map*>> buckets(inputed.size());
    for(int i = 0; i < inputed.size(); ++i){
        uint64_t elem = (inputed[i]->key - minElemen) / interval;
        if(elem == inputed.size())
            elem--;
        buckets[elem].push_back(inputed[i]);
    }
    for(int i = 0; i < buckets.size(); ++i){
        InsertionSort(buckets[i]);
    }
    int pos = 0;
    for(int i = 0; i < buckets.size(); ++i){
        for(int j = 0; j < buckets[i].size(); ++j){
            inputed[pos++] = buckets[i][j];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    uint64_t key;
    vector<Map*> inputed;
    while(cin >> key >> str){
        Map* data = new Map();
        data->key = key;
        data->value = str;
        inputed.emplace_back(data);
    }
    if(inputed.size() != 0){
        BucketSort(inputed);
    }
    for(const auto &item: inputed){
        cout << item->key << '\t' << item->value << "\n";
    }
    for (int i = 0; i < inputed.size(); ++i) {
        delete inputed[i];
    }
    return 0;
}
