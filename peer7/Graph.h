#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

#ifndef PEER7_GRAPH_H
#define PEER7_GRAPH_H

// Класс графа.
struct Graph {
    // Представление графа в разных формах.
    vector<vector<ll>> adjacency_matrix;
    vector<vector<ll>> incidence_matrix;
    vector<vector<ll>> adjacency_list;
    vector<pair<ll, ll>> edges_list;
    // Число вершин в графе.
    size_t number_vertexes = 0;

    // Чтение графа в виде матрицы смежности.
    istream& ReadGraphFromAdjacencyMatrix(istream& in) {
        size_t graph_size;
        in >> graph_size;
        number_vertexes = graph_size;
        adjacency_matrix.assign(graph_size, vector<ll>(graph_size, 0));
        for (size_t i = 0; i < graph_size; i++) {
            for (size_t j = 0; j < graph_size; j++) {
                in >> adjacency_matrix[i][j];
            }
        }
        return in;
    }

    // Чтение графа в виде матрицы инциндентностей.
    istream& ReadGraphFromIncidenceMatrix(istream& in) {
        size_t number_edges;
        in >> number_vertexes >> number_edges;
        incidence_matrix.assign(number_vertexes, vector<ll>(number_edges, 0));
        for (size_t i = 0; i < number_vertexes; i++) {
            for (size_t j = 0; j < number_edges; j++) {
                in >> incidence_matrix[i][j];
            }
        }
        return in;
    }

    // Чтение графа в виде списка смежности.
    istream& ReadGraphFromAdjacencyList(istream& in) {
        in >> number_vertexes;
        adjacency_list.assign(number_vertexes, vector<ll>(0, 0));
        for (size_t i = 0; i < adjacency_list.size(); i++) {
            size_t amount;
            in >> amount;
            adjacency_list[i].resize(amount);
            for (size_t j = 0; j < amount; j++) {
                in >> adjacency_list[i][j];
                --adjacency_list[i][j];
            }
            sort(adjacency_list[i].begin(), adjacency_list[i].end());
        }
        return in;
    }

    // Чтение графа в виде списка ребер.
    istream& ReadGraphFromEdgesList(istream& in) {
        size_t number_edges;
        in >> number_vertexes >> number_edges;
        edges_list.assign(number_edges, make_pair(-1, -1));
        for (size_t i = 0; i < number_edges; i++) {
            in >> edges_list[i].first >> edges_list[i].second;
            --edges_list[i].first;
            --edges_list[i].second;
        }
        sort(edges_list.begin(), edges_list.end());
        return in;
    }

    // Получение графа в виде матрицы инцидентностей из списка ребер.
    void UpdateFromELtoIM() {
        ll max_vertex_number = number_vertexes;
        incidence_matrix.resize(max_vertex_number);
        for (size_t edge_num = 0; edge_num < edges_list.size(); edge_num++) {
            for (size_t vertex = 0; vertex < incidence_matrix.size(); vertex++) {
                incidence_matrix[vertex].push_back(0);
            }
            incidence_matrix[edges_list[edge_num].first].back() = 1;
            incidence_matrix[edges_list[edge_num].second].back() = -1;
        }
    }

    // Получение графа в виде списка ребер из матрицы инциндентностей.
    void UpdateFromIMtoAL() {
        adjacency_list.resize(incidence_matrix.size());
        size_t amount_edges = 0;
        if (incidence_matrix.size() > 0) {
            amount_edges = incidence_matrix[0].size();
        }
        for (size_t edge_number = 0; edge_number < amount_edges; edge_number++) {
            vector<ll> nodes_of_vertex;
            for (size_t vertex = 0; vertex < incidence_matrix.size(); vertex++) {
                if (incidence_matrix[vertex][edge_number] != 0) {
                    nodes_of_vertex.push_back(vertex);
                }
            }
            if (incidence_matrix[nodes_of_vertex[0]][edge_number] <
                incidence_matrix[nodes_of_vertex[1]][edge_number]) {
                swap(nodes_of_vertex[0], nodes_of_vertex[1]);
            }
            adjacency_list[nodes_of_vertex[0]].push_back(nodes_of_vertex[1]);
            if (incidence_matrix[nodes_of_vertex[0]][edge_number] ==
                incidence_matrix[nodes_of_vertex[1]][edge_number]) {
                adjacency_list[nodes_of_vertex[1]].push_back(nodes_of_vertex[0]);
            }
        }
        for (size_t i = 0; i < adjacency_list.size(); i++) {
            sort(adjacency_list[i].begin(), adjacency_list[i].end());
        }
    }

    // Получение графа в виде матрицы смежности из списка смежности.
    void UpdateFromALtoAM() {
        adjacency_matrix.assign(adjacency_list.size(), vector<ll>(adjacency_list.size(), 0));
        for (size_t vertex = 0; vertex < adjacency_matrix.size(); vertex++) {
            for (ll neighbor_vertex : adjacency_list[vertex]) {
                adjacency_matrix[vertex][neighbor_vertex] = 1;
            }
        }
    }

    // Получение графа в виде списка ребер из матрицы смежности.
    void UpdateFromAMtoEL() {
        for (size_t vertex1 = 0; vertex1 < adjacency_matrix.size(); vertex1++) {
            for (size_t vertex2 = 0; vertex2 < adjacency_matrix.size(); vertex2++) {
                if (adjacency_matrix[vertex1][vertex2]) {
                    edges_list.push_back(make_pair(vertex1, vertex2));
                }
            }
        }
        sort(edges_list.begin(), edges_list.end());
        edges_list.resize(unique(edges_list.begin(), edges_list.end()) - edges_list.begin());
    }

    // Перегрузка ввода графа.
    friend istream& operator>>(istream& in, Graph& g) {
        string graph_type;
        in >> graph_type;
        bool correct_type = true;
        if (graph_type == "am") {
            g.ReadGraphFromAdjacencyMatrix(in);
            g.UpdateFromAMtoEL();
            g.UpdateFromELtoIM();
            g.UpdateFromIMtoAL();
        } else {
            if (graph_type == "im") {
                g.ReadGraphFromIncidenceMatrix(in);
                g.UpdateFromIMtoAL();
                g.UpdateFromALtoAM();
                g.UpdateFromAMtoEL();
            } else {
                if (graph_type == "al") {
                    g.ReadGraphFromAdjacencyList(in);
                    g.UpdateFromALtoAM();
                    g.UpdateFromAMtoEL();
                    g.UpdateFromELtoIM();
                } else {
                    if (graph_type == "el") {
                        g.ReadGraphFromEdgesList(in);
                        g.UpdateFromELtoIM();
                        g.UpdateFromIMtoAL();
                        g.UpdateFromALtoAM();
                    }
                }
            }
        }
        return in;
    }

    // Вывод графа в виде матрицы смежности.
    void PrintGraphAdjacencyMatrix(ostream& out) {
        out << "am" << endl;
        out << adjacency_matrix.size() << endl;
        for (size_t i = 0; i < adjacency_matrix.size(); i++) {
            for (size_t j = 0; j < adjacency_matrix[i].size(); j++) {
                out << adjacency_matrix[i][j] << ' ';
            }
            out << endl;
        }
        out.flush();
    }

    // Вывод графа в виде матрицы инцидентностей.
    void PrintGraphIncidenceMatrix(ostream& out) {
        out << "im" << endl;
        out << incidence_matrix.size() << ' ';
        if (incidence_matrix.size() == 0) {
            out << "0" << endl;
        } else {
            out << incidence_matrix[0].size() << endl;
        }
        for (size_t i = 0; i < incidence_matrix.size(); i++) {
            for (size_t j = 0; j < incidence_matrix[i].size(); j++) {
                out << incidence_matrix[i][j] << ' ';
            }
            out << endl;
        }
        out.flush();
    }

    // Вывод графа в виде списка смежности.
    void PrintGraphAdjacencyList(ostream& out) {
        out << "al" << endl;
        out << adjacency_list.size() << endl;
        for (size_t i = 0; i < adjacency_list.size(); i++) {
            out << adjacency_list[i].size() << ' ';
            for (ll vertex : adjacency_list[i]) out << vertex + 1 << ' ';
            out << endl;
        }
        out.flush();
    }

    // Вывод графа в виде списка ребер.
    void PrintGraphEdgesList(ostream& out) {
        out << "el" << endl;
        out << number_vertexes << ' ' << edges_list.size() << endl;
        for (pair<ll, ll> p : edges_list) {
            out << p.first + 1 << ' ' << p.second + 1 << endl;
        }
        out.flush();
    }

    // Вывод степеней вершин графа.
    void GetDegreesOfVertexes(ostream& out) {
        bool oriented = true;
        for (size_t i = 0; i < adjacency_matrix.size(); i++) {
            for (size_t j = 0; j < adjacency_matrix[i].size(); j++) {
                if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
                    oriented = false;
                }
            }
        }
        if (oriented) {
            out << "degrees: ";
            for (size_t vertex = 0; vertex < adjacency_list.size(); vertex++) {
                out << adjacency_list[vertex].size() << ' ';
            }
            out << endl;
            out.flush();
        } else {
            out << "indegree: ";
            for (size_t vertex = 0; vertex < adjacency_matrix.size(); vertex++) {
                size_t degree = 0;
                for (size_t neighbor = 0; neighbor < adjacency_matrix.size(); neighbor++) {
                    degree += adjacency_matrix[neighbor][vertex];
                }
                out << degree << ' ';
            }
            out << endl << "outdegree: ";
            for (size_t vertex = 0; vertex < adjacency_matrix.size(); vertex++) {
                size_t degree = 0;
                for (size_t neighbor = 0; neighbor < adjacency_matrix.size(); neighbor++) {
                    degree += adjacency_matrix[vertex][neighbor];
                }
                out << degree << ' ';
            }
            out << endl;
            out.flush();
        }
    }

    // Получение количества ребер в графе (если граф ориентированный, то дуг, иначе именно ребер).
    ll GetAmountEdges() {
        set<pair<ll, ll>> unique_edges;
        for (pair<ll, ll> p : edges_list) {
            unique_edges.insert(make_pair(min(p.first, p.second), max(p.first, p.second)));
        }
        if (unique_edges.size() * 2 == edges_list.size()) {
            return unique_edges.size();
        }
        return edges_list.size();
    }

    // DFS рекурсивной реализации.
    void DFSRec(ll vertex, vector<bool>& used, vector<ll>& order) {
        order.push_back(vertex);
        used[vertex] = true;
        for (ll neighbor : adjacency_list[vertex]) {
            if (!used[neighbor]) {
                DFSRec(neighbor, used, order);
            }
        }
    }

    // DFS нерекурсивной реализации.
    void DFSNonRec(ll vertex, vector<bool>& used, vector<ll>& order) {
        vector<ll> stak = { vertex };
        used[vertex] = true;
        order.push_back(vertex);
        while (!stak.empty()) {
            ll good_vertex = -1;
            for (ll neighbor : adjacency_list[stak.back()]) {
                if (!used[neighbor]) {
                    good_vertex = neighbor;
                    break;
                }
            }
            if (good_vertex == -1) {
                stak.pop_back();
            } else {
                stak.push_back(good_vertex);
                used[good_vertex] = true;
                order.push_back(good_vertex);
            }
        }
    }

    // Вывод порядка вершин в обходе DFS.
    void PrintDFSOrder(ostream& out) {
        vector<bool> used(adjacency_matrix.size(), false);
        vector<ll> order;
        for (size_t vertex = 0; vertex < adjacency_matrix.size(); vertex++) {
            if (!used[vertex]) {
                DFSRec(vertex, used, order);
            }
        }
        out << "recursive: ";
        for (ll vertex : order) {
            out << vertex + 1 << ' ';
        }
        out << endl << "non recursive: ";
        used.assign(adjacency_matrix.size(), false);
        order.clear();
        for (size_t vertex = 0; vertex < adjacency_matrix.size(); vertex++) {
            if (!used[vertex]) {
                DFSNonRec(vertex, used, order);
            }
        }
        for (ll vertex : order) {
            out << vertex + 1 << ' ';
        }
        out << endl;
        out.flush();
    }

    // Реализация BFS на графе.
    void BFS(ll vertex, vector<bool>& used, vector<ll>& order) {
        used[vertex] = true;
        order.push_back(vertex);
        queue<ll> q;
        q.push(vertex);
        while (!q.empty()) {
            vertex = q.front();
            q.pop();
            for (ll neighbor : adjacency_list[vertex]) {
                if (!used[neighbor]) {
                    q.push(neighbor);
                    order.push_back(neighbor);
                    used[neighbor] = true;
                }
            }
        }
    }

    // Вывод порядка вершин в порядке обхода BFS.
    void PrintBFSOrder(ostream& out) {
        vector<bool> used(adjacency_matrix.size(), false);
        vector<ll> order;
        for (size_t vertex = 0; vertex < used.size(); vertex++) {
            if (!used[vertex]) {
                BFS(vertex, used, order);
            }
        }
        for (ll vertex : order) {
            out << vertex + 1 << ' ';
        }
        out << endl;
        out.flush();
    }
};

#endif
