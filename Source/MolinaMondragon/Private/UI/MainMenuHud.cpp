// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuHud.h"
#include "UI/MainMenuWidget.h"
#include "UI/CreditsWidget.h"

void AMainMenuHud::BeginPlay() {
    Super::BeginPlay();

    mainMenuWidgetInstance_ = CreateWidget<UMainMenuWidget>(GetWorld()->PersistentLevel->GetWorld(), mainMenuWidget_);
    mainMenuWidgetInstance_->AddToViewport();

    creditsWidgetInstance_ = CreateWidget<UCreditsWidget>(GetWorld()->PersistentLevel->GetWorld(), creditsWidget_);
    creditsWidgetInstance_->AddToViewport();
    creditsWidgetInstance_->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuHud::changeToCredits(bool ch)
{
    if (ch) {
        mainMenuWidgetInstance_->SetVisibility(ESlateVisibility::Hidden);
        creditsWidgetInstance_->SetVisibility(ESlateVisibility::Visible);
    }
    else {
        mainMenuWidgetInstance_->SetVisibility(ESlateVisibility::Visible);
        creditsWidgetInstance_->SetVisibility(ESlateVisibility::Hidden);
    }
}
