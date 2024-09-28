// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

UDash::UDash()
{
	PrimaryComponentTick.bCanEverTick = true;

	DashForce = 10000.0f;
	IsCoolTime = false;
}


void UDash::BeginPlay()
{
	Super::BeginPlay();

	CQP.AddIgnoredActor(Player);
	
}

void UDash::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDash::SkillEffect()
{
	if (!IsCoolTime) {
		FVector Forward = Player->GetForwardVector();
		if (Forward.Z <= 0.0f && Forward.Z >= -0.35f) Forward.Z = 0.02f; 
		Player->LaunchCharacter(Forward * DashForce, true, true);
		if (auto Delay = AddDelay<UDash>(this, 0.35f)) {
			Delay->EndDelayActionDelegate.AddDynamic(this, &UDash::DashControl);
		}

		IsCoolTime = true; 
		if (auto Delay = AddDelay<UDash>(this, 3.0f)) {
			Delay->EndDelayActionDelegate.AddDynamic(this, &UDash::StartCoolTime);
		}
	}
}

void UDash::StartCoolTime()
{
	IsCoolTime = false;
}

void UDash::Init(AMain_Player* _Player)
{
	Super::Init(_Player);
}

void UDash::DashControl()
{
	Player->GetCharacterMovement()->Velocity /= 10.0f;
}

