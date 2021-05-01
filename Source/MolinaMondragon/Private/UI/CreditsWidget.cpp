// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreditsWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainMenuHud.h"

void UCreditsWidget::NativeConstruct() {
    Super::NativeConstruct();

    creditsOff_->OnClicked.AddDynamic(this, &UCreditsWidget::BackToMenu);
    creditsOff_->SetUserFocus(GetOwningPlayer());
}

void UCreditsWidget::BackToMenu()
{
    AMainMenuHud* menu = Cast<AMainMenuHud>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    menu->changeToCredits(false);
}
