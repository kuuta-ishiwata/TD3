#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Tree {

	public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// ViewProjection viewProjection_;

	// モデル
	Model* TreeModel_ = nullptr;

	uint32_t textureHandle_ = 0u;



};
