// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy1_AI_Controller.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy1.h"

AEnemy1_AI_Controller::AEnemy1_AI_Controller()
{
	behavior_tree_component = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	TargetPlayer = "Target";
	TargetLocation = FVector(0.0f, 0.0f, 0.0f);
}

void AEnemy1_AI_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);

	AIEnemy = Cast<AEnemy1>(pawn);

	if (AIEnemy)
	{

		if (AIEnemy->behavior_tree->BlackboardAsset)
		{

			BlackboardComp->InitializeBlackboard(*(AIEnemy->behavior_tree->BlackboardAsset));
		}

		behavior_tree_component->StartTree(*AIEnemy->behavior_tree);
	}
}