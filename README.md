2020-08-09

根据序号+文字生成word文档表格

主要参考微软官方的API文档制作
https://docs.microsoft.com/zh-cn/office/vba/api/word.application


编译时项目要选择debug模式编译，并且在project->Options->Packages中取消Builder with runtime packages的对钩
project->选项->链接器中取消使用动态RTL的对钩，否则编译出来会报错XXX.bpl没有
如果好好的报了这个错，那就项目clean，重新编译即可
