# NJson
### 使用Github上Star数最高的JSON库 <https://github.com/nlohmann/json> 来对UE做的中间层扩展, 目前支持：
- 读取文件来加载json数据，无需事先定义结构，可以按需解析任何json结构；
- 读取文本解析为JSON结构数据；
- 读取数组、对象、字符串、float、int、bool作为值读取与转化；
- 中文utf8转码解析；

<br>

自定义了与蓝图通讯的结构**FJSON**，全部方法都写在继承UBlueprintFunctionLibrary的函数库中：
![alt text](Resources/image.png)
![alt text](Resources/image-1.png)

<br><br><br>

----
# Epic Unreal Store Information

## Brief
A Json Plugin for UE extend by Github 40K star Json Lib.

<br>

## Details Description
Use BlueprintFunctionLibrary package all nlohmannjson's functions, easy to use in blueprint flexibly.

<br>

## TECHNICAL INFORMATION
Features: 
- Construct Json Object by loadfile, parse string or step by step 
- Save Json Object as string to a file
- Supports maximum flexibility in constructing arrays
- Support types of string, int, float, bool, object, array to addition, deletion, modification and query;

<br>Number of Blueprints: 32+
<br>Supported Development Platforms:
<br>$~~~$ Windows: Yes
<br>$~~~$ Linux: Yes
<br>$~~~$ Mac: Yes
<br>Documentation: <https://github.com/Zedidle/nlohmannjsonForUE>
<br>Important/Additional Notes: Plugin use the GitHub 40K Star JsonLib. This ensures flexibility, stability, compatibility.


