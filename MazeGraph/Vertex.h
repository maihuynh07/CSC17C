
/* 
 * File:   Vertex.h
 * Author: Thi Nguyen
 *
 * Created on June 7, 2022, 10:46 PM
 */

#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <map>

using namespace std;

class Vertex {
public:

    static enum class DIRECTIONS {
        LEFT, RIGHT, UP, DOWN
    };

private:
    string name;
    map<string, DIRECTIONS> edges;


public:

    Vertex() {
    }

    Vertex(string name) {
        this->name = name;
    }

    string get_name() {
        return this->name;
    }

    map<string, double> get_edges() {
        return edges;
    }

    bool connect(Vertex *neighbor, DIRECTIONS direction) {

        if (this->name.compare(neighbor->get_name()) != 0) {
            if (edges.find(neighbor->get_name()) == edges.end()) {
                edges[neighbor->get_name()] = direction;
                return true;
            }
        }

        return false;
    }

    string get_neighbor(DIRECTIONS direction) {
        for (auto& edge : edges) {
            if (direction == edge.second) {
                return edge.first;
            }
        }
        return "";
    }

};

#endif /* VERTEX_H */
