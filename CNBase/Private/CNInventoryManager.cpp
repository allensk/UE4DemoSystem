// Fill out your copyright notice in the Description page of Project Settings.


#include "CNInventoryManager.h"
#include "CNInventoryComponent.h"
#include "CNGameLog.h"

// Sets default values for this component's properties
UCNInventoryManager::UCNInventoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
	Inventory = CreateDefaultSubobject<UCNInventoryComponent>(TEXT("Inventory"));
}


// Called when the game starts
void UCNInventoryManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCNInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCNInventoryManager::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(CNLog, Verbose, TEXT("UCNInventoryManager::InitializeComponent"));
}