// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "../Interface/Hitable.h"
#include "TestMonster.generated.h"

UCLASS()
class SOTIRAS_API ATestMonster : public AActor, public IHitable
{
	GENERATED_BODY()
	
public:	
	ATestMonster();
	virtual void BeginPlay() override; 
	virtual void Tick(float DeltaTime) override;

	virtual bool Hit(float Damage) override; 

	UPROPERTY(EditAnywhere, Category = Stat)
	float DefaultMaxHP; 

};
