// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemies/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DungeonGameMode.h"
#include "GameModes/DungeonPlayerController.h"
#include "UI/IngameHUD.h"

#include "Components/GredMovementComponent.h"
// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  Mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
  Mesh_->SetupAttachment(RootComponent);
  GridMovementComponent_ = CreateDefaultSubobject<UGredMovementComponent>("Grid Movement Component");

  gameIsPaused = false;
  playerHealth_ = 100;
  playerScore_ = 0;
  temporalTimer_ = 0.0f;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
  
  GridMovementComponent_->GridPosition_ = GridMovementComponent_->RandomWalkableNode();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);

  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

  for (int i = 0; i < gamemode->numberEnemy_; i++) {
      GetWorld()->SpawnActor<AEnemy>(gamemode->Enemy_);
  }
}

void AMyPlayer::MoveUp()
{
  UE_LOG(LogTemp, Warning, TEXT("MOVE UP"));
  GridMovementComponent_->MoveUp();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AMyPlayer::MoveDown()
{
  UE_LOG(LogTemp, Warning, TEXT("MOVE DOWN"));
  GridMovementComponent_->MoveDown();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AMyPlayer::MoveLeft()
{
  UE_LOG(LogTemp, Warning, TEXT("MOVE LEFT"));
  GridMovementComponent_->MoveLeft();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AMyPlayer::MoveRight()
{
  UE_LOG(LogTemp, Warning, TEXT("MOVE RIGHT"));
  GridMovementComponent_->MoveRight();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

void AMyPlayer::ActivePathfindingEnemies()
{
    TArray<AActor*> Enemies;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Enemy")), Enemies);

    for (AActor* a : Enemies)
    {
        AEnemy* e = Cast<AEnemy>(a);
        e->ExecuteInternalPathfinding();
    }
}

void AMyPlayer::PauseController()
{
    AIngameHUD* hud = Cast<AIngameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    ADungeonPlayerController* player = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    if (gameIsPaused) {
        hud->DeletePause();
        gameIsPaused = false;
        player->SetPause(gameIsPaused);
        player->SetInputMode(FInputModeGameOnly());
    }
    else {
        hud->CreatePause();
        gameIsPaused = true;
        player->SetPause(gameIsPaused);
        player->SetInputMode(FInputModeGameAndUI());
    }

}

void AMyPlayer::GetDamage(int dmg)
{
    AIngameHUD* hud = Cast<AIngameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (hud != nullptr) {
        if (playerHealth_ - dmg > 0) {
            playerHealth_ -= dmg;
            hud->SetHealthPlayer(playerHealth_);
        }
        else {
            //DEATH
        }
    }  
}

int AMyPlayer::GetHealth()
{
    return playerHealth_;
}

void AMyPlayer::AddScore(int score)
{
    AIngameHUD* hud = Cast<AIngameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    playerScore_ += score;
    if (hud != nullptr) {
        hud->SetScorePlayer(playerScore_);
    }
}

int AMyPlayer::GetScore()
{
    return playerScore_;
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  temporalTimer_ += DeltaTime;
  if (temporalTimer_ >= 1.0f) {
      GetDamage(1);
      AddScore(100);
      temporalTimer_ = 0.0f;
  }
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAction("UP", IE_Pressed, this, &AMyPlayer::MoveUp);
  PlayerInputComponent->BindAction("DOWN", IE_Pressed, this, &AMyPlayer::MoveDown);
  PlayerInputComponent->BindAction("LEFT", IE_Pressed, this, &AMyPlayer::MoveLeft);
  PlayerInputComponent->BindAction("RIGHT", IE_Pressed, this, &AMyPlayer::MoveRight);
  PlayerInputComponent->BindAction("PAUSE", IE_Pressed, this, &AMyPlayer::PauseController).bExecuteWhenPaused = true;
}

