// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"


AGunActor::AGunActor()
{
	// create the gun mesh
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Mesh->SetupAttachment(Root);
}
//shoot bullet and generate effect after pull trigger
void AGunActor::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(Particle, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleSound"));

	FHitResult Hit;
	FVector ShotDirection;
	AController* OwnerController;
	//if the location of bullet located hit something, then generate effects
	bool bSuccess = GunTrace(Hit, ShotDirection, OwnerController);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

//Trace bullet from the character eye level to the generate the hit location to check is the bullet hit or not
bool AGunActor::GunTrace(FHitResult& Hit, FVector& ShotDirection, AController*& OwnerController)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return false;
	OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return false;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

