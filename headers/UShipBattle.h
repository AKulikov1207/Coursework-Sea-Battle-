//---------------------------------------------------------------------------

#ifndef UShipBattleH
#define UShipBattleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
struct Ship {
	bool destroy;
	int col_deck;
	bool *decks;
	TPoint *desp_of_part;
};

int code;

class Flot {
public:
	Flot(TImage *I, int code) {
		destroy = false;
		Im = I;
		n = 1;

		for (i = 0; i < code; i++) {
			if (code == 10) {
				if (i < 6) n = 2;
				if (i < 3) n = 3;
				if (i == 0) n = 4;
			}
			else if (code == 12) {
				if (i < 8) n = 2;
				if (i < 5) n = 3;
				if (i == 0) n = 4;
			}
            else if (code == 15) {
				if (i < 10) n = 2;
				if (i < 5) n = 3;
				if (i == 0) n = 4;
			}
			ship[i].destroy = false;
			ship[i].col_deck = n;
			ship[i].decks = new bool[n];
			ship[i].desp_of_part = new TPoint[n];
		}
	}

	int GetStatus();

	int i, j, n;
	bool destroy;
	TImage *Im;
	Ship ship[15];
};

class AI {
public:
	TPoint decks_[30];
	int col_decks_;
	int Generation(Flot *CPU, int col_ship, int col_deck);
};

class Referee: public AI {
public:
	int i, j, target_player, target_CPU, col_1, col_2, col_3, col_4;
	bool net1[15][15], net2[15][15], game_over;
	Flot *player, *CPU;

	Referee() {
		for (i = 0; i < code; i++)
			for (j = 0; j < code; j++) {
				net1[i][j] = true;
				net2[i][j] = true;
			}

		game_over = false;
		target_player = 0;
		target_CPU = 0;
		col_decks_ = 0;
	}

	int GoChecking(int x, int y, int n);
	int Check(bool net[15][15], int x, int y);
	int GoScaning(int x, int y, int n);
	int Scan(Flot *fl, int x, int y);
	int Miss(int x, int y, int n);
	int EndRaund(int n);
};

class HandlersOfEvents: public Referee {
public:
	bool play;
	int col_deck, col_ship, i, j, k;

	HandlersOfEvents(TImage *Im1, TImage *Im2, int code) {
		play = false;
		col_deck = 4;
		col_ship = 1;
		player = new Flot(Im1, code);
		CPU = new Flot(Im2, code);
	}

	int Play(TImage *Im1, TImage *Im2);
	int Move();
	int Desposition(int x, int y, TMouseButton Button);
	int Draw(String key, int x, int y, int n);
	int ShootPlayer(int x, int y, int n);
	int Shoot(int x, int y);
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Fild1;
	TImage *Fild2;
	TPanel *Panel2;
	TBitBtn *BitBtn3;
	TRadioGroup *RadioGroup1;
	void __fastcall Fild1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Fild2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    HandlersOfEvents *HE;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
