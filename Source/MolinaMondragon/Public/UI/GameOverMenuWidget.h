// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API UGameOverMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry,
        const FFocusEvent& InFocusEvent) override;

    void SetFinalScore(int score);

protected:
    /* Properties from the widget*/
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UButton* Restart_;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UButton* BackMenu_;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UTextBlock* FinalScore_;

    UFUNCTION()
        void RestartClicked();

    UFUNCTION()
        void BackMenuClicked();
};
