//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UShipBattle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner):TForm(Owner) {
	HE = new HandlersOfEvents(Fild1, Fild2, 10);
}
//---------------------------------------------------------------------------
int Flot::GetStatus() {
	destroy = true;

	if (Form1->RadioGroup1->ItemIndex == 0) {
		code = 10;
	}
	else if (Form1->RadioGroup1->ItemIndex == 1) {
		code = 12;
	}
	else if (Form1->RadioGroup1->ItemIndex == 2) {
		code = 15;
	}

	for (j = 0; j < code; j++)
		for (i = 0; i < ship[j].col_deck; i++)
			if (ship[j].decks[i]) {
				destroy = false;
				return 1;
			}
	return 0;
}
//---------------------------------------------------------------------------
int AI::Generation(Flot *CPU, int col_ship, int col_deck) {
	int x1, y1, k, i, j;
	bool vertical = false, regen;

    if (Form1->RadioGroup1->ItemIndex == 0) {
		code = 10;
	}
	else if (Form1->RadioGroup1->ItemIndex == 1) {
		code = 12;
	}
	else if (Form1->RadioGroup1->ItemIndex == 2) {
		code = 15;
	}

	do {
		randomize();
		x1 = rand()% code;
		y1 = rand()% code;
		regen = false;

		for (k = 0; k < col_deck; k++)
			for (i = 0; i < col_ship; i++)
				for (j = 0; j < CPU -> ship[i].col_deck; j++) {
					if(regen) break;
					if(!vertical) {
						if((CPU->ship[i].desp_of_part[j].x == x1 + k &&
							CPU->ship[i].desp_of_part[j].y == y1) || (x1 + k >= code))
						{
							vertical = true;
							regen = true;
							continue;
						}

						if((CPU->ship[i].desp_of_part[j].x - 1 == x1 + k ||
							CPU->ship[i].desp_of_part[j].x + 1 == x1 + k) &&
						   (CPU->ship[i].desp_of_part[j].y - 1 == y1 ||
							CPU->ship[i].desp_of_part[j].y + 1 == y1))
						{
							vertical = true;
							regen = true;
							continue;
						}
					}

					if(vertical) {
						if((CPU -> ship[i].desp_of_part[j].x == x1 &&
							CPU -> ship[i].desp_of_part[j].y == y1 + k) ||
							(y1 + k >= code))
						{
							vertical = false;
							regen = true;
							continue;
						}

						if((CPU -> ship[i].desp_of_part[j].x - 1 == x1 ||
							CPU -> ship[i].desp_of_part[j].x + 1 == x1) &&
						   (CPU -> ship[i].desp_of_part[j].y - 1 == y1 + k ||
							CPU -> ship[i].desp_of_part[j].y + 1 == y1 + k))
						{
							vertical = true;
							regen = true;
							continue;
						}
					}
				}
	} while(regen);

	if(!vertical)
		for (i = 0; i < col_deck; i++) {
			CPU -> ship[col_ship - 1].desp_of_part[i].x = x1 + i;
			CPU -> ship[col_ship - 1].desp_of_part[i].y = y1;
		}
	else
		for (i = 0; i < col_deck; i++) {
			CPU -> ship[col_ship - 1].desp_of_part[i].x = x1;
			CPU -> ship[col_ship - 1].desp_of_part[i].y = y1 + i;
		}

	return 0;
}
//---------------------------------------------------------------------------
int Referee::GoChecking(int x, int y, int n) {
	if (n == 1)
		if (!Check(net1, x, y))
			return 0;

	if (n == 2)
		if (!Check(net2, x, y))
			return 0;

	return 1;
}
//---------------------------------------------------------------------------
int Referee::Check(bool net[15][15], int x, int y) {
	x /= 20; y /= 20;

	if (!net[x][y])
		return 0;

	return 1;
}
//---------------------------------------------------------------------------
int Referee::GoScaning(int x, int y, int n) {
	if (n == 1)
		if (!Scan(player, x, y))
			return 0;

	if (n == 2)
		if (!Scan(CPU, x, y))
			return 0;
	return 1;
}
//---------------------------------------------------------------------------
int Referee::Scan(Flot *fl, int x, int y) {
	x /= 20; y /= 20;

    if (Form1->RadioGroup1->ItemIndex == 0) {
		code = 10;
	}
	else if (Form1->RadioGroup1->ItemIndex == 1) {
		code = 12;
	}
	else if (Form1->RadioGroup1->ItemIndex == 2) {
		code = 15;
	}

	for (i = 0; i < code; i++)
		for (j = 0; j < fl -> ship[i].col_deck; j++)
			if (fl -> ship[i].desp_of_part[j].x == x &&
				fl -> ship[i].desp_of_part[j].y == y)
			{
				fl -> ship[i].decks[j] = false;
				return 0;
			}

	return 1;
}
//---------------------------------------------------------------------------
int Referee::Miss(int x, int y, int n) {
	x /= 20; y /= 20;

	if (n == 1) net1[x][y] = false;
	if (n == 2) net2[x][y] = false;

	return 1;
}
//---------------------------------------------------------------------------
int Referee::EndRaund(int n) {
	if (n == 2)
		Form1 -> Panel2 -> Caption = "Вы победили!";

	if (n == 1)
		Form1 -> Panel2 -> Caption = "Вы проиграли!";

	game_over = true;
	return 0;
}
//---------------------------------------------------------------------------
int HandlersOfEvents::Play(TImage *Im1, TImage *Im2) {
	Im1 -> Enabled = true;
	Im2 -> Enabled = true;

	return 0;
}
//---------------------------------------------------------------------------
int HandlersOfEvents::Desposition(int x, int y, TMouseButton Button) {
	if(play) return 0;
	x /= 20; y /= 20;

	for (k = 0; k < col_deck; k++)
		for (i = 0; i < col_ship; i++)
			for (j = 0; j < player -> ship[i].col_deck; j++) {
				if (Button == mbLeft) {
					if (player -> ship[i].desp_of_part[j].x == x + k &&
						player -> ship[i].desp_of_part[j].y == y)
					{
						ShowMessage("Невозможно выполнить действие!");
						return 0;
					}

					if(x + k >= code) {
						ShowMessage("Невозможно выполнить действие!");
						return 0;
					}

					if((player -> ship[i].desp_of_part[j].x - 1 == x + k ||
						player -> ship[i].desp_of_part[j].x + 1 == x + k) &&
					   (player -> ship[i].desp_of_part[j].y - 1 == y ||
						player -> ship[i].desp_of_part[j].y + 1 == y))
					{
						ShowMessage("Невозможно выполнить действие!");
						return 0;
					}
				}

				if (Button == mbRight) {
					if (player -> ship[i].desp_of_part[j].x == x &&
						player -> ship[i].desp_of_part[j].y == y + k)
					{
						ShowMessage("Невозможно выполнить действие!");
						return 0;
					}

					if(y + k >= code) {
						ShowMessage("Невозможно выполнить действие!");
						return 0;
					}

					if((player -> ship[i].desp_of_part[j].x - 1 == x ||
						player -> ship[i].desp_of_part[j].x + 1 == x) &&
					   (player -> ship[i].desp_of_part[j].y - 1 == y + k ||
						player -> ship[i].desp_of_part[j].y + 1 == y + k))
					{
						ShowMessage("Невозможно выполнить действие!");
						return 0;
					}
				}
			}

	if (Button == mbLeft)
		Draw ("position_h", x*20, y*20, 1);
	else
		Draw ("position_v", x*20, y*20, 1);

	Generation (CPU, col_ship, col_deck);

	if (Form1->RadioGroup1->ItemIndex == 0) {
		if (col_ship == 1) col_deck--;
		if (col_ship == 3) col_deck--;
		if (col_ship == 6) col_deck--;
		if (col_ship == 10) play = true;
	}
	else if (Form1->RadioGroup1->ItemIndex == 1) {
		if (col_ship == 2) col_deck--;
		if (col_ship == 5) col_deck--;
		if (col_ship == 8) col_deck--;
		if (col_ship == 12) play = true;
	}
	else if (Form1->RadioGroup1->ItemIndex == 2) {
		if (col_ship == 2) col_deck--;
		if (col_ship == 5) col_deck--;
		if (col_ship == 10) col_deck--;
		if (col_ship == 15) play = true;
	}

	if(play) Form1 -> Panel2 -> Caption = "Поехали";

	col_ship++;

	return 0;
};
//---------------------------------------------------------------------------
int HandlersOfEvents::Shoot(int x, int y) {
	if (game_over) return 0;

    if (Form1->RadioGroup1->ItemIndex == 0) {
		code = 10;
	}
	else if (Form1->RadioGroup1->ItemIndex == 1) {
		code = 12;
	}
	else if (Form1->RadioGroup1->ItemIndex == 2) {
		code = 15;
	}

	int shoot_player = ShootPlayer (x, y, 2);


	if (shoot_player > 0)
		do {
			x = rand()% code*20;
			y = rand()% code*20;
			int shoot_cpu = ShootPlayer (x, y, 1);

			if (shoot_cpu > 0)
				break;
			if (shoot_cpu < 0)
				player -> GetStatus();

			if (Form1->RadioGroup1->ItemIndex == 0) {
				if (player -> destroy && target_CPU > 19) {
					EndRaund(1);
					return 0;
				}
			}
			else if (Form1->RadioGroup1->ItemIndex == 1) {
				if (player -> destroy && target_CPU > 26) {
					EndRaund(1);
					return 0;
				}
			}
			else if (Form1->RadioGroup1->ItemIndex == 2) {
				if (player -> destroy && target_CPU > 32) {
					EndRaund(1);
					return 0;
				}
			}


		} while(true);
	else {
		if (shoot_player < 0)
			CPU -> GetStatus();

		if (Form1->RadioGroup1->ItemIndex == 0) {
			if (CPU -> destroy && target_player > 19) {
				EndRaund(2);
				return 0;
			}
		}
		else if (Form1->RadioGroup1->ItemIndex == 1) {
			if (CPU -> destroy && target_player > 26) {
				EndRaund(2);
				return 0;
			}
		}
		else if (Form1->RadioGroup1->ItemIndex == 2) {
			if (CPU -> destroy && target_player > 30) {
				EndRaund(2);
				return 0;
			}
		}
	}

	return 0;
}
//---------------------------------------------------------------------------
int HandlersOfEvents::ShootPlayer(int x, int y, int n) {
	if(!play) return 0;

	if (!GoChecking(x, y, n)) {
		if (n == 2)
			Form1 -> Panel2 -> Caption = "Ещё раз! Туда уже стреляли!";
		return 0;
	}
	else if (!GoScaning(x, y, n)) {
		Draw("target", x, y, n);
		Miss(x, y, n);

		if (n == 2) {
			Form1 -> Panel2 -> Caption = "Попал! Ещё раз!";
			target_player++;
			col_1++;
			col_2++;
			col_3++;
			col_4++;
		}
		else
			target_CPU++;

		if (col_4 == 4 && GoScaning(x + 1, y, 2) && GoScaning(x, y + 1, 2) && GoScaning(x, y - 1, 2) && GoScaning(x - 1, y, 2)) {
			Form1 -> Panel2 -> Caption = "Корабль убит";
			col_4 = 0;
			return -1;
		}
		else if (col_3 == 3) {
			Form1 -> Panel2 -> Caption = "Корабль убит";
			col_3 = 0;
			return -1;
		}
		else if (col_2 == 2) {
			Form1 -> Panel2 -> Caption = "Корабль убит";
			col_2 = 0;
			return -1;
		}
		else if (col_1 == 1) {
			Form1 -> Panel2 -> Caption = "Корабль убит";
			col_1 = 0;
			return -1;
		}

		return -1;
	}

	Miss(x, y, n);
	if (n == 2)
		Form1 -> Panel2 -> Caption = "Мимо! Ход опонента";
	Draw("miss", x, y, n);

	return 1;
}
//---------------------------------------------------------------------------
int HandlersOfEvents::Draw(String key, int x, int y, int n) {
	TImage *Im;
	x /= 20; y /= 20;

	if (n == 1) Im = Form1 -> Fild1;
	if (n == 2) Im = Form1 -> Fild2;

	if (key == "target") {
		Im -> Canvas -> Rectangle(x*20, y*20, x*20 + 20, y*20 + 20);
		Im -> Canvas -> Brush -> Color = clYellow;
		Im -> Canvas -> Rectangle(x*20, y*20 + 20, x*20 + 20, y*20);
		Im -> Canvas -> Brush -> Color = clWhite;
	}

	if (key == "miss") {
		Im -> Canvas -> Ellipse(x*20, y*20, x*20 + 20, y*20 + 20);
		Im -> Canvas -> Ellipse(x*20 + 5, y*20 + 5, x*20 + 15, y*20 + 15);
	}

	if (key == "position_h") {
		for (i = 0; i < col_deck; i++) {
			Im -> Canvas -> Brush -> Color = clBlue;
			Im -> Canvas -> Rectangle(x*20 + i*20, y*20, x*20 + 20 + i*20, y*20 + 20);
			player -> ship[col_ship - 1].desp_of_part[i].x = x + i;
			player -> ship[col_ship - 1].desp_of_part[i].y = y;
			Im -> Canvas -> Brush -> Color = clWhite;
		}
	}

	if (key == "position_v") {
		for (i = 0; i < col_deck; i++) {
			Im -> Canvas -> Brush -> Color = clBlue;
			Im -> Canvas -> Rectangle(x*20, y*20 + i*20, x*20 + 20, y*20 + 20 + i*20);
			player -> ship[col_ship - 1].desp_of_part[i].x = x;
			player -> ship[col_ship - 1].desp_of_part[i].y = y + i;
			Im -> Canvas -> Brush -> Color = clWhite;
		}
	}

	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Fild1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    HE -> Desposition(X, Y, Button);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Fild2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    HE -> Shoot(X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn3Click(TObject *Sender) {
    Panel2 -> Caption = "Расставьте корабли";
	//Fild1 -> Picture -> LoadFromFile("field.bmp");
	//Fild2 -> Picture -> LoadFromFile("field.bmp");

	if (Form1->RadioGroup1->ItemIndex == 0) {
		code = 10;
		HE = new HandlersOfEvents(Fild1, Fild2, code);
		HE -> Play(Fild1, Fild2);
		HE->decks_[20];
	}
	else if (Form1->RadioGroup1->ItemIndex == 1) {
		code = 12;
		HE = new HandlersOfEvents(Fild1, Fild2, code);
		HE -> Play(Fild1, Fild2);
		HE->decks_[24];
	}
	else if (Form1->RadioGroup1->ItemIndex == 2) {
		code = 15;
		HE = new HandlersOfEvents(Fild1, Fild2, code);
		HE -> Play(Fild1, Fild2);
        HE->decks_[30];
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
	if (RadioGroup1->ItemIndex == 0) {
		Form1->ClientHeight = 398;
		Form1->ClientWidth = 492;
		Fild1->Height = 201;
		Fild1->Width = 201;
		Fild2->Height = 201;
		Fild2->Width = 201;
        Fild2->Left = 272;
		BitBtn3->Left = 176;
		BitBtn3->Top = 280;
		Panel2->Left = 56;
        RadioGroup1->Top = 280;
        Fild1 -> Picture -> LoadFromFile("field.bmp");
		Fild2 -> Picture -> LoadFromFile("field.bmp");
	}
	else if (RadioGroup1->ItemIndex == 1) {
		Form1->ClientHeight = 438;
		Form1->ClientWidth = 552;
		Fild1->Height = 241;
		Fild1->Width = 241;
		Fild2->Height = 241;
		Fild2->Width = 241;
		Fild2->Left = 292;
		BitBtn3->Left = 206;
		BitBtn3->Top = 320;
		Panel2->Left = 86;
		RadioGroup1->Top = 320;
		Fild1 -> Picture -> LoadFromFile("field1.bmp");
		Fild2 -> Picture -> LoadFromFile("field1.bmp");
	}
	else if (RadioGroup1->ItemIndex == 2) {
		Form1->ClientHeight = 498;
		Form1->ClientWidth = 652;
		Fild1->Height = 301;
		Fild1->Width = 301;
		Fild2->Height = 301;
		Fild2->Width = 301;
        Fild2->Left = 332;
		BitBtn3->Left = 256;
		BitBtn3->Top = 380;
		Panel2->Left = 136;
		RadioGroup1->Top = 380;
		Fild1 -> Picture -> LoadFromFile("field2.bmp");
		Fild2 -> Picture -> LoadFromFile("field2.bmp");
	}
}
//---------------------------------------------------------------------------

