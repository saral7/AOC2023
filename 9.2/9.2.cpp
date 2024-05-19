#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void parse (string line, vector<lli> &p) {
	line += ";";
	lli val = 0;
	int plus = 1;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '-') {
			plus = -1;
			continue;
		}
		if ('0' <= line[i] && line[i] <= '9') {
			val = val*10+line[i]-'0';
			continue;
		}
		p.push_back(val*plus);
		val = 0;
		plus = 1;
	}
	return;
}

void read (string name, vector<vector<lli> >&v) {
	fstream file;
	file.open(name, ios::in);
	
	string line;
	while (getline(file, line)) {
		vector<lli>pom;
		parse (line, pom);
		v.push_back(pom);
	}
	
	file.close();
}

lli get (vector<lli> &v) {
	int n = v.size();
	int diff[n+1][n+1];
	memset (diff, 0, sizeof(diff));

	for (int j = 1; j <= n; j++) diff[1][j] = v[j-1];
	int stop;
	for (int i = 2; i < n; i++) {
		bool done = true;
		for (int j = i; j <= n; j++) {
			diff[i][j] = diff[i-1][j]-diff[i-1][j-1];
			if (diff[i][j]) done = false;
		}
		if (done) {
			stop = i;
			break;
		}
	}
	lli ret = 0;
	lli a = 0;
	
	/*for (int i = 1; i <= stop; i++) {
		for (int j = i; j <= n; j++) {
			cout << diff[i][j] << " ";
		}
		cout << endl;
	}*/
	for (int i = stop-1; i >= 1; i-=1) {
		a = diff[i][i]-a;
	}
	return a;
}

void solve (vector<vector<lli> >&v) {
	lli sol = 0;
	for (int i = 0; i < v.size(); i++) {
		sol += get(v[i]);
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<vector<lli> >v;
    read ("input.txt", v);
    
	solve(v);

return 0;
}

