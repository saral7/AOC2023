#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<vector<string> >&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	vector<string>pom;
	while (getline(file, line)) {
		if (line == "") {
			v.push_back(pom);
			pom.clear();
		} 
		else {
			pom.push_back(line);
		}
	}
	if (pom.size()) v.push_back(pom);
	file.close();
}

int getRows (vector<string> &v, int dx = -1) {
	int ret = 0;
	for (int i = 0; i < v.size()-1; i++) {
		if (i == dx-1) continue;
		for (int j = 0; j < v.size(); j++) {
			if (i-j < 0 || i+j+1 >= v.size()) {
				return i+1;	
			}
			if (v[i-j] != v[i+j+1]) break;
		}
	}
	return ret;
}

int calc (vector<string> &v) {
	vector<string>pom;
	string s;
	for (int j = 0; j < v[0].size(); j++) {
		s = "";
		for (int i = 0; i < v.size(); i++) s += v[i][j];
		pom.push_back(s);
	}
	
	int ret = 0;
	int n = v.size(), m = v[0].size();
	int dx = getRows(v);
	int dy = getRows(pom);
	if (!dx) dx = -1;
	if (!dy) dy = -1;
	//cout << dx << " " << dy << endl;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == '.') {
				v[i][j] = '#';
				pom[j][i] = '#';
			}
			else {
				v[i][j] = '.';
				pom[j][i] = '.';
			}
			//cout << i << " " << j << endl;
			//for (int k = 0; k < v.size(); k++) cout << v[k] << endl;
			//cout << endl;
			int len, mini, maxi;
			ret = 100*getRows(v, dx);
			len = min(n-ret/100, ret/100);
			mini = ret/100-len;
			maxi = ret/100+len-1;
			if (ret && mini <= i && i <= maxi) {
				if (v[i][j] == '.') {
					v[i][j] = '#';
					pom[j][i] = '#';
				}
				else {
					v[i][j] = '.';
					pom[j][i] = '.';
				}
				return ret;
			}
			ret = getRows(pom, dy);
			len = min(m-ret, ret);
			mini = ret-len;
			maxi = ret+len-1;
			if (ret && mini <= j && j <= maxi) {
				if (v[i][j] == '.') {
					v[i][j] = '#';
					pom[j][i] = '#';
				}
				else {
					v[i][j] = '.';
					pom[j][i] = '.';
				}
				return ret;
			}
			if (v[i][j] == '.') {
				v[i][j] = '#';
				pom[j][i] = '#';
			}
			else {
				v[i][j] = '.';
				pom[j][i] = '.';
			}
		}
	}
		
	return ret;
}

void solve (vector<vector<string> >&v) {
	int sol = 0;
	cout << v.size() << endl;
	for (int i = 0; i < v.size(); i++) {
		//for (int j = 0; j < v[i].size(); j++) cout << v[i][j] << endl;
		//cout << calc(v[i]) << endl;
		//system("pause");
		sol += calc(v[i]);
	}
	cout << sol << endl; 
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<vector<string> >v;
    read ("input.txt", v);
	solve(v);

return 0;
}

