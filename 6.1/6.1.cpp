#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void parse (string s, vector<int>&v) {
	int val = 0;
	for (int i = 10; i < s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			val = 10*val+s[i]-'0';
			continue;
		}
		else {
			if (val) v.push_back(val);
			val = 0;
		}
	}
}

void read (string name, vector<int>&t, vector<int>&d) {
	fstream file;
	file.open(name, ios::in);
	string line;
	getline(file, line);
	line += ";";
	parse(line, t);
	getline(file, line);
	line += ";";
	parse(line, d);
}

void solve (vector<int>&t, vector<int>&d) {
	int sol = 1;
	for (int i = 0; i < t.size(); i++) {
		int cnt = 0;
		for (int j = 0; j < t[i]; j++) {
			int dist = j*(t[i]-j);
			if (dist >= d[i]) cnt++;
		}
		cout << cnt << endl;
		sol *= cnt;
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int>t, d;
    read("input.txt", t, d);
	solve(t, d);

return 0;
}

