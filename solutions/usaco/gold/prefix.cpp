#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge {
    int to;
    long long length;
};

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<long long>& dist) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            long long len = edge.length;
            if (dist[u] + len < dist[v]) {
                dist[v] = dist[u] + len;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int N, M, C, R, K;
    cin >> N >> M >> C >> R >> K;

    vector<vector<Edge>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v;
        long long l;
        cin >> u >> v >> l;
        graph[u].push_back({v, l});
        graph[v].push_back({u, l});
    }

    vector<vector<long long>> dist(C + 1, vector<long long>(N + 1, INF));

    for (int i = 1; i <= C; ++i) {
        dijkstra(i, graph, dist[i]);
    }

    vector<int> well_connected;

    for (int i = C + 1; i <= N; ++i) {
        int count = 0;
        for (int j = 1; j <= C; ++j) {
            if (dist[j][i] <= R) {
                ++count;
            }
        }
        if (count >= K) {
            well_connected.push_back(i);
        }
    }

    cout << well_connected.size() << endl;
    for (int dest : well_connected) {
        cout << dest << endl;
    }

    return 0;
}