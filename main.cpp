#include <Novice.h>
#include "Player.h"

const char kWindowTitle[] = "並行世界";

enum MapInfo {
	NONE, // 0
	BLOCK // 1
};

typedef struct Block {
	MapInfo state;    //ブロックの状態
	Vector2 pos;      //座標
	Vector2 size;     //画像の大きさ
	Vector2 imagePos; //読み込む画像の座標
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 752);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Player* player = new Player();

	const int mapHeight = 24; //Y軸のブロックの数
	const int mapWidth = 40;  //X軸のブロックの数

	int BlockSize = 32;

	int map[mapHeight][mapWidth]{
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},


	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	Block block[mapHeight][mapWidth]{};

	int gh1 = Novice::LoadTexture("./map.png");
	int pinkground = Novice::LoadTexture("./Resources/pinkground.png");
	int pinkground1 = Novice::LoadTexture("./Resources/pinkground1.png");//反転バージョン
	int blueground = Novice::LoadTexture("./Resources/blueground.png");
	int blueground1 = Novice::LoadTexture("./Resources/blueground1.png");//反転バージョン

	//ブロックの状況
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			//ブロックの座標、サイズ設定
			block[y][x].pos.x = x * BlockSize;
			block[y][x].pos.y = y * BlockSize;
			block[y][x].size.x = 32;
			block[y][x].size.y = 32;

			//ブロックがある場合
			if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0;
				block[y][x].imagePos.y = 32;
			}

			//ブロックがない場合
			if (map[y][x] == 0) {
				block[y][x].state = NONE;
				block[y][x].imagePos.x = 32;
				block[y][x].imagePos.y = 0;
			}
		}

	}
	bool UpSideGround = false;
	bool DownSideGround = true;
	bool changeFlag = false;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		
		player->Update(keys,preKeys);

		if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0 ) {
			changeFlag = true;
		}
		
		if(changeFlag==true){
			if ( UpSideGround == true) {
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
		switch (switch_on)
		{
		default:
			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (UpSideGround == true){
			Novice::DrawSprite(0, 272, blueground, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(0, 384, pinkground1, 1, 1, 0.0f, WHITE);
		}
		if (DownSideGround == true) {
			Novice::DrawSprite(0, 272, pinkground, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(0, 384, blueground1, 1, 1, 0.0f, WHITE);
		}
		//行の繰り返し
		for (int y = 0; y < mapHeight; y++) {
			//列の繰り返し
			for (int x = 0; x < mapWidth; x++) {
				//配列でブロックが存在している場合は配置する
				if (map[y][x] == BLOCK) {
					Novice::DrawSpriteRect(x * BlockSize, y * BlockSize, 0, 32, 0, 32, gh1, 1.0, 1.0, 0.0f, 0xFFFFFFFF);
				}
			}
		}
		Novice::ScreenPrintf(100, 100, "%d", UpSideGround);
		player->Draw();
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
