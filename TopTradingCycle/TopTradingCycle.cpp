#include<bits/stdc++.h>

using namespace std;

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;
    vector<bool> visited;
    vector<int> cycle;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    }

    void addEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjacencyMatrix[source][destination] = 1;
        }
    }

    void removeEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjacencyMatrix[source][destination] = 0;
        }
    }

    void printGraph() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    
    void DFS(int node, vector<int>& path) {
        visited[node] = true;
        path.push_back(node);

        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            if (adjacencyMatrix[node][neighbor]) {
                if (!visited[neighbor]) {
                    DFS(neighbor, path);
                } else {
                    if (find(path.begin(), path.end(), neighbor) != path.end()) {
                        auto start = find(path.begin(), path.end(), neighbor);
                        cycle = vector<int>(start, path.end());
                    }
                }
            }
        }

        path.pop_back();
    }

    vector<int> findCycle() {
        cycle.clear();
        visited.assign(numVertices, false);

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                vector<int> path;
                DFS(i, path);

                if (!cycle.empty()) {
                    return cycle;
                }
            }
        }

        return cycle;
    }

    int getDestination(int node) {
        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            if (adjacencyMatrix[node][neighbor]) {
                return neighbor;
            }
        }
        return -1;
    }


    void removeIncominEdges(int node) {
        for (int i = 0; i < numVertices; ++i) {
            adjacencyMatrix[i][node] = 0;
        }
    }

    vector<int> getIncomingEdges(int node) {
        vector<int> incomingEdges;
        for (int i = 0; i < numVertices; ++i) {
            if (adjacencyMatrix[i][node]) {
                incomingEdges.push_back(i);
            }
        }
        return incomingEdges;
    }


};


bool searchInAVector(vector<int> vec, int item) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == item) {
            return true;
        }
    }
    return false;
}

void printVector(vector<int> vec) {
    for (auto item: vec) {
        cout << item << " ";
    }
    cout << endl;
}

bool isNotKey(vector<pair<int, int>> vec, int item) {
    for (auto pair: vec) {
        if (pair.first == item || pair.second == item) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<std::pair<int, int>> dests;
    std::vector<std::vector<int>> preferences;
    std::vector<int> nextPreference;
    int n;
    cin >> n;
    Graph graph(n);

    for (int i = 0; i < n; ++i) {
        nextPreference.push_back(0);
        std::vector<int> preference;
        for (int j = 0; j < n; ++j) {
            int dest;
            cin >> dest;
            preference.push_back(dest - 1);
        }
        preferences.push_back(preference);
    }

    for (int i = 0; i < n; ++i) {
        int source = i;
        int destination = preferences[i][nextPreference[i]];
        graph.addEdge(source, destination);
        nextPreference[i]++;
    }

    while (dests.size() != n) {
        std::vector<int> cycle = graph.findCycle();
        for (auto node: cycle) {
                int dest = graph.getDestination(node);
                dests.push_back({node, dest});
        }
        for (auto node: cycle) {
            std::vector<int> incomingEdge = graph.getIncomingEdges(node);
            for (auto edge: incomingEdge) {
                if (searchInAVector(cycle, edge)) {
                    graph.removeEdge(edge, node);
                }
                else {
                    graph.removeEdge(edge, graph.getDestination(edge));
                    while (!isNotKey( dests, preferences[edge][nextPreference[edge]] )) {
                        nextPreference[edge]++;
                    }
                    graph.addEdge(edge, preferences[edge][nextPreference[edge]]);
                    nextPreference[edge]++;
                }
            }
        }
    }

    for (auto dest: dests) {
        cout << dest.first + 1 << " Will Go To => " << dest.second + 1 << endl;
    }    
    return 0;
}




