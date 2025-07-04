#include "TitleScene.h"

TitleScene::TitleScene()
{
	TitleImage = LoadGraph("data/image/title.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (prevButton == false) {
			GetMousePoint(&mouseX, &mouseY);
			//マウスがスタートボタン内にいるか判定
			if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
				mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
				SceneManager::ChangeScene("PLAY");
			}
		}
		prevButton = true;
	}
	else {
		prevButton = false;
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawGraph(0, 0, TitleImage, TRUE);

	//Debug
	//DrawCircle(buttonX, buttonY, 10, GetColor(0, 255, 255), 1);
	//DrawCircle(buttonWidth + buttonX, buttonHeight + buttonY, 10, GetColor(0, 255, 255), 1);
	//DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
