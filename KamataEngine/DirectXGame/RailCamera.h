#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#define PI 3.141592653589

class RailCamera
{
public:
	void Initialize(WorldTransform worldTransform);
	void Update(WorldTransform worldTransform);
	//モードを切り替える
	void modeManager();
	//モード
	void Approach();	//接近、導入
	void Homing();		//追従
	void Operarion();	//操作
	//ゲッター
	ViewProjection GetViewProjection() { return viewProjection_; }
private:
	ViewProjection viewProjection_;
	WorldTransform worldTransfomr_;
	//自機とカメラの距離
	float length = 20.0f;
	//カメラの角度
	float angleX = 0.3 * PI;
	float angleY = 0.3 * PI;
	//モード
	enum class Mode
	{
		Approach,	//接近、導入
		Horming,	//カメラ追従
		Operation	//操作
	};
	//モード
	size_t mode_ = static_cast<size_t>(Mode::Approach);
	//メンバ関数のポインタテーブル
	static void (RailCamera::* Mode_[])();
};

