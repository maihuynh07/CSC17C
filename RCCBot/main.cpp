#include "BinaryTree.h"
#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char const *argv[]) {

    ifstream prof_file("./rcc_professors.txt");
    string prev_line;
    string crr_line;
    BinaryTree* prof_tree = new BinaryTree();
    while (getline(prof_file, prev_line)) {
        if (getline(prof_file, crr_line)) {
            if (prev_line.compare("") == 0) {
                stringstream initials;
                initials << crr_line[0];
                for (int i = 1; i < crr_line.size(); i++) {
                    if (crr_line[i - 1] == ' ' || crr_line[i - 1] == '(') {
                        if (crr_line[i] != '(') {
                            initials << crr_line[i];
                        }
                    }
                }
                stringstream contents;
                contents << crr_line << endl;
                for (int i = 0; i < 3; i++) {
                    getline(prof_file, crr_line);
                    contents << crr_line << endl;
                }

                prof_tree->insert(initials.str(), contents.str());

            }
        }
    }
    prof_file.close();

    GameGraph *game_graph = new GameGraph(prof_tree);
    while (game_graph->start()) {
    }

    delete prof_tree;
    return 0;
}
