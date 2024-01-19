#include <bits/stdc++.h>

using namespace std;
#define MAX 2000+1
int main(){
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    
    int N;
    cin >> N;
    
    int A[MAX];
    
    for(int i = 0 ; i < N ; i++) cin >> A[i];

    sort(A, A+N);
    
    int sum = 0;
    int cnt = 0;
    int res = 0;
    int visited[MAX]={0,};
    int start, end;
    for(int i = 0 ; i < N ; i++){
        res = A[i];
        start = 0;
        end = N - 1;
        while(start < end){ 
            sum = A[start] + A[end];
            if(sum == res){
                
            if(start != i && end != i){
                cnt++;
                break;
            }
            else if(start == i) start++;
            else if(end == i) end--;
            }
            else if(sum < res) start++;
            else end--;
        }
    }
    cout << cnt << "\n";

}