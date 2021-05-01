// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::SetScore(int score) {
    FText scoreText;
    FString num = FString(("SCORE:")) + FString::FromInt(score);
    scoreText = FText::FromString(num);
    ScoreText_->SetText(scoreText);
}