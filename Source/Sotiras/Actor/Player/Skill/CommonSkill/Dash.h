// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../Interface/Skill.h"
#include "../../PlayerActorComponent.h"
#include "Dash.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOTIRAS_API UDash : public UPlayerActorComponent, public ISkill
{
	GENERATED_BODY()

public:	
	UDash(); 
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SkillEffect() override; 
	UFUNCTION()
	virtual void StartCoolTime() override;

	virtual void Init(AMain_Player* _Player) override;

	UFUNCTION() 
	void DashControl();

private:
	float DashForce;

	FCollisionQueryParams CQP;
};
