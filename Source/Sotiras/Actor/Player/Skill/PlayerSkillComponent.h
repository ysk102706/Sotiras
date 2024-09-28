// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "../PlayerActorComponent.h"
#include "CommonSkill/CommonSkillComponent.h"
#include "PlayerSkillComponent.generated.h" 

UENUM(BlueprintType) 
enum ESkillType {
	CommonSkill	UMETA(DisplayName = "CommonSkill"),
	SwordSkill	UMETA(DisplayName = "SwordSkill"),
	MutuSkill	UMETA(DisplayName = "MutuSkill"),
	BowSkill	UMETA(DisplayName = "BowSkill"), 
	MagicSkill	UMETA(DisplayName = "MagicSkill") 
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SOTIRAS_API UPlayerSkillComponent : public UPlayerActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerSkillComponent(); 
	virtual void BeginPlay() override; 
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Init(AMain_Player* _Player) override; 

	void UseSkill(ESkillType Type, int DetailType);

private:
	UPROPERTY()
	TObjectPtr<UCommonSkillComponent> CommonSkillComponent; 

};
