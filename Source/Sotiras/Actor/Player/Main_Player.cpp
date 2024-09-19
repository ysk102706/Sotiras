// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AMain_Player::AMain_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;
}

void AMain_Player::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto _PlayerController = Cast<APlayerController>(GetController())) {
		if (auto _Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_PlayerController->GetLocalPlayer())) {
			_Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

void AMain_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMain_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMain_Player::InputMove);
		EIC->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AMain_Player::InputCamera);
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMain_Player::InputJump);
	}

}

void AMain_Player::InputMove(const FInputActionValue& Value)
{
	FVector f = GetActorForwardVector();
	FVector r = FVector(0, 0, 1).Cross(f);
	AddMovementInput(f, Value.Get<FVector2D>().X);
	AddMovementInput(r, Value.Get<FVector2D>().Y);
}

void AMain_Player::InputCamera(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<FVector2D>().X);
	AddControllerPitchInput(-Value.Get<FVector2D>().Y);
}

void AMain_Player::InputJump(const FInputActionValue& Value)
{
	Jump();
}

