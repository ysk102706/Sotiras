// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillComponent.h"
 
UPlayerSkillComponent::UPlayerSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CommonSkillComponent = CreateDefaultSubobject<UCommonSkillComponent>(TEXT("CommonSkillComponent")); 
	
}

void UPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UPlayerSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerSkillComponent::Init(AMain_Player* _Player)
{
	Super::Init(_Player);

	CommonSkillComponent->Init(_Player);
}

void UPlayerSkillComponent::UseSkill(ESkillType Type, int DetailType)
{
	switch (Type) {
	case ESkillType::CommonSkill:
		CommonSkillComponent->UseCommonSkill(ECommonSkillType(DetailType));
		break;
	}
}
