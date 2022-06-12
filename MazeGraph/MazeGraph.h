/*
 * File:   MazeGraph.h
 * Author: Thi Nguyen
 *
 * Created on June 7, 2022, 10:47 PM
 */

#ifndef MAZEGRAPH_H
#define MAZEGRAPH_H

#include <iostream>
#include <string>

#include "Vertex.h"

using namespace std;

class MazeGraph {
private:
  map<string, Vertex *> vertices;
  Vertex *current_vertex;

public:
  MazeGraph() {}

  ~MazeGraph() {
    for (auto &vertex : vertices) {
      delete vertex.second;
    }
  }

  bool add_vertex(string vertex_name) {
    if (vertices.find(vertex_name) == vertices.end()) {
      vertices[vertex_name] = new Vertex(vertex_name);
      return true;
    }

    return false;
  }

  bool add_edge(string start_vertex, int direction, string end_vertex) {
    if ((vertices.find(start_vertex) != vertices.end()) &&
        (vertices.find(end_vertex) != vertices.end())) {
      return vertices[start_vertex]->connect(vertices[end_vertex], direction);
    }
    return false;
  }

  Vertex *get_neighbor(int direction) {
    string result = current_vertex->get_neighbor(direction);

    if (result.compare("") == 0) {
      return NULL;
    }

    current_vertex = vertices[result];
    return current_vertex;
  }

  void set_current_vertex(string vertex_id) {
    current_vertex = vertices[vertex_id];
  }

  void clear() {
    for (auto &vertex : vertices) {
      delete vertex.second;
    }
    vertices.clear();
  }
};

#endif /* MAZEGRAPH_H */