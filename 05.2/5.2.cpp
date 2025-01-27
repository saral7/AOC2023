#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<lli> &seeds, vector<vector<string> >&maps) {
	fstream file;
	file.open(name, ios::in);
	string line;
	getline(file, line);
	line += ";";
	lli val = 0;
	for (int i = 7; i < line.size(); i++) {
		if ('0' <= line[i] && line[i] <= '9') {
			val = val*10+line[i]-'0';
		}
		else {
			seeds.push_back(val);
			val = 0;
		}
	}
	vector<string>curr;
	while (getline(file, line)) {
		line += ";";
		if ('0' <= line[0] && line[0] <= '9') curr.push_back(line);
		else {
			if (!curr.empty()) maps.push_back(curr);
			curr.clear();
		}
	}
	if (!curr.empty()) maps.push_back(curr);
	curr.clear();
	
    /*for (int i = 0; i < seeds.size(); i++) cout << seeds[i] << " ";
    cout << endl;
	for (int i = 0;i < maps.size(); i++) {
		for (int j = 0; j < maps[i].size(); j++) {
			cout << maps[i][j] << endl;
		}
		cout << endl;
	}*/
	file.close();
}

void parse (string s, lli &a, lli &b, lli &len) {
	a = b = len = -1;
	lli val = 0;
	for (int i = 0; i < s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			val = 10*val+s[i]-'0';
		}
		else {
			if (a == -1) a = val;
			else {
				if (b == -1) b = val;
				else len = val;
			}
			val = 0;
		}
	}
}


void sweepLine (vector<pair<lli, lli> >&v) {
	vector<pair<lli, lli> >pom;
	lli l, r;
	sort (v.begin(), v.end());
	l = v[0].first, r = v[0].second;
	for (int i = 0; i < v.size(); i++) {
		if (l <= v[i].first && v[i].first <= r) {
			r = max(r, v[i].second);
			continue;
		}	
		pom.push_back({l, r});
		l = v[i].first;
		r = v[i].second;
	}
	pom.push_back({l, r});
	v.clear();
	for (int i = 0; i < pom.size(); i++) {
		v.push_back(pom[i]);
	}
}

void debug (vector<pair<lli, lli> >&v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << " " << v[i].second << endl;
	}
}

void solve (vector<lli> &seeds, vector<vector<string> >&maps) { 
	lli sol = 999999999999;
	vector<pair<lli, lli> >intervals, newIntervals, helper;
	
	for (int k = 0; k < seeds.size(); k+=2) { 
		lli l = seeds[k], r = seeds[k+1];
		intervals.clear();
		intervals.push_back({l, l+r-1});
		newIntervals.clear();
		for (int i = 0; i < maps.size(); i++) {
			lli a, b, len;
			//cout << "____________________________________________________" << endl;
			for (int x = 0; x < maps[i].size(); x++) {
				parse (maps[i][x], a, b, len);
				lli L = b, R = b+len-1;	// trenutni interval za preslikavanje
				lli off = a-b;
				//cout << "L, R " << L << ", " << R << endl;
				helper.clear();
				for (int j = 0; j < intervals.size(); j++) {
					l = intervals[j].first;
					r = intervals[j].second;
					
					if (l <= L && R <= r) { ///sredina upada
						if (l != L) helper.push_back({l, L-1});
						if (r != R) helper.push_back({R+1, r});
						newIntervals.push_back({L+off, R+off});
					//	cout << "sredina" << endl;
					}
					else if (l <= L && L <= r && r < R) { ///desni dio upada
						if (l != L) helper.push_back({l, L-1});
						newIntervals.push_back({L+off, r+off});
					//	cout << "desni dio" << endl;
					}
					else if (L < l && l <= R && R <= r) { ///lijevi dio upada
						if (r != R) helper.push_back({R+1, r});
						newIntervals.push_back({l+off, R+off});
					//	cout << "lijevi dio" << endl;
					}
					else if (L <= l && r <= R) { ///cijeli upada
						newIntervals.push_back({l+off, r+off});
					//	cout << "cijeli" << endl;
					}
					else if (R < l || r < L) { ///nis ne upada
						helper.push_back({l, r});
					//	cout << "nista" << endl;
					}
				}
				intervals.clear();
				//sweepLine(helper);
				for (int j = 0; j < helper.size(); j++) intervals.push_back(helper[j]);
			/*	cout << "helper: " << endl;
				debug(helper);
				cout << "news: " << endl;
				debug(newIntervals);*/
			}
			for (int j = 0; j < helper.size(); j++) newIntervals.push_back(helper[j]);
			sweepLine(newIntervals);
			intervals.clear();
			for (int j = 0; j < newIntervals.size(); j++) intervals.push_back(newIntervals[j]);
			newIntervals.clear();
		}
		sol = min(sol, intervals[0].first);
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<lli>seeds;
    vector<vector<string> >maps;
    read("input.txt", seeds, maps);

	solve (seeds, maps);
return 0;
}

