// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IngameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API AIngameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

		virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
        TSubclassOf<class UPauseWidget> pauseMenuWidget_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
        TSubclassOf<class UHealthWidget> healthWidget_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
        TSubclassOf<class UScoreWidget> scoreWidget_;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
        class UPauseWidget* pauseMenuWidgetInstance_;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
        class UHealthWidget* healthWidgetInstance_;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
        class UScoreWidget* scoreWidgetInstance_;

    UFUNCTION()
        void CreatePause();

    UFUNCTION()
        void DeletePause();

    UFUNCTION()
        void SetHealthPlayer(int h);

    UFUNCTION()
        void SetScorePlayer(int s);
};
