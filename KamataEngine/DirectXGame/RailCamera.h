#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#define PI 3.141592653589

class RailCamera
{
public:
	void Initialize(WorldTransform worldTransform);
	void Update(WorldTransform worldTransform);
	//���[�h��؂�ւ���
	void modeManager();
	//�Q�b�^�[
	ViewProjection GetViewProjection() { return viewProjection_; }
private:
	ViewProjection viewProjection_;
	WorldTransform worldTransfomr_;
	//���@�ƃJ�����̋���
	float length = 20.0f;
	//�J�����̊p�x
	float angleX = 0.3 * PI;
	float angleY = 0.3 * PI;
	//�Ǐ]

};

