// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    void SetHealth(int health);
protected:
    /* Properties from the widget*/
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UProgressBar* HealthPlayer_;
};
