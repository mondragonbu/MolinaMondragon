// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GredMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DungeonGameMode.h"

// Sets default values for this component's properties
UGredMovementComponent::UGredMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
  GridPosition_ = 0;
	// ...
}


// Called when the game starts
void UGredMovementComponent::BeginPlay()
{
	Super::BeginPlay();
  GM_ = Cast<ADungeonGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
  GetWorldPosition();
	// ...
	
}

FVector UGredMovementComponent::GetWorldPosition()
{
 
  int Y =  GridPosition_ / GM_->gridSize_.X ;
  int X = GridPosition_- Y * GM_->gridSize_.X;
  UE_LOG(LogTemp, Warning, TEXT(" Y: %d X: %d"),Y ,X);
  return FVector(X*GM_->groundTileWidth_, Y*GM_->groundTileHeight_,0) ;
}

void UGredMovementComponent::MoveUp()
{
  GridPosition_ -= GM_->gridSize_.X;
}

void UGredMovementComponent::MoveLeft()
{
  GridPosition_ -= 1;
}

void UGredMovementComponent::MoveRight()
{
  GridPosition_ += 1;
}

void UGredMovementComponent::MoveDown()
{
  GridPosition_ += GM_->gridSize_.X;
}


// Called every frame
void UGredMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

