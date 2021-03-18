// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Placeables/DungeonNode.h"
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
		FLinearColor groundColor0_;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
		FLinearColor groundColor1_;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
	GenerationType GenerationType_;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
	FVector gridSize_;
	UPROPERTY(EditDefaultsOnly, Category = "Cave Generation")
	uint8 iterations_ = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Cave Generation")
	uint8 neighborsRule = 4;
	private:
		TArray<ADungeonNode*> groundEnablePool_;
		TArray<ADungeonNode*> groundActivePool_;
		TArray<NodeType> grid_;
	public:
		UFUNCTION()
		void GenerateLevel();

		void IterateCave();
	protected:
		virtual void BeginPlay() override;
	private:
		void CreatePool();
		void GenerateNode(FVector position, FLinearColor color, NodeType type);
		void GenerateCave();
		
};
