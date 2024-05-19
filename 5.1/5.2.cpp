#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<lli> &seeds, vector<vector<string> >&maps) {
	fstream file;
	file.open(name, ios::in);
	string line;
	getline(file, line);
	line += ";";
	lli val = 0;
	for (int i = 7; i < line.size(); i++) {
		if ('0' <= line[i] && line[i] <= '9') {
			val = val*10+line[i]-'0';
		}
		else {
			seeds.push_back(val);
			val = 0;
		}
	}
	vector<string>curr;
	while (getline(file, line)) {
		line += ";";
		if ('0' <= line[0] && line[0] <= '9') curr.push_back(line);
		else {
			if (!curr.empty()) maps.push_back(curr);
			curr.clear();
		}
	}
	if (!curr.empty()) maps.push_back(curr);
	curr.clear();
	
	/*for (int i = 0;i < maps.size(); i++) {
		for (int j = 0; j < maps[i].size(); j++) {
			cout << maps[i][j] << endl;
		}
		cout << endl;
	}*/
	file.close();
}

void parse (string s, lli &a, lli &b, lli &len) {
	a = b = len = -1;
	lli val = 0;
	for (int i = 0; i < s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			val = 10*val+s[i]-'0';
		}
		else {
			if (a == -1) a = val;
			else {
				if (b == -1) b = val;
				else len = val;
			}
			val = 0;
		}
	}
}


void solve (vector<lli> &seeds, vector<vector<string> >&maps) { 
	lli sol = 999999999999;
	for (lli seed : seeds) {
		//cout << "seed: " << seed << endl; 
		for (int i = 0; i < maps.size(); i++) {
			lli a, b, len;
			for (int j = 0; j < maps[i].size(); j++) {
				parse (maps[i][j], a, b, len);
				if (b <= seed && seed <= b+len-1) { 
					seed = a+(seed-b);
					break;
				}
			}
			//cout << seed << endl;
		}
		sol = min(seed, sol);
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<lli>seeds;
    vector<vector<string> >maps;
    read("input.txt", seeds, maps);
	solve (seeds, maps);
return 0;
}

