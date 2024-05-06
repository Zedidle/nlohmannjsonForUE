// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <nlohmann/json.hpp>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "fstream"
#include <iostream>
#include <iomanip>
#include <sstream>
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
	operator bool() const {
		return bool(data);
	}
};



UCLASS()
class NLOHMANNJSON_API UnlohmannjsonBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load JSON", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON loadjsonfile(const FString& file);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prase JSON", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON Parse(const FString& content);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static const FJSON& PrintJSON(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get JSON Type", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString GetJSONType(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON Type", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static void PrintJSONType(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "ToString", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString JSONToString(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON String", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString GetString(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Float", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static float GetFloat(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Integer", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static int32 GetInteger(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Boolean", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool GetBoolean(const FJSON& JSON, const FString& str);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Object Self", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool IsObjectSelf(const FJSON& JSON);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Object", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool IsObject(const FJSON& JSON, const FString& str);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Object", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON GetObject(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Array Self", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool IsArraySelf(const FJSON& JSON);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Array", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool IsArray(const FJSON& JSON, const FString& str);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON GetArray(const FJSON& JSON, const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Element", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FJSON GetArrayElement(const FJSON& JSON, int32 Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Size", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static int GetArraySize(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value String", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString ToString(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Float", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static float ToFloat(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Integer", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static int ToInteger(const FJSON& JSON);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Boolean", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static bool ToBoolean(const FJSON& JSON);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "UrlEncode", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString UrlEncode(const FString& String);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "BinaryDecode", Keywords = "nlohmannjson"), Category = "nlohmannjson")
	static FString BinaryDecode(const FString& Message);


};
