#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"Sprite.h"
#include "TextureManager.h"
#include "MATHEX.h"
#include "imgui.h"

class Gauge {

public:
	
	Gauge();

	~Gauge();

	void Initialize();

	void Update();

	void Draw();

	void Incorrect();
	void flagOnCollision();
	void flagOnCollision2();

	bool IsSize() { return isSize_; }

private:


	// ワールド変換データ
	WorldTransform worldTransform_;

	const ViewProjection* viewProjection_ = nullptr;


	uint32_t GaugeSprite = 0u;

	Sprite* GaugeSprite_ = nullptr;

	
	Vector2 size_;

	float speed_ = 0.4f;

	bool flag = false;

	int ImGuiflag = 0;

	bool isSize_ = false;

};
