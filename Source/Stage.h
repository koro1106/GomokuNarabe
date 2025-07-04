#pragma once
#include "../Library/GameObject.h"

const int HEIGHT = 15;
const int WIDTH = 15;

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Draw() override;
	void Update() override;
	void SetMapValue(int x, int y, int value);//マップにPlayerかAIか置く
	int GetMapValue(int x, int y);//コマ取得
    int Put(int x, int y, int value);
	bool IsCellEmpty(int x, int y); //セルが空いてるかチェック
	bool CheckWin(int turn);
	bool isGameOver ;
	bool isTie();//引き分け判定
	bool Tie;
	int CountLine(int x, int y, int dx, int dy, int turn);
	       //(x,y)は並んでいるか調べ始める位置
	       //(dx,dy)は、並んでいる方向を入れる(dx=xに足す値、dy=yに足す値)
	       //turnは、調べてるコマがどっちなのか（PlayerかAIの)をみる
private:
	int backGround = LoadGraph("data/image/backGround.png");
	int playerGraph = LoadGraph("data/image/player.png");
	int aiGraph = LoadGraph("data/image/AI.png");
};