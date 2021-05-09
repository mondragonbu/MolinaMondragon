// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/EnemyAIController.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardComponent.h"


AEnemyAIController::AEnemyAIController(FObjectInitializer const& object_initializer)
{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/MolinaMondragon/Enemies/AI/BT_Enemy.BT_Enemy'"));
		if (obj.Succeeded())
		{
				btree = Cast<UBehaviorTree>(obj.Object);
		}


		behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
		blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
		

}


void AEnemyAIController::BeginPlay()
{
		Super::BeginPlay();
		RunBehaviorTree(btree);
		behavior_tree_component->StartTree(*btree);
		blackboard->SetValueAsBool(TEXT("Turn"), false);
		blackboard->SetValueAsBool(TEXT("IsActive"), true);
}

void AEnemyAIController::OnPossess(APawn* const pawn)
{
		Super::OnPossess(pawn);
		if (blackboard)
		{
				blackboard->InitializeBlackboard(*btree->BlackboardAsset);
		}
}

UBlackboardComponent* AEnemyAIController::get_blackboard() const
{
		return blackboard;
}
void AEnemyAIController::SetTurn()
{
		if (blackboard) {
				blackboard->SetValueAsBool(TEXT("Turn"), true);
		}
		else
				UE_LOG(LogTemp, Warning, TEXT("no blackboard"));
}

void AEnemyAIController::on_updated(TArray<AActor*> const& updated_actors)
{
}
