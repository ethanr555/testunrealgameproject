// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseProjectile.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PickupBase.h"
#include "PowerUpList.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy1.generated.h"

UCLASS()
class TESTGAME_API AEnemy1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void RotateRight(float Value);
	UPROPERTY(EditAnywhere, Category = AI)
	UBehaviorTree* behavior_tree;
	bool bMoveForward;
	bool bRotateLeft;
	bool bRotateRight;
	void ToggleRotate(bool direction);
	void ToggleForwardMovement();
	UFUNCTION()
	void OnOverlapBeginProjectile(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	virtual void PostInitializeComponents() override;
	void SpawnPowerUp();
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* EnemyMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* EnemyMaterialInstance;




};
