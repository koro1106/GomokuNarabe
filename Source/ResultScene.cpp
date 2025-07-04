#include "ResultScene.h"
#include "Stage.h"
#include "Player.h"
#include "AI.h"
#include "Stage.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
  if(CheckHitKey(KEY_INPUT_T))
  {
	SceneManager::ChangeScene("TITLE");
  }
}

void ResultScene::Draw()
{
	DrawString(100, 400, "RESULT SCENE", GetColor(255, 255, 0));
	DrawString(500, 500, "TITLE SCENE: PUSH [T]", GetColor(255, 255, 0));
}
