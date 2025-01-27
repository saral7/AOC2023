#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void parse (string s, lli &v) {
	lli val = 0;
	for (int i = 10; i < s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			val = 10*val+s[i]-'0';
			continue;
		}
		else {
			if (s[i] == ';') v = val;
		}
	}
}

void read (string name, lli &t, lli &d) {
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

lli binaryLeft (lli l, lli r, lli t, lli d) {
	while (l != r) {
		lli mid = (l+r)/2;
		lli val = -mid*mid+mid*t;
		if (val >= d) {
			r = mid;
		}
		else {
			l = mid+1;
		}
	}
	return l;
}

void solve (lli t, lli d) {
	int sol = 1;
	cout << t << " " << d << endl;
	lli l = binaryLeft(0, t/2, t, d);
	lli r = t-l;
	cout << l << " " << r << endl;
	sol = r-l+1;
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t, d;
    read("input.txt", t, d);
	solve(t, d);

return 0;
}

