#include <bits/stdc++.h>

using namespace std;
#define lli long long int

void read (string name, vector<string>&v, pair<int, int>&pos) {
	fstream file;
	file.open(name, ios::in);
	string line;
	int i = 0;
	while (getline(file, line)) {
		v.push_back(line);
		for (int j = 0; j < line.size(); j++) {
			if (line[j] == 'S') {
				pos = {i, j};
			}
		}
		i++;
	}
	file.close();
}

const int N = 307;
int been[2][N][N];

void solve (vector<string>&v, pair<int, int>&pos) {
	queue<pair<pair<int, int>, int> >q;
	q.push({pos, 0});
	been[0][pos.first][pos.second] = 1;
	int dx[] = {-1, 0, 0, 1};
	int dy[] = {0, -1, 1, 0};
	int sol = 0;
	cout << v.size() << " " << v[0].size() << endl;
	while (q.size()) {
		pair<int, int>node = q.front().first;
		int state = q.front().second;
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int susx = node.first+dx[i];
			int susy = node.second+dy[i];
			if (0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size()) {
				if (been[1-state][susx][susy] || v[susx][susy] == '#') continue;
				been[1-state][susx][susy] = been[state][node.first][node.second]+1;
				q.push({{susx, susy}, 1-state});
			}
		}
	}
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[0].size(); j++) {
			if (been[0][i][j] && been[1][i][j] <= 66) sol++;
		}
	}
	cout << sol << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>v;
    pair<int, int>pos;
    read ("input.txt", v, pos);
	solve(v, pos);

return 0;
}

