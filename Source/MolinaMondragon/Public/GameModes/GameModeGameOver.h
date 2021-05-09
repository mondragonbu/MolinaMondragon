// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeGameOver.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API AGameModeGameOver : public AGameMode
{
	GENERATED_BODY()
	
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InGame", Meta = (BlueprintProtected = "true"))
        TSubclassOf<class UUserWidget> GameOverHUD;

    UPROPERTY()
        class UUserWidget* CurrentWidget;
};
