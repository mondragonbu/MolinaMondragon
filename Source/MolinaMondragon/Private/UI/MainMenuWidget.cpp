// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

    NewGame->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGameClicked);
    Credits->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGameClicked);
    Exit->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitClicked);
}

void UMainMenuWidget::NewGameClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), "demoMap");
}

void UMainMenuWidget::ExitClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), NULL, EQuitPreference::Quit, true);
}
