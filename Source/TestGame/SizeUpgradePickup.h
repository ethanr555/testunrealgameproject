// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "SizeUpgradePickup.generated.h"

/**
 * 
 */
UCLASS()
class TESTGAME_API ASizeUpgradePickup : public APickupBase
{
	GENERATED_BODY()
public:
	ASizeUpgradePickup();
	virtual void OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
	
};
