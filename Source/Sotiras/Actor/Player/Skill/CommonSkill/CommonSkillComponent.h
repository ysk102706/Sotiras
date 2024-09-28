// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Dash.h"
#include "../../PlayerActorComponent.h"
#include "CommonSkillComponent.generated.h"

UENUM(BlueprintType)
enum ECommonSkillType {
	Dash			UMETA(DisplayName = "Dash"),
	Parrying		UMETA(DisplayName = "Parrying"),
	SelectAttribute	UMETA(DisplayName = "SelectAttribute")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOTIRAS_API UCommonSkillComponent : public UPlayerActorComponent
{
	GENERATED_BODY()

public:	
	UCommonSkillComponent(); 
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Init(AMain_Player* _Player) override; 

	void UseCommonSkill(ECommonSkillType CommonSkillType); 
	
	void Dash();
	void Parrying();
	void SelectAttribute();

private:
	UPROPERTY()
	TObjectPtr<UDash> DashComponent; 

};
