#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	model_ = Model::Create();
	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++)
			{
				worldTransform_[i][j][k].Initialize();
				worldTransform_[i][j][k].translation_.x = k * blockSize * blockScale;
				worldTransform_[i][j][k].translation_.y = i * blockSize * blockScale;
				worldTransform_[i][j][k].translation_.z = j * blockSize * blockScale;
				worldTransform_[i][j][k].scale_ ={blockScale,blockScale,blockScale };
				worldTransformUpdate(&worldTransform_[i][j][k]);
			}
		}
	}

	//自キャラ
	Player* newPlayer = new Player();
	newPlayer->Initialize(model_, textureHandle_);
	player_.reset(newPlayer);

	//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	viewProjection_.Initialize();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture.jpg");

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//レールカメラ
	RailCamera* newRailCamera = new RailCamera();
	newRailCamera->Initialize(player_->GetWorldTransform());
	railCamera_.reset(newRailCamera);

	//マップ
	/*const char* fileName = "map1.csv";*/
	map.Loding("map1.csv");

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
}

void GameScene::Update() 
{
	player_->Update();
	MapCollision();
	map.Loding("tutorialHole.csv");
	railCamera_->Update(player_->GetWorldTransform());
	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++)
			{
				if (map.M[i][j][k] == 1)
				{
					model_->Draw(worldTransform_[i][j][k], debugCamera_->GetViewProjection(), textureHandle_);
				}
			}
		}
	}
				debugText_->SetPos(0, 0);
				debugText_->Printf("%d", map.M[0][0][0]);
	player_->Draw(debugCamera_->GetViewProjection());

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::MapCollision()
{
	//座標を用意
	float left = player_->GetTranslation().x;
	float down = player_->GetTranslation().y;
	float front = player_->GetTranslation().z;
	float right = player_->GetTranslation().x + player_->GetSize();
	float up = player_->GetTranslation().y - player_->GetSize();
	float back = player_->GetTranslation().z + player_->GetSize();

	player_->MoveSpeedSet();

	////右に仮想的に移動して当たったら
	//if (mapcol(right, down + player_->GetSize() / 2, front + 0.1) || mapcol(right, down + player_->GetSize() / 2, back - player_->GetSize() / 2) && player_->GetMove().x > 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(right, down + player_->GetSize() / 2, front + 0.1) || mapcol(right, down + player_->GetSize() / 2, back - player_->GetSize() / 2)))
	//	{
	//		player_->OnMapCollisionX2();
	//		right = player_->GetTranslation().x + player_->GetSize();
	//		left = player_->GetTranslation().x;
	//	}
	//}
	////左に仮想的に移動して当たったら
	//if (mapcol(left, down + player_->GetSize() / 2, front + 0.1) || mapcol(left, down + player_->GetSize() / 2, back - player_->GetSize() / 2) && player_->GetMove().x < 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(left, down + player_->GetSize() / 2, front + 0.1) || mapcol(left, down + player_->GetSize() / 2, back - player_->GetSize() / 2)))
	//	{
	//		player_->OnMapCollisionX();
	//		right = player_->GetTranslation().x + player_->GetSize();
	//		left = player_->GetTranslation().x;
	//	}
	//}
	//left = player_->GetTranslation().x;
	//right = player_->GetTranslation().x + player_->GetSize();

	////下に仮想的に移動して当たったら
	//if (mapcol(left, down, front + 0.1))
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(left, down, front + 0.1)))
	//	{
	//		player_->OnMapCollisionY();
	//		up = player_->GetTranslation().y - player_->GetSize();
	//		down = player_->GetTranslation().y;
	//	}
	//}
	//up = player_->GetTranslation().y - player_->GetSize();
	//down = player_->GetTranslation().y;

	////z軸に対しての当たり判定
	////奥に仮想的に移動して当たったら
	//if (mapcol(left, down + player_->GetSize() / 2, back) || mapcol(right, down + player_->GetSize() / 2, back) && player_->GetMove().z > 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(left, down + player_->GetSize() / 2, back) || mapcol(right, down + player_->GetSize() / 2, back)))
	//	{
	//		player_->OnMapCollisionZ2();
	//		front = player_->GetTranslation().z;
	//		back = player_->GetTranslation().z + player_->GetSize();
	//	}
	//}
	////手前に仮想的に移動して当たったら
	//if (mapcol(left, down, front) || mapcol(right, down, front) && player_->GetMove().z < 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(left, down, front - 0.1) || mapcol(right, down, front - 0.1)))
	//	{
	//		player_->OnMapCollisionZ();
	//		front = player_->GetTranslation().z;
	//		back = player_->GetTranslation().z + player_->GetSize();
	//	}
	//}

	//右に仮想的に移動して当たったら
	//if (mapcol(right + player_->GetMove().x, down + player_->GetSize() / 2, front) || mapcol(right + player_->GetMove().x, down + player_->GetSize() / 2, back) &&
	//	player_->GetMove().x > 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while (!(mapcol(right + 1, down + player_->GetSize() / 2, front) || mapcol(right + 1, down + player_->GetSize() / 2, back)))
	//	{
	//		player_->OnMapCollisionX();
	//		right = player_->GetTranslation().x + player_->GetSize() - 1;
	//		left = player_->GetTranslation().x;
	//	}
	//	player_->MoveStopX();
	//}
	////左に仮想的に移動して当たったら
	//if (mapcol(left + player_->GetMove().x, down + player_->GetSize() / 2, front) || mapcol(left + player_->GetMove().x, down + player_->GetSize() / 2, back) &&
	//	player_->GetMove().x > 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while (!(mapcol(left - 1, down + player_->GetSize() / 2, front) || mapcol(left - 1, down + player_->GetSize() / 2, back)))
	//	{
	//		player_->OnMapCollisionX();
	//		right = player_->GetTranslation().x + player_->GetSize() - 1;
	//		left = player_->GetTranslation().x;
	//	}
	//	player_->MoveStopX();
	//}

	////下に仮想的に移動して当たったら
	//if (mapcol(left, down, front))
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(left, down, front + 0.1)))
	//	{
	//		player_->OnMapCollisionY();
	//		up = player_->GetTranslation().y - player_->GetSize();
	//		down = player_->GetTranslation().y;
	//	}
	//}
	//up = player_->GetTranslation().y - player_->GetSize();
	//down = player_->GetTranslation().y;

	////z軸に対しての当たり判定
	////奥に仮想的に移動して当たったら
	//if (mapcol(left, down + player_->GetSize() / 2, back + player_->GetMove().z) || mapcol(right, down + player_->GetSize() / 2, back + player_->GetMove().z) && player_->GetMove().z > 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while (!(mapcol(left, down + player_->GetSize() / 2, back + 0.1) || mapcol(right, down + player_->GetSize() / 2, back + 0.1)))
	//	{
	//		player_->OnMapCollisionZ();
	//		front = player_->GetTranslation().z;
	//		back = player_->GetTranslation().z + player_->GetSize();
	//	}
	//	player_->MoveStopZ();
	//}
	////手前に仮想的に移動して当たったら
	//if (mapcol(left, down, front) || mapcol(right, down, front) && player_->GetMove().z < 0)
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((mapcol(left, down, front - 0.1) || mapcol(right, down, front - 0.1)))
	//	{
	//		player_->OnMapCollisionZ();
	//		front = player_->GetTranslation().z;
	//		back = player_->GetTranslation().z + player_->GetSize();
	//	}
	//}

	//debugText_->SetPos(0, 0);
	//debugText_->Printf("%d", mapcol(right + player_->GetMove().x, down, front));
}
