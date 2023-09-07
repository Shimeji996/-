#pragma once
#include <Vector2.h>
typedef struct Chara {
	Vector2 pos;
	int radius;
	unsigned int color;
};

class Player
{
public:
	void Initialize();
	void Update(char* keys, char* preKeys);
	void Draw();
private:
	Chara BluePlayer = {
		{2,8},
		32,
		0xffffffff,
	};

	Chara PinkPlayer = {
		{2,15},
		32,
		0x000000ff,
	};
private:
	bool UpSideGround = false;
	bool DownSideGround = true;
	bool changeFlag = false;

};

