// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthWidget.h"
#include "Components/ProgressBar.h"

void UHealthWidget::SetHealth(int health) {

    float percent = health / 100.0f;
    HealthPlayer_->SetPercent(percent);

}