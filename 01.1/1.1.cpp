#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read(vector<string> &v, string name) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		v.push_back(line);
	}
	file.close();
	return;
}

void solve (vector<string> &v) {
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		string curr = v[i];
		int first = -1, last = -1;
		for (int j = 0; j < curr.size(); j++) {
			if ('0' <= curr[j] && curr[j] <= '9') {
				if (first == -1) first = curr[j]-'0';
				last = curr[j]-'0';
			}	
		} 
		if (first == -1) first = last = 0;
		sol += first*10+last;
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    vector<string> v;
	read(v, "input.txt");
	solve(v);

return 0;
}

