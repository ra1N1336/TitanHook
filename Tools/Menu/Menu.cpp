#include "../../stdafx.h"
#include "SettingsManager.h"
#include "Menu.h"

int MenuRed;
int MenuGreen;
int MenuBlue;
int MenuAlpha;
int TextRed;
int TextGreen;
int TextBlue;
int TextAlpha;
int BackgroundRed;
int BackgroundGreen;
int BackgroundBlue;
int BackgroundAlpha;
int OutlineRed;
int OutlineGreen;
int OutlineBlue;
int OutlineAlpha;

float GlobalMenuAlpha = 0.f;

/* func buttons here */
void Unhook();

void SaveSettings();

void LoadSettings();

//void ResetSettings();

bool savesettings = false;
bool loadsettings = false;
bool resetsettings = false;

int phase1 = 0;
int phase2 = 30;
int phase3 = 60;
int phase4 = 90;

bool Clicked_This_Frame;
bool Holding_Mouse_1;
bool Dont_Click;
bool Holding_Menu;
int Menu_Drag_X;
int Menu_Drag_Y;
int Tab_Count = 0;

bool keys[256];
bool oldKeys[256];

bool GetKeyPress( unsigned int key )
{
	try
	{
		if( keys[ key ] == true && oldKeys[ key ] == false )
			return true;
		else
			return false;
	}
	catch( ... )
	{
	}
}

std::vector< char* > KeyStrings = { "{ _ }", "{MOUSE1}", "{MOUSE2}", "{BREAK}", "{MOUSE3}", "{MOUSE4}", "{MOUSE5}",
	"{ _ }", "{BCKSPC}", "{TAB}", "{ _ }", "{ _ }", "{ _ }", "{ENTER}", "{ _ }", "{ _ }", "{SHIFT}",
	"{CTRL}", "{ALT}","{PAUSE}","{CAPS}", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ESC}", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{SPACE}","{PGUP}", "{PGDOWN}", "{END}", "{HOME}", "{LEFT}",
	"{UP}", "{RIGHT}", "{DOWN}", "{ _ }", "{PRNT}", "{ _ }", "{PRTSCR}", "{INS}","{DEL}", "{ _ }", "{0}", "{1}",
	"{2}", "{3}", "{4}", "{5}", "{6}", "{7}", "{8}", "{9}", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{A}", "{B}", "{C}", "{D}", "{E}", "{F}", "{G}", "{H}", "{I}", "{J}", "{K}", "{L}", "{M}", "{N}", "{O}", "{P}", "{Q}", "{R}", "{S}", "{T}", "{U}",
	"{V}", "{W}", "{X}","{Y}", "{Z}", "{LFTWIN}", "{RGHTWIN}", "{ _ }", "{ _ }", "{ _ }", "{NUM0}", "{NUM1}",
	"{NUM2}", "{NUM3}", "{NUM4}", "{NUM5}", "{NUM6}","{NUM7}", "{NUM8}", "{NUM9}", "{*}", "{+}", "{_}", "{-}", "{.}", "{/}", "{F1}", "{F2}", "{F3}",
	"{F4}", "{F5}", "{F6}", "{F7}", "{F8}", "{F9}", "{F10}", "{F11}", "{F12}","{F13}", "{F14}", "{F15}", "{F16}", "{F17}", "{F18}", "{F19}", "{F20}", "{F21}",
	"{F22}", "{F23}", "{F24}", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }","{ _ }", "{ _ }", "{ _ }",
	"{NUMLCK}", "{SCRLLLCK}", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }","{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{LSHIFT}", "{RSHIFT}", "{LCTRL}",
	"{RCTRL}", "{LMENU}", "{RMENU}", "{ _ }","{ _ }", "{ _ }","{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }", "{ _ }", "{NTRK}", "{PTRK}", "{STOP}", "{PLAY}", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }", "{ _ }", "{ _ }", ";", "+", ",", "-", ".", "/?", "~", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }","{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }","{ _ }",
	"{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }", "{ _ }","{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }", "{ _ }",
	"{ _ }", "{ _ }" };

void DrawMouse()
{
	POINT Mouse;
	POINT mp;
	GetCursorPos( &mp );
	ScreenToClient( GetForegroundWindow(), &mp );
	Mouse.x = mp.x;
	Mouse.y = mp.y;
	static int Texturer = Interfaces.pSurface->CreateNewTextureID( true );
	unsigned char buffer[4] = { 255, 255, 255, GlobalMenuAlpha };

	Interfaces.pSurface->DrawSetTextureRGBA( Texturer, buffer, 1, 1 );
	Interfaces.pSurface->DrawSetTexture( Texturer );
	Interfaces.pSurface->DrawSetColor( 255, 255, 255, GlobalMenuAlpha );
	/**/
	Vertex_t Verts[3];
	Verts[ 0 ].x = Mouse.x;
	Verts[ 0 ].y = Mouse.y;
	Verts[ 1 ].x = Mouse.x + 27;
	Verts[ 1 ].y = Mouse.y + 13;
	Verts[ 2 ].x = Mouse.x + 13;
	Verts[ 2 ].y = Mouse.y + 27;
	Interfaces.pSurface->DrawTexturedPolygon( 3, Verts );
}

void CMenu::Set_Current_Tab( int tab )
{
	Current_tab = tab;
}

int CMenu::GetCurret_Tab()
{
	return Current_tab;
}

void CMenu::Update_Frame()
{
	if( !Holding_Mouse_1 )
	{
		if( GetClicked() )
		{
			Holding_Menu = true;
		}
		else
		{
			Holding_Menu = false;
		}
	}

	if( Holding_Menu )
	{
		MenuPOS NewPOS;
		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		NewPOS.x = Mouse.x - Menu_Drag_X;
		NewPOS.y = Mouse.y - Menu_Drag_Y;
		this->pos = NewPOS;
	}
}

bool CMenu::GetClicked()
{
	if( !( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) )
	{
		return false;
	}

	POINT Mouse;
	POINT mp;
	GetCursorPos( &mp );
	ScreenToClient( GetForegroundWindow(), &mp );
	Mouse.x = mp.x;
	Mouse.y = mp.y;

	if (Mouse.x > this->pos.x  && Mouse.y > this->pos.y - 6 && Mouse.x < this->pos.x + 525 && Mouse.y < this->pos.y + 30)
	{
		if( !Holding_Mouse_1 )
		{
			Menu_Drag_X = Mouse.x - pos.x;
			Menu_Drag_Y = Mouse.y - pos.y;
		}
		return true;
	}
	else
	{
		return false;
	}
}

CMenu Menu;
class CButton;
class CSlider;
class CDropbox;
class CKeybutton;
class CTab;
class CMenuBox;

class CButton
{
private:
	MenuPOS pos;
	MenuPOS offset;
	int Tab;
	int Sub;

	int Setting;
	char* Name = "ERROR";

	bool Hovering()
	{
		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y - 2 && Mouse.x < this->pos.x + 12 && Mouse.y < this->pos.y - 2 + 12 )
		{
			return true;
		}
		return false;
	}

	bool Clicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}

		if( Hovering() )
		{
			return true;
		}
		return false;
	}

public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if( Menu.GetCurret_Tab() == Tab )
		{
			if( Clicked() )
			{
				Dont_Click = true;
				Settings.SetSetting( Tab, Setting, !Settings.GetMenuSetting( Tab, Setting ) );
			}
		}
	}

	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab )
		{
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawOutlinedRect( this->pos.x, this->pos.y - 2, this->pos.x + 12, this->pos.y - 2 + 12 );
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y - 2 + 1, this->pos.x + 11, this->pos.y - 2 + 11 );

			if( Settings.GetMenuSetting( this->Tab, this->Setting ) )
			{
				Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f));
				Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y -2 + 1, this->pos.x + 11, this->pos.y - 2 + 11 );
			}
			//Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
			//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);
			Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 3, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, this->Name);
		}
	}

	void Init( int Tab, int Setting, bool defult, int x, int y, char* name, int sub )
	{
		this->Tab = Tab;
		this->Setting = Setting;
		this->offset.y = y;
		this->offset.x = x;
		this->Name = name;
		this->Sub = sub;

		Settings.SetSetting( Tab, Setting, defult );
	}
};

class CSlider
{
private:
	int Tab = 0;
	int SubTab = 0;
	int Setting = 0;
	double Max = 100;
	double Min = 0;
	bool color_from_some_set = false;
	int cus_r, cus_g, cus_b, cus_a;
	bool custom_color = true;
	int r = 55, g = 5, b = 5, a = 255, r_back = 5, g_back = 55, b_back = 5, a_back = 255;
	MenuPOS pos;
	MenuPOS offset;
	char* Name = "ERROR";
	//char* SValue = "0";
	bool Is_Holding;

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			this->Is_Holding = false;
			return false;
		}
		if( Holding_Mouse_1 )
		{
			if( !this->Is_Holding )
			{
				return false;
			}
		}
		if( Dont_Click )
			return false;

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 13 )
		{
			this->Is_Holding = true;
			return true;
		}
		else if( this->Is_Holding )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab )
		{
			double Ratio = Settings.GetMenuSetting( this->Tab, this->Setting ) / ( this->Max - this->Min );
			double Location = Ratio * 125;
			if (GlobalMenuAlpha == 0)
			{
				Interfaces.pSurface->DrawSetColor(0, 0, 0, 0);
			}
			else if (custom_color)
			{
				Interfaces.pSurface->DrawSetColor(r_back, g_back, b_back, a_back * (GlobalMenuAlpha / 255));
			}
			else
			{
				Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_sliders_back_r), Settings.GetSetting(Tab_Colors, Colors_sliders_back_g), Settings.GetSetting(Tab_Colors, Colors_sliders_back_b), Settings.GetSetting(Tab_Colors, Colors_sliders_back_a) * (GlobalMenuAlpha / 255));
			}
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y + 6, this->pos.x + 124, this->pos.y + 12 );
			if (GlobalMenuAlpha == 0)
			{
				Interfaces.pSurface->DrawSetColor(0, 0, 0, 0);
			}
			else if (color_from_some_set)
			{
				Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, cus_r), Settings.GetSetting(Tab_Colors, cus_g), Settings.GetSetting(Tab_Colors, cus_b), Settings.GetSetting(Tab_Colors, cus_a) * (GlobalMenuAlpha / 255));
			}
			else if (custom_color)
			{
				Interfaces.pSurface->DrawSetColor(r, g, b, a * (GlobalMenuAlpha / 255));
			}
			else
			{
				Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_sliders_r), Settings.GetSetting(Tab_Colors, Colors_sliders_g), Settings.GetSetting(Tab_Colors, Colors_sliders_b), Settings.GetSetting(Tab_Colors, Colors_sliders_a) * (GlobalMenuAlpha / 255));
			}
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y + 6, this->pos.x + Location, this->pos.y + 12 );
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawOutlinedRect( this->pos.x, this->pos.y + 5, this->pos.x + 125, this->pos.y + 13 );
			Interfaces.pSurface->DrawT( this->pos.x, this->pos.y - 10, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, "%s", this->Name, ( float )Settings.GetMenuSetting( this->Tab, this->Setting ) );
			float Value1 = ( float )Settings.GetMenuSetting( this->Tab, this->Setting );
			char vl[128];
			sprintf( vl, "%.f", Value1 );
			Interfaces.pSurface->DrawT( this->pos.x + 130, this->pos.y + 3.5, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, vl );
		}
	}

	void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub, int R = 55, int G = 5, int B = 5, int A = 255, int RB = 5, int GB = 55, int BB = 5, int AB = 255, int color_set_r = -1, int color_set_g = -1, int color_set_b = -1, int color_set_a = -1)
	{
		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Max = max;
		Min = min;
		Name = name;
		SubTab = sub;
		if (color_set_r != -1 && color_set_g != -1 && color_set_b != -1 && color_set_a != -1)
		{
			color_from_some_set = true;
			custom_color = false;
			Settings.SetSetting(Tab, Setting, defult);
			cus_r = color_set_r;
			cus_g = color_set_g;
			cus_b = color_set_b;
			cus_a = color_set_a;
			return;
		}
		if (R == -1 || G == -1 || B == -1 || A == -1 || RB == -1 || GB == -1 || BB == -1 || AB == -1)
		{
			custom_color = false;
			Settings.SetSetting(Tab, Setting, defult);
			return;
		}
		r = R;
		g = G;
		b = B;
		a = A;
		r_back = RB;
		g_back = GB;
		b_back = BB;
		a_back = AB;
		Settings.SetSetting( Tab, Setting, defult );
	}

	void Update()
	{
		this->pos.x = Menu.pos.x + offset.x;
		this->pos.y = Menu.pos.y + offset.y;

		// get clicked and changing value
		if( Menu.GetCurret_Tab() == Tab )
		{
			if( this->GetClicked() )
			{
				Dont_Click = true;
				POINT Mouse;
				POINT mp;
				GetCursorPos( &mp );
				ScreenToClient( GetForegroundWindow(), &mp );
				Mouse.x = mp.x;
				Mouse.y = mp.y;
				// get differance
				double idifference;
				idifference = Mouse.x - this->pos.x;
				// Set Value
				double value = ( ( idifference / 125 ) * ( this->Max - this->Min ) );
				if( value < Min )
				{
					value = Min;
				}
				else if( value > Max )
				{
					value = Max;
				}

				Settings.SetSetting( Tab, Setting, value );
			}
		}
	}
};

class CDropBox
{
private:
	int Tab = 0;
	int Setting = 0;

	char* Name = "ERROR";
	char* Parts[256];
	int Amount = 0;

	bool Dropping = false;

	MenuPOS pos;
	MenuPOS offset;
	int Sub = 0;

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}
		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 16 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int GetPartClicked()
	{
		if( !Clicked_This_Frame )
		{
			return -1;
		}
		if( Holding_Mouse_1 )
		{
			return -1;
		}
		if( Dont_Click )
		{
			return -1;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		for( int i = 1; i < this->Amount; i++ )
		{
			if( Mouse.x > this->pos.x && Mouse.y > this->pos.y + ( 16 * ( i ) ) && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + ( 16 * ( i + 1 ) ) )
			{
				return i;
			}
		}
		return -1;
	}

public:
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if( Tab == Menu.GetCurret_Tab() )
		{
			if( this->GetClicked() )
			{
				if( this->Dropping == true )
				{
					this->Dropping = false;
				}
				else
				{
					this->Dropping = true;
				}
				Dont_Click = true;
			}
			else if( this->Dropping )
			{
				int index = this->GetPartClicked();
				if( index != -1 )
				{
					Settings.SetSetting( this->Tab, this->Setting, index );
					this->Dropping = false;
					Dont_Click = true;
				}
				else if( Clicked_This_Frame && !Holding_Mouse_1 )
				{
					Dropping = false;
				}
			}
			else
			{
				Dropping = false;
			}
		}
		else
		{
			Dropping = false;
		}
	}

	void Draw()
	{
		if( Tab == Menu.GetCurret_Tab() )
		{
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y + 1, this->pos.x + 124, this->pos.y + 15 );
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawOutlinedRect( this->pos.x, this->pos.y, this->pos.x + 125, this->pos.y + 16 );
			Interfaces.pSurface->DrawT( this->pos.x + 1, this->pos.y - 15, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, this->Name );

			if( this->Dropping )
			{
				for( int i = 1; i < this->Amount; i++ )
				{
					Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f)); //dark top color
					Interfaces.pSurface->DrawFilledRect( this->pos.x, this->pos.y + ( 16 * i ), this->pos.x + 125, this->pos.y + ( 16 * i ) + 16 );
					Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
					Interfaces.pSurface->DrawOutlinedRect( pos.x, pos.y + (16 * i) - 1, pos.x + 125, pos.y + ( 16 * i ) + 17 );
					Interfaces.pSurface->DrawT( this->pos.x + 11, this->pos.y + ( 16 * i ), CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, this->Parts[ i ] );
					//part 2
					int value = ( int )Settings.GetMenuSetting( Tab, Setting );
					if( value >= this->Amount )
						value = 0;
					//Interfaces.pSurface->DrawT(pos.x + 11, pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, Parts[value]);

					static int Texture = Interfaces.pSurface->CreateNewTextureID( true ); //need to make a texture with procedural true
					unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha/2 };//{ color.r(), color.g(), color.b(), color.a() };

					Interfaces.pSurface->DrawSetTextureRGBA( Texture, buffer, 1, 1 ); //Texture, char array of texture, width, height
					Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f) ); // keep this full color and opacity use the RGBA @top to set values.
					Interfaces.pSurface->DrawSetTexture( Texture ); // bind texture

					Vertex_t Verts2[3];
					Verts2[ 0 ].x = pos.x + 103;
					Verts2[ 0 ].y = pos.y + 11;
					Verts2[ 1 ].x = pos.x + 107.5;
					Verts2[ 1 ].y = pos.y + 6;
					Verts2[ 2 ].x = pos.x + 112;
					Verts2[ 2 ].y = pos.y + 11;

					Interfaces.pSurface->DrawTexturedPolygon( 3, Verts2 );
				}
				int value = ( int )Settings.GetMenuSetting( Tab, Setting );
				if( value >= this->Amount )
					value = 0;
				Interfaces.pSurface->DrawT( this->pos.x + 11, this->pos.y, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, this->Parts[ value ] );
			}
			else
			{
				int value = ( int )Settings.GetMenuSetting( Tab, Setting );
				if( value >= this->Amount )
					value = 0;
				Interfaces.pSurface->DrawT( this->pos.x + 11, this->pos.y, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, this->Parts[ value ] );

				static int Texture = Interfaces.pSurface->CreateNewTextureID( true ); //need to make a texture with procedural true
				unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };

				Interfaces.pSurface->DrawSetTextureRGBA( Texture, buffer, 1, 1 ); //Texture, char array of texture, width, height
				Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)); // keep this full color and opacity use the RGBA @top to set values.
				Interfaces.pSurface->DrawSetTexture( Texture ); // bind texture

				Vertex_t Verts2[3];
				Verts2[ 0 ].x = pos.x + 103;
				Verts2[ 0 ].y = pos.y + 6;
				Verts2[ 1 ].x = pos.x + 112;
				Verts2[ 1 ].y = pos.y + 6;
				Verts2[ 2 ].x = pos.x + 107.5;
				Verts2[ 2 ].y = pos.y + 11;

				Interfaces.pSurface->DrawTexturedPolygon( 3, Verts2 );
			}
		}
	}

	void Init( int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int sub )
	{
		Name = name;
		Amount = parts;

		for( int i = 0; i < parts; i++ )
		{
			Parts[ i ] = arr[ i ];
		}

		Tab = tab;
		Setting = setting;
		offset.x = x;
		offset.y = y;
		Sub = sub;
	}
};

class CKeyButton
{
private:
	MenuPOS pos;
	MenuPOS offset;

	int Tab;
	int Setting;
	bool Getting_New_Key;
	char* Name = "ERROR";
	int Sub = 0;

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 25 && Mouse.y < this->pos.y + 20 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab )
		{
			//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, "%s", this->Name);
			//Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
			//Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 80, this->pos.y + 20);
			//Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
			//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 80, this->pos.y + 20);
			if( this->Getting_New_Key )
			{
				Interfaces.pSurface->DrawT( this->pos.x, this->pos.y, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, "{ _ }" );
			}
			else
			{
				if( Settings.GetMenuSetting( this->Tab, this->Setting ) == -1 )
					Interfaces.pSurface->DrawT( this->pos.x, this->pos.y, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, "{ _ }" );
				else
				{
					char* NameOfKey = KeyStrings[ ( int )Settings.GetMenuSetting( this->Tab, this->Setting ) ];
					Interfaces.pSurface->DrawT( this->pos.x, this->pos.y, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, NameOfKey );
				}
			}
		}
	}

	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if( Menu.GetCurret_Tab() == Tab )
		{
			if( Getting_New_Key )
			{
				for( int i = 0; i < 255; i++ )
				{
					if( GetKeyPress( i ) )
					{
						if( i == VK_DELETE )
						{
							this->Getting_New_Key = false;
							Settings.SetSetting( Tab, Setting, -1 );
							break;
						}
						if( i == VK_ESCAPE )
						{
							Settings.SetSetting( Tab, Setting, -1 );
							this->Getting_New_Key = false;
							break;
						}
						Settings.SetSetting( Tab, Setting, i );
						this->Getting_New_Key = false;
						break;
					}
				}
			}
			else if( this->GetClicked() )
			{
				this->Getting_New_Key = !this->Getting_New_Key;
			}
		}
	}

	void Init( int x, int y, int tab, int setting, char* name, int sub )
	{
		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Name = name;
		Sub = sub;
		Settings.SetSetting( Tab, Setting, -1 );
	}
};

class CTab
{
public:
	void Update()
	{
		pos.x = Menu.pos.x + 0;
		pos.y = Menu.pos.y + 30 + ( ( 200 / Tab_Count ) * Tab );

		if( GetClicked() )
		{
			Dont_Click = true;
			Menu.Set_Current_Tab( Tab );
		}
	}

	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab )
		{
			//Interfaces.pSurface->DrawSetColor( 75, 75, 75, GlobalMenuAlpha );
			//Interfaces.pSurface->DrawFilledRect( pos.x - 1, pos.y - 2, pos.x + 109, pos.y + 12 + ( 160 / Tab_Count ) );
			//Interfaces.pSurface->DrawSetColor( 5, 5, 5, GlobalMenuAlpha );
			//Interfaces.pSurface->DrawFilledRect( pos.x, pos.y - 1, pos.x + 110, pos.y + 11 + ( 160 / Tab_Count ) );
			Interfaces.pSurface->DrawSetColor( 25, 25, 25, GlobalMenuAlpha );
			//Interfaces.pSurface->DrawFilledRect( pos.x, pos.y, pos.x + 111, pos.y + 10 + ( 160 / Tab_Count ) );
			Interfaces.pSurface->DrawT( pos.x + 20, pos.y + ( 160 / Tab_Count / 2 ) - 3, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Tab, false, Name );
			Interfaces.pSurface->DrawT( pos.x + 30, pos.y + ( 160 / Tab_Count / 2 ) - 5, CColor( 255, 255, 255, ( GlobalMenuAlpha / 255.f ) * 240.f ), Hacks.Font_Icons, false, Icon );
		}
		else
		{
			Interfaces.pSurface->DrawT( pos.x + 10, pos.y + ( 160 / Tab_Count / 2 ) - 3, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Tab, false, Name );
			Interfaces.pSurface->DrawT( pos.x + 10, pos.y + ( 160 / Tab_Count / 2 ) - 5, CColor( 255, 255, 255, ( GlobalMenuAlpha / 255.f ) * 110.f ), Hacks.Font_Icons, false, Icon );
		}
	}

	void Init( char* name, int tab, char* icon )
	{
		Name = name;
		Tab = tab;
		Icon = icon;
	}

private:
	int Tab;
	MenuPOS pos;
	char* Name = "ERROR";
	char* Icon = "ERROR";

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > pos.x && Mouse.y > pos.y && Mouse.x < pos.x + 90 && Mouse.y < pos.y + ( ( 200 / Tab_Count ) ) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class CMenuBox
{
public:
	void Init( char* name, int x, int y, int w, int h, int tab, int sub )
	{
		Name = name;
		offset.x = x;
		offset.y = y;
		size.x = w;
		size.y = h;
		Tab = tab;
		SubTab = sub;
	}

	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;
	}

	void Draw()
	{
		if( Tab == Menu.GetCurret_Tab() )
		{
			int Width = 0, Height = 0;
			char Buffer[256] = { '\0' };
			va_list Args;
			va_start(Args, Name);
			vsprintf_s( Buffer, Name, Args );
			va_end(Args);
			size_t Size = strlen( Buffer );
			/* set up size.xidebuffer*/
			wchar_t* wBuffer = new wchar_t[Size];
			/* char -> size.xchar */
			mbstowcs_s( nullptr, wBuffer, Size, Buffer, Size - 1 );
			/* check center */
			Interfaces.pSurface->GetTextSize( Hacks.Font_Controls, wBuffer, Width, Height );
			Interfaces.pSurface->DrawSetColor(40, 5, 5, GlobalMenuAlpha / 2);
			Interfaces.pSurface->DrawLine( pos.x, pos.y, pos.x, pos.y + size.y );
			Interfaces.pSurface->DrawLine( pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y );
			Interfaces.pSurface->DrawLine( pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y );
			Interfaces.pSurface->DrawLine(pos.x, pos.y, (pos.x * 2 + size.x) / 2 - Width / 2 - 6, pos.y);
			Interfaces.pSurface->DrawLine((pos.x * 2 + size.x) / 2 + Width / 2 + 6, pos.y, pos.x + size.x, pos.y );
			Interfaces.pSurface->DrawSetColor(40, 5, 5, GlobalMenuAlpha / 2);
			Interfaces.pSurface->DrawLine( pos.x + 1, pos.y + 1, pos.x + 1, pos.y + size.y - 1 );
			Interfaces.pSurface->DrawLine( pos.x + 1, pos.y + size.y - 1, pos.x + size.x - 1, pos.y + size.y - 1 );
			Interfaces.pSurface->DrawLine( pos.x + size.x - 1, pos.y + 1, pos.x + size.x - 1, pos.y + size.y - 1 );
			Interfaces.pSurface->DrawLine( pos.x + 1, pos.y + 1, (pos.x * 2 + size.x) / 2 - Width / 2 - 6, pos.y + 1 );
			Interfaces.pSurface->DrawLine((pos.x * 2 + size.x) / 2 + Width / 2 + 6, pos.y + 1, pos.x + size.x - 1, pos.y + 1);
			Interfaces.pSurface->DrawT((pos.x + pos.x + size.x) / 2, pos.y - 6, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, true, Name);
		}
	}

private:
	MenuPOS pos;
	MenuPOS offset;
	MenuPOS size;
	char* Name = "ERROR";
	int Tab;
	char* Icon = "ERROR";
	int SubTab = 0;
};

class CFunctionButton
{
public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if( Menu.GetCurret_Tab() == Tab )
		{
			if( this->GetClicked() )
			{
				DWORD disfunc = Function;
				__asm
				{
					CALL disfunc
				}
			}
		}
	}

	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab )
		{
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawOutlinedRect( this->pos.x + 1, this->pos.y + 1, this->pos.x + 124, this->pos.y + 15 );
			Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f));
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 2, this->pos.y + 2, this->pos.x + 123, this->pos.y + 14 );
			Interfaces.pSurface->DrawT( this->pos.x + 62.5, this->pos.y, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, true, Name );
		}
	}

	void Init( int x, int y, DWORD function, char* name, int tab )
	{
		Function = function;
		Name = name;
		offset.x = x;
		offset.y = y;
		Tab = tab;
	}

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 16)
		{
			return true;
		}

		return false;
	}

private:
	DWORD Function;
	char* Name = "NO NAME";
	MenuPOS pos;
	MenuPOS offset;
	int Tab = -1;
};

std::vector< CSlider > Sliders;
std::vector< CButton > Buttons;
std::vector< CDropBox > Dropboxes;
std::vector< CKeyButton > KeyButtons;
std::vector< CMenuBox > MenuBoxs;
std::vector< CTab > Tabs;

std::vector< CFunctionButton > FuncButtons;

int Dropboxs_Amount = 0;

void AddNewButton( int Tab, int Setting, bool defult, int x, int y, char* name )
{
	CButton Filler;
	Filler.Init( Tab, Setting, defult, x, y, name, -1 );
	Buttons.push_back( Filler );
}

void AddNewSlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int r = -1, int g = -1, int b = -1, int a = -1, int rb = -1, int gb = -1, int bb = -1, int ab = -1, int cus_r = -1, int cus_g = -1, int cus_b = -1, int cus_a = -1)
{
	CSlider Slid;
	Slid.Init(x, y, min, max, defult, name, tab, setting, -1, r, g, b, a, rb, gb, bb, ab, cus_r, cus_g, cus_b, cus_a);
	Sliders.push_back( Slid );
}

void AddNewDropbox( int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr )
{
	CDropBox Dropper;
	Dropper.Init( x, y, tab, setting, name, parts, arr, -1 );
	Dropboxes.push_back( Dropper );//
	Dropboxs_Amount++;
}

void AddNewKeyButton( int x, int y, int tab, int setting, char* name )
{
	CKeyButton KeyButton;
	KeyButton.Init( x, y, tab, setting, name, -1 );
	KeyButtons.push_back( KeyButton );
}

void AddNewTab( char* Name, int Tab, char* Icon )
{
	CTab Filler;
	Filler.Init( Name, Tab, Icon );
	Tabs.push_back( Filler );
	Tab_Count++;
}

void AddNewMenuBox( char* name, int x, int y, int w, int h, int tab )
{
	CMenuBox Filler;
	Filler.Init( name, x, y, w, h, tab, -1 );
	MenuBoxs.push_back( Filler );
}

void AddNewFuncButton( int x, int y, DWORD function, char* name, int tab )
{
	CFunctionButton Filler;
	Filler.Init( x, y, function, name, tab );
	FuncButtons.push_back( Filler );
}

extern player_info_t* Info;
std::vector< char* > ingameNames{ "NONE", "DEAGLE", "DUALBERETTAS", "FIVESEVEN", "GLOCK", "AK47", "AUG", "AWP", "FAMAS", "G3SG1",
	"GALILAR", "M249", "M4A4", "MAC10", "P90", "UMP45", "XM1014", "PPBIZON", "MAG7", "NEGEV", "SAWEDOFF", "TEC9",
	"P2000", "MP7", "MP9", "NOVA", "P250", "SCAR20", "SG553", "SSG08", "CTKnife", "TKnife", "M4A1S", "USPS", "CZ75AUTO", "R8Revolver" };
int page[256];
int selected[256];
int realselected[256];

void drawselectbox( int amount, char* arr[100], int width, int height, int setting, int realvals[100] )
{
	int startx = Menu.pos.x + width + 3;
	int starty = Menu.pos.y + height + 3;
	Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
	Interfaces.pSurface->DrawOutlinedRect( startx - 2, starty - 2, startx + 137, starty + 202 );

	for( int i = 0; i < 10; i++ )
	{
		int number = i + 10 * page[ setting ];
		if( number > amount )
		{
		}
		else
		{
			Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
			Interfaces.pSurface->DrawFilledRect( startx, starty + i * 16, startx + 120, starty + i * 16 + 16 );
			Interfaces.pSurface->DrawSetColor( 30, 30, 30, GlobalMenuAlpha );
			Interfaces.pSurface->DrawFilledRect( startx + 1, starty + i * 16 + 1, startx + 119, starty + i * 16 + 15 );
			if( number == selected[ setting ] )
			{
				Interfaces.pSurface->DrawT( startx + 3, starty + i * 16 + 3, CColor( 20, 200, 255, GlobalMenuAlpha ), Hacks.Font_Controls, false, arr[ number ] );
				realselected[ setting ] = realvals[ number ];
			}
			else
				Interfaces.pSurface->DrawT( startx + 3, starty + i * 16 + 3, CColor( 255, 255, 255, GlobalMenuAlpha ), Hacks.Font_Controls, false, arr[ number ] );
		}
	}
	double drawbarheight = ( 10 * 160 );
	drawbarheight /= amount;
	if( drawbarheight > 200 )
		drawbarheight = 200;
	Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
	Interfaces.pSurface->DrawOutlinedRect( startx + 125, starty, startx + 135, starty + 200 );
	Interfaces.pSurface->DrawFilledRect( startx + 127, starty + page[ setting ] * drawbarheight, startx + 133, starty + drawbarheight + page[ setting ] * drawbarheight );
	// scroll
	if( Clicked_This_Frame )
	{
		if( !Holding_Mouse_1 )
		{
			if( !Dont_Click )
			{
				POINT Mouse;
				POINT mp;
				GetCursorPos( &mp );
				ScreenToClient( GetForegroundWindow(), &mp );
				Mouse.x = mp.x;
				Mouse.y = mp.y;
				if( Mouse.x > startx + 125 && Mouse.y > starty && Mouse.x < startx + 135 && Mouse.y < starty + 200 )
				{
					int percentage = ( Mouse.y - starty );
					for( int i = 0; i < 10; i++ )
					{
						if( drawbarheight * i < percentage && percentage < drawbarheight * ( i + 1 ) )
						{
							page[ setting ] = i;
						}
					}
				}
			}
		}
	}
	// getting clicked
	if( Clicked_This_Frame )
	{
		if( !Holding_Mouse_1 )
		{
			if( !Dont_Click )
			{
				POINT Mouse;
				POINT mp;
				GetCursorPos( &mp );
				ScreenToClient( GetForegroundWindow(), &mp );
				Mouse.x = mp.x;
				Mouse.y = mp.y;
				if( Mouse.x > startx && Mouse.y > starty && Mouse.x < startx + 120 && Mouse.y < starty + 200 )
				{
					int percentage = ( Mouse.y - starty );
					for( int i = 0; i < 10; i++ )
					{
						if( 20 * i < percentage && percentage < 20 * ( i + 1 ) )
						{
							int number = i + 10 * page[ setting ];
							selected[ setting ] = number;
						}
					}
				}
			}
		}
	}
}

void skinchanger()
{
}

void SetupMenu()
{
	char* arr[512] = { "ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR", };

	//Tabs
	AddNewTab( "LEGIT", Tab_Legitbot, "" );
	//AddNewTab( "RAGE", Tab_Ragebot, "" );
	AddNewTab( "VISUAL", Tab_Visuals, "" );
	AddNewTab("SKINS", Tab_Skinchanger, "");
	AddNewTab("COLORS", Tab_Colors, "");
	AddNewTab( "MISC", Tab_Misc, "" );
	AddNewTab( "CFG", Tab_Config, "" );

	//AddNewMenuBox("Aimbot", 100, 50, 220, 300, Tab_Legitbot);
	{
		//Dropbox Config
		std::vector< char* > Hitbox = { "Head", "Head", "Chest", "Stomach"};
		std::vector< char* > FovType = { "Static", "Static"};
		std::vector< char* > SmoothType = { "Static", "Static" };

		//Controls
		AddNewButton(Tab_Legitbot, Legitbot_enable, false, 120, 50, "Aimbot Enabled");
		AddNewButton(Tab_Legitbot, Legitbot_Aimonkey, false, 120, 70, "Aimbot On Key");
		AddNewKeyButton(120, 85, Tab_Legitbot, Legitbot_Aimbotkey, "");
		AddNewButton(Tab_Legitbot, Legitbot_multihitbox, false, 120, 105, "Nearest");
		AddNewDropbox(120, 135, Tab_Legitbot, Legitbot_hitbox, "Hitbox", 4, Hitbox);
		//AddNewDropbox(235, 140, Tab_Legitbot, Legitbot_fovtype, "Fov Type", 2, FovType);
		AddNewSlider(120, 165, 0, 40, 0, "Fov", Tab_Legitbot, Legitbot_fov);
		//AddNewDropbox(235, 200, Tab_Legitbot, Legitbot_smoothtype, "Smooth Type", 2, SmoothType);
		AddNewSlider(120, 185, 0, 100, 0, "Speed X", Tab_Legitbot, Legitbot_smoothY);
		AddNewSlider(120, 205, 0, 100, 0, "Speed Y", Tab_Legitbot, Legitbot_smoothX);
		//AddNewButton(Tab_Legitbot, Legitbot_rcs, false, 215, 270, "Rcs");
		AddNewSlider(120, 225, 0, 100, 0, "Rcs force X", Tab_Legitbot, Legitbot_rcsforceX);
		AddNewSlider(120, 245, 0, 100, 0, "Rcs force Y", Tab_Legitbot, Legitbot_rcsforceY);
		AddNewSlider(120, 265, 0, 150, 0, "Fire delay", Tab_Legitbot, Legitbot_Firedelay);
	}

	/* Ragebot */

	/*AddNewMenuBox( "Aimbot", 195, 20, 235, 455, Tab_Ragebot );
	{
		//Dropbox Config
		std::vector< char* > Selection = { "Distance", "Distance","Cycle" };
		std::vector< char* > Hitbox = { "Head", "Head", "Neck", "Chest", "Pelvis" };
		std::vector< char* > MultipointType = { "Compression", "Compression", "Max", };
		std::vector< char * > MultiBox = { "Off", "Off", "Vitals", "Max" };

		//Controls
		AddNewButton( Tab_Ragebot, Ragebot_AimbotEnabled, false, 215, 40, "Enabled" );
		AddNewDropbox( 235, 70, Tab_Ragebot, Ragebot_Selection, "Target Selection", 3, Selection );
		AddNewDropbox( 235, 110, Tab_Ragebot, Ragebot_Hitbox, "Hitbox", 5, Hitbox );
		AddNewButton( Tab_Ragebot, Ragebot_Multipoint, false, 215, 140, "Multi-point" );
		AddNewDropbox( 235, 155, Tab_Ragebot, Ragebot_MultipointType, "", 3, MultipointType );
		AddNewSlider( 235, 175, 0, 100, 50, "", Tab_Ragebot, Ragebot_PS );
		AddNewDropbox( 235, 205, Tab_Ragebot, Ragebot_Multibox, "MultiBox", 4, MultiBox );
		AddNewButton( Tab_Ragebot, Ragebot_Velocity, false, 215, 235, "Velocity Multibox" );
		AddNewButton( Tab_Ragebot, Ragebot_AutoShoot, false, 215, 255, "Auto Shoot" );
		AddNewButton( Tab_Ragebot, Ragebot_Autoscope, false, 215, 275, "Auto Scope" );
		AddNewButton( Tab_Ragebot, Ragebot_SilentAim, false, 215, 295, "Silent aim" );
		AddNewSlider( 235, 325, 0, 100, 0, "Hit Chance", Tab_Ragebot, Ragebot_Hitchance );
		AddNewSlider( 235, 355, 0, 120, 0, "Minimum Damage", Tab_Ragebot, Ragebot_MinDamage );
		AddNewButton( Tab_Ragebot, Ragebot_AcceptKill, false, 215, 380, "Accept Kill Damage" );
		AddNewButton( Tab_Ragebot, Ragebot_GOTV, false, 215, 400, "GOTV" );
	}

	AddNewMenuBox( "AntiAim", 450, 260, 235, 215, Tab_Ragebot );
	{
		//Dropbox Config
		std::vector< char* > Antiaim_Pitch = { "Off", "Off","Emotion", "Down", "Minimal", };
		std::vector< char* > Antiaim_Yaw = { "Off", "Off", "Sideways Distortion", "180", "Crooked Distortion", "Spin", "180 Distortion", "test" };
		std::vector< char* > AtTargets = { "Off", "Off", "Nospread", "Normal" };

		//Controls
		AddNewButton( Tab_Ragebot, AntiAim_Enabled, false, 470, 280, "Enable" );
		AddNewDropbox( 490, 310, Tab_Ragebot, AntiAim_Pitch, "Pitch", 5, Antiaim_Pitch );
		AddNewDropbox( 490, 350, Tab_Ragebot, AntiAim_Yaw, "Yaw", 8, Antiaim_Yaw );
		AddNewDropbox( 490, 390, Tab_Ragebot, AntiAim_AtTargets, "At Targets", 4, AtTargets );
		AddNewButton( Tab_Ragebot, AntiAim_FakeHitbox, false, 470, 420, "Fake Hitbox" );
		AddNewButton( Tab_Ragebot, AntiAim_EdgeDetection, false, 470, 440, "Edge Detection" );
	}

	AddNewMenuBox( "Other", 450, 20, 235, 220, Tab_Ragebot );
	{
		//Dropbox Config
		//std::vector<char*> Accuracy = { "Off", "Off", "FPS Save", "Medium", "Maximum" };
		std::vector< char* > PreferBodyAim = { "Never", "Never", "Adaptive", "Max" };

		//Controls
		AddNewButton( Tab_Ragebot, Ragebot_Resolver, false, 470, 40, "Anti Aim Correction" );
		//AddNewDropbox(490, 70, Tab_Ragebot, Ragebot_Accuracy, "Accuracy Boost", 5, Accuracy);
		AddNewDropbox( 490, 70, Tab_Ragebot, Ragebot_PreferBodyAim, "Prefer Body-Aim", 4, PreferBodyAim );
		AddNewButton( Tab_Ragebot, Ragebot_PositionAdjustment, false, 470, 100, "Position Adjustment" );
	}*/

	/* MISC */
	{
		//AddNewMenuBox( "Miscellaneous", 195, 20, 235, 455, Tab_Misc );
		{
			//Dropbox Config
			std::vector< char* > AutoStraferMode = { "Silent", "Silent", "Normal", "Sideways", "W Only" };
			//std::vector<char*> ClanMode = { "Woghook", "Woghook", "Undefeated", "Chefware", "keegan_priv", "ANIME.CHEAT" };
			std::vector< char* > ClanTag = { "TITAN HOOK", "TITAN HOOK", "TITAN HOOK FREE", "NAGIBATOR228"};
			std::vector< char* > Fakelag = { "Off", "Off", "Maximum", "Adaptive", "Switch", "Step", "Random" };

			//Controls
			AddNewButton( Tab_Misc, Misc_AutoJump, true, 120, 50, "Bunny hop" );
			//AddNewButton( Tab_Misc, Misc_AutoStrafe, false, 215, 80, "Auto Strafe" );
			//AddNewDropbox( 235, 95, Tab_Misc, Misc_AutoStraferMode, "", 5, AutoStraferMode );
			//AddNewDropbox( 235, 135, Tab_Misc, Misc_FakeLag, "Fake Lag", 6, Fakelag );
			//AddNewButton( Tab_Misc, Misc_ZStrafe, false, 215, 165, "Z Strafe" );
			//AddNewKeyButton( 390, 165, Tab_Misc, Misc_ZStrafeKey, "" );
			//AddNewButton( Tab_Misc, Misc_CircleStrafe, false, 215, 185, "Circle Strafe" );
			//AddNewKeyButton( 390, 185, Tab_Misc, Misc_CircleStrafeKey, "" );
			AddNewButton( Tab_Misc, Misc_AutoAccept, false, 120, 70, "Auto Accept" );
			//AddNewButton( Tab_Misc, Misc_Aimstep, false, 215, 225, "Aimstep" );
			AddNewButton( Tab_Misc, Misc_ClanTagSpammer, false, 120, 90, "Clantag Changer" );
			AddNewDropbox( 120, 110, Tab_Misc, Misc_ClanTagSelection, "", 4, ClanTag );
			//AddNewButton( Tab_Misc, Misc_ClanTagAnimate, false, 120, 180, "Animated Clantag" );
			AddNewButton(Tab_Misc, Misc_KnifeBot, false, 120, 135, "Knifebot");
			//AddNewButton(Tab_Misc, Misc_UI, false, 215, 330, "Custom UI");
		}
		//AddNewMenuBox( "Settings", 450, 20, 235, 160, Tab_Misc );
		{
			//Controls
			//AddNewButton( Tab_Misc, Misc_AntiUntrusted, true, 470, 70, "Anti Untrusted" );
		}
		//AddNewMenuBox( "Weapon Config", 450, 200, 235, 275, Tab_Misc );
		{
			//Dropbox Config
			std::vector< char* > wgroup = { "Current", "Rifle","Pistol", "Shotgun", "SMG", "Heavy",  "Awp", "Scout", "Other Snipers", "Current" };

			//Controls
			//AddNewDropbox( 120, 140, Tab_Config, Misc_WhichWeapon, "Weapon Group", 10, wgroup );
		}
	}



	{//Colors

		AddNewSlider(120, 50, 0, 255, 0, "Sliders", Tab_Colors, Colors_sliders_r);
		AddNewSlider(120, 65, 0, 255, 255, "", Tab_Colors, Colors_sliders_g);
		AddNewSlider(120, 80, 0, 255, 0, "", Tab_Colors, Colors_sliders_b);
		AddNewSlider(120, 95, 0, 255, 255, "", Tab_Colors, Colors_sliders_a);

		AddNewSlider(120, 120, 0, 255, 0, "Sliders Background", Tab_Colors, Colors_sliders_back_r);
		AddNewSlider(120, 135, 0, 255, 0, "", Tab_Colors, Colors_sliders_back_g);
		AddNewSlider(120, 150, 0, 255, 0, "", Tab_Colors, Colors_sliders_back_b);
		AddNewSlider(120, 165, 0, 255, 255, "", Tab_Colors, Colors_sliders_back_a);

		AddNewSlider(120, 190, 0, 255, 0, "Chams Visible", Tab_Colors, Colors_chams_visible_r, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_visible_r, Colors_chams_visible_g, Colors_chams_visible_b, Colors_chams_visible_a);
		AddNewSlider(120, 205, 0, 255, 255, "", Tab_Colors, Colors_chams_visible_g, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_visible_r, Colors_chams_visible_g, Colors_chams_visible_b, Colors_chams_visible_a);
		AddNewSlider(120, 220, 0, 255, 0, "", Tab_Colors, Colors_chams_visible_b, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_visible_r, Colors_chams_visible_g, Colors_chams_visible_b, Colors_chams_visible_a);
		AddNewSlider(120, 235, 0, 255, 255, "", Tab_Colors, Colors_chams_visible_a, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_visible_r, Colors_chams_visible_g, Colors_chams_visible_b, Colors_chams_visible_a);

		AddNewSlider(120, 260, 0, 255, 0, "Chams Invisible", Tab_Colors, Colors_chams_invisible_r, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_invisible_r, Colors_chams_invisible_g, Colors_chams_invisible_b, Colors_chams_invisible_a);
		AddNewSlider(120, 275, 0, 255, 0, "", Tab_Colors, Colors_chams_invisible_g, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_invisible_r, Colors_chams_invisible_g, Colors_chams_invisible_b, Colors_chams_invisible_a);
		AddNewSlider(120, 290, 0, 255, 0, "", Tab_Colors, Colors_chams_invisible_b, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_invisible_r, Colors_chams_invisible_g, Colors_chams_invisible_b, Colors_chams_invisible_a);
		AddNewSlider(120, 305, 0, 255, 255, "", Tab_Colors, Colors_chams_invisible_a, -1, -1, -1, -1, -1, -1, -1, -1, Colors_chams_invisible_r, Colors_chams_invisible_g, Colors_chams_invisible_b, Colors_chams_invisible_a);

		AddNewSlider(300, 50, 0, 255, 0, "Menu Background", Tab_Colors, Colors_background_r);
		AddNewSlider(300, 65, 0, 255, 0, "", Tab_Colors, Colors_background_g);
		AddNewSlider(300, 80, 0, 255, 0, "", Tab_Colors, Colors_background_b);
		AddNewSlider(300, 95, 0, 255, 255, "", Tab_Colors, Colors_background_a);

		AddNewSlider(300, 120, 0, 255, 0, "Outlines", Tab_Colors, Colors_outline_r);
		AddNewSlider(300, 135, 0, 255, 255, "", Tab_Colors, Colors_outline_g);
		AddNewSlider(300, 150, 0, 255, 0, "", Tab_Colors, Colors_outline_b);
		AddNewSlider(300, 165, 0, 255, 255, "", Tab_Colors, Colors_outline_a);

		AddNewSlider(300, 190, 0, 255, 0, "Text", Tab_Colors, Colors_controls_text_r);
		AddNewSlider(300, 205, 0, 255, 255, "", Tab_Colors, Colors_controls_text_g);
		AddNewSlider(300, 220, 0, 255, 0, "", Tab_Colors, Colors_controls_text_b);
		AddNewSlider(300, 235, 0, 255, 255, "", Tab_Colors, Colors_controls_text_a);

		AddNewSlider(300, 260, 0, 255, 0, "Controls Background", Tab_Colors, Colors_controls_background_r);
		AddNewSlider(300, 275, 0, 255, 0, "", Tab_Colors, Colors_controls_background_g);
		AddNewSlider(300, 290, 0, 255, 0, "", Tab_Colors, Colors_controls_background_b);
		AddNewSlider(300, 305, 0, 255, 255, "", Tab_Colors, Colors_controls_background_a);


	}

	/* Visual */
	//AddNewMenuBox( "Player ESP", 195, 20, 235, 285, Tab_Visuals );
	{
		//Dropbox Config
		//std::vector<char*> VisBox = { "Frame" ,"Frame", "Alt" };

		//Controls
		AddNewButton( Tab_Visuals, Visuals_BoxEnabled, false, 120, 50, "Box" );
		AddNewButton(Tab_Visuals, Visuals_XQZ, false, 120, 70, "Only Visible");
		AddNewButton( Tab_Visuals, Visuals_EspTeam, false, 120, 90, "Show Team" );
		AddNewButton( Tab_Visuals, Visuals_HealthBar, false, 120, 110, "Show Health Bar" );
		//AddNewButton( Tab_Visuals, Visuals_ArmorBar, false, 120, 130, "Show Armor" );
		AddNewButton( Tab_Visuals, Visuals_Name, false, 120, 130, "Show Name" );
		//AddNewButton( Tab_Visuals, Visuals_Weapons, false, 215, 160, "Weapons" );
		//AddNewButton( Tab_Visuals, Visuals_Flashed, false, 215, 180, "Flashed" );
		//AddNewButton( Tab_Visuals, Visuals_AimLines, false, 215, 200, "Aim Lines" );
		AddNewButton( Tab_Visuals, Visuals_Skeltal, false, 120, 150, "Bone Esp" );
		//AddNewButton( Tab_Visuals, Visuals_Hostage, false, 215, 240, "Hostage" );
		//AddNewButton( Tab_Visuals, Visuals_Flags, false, 215, 260, "Flags" );
	}
	//AddNewMenuBox( "Chams", 195, 325, 235, 150, Tab_Visuals );
	{
		//Controls
		AddNewButton( Tab_Visuals, Visuals_Chams, false, 250, 50, "Chams" );
		AddNewButton(Tab_Visuals, Visuals_ChamsTeam, false, 250, 70, "Show Team");
		AddNewButton( Tab_Visuals, Visuals_ChamsXQZ, false, 250, 90, "XQZ" );
		//AddNewButton( Tab_Visuals, Visuals_ChamsGuns, false, 215, 390, "Dropped Weapons" );
		
	}

	//AddNewMenuBox( "Other ESP", 450, 20, 235, 180, Tab_Visuals );
	{
		//Controls
		//AddNewButton( Tab_Visuals, Visuals_DroppedWeapons, false, 470, 40, "Dropped Weapons" );
		//AddNewButton( Tab_Visuals, Visuals_Crosshair, false, 470, 60, "Crosshair" );
		//AddNewButton( Tab_Visuals, Visuals_CrosshairDynamic, false, 470, 80, "Crosshair Dynamic" );
		AddNewButton( Tab_Visuals, Visuals_C4, false, 250, 170, "Show Bomb" );
		AddNewButton( Tab_Visuals, Visuals_EngineRadar, false, 250, 190, "Ingame Radar" );
	}

	//AddNewMenuBox( "Effects", 450, 220, 235, 255, Tab_Visuals );
	{
		//Controls
		AddNewButton(Tab_Visuals, Visuals_NoFlash, false, 250, 210, "No Flash");
		AddNewButton(Tab_Visuals, Visuals_NoSmoke, false, 250, 230, "No Smoke");
		AddNewButton( Tab_Visuals, Visuals_NoRecoil, false, 250, 250, "No Visual Recoil" );
		AddNewSlider(250, 280, 0, 80, 0, "Fov", Tab_Visuals, Visuals_fov);

		//AddNewButton( Tab_Visuals, Visuals_ThirdPerson, false, 470, 300, "Force ThirdPerson" );
		//AddNewButton( Tab_Visuals, Visuals_NoScope, false, 470, 320, "Remove Scope" );
	}

	/* Config */

	//Dropbox Config
	std::vector< char* > ConfigType = { "Legit1", "Legit1","Legit2", "Legit3", "Rage casual", "Custom1", "Custom2", "Custom3" };

	//Controls
	AddNewDropbox(120, 50, Tab_Config, Config_type, "", 8, ConfigType);
	AddNewFuncButton( 120, 70, ( DWORD )LoadSettings, "Load", Tab_Config );
	AddNewFuncButton( 120, 90, ( DWORD )SaveSettings, "Save", Tab_Config );
	//AddNewFuncButton(195, 185, (DWORD)ResetSettings, "Reset", Tab_Config);
	AddNewFuncButton( 370, 300, ( DWORD )Unhook, "Unload DLL", Tab_Config );
}

void DrawMenu()
{
	unsigned int Build = Interfaces.pEngine->GetEngineBuildNumber();
	static bool firsttime = true;
	Dont_Click = false;

	/* UPDATE KEYS */
	std::copy( keys, keys + 255, oldKeys );
	for( int x = 0; x < 255; x++ )
	{
		keys[ x ] = ( GetAsyncKeyState( x ) );
	}

	static int Clock = 0;
	if( GlobalMenuAlpha == 0 || GlobalMenuAlpha == 255 )
		if( GetKeyPress( VK_DELETE ) )
		{
			Clock = 0;
			Menu.Opened = !Menu.Opened;
			std::string msg = "cl_mouseenable " + std::to_string( !Menu.Opened );
			Interfaces.pEngine->ClientCmd_Unrestricted( msg.c_str(), 0 );
		}

	double timeSoFar1 = ( double )Clock / 30.f;
	Clock++;

	if( Menu.Opened )
	{
		if( GlobalMenuAlpha != 255 )
			if( GlobalMenuAlpha > 255 )
				GlobalMenuAlpha = 255;
			else
				GlobalMenuAlpha = timeSoFar1 * 255.f;
	}
	else if( GlobalMenuAlpha != 0 )
	{
		if( GlobalMenuAlpha < 0 )
			GlobalMenuAlpha = 0;
		else
			GlobalMenuAlpha = 255 - ( timeSoFar1 * 255.f );
	}

	if( firsttime )
	{
		if(  Build == 13583 )
		{
			SetupMenu();
			firsttime = false;
		}
		else
		{
			Unhook();
		}
	}

	if( !( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) )
	{
		Holding_Mouse_1 = false;
	}
	if( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 )
	{
		Clicked_This_Frame = true;
	}
	else
	{
		Clicked_This_Frame = false;
	}

	Menu.Update_Frame();

	//Drawing the menu base
	//Interfaces.pSurface->DrawSetColor( 5, 5, 5, GlobalMenuAlpha );
	//Interfaces.pSurface->DrawFilledRect( Menu.pos.x - 2, Menu.pos.y - 2, Menu.pos.x + 707, Menu.pos.y + 497 );
	Interfaces.pSurface->DrawSetColor( Settings.GetSetting(Tab_Colors,Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
	Interfaces.pSurface->DrawOutlinedRect(Menu.pos.x - 3, Menu.pos.y - 3, Menu.pos.x + 528, Menu.pos.y + 353);
	Interfaces.pSurface->DrawOutlinedRect(Menu.pos.x - 2, Menu.pos.y - 2, Menu.pos.x + 527, Menu.pos.y + 352);
	Interfaces.pSurface->DrawOutlinedRect( Menu.pos.x - 1, Menu.pos.y - 1, Menu.pos.x + 526, Menu.pos.y + 351 );
	Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_background_r), Settings.GetSetting(Tab_Colors, Colors_background_g), Settings.GetSetting(Tab_Colors, Colors_background_b), Settings.GetSetting(Tab_Colors, Colors_background_a) * (GlobalMenuAlpha / 255.f));
	Interfaces.pSurface->DrawFilledRect( Menu.pos.x, Menu.pos.y, Menu.pos.x + 525, Menu.pos.y + 350 );
	//Interfaces.pSurface->DrawSetColor(0, 40, 0, GlobalMenuAlpha / 2);
	//Interfaces.pSurface->DrawFilledRect( Menu.pos.x + 176, Menu.pos.y, Menu.pos.x + 705, Menu.pos.y + 495 );
	Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
	//Interfaces.pSurface->DrawLine( Menu.pos.x + 174, Menu.pos.y+40, Menu.pos.x + 174, Menu.pos.y + 495 );
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x+90, Menu.pos.y+30, Menu.pos.x + 92, Menu.pos.y + 350);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x , Menu.pos.y + 30, Menu.pos.x + 525, Menu.pos.y + 32);
	//Interfaces.pSurface->DrawLine( Menu.pos.x + 10, Menu.pos.y + 140, Menu.pos.x + 165, Menu.pos.y + 140 );
	Interfaces.pSurface->DrawSetColor( 5, 5, 5, GlobalMenuAlpha );
	//Interfaces.pSurface->DrawLine( Menu.pos.x + 10, Menu.pos.y + 141, Menu.pos.x + 165, Menu.pos.y + 141 );
	//Interfaces.pSurface->DrawString( Hacks.Font_Logo, Menu.pos.x + 47.5, Menu.pos.y + 32.5, 0, CColor( 12, 23, 25, GlobalMenuAlpha ), L"\u7121\u6557" );
	//Interfaces.pSurface->DrawString( Hacks.Font_Logo, Menu.pos.x + 47.5, Menu.pos.y + 37.5, 0, CColor( 0, 200, 255, GlobalMenuAlpha ), L"\u7121\u6557" );
	Interfaces.pSurface->DrawT(Menu.pos.x + 260, Menu.pos.y + 8, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_MenuTitle, true, "T I T A N    H O O K");

	for( CTab& Tab : Tabs )
		Tab.Draw();

	for( CMenuBox& MenuBox : MenuBoxs )
		MenuBox.Draw();

	for( CFunctionButton& FuncButton : FuncButtons )
		FuncButton.Draw();

	for( CKeyButton& KeyButton : KeyButtons )
		KeyButton.Draw();

	for( CSlider& slider : Sliders )
		slider.Draw();

	for( CButton& Button : Buttons )
		Button.Draw();

	std::reverse( Dropboxes.begin(), Dropboxes.end() );

	for( CDropBox& Dropbox : Dropboxes )
		Dropbox.Draw();

	std::reverse( Dropboxes.begin(), Dropboxes.end() );

	if( Menu.Opened )
	{
		DrawMouse();
		for( CTab& Tab : Tabs )
			Tab.Update();

		for( CMenuBox& MenuBox : MenuBoxs )
			MenuBox.Update();

		for( CDropBox& Dropbox : Dropboxes )
			Dropbox.Update();

		for( CSlider& slider : Sliders )
			slider.Update();

		for( CButton& Button : Buttons )
			Button.Update();

		for( CKeyButton& KeyButton : KeyButtons )
			KeyButton.Update();

		for( CFunctionButton& FuncButton : FuncButtons )
			FuncButton.Update();
	}
	if( Clicked_This_Frame )
	{
		Holding_Mouse_1 = true;
	}
}
