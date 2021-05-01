// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    /* Properties from the widget*/
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UTextBlock* ScoreText_;
};
