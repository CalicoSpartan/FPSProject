// Fill out your copyright notice in the Description page of Project Settings.

#include "AssaultRifle.h"
#include "FPSCharacter.h"
#include "Net/UnrealNetwork.h"


AAssaultRifle::AAssaultRifle()
{
	//keep movement synced from server to clients
	bReplicateMovement = true;
	//this pickup is physics enabled and should move
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetEnableGravity(true);
}

void AAssaultRifle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void AAssaultRifle::OnShoot()
{
	Super::OnShoot();

	ServerOnShoot();
}
void AAssaultRifle::PickedUpBy(APawn * Pawn)
{
	Super::PickedUpBy(Pawn);

	if (Role == ROLE_Authority)
	{
		if (AFPSCharacter* const AttachedPlayer = Cast<AFPSCharacter>(Pawn)) {
			UE_LOG(LogClass, Log, TEXT("%s was picked up by %s"),*GetName(), *Pawn->GetName());
		}
		// give clients time to play vfx, etc... before destroying the battery
		//SetLifeSpan(2.0f);
	}
}

bool AAssaultRifle::ServerOnShoot_Validate()
{
	Super::ServerOnShoot_Validate();
	return true;
}
void AAssaultRifle::ServerOnShoot_Implementation()
{
	Super::ServerOnShoot_Implementation();
	//do something
}