//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------
USEFORM("UShipBattle.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	try {
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
	}
	catch(Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}

	return 0;
}