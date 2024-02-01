#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"Sprite.h"
#include "TextureManager.h"
#include "MATHEX.h"

class Gauge {

public:
	
	Gauge();

	~Gauge();

	void Initialize();

	void Update();

	void Draw();

	void OnCollision();
	void OnCollision2();

private:


	// ワールド変換データ
	WorldTransform worldTransform_;

	const ViewProjection* viewProjection_ = nullptr;


	uint32_t GaugeSprite = 0u;

	Sprite* GaugeSprite_ = nullptr;

	
	Vector2 size_;

	float speed_ = 0.2f;

	bool flag = false;

};
