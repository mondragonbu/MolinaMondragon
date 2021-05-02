// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"


USTRUCT(BlueprintType)
struct FPathInfo
{
    GENERATED_USTRUCT_BODY();

        int positionX = 0;
        int positionY = 0;
        int positionFromTheStart = 0;
        int distanceToTheEnd = 0;
        int positionPlusDistance = 0;
        FPathInfo* fatherPath;
};

UENUM(BlueprintType)
enum class  MovementsEnemy : uint8
{
    None     UMETA(DisplayName = "None"),
    Right      UMETA(DisplayName = "Right"),
    Up      UMETA(DisplayName = "Up"),
    Left      UMETA(DisplayName = "Left"),
    Down      UMETA(DisplayName = "Down"),
};

class AEnemy;
UCLASS()
class MOLINAMONDRAGON_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
  class USkeletalMeshComponent* Mesh_;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
  class UGredMovementComponent* GridMovementComponent_;
  UPROPERTY(EditDefaultsOnly, Category = "Pathfinding")
      uint8 maxLoopsPathfinding_ = 1;

  UFUNCTION()
    void MoveUp();
  UFUNCTION()
    void MoveDown();
  UFUNCTION()
    void MoveLeft();
  UFUNCTION()
    void MoveRight();
  UFUNCTION()
    void ExecuteInternalPathfinding();
  UFUNCTION()
    void Attack();
  UFUNCTION()
    void SetTurn();
  UFUNCTION()
  void ExecuteMovement();
  TArray<FPathInfo> openList_;
  TArray<FPathInfo> closedList_;
  TArray<MovementsEnemy> movementEnemy_;
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  void PathFinding(int actualPosition, int originPosition);
  void BuildPath(int origin);
  



  int actualPositionPath;
  int originPositionPath;

  int loopInPath_;
  float timer;

public:	
  bool turn_;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
