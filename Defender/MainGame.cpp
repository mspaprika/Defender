#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "MainGame.h"


GameState gState;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	//Play::LoadBackground("Data//Backgrounds//background.png");
	CreateGameObjects();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	UpdateGameStates();
	Draw();

	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}


// Main game functions
void CreateGameObjects()
{
	int id = Play::CreateGameObject(TYPE_CAT, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, 25, SPR_CAT);
	Play::GetGameObject(id).animSpeed = 0.1f;
	Play::GetGameObject(id).scale = 2.f;
}

void PlayerControls()
{
	GameObject& objCat = Play::GetGameObjectByType(TYPE_CAT);

	if (Play::KeyDown(VK_LEFT)) objCat.rotation -= Play::DegToRad(5.f);
	if (Play::KeyDown(VK_RIGHT)) objCat.rotation += Play::DegToRad(5.f);

	if (Play::KeyPressed(VK_SPACE))
	{	
		int id = Play::CreateGameObject(TYPE_BALL, objCat.pos, 25, BALLS[Play::RandomRollRange(0, 5)]);
		GameObject& objBall = Play::GetGameObject(id);
		objBall.rotSpeed = 0.3f;
		Play::SetGameObjectDirection(objBall, 3, objCat.rotation);		
	}
}

void GenerateFleas()
{
	std::vector <int> vFleas = Play::CollectGameObjectIDsByType(TYPE_FLEA);
	if (vFleas.size() < 5)
	{
		int id = Play::CreateGameObject(TYPE_FLEA, { Play::RandomRollRange(0, DISPLAY_WIDTH), Play::RandomRollRange(0, DISPLAY_HEIGHT) }, 25, SPR_FLEA);
		
		GameObject& objFlea = Play::GetGameObject(id);
		objFlea.scale = 0.5f;
		objFlea.animSpeed = 0.1f;
		SetFleaDirection(objFlea);	
	}
}

void SetFleaDirection(GameObject& flea)
{
	GameObject& objCat = Play::GetGameObjectByType(TYPE_CAT);
	Play::PointGameObject(flea, 1, objCat.pos.x, objCat.pos.y);
}


// Draw functions
void Draw()
{
	Play::ClearDrawingBuffer(Play::cGrey);

	DrawObjects(TYPE_FLEA);
	DrawObjects(TYPE_BALL);
	DrawObjects(TYPE_CAT);
	
	Play::PresentDrawingBuffer();
}

void DrawObjects(int TYPE)
{
	std::vector <int> vObjects = Play::CollectGameObjectIDsByType(TYPE);
	for (int id : vObjects) Play::DrawObjectRotated(Play::GetGameObject(id));
}


// Update functions
void UpdateGameStates()
{
	switch (gState.state)
	{
		case STATE_PLAY:
		{
			PlayerControls();
			GenerateFleas();
			UpdateCat();
			UpdateFleas();
			UpdateBalls();
			break;
		}
		case STATE_GAMEOVER:
		{
			break;
		}
		case STATE_PAUSE:
		{
			break;
		}
		case STATE_LOBBY:
		{
			break;
		}
		case STATE_WIN:
		{
			break;
		}
	}
}

void UpdateCat()
{
	GameObject& objCat = Play::GetGameObjectByType(TYPE_CAT);

	Play::UpdateGameObject(objCat);
}

void UpdateDestroyed()
{
	std::vector <int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
	for (int id : vDestroyed) Play::DestroyGameObject(id);
}

void UpdateFleas()
{
	std::vector <int> vFleas = Play::CollectGameObjectIDsByType(TYPE_FLEA);
	for (int id : vFleas) Play::UpdateGameObject(Play::GetGameObject(id));

}

void UpdateBalls()
{
	std::vector <int> vBalls = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int id : vBalls) Play::UpdateGameObject(Play::GetGameObject(id));
}





