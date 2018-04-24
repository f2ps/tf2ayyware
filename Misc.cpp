#include "Misc.h"
#include "Util.h"
#include "CDrawManager.h"

CMisc gMisc;

void CMisc::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	//if (gInts.cvar->FindVar("viewmodel_fov")->GetInt != gCvars.misc_viewmodel_fov)
	gInts.cvar->FindVar("viewmodel_fov")->SetValue(gCvars.misc_viewmodel_fov);
	//pLocal->setfov(gCvars.misc_fov); // im gonna keep this code here because its funny and cute - plasma
	
	if (gCvars.misc_no_push)
	{
		ConVar* tf_avoidteammates_pushaway = gInts.cvar->FindVar("tf_avoidteammates_pushaway");
		if (tf_avoidteammates_pushaway->GetInt() == 1)
			tf_avoidteammates_pushaway->SetValue(0);
	}



	if (!(pLocal->GetFlags() & FL_ONGROUND) && pCommand->buttons & IN_JUMP)
	{
		if (gCvars.misc_autostrafe)
			if (pCommand->mousedx > 1 || pCommand->mousedx < -1)  //> 1 < -1 so we have some wiggle room
				pCommand->sidemove = pCommand->mousedx > 1 ? 450.f : -450.f;

		if (gCvars.misc_bunnyhop)
			pCommand->buttons &= ~IN_JUMP;
	}

	if (gCvars.misc_autobackstab && pLocal->GetActiveWeapon() && Util->IsReadyToBackstab(pLocal, pLocal->GetActiveWeapon()))
		pCommand->buttons |= IN_ATTACK;

	if (gCvars.misc_noisemaker_spam)
	{
		PVOID kv = Util->InitKeyValue();
		if (kv != NULL)
		{
			NoisemakerSpam(kv);
			gInts.Engine->ServerCmdKeyValues(kv);
		}
	}

	if (gCvars.misc_thirdPerson)
	{
		pLocal->ForceTauntCam(true);
	}
	else
	{
		pLocal->ForceTauntCam(false);
	}
	
	if (gCvars.misc_roll_speedhack && !(pCommand->buttons & IN_ATTACK)) // who changed my comment >:(
	{
		Vector vLocalAngles = pCommand->viewangles;
		float speed = pCommand->forwardmove;
		if (fabs(speed) > 0.0f) {
			pCommand->forwardmove = -speed;
			pCommand->sidemove = 0.0f;
			pCommand->viewangles.y = vLocalAngles.y;
			pCommand->viewangles.y -= 180.0f;
			if (pCommand->viewangles.y < -180.0f) pCommand->viewangles.y += 360.0f;
			pCommand->viewangles.z = 90.0f;
		}
	}

	if (gCvars.misc_wowsweet && fLastTime + 0.5f < gInts.globals->curtime)
	{
		if (pLocal->szGetClass() == "Heavy" && pLocal->GetActiveWeapon() && pLocal->GetActiveWeapon()->GetSlot() == 1 && pLocal->GetFlags() & FL_DUCKING)
		{
			if (pCommand->tick_count % 2)
				gInts.Engine->ClientCmd_Unrestricted("say wow sweet.");
			else
				gInts.Engine->ClientCmd_Unrestricted("say wow sweet!");
			fLastTime = gInts.globals->curtime;
		}
	}

	if (gCvars.misc_voice && fLastSpam + 3.f < gInts.globals->curtime) //add an option for the spam delay later
	{
		char* voicemenu = NULL;
		switch ((int)gCvars.misc_voice)
		{
		case 0: voicemenu = "voicemenu 2 2"; break;
		case 1: voicemenu = "voicemenu 2 3"; break;
		case 2: voicemenu = "voicemenu 2 6"; break;
		case 3: voicemenu = "voicemenu 1 4"; break;
		case 4: voicemenu = "voicemenu 1 6"; break;
		case 5: voicemenu = "voicemenu 0 0"; break;
		case 6: voicemenu = "voicemenu 0 1"; break;
			break;
		}
		gInts.Engine->ClientCmd_Unrestricted(voicemenu);
		fLastSpam = gInts.globals->curtime;
	}

}

void CMisc::NoisemakerSpam(PVOID kv) //Credits gir https://www.unknowncheats.me/forum/team-fortress-2-a/141108-infinite-noisemakers.html
{
	char chCommand[30] = "use_action_slot_item_server";
	typedef int(__cdecl* HashFunc_t)(const char*, bool);
	static DWORD dwHashFunctionLocation = gSignatures.GetClientSignature("FF 15 ? ? ? ? 83 C4 08 89 06 8B C6");
	static HashFunc_t s_pfGetSymbolForString = (HashFunc_t)**(PDWORD*)(dwHashFunctionLocation + 0x2);
	*(PDWORD)((DWORD)kv + 0x4) = 0;
	*(PDWORD)((DWORD)kv + 0x8) = 0;
	*(PDWORD)((DWORD)kv + 0xC) = 0;
	*(PDWORD)((DWORD)kv + 0x10) = 0xDEADBEEF;
	*(PDWORD)((DWORD)kv + 0x14) = 0;
	*(PDWORD)((DWORD)kv + 0x18) = 0;
	*(PDWORD)((DWORD)kv + 0x1C) = 0;
	*(PDWORD)((DWORD)kv + 0) = s_pfGetSymbolForString(chCommand, 1);
}

















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xwonhuk {
public:
	string blsklddqw;
	int hvhjjkd;
	int aniywvjoboq;
	bool hgqwngfum;
	xwonhuk();
	void uprhefvhopulmdryrxz();
	void uwjxkfcandzekxrqnppcooled(double qekxtazferbqd, bool rgahgy);
	bool nvylvthlkhfj(double bbxmwsvhqtegrgu, bool dwffvj, bool ohtrwelwyjwwb, bool hcayx, int ypnnq, string jzmrsqcgglc, double ktwcy, bool eqplsjxhw, string wsaqhuwvliqc);
	void scqqijzrqdnmgfiylrg();
	string jagbvuutfmwz(int aglmhzphv, double lidzh, string yzoqilqvcalsg, int bzdensfpwbtwlz, string xuujgntjaopza, double jtxmvwlplx);
	string eopqbbkexxaiam(bool smkfwosyglwi, double rpmghtqbskjlv, string stupojaopnjyt, string anvioepzp, string gkutmiavgjfehus, double nblsoxfiucolj);
	bool gcvkwnurxoyrazat(double pasetucmdwvib, int ekvzrp, string nujygpbqpmqsb, bool gncysqjivutm);
	double dzekwiovqohi();
	string zyfsyphgowooxnk(int iuubulexo, double uhhywomuzcc, double pdjgjqvpu, double tkqbyiy, int pnykdxyd, int horuqxzmutec, double chzux, string cinvr, double rgixused);

protected:
	bool cotktoxbedd;
	string kdchobinwnfrkle;
	double drecervmragcp;
	string fifxhfuofm;
	int kjaspijg;

	string myjiawmccroqgtdbvqwrxwgru(bool smnfr, bool dheuumrb, string enbkiadhsio, double rlgrlnwb, double lqrjffhvolfmd, string uaxuqlfq, int ucxnl, bool fjqme, bool koxvdav, int rfuyo);
	string xrqfaibapqlhl();
	bool qjmxovqdiwphzciptop(bool fwpxp, int pmqle, bool ygfflxlakuxlz, string hjkxo, int qryczv, int xzyzzuqoaixvv, double uudaji, int emtxnsnr);
	string dzluovecauodkyziaicd(double qsrpdqdmfakr, int bspxofxynsahwio, string vtmnz);
	bool fwqcxxvvdayjv();
	void kvkzbeccbryndbqtdqbj(string ryqoufdtxbgigp, bool mpzrawilipmtg, string tyexobbonecqmvp);
	string wadlqyzfaqmr(bool zzhlqp, double jcqjbzc, double wpyacxluyygam, bool fjnbnxba, int nieorocfuligdk, int cgkrztdzdqckqb, int czsek, string dygjtfwxfysrmt, double bglvlrahcusjdic);
	string sgixnxpqgijjuwmfhqkwmrpv(int xvxldcddzp, int yrhxfzkmhdbznag);

private:
	double iqzauklaas;
	double vaebzzklljqcgg;

	double amokgwyrszsrdwpxnr(double kbscufiyjuw, int rwwwnlvhnd, double uuygrzynugjogcd);
	void auckfskpjhmqplaprcqpnx(bool eavqal, double mgusl, int lsragoghrotbcb, bool vuwifcmralsasj);
	double psptgrgbqcvbplauqliimb(string uvxdky);
	string kwtxbguopnwepif(double sghvdmpjypusm);
	void jkeyvbhcvcomatnepqffqipl(string hzcvupumjfd, string zcdyfeu, bool temprzldwa, bool wqmtjhxxryhcuv, bool mtgxsb, int yufnnipl, bool hiqwydk, bool uwnnakpgqd, int tddrtbmghaxa, string shpfn);
	string oexsyouuglakwnimmvinbku(int enavp, bool tbzasslnenb, bool sdjrctdsnqzkbg, bool jxnumsh, string njrrcg, string sethbzlptwl);
	double pcsiarsxosdpyscmzqvgfe();
	void wxqaixjzoarwllczurvemhn(int dgzdgeu, double mgxmdmyzn);

};


double xwonhuk::amokgwyrszsrdwpxnr(double kbscufiyjuw, int rwwwnlvhnd, double uuygrzynugjogcd) {
	double lrkpwwbrmc = 37468;
	int jdlyydlounw = 3205;
	double ebfcxqxvyemjqrp = 72340;
	if (3205 != 3205) {
		int ydz;
		for (ydz = 10; ydz > 0; ydz--) {
			continue;
		}
	}
	return 38650;
}

void xwonhuk::auckfskpjhmqplaprcqpnx(bool eavqal, double mgusl, int lsragoghrotbcb, bool vuwifcmralsasj) {
	string svfijfyqajqvo = "bgmbzsyyggchldumsddosfcqnkyactaksgnutvxdauasqlxxbocojxxgh";
	bool zsipfk = false;
	string lbrxyfquds = "ucpyaoebdkauzjygmt";
	int ckjiickwtkfxi = 572;
	double esdzbcdc = 49135;
	int zoxgxaugolbohc = 1708;
	double zwvoetu = 30453;
	int fxtnndr = 3228;

}

double xwonhuk::psptgrgbqcvbplauqliimb(string uvxdky) {
	string jyliv = "wmbvcjfrwkyetlfqacyxqsxtcaxsju";
	return 43756;
}

string xwonhuk::kwtxbguopnwepif(double sghvdmpjypusm) {
	return string("");
}

void xwonhuk::jkeyvbhcvcomatnepqffqipl(string hzcvupumjfd, string zcdyfeu, bool temprzldwa, bool wqmtjhxxryhcuv, bool mtgxsb, int yufnnipl, bool hiqwydk, bool uwnnakpgqd, int tddrtbmghaxa, string shpfn) {
	string ohsaqqcrysyjou = "armezmiawcvbroyveoonxlaamkrms";
	double ayynovsgn = 27798;
	double nfqyizmmexkcj = 8307;
	string tpeitygxo = "gbkwxw";
	bool fdlwbuzpsad = true;
	string fexjxmfoyauwyjz = "bhuwcnoemcqaocoj";
	double uvvueqqultd = 92171;
	int dwjiwftmycjij = 1459;
	string mmhwamahxw = "yvdwhqpbnbxecipnxtjrjdzf";
	if (string("armezmiawcvbroyveoonxlaamkrms") == string("armezmiawcvbroyveoonxlaamkrms")) {
		int chjraezj;
		for (chjraezj = 96; chjraezj > 0; chjraezj--) {
			continue;
		}
	}
	if (true == true) {
		int hripytd;
		for (hripytd = 99; hripytd > 0; hripytd--) {
			continue;
		}
	}
	if (string("yvdwhqpbnbxecipnxtjrjdzf") != string("yvdwhqpbnbxecipnxtjrjdzf")) {
		int kfcnypm;
		for (kfcnypm = 24; kfcnypm > 0; kfcnypm--) {
			continue;
		}
	}

}

string xwonhuk::oexsyouuglakwnimmvinbku(int enavp, bool tbzasslnenb, bool sdjrctdsnqzkbg, bool jxnumsh, string njrrcg, string sethbzlptwl) {
	double mbpbdfvxmxxbvn = 16355;
	int dnjotxbvh = 7097;
	bool qzizfvmfshivh = true;
	if (true != true) {
		int myyzj;
		for (myyzj = 96; myyzj > 0; myyzj--) {
			continue;
		}
	}
	if (16355 != 16355) {
		int qbietasw;
		for (qbietasw = 32; qbietasw > 0; qbietasw--) {
			continue;
		}
	}
	return string("xlwgrkrsx");
}

double xwonhuk::pcsiarsxosdpyscmzqvgfe() {
	double clfiu = 7530;
	int jmsppeglesi = 2305;
	string akwyo = "hmfmkbpxeedbckbdodfhzdjifjangqbclwpplybtucjmedacftzcsrujuxlujvxbiijctlpvqhimna";
	int pltkjdjj = 1035;
	double zmyxsgxz = 47394;
	bool yzljgubeqmqz = false;
	int qqjgy = 2230;
	string inarajjm = "xedxhbwwppjqfjqfgagbixzavyxqvflffwfclenxroopiklcxjgfcruvzp";
	string ladopo = "eaqpbiqwgumb";
	if (7530 == 7530) {
		int decoo;
		for (decoo = 87; decoo > 0; decoo--) {
			continue;
		}
	}
	return 34846;
}

void xwonhuk::wxqaixjzoarwllczurvemhn(int dgzdgeu, double mgxmdmyzn) {
	double mwdnhejmgwa = 37482;
	double ooivfhiqvsgrgz = 1001;
	int pcjaiolvshdgh = 2475;
	if (1001 == 1001) {
		int fxkudpogeu;
		for (fxkudpogeu = 71; fxkudpogeu > 0; fxkudpogeu--) {
			continue;
		}
	}
	if (2475 != 2475) {
		int gdhhlgsit;
		for (gdhhlgsit = 86; gdhhlgsit > 0; gdhhlgsit--) {
			continue;
		}
	}

}

string xwonhuk::myjiawmccroqgtdbvqwrxwgru(bool smnfr, bool dheuumrb, string enbkiadhsio, double rlgrlnwb, double lqrjffhvolfmd, string uaxuqlfq, int ucxnl, bool fjqme, bool koxvdav, int rfuyo) {
	double bmjfcqyqqmecixk = 45779;
	int fmwsfjnrux = 3481;
	int somjt = 3759;
	int rzusu = 2266;
	if (3759 != 3759) {
		int ymygzarrm;
		for (ymygzarrm = 84; ymygzarrm > 0; ymygzarrm--) {
			continue;
		}
	}
	if (45779 != 45779) {
		int iztbnnvtg;
		for (iztbnnvtg = 61; iztbnnvtg > 0; iztbnnvtg--) {
			continue;
		}
	}
	return string("ohvfcdxxkfvrdoercy");
}

string xwonhuk::xrqfaibapqlhl() {
	bool oxggfiwqaeuurbi = true;
	if (true != true) {
		int fffbbtonvw;
		for (fffbbtonvw = 85; fffbbtonvw > 0; fffbbtonvw--) {
			continue;
		}
	}
	if (true != true) {
		int qxbu;
		for (qxbu = 53; qxbu > 0; qxbu--) {
			continue;
		}
	}
	if (true == true) {
		int qxcnwvwxp;
		for (qxcnwvwxp = 32; qxcnwvwxp > 0; qxcnwvwxp--) {
			continue;
		}
	}
	if (true != true) {
		int mzmmqog;
		for (mzmmqog = 93; mzmmqog > 0; mzmmqog--) {
			continue;
		}
	}
	return string("vnjbxmxa");
}

bool xwonhuk::qjmxovqdiwphzciptop(bool fwpxp, int pmqle, bool ygfflxlakuxlz, string hjkxo, int qryczv, int xzyzzuqoaixvv, double uudaji, int emtxnsnr) {
	int dlqedrhfzqe = 5637;
	string anvjqwoffcrgbc = "twpsyxjjljtowczkzchdjudwzkdenwpqjyfgeamdwmnktaeenzyggpxrokqaogaiaiqwr";
	double reneef = 99054;
	double ccsguj = 35748;
	string lhhvuvigwrm = "ofjunsvakicwcqxfsemqkflcmpycwweofpnugpylngexwtdhrgnsoqqwkppdhlwfoapnyhwebzcwbsjy";
	string isgthxvq = "jlrtvvvzykt";
	string npucndobgxt = "rvbgxcrwhguetmgbhxgqzjgtbkcjvszifxaupmnaqykfkkfdjretnpiphhdcsekzobfcuesjlkswueteh";
	if (string("twpsyxjjljtowczkzchdjudwzkdenwpqjyfgeamdwmnktaeenzyggpxrokqaogaiaiqwr") != string("twpsyxjjljtowczkzchdjudwzkdenwpqjyfgeamdwmnktaeenzyggpxrokqaogaiaiqwr")) {
		int bkvzffvei;
		for (bkvzffvei = 99; bkvzffvei > 0; bkvzffvei--) {
			continue;
		}
	}
	return false;
}

string xwonhuk::dzluovecauodkyziaicd(double qsrpdqdmfakr, int bspxofxynsahwio, string vtmnz) {
	return string("uxtjxd");
}

bool xwonhuk::fwqcxxvvdayjv() {
	double nyiginuyi = 2187;
	bool jxtjqfwrqqxu = false;
	int xtxkaarc = 830;
	double jwhgpmzcbnwecut = 26466;
	int eqaphdobbobuvx = 1205;
	bool iqfxhzr = false;
	int laysmzkgly = 3337;
	string albsur = "tlyaqhavvajzuqkz";
	double sbfwuc = 44116;
	if (string("tlyaqhavvajzuqkz") == string("tlyaqhavvajzuqkz")) {
		int ygaarlb;
		for (ygaarlb = 80; ygaarlb > 0; ygaarlb--) {
			continue;
		}
	}
	if (3337 != 3337) {
		int tqyzcyxs;
		for (tqyzcyxs = 19; tqyzcyxs > 0; tqyzcyxs--) {
			continue;
		}
	}
	return true;
}

void xwonhuk::kvkzbeccbryndbqtdqbj(string ryqoufdtxbgigp, bool mpzrawilipmtg, string tyexobbonecqmvp) {
	int lrudj = 40;
	bool rihotwuvjk = true;
	double phepgnnkv = 42234;
	int cjpmvtqqgq = 3942;
	bool arsljrmp = true;
	int smhlabmkuo = 3643;
	double ygsbqffdxz = 23846;

}

string xwonhuk::wadlqyzfaqmr(bool zzhlqp, double jcqjbzc, double wpyacxluyygam, bool fjnbnxba, int nieorocfuligdk, int cgkrztdzdqckqb, int czsek, string dygjtfwxfysrmt, double bglvlrahcusjdic) {
	bool aouhoubkibjetik = true;
	string svidjyunbvlh = "nisnfwpqcevfnaknrncienxdndhnbncpoeijzbxqrpvxtqhubsvyqsjiymbraedamhadnjsuikcdafnszcqsuctjfpsv";
	if (true == true) {
		int vlji;
		for (vlji = 56; vlji > 0; vlji--) {
			continue;
		}
	}
	if (true != true) {
		int wzqq;
		for (wzqq = 77; wzqq > 0; wzqq--) {
			continue;
		}
	}
	return string("tuoip");
}

string xwonhuk::sgixnxpqgijjuwmfhqkwmrpv(int xvxldcddzp, int yrhxfzkmhdbznag) {
	double fjaukrfarlzax = 70922;
	string srnilgbnvvnrg = "itmyfnxfsnajnzmozwyssrmwdzquutmechgdawujaprzjkmxkgcidsfzakonwuvdshhn";
	string fjlllvdi = "byvzxrymjcdyosavkzeqenhnwdaizuhwtrwabzzzalnbhexowqrhkvgr";
	int iwrmitynwgjre = 1691;
	bool hfqchxhslat = true;
	bool oblymnso = false;
	double fbbfhjbuni = 7599;
	int kiqqxcq = 6840;
	int wnpxpmxfvnxlqa = 1685;
	if (true == true) {
		int oleeiuff;
		for (oleeiuff = 86; oleeiuff > 0; oleeiuff--) {
			continue;
		}
	}
	if (false != false) {
		int rxlr;
		for (rxlr = 38; rxlr > 0; rxlr--) {
			continue;
		}
	}
	if (true != true) {
		int rpyzm;
		for (rpyzm = 20; rpyzm > 0; rpyzm--) {
			continue;
		}
	}
	if (true != true) {
		int zyz;
		for (zyz = 16; zyz > 0; zyz--) {
			continue;
		}
	}
	return string("ltbnpzwdhhf");
}

void xwonhuk::uprhefvhopulmdryrxz() {
	double hvpxoyxpls = 31942;
	int ekhksncazuhbptz = 51;
	double hyutnuqmxxp = 9322;
	int enrueqjjs = 543;
	bool hshzcxjygsdvrue = true;
	string foefdufftv = "ogcmvsupiatiazxbgpkeuaulfzaafwvtipeqhrokmgfuhksjspbkdpskfwotgpksahzimok";
	double wtcntmtc = 24747;
	string rosgxvdmyvixrid = "mtpfhpfyswejjcypszlxlljgtcmpbvkimgazpoqranqrtqsicsyepgmevgzwjphjsetesmnnyvhcyvtlidgf";
	double cdjaptanva = 56107;
	if (9322 == 9322) {
		int qfcax;
		for (qfcax = 83; qfcax > 0; qfcax--) {
			continue;
		}
	}

}

void xwonhuk::uwjxkfcandzekxrqnppcooled(double qekxtazferbqd, bool rgahgy) {
	double fpztuvgulj = 11215;
	string lnbfusbdkvp = "ucoamwcjtnltlktekuqkqwlnsqpnugmssvgfzvkmfjwijuruupkbavmpsbvkvfujyofyt";
	double lbwbrtrupjqfs = 49908;
	double pfjgvnjci = 57321;
	bool tefoiai = true;
	double mxhxvfwijkefc = 9383;
	double fqmrigrmumyga = 778;

}

bool xwonhuk::nvylvthlkhfj(double bbxmwsvhqtegrgu, bool dwffvj, bool ohtrwelwyjwwb, bool hcayx, int ypnnq, string jzmrsqcgglc, double ktwcy, bool eqplsjxhw, string wsaqhuwvliqc) {
	int kqhtwgkvpi = 6949;
	string yluwodmtqhwfmn = "gtvembjifasokxvjtaddxmfacxmlovpdwqnqqcvkeinqvndquiqwanlrhsmlzagcjifqjpplan";
	bool otokjqnbeysp = true;
	string xllbusgcmle = "vdnkqkijunovjaucltxivzkqjakoowscrtfgeoappthwihfvztqeyikgti";
	string qihtdzws = "evzhqnxshfyvmtklkmkkwbeaabobwaiwurjxgfsqlrvkmovwrpkrkizmwxvguxknazu";
	int vtqlwl = 525;
	bool bgjsg = false;
	double ykhqambwoe = 34710;
	int duqanjzcp = 1560;
	if (34710 != 34710) {
		int uyz;
		for (uyz = 22; uyz > 0; uyz--) {
			continue;
		}
	}
	if (string("evzhqnxshfyvmtklkmkkwbeaabobwaiwurjxgfsqlrvkmovwrpkrkizmwxvguxknazu") != string("evzhqnxshfyvmtklkmkkwbeaabobwaiwurjxgfsqlrvkmovwrpkrkizmwxvguxknazu")) {
		int hvbypbcta;
		for (hvbypbcta = 24; hvbypbcta > 0; hvbypbcta--) {
			continue;
		}
	}
	if (string("gtvembjifasokxvjtaddxmfacxmlovpdwqnqqcvkeinqvndquiqwanlrhsmlzagcjifqjpplan") == string("gtvembjifasokxvjtaddxmfacxmlovpdwqnqqcvkeinqvndquiqwanlrhsmlzagcjifqjpplan")) {
		int fwfhm;
		for (fwfhm = 56; fwfhm > 0; fwfhm--) {
			continue;
		}
	}
	if (string("evzhqnxshfyvmtklkmkkwbeaabobwaiwurjxgfsqlrvkmovwrpkrkizmwxvguxknazu") == string("evzhqnxshfyvmtklkmkkwbeaabobwaiwurjxgfsqlrvkmovwrpkrkizmwxvguxknazu")) {
		int tls;
		for (tls = 55; tls > 0; tls--) {
			continue;
		}
	}
	if (string("gtvembjifasokxvjtaddxmfacxmlovpdwqnqqcvkeinqvndquiqwanlrhsmlzagcjifqjpplan") == string("gtvembjifasokxvjtaddxmfacxmlovpdwqnqqcvkeinqvndquiqwanlrhsmlzagcjifqjpplan")) {
		int equaedhjk;
		for (equaedhjk = 51; equaedhjk > 0; equaedhjk--) {
			continue;
		}
	}
	return true;
}

void xwonhuk::scqqijzrqdnmgfiylrg() {
	double kmzqje = 37814;
	int uicvfiid = 5366;
	double bzggkenrx = 47474;
	int xehrlvzord = 1245;
	bool ifxbtrpybjfs = false;
	double djaksnaved = 16436;
	bool dzvdamtmy = true;
	double xludaraouvh = 46179;
	string kinmhrkourrufs = "wspjfeqhfwjfmyaqifiiypskijaykpifivokfxkcjfatjwgcvoyyetvqperrssgztgtdisenfpgnkr";
	bool kchcsbnyspho = true;
	if (16436 != 16436) {
		int cz;
		for (cz = 77; cz > 0; cz--) {
			continue;
		}
	}
	if (16436 == 16436) {
		int lmufmvtjnx;
		for (lmufmvtjnx = 65; lmufmvtjnx > 0; lmufmvtjnx--) {
			continue;
		}
	}

}

string xwonhuk::jagbvuutfmwz(int aglmhzphv, double lidzh, string yzoqilqvcalsg, int bzdensfpwbtwlz, string xuujgntjaopza, double jtxmvwlplx) {
	double jghlbggcl = 14401;
	double zqgdtqjfezxpkkf = 50172;
	string umcctbetigdj = "fjckscyijqvzbpdvyoisxcmukdrolzrybyuoumzutnmpqcbx";
	int mtimwyraqynv = 3884;
	int nzaplb = 1944;
	if (string("fjckscyijqvzbpdvyoisxcmukdrolzrybyuoumzutnmpqcbx") == string("fjckscyijqvzbpdvyoisxcmukdrolzrybyuoumzutnmpqcbx")) {
		int tv;
		for (tv = 23; tv > 0; tv--) {
			continue;
		}
	}
	if (string("fjckscyijqvzbpdvyoisxcmukdrolzrybyuoumzutnmpqcbx") != string("fjckscyijqvzbpdvyoisxcmukdrolzrybyuoumzutnmpqcbx")) {
		int moj;
		for (moj = 67; moj > 0; moj--) {
			continue;
		}
	}
	return string("wxnf");
}

string xwonhuk::eopqbbkexxaiam(bool smkfwosyglwi, double rpmghtqbskjlv, string stupojaopnjyt, string anvioepzp, string gkutmiavgjfehus, double nblsoxfiucolj) {
	double ydnsbfnzvls = 10055;
	double rhtvhhvwxhlckrq = 19824;
	string sngtgogx = "vtvntgarkgrmnujbddotxeygegnrhlqqvtsesanmepwabmrqoecvrhybmoiiuy";
	int mlqlymzktqsqji = 1816;
	bool mzont = true;
	bool rjoncibxyg = false;
	bool ruryvn = false;
	string yucbmw = "ijnsdqtmrclslnmzboikprlvkqienldnzopsnpcyhkuvceumjzemlhinxsqdzrkeidaqgerponilo";
	double kcmxkwbluvjuzo = 8131;
	double yvkcmzwxvwrrm = 1094;
	if (string("vtvntgarkgrmnujbddotxeygegnrhlqqvtsesanmepwabmrqoecvrhybmoiiuy") != string("vtvntgarkgrmnujbddotxeygegnrhlqqvtsesanmepwabmrqoecvrhybmoiiuy")) {
		int cqgbc;
		for (cqgbc = 28; cqgbc > 0; cqgbc--) {
			continue;
		}
	}
	if (1816 != 1816) {
		int ncxmkoosgp;
		for (ncxmkoosgp = 59; ncxmkoosgp > 0; ncxmkoosgp--) {
			continue;
		}
	}
	if (1094 == 1094) {
		int bgtqi;
		for (bgtqi = 96; bgtqi > 0; bgtqi--) {
			continue;
		}
	}
	return string("");
}

bool xwonhuk::gcvkwnurxoyrazat(double pasetucmdwvib, int ekvzrp, string nujygpbqpmqsb, bool gncysqjivutm) {
	int kaabylbltiupw = 1734;
	string dchttfdawoup = "qnbrijrkjspdlnizdzzdjijfrmfnqairziflcafnwokkhcmbynhbielgptdorpdhnbeodafvvcycqenzasljmayjoihzunti";
	double clftibpmzluvlkf = 4048;
	int epmwicflwhxcbx = 502;
	int qxvinid = 623;
	if (4048 == 4048) {
		int tylgevpn;
		for (tylgevpn = 45; tylgevpn > 0; tylgevpn--) {
			continue;
		}
	}
	if (4048 == 4048) {
		int ffbxafd;
		for (ffbxafd = 79; ffbxafd > 0; ffbxafd--) {
			continue;
		}
	}
	return true;
}

double xwonhuk::dzekwiovqohi() {
	string iqpfhflkzazr = "zkfxsepkmq";
	int nhquzvfenu = 6352;
	int tftqxmwosz = 3430;
	return 3078;
}

string xwonhuk::zyfsyphgowooxnk(int iuubulexo, double uhhywomuzcc, double pdjgjqvpu, double tkqbyiy, int pnykdxyd, int horuqxzmutec, double chzux, string cinvr, double rgixused) {
	int yedmblkhptdny = 4085;
	int rywjxk = 1970;
	double viffqauzirjzdir = 32255;
	double gwlareooqsxdp = 5064;
	int avimigwgxgsmua = 1185;
	double jqstuw = 6708;
	string sqzzeutrr = "utgttrwhrmtxxjcpqkzqqurdsmvvjkssubkuwmncmupyapxwsoioxdticxumofkglxaqyan";
	string jppanfwradowsp = "ipgworztxqcmpmodkfpiflqqygdxrdkbxxedhqxfvmqsfivpj";
	if (string("utgttrwhrmtxxjcpqkzqqurdsmvvjkssubkuwmncmupyapxwsoioxdticxumofkglxaqyan") != string("utgttrwhrmtxxjcpqkzqqurdsmvvjkssubkuwmncmupyapxwsoioxdticxumofkglxaqyan")) {
		int jeh;
		for (jeh = 38; jeh > 0; jeh--) {
			continue;
		}
	}
	if (1185 == 1185) {
		int hcphpyn;
		for (hcphpyn = 19; hcphpyn > 0; hcphpyn--) {
			continue;
		}
	}
	if (5064 == 5064) {
		int lfuagysdu;
		for (lfuagysdu = 26; lfuagysdu > 0; lfuagysdu--) {
			continue;
		}
	}
	if (4085 != 4085) {
		int wqjyqovw;
		for (wqjyqovw = 86; wqjyqovw > 0; wqjyqovw--) {
			continue;
		}
	}
	return string("eivmc");
}

xwonhuk::xwonhuk() {
	this->uprhefvhopulmdryrxz();
	this->uwjxkfcandzekxrqnppcooled(8659, false);
	this->nvylvthlkhfj(40247, false, false, false, 8829, string("nbzlldfxfkwfophgberkziixaotncuhapcnnemgoisowxxlvpxvurwjrqtfqdowj"), 2720, false, string("codnosjziomwaambjdqvrjymntagwmbuqxroeosuecpfqmlyqgldqpnzydvoqgupfmmqmsdwmezu"));
	this->scqqijzrqdnmgfiylrg();
	this->jagbvuutfmwz(1197, 39880, string("rdypcdgpkzpvwdamlcenoclqwbgxkdaxgyzljvjvpeqguxdofvikdaqtmgqnamtyvfrxonkmxxsttayfqlxzxf"), 5080, string("cxzgnpwiqyqtoaopdgpanlxnmvpwkowryldrgwzlavykhikojzlznepsppwamryqvsoybeyqiszuzcwrjzo"), 2342);
	this->eopqbbkexxaiam(true, 16710, string("frubztfxrbrphhkmfztrqwuuznxxacxusaajmophhtqmggsxqpgesxuoufasyludqcqcgmhunboylpum"), string("skdubdsmhqhkpchvo"), string("ssmtlhajaetefqifbgmsvdtejrpzmhmyb"), 18031);
	this->gcvkwnurxoyrazat(6201, 4027, string("tneoztwkzoxuyryzzjfdaccvtpw"), false);
	this->dzekwiovqohi();
	this->zyfsyphgowooxnk(3545, 3129, 4060, 9926, 109, 3731, 82780, string("nmwxjafytqackknhuzndbsunihatihgehvjpmtuyflbpnmfhezzmy"), 9117);
	this->myjiawmccroqgtdbvqwrxwgru(true, true, string("pcmoqtzzsaolwhvwnyjmjglxjwoueubdsapxrxbtrwjjqtococonklrisdxdgaebqnxswcrpskdynoafa"), 28563, 84476, string("cufymnusmzgl"), 1284, false, true, 823);
	this->xrqfaibapqlhl();
	this->qjmxovqdiwphzciptop(true, 498, true, string("ookcdyvseskuuofizqjiemlhtgwphsmgbgailefubmckzjzjrnfpdpluekqwntmofeveaooumtxxhwrsfnppvggwcfuxax"), 5150, 5574, 7502, 4449);
	this->dzluovecauodkyziaicd(8484, 4015, string("vormxpbjxsawuvcikxyniqqnajvejzgpcukbddvtqixxseoqhpctnuczefzhcvulpnoihrlfrmdloznex"));
	this->fwqcxxvvdayjv();
	this->kvkzbeccbryndbqtdqbj(string("jwhoeaqpxtlukfuicqyyrksvtseysqmoghxcslicdbfzthhyltycagucwplpbnrdweybqevmelckf"), true, string("gstknyqpecndkcpkducttdixuzdeggieqidwlxz"));
	this->wadlqyzfaqmr(true, 15130, 23333, false, 2152, 964, 2120, string("zrbdrehvniqqsrvldequybwhswzktsc"), 82595);
	this->sgixnxpqgijjuwmfhqkwmrpv(2311, 8118);
	this->amokgwyrszsrdwpxnr(6453, 2996, 6306);
	this->auckfskpjhmqplaprcqpnx(false, 12427, 2865, true);
	this->psptgrgbqcvbplauqliimb(string("zfdojwopnwhrnkjqkwseurktktrppmuajemrvkj"));
	this->kwtxbguopnwepif(9484);
	this->jkeyvbhcvcomatnepqffqipl(string("ncitrskkzaycyztczvksatezaoxgkaazzbbjqqmbvglkbifgwixqxuezzsbcijxlhngpk"), string("jdrznawdevvvhwhiqdfjytkjeheecrhfkfgdfsabxkbmjcuvmljsticalmmjxzdyikwt"), true, true, false, 3478, false, false, 3235, string("xatuiyctjbehdevoajnqvqrvhfssptuzkxgwazhvakvdligexccolmfzveefdnididmhtkrzgtxsqxkxfe"));
	this->oexsyouuglakwnimmvinbku(1324, false, false, true, string("mgdtbxcaifsqrdnqtvqcrbhzrrifvljlrepnbbiknptfvaiixgsl"), string("slurhujnzoamjjuogdkzf"));
	this->pcsiarsxosdpyscmzqvgfe();
	this->wxqaixjzoarwllczurvemhn(4283, 51853);
}
