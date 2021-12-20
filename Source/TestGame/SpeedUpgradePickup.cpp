// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUpgradePickup.h"

ASpeedUpgradePickup::ASpeedUpgradePickup()
{

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Game/PowerUpGreen.PowerUpGreen"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);

}


	void ASpeedUpgradePickup::OnOverlapBegin(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & Hit)
	{
		APickupBase::OnOverlapBegin(HitComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, Hit);
		ATopDownCharacter* theActor = Cast<ATopDownCharacter>(OtherActor);
		if (theActor)
		{
			theActor->upgradeSpeed();
			Destroy();
		}
	}
