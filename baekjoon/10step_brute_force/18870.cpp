#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int N;
    scanf("%d", &N);

    vector<int> v;
    vector<int> uv;
    
    for(int i = 0; i < N; i++) {
        int temp;
        scanf("%d", &temp);
        v.push_back(temp);
        uv.push_back(temp);
    }

    
    sort(uv.begin(), uv.end());
    uv.erase( unique(uv.begin(), uv.end()), uv.end() );

    
    for(int i = 0; i < N; i++) {
        printf("%ld ", lower_bound(uv.begin(), uv.end(), v[i]) - uv.begin());
    }
    
    return 0;
}