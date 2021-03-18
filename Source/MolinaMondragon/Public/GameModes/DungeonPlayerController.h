// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API ADungeonPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	UFUNCTION()
	void IterateCave();
};
