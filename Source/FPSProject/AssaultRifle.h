// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "AssaultRifle.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AAssaultRifle : public AGun
{
	GENERATED_BODY()
	
public:
	AAssaultRifle();

	//required network scaffolding
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void OnShoot();


	//server side handling of being picked up
	UFUNCTION(BlueprintAuthorityOnly, Category = "Weapon")
		virtual void PickedUpBy(APawn* Pawn) override;
	
protected:
	UFUNCTION(Reliable, Server, WithValidation)
		virtual void ServerOnShoot() override;
};
