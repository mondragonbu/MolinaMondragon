// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry,
        const FFocusEvent& InFocusEvent) override;

protected:
    /* Properties from the widget*/
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UButton* ContinueGame_;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UButton* ExitGame_;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
        class UButton* MenuButton_;

    UFUNCTION()
        void ContinueGame();

    UFUNCTION()
        void ExitGame();

    UFUNCTION()
        void ReturnToMenu();
};
