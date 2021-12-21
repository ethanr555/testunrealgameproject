// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BaseProjectile.generated.h"

UCLASS()
class TESTGAME_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;
	UPROPERTY(BlueprintReadWrite,meta=(ExposeOnSpawn="true"), Category = Projectile)
	float scale;
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = Projectile)
	float speed;
	uint8 team;
	bool bDoesPierce;
	uint8 numberOfPierces;
	UPROPERTY(VisibleDefaultsOnly, Category = Particle)
	UParticleSystem* explosion;
	virtual void LifeSpanExpired() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireInDirection(const FVector& ShootDirection);
	void Initialize(float scale1, float speed1, float life1, uint8 team1, bool bPiercing1, uint8 pierces);
	UFUNCTION()
	void OnOverlapBeginEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	virtual void PostInitializeComponents() override;

};
