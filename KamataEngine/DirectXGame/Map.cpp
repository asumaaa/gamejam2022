#include "Map.h"

bool mapcol(int x, int y, int z)
{
	int mapx = x / (blockScale * blockSize);
	int mapy = y / (blockScale * blockSize);
	int mapz = z / (blockScale * blockSize);

	//���肦�Ȃ��l��false�ŕԂ�
	if (mapx < 0 || mapx >= blockX)	return false;
	if (mapy < 0 || mapy >= blockY)	return false;
	if (mapz < 0 || mapz >= blockZ)	return false;

	return Map[mapy][mapz][mapx] == BLOCK;
}

void map::Initialize()
{
}

void map::Loding(char const* _FileName)
{
	FILE* fp = NULL;

	fopen_s(&fp,_FileName, "r");

	//�z��p�̕ϐ�
	int i, j, k;
	i = 0; j = 0; k = 0;
	//���
	while (i < blockY && j < blockZ && k < blockX) {
		fscanf_s(fp, "%d,", &M[i][j][k]);
		if (k < blockX - 1)
		{
			k++;
		}
		else if(j < blockZ - 1)
		{
			k = 0;
			j++;
		}
		else
		{
			k = 0;
			j = 0;
			i++;
		}
	}


	fclose(fp);
}
