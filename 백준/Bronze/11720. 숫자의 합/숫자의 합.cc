#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;



int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);    
    int N; 
    string num;
    cin >> N;
    cin >> num;
    int sum = 0;
    int i = N;
    while(i){
        sum+= num[i - 1] - '0';
        i--;
    }
    cout << sum << endl;
    
    


}