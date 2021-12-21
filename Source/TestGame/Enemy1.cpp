// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1.h"
#include "Enemy1_AI_Controller.h"


// Sets default values
AEnemy1::AEnemy1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bMoveForward = false;
	bRotateLeft = false;
	bRotateRight = false;
	healthPoints = 5.0f;
	hurtCD = 0.0f;
	team = 2;
	UCharacterMovementComponent* temporary = GetCharacterMovement();
	temporary->MaxWalkSpeed = 300.0f;
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Game/PowerUpRed.PowerUpRed"));
	if (Material.Succeeded())
	{
		//EnemyMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, EnemyMaterialComponent);
	}
	//EnemyMaterialComponent->SetMaterial(0, EnemyMaterialInstance);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshTemp(TEXT("/Engine/EngineMeshes/SkeletalCube.SkeletalCube"));
	if (MeshTemp.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshTemp.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialTemp(TEXT("/Game/Enemy1.Enemy1"));
	if (MaterialTemp.Succeeded())
	{
		EnemyMaterialInstance = UMaterialInstanceDynamic::Create(MaterialTemp.Object, GetMesh());
		GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
		GetMesh()->SetMaterial(0, EnemyMaterialInstance);
		GetMesh()->SetRelativeScale3D(FVector(3.69f, 3.69f, 3.69f));
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
		
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>bttemp(TEXT("/Game/BehavioralTree/Enemy1Behavior.Enemy1Behavior"));
	if (bttemp.Succeeded())
	{
		behavior_tree = bttemp.Object;
	}



}

// Called when the game starts or when spawned
void AEnemy1::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AEnemy1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMoveForward)
	{
		MoveForward(100.0f);
	}
	if (bRotateLeft)
	{
		Controller->SetControlRotation(Controller->GetControlRotation().Add(0.0f, -1.0f, 0.0f));
		SetActorRotation(Controller->GetControlRotation());
	}
	if (bRotateRight)
	{
		Controller->SetControlRotation(Controller->GetControlRotation().Add(0.0f, 1.0f, 0.0f));
		SetActorRotation(Controller->GetControlRotation());
	}
	if (healthPoints <= 0.0f)
	{
		Killed();
	}
	if (hurtCD > 0.0f)
	{
		hurtCD = hurtCD - 0.1f;
	}
	else if (hurtCD > -1.0f)
	{
		EnemyMaterialInstance->SetScalarParameterValue(TEXT("bHurt"), 0.0f);
		hurtCD = -1.0f;
	}


}

// Called to bind functionality to input
void AEnemy1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AEnemy1::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEnemy1::RotateRight);
}

void AEnemy1::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);

}

void AEnemy1::RotateRight(float Value)
{
	FRotator newRotation = Controller->GetControlRotation().Add(0.0f, Value, 0.0f);
	Controller->SetControlRotation(newRotation);

}

void AEnemy1::ToggleForwardMovement()
{
	bMoveForward = !bMoveForward;
}

void AEnemy1::ToggleRotate(bool direction)
{
	if (direction && !(bRotateLeft || bRotateRight))
	{
		//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Yellow, Controller->GetControlRotation().ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Left"));
		bRotateLeft = true;
		bRotateRight = false;
	}
	else if (!(bRotateLeft || bRotateRight))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, Controller->GetControlRotation().ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Right"));
		bRotateLeft = false;
		bRotateRight = true;
	}
	else
	{
		bRotateLeft = false;
		bRotateRight = false;
	}
}


void AEnemy1::OnOverlapBeginProjectile(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	/*ABaseProjectile* theActor = Cast<ABaseProjectile>(OtherActor);
	if (theActor && theActor->team != 2)
	{
		float Gen_Num = FMath::RandRange(0.0f, 1.0f);
		if (Gen_Num < 0.25f)
		{
				SpawnPowerUp();
		}	
		Destroy();
	}*/
}

void AEnemy1::TakeSomeDamage(float damage)
{
	healthPoints -= damage;
	hurtCD = 3.0f;
	EnemyMaterialInstance->SetScalarParameterValue(TEXT("bHurt"), 1.0f);

}

void AEnemy1::Killed()
{
	if (FMath::FRandRange(0.0, 1.0) < 0.25f)
	{
		SpawnPowerUp();
	}
	Destroy();
}

void AEnemy1::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UCapsuleComponent* collision = GetCapsuleComponent();
	collision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy1::OnOverlapBeginProjectile);
}

void AEnemy1::SpawnPowerUp()
{
	float Gen_Num = FMath::FRandRange(0.0f, 1.0f);
	UWorld* World = GetWorld();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	if (Gen_Num < 0.25f)
	{
		ALifeSpanUpgradePickup* Powerup = World->SpawnActor<ALifeSpanUpgradePickup>(GetActorLocation(), GetActorRotation(), SpawnParams);
	}
	else if (Gen_Num < 0.5f)
	{
		AFireRateUpgradePickup* Powerup = World->SpawnActor<AFireRateUpgradePickup>(GetActorLocation(), GetActorRotation(), SpawnParams);
	}
	else if (Gen_Num < 0.75f)
	{
		ASizeUpgradePickup* Powerup = World->SpawnActor<ASizeUpgradePickup>(GetActorLocation(), GetActorRotation(), SpawnParams);
	}
	else
	{
		ASpeedUpgradePickup* Powerup = World->SpawnActor<ASpeedUpgradePickup>(GetActorLocation(), GetActorRotation(), SpawnParams);
	}
}

