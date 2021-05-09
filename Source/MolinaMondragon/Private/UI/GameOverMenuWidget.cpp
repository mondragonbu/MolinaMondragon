// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameOverMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

    Restart_->OnClicked.AddDynamic(this, &UGameOverMenuWidget::RestartClicked);
    Restart_->SetUserFocus(GetOwningPlayer());
    BackMenu_->OnClicked.AddDynamic(this, &UGameOverMenuWidget::BackMenuClicked);
}

FReply UGameOverMenuWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

    Restart_->SetUserFocus(GetOwningPlayer());

    return FReply::Handled();
}

void UGameOverMenuWidget::SetFinalScore(int score)
{
    FText scoreText;
    FString num = FString(("SCORE:")) + FString::FromInt(score);
    scoreText = FText::FromString(num);
    FinalScore_->SetText(scoreText);
}

void UGameOverMenuWidget::RestartClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), "demoMap");
}

void UGameOverMenuWidget::BackMenuClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Menu");
}
