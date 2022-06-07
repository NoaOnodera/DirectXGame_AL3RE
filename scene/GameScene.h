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
#include <DirectXMath.h>
#include"MyMath.h"
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

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;//テクスチャハンドル
	Model* model_ = nullptr;//3Dモデル
	float viewAngle = 0.0f;//カメラ上方向の角度
	WorldTransform worldTransforms_[100];//ワールドトランスフォーム
	ViewProjection viewProjection_;//ビュープロジェクション
	DebugCamera* debugCamera_ = nullptr;//デバッグカメラ
	MyMath* myMath_ = nullptr;

public:
	enum PartId {
		kRoot,//大元
		kSpine,//脊椎
		kChest,//胸
		kHead,//頭
		kArmL,//左腕
        kArmR,//右腕
		kHip,//尻
		kLegL,//左足
		kLegR,//右足


		kNumPartId
	};
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
