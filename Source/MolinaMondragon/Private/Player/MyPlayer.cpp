// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemies/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DungeonGameMode.h"
#include "GameModes/DungeonPlayerController.h"
#include "UI/IngameHUD.h"
#include "Placeables/DungeonNode.h"
#include "Placeables/Door.h"
#include "GameModes/DungeonGameInstance.h"
#include "Animation/AnimMontage.h"
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
  currentTurn_ = 0;
  turn_ = true;
  for (int i = 0; i < gamemode->numberEnemy_; i++) {
      GetWorld()->SpawnActor<AEnemy>(gamemode->Enemy_);
  }
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Enemy")), actors);
 // actors_.Insert(Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)), 0);
  for (AActor* actor : actors)
  {
      AEnemy* enemy = Cast<AEnemy>(actor);
      enemy->active_ = true;
      Enemies_.Add(enemy);
  }
  UE_LOG(LogTemp, Warning, TEXT(" enemies length: %d"), Enemies_.Num());


  gamemode->SpawnFinishDoor();


}

void AMyPlayer::MoveUp()
{
  if (!turn_) return;
  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  if (gamemode->grid_[GridMovementComponent_->GridPosition_ - gamemode->gridSize_.X] == NodeType::Wall) return;
  direction_ = Direction::Up;
  FRotator rot = GetActorRotation();
  rot.Yaw = 0.0f;
  SetActorRotation(rot);
  turn_ = false;
  NextTurn();
  //UE_LOG(LogTemp, Warning, TEXT("MOVE UP"));
  GridMovementComponent_->MoveUp();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
  CheckFinish();
}

void AMyPlayer::MoveDown()
{
  if (!turn_) return;
  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  if(gamemode->grid_[GridMovementComponent_->GridPosition_ + gamemode->gridSize_.X] == NodeType::Wall) return;
  direction_ = Direction::Down;
  FRotator rot = GetActorRotation();
  rot.Yaw = 180.0f;
  SetActorRotation(rot);
  turn_ = false;
  NextTurn();
  //UE_LOG(LogTemp, Warning, TEXT("MOVE DOWN"));
  GridMovementComponent_->MoveDown();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
  CheckFinish();
}

void AMyPlayer::MoveLeft()
{
  if (!turn_) return;
  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  if (gamemode->grid_[GridMovementComponent_->GridPosition_ -1] == NodeType::Wall) return;
  direction_ = Direction::Left;
  FRotator rot = GetActorRotation();
  rot.Yaw = 270.0f;
  SetActorRotation(rot);
  turn_ = false;
  NextTurn();
  //UE_LOG(LogTemp, Warning, TEXT("MOVE LEFT"));
  GridMovementComponent_->MoveLeft();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
  CheckFinish();
}

void AMyPlayer::MoveRight()
{
  if(!turn_) return;
  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  if (gamemode->grid_[GridMovementComponent_->GridPosition_ +1] == NodeType::Wall) return;
  direction_ = Direction::Right;
  FRotator rot = GetActorRotation();
  rot.Yaw = 90.0f;
  SetActorRotation(rot);
  turn_ = false;
  NextTurn();
  //UE_LOG(LogTemp, Warning, TEXT("MOVE RIGHT"));
  GridMovementComponent_->MoveRight();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
  CheckFinish();
}
void AMyPlayer::Attack()
{
  if(!turn_) return;
  //RestartLevel(true);
  Mesh_->GetAnimInstance()->Montage_Play(AttackMontage_);
 // ->play
  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  switch (direction_)
  {
  case Direction::None:
    break;
  case Direction::Right:

    for (int i = 0; i < Enemies_.Num(); i++)
    {
      if(Enemies_[i]->GridMovementComponent_->GridPosition_ == GridMovementComponent_->GridPosition_ + 1)
        Enemies_[i]->health_--;
    }
    break;
  case Direction::Up:

    for (int i = 0; i < Enemies_.Num(); i++)
    {
      if (Enemies_[i]->GridMovementComponent_->GridPosition_ == GridMovementComponent_->GridPosition_ - gamemode->gridSize_.X)
        Enemies_[i]->health_--;
    }
    break;
  case Direction::Left:
    for (int i = 0; i < Enemies_.Num(); i++)
    {
      if (Enemies_[i]->GridMovementComponent_->GridPosition_ == GridMovementComponent_->GridPosition_ - 1)
        Enemies_[i]->health_--;
    }
    break;
  case Direction::Down:

    for (int i = 0; i < Enemies_.Num(); i++)
    {
      if (Enemies_[i]->GridMovementComponent_->GridPosition_ == GridMovementComponent_->GridPosition_ + gamemode->gridSize_.X)
        Enemies_[i]->health_--;
    }
    break;

  }
  UE_LOG(LogTemp, Warning, TEXT("PLAYER ATTACK"));
  NextTurn();
}

void AMyPlayer::ActivePathfindingEnemies()
{
   /* TArray<AActor*> Enemies;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Enemy")), Enemies);

    for (AActor* a : Enemies)
    {
        AEnemy* e = Cast<AEnemy>(a);
        e->ExecuteInternalPathfinding();
    }*/
}

void AMyPlayer::CheckFinish()
{
    ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GridMovementComponent_->GridPosition_ == gamemode->DoorFinishInstance_->GridMovementComponent_->GridPosition_) {
        UGameplayStatics::OpenLevel(GetWorld(), "Menu");
    }
}

void AMyPlayer::NextTurn()
{
  currentTurn_++;
  if (currentTurn_ == Enemies_.Num() + 1) {
    currentTurn_ = 0;
  }
  if(currentTurn_ == 0)
    turn_ = true;
  else {
    if (Enemies_[currentTurn_ - 1]->active_)
      Enemies_[currentTurn_-1]->SetTurn();
    else
      NextTurn();
  }
}



void AMyPlayer::RestartLevel(bool succes)
{
  //cueva nueva e iterar
  ADungeonGameMode* gamemode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
  gamemode->DestroyLevel();

  gamemode->GenerateCave();
  for (int i = 0; i < gamemode->iterations_; i++) {
    gamemode->IterateCave();
  }
  //activar enemigos y posicinarlos
  for (int i = 0; i < Enemies_.Num(); i++)
  {
    Enemies_[i]->SetActive(true);
    Enemies_[i]->GridMovementComponent_->grid_ = gamemode->grid_;
    Enemies_[i]->GridMovementComponent_->GridPosition_ = Enemies_[i]->GridMovementComponent_->RandomWalkableNode();
    Enemies_[i]->SetActorLocation(Enemies_[i]->GridMovementComponent_->GetWorldPosition());
  }
  //posicionar puerta y player
  GridMovementComponent_->grid_ = gamemode->grid_;
  GridMovementComponent_->GridPosition_ = GridMovementComponent_->RandomWalkableNode();
  SetActorLocation(GridMovementComponent_->GetWorldPosition());

  gamemode->SpawnFinishDoor();
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
    UDungeonGameInstance* gminstance = Cast<UDungeonGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (gminstance != nullptr) {
        gminstance->score_ = GetScore();
    }
    if (hud != nullptr) {
        if (playerHealth_ - dmg > 0) {
            playerHealth_ -= dmg;
            hud->SetHealthPlayer(playerHealth_);
        }
        else {
            //DEATH
            UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
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

 /* temporalTimer_ += DeltaTime;
  if (temporalTimer_ >= 1.0f) {
      GetDamage(10);
      AddScore(100);
      temporalTimer_ = 0.0f;
  }*/
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAction("UP", IE_Pressed, this, &AMyPlayer::MoveUp);
  PlayerInputComponent->BindAction("DOWN", IE_Pressed, this, &AMyPlayer::MoveDown);
  PlayerInputComponent->BindAction("LEFT", IE_Pressed, this, &AMyPlayer::MoveLeft);
  PlayerInputComponent->BindAction("RIGHT", IE_Pressed, this, &AMyPlayer::MoveRight);
  PlayerInputComponent->BindAction("ATTACK", IE_Pressed, this, &AMyPlayer::Attack);
  PlayerInputComponent->BindAction("PAUSE", IE_Pressed, this, &AMyPlayer::PauseController).bExecuteWhenPaused = true;
}
