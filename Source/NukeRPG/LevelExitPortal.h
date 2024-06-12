// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelExitPortal.generated.h"

UCLASS()
class NUKERPG_API ALevelExitPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelExitPortal();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* PortalMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBoxComponent* PortalBox;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bPlayerClose;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bDoorOpen;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class ANukeRPGCharacter* OverlappedPlayer;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class ANukeRPGCharacter* PlayerRef;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName LevelDisplayName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UUserWidget* InteractUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> InteractUIClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnInteract(ACharacter* PlayerActor);

};
