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
		line += ";";
		v.push_back(line);
	}
	
	file.close();
}

int parse (string s) {
	int ind = 0, ret = 0;
	while (s[ind++] != ':');
	int val = 0;
	set<int>mySet;
	bool before = true;
	for (int i = ind; i < s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			val = val*10+s[i]-'0';
			continue;
		}
		if (before && val) {
			mySet.insert(val);
			val = 0;
		}
		else {
			if (val && mySet.find(val) != mySet.end()) {
				ret++;
			}
			val = 0;
		}
		if (s[i] == '|') {
			before = false;
			continue;
		}
		
	}
	cout << ret << endl;
	return ret;
}

void solve (vector<string> &v) {
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
		sol += parse(v[i]);
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>v;
    read("input2.txt", v);
	solve(v);

return 0;
}

