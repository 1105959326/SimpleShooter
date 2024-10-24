// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGunActor;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Bind player action to different keys
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	//override damage function from ACharacter
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const;

	UPROPERTY(EditAnywhere)
		FVector PatrolLocation;

private:
	void MoveForward(float Value);
	void MoveLeftAndRight(float Value);
	void LookUpRight(float Value);
	void TurnRight(float Value);
	
	UPROPERTY(EditAnywhere)
		float RotateRate = 100.f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGunActor> GunClass;

	UPROPERTY()
		AGunActor* Gun;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 200.f;

	UPROPERTY(VisibleDefaultsOnly)
		float Health;
	
	
	
};
