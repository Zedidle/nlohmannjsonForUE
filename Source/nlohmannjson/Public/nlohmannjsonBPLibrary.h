// Author: Zen5th

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
	GENERATED_USTRUCT_BODY()
	FJSON():data(new json){};
	FJSON(json& d) :data(&d) {};
	FJSON(json* d) :data(d) {};

	json* data;;

	operator bool() const {
		return bool(data);
	}

	const FJSON SetField(const FString& key, const FJSON& field);
};



UCLASS()
class NLOHMANNJSON_API UnlohmannjsonBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/* Load file to Make JSON */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load JSON"), Category = "njson")
	static FJSON& Loadjsonfile(const FString& file);

	/* Parse a string to json, it's should be vliad json string. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse JSON"), Category = "njson")
	static FJSON Parse(const FString& content);

	/* Handle  UTF8 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "BinaryDecode"), Category = "njson")
	static FString BinaryDecode(const FString& Message);

	/* Print JSON as string on Screen */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON"), Category = "njson")
	static const FJSON& PrintJSON(const FJSON& J);

	/* Print JSON's datatype */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Type", CompactNodeTitle = "Type"), Category = "njson")
	static FString GetJSONType(const FJSON& J);

	/* Convert JSON as string */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "ToPrettyString"), Category = "njson")
	static FString JSONToString(const FJSON& J);

	/* Get JSON string field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON String"), Category = "njson")
	static FString GetString(const FJSON& J, const FString& key);

	/* Get JSON float field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Float"), Category = "njson")
	static float GetFloat(const FJSON& J, const FString& key);

	/* Get JSON integer field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Integer"), Category = "njson")
	static int32 GetInteger(const FJSON& J, const FString& key);

	/* Get JSON bool field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Boolean"), Category = "njson")
	static bool GetBoolean(const FJSON& J, const FString& key);
	
	/* Judge if a JSON is object type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Object Self"), Category = "njson")
	static bool IsObjectSelf(const FJSON& J);
	/* Judge if a JSON's field with the key is object type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Object"), Category = "njson")
	static bool IsObject(const FJSON& J, const FString& key);
	/* Get JSON's object field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Object"), Category = "njson")
	static FJSON GetObject(const FJSON& J, const FString& key, bool copy);

	/* Judge if a JSON is array type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Array Self"), Category = "njson")
	static bool IsArraySelf(const FJSON& J);
	/* Judge if a JSON's field with the key is array type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Array"), Category = "njson")
	static bool IsArray(const FJSON& J, const FString& key);
	/* Get JSON's array field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array"), Category = "njson")
	static FJSON GetArray(const FJSON& J, const FString& key);

	/* Get JSON array's length */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Size", CompactNodeTitle = "Size"), Category = "njson")
	static int GetArraySize(const FJSON& J);

	/* Get JSON array's element with index */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Element", CompactNodeTitle = "GetElement"), Category = "njson")
	static FJSON GetArrayElement(const FJSON& J, int32 Index);

	/* Remove element from a JSON array given an index */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove JSON Array Element at Index", CompactNodeTitle = "EraseElement"), Category = "njson")
	static FJSON EraseArrayElementAtIndex(const FJSON& J, int32 Index);

	/* Remove element from a JSON array given an index */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove JSON Object Filed by Key", CompactNodeTitle = "RemoveKey"), Category = "njson")
	static FJSON RemoveObjectFieldByKey(const FJSON& J, const FString& key);

	/* Convert JSON to string type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value String", CompactNodeTitle = "ToString"), Category = "njson")
	static FString ToString(const FJSON& J);

	/* Convert JSON to float type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Float", CompactNodeTitle = "ToFloat"), Category = "njson")
	static float ToFloat(const FJSON& J);

	/* Convert JSON to integer type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Integer", CompactNodeTitle = "ToInt"), Category = "njson")
	static int ToInteger(const FJSON& J);

	/* Convert JSON to bool type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Boolean", CompactNodeTitle = "ToBool"), Category = "njson")
	static bool ToBoolean(const FJSON& J);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Filed"), Category = "njson")
	static FJSON SetJSONField(const FJSON& J, const FString& key, const FJSON& field);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Fileds"), Category = "njson")
	static FJSON MultiSetJSONFields(const FJSON& J, const TMap<FString, FJSON>& kf);


	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON String", CompactNodeTitle = "JSON String"), Category = "njson")
	static FJSON MakeJSONString(const FString& S);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Int", CompactNodeTitle = "JSON Int"), Category = "njson")
	static FJSON MakeJSONInt(const int I);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Float", CompactNodeTitle = "JSON Float"), Category = "njson")
	static FJSON MakeJSONFloat(const double F);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Bool", CompactNodeTitle = "JSON Bool"), Category = "njson")
	static FJSON MakeJSONBool(const bool B);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Array", CompactNodeTitle = "Array JSON"), Category = "njson")
	static FJSON MakeJSONArray(const TArray<FJSON>& ArrayS);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Array String", CompactNodeTitle = "Array String"), Category = "njson")
	static FJSON MakeJSONArrayString(const TArray<FString>& ArrayS);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Array Int", CompactNodeTitle = "Array Int"), Category = "njson")
	static FJSON MakeJSONArrayInt(const TArray<int32>& ArrayI);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Array Float", CompactNodeTitle = "Array Float"), Category = "njson")
	static FJSON MakeJSONArrayFloat(const TArray<float>& ArrayF);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make JSON Array Bool", CompactNodeTitle = "Array Bool"), Category = "njson")
	static FJSON MakeJSONArrayBool(const TArray<bool>& ArrayB);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JSON PushBack As Array", CompactNodeTitle = "Push Back"), Category = "njson")
	static FJSON JSONArrayPushBack(const FJSON& J, const FJSON& J2);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Keys"), Category = "njson")
	static TArray<FString> GetJSONKeys(const FJSON& J);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save JSON"), Category = "njson")
	static void SaveJSON(const FJSON& J, const FString& filepath);

};
