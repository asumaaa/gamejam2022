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

	//マップ
	map map;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};