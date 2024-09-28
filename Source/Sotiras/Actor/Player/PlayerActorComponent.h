// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Main_Player.h" 
#include "../DelayComponent.h"
#include "PlayerActorComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SOTIRAS_API UPlayerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerActorComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Init(AMain_Player* _Player);

	void RemoveDelay(UDelayComponent* _DelayComponent); 

	UPROPERTY()
	TObjectPtr<AMain_Player> Player;

protected:
	template<typename T>
	TObjectPtr<UDelayComponent> AddDelay(T* Parent, float Time) {
		if (Cast<UPlayerActorComponent>(Parent)) {
			TObjectPtr<UDelayComponent> DelayComponent = NewObject<UDelayComponent>(Parent);
			DelayComponent->RegisterComponent(); 
			DelayComponents.Add(DelayComponent);
			DelayComponent->StartDelay(Time, EDelayOwnerType::Player, Parent);
			return DelayComponent;
		}
		return nullptr;
	};
	
	UPROPERTY()
	TArray<TObjectPtr<UDelayComponent>> DelayComponents; 

}; 
