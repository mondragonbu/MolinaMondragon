// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DungeonGameMode.generated.h"

/**
 * 
 */
 class ADungeonNode;
UCLASS()
class MOLINAMONDRAGON_API ADungeonGameMode : public AGameMode
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditDefaultsOnly, Category="Generation")
		TSubclassOf<ADungeonNode> Ground1;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
		FLinearColor groundColor0;
	UPROPERTY(EditDefaultsOnly, Category = "Generation")
		FLinearColor groundColor1;
	private:
		TArray<ADungeonNode*> groundEnablePool;
		TArray<ADungeonNode*> groundActivePool;
		ADungeonNode* grid [64][48];
	public:
		UFUNCTION()
		void GenerateLevel();

	protected:
		virtual void BeginPlay() override;
	private:
		void CreatePool();
		void GenerateNode(FVector position, FLinearColor color);
};
