#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HUD/GameModeWidget.h"
#include "LemonSourGameModeBase.generated.h"

class UWidgetComponent;
class UGameModeWidget;

UCLASS()
class LEMONSOUR_API ALemonSourGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// ������
	ALemonSourGameModeBase();

	virtual void BeginPlay() override;

	// gamemode�� ����� ����: �ϴ� BP���� �Ѱܺ���
	/*UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;*/

	UPROPERTY(EditAnywhere, Category = "ClassTypes")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	UGameModeWidget* GameModeWidget;
};
