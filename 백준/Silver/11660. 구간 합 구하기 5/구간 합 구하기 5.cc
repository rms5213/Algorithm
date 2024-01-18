#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 1024 + 1

int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);    

    int N, M;
    int x1, y1, x2, y2;
    cin >> N >> M;
    int prefix[MAX][MAX];
    int val1, val2;
    int sum1 = 0, sum2[MAX];
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            cin >> val1;
            sum1+=val1;
            prefix[i+1][j+1] = sum1 + prefix[i][j+1];
        }
        sum1=0;
    }
    
    int res[100000];

    for(int i = 0 ; i < M ; i++){
            cin >> x1 >> y1 >> x2 >> y2;
            res[i] = prefix[x2][y2] - prefix[x2][y1-1] - prefix[x1-1][y2] + prefix[x1-1][y1-1];
    }
    for(int i = 0 ; i < M ; i++){
        cout << res[i] << '\n';            
    }

    
}