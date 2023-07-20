// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingGameModeBase.h"
#include <Components/TextBlock.h>
#include <Blueprint/UserWidget.h>
#include "MainWidget.h"
#include "GameOverWidget.h"

void AShootingGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (MainWidgetClass != nullptr)
    {
        MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass, TEXT("MainWidget"));
        
        if (MainWidget != nullptr)
        {
            MainWidget->AddToViewport();
        }
    }

    if (GameOverWidgetClass != nullptr)
    {
        GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass, TEXT("GameOverWidget"));
    }
}

void AShootingGameModeBase::AddScore(int32 EarnScore)
{
    CurrentScore += EarnScore;
    MaxScore = FMath::Max(CurrentScore, MaxScore);

    PrintScore();
}

void AShootingGameModeBase::PrintScore()
{
    if (MainWidget != nullptr)
        MainWidget->ScoreData->SetText(FText::AsNumber(CurrentScore));
}

void AShootingGameModeBase::GameOver()
{
    if (GameOverWidget != nullptr)
    {
        GameOverWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
        GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
    }
}
