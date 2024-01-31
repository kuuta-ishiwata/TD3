#include "Load.h"
#include <assert.h>

void Load::Initialize(Model* model, uint32_t textureHandle) {

	assert(model);

	LoadModel_ = model;

	textureHandle_ = textureHandle; 

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 0.1f;
	worldTransform_.scale_ = {0.3f, 1.0f, 250.0f};

}

void Load::Update() { 
	worldTransform_.UpdateMatrix(); 
}

void Load::Draw(ViewProjection& viewProjection)
{
	LoadModel_->Draw(worldTransform_, viewProjection,textureHandle_);
}