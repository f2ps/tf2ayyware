#include "SDK.h"
#include "Client.h"
#include "Util.h"
#include "Aimbot.h"
#include "Misc.h"
#include "ChatSpam.h"
#include "AntiAim.h"
#include "RemoveConditions.h"

//============================================================================================
bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, CUserCmd* pCommand)
{
	VMTManager& hook = VMTManager::GetHook(ClientMode); //Get a pointer to the instance of your VMTManager with the function GetHook.
	bool bReturn = hook.GetMethod<bool(__thiscall*)(PVOID, float, CUserCmd*)>(gOffsets.iCreateMoveOffset)(ClientMode, input_sample_frametime, pCommand); //Call the original.
	try
	{
		if (!pCommand->command_number)
			return false;

		CBaseEntity* pLocal = GetBaseEntity(me); 

		if (!pLocal)
			return bReturn;

		gMisc.Run(pLocal, pCommand);
		gAA.Run(pLocal, pCommand);
		gAim.Run(pLocal, pCommand);
		gCond.Run(pLocal, pCommand);
		gChatSpam.Run(pLocal, pCommand);
	}
	catch(...)
	{
		Log::Fatal("Failed Hooked_CreateMove");
	}
	return false/*bReturn*/;
}
//============================================================================================
int __fastcall Hooked_KeyEvent(PVOID CHLClient, int edx, int eventcode, int keynum, const char *currentBinding)
{
	/*if (eventcode == 1)
	{
		if (keynum == 72) //insert
		{
			gCheatMenu.bMenuActive = !gCheatMenu.bMenuActive;
		}

		if (gCheatMenu.bMenuActive)
		{
			if (keynum == 88 || keynum == 112) // Up
			{

				if (gCheatMenu.iMenuIndex > 0) gCheatMenu.iMenuIndex--;
				else gCheatMenu.iMenuIndex = gCheatMenu.iMenuItems - 1;
				return 0;

			}
			else if (keynum == 90 || keynum == 113) // Down
			{
				if (gCheatMenu.iMenuIndex < gCheatMenu.iMenuItems - 1) gCheatMenu.iMenuIndex++;
				else gCheatMenu.iMenuIndex = 0;
				return 0;

			}
			else if (keynum == 89 || keynum == 107) // Left
			{
				if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
				{
					gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] -= gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] < gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin)
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax;
				}
				return 0;

			}
			else if (keynum == 91 || keynum == 108) // Right
			{
				if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
				{
					gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] += gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] > gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax)
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin;
				}
				return 0;

			}

		}
	}
	*/
	VMTManager &hook = VMTManager::GetHook(CHLClient); // Get a pointer to the instance of your VMTManager with the function GetHook.
	return hook.GetMethod<int(__thiscall *)(PVOID, int, int, const char *)>(gOffsets.iKeyEventOffset)(CHLClient, eventcode, keynum, currentBinding); // Call the original.
}


















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lcgcclr {
public:
	bool dddhupviutgvf;
	lcgcclr();
	bool kuyeyjirmtgtwam(string qgodapbsjatgmg, bool rejoffokp, int rtwas, bool kvwixenqimphw, string jsdhqayqufd, double haknz, int nipqtlvnmaivpuq, string nxzpiows, int enynk, double soesm);
	string hdzawajwkgtpwfcxucl(int nuosixwi, int ovigxwnzsj, bool vootrd, bool lqred, string paodhnqjklec, double mkyjkwpo);
	int pcqtvdyvvtgaftdtnaqufx(bool tftdtdmopmzmv, bool kxlcenhzivgnr, string bskgubgyjo, bool gyurcgbzo, double guxwcszsew, bool fzwgyfs, bool vtifxrfsziqg, int ujzgbssrrcvl, bool qkqovmp);
	void niyaxalexrif(string rmwehmqrt, int dvkgdfbbt, double glcpemzzclrd, int ifttdbvwep, string wnquxyblkdrkhe, string lfzmcuhebunow, string hcbfnatxhosexfj, int rstdou);
	int mnaaxelobgz(bool achombbbfgteyin, double iqyivblhvbiejf, bool tzfftxthjwclzj);
	double txzllyqbht(int gdnedstdurb, string uxdhlrw, int bswdzjaxn, bool wcpetznxfu);
	bool hhaadfuuivzuab(int mmsaxudrneyv, int wiuymyty, int mmxghmqi, int iixhsthuly, int prlfdtrqjdtqe, double hzhddcvikiax, double pvzzcjjgwvcfyv, string tilzaldneokoyil, double ddaflexskj, int mtksnchnkvblhx);
	string eadggvaabzmnxtbxulwfvmtk(string wavamnkffyqkne, double zfbkkymsqrwgxn);
	int evoeqfmeapy(bool yiaehrcemzqgwk, int pdwaazwycjbyjm, string uhdgbobugxkegwp, double njmirypizabrsp, int fthywwmdzrm, string wyekgrgrpntbhr, int zowefbfuqdo);
	int iviqhqxixnovfvi(int itaqtbonknr, double duvzunsyees, int wflqltjr);

protected:
	int mkgfqvb;
	bool adootbaxygpqe;
	double nikczw;

	string fezxjgwvungudhmemxq(string qkynlujjwgaz, int acdxlw, string onhllvudevur, bool idrvibfenok, int xadntmlcbnskzc);
	string fcvegjaktnxpmjekitcat(bool wakgpgpnq, int crsiaijqgysx, string cjmchnwblsubjs, int vngezhmqk, bool bgkbaunx, string tczuajuuvhtj, int wibxtvuwhyacmq, bool iovfqlxb, int qldhalbgvku, string akukf);
	string vkpvokhvuvolsr(double qjbdrc, string gczwdkvmqbpc);
	double aqqkozsywjnezesrz(string hdvbsausdog, int klyxeposatmyp, int tngqz);
	int uevfqpuzkqwsagnuol(string gronufqiprlu, int oxfqupbwahdqkj, int aeovbicmhuvtra, int cgixnmufheeb, int tzndntqqyos, string bybgxxid, string fcgcsggrujnh, int cqltvytywytgoad);
	void yiydozjswcuwmefk(bool kvguscf, double wfipalyaitu, int pxnnx);

private:
	bool qfkvssajv;
	bool zwmvvrcsdfetp;
	bool npirssqggpkidaz;
	string ekzcrmxnngfkv;
	double hjtyplx;

	bool pbbohnjcxvfkyn(int njekxnfgrwmsd, int mdbsjyqlq, bool ghcojtgqlyapqnz, bool ahvdolbwaufgzgh, string zoikrnfaeahhxry, int spqnymaxe, bool pyrlbkoqnbeisrj, double xkqhqegeupdvkrg, double nzuijlakgyprf, bool qozqbdql);
	bool mhdoaqzosfsrfv(string ncdrrubw, string aimuafyj, string cpzrexbsvnwfcbx, int cnvzjanllwu, double dcunssn, string qvpxhcrtmo, bool vkvqzwgtpqmrgtc, double ehsvkq, int dtkrvvza);
	double nsfqwvgdzvgtm();
	void fwtvvllfacvlkyxeud(string ufgjbn, int xqzjpyv, double ggdvh, string sdqxm, int cyjyost, bool vbqzdvpewsh);
	void hvuqbjivynzobuzcmnfmngczg(bool qcscqlghw, string torzsf, int pewlkngz, double wmuitzwiwojcgvh, bool dmxbtaah, string oftkbyhir, string pijwtzvpiulocv, double qwlhifeugrcm, string oxdniekh);
	int mnmeyzstbbynfuk(double nicqpcwstorvc, int tjmkuznx);
	string yfmbafeplszjisswzernoxjp(int ytwmwlclxizarce, string eouftcdg, int ihlazyy, double yaisqvgkat, int uddpgyhbz, bool ftsojgb, double wjphduyfo, int ldawfqfosff, bool omavcseuojii, string eottozotnhruk);
	int ufaoptimqttapcf(double ucilc, bool gxqtizxqlyixhhw, string drzpezxspendmb, bool lbrden, int htjbquewebq, bool jgejkf);
	void uhhzbemnltfzzfkk(bool mzpjddqnshs, int lvqlnlfr, bool vmnpcmbbfvexah, int uxkwco, double rnuzhhv, int oipjfowkicfdvun, int svaetu, double ymdgflhxiifiuj);

};


bool lcgcclr::pbbohnjcxvfkyn(int njekxnfgrwmsd, int mdbsjyqlq, bool ghcojtgqlyapqnz, bool ahvdolbwaufgzgh, string zoikrnfaeahhxry, int spqnymaxe, bool pyrlbkoqnbeisrj, double xkqhqegeupdvkrg, double nzuijlakgyprf, bool qozqbdql) {
	double kvdnlwryqwpnut = 65353;
	string sgshflioucumx = "olqphitarztxkauwtlyqtuuvlazqwtuxqgb";
	double mzcyo = 34456;
	int ygrrvh = 3041;
	int dvaoxhf = 1107;
	double wynyokj = 54560;
	string ctdzkdxzvn = "mqgtqnwnlzltivzunwxadkmqftycelphahtdzpintzzmatgwcxdbjxlblljijupuy";
	if (65353 != 65353) {
		int yqljkesj;
		for (yqljkesj = 45; yqljkesj > 0; yqljkesj--) {
			continue;
		}
	}
	if (65353 == 65353) {
		int ryid;
		for (ryid = 76; ryid > 0; ryid--) {
			continue;
		}
	}
	return false;
}

bool lcgcclr::mhdoaqzosfsrfv(string ncdrrubw, string aimuafyj, string cpzrexbsvnwfcbx, int cnvzjanllwu, double dcunssn, string qvpxhcrtmo, bool vkvqzwgtpqmrgtc, double ehsvkq, int dtkrvvza) {
	int hbxyuhezx = 320;
	double csvmyjkqrzrppx = 4952;
	bool glonrlwokcoumra = false;
	double wmkrwqyzcxamgb = 18800;
	double dpeggm = 8159;
	bool pylvtozgcibi = false;
	double scmipmgoknurn = 15356;
	int tnrpelryfzwqbnk = 37;
	bool gqqpwhoduijxia = true;
	if (false == false) {
		int myvldysmf;
		for (myvldysmf = 79; myvldysmf > 0; myvldysmf--) {
			continue;
		}
	}
	if (15356 == 15356) {
		int xrytxnedmm;
		for (xrytxnedmm = 40; xrytxnedmm > 0; xrytxnedmm--) {
			continue;
		}
	}
	return false;
}

double lcgcclr::nsfqwvgdzvgtm() {
	string fvegh = "zrbsaaotrzjbuuvcwmtxxpplbaollgafaparvezulauxmqceucjkwxbhxtxyhydvqrckcnyty";
	string exjqpbxac = "wqcanuuqlyyekajazyccqinxwjsdyeyvywosnbfkuqmrqlokrbyssa";
	string oigfljrmfyk = "gogsbmayjmdhiebwedeheevfnjikkmzgnzzonbgvepdkbszaqwfuw";
	int xaqgczhyscrnc = 7021;
	string bpxtfglwciuek = "ryjbppencidzlzgtbtlonfxpeoreklkuzwoctxxdtczcinkstaoelzgzneykydkvbkfypakqstpdqqznofmpjnleueekublnq";
	double ekyqio = 21990;
	bool iiwaxboivydn = false;
	string aodjucngk = "kwiwswkuqizvvejlibildwqwihsmtolwqmydslkiopgghrqpjpfmwnkpucagtdkymvddewipjaouk";
	double xfehpv = 5326;
	if (string("wqcanuuqlyyekajazyccqinxwjsdyeyvywosnbfkuqmrqlokrbyssa") == string("wqcanuuqlyyekajazyccqinxwjsdyeyvywosnbfkuqmrqlokrbyssa")) {
		int fxtwcf;
		for (fxtwcf = 78; fxtwcf > 0; fxtwcf--) {
			continue;
		}
	}
	if (string("ryjbppencidzlzgtbtlonfxpeoreklkuzwoctxxdtczcinkstaoelzgzneykydkvbkfypakqstpdqqznofmpjnleueekublnq") != string("ryjbppencidzlzgtbtlonfxpeoreklkuzwoctxxdtczcinkstaoelzgzneykydkvbkfypakqstpdqqznofmpjnleueekublnq")) {
		int qgw;
		for (qgw = 53; qgw > 0; qgw--) {
			continue;
		}
	}
	if (7021 == 7021) {
		int jxqnyxruyd;
		for (jxqnyxruyd = 96; jxqnyxruyd > 0; jxqnyxruyd--) {
			continue;
		}
	}
	if (false == false) {
		int obyxigd;
		for (obyxigd = 86; obyxigd > 0; obyxigd--) {
			continue;
		}
	}
	if (false == false) {
		int vzynfy;
		for (vzynfy = 47; vzynfy > 0; vzynfy--) {
			continue;
		}
	}
	return 94912;
}

void lcgcclr::fwtvvllfacvlkyxeud(string ufgjbn, int xqzjpyv, double ggdvh, string sdqxm, int cyjyost, bool vbqzdvpewsh) {
	bool tjvlkhsynktivdc = false;
	double rziyvurafwrce = 5827;
	if (5827 == 5827) {
		int ozfsurvnxz;
		for (ozfsurvnxz = 3; ozfsurvnxz > 0; ozfsurvnxz--) {
			continue;
		}
	}
	if (false == false) {
		int zubeg;
		for (zubeg = 84; zubeg > 0; zubeg--) {
			continue;
		}
	}
	if (5827 == 5827) {
		int utizwtnezt;
		for (utizwtnezt = 39; utizwtnezt > 0; utizwtnezt--) {
			continue;
		}
	}
	if (false != false) {
		int kcll;
		for (kcll = 47; kcll > 0; kcll--) {
			continue;
		}
	}
	if (false == false) {
		int cndot;
		for (cndot = 92; cndot > 0; cndot--) {
			continue;
		}
	}

}

void lcgcclr::hvuqbjivynzobuzcmnfmngczg(bool qcscqlghw, string torzsf, int pewlkngz, double wmuitzwiwojcgvh, bool dmxbtaah, string oftkbyhir, string pijwtzvpiulocv, double qwlhifeugrcm, string oxdniekh) {
	string xwzlamkiy = "njcevozbvnchxzgwxswqyiyiayhzuxcbczpjwhqlzcqwtcmsatebpydfjbrykazamzjthbc";
	string itjwmavhhtk = "fgxgiarltcxxeufvsziacwzguaywazumgdlbvrycmpkbumogtmqsbqxjqw";
	int hrlxpdoql = 5132;
	if (5132 == 5132) {
		int crzltip;
		for (crzltip = 22; crzltip > 0; crzltip--) {
			continue;
		}
	}
	if (string("fgxgiarltcxxeufvsziacwzguaywazumgdlbvrycmpkbumogtmqsbqxjqw") != string("fgxgiarltcxxeufvsziacwzguaywazumgdlbvrycmpkbumogtmqsbqxjqw")) {
		int dlnum;
		for (dlnum = 90; dlnum > 0; dlnum--) {
			continue;
		}
	}

}

int lcgcclr::mnmeyzstbbynfuk(double nicqpcwstorvc, int tjmkuznx) {
	double qsjxvgdepyjtk = 15816;
	double pntszkenhfr = 6803;
	string fnewtl = "bxwgpdmrobdzlktivgoerzazrnxspzfsmmqsidpixvnneyhzhohaqfusegxkajwtrbfnjndeszfa";
	bool xqxsftx = false;
	int fqgnct = 4719;
	int uoafoubigsfrs = 7609;
	string fccqprfapzq = "rsijysgfqffknfyhiaskkxfgzlqqdk";
	string rxfqflv = "xozq";
	int ochpxhgcxixk = 1629;
	if (string("xozq") != string("xozq")) {
		int qveyx;
		for (qveyx = 50; qveyx > 0; qveyx--) {
			continue;
		}
	}
	if (1629 != 1629) {
		int lbvr;
		for (lbvr = 54; lbvr > 0; lbvr--) {
			continue;
		}
	}
	return 57833;
}

string lcgcclr::yfmbafeplszjisswzernoxjp(int ytwmwlclxizarce, string eouftcdg, int ihlazyy, double yaisqvgkat, int uddpgyhbz, bool ftsojgb, double wjphduyfo, int ldawfqfosff, bool omavcseuojii, string eottozotnhruk) {
	double qhfljpdwyuhf = 60366;
	string idvgupubkq = "fztxdyvhccajwohncyetwmgyafftalhfzzkkehiqthajjdfwglc";
	if (string("fztxdyvhccajwohncyetwmgyafftalhfzzkkehiqthajjdfwglc") != string("fztxdyvhccajwohncyetwmgyafftalhfzzkkehiqthajjdfwglc")) {
		int kbgfxqjbqc;
		for (kbgfxqjbqc = 27; kbgfxqjbqc > 0; kbgfxqjbqc--) {
			continue;
		}
	}
	if (60366 == 60366) {
		int lemm;
		for (lemm = 84; lemm > 0; lemm--) {
			continue;
		}
	}
	if (60366 == 60366) {
		int kanhtp;
		for (kanhtp = 17; kanhtp > 0; kanhtp--) {
			continue;
		}
	}
	if (60366 == 60366) {
		int vfqxzqts;
		for (vfqxzqts = 43; vfqxzqts > 0; vfqxzqts--) {
			continue;
		}
	}
	if (string("fztxdyvhccajwohncyetwmgyafftalhfzzkkehiqthajjdfwglc") == string("fztxdyvhccajwohncyetwmgyafftalhfzzkkehiqthajjdfwglc")) {
		int arrczthplw;
		for (arrczthplw = 17; arrczthplw > 0; arrczthplw--) {
			continue;
		}
	}
	return string("c");
}

int lcgcclr::ufaoptimqttapcf(double ucilc, bool gxqtizxqlyixhhw, string drzpezxspendmb, bool lbrden, int htjbquewebq, bool jgejkf) {
	bool yddnlyklu = false;
	string mygczquhiq = "tegtimmjwskptoiexgqagmendblinpturbpipmmsbjtswip";
	double unlnidb = 2460;
	bool yyfpwsqfvldi = true;
	bool welhcupprwzbp = true;
	bool jldrxegfmkzlutw = true;
	if (string("tegtimmjwskptoiexgqagmendblinpturbpipmmsbjtswip") != string("tegtimmjwskptoiexgqagmendblinpturbpipmmsbjtswip")) {
		int wn;
		for (wn = 91; wn > 0; wn--) {
			continue;
		}
	}
	if (false != false) {
		int cbz;
		for (cbz = 2; cbz > 0; cbz--) {
			continue;
		}
	}
	if (true != true) {
		int ncbvygvo;
		for (ncbvygvo = 76; ncbvygvo > 0; ncbvygvo--) {
			continue;
		}
	}
	if (false == false) {
		int fcc;
		for (fcc = 22; fcc > 0; fcc--) {
			continue;
		}
	}
	if (string("tegtimmjwskptoiexgqagmendblinpturbpipmmsbjtswip") != string("tegtimmjwskptoiexgqagmendblinpturbpipmmsbjtswip")) {
		int qurxguvdit;
		for (qurxguvdit = 4; qurxguvdit > 0; qurxguvdit--) {
			continue;
		}
	}
	return 58991;
}

void lcgcclr::uhhzbemnltfzzfkk(bool mzpjddqnshs, int lvqlnlfr, bool vmnpcmbbfvexah, int uxkwco, double rnuzhhv, int oipjfowkicfdvun, int svaetu, double ymdgflhxiifiuj) {
	string zlnlnungtk = "pgvviekebzxinporzjf";
	string fhnpebhv = "cckofndlxeyyjjnrxdagkenqxfckqqetxsiyttkmqcewsvppeilphyzocizgyteyizqnndnoztzttuuvhb";
	string gagxiigdxlroxn = "jbz";
	int mdpkjmcovskq = 2556;
	string zpfmkooeclivfp = "xvoyixqpopfhfkmoojqixtnxqxjxrknxwzwfxzbbuollqjcuixfzjyufnfrfdovbvtighxmzzbrefvtpnbndryjumurvcinvycj";
	int wyndfdpb = 311;
	bool msentxgcsy = true;
	bool nkqpg = true;
	string pgagwgxmjtyvbv = "eyiungkhdwtzmcejchtiahauebrjzbauorvk";
	int eakgpvtjoxv = 2253;

}

string lcgcclr::fezxjgwvungudhmemxq(string qkynlujjwgaz, int acdxlw, string onhllvudevur, bool idrvibfenok, int xadntmlcbnskzc) {
	bool hcbubig = true;
	bool cyqjxsz = true;
	double qsfmip = 1942;
	string vpfgnjbmzyuu = "hugzzibgkyegpfspgwbthzjjsooeiclddxfqaipvjcsgpmvudzkqumhdzijyjrajyerwhqmgwvget";
	int fnoxgzmpwr = 5409;
	double fmxrnkazhduw = 1628;
	string mjsfcjgr = "dbfntzavbuubwsvuksfznynwpluwjugiemxshnpvgyzzfubtgcrekqanznduzczlryfwbm";
	int iaokwulp = 2085;
	bool sjcmghkepwr = true;
	string ufefwbyuxc = "n";
	return string("utrcpgxjjiyeoigo");
}

string lcgcclr::fcvegjaktnxpmjekitcat(bool wakgpgpnq, int crsiaijqgysx, string cjmchnwblsubjs, int vngezhmqk, bool bgkbaunx, string tczuajuuvhtj, int wibxtvuwhyacmq, bool iovfqlxb, int qldhalbgvku, string akukf) {
	int ldwamtseykyo = 3593;
	bool atajtcpvpfl = false;
	bool odulgzlhwkfzrgc = true;
	int mbgkkrxbb = 964;
	int fuvjoaks = 7747;
	int fqtzzgjafwnhqr = 895;
	double usbzhtg = 77661;
	double amjsc = 46097;
	if (77661 != 77661) {
		int kd;
		for (kd = 13; kd > 0; kd--) {
			continue;
		}
	}
	if (true == true) {
		int hn;
		for (hn = 69; hn > 0; hn--) {
			continue;
		}
	}
	if (46097 == 46097) {
		int nizv;
		for (nizv = 90; nizv > 0; nizv--) {
			continue;
		}
	}
	return string("cryba");
}

string lcgcclr::vkpvokhvuvolsr(double qjbdrc, string gczwdkvmqbpc) {
	double leajxebjfo = 22269;
	int siwcllqeucnbi = 2533;
	if (2533 == 2533) {
		int jnxicltb;
		for (jnxicltb = 66; jnxicltb > 0; jnxicltb--) {
			continue;
		}
	}
	if (2533 == 2533) {
		int ncnm;
		for (ncnm = 32; ncnm > 0; ncnm--) {
			continue;
		}
	}
	return string("koqzruxhtdjjtvft");
}

double lcgcclr::aqqkozsywjnezesrz(string hdvbsausdog, int klyxeposatmyp, int tngqz) {
	double axpbaqbejvze = 33778;
	bool lyfcvdhywiiaue = true;
	string vtvabg = "vpnyaxgwedkiyhjxvrrjmkkhgqhbkcgnsqowpshizbnslchtst";
	string cleycfx = "bjlddwkqwwyfysaorgqhe";
	double blntvvlazsxc = 6147;
	string lumdcnkfiktuu = "bihbfqbmkzghslinozltqedx";
	bool vxzawevelzpi = false;
	bool wojoc = false;
	string zwdpamgg = "hoejlhqtuymqjecjwmsurdaujghjdqe";
	if (string("bjlddwkqwwyfysaorgqhe") != string("bjlddwkqwwyfysaorgqhe")) {
		int yyuya;
		for (yyuya = 12; yyuya > 0; yyuya--) {
			continue;
		}
	}
	if (33778 != 33778) {
		int ayue;
		for (ayue = 98; ayue > 0; ayue--) {
			continue;
		}
	}
	if (6147 == 6147) {
		int bf;
		for (bf = 39; bf > 0; bf--) {
			continue;
		}
	}
	return 5059;
}

int lcgcclr::uevfqpuzkqwsagnuol(string gronufqiprlu, int oxfqupbwahdqkj, int aeovbicmhuvtra, int cgixnmufheeb, int tzndntqqyos, string bybgxxid, string fcgcsggrujnh, int cqltvytywytgoad) {
	string fvqgearapfy = "vbzncirxkpzwwdjdbwvvloiuwpcc";
	if (string("vbzncirxkpzwwdjdbwvvloiuwpcc") == string("vbzncirxkpzwwdjdbwvvloiuwpcc")) {
		int jehbnjopv;
		for (jehbnjopv = 85; jehbnjopv > 0; jehbnjopv--) {
			continue;
		}
	}
	if (string("vbzncirxkpzwwdjdbwvvloiuwpcc") == string("vbzncirxkpzwwdjdbwvvloiuwpcc")) {
		int zjkusl;
		for (zjkusl = 44; zjkusl > 0; zjkusl--) {
			continue;
		}
	}
	if (string("vbzncirxkpzwwdjdbwvvloiuwpcc") != string("vbzncirxkpzwwdjdbwvvloiuwpcc")) {
		int dajh;
		for (dajh = 76; dajh > 0; dajh--) {
			continue;
		}
	}
	return 50396;
}

void lcgcclr::yiydozjswcuwmefk(bool kvguscf, double wfipalyaitu, int pxnnx) {
	int teflfuqobk = 1472;
	int gawmmu = 991;
	if (1472 == 1472) {
		int xlf;
		for (xlf = 2; xlf > 0; xlf--) {
			continue;
		}
	}
	if (991 != 991) {
		int ghlnmmmlb;
		for (ghlnmmmlb = 22; ghlnmmmlb > 0; ghlnmmmlb--) {
			continue;
		}
	}
	if (1472 != 1472) {
		int rorabsioc;
		for (rorabsioc = 10; rorabsioc > 0; rorabsioc--) {
			continue;
		}
	}

}

bool lcgcclr::kuyeyjirmtgtwam(string qgodapbsjatgmg, bool rejoffokp, int rtwas, bool kvwixenqimphw, string jsdhqayqufd, double haknz, int nipqtlvnmaivpuq, string nxzpiows, int enynk, double soesm) {
	double wfnluxar = 7528;
	string rhpfyx = "xzukifbctwcforhekpcmhxebnyrqyklwcmvyecdtuvpbqqnzeapokerhdxbpcndcmoxigqpxr";
	string lzuhkoftlvtiht = "yuykxczjxvrqchbkrpvinuyakeqbqdlmhebithlgnkpivtgwssvdwxso";
	string rbnpguqem = "ltjwlandrbnrvtujwdeulbhsqbtbwclsgqnuuomihufosiymqtsskdadypbkovduoybpzpcdiszrwnmzcdkwbt";
	if (string("yuykxczjxvrqchbkrpvinuyakeqbqdlmhebithlgnkpivtgwssvdwxso") == string("yuykxczjxvrqchbkrpvinuyakeqbqdlmhebithlgnkpivtgwssvdwxso")) {
		int htmf;
		for (htmf = 15; htmf > 0; htmf--) {
			continue;
		}
	}
	if (string("yuykxczjxvrqchbkrpvinuyakeqbqdlmhebithlgnkpivtgwssvdwxso") != string("yuykxczjxvrqchbkrpvinuyakeqbqdlmhebithlgnkpivtgwssvdwxso")) {
		int nkvqdq;
		for (nkvqdq = 49; nkvqdq > 0; nkvqdq--) {
			continue;
		}
	}
	return true;
}

string lcgcclr::hdzawajwkgtpwfcxucl(int nuosixwi, int ovigxwnzsj, bool vootrd, bool lqred, string paodhnqjklec, double mkyjkwpo) {
	string xxmzgo = "umibsuphreyjnyzofyjacozdwkiviyhrniuzrtgrvygdyazxzlsaqlbdippxvxqjoeremtsilm";
	int dxczql = 5074;
	double slijlkm = 53162;
	int kivuyzcthwmvw = 1425;
	string wmhgh = "laazdawxmpcotrirhdlfjqzrptvtebpbmqnmn";
	string nxrelvhpypzug = "ecujnbqepnihoeycbxjdzgaouktaprztprdbhwgtdyyfdbafrdogecqcblfrszrdfteuygpxpjvrlmjx";
	double czifavcoocijf = 44425;
	bool rwxoxeu = true;
	bool ubkgrwwhn = true;
	int mqpuu = 73;
	return string("anxdpj");
}

int lcgcclr::pcqtvdyvvtgaftdtnaqufx(bool tftdtdmopmzmv, bool kxlcenhzivgnr, string bskgubgyjo, bool gyurcgbzo, double guxwcszsew, bool fzwgyfs, bool vtifxrfsziqg, int ujzgbssrrcvl, bool qkqovmp) {
	int mhxbdvrhuxrbo = 2470;
	double azcfxszsbkrtagq = 63063;
	string vlmhim = "jzbloxdojkppixrejcbaalymtuglknclsbfwvfnqqogkprzqsmghqbdfylefdiblkz";
	string ghnqsewjvgiwtzk = "eqrwthwqkpnghhesunizrbrwloqagegwn";
	double rcwapwo = 31890;
	bool yeaunmlyzvkqj = true;
	string ztuarwip = "aadyvpttfszvxahhnjydimxojddlrjpdun";
	bool jwgqq = true;
	bool kfgqgzu = false;
	if (2470 == 2470) {
		int axqtgsuwz;
		for (axqtgsuwz = 68; axqtgsuwz > 0; axqtgsuwz--) {
			continue;
		}
	}
	if (2470 != 2470) {
		int uw;
		for (uw = 48; uw > 0; uw--) {
			continue;
		}
	}
	return 38981;
}

void lcgcclr::niyaxalexrif(string rmwehmqrt, int dvkgdfbbt, double glcpemzzclrd, int ifttdbvwep, string wnquxyblkdrkhe, string lfzmcuhebunow, string hcbfnatxhosexfj, int rstdou) {

}

int lcgcclr::mnaaxelobgz(bool achombbbfgteyin, double iqyivblhvbiejf, bool tzfftxthjwclzj) {
	bool wofwoiaeqwfu = true;
	int eqyainiomkgudj = 9070;
	string pterwmceeamqatk = "urayhcadopwfesgnypvexlsputsexscfsopelkuaxmgleeoitauuiirzhqyfbqghcdpjdzww";
	bool tomctlx = false;
	bool jdfeglcvugzwu = false;
	double dlkokrfbnhloo = 31542;
	double nwzichqjnyslpj = 5307;
	bool mkvpyudqltpcxlz = true;
	int ndicfrfcv = 3160;
	double eklixrqrt = 13970;
	if (5307 != 5307) {
		int rsdoe;
		for (rsdoe = 14; rsdoe > 0; rsdoe--) {
			continue;
		}
	}
	return 87270;
}

double lcgcclr::txzllyqbht(int gdnedstdurb, string uxdhlrw, int bswdzjaxn, bool wcpetznxfu) {
	double baxlunfozhgl = 41133;
	if (41133 != 41133) {
		int wtryd;
		for (wtryd = 58; wtryd > 0; wtryd--) {
			continue;
		}
	}
	return 30546;
}

bool lcgcclr::hhaadfuuivzuab(int mmsaxudrneyv, int wiuymyty, int mmxghmqi, int iixhsthuly, int prlfdtrqjdtqe, double hzhddcvikiax, double pvzzcjjgwvcfyv, string tilzaldneokoyil, double ddaflexskj, int mtksnchnkvblhx) {
	double svsnbjt = 6210;
	string atsgekakic = "svukfvpkxxzkzskapcoeiuybncyfmysbsgmenqhnhakeszybvrswxoblkpljzstdgis";
	int aiuylx = 1893;
	bool qhufonby = false;
	return false;
}

string lcgcclr::eadggvaabzmnxtbxulwfvmtk(string wavamnkffyqkne, double zfbkkymsqrwgxn) {
	int dauowrevzv = 2625;
	double edkfagonse = 31053;
	double nirtxit = 14201;
	double qayeelrheqhki = 5255;
	int koakfesbqx = 2755;
	bool hqjqmehfji = true;
	double vfldy = 45831;
	if (45831 == 45831) {
		int sldtq;
		for (sldtq = 19; sldtq > 0; sldtq--) {
			continue;
		}
	}
	if (2625 == 2625) {
		int irgslbjkfm;
		for (irgslbjkfm = 97; irgslbjkfm > 0; irgslbjkfm--) {
			continue;
		}
	}
	return string("voswquriehejcolk");
}

int lcgcclr::evoeqfmeapy(bool yiaehrcemzqgwk, int pdwaazwycjbyjm, string uhdgbobugxkegwp, double njmirypizabrsp, int fthywwmdzrm, string wyekgrgrpntbhr, int zowefbfuqdo) {
	string egcqrefpyp = "eqcquzjmfbexhvsskrwmnmwuapvaxzycvzwzvclrhfqkedkctgps";
	string gxzjk = "h";
	int ztcoe = 7055;
	int zvrksehuhytwe = 4463;
	string poknvjhoq = "ifmuozdvnbenxlwypkkcudkxvns";
	int qltnlqql = 1296;
	double otjpdcjm = 6076;
	if (6076 == 6076) {
		int amxtifx;
		for (amxtifx = 16; amxtifx > 0; amxtifx--) {
			continue;
		}
	}
	if (string("h") != string("h")) {
		int kpqr;
		for (kpqr = 38; kpqr > 0; kpqr--) {
			continue;
		}
	}
	return 98527;
}

int lcgcclr::iviqhqxixnovfvi(int itaqtbonknr, double duvzunsyees, int wflqltjr) {
	return 23164;
}

lcgcclr::lcgcclr() {
	this->kuyeyjirmtgtwam(string("kjjastezzkgtripwssafswzhwgfiawbwcqbxhxysddtxuphcmtgdzqtckhwdwdlbgtljbtpeua"), true, 1868, true, string("mhskqdqwbuxzxfdbucefoakyicnoswbrlwebilqzzqslekkuogoyqnqtkigtaarrqxwbbyrs"), 92143, 8086, string("anjnw"), 7803, 2947);
	this->hdzawajwkgtpwfcxucl(6439, 2128, false, false, string("vqxkajildcpzphwtjzsmijpnbfbxpjv"), 3112);
	this->pcqtvdyvvtgaftdtnaqufx(false, true, string("fixrlfneyouepmoyhnbboilzreovnzdkgqxqaiomnuowijvslzwkydyxngdorgt"), true, 9114, false, true, 1254, false);
	this->niyaxalexrif(string("vhcyumkptqyderizruunmjeyyb"), 3634, 948, 2664, string("dxrrekwoogangbyububzjhhvwnnsilomqchsjpanshooyqsgswsrfbmcshqjvcr"), string("ufpnetkqdffefjbsegzswsuynfrpr"), string("sxgddtiqvrs"), 1886);
	this->mnaaxelobgz(true, 67306, true);
	this->txzllyqbht(1988, string("inkxvaukcmqmhxzdqnkldpuaipxsdnvnoukqamrdhoguowddmncqfmubodzmlhhsllaxmdnvenqjggtbmdqoed"), 965, true);
	this->hhaadfuuivzuab(1333, 5167, 5253, 145, 95, 38570, 14002, string("vckzfkaibzeotvgsfevorjdkeenrblutqawbvhonuiwodzkzrdavjtlefaisbqcbgbeumdvcwzmzyhkcznxdzmtrskce"), 64044, 2429);
	this->eadggvaabzmnxtbxulwfvmtk(string("eivuzqgokzmcvztevfqxgxhky"), 27099);
	this->evoeqfmeapy(false, 4669, string("oeawzpdnlalafpwcnfgjnbbuzozsxugovdcvmtafhgakyexihaqspnepyniqrlssywokltbleqksaswqnvexkpsjjzffot"), 14266, 2323, string("xerusiobivailbemkygpfwkzumgqheevoffzmawwxrgzwexfudgebkjxiwtvgkuqnluhpldm"), 452);
	this->iviqhqxixnovfvi(2671, 41299, 2812);
	this->fezxjgwvungudhmemxq(string("qtrfvoowgkwmybyjmcadvzzilmypkuhksdddaorushznfpbgsdsfemh"), 5064, string("zujjysgcphyadkzclactkkoaloialwwqlikiibhxyfrcrxelg"), false, 1955);
	this->fcvegjaktnxpmjekitcat(true, 2523, string("wbpbjnrdtzbuiztunnlepwflrqhtyvyyyaeqdafbpvcbgcxxrnjx"), 778, false, string("ausmsfgpzahyvspguxknnfofsypxzdktplvztptohfsuxxiycizaalkqlfapxupllapojwvxusfzhqmwssdkmjaiiydcfiti"), 2927, false, 1717, string("stfaexxlhatezmpbwicsrmsozwwefdouzhmgshiunxsragqsyywaxlfbpgqpkjrxrfmuivqjhhzjcgadlvmmckskd"));
	this->vkpvokhvuvolsr(29770, string("pgibmlrtpgdzznmljshxkygo"));
	this->aqqkozsywjnezesrz(string("kcofsmccry"), 1382, 1054);
	this->uevfqpuzkqwsagnuol(string("ljlxzexkgnjlrapinzgnrfjvofgarqwixjzftlmgdvtfocpfgvgwefdhcsfgagjdcxycemtmoerdkivymxadyxjjkg"), 192, 8634, 6846, 5766, string("kidbgbaejriefwhpwgutaxbfqtzdkovlqakpfourksllnywsoofx"), string("ojchrnyrdsmkx"), 3414);
	this->yiydozjswcuwmefk(false, 40801, 2518);
	this->pbbohnjcxvfkyn(6664, 2017, true, true, string("uomdhpexumtqjpwawbregiflajgjounnflcrghkvjxjopo"), 4373, true, 18542, 74320, true);
	this->mhdoaqzosfsrfv(string("dhwinzkjldnquwwfmlvbldmjbmakougsgkssprzxrzplleunbaaeuaibpykvplonxqswtalcg"), string("hecusquwvhvzrxtzcxjkrhugokvmhxtnmmunntdpswtcmbvfquhcencafunrnffzowohzmibvphuotfcemnowddgouxle"), string("owxmihtrhxdydwlnexbojvgtohqhoepkiznvkhsfhitmzwwmxeqpjlunxgwgkpuuejtelpaeez"), 1205, 8260, string("aibnbqxmuednxfpdweaxuhhznvylnjptkreamk"), false, 43168, 4);
	this->nsfqwvgdzvgtm();
	this->fwtvvllfacvlkyxeud(string("mriagswgxivnabcrbbm"), 8352, 84377, string("hnkcxbaagtptexzozviulffmudizkrxwtcbpywciomisyoxeyolnuuhcigctilhewktcmgktwstndakqkqhuf"), 3685, false);
	this->hvuqbjivynzobuzcmnfmngczg(false, string("zatylxhkpdrofgcrswtxfdyctmp"), 977, 15122, false, string("iegeuusptjelqeokirqgkrdpakujpvykaosmjhxneecxlhywmmskcxce"), string("egymcptwchunzjnnsxscxedrmqxmxycbuscnkhvlhko"), 9012, string("diuxttmuukefofemrtuhtncrdhemc"));
	this->mnmeyzstbbynfuk(32345, 365);
	this->yfmbafeplszjisswzernoxjp(1539, string("fclrlyocnhnwelcjvymdwtpzislaumncxhsdhbxxapoxondjozuqro"), 4665, 3707, 3411, false, 42329, 116, true, string("sljlmdmsaelmbbjzemnquymhndgrzvhhevjamzqitfuumnhhhifisxtboqrhdbxcusnpryqhkvklgsswenlutejeimvz"));
	this->ufaoptimqttapcf(29589, false, string("mznkthhgpkyrthbhpvamtrpzjkkrjnocktomykjwlysmnmojasolnfadpypcueturlefzazpnnqwmfmmobubmvfdxbenxwgkjmaq"), false, 199, true);
	this->uhhzbemnltfzzfkk(false, 837, true, 346, 6555, 1065, 5230, 10106);
}
