// Copyright Epic Games, Inc. All Rights Reserved.


#include "LemonSourGameModeBase.h"

// ���� ������Ʈ
#include "Components/WidgetComponent.h"

ALemonSourGameModeBase::ALemonSourGameModeBase()
{
	/*WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());*/


}

void ALemonSourGameModeBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("begin play called!"));

	if (IsValid(WidgetClass))
	{
		GameModeWidget = Cast<UGameModeWidget>(CreateWidget(GetWorld(), WidgetClass));
		UE_LOG(LogTemp, Warning, TEXT("casted!"));

		if (GameModeWidget != nullptr)
		{
			GameModeWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("added!"));
		}
	}
}
