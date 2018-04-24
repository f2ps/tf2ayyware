#include "sdk.h"
#include <time.h>

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

DWORD CSignature::dwFindPattern(DWORD dwAddress, DWORD dwLength, const char* szPattern)
{
	const char* pat = szPattern;
	DWORD firstMatch = NULL;
	for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else {
			pat = szPattern;
			firstMatch = 0;
		}
	}
	return NULL;
}
//===================================================================================
HMODULE CSignature::GetModuleHandleSafe( const char* pszModuleName )
{
	HMODULE hmModuleHandle = NULL;

	do
	{
		hmModuleHandle = GetModuleHandle( pszModuleName );
		Sleep( 1 );
	}
	while(hmModuleHandle == NULL);

	return hmModuleHandle;
}
//===================================================================================
DWORD CSignature::GetClientSignature(char* chPattern)
{
	static HMODULE hmModule = GetModuleHandleSafe("client.dll");
	static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
	return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
}
//===================================================================================
DWORD CSignature::GetEngineSignature(char* chPattern)
{
	static HMODULE hmModule = GetModuleHandleSafe("engine.dll");
	static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
	return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
}

CSignature gSignatures;



















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class phsydvu {
public:
	double wtetwpq;
	int znglizblyyjyt;
	phsydvu();
	void wyweyanwqv(bool nholmwxqysxn, bool rdaxuetttd, double zycnadqh, int jyvfnzs, double ssuspl, bool kukopwgrof, double ediqvnammexqr, bool howvqopldrc);
	bool hiusxutjlld(double fsmbdfvq, int nrmka, int chixxdynctav);

protected:
	string ziiusvayyrerq;
	double fxubce;
	bool bwpxipm;
	string ufpoikwexdx;
	bool czqelquckfxr;

	bool xpfebilpycugd(double tjovrebctprytse, string atzfqlotrbjh, int mwucvjmgbhnltv, double qjnkk, string pbpkwryxabdsq, int umovkofitbhu, string llawdpc, bool penaieic, string uhpbvanvrpujwq);
	string bkwtqkuwtcmufxxvbgfgxhpo(string rlgtqsfqnrgmxoy, bool gxemvaupxs, double skfkesx, string hxfbzqerlces, int etzntcvenchbrl, double beimgwd, double xqbcxojf, int iqcdakrqgha);
	string pcestcnhvdlcdlyadoyf(int dzuovbh, string qzbfmrsbyk, string trfobafuzp, bool xqoees);
	int oevbxggfmtudsqabaqxcvhaof(int gudoynltiand, bool lsrjbeevc, string ukbdhacttlykt, double pxkyk, bool lbxhclcmxgw, string wwasvuokpfnwyuq, string pxxhsptr, int cdmtfrjwuzx);
	string gztiwfpsbraxykrmpvi(string qwjdxewa, int iveuhzmewvrtz, double kdkzi, double xfmeovmzeqiqs, double lyifehrtu, string zzfwvnxooxvkl, string dhflnvnsanevag, int gaveipvsuax, bool qablglchdmyvu, bool magdtqdzsp);
	double ggugzyuyjpvvtrapjuoskvw(int adwahysirn);
	int mzzmjsjhfwnt(string ixkueg);
	bool yghuhlkchcgik();
	int brcifrvvyzmurmprjpbziw(int qdmmmhfy, bool uafniardvg, int sjtojpilt, string hymxjteqftlrde, int gkujnvqno, string iuyqqhfuyspinu, double wglmta, bool icqgbvmnpaelmgk, string rczcaqynkdsr, double suzpaodaloxnjb);
	double ptmkazqqidjzqylcmly();

private:
	string uurkgs;
	string jxwebwwtbgetpag;
	string xmfqtecqoijp;

	string nyklmcuahsfsktormkh(bool vqewkooijxnaozx, bool edrbbb, bool bnanviepc, double nulnm, double crasju);

};


string phsydvu::nyklmcuahsfsktormkh(bool vqewkooijxnaozx, bool edrbbb, bool bnanviepc, double nulnm, double crasju) {
	return string("gxsnn");
}

bool phsydvu::xpfebilpycugd(double tjovrebctprytse, string atzfqlotrbjh, int mwucvjmgbhnltv, double qjnkk, string pbpkwryxabdsq, int umovkofitbhu, string llawdpc, bool penaieic, string uhpbvanvrpujwq) {
	double dxvfobizuapn = 9030;
	bool djybklooaqyygt = true;
	double qtoqotienazwvex = 33041;
	bool yevzci = false;
	double kegvdup = 42209;
	bool qssou = true;
	string ezqfadcjhkc = "fnjddxgojuyeszsexniodrno";
	bool fbhogsttkirfb = false;
	bool dbewxuwwxslawft = true;
	string vxczdjgearijk = "myghgciitncltwqpuecvarvqmudatxqzsowgmhrn";
	if (true != true) {
		int kobxtsjm;
		for (kobxtsjm = 20; kobxtsjm > 0; kobxtsjm--) {
			continue;
		}
	}
	if (33041 != 33041) {
		int kiihslcwp;
		for (kiihslcwp = 4; kiihslcwp > 0; kiihslcwp--) {
			continue;
		}
	}
	if (false != false) {
		int ehaqowa;
		for (ehaqowa = 27; ehaqowa > 0; ehaqowa--) {
			continue;
		}
	}
	if (string("fnjddxgojuyeszsexniodrno") != string("fnjddxgojuyeszsexniodrno")) {
		int az;
		for (az = 10; az > 0; az--) {
			continue;
		}
	}
	return false;
}

string phsydvu::bkwtqkuwtcmufxxvbgfgxhpo(string rlgtqsfqnrgmxoy, bool gxemvaupxs, double skfkesx, string hxfbzqerlces, int etzntcvenchbrl, double beimgwd, double xqbcxojf, int iqcdakrqgha) {
	string jsrlpzbzygijyna = "pjqbpyyaelqtiounzktzppwzimefkrqdgvmttpklzdhxjqnjgaklhkeejkh";
	string yvgwrajoi = "zpchgmdvczlcooxom";
	int lunoqjltsyydu = 3105;
	if (3105 == 3105) {
		int rs;
		for (rs = 15; rs > 0; rs--) {
			continue;
		}
	}
	return string("iptliwp");
}

string phsydvu::pcestcnhvdlcdlyadoyf(int dzuovbh, string qzbfmrsbyk, string trfobafuzp, bool xqoees) {
	bool jnxnpmgw = true;
	bool sdsxws = true;
	int quhwbtuecpu = 1469;
	bool qkuxugoghuzt = false;
	int gbdiqrbyepp = 4360;
	bool dfciqkjih = true;
	int fyzgycltg = 5326;
	bool cnsjpgc = false;
	string wfdgzcpqezqe = "kvqbdttbqxittcwnlxvjhutseemdjxvkgcqxlcyuab";
	return string("blpzeop");
}

int phsydvu::oevbxggfmtudsqabaqxcvhaof(int gudoynltiand, bool lsrjbeevc, string ukbdhacttlykt, double pxkyk, bool lbxhclcmxgw, string wwasvuokpfnwyuq, string pxxhsptr, int cdmtfrjwuzx) {
	double sxtgrtpfmqkfafv = 483;
	int cqwdljxnouny = 879;
	bool unjhrtthxlqy = true;
	int tnixjsznp = 4888;
	bool idjlneu = true;
	int kaqltloyrbchm = 7049;
	bool zlfqsfdisnsjlb = false;
	if (false != false) {
		int xdiai;
		for (xdiai = 58; xdiai > 0; xdiai--) {
			continue;
		}
	}
	if (false == false) {
		int dnfupzlws;
		for (dnfupzlws = 57; dnfupzlws > 0; dnfupzlws--) {
			continue;
		}
	}
	if (7049 != 7049) {
		int pby;
		for (pby = 73; pby > 0; pby--) {
			continue;
		}
	}
	return 74486;
}

string phsydvu::gztiwfpsbraxykrmpvi(string qwjdxewa, int iveuhzmewvrtz, double kdkzi, double xfmeovmzeqiqs, double lyifehrtu, string zzfwvnxooxvkl, string dhflnvnsanevag, int gaveipvsuax, bool qablglchdmyvu, bool magdtqdzsp) {
	bool mjfxfqvfz = true;
	bool qiqsghhu = true;
	bool kmodwugesrdzv = true;
	int affjyseaubhxvj = 103;
	int gwasaxebdklr = 69;
	bool mfpsw = false;
	string xhjdhturj = "yakobuxzqfaaec";
	double mjrmw = 17336;
	if (69 != 69) {
		int uy;
		for (uy = 17; uy > 0; uy--) {
			continue;
		}
	}
	return string("ahwcbgj");
}

double phsydvu::ggugzyuyjpvvtrapjuoskvw(int adwahysirn) {
	double fbdpktxk = 50111;
	string cgpaz = "ifhvlriw";
	if (50111 == 50111) {
		int etydmibu;
		for (etydmibu = 91; etydmibu > 0; etydmibu--) {
			continue;
		}
	}
	if (50111 != 50111) {
		int lj;
		for (lj = 8; lj > 0; lj--) {
			continue;
		}
	}
	return 79215;
}

int phsydvu::mzzmjsjhfwnt(string ixkueg) {
	string twvugfvdkiy = "fpxrfomrtqsqkhydodikebvksyhaakygifxavlllxfcdbqtgizxenfgieqqr";
	double wfjathguj = 23756;
	if (string("fpxrfomrtqsqkhydodikebvksyhaakygifxavlllxfcdbqtgizxenfgieqqr") != string("fpxrfomrtqsqkhydodikebvksyhaakygifxavlllxfcdbqtgizxenfgieqqr")) {
		int rujzhbyy;
		for (rujzhbyy = 35; rujzhbyy > 0; rujzhbyy--) {
			continue;
		}
	}
	return 41772;
}

bool phsydvu::yghuhlkchcgik() {
	int fcwgxtfk = 3310;
	int wxtchliygiepdm = 2081;
	int jhyttwpacdd = 3292;
	string mvzbiniwlbe = "gmnzxklqeupdpzdnjmknowpbhcuyyjjqxrfwtbwvkxttf";
	string hjwuhvclktgpirj = "kdwqhjczaxdcykwssxjdoocawiex";
	bool ouqhfnl = false;
	double yogkfhxo = 65522;
	string zrmig = "rwafiassgbjepinnoqwvdsrvklmlvwvleplylnegec";
	double flqwtmffjxzu = 5062;
	if (65522 == 65522) {
		int yfw;
		for (yfw = 79; yfw > 0; yfw--) {
			continue;
		}
	}
	if (string("rwafiassgbjepinnoqwvdsrvklmlvwvleplylnegec") == string("rwafiassgbjepinnoqwvdsrvklmlvwvleplylnegec")) {
		int vlty;
		for (vlty = 62; vlty > 0; vlty--) {
			continue;
		}
	}
	return false;
}

int phsydvu::brcifrvvyzmurmprjpbziw(int qdmmmhfy, bool uafniardvg, int sjtojpilt, string hymxjteqftlrde, int gkujnvqno, string iuyqqhfuyspinu, double wglmta, bool icqgbvmnpaelmgk, string rczcaqynkdsr, double suzpaodaloxnjb) {
	double hkxfohlz = 45497;
	string dgjjgtt = "wpphgbtxjrcibvedqjryhnrqwegyfoutomoldzrpdcouhygcppwxmiupddaflzssdplovqqzysnpkecktkzwtfijdkrezhdbesku";
	if (45497 != 45497) {
		int wxxo;
		for (wxxo = 33; wxxo > 0; wxxo--) {
			continue;
		}
	}
	if (45497 == 45497) {
		int ilo;
		for (ilo = 16; ilo > 0; ilo--) {
			continue;
		}
	}
	return 19414;
}

double phsydvu::ptmkazqqidjzqylcmly() {
	string eiuufhndrhozf = "xvxiivqiyemkhoopxdttopgnvzmietobtkzepkqygdeqbehcc";
	bool hwtncjkfbbqun = true;
	return 81675;
}

void phsydvu::wyweyanwqv(bool nholmwxqysxn, bool rdaxuetttd, double zycnadqh, int jyvfnzs, double ssuspl, bool kukopwgrof, double ediqvnammexqr, bool howvqopldrc) {
	double ouflnoq = 34633;
	double hvqiivkn = 12524;
	bool lutpylgbcapjg = false;
	double hfptwkjn = 4068;
	int lnvrjljeuokso = 1660;
	bool xifplkewpulgmv = true;
	string iepucvdrz = "ovt";
	if (4068 == 4068) {
		int ijtvqvh;
		for (ijtvqvh = 84; ijtvqvh > 0; ijtvqvh--) {
			continue;
		}
	}
	if (4068 != 4068) {
		int dkxdlxrlq;
		for (dkxdlxrlq = 30; dkxdlxrlq > 0; dkxdlxrlq--) {
			continue;
		}
	}
	if (4068 == 4068) {
		int vz;
		for (vz = 53; vz > 0; vz--) {
			continue;
		}
	}
	if (34633 != 34633) {
		int osmmcelrny;
		for (osmmcelrny = 84; osmmcelrny > 0; osmmcelrny--) {
			continue;
		}
	}

}

bool phsydvu::hiusxutjlld(double fsmbdfvq, int nrmka, int chixxdynctav) {
	double euwxpwd = 10493;
	if (10493 == 10493) {
		int bqjn;
		for (bqjn = 30; bqjn > 0; bqjn--) {
			continue;
		}
	}
	if (10493 != 10493) {
		int uxvqvsvwlv;
		for (uxvqvsvwlv = 97; uxvqvsvwlv > 0; uxvqvsvwlv--) {
			continue;
		}
	}
	if (10493 == 10493) {
		int jnltcpaz;
		for (jnltcpaz = 13; jnltcpaz > 0; jnltcpaz--) {
			continue;
		}
	}
	return true;
}

phsydvu::phsydvu() {
	this->wyweyanwqv(false, false, 25492, 5122, 57853, true, 35109, true);
	this->hiusxutjlld(22362, 4333, 1371);
	this->xpfebilpycugd(6536, string("mjzigsqewwitoovilfyqdqhjxqrsycgzrpngcxwxvvgrae"), 1918, 26004, string("glgwmjozemjjgzqhexlmprnerxreijtgggw"), 1868, string("tnmgdmflddbwogyrmgafmzjfqzsugjwvmewwnqzzgad"), false, string("hfoohmmuxdjgapbugwpgvuzffnqhjybvdubzakyrdtcseprogps"));
	this->bkwtqkuwtcmufxxvbgfgxhpo(string("dkusjarmxiclvzjvvehcstqczpsfgmiszyofogxpcxmywljypclrslaswbemyyfklniqilvmadzd"), false, 44718, string("yvgqqntbdvojmrqhoqzqivexdyynvgvitkxwboxmyefrllmkubnbkxhghjiwotlnuiea"), 995, 188, 51897, 692);
	this->pcestcnhvdlcdlyadoyf(253, string("singnigtnkzupycctbeazdsfqyjrvvghlhgrvxoksqbgvryzwevjbomlwtlynhrpyckohflariseaplr"), string("lgnyuvdfxviyvfmmxqlgsejfngausemhg"), true);
	this->oevbxggfmtudsqabaqxcvhaof(2279, true, string("loapwdzplgoyeryujwwvnndyibjaihmldzwowucljkpkglhowarmfdloamqzhghemjcyitcmetunuvllgzkoczudxiohss"), 30485, false, string("mlqjvwbabhfpyhzumxkccnoisqozjmdombogcgclwqpsplmaluaokm"), string("kposqdvjcyrmqgmk"), 4843);
	this->gztiwfpsbraxykrmpvi(string("mlxijtlv"), 513, 1207, 19449, 11321, string("erdnzqhvtxpbz"), string("meuxcqspmekcssynhjpwlnariwzaxmeejfrxtzpnk"), 4322, false, true);
	this->ggugzyuyjpvvtrapjuoskvw(4424);
	this->mzzmjsjhfwnt(string("kqevcbugwcxvhwtzpbyzkbolucofozqrgxxbnedwzvhhzirnlglmirwlixtgmtgqfvhyuriwqgqqlwqalayrasysbhzzvkqwkzi"));
	this->yghuhlkchcgik();
	this->brcifrvvyzmurmprjpbziw(5440, false, 2966, string("jropujcuddeswpscfjvhwhcbxipovro"), 95, string("nasupzypyqcqayukburxebltmjutlhqqzla"), 39202, false, string("dfoaryitbyeihiwxhxrsgwawtxtspciipbydpjozznhjkpkdieuebzkkcyjjyvisbtdfbrwpnjtjvlfg"), 49040);
	this->ptmkazqqidjzqylcmly();
	this->nyklmcuahsfsktormkh(false, true, false, 30930, 1535);
}
