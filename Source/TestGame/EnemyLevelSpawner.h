// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy1.h"
#include "EnemyLevelSpawner.generated.h"

UCLASS()
class TESTGAME_API AEnemyLevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyLevelSpawner();
	TArray<AEnemy1*> enemyPointerArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void checkEnemyCount();
	void SpawnEnemy1(FVector location, FRotator rotation);
	float spawningCD;

};
