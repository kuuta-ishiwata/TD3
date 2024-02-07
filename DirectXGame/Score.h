#pragma once
#include"Vector2.h"
#include <cstdint>
#include"Sprite.h"



class Score {
public:
	void Initialize();

	void Update();

	void Draw();

	void OnCollision();

	void Reset();

	

	private:
	Vector2 pos_[2];

	uint32_t textureSprite_[13];

	Sprite* sprite_[13] = {nullptr,nullptr};

	int32_t counter_;



};
