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
int cnt[2][20];

void count (vector<string> &v) {
	int n = v.size();
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[0].size(); j++) {
			int area;
			if (i+j <= n/2) {
				area = 0;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (i+j >= n/2) {
				area = 4;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (j-i >= n/2) {
				area = 1;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (j-i <= n/2) {
				area = 5;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (i-j >= n/2) {
				area = 2;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (i-j <= n/2) {
				area = 6;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (i+j >= 3*(n/2)) {
				area = 3;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (i+j <= 3*(n/2)) {
				area = 7;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			if (i+j > n/2 && i+j < 3*(n/2) && j-i < n/2 && i-j < n/2) {
				area = 10;
				cnt[0][area] += been[0][i][j];
				cnt[1][area] += been[1][i][j];
			}
			cnt[0][9] += been[0][i][j];
			cnt[1][9] += been[1][i][j];
			
			if (i+j == n/2 || i+j == 3*(n/2) || abs(i-j) == n/2) {
				cnt[0][12] += been[0][i][j];
				cnt[1][12] += been[1][i][j];
			}
		}
	}
	return;
}


void solve (vector<string>&v, pair<int, int>&pos) {
	queue<pair<pair<int, int>, int> >q;
	q.push({pos, 0});
	been[0][pos.first][pos.second] = 1;
	int dx[] = {-1, 0, 0, 1};
	int dy[] = {0, -1, 1, 0};
	int n = v.size();
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
			if (been[0][i][j]) been[0][i][j] = 1;
			if (been[1][i][j]) been[1][i][j] = 1;
		}
	}
	/*
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[0].size(); j++) {
			cout << been[0][i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[0].size(); j++) {
			cout << been[1][i][j];
		}
		cout << endl;
	}
	cout << endl;*/
	count(v);
	int odd = 0, even = 0;
	lli sol = (lli)cnt[1][9], h = 0;
	int c = 202300;
	for (int i = 1; i < c; i++) {
		if (i%2) {
			sol += (lli)(4*i)*cnt[0][9];
		}
		else {
			sol += (lli)(4*i)*cnt[1][9];
		}
	}
	for (int i = 0; i <= 12; i++) {
		cout << i << ": " << cnt[0][i] << " " << cnt[1][i] << endl;
	}
	sol += (lli)(c)*(cnt[0][0]+cnt[0][1]+cnt[0][2]+cnt[0][3]);
	sol += (lli)(2)*(cnt[1][0]+cnt[1][1]+cnt[1][2]+cnt[1][3]);
	sol += (lli)(c-1)*(cnt[1][4]+cnt[1][5]+cnt[1][6]+cnt[1][7]);
	sol += (lli)4*cnt[1][10];
	sol += (lli)2*cnt[1][12];
	sol -= 4*(been[1][0][n/2]+been[1][n][n/2]+been[1][n/2][0]+been[1][n/2][n]);
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

