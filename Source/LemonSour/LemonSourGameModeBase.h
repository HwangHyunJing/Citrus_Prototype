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
	// 생성자
	ALemonSourGameModeBase();

	virtual void BeginPlay() override;

	// gamemode가 사용할 위젯: 일단 BP에서 넘겨보기
	/*UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;*/

	UPROPERTY(EditAnywhere, Category = "ClassTypes")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	UGameModeWidget* GameModeWidget;
};
