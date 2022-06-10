#include "BinaryTree.h"
#include "data.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class Vertex {
private:
    string name;
    map<string, vector<string>> edges;
    string content;

public:

    Vertex() {
    }

    Vertex(string name, string content) {
        this->name = name;

        this->content = content;
    }

    string get_name() {
        return this->name;
    }

    map<string, vector<string>> get_edges() {
        return edges;
    }

    void set_content(string content) {
        this->content = content;
    }

    string get_content() {
        return this->content;
    }

    bool connect(Vertex *neighbor, vector<string> keywords) {

        if (this->name.compare(neighbor->get_name()) != 0) {
            if (edges.find(neighbor->get_name()) == edges.end()) {
                edges[neighbor->get_name()] = keywords;
                return true;
            }
        }

        return false;
    }
};

class GameGraph {
private:
    map<string, Vertex *> vertices;
    Vertex *current_vertex;
    BinaryTree *prof_tree;

public:

    GameGraph(BinaryTree* prof_tree) {
        this->add_vertex(Data::RCC, Data::RCC_CONTENT);

        this->add_vertex(Data::CS, Data::CS_CONTENT);
        this->add_vertex(Data::CE, Data::CE_CONTENT);

        this->add_vertex(Data::CS_NET, Data::CS_NET_CONTENT);
        this->add_vertex(Data::CS_AL_DT, Data::CS_AL_DT_CONTENT);

        this->add_vertex(Data::CE_SE, Data::CE_SE_CONTENT);
        this->add_vertex(Data::CE_CSE, Data::CE_CSE_CONTENT);

        this->add_edge(Data::RCC, Data::CS_KEYWORDS, Data::CS);
        this->add_edge(Data::RCC, Data::CE_KEYWORDS, Data::CE);

        this->add_edge(Data::CS, Data::CS_NET_KEYWORDS, Data::CS_NET);
        this->add_edge(Data::CS, Data::CS_AL_DT_KEYWORDS, Data::CS_AL_DT);

        this->add_edge(Data::CE, Data::CE_SE_KEYWORDS, Data::CE_SE);
        this->add_edge(Data::CE, Data::CE_CSE_KEYWORDS, Data::CE_CSE);

        this->prof_tree = prof_tree;
    }

    ~GameGraph() {
        for (auto &vertex : vertices) {
            delete vertex.second;
        }
    }

    bool add_vertex(string vertex_name, string content) {
        if (vertices.find(vertex_name) == vertices.end()) {
            vertices[vertex_name] = new Vertex(vertex_name, content);
            return true;
        }
        return false;
    }

    bool add_edge(string start_vertex, vector<string> keywords,
            string end_vertex) {
        if ((vertices.find(start_vertex) != vertices.end()) &&
                (vertices.find(end_vertex) != vertices.end())) {
            return vertices[start_vertex]->connect(vertices[end_vertex], keywords);
        }
        return false;
    }

    bool start() {
        current_vertex = vertices[Data::RCC];
        string message = "";

        while (current_vertex->get_edges().size() > 0) {

            cout << "\n\n" << current_vertex->get_content() << endl;
            getline(cin, message);

            process_message(message);
        }
        cout << current_vertex->get_content() << endl;

        while (true) {

            cout << Data::FINAL_OPTIONS << endl;
            getline(cin, message);

            if (message.compare("restart") == 0) {
                return true;
            }

            if (message.compare("") == 0) {
                return false;
            }
            
            transform(message.begin(), message.end(), message.begin(), ::toupper);
            Node* result = prof_tree->search(message);
            if (result != NULL) {
                cout << "Found 1 entry: " << endl;
                cout << result->getContent() << endl;
            }else{
                cout << "No entry found." << endl;
            }
        }

        return false;
    }

private:

    void process_message(string message) {
        vector<pair < Vertex *, int>> distances;

        for (auto &edge : current_vertex->get_edges()) {
            for (auto &keyword : edge.second) {
                distances.push_back({vertices[edge.first], get_levenshtein_dist(keyword, message)});
            }
        }

        sort(distances.begin(), distances.end(),
                [](const pair<Vertex *, int> &p1, const pair<Vertex *, int> &p2) {
                    return p1.second < p2.second;
                });
        current_vertex = distances[0].first;
    }

    int get_levenshtein_dist(std::string keyword, std::string message) {
        // Upper Case
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);
        transform(message.begin(), message.end(), message.begin(), ::toupper);

        if (keyword.size() == 0) {
            return message.size();
        }

        if (message.size() == 0) {
            return keyword.size();
        }

        int *costs = new int[message.size() + 1];

        for (int i = 0; i <= message.size(); i++) {
            costs[i] = i;
        }

        for (int i = 0; i < keyword.size(); i++) {
            costs[0] = i + 1;
            int corner = i;

            for (int j = 0; j < message.size(); ++j) {
                int upper = costs[j + 1];

                if (keyword[i] == message[j]) {
                    costs[j + 1] = corner;
                } else {
                    int tmp = (upper < corner ? upper : corner);
                    costs[j + 1] = (costs[j] < tmp ? costs[j] : tmp) + 1;
                }

                corner = upper;
            }
        }

        int result = costs[message.size()];
        delete[] costs;

        return result;
    }
};