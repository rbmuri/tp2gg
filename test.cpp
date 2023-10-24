#include <bits/stdc++.h>

using namespace std;

struct conex {
    int year;
    int dist;
    string name;
    conex(int d, int y, string n){
        dist = d;
        year = y;
        name = n;
    }
};

class compareconexdist{
    public:
    bool operator()(const conex& a, const conex& b) {
        if (a.dist == b.dist)
            return a.year > b.year;
        else
            return a.dist > b.dist; 
    }
};

int main(){
    priority_queue<conex, vector<conex>, compareconexdist> q;
    q.push(conex(1, 2, "AE"));
    q.push(conex(3, 1, "CB"));
    q.push(conex(4, 1, "DC"));
    q.push(conex(2, 1, "BA"));
    q.push(conex(5, 1, "FD"));
    q.push(conex(4, 2, "EF"));
    while (!q.empty()){
        cout << q.top().name << endl;
        q.pop();
    }
    return 0;
};