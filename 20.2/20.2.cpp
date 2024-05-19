#include <bits/stdc++.h>

using namespace std;
#define lli long long int

struct module {
	string name;
	int type = 0;
	bool on = false;
	int mask = 0;
	int insNum = 0;
	
	friend bool operator < (module a, module b) {
		return a.name < b.name;
	}
};

string getName (string line) {
	string pom = "";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ') break;
		if (line[i] != '%' && line[i] != '&') pom += line[i];
	} 
	return pom;
}

void parseVector(string line, vector<pair<string, int> >&v, map<string, module> &temp, map<pair<string, string>, int> &inputs) {
	string pom = getName(line);
	int pos = 0;
	if (line[0] == '%' || line[0] == '&') pos = 1;
	pos += pom.size()+4;
	string curr = "";
	line += ",";
	module mod;
	for (int i = pos; i < line.size(); i++) {
		if (line[i] == ',') {
			if (temp.count(curr)) {
				if (temp[curr].type == 1) {
					inputs[{curr, pom}] = temp[curr].insNum;
					temp[curr].insNum++;
				}
				v.push_back({curr, 0});
			}
			else {
				module mod;
				mod.name = curr;
				mod.type = 0;
				temp[curr] = mod;
				v.push_back({curr, 0});
			}
			curr = "";
			i++;
			continue;
		}
		curr += line[i];
	}
	return;
}

void read (string name, map<string, vector<pair<string, int> > >&graph, map<string, module> &temp, map<pair<string, string>, int> &inputs) {
	fstream file;
	file.open(name, ios::in);
	string line;
	vector<string>lines;
	
	module mod;
	
	while (getline(file, line)) {
		lines.push_back(line);
		
		string name = getName(line);
		mod.name = name;
		if (line[0] == '%') mod.type = -1;
		else if (line[0] == '&') mod.type = 1;
		else mod.type = 0;
		temp[name] = mod;
	}
	
	for (int i = 0; i < lines.size(); i++) {
		vector<pair<string, int> >v;
		string name = getName(lines[i]);
		parseVector(lines[i], v, temp, inputs);
		graph[name] = v;
	}
	file.close();
}

int sol[2];

bool sendLow (map<string, vector<pair<string, int> > >&graph, map<string, module> &temp, map<pair<string, string>, int> &inputs) {
	queue<pair<string, int> >q;
	q.push({"broadcaster", 0});
	
	bool ret = false;
	
	while (q.size()) {
		string node = q.front().first;
		int impuls = q.front().second;
		sol[impuls]++;
		q.pop();
		//cout << node << " " << impuls << endl;
		//system("pause");
		
		if (node == "bh" && impuls == 0) ret = true;
		
		if (temp[node].type == -1) { //flip module
			if (impuls == 1) continue;
			impuls = !temp[node].on;
			temp[node].on = !temp[node].on;
		}
		if (temp[node].type == 1) { //conjecture module
			//cout << node.mask << " " << node.insNum <<endl;
			if (temp[node].mask == (1<<temp[node].insNum)-1) impuls = 0;
			else impuls = 1;
		}
		for (int i = 0; i < graph[node].size(); i++) {
			string sus = graph[node][i].first;
			if (temp[sus].type == -1 || temp[sus].type == 0) { //if flip module
				q.push({sus, impuls});
				continue;
			}
			if (temp[sus].type == 1) {
				int mask = inputs[{sus, node}];
				mask = (1<<mask);
				if (impuls == 0) {
					if (temp[sus].mask & mask) temp[sus].mask -= mask;
				}
				else {
					if (!(temp[sus].mask & mask)) temp[sus].mask += mask;
				}
				//cout << sus.name << " " << sus.insNum << " " << sus.mask << endl;
				q.push({sus, impuls});
			}
		}
	}
	return ret;
}

void dfs (string node, map<string, vector<pair<string, int> > >&graph, map<string, bool>&been, map<string, module>&temp) {
	if (been[node]) return;
	been[node] = true;
	cout << node << " " << temp[node].type << endl;
	for (int i = 0; i < graph[node].size(); i++) {
		cout << graph[node][i].first << ", ";
	}
	cout << endl;
	system("pause");
	for (int i = 0; i < graph[node].size(); i++) {
		dfs (graph[node][i].first, graph, been, temp);
	}
	return;
}

void solve (map<string, vector<pair<string, int> > >&graph, map<string, module>&temp, map<pair<string, string>, int> &inputs) {
	int cnt = 0;
	/*for (auto it = graph.begin(); it != graph.end(); it++) {
		cout  << ++cnt << " " << (it->first) << ": ";
		for (int j = 0; j < (it->second).size(); j++) {
			cout << (it->second)[j].first << " ";
		}
		cout << endl;
	}*/
	map<string, bool>been;
	//dfs ("broadcaster", graph, been, temp);
	int i = 1;
	while (i++ != 50000) {
		if (sendLow(graph, temp, inputs)) {
			cout << i << endl;
		}
		//system("pause");
	}
	///IDEJA: ispisi si koliko je potrebno koraka da ovi prije mf postignu 0 (to su sh, jf, bh i mz) jer su oni & i mf je &;
	///ugl dobit ces periodicno i onda opet LCM :)
	cout << sol[0] * sol[1] << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    map<string, vector<pair<string, int> > >graph;
    map<string, module>temp;
    map<pair<string, string>, int> inputs;
    read("input.txt", graph, temp, inputs);
	solve(graph, temp, inputs);

return 0;
}

