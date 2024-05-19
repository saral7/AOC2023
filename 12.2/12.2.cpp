#include <bits/stdc++.h>

using namespace std;
#define lli long long int

void parse (string line, string &s, vector<int> &pom) {
	bool signs = true;
	int val = 0;
	line += ";";
	string curr = "";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
			signs = false;
			s = curr;
		}
		if (signs) {
			curr += line[i];
			continue;
		}
		else {
			if (!('0' <= line[i] && line[i] <= '9')) {
				if (val) pom.push_back(val);
				val = 0;
			}
			else {
				val = 10*val+line[i]-'0';
			}
		}
	}
	return;
}

void read (string name, vector<string> &s, vector<vector<int> > &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	
	while (getline(file, line)) {
		vector<int> pom;
		string curr;
		parse (line, curr, pom);
		s.push_back(curr);
		v.push_back(pom);
	}
	file.close();
}

const int N = 300;
lli dp[N][N];

bool canPlace (string s, int l, int r) {
	if (l < 0 || r >= s.size()) return false;
	for (int j = l; j <= r; j++) {
		if (s[j] == '.') return false;
	}
	if (r == s.size()-1 || s[r+1] != '#') return true;
	return false;
}

lli calc (string &s, const vector<int> &v, int posS, int posV) {
	//cout << posS << " " << posV << endl;
	//system("pause");
	if (dp[posS][posV] != -1) return dp[posS][posV];
	if (posS >= s.size() && posV >= v.size()) {
		dp[posS][posV] = 1;
		return 1;	
	}
	if (posS >= s.size()) return 0;
	if (posV >= v.size()) {
		for (int j = posS; j < s.size(); j++) {
			if (s[j] == '#') {
				dp[posS][posV] = 0;
				return 0;
			}
		}	
		dp[posS][posV] = 1;
		return 1;
	}
	//cout << "prosao" << endl;
	char z = s[posS];
	int l = v[posV];
	lli ret = 0;
	if (z == '.') ret = calc(s, v, posS+1, posV);
	if (z == '?') {
		if (canPlace(s, posS, posS+l-1)) {
			ret += calc(s, v, posS+l+1, posV+1);
		}
		ret += calc(s, v, posS+1, posV);
		
	} 
	if (z == '#') {
		if (!canPlace(s, posS, posS+l-1)) {
			dp[posS][posV] = 0;
			return 0;
		}
		ret += calc(s, v, posS+l+1, posV+1);
	}
	dp[posS][posV] = ret;
	return ret;
}

void solve (vector<string> &s, vector<vector<int> > &v) {
	lli sol = 0;
	vector<int>v2;
	for (int i = 0; i < v.size(); i++) {
		string s2 = s[i];
		/*cout << s[i] << endl;*/
		for (int k = 0; k < 5; k++) {
			if (k < 4) s2 = s2+"?"+s[i];
			for (int j = 0; j < v[i].size(); j++) {
				v2.push_back(v[i][j]);
			}
		}
		/*cout << s2 << " ";
		for (int j = 0; j < v2.size(); j++) {
			cout << v2[j] << " ";
		}
		cout << endl;*/
		memset (dp, -1, sizeof(dp));
		sol +=  calc(s2, v2, 0, 0);
		v2.clear();
	}
	cout << sol << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>s;
    vector<vector<int> >v;
    read ("input.txt", s, v);
	solve(s, v);

return 0;
}

