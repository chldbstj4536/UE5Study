// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UE5StudyPrecompiled.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5STUDY_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void AddScore(int32 EarnScore);

	UFUNCTION()
	void GameOver();

private:
	void PrintScore();
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> GameOverWidgetClass;

private:
	UPROPERTY(VisibleAnywhere)
	int32 CurrentScore;
	UPROPERTY(VisibleAnywhere)
	int32 MaxScore;

	class UMainWidget* MainWidget;
	class UGameOverWidget* GameOverWidget;
};
