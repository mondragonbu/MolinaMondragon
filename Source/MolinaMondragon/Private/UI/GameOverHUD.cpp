// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverHUD.h"
#include "UI/GameOverMenuWidget.h"
#include "Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DungeonGameInstance.h"

void AGameOverHUD::BeginPlay() {
    Super::BeginPlay();

    gameOverWidgetInstance_ = CreateWidget<UGameOverMenuWidget>(GetWorld()->PersistentLevel->GetWorld(), gameOverWidget_);
    gameOverWidgetInstance_->AddToViewport();

    UDungeonGameInstance* gminstance = Cast<UDungeonGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    gameOverWidgetInstance_->SetFinalScore(gminstance->score_);
}

