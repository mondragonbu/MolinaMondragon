// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
    if (MainMenuHUD != nullptr) {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuHUD);
    }
}
