#define USE_MOVIE
#include <DxLib.h>
#include "Stage.h"
#include <iostream>
using namespace std;

int map[HEIGHT][WIDTH];


Stage::Stage()
{
	// ������Ԃ̃{�[�h����i0�j�ɂ���
	memset(map, 0, sizeof(map));
	isGameOver = false;
	Tie = false;

	//map[1][1] = 1;
	//map[1][2] = 1;
	//map[1][3] = 1;
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	//�w�i�`��
	DrawGraph(0, 0, backGround, true);
	
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			int x = 50 * i + 450 + 50/2;
			int y = 50 * j + 100 + 50/2;

			int chip = GetMapValue(i, j);
			int imageWidth = 30;
		    int imageHeight = 30;

			int drawX = x - imageWidth / 2;//�摜�̒��S���}�E�Xc�N���b�N�����ʒu�ɍ��킹��
			int drawY = y - imageHeight / 2;

			if (chip == 1) {
				//DrawCircle(x, y, 10, GetColor(0, 255, 255), 1);
				DrawGraph(drawX, drawY, playerGraph, TRUE);
			}
			if (chip == 2) {
				//DrawCircle(x, y, 10, GetColor(0, 255, 255), 0);
				DrawGraph(drawX, drawY, aiGraph, TRUE);
			}
		}
	}
}

void Stage::Update()
{
	if (isGameOver)
	{
		SceneManager::ChangeScene("RESULT");
	}
}

int Stage::Put(int x, int y, int value)
{
	if (IsCellEmpty(x, y)) 
	{
		SetMapValue(x, y, value);//�R�}��u��
		return 0;
	}
	return -1; //���łɃR�}���u����Ă���ꍇ
}

//�l���擾
int Stage::GetMapValue(int x, int y)
{
	//�͈͊O�Ȃ�-1��Ԃ�
	if (x < 0 || x >= WIDTH || y >= HEIGHT) return -1;
	return map[y][x]; 
}

void Stage::SetMapValue(int x, int y, int value)
{
	map[y][x] = value;
}

bool Stage::IsCellEmpty(int x, int y)
{
	return map[y][x] == 0; //0�Ȃ�󂢂Ă���
}

bool Stage::CheckWin(int turn)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++){
			if (GetMapValue(x, y) == turn) {
				//4�����`�F�b�N
				if (CountLine(x, y, 1, 0, turn) == 5)return true;//��
				if (CountLine(x, y, 0, 1, turn) == 5)return true;//�c
				if (CountLine(x, y, 1, 1, turn) == 5)return true;//�E��
				if (CountLine(x, y, -1,1, turn) == 5)return true;//����
			}
		}
	}
	return false;
}

//�������w�肵�āA����ł鐔���J�E���g����
int Stage::CountLine(int x, int y, int dx, int dy, int  turn)
{
	int count = 0;
	for (int i = 0; i < 5; i++) {
		int nx = x + dx * i;
		int ny = y + dy * i;
		if (nx < 0 || ny < 0 || nx >= WIDTH || ny >= HEIGHT) return 0;//�͈͊O�Ȃ�I��

		if (GetMapValue(nx, ny) == turn) {
			count++;//�����R�}�Ȃ�J�E���g
		}
		else {
			break;//�Ⴄ�R�}�Ȃ璲�ׂ�̂�߂�
		}
	}
	return count;
}

bool Stage::isTie()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (map[y][x] == 0) {
				return false;
			}
		}
	}
	return true;
}



