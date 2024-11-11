// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "firstperson415Character.h"
#include "Kismet/GameplayStatics.h"
#include "firstperson415PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create subobjects
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	playerSim = CreateDefaultSubobject<USceneComponent>("Player Sim");
	sceneCapRoot = CreateDefaultSubobject<USceneComponent>("Scene Capture Root");

	//Set scene capture roots height to match players height
	sceneCapRoot->SetRelativeLocation(FVector(0, 0, 58));

	//Set root component
	RootComponent = boxComp;

	//Setup attachments
	mesh->SetupAttachment(boxComp);
	playerSim->SetupAttachment(boxComp);
	sceneCapRoot->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(sceneCapRoot);


	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);

	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals();
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Afirstperson415Character* playerChar = Cast<Afirstperson415Character>(OtherActor);

	//Is actor cast valid
	if (!playerChar) return;

	//Is the other portal set
	if (!OtherPortal) return;

	//If the player is not already teleporting
	if (playerChar->isTeleporting) return;

	//Get player controller
	Afirstperson415PlayerController* controller = Cast<Afirstperson415PlayerController>(playerChar->GetController());

	//If the controller is not found, break
	if (!controller) return;

	//Set that player is teleporting
	playerChar->isTeleporting = true;

	//Get rotation and position of portal
	FVector PortalLoc = GetActorLocation();
	FVector OtherPortalLoc = OtherPortal->GetActorLocation();
	FRotator OtherPortalRot = OtherPortal->GetActorRotation();

	//Get player movement component
	UCharacterMovementComponent* moveComp = playerChar->GetCharacterMovement();

	//Cache player rotation offset based on entry portal
	FRotator playerRotationOffset = playerChar->GetActorRotation() - GetActorRotation();
	
	//Rotate player rotation offset 180 on YAW to face correct direction. Insert correct pitch from players controller
	playerRotationOffset = FRotator(controller->GetControlRotation().Pitch, playerRotationOffset.Yaw + 180, playerRotationOffset.Roll);
	
	//Create new forward vector for player when exiting portal
	FRotator newForwardVector = OtherPortalRot + playerRotationOffset;
	
	//Get location of the player
	FVector playerLoc = playerChar->GetActorLocation();

	//Calculate Z offset of player based on portal location
	float zOffset = playerLoc.Z - PortalLoc.Z;

	//Set player position and rotation
	playerChar->SetActorLocation(OtherPortalLoc + zOffset, false, nullptr, ETeleportType::TeleportPhysics);
	controller->SetControlRotation(newForwardVector);

	//Set new velocity based on portal rotation
	FVector velocityRot = newForwardVector.Vector() * moveComp->Velocity.Size();

	//Translate velocity to new vector
	moveComp->Velocity.Set(velocityRot.X, velocityRot.Y, velocityRot.Z);

	//Create a timer
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, "SetBool", playerChar);

	//Set the timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);
}

void APortal::SetBool(Afirstperson415Character* playerChar)
{
	if (!playerChar) return;

	playerChar->isTeleporting = false;
}

void APortal::UpdatePortals()
{
	//Location of the player camera
	FVector playerCamLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator playerCamRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();

	//Set location for simulated player
	playerSim->SetWorldLocation(playerCamLocation);

	//Cache player sim location
	FVector playerSimLocation = OtherPortal->playerSim->GetRelativeLocation();

	//Set location of scene capture to simulated player on relative axis: 58 is player height
	sceneCapture->SetRelativeLocation(FVector(playerSimLocation.X, playerSimLocation.Y, playerSimLocation.Z - 58));

	//Calculate and set looking direction of scene capture based on position of scene capture to portal center
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(sceneCapture->GetComponentLocation(), sceneCapture->GetAttachParent()->GetComponentLocation());
	sceneCapture->SetWorldRotation(LookRotation);
	
	//Set relative rotation to match the angle the player is actively looking through the portal (keeps view from rotating on a pivot when walking around portal)
	sceneCapture->SetRelativeRotation(FRotator(playerCamRotation.Pitch, playerCamRotation.Yaw - OtherPortal->GetActorRotation().Yaw, playerCamRotation.Roll));
}