// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayer.generated.h"

UCLASS()
class MOLINAMONDRAGON_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
  class USkeletalMeshComponent* Mesh_;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
  float health_;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
  class UGredMovementComponent* GridMovementComponent_;


  UFUNCTION()
      void PauseController();

  UFUNCTION()
      void GetDamage(int dmg);
  UFUNCTION()
      int GetHealth();

  UFUNCTION()
      void AddScore(int score);
  UFUNCTION()
      int GetScore();


private:
  TArray<class AEnemy*> Enemies_;
  int currentTurn_;
  bool turn_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  bool gameIsPaused;
private:
  UFUNCTION()
    void MoveUp();
  UFUNCTION()
    void MoveDown();
  UFUNCTION()
    void MoveLeft();
  UFUNCTION()
    void MoveRight();
  UFUNCTION()
    void ActivePathfindingEnemies();
  
  int playerHealth_;
  int playerScore_;

  float temporalTimer_;
public:	
  UFUNCTION()
  void NextTurn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
