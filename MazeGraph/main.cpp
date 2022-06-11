#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

/**
 * The Game Name
 */
const string GAME_NAME = "Maze Running";

/**
 * The Ball image
 */
const string BALL_FILE_NAME = "ball.png";

/**
 * The Ball move sound
 */
const string MOVE_SOUND_FILE_NAME = "move.wav";

/**
 * The Bar hit sound
 */
const string HIT_SOUND_FILE_NAME = "hit.wav";

/**
 * The winning music
 */
const string WIN_MUSIC_FILE_NAME = "win.wav";

/**
 * The background color
 */
const int BACKGROUND_COLOR = 0xD0;

/**
 * The color of a maze bar
 */
const int BAR_COLOR = 0x0D;

/**
 * Number Zero
 */
const int ZERO = 0;

/**
 * The error index
 */
const int ERROR = -1;

/**
 *Screen width max
 */
const int SCREEN_WIDTH = 650;

/**
 *Screen height max
 */
const int SCREEN_HEIGHT = 500;

/**
 * The current number of mazes
 */
const int MAX_MAZE_FILE = 2;

/**
 * The array of all maze file names
 */
const string MAZE_FILE_NAMES[MAX_MAZE_FILE] = {"maze.dat", "maze1.dat"};

/**
 * The maze will be changed after this period of time
 */
const Uint32 TIME_GAP = 3000;

/**
 * This class draw a canon on the main screen and process its operations
 */
class Ball {
public:
  /*
   * The width/height of a ball
   */
  static const int BALL_SIZE = 50;

private:
  /*
   * The initial Y position of a ball on the main screen
   */
  const int BALL_ON_Y = (SCREEN_HEIGHT - BALL_SIZE);

  /*
   * The current position of a ball
   */
  SDL_Point *currentBallPosition = NULL;

  /*
   * The winning position
   */
  SDL_Point *winningPosition = NULL;

  /*
   * The reference to the window render of the main screen
   */
  SDL_Renderer *ballWindowRender = NULL;

  // The actual hardware texture
  SDL_Texture *ballTexture = NULL;

private:
  /**
   * Load the picture of a ball
   */
  void loadBallImage() {
    // Load canon image at the same folder
    SDL_Surface *loadedSurface = IMG_Load(BALL_FILE_NAME.c_str());

    if (loadedSurface == NULL) {
      cout << "Unable to load image " << BALL_FILE_NAME
           << "! SDL_image Error: " << IMG_GetError() << endl;
    } else {

      // Color key image
      SDL_SetColorKey(loadedSurface, SDL_TRUE,
                      SDL_MapRGB(loadedSurface->format, ZERO, BACKGROUND_COLOR,
                                 BACKGROUND_COLOR));

      // Create texture from surface pixels
      ballTexture =
          SDL_CreateTextureFromSurface(ballWindowRender, loadedSurface);

      if (ballTexture == NULL) {
        cout << "Unable to create texture from " << BALL_FILE_NAME
             << "! SDL Error: " << SDL_GetError() << endl;
      }

      // Get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
    }
  }

  /**
   * Erase the old ball on the screen
   */
  void eraseOldBall() {

    // Set rendering space and render to screen
    // Erase only the space inside a maze square
    SDL_Rect renderQuad = {currentBallPosition->x + 1,
                           currentBallPosition->y + 1, BALL_SIZE - 1,
                           BALL_SIZE - 1};

    // Clear a ball in the main screen
    SDL_RenderFillRect(ballWindowRender, &renderQuad);

    // Update the screen
    SDL_RenderPresent(ballWindowRender);
  }

public:
  /**
   * The default constructor
   */
  Ball() {}

  /**
   * The customized constructor
   */
  Ball(SDL_Renderer *windowRender, SDL_Point *ballLocationOnMaze) {
    ballWindowRender = windowRender;
    loadBallImage();

    currentBallPosition = new SDL_Point;
    currentBallPosition->x = ballLocationOnMaze->x * BALL_SIZE;
    currentBallPosition->y = BALL_ON_Y;

    winningPosition = new SDL_Point;
    winningPosition->x = ballLocationOnMaze->y * BALL_SIZE;
    winningPosition->y = ZERO;
  }

  /**
   * The destructor
   */
  ~Ball() {
    if (ballTexture != NULL) {
      SDL_DestroyTexture(ballTexture);
      ballTexture = NULL;
      delete currentBallPosition;
    }
  }

  /**
   * Draw a ball on the main screen
   */
  void renderNewBall() {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {currentBallPosition->x + 1,
                           currentBallPosition->y + 1, BALL_SIZE - 1,
                           BALL_SIZE - 1};

    // Render a ball to the main screen
    SDL_RenderCopyEx(ballWindowRender, ballTexture, NULL, &renderQuad, ZERO,
                     NULL, SDL_FLIP_NONE);

    // Update the screen
    SDL_RenderPresent(ballWindowRender);
  }

  /**
   * Draw a win ball on the main screen
   */
  void renderWinBallPosition() {

    // Set new color for the window render
    SDL_SetRenderDrawColor(ballWindowRender, BACKGROUND_COLOR, BACKGROUND_COLOR,
                           ZERO, ZERO);

    for (int index = 2; index < BALL_SIZE; index += 3) {
      // Set rendering space and render to screen
      SDL_Rect renderQuad = {winningPosition->x + index,
                             winningPosition->y + index, BALL_SIZE - index,
                             BALL_SIZE - index};

      // Clear a ball in the main screen
      SDL_RenderDrawRect(ballWindowRender, &renderQuad);
    }

    // Update the screen
    SDL_RenderPresent(ballWindowRender);

    // Set back the old color for the window render
    SDL_SetRenderDrawColor(ballWindowRender, BACKGROUND_COLOR, BACKGROUND_COLOR,
                           BACKGROUND_COLOR, BACKGROUND_COLOR);
  }

  /**
   * Move the ball to the left
   */
  void moveLeft(SDL_Renderer *windowRender) {
    if (currentBallPosition->x >= BALL_SIZE) {
      eraseOldBall();
      currentBallPosition->x -= BALL_SIZE;
      SDL_RenderPresent(windowRender);
      renderWinBallPosition();
      SDL_RenderPresent(windowRender);
      renderNewBall();
    }
  }

  /**
   * Move the canon to the right
   */
  void moveRight(SDL_Renderer *windowRender) {
    if ((currentBallPosition->x + BALL_SIZE) < SCREEN_WIDTH) {
      eraseOldBall();
      currentBallPosition->x += BALL_SIZE;
      SDL_RenderPresent(windowRender);
      renderWinBallPosition();
      SDL_RenderPresent(windowRender);
      renderNewBall();
    }
  }

  /**
   * Move the canon to the right
   */
  void moveUp(SDL_Renderer *windowRender) {
    if (currentBallPosition->y >= BALL_SIZE) {
      eraseOldBall();
      currentBallPosition->y -= BALL_SIZE;
      SDL_RenderPresent(windowRender);
      renderWinBallPosition();
      SDL_RenderPresent(windowRender);
      renderNewBall();
    }
  }

  /**
   * Move the canon to the right
   */
  void moveDown(SDL_Renderer *windowRender) {
    if ((currentBallPosition->y + BALL_SIZE) < SCREEN_HEIGHT) {
      eraseOldBall();
      currentBallPosition->y += BALL_SIZE;
      SDL_RenderPresent(windowRender);
      renderWinBallPosition();
      SDL_RenderPresent(windowRender);
      renderNewBall();
    }
  }

  /**
   *  Get the maze square position from the ball graphic position
   */
  void getBallPositionInMaze(int &rowIndex, int &colIndex) {
    rowIndex = currentBallPosition->y / BALL_SIZE;
    colIndex = currentBallPosition->x / BALL_SIZE;
  }

  /**
   * Check if the ball reached the winning position
   */
  bool isGameOver() {
    if ((currentBallPosition->x == winningPosition->x) &&
        (currentBallPosition->y == winningPosition->y)) {
      return true;
    }
    return false;
  }

  /**
   * Update the winning position in a new maze
   */
  void updateWinningPostion(int positionOnX) {
    winningPosition->x = positionOnX * BALL_SIZE;
  }
};

/**
 * This class defines the main screen for the mini game
 */
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

        ((mask & logicValue) == mask)
            ? (mazeSquares[rowIndex][colIndex].isDownBarOn = true)
            : (mazeSquares[rowIndex][colIndex].isDownBarOn = false);

        logicValue >>= 1;
        ((mask & logicValue) == mask)
            ? (mazeSquares[rowIndex][colIndex].isUpBarOn = true)
            : (mazeSquares[rowIndex][colIndex].isUpBarOn = false);

        logicValue >>= 1;
        ((mask & logicValue) == mask)
            ? (mazeSquares[rowIndex][colIndex].isRightBarOn = true)
            : (mazeSquares[rowIndex][colIndex].isRightBarOn = false);

        logicValue >>= 1;
        ((mask & logicValue) == mask)
            ? (mazeSquares[rowIndex][colIndex].isLeftBarOn = true)
            : (mazeSquares[rowIndex][colIndex].isLeftBarOn = false);
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
      // Load media
      if (!loadMedia()) {
        cout << "Failed to load media!\n";
      } else {
        int rowIndex;

        int colIndex;

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
                // Located the ball position in the Maze
                ball->getBallPositionInMaze(rowIndex, colIndex);

                switch (e.key.keysym.sym) {
                case SDLK_LEFT: {
                  // Check if the left side is opened
                  if (!mazeSquares[rowIndex][colIndex].isLeftBarOn) {
                    ball->moveLeft(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                case SDLK_RIGHT: {
                  // Check if the right side is opened
                  if (!mazeSquares[rowIndex][colIndex].isRightBarOn) {
                    ball->moveRight(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                case SDLK_UP: {
                  // Check if the up side is opened
                  if (!mazeSquares[rowIndex][colIndex].isUpBarOn) {
                    ball->moveUp(windowRenderer);
                    Mix_PlayChannel(ERROR, moveSound, ZERO);

                  } else {
                    Mix_PlayChannel(ERROR, hitSound, ZERO);
                  }

                  break;
                }
                case SDLK_DOWN: {
                  // Check if the down side is opened
                  if (!mazeSquares[rowIndex][colIndex].isDownBarOn) {
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
                    "Maze Running: Congratulation! You are the winner!!!");
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
  }
};

/**
 * The main process
 */
int main(int argc, char *args[]) {
  srand(time(NULL));
  new Maze();
  return 0;
}
