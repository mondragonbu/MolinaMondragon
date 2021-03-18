// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DungeonPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DungeonGameMode.h"

void ADungeonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent) {
		InputComponent->BindAction("IterateCave",IE_Pressed,this, &ADungeonPlayerController::IterateCave);
	}
}

void ADungeonPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonPlayerController::IterateCave()
{
	ADungeonGameMode* GM = (ADungeonGameMode*)UGameplayStatics::GetGameMode(GetWorld());
	GM->IterateCave();
}
