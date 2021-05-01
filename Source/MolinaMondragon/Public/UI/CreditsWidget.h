// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

protected:
    /* Properties from the widget*/
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UTextBlock* mikelText_;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UTextBlock* alexText_;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UButton* creditsOff_;

    UFUNCTION()
        void BackToMenu();
};
