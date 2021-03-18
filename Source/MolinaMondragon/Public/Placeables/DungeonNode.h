// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonNode.generated.h"


UENUM(BlueprintType)
enum class  NodeType : uint8
{
	Ground     UMETA(DisplayName = "Ground"),
	Wall      UMETA(DisplayName = "Wall"),

};
UCLASS()
class MOLINAMONDRAGON_API ADungeonNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonNode();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		class USceneComponent* root_;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		NodeType type_;
private:
	class UMaterialInstanceDynamic* MI_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void SetActive(bool active);
	UFUNCTION()
	void SetColor(FLinearColor color);
};
