// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <nlohmann/json.hpp>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "fstream"
#include "nlohmannjsonBPLibrary.generated.h"

using namespace std;
using json = nlohmann::json;

USTRUCT(BlueprintType)
struct FJSON
{
	GENERATED_BODY()
	FJSON(){};
	FJSON(json d):data(d){};

	json data;

};




UCLASS()
class UnlohmannjsonBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load JSON", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON loadjsonfile(const FString& file);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static const FJSON& PrintJSON(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON Type", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static void PrintJSONType(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON String", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString GetString(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Float", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static float GetFloat(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Integer", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static int32 GetInteger(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Boolean", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool GetBoolean(const FJSON& JSON, const FString& str);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Object", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON GetObject(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON GetArray(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Element", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON GetArrayElement(const FJSON& JSON, int32 Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value String", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString ToString(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Float", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static float ToFloat(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Integer", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static int ToInteger(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Boolean", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool ToBoolean(const FJSON& JSON);
	

};
