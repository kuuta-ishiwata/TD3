#include "Player.h"

void Player::Initialize() { 
	worldTransform_.Initialize();
	model_ = Model::Create();
}

void Player::Update() { /*worldTransform_.UpdateMatrix();*/ }

void Player::Draw(ViewProjection& viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection); 

}
