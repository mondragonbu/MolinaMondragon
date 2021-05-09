// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Placeables/DungeonNode.h"
#include "Enemies/Enemy.h"
#include "DungeonGameMode.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class  GenerationType : uint8
{
	None     UMETA(DisplayName = "None"),
	Cave      UMETA(DisplayName = "Cave"),

};
 class ADungeonNode;
UCLASS()
class MOLINAMONDRAGON_API ADungeonGameMode : public AGameMode
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditDefaultsOnly, Category="Generation")
		TSubclassOf<ADungeonNode> Ground1_;
  UPROPERTY(EditDefaultsOnly, Category = "Generation")
      TSubclassOf<class ADoor> DoorFinish_;

	class ADoor* DoorFinishInstance_;

	UPROPERTY(EditDefaultsOnly, Category = "Generation")
		FLinearColor groundColor0_;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
		FLinearColor groundColor1_;
  UPROPERTY(EditDefaultsOnly, Category = "Generation")
    float groundTileHeight_ = 100.0f;
  UPROPERTY(EditDefaultsOnly, Category = "Generation")
    float groundTileWidth_ = 100.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
	GenerationType GenerationType_;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
	FVector gridSize_;
	UPROPERTY(EditDefaultsOnly, Category = "Cave Generation")
	uint8 iterations_ = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Cave Generation")
	uint8 neighborsRule = 4;

	//ENEMY
  UPROPERTY(EditDefaultsOnly, Category = "Enemy")
      TSubclassOf<AEnemy> Enemy_;
  UPROPERTY(EditDefaultsOnly, Category = "Enemy")
      uint8 numberEnemy_ = 1;


  TArray<NodeType> grid_;
	private:
		TArray<ADungeonNode*> groundEnablePool_;
		TArray<ADungeonNode*> groundActivePool_;

		
	public:
		UFUNCTION()
		void GenerateLevel();
    UFUNCTION()
    void DestroyLevel();
    UFUNCTION()
		void IterateCave();
    UFUNCTION()
    void GenerateCave();
    UFUNCTION()
    void SpawnFinishDoor();
	protected:
		virtual void BeginPlay() override;
	private:
		void CreatePool();
		void GenerateNode(FVector position, FLinearColor color, NodeType type);


};
