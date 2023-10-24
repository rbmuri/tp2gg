#include <bits/stdc++.h>

#define ll long long int

using namespace std;

struct conex {
    ll a;
    ll b;
    ll year;
    ll time;
    ll cost;
    ll mindist;

    conex(ll o, ll d, ll y, ll t, ll c){
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
        ll temp = a;
        a = b;
        b = temp;
    }
    void printn(){
        cout << a << "-" << b << " (y="
        << year << ", t=" << time <<
        ", c=" << cost << ", md=" << mindist
        << ")\n";
    }
    void print(){
        cout << a << "-" << b << " (y="
        << year << ", t=" << time <<
        ", c=" << cost << ", md=" << mindist
        << ")";
    }
};

struct unionfind {
    vector<ll> parents;
    vector<ll> rank;
    unionfind(ll size){
        for (int i = 0; i < size; i++){
            parents.push_back(i);
            rank.push_back(1);
            }
    }

    ll find(ll index){
        if (parents[index] == index) 
            return index;
        else 
            return find(parents[index]);
    }
    void unite(ll a, ll b){
        ll ia = find(a);
        ll ib = find(b);
        if (rank[ia] > rank[ib]){
            parents[ib] = ia;
            rank[ia] += rank[ib];
            }
        else{
            parents[ia] = ib;
            rank[ib] += rank[ia];
        }
    }
};

struct compareconexdist{
    bool operator()(const conex& a, const conex& b) {
        if (a.mindist == b.mindist)
             return a.year > b.year;
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

ll kruskalyear(priority_queue<conex, vector<conex>, compareconexyear> edges, ll v){
    vector<vector<conex>> g(v);
    unionfind un(v);
    ll loop = 1;
    conex c, answ;

    while(loop < v){
        c = edges.top();
        edges.pop();
        if (un.find(c.a) != un.find(c.b)) {
            un.unite(c.a, c.b);
            loop++;
            g[c.a].push_back(c);
            c.inverse();
            g[c.a].push_back(c);
            answ = c;
        }
    }
    return answ.year;
}

ll kruskalcost(priority_queue<conex, vector<conex>, compareconexcost> edges, ll v){
    vector<vector<conex>> g(v);
    unionfind un(v);
    ll loop = 1;
    ll cost = 0;
    conex c;

    while(loop < v){
        c = edges.top();
        edges.pop();
        if (un.find(c.a) != un.find(c.b)) {
            un.unite(c.a, c.b);
            loop++;
            g[c.a].push_back(c);
            c.inverse();
            g[c.a].push_back(c);
            cost += c.cost;
        }       
    }
    return cost;
}

vector<ll> djikstra(vector<vector<conex>> &g){
    priority_queue<conex, vector<conex>, compareconexdist> q;
    ll v = g.size();
    vector<ll> answ(v);
    answ[0] = 0;
    ll year = 0;
    ll i = 0;
    conex nextnode;
    

    for (ll h = 1; h<v; h++){ //loops v-1 times
        //for each edge
        for (ll j = 0; j < g[i].size(); j++){ 
            //calculate distance from v1 to it
            g[i][j].mindist += answ[g[i][j].a];
            q.push(g[i][j]);
        }
        while (true){
            nextnode = q.top();
            q.pop();
            //when an unvisited vertice is found, 
            //break and calculate distance
            if (answ[nextnode.b] == 0 && nextnode.b != 0) break;
            if (q.empty()) break;
        }
        i = nextnode.b;       
        if (nextnode.year > year) year = nextnode.year;
        //answ is distance from v1 to each vertice
        answ[i] = answ[nextnode.a] + nextnode.time;  
    }
    answ[0] = year;
    return answ;
}

int main(){
    ll v, e;
    ll firstyear;
    ll fymintree;
    ll mincost;
    FILE *in = fopen("t1.txt", "r");
    //cin >> v >> e;
    fscanf(in, "%lld %lld", &v, &e);
    vector<vector<conex>> g(v);
    priority_queue<conex, vector<conex>, compareconexyear> eyear;
    priority_queue<conex, vector<conex>, compareconexcost> ecost;

    for (ll i = 0; i<e; i++){
        ll a, b, y, t, c;
        //cin >> a >> b >> y >> t >> c;
        fscanf(in, "%lld %lld %lld %lld %lld", &a, &b, &y, &t, &c);
        conex ab(a-1, b-1, y, t, c);
        conex ba(b-1, a-1, y, t, c);

        g[a-1].push_back(ab);
        g[b-1].push_back(ba);
        eyear.push(ab);
        //eyear.push(ba);
        ecost.push(ab);
        //ecost.push(ba);
    }

    clock_t kruskal_start = clock();
    fymintree = kruskalyear(eyear, v);
    mincost = kruskalcost(ecost, v);
    clock_t kruskal_end = clock();
    double kruskal_duration = static_cast<double>(kruskal_end - kruskal_start) / CLOCKS_PER_SEC;

    clock_t dijkstra_start = clock();
    vector<ll> mintime = djikstra(g); 
    clock_t dijkstra_end = clock();
    double dijkstra_duration = static_cast<double>(dijkstra_end - dijkstra_start) / CLOCKS_PER_SEC;
    
    firstyear = mintime[0];
    mintime[0] = 0;

    for (ll i = 0; i < v; i++){
        cout << mintime[i] << "\n";
    }
    cout << firstyear << "\n";
    cout << fymintree << "\n";
    cout << mincost << "\n";

    cout << "kruskal: " << kruskal_duration << endl;
    cout << "djikstra: " << dijkstra_duration << endl;

    return 0;
};