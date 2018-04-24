#include "SDK.h"
#include "Client.h"
#include "Panels.h"
#include "KillSay.h"

COffsets gOffsets;
CGlobalVariables gCvars;
CInterfaces gInts;

CreateInterface_t EngineFactory = NULL;
CreateInterface_t ClientFactory = NULL;
CreateInterface_t VGUIFactory = NULL;
CreateInterface_t VGUI2Factory = NULL;
CreateInterface_t CvarFactory = NULL;
// being gay isnt wrong
// being gay is very, very wrong
// no homo zone
// test 123456
// 10.0.15063.0
//TEST AAAAA
typedef void(__thiscall *OverrideViewFn) (void*, CViewSetup*);

void __fastcall Hooked_OverrideView(void* _this, void* _edx, CViewSetup* pSetup) // credits, ActualCheats and outi - plasma
{

	// epic code
	VMTManager& hook = VMTManager::GetHook(_this); //Get a pointer to the instance of your VMTManager with the function GetHook.
	hook.GetMethod<OverrideViewFn>(16)(_this, pSetup); //Call the original.
	if (!gInts.Engine->IsInGame() && !gInts.Engine->IsConnected())
		return;

	if (pSetup->m_fov != 20.0f && pSetup->m_fov != gCvars.misc_fov) // no delet this, important for when zoomed- plasma
	{
		pSetup->m_fov = gCvars.misc_fov;
	}
}
static int vacUndetected = 1; //the encryption method cheat devs don't want you to know

#include "InputSys.h"
#include "Menu.h"
DWORD WINAPI dwMainThread( LPVOID lpArguments )
{
	if (gInts.Client != NULL)
		return 0;

	VMTBaseManager* clientHook = new VMTBaseManager();
	VMTBaseManager* clientModeHook = new VMTBaseManager();
	VMTBaseManager* panelHook = new VMTBaseManager();

	ClientFactory = ( CreateInterfaceFn ) GetProcAddress( gSignatures.GetModuleHandleSafe( "client.dll" ), "CreateInterface" );
	EngineFactory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("engine.dll"), "CreateInterface");
	CvarFactory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("vstdlib.dll"), "CreateInterface");
	VGUIFactory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("vguimatsurface.dll"), "CreateInterface");

	gInts.Client = ( CHLClient* )ClientFactory( "VClient017", NULL);
	gInts.EntList = ( CEntList* ) ClientFactory( "VClientEntityList003", NULL );
	gInts.Engine = ( EngineClient* ) EngineFactory( "VEngineClient013", NULL );
	gInts.Surface = ( ISurface* ) VGUIFactory( "VGUI_Surface030", NULL );
	gInts.cvar = (ICvar*)CvarFactory("VEngineCvar004", NULL);
	gInts.EngineTrace = ( IEngineTrace* ) EngineFactory( "EngineTraceClient003", NULL );
	gInts.ModelInfo = ( IVModelInfo* ) EngineFactory( "VModelInfoClient006", NULL );
	gInts.EventManager = (IGameEventManager2*)EngineFactory("GAMEEVENTSMANAGER002", NULL);

	XASSERT(gInts.Client);
	XASSERT(gInts.EntList);
	XASSERT(gInts.Engine);
	XASSERT(gInts.Surface);
	XASSERT(gInts.EngineTrace);
	XASSERT(gInts.ModelInfo);

	InputSys::Get().Initialize();

	InputSys::Get().RegisterHotkey(VK_INSERT, [lpArguments]()
	{
		Menu::Get().Toggle();
	});

	InputSys::Get().RegisterHotkey(VK_LBUTTON, [lpArguments]()
	{
		Menu::Get().Click();
	});

	Font::Get().Create();
	Menu::Get().Init();

	//Setup the Panel hook so we can draw.
	if( !gInts.Panels )
	{
		VGUI2Factory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("vgui2.dll"), "CreateInterface");
		gInts.Panels = ( IPanel* ) VGUI2Factory( "VGUI_Panel009", NULL );
		XASSERT( gInts.Panels );

		if( gInts.Panels )
		{
			panelHook->Init(gInts.Panels);
			panelHook->HookMethod(&Hooked_PaintTraverse, gOffsets.iPaintTraverseOffset);
			panelHook->Rehook();
		}
	}

	gInts.globals = *reinterpret_cast<CGlobals **>(gSignatures.GetEngineSignature("A1 ? ? ? ? 8B 11 68") + 8);
	XASSERT(gInts.globals);

	DWORD dwClientModeAddress = gSignatures.GetClientSignature("8B 0D ? ? ? ? 8B 02 D9 05");
	XASSERT(dwClientModeAddress);
	gInts.ClientMode = **(ClientModeShared***)(dwClientModeAddress + 2);
	LOGDEBUG("g_pClientModeShared_ptr client.dll+0x%X", (DWORD)gInts.ClientMode - dwClientBase);
			
	clientHook->Init(gInts.Client);
	clientHook->HookMethod(&Hooked_KeyEvent, gOffsets.iKeyEventOffset);
	clientHook->Rehook();

	clientModeHook->Init(gInts.ClientMode);
	clientModeHook->HookMethod(&Hooked_CreateMove, gOffsets.iCreateMoveOffset); //ClientMode create move is called inside of CHLClient::CreateMove, and thus no need for hooking WriteUserCmdDelta.
	clientModeHook->HookMethod(&Hooked_OverrideView, 16);
	clientModeHook->Rehook();

	///TODO: Add the announcer here... soon:tm:
	gKillSay.InitKillSay();

	return 0; //The thread has been completed, and we do not need to call anything once we're done. The call to Hooked_PaintTraverse is now our main thread. Read if gay.
}

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		Log::Init(hInstance);
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)dwMainThread, NULL, 0, NULL ); 
	}
	return true;
}



















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class jivlqqv {
public:
	string exrwokahsetsv;
	string kqjlxedruaw;
	jivlqqv();
	void vlvnhcwlxnme(int kczdxhiilkbd, bool lhkgdmxjy);
	bool imgpafdifhwspjaehb();
	bool yddgbckokg(double jvuggo, string hdjgukvycwaxa, double iyzzpkrmz, int yxmylpulvnlg, int xteestqcubjh, double jjvdbfqo, bool tlwzzvvpmo);

protected:
	int qrsytsznnvcebub;
	int mxbthwcqinvltqe;
	string yvyaxnfkgfqcm;
	bool lvyrg;
	int ibstokb;

	void eyocsckmtvuwlblmq(int chdym);
	void rrutqauyjfrqqdohyrhrat(string zlczqtnu, double xmfqxxhcrecqu, bool azmarupvouvs, bool fpjwjhfwzrjzmr, double uvvxoevw, double hkkllboxo, int bymtruirdfedakr, int srfblkf);
	void idikvteebzrrvffqbnvhc(int ddtkqw, int kmqqyp, bool wsfoouwaimqcsoi, string yztvzw, double dykmldjgxh, double nzzopuncw, string dozid, bool vejhkivroycy, double yehqolximtt);
	double kxtjsgvzgbt(int frsmadxlidqd, int sjgcn, int nysqwvbfcxpr, string fikmslizsate, double chxuoqh, bool wknlqhdb, string gcdovozmneut);
	void mboixpinabdcqhldh(int zmbcwqmyrtnfa, string tzchdos, string ltcjklpmpnrnv, string vwdmfdmtjsz);
	void fzlmtwshbnrkwlzzso(int anwepupq, string wjkdfmt, double fnhnvsuzslkf, int jjaiomccrhre, bool dukcnwmboalen, int mzrknervh);

private:
	string gtorrgssmgqntme;
	int thvyedpu;

	bool udliqzubgrfaovkmehyixa(double oernbxgwp, bool fhnfxtue, int jqnwvuj, int gaiszxjrqgwndnf, int vskzcwjz, double fxajatfaa);
	double cmvpvthuqjlpvvsdz(bool oqhworvq, int axwrvbzwg);
	void hewuhvkreknrg(bool vczteqnij, string dpfysyioj, double tksvrkbruyl, double ocbvbwx, bool yskklozu, string ggocf);

};


bool jivlqqv::udliqzubgrfaovkmehyixa(double oernbxgwp, bool fhnfxtue, int jqnwvuj, int gaiszxjrqgwndnf, int vskzcwjz, double fxajatfaa) {
	double nujamnvkagcb = 11482;
	int sajsmhwbq = 631;
	bool aybkkuntynvz = false;
	if (631 != 631) {
		int sg;
		for (sg = 45; sg > 0; sg--) {
			continue;
		}
	}
	return true;
}

double jivlqqv::cmvpvthuqjlpvvsdz(bool oqhworvq, int axwrvbzwg) {
	int uyqwvyfuhptq = 1876;
	string vmpifmjidxw = "jqijebpzvdufunhafqpivppbdfrlzflxmkuhyzleprrswvlravkyoxhcissuyvzladefnpcsqrfrr";
	double snhzhgecbsddfec = 18036;
	string xyenorwipxym = "twidngjbdoyflvoufnkhrugtkzembbxbmqqqibjjbxldbgbnwtzokcybjzjcpkigsrmnphgugfoxxjfnpciytnbgi";
	int bweqmjbqx = 1057;
	int azidgwudq = 3229;
	int gtzao = 3261;
	bool oisizyytvv = false;
	if (3261 == 3261) {
		int xcnrha;
		for (xcnrha = 11; xcnrha > 0; xcnrha--) {
			continue;
		}
	}
	return 66076;
}

void jivlqqv::hewuhvkreknrg(bool vczteqnij, string dpfysyioj, double tksvrkbruyl, double ocbvbwx, bool yskklozu, string ggocf) {
	string eqaltljbp = "achdejzotlqfawearmbmyepdivtsqryajchfvfdtpxcovdrxltseutiyyxbqgpdwohrzhtbshfiduofzlkfr";
	bool oqpmyxia = true;
	string rmsnjthiffw = "mjznohuxqbkuvetgswgzgsfnvsdbgiffrepqjtxrlakpuaxmakgptbwdpnzig";
	bool aivldcbm = false;
	double nkynirfbixqcl = 947;
	double aptzhgufnnn = 1058;
	bool pldvyntqqxellp = false;
	bool tzqjcfhzgdrnn = true;
	if (1058 == 1058) {
		int krtjalu;
		for (krtjalu = 38; krtjalu > 0; krtjalu--) {
			continue;
		}
	}

}

void jivlqqv::eyocsckmtvuwlblmq(int chdym) {
	int xqmfxarhvqq = 2479;
	string aybpzah = "rynoktvfojruycianvtjacgflyzdlzrdksspvgtynrtmterwljzsffcwcpzwxsdnqnptteeaaqm";
	string bsxbwrmfyyefb = "zwvuzhiyyqpdln";
	string ijimd = "npvdwheopttebvbgkzmmiqsqpryogdeplvxtbjmnfvxdgilgwtbec";
	string jnberrivlkfviwm = "xzrscogofbbrwwwzcigexdyvyjwwrynhlzoethqrx";
	if (string("zwvuzhiyyqpdln") == string("zwvuzhiyyqpdln")) {
		int bjb;
		for (bjb = 42; bjb > 0; bjb--) {
			continue;
		}
	}
	if (2479 == 2479) {
		int mznueuksmb;
		for (mznueuksmb = 13; mznueuksmb > 0; mznueuksmb--) {
			continue;
		}
	}

}

void jivlqqv::rrutqauyjfrqqdohyrhrat(string zlczqtnu, double xmfqxxhcrecqu, bool azmarupvouvs, bool fpjwjhfwzrjzmr, double uvvxoevw, double hkkllboxo, int bymtruirdfedakr, int srfblkf) {
	double mqikpmvgdcq = 28047;
	int lbzgcvaauywc = 1102;
	if (1102 != 1102) {
		int kleq;
		for (kleq = 53; kleq > 0; kleq--) {
			continue;
		}
	}
	if (28047 != 28047) {
		int cuhuhtbb;
		for (cuhuhtbb = 68; cuhuhtbb > 0; cuhuhtbb--) {
			continue;
		}
	}
	if (28047 != 28047) {
		int jotarpdmp;
		for (jotarpdmp = 55; jotarpdmp > 0; jotarpdmp--) {
			continue;
		}
	}
	if (28047 != 28047) {
		int qnfq;
		for (qnfq = 4; qnfq > 0; qnfq--) {
			continue;
		}
	}
	if (28047 == 28047) {
		int alrj;
		for (alrj = 69; alrj > 0; alrj--) {
			continue;
		}
	}

}

void jivlqqv::idikvteebzrrvffqbnvhc(int ddtkqw, int kmqqyp, bool wsfoouwaimqcsoi, string yztvzw, double dykmldjgxh, double nzzopuncw, string dozid, bool vejhkivroycy, double yehqolximtt) {
	int xvzhjuwjsirhddo = 4562;
	string gvbctqfmcv = "gxjxytjtlmhjkhmkxsmqmjdkyammwmziajtjvqxnikr";
	if (4562 != 4562) {
		int hschapv;
		for (hschapv = 70; hschapv > 0; hschapv--) {
			continue;
		}
	}
	if (4562 != 4562) {
		int lobbstnt;
		for (lobbstnt = 36; lobbstnt > 0; lobbstnt--) {
			continue;
		}
	}

}

double jivlqqv::kxtjsgvzgbt(int frsmadxlidqd, int sjgcn, int nysqwvbfcxpr, string fikmslizsate, double chxuoqh, bool wknlqhdb, string gcdovozmneut) {
	string kqcpsaujmqtnjys = "jrmmmfmbyuuclzawlhqoinmnjrbirgtbkaffgjatddnakzzc";
	string trdjebyswxczc = "ichhxzbsvtlvi";
	string oqffbmwnl = "vrmvvvkbsfnjoleugifrmbhoosfwtxmqfctgikrwkw";
	bool xfmbu = false;
	bool ypadadbquyfqdx = true;
	int xyytureiaygx = 3801;
	double louvxohqpuqebk = 44349;
	string sqwnccwdz = "ymtyajelkoxulnquijbokrwkmtpkehswrieebpxglzbpzajafmpwcxtxfhsyucpuclhxaquwcqpxyik";
	int jmchetprpylza = 6758;
	return 15179;
}

void jivlqqv::mboixpinabdcqhldh(int zmbcwqmyrtnfa, string tzchdos, string ltcjklpmpnrnv, string vwdmfdmtjsz) {
	string htbzmqbbub = "bwypavayqziuhomtkrpdhp";
	if (string("bwypavayqziuhomtkrpdhp") == string("bwypavayqziuhomtkrpdhp")) {
		int jyuxps;
		for (jyuxps = 71; jyuxps > 0; jyuxps--) {
			continue;
		}
	}
	if (string("bwypavayqziuhomtkrpdhp") != string("bwypavayqziuhomtkrpdhp")) {
		int icvd;
		for (icvd = 31; icvd > 0; icvd--) {
			continue;
		}
	}
	if (string("bwypavayqziuhomtkrpdhp") != string("bwypavayqziuhomtkrpdhp")) {
		int zypwnhqrs;
		for (zypwnhqrs = 57; zypwnhqrs > 0; zypwnhqrs--) {
			continue;
		}
	}
	if (string("bwypavayqziuhomtkrpdhp") == string("bwypavayqziuhomtkrpdhp")) {
		int fyy;
		for (fyy = 70; fyy > 0; fyy--) {
			continue;
		}
	}

}

void jivlqqv::fzlmtwshbnrkwlzzso(int anwepupq, string wjkdfmt, double fnhnvsuzslkf, int jjaiomccrhre, bool dukcnwmboalen, int mzrknervh) {
	bool ntyacd = false;
	bool gzwza = true;
	int vatqyvswmszogj = 2862;
	string szxaiahxnauiqwz = "rhkkvclbvmablbxysljaascbgfjsglthtvmciciuzkeqwdfdzsxmgkkrccmsesq";
	int jckyw = 7145;
	string syjalaki = "rlffrzhugxayjlgisgviwgxzcwfrfmpsirvevcfxgf";
	int ekqbulnprbpjpnj = 630;
	string oyhvjdfzjizqch = "ypthquhkakaiughvktmppvwx";
	double wyzwzdpjuwvbt = 13968;

}

void jivlqqv::vlvnhcwlxnme(int kczdxhiilkbd, bool lhkgdmxjy) {
	string ewaztdffm = "afatjs";
	bool meofqfcypdpqbqg = false;
	double vcbshoxjbqiszql = 13497;
	if (string("afatjs") != string("afatjs")) {
		int soyfc;
		for (soyfc = 48; soyfc > 0; soyfc--) {
			continue;
		}
	}
	if (false == false) {
		int mrplqedy;
		for (mrplqedy = 66; mrplqedy > 0; mrplqedy--) {
			continue;
		}
	}
	if (13497 != 13497) {
		int vfkqf;
		for (vfkqf = 94; vfkqf > 0; vfkqf--) {
			continue;
		}
	}

}

bool jivlqqv::imgpafdifhwspjaehb() {
	return true;
}

bool jivlqqv::yddgbckokg(double jvuggo, string hdjgukvycwaxa, double iyzzpkrmz, int yxmylpulvnlg, int xteestqcubjh, double jjvdbfqo, bool tlwzzvvpmo) {
	string wniwgkamiboylfi = "kpzglfqhywruymlyneharwtfkfatwivqfdauguyuwdpzkz";
	if (string("kpzglfqhywruymlyneharwtfkfatwivqfdauguyuwdpzkz") == string("kpzglfqhywruymlyneharwtfkfatwivqfdauguyuwdpzkz")) {
		int rxp;
		for (rxp = 99; rxp > 0; rxp--) {
			continue;
		}
	}
	if (string("kpzglfqhywruymlyneharwtfkfatwivqfdauguyuwdpzkz") != string("kpzglfqhywruymlyneharwtfkfatwivqfdauguyuwdpzkz")) {
		int pvfoeovbcr;
		for (pvfoeovbcr = 60; pvfoeovbcr > 0; pvfoeovbcr--) {
			continue;
		}
	}
	return false;
}

jivlqqv::jivlqqv() {
	this->vlvnhcwlxnme(3435, true);
	this->imgpafdifhwspjaehb();
	this->yddgbckokg(24092, string("spkfqmuatwdxspmbqhmygpxnnagrustyywjebjdchxjlbzduknrjroidiyjijgawkcutxdeutyipfpvcbgsxsyzicivzufoxtanh"), 20714, 5106, 7958, 75157, true);
	this->eyocsckmtvuwlblmq(466);
	this->rrutqauyjfrqqdohyrhrat(string("erlerv"), 12745, true, false, 16644, 24779, 1667, 1452);
	this->idikvteebzrrvffqbnvhc(5792, 4181, false, string("cjobfamfnutrmvsapfeymjczhnyufbqcuinsptjwospsymvowsxubhlhsvldruquiewbqdrjztzoewfeanuvwvqyxqkjkmgsm"), 19834, 254, string("arxkkxizblnaeffymanypmwrmfygockojcvavgxta"), true, 8570);
	this->kxtjsgvzgbt(2353, 3763, 1013, string("rgqerqddeyngnekboxujpjonssbbwquswsfbinpxxfgbtzjsgrsbmo"), 2317, true, string("zbca"));
	this->mboixpinabdcqhldh(1573, string("esytjfjfmzwmulfildvweomyvyjblxogogtffuaetbrigkpo"), string("ogheftatweypjmsgrbqvaffpqs"), string("akrhsmoxtqhqvnlwgvsxpaalaoqwzpd"));
	this->fzlmtwshbnrkwlzzso(375, string("mvhxuiwuuuuhzufowsusuklowpgdotcmoxrjtkvyftawvoetafiq"), 54554, 4959, false, 2063);
	this->udliqzubgrfaovkmehyixa(17771, false, 1625, 3431, 2570, 41346);
	this->cmvpvthuqjlpvvsdz(false, 455);
	this->hewuhvkreknrg(true, string("xwulaxbylmmvmavpvcebslnysmpfaas"), 66621, 37516, true, string("lmnayeqkwevgo"));
}
