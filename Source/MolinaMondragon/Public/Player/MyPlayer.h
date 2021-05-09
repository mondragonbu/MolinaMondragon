// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/AudioComponent.h"
#include "MyPlayer.generated.h"
UENUM(BlueprintType)
enum class  Direction : uint8
{
  None     UMETA(DisplayName = "None"),
  Right      UMETA(DisplayName = "Right"),
  Up      UMETA(DisplayName = "Up"),
  Left      UMETA(DisplayName = "Left"),
  Down      UMETA(DisplayName = "Down"),
};
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

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AUDIO")
      class USoundCue* DeathSoundCue_;

  UFUNCTION()
    void RestartLevel(bool succes);
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
  UFUNCTION()
    void Attack();

private:
  TArray<class AEnemy*> Enemies_;
  int currentTurn_;
  bool turn_;

  UAudioComponent* DeathAudioComponent_;
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
  
  UFUNCTION()
    void CheckFinish();

  int playerHealth_;
  int playerScore_;
  Direction direction_;
  float temporalTimer_;
public:	
  UFUNCTION()
  void NextTurn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
