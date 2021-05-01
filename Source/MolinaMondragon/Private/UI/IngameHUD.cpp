// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IngameHUD.h"
#include "UI/PauseWidget.h"
#include "UI/ScoreWidget.h"
#include "UI/HealthWidget.h"

void AIngameHUD::BeginPlay() {
    Super::BeginPlay();

    healthWidgetInstance_ = CreateWidget<UHealthWidget>(GetWorld()->PersistentLevel->GetWorld(), healthWidget_);
    healthWidgetInstance_->AddToViewport();

    scoreWidgetInstance_ = CreateWidget<UScoreWidget>(GetWorld()->PersistentLevel->GetWorld(), scoreWidget_);
    scoreWidgetInstance_->AddToViewport();
}

void AIngameHUD::CreatePause()
{
    pauseMenuWidgetInstance_ = CreateWidget<UPauseWidget>(GetWorld()->PersistentLevel->GetWorld(), pauseMenuWidget_);
    if (pauseMenuWidgetInstance_) {
        pauseMenuWidgetInstance_->AddToViewport();
    }
}

void AIngameHUD::DeletePause()
{
    if (pauseMenuWidgetInstance_) {
        pauseMenuWidgetInstance_->RemoveFromViewport();
    }
}

void AIngameHUD::SetHealthPlayer(int h)
{
    healthWidgetInstance_->SetHealth(h);
}

void AIngameHUD::SetScorePlayer(int s)
{
    scoreWidgetInstance_->SetScore(s);
}
