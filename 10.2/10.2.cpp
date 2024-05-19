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
		v.push_back(line);
	}
	file.close();
}

bool inside (int x, int y, const vector<string> &v) {
	return (0 <= x && x < v.size() && 0 <= y && y < v[0].size());
}

pair<int, int> moveIt (pair<int, int> pos, const vector<string> &v, const vector<string> &been) {
	char z = v[pos.first][pos.second];
	int dx[] = {-1, 1, 0, 0, -1, 0, -1, 0, 1, 0, 1, 0};
	int dy[] = {0, 0, -1, 1, 0, 1, 0, -1, 0, -1, 0, 1};
	map<char, int>m;
	m['|'] = 0, m['-'] = 2, m['L'] = 4, m['J'] = 6, m['7'] = 8, m['F'] = 10;
	int x = pos.first, y = pos.second, susx, susy;
	if (z == 'S') {
		return {x+1, y};
	}
	for (int i = m[z]; i < m[z]+2; i++) {
		susx = x+dx[i];
		susy = y+dy[i];
		if (!inside(susx, susy, v) || been[susx][susy] == '1' || v[susx][susy] == '.') continue;
		return {susx, susy};
	}
	return {-1, -1};
}

void dfs (pair<int, int>pos, const vector<string> &v, vector<string> &been, int& val, vector<string> &borders) {
	if (been[pos.first][pos.second] == '1') return;
	//cout << pos.first << " " << pos.second << endl;
	//system("pause");
	been[pos.first][pos.second] = '1';
	val++;
	borders[pos.first][pos.second] = v[pos.first][pos.second];
	pair<int, int>nextPos = moveIt(pos, v, been);
	//cout << "next -> " << nextPos.first << " " << nextPos.second << endl;
	if (nextPos.first == nextPos.second && nextPos.first == -1) return;
	dfs (nextPos, v, been, val, borders);
	return;
}

void write (string name, vector<string> &v) {
	fstream file;
	file.open(name, ios::out);
	for (int i = 0; i < v.size(); i++) {
		file << v[i] << "\n";
	}
	file.close();
}

int calc (string s) {
	int pos = 0, lastPos, sol = 0;
	bool open = false;
	char first = '!';
	
	for (int i = 0; i < s.size(); i++) {
		char z = s[i];
		//cout << open;
		//cout << "(" << z << ": " << open << ") "; 
		if (!open) {
			if (z == '.' || z == '-') continue;
			if (z == 'F' || z == 'L' || z == '|') {
				open = true;
				first = z;
			}
			if (z == 'J') {
				if (first == 'L') {
					open = true;
					first = z;
				}
				else {
					open = false;
				}
			}
			if (z == '7') {
				if (first == 'F') {
					open = true;
					first = z;
				}
				else {
					open = false;
				}
			}
		}
		else {
			if (z == '.') sol++;
			if (z == '.' || z == '-') continue;
			if (z == 'F' || z == 'L' || z == '|') {
				open = false;
				first = z;
			}
			if (z == 'J') {
				if (first == 'L') {
					open = false;
				}
			}
			if (z == '7') {
				if (first == 'F') {
					open = false;
				}
			}
		}
	}
	cout << endl;
	return sol;
}

int getArea (vector<string> &v) {
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		sol += calc(v[i]);
		cout << v[i] << " " << calc(v[i]) << endl;
		//system("pause");
	}
	return sol;
}

void solve (vector<string> &v) {
	vector<string>been, borders;
	string pom = "";
	pair<int, int> pos;
	for (int i = 0; i < v.size(); i++) {
		//cout << v[i] << endl;
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == 'S') pos = {i, j};
		}
	}
	for (int j = 0; j < v[0].size(); j++) pom += ".";
	for (int i = 0; i < v.size(); i++) {
		been.push_back(pom);
		borders.push_back(pom);
	}
	int cycleLength = 0;
	cout << borders[pos.first] << endl;
	dfs (pos, v, been, cycleLength, borders);
	borders[pos.first][pos.second] = '7';
	write ("clean.txt", borders);
	cout << getArea(borders);
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

