// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Enemy1.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	scale = 5.0f;
	speed = 5000.0f;
	team = 0;
	bDoesPierce = false;
	numberOfPierces = 0;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		//CollisionComponent->BodyInstance.UpdateBodyScale(FVector(scale, scale, scale),true); //InitSphereRadius(scale);
		//CollisionComponent->RecreatePhysicsState();	
		CollisionComponent->SetWorldScale3D(FVector(scale, scale, scale));

		RootComponent = CollisionComponent;
	}
	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = speed;
		ProjectileMovementComponent->MaxSpeed = speed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
			ProjectileMeshComponent->SetCollisionProfileName(TEXT("Projectile"));
		}
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Game/projectileBase.projectileBase"));
		if (Material.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
	/**if (!explosion)
	{
		explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
		UParticleSystem* particleSystem;
		static ConstructorHelpers::FObjectFinder<UParticleSystem>importedParticle(TEXT("/Game/Particles/ProjectileDeath.ProjectileDeath"));
		if (importedParticle.Succeeded())
		{
			particleSystem = importedParticle.Object;
			explosion->SetTemplate(particleSystem);
			explosion->SetupAttachment(RootComponent);
			explosion->
		}
	}*/
	static ConstructorHelpers::FObjectFinder<UParticleSystem>importedParticle(TEXT("/Game/Particles/ProjectileDeath.ProjectileDeath"));
	if (importedParticle.Succeeded())
	{
		explosion = importedParticle.Object;
	}

	InitialLifeSpan = 1.0f;

}


void ABaseProjectile::Initialize(float scale1, float speed1, float life1, uint8 team1, bool bPiercing1, uint8 pierces)
{
	//ProjectileMeshComponent->SetRelativeScale3D(FVector(scale1, scale1, scale1));
	ProjectileMovementComponent->InitialSpeed = speed1;
	ProjectileMovementComponent->MaxSpeed = speed1;
	CollisionComponent->SetWorldScale3D(FVector(scale1, scale1, scale1));
	//CollisionComponent->BodyInstance.UpdateBodyScale(FVector(scale1, scale1, scale1), true); //InitSphereRadius(scale);
	team = team1;
	SetLifeSpan(life1);
	bDoesPierce = bPiercing1;
	numberOfPierces = pierces;
	//CollisionComponent->RecreatePhysicsState();



}
// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABaseProjectile::OnOverlapBeginEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	AEnemy1* theActor = Cast<AEnemy1>(OtherActor);
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Test"));

	if (theActor && theActor->team != team)
	{
		theActor->TakeSomeDamage(1.0f);
		if (bDoesPierce)
		{
			--numberOfPierces;
			if (numberOfPierces <= 0)
			{
				//if (explosion) explosion->BeginPlay();
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, FTransform(FRotator(0.0f, 0.0f, 0.0f), GetActorLocation(), FVector(1.0f, 1.0f, 1.0f)), true);
				Destroy();
			}
		}
		else
		{
			//if (explosion) explosion->BeginPlay();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, FTransform(FRotator(0.0f, 0.0f, 0.0f), GetActorLocation(), FVector(1.0f, 1.0f, 1.0f)), true);
			Destroy();
		}
	}
}

void ABaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapBeginEnemy);
}

void ABaseProjectile::LifeSpanExpired()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, FTransform(FRotator(0.0f, 0.0f, 0.0f), GetActorLocation(), FVector(1.0f, 1.0f, 1.0f)), true);
	Destroy();
}