#include "PlayScene.h"
#include "Player.h"
#include "AI.h"


PlayScene::PlayScene()
{
	
	new Stage();
	new Player();
	new AI();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	
	int offsetX = 450;
	int offsetY = 100;
	for (int x = 0; x < 16; x++) {
		//縦
		DrawLine(50 * x + offsetX, offsetY, 50 * x + offsetX, 850, GetColor(0, 0, 250));
		//横
		DrawLine(offsetX, 50 * x + offsetY, 1200, 50 * x + offsetY, GetColor(0, 0, 250));
	}
	
}
