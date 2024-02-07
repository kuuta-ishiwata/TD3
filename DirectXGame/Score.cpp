#include "Score.h"
#include <TextureManager.h>


void Score::Initialize(){


	pos_[0] = {55.0f, 55.0f};
	pos_[1] = {35.0f, 55.0f};


	textureSprite_[0] = TextureManager::Load("Point/Point0.png");
	sprite_[0] = Sprite::Create(textureSprite_[0], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	textureSprite_[1] = TextureManager::Load("Point/Point.png");
	sprite_[1] = Sprite::Create(textureSprite_[1], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[2] = TextureManager::Load("Point/Point2.png");
	sprite_[2] = Sprite::Create(textureSprite_[2], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[3] = TextureManager::Load("Point/Point3.png");
	sprite_[3] = Sprite::Create(textureSprite_[3], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[4] = TextureManager::Load("Point/Point4.png");
	sprite_[4] = Sprite::Create(textureSprite_[4], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[5] = TextureManager::Load("Point/Point5.png");
	sprite_[5] = Sprite::Create(textureSprite_[5], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[6] = TextureManager::Load("Point/Point6.png");
	sprite_[6] = Sprite::Create(textureSprite_[6], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[7] = TextureManager::Load("Point/Point7.png");
	sprite_[7] = Sprite::Create(textureSprite_[7], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[8] = TextureManager::Load("Point/Point8.png");
	sprite_[8] = Sprite::Create(textureSprite_[8], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		textureSprite_[9] = TextureManager::Load("Point/Point9.png");
	sprite_[9] = Sprite::Create(textureSprite_[9], pos_[0], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	textureSprite_[10] = TextureManager::Load("Point/Point.png");
	sprite_[10] = Sprite::Create(textureSprite_[10], pos_[1], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	textureSprite_[11] = TextureManager::Load("Point/Point2.png");
	sprite_[11] =
	    Sprite::Create(textureSprite_[11], pos_[1], {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	textureSprite_[12] = TextureManager::Load("SCORE.png");
	sprite_[12] = Sprite::Create(textureSprite_[12], {70.0f,20.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	counter_ = 0;


}

void Score::Update() 
{
	
		pos_[0] = {650.0f, 360.0f};
		pos_[1] = {630.0f, 360.0f};
	    

}

void Score::Draw() 
{ 

	if (counter_ == 0 || counter_ == 10 || counter_ == 20) {
		sprite_[0]->Draw();
	} else if (counter_ == 1||counter_==11||counter_==21) {
		sprite_[1]->Draw();
	} else if (counter_ == 2 || counter_ == 11 || counter_ == 21) {
		sprite_[2]->Draw();
	} else if (counter_ == 3 || counter_ == 12 || counter_ == 22) {
		sprite_[3]->Draw();
	} else if (counter_ == 4 || counter_ == 13 || counter_ == 23) {
		sprite_[4]->Draw();
	} else if (counter_ == 5 || counter_ == 14 || counter_ == 24) {
		sprite_[5]->Draw();
	} else if (counter_ == 6 || counter_ == 15 || counter_ == 25) {
		sprite_[6]->Draw();
	} else if (counter_ == 7 || counter_ == 16 || counter_ == 26) {
		sprite_[7]->Draw();
	} else if (counter_ == 8 || counter_ == 17 || counter_ == 27) {
		sprite_[8]->Draw();
	} else if (counter_ == 9 || counter_ == 18 || counter_ == 28) {
		sprite_[9]->Draw();
	} 
	if (counter_ >=10&&counter_<=19) {
		sprite_[10]->Draw();
	} else if (counter_ >= 20 && counter_ <= 29) {
		sprite_[11]->Draw();
	}

	sprite_[12]->Draw();

}

void Score::OnCollision() 
{ 
	counter_ = counter_ + 1; 
}

void Score::Reset()
{ counter_ = 0; }