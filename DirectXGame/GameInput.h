#pragma once
#include "Input.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "numbers"
#include <string>
#include <stdio.h>
#include "ImGuiManager.h"

class GameInput final {
public:


	
	~GameInput();
	

	void Initialize();

	void Upadte();
   
	bool Input();


	GameInput(const GameInput& gameInput) = delete;

	GameInput& operator = (const GameInput& gameInput) = delete;

	
	//コピーや代入演算子を無効化
	static GameInput* GetInstance()
	{ 
		static GameInput instance;
		return &instance;

	}


private:

	GameInput();
	
	//Input* input_ = nullptr;
	

	std::array<BYTE, 256> keys;

	int i = 0;

   const static int kMax = 4;

	std::array<BYTE, 256> a ;


};
