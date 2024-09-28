// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Hitable.h" 
#include "Boss.generated.h"

UCLASS()
class SOTIRAS_API ABoss : public AActor, public IHitable
{
	GENERATED_BODY()
	
public:	
	ABoss();
	virtual void BeginPlay() override; 
	virtual void Tick(float DeltaTime) override;

	virtual bool Hit(float Damage) override;
	virtual void HitEffect() override;

	UPROPERTY(EditAnywhere, Category = Stat)
	float DefaultMaxHP;
};
