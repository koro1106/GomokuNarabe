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
		ResetAIScores();//�������i�X�R�A0�Ɂj
		AIstrategy();//�U���E�h��`�F�b�N�i�D�揇�ʂ̃X�R�A�t�j

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
	}	
}

void AI::Draw()
{
	
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
					AImap[y][x] += 10000;
				}
				//���ɖ߂�
				st->SetMapValue(x, y, 0);

				//�h��`�F�b�N�iPlayer�����Ă�j
				st->SetMapValue(x, y, 1);//����Player���u��
				if (st->CheckWin(1)) {
					AImap[y][x] += 9000;
				}
				//���ɖ߂�
				st->SetMapValue(x, y, 0);
			}
			//�v���C���[���������ȂƂ�AI���u���Ă���Ȃ��Ƃ�����
		}
	}

	//���[���󂢂Ă�3�Aor2�APlayer������ł�Ƃ�
	IsThreeLine();
	IsTwoLine();

	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (st->GetMapValue(x, y) != 0) continue;//�}�X���܂��Ă��玟�̃}�X��
		   //Player���R�A����ł�Ƃ��i�Е������󔒁j
			//�������i���j
			if (st->CountLine(x, y, 1, 0, 1) == 3) {
				int before = st->GetMapValue(x - 1, y);
				int after = st->GetMapValue(x + 3, y);
				if ((before == 0 && after != 0) || (before != 0 && after == 0)) {
					AImap[y][x] += 500;//�Е������󔒂Ȃ���_
				}
			}
		}
	}
}

void AI::ResetAIScores()
{
	//������
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			AImap[y][x] = 0;
		}
	}
}

//n����łāA���[��
bool AI::IsLineN(int x, int y, int n, int dx, int dy, int turn)
{
	Stage* st = FindGameObject<Stage>();
	int count = st->CountLine(x, y, dx, dy, turn);//�A�����Ă鐔���J�E���g����
	if (count != n) return false;//�A���ŕ���łȂ�������false��

	//���[�̊m�F
	int beforeX = x - dx;
	int beforeY = y - dy;
	int afterX = x + dx * n;
	int afterY = y + dy * n;

	int before = st->GetMapValue(beforeX, beforeY);
	int after = st->GetMapValue(afterX, afterY);
	
	//���[�󂢂Ă��true�󂢂ĂȂ����false
	return (before == 0 && after == 0);
}

void AI::IsThreeLine()
{
	for (int y = 0; y < AI_HEIGHT; y++) {
		for (int x = 0; x < AI_WIDTH; x++) {
			if (IsLineN(x, y, 3, 1, 0, 1)) { //��
				AImap[y][x + 1] += 1000;
				AImap[y][x - 1] += 1000;
			}
			if (IsLineN(x, y, 3, 1, 0, 2)) {
				AImap[y][x + 1] += 500;
				AImap[y][x - 1] += 500;
			}

			if (IsLineN(x, y, 3, 0, 1, 1)) { //�c
				AImap[y + 1][x] += 1000;
				AImap[y - 1][x] += 1000;
			}
			if (IsLineN(x, y, 3, 0, 1, 2)) { 
				AImap[y + 1][x] += 500;
				AImap[y - 1][x] += 500;
			}
			if (IsLineN(x, y, 3, 1, 1, 1)) { //�E��
				AImap[y + 1][x + 1] += 1000;
				AImap[y - 1][x - 1] += 1000;
			}
			if (IsLineN(x, y, 3, 1, 1, 2)) { 
				AImap[y + 1][x + 1] += 500;
				AImap[y - 1][x - 1] += 500;
			}
			if (IsLineN(x, y, 3, -1, 1, 1)) {//����
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
			if (IsLineN(x, y, 2, 1, 0, 1)) { //��
				AImap[y][x + 1] += 50;
				AImap[y][x - 1] += 50;
			}
			if (IsLineN(x, y, 2, 1, 0, 2)) {
				AImap[y][x + 1] += 30;
				AImap[y][x - 1] += 30;
			}
			if (IsLineN(x, y, 2, 0, 1, 1)) { //�c
				AImap[y + 1][x] += 50;
				AImap[y - 1][x] += 50;
			}
			if (IsLineN(x, y, 2, 0, 1, 2)) { 
				AImap[y + 1][x] += 30;
				AImap[y - 1][x] += 30;
			}
			if (IsLineN(x, y, 2, 1, 1, 1)) { //�E��
				AImap[y + 1][x + 1] += 50;
				AImap[y - 1][x - 1] += 50;
			}
			if (IsLineN(x, y, 2, 1, 1, 2)) { 
				AImap[y + 1][x + 1] += 30;
				AImap[y - 1][x - 1] += 30;
			}
			if (IsLineN(x, y, 2, -1, 1, 1)) {//����
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

