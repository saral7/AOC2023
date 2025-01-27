#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
void read (string name, vector<string> &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		line += ".";
		v.push_back(line);
	}
	file.close();
	return;
}

bool check (const vector<string> &v, int i, int j, vector<pair<int, int> > &s) {
	int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	
	for (int k = 0; k < 8; k++) {
		int x = i+dx[k];
		int y = j+dy[k];
		
		if (x < 0 || x >= v.size() || y < 0 || y >= v[i].size()) continue;
		
		if (v[x][y] == '*') s.push_back({x, y});
		if (v[x][y] != '.' && (v[x][y] < '0' || v[x][y] > '9')) return true;
	}
	return false;
}


void solve (vector<string> &v) {
	int sol = 0;
	vector<int> arr[v.size()][v[0].size()];
	vector<pair<int, int> >stars;
	for (int i = 0; i < v.size(); i++) {
		string curr = v[i];
		int val = 0;
		bool good = false;
		stars.clear();
		for (int j = 0; j < curr.size(); j++) {
			if ('0' <= curr[j] && curr[j] <= '9') {
				val = val*10+curr[j]-'0';
				if (!good) good = check(v, i, j, stars);
				continue;
			}
			
			if (good) {
				for (int k = 0; k < stars.size(); k++) {
					arr[stars[k].first][stars[k].second].push_back(val);
				}
			}
		
			stars.clear();
			good = false;
			val = 0;
		}
	}
	
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == '*' && arr[i][j].size() == 2) {
				//cout << "(" << i << ", " << j << ")\n";
				int val = 1;
				for (int k = 0; k < arr[i][j].size(); k++) {
					//cout << arr[i][j][k] << "\n";
					val *= arr[i][j][k];
				} 
				sol += val;
			}
		}
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>v;
    read("input.txt", v);
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
	solve(v);

return 0;
}

