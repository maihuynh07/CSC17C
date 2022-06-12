/**
 * This class defines the main screen for the mini game
 */

#ifndef MAZE_H
#define MAZE_H
#include "Lib.h"
class Maze {

private:
  /*
   * The number of rows in a maze
   */
  static const int MAZE_ROW = SCREEN_HEIGHT / Ball::BALL_SIZE;

  /*
   * The number of cols in a maze
   */
  static const int MAZE_COL = SCREEN_WIDTH / Ball::BALL_SIZE;

  /*
   *The main window
   */
  SDL_Window *mainWindow = NULL;

  /*
   *The main window renderer
   */
  SDL_Renderer *windowRenderer = NULL;

  /*
   * The sound of a moving ball
   */
  Mix_Chunk *moveSound = NULL;

  /*
   * The sound created when the ball hit a bar
   */
  Mix_Chunk *hitSound = NULL;

  // The winning music
  Mix_Music *winningMusic = NULL;

  /**
   * The structure of a square in the maze
   */
  typedef struct MAZE_SQUARE {

    /*
     * Check to draw left bar
     */
    bool isLeftBarOn;

    /*
     * Check to draw right bar
     */
    bool isRightBarOn;

    /*
     * Check to draw up bar
     */
    bool isUpBarOn;

    /*
     * Check to draw down bar
     */
    bool isDownBarOn;
  } MazeSquare;

  /**
   *The Maze database
   */
  MazeSquare mazeSquares[MAZE_ROW][MAZE_COL];

  /**
   * x: The initiated position of the ball on X-axis in the maze
   * y: The winning position on X-axis in the maze
   */
  SDL_Point *ballLocationOnMaze;

  /**
   *The Ball class
   */
  Ball *ball;

  /**
   * A representation of the Maze keeps tracking of valid movements of the Ball
   */
  MazeGraph *mazeGraph;

private:
  /**
   *Starts up SDL and creates window
   */
  bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < ZERO) {
      cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
      return false;
    } else {
      // Set texture filtering to linear
      if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        cout << "Warning: Linear texture filtering not enabled!";
      }

      // Create window
      mainWindow = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (mainWindow == NULL) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError()
             << endl;
        return false;
      } else {
        // Create a renderer for the window
        windowRenderer = SDL_CreateRenderer(mainWindow, -1,
                                            SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
        if (windowRenderer == NULL) {
          cout << "Renderer could not be created! SDL Error: " << SDL_GetError()
               << endl;

          return false;
        } else {
          // Initialize renderer color
          SDL_SetRenderDrawColor(windowRenderer, BACKGROUND_COLOR,
                                 BACKGROUND_COLOR, BACKGROUND_COLOR,
                                 BACKGROUND_COLOR);

          // Initialize PNG loading
          int imgFlags = IMG_INIT_PNG;
          if (!(IMG_Init(imgFlags) & imgFlags)) {
            cout << "SDL_image could not initialize! SDL_image Error: "
                 << IMG_GetError() << endl;
            return false;
          }

          // Initialize SDL_mixer
          if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            cout << "SDL_mixer could not initialize! SDL_mixer Error: "
                 << Mix_GetError() << endl;
            return false;
          }
        }
      }
    }

    return true;
  }

  /**
   * This function is used for loading a Maze File
   * @param fileName
   * @return true if the file is loaded successful
   */
  bool loadMazeFile(string fileName) {

    ifstream loadFile(fileName.c_str());

    if (!loadFile) {
      return false;
    }

    int rowIndex;
    int colIndex;

    string crr_vertex;
    string adj_vertex;

    // A number will represent left, right, up, and down bar
    // Exmple a byte: x x x x x x x x
    //                        L R U D
    int logicValue;
    int mask = 0x01;

    ballLocationOnMaze = new SDL_Point;

    if (!(loadFile >> ballLocationOnMaze->x)) {
      return false;
    }

    if (!(loadFile >> ballLocationOnMaze->y)) {
      return false;
    }

    for (rowIndex = 0; rowIndex < MAZE_ROW; rowIndex++) {
      for (colIndex = 0; colIndex < MAZE_COL; colIndex++) {

        if (!(loadFile >> logicValue)) {
          return false;
        }

        crr_vertex = to_string(rowIndex) + to_string(colIndex);
        mazeGraph->add_vertex(crr_vertex);

        if ((mask & logicValue) == mask) {
          mazeSquares[rowIndex][colIndex].isDownBarOn = true;
        } else {
          mazeSquares[rowIndex][colIndex].isDownBarOn = false;

          if (rowIndex + 1 < MAZE_ROW) {
            adj_vertex = to_string(rowIndex + 1) + to_string(colIndex);
            mazeGraph->add_vertex(adj_vertex);
            mazeGraph->add_edge(crr_vertex, Vertex::SOUTH, adj_vertex);
            mazeGraph->add_edge(adj_vertex, Vertex::NORTH, crr_vertex);
          }
        }

        logicValue >>= 1;
        if ((mask & logicValue) == mask) {
          mazeSquares[rowIndex][colIndex].isUpBarOn = true;
        } else {
          mazeSquares[rowIndex][colIndex].isUpBarOn = false;

          if (rowIndex - 1 > -1) {
            adj_vertex = to_string(rowIndex - 1) + to_string(colIndex);
            mazeGraph->add_vertex(adj_vertex);
            mazeGraph->add_edge(crr_vertex, Vertex::NORTH, adj_vertex);
            mazeGraph->add_edge(adj_vertex, Vertex::SOUTH, crr_vertex);
          }
        }

        logicValue >>= 1;
        if ((mask & logicValue) == mask) {
          mazeSquares[rowIndex][colIndex].isRightBarOn = true;
        } else {
          mazeSquares[rowIndex][colIndex].isRightBarOn = false;

          if (colIndex + 1 < MAZE_COL) {
            adj_vertex = to_string(rowIndex) + to_string(colIndex + 1);
            mazeGraph->add_vertex(adj_vertex);
            mazeGraph->add_edge(crr_vertex, Vertex::WEST, adj_vertex);
            mazeGraph->add_edge(adj_vertex, Vertex::EAST, crr_vertex);
          }
        }

        logicValue >>= 1;
        if ((mask & logicValue) == mask) {
          mazeSquares[rowIndex][colIndex].isLeftBarOn = true;
        } else {
          mazeSquares[rowIndex][colIndex].isLeftBarOn = false;
          if (colIndex - 1 > -1) {
            adj_vertex = to_string(rowIndex) + to_string(colIndex - 1);
            mazeGraph->add_vertex(adj_vertex);
            mazeGraph->add_edge(crr_vertex, Vertex::EAST, adj_vertex);
            mazeGraph->add_edge(adj_vertex, Vertex::WEST, crr_vertex);
          }
        }
      }
    }

    loadFile.close();

    return true;
  }

  /**
   * Set up the maze of a new game
   */
  bool initMaze() {

    if ((rand() % MAX_MAZE_FILE) == ZERO) {
      return loadMazeFile(MAZE_FILE_NAMES[ZERO]);
    } else {
      return loadMazeFile(MAZE_FILE_NAMES[1]);
    }
  }

  // Loads media
  bool loadMedia() {

    if (!initMaze()) {
      cout << "Failed to load the maze!\n";
      return false;
    }

    ball = new Ball(windowRenderer, ballLocationOnMaze);

    if (ball == NULL) {
      cout << "Failed to load the ball texture!\n";
      return false;
    }

    int x, y;
    ball->getBallPositionInMaze(x, y);
    mazeGraph->set_current_vertex(to_string(x) + to_string(y));

    // Load sound effects
    hitSound = Mix_LoadWAV(HIT_SOUND_FILE_NAME.c_str());
    if (hitSound == NULL) {
      cout << "Failed to load scratch sound effect! SDL_mixer Error: "
           << Mix_GetError() << endl;
      return false;
    }

    moveSound = Mix_LoadWAV(MOVE_SOUND_FILE_NAME.c_str());
    if (moveSound == NULL) {
      cout << "Failed to load high sound effect! SDL_mixer Error: "
           << Mix_GetError() << endl;
      return false;
    }

    // Load music
    winningMusic = Mix_LoadMUS(WIN_MUSIC_FILE_NAME.c_str());
    if (winningMusic == NULL) {
      cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError()
           << endl;
      return false;
    }

    return true;
  }

  /**
   * Render the maze
   */
  void drawLoadedMaze() {

    int rowIndex;
    int colIndex;

    int x;
    int y;

    // Set new color for bars
    SDL_SetRenderDrawColor(windowRenderer, BAR_COLOR, BAR_COLOR, BAR_COLOR,
                           BAR_COLOR);

    // Draws bars
    for (rowIndex = 0; rowIndex < MAZE_ROW; rowIndex++) {
      for (colIndex = 0; colIndex < MAZE_COL; colIndex++) {
        x = Ball::BALL_SIZE * colIndex;
        y = Ball::BALL_SIZE * rowIndex;

        // Draw the left bar of a maze square
        if (mazeSquares[rowIndex][colIndex].isLeftBarOn) {
          SDL_RenderDrawLine(windowRenderer, x, y, x, (y + Ball::BALL_SIZE));
        }

        // Draw the right bar of a maze square
        if (mazeSquares[rowIndex][colIndex].isRightBarOn) {
          SDL_RenderDrawLine(windowRenderer, (x + Ball::BALL_SIZE), y,
                             (x + Ball::BALL_SIZE), (y + Ball::BALL_SIZE));
        }

        // Draw the up bar of a maze square
        if (mazeSquares[rowIndex][colIndex].isUpBarOn) {
          SDL_RenderDrawLine(windowRenderer, x, y, (x + Ball::BALL_SIZE), y);
        }

        // Draw the down bar of a maze square
        if (mazeSquares[rowIndex][colIndex].isDownBarOn) {
          SDL_RenderDrawLine(windowRenderer, x, (y + Ball::BALL_SIZE),
                             (x + Ball::BALL_SIZE), (y + Ball::BALL_SIZE));
        }
      }
    }

    // Update bars to the main screen
    SDL_RenderPresent(windowRenderer);

    // Get back to background color for other tasks
    SDL_SetRenderDrawColor(windowRenderer, BACKGROUND_COLOR, BACKGROUND_COLOR,
                           BACKGROUND_COLOR, BACKGROUND_COLOR);
  }

  /**
   * Change to new a maze
   */
  void switchMaze() {

    mazeGraph->clear();

    initMaze();

    // Clear the main screen
    SDL_RenderClear(windowRenderer);

    // Draw a new maze
    drawLoadedMaze();

    // Update new winning position
    ball->updateWinningPostion(ballLocationOnMaze->y);
    ball->renderWinBallPosition();

    // Draw the ball at the old position
    ball->renderNewBall();

    int x, y;
    ball->getBallPositionInMaze(x, y);
    mazeGraph->set_current_vertex(to_string(x) + to_string(y));
  }

public:
  /**
   * The Space constructor
   */
  Maze() {
    // Start up SDL and create window
    if (!init()) {
      cout << "Failed to initialize!\n";
    } else {

      // Graph Initialization
      mazeGraph = new MazeGraph();

      // Load media
      if (!loadMedia()) {
        cout << "Failed to load media!\n";
      } else {

        Uint32 startTimer = SDL_GetTicks();

        // Main loop flag
        bool quit = false;

        // Event handler
        SDL_Event e;

        // Initialized the main screen
        SDL_SetRenderDrawColor(windowRenderer, BACKGROUND_COLOR,
                               BACKGROUND_COLOR, BACKGROUND_COLOR,
                               BACKGROUND_COLOR);
        SDL_RenderClear(windowRenderer);

        // Render the maze
        drawLoadedMaze();

        // Render the goal
        ball->renderWinBallPosition();

        // Render the ball
        ball->renderNewBall();

        // While application is running
        while (!quit) {

          // Handle events on queue
          while (SDL_PollEvent(&e) != ZERO) {

            // User requests quit
            if (e.type == SDL_QUIT) {
              quit = true;
            } else if (e.type == SDL_KEYDOWN) {

              if (!ball->isGameOver()) // Lock the ball if a game was over
              {

                switch (e.key.keysym.sym) {
                case SDLK_LEFT: {
                  // Check if the left side is opened
                  if (mazeGraph->get_neighbor(Vertex::EAST) != NULL) {
                    ball->moveLeft(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                case SDLK_RIGHT: {
                  // Check if the right side is opened
                  if (mazeGraph->get_neighbor(Vertex::WEST) != NULL) {
                    ball->moveRight(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                case SDLK_UP: {
                  // Check if the up side is opened
                  if (mazeGraph->get_neighbor(Vertex::NORTH) != NULL) {
                    ball->moveUp(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                case SDLK_DOWN: {
                  // Check if the down side is opened
                  if (mazeGraph->get_neighbor(Vertex::SOUTH) != NULL) {
                    ball->moveDown(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                default:

                  break;
                }

                // Switch the maze after TIME_GAP
                if ((SDL_GetTicks() - startTimer) > TIME_GAP) {
                  switchMaze();
                  startTimer = SDL_GetTicks();
                }
              }

              // Check if game is over again after a new move
              if (ball->isGameOver()) {
                // Play the music
                Mix_PlayMusic(winningMusic, ERROR);
                SDL_SetWindowTitle(
                    mainWindow,
                    "Maze Graph: Congratulation! You are the Winner!!!");
              }
            }
          }
        }
      }
    }
  }

  /**
   * The destructor: Frees media and shuts down SDL
   */
  ~Maze() {
    // Destroy window
    SDL_DestroyRenderer(windowRenderer);
    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
    windowRenderer = NULL;

    // Destroy the sound effects
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(hitSound);
    moveSound = NULL;
    hitSound = NULL;

    // Free the music
    Mix_FreeMusic(winningMusic);
    winningMusic = NULL;

    // Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    // Destroy the ball position
    ballLocationOnMaze = NULL;

    // Graph deallocation
    delete mazeGraph;
  }
};
#endif /*MAZE_H*/