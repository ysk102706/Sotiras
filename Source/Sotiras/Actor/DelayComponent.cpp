// Fill out your copyright notice in the Description page of Project Settings.


#include "DelayComponent.h"
#include "Player/PlayerActorComponent.h"

UDelayComponent::UDelayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDelayComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(true);
} 

void UDelayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsDelay) {
		Timer += DeltaTime; 
		if (Timer >= DelayTime) {
			IsDelay = false;

			EndDelay();
		}
	}
}

void UDelayComponent::StartDelay(float _DelayTime, EDelayOwnerType _DelayOwnerType, UObject* _CalledClass)
{
	IsDelay = true; 
	Timer = 0.0f; 
	DelayTime = _DelayTime; 
	DelayOwnerType = _DelayOwnerType;
	CalledClass = _CalledClass;
}

void UDelayComponent::EndDelay()
{
	EndDelayActionDelegate.Broadcast();
	
	switch (DelayOwnerType) {
	case EDelayOwnerType::Player:
		Cast<UPlayerActorComponent>(CalledClass)->RemoveDelay(this);
		break;
	case EDelayOwnerType::Boss: 
		// TODO: 보스가 호출한 딜레이 제거
		break; 
	}
}
