// Copyright Epic Games, Inc. All Rights Reserved.

#include "nlohmannjsonBPLibrary.h"
#include "nlohmannjson.h"



const FJSON FJSON::SetField(const FString& key, const FJSON& field)
{
	string k = TCHAR_TO_UTF8(*key);
	if (data->is_object())
	{
		(*data)[k] = *(field.data);
	}
	else if (data->is_null())
	{
		data = new json;
		(*data)[k] = *(field.data);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("It's not a valid type can set a key-field"));
	}
	return *this;
}



UnlohmannjsonBPLibrary::UnlohmannjsonBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


FJSON& UnlohmannjsonBPLibrary::Loadjsonfile(const FString& file)
{
	std::ifstream f(TCHAR_TO_UTF8(*file));
	if (!f) {
		UE_LOG(LogTemp, Error, TEXT("UnlohmannjsonBPLibrary::loadjsonfile load error: %s"), *file);
		return *(new FJSON());
	}
	json* ptr_j = new json(json::parse(f, nullptr, false));
	FJSON* J = new FJSON(ptr_j);
	if (ptr_j->is_discarded()) {
		UE_LOG(LogTemp, Error, TEXT("UnlohmannjsonBPLibrary::loadjsonfile load error: %s , incorrect data format. "), *file);
	}
	f.close();
	return *J;
}


FJSON UnlohmannjsonBPLibrary::Parse(const FString& content)
{
	json* ptr_j = new json(json::parse(TCHAR_TO_UTF8(*content), nullptr, false));
	FJSON* J = new FJSON(ptr_j);
	if (ptr_j->is_discarded()) {
		UE_LOG(LogTemp, Error, TEXT("UnlohmannjsonBPLibrary::loadjsonfile load error: %s , incorrect data format. "), *content);
	}
	return *J;
}

FString UnlohmannjsonBPLibrary::BinaryDecode(const FString& Message)
{
	FString DecodedMessage = FString(UTF8_TO_TCHAR(TCHAR_TO_UTF8(*Message)));
	return DecodedMessage;
}



const FJSON& UnlohmannjsonBPLibrary::PrintJSON(const FJSON& J)
{
	if (J.data)
	{
		string s = (*J.data).dump();
		UE_LOG(LogTemp, Log, TEXT("Print J : %s"), UTF8_TO_TCHAR(s.c_str()));

		const FString Message = FString::Printf(TEXT("Print J : %s"), UTF8_TO_TCHAR(s.c_str()));
		if (GEngine != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, *Message);
		}
	}
	return J;
}

FString UnlohmannjsonBPLibrary::GetJSONType(const FJSON& J)
{
	string s = J.data->type_name();
	return s.c_str();
}

FString UnlohmannjsonBPLibrary::JSONToString(const FJSON& J)
{
	string s = J.data->dump();
	const FString Message = FString::Printf(TEXT("%s"), UTF8_TO_TCHAR(s.c_str()));
	return Message;
}

FString UnlohmannjsonBPLibrary::GetString(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	if (J.data->contains(k))
	{
		json j = (*J.data)[k];

		if (j.is_number_integer())
		{
			int i = j.template get<int>();
			return FString::FromInt(i);
		}
		else if (j.is_number_float())
		{
			float f = j.template get<float>();
			return FString::SanitizeFloat(f);
		}
		else if (j.is_boolean())
		{
			bool b = j.template get<bool>();
			return b ? FString("true") : FString("false");
		}
		else if (j.is_string())
		{
			string result = j.template get<string>();
			return result.c_str();
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("J GetString :  No String Type ."));
			return "JSONGetString-NoStringType";
		}
	}
	else
	{
		return "Key-Absent";
	}
}

float UnlohmannjsonBPLibrary::GetFloat(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json j = (*J.data)[k];
	check(j.is_number_float());
	if (j.is_number_float()) {
		float f = j.template get<float>();
		return f;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Float Type ."));
		return 0.0f;
	}
}

int32 UnlohmannjsonBPLibrary::GetInteger(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json j = (*J.data)[k];
	check(j.is_number_integer());
	if (j.is_number_integer()) {
		int32 i = j.template get<int32>();
		return i;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetInteger :  No Integer Type ."));
		return 0;
	}

}

bool UnlohmannjsonBPLibrary::GetBoolean(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json j = (*J.data)[k];
	check(j.is_boolean());
	if (j.is_boolean()) {
		bool b = j.template get<bool>();
		return b;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Boolean Type ."));
		return false;
	}

}

bool UnlohmannjsonBPLibrary::IsObjectSelf(const FJSON& J)
{
	return J.data->is_object();
}

bool UnlohmannjsonBPLibrary::IsObject(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json j = (*J.data)[k];
	return j.is_object();
}

FJSON UnlohmannjsonBPLibrary::GetObject(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	if (J.data->contains(k))
	{
		json j = (*J.data)[k];
		check(j.is_object());
		if (j.is_object()) {
			json* result = new json(j.template get<json>());
			return FJSON(result);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("JSON GetObject :  No Object Type ."));
			return FJSON();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("JJSON GetObject :  Key-Absent."));
		return FJSON();
	}
}

bool UnlohmannjsonBPLibrary::IsArraySelf(const FJSON& J)
{
	return J.data->is_array();
}

bool UnlohmannjsonBPLibrary::IsArray(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json j = (*J.data)[k];
	return j.is_array();
}

FJSON UnlohmannjsonBPLibrary::GetArray(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json j = (*J.data)[k];
	check(j.is_array());
	if (j.is_array()) {
		json* result = new json(j.template get<json>());
		return FJSON(result);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("JSON GetFloat :  No Array Type ."));
		return FJSON();
	}
}

FJSON UnlohmannjsonBPLibrary::GetArrayElement(const FJSON& J, int32 Index)
{
	check(J.data->is_array());
	if (J.data->is_array())
	{
		return FJSON((*J.data)[Index]);
	}
	else {
		return FJSON();
	}
}

int UnlohmannjsonBPLibrary::GetArraySize(const FJSON& J)
{
	check(J.data->is_array());
	if (J.data->is_array())
	{
		return J.data->size();
	}
	else
	{
		return 0;
	}
}

FString UnlohmannjsonBPLibrary::ToString(const FJSON& J)
{
	check(J.data->is_string());
	if (J.data->is_string()) {
		string result = J.data->template get<string>();
		return result.c_str();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("JSON ToString :  No String Type ."));
		return "";
	}
}

float UnlohmannjsonBPLibrary::ToFloat(const FJSON& J)
{
	check(J.data->is_number_float());
	if (J.data->is_number_float()) {
		float result = J.data->template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("JSON ToFloat :  No Float Type ."));
		return 0.0f;
	}
}

int UnlohmannjsonBPLibrary::ToInteger(const FJSON& J)
{
	check(J.data->is_number_integer());
	if (J.data->is_number_integer()) {
		float result = J.data->template get<int>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("JSON ToInteger :  No Integer Type ."));
		return 0;
	}
}

bool UnlohmannjsonBPLibrary::ToBoolean(const FJSON& J)
{
	if (J.data->is_boolean()) {
		bool result = J.data->template get<bool>();
		return result;
	}
	else if (J.data->is_string())
	{
		string s = J.data->template get<string>();
		if(s == "true"){
			return true;
		}
		else if(s == "false")
		{
			return false;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("J ToBoolean :  No Boolean Type ."));
	return false;
}

FJSON UnlohmannjsonBPLibrary::SetJSONField(const FJSON& J, const FString& key, const FJSON& field)
{
	string k = TCHAR_TO_UTF8(*key);
	if (J.data->is_object())
	{
		(*J.data)[k] = *(field.data);
	}
	else if(J.data->is_null())
	{
		(*J.data)[k] =  *(field.data);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("It's not a valid type can set a key-field"));
	}
	
	return J;
}

FJSON UnlohmannjsonBPLibrary::MultiSetJSONFields(const FJSON& J, const TMap<FString, FJSON>& kf)
{
	for (const auto& Pair : kf)
	{
		SetJSONField( J, Pair.Key, Pair.Value);
	}
	return J;
}


FJSON UnlohmannjsonBPLibrary::MakeJSONString(const FString& S)
{
	json* ptr_j = new json(*S);
	return FJSON(ptr_j);
}


FJSON UnlohmannjsonBPLibrary::MakeJSONInt(const int I)
{
	json* ptr_j = new json(I);
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONFloat(const double F)
{
	json* ptr_j = new json(F);
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONBool(const bool B)
{
	json* ptr_j = new json(B);
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONArray(const TArray<FJSON>& ArrayJ)
{
	json* ptr_j = new json;
	for (const FJSON& J : ArrayJ)
	{
		ptr_j->push_back((*J.data));
	}
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONArrayString(const TArray<FString>& ArrayS)
{
	json* ptr_j = new json;
	for (const FString& S : ArrayS)
	{
		ptr_j->push_back(*S);
	}
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONArrayInt(const TArray<int32>& ArrayI)
{
	json* ptr_j = new json;
	for (const int32& I : ArrayI)
	{
		ptr_j->push_back(I);
	}
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONArrayFloat(const TArray<float>& ArrayF)
{
	json* ptr_j = new json;
	for (const float& F : ArrayF)
	{
		ptr_j->push_back(F);
	}
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::MakeJSONArrayBool(const TArray<bool>& ArrayB)
{
	json* ptr_j = new json;
	for (const bool& B : ArrayB)
	{
		ptr_j->push_back(B);
	}
	return FJSON(ptr_j);
}

FJSON UnlohmannjsonBPLibrary::JSONArrayPushBack(const FJSON& J, const FJSON& J2)
{
	if (J.data->is_null() || J.data->is_array())
	{
		J.data->push_back(*(J2.data));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UnlohmannjsonBPLibrary::JSONArrayPushBack error : the former isn't valid type to push. "));
	}

	return J;
}

void UnlohmannjsonBPLibrary::SaveJSON(const FJSON& J, const FString& filepath)
{
	std::ofstream f(TCHAR_TO_UTF8(*filepath));

	FString s = JSONToString(J);
	if (f.is_open())
	{
		f << TCHAR_TO_UTF8(*s);
		f.close();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Filepath is not valid"));
	}
}

TArray<FString> UnlohmannjsonBPLibrary::GetJSONKeys(const FJSON& J)
{
	TArray<FString> Arr;
	for (auto& item : J.data->items())
	{
		Arr.Add(item.key().c_str());
	}
	return Arr;
}
