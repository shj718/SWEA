#include <iostream>
#include <queue>
#include <string>
#define MAX 101
typedef long long lld;
const lld INF = 1e18;

using namespace std;

int arr[MAX][MAX];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
lld dist[MAX * MAX];

struct edge {
	int x;
	int y;
	lld cost;

	bool operator<(const edge& b) const {
		return cost > b.cost;
	}
};

int getNodeNum(int v, int x, int y) {
	return (x + 1) * v - (v - 1 - y);
}

void dijk(int v) {
	// dist 초기화
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			dist[getNodeNum(v, i, j)] = INF;
		}
	}
	priority_queue<edge> pq;
	// 시작점 삽입, dist 설정
	pq.push({ 0,0,0 });
	dist[1] = 0;
	while (!pq.empty()) {
		edge front = pq.top();
		pq.pop();
		int nowNodeX = front.x;
		int nowNodeY = front.y;
		lld nowCost = front.cost;

		if (dist[getNodeNum(v, nowNodeX, nowNodeY)] < nowCost) {
			continue;
		}
		// 최단거리 계산
		for (int i = 0; i < 4; i++) {
			int nextNodeX = nowNodeX + dx[i];
			int nextNodeY = nowNodeY + dy[i];
			// 범위 체크
			if (nextNodeX < 0 || nextNodeX >= v || nextNodeY < 0 || nextNodeY >= v) continue;

			if (dist[getNodeNum(v, nextNodeX, nextNodeY)] > dist[getNodeNum(v, nowNodeX, nowNodeY)] + arr[nextNodeX][nextNodeY]) {
				dist[getNodeNum(v, nextNodeX, nextNodeY)] = dist[getNodeNum(v, nowNodeX, nowNodeY)] + arr[nextNodeX][nextNodeY];
				pq.push({ nextNodeX, nextNodeY, dist[getNodeNum(v, nextNodeX, nextNodeY)] });
			}
		}
	}
}

int main() {
	int T, N;
	string s;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> s;
			for (int j = 0; j < N; j++) {
				arr[i][j] = s[j] - '0';
			}
		}
		dijk(N);
		cout << '#' << tc << ' ' << dist[getNodeNum(N, N - 1, N - 1)] << '\n';
	}
	return 0;
}
