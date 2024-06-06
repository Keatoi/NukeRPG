// Fill out your copyright notice in the Description page of Project Settings.


#include "RadZone.h"
#include "Components/SphereComponent.h"

// Sets default values
ARadZone::ARadZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Source Mesh"));
	
	RadZone = CreateDefaultSubobject<USphereComponent>(TEXT("Rad Zone"));
	RootComponent  = RadZone;
	SourceMesh->SetupAttachment(RadZone);
}

// Called when the game starts or when spawned
void ARadZone::BeginPlay()
{
	Super::BeginPlay();
	RadZone->OnComponentBeginOverlap.AddDynamic(this,&ARadZone::OnOverlapBegin);
}

// Called every frame
void ARadZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARadZone::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag(FName("Rad")))
	{
		//Do Radiation Damage here
	}
}

