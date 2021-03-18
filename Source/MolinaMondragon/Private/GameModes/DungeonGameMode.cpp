// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DungeonGameMode.h"
#include "Placeables/DungeonNode.h"
#include "Materials/MaterialInstanceDynamic.h"

void ADungeonGameMode::BeginPlay() {
	CreatePool();
	GenerateLevel();
}

void ADungeonGameMode::GenerateNode(FVector position, FLinearColor color)
{
	//GetWorld()->SpawnActor<ADungeonNode>(Ground1);
	//pool
	ADungeonNode* genNode = groundEnablePool[0];
	groundEnablePool.Remove(genNode);
	groundActivePool.Add(genNode);
	//values
	genNode->SetActorLocation(position);
	genNode->SetActive(true);
	//color
	UMaterialInstanceDynamic* mi;
	mi = UMaterialInstanceDynamic::Create(genNode->Mesh->GetMaterial(0), this);
	mi->SetVectorParameterValue(TEXT("Color"), color );
	genNode->Mesh->SetMaterial(0, mi);
	
}
void ADungeonGameMode::CreatePool()
{
	for (int i = 0; i < 64*48; i++)
	{
		ADungeonNode* newNode = GetWorld()->SpawnActor<ADungeonNode>(Ground1);
		groundEnablePool.Add(newNode);
		newNode->SetActive(false);
		
	}
	
}

void ADungeonGameMode::GenerateLevel() {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Generate level"));
	bool colorType = true;
	for (int j = 0; j < 64; j++)//64
	{
		colorType = !colorType;
		for (int i = 0; i < 48; i++)//48
		{
			colorType = !colorType;
			FLinearColor color;
			if(colorType)
				color = groundColor0;
			else
				color = groundColor1;
			GenerateNode(FVector(100*i, 100*j,0.f), color);
		}
	}

	
}