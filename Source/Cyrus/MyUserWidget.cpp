// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "CyrusGameMode.h"
#include <Components/TextBlock.h>


void UMyUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ScoreText->SetText(FText::FromString("Score"));

}

void UMyUserWidget::NativeTick(const FGeometry& MyGeomentry, float InDeltaTime)
{
	Super::NativeTick(MyGeomentry, InDeltaTime);

	ACyrusGameMode* const GM = GetWorld()->GetAuthGameMode<ACyrusGameMode>();

	ScoreBoard->SetText(FText::AsNumber(GM->GetScore()));
}


