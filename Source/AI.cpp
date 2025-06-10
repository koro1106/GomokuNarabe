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
		AIstrategy();//�U���E�h��`�F�b�N�i�D�揇�ʁj

		//�œK����T��
		int bestScore = -1;
		int bestX = -1;
		int bestY = -1;

		for (int j = 0; j < HEIGHT; j++) {
			for (int i = 0; i < WIDTH; i++) {
				if (st->GetMapValue(i, j) == 0) {//����������Ă��Ȃ�(�󂫃Z��)
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
		
		  if (st->CheckWin(2)) {//�����`�F�b�N
			AIWin = true;
			st->isGameOver = true;
		  }else if (st->isTie()) {//���������`�F�b�N
			st->Tie = true;
			st->isGameOver = true;
		  }
    		pl->isPlayerTurn = true;//Player�̃^�[����
		}
		ResetAIScores();
	}	
}

void AI::Draw()
{
	if (AIWin) {
		DrawString(100, 500, "�M���̕����ł��I", GetColor(255, 255, 255));
	}
}

void AI::AIstrategy()
{
	Stage*st = FindGameObject<Stage>();

	int tempMap[AI_HEIGHT][AI_WIDTH];
	
	//�D�揇�ʃ`�F�b�N
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (st->GetMapValue(x, y) == 0) {//�󂫃}�X
				//�U���`�F�b�N�iAI�����Ă�j
				st->SetMapValue(x, y, 2);//����AI���u��
				if (st->CheckWin(2)) {
					AImap[y][x] += 1000;
				}

				//���[���󂢂Ă�3�A����ł�Ƃ�
				st->SetMapValue(x, y, 2);//����AI���u��
				if (CheckOpenThree(2)) {
					AImap[y][x] += 700;
				}

				//�h��`�F�b�N�iPlayer�����Ă�j
				st->SetMapValue(x, y, 1);//����Player���u��
				if (st->CheckWin(1)) {
					AImap[y][x] += 500;
				}
				//���ɖ߂�
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
			//���`�F�b�N
			if (st->GetMapValue(x + 1, y) == target && st->GetMapValue(x + 2, y) == target &&
				st->GetMapValue(x + 3, y) == target) {
				return true;
			}
			//�c
		}
	}
	return false;
}



