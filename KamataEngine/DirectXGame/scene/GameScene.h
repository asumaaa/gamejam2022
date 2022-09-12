#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Matrix.h"
#include "list"
#include "Player.h"
#include "Map.h"
#include "RailCamera.h"
#include "Map.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//当たり判定
	void MapCollision();

	//シーンごとの処理
	void Title();
	void Select();
	void Game();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Model* model_;

	WorldTransform worldTransform_[10][10][10];
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//レールカメラ
	std::unique_ptr<RailCamera>railCamera_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//シーン
	enum class Scene
	{
		Title,	//タイトル
		Select,	//ステージ選択
		Game	//操作
	};
	//シーン	最初がタイトル
	size_t scene_ = static_cast<size_t>(Scene::Title);
	//メンバ関数のポインタテーブル
	static void (GameScene::* Scene_[])();

	//マップ
	map map;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};