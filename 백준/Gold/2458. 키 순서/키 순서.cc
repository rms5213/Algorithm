#include<iostream>

using namespace std;
 
#define INF 987654321
#define MAX 500+1

int main() {
    int N, M;
    int map[MAX][MAX];
 
    cin >> N >> M;
 
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            map[i][j] = INF;
        }
    }
 
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        map[a][b] = 1;
    }
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (map[i][j] > map[i][k] + map[k][j]) {
                    map[i][j] = map[i][k] + map[k][j];
                }
            }
        }
    }
 
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int cnt = 0;
        for (int j = 1; j <= N; j++) {
            if (map[i][j] != INF || map[j][i] != INF) { 
                cnt++;
            }
        }
        if (cnt == N - 1) ans++;
    }
    cout << ans << endl;
 
    return 0;
}