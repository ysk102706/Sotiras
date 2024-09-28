// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
	SetCurMaxHP(DefaultMaxHP);
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABoss::Hit(float Damage)
{
	CurHP -= Damage;
	if (CurHP <= 0) {
		Destroy();
		return true;
	}
	return false;
}

void ABoss::HitEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Monster Hit"));
}
