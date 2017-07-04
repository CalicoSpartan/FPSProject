// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Net/UnrealNetwork.h"


AGun::AGun()
{
	//tell engine to replicate this actor
	bReplicates = true;
	//gun doesn't need to tick
	PrimaryActorTick.bCanEverTick = false;
	//static mesh actor disables overlap events by default, which we need to re-enable
	GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	if (Role == ROLE_Authority)
	{
		bIsActive = true;
	}
}

void AGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGun, bIsActive);
}

bool AGun::IsActive()
{
	return bIsActive;
}

void AGun::OnShoot()
{
	ServerOnShoot();
}

bool AGun::ServerOnShoot_Validate()
{
	return true;
}
void AGun::ServerOnShoot_Implementation()
{

}

void AGun::SetActive(bool NewWeaponState)
{
	if (Role == ROLE_Authority)
	{
		bIsActive = NewWeaponState;
	}
}

void AGun::WasCollected_Implementation()
{
	// log a debug message
	UE_LOG(LogClass, Log, TEXT("AGun::WasCollected_Implementation %s"), *GetName());
}

void AGun::PickedUpBy(APawn * Pawn)
{
	if (Role == ROLE_Authority)
	{
		//store the pawn who picked up the pickup
		WeaponInstigator = Pawn;
		//Notify clients of the picked up action
		ClientOnPickedUpBy(Pawn);
	}
}

void AGun::OnRep_IsActive()
{

}

void AGun::ClientOnPickedUpBy_Implementation(APawn* Pawn)
{
	//store the pawn who picked up pickup (client
	WeaponInstigator = Pawn;
	//fire the blueprint native event, which itself cannot be replicated
	WasCollected();
}