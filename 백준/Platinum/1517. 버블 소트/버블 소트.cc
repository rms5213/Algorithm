#include <bits/stdc++.h> 
using namespace std;
#define MAX 500000 + 1

long long sorted[MAX];

vector<long long> arr;

long long ans = 0;

void merge(int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			sorted[k] = arr[i];
			i++;
		}
		else {
			sorted[k] = arr[j];
			ans += j - k;
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (int x = j; x <= right; x++) {
			sorted[k] = arr[x];
			k++;
		}
	}
	else {
		for (int x = i; x <= mid; x++) {
			sorted[k] = arr[x];
			k++;
		}
	}
	for (int x = left; x <= right; x++) {
		arr[x] = sorted[x];
	}
}

void msort(int left, int right) {
	if (left >= right) return;
	int mid = (left + right) >> 1;
	msort(left, mid);
	msort(mid + 1, right);
	merge(left, mid, right);
}

int main(void){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		arr.push_back(k);
	}
	msort(0, n - 1);
	cout << ans;
	return 0;
}