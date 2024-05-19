#include <bits/stdc++.h>

using namespace std;
#define lli long long int

const int N = 1500;
vector<int>graph[N];

void read (string name, vector<string>&v, map<string, int>&m) {
	fstream file;
	file.open(name, ios::in);
	string line;
	string pom, node;
	int cnt = 0;
	while (getline(file, line)) {
		line += " ";
		pom = "";
		node = "";
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ':') {
				if (!m.count(pom)) {
					m[pom] = cnt;
					v.push_back(pom);
					cnt++;
				}	
				node = pom;
				pom = "";
				i++;
				continue;
			}
			if (line[i] == ' ') {
				if (!m.count(pom)) {
					m[pom] = cnt;
					v.push_back(pom);
					cnt++;
				}
				graph[m[node]].push_back(m[pom]);
				graph[m[pom]].push_back(m[node]);
				pom = "";
			}
			else {
				pom += line[i];
			}
		}
	}
	file.close();
}

int col[N];
int been[N];
int active[N][N];

void dfs (int node, int c) {
	if (col[node]) return;
	col[node] = c;
	for (int i = 0; i < graph[node].size(); i++) {
		if (!active[node][graph[node][i]]) continue;
		dfs(graph[node][i], c);
	}
	return;
}

bool bfs (int a, int b, vector<int> &path) {
	queue<int>q;
	memset (been, 0, sizeof(been));
	q.push(a);
	been[a] = 1;
	
	while (q.size()) {
		int node = q.front();
		q.pop();
		
		for (int i = 0; i < graph[node].size(); i++) {
			if (!active[node][graph[node][i]] || been[graph[node][i]]) continue;
			been[graph[node][i]] = been[node]+1;
			q.push(graph[node][i]);
		}
	}
	
	if (!been[b]) return false;
	
	path.push_back(b);
	int node = b;
	while (node != a) {
		for (int i = 0; i < graph[node].size(); i++) {
			if (been[graph[node][i]]+1 == been[node]) {
				path.push_back(graph[node][i]);
				node = graph[node][i];
				break;
			}
		}
	}
	return true;
}

void solve (vector<string>&v, map<string, int>&m) {
	cout << v.size() << endl;
	vector<pair<int, int> > edges;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			if (active[i][graph[i][j]]) continue;
			edges.push_back({min(i, graph[i][j]), max(i, graph[i][j])});
			active[i][graph[i][j]] = active[graph[i][j]][i] = true;
		}
	}
	int cnt;
	vector<int>path1, path2;
	for (int i = 0; i < edges.size(); i++) {
		///select first edge to remove
		active[edges[i].first][edges[i].second] = active[edges[i].second][edges[i].first] = false;
		///find first path
		path1.clear();
		bfs (edges[i].first, edges[i].second, path1);
		for (int j = 0; j < path1.size()-1; j++) {
			int x = path1[j];
			int y = path1[j+1];
			active[x][y] = active[y][x] = false;
		}
		///find second path
		path2.clear();
		bfs (edges[i].first, edges[i].second, path2);
		for (int j = 0; j < path2.size()-1; j++) {
			int x = path2[j];
			int y = path2[j+1];
			active[x][y] = active[y][x] = false;
		}
		///reset
		for (int j = 0; j < path2.size()-1; j++) {
			int x = path2[j];
			int y = path2[j+1];
			active[x][y] = active[y][x] = true;
		}
		for (int j = 0; j < path1.size()-1; j++) {
			int x = path1[j];
			int y = path1[j+1];
			active[x][y] = active[y][x] = true;
		}
		
		///generate all pairs of possible edge 2 and 3 ti delete
		for (int j = 0; j < path1.size()-1; j++) {
			int x = path1[j];
			int y = path1[j+1];
			active[x][y] = active[y][x] = false;
			
			for (int k = 0; k < path2.size()-1; k++) {
				int x2 = path2[k];
				int y2 = path2[k+1];
				active[x2][y2] = active[y2][x2] = false;
				
				memset (col, 0, sizeof(col));
				int cnt = 1;
				for (int l = 0; l < v.size(); l++) {
					if (!col[l]) {
						dfs (l, cnt);
						cnt++;
					}
					if (cnt > 2) break;
				}
				if (cnt == 3) {
					cout << v[x] << " " << v[y] << endl;
					cout << v[x2] << " " << v[y2] << endl;
					cout << v[edges[i].first] << " " << v[edges[i].second] << endl;
					int k1 = 0, k2 = 0;
					for (int l = 0; l < v.size(); l++) {
						if (col[l] == 1) k1++;
						if (col[l] == 2) k2++;
					}
					cout << k1 << " " << k2 << endl;
					return;
				}
				
				active[x2][y2] = active[y2][x2] = true;
			}
			active[x][y] = active[y][x] = true;
		}
		active[edges[i].first][edges[i].second] = active[edges[i].second][edges[i].first] = true;
	}
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>v;
	map<string, int>m;
	read ("input.txt", v, m);
	solve(v, m);

return 0;
}

