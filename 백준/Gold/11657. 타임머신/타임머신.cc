#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

typedef long long LL;
#define MAX 500 + 1
#define INF 0x3f3f3f3f
int N, M;

vector<pair<int, pair<int, int>>> edges;

LL dist[MAX];


void bellmanFord(int start){
    dist[start] = 0;
    bool flag = true;
    for(int i = 1 ; i <= N ; i++){
        for(int j = 0 ; j < M ; j++){
            int from = edges[j].first;
            int to = edges[j].second.first;
            int cost = edges[j].second.second;
            
            if(dist[from] == INF) continue;
            if(dist[to] > dist[from] + cost){
                dist[to] = dist[from] + cost;
                if(i == N) {
                    cout << "-1\n";
                    flag = false;
                    // break;
                    return;
                }
            }
        }
        // if(!flag) break;
    }
    if(flag){
        for(int i = 2 ; i <= N ; i++){
            if(dist[i] == INF) {
                cout << "-1\n";
            }
            else cout << dist[i] << "\n";
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N >> M;

    for(int i = 0 ; i < M ; i++){
        int A, B, C;
        cin >> A >> B >> C;
        edges.push_back({A, {B, C}});
    }
    for(int i = 2 ; i <= N ; i++) dist[i] = INF;
    
    bellmanFord(1);

    return 0;
}