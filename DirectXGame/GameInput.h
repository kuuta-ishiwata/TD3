#pragma once
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "PrimitiveDrawer.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include "numbers"
#include <stdio.h>
#include <string>

class GameInput final {
public:
	~GameInput();

	void Initialize();

	void Update();

	void Draw();

	void InputCommand();

	void Reset();

	bool CommandClear() { return isCommandClear_; }

	void Translate(int i);

	GameInput(const GameInput& gameInput) = delete;

	GameInput& operator=(const GameInput& gameInput) = delete;

	// コピーや代入演算子を無効化
	static GameInput* GetInstance() {
		static GameInput instance;
		return &instance;
	}

private:
	GameInput();

	std::array<BYTE, 256> keys;

	const static int kMax = 4;

	std::array<BYTE, 256> a;

	bool isCommandClear_ = false;

	bool commandClear[kMax] = {};

	int count = 0;

	int index = 0;

	// 入力
	Input* input_ = nullptr;

	// 画像
	uint32_t tex_ = 0u;

	// スプライト
	std::unique_ptr<Sprite> sprite_[kMax] = {};
};
