#include <bits/stdc++.h>

using namespace std;
#define lli long long int

struct brick {
	int x1, y1, z1;
	int x2, y2, z2;
	
	friend bool operator < (brick a, brick b) {
		return a.z1 < b.z1;
	}
	
	friend ostream& operator << (ostream &o, brick a) {
		o << a.x1 << "," << a.y1 << "," << a.z1 << "~" << a.x2 << "," << a.y2 << "," << a.z2;
		return o; 
	}
};

void parse (string line, int &x1, int &y1, int &z1, int &x2, int &y2, int &z2) {
	int state = 1;
	line += ",";
	int val = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ',' || line[i] == '~') {
			if (state == 1) x1 = val;
			if (state == 2) y1 = val;
			if (state == 3) z1 = val;
			if (state == 4) x2 = val;
			if (state == 5) y2 = val;
			if (state == 6) z2 = val;
			val = 0;
			state++;
			continue;
		}
		val = 10*val+line[i]-'0';
	}
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	if (z1 > z2) swap(z1, z2);
	return;
}

void read (string name, vector<brick>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	int i = 0;
	while (getline(file, line)) {
		brick b;
		parse(line, b.x1, b.y1, b.z1, b.x2, b.y2, b.z2);
		v.push_back(b);
	}
	file.close();
}

bool cmp (brick a, brick b) {
	return a.z1 < b.z1;
}

const int N = 1507;
vector<int>under[N], above[N];

bool intersect (brick a, brick b) {
	return max(a.x1, b.x1) <= min(a.x2, b.x2) && max(a.y1, b.y1) <= min(a.y2, b.y2);
}

void solve (vector<brick>&v) {
	sort(v.begin(), v.end(), cmp);
	int cnt = 0;
	for (int i = 0; i < v.size(); i++) {
		int zmax = 1;
		for (int j = 0; j < i; j++) {
			if (intersect(v[i], v[j])) {
				cnt++;
				zmax = max(zmax, v[j].z2+1);
			}
		}
		v[i].z2 += (zmax-v[i].z1);
		v[i].z1 = zmax;
		for (int j = 0; j < i; j++) {
			if (intersect(v[i], v[j]) && v[j].z2+1 == v[i].z1) {
				under[i].push_back(j);
				above[j].push_back(i);
			}
		}
	}
	cout << cnt << endl;
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		bool can = true;
		for (int j = 0; j < above[i].size(); j++) {
			if (under[above[i][j]].size() == 1) can = false;
		}
		sol += can;
	}
	cout << v.size() << endl;
	cout << sol << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<brick>v;
    read("input.txt", v);
	solve(v);

return 0;
}

