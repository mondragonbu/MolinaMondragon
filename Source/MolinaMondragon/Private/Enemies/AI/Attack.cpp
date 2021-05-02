// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/Attack.h"


UAttack::UAttack(FObjectInitializer const& object_initializer)
{
  NodeName = TEXT("Enemy Attack");
}

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    UE_LOG(LogTemp, Warning, TEXT("attack bt"));
    //finish with success
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
