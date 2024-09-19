// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main_Player.generated.h"

UCLASS()
class SOTIRAS_API AMain_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AMain_Player();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void InputMove(const FInputActionValue& Value);
	UFUNCTION()
	void InputCamera(const FInputActionValue& Value);
	UFUNCTION()
	void InputJump(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputMappingContext> IMC;
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> IA_Camera;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> IA_Jump;

private:
	UPROPERTY()
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY()
	TObjectPtr<class UCameraComponent> MainCamera;

};
