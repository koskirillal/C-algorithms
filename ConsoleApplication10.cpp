#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <list>
#include <iterator>
#include <string>
#include <set>
#include <stack>
#include <deque>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <map>

using namespace std;
typedef long long ll;
typedef vector <vector <int>> vv;
typedef vector <vector <char>> vvc;
typedef pair<int, int> pii;

void ccout(vector <int>& q) {
	for (auto c : q) {
		cout << c << ' ';
	}
	cout << '\n';
}
// Алгоритм дейкстры
void djikstra(vector <vector <pii>>& graph, int s, vector <int>& dist) {
    int n = graph.size();
    dist[s] = 0;
    priority_queue < pii, vector <pii>, greater<pii>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        int curdist = pq.top().first;
        int nod = pq.top().second;
        
        pq.pop();
        if (curdist > dist[nod]) {
            continue;
        }
        for (auto& ed : graph[nod]) {
            int neighbor = ed.first;
            int weight = ed.second;
            if (dist[nod] + weight < dist[neighbor]) {
                dist[neighbor] = dist[nod] + weight;
                pq.push({ dist[neighbor] , neighbor });
            }
        }
    }


}


void bfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q; 
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int nod = q.front();
        q.pop();
        for (auto adj : graph[nod]) {
            if (visited[adj] == false) {
                q.push(adj);
                visited[adj] = 1;
            }
        }

    }
}
void dfs(int nod, vector<vector<int>>& graph, vector<int>& visited , vector <int>& pr , vector <int>& path ) {
    visited[nod] = true;

    for (auto ed : graph[nod]) {
        if (visited[ed] == false) {
            pr[ed] = nod;
            path.push_back(ed+1);
            dfs(ed, graph, visited , pr ,path);
        }
        else if (pr[ed] != nod){
            visited[ed]++;
            path.push_back(ed+1);
            return;
        }
        

    }
}


//Алгоритм примо
int findmin(const vector<int>& minw, const vector<bool>& inmst, int n) {
    int mw = 2000000;
    int minver = -1;
    for (int v = 0; v < n; v++) {
        if (inmst[v] == false && minw[v] < mw) {
            mw = minw[v];
            minver = v;
        }
    }
    return minver;

}

void primMST(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector <int> minw(n, 20000000);
    vector <int> parent(n, -1);
    vector <bool > inmst(n, false);
    minw[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = findmin(minw, inmst, n);
        inmst[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !inmst[v] && graph[u][v] < minw[v]) {
                parent[v] = u;
                minw[v] = graph[u][v];
            }
        }
    }
    cout << "Ребра остовного дерева:" << endl;
    for (int i = 1; i < n; ++i) {
        cout << parent[i] << " - " << i << " : " << graph[parent[i]][i] << endl;
    }

}
// Система не перескающихся множеств
int fnd(int x , vector <int>& p) {
    if (p[x] == x) {
        return x;
    }
    else {
        return fnd(p[x] , p);
    }
}
void und(int x, int y , vector <int>& p) {
    x = fnd(x , p);
    y = fnd(y , p);
    p[y] = x;
}
// Сортировка для алгоритма крускала
struct edge {
    int from, to, weight;
};
bool cmp(edge e1, edge e2) {
    return e1.weight < e2.weight;
}

// Вещественный бинарный поиск
double binary(double x) {
    double l = 0;
    double r = 1.7976931348623157E+308;
    double exp = 0.000001;
    while (r - l > exp) {
        double mid = (l + r) / 2;
        cout << mid << '\n';
        if (x > mid) {
            l = mid;

        }
        else {
            r = mid;
        }
    }
    return l;
}
//Тернарный поиск
double f(double a) {
    return a * a + a - 2;
}
double ternary() {
    double l = -1000;
    double r = 1000;
    double exp = 0.000001;
    while (r - l > exp) {
        double a = (l * 2 + r) / 3;
        double b = (r * 2 + l) / 3;
        if (f(a) < f(b)) {
            r = b;
        }
        else {
            l = a;
        }
    }
    return (l + r) / 2;
}

//Quick sort
vector <int> summa(vector <int> l, int mid, vector <int> r) {
    vector <int> ans(l.size() + 1 + r.size());
    for (int i = 0; i < l.size(); i++) {
        ans[i] = l[i];
    }
    ans[l.size()] = mid;
    for (int i = 0; i < r.size(); i++) {
        ans[l.size() + 1 + i] = r[i];
    }
    return ans;
}

vector <int> qsort(vector <int>& q) {
    if (q.size() <= 1) {
        return q;
    }
    else if (q.size() == 2) {
        if (q[1] < q[0]) {
            swap(q[0], q[1]);
        }
        return q;
    }
    int mid = q[0];
    vector <int> l;
    vector <int> r;
    for (int i = 1; i < q.size(); i++) {
        if (q[i] <= mid) {
            l.push_back(q[i]);
        }
        else {
            r.push_back(q[i]);
        }
    }
    return summa(qsort(l), mid, qsort(r));
}


int main() {
    
    vector <int> q = { 1 , 2 , 3 , 4 , 5 };
    q = qsort(q);
    ccout(q);
    return 0;
}


