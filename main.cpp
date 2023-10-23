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
    void inverse(){
        int temp = a;
        a = b;
        b = temp;
    }
};

struct subset {
    int parent;
    int rank;
};

int find(vector<int> parents, int index){
    if (parents[index] == index) return index;
    else return find(parents, parents[index]);
}
void unite(vector<int> &parents, int i1, int i2){
    int i = find(parents, i2);
    parents[i] = i1;
    return;
}

struct compareconexdist{
    bool operator()(const conex& a, const conex& b) {
        if (a.mindist == b.mindist){

            cout << "compared " << a.year << " > " << b.year << "\n";
            cout << "in " << a.a+1 << "-" << a.b+1 << " and "
                 << b.a+1 << "-" << b.b+1 << "\n";
            return a.year > b.year;
            }
        else
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

int kruskalyear(priority_queue<conex, vector<conex>, compareconexyear> edges, int v){
    vector<vector<conex>> g(v);
    vector<int> parents(v);
    int loop = 1;
    for (int i = 0; i<v; i++)
        parents[i] = i;


    conex c, answ;
    while(loop < v){
        c = edges.top();
        edges.pop();
        if (find(parents, c.a) != find(parents, c.b)) {
            unite(parents, c.a, c.b);
            loop++;
            g[c.a].push_back(c);
            c.inverse();
            g[c.a].push_back(c);
            answ = c;
        }
        
    }
    return answ.year;
}

int kruskalcost(priority_queue<conex, vector<conex>, compareconexcost> edges, int v){
    vector<vector<conex>> g(v);
    vector<int> parents(v);
    int loop = 1;
    for (int i = 0; i<v; i++)
        parents[i] = i;

    int cost = 0;
    conex c;
    while(loop < v){
        c = edges.top();
        edges.pop();
        if (find(parents, c.a) != find(parents, c.b)) {
            unite(parents, c.a, c.b);
            loop++;
            g[c.a].push_back(c);
            c.inverse();
            g[c.a].push_back(c);
            cost += c.cost;
        }
        
    }
    return cost;
}

vector<int> djikstra(vector<vector<conex>> &g){
    priority_queue<conex, vector<conex>, compareconexdist> q;
    int v = g.size();
    vector<int> answ(v);
    answ[0] = 0;
    int year = 0;
    int i = 0;
    conex nextnode;
    for (int h = 1; h<v; h++){
        for (int j = 0; j < g[i].size(); j++){
            g[i][j].mindist += g[i][j].a;
            q.push(g[i][j]);
        }
        while (true){
            nextnode = q.top();
            q.pop();
            if (answ[nextnode.b] == 0 && nextnode.b != 0) break;
            cout << "edge " << nextnode.a+1 << "-" << nextnode.b+1 << " refused.\n";
            if (q.empty()) break;
        }
        i = nextnode.b;       
        if (nextnode.year > year) year = nextnode.year;
        answ[i] = answ[nextnode.a] + nextnode.time;   
        cout << "found shortest path " << answ[i] << " from "
        << nextnode.a+1 << " to " << nextnode.b+1 << endl;    
    }
    answ[0] = year;
    return answ;
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
        conex ba(b-1, a-1, y, t, c);

        g[a-1].push_back(ab);
        g[b-1].push_back(ba);
        eyear.push(ab);
        //eyear.push(ba);
        ecost.push(ab);
        //ecost.push(ba);
    }
    
    vector<int> mintime = djikstra(g);
    firstyear = mintime[0];
    mintime[0] = 0;

    fymintree = kruskalyear(eyear, v);
    mincost = kruskalcost(ecost, v);
    for (int i = 0; i < v; i++){
        cout << mintime[i] << "\n";
    }
    cout << firstyear << "\n";
    cout << fymintree << "\n";
    cout << mincost << "\n";

    return 0;
};