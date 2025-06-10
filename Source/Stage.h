#pragma once
#include "../Library/GameObject.h"

const int HEIGHT = 15;
const int WIDTH = 15;

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Draw() override;
	void SetMapValue(int x, int y, int value);
    int Put(int x, int y, int value);
	int GetMapValue(int x, int y);
	int backGround;
	bool IsCellEmpty(int x, int y); //セルが空いてるかチェック
	bool CheckWin(int turn);
	bool isGameOver ;
	bool isTie();//引き分け判定
	bool Tie;
	int CountLine(int x, int y, int a, int b);
	void Horizontal();
};