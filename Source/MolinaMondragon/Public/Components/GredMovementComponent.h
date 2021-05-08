// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Placeables/DungeonNode.h"
#include "GredMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOLINAMONDRAGON_API UGredMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGredMovementComponent();
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
  int GridPosition_;
  
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
  
private:
   TArray<NodeType> grid_;
   class ADungeonGameMode* GM_;
   
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
  UFUNCTION()
    FVector GetWorldPosition();
  UFUNCTION()
    void MoveUp();
  UFUNCTION()
    void MoveLeft();
  UFUNCTION()
    void MoveRight();
  UFUNCTION()
    void MoveDown();
  UFUNCTION()
      int RandomWalkableNode();
  UFUNCTION()
      int RandomWalkableNodeFromLast();
  UFUNCTION()
      int ManhattanDistance(int origin, int dest);
  UFUNCTION()
      FVector Index2RowCol(int idx);
  UFUNCTION()
      int RowCol2Index(int x, int y);
};
