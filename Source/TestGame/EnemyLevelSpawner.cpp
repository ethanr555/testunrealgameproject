// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyLevelSpawner.h"
#include "Enemy1_AI_Controller.h"

// Sets default values
AEnemyLevelSpawner::AEnemyLevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AEnemyLevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyLevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	spawningCD -= 0.1f;
	if (enemyPointerArray.Num() < 10 && spawningCD <= 0.0f)
	{
		SpawnEnemy1(FVector(FMath::RandRange(130.0f, 1050.0f), FMath::RandRange(130.0f, 1050.0f), 0.0f), FRotator(0.0f, FMath::RandRange(-360.0f, 360.0f), 0.0f));
		spawningCD = 2.0f;
	}
	checkEnemyCount();

}

void AEnemyLevelSpawner::checkEnemyCount()
{
	for (int i = 0; i < enemyPointerArray.Num(); i++)
	{
		if (!IsValid(enemyPointerArray[i]))
		{
			enemyPointerArray.RemoveAt(i);
		}
	}
}

void AEnemyLevelSpawner::SpawnEnemy1(FVector location, FRotator rotation)
{
	UWorld* World = GetWorld();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	if (World)
	{
		AEnemy1* enemy = World->SpawnActor<AEnemy1>(location, rotation, SpawnParams);
		if (enemy)
		{
			AEnemy1_AI_Controller* enemyController = World->SpawnActor<AEnemy1_AI_Controller>(location, rotation, SpawnParams);
			if (enemyController) enemyController->Possess(enemy);
		}
		//enemy->SpawnDefaultController();
		enemyPointerArray.Add(enemy);
	}
	

}

