#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;

void read (string name, vector<string>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	vector<string>pom;
	while (getline(file, line)) {
		v.push_back(line);
	}
	file.close();

}


void tilt (vector<string>&v) {
	int cnt = 0;
	for (int j = 0; j < v[0].size(); j++) {
		cnt = 0;
		for (int i = v.size()-1; i >= -1; i-=1) {
			if (i == -1 || v[i][j] == '#') {
				for (int k = i+1; k < i+1+cnt; k++) {
					v[k][j] = 'O';
				}
				cnt = 0;
				continue;
			} 
			if (v[i][j] == 'O') {
				cnt++;
				v[i][j] = '.';
			}
		}
	}
}

bool isEqual (vector<string>&v, vector<string>&og) {
	if (v.size() != og.size()) return false;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] != og[i]) return false;
	}
	return true;
}

void rotate90 (vector<string> &v) {
	vector<string>pom;
	string s = "";
	for (int j = 0; j < v[0].size(); j++) {
		for (int i = v.size()-1; i >= 0; i-=1) {
			s += v[i][j];
		}
		pom.push_back(s);
		s = "";
	}
	v.clear();
	for (int i = 0; i < pom.size(); i++) v.push_back(pom[i]);
}

void cycle (vector<string> &v) {
	for (int i = 0; i < 4; i++) {
		tilt(v);
		rotate90(v);
	}
}

void print (vector<string>&v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	cout << endl;
}

map<vector<string>, int>m;

int calc (vector<string>&v) {
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == 'O') {
				sol += v.size()-i;
			}
		}
	}
	return sol;
}

void solve (vector<string>&v) {
	int sol = 0;
	int cnt = 0;
	
	vector<string>pom;
	for (int i = 0; i < v.size(); i++) pom.push_back(v[i]);
	
	m[pom] = 1;
	int c = 300, big = 1e9;
	int cycleLen = -1, start = -1;
	for (int i = 2; i < c; i++) {
		cycle(pom);
		if (m[pom]) {
			//cout << m[pom] << " " << i << endl;
			cycleLen = i-m[pom];
			start = m[pom];
			break;
		}
		m[pom] = i;
	}
	pom.clear();
	for (int i = 0; i < v.size(); i++) pom.push_back(v[i]);
	for (int i = 1; i < start; i++) {
		cycle(pom);
	}
	for (int i = 0; i < (big-start+1)%cycleLen; i++) {
		cycle(pom);
	}
	//cout << big%cycleLen << endl;
	//print(pom);
	cout << calc(pom);
	
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

