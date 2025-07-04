#include "AI.h"
#include "Player.h"
#include "Stage.h"
#include <iostream>

int AImap[AI_HEIGHT][AI_WIDTH];

AI::AI()
{
	AIWin = false;
}

AI::~AI()
{
}

void AI::Update()
{
	Stage* st = FindGameObject<Stage>();
	Player* pl = FindGameObject<Player>();

	if (st->isGameOver) return;

	if (AITurn){
		ResetAIScores();//初期化（スコア0に）
		AIstrategy();//攻撃・防御チェック（優先順位のスコア付）

		//最適解を探す
		int bestScore = -1;
		int bestX = -1;
		int bestY = -1;

		for (int j = 0; j < HEIGHT; j++) {
			for (int i = 0; i < WIDTH; i++) {
				if (st->GetMapValue(i, j) == 0) {//何も書かれていない(空きセル)
					int score = AImap[j][i];
					if (score > bestScore) {
						bestScore = score;
						bestX = i;
						bestY = j;
					}
				}
			}
		}

		if (bestX != -1 && bestY != -1) {
			st->SetMapValue(bestX, bestY, 2);
			AITurn = false;
		  if (st->CheckWin(2)) {//勝利チェック
			AIWin = true;
			st->isGameOver = true;
		  }else if (st->isTie()) {//引き分けチェック
			st->Tie = true;
			st->isGameOver = true;
		  }
    		pl->isPlayerTurn = true;//Playerのターンへ
		}
	}	
}

void AI::Draw()
{
	
}

void AI::AIstrategy()
{
	Stage*st = FindGameObject<Stage>();

	int tempMap[AI_HEIGHT][AI_WIDTH];

	//優先順位チェック
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (st->GetMapValue(x, y) == 0) {//空きマス
				//攻撃チェック（AIが勝てる）
				st->SetMapValue(x, y, 2);//仮でAIが置く
				if (st->CheckWin(2)) {
					AImap[y][x] += 10000;
				}
				//元に戻す
				st->SetMapValue(x, y, 0);

				//防御チェック（Playerが勝てる）
				st->SetMapValue(x, y, 1);//仮でPlayerが置く
				if (st->CheckWin(1)) {
					AImap[y][x] += 9000;
				}
				//元に戻す
				st->SetMapValue(x, y, 0);
			}
			//プレイヤー勝ちそうなときAIが置いてくれないときある
		}
	}

	//両端が空いてて3連or2連Playerが並んでるとき
	IsThreeLine();
	IsTwoLine();

	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (st->GetMapValue(x, y) != 0) continue;//マス埋まってたら次のマスへ
		   //Playerが３連並んでるとき（片方だけ空白）
			//横方向（→）
			if (st->CountLine(x, y, 1, 0, 1) == 3) {
				int before = st->GetMapValue(x - 1, y);
				int after = st->GetMapValue(x + 3, y);
				if ((before == 0 && after != 0) || (before != 0 && after == 0)) {
					AImap[y][x] += 500;//片方だけ空白なら加点
				}
			}
		}
	}
}

void AI::ResetAIScores()
{
	//初期化
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			AImap[y][x] = 0;
		}
	}
}

//n個並んでて、両端空白
bool AI::IsLineN(int x, int y, int n, int dx, int dy, int turn)
{
	Stage* st = FindGameObject<Stage>();
	int count = st->CountLine(x, y, dx, dy, turn);//連続してる数をカウントする
	if (count != n) return false;//連続で並んでなかったらfalseに

	//両端の確認
	int beforeX = x - dx;
	int beforeY = y - dy;
	int afterX = x + dx * n;
	int afterY = y + dy * n;

	int before = st->GetMapValue(beforeX, beforeY);
	int after = st->GetMapValue(afterX, afterY);
	
	//両端空いてればtrue空いてなければfalse
	return (before == 0 && after == 0);
}

void AI::IsThreeLine()
{
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (IsLineN(x, y, 3, 1, 0, 1)) { //横
				AImap[y][x + 1] += 1000;
				AImap[y][x - 1] += 1000;
			}
			if (IsLineN(x, y, 3, 1, 0, 2)) {
				AImap[y][x + 1] += 500;
				AImap[y][x - 1] += 500;
			}

			if (IsLineN(x, y, 3, 0, 1, 1)) { //縦
				AImap[y + 1][x] += 1000;
				AImap[y - 1][x] += 1000;
			}
			if (IsLineN(x, y, 3, 0, 1, 2)) { 
				AImap[y + 1][x] += 500;
				AImap[y - 1][x] += 500;
			}
			if (IsLineN(x, y, 3, 1, 1, 1)) { //右下
				AImap[y + 1][x + 1] += 1000;
				AImap[y - 1][x - 1] += 1000;
			}
			if (IsLineN(x, y, 3, 1, 1, 2)) { 
				AImap[y + 1][x + 1] += 500;
				AImap[y - 1][x - 1] += 500;
			}
			if (IsLineN(x, y, 3, -1, 1, 1)) {//左下
				AImap[y - 1][x + 1] += 1000;
				AImap[y + 1][x - 1] += 1000;
			}
			if (IsLineN(x, y, 3, -1, 1, 2)) {
				AImap[y - 1][x + 1] += 500;
				AImap[y + 1][x - 1] += 500;
			}
		}
	}
}

void AI::IsTwoLine()
{
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (IsLineN(x, y, 2, 1, 0, 1)) { //横
				AImap[y][x + 1] += 50;
				AImap[y][x - 1] += 50;
			}
			if (IsLineN(x, y, 2, 1, 0, 2)) {
				AImap[y][x + 1] += 30;
				AImap[y][x - 1] += 30;
			}
			if (IsLineN(x, y, 2, 0, 1, 1)) { //縦
				AImap[y + 1][x] += 50;
				AImap[y - 1][x] += 50;
			}
			if (IsLineN(x, y, 2, 0, 1, 2)) { 
				AImap[y + 1][x] += 30;
				AImap[y - 1][x] += 30;
			}
			if (IsLineN(x, y, 2, 1, 1, 1)) { //右下
				AImap[y + 1][x + 1] += 50;
				AImap[y - 1][x - 1] += 50;
			}
			if (IsLineN(x, y, 2, 1, 1, 2)) { 
				AImap[y + 1][x + 1] += 30;
				AImap[y - 1][x - 1] += 30;
			}
			if (IsLineN(x, y, 2, -1, 1, 1)) {//左下
				AImap[y - 1][x + 1] += 50;
				AImap[y + 1][x - 1] += 50;
			}
			if (IsLineN(x, y, 2, -1, 1, 2)) {
				AImap[y - 1][x + 1] += 30;
				AImap[y + 1][x - 1] += 30;
			}
		}
	}
}

