// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy1.h"
#include "GameFramework/Character.h"
#include "Enemy1_AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class TESTGAME_API AEnemy1_AI_Controller : public AAIController
{
	GENERATED_BODY()
		
		class UBehaviorTreeComponent* behavior_tree_component;

		class UBlackboardComponent* BlackboardComp;

		UPROPERTY(EditDefaultsOnly, Category = AI)
		FName TargetPlayer;
		UPROPERTY(EditDefaultsOnly, Category = AI)
		FVector TargetLocation;
		virtual void OnPossess(APawn* const pawn) override;

public:
	AEnemy1* AIEnemy;

	AEnemy1_AI_Controller();
	//void BeginPlay() override;
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	
};
