// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/Attack.h"
#include "Enemies/AI/EnemyAIController.h"
#include "Enemies/Enemy.h"

UAttack::UAttack(FObjectInitializer const& object_initializer)
{
  NodeName = TEXT("Enemy Attack");
}

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    UE_LOG(LogTemp, Warning, TEXT("attack bt"));
    //finish with success
    auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
    AEnemy* enemy = Cast<AEnemy>(cont->GetPawn());
    enemy->Attack();
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
