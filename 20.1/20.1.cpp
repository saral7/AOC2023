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

void parseVector(string line, vector<pair<module, int> >&v, map<string, module> &temp, map<pair<module, module>, int> &inputs) {
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
					inputs[{temp[curr], temp[pom]}] = temp[curr].insNum;
					temp[curr].insNum++;
				}
				v.push_back({temp[curr], 0});
			}
			else {
				module mod;
				mod.name = curr;
				mod.type = 0;
				v.push_back({mod, 0});
			}
			curr = "";
			i++;
			continue;
		}
		curr += line[i];
	}
	return;
}

void read (string name, map<module, vector<pair<module, int> > >&graph, map<string, module> &temp, map<pair<module, module>, int> &inputs) {
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
		vector<pair<module, int> >v;
		string name = getName(lines[i]);
		parseVector(lines[i], v, temp, inputs);
		graph[temp[name]] = v;
	}
	file.close();
}

int sol[2];

void sendLow (map<module, vector<pair<module, int> > >&graph, map<string, module> &temp, map<pair<module, module>, int> &inputs) {
	queue<pair<module, int> >q;
	q.push({temp["broadcaster"], 0});
	
	while (q.size()) {
		module node = q.front().first;
		int impuls = q.front().second;
		sol[impuls]++;
		q.pop();
		cout << node.name << " " << impuls << endl;
		system("pause");
		
		if (node.type == -1) { //flip module
			if (impuls == 1) continue;
			impuls = !node.on;
			node.on = !node.on;
		}
		if (node.type == 1) { //conjecture module
			//cout << node.mask << " " << node.insNum <<endl;
			if (node.mask == (1<<node.insNum)-1) impuls = 0;
			else impuls = 1;
		}
		
		for (int i = 0; i < graph[node].size(); i++) {
			module sus = graph[node][i].first;
			if (sus.type == -1 || sus.type == 0) { //if flip module
				q.push({sus, impuls});
				continue;
			}
			if (sus.type == 1) {
				int mask = inputs[{sus, node}];
				mask = (1<<mask);
				if (impuls == 0) {
					if (sus.mask & mask) sus.mask -= mask;
				}
				else {
					if (!(sus.mask & mask)) sus.mask += mask;
				}
				//cout << sus.name << " " << sus.insNum << " " << sus.mask << endl;
				q.push({sus, impuls});
			}
			graph[node][i].first = sus;
		}
	}
}

void solve (map<module, vector<pair<module, int> > >&graph, map<string, module>&temp, map<pair<module, module>, int> &inputs) {
	for (auto it = graph.begin(); it != graph.end(); it++) {
		cout << "current: " << (it->first).name << " type: " << (it->first).type << " " << (it->first).insNum << endl;
		for (int j = 0; j < (it->second).size(); j++) {
			cout << (it->second)[j].first.name << " ";
		}
		cout << endl;
	}
	sendLow(graph, temp, inputs);
	cout << sol[0] << " " << sol[1] << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    map<module, vector<pair<module, int> > >graph;
    map<string, module>temp;
    map<pair<module, module>, int> inputs;
    read("input2.txt", graph, temp, inputs);
	solve(graph, temp, inputs);

return 0;
}

