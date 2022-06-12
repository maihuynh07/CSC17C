#ifndef LIB_H
#define LIB_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
/**
 * The Game Name
 */
const string GAME_NAME = "Maze Graph";

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

#endif /*LIB_H*/