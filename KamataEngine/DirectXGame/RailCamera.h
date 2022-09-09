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
	//追従

};

