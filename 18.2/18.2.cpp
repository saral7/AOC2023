#include <bits/stdc++.h>

using namespace std;
#define lli long long int

struct str {
	char z;
	lli d;
	string col;
};

lli hex (string s) {
	lli val = 0;
	lli h = 1;
	for (int i = s.size()-2; i >= 0; i-=1) {
		if ('0' <= s[i] && s[i] <= '9') {
			val += (s[i]-'0')*h;
		}
		else {
			val += (s[i]-'a'+10)*h;
		}
		h *= 16;
	}
	return val;
}

void parse (string line, char &z, lli &d, string &col) {
	col = "";
	d = 0;
	int i;
	if (line[line.size()-2] == '0') z = 'R';
	if (line[line.size()-2] == '1') z = 'D';
	if (line[line.size()-2] == '2') z = 'L';
	if (line[line.size()-2] == '3') z = 'U';
	for (i = 2; i < line.size() && line[i] != ' '; i++) {}
	i+=3;
	for (; i < line.size() && line[i] != ')'; i++) {
		col += line[i];
	}
	d = hex(col);
	return;
}

void read (string name, vector<str>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		str curr;
		parse (line, curr.z, curr.d, curr.col);
		v.push_back(curr);
	}
	
	file.close();
}

const int N = 407;
char grid[N][N];

lli sweepLine (vector<pair<lli, pair<lli, lli> > > &v) {
	set<lli>s;
	vector<lli>yaxis;
	lli sol = 0;
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		s.insert(v[i].second.first);
		s.insert(v[i].second.second);
	}
	for (auto val : s) {
		yaxis.push_back(val);
	}
	bool open = false;
	const lli INF = 1e17;
	lli last = INF;
	
	for (int j = 0; j < yaxis.size()-1; j++) {
		lli y = yaxis[j], y2 = yaxis[j+1];
		for (int i = v.size()-1; i >= 0; i-=1) {
			lli l = v[i].second.first;
			lli r = v[i].second.second;
			lli row = v[i].first;
			if (!(l <= y && y < r)) continue;
			if (open) {
				sol += (y2-y)*(last-row);
				open = false;
				last = INF;
			}
			else {
				open = true;
				last = row;
			}
		}
	}
	return sol;
}

void solve (vector<str>&v) {
	int x = 0, y = 0;
	int dx = 0, dy = 0;
	int n = 0, m = 0;
	char z;
	vector<pair<lli, pair<lli, lli> > >lines;
	bool ccw;
		
	z = v[0].z;
	///assume cw traversal
	vector<pair<lli, lli> >nodes;
	
	
	for (int i = 0; i < v.size(); i++) {
		int ind2 = i;
		int ind1 = (i-1+v.size())%v.size();
		dx = dy = 0;
		char z1 = v[ind1].z;
		char z2 = v[ind2].z;
		//cout << x << " " << y << " " << z1 << " " << z2 << endl;
		if (z2 == 'R') dy = 1;
		if (z2 == 'L') dy = -1;
		if (z2 == 'U') dx = 1;
		if (z2 == 'D') dx = -1;
		
		int x2 = y;
		int y2 = x;
		
		if (z1 == 'R' && z2 == 'D') {
			nodes.push_back({x2+1, y2+1}); //
		}
		if (z1 == 'L' && z2 == 'D') {
			nodes.push_back({x2+1, y2}); //
		}
		if (z1 == 'R' && z2 == 'U') {
			nodes.push_back({x2, y2+1}); 
		}
		if (z1 == 'L' && z2 == 'U') {
			nodes.push_back({x2, y2}); //
		}
		
		if (z1 == 'U' && z2 == 'R') {
			nodes.push_back({x2, y2+1}); //
		}
		if (z1 == 'D' && z2 == 'R') {
			nodes.push_back({x2+1, y2+1}); //
		}
		if (z1 == 'U' && z2 == 'L') {
			nodes.push_back({x2, y2}); //
		}
		if (z1 == 'D' && z2 == 'L') {
			nodes.push_back({x2+1, y2}); //
		}
		//cout << "pushed: " << nodes.back().first << " " << nodes.back().second << endl;
		x = x+dx*v[ind2].d, y = y+dy*v[ind2].d;
	}
	//cout << "Nodes:\n";
	for (int i = 0; i < nodes.size(); i+=2) {
		lines.push_back({nodes[i].second, {min(nodes[i].first, nodes[i+1].first), max(nodes[i].first, nodes[i+1].first)}});
		//cout << lines.back().first << " " << lines.back().second.first << " " << lines.back().second.second << endl;
	}
	cout << sweepLine(lines);
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<str>v;
    read ("input.txt", v);
	solve(v);

return 0;
}

