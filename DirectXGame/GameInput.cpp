#include "GameInput.h"

GameInput::~GameInput() {}

GameInput::GameInput() { this->Initialize(); }

void GameInput::Initialize() {
	tex_ = TextureManager::Load("command.png");

	for (int i = 0; i < 4; ++i) {
		sprite_[i].reset(Sprite::Create(tex_, {0.0f, 0.0f}));
		sprite_[i]->SetSize({120.0f, 120.0f});
		sprite_[i]->SetTextureRect(
		    {
		        0.0f,
		        0.0f,
		    },
		    {120.0f, 120.0f});
		sprite_[i]->SetPosition({(float)i * 120.0f + 400.0f, 330.0f});
	}
	input_ = Input::GetInstance();
	Reset();
}

void GameInput::Update() {

	srand(unsigned int(time(nullptr)));

	while (a[index] == a[0] && a[index] == a[1] && a[index] == a[2] && a[index] == a[3]) {
		for (int i = 0; i < 4; ++i) {
			// 文字変換
			count = rand() % 26 + 1;
			Translate(i);
			sprite_[i]->SetTextureRect({120.0f * count - 120.0f, 0.0f}, {120.0f, 120.0f});
			index++;
		}
	} 
}

void GameInput::Draw() {
	for (int i = 0; i < 4; ++i) {
		sprite_[i]->Draw();
	}
}

void GameInput::InputCommand() {
	if (input_->PushKey(a[0])) {
		commandClear[0] = true;
	}
	if (input_->PushKey(a[1])) {
		commandClear[1] = true;
	}
	if (input_->PushKey(a[2])) {
		commandClear[2] = true;
	}
	if (input_->PushKey(a[3])) {
		commandClear[3] = true;
	}
	if (commandClear[0] && commandClear[1] && commandClear[2] && commandClear[3]) {
		isCommandClear_ = true;
	}
}

void GameInput::Reset() {
	for (int i = 0; i < 4; ++i) {
		a[i] = DIK_RETURN;
		commandClear[i] = false;
	}
	isCommandClear_ = false;
	count = 0;
	index = 0;
}

void GameInput::Translate(int i) {
	if (count == 1) {
		a[i] = DIK_A;
	} else if (count == 2) {
		a[i] = DIK_B;
	} else if (count == 3) {
		a[i] = DIK_C;
	} else if (count == 4) {
		a[i] = DIK_D;
	} else if (count == 5) {
		a[i] = DIK_E;
	} else if (count == 6) {
		a[i] = DIK_F;
	} else if (count == 7) {
		a[i] = DIK_G;
	} else if (count == 8) {
		a[i] = DIK_H;
	} else if (count == 9) {
		a[i] = DIK_I;
	} else if (count == 10) {
		a[i] = DIK_J;
	} else if (count == 11) {
		a[i] = DIK_K;
	} else if (count == 12) {
		a[i] = DIK_L;
	} else if (count == 13) {
		a[i] = DIK_M;
	} else if (count == 14) {
		a[i] = DIK_L;
	} else if (count == 15) {
		a[i] = DIK_O;
	} else if (count == 16) {
		a[i] = DIK_P;
	} else if (count == 17) {
		a[i] = DIK_Q;
	} else if (count == 18) {
		a[i] = DIK_R;
	} else if (count == 19) {
		a[i] = DIK_S;
	} else if (count == 20) {
		a[i] = DIK_T;
	} else if (count == 21) {
		a[i] = DIK_U;
	} else if (count == 22) {
		a[i] = DIK_V;
	} else if (count == 23) {
		a[i] = DIK_W;
	} else if (count == 24) {
		a[i] = DIK_X;
	} else if (count == 25) {
		a[i] = DIK_Y;
	} else if (count == 26) {
		a[i] = DIK_Z;
	} else {
		// count = rand() % 26 + 1;
	}
}
