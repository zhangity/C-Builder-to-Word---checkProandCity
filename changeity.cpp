
#include <windows.h>
#include <vcl.h>
#pragma hdrstop
#include "comobj.hpp"
#include <Clipbrd.hpp>
#include "changeity.h"
#include <regex>
#include "D:/Program Files (x86)/Python_3.8.5/include/Python.h"
#include "D:/Program Files (x86)/Python_3.6.2/include/Python.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//using namespace boost;
using namespace std;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
Column1->Text = 37.7;
Column2->Text =  461;
// 打开程序的时候就允许拖拽文件，参考https://www.cnblogs.com/hanny/p/9028489.html 但是没说特别清楚
DragAcceptFiles(Handle,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::转换Click(TObject *Sender)
{
		String stext = cc->Text.Trim().c_str();

		// 去掉空格
		TReplaceFlags rf1;
		rf1 << rfReplaceAll;
		stext =  StringReplace(AnsiString(stext.c_str()).c_str()," ","",rf1);

	   char str[5000] = "";
//	   strcpy(str,AnsiString(stext.c_str()).c_str());
		strcpy(str,stext.t_str());

	   char split[] = "\n";
	   char * p = strtok (str,split);

	   TStringList *text, *regexString;
	   text = new TStringList();
	   regexString = new TStringList();
	   // 补充正则表达式
	   regexString->Append("^\\w+\\."); // a. A. 1. _
	   regexString->Append("^\\w+、");  // a、A、1、_
	   regexString->Append("^\\([\u4E00-\u9FA5]{1,3}\\)");  // (一)  (二) (三)
	   regexString->Append("^\\（[\u4E00-\u9FA5]{1,3}\\）");   // 中文的括号
	   regexString->Append("^\\(\\w+\\)");   // 英文的括号
	   regexString->Append("^\\（\\w+\\）"); // (a) (b) (A) (B) (1) （2) 英文括号
	   regexString->Append("^\\w+\\）");   // 中文的括号
	   regexString->Append("^\\w+\\)"); // a) b) A) B) 1) 2) 英文括号
	   regexString->Append("^\\w+\\>");  // 1>  a>
	   regexString->Append("^[\u4E00-\u9FA5]{1,3}、");  // 一、 二、 十一、
		// 最大到20 特殊字符无法用范围的方式去写
//	   regexString->Append("^[\u2460\u2461\u2462\u2463\u2464\u2465\u2466\u2467\u2468\u2469\u2473]");  // ① ② ③
	   regexString->Append("^[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳]、");  // ① ② ③
	   regexString->Append("^[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳]\\.");  // ① ② ③
	   regexString->Append("^[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳]\\．");  // ① ② ③
	   regexString->Append("^[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳]");  // ① ② ③

	   regexString->Append("^[⑴⑵⑶⑷⑸⑹⑺⑻⑼⑽⑾⑿⒀⒁⒂⒃⒄⒅⒆⒇]"); //  特殊的 ⑴ ⑵ ⑶ ⑷

	   // 不带点的场景  需要放在最后否则会和其他1) 这种有冲突
	   regexString->Append("^\\w+");  // a A 1_

	   int i = 0;
	   while(p!= NULL) {
		   String ssss = p;
		   if (ssss.IsEmpty() == false) {
			  AnsiString sstext =  AnsiString(p);

			  TReplaceFlags rf;
			  rf << rfReplaceAll;
			  AnsiString Result = StringReplace(sstext,"\r","",rf);

              Result = Result.Trim();
			  // 去除无效的换行
			  if (Result.IsEmpty()) {
					p = strtok(NULL,split);
                  continue;
			  }

		   // 正则属性用法参考 https://blog.csdn.net/gufengaoyue/article/details/16342115

			 Variant    Axl= Variant::CreateObject("VBScript.RegExp"); //利用脚本里的正则
			  Axl.OlePropertySet("Global",false);//只匹配第一个

			  for (int kk = 0; kk < regexString->Count; kk++) {
					Axl.OlePropertySet("Pattern", regexString->Strings[kk].t_str());  //写入正则表达式
					if (Axl.OleFunction("Test",Result.c_str())) {
					   Result = Axl.OleFunction("Replace",Result.c_str(), "");
//					   ShowMessage(Result);
					   break;
					}

			  }

//			  Axl.OlePropertySet("Pattern", "\\d+\\.");  //写入正则表达式
//			  Variant    rtn=Axl.OleFunction("Execute",Result.c_str());//开始执行
//			  for (int k=0; k!= rtn.OlePropertyGet("Count"); k++) {
//				 ShowMessage((rtn.OlePropertyGet("Item",k).OlePropertyGet("Value")));//取出匹配的东东
//			  }
//
//			  Result = Axl.OleFunction("Replace",Result.c_str(), "");
			  Result = Result.Trim();  // 去掉前后的空格
			  text->Append(Result);
		   }
		   p = strtok(NULL,split);
       }


	Variant WordApp,WordDocs,WordDoc,vWordApp;
	Variant word_activedoc;
	Variant word_select;
	Variant word_table;
	Variant my_cell;

	vWordApp = CreateOleObject("Word.Application");
	// 显示Word界面
	vWordApp.OlePropertySet("Visible", false);
	// 新建一个文档
	vWordApp.OlePropertyGet("Documents").OleFunction("Add");
	//
	Variant vSelect = vWordApp.OlePropertyGet("Selection");

	// 插入一段文字
	//String str1 = "要插入的第一段文字\r\n换一个行先";
	//vSelect.OleProcedure("TypeText", WideString(str1));
	//vSelect.OleProcedure("TypeParagraph");
	// RGB 颜色 bigdecimal 值
	long shenseColor = 15057564;
	long qianseColor = 16181982;

	// 插入一个表格
	int nRowCount = text->Count + 1; // 行
	int nColCount = 2; // 列
	// 添加表格的微软官方API https://docs.microsoft.com/zh-cn/office/vba/api/word.tables.add
	vWordApp.OlePropertyGet("ActiveDocument").OlePropertyGet("Tables")
	.OleProcedure("Add", vSelect.OlePropertyGet("Range"),nRowCount, nColCount,1,0);

	   word_table = vWordApp.OlePropertyGet("ActiveDocument").OlePropertyGet("Tables").OleFunction("Item", 1);

	   // 设置表格列宽为自动    1-自动 2-百分比 3-固定 磅为单位
	   Variant varColumnWidth1 = word_table.OlePropertyGet("Columns").OleFunction("Item", 1); // 第1列
	   Variant varColumnWidth2 = word_table.OlePropertyGet("Columns").OleFunction("Item", 2); // 第2列
	   varColumnWidth1.OlePropertySet("PreferredWidthType", 3);
	   varColumnWidth1.OlePropertySet("PreferredWidth", atoi(Column1->Text.t_str())); //37.7
	   varColumnWidth2.OlePropertySet("PreferredWidthType", 3);
	   varColumnWidth2.OlePropertySet("PreferredWidth", atoi(Column2->Text.t_str())); // 451.61

	   // 第一行第一列写入序号两个字 水平居中 垂直居中
	   my_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)1);
	   my_cell.OlePropertySet("Range", "序号");
	   my_cell.OlePropertyGet("Range").OlePropertyGet("ParagraphFormat").OlePropertySet("Alignment", 1);
	   my_cell.OlePropertySet("VerticalAlignment", 1);
	   // 表格添加背景色 2021年10月16日
	   if (CheckBackColor->Checked) {
		  my_cell.OlePropertyGet("Shading").OlePropertySet("BackgroundPatternColor", shenseColor);
	   }

	   // 第一行 第二列 水平居中  垂直居中
	   my_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)2);
	   my_cell.OlePropertyGet("Range").OlePropertyGet("ParagraphFormat").OlePropertySet("Alignment", 1);
	   my_cell.OlePropertySet("VerticalAlignment", 1);
	   // 表格添加背景色 2021年10月16日
	   if (CheckBackColor->Checked){
		   my_cell.OlePropertyGet("Shading").OlePropertySet("BackgroundPatternColor", shenseColor);
	   }


	 for (int j = 1; j < text->Count + 1; j++) {
		// 第一列数据
		my_cell = word_table.OleFunction("Cell", (Variant)(j + 1), (Variant)1);
		my_cell.OlePropertySet("Range", j);
		// 水平居中
		my_cell.OlePropertyGet("Range").OlePropertyGet("ParagraphFormat").OlePropertySet("Alignment", 1);
		// 垂直居中
		my_cell.OlePropertySet("VerticalAlignment", 1);
		// 表格添加背景色 2021年10月16日
		if (CheckBackColor->Checked) {
			 my_cell.OlePropertyGet("Shading").OlePropertySet("BackgroundPatternColor", qianseColor);
		}

        // 第二列数据
		my_cell = word_table.OleFunction("Cell", (Variant)(j + 1), (Variant)2);
		my_cell.OlePropertySet("Range", text->Strings[j-1].t_str());

		// 给表格添加颜色 2021年10月16日
//	   long colorRGB =R +  G * 256 + B * 65536  ;   // RGB 转 bigdecimal

	 }

	// 将光标移到文档结尾
//	vWordApp.OlePropertyGet("Selection").OleProcedure("EndKey", 6); //wdStory
	// 设定选取范围 并复制
	vSelect.OleProcedure("SetRange", vSelect.OlePropertyGet("Start"),
				vWordApp.OlePropertyGet("ActiveDocument").OlePropertyGet("Content").OlePropertyGet("End"));
	vSelect.OleProcedure("Copy"); 
	// 再插入一段文字
	//String str2 = "要插入的第二段文字";
	//vSelect.OleProcedure("TypeText", WideString(str2));
//   //保存修改内容:
//   word_activedoc.OleProcedure("Save");
//   //打印文档:
//   WordApp.OlePropertyGet("ActiveDocument").OleFunction("PrintOut");
	// 不保存退出
   vWordApp.OleProcedure("Quit", 0);
   successTime->Caption = nRowCount - 1;

}


//---------------------------------------------------------------------------


void __fastcall TForm2::clearClick(TObject *Sender)
{
	cc->Text = "";   // 清空
	successTime->Caption = 0 ;// 转换次数改成0
	cc->SetFocus();   // 获取光标闪烁

}
//---------------------------------------------------------------------------

void __fastcall TForm2::ccChange(TObject *Sender)
{
	 successTime->Caption = 0 ;// 转换次数改成0
}
//---------------------------------------------------------------------------

void __fastcall TForm2::helpClick(TObject *Sender)
{
	ShowMessage("点击转换按钮后，表格已经复制到剪切板，直接粘贴即可！\r\nv1.3更新：拖拽word即可检测文档内是否有省市区县 2023年10月15日 \r\n\r\n版本 v1.2 版权所有-吕天伊 2021年10月16日 ");
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Column1Change(TObject *Sender)
{
       successTime->Caption = 0 ;// 转换次数改成0
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Column2Change(TObject *Sender)
{
	successTime->Caption = 0 ;// 转换次数改成0
}
//---------------------------------------------------------------------------
void __fastcall TForm2::checkProCity(TObject *Sender)
{
	 checkcity->Text =  "检测中";
	// 这里Python 版本要和exe版本一致，之前一直set的是3.8.5的64位的，导致下面的初始化不成功
	Py_SetPythonHome(L"D:\\Program Files (x86)\\Python_3.6.2");
	Py_Initialize();
	if(!Py_IsInitialized()){
		ShowMessage("python解释器初始化失败\n");
	}
	//初始化使用的变量
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
	PyObject* pName = NULL;

	// 参考 https://www.cnblogs.com/mxnote/p/16742618.html      https://zhuanlan.zhihu.com/p/612714596   https://blog.csdn.net/weixin_43676978/article/details/118630198
	  // https://blog.csdn.net/qq_38770597/article/details/128061813     https://blog.csdn.net/Create789/article/details/115029189

	//2、初始化python系统文件路径，保证可以访问到 .py文件
	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('D:/AppDocument/Python/Regional_identification20231009/')");
	PyRun_SimpleString("sys.path.append('D:/')");  // 给老婆用的
	//3、调用python文件名。当前的测试python文件名是 myadd.py
    // 在使用这个函数的时候，只需要写文件的名称就可以了。不用写后缀。
	pModule = PyImport_ImportModule("start");     // start.py
	//4、调用函数
	pFunc = PyObject_GetAttrString(pModule, "checkProCity");   // checkProCity   testCPlus
	//5、给python传参数
    // 函数调用的参数传递均是以元组的形式打包的,2表示参数个数
    // 如果AdditionFc中只有一个参数时，写1就可以了
	PyObject* pArgs = PyTuple_New(1);
	// 文件URL作为入参给 Python      C:\Users\Zhangity\Desktop\sjyy0715.docx  沈家雅苑0715
	String sFileURL = fileurl->Text.Trim().c_str(); // 获取填写的文件路径
	string GbkToUtf8(const char* src_str); // 调用方法前声明 .h 文件不用加 private 方法
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", GbkToUtf8(sFileURL.t_str()).c_str()));  // 这里还用c_str()会报错所以用t_str： Cannot convert 'wchar_t *' to 'const char *'
//	PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", "ity"));     //这里修改要和上面 PyTuple_New(1); 联动
	// 6、使用C++的python接口调用该函数
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);  // 这里没有入参就NULL 有就 pArgs

	char *nResult;
	// 7、接收python计算好的返回值 PyArg_Parse的最后一个参数，必须加上“&”符号
//	PyArg_Parse(pReturn, "s", &nResult);
	 // 8、上面是接收一个string返回值，下面是接收一个List 如何处理
	 int i_size = PyList_Size(pReturn);
//	 ShowMessage(i_size);   // 查看返回值有几个，打开这个注释
	wchar_t* pValue;
	Py_ssize_t* len = NULL;
	char* UTF8TOGBK =NULL;
	  int iiisize = 0;

	  string sResult = "";
	  if (i_size == 0) {
          sResult = "未检测到";  // 检测不到下面的set返回的是空
	  }
	 for(int i=0; i<i_size; ++i){
//		 PyArg_Parse(PyList_GetItem(pReturn, i), "s", &nResult);  中文的话会乱码，要用下面的方式
		 pValue = PyUnicode_AsWideCharString(PyList_GetItem(pReturn, i), len);
		 iiisize = WideCharToMultiByte(CP_ACP,0,pValue,-1,NULL,0,NULL,NULL);

		UTF8TOGBK = (char*)malloc(iiisize * sizeof(char));
		WideCharToMultiByte(CP_ACP,0,pValue,-1,UTF8TOGBK,iiisize,NULL,NULL);
		sResult.append(UTF8TOGBK);
		if (i != i_size - 1) {
            sResult.append("、");
		}
	 }

	checkcity->Text =  sResult.c_str();

	// 或者这样调用试试      https://blog.csdn.net/howard789/article/details/125254849
    //  PyObject* pReturn = PyObject_CallObject(pFunc, pArgs);
	//  PyObject* repr = PyObject_Repr(pReturn);
//	PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8","strict");
//	char* result = PyBytes_AsString(str);


	// 资源释放
	Py_Finalize();

	// C++ Builder 使用手册 https://www.doc88.com/p-181696948191.html

}
//---------------------------------------------------------------------------
string GbkToUtf8(const char* src_str)
{
	  int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	  wchar_t* wstr = new wchar_t[len + 1];
	  memset(wstr, 0, len + 1);
	  MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	  len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	  char* str = new char[len + 1];
	  memset(str, 0, len + 1);
	  WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	  string strTemp = str;
	  if (wstr) delete[] wstr;
	  if (str) delete[] str;
	  return strTemp;
}

void __fastcall TForm2::FormCreate(TObject *Sender)
{
	// 这部分代码其实就没用了，是整个窗口允许拖入文件识别，在初始化的时候做即可
	// 参考https://www.cnblogs.com/hanny/p/9028489.html 但是没说特别清楚
    DragAcceptFiles(Handle,true);

}
//---------------------------------------------------------------------------
void __fastcall TForm2::HandleDropFiles(TMessage   &msg)
{
    char FileName[_MAX_PATH];
	int i, Sum;
    //   获得拖拉的文件数目，该功能由第二个参数决定
    Sum = DragQueryFile(HDROP(msg.WParam), 0xFFFFFFFF, NULL, 0);
    if(Sum > 0)
    {
        // 这里只要第一个文件
        DragQueryFile(HDROP(msg.WParam), 0, FileName, _MAX_PATH);
        // 将文件路径显示于窗体上的Text控件
		fileurl->Text = AnsiString(FileName);
	}
    //  释放应用程序为传递文件名而开辟的内存空间
    DragFinish( HDROP(msg.WParam) );
}

