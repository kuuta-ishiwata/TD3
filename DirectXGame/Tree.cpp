#include "Tree.h"
#include <assert.h>

void Tree::Initialize(Model* model, uint32_t textureHandle)
 {

	assert(model);

	TreeModel_ = model;

	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	//worldTransform_.translation_.x = 2.5f;
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};

}

void Tree::Update() { worldTransform_.UpdateMatrix(); }

void Tree::Draw(ViewProjection& viewProjection, Vector3 pos) 
{
	
	worldTransform_.translation_ = pos;
	TreeModel_->Draw(worldTransform_, viewProjection,textureHandle_);


}