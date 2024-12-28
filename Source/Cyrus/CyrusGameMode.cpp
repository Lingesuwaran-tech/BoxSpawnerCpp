// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyrusGameMode.h"
#include "CyrusCharacter.h"
#include "Json.h"
#include "JsonObjectConverter.h"

#include "JsonBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ACyrusGameMode::ACyrusGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


}

void ACyrusGameMode::StartPlay()
{
	Super::StartPlay();

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &ACyrusGameMode::OnResponseReceived);
	Request->ProcessRequest();

	HudWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HudWidget);
	HudWidgetInstance->AddToViewport();
}

//Fuction that gets Json file
void ACyrusGameMode::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectionSuccess)
{
	TSharedPtr <FJsonObject> ResponseObj;
	TSharedRef <TJsonReader<>>Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(Reader, ResponseObj) && ResponseObj.IsValid())
	{
		UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
	}
	FJsonStruct Val;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FJsonStruct>(ResponseObj.ToSharedRef(), &Val))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("Name: %s"), *Val.types[1].name);
	UE_LOG(LogTemp, Display, TEXT("Name: %f"), Val.objects[1].transform.location[0]);

	TArray <FJsonObjects> BoxVals = Val.objects;

	for (FJsonObjects i : BoxVals) {
		FVector location = FVector(float(i.transform.location[0]), float(i.transform.location[1]), float(i.transform.location[2]));
		FRotator rotation = FRotator(float(i.transform.rotation[0]), float(i.transform.rotation[1]), float(i.transform.rotation[2]));
		FVector scale = FVector(float(i.transform.scale[0]), float(i.transform.scale[1]), float(i.transform.scale[2]));
		for (FJsonTypes j : Val.types) 
		{
			if (j.name == i.type)
			{
				//Calling Spawn function
				BoxSpawner(location, rotation, scale, j);
			}
		}
	}
	

}

//Fuction to Spawn Box
void ACyrusGameMode::BoxSpawner(FVector location, FRotator rotation,FVector scale, FJsonTypes type)
{
	FTransform Trans(rotation,location,scale);
	
	AJsonBox* Box = GetWorld()->SpawnActorDeferred<AJsonBox>(BoxActor, Trans);
	Box->setValues(type.name,type.color,type.health,type.score);
}

void ACyrusGameMode::AddScore(int s)
{
	ScoreBoard = ScoreBoard + s;
}

int ACyrusGameMode::GetScore() 
{
	return ScoreBoard;
}