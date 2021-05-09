// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/GredMovementComponent.h"
#include "GameModes/DungeonGameMode.h"
#include "Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Enemies/AI/EnemyAIController.h"


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
  direction_ = MovementsEnemy::Up;
  FRotator rot = GetActorRotation();
  rot.Yaw = 0.0f;
  SetActorRotation(rot);
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::MoveDown()
{
  GridMovementComponent_->MoveDown();
  direction_ = MovementsEnemy::Down;
  FRotator rot = GetActorRotation();
  rot.Yaw = 180.0f;
  SetActorRotation(rot);
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::MoveLeft()
{
  GridMovementComponent_->MoveLeft();
  direction_ = MovementsEnemy::Left;
  FRotator rot = GetActorRotation();
  rot.Yaw = 270.0f;
  SetActorRotation(rot);
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AEnemy::MoveRight()
{
  GridMovementComponent_->MoveRight();
  direction_ = MovementsEnemy::Right;
  FRotator rot = GetActorRotation();
  rot.Yaw = 90.0f;
  SetActorRotation(rot);
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
  ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  gameMode->grid_[GridMovementComponent_->GridPosition_] = NodeType::Ocupped;
  turn_ = false;
  ExecuteInternalPathfinding();
}

void AEnemy::PathFinding(int actualPosition, int originPosition)
{
    openList_.Empty();
    closedList_.Empty();
    
    //INSERT FIRST NODE IN THE OPEN LIST
    FPathInfo firstNode;
    firstNode.positionX = GridMovementComponent_->Index2RowCol(actualPosition).X;
    firstNode.positionY = GridMovementComponent_->Index2RowCol(actualPosition).Y;
    firstNode.positionFromTheStart = 0;
    firstNode.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(actualPosition, originPosition);
    firstNode.positionPlusDistance = firstNode.positionFromTheStart + firstNode.distanceToTheEnd;
    firstNode.fatherPath = nullptr;


    openList_.Add(firstNode);
    loopInPath_ = 1;
    bool loopFinished = false;
    
    while (openList_.Num() > 0 && !loopFinished)
    {       
        FPathInfo lowestScore;
        int lowestScoreNum = 1000;

        //GET THE SQUARE WITH THE LOWEST SCORE
        for (FPathInfo p : openList_) {
            if (p.positionPlusDistance < lowestScoreNum) {
                lowestScore = p;
                lowestScoreNum = p.positionPlusDistance;
            }
        }

        //REMOVE FROM THE OPEN LIST
        int positionToRemove = 0;
        for (int i = 0; i< openList_.Num();i++)
        {
            if (openList_[i].positionX == lowestScore.positionX && openList_[i].positionY == lowestScore.positionY) {
                positionToRemove = i;
            }
        }

        openList_.RemoveAt(positionToRemove);

        //ADD TO THE CLOSED LIST
        closedList_.Add(lowestScore);
        
        //CHECK NEIGHBOURDS
        ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
        for (FPathInfo p : closedList_) {           
            //RIGHT
            int rightPosition = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY) + 1;
            if (rightPosition > 0 && rightPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
                if (gameMode->grid_[rightPosition] == NodeType::Ground) {
                    FPathInfo enemyLoopRight;

                    enemyLoopRight.positionX = GridMovementComponent_->Index2RowCol(rightPosition).X;
                    enemyLoopRight.positionY = GridMovementComponent_->Index2RowCol(rightPosition).Y;
                    enemyLoopRight.positionFromTheStart = loopInPath_;
                    enemyLoopRight.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(rightPosition, originPosition);
                    enemyLoopRight.positionPlusDistance = enemyLoopRight.positionFromTheStart + enemyLoopRight.distanceToTheEnd;
                    //enemyLoopRight.fatherPath = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY);
                    FPathInfo* pathTmp = new FPathInfo();
                    pathTmp->positionX = p.positionX;
                    pathTmp->positionY = p.positionY;
                    pathTmp->positionFromTheStart = p.positionFromTheStart;
                    pathTmp->distanceToTheEnd = p.distanceToTheEnd;
                    pathTmp->positionPlusDistance = p.positionPlusDistance;
                    pathTmp->fatherPath = p.fatherPath;
                    enemyLoopRight.fatherPath = pathTmp;

                    if (enemyLoopRight.distanceToTheEnd < 1) {
                       // UE_LOG(LogTemp, Warning, TEXT("-----FIND PLAYER---%d--"), loopInPath_);
                        loopFinished = true;
                    }

                    bool isInOpenList = false;
                    int positionToUpdate = 0;
                    for (int i = 0; i < openList_.Num(); i++) {
                        if (openList_[i].positionX == enemyLoopRight.positionX && openList_[i].positionY == enemyLoopRight.positionY) {
                            isInOpenList = true;
                            positionToUpdate = i;
                        }
                    }

                    //CHECK IF IS IN CLOSED LIST
                    bool isInClosedList = false;
                    for (int i = 0; i < closedList_.Num(); i++) {
                        if (closedList_[i].positionX == enemyLoopRight.positionX && closedList_[i].positionY == enemyLoopRight.positionY) {
                            isInClosedList = true;
                        }
                    }

                    if (!isInClosedList) {
                        if (isInOpenList) {
                            if (enemyLoopRight.positionPlusDistance < openList_[positionToUpdate].positionPlusDistance) {
                                openList_[positionToUpdate].positionFromTheStart = enemyLoopRight.positionFromTheStart;
                                openList_[positionToUpdate].distanceToTheEnd = enemyLoopRight.distanceToTheEnd;
                                openList_[positionToUpdate].positionPlusDistance = enemyLoopRight.positionPlusDistance;
                                openList_[positionToUpdate].fatherPath = enemyLoopRight.fatherPath;
                            }
                        }
                        else {
                            openList_.Add(enemyLoopRight);
                        }
                    }
                    
                }
            }

            //UP
            int upPosition = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY) - gameMode->gridSize_.X;
            if (upPosition > 0 && upPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
                if (gameMode->grid_[upPosition] == NodeType::Ground) {
                    FPathInfo enemyLoopUp;

                    enemyLoopUp.positionX = GridMovementComponent_->Index2RowCol(upPosition).X;
                    enemyLoopUp.positionY = GridMovementComponent_->Index2RowCol(upPosition).Y;
                    enemyLoopUp.positionFromTheStart = loopInPath_;
                    enemyLoopUp.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(upPosition, originPosition);
                    enemyLoopUp.positionPlusDistance = enemyLoopUp.positionFromTheStart + enemyLoopUp.distanceToTheEnd;
                    //enemyLoopUp.fatherPath = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY);
                    FPathInfo* pathTmp = new FPathInfo();
                    pathTmp->positionX = p.positionX;
                    pathTmp->positionY = p.positionY;
                    pathTmp->positionFromTheStart = p.positionFromTheStart;
                    pathTmp->distanceToTheEnd = p.distanceToTheEnd;
                    pathTmp->positionPlusDistance = p.positionPlusDistance;
                    pathTmp->fatherPath = p.fatherPath;
                    enemyLoopUp.fatherPath = pathTmp;

                    if (enemyLoopUp.distanceToTheEnd < 1) {
                        //UE_LOG(LogTemp, Warning, TEXT("-----FIND PLAYER---%d--"), loopInPath_);
                        loopFinished = true;
                    }

                    bool isInOpenList = false;
                    int positionToUpdate = 0;
                    for (int i = 0; i < openList_.Num(); i++) {
                        if (openList_[i].positionX == enemyLoopUp.positionX && openList_[i].positionY == enemyLoopUp.positionY) {
                            isInOpenList = true;
                            positionToUpdate = i;
                        }
                    }

                    //CHECK IF IS IN CLOSED LIST
                    bool isInClosedList = false;
                    for (int i = 0; i < closedList_.Num(); i++) {
                        if (closedList_[i].positionX == enemyLoopUp.positionX && closedList_[i].positionY == enemyLoopUp.positionY) {
                            isInClosedList = true;
                        }
                    }

                    if (!isInClosedList) {
                        if (isInOpenList) {
                            if (enemyLoopUp.positionPlusDistance < openList_[positionToUpdate].positionPlusDistance) {
                                openList_[positionToUpdate].positionFromTheStart = enemyLoopUp.positionFromTheStart;
                                openList_[positionToUpdate].distanceToTheEnd = enemyLoopUp.distanceToTheEnd;
                                openList_[positionToUpdate].positionPlusDistance = enemyLoopUp.positionPlusDistance;
                                openList_[positionToUpdate].fatherPath = enemyLoopUp.fatherPath;
                            }
                        }
                        else {
                            openList_.Add(enemyLoopUp);
                        }
                    }       
                }
            }

            //LEFT
            int leftPosition = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY) - 1;
            if (leftPosition > 0 && leftPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
                if (gameMode->grid_[leftPosition] == NodeType::Ground) {
                    FPathInfo enemyLoopLeft;

                    enemyLoopLeft.positionX = GridMovementComponent_->Index2RowCol(leftPosition).X;
                    enemyLoopLeft.positionY = GridMovementComponent_->Index2RowCol(leftPosition).Y;
                    enemyLoopLeft.positionFromTheStart = loopInPath_;
                    enemyLoopLeft.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(leftPosition, originPosition);
                    enemyLoopLeft.positionPlusDistance = enemyLoopLeft.positionFromTheStart + enemyLoopLeft.distanceToTheEnd;
                    //enemyLoopLeft.fatherPath = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY);
                    FPathInfo* pathTmp = new FPathInfo();
                    pathTmp->positionX = p.positionX;
                    pathTmp->positionY = p.positionY;
                    pathTmp->positionFromTheStart = p.positionFromTheStart;
                    pathTmp->distanceToTheEnd = p.distanceToTheEnd;
                    pathTmp->positionPlusDistance = p.positionPlusDistance;
                    pathTmp->fatherPath = p.fatherPath;
                    enemyLoopLeft.fatherPath = pathTmp;

                    if (enemyLoopLeft.distanceToTheEnd < 1) {
                        //UE_LOG(LogTemp, Warning, TEXT("-----FIND PLAYER---%d--"), loopInPath_);
                        loopFinished = true;
                    }

                    bool isInOpenList = false;
                    int positionToUpdate = 0;
                    for (int i = 0; i < openList_.Num(); i++) {
                        if (openList_[i].positionX == enemyLoopLeft.positionX && openList_[i].positionY == enemyLoopLeft.positionY) {
                            isInOpenList = true;
                            positionToUpdate = i;
                        }
                    }


                    //CHECK IF IS IN CLOSED LIST
                    bool isInClosedList = false;
                    for (int i = 0; i < closedList_.Num(); i++) {
                        if (closedList_[i].positionX == enemyLoopLeft.positionX && closedList_[i].positionY == enemyLoopLeft.positionY) {
                            isInClosedList = true;
                        }
                    }

                    if (!isInClosedList) {
                        if (isInOpenList) {
                            if (enemyLoopLeft.positionPlusDistance < openList_[positionToUpdate].positionPlusDistance) {
                                openList_[positionToUpdate].positionFromTheStart = enemyLoopLeft.positionFromTheStart;
                                openList_[positionToUpdate].distanceToTheEnd = enemyLoopLeft.distanceToTheEnd;
                                openList_[positionToUpdate].positionPlusDistance = enemyLoopLeft.positionPlusDistance;
                                openList_[positionToUpdate].fatherPath = enemyLoopLeft.fatherPath;
                            }
                        }
                        else {
                            openList_.Add(enemyLoopLeft);
                        }
                    }        
                }
            }

            //DOWN
            int downPosition = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY) + gameMode->gridSize_.X;
            if (downPosition > 0 && downPosition < gameMode->gridSize_.X * gameMode->gridSize_.Y) {
                if (gameMode->grid_[downPosition] == NodeType::Ground) {
                    FPathInfo enemyLoopDown;

                    enemyLoopDown.positionX = GridMovementComponent_->Index2RowCol(downPosition).X;
                    enemyLoopDown.positionY = GridMovementComponent_->Index2RowCol(downPosition).Y;
                    enemyLoopDown.positionFromTheStart = loopInPath_;
                    enemyLoopDown.distanceToTheEnd = GridMovementComponent_->ManhattanDistance(downPosition, originPosition);
                    enemyLoopDown.positionPlusDistance = enemyLoopDown.positionFromTheStart + enemyLoopDown.distanceToTheEnd;
                    //enemyLoopDown.fatherPath = GridMovementComponent_->RowCol2Index(p.positionX, p.positionY);
                    FPathInfo* pathTmp = new FPathInfo();
                    pathTmp->positionX = p.positionX;
                    pathTmp->positionY = p.positionY;
                    pathTmp->positionFromTheStart = p.positionFromTheStart;
                    pathTmp->distanceToTheEnd = p.distanceToTheEnd;
                    pathTmp->positionPlusDistance = p.positionPlusDistance;
                    pathTmp->fatherPath = p.fatherPath;
                    enemyLoopDown.fatherPath = pathTmp;

                    if (enemyLoopDown.distanceToTheEnd < 1) {
                        //UE_LOG(LogTemp, Warning, TEXT("-----FIND PLAYER---%d--"), loopInPath_);
                        loopFinished = true;
                    }

                    bool isInOpenList = false;
                    int positionToUpdate = 0;
                    for (int i = 0; i < openList_.Num(); i++) {
                        if (openList_[i].positionX == enemyLoopDown.positionX && openList_[i].positionY == enemyLoopDown.positionY) {
                            isInOpenList = true;
                            positionToUpdate = i;
                        }
                    }

                    //CHECK IF IS IN CLOSED LIST
                    bool isInClosedList = false;
                    for (int i = 0; i < closedList_.Num(); i++) {
                        if (closedList_[i].positionX == enemyLoopDown.positionX && closedList_[i].positionY == enemyLoopDown.positionY) {
                            isInClosedList = true;
                        }
                    }

                    if (!isInClosedList) {
                        if (isInOpenList) {
                            if (enemyLoopDown.positionPlusDistance < openList_[positionToUpdate].positionPlusDistance) {
                                openList_[positionToUpdate].positionFromTheStart = enemyLoopDown.positionFromTheStart;
                                openList_[positionToUpdate].distanceToTheEnd = enemyLoopDown.distanceToTheEnd;
                                openList_[positionToUpdate].positionPlusDistance = enemyLoopDown.positionPlusDistance;
                                openList_[positionToUpdate].fatherPath = enemyLoopDown.fatherPath;
                            }
                        }
                        else {
                            openList_.Add(enemyLoopDown);
                        }
                    }             
                }
            }
                     
        }

        loopInPath_++;
    }

    if (!loopFinished) {
        openList_.Empty();
        closedList_.Empty();
    }

    //UE_LOG(LogTemp, Warning, TEXT("-----PATHFINDING-----"));
    BuildPath(originPosition);
    if(movementEnemy_.Num()==1)
      attackRange = true;
    else
      attackRange = false;
}

void AEnemy::BuildPath(int origin)
{
    TArray<MovementsEnemy> movement_;    
    if (closedList_.Num() > 0) {
        FPathInfo actualPointPath = closedList_.Last();

        while (actualPointPath.fatherPath != nullptr) {
            if (actualPointPath.fatherPath->positionX < actualPointPath.positionX) {
                movement_.Add(MovementsEnemy::Right);
            }
            else if (actualPointPath.fatherPath->positionX > actualPointPath.positionX) {
                movement_.Add(MovementsEnemy::Left);
            }
            else if (actualPointPath.fatherPath->positionY < actualPointPath.positionY) {
                movement_.Add(MovementsEnemy::Down);
            }
            else if (actualPointPath.fatherPath->positionY > actualPointPath.positionY) {
                movement_.Add(MovementsEnemy::Up);
            }

            actualPointPath = *actualPointPath.fatherPath;
        }

        movementEnemy_.Empty();

        for (int i = movement_.Num() - 1; i >= 0; i--) {
            movementEnemy_.Add(movement_[i]);
        }

        if (GridMovementComponent_->Index2RowCol(origin).X > actualPointPath.positionX) {
            movementEnemy_.Add(MovementsEnemy::Right);
        }
        else if (GridMovementComponent_->Index2RowCol(origin).X < actualPointPath.positionX) {
            movementEnemy_.Add(MovementsEnemy::Left);
        }
        else if (GridMovementComponent_->Index2RowCol(origin).Y > actualPointPath.positionY) {
            movementEnemy_.Add(MovementsEnemy::Down);
        }
        else if (GridMovementComponent_->Index2RowCol(origin).Y < actualPointPath.positionY) {
            movementEnemy_.Add(MovementsEnemy::Up);
        }
    }
    else {
        movementEnemy_.Add(MovementsEnemy::None);
    }
    
    //UE_LOG(LogTemp, Warning, TEXT("-----BUILD PATH-----"));
}

void AEnemy::ExecuteMovement()
{  
    if (movementEnemy_.Num() > 1) {
        switch (movementEnemy_[0])
        {
        case MovementsEnemy::None:
            actualPositionPath = GridMovementComponent_->GridPosition_;
            movementEnemy_.RemoveAt(0);
            break;
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

void AEnemy::Death()
{
  AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
  player->AddScore(10);
  ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  gameMode->grid_[GridMovementComponent_->GridPosition_] = NodeType::Ground;
  
  SetActive(false);
}

void AEnemy::SetActive(bool active)
{
  active_ = active;
  
  Mesh_->SetHiddenInGame(!active);
  Mesh_->SetVisibility(active);

}

void AEnemy::GetDamage(float damage)
{
  if(!active_)return;
  health_-= damage;
  if(health_ <= 0)
    Death();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  /*if (turn_) {
      turn_ = false;
      AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
      player->NextTurn();
      //ExecuteInternalPathfinding();
      //ExecuteMovement();
      //FTimerDelegate TimerDel;
      //FTimerHandle TimerHandle;
      //TimerDel.BindUFunction(player, FName("NextTurn"));
      //GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 1.0f, false);
      //player->NextTurn();
      //UE_LOG(LogTemp, Warning, TEXT("TURN OF : %S"),);
      GEngine->AddOnScreenDebugMessage(-1, 15.0f , FColor::Yellow, this->GetDebugName(this));

  }*/
  /*timer += DeltaTime;
  if (timer >= 0.66f) { 
      ExecuteInternalPathfinding();
      ExecuteMovement();
      timer = 0.0f;   
  }*/

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemy::Attack()
{
  AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
  player->GetDamage(5);
}
void AEnemy::SetTurn()
{
    turn_ = true;
    AEnemyAIController* controller = Cast<AEnemyAIController>(GetController());
    controller->SetTurn();
}
