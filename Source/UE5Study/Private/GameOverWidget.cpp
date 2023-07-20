// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UGameOverWidget::Restart()
{
    UGameplayStatics::OpenLevel(GetWorld(), "MainLevelC++");
}

void UGameOverWidget::Exit()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UGameOverWidget::NativeConstruct()
{
    RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::Restart);
    ExitButton->OnClicked.AddDynamic(this, &UGameOverWidget::Exit);
}
