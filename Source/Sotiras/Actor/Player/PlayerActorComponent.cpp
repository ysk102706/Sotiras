// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActorComponent.h"

UPlayerActorComponent::UPlayerActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetComponentTickEnabled(true);
}

void UPlayerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerActorComponent::Init(AMain_Player* _Player)
{
	Player = _Player;
}

void UPlayerActorComponent::RemoveDelay(UDelayComponent* _DelayComponent)
{
	for (auto DelayComponent : DelayComponents) {
		if (DelayComponent == _DelayComponent) {
			DelayComponents.Remove(DelayComponent);
			DelayComponent->DestroyComponent(); 
			return;
		}
	}
}
