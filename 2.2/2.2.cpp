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
	int ind = 0;
	while (s[++ind] != ':');
	ind+=2;
	s = s.substr(ind);
	
	int arr[3] = {0, 0, 0};
	int val = 0, sol = 0;
	for (int i = 0; i < s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			val = val*10+(s[i]-'0');
			continue;
		}
		if (s[i+1] == 'r') {
			arr[0] = max(arr[0], val);
			i+=5;
		}
		if (s[i+1] == 'g') {
			arr[1] = max(arr[1], val);
			i+=7;
		}
		if (s[i+1] == 'b') {
			arr[2] = max(arr[2], val);
			i+=6;
		}
		val = 0;
		
	}
	sol += arr[0]*arr[1]*arr[2];
	return sol;
}

void solve (vector<string> &v) {
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		sol += parse(v[i]);
	}
	cout << sol << endl;
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

