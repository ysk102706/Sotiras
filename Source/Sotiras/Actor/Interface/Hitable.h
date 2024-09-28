// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hitable.generated.h"

UENUM(BlueprintType) 
enum EDamageType { 
	PhysicalDamage UMETA(DisplayName = "PhysicalDamage"), 
	SpecialPhysicalDamage UMETA(DisplayName = "SpecialPhysicalDamage"),
	AttributeDamage UMETA(DisplayName = "AttributeDamage"), 
	SpecialAttributeDamage UMETA(DisplayName = "SpecialAttributeDamage"), 
	MagicDamage UMETA(DisplayName = "MagicDamage"),
	SpecialMagicDamage UMETA(DisplayName = "SpecialMagicDamage") 
};

UINTERFACE(MinimalAPI)
class UHitable : public UInterface
{
	GENERATED_BODY()
};

class SOTIRAS_API IHitable
{
	GENERATED_BODY() 

public:
	virtual bool Hit(float Damage) = 0; 
	virtual void HitEffect() = 0;
	
protected: 
	void SetCurMaxHP(float MaxHP) {
		CurHP = CurMaxHP = MaxHP; 
	};

	float CurMaxHP; 
	float CurHP; 
};
