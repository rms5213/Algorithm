#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 500 + 10
int arr[MAX][MAX];
int dp[MAX][MAX];

int main() {
    int N;
    cin >> N;
    
    
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= i ; j++){
            int num;
            cin >> num;
            arr[i][j] = num;
        }
    }
    
    
    dp[1][1] = arr[1][1]; 
    
    for(int i = 2 ; i <= N ; i++){
        for(int j = 1 ; j <= i ; j++){
            dp[i][j] = arr[i][j] + max(dp[i-1][j-1], dp[i-1][j]);
        }
    }
    
    int res = -1;
    for(int i = 1 ; i <= N ; i++) res = max(res, dp[N][i]);
    
    cout << res;
    
    return 0;
}