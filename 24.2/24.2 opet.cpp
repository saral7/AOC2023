#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

double e = 1e-4;
lli INF = 5*1e16;

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


struct frac {
public:
	lli x, y;
	
	frac (lli x, lli y) {
		this->x = x;
		this->y = y;
		this->sign();
		this->shorten();
	}
	
	void sign () {
		if (x < 0 && y < 0) {
			x *= -1;
			y *= -1;
		}
		if (x > 0 && y < 0) {
			x *= -1;
			y *= -1;
		}
	}
	
	static lli gcd (lli x, lli y) {
		return __gcd(abs(x), abs(y));
	}
	
	void shorten () {
		lli g = gcd(x, y);
		this->x /= g;
		this->y /= g;
	}
	
	friend frac operator + (frac a, frac b) {
		lli g = gcd(a.y, b.y);
		lli n = a.y/g*b.y;
		lli m = a.x*(b.y/g) + b.x*(a.y/g);
		return frac(m, n);
	}
	
	friend frac operator * (frac a, frac b) {
		lli n = a.y*b.y;
		lli m = a.x*b.x;
		frac f = frac(m, n);
		return f;
	}
	
	friend frac operator * (frac a, lli b) {
		lli n = a.y;
		lli m = a.x*b;
		return frac(m, n);
	}
	
	friend ostream& operator << (ostream &o, frac &s) {
		o << s.x << "/" << s.y;
		return o;
	}
};

bool mul (vector<frac> &v, frac a) {
	for (int i = 0; i < v.size(); i++) {
		v[i] = v[i]*a;
		if (v[i].x >= INF) return false;
	}
	return true;
}

bool add (vector<frac> &v1, vector<frac> &v2, frac a) {
	if (v1.size() != v2.size()) return false;;
	for (int i = 0; i < v1.size(); i++) {
		frac f = (v2[i]*a);
		if (f.x >= INF) return false;
		v1[i] = v1[i] + f;
		/*cout << v2[i] << "*" << a << " = " << f << " + " << v1[i] << endl;
		cout << " = " << v1[i] << endl;*/
	}
	return true;
}

void debug (vector<vector<frac> > &mat) {
	cout << "________________________________" << endl;
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			cout << mat[i][j] << " ";
		} 
		cout << endl;
	}
}


bool solveSystem (vector<vector<frac> > &mat) {
	for (int i = 0; i < mat[0].size()-1; i++) {
		/*cout << "new round" << endl;
		debug(mat);*/
		if (mat[i][i].x == 0) {
			for (int j = i+1; j < mat.size(); j++) {
				if (mat[j][i].x != 0) {
					swap(mat[i], mat[j]);
					break;
				}
			}
			if (mat[i][i].x == 0) return false;
			//cout << "moved" << endl;
			//debug(mat);
		}
		if (mat[i][i].x != 1 || mat[i][i].y != 1) {
			frac f = frac(mat[i][i].y, mat[i][i].x);
			if (!mul (mat[i], f)) return false;
			//cout << "reduced" << endl;
			//debug(mat);
		}
		for (int j = 0; j < mat.size(); j++) {
			if (j == i) continue;
			if (mat[j][i].x != 0) {
				frac f = frac(-mat[j][i].x, mat[j][i].y);
			//cout << j << " " << i << endl;
				if (!add(mat[j], mat[i], f)) return false;
			}
		}
		
	}
	return true;
}

bool get (stone a, stone b, stone c, vector<vector<frac> >&mat) {
	lli arr[7];
	mat.clear();
	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 3; j++) {
			vector<frac>pom;
			memset (arr, 0, sizeof(arr));
			arr[i] = a.v[j]-b.v[j];
			arr[j] = -a.v[i]+b.v[i];
			arr[i+3] = -a.c[j]+b.c[j];
			arr[j+3] = a.c[i]-b.c[i];
			arr[6] = a.c[i]*a.v[j]-a.c[j]*a.v[i]-(b.c[i]*b.v[j]-b.c[j]*b.v[i]);
			//cout << a << " " << i << " " << j << " -> " << -a.c[i]*a.v[j] << " " << a.c[j]*a.v[i] << endl; 
			//+b.c[i]*b.v[j]-b.c[j]*b.v[i];
			for (int j = 0; j < 7; j++) pom.push_back(frac(arr[j], 1));
			mat.push_back(pom);
		}
	}
	b = c;
	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 3; j++) {
			vector<frac>pom;
			memset (arr, 0, sizeof(arr));
			arr[i] = a.v[j]-b.v[j];
			arr[j] = -a.v[i]+b.v[i];
			arr[i+3] = -a.c[j]+b.c[j];
			arr[j+3] = a.c[i]-b.c[i];
			arr[6] = a.c[i]*a.v[j]-a.c[j]*a.v[i]-(b.c[i]*b.v[j]-b.c[j]*b.v[i]);
			//cout << a << " " << i << " " << j << " -> " << -a.c[i]*a.v[j] << " " << a.c[j]*a.v[i] << endl; 
			//+b.c[i]*b.v[j]-b.c[j]*b.v[i];
			for (int j = 0; j < 7; j++) pom.push_back(frac(arr[j], 1));
			mat.push_back(pom);
		}
	}
	if (!solveSystem(mat)) return false;
	
	for (int i = 0; i < 6; i++) {
		if (mat[i][6].y != 1 && mat[i][6].x != 0) return false;
	}
	return true;
}

void solve (vector<stone>&v) {
	double sol = 0.0;
	vector<vector<frac> >mat;
	int cnt = 0;
	for (int i = v.size()-1; i >= 0; i--) {
		for (int j = i-1; j >= 0; j--) {
			for (int k = j-1; k >= 0; k--) {
				++cnt;
				//cnt == 2961837
				if (get(v[i], v[j], v[k], mat)) {
					debug(mat);
					return;
				}
			}
		}
	}
	for (int i = 0; i < mat.size(); i++) {
		sol += mat[i][6].x;
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

