#include "Player.h"
#include <Novice.h>


void Player::Initialize()
{
}

void Player::Update(char* keys, char* preKeys)
{
	BluePlayer.pos.x += 0.06f;
	PinkPlayer.pos.x += 0.06f;

	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		changeFlag = true;
	}

	if (changeFlag == true) {
		if (UpSideGround == true) {
			UpSideGround = false;
			DownSideGround = true;
			changeFlag = false;
		}
		else if (DownSideGround == true) {
			UpSideGround = true;
			DownSideGround = false;
			changeFlag = false;
		}
	}

}

void Player::Draw()
{
	if (UpSideGround == true) {
		Novice::DrawBox(BluePlayer.pos.x * 32, BluePlayer.pos.y * 32+224, BluePlayer.radius, BluePlayer.radius, 0.0f, BluePlayer.color, kFillModeSolid);
		Novice::DrawBox(PinkPlayer.pos.x * 32, PinkPlayer.pos.y * 32-224, PinkPlayer.radius, PinkPlayer.radius, 0.0f, PinkPlayer.color, kFillModeSolid);
	}
	if (DownSideGround == true) {
		Novice::DrawBox(BluePlayer.pos.x * 32, BluePlayer.pos.y * 32, BluePlayer.radius, BluePlayer.radius, 0.0f, BluePlayer.color, kFillModeSolid);
		Novice::DrawBox(PinkPlayer.pos.x * 32, PinkPlayer.pos.y * 32, PinkPlayer.radius, PinkPlayer.radius, 0.0f, PinkPlayer.color, kFillModeSolid);
	}
}
