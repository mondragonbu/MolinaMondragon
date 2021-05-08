// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GameModeGameOver.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AGameModeGameOver::BeginPlay()
{
    if (GameOverHUD != nullptr) {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverHUD);
    }
}
