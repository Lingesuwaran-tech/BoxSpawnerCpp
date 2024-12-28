// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "CyrusGameMode.generated.h"


//Box Types Struct
USTRUCT()
struct FJsonTypes
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString name;
	UPROPERTY()
	TArray <int> color;
	UPROPERTY()
	int health;
	UPROPERTY()
	int score;
};

//Box Transforms Struct
USTRUCT()
struct FJsonTransforms
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray <float> location;
	UPROPERTY()
	TArray <float> rotation;
	UPROPERTY()
	TArray <float> scale;
};

//Box Objects Struct
USTRUCT()
struct FJsonObjects
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString type;
	UPROPERTY()
	FJsonTransforms transform;
};

//Box Values Struct
USTRUCT()
struct FJsonStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray <FJsonTypes> types;
	UPROPERTY()
	TArray <FJsonObjects> objects;

};

UCLASS(minimalapi)
class ACyrusGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACyrusGameMode();

	virtual void StartPlay() override;
	void BoxSpawner(FVector location, FRotator rotation, FVector scale, FJsonTypes type);

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	int ScoreBoard;

	void AddScore(int s);
	int GetScore();

	UPROPERTY(EditAnywhere) 
	TSubclassOf<UUserWidget> HudWidget;
	UUserWidget* HudWidgetInstance;
	

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectionSuccess);
	UPROPERTY(EditDefaultsOnly, Category = "Spawner") TSubclassOf<class AJsonBox> BoxActor;
};