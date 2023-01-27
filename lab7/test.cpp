#include <iostream>
#define MAX 10010
#include <vector>

int main(){
    int s, n;
    std::cin >> s >> n;

    std::vector<int> m(s+1);

    m[0] = 1;
    int w;
    for(int i = 0; i < n; ++i){
        std::cin >> w;
        for(int j = s; j >= w; j--)

            if (m[j - w] == 1) m[j] = 1;

    }
    int ans;
    for(int i = s;; i--)
    if (m[i] > 0) {
        ans = i;
        break;
    }
    std::cout << ans << '\n';
}