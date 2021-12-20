// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownCharacter.generated.h"

UCLASS()
class TESTGAME_API ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATopDownCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	UFUNCTION()
	void Fire(FVector LaunchDirection);
	UFUNCTION()
	void FireRight(float Value);
	UFUNCTION()
	void FireTop(float Value);
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TopDownCamera;
	FVector currentVelocity;
	FVector currentFacing;
	FVector fireDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	FVector cameraDistance;
	int fireRateCD;
	int fireRate;
	FVector firingDirection;
	float projectileScale;
	float projectileSpeed;
	float projectileLifeSpan;
	void upgradeSpeed();
	void upgradeSize();
	void upgradeFireRate();
	void upgradeLifeSpan();
	

};
