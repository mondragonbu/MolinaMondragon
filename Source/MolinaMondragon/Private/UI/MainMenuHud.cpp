// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuHud.h"
#include "UI/MainMenuWidget.h"

void AMainMenuHud::BeginPlay() {
    Super::BeginPlay();

    mainMenuWidgetInstance_ = CreateWidget<UMainMenuWidget>(GetWorld()->PersistentLevel->GetWorld(), mainMenuWidget_);
    mainMenuWidgetInstance_->AddToViewport();

}