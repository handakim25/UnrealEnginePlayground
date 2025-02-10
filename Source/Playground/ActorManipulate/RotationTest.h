// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationTest.generated.h"

UENUM()
enum class ERotateType
{
	RotateType_None,
	RotateType_Const,
	RotateType_RLerp,
	RotateType_Slerp,
};

UCLASS()
class PLAYGROUND_API ARotationTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotationTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
	void ResetRotation();

	bool IsRotateFinished() const;
	
private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* HeadMesh;

	UPROPERTY(EditAnywhere)
	float RotateDuration;

	UPROPERTY(EditAnywhere)
	FRotator TargetRotator;

	UPROPERTY(EditAnywhere)
	float LerpSpeed;
	
	float CurrentTime;
	FRotator StartRotator;

	UPROPERTY(EditAnywhere)
	ERotateType RotateType;

	bool bIsRotating;
};
