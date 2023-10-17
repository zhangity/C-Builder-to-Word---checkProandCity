
2023年10月17日23:12:39

本次修改内容，是在之前小工具基础上，增加对word文件的识别，是否有省市区县（浙江省内），使用Python的开源cpca库（https://github.com/DQinYuan/chinese_province_city_area_mapper）
自己修改了部分源码（见"Python文件"这个文件夹）下面有几个坑记录下。

后端：
1.先用字符串识别，涉及到修改cpca库源码，限制浙江省内的省市区县，返回格式源码是表格的格式，修改成了list
2.再把入参改成读取word文件的段落
3.现在发现word读取表格中的段落的时候特别慢，在考虑用多线程

前端：
1.后端写好后打算和前端连接，但是百度的方法很少有C++ Builder工具的，装的vscode好像也不对，后来根据百度的vscode修改的配置的中文翻译成英文对照着在CB里找，才知道要链接Python的库才行
![image](https://github.com/zhangity/C-Builder-to-Word---checkProandCity/assets/9999872/387a2188-6f2f-426d-b16f-94b42181bdd5)












