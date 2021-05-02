// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOLINAMONDRAGON_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
		AEnemyAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
		void BeginPlay() override;
		void OnPossess(APawn* const pawn) override;
		class UBlackboardComponent* get_blackboard() const;
		UFUNCTION()
		void SetTurn();

private:
		UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
				class UBehaviorTreeComponent* behavior_tree_component;

		UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
				class UBehaviorTree* btree;
		UFUNCTION()
				void on_updated(TArray<AActor*> const& updated_actors);
		class UBlackboardComponent* blackboard;
};
