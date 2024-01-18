#include <iostream>
using namespace std;

#define MAX 100000 + 1

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);    

    int N, M;
    cin >> N >> M;

    int num, prefix[MAX];

    int val = 0;
    for (int i = 0; i < N; i++) {
        cin >> num;
        val += num;
        prefix[i + 1] = val;
    }
    int result[MAX];
    for (int i = 0; i < M; i++) {
        int start, end;
        cin >> start >> end;
        result[i] = prefix[end] - prefix[start - 1];
    }
    for (int i = 0; i < M; i++) {
        cout << result[i] << '\n';
    }

}
