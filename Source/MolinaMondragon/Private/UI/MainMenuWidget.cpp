// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

    NewGame_->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGameClicked);
    NewGame_->SetUserFocus(GetOwningPlayer());
    Credits_->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGameClicked);
    Exit_->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitClicked);
}

FReply UMainMenuWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
    
    NewGame_->SetUserFocus(GetOwningPlayer());

    return FReply::Handled();
}

void UMainMenuWidget::NewGameClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), "demoMap");
}

void UMainMenuWidget::ExitClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), NULL, EQuitPreference::Quit, true);
}
