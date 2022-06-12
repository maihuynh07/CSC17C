/**
 * This class draw a canon on the main screen and process its operations
 */

#ifndef BALL_H
#define BALL_H
#include "Lib.h"

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
#endif /*BALL_H*/