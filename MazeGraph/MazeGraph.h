
/*
 * File:   Graph.h
 * Author: Thi Nguyen
 *
 * Created on June 7, 2022, 10:47 PM
 */

#ifndef MAZEGRAPH_H
#define MAZEGRAPH_H

#include <string>

#include "Vertex.h"

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

  bool add_edge(string start_vertex, Vertex::DIRECTIONS direction,
                string end_vertex) {
    if ((vertices.find(start_vertex) != vertices.end()) &&
        (vertices.find(end_vertex) != vertices.end())) {
      return vertices[start_vertex]->connect(vertices[end_vertex], direction);
    }
    return false;
  }

  Vertex *get_neighbor(Vertex::DIRECTIONS direction) {
    string result = current_vertex->get_neighbor(direction);

    if (result.compare("") == 0) {
      return NULL;
    }

    return vertices[result];
  }

  void load_maze(string file_name) {
    for (auto &vertex : vertices) {
      delete vertex.second;
    }
    vertices.clear();
  }
};

#endif /* MAZEGRAPH_H */
