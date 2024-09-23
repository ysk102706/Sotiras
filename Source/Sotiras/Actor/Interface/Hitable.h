// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hitable.generated.h"

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
	
protected: 
	void SetCurMaxHP(float MaxHP) {
		CurHP = CurMaxHP = MaxHP; 
	};

	float CurMaxHP; 
	float CurHP; 
};
