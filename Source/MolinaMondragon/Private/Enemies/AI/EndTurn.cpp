// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/EndTurn.h"
#include "Enemies/AI/EnemyAIController.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayer.h"

UEndTurn::UEndTurn(FObjectInitializer const& object_initializer)
{
    NodeName = TEXT("End enemy's turn");
}

EBTNodeResult::Type UEndTurn::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    UE_LOG(LogTemp, Warning, TEXT("end turn bt"));
    //finish with success
    auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
    cont->get_blackboard()->SetValueAsBool(TEXT("Turn"), false);
    AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
    player->NextTurn();
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

