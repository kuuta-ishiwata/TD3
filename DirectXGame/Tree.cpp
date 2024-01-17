#include "Tree.h"
#include <assert.h>

void Tree::Initialize(Model* model) {

	assert(model);

	TreeModel_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_.x = 2.5f;
	//worldTransform_.scale_ = {0.3f, 1.0f, 250.0f};
}

void Tree::Update() { worldTransform_.UpdateMatrix(); }

void Tree::Draw(ViewProjection& viewProjection) {

	TreeModel_->Draw(worldTransform_, viewProjection);
}