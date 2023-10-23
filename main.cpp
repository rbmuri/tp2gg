#include <bits/stdc++.h>

using namespace std;

struct conex {
    int a;
    int b;
    int year;
    int time;
    int cost;
    int mindist;

    conex(int o, int d, int y, int t, int c){
        a = o;
        b = d;
        year = y;
        time = t;
        cost = c;
        mindist = t;
    }
    conex(){
        b = 0;
        year = 0;
        time = 0;
        cost = 0;
        mindist = 0;
    }
};

struct subset {
    int parent;
    int rank;
};

struct compareconexdist{
    bool operator()(const conex& a, const conex& b) {
        return a.mindist > b.mindist; 
    }
};
struct compareconexcost{
    bool operator()(const conex& a, const conex& b) {
        return a.cost > b.cost; 
    }
};
struct compareconexyear{
    bool operator()(const conex& a, const conex& b) {
        return a.year > b.year; 
    }
};

int kruskal(priority_queue<conex, vector<conex>, compareconexyear> edges, int v){
    vector<vector<conex>> g(v);
    int visited[v] = {0};

    while(true){
        conex c = edges.top();
        edges.pop();
        if (visited[c.a] == 1 && visited[c.b] == 1) continue;
        
    }
    

}

int prim(){

}

vector<int> djikstra(vector<vector<conex>> g){
    priority_queue<conex, vector<conex>, compareconexdist> q;
    int v = g.size();
    vector<int> answ(v);
    answ[0] = 0;
    int year = 0;
    int i = 0;
    conex nextnode;
    while(true){
        for (int j = 0; j < g[i].size(); j++){
            g[i][j].mindist += g[i][j].a;
            q.push(g[i][j]);
        }
        while (true){
            nextnode = q.top();
            q.pop();
            if (answ[nextnode.b] == 0) break;
            if (q.empty()) break;
        }
        if (q.empty()) break;
        i = nextnode.b;       
        if (nextnode.year > year) year = nextnode.year;
        answ[i] = answ[nextnode.a] + nextnode.time;        
    }
    answ[0] = year;
    return answ;
}

int mintree(){

}

int main(){
    int v, e;
    int firstyear;
    int fymintree;
    int mincost;

    cin >> v >> e;
    vector<vector<conex>> g(v);
    priority_queue<conex, vector<conex>, compareconexyear> eyear;
    priority_queue<conex, vector<conex>, compareconexcost> ecost;

    for (int i = 0; i<e; i++){
        int a, b, y, t, c;
        cin >> a >> b >> y >> t >> c;
        conex ab(a-1, b-1, y, t, c);
        conex ba(a-1, b-1, y, t, c);

        g[a-1].push_back(ab);
        g[b-1].push_back(ba);
        eyear.push(ab);
        eyear.push(ba);
        ecost.push(ab);
        ecost.push(ba);
    }
    
    cout << "BREAK\n";
    vector<int> mintime = djikstra(g);
    firstyear = mintime[0];
    mintime[0] = 0;
    cout << "BREAK\n";
    for (int i = 0; i < v; i++){
        cout << mintime[i] << "\n";
    }
    cout << firstyear << "\n";
    cout << fymintree << "\n";
    cout << mincost << "\n";

    return 0;
};