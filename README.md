2020-08-09

根据序号+文字生成word文档表格

主要参考微软官方的API文档制作
https://docs.microsoft.com/zh-cn/office/vba/api/word.application


编译时项目要选择debug模式编译，并且在project->Options->Packages中取消Builder with runtime packages的对钩
project->选项->链接器中取消使用动态RTL的对钩，否则编译出来会报错XXX.bpl没有
如果好好的报了这个错，那就项目clean，重新编译即可

------------------------以上是之前的README.md 下面是这次新的-------------------------------------------
2023年10月17日23:12:39

本次修改内容，是在之前小工具基础上，增加对word文件的识别，是否有省市区县（浙江省内），使用Python的开源cpca库（https://github.com/DQinYuan/chinese_province_city_area_mapper），自己修改了部分源码（见"Python文件"这个文件夹）下面有几个坑记录下。

后端：
1.先用字符串识别，涉及到修改cpca库源码，限制浙江省内的省市区县，返回格式源码是表格的格式，修改成了list
2.再把入参改成读取word文件的段落
3.现在发现word读取表格中的段落的时候特别慢，在考虑用多线程

前端：
1.后端写好后打算和前端连接，但是百度的方法很少有C++ Builder工具的，装的vscode好像也不对，后来根据百度的vscode修改的配置的中文翻译成英文对照着在CB里找，才知道要链接Python的库才行
![image](https://github.com/zhangity/C-Builder-to-Word---checkProandCity/assets/9999872/ce89abfa-5ecd-4a67-a299-e70547d0aa91)











