// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSkillComponent.h"

UCommonSkillComponent::UCommonSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	DashComponent = CreateDefaultSubobject<UDash>(TEXT("DashComponent"));

}

void UCommonSkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCommonSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UCommonSkillComponent::Init(AMain_Player* _Player)
{
	Super::Init(_Player);

	DashComponent->Init(_Player);
} 

void UCommonSkillComponent::UseCommonSkill(ECommonSkillType CommonSkillType)
{ 
	switch (CommonSkillType) {
	case ECommonSkillType::Dash:
		Dash();
		break;
	case ECommonSkillType::Parrying:
		Parrying();
		break;
	case ECommonSkillType::SelectAttribute:
		SelectAttribute();
		break;
	}
}

void UCommonSkillComponent::Dash()
{
	DashComponent->SkillEffect(); 
}

void UCommonSkillComponent::Parrying()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Parrying"));
}

void UCommonSkillComponent::SelectAttribute()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("SelectAttribute"));
}

