// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadZone.generated.h"

UCLASS()
class NUKERPG_API ARadZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadZone();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* SourceMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USphereComponent* RadZone;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
