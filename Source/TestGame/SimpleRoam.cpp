// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRoam.h"

EBTNodeResult::Type USimpleRoam::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AEnemy1_AI_Controller* AICon = Cast<AEnemy1_AI_Controller>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		//AICon->AIEnemy->MoveForward(100.0f);
		AICon->AIEnemy->ToggleForwardMovement();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	//return EBTNodeResult::Type();
}

