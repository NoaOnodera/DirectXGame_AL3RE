#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include "MyMath.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Skydome.h"
#include"Collider.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	
  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;//テクスチャハンドル
	DebugCamera* debugCamera_ = nullptr;//デバッグカメラ
	Collider* collider_ = nullptr;
	ViewProjection viewProjection_;//ビュープロジェクション
	WorldTransform worldTransform_;
    std::unique_ptr<Player>player_;
	std::unique_ptr<Enemy>enemy_;
	std::unique_ptr<EnemyBullet>enemyBullet_;
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	bool isDebugCameraActive_ = false;
	
	
};
