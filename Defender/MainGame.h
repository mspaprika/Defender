#pragma once

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;


// Sprites
const char* SPR_CAT = "ghost_cat_right";
const char* SPR_FLEA = "bug_up";

const char* SPR_BALL_RED = "red_m";
const char* SPR_BALL_BLUE = "blue_m";
const char* SPR_BALL_OCEAN = "ocean_m";
const char* SPR_BALL_GREEN = "green_m";
const char* SPR_BALL_YELLOW = "yellow_dark_m";
const char* SPR_BALL_PURPLE = "pink_m";

const char* BALLS[6] = { SPR_BALL_RED, SPR_BALL_BLUE, SPR_BALL_OCEAN, SPR_BALL_GREEN, SPR_BALL_YELLOW, SPR_BALL_PURPLE };


enum GameObjectType
{
	TYPE_CAT,
	TYPE_FLEA,
	TYPE_BALL,
	TYPE_DESTROYED
};

enum GameFlow
{
	STATE_PLAY,
	STATE_GAMEOVER,
	STATE_PAUSE,
	STATE_LOBBY,
	STATE_WIN,
};

struct GameState
{
	int score{ 0 };
	int lives{ 3 };
	int level{ 1 };

	GameFlow state{ STATE_PLAY };
};

struct Player
{

};

struct Flea
{

};


// Functions
void Draw();
void DrawObjects(int TYPE);
void CreateGameObjects();
void UpdateDestroyed();
void UpdateGameStates();
void PlayerControls();
void UpdateCat();
void UpdateFleas();
void UpdateBalls();
void SetFleaDirection(GameObject& flea);