#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

struct stone {
	lli c[3];
	lli v[3];
	
	friend ostream& operator << (ostream &o, stone &s) {
		o << s.c[0] << " " << s.c[1] << " " << s.c[2] << " " << s.v[0] << " " << s.v[1] << " " << s.v[2];
		return o;
	}
};

void parse (string line, stone &curr) {
	line += ",";
	lli val = 0;
	int sign = 1;
	int cnt = 1;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '-') {
			sign = -1;
			continue;
		}
		if (line[i] == ' ') continue;
		if (line[i] == ',' || line[i] == '@') {
			val *= sign;
			if (cnt <= 3) curr.c[cnt-1] = val;
			else curr.v[cnt-4] = val;
			cnt++;
			sign = 1;
			val = 0;
		}
		else {
			val = 10*val+line[i]-'0';
		}
	}
	return;
}

void read (string name, vector<stone> &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		stone curr;
		parse (line, curr);
		v.push_back(curr);
	}
	file.close();
}

void mul (vector<double> &v, double a) {
	for (int i = 0; i < v.size(); i++) {
		v[i] *= a;
	}
}

void add (vector<double> &v1, vector<double> &v2, double a) {
	if (v1.size() != v2.size()) return;
	for (int i = 0; i < v1.size(); i++) {
		v1[i] += v2[i]*a;
	}
}

void debug (vector<vector<double> > &mat) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			cout << mat[i][j] << " ";
		} 
		cout << endl;
	}
}

double e = 1e-4;

bool intersect (stone &a, stone &b, double &x, double &y, double &z) {
	vector<vector<double> >mat;
	for (int i = 0; i < 2; i++) {
		vector<double>pom;
		pom.push_back(a.v[i]);
		pom.push_back(-b.v[i]);
		pom.push_back(b.c[i]-a.c[i]);
		mat.push_back(pom);
	}
	
	for (int i = 0; i < mat.size(); i++) {
		if (mat[i][i] != 1) {
			mul (mat[i], (double)1.0/mat[i][i]);
		}
		
		for (int j = 0; j < mat.size(); j++) {
			if (j == i) continue;
			if (mat[j][i] != 0) {
				add(mat[j], mat[i], -mat[j][i]);
			}
		}
	}
	//if (mat[0][0] != 1 || mat[1][1] != 1) return false;
	if (abs(mat[0][0]-1.0) > e || abs(mat[1][1]-1.0) > e) return false;
	if (mat[0][2] < 0 || mat[1][2] < 0) return false;
	//debug(mat);
	x = a.c[0]+mat[0][2]*a.v[0];
	y = b.c[1]+mat[1][2]*b.v[1];
	//cout << a << ", " << b << ": " << x << " " << y << endl; 
	return true;
}

void solve (vector<stone>&v) {
	cout << v.size() << endl;
	int sol = 0;
	//double low = 200000000000000.0, up = 400000000000000.0;
	double low = 7.0, up = 27.0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < i; j++) {
			double x, y, z;
			if (intersect(v[i], v[j], x, y, z)) {
				if (low <= x && x <= up && low <= y && y <= up) sol++;
				/*cout << v[i] << " " << v[j] << endl;
				cout << x << " " << y << endl;
				system("pause");*/
			}
		}
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<stone>v;
    read("input2.txt", v);
	solve(v);

return 0;
}

