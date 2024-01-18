#include <iostream>
using namespace std;
#define MAX 1000 + 1


int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);    

    int N;
    cin >> N;
    int score[MAX];
    int sum = 0;
    int max = 0;
    for(int i = 0 ; i < N ; i++) {
        cin >> score[i];
        sum+=score[i];
        if(max < score[i]) max = score[i];
    }
    
    double res = (double)sum*100/max/N;
    cout << res << endl;


}