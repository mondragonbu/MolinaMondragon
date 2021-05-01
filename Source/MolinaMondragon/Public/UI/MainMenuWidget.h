// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry,
        const FFocusEvent& InFocusEvent) override;
	
protected:
      /* Properties from the widget*/
      UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
      class UButton* NewGame_;

      UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
          class UButton* Exit_;

      UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
          class UButton* Credits_;

      UFUNCTION()
          void NewGameClicked();

      UFUNCTION()
          void ExitClicked();

      UFUNCTION()
          void CreditsClicked();
};
