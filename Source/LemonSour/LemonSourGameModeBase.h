#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HUD/GameModeWidget.h"
#include "Public/Events/InputEventCode.h"
#include "LemonSourGameModeBase.generated.h"

class UWidgetComponent;
class UGameModeWidget;

class AEvent_CameraLock;
class AEvent_SavePoint;

class ALemonCharacter;
class APlayerStart;

UCLASS()
class LEMONSOUR_API ALemonSourGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// 생성자
	ALemonSourGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "ClassTypes")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	UGameModeWidget* GameModeWidget;

	// 리스폰을 위한 엑터 데이터입니다
	AEvent_CameraLock* Tmp_CameraEvent;
	// 231228; 자꾸 call ref되서 그냥 save point 이벤트로 옮겨버렸습니다
	AEvent_CameraLock* CameraEvent;
	AEvent_SavePoint* SaveEvent;

public:
	// 리스폰을 위한 값을 설정합니다
	void SetCameraEvent(AEvent_CameraLock* Actor);
	void SetSaveEvent(AEvent_SavePoint* Actor);
	// 반대로 외부에서 참조합니다
	AEvent_CameraLock* GetCameraEvent();
	AEvent_SavePoint* GetSaveEvent();

	void RespawnCharacter();

	// event에게서 code에 의한 호출을 받습니다
	virtual void InvokeEvents(EEventCode EventCode);

protected:
	ALemonCharacter* LemonCharacter;
	APlayerStart* StartPoint;

	// 뭔가 null 뜰까봐 무서움
	ALemonCharacter* SearchLemonCharacter();


private:
	FVector DefaultRespawnPoint;
};
