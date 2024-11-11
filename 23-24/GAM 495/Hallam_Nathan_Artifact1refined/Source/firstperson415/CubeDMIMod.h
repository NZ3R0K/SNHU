// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

class UNiagaraSystem;

UCLASS()
class FIRSTPERSON415_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cubeMesh;

	//Base material used for creating the dynamic material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* baseMat;

	//Dynamically created material
	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	//Particle System
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* colorP;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};