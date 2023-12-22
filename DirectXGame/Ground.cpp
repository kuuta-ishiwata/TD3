#include "Ground.h"
#include <assert.h>


void Ground::Initialize(Model* model)
{


	assert(model);

	GroundModel_ = model;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

}

void Ground::Update() { worldTransform_.UpdateMatrix(); }

void Ground::Draw(ViewProjection& viewProjection) {

	GroundModel_->Draw(worldTransform_, viewProjection);
}