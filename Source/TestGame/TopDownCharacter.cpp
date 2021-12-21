// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacter.h"

// Sets default values
ATopDownCharacter::ATopDownCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	check(TopDownCamera != nullptr);
	//cameraDistance = FVector(-600.0f, 0.0f, 5000.0f);
	//TopDownCamera->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	TopDownCamera->SetWorldLocation(cameraDistance);
	TopDownCamera->SetWorldRotation(FRotator(300.0f, 0.0f, 0.0f));
	currentVelocity = FVector(0.0f, 0.0f, 0.0f);
	currentFacing = FVector(0.0f, 0.0f, 0.0f);
	fireRateCD = 0;
	fireRate = 50;
	firingDirection = FVector(0.0f, 0.0f, 0.0f);
	projectileScale = 0.5f;
	projectileSpeed = 600.0f;
	projectileLifeSpan = 1.0f;
	UCharacterMovementComponent* temporary = GetCharacterMovement();
	temporary->MaxWalkSpeed = 500.0f;

}

// Called when the game starts or when spawned
void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	if (firingDirection != FVector(0.0f, 0.0f, 0.0f))
	{
		currentFacing = FVector(firingDirection.X, firingDirection.Y, firingDirection.Z);
	}
	else
	{
	if (currentVelocity.X < 0)
	{
		currentFacing.X = -1.f;
	}
	else if (currentVelocity.X > 0)
	{
		currentFacing.X = 1.0f;
	}
	else
	{
		currentFacing.X = 0.0f;
	}
	if (currentVelocity.Y < 0)
	{
		currentFacing.Y = -1.0f;
	}
	else if (currentVelocity.Y > 0)
	{
		currentFacing.Y = 1.0f;
	}
	else
	{
		currentFacing.Y = 0.0f;
	}
	}
	if (currentVelocity.X != 0 || currentVelocity.Y != 0 || firingDirection.X != 0 || firingDirection.Y != 0)
	{
		Controller->SetControlRotation(currentFacing.ToOrientationRotator());
	}
	TopDownCamera->SetWorldLocation(GetActorLocation() + cameraDistance);
	if (fireRateCD > 0) fireRateCD -= 1;

}

// Called to bind functionality to input
void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATopDownCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATopDownCharacter::MoveRight);
	PlayerInputComponent->BindAxis("FireTop", this, &ATopDownCharacter::FireTop);
	PlayerInputComponent->BindAxis("FireRight", this, &ATopDownCharacter::FireRight);
	PlayerInputComponent->BindAction("IncreaseSpeed", IE_Pressed, this, &ATopDownCharacter::upgradeSpeed);
	PlayerInputComponent->BindAction("IncreaseSize", IE_Pressed, this, &ATopDownCharacter::upgradeSize);
	PlayerInputComponent->BindAction("IncreaseFireRate", IE_Pressed, this, &ATopDownCharacter::upgradeFireRate);
	PlayerInputComponent->BindAction("IncreaseLifeSpan", IE_Pressed, this, &ATopDownCharacter::upgradeLifeSpan);


}

void ATopDownCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	currentVelocity.X = Value;

}

void ATopDownCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
	currentVelocity.Y = Value;
}

void ATopDownCharacter::Fire(FVector LaunchDirection)
{
	if (ProjectileClass)
	{


		MuzzleOffset.Set(0.0f, 0.0f, 5.0f);
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetControlRotation()).TransformVector(MuzzleOffset);

		FRotator MuzzleRotation = GetControlRotation();
		MuzzleRotation.Pitch += 0.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->Initialize(projectileScale, projectileSpeed, projectileLifeSpan, 1, false, 0);
				//Projectile->FinishSpawning( FTransform(MuzzleRotation, MuzzleLocation));
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}


void ATopDownCharacter::FireRight(float Value)
{
	if (Value != 0)
	{
		
		if (Value < 0)
		{
			firingDirection = FVector(firingDirection.X, -1.0f, firingDirection.Z);
			
		}
		else if (Value > 0)
		{
			firingDirection = FVector(firingDirection.X, 1.0f, firingDirection.Z);
		}
		if (fireRateCD <= 0) { Fire(firingDirection); fireRateCD = fireRate; }
	}
	else
	{
		firingDirection = FVector(firingDirection.X, 0.0f, firingDirection.Z);
	}

}

void ATopDownCharacter::FireTop(float Value)
{
	if (Value != 0)
	{
		if (Value < 0)
		{
			firingDirection = FVector(-1.0f, firingDirection.Y, firingDirection.Z);
		}
		else if (Value > 0)
		{
			firingDirection = FVector(1.0f, firingDirection.Y, firingDirection.Z);
		}
		if (fireRateCD <= 0) { Fire(firingDirection); fireRateCD = fireRate; }
	}
	else
	{
		firingDirection = FVector(0.0f, firingDirection.Y, firingDirection.Z);
	}

}

void ATopDownCharacter::upgradeSpeed()
{
	projectileSpeed = projectileSpeed + 100.0f;
}

void ATopDownCharacter::upgradeSize()
{
	projectileScale = projectileScale + 1.0f;
}

void ATopDownCharacter::upgradeFireRate()
{
	if (fireRate > 0.0f) fireRate = fireRate - 5.0f;
}

void ATopDownCharacter::upgradeLifeSpan()
{
	projectileLifeSpan = projectileLifeSpan + 1.0f;
}



