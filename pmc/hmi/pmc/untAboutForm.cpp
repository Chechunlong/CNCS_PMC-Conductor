//---------------------------------------------------------------------
#include "precomp.h"
#pragma hdrstop


//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
    ProductName->Caption = Application->Title;
    Version->Caption = "3.0";
    Copyright->Caption = "Actech (c) 2002-2003";
    Comments->Caption = "爱信特(北京)测控技术有限公司";
}
//--------------------------------------------------------------------- 
