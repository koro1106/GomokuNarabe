#include "Player.h"
#include"Stage.h"
#include "AI.h"
#include <iostream>
using namespace std;

Player::Player()
{
	isPlayerTurn = true;
	PlayerWin = false;
	
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* st = FindGameObject<Stage>();

	if (st->isGameOver) return;

	if (st->Tie) return;

	if (!isPlayerTurn) return;

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (prevButton == false) {
			GetMousePoint(&MouseX, &MouseY);
			
		   int x = (MouseX - gridOriginX) / cellSize;
		   int y = (MouseY - gridOriginY) / cellSize;

			//押したマスが空いているかチェック
		   if (x >= 0 && x < 15 && y >= 0 && y < 15) {
			   if (st->IsCellEmpty(x, y)) {
				   st->Put(x, y, 1);//プレイヤーのターンでコマを置く

				   //勝利チェック
				   if (st->CheckWin(1)) {
					   PlayerWin = true;
					   st->isGameOver = true;
				   }

				   //引き分けチェック
				   if (!PlayerWin) {
					   if (st->isTie()) {
						   st->Tie = true;
						   st->isGameOver = true;
					   }
				   }

				   isPlayerTurn = false;//プレイヤーのターン終了

				   //AIにターンを渡す
				   AI* ai = FindGameObject<AI>();
				   if (ai != nullptr) {
					   ai->AITurn = true;
				   }
			   }
		   }
		}
		prevButton = true;
	}else {
		prevButton = false;
	}	
	
}

void Player::Draw()
{
	if (PlayerWin) {
		DrawString(100, 500, "貴方の勝ちです！", GetColor(255, 255, 255));
	}
}
