// Copyright Epic Games, Inc. All Rights Reserved.

#include "nlohmannjsonBPLibrary.h"
#include "nlohmannjson.h"

UnlohmannjsonBPLibrary::UnlohmannjsonBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FJSON UnlohmannjsonBPLibrary::loadjsonfile(const FString& file)
{
	std::ifstream f(TCHAR_TO_UTF8(*file));
	if (!f) {
		// 抛出异常
		//throw("Can't find file %s", file);
		//throw std::runtime_error("load json file failure");
		UE_LOG(LogTemp, Error, TEXT("UnlohmannjsonBPLibrary::loadjsonfile load error: %s"), *file);
		return FJSON(nullptr);
	}

	json data = json::parse(f);
	FJSON j(data);
	f.close();
	return  j;
}

FJSON UnlohmannjsonBPLibrary::Parse(const FString& content)
{
	json j = json::parse(TCHAR_TO_UTF8(*content));
	return FJSON(j);
}

const FJSON& UnlohmannjsonBPLibrary::PrintJSON(const FJSON& JSON)
{
	string s = JSON.data.dump();
	UE_LOG(LogTemp, Log, TEXT("Print JSON : %s"), UTF8_TO_TCHAR(s.c_str()));
	
	const FString Message = FString::Printf(TEXT("Print JSON : %s"), UTF8_TO_TCHAR(s.c_str()));
	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, *Message);
	}
	return JSON;
}

FString UnlohmannjsonBPLibrary::GetJSONType(const FJSON& JSON)
{
	string s = JSON.data.type_name();
	return s.c_str();
}

void UnlohmannjsonBPLibrary::PrintJSONType(const FJSON& JSON)
{
	string s = JSON.data.type_name();
	UE_LOG(LogTemp, Log, TEXT("Print JSON Type: %s"), UTF8_TO_TCHAR(s.c_str()));

	const FString Message = FString::Printf(TEXT("Print JSON Type: %s"), UTF8_TO_TCHAR(s.c_str()));
	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, *Message);
	}
}

FString UnlohmannjsonBPLibrary::JSONToString(const FJSON& JSON)
{
	string s = JSON.data.dump();
	const FString Message = FString::Printf(TEXT("%s"), UTF8_TO_TCHAR(s.c_str()));
	return Message;
}

FString UnlohmannjsonBPLibrary::GetString(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	if (JSON.data.contains(key))
	{
		json b = JSON.data[key];

		check(b.is_string());
		if (b.is_string()) {
			string result = b.template get<string>();
			return result.c_str();
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("JSON GetString :  No String Type ."));
			return "JSONGetString-NoStringType";
		}
	}
	else
	{
		return "Key-Absent";
	}
}

float UnlohmannjsonBPLibrary::GetFloat(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_number_float());
	if (b.is_number_float()) {
		float result = b.template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Float Type ."));
		return 0.0f;
	}
}

int32 UnlohmannjsonBPLibrary::GetInteger(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_number_integer());
	if (b.is_number_integer()) {
		int32 result = b.template get<int32>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Integer Type ."));
		return 0;
	}

}

bool UnlohmannjsonBPLibrary::GetBoolean(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_boolean());
	if (b.is_boolean()) {
		bool result = b.template get<bool>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Boolean Type ."));
		return false;
	}

}

bool UnlohmannjsonBPLibrary::IsObjectSelf(const FJSON& JSON)
{
	return JSON.data.is_object();
}

bool UnlohmannjsonBPLibrary::IsObject(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	return b.is_object();
}

FJSON UnlohmannjsonBPLibrary::GetObject(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	if (JSON.data.contains(key))
	{
		json b = JSON.data[key];
		check(b.is_object());
		if (b.is_object()) {
			json result = b.template get<json>();
			return FJSON(result);
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("JSON GetObject :  No Object Type ."));
			return FJSON();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("JSON GetObject :  Key-Absent."));
		return FJSON();
	}
}

bool UnlohmannjsonBPLibrary::IsArraySelf(const FJSON& JSON)
{
	return JSON.data.is_array();
}

bool UnlohmannjsonBPLibrary::IsArray(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	return b.is_array();
}

FJSON UnlohmannjsonBPLibrary::GetArray(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_array());
	if (b.is_array()) {
		json result = b.template get<json>();
		return FJSON(result);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Array Type ."));
		return FJSON();
	}
}

FJSON UnlohmannjsonBPLibrary::GetArrayElement(const FJSON& JSON, int32 Index)
{
	check(JSON.data.is_array());
	if (JSON.data.is_array())
	{
		json b = JSON.data[Index];
		return FJSON(b);
	}
	else {
		return FJSON();
	}
}

int UnlohmannjsonBPLibrary::GetArraySize(const FJSON& JSON)
{
	check(JSON.data.is_array());
	if (JSON.data.is_array())
	{
		return JSON.data.size();
	}
	else
	{
		return 0;
	}
}

FString UnlohmannjsonBPLibrary::ToString(const FJSON& JSON)
{
	check(JSON.data.is_string());
	if (JSON.data.is_string()) {
		string result = JSON.data.template get<string>();
		return result.c_str();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToString :  No String Type ."));
		return "";
	}
}

float UnlohmannjsonBPLibrary::ToFloat(const FJSON& JSON)
{
	check(JSON.data.is_number_float());
	if (JSON.data.is_number_float()) {
		float result = JSON.data.template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToFloat :  No Float Type ."));
		return 0.0f;
	}
}

int UnlohmannjsonBPLibrary::ToInteger(const FJSON& JSON)
{
	check(JSON.data.is_number_integer());
	if (JSON.data.is_number_integer()) {
		float result = JSON.data.template get<int>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToInteger :  No Integer Type ."));
		return 0;
	}
}

bool UnlohmannjsonBPLibrary::ToBoolean(const FJSON& JSON)
{
	check(JSON.data.is_boolean());
	if (JSON.data.is_boolean()) {
		bool result = JSON.data.template get<bool>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToBoolean :  No Boolean Type ."));
		return false;
	}
}

FString UnlohmannjsonBPLibrary::UrlEncode(const FString& String)
{
	string str = TCHAR_TO_UTF8(*String);
	std::ostringstream escaped;
	escaped.fill('0');
	escaped << std::hex;

	for (char c : str) {
		// 保留字符不编码
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
		}
		else {
			// 将非保留字符编码为%xx形式
			escaped << '%' << std::setw(2) << int((unsigned char)c);
		}
	}

	//UE_LOG(LogTemp, Log, TEXT("UrlEncode2 : %s ."), escaped.str().c_str());
	return escaped.str().c_str();
}

FString UnlohmannjsonBPLibrary::BinaryDecode(const FString& Message)
{
		// 在这里处理来自 JavaScript 的消息
		// 你需要将 UTF-8 编码的字符串转换为 Unreal Engine 的 FString
		FString DecodedMessage = FString(UTF8_TO_TCHAR(TCHAR_TO_UTF8(*Message)));

		// 现在你可以在这里处理你的中文消息
		UE_LOG(LogTemp, Log, TEXT("Received message from JavaScript: %s"), *DecodedMessage);
		return DecodedMessage;
}
