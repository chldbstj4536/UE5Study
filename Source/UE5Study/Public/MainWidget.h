// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UE5StudyPrecompiled.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5STUDY_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreData;
};
