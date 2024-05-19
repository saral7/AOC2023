#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

double e = 1e-4;
long double INF = 5*1e16;

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

bool mul (vector<long double> &v, long double a) {
	for (int i = 0; i < v.size(); i++) {
		v[i] = v[i]*a;
		if (v[i] >= INF) return false;
	}
	return true;
}

bool add (vector<long double> &v1, vector<long double> &v2, long double a) {
	if (v1.size() != v2.size()) return false;;
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = v1[i] + v2[i]*a;
		/*cout << v2[i] << "*" << a << " = " << f << " + " << v1[i] << endl;
		cout << " = " << v1[i] << endl;*/
	}
	return true;
}

void debug (vector<vector<long double> > &mat) {
	cout << "________________________________" << endl;
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			cout << setprecision(20) << mat[i][j] << " ";
		} 
		cout << endl;
	}
}


bool solveSystem (vector<vector<long double> > &mat) {
	for (int i = 0; i < mat[0].size()-1; i++) {
		/*cout << "new round" << endl;
		debug(mat);*/
		if (abs(mat[i][i]) < e) { ///mat[i][i] == 0
			for (int j = i+1; j < mat.size(); j++) {
				if (llabs(mat[j][i]) > e) {
					swap(mat[i], mat[j]);
					break;
				}
			}
			if (abs(mat[i][i]) < e) return false;
			//cout << "moved" << endl;
			//debug(mat);
		}
		if (abs(mat[i][i]-1.0) > e) {
			if (!mul (mat[i], (long double)1.0/mat[i][i])) return false;
			//cout << "reduced" << endl;
			//debug(mat);
		}
		for (int j = 0; j < mat.size(); j++) {
			if (j == i) continue;
			if (abs(mat[j][i]) > e) { /// mat[j][i] != 0
				if (!add(mat[j], mat[i], -mat[j][i])) return false;
			}
		}
		
	}
	return true;
}

bool get (stone a, stone b, stone c, vector<vector<long double> >&mat) {
	lli arr[7];
	mat.clear();
	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 3; j++) {
			vector<long double>pom;
			memset (arr, 0, sizeof(arr));
			arr[i] = a.v[j]-b.v[j];
			arr[j] = -a.v[i]+b.v[i];
			arr[i+3] = -a.c[j]+b.c[j];
			arr[j+3] = a.c[i]-b.c[i];
			arr[6] = a.c[i]*a.v[j]-a.c[j]*a.v[i]-(b.c[i]*b.v[j]-b.c[j]*b.v[i]);
			//cout << a << " " << i << " " << j << " -> " << -a.c[i]*a.v[j] << " " << a.c[j]*a.v[i] << endl; 
			//+b.c[i]*b.v[j]-b.c[j]*b.v[i];
			for (int j = 0; j < 7; j++) pom.push_back(arr[j]);
			mat.push_back(pom);
		}
	}
	b = c;
	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 3; j++) {
			vector<long double>pom;
			memset (arr, 0, sizeof(arr));
			arr[i] = a.v[j]-b.v[j];
			arr[j] = -a.v[i]+b.v[i];
			arr[i+3] = -a.c[j]+b.c[j];
			arr[j+3] = a.c[i]-b.c[i];
			arr[6] = a.c[i]*a.v[j]-a.c[j]*a.v[i]-(b.c[i]*b.v[j]-b.c[j]*b.v[i]);
			//cout << a << " " << i << " " << j << " -> " << -a.c[i]*a.v[j] << " " << a.c[j]*a.v[i] << endl; 
			//+b.c[i]*b.v[j]-b.c[j]*b.v[i];
			for (int j = 0; j < 7; j++) pom.push_back(arr[j]);
			mat.push_back(pom);
		}
	}
	
	if (!solveSystem(mat)) return false;
	
	for (int i = 0; i < 6; i++) {
		if (llabs(mat[i][6]-(lli)mat[i][6]) > e) return false;
	}
	return true;
}

void solve (vector<stone>&v) {
	double sol = 0.0;
	vector<vector<long double> >mat;
	int cnt = 0;
	for (int i = v.size()-1; i >= 0; i--) {
		for (int j = i-1; j >= 0; j--) {
			for (int k = j-1; k >= 0; k--) {
				//cnt == 2961837
				if (get(v[i], v[j], v[k], mat)) {
					debug(mat);
					for (int l = 0; l < mat.size(); l++) {
						sol += mat[l][6];
					}
				++cnt;
					//cout << setprecision(21) << sol << endl;
					system("pause");
				}
			}
		}
	}
	cout << cnt;
return;
}

int main () {
	cout << setprecision(20) << 446533732372768+293892176908833+180204909018503;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<stone>v;
    read("input.txt", v);
	solve(v);

return 0;
}

