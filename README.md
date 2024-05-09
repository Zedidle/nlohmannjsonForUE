# NJson
### 使用Github上Star数最高的JSON库 <https://github.com/nlohmann/json> 来对UE做的中间层扩展, 目前支持：
- 蓝图中无需事先定义任何结构，通过读取文件、解析字符串加载nlohmann::json数据，可以按需逐步解析或构筑任何json结构；
- 将json对象作为字符串存储为某个文件；
- 极度灵活的数组构建；
- 支持string, int, float, bool, object, array类型的增删改查；
- （中文）UTF8转码解析；

<br>

自定义了与蓝图通讯的结构**JSON**，其内部存储一个nlohmann::json结构，所有的函数都是围绕这个nlohmann::json自带的函数来展开，写在继承UBlueprintFunctionLibrary的函数库中：

![alt text](Resources/image.png)
![alt text](Resources/image-1.png)

<br><br><br>

----
# Epic Unreal Store Information

## Brief
A Json Plugin for UE extend by Github 40K star Json Lib <https://github.com/nlohmann/json> .

<br>

## Details Description
Use BlueprintFunctionLibrary package all nlohmann::json's functions, easy to use in blueprint flexibly.

<br>

## TECHNICAL INFORMATION
Features: 
- Construct Json Object by loadfile, parse string or step by step .
- Save Json Object as string to a file .
- Supports maximum flexibility in constructing arrays .
- Support types of string, int, float, bool, object, array to addition, deletion, modification and query .
- Support UTF8 .

<br>Number of Blueprints: 32+
<br>Supported Development Platforms:
<br>$~~~$ Windows: Yes
<br>$~~~$ Linux: Yes
<br>$~~~$ Mac: Yes
<br>Documentation: <https://github.com/Zedidle/nlohmannjsonForUE>
<br>Important/Additional Notes: Plugin use the GitHub 40K Star JsonLib. This ensures flexibility, stability, compatibility, performance.


