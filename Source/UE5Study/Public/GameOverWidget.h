// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UE5StudyPrecompiled.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5STUDY_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Exit();

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, Meta = (BindWidget))
	class UButton* RestartButton;
	UPROPERTY(EditAnywhere, Meta = (BindWidget))
	class UButton* ExitButton;
};
