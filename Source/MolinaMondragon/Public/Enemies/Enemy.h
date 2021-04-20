// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"


USTRUCT(BlueprintType)
struct FPathInfo
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float positionFromTheStart = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float distanceToTheEnd = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float positionPlusDistance = 0.0f;
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

  TArray<FPathInfo> pathInfo_;
  TArray<MovementsEnemy> movementEnemy_;
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  void PathFinding(int actualPosition, int originPosition);
  void ExecuteMovement();

  int actualPositionPath;
  int originPositionPath;

  int loopInPath_;
  float timer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
