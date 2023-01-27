#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

typedef long long ll;

const int MAX_NUM = 3;

ll NextPosition(int num, ll cur_pos, std::vector<int> &nums,
    bool rev_order = false){
        if (nums.empty() || cur_pos < 0 || cur_pos >= nums.size()){
            return 0;
        }
        if(!rev_order){
            while(nums[cur_pos] != num && cur_pos + 1 < nums.size()){
                ++cur_pos;
            }
        } 
        else{
            while(nums[cur_pos] != num && cur_pos - 1 >= 0){
                --cur_pos;
            }
        }
        return cur_pos;
    }

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // std::ifstream fin("test.txt"); // открыли файл для чтения
    // unsigned int start_time =  clock(); // начальное время
    // fin >> n; // считали первое слово из файла
    ll n;
    std::cin >> n;
    std::vector<int> nums(n);
    std::vector<ll> count(MAX_NUM);

    for(ll i = 0; i < n; ++i){
        std::cin >> nums[i];
        ++count[nums[i] - 1];
    }

    ll swap = 0;

    ll pos3_1 = NextPosition(1, n - 1, nums, true);
    ll pos3_2 = NextPosition(2, count[0] + count[1], nums);
    ll pos2_1 = NextPosition(1, count[0], nums);
    for(int i = 0; i < n; ++i){
        if(count[0] <= i && i < count[0] + count[1] && nums[i] != 2){
            std::swap(nums[i], nums[pos3_2]);
            ++swap;
            pos3_2 = NextPosition(2, pos3_2, nums);
        }

        else if(i < count[0] && nums[i] != 1){
            if(nums[i] == 2){
                std::swap(nums[i], nums[pos2_1]);
                ++swap;
                pos2_1 = NextPosition(1, pos2_1, nums);
            }
            else{
                std::swap(nums[i], nums[pos3_1]);
                ++swap;
                pos3_1 = NextPosition(1, pos3_1, nums, true);
            }
        }
    }
    // unsigned int end_time = clock(); // конечное время
    // unsigned int search_time = end_time - start_time; // искомое время
    // std::cout << search_time << "\n";
    std::cout << swap << "\n";
    return 0;
}