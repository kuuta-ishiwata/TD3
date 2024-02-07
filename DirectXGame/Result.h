#pragma once
#include "GameInput.h"
#include "ImGuiManager.h"
#include "Sprite.h"
#include "Vector2.h"
#include <cstdint>

class Result {
public:
	void Initialize();

	void Update();

	void Draw();

	void Oncollision();

	void Reset();

private:
	Vector2 pos_[2];

	uint32_t textureSprite_[13];

	Sprite* sprite_[13] = {nullptr, nullptr};

	int32_t counter_;

	GameInput* gameinput_ = nullptr;

	int32_t timer_;
};
