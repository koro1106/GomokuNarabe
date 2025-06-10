#include "AI.h"
#include "Player.h"
#include "Stage.h"

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
		AIstrategy();//攻撃・防御チェック（優先順位）

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
		ResetAIScores();
	}	
}

void AI::Draw()
{
	if (AIWin) {
		DrawString(100, 500, "貴方の負けです！", GetColor(255, 255, 255));
	}
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
					AImap[y][x] += 1000;
				}

				//両端が空いてて3連並んでるとき
				st->SetMapValue(x, y, 2);//仮でAIが置く
				if (CheckOpenThree(2)) {
					AImap[y][x] += 700;
				}

				//防御チェック（Playerが勝てる）
				st->SetMapValue(x, y, 1);//仮でPlayerが置く
				if (st->CheckWin(1)) {
					AImap[y][x] += 500;
				}
				//元に戻す
				st->SetMapValue(x, y, 0);
			}
		}
	}
}

void AI::ResetAIScores()
{
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (AImap[y][x] >= 1000) AImap[y][x] -= 1000;
			else if(AImap[y][x] >= 500) AImap[y][x] -= 500;
		}
	}
}

bool AI::CheckOpenThree(int target)
{
	Stage* st = FindGameObject<Stage>();

	//AI
	if(target == 2)
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			//横チェック
			if (st->GetMapValue(x + 1, y) == target && st->GetMapValue(x + 2, y) == target &&
				st->GetMapValue(x + 3, y) == target) {
				return true;
			}
			//縦
		}
	}
	return false;
}



