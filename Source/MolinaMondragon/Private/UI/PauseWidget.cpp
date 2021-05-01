// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

    ContinueGame_->OnClicked.AddDynamic(this, &UPauseWidget::ContinueGame);
    ExitGame_->OnClicked.AddDynamic(this, &UPauseWidget::ExitGame);
    MenuButton_->OnClicked.AddDynamic(this, &UPauseWidget::ReturnToMenu);
}

FReply UPauseWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

    ContinueGame_->SetUserFocus(GetOwningPlayer());

    return FReply::Handled();
}

void UPauseWidget::ContinueGame()
{
    AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
    
    player->PauseController();
}

void UPauseWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), NULL, EQuitPreference::Quit, true);
}

void UPauseWidget::ReturnToMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Menu");
}
