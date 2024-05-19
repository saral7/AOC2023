#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<string> &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		v.push_back(line);
	}
	file.close();
}

bool isEmpty (string &v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == '#') return false;
	}
	return true;
}

void solve (vector<string> &v) {
	int n = v.size();
	int m = v[0].size();
	int *prefRow = new int[n];
	int *prefCol = new int[m];
	lli C = 1e6;
	memset (prefRow, 0, sizeof(prefRow));
	memset (prefCol, 0, sizeof(prefCol));
	vector<pair<int, int> >pos;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == '#') pos.push_back({i, j});
		}
	}
	string pom = "";
	for (int i = 0; i < v.size(); i++) {
		pom = v[i];
		prefRow[i] = isEmpty(pom);
		if (i != 0) prefRow[i] += prefRow[i-1]; 
	}
	
	for (int j = 0; j < v[0].size(); j++) {
		pom = "";
		for (int i = 0; i < v.size(); i++) {
			pom += v[i][j];
		}
		prefCol[j] = isEmpty(pom);
		if (j != 0) prefCol[j] += prefCol[j-1];
	}
	
	lli sol = 0;
	for (int i = 0; i < pos.size(); i++) {
		for (int j = i+1; j < pos.size(); j++) {
			lli val = abs(pos[i].first-pos[j].first)+abs(pos[i].second-pos[j].second);
			val += (prefRow[max(pos[i].first, pos[j].first)]-prefRow[min(pos[i].first, pos[j].first)])*(C-1);
			val += (prefCol[max(pos[i].second, pos[j].second)]-prefCol[min(pos[i].second, pos[j].second)])*(C-1);
			sol += val;
		}
	}
	cout << sol << endl;
	delete [] prefRow;
	delete [] prefCol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	vector<string>v;
    read("input.txt", v);
	solve(v);

return 0;
}

