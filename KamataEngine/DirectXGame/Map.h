#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <array>
#include <d3dx12.h>
#include <unordered_map>
#include <wrl.h>

//ブロックのサイズ 変更不可
const float blockSize = 2.0;
//ブロックのサイズ 変更可
const float blockScale = 1.0;

//xyzのブロックの数
const int blockX = 10;
const int blockY = 2;
const int blockZ = 10;

enum mapdate
{
	BLUNK,
	BLOCK
};

bool mapcol(int x, int y, int z);

class map
{
public:
	void Initialize();
	void Loding(char const* _FileName);
public:
	//マップのデータを入れておく変数
	int M[blockY][blockZ][blockX];
};

static int Map[blockY][blockZ][blockX]
{
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
};