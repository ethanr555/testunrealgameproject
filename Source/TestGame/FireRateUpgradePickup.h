// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "FireRateUpgradePickup.generated.h"

/**
 * 
 */
UCLASS()
class TESTGAME_API AFireRateUpgradePickup : public APickupBase
{
	GENERATED_BODY()
public:
	AFireRateUpgradePickup();
	virtual void OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;

	
};
