#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

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

void solve (vector<string>&v) {
	int sol = 0;
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
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == 'O') {
				sol += v.size()-i;
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
	solve(v);

return 0;
}

