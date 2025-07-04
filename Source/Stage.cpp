#define USE_MOVIE
#include <DxLib.h>
#include "Stage.h"
#include <iostream>
using namespace std;

int map[HEIGHT][WIDTH];


Stage::Stage()
{
	// 初期状態のボードを空（0）にする
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
	//背景描画
	DrawGraph(0, 0, backGround, true);
	
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			int x = 50 * i + 450 + 50/2;
			int y = 50 * j + 100 + 50/2;

			int chip = GetMapValue(i, j);
			int imageWidth = 30;
		    int imageHeight = 30;

			int drawX = x - imageWidth / 2;//画像の中心をマウスcクリックした位置に合わせる
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
		SetMapValue(x, y, value);//コマを置く
		return 0;
	}
	return -1; //すでにコマが置かれている場合
}

//値を取得
int Stage::GetMapValue(int x, int y)
{
	//範囲外なら-1を返す
	if (x < 0 || x >= WIDTH || y >= HEIGHT) return -1;
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
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++){
			if (GetMapValue(x, y) == turn) {
				//4方向チェック
				if (CountLine(x, y, 1, 0, turn) == 5)return true;//横
				if (CountLine(x, y, 0, 1, turn) == 5)return true;//縦
				if (CountLine(x, y, 1, 1, turn) == 5)return true;//右下
				if (CountLine(x, y, -1,1, turn) == 5)return true;//左下
			}
		}
	}
	return false;
}

//方向を指定して、並んでる数をカウントする
int Stage::CountLine(int x, int y, int dx, int dy, int  turn)
{
	int count = 0;
	for (int i = 0; i < 5; i++) {
		int nx = x + dx * i;
		int ny = y + dy * i;
		if (nx < 0 || ny < 0 || nx >= WIDTH || ny >= HEIGHT) return 0;//範囲外なら終了

		if (GetMapValue(nx, ny) == turn) {
			count++;//同じコマならカウント
		}
		else {
			break;//違うコマなら調べるのやめる
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



