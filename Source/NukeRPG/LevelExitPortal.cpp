// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelExitPortal.h"

#include "NukeRPGCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelExitPortal::ALevelExitPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	check(PortalMesh != nullptr);
	RootComponent = PortalMesh;
	PortalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalBox"));
	PortalBox->SetupAttachment(PortalMesh);
	PortalBox->OnComponentBeginOverlap.AddDynamic(this,&ALevelExitPortal::OnBoxBeginOverlap);
	PortalBox->OnComponentEndOverlap.AddDynamic(this,&ALevelExitPortal::OnBoxEndOverlap);
}

// Called when the game starts or when spawned
void ALevelExitPortal::BeginPlay()
{
	Super::BeginPlay();
	if(InteractUIClass)
	{
		UE_LOG(LogTemp,Warning,TEXT("Interact UI class loaded"));
		InteractUI = CreateWidget(GetWorld(),InteractUIClass);
	}
}

// Called every frame
void ALevelExitPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelExitPortal::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("Actor Entered"));
	if(OtherActor->IsA(ANukeRPGCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Player Entered"));
		bPlayerClose = true;
		OverlappedPlayer = Cast<ANukeRPGCharacter>(OtherActor);
		if(InteractUI) InteractUI->AddToViewport();
	}
}

void ALevelExitPortal::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("Actor left"));
	
	if(OtherActor->IsA(ANukeRPGCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Player left"));
		bPlayerClose = false;
		OverlappedPlayer = nullptr;
		if(OverlappedPlayer == nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("Player null"));
			if(InteractUI) InteractUI->RemoveFromParent();
			
			
		}
	}
}

void ALevelExitPortal::OnInteract(ACharacter* PlayerActor)
{
	if(OverlappedPlayer != nullptr && bDoorOpen)
	{
		InteractUI->RemoveFromParent();
		UGameplayStatics::OpenLevel(this,LevelName);
	}
}

