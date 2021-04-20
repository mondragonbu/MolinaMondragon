// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DungeonGameMode.h"
#include "Placeables/DungeonNode.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Math/UnrealMathUtility.h"


void ADungeonGameMode::BeginPlay() {

	CreatePool();

	switch (GenerationType_)
	{
	case GenerationType::None:
		break;
	case GenerationType::Cave:
		GenerateCave();
		break;

	}

	for (int i = 0; i < iterations_; i++) {
			IterateCave();
	}

}

void ADungeonGameMode::GenerateNode(FVector position, FLinearColor color, NodeType type)
{
	//GetWorld()->SpawnActor<ADungeonNode>(Ground1);
	//pool
	ADungeonNode* genNode = groundEnablePool_[0];
	groundEnablePool_.Remove(genNode);
	groundActivePool_.Add(genNode);
	//values
	genNode->SetActorLocation(position);
	genNode->SetActive(true);
	//color
	//genNode->SetColor(color);
	/*UMaterialInstanceDynamic* mi;
	mi = UMaterialInstanceDynamic::Create(genNode->Mesh->GetMaterial(0), this);
	mi->SetVectorParameterValue(TEXT("Color"), color );
	genNode->Mesh->SetMaterial(0, mi);*/
	
}
void ADungeonGameMode::GenerateCave()
{
		FMath::RandInit(69);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Generate cave"));

	for (int j = 0; j < gridSize_.Y; j++)
	{
		for (int i = 0; i < gridSize_.X; i++)
		{
			int type = FMath::RandRange(0, 100);
			FLinearColor color;
			NodeType typeNode;
			if (type < 40) {
				color = groundColor0_;
				typeNode = NodeType::Wall;
				grid_.Add(NodeType::Wall);
			}	
			else {
				color = groundColor1_;
				typeNode = NodeType::Ground;
				grid_.Add(NodeType::Ground);
			}
				
			GenerateNode(FVector(groundTileWidth_ * i, groundTileHeight_ * j, 0.f), color, typeNode);
		}
	}
	//TODO CREATE FUNCTION
	for (int i = 0; i < gridSize_.X * gridSize_.Y; i++)
	{
		groundActivePool_[i]->type_ = grid_[i];
		if (groundActivePool_[i]->type_ == NodeType::Wall)
			groundActivePool_[i]->SetColor(groundColor0_);
		else
			groundActivePool_[i]->SetColor(groundColor1_);
	}

}

void ADungeonGameMode::IterateCave()
{
		TArray<NodeType> nextGrid;

		UE_LOG(LogTemp, Warning, TEXT("--------begin iteration-----"));
		for (int iY = 0; iY < gridSize_.Y; iY++)
		{
			for (int iX = 0; iX < gridSize_.X; iX++)
			{
				int  neighbors = 0;
				//self
				int selfidx = iY * gridSize_.X + iX;
				if (grid_[selfidx] == NodeType::Wall) {
					neighbors++;
				}
				
				//top left
				if (iX == 0 || iY == 0) {
					neighbors++;

				}
				else {
					int index = iY * gridSize_.X + iX;
					index -=  gridSize_.X;
					index -= 1;
					if (grid_[index] == NodeType::Wall)
						neighbors++;

				}

				//top right
				if (iY == 0 || iX == gridSize_.X - 1) {
					//UE_LOG(LogTemp, Warning, TEXT("top right"));
					neighbors++;

				}
				else {
					int index = iY * gridSize_.X + iX;
					index -= (gridSize_.X - 1);
					if (grid_[index] == NodeType::Wall)
						neighbors++;

				}
				//top
				if (iY == 0) {
					neighbors++;

				}
				else {
					int index = iY * gridSize_.X + iX;
					index -= gridSize_.X;
					if (grid_[index] == NodeType::Wall)
						neighbors++;

				}

				
				//left
				if (iX == 0) {
					//UE_LOG(LogTemp, Warning, TEXT("left"));
					neighbors++;
				}
				else {
					int index = iY * gridSize_.X + iX;
					index -= 1;
					if (grid_[index] == NodeType::Wall)
						neighbors++;
				}

				//down left
				if (iY == gridSize_.Y - 1 || iX == 0) {
					//UE_LOG(LogTemp, Warning, TEXT("down left"));
					neighbors++;
				}
				else {
					int index = iY * gridSize_.X + iX;
					index += gridSize_.X - 1;
					if (grid_[index] == NodeType::Wall)
						neighbors++;
				}

				//down right
				if (iY == gridSize_.Y - 1 || iX == gridSize_.X - 1) {
					//UE_LOG(LogTemp, Warning, TEXT("down right"));
					neighbors++;
				}
				else {
					int index = iY * gridSize_.X + iX;
					index += gridSize_.X + 1;
					if (grid_[index] == NodeType::Wall)
						neighbors++;
				}
				//right
				if (iX == gridSize_.X - 1) {
					//UE_LOG(LogTemp, Warning, TEXT("right"));
					neighbors++;
				}
				else {
					int index = iY * gridSize_.X + iX;
					index += 1;
					if (grid_[index] == NodeType::Wall)
						neighbors++;
				}


				//down 
				if (iY == gridSize_.Y - 1) {
					//UE_LOG(LogTemp, Warning, TEXT("down"));
					neighbors++;
				}
				else {
					int index = iY * gridSize_.X + iX;
					index += gridSize_.X;
					if (grid_[index] == NodeType::Wall)
						neighbors++;
				}
				
				

				if (neighbors >= neighborsRule)
					nextGrid.Add(NodeType::Wall);
				else
					nextGrid.Add(NodeType::Ground);
			}
		}
			
		grid_ = nextGrid;
		//TODO CREATE FUNCTION
		for (int iY = 0; iY < gridSize_.Y; iY++)
		{
			for (int iX = 0; iX < gridSize_.X; iX++)
			{
				groundActivePool_[iY * gridSize_.X + iX]->type_ = grid_[iY * gridSize_.X + iX];
				if (groundActivePool_[iY * gridSize_.X + iX]->type_ == NodeType::Wall)
					groundActivePool_[iY * gridSize_.X + iX]->SetColor(groundColor0_);
				else
					groundActivePool_[iY * gridSize_.X + iX]->SetColor(groundColor1_);
			}

		}
		/*for (int i = 0; i < gridSize_.X * gridSize_.Y; i++)
		{
			groundActivePool_[i]->type_ = grid_[i];
			if (groundActivePool_[i]->type_ == NodeType::Wall)
				groundActivePool_[i]->SetColor(groundColor0_);
			else
				groundActivePool_[i]->SetColor(groundColor1_);
		}*/
}

void ADungeonGameMode::CreatePool()
{
	if(!Ground1_) return;

	for (int i = 0; i < gridSize_.X * gridSize_.Y; i++)
	{
		ADungeonNode* newNode = GetWorld()->SpawnActor<ADungeonNode>(Ground1_);
		groundEnablePool_.Add(newNode);
		newNode->SetActive(false);
		
	}
	
}

void ADungeonGameMode::GenerateLevel() {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Generate level"));
	bool colorType = true;
	for (int j = 0; j < gridSize_.X; j++)//64
	{
		colorType = !colorType;
		for (int i = 0; i < gridSize_.Y; i++)//48
		{
			colorType = !colorType;
			FLinearColor color;
			if(colorType)
				color = groundColor0_;
			else
				color = groundColor1_;
			GenerateNode(FVector(groundTileWidth_*i, groundTileHeight_*j,0.f), color, NodeType::Ground);
		}
	}

	
}

