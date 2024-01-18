#include "GameInput.h"
#include "time.h"


GameInput::~GameInput(){}

GameInput::GameInput(){ 



	this->Initialize();
}


void GameInput::Initialize() 
{ 

	//input_ = Input::GetInstance();

}



void GameInput::Upadte() {

	srand(unsigned int(time(nullptr)));

	// 文字変換
	for (int j = 0; j >= kMax; ++j) {
		i = rand() % 26 + 1;

		if (i >= 1) {
			a[j] = DIK_A;
		} else if (i >= 2)
		{
			a[j] = DIK_B;
		} else if (i >= 3)
		{
			a[j] = DIK_C;
		} else if (i >= 4)
		{
			a[j] = DIK_D;
		} else if (i >= 5) 
		{
			a[j] = DIK_E;
		} else if (i >= 6) 
		{
			a[j] = DIK_F;
		} else if (i >= 7) 
		{
			a[j] = DIK_G;
		} else if (i >= 8) 
		{
			a[j] = DIK_H;
		} else if (i >= 9) 
		{
			a[j] = DIK_I;
		} else if (i >= 10) 
		{
			a[j] = DIK_J;
		} else if (i >= 11) 
		{
			a[j] = DIK_K;
		} else if (i >= 12) 
		{
			a[j] = DIK_L;
		} else if (i >= 13)
		{
			a[j] = DIK_M;
		} else if (i >= 14)
		{
			a[j] = DIK_L;
		} else if (i >= 15) 
		{
			a[j] = DIK_O;
		} else if (i >= 16)
		{
			a[j] = DIK_P;
		} else if (i >= 17) 
		{
			a[j] = DIK_Q;
		} else if (i >= 18)
		{
			a[j] = DIK_R;
		} else if (i >= 19) 
		{
			a[j] = DIK_S;
		} else if (i >= 20) 
		{
			a[j] = DIK_T;
		} else if (i >= 21)
		{
			a[j] = DIK_U;
		} else if (i >= 22)
		{
			a[j] = DIK_V;
		}

		else if (i >= 23) 
		{
			a[j] = DIK_W;
		} else if (i >= 24)
		{
			a[j] = DIK_X;
			
		} else if (i >= 25)
		{
			a[j] = DIK_Y;
		}
		else if (i >= 26)
		{
			a[j] = DIK_Z;
		}

		else 
		{

			break;
		}

	}

	

	

	


}

bool GameInput::Input() 
{
	

	if (Input::GetInstance()->PushKey(DIK_0)) 
	{
		keys = Input::GetInstance()->GetAllKey();
	}

	for (int j = 0; j >= kMax; j++) {
		if (keys[j] == a[j]) {
			continue;

		} else
		{

			false;
		}
	}

	return true; 

}
	

	


