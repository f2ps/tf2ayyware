#include "Util.h"

CUtil* Util;



void CUtil::VectorTransform(const Vector& vSome, const matrix3x4& vMatrix, Vector& vOut)
{
	for (auto i = 0; i < 3; i++)
		vOut[i] = vSome.Dot((Vector&)vMatrix[i]) + vMatrix[i][3];
}

float CUtil::RandFloatRange(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

void CUtil::ReplaceString(std::string& input, const std::string& what, const std::string& with_what)
{
	size_t index;
	index = input.find(what);
	while (index != std::string::npos)
	{
		input.replace(index, what.size(), with_what);
		index = input.find(what, index + with_what.size());
	}
}

float CUtil::flGetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = sqrt(vDelta.Length());

	if (m_fDistance < 1.0f)
		return 1.0f;

	return m_fDistance;
}

bool CUtil::IsVisible(void* pLocal, void* pEntity, Vector vStart, Vector vEnd)
{
	trace_t Trace;
	Ray_t Ray;			 // the future of variable naming
	CTraceFilter Filter;

	Filter.pSkip = pLocal;

	Ray.Init(vStart, vEnd);

	gInts.EngineTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	return (Trace.m_pEnt == pEntity);
}
void CUtil::silentMovementFix(CUserCmd *pUserCmd, Vector angles) //Fix for silent movement    creds gir + f1ssi0n
{
	Vector vecSilent(pUserCmd->forwardmove, pUserCmd->sidemove, pUserCmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);
	Vector angMove;
	VectorAngles(vecSilent, angMove);
	float flYaw = DEG2RAD(angles.y - pUserCmd->viewangles.y + angMove.y);
	pUserCmd->forwardmove = cos(flYaw) * flSpeed;
	pUserCmd->sidemove = sin(flYaw) * flSpeed;
}
bool CUtil::IsKeyPressed(int i)
{
	switch (i)
	{
	case 0: //None
		return true;
	case 1: //Mouse 1
		return GetAsyncKeyState(VK_LBUTTON);
	case 2:
		return GetAsyncKeyState(VK_RBUTTON);
	case 3:										  //Mouses 1-5
		return GetAsyncKeyState(VK_MBUTTON);
	case 4:
		return GetAsyncKeyState(VK_XBUTTON1);
	case 5:
		return GetAsyncKeyState(VK_XBUTTON2);
	case 6: //Shift
		return GetAsyncKeyState(VK_SHIFT);
	case 7: //Alt
		return GetAsyncKeyState(VK_MENU);
	case 8: //F
		return GetAsyncKeyState(0x46);
	default:
		return false;
	}

	return false;
}

bool CUtil::IsKeyPressedString(const char* i)
{
	if (i == "Always")
		return true;
	if (i == "Mouse 1")
		return GetAsyncKeyState(VK_LBUTTON);
	if (i == "Mouse 2")
		return GetAsyncKeyState(VK_RBUTTON);
	if (i == "Mouse 3")
		return GetAsyncKeyState(VK_MBUTTON);
	if (i == "Mouse 4")
		return GetAsyncKeyState(VK_XBUTTON1);
	if (i == "Mouse 5")
		return GetAsyncKeyState(VK_XBUTTON2);
	if (i == "Shift")
		return GetAsyncKeyState(VK_SHIFT);
	if (i == "Alt")
		return GetAsyncKeyState(VK_MENU);
	if (i == "F")
		return GetAsyncKeyState(0x46);

		return false;
}

bool CUtil::IsKeyDown(char* key)
{
	if (strlen(key) < 1) return true;

	return gInts.InputSys->IsButtonDown(gInts.InputSys->StringToButtonCode(key));
}

void CUtil::SilentMovementFix(CUserCmd *pUserCmd, Vector angles)
{
	Vector vecSilent(pUserCmd->forwardmove, pUserCmd->sidemove, pUserCmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);
	Vector angMove;
	VectorAngles(vecSilent, angMove);
	float flYaw = DEG2RAD(angles.y - pUserCmd->viewangles.y + angMove.y);
	pUserCmd->forwardmove = cos(flYaw) * flSpeed;
	pUserCmd->sidemove = sin(flYaw) * flSpeed;
	pUserCmd->viewangles = angles;
}

bool CUtil::IsHeadshotWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep)
{
	if (pWep->GetSlot() == 0 && pLocal->GetClassNum() == TF2_Sniper)
		if (pWep->GetItemDefinitionIndex() != WPN_Huntsman && pWep->GetItemDefinitionIndex() != WPN_CompoundBow)
			return true;

	if (pWep->GetItemDefinitionIndex() == WPN_Ambassador || pWep->GetItemDefinitionIndex() == WPN_FestiveAmbassador)
		return true;

	return false;
}

bool CUtil::IsReadyToHeadshot(CBaseCombatWeapon* pWep)
{
	if (pWep->ChargedDamage() >= 15.f)
		return true;

	return false;
}

bool CUtil::IsBackstabWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep)
{
	if (pWep->GetSlot() == 2 && pLocal->GetClassNum() == TF2_Spy)
		return true;

	return false;
}

bool CUtil::IsReadyToBackstab(CBaseEntity* pLocal, CBaseCombatWeapon* pWep)
{
	return Util->IsBackstabWeapon(pLocal, pLocal->GetActiveWeapon()) && pWep->ReadyToBackstab();
}

PVOID CUtil::InitKeyValue() //Credits f1ssion
{
	typedef PDWORD(__cdecl* Init_t)(int);
	static DWORD dwInitLocation = gSignatures.GetClientSignature("E8 ? ? ? ? 83 C4 14 85 C0 74 10 68") + 0x1;
	static DWORD dwInit = ((*(PDWORD)(dwInitLocation)) + dwInitLocation + 4);
	static Init_t InitKeyValues = (Init_t)dwInit;
	return InitKeyValues(32);
}




















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class msncexc {
public:
	double qsibbiq;
	double jzpcejorr;
	bool quohskpi;
	bool vnbkykfppoeqaya;
	string xcrsaca;
	msncexc();
	double ohglnkdhhkcmmbumu(bool ttzsursgjeqsoo, string efvpwqdftxpr, double ypwtcqjouik, int hxvmktl, string xghyocyaelmky);

protected:
	double dqcyccdzuahzc;
	double guixinbayoh;
	bool zyibaecpehgdx;

	void ckkhrhouyg(string rltutjislefs, int ccdelmf, double xakncg, int jqauwjcffnqo, string lqzijprpyud, string xsvlw, bool rreiad, double ueyvknlkguhy, int lhtlqyapayxidf);
	void xcbspdefoi(bool texxuudmkr, bool dhtnmflcyvfm, bool aijozlsbvdfycqj, bool jywaoqcmuvgb);

private:
	bool jbtldvfmfaykhr;
	double yqnbrebspjar;
	string hrtvw;

	bool hiuoqbgayukitagyoxgntkad();
	bool rheejrudntk(bool bgveywczbk, int hvuasbqoya, bool uiitxjffqt, bool ryfwowgxzhffvc, int mvhtpacsg, string fnwwjfnalpwn, bool sdswyrq, bool wonwcahdey, bool cpjxvqjgxtrqh, int ybbocza);

};


bool msncexc::hiuoqbgayukitagyoxgntkad() {
	double tfhoebhlkbgrton = 50704;
	double cppcyotytagzxx = 51201;
	string zyxij = "pcmedgyutokzdmhhmy";
	double ezgndcadp = 54102;
	bool imxudcryach = true;
	int eqdbjuowj = 423;
	bool hcteingne = false;
	int myiswozefcr = 662;
	bool hbdsdfihfbv = true;
	if (423 == 423) {
		int oecy;
		for (oecy = 83; oecy > 0; oecy--) {
			continue;
		}
	}
	return false;
}

bool msncexc::rheejrudntk(bool bgveywczbk, int hvuasbqoya, bool uiitxjffqt, bool ryfwowgxzhffvc, int mvhtpacsg, string fnwwjfnalpwn, bool sdswyrq, bool wonwcahdey, bool cpjxvqjgxtrqh, int ybbocza) {
	string rgnywizdbc = "hrktsijoqkkiwgokomcptsjcpvdqsekptflpdufsqlxg";
	string mdjkqysfzrij = "osspvjhujlmupypwxubbpizyreeybbnieryybslwwubqxbtksvjrpgt";
	double iqbscyisp = 16209;
	string tsvtdvav = "anqknkfbytckbholffaptlkr";
	string txhhrmdhjll = "iukmiltqonvipiqwpuuckjmouvfkerthoexrrrtoxavbeqdyzscehiwalvgazvpfiwymgyfezcjoonqbpovmrnlmfcrnoxux";
	int tsycehn = 5188;
	string pfqqkqkjlxsefd = "qbqwpaythjxbpjxjgkazicfmipokqaibjmfwobwyzbbelaxyq";
	int nerdbthxj = 5018;
	double uejjcqrc = 2172;
	if (5018 == 5018) {
		int bzr;
		for (bzr = 13; bzr > 0; bzr--) {
			continue;
		}
	}
	if (5018 == 5018) {
		int lfyk;
		for (lfyk = 7; lfyk > 0; lfyk--) {
			continue;
		}
	}
	if (5018 != 5018) {
		int nlmzayzvw;
		for (nlmzayzvw = 56; nlmzayzvw > 0; nlmzayzvw--) {
			continue;
		}
	}
	if (string("iukmiltqonvipiqwpuuckjmouvfkerthoexrrrtoxavbeqdyzscehiwalvgazvpfiwymgyfezcjoonqbpovmrnlmfcrnoxux") == string("iukmiltqonvipiqwpuuckjmouvfkerthoexrrrtoxavbeqdyzscehiwalvgazvpfiwymgyfezcjoonqbpovmrnlmfcrnoxux")) {
		int siiirkbsbo;
		for (siiirkbsbo = 19; siiirkbsbo > 0; siiirkbsbo--) {
			continue;
		}
	}
	if (5018 == 5018) {
		int mwoh;
		for (mwoh = 28; mwoh > 0; mwoh--) {
			continue;
		}
	}
	return true;
}

void msncexc::ckkhrhouyg(string rltutjislefs, int ccdelmf, double xakncg, int jqauwjcffnqo, string lqzijprpyud, string xsvlw, bool rreiad, double ueyvknlkguhy, int lhtlqyapayxidf) {
	string prgwgjrxvc = "ziduhdknuowackjazgywvvkwmirvslrcgctoipnxuvjxpkcarnuydimkgdxqeprxqypuczgm";
	bool mvmyifhshbzhp = true;
	string ttsilzagytu = "taf";
	if (string("taf") != string("taf")) {
		int ehnmsks;
		for (ehnmsks = 78; ehnmsks > 0; ehnmsks--) {
			continue;
		}
	}
	if (true == true) {
		int mj;
		for (mj = 7; mj > 0; mj--) {
			continue;
		}
	}
	if (true == true) {
		int hwp;
		for (hwp = 46; hwp > 0; hwp--) {
			continue;
		}
	}
	if (true == true) {
		int leo;
		for (leo = 63; leo > 0; leo--) {
			continue;
		}
	}
	if (true == true) {
		int akuzxwdij;
		for (akuzxwdij = 9; akuzxwdij > 0; akuzxwdij--) {
			continue;
		}
	}

}

void msncexc::xcbspdefoi(bool texxuudmkr, bool dhtnmflcyvfm, bool aijozlsbvdfycqj, bool jywaoqcmuvgb) {
	int rkbdpnw = 2654;
	int bynccfxyt = 1360;
	string dutjiggrcbve = "hllkcjxzbnitrairtaefvpiszishdmpsungfwhpkslq";
	string xcnoxopz = "ffwckbxuwbpzfovpwpbsrcytojkuvlfgjqybvcoxdachokefpfniiwjuqkzeucdnwwicnetmpyfujoxpgykjwchbcxktgmsww";
	int ctbkkh = 506;
	if (1360 == 1360) {
		int wvmtx;
		for (wvmtx = 85; wvmtx > 0; wvmtx--) {
			continue;
		}
	}
	if (506 != 506) {
		int jxw;
		for (jxw = 43; jxw > 0; jxw--) {
			continue;
		}
	}
	if (string("ffwckbxuwbpzfovpwpbsrcytojkuvlfgjqybvcoxdachokefpfniiwjuqkzeucdnwwicnetmpyfujoxpgykjwchbcxktgmsww") == string("ffwckbxuwbpzfovpwpbsrcytojkuvlfgjqybvcoxdachokefpfniiwjuqkzeucdnwwicnetmpyfujoxpgykjwchbcxktgmsww")) {
		int ynja;
		for (ynja = 61; ynja > 0; ynja--) {
			continue;
		}
	}
	if (1360 == 1360) {
		int anhpm;
		for (anhpm = 37; anhpm > 0; anhpm--) {
			continue;
		}
	}
	if (string("hllkcjxzbnitrairtaefvpiszishdmpsungfwhpkslq") == string("hllkcjxzbnitrairtaefvpiszishdmpsungfwhpkslq")) {
		int hmdgur;
		for (hmdgur = 87; hmdgur > 0; hmdgur--) {
			continue;
		}
	}

}

double msncexc::ohglnkdhhkcmmbumu(bool ttzsursgjeqsoo, string efvpwqdftxpr, double ypwtcqjouik, int hxvmktl, string xghyocyaelmky) {
	double bbagyu = 15475;
	double dxbnqqrshwqife = 26588;
	int gpfeneukelbhjck = 378;
	if (378 == 378) {
		int xhky;
		for (xhky = 55; xhky > 0; xhky--) {
			continue;
		}
	}
	if (15475 == 15475) {
		int unodx;
		for (unodx = 5; unodx > 0; unodx--) {
			continue;
		}
	}
	if (378 == 378) {
		int xiyjtbrdxb;
		for (xiyjtbrdxb = 75; xiyjtbrdxb > 0; xiyjtbrdxb--) {
			continue;
		}
	}
	if (26588 != 26588) {
		int majrbs;
		for (majrbs = 48; majrbs > 0; majrbs--) {
			continue;
		}
	}
	return 90263;
}

msncexc::msncexc() {
	this->ohglnkdhhkcmmbumu(false, string("alrvebwzuzgohwjljisdlihnhgyiugkjisggucqrkqhqfafdcwwgwigxvcutjrpfslljgkj"), 1797, 638, string("bgnoqbvegqjvsbuiaiazpkydmpfybbajqh"));
	this->ckkhrhouyg(string("kpvzkiwepejpeauixbechpu"), 208, 1389, 1138, string("jrkmevfxuwbxjiurpqnzkvfz"), string("gndwqtkyc"), true, 1804, 7990);
	this->xcbspdefoi(false, true, true, true);
	this->hiuoqbgayukitagyoxgntkad();
	this->rheejrudntk(true, 4321, false, true, 4177, string("vauaxdvinktfrrmlyafpzwi"), false, false, false, 6927);
}
