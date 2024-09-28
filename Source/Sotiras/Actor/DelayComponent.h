// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DelayComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDelayAction);

UENUM(BlueprintType) 
enum EDelayOwnerType {
	Player	UMETA(DisplayName = "Player"),
	Boss	UMETA(DisplayName = "Boss")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOTIRAS_API UDelayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDelayComponent(); 
	virtual void BeginPlay() override; 
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartDelay(float _DelayTime, EDelayOwnerType _DelayOwnerType, UObject* _CalledClass);
	void EndDelay();

	UPROPERTY()
	FEndDelayAction EndDelayActionDelegate; 

private: 
	bool IsDelay; 
	float Timer; 
	float DelayTime; 

	EDelayOwnerType DelayOwnerType; 

	UPROPERTY() 
	TObjectPtr<UObject> CalledClass;

};
