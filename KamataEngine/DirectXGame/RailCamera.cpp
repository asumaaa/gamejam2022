#include "RailCamera.h"
#include "math.h"
#include <cassert>
#define PI 3.141592653589

void RailCamera::Initialize(WorldTransform worldTransform)
{
	viewProjection_.Initialize();
}

void RailCamera::Update(WorldTransform worldTransform)
{
	(this->*Mode_[mode_])();

	float x, y, z;

	//プレイヤーの角度に合わせてカメラを回転
	/*x = worldTransform.translation_.x + (sin(-worldTransform.rotation_.x + (PI / 2)) * cos(-worldTransform.rotation_.y - (PI / 2)) * length);
	y = worldTransform.translation_.y + (cos(-worldTransform.rotation_.x + (PI / 2)) * length);
	z = worldTransform.translation_.z + (sin(-worldTransform.rotation_.x + (PI / 2)) * sin(-worldTransform.rotation_.y - (PI / 2)) * length);*/

	//指定した角度で回転
	x = worldTransform.translation_.x + (sin(-angleY + (PI / 2)) * cos(-angleX - (PI / 2)) * length);
	y = worldTransform.translation_.y + (cos(-angleY + (PI / 2)) * length);
	z = worldTransform.translation_.z + (sin(-angleY + (PI / 2)) * sin(-angleX - (PI / 2)) * length);

	if (sin(angleY) <= 0)
	{
		viewProjection_.up = { 0,-1,0 };
	}
	else
	{
		viewProjection_.up = { 0,1,0 };
	}
	viewProjection_.eye = { x,y,z };
	viewProjection_.target = { worldTransform.translation_.x, worldTransform.translation_.y, worldTransform.translation_.z };
	viewProjection_.Initialize();
}

void (RailCamera::* RailCamera::Mode_[])() =
{
	&RailCamera::Approach,
	&RailCamera::Homing,
	&RailCamera::Operarion,
};


void RailCamera::Approach()
{
}

void RailCamera::Homing()
{
}

void RailCamera::Operarion()
{
}
