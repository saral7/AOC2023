#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<string>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	string pom = "";
	getline(file, line);
	line += ",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ',') {
			v.push_back(pom);
			pom = "";
		}
		else pom += line[i];
	}
	file.close();

}

lli hashIt (string s) {
	lli ret = 0;
	for (int i = 0; i < s.size(); i++) {
		ret = ((ret+s[i])*17)%256;
	}
	return ret;
}

vector<pair<string, int> >arr[256];

void label (string s, string &name, char &action, int &val) {
	name = "", val = 0;
	bool flag = false;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '=' || s[i] == '-') {
			flag = true;
			action = s[i];
			continue;
		}
		if (flag) {
			val = 10*val+s[i]-'0';
		}
		else {
			name += s[i];
		}
	}
	return;
}

void put (string s, int val, vector<pair<string, int> > &v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].first == s) {
			v[i].second = val;
			return;
		}
	}
	v.push_back({s, val});
}

void remove (string s, vector<pair<string, int> > &v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].first == s) {
			v.erase(v.begin()+i);
			return;
		}
	}
}

void solve (vector<string> &v) {
	lli sol = 0;
	string name;
	char action;
	int val, h;
	for (int i = 0; i < v.size(); i++) {
		label (v[i], name, action, val);
		h = hashIt(name);
		if (action == '=') put(name, val, arr[h]);
		if (action == '-') remove(name, arr[h]);
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			sol += (i+1)*(j+1)*arr[i][j].second;
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
    read ("input.txt", v);
	solve(v);

return 0;
}

