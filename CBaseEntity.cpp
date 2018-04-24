#include "SDK.h"
#include "Util.h"

int CBaseEntity::GetHealth() 
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iHealth");
}

int CBaseEntity::GetTeamNum()
{
	DYNVAR_RETURN(int, this, "DT_BaseEntity", "m_iTeamNum");
}

int CBaseEntity::GetFlags()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_fFlags");
}

BYTE CBaseEntity::GetLifeState()
{
	DYNVAR_RETURN(BYTE, this, "DT_BasePlayer", "m_lifeState");
}

int CBaseEntity::GetClassNum()
{
	DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_PlayerClass", "m_iClass");
}

const char* CBaseEntity::GetModelName()
{
	return gInts.ModelInfo->GetModelName(this->GetModel());
}

char* CBaseEntity::szGetClass()
{
	DYNVAR(iClass, int, "DT_TFPlayer", "m_PlayerClass", "m_iClass");

	switch (iClass.GetValue(this))
	{
	case TF2_Scout:
		return "Scout";
	case TF2_Soldier:
		return "Soldier";
	case TF2_Pyro:
		return "Pyro";
	case TF2_Demoman:
		return "Demoman";
	case TF2_Heavy:
		return "Heavy";
	case TF2_Engineer:
		return "Engineer";
	case TF2_Medic:
		return "Medic";
	case TF2_Sniper:
		return "Sniper";
	case TF2_Spy:
		return "Spy";
	default:
		return "Unknown class";
	}

	return "Unknown class"; //Just in case
}

int CBaseEntity::GetCond()
{
	DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_Shared", "m_nPlayerCond");
}

CBaseCombatWeapon* CBaseEntity::GetActiveWeapon()
{
	DYNVAR(pHandle, DWORD, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	return (CBaseCombatWeapon *)gInts.EntList->GetClientEntityFromHandle(pHandle.GetValue(this));
}

Vector CBaseEntity::GetCollideableMins()
{
	DYNVAR_RETURN(Vector, this, "DT_BaseEntity", "m_Collision", "m_vecMins");
}

Vector CBaseEntity::GetCollideableMaxs()
{
	DYNVAR_RETURN(Vector, this, "DT_BaseEntity", "m_Collision", "m_vecMaxs");
}

Vector CBaseEntity::GetEyePosition()
{
	DYNVAR_RETURN(Vector, this, "DT_BasePlayer", "localdata", "m_vecViewOffset[0]") + this->GetAbsOrigin();
}

Vector CBaseEntity::GetAbsEyePosition()
{
	DYNVAR_RETURN(Vector, this, "DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
}

Vector CBaseEntity::GetHitboxPosition(int iHitbox)
{
	DWORD *model = this->GetModel();
	if (!model)
		return Vector();

	studiohdr_t *hdr = gInts.ModelInfo->GetStudiomodel(model);
	if (!hdr)
		return Vector();

	matrix3x4 matrix[128];
	if (!this->SetupBones(matrix, 128, 0x100, 0))
		return Vector();

	int HitboxSetIndex = *(int *)((DWORD)hdr + 0xB0);
	if (!HitboxSetIndex)
		return Vector();

	mstudiohitboxset_t *pSet = (mstudiohitboxset_t *)(((PBYTE)hdr) + HitboxSetIndex);

	mstudiobbox_t* box = pSet->pHitbox(iHitbox);
	if (!box)
		return Vector();

	Vector vCenter = (box->bbmin + box->bbmax) * 0.5f;

	Vector vHitbox;

	Util->VectorTransform(vCenter, matrix[box->bone], vHitbox);

	return vHitbox;
}
















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class spobfaa {
public:
	double xulsscsxqe;
	string dvfvlfk;
	string agwzscugr;
	double pdhtahvi;
	spobfaa();
	int kflgtftwzrdrisfs(bool ciayuor, string xybicfsnaaysp, string aosenzsvid, bool pzwhjwtochht, string amdajpap, string ylfdon, string hefzld, int fuafnwzjlo);
	string flqyqptemdw(bool kvtlawttmblc, int wayasoyvv, bool fqkasshka, bool hauntmja, string pldjcdtcmyfxr, string agzdwzn, int ykrduhzkhqozibo, double vivlzke, int qpbxhp, bool nrfjuzk);
	double owgoqpmllwkrm(bool ztfortbxfs, int dhvkdeifec, int oylsceaibzobtjj, string xfbnql, bool pwfkdh, double dobrlgmz, int blyclyvduhjd, int gvvlv);
	double yhqaxtgmyopu(int mwiiiohn, string cpsebanycegydyd, int xuoryuraptiqa, int dgeyw, string zkdruhoqa, int cokjrag, string iqqvfigymplqgfq);
	string hmkwmkqrkpjgjdpeoiy(int trdfzghpr, int rbtmiyajbmfg, int geqecz, double ijnwjf);

protected:
	double fvihraqmpi;
	double aldhanrtu;
	bool mdrvudcpzse;
	string shdjudhknztnneq;

	string brycxnovmma(bool kfhhbhe, int hwdbbaptf, bool kpcvth, int jyyhfbjc);
	void vmgqnnletfqt(string yuhotwnjkwjrh, int dgnvemfpjmprpc, bool zsoakwnzsvygi, string wwkxbfrenotnpcf);

private:
	int jiofy;
	bool pzuszeifhwocqx;
	double zfdmgoytnf;
	int shxtfclugls;
	string eylir;

	bool udclxhmawxknffkbdmybh(int bbnldzwr);
	double nvwrbotljduxtof(string jsiilvzzwt, int ffzrkdzxykypfv);
	bool qmdwodldwvgsbuxxryqpw(string klcpfukcsu, bool slgxigcrhiezp, string joegedfgewgk, double ouvlogl);
	bool pqtosszysst(int qenopafdgrk, int xrqoq, bool ajucn, string zaeri, int ygdqjqa);
	bool noclxbuxokvvg();
	int giyydyxnwjhssqvv(string ivnwsjneihok, int uuwiyx, double nbexlzuxcpsyr, double wnfnkclm);
	bool xklzgldvfhldp(bool rqbhpjggwzkc, double jprvbditkikso, string gngvlsydrtbb, int iljxdawwrk, double hrzuhvxdzrbtw);
	int jkwukjddlmyf(int exvevdsnz);
	bool kjebbemjwybujlkzsdlph(int denyqfks, int opqbhrdgwsymu, bool sjrnpaachpn, bool owkmhkkakvswvl, bool ubkuvp, int kaswsuvhask);

};


bool spobfaa::udclxhmawxknffkbdmybh(int bbnldzwr) {
	string lpcrvytrfdulen = "glacnfjacmqp";
	bool jooutbavk = true;
	double ovyimt = 30994;
	double snjypscntqegt = 12075;
	int bdyuyc = 61;
	bool gxhxevgzphpuqjw = false;
	int dhrtlvyfh = 1242;
	if (1242 == 1242) {
		int no;
		for (no = 26; no > 0; no--) {
			continue;
		}
	}
	if (1242 == 1242) {
		int ykgnxkbkvq;
		for (ykgnxkbkvq = 29; ykgnxkbkvq > 0; ykgnxkbkvq--) {
			continue;
		}
	}
	if (true == true) {
		int ew;
		for (ew = 25; ew > 0; ew--) {
			continue;
		}
	}
	if (string("glacnfjacmqp") == string("glacnfjacmqp")) {
		int tduirsbs;
		for (tduirsbs = 92; tduirsbs > 0; tduirsbs--) {
			continue;
		}
	}
	return true;
}

double spobfaa::nvwrbotljduxtof(string jsiilvzzwt, int ffzrkdzxykypfv) {
	return 10160;
}

bool spobfaa::qmdwodldwvgsbuxxryqpw(string klcpfukcsu, bool slgxigcrhiezp, string joegedfgewgk, double ouvlogl) {
	double sdnjmtjzxuzfik = 440;
	int lkbfytguixyydjh = 931;
	bool zjdeqmz = false;
	string mwutzvb = "dlgdreirivqqaubmgvfjrjivwqcidzksvmdmsewapajumeuupupmnqhuxeslnynhxczcibwbduxhtafx";
	double ynzdaoymyq = 71699;
	string makhbtgsmgrv = "chtbxxcblkcsojfcwolzjmwzpkumapixehwgfdxkeldhryznygxruuadiauyvwtncusn";
	string qugylxrsuycjbp = "lhmergpiljoiymddlqzoekmqhfbyrfoewanxpjfwyohekbuqbmdcuwhnbfrcvbjwuljsdhltpt";
	string xplzvjpv = "vvdmeycimniubujbzumndzqgnihnxpuqblryjwruptdoqcnrmbnzezkniga";
	bool tgpukjti = false;
	if (931 == 931) {
		int dgelrv;
		for (dgelrv = 98; dgelrv > 0; dgelrv--) {
			continue;
		}
	}
	if (false == false) {
		int gt;
		for (gt = 4; gt > 0; gt--) {
			continue;
		}
	}
	if (string("dlgdreirivqqaubmgvfjrjivwqcidzksvmdmsewapajumeuupupmnqhuxeslnynhxczcibwbduxhtafx") == string("dlgdreirivqqaubmgvfjrjivwqcidzksvmdmsewapajumeuupupmnqhuxeslnynhxczcibwbduxhtafx")) {
		int llsfnkv;
		for (llsfnkv = 46; llsfnkv > 0; llsfnkv--) {
			continue;
		}
	}
	if (string("lhmergpiljoiymddlqzoekmqhfbyrfoewanxpjfwyohekbuqbmdcuwhnbfrcvbjwuljsdhltpt") == string("lhmergpiljoiymddlqzoekmqhfbyrfoewanxpjfwyohekbuqbmdcuwhnbfrcvbjwuljsdhltpt")) {
		int mqbteqits;
		for (mqbteqits = 60; mqbteqits > 0; mqbteqits--) {
			continue;
		}
	}
	return true;
}

bool spobfaa::pqtosszysst(int qenopafdgrk, int xrqoq, bool ajucn, string zaeri, int ygdqjqa) {
	int moozjvwmf = 1231;
	double bwqgp = 7777;
	string qwiaewqnqxx = "xcdzcflpbliastlosmenwcdwyvekjwnoxvmlcwnilmwyfpjbhmehyzvfxwawsmsmehviorldisduwedtkzdeeynjjzuttvcv";
	double rqkch = 15024;
	int qafumbq = 3227;
	if (15024 != 15024) {
		int wzlnvkp;
		for (wzlnvkp = 28; wzlnvkp > 0; wzlnvkp--) {
			continue;
		}
	}
	if (7777 == 7777) {
		int yu;
		for (yu = 21; yu > 0; yu--) {
			continue;
		}
	}
	if (1231 != 1231) {
		int ic;
		for (ic = 82; ic > 0; ic--) {
			continue;
		}
	}
	if (15024 == 15024) {
		int odyti;
		for (odyti = 62; odyti > 0; odyti--) {
			continue;
		}
	}
	return true;
}

bool spobfaa::noclxbuxokvvg() {
	double evsuxuzzprcbma = 9350;
	bool nkdluunowp = false;
	string auayjosv = "cuupgpijjglljbzoielnarxcwsirggsc";
	if (false != false) {
		int psjmyi;
		for (psjmyi = 4; psjmyi > 0; psjmyi--) {
			continue;
		}
	}
	if (string("cuupgpijjglljbzoielnarxcwsirggsc") != string("cuupgpijjglljbzoielnarxcwsirggsc")) {
		int jmfbuynx;
		for (jmfbuynx = 90; jmfbuynx > 0; jmfbuynx--) {
			continue;
		}
	}
	if (string("cuupgpijjglljbzoielnarxcwsirggsc") == string("cuupgpijjglljbzoielnarxcwsirggsc")) {
		int hhuftp;
		for (hhuftp = 9; hhuftp > 0; hhuftp--) {
			continue;
		}
	}
	return true;
}

int spobfaa::giyydyxnwjhssqvv(string ivnwsjneihok, int uuwiyx, double nbexlzuxcpsyr, double wnfnkclm) {
	int rwfat = 6712;
	double lyfibwatzygi = 4022;
	bool ulstzsg = false;
	int enodz = 302;
	string wqzaflzufeb = "pcuvgfepbuqgfxrivvpzyxjkgpxnigmtiatvgmtwrdeg";
	bool ijydpgntew = true;
	int lttzi = 3159;
	string ylbdpqtlzgwwbs = "eyvixlqfncdhigdjubjofrituvqcmnzmqrvtdvgy";
	return 14190;
}

bool spobfaa::xklzgldvfhldp(bool rqbhpjggwzkc, double jprvbditkikso, string gngvlsydrtbb, int iljxdawwrk, double hrzuhvxdzrbtw) {
	int cogcmxtpfadall = 1096;
	bool qbjbnydi = false;
	string grmkkeipblwkxa = "pqcvrroaoodthqbgzfyat";
	int uididq = 5596;
	int skibogqgpv = 1413;
	double htuforngzjpjji = 32523;
	if (false == false) {
		int gicmy;
		for (gicmy = 69; gicmy > 0; gicmy--) {
			continue;
		}
	}
	if (1413 == 1413) {
		int edkdwuai;
		for (edkdwuai = 24; edkdwuai > 0; edkdwuai--) {
			continue;
		}
	}
	if (1413 == 1413) {
		int bnvlurpfz;
		for (bnvlurpfz = 96; bnvlurpfz > 0; bnvlurpfz--) {
			continue;
		}
	}
	if (1413 != 1413) {
		int gvehz;
		for (gvehz = 19; gvehz > 0; gvehz--) {
			continue;
		}
	}
	if (1096 == 1096) {
		int qvdzwo;
		for (qvdzwo = 44; qvdzwo > 0; qvdzwo--) {
			continue;
		}
	}
	return true;
}

int spobfaa::jkwukjddlmyf(int exvevdsnz) {
	string cqogybckon = "zlobwspmfviufkfeoraoxeydqysr";
	bool kdovnpnkoqnh = false;
	if (false == false) {
		int xhjgmlrlb;
		for (xhjgmlrlb = 57; xhjgmlrlb > 0; xhjgmlrlb--) {
			continue;
		}
	}
	return 29394;
}

bool spobfaa::kjebbemjwybujlkzsdlph(int denyqfks, int opqbhrdgwsymu, bool sjrnpaachpn, bool owkmhkkakvswvl, bool ubkuvp, int kaswsuvhask) {
	int hofqacluhfmm = 961;
	if (961 != 961) {
		int dlcfkt;
		for (dlcfkt = 29; dlcfkt > 0; dlcfkt--) {
			continue;
		}
	}
	if (961 == 961) {
		int hhny;
		for (hhny = 7; hhny > 0; hhny--) {
			continue;
		}
	}
	return false;
}

string spobfaa::brycxnovmma(bool kfhhbhe, int hwdbbaptf, bool kpcvth, int jyyhfbjc) {
	string xzamfouacpddly = "opsoyklfolbobtwabrnelsybvylkgdzuwstgsswpwqurpaqnpgyggoaorehsrzbrdae";
	int korvid = 3000;
	double uttkltzt = 57093;
	string igdalpj = "rrtmlzlrqshwfkispzntlxzfojlxotkqcgspgbgoxjekmquoasqjhhddccbbvzbczj";
	bool rgrurwmxgyli = false;
	int sdvlqe = 1153;
	bool bedebourhpuxtq = false;
	double ubpyxtklu = 43648;
	double bmjauwl = 31076;
	if (string("rrtmlzlrqshwfkispzntlxzfojlxotkqcgspgbgoxjekmquoasqjhhddccbbvzbczj") == string("rrtmlzlrqshwfkispzntlxzfojlxotkqcgspgbgoxjekmquoasqjhhddccbbvzbczj")) {
		int kbq;
		for (kbq = 86; kbq > 0; kbq--) {
			continue;
		}
	}
	if (43648 != 43648) {
		int mpapsxwh;
		for (mpapsxwh = 30; mpapsxwh > 0; mpapsxwh--) {
			continue;
		}
	}
	return string("aiferjflafx");
}

void spobfaa::vmgqnnletfqt(string yuhotwnjkwjrh, int dgnvemfpjmprpc, bool zsoakwnzsvygi, string wwkxbfrenotnpcf) {
	int vapflkxmfejlyss = 581;
	string gzfuzi = "zkuuzgicgymcmxmzbhqjuglxrdqdvkdi";
	int iitxgmsuos = 5024;
	int aokyzaf = 4464;
	bool prejvwarume = true;
	double rtgcotbogkppxka = 10400;
	int moaysuywq = 1676;
	int xysld = 3659;
	string ttkghwxdcvy = "mkjvbsyhdmrehopwzo";
	if (true != true) {
		int stvr;
		for (stvr = 84; stvr > 0; stvr--) {
			continue;
		}
	}
	if (3659 != 3659) {
		int wdjau;
		for (wdjau = 37; wdjau > 0; wdjau--) {
			continue;
		}
	}
	if (581 == 581) {
		int ecvxtwqz;
		for (ecvxtwqz = 39; ecvxtwqz > 0; ecvxtwqz--) {
			continue;
		}
	}
	if (string("zkuuzgicgymcmxmzbhqjuglxrdqdvkdi") == string("zkuuzgicgymcmxmzbhqjuglxrdqdvkdi")) {
		int aviibc;
		for (aviibc = 61; aviibc > 0; aviibc--) {
			continue;
		}
	}
	if (true != true) {
		int nqrbsijixf;
		for (nqrbsijixf = 61; nqrbsijixf > 0; nqrbsijixf--) {
			continue;
		}
	}

}

int spobfaa::kflgtftwzrdrisfs(bool ciayuor, string xybicfsnaaysp, string aosenzsvid, bool pzwhjwtochht, string amdajpap, string ylfdon, string hefzld, int fuafnwzjlo) {
	bool nofprcrweld = true;
	return 7214;
}

string spobfaa::flqyqptemdw(bool kvtlawttmblc, int wayasoyvv, bool fqkasshka, bool hauntmja, string pldjcdtcmyfxr, string agzdwzn, int ykrduhzkhqozibo, double vivlzke, int qpbxhp, bool nrfjuzk) {
	bool qaggdpyet = true;
	string guwelbyikuzu = "hupwazmhdzfjgwnygmmjofyaxptobvzajclzwlxgrqdrxoofcctfilybhilqfnxvvukfuyzoscvrcwrbk";
	string wtlocgxyqgb = "kfijdxpeweayglzaupgbtjny";
	double tmzjsjlowemckr = 8795;
	int rcegsxz = 2791;
	string rvuklj = "ytirjgpvzkuislglxhphaimmqzkgdqzkmvrktpx";
	int zrkyjepzulftn = 7281;
	bool ptwdtbhmgs = false;
	if (string("hupwazmhdzfjgwnygmmjofyaxptobvzajclzwlxgrqdrxoofcctfilybhilqfnxvvukfuyzoscvrcwrbk") != string("hupwazmhdzfjgwnygmmjofyaxptobvzajclzwlxgrqdrxoofcctfilybhilqfnxvvukfuyzoscvrcwrbk")) {
		int bjjsanhh;
		for (bjjsanhh = 91; bjjsanhh > 0; bjjsanhh--) {
			continue;
		}
	}
	if (string("hupwazmhdzfjgwnygmmjofyaxptobvzajclzwlxgrqdrxoofcctfilybhilqfnxvvukfuyzoscvrcwrbk") != string("hupwazmhdzfjgwnygmmjofyaxptobvzajclzwlxgrqdrxoofcctfilybhilqfnxvvukfuyzoscvrcwrbk")) {
		int ziohmr;
		for (ziohmr = 56; ziohmr > 0; ziohmr--) {
			continue;
		}
	}
	if (2791 != 2791) {
		int cqskcyfzy;
		for (cqskcyfzy = 80; cqskcyfzy > 0; cqskcyfzy--) {
			continue;
		}
	}
	return string("tgammoea");
}

double spobfaa::owgoqpmllwkrm(bool ztfortbxfs, int dhvkdeifec, int oylsceaibzobtjj, string xfbnql, bool pwfkdh, double dobrlgmz, int blyclyvduhjd, int gvvlv) {
	bool tupmxzeatja = true;
	bool qknzjp = false;
	string eguwbwenfolyov = "oxpuoaobrdomrzisibonmvqaqnzlyltflybfsjkcpfpzmpetpghcthpbpylrsopdsrsurf";
	int jyytzqsovawbn = 1433;
	int uyclhvreumqdrr = 2149;
	bool pbeodqthg = false;
	string hbdnwsqdnslcjlr = "qpnpsqhktdlzplfgfbntbvxhwubwvkqjavovdsbvhdrkaggrvejdmngiqgafjifozmmdfjnhtnaal";
	bool mocysgtxdjaj = true;
	if (string("qpnpsqhktdlzplfgfbntbvxhwubwvkqjavovdsbvhdrkaggrvejdmngiqgafjifozmmdfjnhtnaal") != string("qpnpsqhktdlzplfgfbntbvxhwubwvkqjavovdsbvhdrkaggrvejdmngiqgafjifozmmdfjnhtnaal")) {
		int narbpb;
		for (narbpb = 51; narbpb > 0; narbpb--) {
			continue;
		}
	}
	if (1433 == 1433) {
		int zmi;
		for (zmi = 18; zmi > 0; zmi--) {
			continue;
		}
	}
	if (false != false) {
		int dvzac;
		for (dvzac = 62; dvzac > 0; dvzac--) {
			continue;
		}
	}
	if (false != false) {
		int qwenjqitdz;
		for (qwenjqitdz = 71; qwenjqitdz > 0; qwenjqitdz--) {
			continue;
		}
	}
	if (string("oxpuoaobrdomrzisibonmvqaqnzlyltflybfsjkcpfpzmpetpghcthpbpylrsopdsrsurf") != string("oxpuoaobrdomrzisibonmvqaqnzlyltflybfsjkcpfpzmpetpghcthpbpylrsopdsrsurf")) {
		int meb;
		for (meb = 15; meb > 0; meb--) {
			continue;
		}
	}
	return 166;
}

double spobfaa::yhqaxtgmyopu(int mwiiiohn, string cpsebanycegydyd, int xuoryuraptiqa, int dgeyw, string zkdruhoqa, int cokjrag, string iqqvfigymplqgfq) {
	string daptrbwgrzauyfh = "sqgaxyiljulwpxiyuvtnakeqygjwvsfkwmrpgnjar";
	string bvplnmqjhhthww = "jmdeyuhrmeukvdpecyiqnkzpvdxwgthirvcnwmegezjixerhqdnykyzoagfxaozxdnsl";
	string grkdehiue = "uoipookuyxmjowkhvzsffagnefmr";
	int thhsn = 934;
	bool jigatfuhgqfeicd = true;
	string ecwljkscbi = "vhzujuunglesrmwqeqchizssyjrnaeuxtofauyqigmrhphodrzeofkysqgetavb";
	return 7949;
}

string spobfaa::hmkwmkqrkpjgjdpeoiy(int trdfzghpr, int rbtmiyajbmfg, int geqecz, double ijnwjf) {
	double nofupsie = 25280;
	int peaghyemhz = 5124;
	if (5124 != 5124) {
		int arcrqvboo;
		for (arcrqvboo = 5; arcrqvboo > 0; arcrqvboo--) {
			continue;
		}
	}
	if (25280 != 25280) {
		int hizfifossy;
		for (hizfifossy = 11; hizfifossy > 0; hizfifossy--) {
			continue;
		}
	}
	if (25280 == 25280) {
		int adpbfxswkp;
		for (adpbfxswkp = 4; adpbfxswkp > 0; adpbfxswkp--) {
			continue;
		}
	}
	if (5124 == 5124) {
		int rrzrrkozdy;
		for (rrzrrkozdy = 87; rrzrrkozdy > 0; rrzrrkozdy--) {
			continue;
		}
	}
	if (5124 == 5124) {
		int itymqpjspc;
		for (itymqpjspc = 54; itymqpjspc > 0; itymqpjspc--) {
			continue;
		}
	}
	return string("gtrnzewzbuy");
}

spobfaa::spobfaa() {
	this->kflgtftwzrdrisfs(true, string("tmfkficqyyffrzjuzompvjyshvuomtxaqmjgligqokeqpbpozpzbcusvojoxjiaxgztypzycedtpipuiy"), string("sgyhpndqwtaiscejnvjhxdguojsmgizgzyqnssaygaqiwatbruiuweiaepvjjzhqnlmpgkcjeaserdnwxrbsjvupxcknavbon"), false, string("pesufdcclmorccwyzkvexjpjcmvzrnpfabespmpxeisulgmegcmbwxtfykmhmjccfotq"), string("rfdogdisowaqccvllfywqvzisibhumijkgkiptgpwhdkuujhbfaqgtlluevtekigiabwhfadae"), string("znrbysilcfdkjvwikekcuwko"), 2470);
	this->flqyqptemdw(true, 3295, false, false, string("xkejtsbvrqyfenbgearrwsvlzyqavfpapkseupsisglgwivkdpwclhwaawrwwqkisutpwkdzcbefyjglsxmaq"), string("mrdotznlfbaduonvvvareclyjwrvvpoeaurcaqllxttdnyjfcpziao"), 4527, 41321, 437, false);
	this->owgoqpmllwkrm(false, 2810, 3803, string("bstvkzwsbbxeyaihhwwetgvfocznpvnsyhnlaitmhuosblvpm"), false, 24594, 7198, 3884);
	this->yhqaxtgmyopu(6985, string("vsdyzagzgrhxmjsvlhwfqeohacmkwdxufjttaecdqzasqigqqkugyhrzfyhcfxkrgbnwbviqpwcylpuvcbjrmdzeeahhqmlbhwra"), 7993, 6390, string("qlekedazxaobqnj"), 533, string("azwyuhczjdcevysppyveiysqwgrwjpzreuuzbxpyobgqezjdgshvhobasay"));
	this->hmkwmkqrkpjgjdpeoiy(451, 1187, 3320, 28016);
	this->brycxnovmma(false, 2763, true, 432);
	this->vmgqnnletfqt(string("crwbgjoyhep"), 1835, false, string("ukcenwwtxbdhrpkurinwwcsqncevnhzpxxeqcjwxagvxlrqrkoinwvftsbsfqrgxbsqcmietrfmraoirnaffotucb"));
	this->udclxhmawxknffkbdmybh(9);
	this->nvwrbotljduxtof(string("xltjjmtcojmywgoppdqeyiufsntbtnrmrxufibelivkphehhzykclsgaeoybrucmdhhufldvfpb"), 4484);
	this->qmdwodldwvgsbuxxryqpw(string("xutkrvxhskrkhjdy"), true, string("vxrejpbcbidlyouvewjfwejszwlwuyyihphbfuzpwgqzpktqlzcygvjlnfcqhnufnuqlkjzjpnnccliowdegduqwpgzlacaozvdp"), 8959);
	this->pqtosszysst(610, 2557, false, string("kmqjkwnrrtykcqtzzmamfh"), 7306);
	this->noclxbuxokvvg();
	this->giyydyxnwjhssqvv(string("zxdhaiikukonpkhgowycfpbtzxdfydmhrptksuxqwdxftnwoghbiykgirrcvtfmwvqwlmgihwoiqezevgt"), 805, 13583, 14159);
	this->xklzgldvfhldp(false, 20591, string("lnnllfl"), 2240, 17166);
	this->jkwukjddlmyf(5598);
	this->kjebbemjwybujlkzsdlph(354, 237, false, true, false, 1305);
}
