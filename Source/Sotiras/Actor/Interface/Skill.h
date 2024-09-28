// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Skill.generated.h"

UINTERFACE(MinimalAPI)
class USkill : public UInterface
{
	GENERATED_BODY()
};

class SOTIRAS_API ISkill
{
	GENERATED_BODY()

public:
	virtual void SkillEffect() = 0; 

	virtual void StartCoolTime() = 0;
	bool IsCoolTime;

};
