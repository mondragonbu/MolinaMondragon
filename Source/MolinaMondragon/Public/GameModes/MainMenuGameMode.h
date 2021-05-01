// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InGame", Meta = (BlueprintProtected = "true"))
        TSubclassOf<class UUserWidget> MainMenuHUD;

    UPROPERTY()
        class UUserWidget* CurrentWidget;
};
