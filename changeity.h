//---------------------------------------------------------------------------

#ifndef changeityH
#define changeityH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *cc;
	TButton *×ª»»;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *successTime;
	TButton *clear;
	TButton *help;
	TLabeledEdit *Column1;
	TLabeledEdit *Column2;
	TCheckBox *CheckBackColor;
	TButton *Button1;
	TRichEdit *checkcity;
	TRichEdit *fileurl;
	void __fastcall ×ª»»Click(TObject *Sender);
	void __fastcall clearClick(TObject *Sender);
	void __fastcall ccChange(TObject *Sender);
	void __fastcall helpClick(TObject *Sender);
	void __fastcall Column1Change(TObject *Sender);
	void __fastcall Column2Change(TObject *Sender);
	void __fastcall checkProCity(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall HandleDropFiles(TMessage &Owner);
private:	// User declarations
//	String GbkToUtf8(const char* src_str);
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_DROPFILES,TMessage,HandleDropFiles)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
