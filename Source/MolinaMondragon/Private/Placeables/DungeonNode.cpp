// Fill out your copyright notice in the Description page of Project Settings.


#include "Placeables/DungeonNode.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ADungeonNode::ADungeonNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	root_ = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot generation point"));
	RootComponent = root_;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ADungeonNode::BeginPlay()
{
	Super::BeginPlay();
	MI_ = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	MI_->SetVectorParameterValue(TEXT("Color"), FLinearColor::Black);
	Mesh->SetMaterial(0, MI_);
}

void ADungeonNode::SetActive(bool active)
{
	// Hides visible components
	SetActorHiddenInGame(!active);

	// Disables collision components
	SetActorEnableCollision(active);

	// Stops the Actor from ticking
	//SetActorTickEnabled(false);

}

void ADungeonNode::SetColor(FLinearColor color)
{
	MI_->SetVectorParameterValue(TEXT("Color"), color);
	//UE_LOG(LogTemp, Warning, TEXT("SET NODE COLOR"));
}

