#include "CDrawManager.h"
//===================================================================================
CDrawManager gDraw;

#define ESP_HEIGHT 14
//===================================================================================
void CDrawManager::Initialize( )
{
	if ( gInts.Surface == NULL )
		return;

	gInts.Engine->GetScreenSize( gScreenSize.iScreenWidth, gScreenSize.iScreenHeight );
	g_DefaultFont = gInts.Surface->CreateFont( );	//This is better than Arial
	gInts.Surface->SetFontGlyphSet( g_DefaultFont, "Tahoma", ESP_HEIGHT, 500, 0, 0, 0x200 );
}
//===================================================================================
Color CDrawManager::GetPlayerColor(CBaseEntity* pPlayer)
{
	if (pPlayer->GetIndex() == gCvars.iAimbotIndex)
		return Color::Green();
	else if (!gCvars.PlayerMode[pPlayer->GetIndex()])
		return Color(0, 255, 255, 255);
	else if (gCvars.PlayerMode[pPlayer->GetIndex()] == 2)
		return Color::Yellow();
	else
	{

		switch (pPlayer->GetTeamNum())
		{
		case 2: //RED
			return Color(255, 20, 20, 255);
		case 3: //BLU
			return Color(0, 153, 255, 255);
		default:
			return Color(0, 0, 0, 0);
		}
	}

	return Color(0, 0, 0, 0); //no reason for this to be here, i just wanna look smart
}
//===================================================================================
void CDrawManager::DrawString( int x, int y, Color clrColor, const wchar_t *pszText, HFont font, bool CenterX, bool CenterY)
{
	if( pszText == NULL )
		return;

	if (CenterX || CenterY)
	{
		int wide, tall;
		gInts.Surface->GetTextSize(font, pszText, wide, tall);
		if (CenterX)
			x -= wide / 2;
		if (CenterY)
			y -= tall / 2;
	}

	gInts.Surface->DrawSetTextPos( x, y );
	gInts.Surface->DrawSetTextFont( font );
	gInts.Surface->DrawSetTextColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawPrintText( pszText, wcslen( pszText ) );
}
//===================================================================================
void CDrawManager::DrawString( int x, int y, Color clrColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf_s( szBuffer, pszText, va_alist );
	va_end( va_alist );

	wsprintfW( szString, L"%S", szBuffer );

	gInts.Surface->DrawSetTextPos( x, y );
	gInts.Surface->DrawSetTextFont( g_DefaultFont );
	gInts.Surface->DrawSetTextColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawPrintText( szString, wcslen( szString ) );
}
//===================================================================================
byte CDrawManager::GetESPHeight( )
{
	return ESP_HEIGHT;
}
//===================================================================================
void CDrawManager::DrawLine(int x, int y, int x1, int y1, Color clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawLine(x, y, x1, y1);
}
//===================================================================================
void CDrawManager::DrawLineEx(int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawLine(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::DrawRect( int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawFilledRect( x, y, x + w, y + h );
}
//===================================================================================
void CDrawManager::OutlineRect( int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawOutlinedRect( x, y, x + w, y + h );
}
//===================================================================================
void CDrawManager::DrawBox( Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius )
{
	Vector vScreen;

	if( !WorldToScreen( vOrigin, vScreen ) )
		return;

	int radius2 = radius<<1;

	OutlineRect( vScreen.x - radius + box_width, vScreen.y - radius + box_width, radius2 - box_width, radius2 - box_width, Color::Black() );
	OutlineRect( vScreen.x - radius - 1, vScreen.y - radius - 1, radius2 + ( box_width + 2 ), radius2 + ( box_width + 2 ), Color::Black() );
	DrawRect( vScreen.x - radius + box_width, vScreen.y - radius, radius2 - box_width, box_width, Color( r, g, b, alpha ));
	DrawRect( vScreen.x - radius, vScreen.y + radius, radius2, box_width, Color( r, g, b, alpha ));
	DrawRect( vScreen.x - radius, vScreen.y - radius, box_width, radius2, Color( r, g, b, alpha ));
	DrawRect( vScreen.x + radius, vScreen.y - radius, box_width, radius2 + box_width, Color( r, g, b, alpha ) );
}
//===================================================================================
bool CDrawManager::WorldToScreen( Vector &vOrigin, Vector &vScreen )
{
	const matrix3x4& worldToScreen = gInts.Engine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	vScreen.z = 0; //Screen doesn't have a 3rd dimension.

	if( w > 0.001 ) //If the object is within view.
	{
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		vScreen.x = (gScreenSize.iScreenWidth / 2) + ( 0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * gScreenSize.iScreenWidth + 0.5); //Get the X dimension and push it in to the Vector.
		vScreen.y = (gScreenSize.iScreenHeight / 2) - ( 0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * gScreenSize.iScreenHeight + 0.5); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

void CDrawManager::DrawCrosshair(int iValue)
{
	int m_iScreenWidth = gScreenSize.iScreenWidth;
	int     m_iScreenHeight = gScreenSize.iScreenHeight;

	int x = m_iScreenWidth / 2;
	int y = m_iScreenHeight / 2;
	switch (iValue)
	{
	case 1:
		DrawRect(x - 14, y, 9, 1, Color(255, 255, 255, 255));
		DrawRect(x + 5, y, 9, 1, Color(255, 255, 255, 255));
		DrawRect(x, y - 14, 1, 9, Color(255, 255, 255, 255));
		DrawRect(x, y + 5, 1, 9, Color(255, 255, 255, 255));
		DrawRect(x, y, 1, 1, Color(255, 255, 255, 255));
	break;
	}

}















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class guhjzni {
public:
	string lfssrybwjklptmy;
	double midotucomg;
	guhjzni();
	void kuluuwayfp(double mqtqapwyybxpey, double bgechgvcsss, bool hvestciqcjjsdq);
	int debnvhtmdegk(int cvnghhu);
	int xbdogzdtxtxdufuspny(bool hmxrlgqvminz, double hkelsvomxudihzu, int uagdce, string hhxzhmi, double euvptryyrflfb, string bhejhs, bool hykeca, string spyjhqk, double csgimgavqhqrkjc);
	double zkjzhrvgtlcwhhzrc(double wimmwtpzap, int qhpnqmwxua, double mghlkpomoaawxi);
	int lyqqbancgxsstz(bool dmfrorel, string qrqcos, int bydtzohlbjoxd, double hiixnrpuivjx, string hywdydpeshkpv, int uligopbgefftn, double hfbtqjxbjbug);
	void bczaogluradyfltdivlordsw(string utatqktmsw);
	double opsomanouqqgqsbddlonzuzk(double kacvopmuztptcz, string wxywqd, string iyvmci, bool fdfgzkew);
	double eupvvcmjtsjscsmwntchglz(string whjcnwzheixyvcl, bool xicgphkpav, bool hhjrvhep);

protected:
	string igwtqqajjjof;
	int tmobckukm;
	string nqskukwuhaaae;
	double lwhytfcn;
	string qjweipwtdobbo;

	bool mqchbhebexctoafj(bool tvevonttdbqgf, string zisnhpqezepgisv, bool djjiyk, double xerohoekhqi, bool nhxpqfo, string mulrkpmgog);
	int fckphcmtsmrhvwkl(string ydvif, double lutdvant, double axlpcjh);
	int lzsotpitfalzfzzjtwaco(bool pkqxspqvfwzfz, double gcgiybvzp, string bdzskbsxi);

private:
	bool obzjjwfdv;
	string njwrwdrwgzppxwj;
	string cwztlrhob;

	void vuitfycqtwdbzjeabsk(int zwybwoujnx, double nvoszfjiijsqkp, string uzqqefiqu, string zaofcrp, string rzadxgvhsgdlqs);
	void hiavqfoaqekvqdbhdmvdyvwt(string iagspqcgy, bool hiquhytkjw, double sbhis, bool nmwppaqvygip, bool ptjqcehkbm, string ztdnfkbdx, int reevuyigxb, double iflga, double oiatmjkcxawvop);
	void kibbczywfjlgnjehvcax(double nvtesezpxw, double pkxbf, double dobbbwkadriwkt, bool vuiythsdp);
	bool ozfmgpxqziu(int csivsatlow);
	string kwgehezokxhll(bool fxmystzruq, bool hybdsmmem, int wlxlktbivr, int dlfdjyrlfgqg, string wrgbqknriekpqxw, string nxeuf);
	double jcvcpkkubjjbjaexnnnprx();

};


void guhjzni::vuitfycqtwdbzjeabsk(int zwybwoujnx, double nvoszfjiijsqkp, string uzqqefiqu, string zaofcrp, string rzadxgvhsgdlqs) {
	int yflibaauwhxdcwd = 3718;
	int japruqeato = 4485;
	double dhodvfxtvo = 10951;
	if (3718 != 3718) {
		int yukghv;
		for (yukghv = 22; yukghv > 0; yukghv--) {
			continue;
		}
	}
	if (4485 == 4485) {
		int lu;
		for (lu = 51; lu > 0; lu--) {
			continue;
		}
	}
	if (4485 == 4485) {
		int lqsgicset;
		for (lqsgicset = 53; lqsgicset > 0; lqsgicset--) {
			continue;
		}
	}
	if (4485 != 4485) {
		int ldbkxiqfa;
		for (ldbkxiqfa = 92; ldbkxiqfa > 0; ldbkxiqfa--) {
			continue;
		}
	}
	if (10951 != 10951) {
		int vqxwxmpib;
		for (vqxwxmpib = 5; vqxwxmpib > 0; vqxwxmpib--) {
			continue;
		}
	}

}

void guhjzni::hiavqfoaqekvqdbhdmvdyvwt(string iagspqcgy, bool hiquhytkjw, double sbhis, bool nmwppaqvygip, bool ptjqcehkbm, string ztdnfkbdx, int reevuyigxb, double iflga, double oiatmjkcxawvop) {
	int tynizfgsfrxcq = 2154;
	string qgnsapa = "ilbfybpthxzhztjdok";
	if (string("ilbfybpthxzhztjdok") == string("ilbfybpthxzhztjdok")) {
		int jiis;
		for (jiis = 100; jiis > 0; jiis--) {
			continue;
		}
	}
	if (2154 == 2154) {
		int gbwg;
		for (gbwg = 0; gbwg > 0; gbwg--) {
			continue;
		}
	}
	if (2154 == 2154) {
		int nzcy;
		for (nzcy = 21; nzcy > 0; nzcy--) {
			continue;
		}
	}

}

void guhjzni::kibbczywfjlgnjehvcax(double nvtesezpxw, double pkxbf, double dobbbwkadriwkt, bool vuiythsdp) {
	double lzntcc = 50295;
	double iiiwwlf = 24023;
	string nxuyteaz = "alrcjgoqrqytvrqcjdgllnubxktjmuoxpqswcxaycbguinepaeiaidmyrkfjvozppzphebljvpiuxmigmwvmuctxtcq";
	if (24023 != 24023) {
		int uow;
		for (uow = 5; uow > 0; uow--) {
			continue;
		}
	}

}

bool guhjzni::ozfmgpxqziu(int csivsatlow) {
	return true;
}

string guhjzni::kwgehezokxhll(bool fxmystzruq, bool hybdsmmem, int wlxlktbivr, int dlfdjyrlfgqg, string wrgbqknriekpqxw, string nxeuf) {
	bool rmghp = true;
	double reacjd = 24464;
	int diyytvyzzwhcm = 758;
	bool zbemcchbsvkhp = true;
	int axfyuxe = 2109;
	if (2109 == 2109) {
		int jzbqdbb;
		for (jzbqdbb = 61; jzbqdbb > 0; jzbqdbb--) {
			continue;
		}
	}
	if (2109 != 2109) {
		int jolzaa;
		for (jolzaa = 35; jolzaa > 0; jolzaa--) {
			continue;
		}
	}
	return string("xjbual");
}

double guhjzni::jcvcpkkubjjbjaexnnnprx() {
	bool favnknqwcopbc = false;
	bool cdvvidwusdadeb = false;
	int dabnz = 4264;
	int gmvkf = 4630;
	bool zcpddhpoiqwesk = false;
	int vynhk = 801;
	string dbkgevhpalalxrd = "mtxaahghsbfzuucsbqnpfymweacczygrtehveezsbjiuxlleajdkevqjuowpxdqwoeuqbddamhjzzoyknz";
	if (string("mtxaahghsbfzuucsbqnpfymweacczygrtehveezsbjiuxlleajdkevqjuowpxdqwoeuqbddamhjzzoyknz") != string("mtxaahghsbfzuucsbqnpfymweacczygrtehveezsbjiuxlleajdkevqjuowpxdqwoeuqbddamhjzzoyknz")) {
		int mqhtxpvs;
		for (mqhtxpvs = 69; mqhtxpvs > 0; mqhtxpvs--) {
			continue;
		}
	}
	if (false != false) {
		int mtdxe;
		for (mtdxe = 5; mtdxe > 0; mtdxe--) {
			continue;
		}
	}
	if (801 != 801) {
		int eoh;
		for (eoh = 87; eoh > 0; eoh--) {
			continue;
		}
	}
	return 87298;
}

bool guhjzni::mqchbhebexctoafj(bool tvevonttdbqgf, string zisnhpqezepgisv, bool djjiyk, double xerohoekhqi, bool nhxpqfo, string mulrkpmgog) {
	double fahdpxac = 10283;
	double qpyeqk = 43331;
	string yjstjhg = "xoojvigxaftxjxczemqgesegrhuhehqgaljzeekojpiapumevpnzjcmpemhsjvfumpevuvkqc";
	int ynnflefkeeco = 5902;
	bool mjsvuycgtq = false;
	string teeoac = "aaeeobycsotafjwmnwxispqqjbwrrmcjiuvbkejyodunmuwzuwyqpuxchtu";
	double cnlkvsurgc = 33461;
	string zksnxvutfuxzez = "dzrnhyiackadipecnn";
	int eivkzockao = 3638;
	string meuugclgpy = "anvinlzfazngynrqjyhtsnystedgutj";
	if (string("dzrnhyiackadipecnn") == string("dzrnhyiackadipecnn")) {
		int dsemiltf;
		for (dsemiltf = 70; dsemiltf > 0; dsemiltf--) {
			continue;
		}
	}
	if (43331 != 43331) {
		int nhd;
		for (nhd = 11; nhd > 0; nhd--) {
			continue;
		}
	}
	if (10283 != 10283) {
		int nb;
		for (nb = 29; nb > 0; nb--) {
			continue;
		}
	}
	return false;
}

int guhjzni::fckphcmtsmrhvwkl(string ydvif, double lutdvant, double axlpcjh) {
	return 90463;
}

int guhjzni::lzsotpitfalzfzzjtwaco(bool pkqxspqvfwzfz, double gcgiybvzp, string bdzskbsxi) {
	return 29046;
}

void guhjzni::kuluuwayfp(double mqtqapwyybxpey, double bgechgvcsss, bool hvestciqcjjsdq) {
	double nzgqawkbsw = 60798;
	int safmdnkcaffnff = 842;
	if (842 != 842) {
		int nsgfe;
		for (nsgfe = 43; nsgfe > 0; nsgfe--) {
			continue;
		}
	}
	if (842 != 842) {
		int jl;
		for (jl = 96; jl > 0; jl--) {
			continue;
		}
	}

}

int guhjzni::debnvhtmdegk(int cvnghhu) {
	bool qkkvuiecj = false;
	string rysvlcrk = "gtgvfhvcfjjoeaejowbdouvxlnkfjobklm";
	int ltpwr = 578;
	int ldmknzsxgz = 3828;
	double eodosqjw = 30693;
	double fsbrwlquojwcqjq = 41536;
	int ztpqdg = 8471;
	int hzcmhppahncd = 631;
	double vioyemk = 21415;
	if (string("gtgvfhvcfjjoeaejowbdouvxlnkfjobklm") == string("gtgvfhvcfjjoeaejowbdouvxlnkfjobklm")) {
		int oudqdctvgn;
		for (oudqdctvgn = 50; oudqdctvgn > 0; oudqdctvgn--) {
			continue;
		}
	}
	return 57393;
}

int guhjzni::xbdogzdtxtxdufuspny(bool hmxrlgqvminz, double hkelsvomxudihzu, int uagdce, string hhxzhmi, double euvptryyrflfb, string bhejhs, bool hykeca, string spyjhqk, double csgimgavqhqrkjc) {
	double pvvxqviauknj = 5520;
	string rzzqatwdr = "woilhjvpklhyxxfepsxyklgugzqfcaejseridvzxswldufimopxklixfiqatulufd";
	if (5520 == 5520) {
		int xyxaojac;
		for (xyxaojac = 8; xyxaojac > 0; xyxaojac--) {
			continue;
		}
	}
	if (5520 == 5520) {
		int yntvtbil;
		for (yntvtbil = 24; yntvtbil > 0; yntvtbil--) {
			continue;
		}
	}
	if (5520 != 5520) {
		int zkemys;
		for (zkemys = 31; zkemys > 0; zkemys--) {
			continue;
		}
	}
	return 99399;
}

double guhjzni::zkjzhrvgtlcwhhzrc(double wimmwtpzap, int qhpnqmwxua, double mghlkpomoaawxi) {
	string elmsuorbrunuizi = "yxsnwnamdhiaqewzw";
	double xvqiczaej = 31064;
	string iegfgpnavkps = "vhfnrykhhqaveebiraqhmblybyv";
	bool jsskkrednsdvp = true;
	double tdxgvgs = 52486;
	double zjdeduezatieq = 101;
	string nizphhtu = "qhrcjsxxgqbttlxowrgthlwohwf";
	if (true != true) {
		int pkewhueh;
		for (pkewhueh = 39; pkewhueh > 0; pkewhueh--) {
			continue;
		}
	}
	if (true != true) {
		int at;
		for (at = 58; at > 0; at--) {
			continue;
		}
	}
	if (31064 != 31064) {
		int ykjtm;
		for (ykjtm = 23; ykjtm > 0; ykjtm--) {
			continue;
		}
	}
	return 33505;
}

int guhjzni::lyqqbancgxsstz(bool dmfrorel, string qrqcos, int bydtzohlbjoxd, double hiixnrpuivjx, string hywdydpeshkpv, int uligopbgefftn, double hfbtqjxbjbug) {
	bool rezpssmf = false;
	bool syngzhafholbot = false;
	int fhmtfthy = 2837;
	double ingsmtpwlpiaznm = 22757;
	double mzfflumz = 9227;
	bool lmatlctohktr = true;
	double bqwlbdrgypjrzhb = 22836;
	if (true == true) {
		int ao;
		for (ao = 98; ao > 0; ao--) {
			continue;
		}
	}
	if (2837 == 2837) {
		int bi;
		for (bi = 47; bi > 0; bi--) {
			continue;
		}
	}
	if (22757 == 22757) {
		int xyhrxq;
		for (xyhrxq = 9; xyhrxq > 0; xyhrxq--) {
			continue;
		}
	}
	if (true != true) {
		int kdxgz;
		for (kdxgz = 79; kdxgz > 0; kdxgz--) {
			continue;
		}
	}
	return 84305;
}

void guhjzni::bczaogluradyfltdivlordsw(string utatqktmsw) {
	bool ymzkb = true;
	double nwrjcpuvpe = 38990;
	double tddffipmyzvmp = 27866;
	if (27866 == 27866) {
		int cfixqv;
		for (cfixqv = 15; cfixqv > 0; cfixqv--) {
			continue;
		}
	}

}

double guhjzni::opsomanouqqgqsbddlonzuzk(double kacvopmuztptcz, string wxywqd, string iyvmci, bool fdfgzkew) {
	return 48474;
}

double guhjzni::eupvvcmjtsjscsmwntchglz(string whjcnwzheixyvcl, bool xicgphkpav, bool hhjrvhep) {
	string smcompt = "fujphvccjayhkputiruvcgnchzbwqzojk";
	string hfacyfwevsy = "awjdnwxopr";
	int blrjhfmzp = 2307;
	bool vaoacmhdnxeqve = true;
	bool joeus = true;
	int zvyanbc = 8115;
	int vzqdssyjcy = 1147;
	bool wbvpafawqwb = true;
	bool ukbvwqi = true;
	if (2307 != 2307) {
		int oerrjkdhqr;
		for (oerrjkdhqr = 78; oerrjkdhqr > 0; oerrjkdhqr--) {
			continue;
		}
	}
	return 59832;
}

guhjzni::guhjzni() {
	this->kuluuwayfp(12753, 4302, true);
	this->debnvhtmdegk(1313);
	this->xbdogzdtxtxdufuspny(false, 66802, 4753, string("qlhohdjwdpbhledgavrqxqvntkhpohppvxsb"), 21805, string("mlmhmmehjvufdedvwkhlokzcacxmcityiokwsjipimlurxyeqkc"), false, string("xeagyyrqbqpdtvtdkqdtyunaw"), 18770);
	this->zkjzhrvgtlcwhhzrc(3419, 990, 911);
	this->lyqqbancgxsstz(true, string("cyxtmabydemjisrneuixzjrhmgqlqbqmqiwqatu"), 1062, 37245, string("atvdxzaivsjfcbmiticehzygkytzgcqzezbrfeaqrmlzcuqrshwstbfpolukorhcrxbrfmgwxdvsxrh"), 2675, 4578);
	this->bczaogluradyfltdivlordsw(string("vaxhiybpoifu"));
	this->opsomanouqqgqsbddlonzuzk(9191, string("fuybenpmjduginokjvzwuoqnxyeobs"), string("jnskerbrcmvepplfmpfwivlpjvynocsxeqehqzctewvvcsufk"), false);
	this->eupvvcmjtsjscsmwntchglz(string("wtsgozvphbqfqyjwwupivruuxlhniyduntfvsxyonsnfflbladpewsorjkpazkqlsxnpwxmnlrnjqwpp"), true, true);
	this->mqchbhebexctoafj(true, string("vikuwbambehfiuuuvrwpjinhnwckwxmpphfrrplwxnipdkgdghkoorefcedbpslkatpcytsoivkbtw"), false, 34010, false, string("xbpbzxupdirfwbcgejxcdouglflrtfpxezmmfyv"));
	this->fckphcmtsmrhvwkl(string("zzrcqbbowdzfxgbjyyymisffzbhafpndwlxemwvisqpwhjkdbymiwxmanxvvdmevmtqgqtcoqyzjepgxm"), 37390, 17854);
	this->lzsotpitfalzfzzjtwaco(false, 87274, string("kyxzphskmkesijomwvwzuext"));
	this->vuitfycqtwdbzjeabsk(4269, 1615, string("zuognffmscveprutzuhtxovyyriffskwsvqbkz"), string("wtddxdnfwtrcvfjvvvpksqcgbzdqciyaziajuspqffzywkuqlnbkegbihikkcxuwyxuaoossbjfmnf"), string("zbmcapcasidlekczmfcxtlnvdfkbpxruv"));
	this->hiavqfoaqekvqdbhdmvdyvwt(string("igurbffilytygrtpdidocblrjtvqmxddcafacrkilquzjwbeiyhpbtwjczeqtcbo"), true, 6861, false, false, string("tnrzznpvqnsdmemdsnrtbxqynkrvozquvoqtuapjprqvhwvfdtrqxwkthicvlwcvzzbifaucvpavdtdhnerldgbbzycde"), 5296, 73966, 4893);
	this->kibbczywfjlgnjehvcax(24335, 22986, 28887, true);
	this->ozfmgpxqziu(450);
	this->kwgehezokxhll(false, false, 1830, 3643, string("bslmuuptbsmwizuxddtyuuodlleckvxdgpidefpzqheqcujvhlce"), string("nrbmbyfmwxbsbuxkvpdfqkoyrcmroowcgefeyrypbqjxnegoiidpernnftjzbibrvaqufnxyngnuyb"));
	this->jcvcpkkubjjbjaexnnnprx();
}
