// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/Hitable.h"
#include "Main_Player.generated.h"

UCLASS()
class SOTIRAS_API AMain_Player : public ACharacter, public IHitable
{
	GENERATED_BODY()

public:
	AMain_Player();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool Hit(float Damage) override;

	UFUNCTION()
	void InputMove(const FInputActionValue& Value);
	UFUNCTION()
	void InputCamera(const FInputActionValue& Value);
	UFUNCTION()
	void InputJump(const FInputActionValue& Value);
	UFUNCTION()
	void InputAttack(const FInputActionValue& Value);

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AttackHitCheck();

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputMappingContext> IMC;
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> IA_Camera;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> IA_Jump;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, Category = Stat)
	float DefaultMaxHP;

private:
	UPROPERTY()
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY()
	TObjectPtr<class UCameraComponent> MainCamera;

	UPROPERTY()
	TObjectPtr<class UBoxComponent> AttackCollider;

	bool IsAttackCoolTime;
	float AttackCoolTimeTimer;
	TArray<TObjectPtr<AActor>> AttackOverlapedObjects;

};
