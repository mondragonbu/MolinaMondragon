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

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
  GridMovementComponent_->GridPosition_ = GridMovementComponent_->RandomWalkableNode();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);

  actualPositionPath = GridMovementComponent_->GridPosition_;

  AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
  originPositionPath = player->GridMovementComponent_->GridPosition_;

  loopInPath_ = 1;
  while (actualPositionPath != originPositionPath) {
      PathFinding(actualPositionPath, originPositionPath);
  }
}

void AEnemy::PathFinding(int actualPosition, int originPosition)
{
    ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

    int actualDirection = -1;
    int actualMinDist = 100;
        
    //RIGHT
    if (gameMode->grid_[actualPosition + 1] != NodeType::Wall) {
        FPathInfo enemyLoopRight;

        enemyLoopRight.positionFromTheStart = loopInPath_;
        enemyLoopRight.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(actualPosition + 1, originPosition);
        enemyLoopRight.positionPlusDistance = enemyLoopRight.positionFromTheStart + enemyLoopRight.distanceToTheEnd;

        pathInfo_.Add(enemyLoopRight);
        if (enemyLoopRight.positionPlusDistance < actualMinDist) {
            actualDirection = 1;
            actualMinDist = enemyLoopRight.positionPlusDistance;
        }
    }

    //UP
    if (gameMode->grid_[actualPosition - gameMode->gridSize_.X] != NodeType::Wall) {
        FPathInfo enemyLoopUp;
        enemyLoopUp.positionFromTheStart = loopInPath_;
        enemyLoopUp.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(actualPosition - gameMode->gridSize_.X, originPosition);
        enemyLoopUp.positionPlusDistance = enemyLoopUp.positionFromTheStart + enemyLoopUp.distanceToTheEnd;
        pathInfo_.Add(enemyLoopUp);
        if (enemyLoopUp.positionPlusDistance < actualMinDist) {
            actualDirection = 2;
            actualMinDist = enemyLoopUp.positionPlusDistance;
        }
    }

    //LEFT
    if (gameMode->grid_[actualPosition - 1] != NodeType::Wall) {
        FPathInfo enemyLoopLeft;
        enemyLoopLeft.positionFromTheStart = loopInPath_;
        enemyLoopLeft.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(actualPosition - 1, originPosition);
        enemyLoopLeft.positionPlusDistance = enemyLoopLeft.positionFromTheStart + enemyLoopLeft.distanceToTheEnd;
        pathInfo_.Add(enemyLoopLeft);
        if (enemyLoopLeft.positionPlusDistance < actualMinDist) {
            actualDirection = 3;
            actualMinDist = enemyLoopLeft.positionPlusDistance;
        }
    }

    //DOWN
    if (gameMode->grid_[actualPosition + gameMode->gridSize_.X] != NodeType::Wall) {
        FPathInfo enemyLoopDown;
        enemyLoopDown.positionFromTheStart = loopInPath_;
        enemyLoopDown.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(actualPosition + gameMode->gridSize_.X, originPosition);
        enemyLoopDown.positionPlusDistance = enemyLoopDown.positionFromTheStart + enemyLoopDown.distanceToTheEnd;
        pathInfo_.Add(enemyLoopDown);
        if (enemyLoopDown.positionPlusDistance < actualMinDist) {
            actualDirection = 4;
            actualMinDist = enemyLoopDown.positionPlusDistance;
        }
    }

    switch (actualDirection) {
    case 1: 
        actualPositionPath = actualPositionPath + 1;
        movementEnemy_.Add(MovementsEnemy::Right); 
        break;
    case 2: 
        actualPositionPath = actualPositionPath - gameMode->gridSize_.X;
        movementEnemy_.Add(MovementsEnemy::Up); 
        break;
    case 3: 
        actualPositionPath = actualPositionPath - 1;
        movementEnemy_.Add(MovementsEnemy::Left); 
        break;
    case 4: 
        actualPositionPath = actualPositionPath + gameMode->gridSize_.X;
        movementEnemy_.Add(MovementsEnemy::Down); 
        break;
    default: break;
    }

    loopInPath_++;
        
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
        default:
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
  if (timer >= 1.0f) { 
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

