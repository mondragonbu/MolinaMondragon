// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/CalculatePathFinding.h"
#include "Enemies/Enemy.h"
#include "Enemies/AI/EnemyAIController.h"

UCalculatePathFinding::UCalculatePathFinding(FObjectInitializer const& object_initializer) 
{
  NodeName = TEXT("Calculate Path Finding");
}

EBTNodeResult::Type UCalculatePathFinding::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
    AEnemy* enemy = Cast<AEnemy>(cont->GetPawn());
    enemy->ExecuteInternalPathfinding();
   
    //finish with success
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
