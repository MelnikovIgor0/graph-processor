#include <algorithm>
#include <fstream>
#include "Graph.h"
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

// Считывание способа считывания графа и самого графа.
void ReadGraph(Graph& g) {
	string stream_name;
	cin >> stream_name;
	if (stream_name == "console") {
		cin >> g;
	} else {
		ifstream fin(stream_name);
		fin >> g;
		fin.close();
	}
}

// Считывание способа вывода графа и вывод графа в указанный поток.
void WriteGraph(Graph& g) {
    string output_stream, output_type;
    cin >> output_stream >> output_type;
    if (output_stream == "console") {
        if (output_type == "am") {
            g.PrintGraphAdjacencyMatrix(cout);
        } else {
            if (output_type == "im") {
                g.PrintGraphIncidenceMatrix(cout);
            } else {
                if (output_type == "al") {
                    g.PrintGraphAdjacencyList(cout);
                } else {
                    if (output_type == "el") {
                        g.PrintGraphEdgesList(cout);
                    }
                }
            }
        }
    } else {
        ofstream file_output(output_stream);
        if (output_type == "am") {
            g.PrintGraphAdjacencyMatrix(file_output);
        } else {
            if (output_type == "im") {
                g.PrintGraphIncidenceMatrix(file_output);
            } else {
                if (output_type == "al") {
                    g.PrintGraphAdjacencyList(file_output);
                } else {
                    if (output_type == "el") {
                        g.PrintGraphEdgesList(file_output);
                    }
                }
            }
        }
        file_output.close();
    }
}

// Главный метод программы.
int main() {
	string command;
	Graph g;
	while (cin >> command) {
        if (command == "exit") {
            break;
        }
		if (command == "convert") {
            ReadGraph(g);
            WriteGraph(g);
		} else {
            if (command == "degrees") {
                ReadGraph(g);
                g.GetDegreesOfVertexes(cout);
            } else {
                if (command == "dfs") {
                    ReadGraph(g);
                    g.PrintDFSOrder(cout);
                } else {
                    if (command == "bfs") {
                        ReadGraph(g);
                        g.PrintBFSOrder(cout);
                    } else {
                        if (command == "edges") {
                            ReadGraph(g);
                            cout << g.GetAmountEdges() << endl;
                        } else {
                            cout << "command was not recognized" << endl;
                        }
                    }
                }
            }
        }
	}
	return 0;
}
