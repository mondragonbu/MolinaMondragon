// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/Move.h"
#include "Enemies/AI/EnemyAIController.h"
#include "Enemies/Enemy.h"

UMove::UMove(FObjectInitializer const& object_initializer)
{
    NodeName = TEXT("Enemy Move");
}

EBTNodeResult::Type UMove::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    UE_LOG(LogTemp, Warning, TEXT("move bt"));

    auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
    AEnemy* enemy = Cast<AEnemy>(cont->GetPawn());
    enemy->ExecuteMovement();
    //finish with success
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

