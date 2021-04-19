// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/GredMovementComponent.h"
#include "GameModes/DungeonGameMode.h"
#include "Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  Mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
  Mesh_->SetupAttachment(RootComponent);
  GridMovementComponent_ = CreateDefaultSubobject<UGredMovementComponent>("Grid Movement Component");
  loopInPath_ = 0;
  timer = 0.0f;
}

void AEnemy::MoveUp()
{
  GridMovementComponent_->MoveUp();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::MoveDown()
{
  GridMovementComponent_->MoveDown();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::MoveLeft()
{
  GridMovementComponent_->MoveLeft();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::MoveRight()
{
  GridMovementComponent_->MoveRight();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::ExecuteInternalPathfinding()
{
    actualPositionPath = GridMovementComponent_->GridPosition_;

    AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
    originPositionPath = player->GridMovementComponent_->GridPosition_;

    PathFinding(actualPositionPath, originPositionPath);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
  GridMovementComponent_->GridPosition_ = GridMovementComponent_->RandomWalkableNode();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);

  ExecuteInternalPathfinding();
}

void AEnemy::PathFinding(int actualPosition, int originPosition)
{
    ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
        
    loopInPath_ = 1;
    movementEnemy_.Empty();

    while (actualPosition != originPosition) {

        int actualDirection = -1;
        int actualMinDist = 100;

        //RIGHT
        int rightPosition = actualPosition + 1;
        if (rightPosition > 0 && rightPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
            if (gameMode->grid_[rightPosition] != NodeType::Wall) {
                FPathInfo enemyLoopRight;

                enemyLoopRight.positionFromTheStart = loopInPath_;
                enemyLoopRight.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(rightPosition, originPosition);
                enemyLoopRight.positionPlusDistance = enemyLoopRight.positionFromTheStart + enemyLoopRight.distanceToTheEnd;

                pathInfo_.Add(enemyLoopRight);
                if (enemyLoopRight.positionPlusDistance < actualMinDist) {
                    actualDirection = 1;
                    actualMinDist = enemyLoopRight.positionPlusDistance;
                }
            }
        }       

        //UP
        int upPosition = actualPosition - gameMode->gridSize_.X;
        if (upPosition > 0 && upPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
            if (gameMode->grid_[upPosition] != NodeType::Wall) {
                FPathInfo enemyLoopUp;
                enemyLoopUp.positionFromTheStart = loopInPath_;
                enemyLoopUp.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(upPosition, originPosition);
                enemyLoopUp.positionPlusDistance = enemyLoopUp.positionFromTheStart + enemyLoopUp.distanceToTheEnd;
                pathInfo_.Add(enemyLoopUp);
                if (enemyLoopUp.positionPlusDistance < actualMinDist) {
                    actualDirection = 2;
                    actualMinDist = enemyLoopUp.positionPlusDistance;
                }
            }
        }
        

        //LEFT
        int leftPosition = actualPosition - 1;
        if (leftPosition > 0 && leftPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
            if (gameMode->grid_[leftPosition] != NodeType::Wall) {
                FPathInfo enemyLoopLeft;
                enemyLoopLeft.positionFromTheStart = loopInPath_;
                enemyLoopLeft.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(leftPosition, originPosition);
                enemyLoopLeft.positionPlusDistance = enemyLoopLeft.positionFromTheStart + enemyLoopLeft.distanceToTheEnd;
                pathInfo_.Add(enemyLoopLeft);
                if (enemyLoopLeft.positionPlusDistance < actualMinDist) {
                    actualDirection = 3;
                    actualMinDist = enemyLoopLeft.positionPlusDistance;
                }
            }
        }     

        //DOWN
        int downPosition = actualPosition + gameMode->gridSize_.X;
        if (downPosition > 0 && downPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {          
            if (gameMode->grid_[downPosition] != NodeType::Wall) {
                FPathInfo enemyLoopDown;
                enemyLoopDown.positionFromTheStart = loopInPath_;
                enemyLoopDown.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(downPosition, originPosition);
                enemyLoopDown.positionPlusDistance = enemyLoopDown.positionFromTheStart + enemyLoopDown.distanceToTheEnd;
                pathInfo_.Add(enemyLoopDown);
                if (enemyLoopDown.positionPlusDistance < actualMinDist) {
                    actualDirection = 4;
                    actualMinDist = enemyLoopDown.positionPlusDistance;
                }
            }
        } 
        

        switch (actualDirection) {
        case 1:
            actualPosition = actualPosition + 1;
            movementEnemy_.Add(MovementsEnemy::Right);
            break;
        case 2:
            actualPosition = actualPosition - gameMode->gridSize_.X;
            movementEnemy_.Add(MovementsEnemy::Up);
            break;
        case 3:
            actualPosition = actualPosition - 1;
            movementEnemy_.Add(MovementsEnemy::Left);
            break;
        case 4:
            actualPosition = actualPosition + gameMode->gridSize_.X;
            movementEnemy_.Add(MovementsEnemy::Down);
            break;
        }

        loopInPath_++;
    }
        
    UE_LOG(LogTemp, Warning, TEXT("-----PATHFINDING-----"));
}

void AEnemy::ExecuteMovement()
{
    if (movementEnemy_.Num() > 1) {
        switch (movementEnemy_[0])
        {
        case MovementsEnemy::Right:
            this->MoveRight();
            actualPositionPath = GridMovementComponent_->GridPosition_;
            movementEnemy_.RemoveAt(0);
            break;
        case MovementsEnemy::Up:
            this->MoveUp();
            actualPositionPath = GridMovementComponent_->GridPosition_;
            movementEnemy_.RemoveAt(0);
            break;
        case MovementsEnemy::Left:
            this->MoveLeft();
            actualPositionPath = GridMovementComponent_->GridPosition_;
            movementEnemy_.RemoveAt(0);
            break;
        case MovementsEnemy::Down:
            this->MoveDown();
            actualPositionPath = GridMovementComponent_->GridPosition_;
            movementEnemy_.RemoveAt(0);
            break;
        }
    }
    else {
        return;
    }
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  timer += DeltaTime;
  if (timer >= 0.66f) { 
      ExecuteMovement();
      UE_LOG(LogTemp, Warning, TEXT("-----TICK ENEMY-----"));
      timer = 0.0f;   
  }
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

