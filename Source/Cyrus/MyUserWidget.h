// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CYRUS_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	int Score;

protected:

	UPROPERTY(EditAnywhere,meta =(BindWidget))
	class UTextBlock* ScoreBoard;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	void NativeTick(const FGeometry& MyGeomentry, float InDeltaTime) override;
	void NativePreConstruct() override;

	
};
