// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NukeRPGCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
USTRUCT(BlueprintType)
struct FAmmoTypes
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int RifleAmmo = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int ShotgunAmmo = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int HandgunAmmo = 0;//Pistols/SMG
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int HeavyAmmo = 0; //Sniper/Machine Gun
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int RocketAmmo = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int FragGrenades = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo Types")
	int FlashGrenades = 0;
};
USTRUCT(BlueprintType)
struct FVitals
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Vitals")
	float Health;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Vitals")
	float Stamina;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Vitals")
	float Rads;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Modifier")
	float DmgResist;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Modifier")
	float RadResist;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Vitals")
	float BaseWalkSpeed = 500.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Vitals")
	float BaseSprintSpeed = 750.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Modifier")
	float WalkSpeedMod = 1.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Modifier")
	float SprintSpeedMod = 1.f;
	
};
UCLASS(config=Game)
class ANukeRPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	/**Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	
public:
	ANukeRPGCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FAmmoTypes AmmoInv;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVitals PlayerVitals;
protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	/**Toggle Crouch**/
	void CrouchToggle(const FInputActionValue& Value);

	/**Sprinting**/
	void OnStartSprint();
	void OnStopSprint();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

