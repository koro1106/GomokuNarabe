#define USE_MOVIE
#include <DxLib.h>
#include "Stage.h"
#include <iostream>
using namespace std;

int map[HEIGHT][WIDTH];


Stage::Stage()
{
	backGround = LoadGraph("data/image/backGround.png");
	
	// 初期状態のボードを空（0）にする
	memset(map, 0, sizeof(map));
	isGameOver = false;
	Tie = false;
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	//背景描画
	DrawGraph(0, 0, backGround, true);
	
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			int x = 50 * i + 450 + 50/2;
			int y = 50 * j + 100 + 50/2;

			int chip = GetMapValue(i, j);
			if (chip == 1) {
				DrawCircle(x, y, 10, GetColor(0, 255, 255), 1);
			}
			if (chip == 2) {
				DrawCircle(x, y, 10, GetColor(0, 255, 255), 0);
			}
		}
	}

	if (Tie) {
		DrawString(100, 500, "引き分けです", GetColor(255, 255, 255));
	}
	
}

int Stage::Put(int x, int y, int value)
{
	if (IsCellEmpty(x, y)) {
		SetMapValue(x, y, value);//コマを置く
		return 0;
	}
	return -1; //すでにコマが置かれている場合
}

//値を取得
int Stage::GetMapValue(int x, int y)
{
	//範囲外なら-1を返す
	if (x < 0 || x >= WIDTH || y >= HEIGHT)
		return -1;
	return map[y][x]; 
}

void Stage::SetMapValue(int x, int y, int value)
{
	map[y][x] = value;
}

bool Stage::IsCellEmpty(int x, int y)
{
	return map[y][x] == 0; //0なら空いている
}

bool Stage::CheckWin(int turn)
{
	//プレイヤー
	if (turn == 1) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (GetMapValue(x, y) == turn) {
					//横チェック
					if (GetMapValue(x + 1, y) == turn && GetMapValue(x + 2, y) == turn &&
						GetMapValue(x + 3, y) == turn && GetMapValue(x + 4, y) == turn) {
						return true;
					}
					//縦チェック
					if (y + 4 < HEIGHT &&
						GetMapValue(x, y + 1) == turn && GetMapValue(x, y + 2) == turn &&
						GetMapValue(x, y + 3) == turn && GetMapValue(x, y + 4) == turn) {
						return true;
					}
					//右斜め
					if ( y + 4 < WIDTH &&
						GetMapValue(x + 1, y + 1) == turn && GetMapValue(x + 2, y + 2) == turn &&
						GetMapValue(x + 3, y + 3) == turn && GetMapValue(x + 4, y + 4) == turn) {
						return true;
					}
					//左斜め
					if (x - 4 > 0 && y + 4 < HEIGHT &&
						GetMapValue(x - 1, y + 1) == turn && GetMapValue(x - 2, y + 2) == turn &&
						GetMapValue(x - 3, y + 3) == turn && GetMapValue(x - 4, y + 4) == turn) {
						return true;
					}
				}
			}
		}
		//どれも当てはまってないなら勝っていない
		return false;
	}
	

	//AI
	if (turn == 2) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (GetMapValue(x, y) == turn) {
					//横チェック
					if (GetMapValue(x + 1, y) == turn && GetMapValue(x + 2, y) == turn &&
						GetMapValue(x + 3, y) == turn && GetMapValue(x + 4, y) == turn) {
						return true;
					}
					//縦チェック
					if (y + 4 < HEIGHT &&
						GetMapValue(x, y + 1) == turn && GetMapValue(x, y + 2) == turn &&
						GetMapValue(x, y + 3) == turn && GetMapValue(x, y + 4) == turn) {
						return true;
					}
					//右斜め
					if (y + 4 < WIDTH &&
						GetMapValue(x + 1, y + 1) == turn && GetMapValue(x + 2, y + 2) == turn &&
						GetMapValue(x + 3, y + 3) == turn && GetMapValue(x + 4, y + 4) == turn) {
						return true;
					}
					//左斜め
					if (x - 4 > 0 && y + 4 < HEIGHT &&
						GetMapValue(x - 1, y + 1) == turn && GetMapValue(x - 2, y + 2) == turn &&
						GetMapValue(x - 3, y + 3) == turn && GetMapValue(x - 4, y + 4) == turn) {
						return true;
					}
				}
			}
		}
		//どれも当てはまってないなら勝っていない
		return false;
	}
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


