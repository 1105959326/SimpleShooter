// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacter.h"
#include "ShooterAIController.h"

//Use BT task to let AI shoot
UBTTask_Shoot::UBTTask_Shoot()
{
	//Name the node
	NodeName = TEXT("Shoot");
}

//Shoot function
EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AShooterCharacter* AICharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	AICharacter->Shoot();

	return EBTNodeResult::Succeeded;
}
