#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void parse (string line, string &node, string &left, string &right) {
	node = left = right = "";
	for (int i = 0; i < 3; i++) node += line[i];
	for (int i = 7; i < 10; i++) left += line[i];
	for (int i = 12; i < 15; i++) right += line[i];
}

void read (string name, string &moves, map<string, pair<string, string> > &m) {
	fstream file;
	file.open(name, ios::in);
	
	string line;
	getline (file, line);
	moves = line;
	getline(file, line);
	int cnt = 0;
	while (getline(file, line)) {
		string node, left, right;
		parse (line, node, left, right);
		m[node] = {left, right};
	}
	cout << cnt << endl;
	file.close();
}

lli LCM (vector<lli>&v) {
	lli curr = v[0];
	lli lcm = v[0];
	for (int i = 1; i < v.size(); i++) {
		lcm = lcm*v[i]/(__gcd(lcm, v[i]));
	}
	return lcm;
}

lli travel (string moves, string start, map<string, pair<string, string> >&m) {
	string curr = start;
	int ind = 0, cnt = 1, n = moves.size();
	map<pair<string, int>, int>been;
	while (!been[{curr, ind}]) {
		been[{curr, ind}] = cnt;
		/*if (curr[curr.size()-1] == 'Z') {
			cout << "found Z at " << curr << " " << cnt-1 << endl; 
		}*/
		
		if (moves[ind] == 'L') curr = m[curr].first;
		else curr = m[curr].second;
		
		cnt++;
		ind = (ind+1)%n;
	}
	//cout << curr << " : " << been[{curr, ind}]-1 << " " << cnt-1 << endl;
	int cycleLength = cnt-been[{curr, ind}];
	//cout << "cycleLength " << cycleLength << endl;
	return (lli) cycleLength;
}

void solve (string moves, map<string, pair<string, string> >&m) {
	int ind = 0, cnt = 0, n = moves.size();
	vector<lli>v;
	for (auto it = m.begin(); it != m.end(); it++) {
		string curr = it->first;
		if (curr[curr.size()-1] == 'A') {
			v.push_back(travel(moves, curr, m));
		}
	}
	
	cout << LCM(v);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string moves;
    map<string, pair<string, string> >m;
    read ("input.txt", moves, m);
    
	solve(moves, m);

return 0;
}

