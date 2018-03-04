#pragma once

#include "Octree.h"
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "RuntimeMeshComponent.h"
#include "ConstructorHelpers.h"

#include "TestActor.generated.h"
class FOctree;
UCLASS()
class ATestActor : public AActor 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	URuntimeMeshComponent* RMC;
	
	FOctree* MainOctree;

	ATestActor();
	~ATestActor();
	void Tick(float DeltaTime) override;
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetOctreeValue(FVector Location);

	UFUNCTION(BlueprintCallable)
	void RenderOctree();
};