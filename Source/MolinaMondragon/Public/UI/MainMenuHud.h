// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHud.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API AMainMenuHud : public AHUD
{
	GENERATED_BODY()
	
public:

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
        TSubclassOf<class UMainMenuWidget> mainMenuWidget_;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
        class UMainMenuWidget* mainMenuWidgetInstance_;

};
