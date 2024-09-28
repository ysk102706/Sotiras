// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h" 
#include "Skill/PlayerSkillComponent.h"

AMain_Player::AMain_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.f;
	SpringArm->bUsePawnControlRotation = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	SetCurMaxHP(DefaultMaxHP);
	
	Init(); 
}

void AMain_Player::BeginPlay()
{
	Super::BeginPlay(); 

	AttackCollider = FindComponentByClass<UBoxComponent>();
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AMain_Player::OnAttackOverlapBegin);
	AttackCollider->OnComponentEndOverlap.AddDynamic(this, &AMain_Player::OnAttackOverlapEnd);
	
	if (auto _PlayerController = Cast<APlayerController>(GetController())) {
		if (auto _Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_PlayerController->GetLocalPlayer())) {
			_Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

void AMain_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	if (IsAttackCoolTime) {
		AttackCoolTimeTimer += DeltaTime;
		if (AttackCoolTimeTimer >= 1) IsAttackCoolTime = false;
	}
}

void AMain_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMain_Player::InputMove);
		EIC->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AMain_Player::InputCamera);
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMain_Player::InputJump);
		EIC->BindAction(IA_Attack, ETriggerEvent::Started, this, &AMain_Player::InputAttack);
		EIC->BindAction(IA_Dash, ETriggerEvent::Started, this, &AMain_Player::InputCommonSkill);
		EIC->BindAction(IA_Parrying, ETriggerEvent::Started, this, &AMain_Player::InputCommonSkill);
		EIC->BindAction(IA_SelectAttribute, ETriggerEvent::Started, this, &AMain_Player::InputCommonSkill);
	}
}

bool AMain_Player::Hit(float Damage)
{
	return false;
}

void AMain_Player::HitEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Player Hit"));
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

void AMain_Player::InputAttack(const FInputActionValue& Value)
{
	if (!IsAttackCoolTime) {
		IsAttackCoolTime = true;
		AttackCoolTimeTimer = 0.0f;

		AttackHitCheck();
	}
}

void AMain_Player::InputCommonSkill(const FInputActionValue& Value)
{
	PlayerSkillComponent->UseSkill(ESkillType::CommonSkill, Value.Get<float>()); 
}

void AMain_Player::OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Hitable = Cast<IHitable>(OtherActor)) {
		AttackOverlapedObjects.Add(OtherActor);
	}
}

void AMain_Player::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Hitable = Cast<IHitable>(OtherActor)) {
		AttackOverlapedObjects.Remove(OtherActor);
	}
}

void AMain_Player::Init()
{ 
	InitComponents();
} 

void AMain_Player::InitComponents()
{ 
	PlayerSkillComponent = CreateDefaultSubobject<UPlayerSkillComponent>(TEXT("PlayerSkillComponent")); 
	PlayerSkillComponent->Init(this);
}

FVector AMain_Player::GetForwardVector()
{
	return MainCamera->GetForwardVector();
}

void AMain_Player::AttackHitCheck()
{
	if (IsAttackCoolTime && AttackOverlapedObjects.Num()) {
		for (int i = 0; i < AttackOverlapedObjects.Num(); i++) {
			if (Cast<IHitable>(AttackOverlapedObjects[i])->Hit(2)) i--;
		}
	}
}
