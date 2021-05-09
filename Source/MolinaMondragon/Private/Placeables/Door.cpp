// Fill out your copyright notice in the Description page of Project Settings.


#include "Placeables/Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/GredMovementComponent.h"
#include "Components/SceneComponent.h"
#include "GameModes/DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  root_ = CreateDefaultSubobject<USceneComponent>(TEXT("root_"));
  RootComponent = root_;
  Mesh_ = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
  Mesh_->SetupAttachment(GetRootComponent());
  GridMovementComponent_ = CreateDefaultSubobject<UGredMovementComponent>("Grid Movement Component");
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
  GridMovementComponent_->GridPosition_ = GridMovementComponent_->RandomWalkableNodeFromLast();
  FVector worldPos = GridMovementComponent_->GetWorldPosition();
  SetActorLocation(worldPos);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

