#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	bool isPlayerTurn;
	int gridOriginX = 450;//盤面左上X座標
	int gridOriginY = 100;//盤面左上Y座標
	int cellSize = 50;//マスサイズ
private:
	int MouseX, MouseY;
	bool prevButton; //前のボタンの状態
	bool PlayerWin;
	
};
