
2023年10月17日23:12:39

本次修改内容，是在之前小工具基础上，增加对word文件的识别，是否有省市区县（浙江省内），使用Python的开源cpca库（https://github.com/DQinYuan/chinese_province_city_area_mapper）
自己修改了部分源码（见"Python文件"这个文件夹）下面有几个坑记录下。

开始：
最开始甚至想用百度NLP处理，但是一方面要收费，一方面对接很麻烦，后来搜到有专门的开源代码就用Python解决，其实最终也就花了7个晚上就搞定了，再一次做到了自己一开始觉得“太难了”“很麻烦”的事，其实一点都不难，也不麻烦。抓住主要矛盾，通过任何方式解决掉即可。

后端：

1.先用字符串识别，涉及到修改cpca库源码，限制浙江省内的省市区县，返回格式源码是表格的格式，修改成了list

2.再把入参改成读取word文件的段落

3.现在发现word读取表格中的段落的时候特别慢，在考虑用多线程

前端：

1.后端写好后打算和前端连接，但是百度的方法很少有C++ Builder工具的，装的vscode好像也不对，后来根据百度的vscode修改的配置的中文翻译成英文对照着在CB里找，才知道要链接Python的库才行，include path要修改。同时百度还说要修改一个Python36_d.lib 的文件进行编译，cmd转码的时候发现32位数不对解决了问题2
![image](https://github.com/zhangity/C-Builder-to-Word---checkProandCity/assets/9999872/387a2188-6f2f-426d-b16f-94b42181bdd5)
![image](https://github.com/zhangity/C-Builder-to-Word---checkProandCity/assets/9999872/eaaa6728-412d-454b-be84-32f9c967d5f8)

2.但是Py_IsInitialized还是一直失败找不到原因，一直没考虑到32位和64位的问题，刚好电脑里有另一个版本的Python，重新设置了Python_Home竟然初始化成功了，这时候才知道CB是32位的Python是64位的二者不兼容所以无法调用，装了32位Python以后就可以连接了

3.但是这时cpca库又报错了，引入的时候报他wiki那个错，找到vs_BuildTools 安装win10SDK和14版本以上的BuildTools可以了

4.CB链接这时候才知道是有专门的CPython库调用，调用方法和入参又是走了很多弯路才成功

5.前端可以直接触发成功以后（返回英文和数字正常中文乱码），开始考虑返回值的展示，涉及到文字编码问题，C++是gb2312但是Python是UTF8,先修改了Python给前端的返回值，让中文可以正常展示，随后考虑入参传文件路径给Pyhon自动读取，也涉及到字符转换。最主要的从前端作为入口的话后端Python即使有print也不会弹窗，也是后来才知道

6.考虑可以直接拖拽文件到小工具内自动识别文件路径，百度了好多有一个没写清楚，最后自己琢磨才知道要在初始化界面的时候就进行设置允许拖入文件DragAcceptFiles，走了很多弯路以为是要加一个控件

7.编译后的exe给老婆电脑结果点击就闪退，解决中。。。

上面全部内容最难的是CB和Python链接那里，根本不知道工具要在哪里改设置怎么链接，也不知道32位和64位不兼容的问题，也不知道拖拽文档进来如何实现，其他的多少还能百度到。
但是好在最终还是做出来了，还是很开心的。









