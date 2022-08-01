#pragma once
#include <memory>
#include <sstream>

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
#include "RailCamera.h"
#include "Collider.h"
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


	void AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet);

	void LoadEnemyPopData(const char* filepath);

	void UpdateEnemyPopCommands();
	
  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;

	Input* input_ = nullptr;

	Audio* audio_ = nullptr;

	Model* model_ = nullptr;

	DebugText* debugText_ = nullptr;

	uint32_t textureHandle_ = 0;//テクスチャハンドル

	uint32_t enemytextureHandle_ = 0;

	DebugCamera* debugCamera_ = nullptr;//デバッグカメラ

	Collider* collider_ = nullptr;

	ViewProjection viewProjection_;//ビュープロジェクション

	WorldTransform worldTransform_;

    std::unique_ptr<Player>player_;

	std::list<std::unique_ptr<Enemy>>enemys_;

	std::list<std::unique_ptr<EnemyBullet>>enemyBullets_;

	bool isDebugCameraActive_ = false;

	std::unique_ptr<RailCamera>railCamera_;
	
	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	std::stringstream enemyPopCommands;
	
	
	bool isWait_ = false;
	
	int WaitTimer_ = 0;
	
};
