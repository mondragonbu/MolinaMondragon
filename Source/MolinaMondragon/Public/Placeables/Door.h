// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class MOLINAMONDRAGON_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
      class USceneComponent* root_;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
      class UStaticMeshComponent* Mesh_;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
      class UGredMovementComponent* GridMovementComponent_;
};
