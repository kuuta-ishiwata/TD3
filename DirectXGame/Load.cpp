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

	



	#ifdef _DEBUG

	ImGui::Begin("window");
	if (ImGui::TreeNode("Player")) {
		ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -10, 10);
		ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -10, 10);
		//ImGui::SliderFloat3("speed", &velocity_.x, -10, 10);

		ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUG
	worldTransform_.UpdateMatrix(); 

}

void Load::Draw(ViewProjection& viewProjection)
{

	LoadModel_->Draw(worldTransform_, viewProjection,textureHandle_);
}