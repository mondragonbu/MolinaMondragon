// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameOverHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API AGameOverHUD : public AHUD
{
	GENERATED_BODY()
	
public:

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
        TSubclassOf<class UGameOverMenuWidget> gameOverWidget_;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
        class UGameOverMenuWidget* gameOverWidgetInstance_;
};
