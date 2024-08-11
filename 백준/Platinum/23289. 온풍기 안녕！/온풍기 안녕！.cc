#include <iostream>
#include <string>
#include <cmath>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#define FIRST cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
#define MAX 25
#define LL long long
#define INF 1e9

using namespace std;
struct BLOWER {
	int Y, X, Dir;
};

int R, C, K, W;
int MAP[MAX][MAX]; // 방의 정보
int Wind_MAP[MAX][MAX]; // 바람의 상태
int Tmp_MAP[MAX][MAX]; // 바람의 변화를 담을 임시 배열
bool Wall[MAX][MAX][5]; // 벽의 유무, (i,j)의 k방향(동:1, 서:2, 북:3, 남:4)에 벽이 있으면 true, 없으면 false
vector<BLOWER> Blower; // 온풍기
vector<pair<int, int> > Investigate; // 조사할 곳
int moveY[5] = { 0,0,0,-1,1 };
int moveX[5] = { 0,1,-1,0,0 };
int answer = 0; // 먹은 초콜릿의 개수

void init() { // 임시 배열을 초기화시키는 함수
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			Tmp_MAP[i][j] = 0;
		}
	}
}

void Copy_Map() { // 바람의 가중치에 따라 바람의 상태가 변화함.
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			Wind_MAP[i][j] += Tmp_MAP[i][j];
		}
	}
}

void Make_Wind_East(int Depth, int Y, int X) {
	// 온풍기에서 바람이 동쪽으로 나올 때
	if (Depth == 0) { // 바람의 세기가 0이 되면 더 이상 바람이 퍼지지 않는다.
		return;
	}
	Tmp_MAP[Y][X] = Depth;
	int nextY = Y - 1;
	int nextX = X + 1;
	/*
		칸 (x, y)에서 (x-1, y+1)로 바람이 이동할 수 있으려면, 
		(x, y)와 (x-1, y) 사이에 벽이 없어야 하고, (x-1, y)와 (x-1, y+1) 사이에도 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][3]) && (!Wall[Y - 1][X][1])) {
		Make_Wind_East(Depth - 1, nextY, nextX);
	}
	nextY = Y;
	nextX = X + 1;
	/*
		(x, y)에서 (x, y+1)로 바람이 이동할 수 있으려면 (x, y)와 (x, y+1) 사이에 벽이 없어야 한다. 
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][1])) {
		Make_Wind_East(Depth - 1, nextY, nextX);
	}
	nextY = Y + 1;
	nextX = X + 1;
	/*
		(x, y)에서 (x+1, y+1)로 바람이 이동할 수 있으려면, (x, y)와 (x+1, y), (x+1, y)와 (x+1, y+1) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][4]) && (!Wall[Y + 1][X][1])) {
		Make_Wind_East(Depth - 1, nextY, nextX);
	}
}

void Make_Wind_West(int Depth, int Y, int X) {
	// 온풍기에서 바람이 서쪽으로 나올 때
	if (Depth == 0) {
		return;
	}
	Tmp_MAP[Y][X] = Depth;
	int nextY = Y - 1;
	int nextX = X - 1;
	/*
		칸 (x, y)에서 (x-1, y-1)로 바람이 이동할 수 있으려면,
		(x, y)와 (x-1, y) 사이에 벽이 없어야 하고, (x-1, y)와 (x-1, y-1) 사이에도 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][3]) && (!Wall[Y - 1][X][2])) {
		Make_Wind_West(Depth - 1, nextY, nextX);
	}
	nextY = Y;
	nextX = X - 1;
	/*
		(x, y)에서 (x, y-1)로 바람이 이동할 수 있으려면 (x, y)와 (x, y-1) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][2])) {
		Make_Wind_West(Depth - 1, nextY, nextX);
	}
	nextY = Y + 1;
	nextX = X - 1;
	/*
		(x, y)에서 (x+1, y-1)로 바람이 이동할 수 있으려면, (x, y)와 (x+1, y), (x+1, y)와 (x+1, y-1) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][4]) && (!Wall[Y + 1][X][2])) {
		Make_Wind_West(Depth - 1, nextY, nextX);
	}
}

void Make_Wind_North(int Depth, int Y, int X) {
	// 온풍기에서 바람이 북쪽으로 나올 때
	if (Depth == 0) {
		return;
	}
	Tmp_MAP[Y][X] = Depth;
	int nextY = Y - 1;
	int nextX = X - 1;
	/*
		칸 (x, y)에서 (x-1, y-1)로 바람이 이동할 수 있으려면,
		(x, y)와 (x, y-1) 사이에 벽이 없어야 하고, (x, y-1)와 (x-1, y-1) 사이에도 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][2]) && (!Wall[Y][X - 1][3])) {
		Make_Wind_North(Depth - 1, nextY, nextX);
	}
	nextY = Y - 1;
	nextX = X;
	/*
		(x, y)에서 (x-1, y)로 바람이 이동할 수 있으려면 (x, y)와 (x-1, y) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][3])) {
		Make_Wind_North(Depth - 1, nextY, nextX);
	}
	nextY = Y - 1;
	nextX = X + 1;
	/*
		(x, y)에서 (x-1, y+1)로 바람이 이동할 수 있으려면, (x, y)와 (x, y+1), (x, y+1)와 (x-1, y+1) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][1]) && (!Wall[Y][X + 1][3])) {
		Make_Wind_North(Depth - 1, nextY, nextX);
	}
}

void Make_Wind_South(int Depth, int Y, int X) {
	// 온풍기에서 바람이 남쪽으로 나올 때
	if (Depth == 0) {
		return;
	}
	Tmp_MAP[Y][X] = Depth;
	int nextY = Y + 1;
	int nextX = X - 1;
	/*
		칸 (x, y)에서 (x+1, y-1)로 바람이 이동할 수 있으려면,
		(x, y)와 (x, y-1) 사이에 벽이 없어야 하고, (x, y-1)와 (x+1, y-1) 사이에도 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][2]) && (!Wall[Y][X - 1][4])) {
		Make_Wind_South(Depth - 1, nextY, nextX);
	}
	nextY = Y + 1;
	nextX = X;
	/*
		(x, y)에서 (x+1, y)로 바람이 이동할 수 있으려면 (x, y)와 (x+1, y) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][4])) {
		Make_Wind_South(Depth - 1, nextY, nextX);
	}
	nextY = Y + 1;
	nextX = X + 1;
	/*
		(x, y)에서 (x+1, y+1)로 바람이 이동할 수 있으려면, (x, y)와 (x, y+1), (x, y+1)와 (x+1, y+1) 사이에 벽이 없어야 한다.
	*/
	if ((nextY >= 1) && (nextY <= R) && (nextX >= 1) && (nextX <= C) && (Tmp_MAP[nextY][nextX] == 0) && (!Wall[Y][X][1]) && (!Wall[Y][X + 1][4])) {
		Make_Wind_South(Depth - 1, nextY, nextX);
	}
}

void Blow_Wind() {
	// 1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
	for (int i = 0; i < Blower.size(); i++) {
		init();
		int Y = Blower[i].Y;
		int X = Blower[i].X;
		int Dir = Blower[i].Dir;
		int nextY = Y + moveY[Dir];
		int nextX = X + moveX[Dir];
		// 방향에 따라 바람이 퍼지는 방향이 다르다.
		if (Dir == 1) {
			Make_Wind_East(5, nextY, nextX);
		}
		else if (Dir == 2) {
			Make_Wind_West(5, nextY, nextX);
		}
		else if (Dir == 3) {
			Make_Wind_North(5, nextY, nextX);
		}
		else if (Dir == 4) {
			Make_Wind_South(5, nextY, nextX);
		}
		Copy_Map();
	}
}

void Temperature_Control() {
	// 2. 온도가 조절됨
	init();
	// 하나의 행에서 1~C열까지 모두 탐색하고, 이것을 R번 반복하기 때문에 서, 북쪽 칸과의 온도 조절은 할 필요가 없다.
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int CurT = Wind_MAP[i][j];
			for (int k = 1; k <= 4; k++) {
				bool Flag = false;
				if ((i + moveY[k] >= 1) && (i + moveY[k] <= R) && (j + moveX[k] >= 1) && (j + moveX[k] <= C)) {
					if (k == 1) {
						Flag = (!Wall[i][j][1] ? true : false); // 칸 (i,j)에서 동쪽에 벽이 있으면 바람이 퍼지지 않는다.
					}
					else if (k == 4) {
						Flag = (!Wall[i][j][4] ? true : false); // 칸 (i,j)에서 북쪽에 벽이 있으면 바람이 퍼지지 않는다.
					}
				}
				if (!Flag) {
					continue;
				}
				int nextT = Wind_MAP[i + moveY[k]][j + moveX[k]];
				int SubT = abs(CurT - nextT);
				SubT /= 4; // 온도가 높은 칸에서 낮은 칸으로 ⌊(두 칸의 온도의 차이) / 4⌋만큼 온도가 조절된다.
				if (CurT > nextT) {
					Tmp_MAP[i][j] -= SubT;
					Tmp_MAP[i + moveY[k]][j + moveX[k]] += SubT; // 온도의 "변화량"을 임시 배열에 담아서 나중에 한꺼번에 처리한다.
				}
				else if (CurT < nextT) {
					Tmp_MAP[i][j] += SubT;
					Tmp_MAP[i + moveY[k]][j + moveX[k]] -= SubT;
				}
			}
		}
	}
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			// 한꺼번에 처리하는 이유는 모든 칸에 대해서 동시에 발생한다고 하였기 때문이다.
			Wind_MAP[i][j] += Tmp_MAP[i][j];
		}
	}
}

void Decrease_Temperature() {
	// 3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
	// 바깥쪽 칸에 있는 온도가 1 이상인 모든 칸의 온도가 1씩 감소한다.
	for (int i = 1; i <= C; i++) {
		if (Wind_MAP[1][i] > 0) {
			Wind_MAP[1][i]--;
		}
	}
	for (int i = 1; i <= C; i++) {
		if (Wind_MAP[R][i] > 0) {
			Wind_MAP[R][i]--;
		}
	}
	for (int i = 2; i < R; i++) {
		if (Wind_MAP[i][1] > 0) {
			Wind_MAP[i][1]--;
		}
	}
	for (int i = 2; i < R; i++) {
		if (Wind_MAP[i][C] > 0) {
			Wind_MAP[i][C]--;
		}
	}
}

void Eat_Chocolate() {
	// 4. 초콜릿을 하나 먹는다.
	answer++; // 초콜릿을 먹는다.
}

bool Check_MAP() {
	// 5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
	bool Flag = true;
	for (int i = 0; i < Investigate.size(); i++) {
		int Y = Investigate[i].first;
		int X = Investigate[i].second;
		if (Wind_MAP[Y][X] < K) {
			// 하나라도 조사할 칸의 온도가 K에 미치치 못 한다면 테스트는 끝나지 않는다.
			return false;
		}
	}
	return true;
}

void Ability_Test() {
	while (1) {
		Blow_Wind();
		Temperature_Control();
		Decrease_Temperature();
		Eat_Chocolate();
		if (answer > 100) {
			// 초콜릿을 100개 넘게 먹으면, 어차피 101로 출력할 것이므로 테스트를 중단한다.
			answer = 101;
			break;
		}
		bool Flag = Check_MAP();
		if (Flag) {
			break;
		}
	};
}

int main() {
	FIRST
	cin >> R >> C >> K;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> MAP[i][j];
			if ((MAP[i][j] >= 1) && (MAP[i][j] <= 4)) {
				Blower.push_back({ i,j,MAP[i][j] });
			}
			else if (MAP[i][j] == 5) {
				Investigate.push_back(make_pair(i, j));
			}
		}
	}
	cin >> W;
	for (int i = 0; i < W; i++) {
		int Y, X, T;
		cin >> Y >> X >> T;
		if (T == 0) {
			Wall[Y][X][3] = true;
			Wall[Y - 1][X][4] = true;
		}
		else if (T == 1) {
			Wall[Y][X][1] = true;
			Wall[Y][X + 1][2] = true;
		}
	}
	Ability_Test();
	cout << answer << "\n";

	return 0;
}