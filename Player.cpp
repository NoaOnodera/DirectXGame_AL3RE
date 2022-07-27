#include <cassert>
#include"Player.h"


using namespace std;
Player::Player() {

}


Player::~Player() {
	delete vectorMove_;
	delete myMath_;
}
void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	//シングルトンインスタンスを取得する

	textureHandle_ = TextureManager::Load("mario.jpg");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	

	
	worldTransform_.Initialize();

	myMath_ = new MyMath();

	worldTransform_.scale_ = { 1,1,1 };

	worldTransform_.translation_ = { 0,0,10 };


}


void Player::Rotate() {

	const float kRotateSpeed = 0.05f;
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_.y -= kRotateSpeed;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_.y += kRotateSpeed;
	}
}


void Player::Update() {
	{

		//デスフラグの立った弾を削除
		playerbullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet)
			{
				return bullet->IsDead();
			});
		Vector3 move = { 0, 0, 0 };


		Rotate();

		const float kCharacterSpeed = 0.2f;





		if (input_->PushKey(DIK_LEFT)) {
			move = { -kCharacterSpeed, 0, 0 };

		}
		else if (input_->PushKey(DIK_RIGHT)) {
			move = { kCharacterSpeed, 0, 0 };
		}
		else if (input_->PushKey(DIK_UP)) {
			move = { 0, kCharacterSpeed, 0 };
		}
		else if (input_->PushKey(DIK_DOWN)) {
			move = { 0, -kCharacterSpeed, 0 };
		}

		debugText_->SetPos(70, 100);
		debugText_->Printf("Player Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
		debugText_->SetPos(70, 130);
		debugText_->Printf("Player Rot:(%f)", worldTransform_.rotation_.y);

		//座標移動(ベクトルの加算)
		worldTransform_.translation_ += move;

		//移動限界座標
		const float kMoveLimitX = 35;
		const float kMoveLimitY = 20;
		//範囲を超えない処理worldTransform_.translation_値に制限をかける
		worldTransform_.translation_.x = myMath_->MaxNum(worldTransform_.translation_.x, -kMoveLimitX);
		worldTransform_.translation_.x = myMath_->MinNum(worldTransform_.translation_.x, +kMoveLimitX);
		worldTransform_.translation_.y = myMath_->MaxNum(worldTransform_.translation_.y, -kMoveLimitY);
		worldTransform_.translation_.y = myMath_->MinNum(worldTransform_.translation_.y, +kMoveLimitY);


		//worldTransform_.matWorld_.MatrixUpdate(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	}
	
			//キャラクタ　攻撃処理
		Attack();

		for (std::unique_ptr<PlayerBullet>& bullet : playerbullets_) {
			bullet->Update();
		}


		vectorMove_->MyUpdate(worldTransform_);
		worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	
	worldTransform_.TransferMatrix();
	

	
}



void Player::Draw(ViewProjection&viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : playerbullets_) {
		bullet->Draw(viewProjection);
	}
}


void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) 
	{
       //弾の速度
		const float kBulletSpeed = 0.5f;
		Vector3 velocity(0,0,kBulletSpeed);
		//弾を生成し、初期化
		//PlayerBullet* newBullet = new PlayerBullet();
        //Vector3 position =worldTransform_.translation_;
		Vector3 position = this->GetWorldPosition();
		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = MathUtility::Vector3TransformNormal(velocity, worldTransform_.matWorld_);
		//弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
 		newBullet->Initialize(model_,position, velocity);
	
	//弾を登録する
		playerbullets_.push_back(std::move(newBullet));
	}
}
void Player::OnCollision()
{

}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


Vector3 Player::GetRadius()
{
	Vector3 playerRadius;

	playerRadius.x = worldTransform_.scale_.x / 2;
	playerRadius.y = worldTransform_.scale_.y / 2;
	playerRadius.z = worldTransform_.scale_.z / 2;

	return playerRadius;
}



Vector3 Player::direction(const Vector3& velocity, const Matrix4& matWorld)
{
	Vector3 puts;

	puts.x = velocity.x * matWorld.m[0][0] + velocity.y * matWorld.m[1][0] + velocity.z * matWorld.m[2][0];
	puts.y = velocity.x * matWorld.m[0][1] + velocity.y * matWorld.m[1][1] + velocity.z * matWorld.m[2][1];
	puts.z = velocity.x * matWorld.m[0][2] + velocity.y * matWorld.m[1][2] + velocity.z * matWorld.m[2][3];

	return puts;

}