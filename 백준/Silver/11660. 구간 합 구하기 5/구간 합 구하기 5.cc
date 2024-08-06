#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 1024 + 10
int arr[MAX][MAX];
int dp[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M;
    cin >> N >> M;
    
    
    
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= N ; j++){
            cin >> arr[i][j];
        }
    }
    

    dp[1][1] = arr[1][1];
    
    for(int i = 2 ; i <= N ; i++) {
        dp[1][i] = dp[1][i-1] + arr[1][i];
        dp[i][1] = dp[i-1][1] + arr[i][1];
    }
    
    for(int i = 2 ; i <= N ; i++){
        for(int j = 2 ; j <= N ; j++){
            dp[i][j] = arr[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
        }
    }
    
    for(int i = 0 ; i < M ; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        cout << dp[x2][y2] - dp[x2][y1-1] - dp[x1-1][y2] + dp[x1-1][y1-1] << "\n";
    }
    
    
    return 0;
}