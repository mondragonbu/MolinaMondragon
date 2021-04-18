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
  grid_ = GM_->grid_;
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

int UGredMovementComponent::RandomWalkableNode()
{
    GM_ = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    
    int sizegrid = GM_->gridSize_.X * GM_->gridSize_.Y;

    while(true){
        int randomNode = FMath::RandRange(0, sizegrid);
        if (grid_[randomNode] == NodeType::Ground) {
            return randomNode;
        }
    }
}

int UGredMovementComponent::ManhattanDistance(int origin, int dest)
{
    FVector originVector;
    FVector destVector;

    originVector = Index2RowCol(dest);
    destVector = Index2RowCol(origin);

    if (destVector.X == -1 || destVector.Y == -1 || originVector.X == -1 || originVector.Y == -1) {
        return -1;
    }

    return FMath::Abs(destVector.X - originVector.X) + FMath::Abs(destVector.Y - originVector.Y);
}

FVector UGredMovementComponent::Index2RowCol(int idx)
{
    GM_ = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

    if (idx < 0 || idx > GM_->gridSize_.X * GM_->gridSize_.Y ) {
        return FVector().ZeroVector; 
    }

    return FVector(idx / GM_->gridSize_.X, idx % (int)GM_->gridSize_.X, 0);
}


// Called every frame
void UGredMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

