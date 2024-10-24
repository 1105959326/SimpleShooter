// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimpleShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
		float DelayTime = 5.f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CursorClass;

	UPROPERTY()
		UUserWidget* HUD;
};
