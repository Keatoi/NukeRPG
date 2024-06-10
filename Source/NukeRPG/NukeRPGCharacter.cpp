// Copyright Epic Games, Inc. All Rights Reserved.

#include "NukeRPGCharacter.h"
#include "NukeRPGProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ANukeRPGCharacter

ANukeRPGCharacter::ANukeRPGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ANukeRPGCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// enable crouching
	if (GetMovementComponent())
	{
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
		GetCharacterMovement()->MaxWalkSpeed = (PlayerVitals.BaseWalkSpeed * PlayerVitals.WalkSpeedMod);
		GetCharacterMovement()->MaxWalkSpeedCrouched = (PlayerVitals.BaseWalkSpeed * PlayerVitals.WalkSpeedMod) / 2.f;
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ANukeRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANukeRPGCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANukeRPGCharacter::Look);

		//Crouch Toggle
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ANukeRPGCharacter::CrouchToggle);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Started,this,&ANukeRPGCharacter::OnStartSprint);
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Completed,this,&ANukeRPGCharacter::OnStopSprint);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ANukeRPGCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ANukeRPGCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

auto ANukeRPGCharacter::CrouchToggle(const FInputActionValue& Value) -> void
{
	UE_LOG(LogTemp,Warning,TEXT("Crouching called"));
	if(!GetMovementComponent()->IsCrouching())
	{
		
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ANukeRPGCharacter::OnStartSprint()
{
	if(GetMovementComponent()->IsCrouching()) UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = (PlayerVitals.BaseSprintSpeed * PlayerVitals.SprintSpeedMod);
}

void ANukeRPGCharacter::OnStopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = (PlayerVitals.BaseWalkSpeed * PlayerVitals.WalkSpeedMod);
}

void ANukeRPGCharacter::DecrementStamina()
{
	PlayerVitals.Stamina--;
}

void ANukeRPGCharacter::IncrementStamina()
{
	PlayerVitals.Stamina++;
}

void ANukeRPGCharacter::IncreaseStamina(float IncreasePercent)
{
	//BP Helper Function, assumes that percentage is inputted as a whole number so 50% would be 50.f not 0.5
	float Percent = IncreasePercent / 100.f;
	float StamIncrease = Percent * PlayerVitals.Stamina;
	float NewStam = PlayerVitals.Stamina + StamIncrease;
	
	PlayerVitals.Stamina = FMath::Clamp(NewStam,0.f,100.f);
}

void ANukeRPGCharacter::DecreaseStamina(float DecreasePercent)
{
	//BP Helper Function, assumes that percentage is inputted as a whole number so 50% would be 50.f not 0.5
	float Percent = DecreasePercent / 100.f;
	float StamDecrease = Percent * PlayerVitals.Stamina;
	float NewStam = PlayerVitals.Stamina - StamDecrease;
	PlayerVitals.Stamina = FMath::Clamp(NewStam,0.f,100.f);
}

void ANukeRPGCharacter::DecrementHP()
{
	PlayerVitals.Health--;
}

void ANukeRPGCharacter::IncrementHP()
{
	PlayerVitals.Health++;
}

void ANukeRPGCharacter::IncreaseHP(float IncreasePercent)
{
	float Percent = IncreasePercent / 100.f;
	float HPIncrease = Percent * PlayerVitals.Health;
	float NewHP = PlayerVitals.Health + HPIncrease;
	
	PlayerVitals.Health = FMath::Clamp(NewHP,0.f,100.f);
}

void ANukeRPGCharacter::DecreaseHP(float DecreasePercent)
{
	float Percent = DecreasePercent / 100.f;
	float HPDecrease = Percent * PlayerVitals.Health;
	float NewHP = PlayerVitals.Health - HPDecrease;
	
	PlayerVitals.Health = FMath::Clamp(NewHP,0.f,100.f);
}

