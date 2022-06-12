#include "Ball.h"
#include "MazeGraph.h"
#include "Maze.h"
#include <time.h>

using namespace std;


/**
 * The main process
 */
int main(int argc, char *args[]) {
  srand(time(NULL));
  new Maze();
  return 0;
}
