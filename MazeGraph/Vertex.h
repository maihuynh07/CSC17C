/*
 * File:   Vertex.h
 * Author: Thi Nguyen
 *
 * Created on June 7, 2022, 10:46 PM
 */

#ifndef VERTEX_H
#define VERTEX_H
#include <map>
#include <string>

using namespace std;
class Vertex {
public:
  static const int EAST = 0;
  static const int WEST = 1;
  static const int NORTH = 2;
  static const int SOUTH = 3;

private:
  string name;
  map<string, int> edges;

public:
  Vertex() {}

  Vertex(string name) { this->name = name; }

  string get_name() { return this->name; }

  map<string, int> get_edges() { return edges; }

  bool connect(Vertex *neighbor, int direction) {

    if (this->name.compare(neighbor->get_name()) != 0) {
      if (edges.find(neighbor->get_name()) == edges.end()) {
        edges[neighbor->get_name()] = direction;
        return true;
      }
    }

    return false;
  }

  string get_neighbor(int direction) {
    for (auto &edge : edges) {
      if (direction == edge.second) {
        return edge.first;
      }
    }
    return "";
  }
};

#endif /* VERTEX_H */