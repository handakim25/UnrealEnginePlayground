// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TObjectPtrTest.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class PLAYGROUND_API ATObjectPtrTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATObjectPtrTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RawPointer;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ObjectPtr;

	UFUNCTION(CallInEditor)
	void AccessRawPointer();

	UFUNCTION(CallInEditor)
	void AccessTObjectPtr();

	UFUNCTION(CallInEditor)
	void DeleteRawPointer();

	UFUNCTION(CallInEditor)
	void DeleteTObjectPtr();

	UFUNCTION(CallInEditor)
	void LogRawPointer();

	UFUNCTION(CallInEditor)
	void LogTObjectPointer();

	void SpawnLoadedActors(TObjectPtr<UStaticMeshComponent> Mesh);

};
