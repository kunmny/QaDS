#include "DialogSystemRuntime.h"
#include "EngineUtils.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "StoryInformationManager.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"

UStoryKeyManager* UStoryKeyManager::Instance = NULL;

UStoryKeyManager* UStoryKeyManager::GetStoryKeyManager(UObject* WorldContextObject)
{
	if (Instance == NULL)
	{
		if(WorldContextObject)
		{
			Instance = NewObject<UStoryKeyManager>(WorldContextObject);
		}
		else
		{
			Instance = NewObject<UStoryKeyManager>();
		}
	}
		

	return Instance;
}

void UStoryKeyManager::BeginDestroy()
{
	Super::BeginDestroy();

	if (Instance == this)
		Instance = NULL;
}

bool UStoryKeyManager::HasKey(const FGameplayTagContainer& Key) const
{
	unimplemented();
	return false;
}

bool UStoryKeyManager::DontHasKey(const FGameplayTagContainer& Key) const
{
	unimplemented();
	return false;
}

bool UStoryKeyManager::AddKey(const FGameplayTagContainer& Key)
{
	unimplemented();
	//if (Database.Contains(Key))
	//	return false;
	//
	//Database.Add(Key);
	//OnKeyAdd.Broadcast(Key);
	//OnKeyAddBP.Broadcast(Key);

	UE_LOG(DialogModuleLog, Log, TEXT("Add key '%s' to storage"), *Key.ToString());
	return true;
}

bool UStoryKeyManager::RemoveKey(const FGameplayTagContainer& Key)
{
	unimplemented();
	//if (!Database.Remove(Key))
	//	return false;
	//
	//OnKeyRemove.Broadcast(Key);
	//OnKeyRemoveBP.Broadcast(Key);

	UE_LOG(DialogModuleLog, Log, TEXT("Remove key '%s' from storage"), *Key.ToString());
	return true;
}

TArray<FName> UStoryKeyManager::GetKeys() const
{
	return Database.Array();
}

void UStoryKeyManager::SetKeys(const TSet<FName>& keys)
{
	Database = keys;
	OnKeysLoaded.Broadcast(Database.Array());
	OnKeysLoadedBP.Broadcast(Database.Array());

	UE_LOG(DialogModuleLog, Log, TEXT("Load %d keys to storage"), keys.Num());
}

void UStoryKeyManager::Reset()
{
	Database.Reset();
	OnKeysLoaded.Broadcast(Database.Array());
	OnKeysLoadedBP.Broadcast(Database.Array());

	UE_LOG(DialogModuleLog, Log, TEXT("Clear storage"));
}

FArchive& operator<<(FArchive& Ar, UStoryKeyManager& A)
{
	return Ar << A.Database;
}

TArray<uint8> UStoryKeyManager::SaveToBinary()
{
	TArray<uint8> result;
	FMemoryWriter writter(result);
	writter << *this;

	return result;
}

void UStoryKeyManager::LoadFromBinary(const TArray<uint8>& Data)
{
	FMemoryReader reader(Data);
	reader << *this;

	OnKeysLoaded.Broadcast(Database.Array());
	OnKeysLoadedBP.Broadcast(Database.Array());
}