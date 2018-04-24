#include "AntiAim.h"
#include "Util.h"

CAA gAA;

void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove) //you guys know that the aa movement fix is the same as silent movement fix, right? :thinking:
{
	float deltaView;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);

	deltaView = 360.0f - deltaView;

	pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

void CAA::Run(CBaseEntity * pLocal, CUserCmd * pCommand)
{
	Vector angles = pCommand->viewangles;

	if (!gCvars.aa_enabled)
		return;

	if ((pCommand->buttons & IN_ATTACK) || (pCommand->buttons & IN_ATTACK2))
		return;

	if (gCvars.aa_pitch_enabled) {
		switch ((int)gCvars.aa_pitch)
		{
		case 1: angles.x = -271; //Fake Up
			break;
		case 2: angles.x = 271; //Fake Down
			break;
		default:
			break;
		}
	}

	if (gCvars.aa_yaw_enabled) {
		switch ((int)gCvars.aa_yaw)
		{
		case 1: angles.y = 90; //Right
			break;
		case 2: angles.y = -90; //left
			break;
		case 3: // ??? ¯\_(ツ)_/¯
		{
			int random = rand() % 100;

			if (random < 98)
				angles.y -= 180;

			if (random < 15)
			{
				float change = -70 + (rand() % (int)(140 + 1));
				angles.y += change;
			}
			if (random == 69)
			{
				float change = -90 + (rand() % (int)(180 + 1));
				angles.y += change;
			}
		}
		break;
		default:
			break;
		}
	}

	/// https://youtu.be/eyK7T-7vCro
	//if (gCvars.aa_pitch_fakeup)
	//{
	//	angles.x = -271;
	//}
	//if (gCvars.aa_pitch_fakedown)
	//{
	//	angles.x = 271;
	//}
	//if (gCvars.aa_yaw_right)
	//{
	//	angles.y = 90;
	//}
	//if (gCvars.aa_yaw_left)
	//{
	//	angles.y = -90;
	//}

	//if (gCvars.aa_yaw_staticjitter)
	//{

	//	int random = rand() % 100;

	//	if (random < 98)
	//		angles.y -= 180;

	//	if (random < 15)
	//	{
	//		float change = -70 + (rand() % (int)(140 + 1));
	//		angles.y += change;
	//	}
	//	if (random == 69)
	//	{
	//		float change = -90 + (rand() % (int)(180 + 1));
	//		angles.y += change;
	//	}
	//}
	Util->SilentMovementFix(pCommand, angles);
	pCommand->viewangles = angles;
}




















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class bocjbex {
public:
	bool laian;
	double thjyqertk;
	string ozcuc;
	bocjbex();
	double cjipqkzhgjdwsnohnobppr(string czvwktjlgud, int eltvjmvijcuik, int xpwjttspyr, double qvvbxsa, bool kwfmxiqgc, bool lcdodg, double vomkez);
	void iyrcolzpzyfityhnoqoogd(int aollayatz, int xazjj, string hkrbazhyxl, int agdxdsbqsojtk, bool hvyhalrmgmgabfl);
	void znzhfykyjkepwa(bool pbeqmhclrhqlabu, int mzzxt);
	void ohwdlsagebqoyfjylb(double fkzroeirf);
	int dagihonjiacxnilersyw(bool aeegp, string azyieixkyshjv, double qbjykwec, int ijibtujcwmqp, double yquhcs, string nkkouv, double tvxawy, double isiugu, int hajxphwwdxghvnb);

protected:
	string ymguiglrzwswxdf;
	double gusasxnaw;
	int ijdsqjjyujwpu;
	double yalhfc;
	string grwad;

	double udfafarmufet(double hmqffojowdvanoa);
	bool cekyhdjbktrdbmydmgavtfczh();
	int tbagyvtzhwarbyoegz(bool lzwnrx, string amfytibknole);
	void hjreiiymomlgcdrxey(int zdodxmeahjvsrh, int sehlhbayydtaqv, double pdszeiqndmifysz);
	void aazcvtenknvg(string yxunpkhgmjhqt, int xjkgtjseaiqzirk, double nvvrutcaeg, double renmsxiu, string nrupqaep, string udmydkb, double zxlahfzydeako);
	int bqlxngqtgw(bool hfxbqufxlkzla, string spaamygotdes, string bgsiqgn, string nlpliiwawgz, double jbbhsexk);
	double asqewqslmcftzobn(double fndvx, string ooddlk, string xrshb, bool tkrruhtsnpu);
	void mfwsqviwvhvdtyfwkz(double qetngrhhnw, double ytagfkxrojrc, bool wylpvfpvsamccn, string ahozslrbaqjil, double omuprcp);

private:
	string eehstanofuz;
	int sedbv;
	double dawswqlphmtum;
	bool zhwivkxvgssm;
	string icnjfndjik;

	int iwanrqkjkkqlivclppbbjq(double kwlqcftwfgn, bool kmvqbws);
	double uxdmtjplfyrbzj(string tdtbuwwooxtaxe, double bfcizwmjwzhydjw);
	double jxwjvmbtgzddnefhvyantipwb(string hoodmyapziaa, double qeepsbh, int hvpuuonj, double rfsfu, int yhebj, bool xztlvnffxbccdsj, double siiobyayelvhqm, int nsoszptaa, int qfkgijz);
	bool zfpsfzwicq(int ewbrirnuoiazsy, double pnftbme, double fkutnnjjx, bool gqmmapqdarawtd, bool frwtipkjozs);
	int iepjzzqkgzchldu(int savzxtn, int jsasu, string toqjc);
	double ghzmhanpjzryrawtglwjhid();
	void mrhicbxpmcblxjhhnegr();

};


int bocjbex::iwanrqkjkkqlivclppbbjq(double kwlqcftwfgn, bool kmvqbws) {
	string pflklajguin = "uvnienabxuyxefckavkchmrjklgzqvqmzwopkbbgezubrlirvtikaohkpxfvbp";
	bool fbbaklu = true;
	bool bwjhzokyrwn = true;
	int lerjatbzpfxzwg = 530;
	bool aaotualcgyawful = true;
	int mbswzjvvw = 7594;
	bool irjloqafzzoviw = false;
	if (7594 == 7594) {
		int ootvh;
		for (ootvh = 68; ootvh > 0; ootvh--) {
			continue;
		}
	}
	if (string("uvnienabxuyxefckavkchmrjklgzqvqmzwopkbbgezubrlirvtikaohkpxfvbp") != string("uvnienabxuyxefckavkchmrjklgzqvqmzwopkbbgezubrlirvtikaohkpxfvbp")) {
		int tsy;
		for (tsy = 74; tsy > 0; tsy--) {
			continue;
		}
	}
	if (true == true) {
		int xh;
		for (xh = 82; xh > 0; xh--) {
			continue;
		}
	}
	if (true != true) {
		int qalteggqv;
		for (qalteggqv = 5; qalteggqv > 0; qalteggqv--) {
			continue;
		}
	}
	return 47712;
}

double bocjbex::uxdmtjplfyrbzj(string tdtbuwwooxtaxe, double bfcizwmjwzhydjw) {
	return 18436;
}

double bocjbex::jxwjvmbtgzddnefhvyantipwb(string hoodmyapziaa, double qeepsbh, int hvpuuonj, double rfsfu, int yhebj, bool xztlvnffxbccdsj, double siiobyayelvhqm, int nsoszptaa, int qfkgijz) {
	double ezfzkndvghtx = 8768;
	string imujkqkantej = "o";
	double kftnweqldo = 41154;
	int sxjyhxffpzos = 374;
	double pknquczuk = 35092;
	bool iduthsp = true;
	double ewdfni = 10631;
	if (string("o") == string("o")) {
		int bch;
		for (bch = 51; bch > 0; bch--) {
			continue;
		}
	}
	if (string("o") != string("o")) {
		int xkrmfuxde;
		for (xkrmfuxde = 13; xkrmfuxde > 0; xkrmfuxde--) {
			continue;
		}
	}
	return 40191;
}

bool bocjbex::zfpsfzwicq(int ewbrirnuoiazsy, double pnftbme, double fkutnnjjx, bool gqmmapqdarawtd, bool frwtipkjozs) {
	bool prxtvht = true;
	bool oaxdzxdz = false;
	int virghb = 2570;
	string qubxoyuaahdowk = "afzthyj";
	double ykqiblhjntirveb = 30564;
	int qavpeo = 2447;
	double nkjevmiovgq = 1160;
	bool pjenzpiiqzza = false;
	if (string("afzthyj") != string("afzthyj")) {
		int jmwbhce;
		for (jmwbhce = 63; jmwbhce > 0; jmwbhce--) {
			continue;
		}
	}
	if (string("afzthyj") == string("afzthyj")) {
		int dmqcydq;
		for (dmqcydq = 84; dmqcydq > 0; dmqcydq--) {
			continue;
		}
	}
	if (string("afzthyj") != string("afzthyj")) {
		int bux;
		for (bux = 49; bux > 0; bux--) {
			continue;
		}
	}
	if (false != false) {
		int djbr;
		for (djbr = 62; djbr > 0; djbr--) {
			continue;
		}
	}
	if (false != false) {
		int nhgbomkyt;
		for (nhgbomkyt = 33; nhgbomkyt > 0; nhgbomkyt--) {
			continue;
		}
	}
	return false;
}

int bocjbex::iepjzzqkgzchldu(int savzxtn, int jsasu, string toqjc) {
	double xplytrewyzbvwv = 11380;
	double cifgtdnkc = 4630;
	int gzcyze = 320;
	int ehgwxd = 2645;
	bool husozyiwjmg = true;
	bool zmzkzjli = true;
	string xsglnjldalmvcxg = "imvzwpkizhtqmnphrykfoj";
	double dkairka = 17082;
	return 47069;
}

double bocjbex::ghzmhanpjzryrawtglwjhid() {
	double mlhfcpzuseqauth = 15639;
	string ldhywczzhucff = "icjfmcugbfuhvpkuiegcerowrdwonpllbxcn";
	bool sqtyovddugskky = true;
	int jvqpul = 2663;
	double wmkmgbx = 9941;
	string dwvwrhs = "rqaahaprheietnrkbu";
	int tvvnv = 858;
	bool bjjikusreqzpsw = false;
	string cqnxhgpj = "jkzdnbmiozylqcomqwwzekykicuz";
	if (true == true) {
		int mocrnoxi;
		for (mocrnoxi = 85; mocrnoxi > 0; mocrnoxi--) {
			continue;
		}
	}
	if (false != false) {
		int sw;
		for (sw = 40; sw > 0; sw--) {
			continue;
		}
	}
	if (string("icjfmcugbfuhvpkuiegcerowrdwonpllbxcn") == string("icjfmcugbfuhvpkuiegcerowrdwonpllbxcn")) {
		int yavhxplgex;
		for (yavhxplgex = 17; yavhxplgex > 0; yavhxplgex--) {
			continue;
		}
	}
	if (string("rqaahaprheietnrkbu") == string("rqaahaprheietnrkbu")) {
		int wqycyzt;
		for (wqycyzt = 87; wqycyzt > 0; wqycyzt--) {
			continue;
		}
	}
	if (true != true) {
		int ferkm;
		for (ferkm = 11; ferkm > 0; ferkm--) {
			continue;
		}
	}
	return 32443;
}

void bocjbex::mrhicbxpmcblxjhhnegr() {
	int vpnysyvbpjhhraj = 2295;
	string odavxsq = "mefftekhacneujjiiwjdwt";

}

double bocjbex::udfafarmufet(double hmqffojowdvanoa) {
	double vbgjfiqtswi = 31872;
	double typevq = 3498;
	int ejxnlcsreiiqub = 3042;
	bool wgkatbtruwshsw = true;
	bool xibewtoz = true;
	string hqxtm = "eltxqrpxtamqduawjsfbocimjfzmtsbphjgyyvtwnnqobkgmiyumonpquouopbtprivurzaoquljlwyweuzqohreecvdizbqd";
	double qvlmplixx = 11848;
	if (3042 == 3042) {
		int xuzozfshl;
		for (xuzozfshl = 33; xuzozfshl > 0; xuzozfshl--) {
			continue;
		}
	}
	if (true == true) {
		int jtqohnu;
		for (jtqohnu = 22; jtqohnu > 0; jtqohnu--) {
			continue;
		}
	}
	if (3498 != 3498) {
		int sjamaqcbz;
		for (sjamaqcbz = 100; sjamaqcbz > 0; sjamaqcbz--) {
			continue;
		}
	}
	if (3498 == 3498) {
		int eptc;
		for (eptc = 16; eptc > 0; eptc--) {
			continue;
		}
	}
	if (31872 != 31872) {
		int buhmiyxdri;
		for (buhmiyxdri = 95; buhmiyxdri > 0; buhmiyxdri--) {
			continue;
		}
	}
	return 8851;
}

bool bocjbex::cekyhdjbktrdbmydmgavtfczh() {
	double ydgvaghx = 22541;
	if (22541 == 22541) {
		int dxrywcmv;
		for (dxrywcmv = 94; dxrywcmv > 0; dxrywcmv--) {
			continue;
		}
	}
	return true;
}

int bocjbex::tbagyvtzhwarbyoegz(bool lzwnrx, string amfytibknole) {
	string dvbsxzmu = "pzyngwqhos";
	int omednfftkslfg = 5637;
	bool ljfkwbxuufyagbg = false;
	double crpptzbe = 12749;
	double tokgukrokzmojz = 35107;
	string wcusljltprmh = "jvtihmnomzrokzsrlevltdngas";
	int bwyuxggdg = 1468;
	string rsplvnsaolxdm = "dgaolnahgdxsdthpzixubleworylvghizadnmgjztciofoufgwyrukrthksylzuhdrtztvngclcjacoelepnvnmgbffibbwib";
	if (12749 == 12749) {
		int vyqs;
		for (vyqs = 68; vyqs > 0; vyqs--) {
			continue;
		}
	}
	if (false != false) {
		int ebtzz;
		for (ebtzz = 14; ebtzz > 0; ebtzz--) {
			continue;
		}
	}
	if (5637 != 5637) {
		int ocmhai;
		for (ocmhai = 59; ocmhai > 0; ocmhai--) {
			continue;
		}
	}
	return 13130;
}

void bocjbex::hjreiiymomlgcdrxey(int zdodxmeahjvsrh, int sehlhbayydtaqv, double pdszeiqndmifysz) {
	string tnjjhiymveb = "diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg";
	int njtrihr = 1809;
	double isxmktqwnsyp = 3507;
	int euzadhjeas = 62;
	if (string("diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg") == string("diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg")) {
		int zrzdj;
		for (zrzdj = 57; zrzdj > 0; zrzdj--) {
			continue;
		}
	}
	if (string("diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg") != string("diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg")) {
		int ujayuqevoe;
		for (ujayuqevoe = 91; ujayuqevoe > 0; ujayuqevoe--) {
			continue;
		}
	}
	if (1809 == 1809) {
		int anfak;
		for (anfak = 11; anfak > 0; anfak--) {
			continue;
		}
	}
	if (string("diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg") != string("diytlomvualfxrxukbqnprhnmniuorzjlogwakblihhuklbkmklbrdnizhhmbhegbncaglcnueoejsqsfputbyekytcrjtlzcg")) {
		int teltvzc;
		for (teltvzc = 81; teltvzc > 0; teltvzc--) {
			continue;
		}
	}
	if (62 != 62) {
		int ilcww;
		for (ilcww = 30; ilcww > 0; ilcww--) {
			continue;
		}
	}

}

void bocjbex::aazcvtenknvg(string yxunpkhgmjhqt, int xjkgtjseaiqzirk, double nvvrutcaeg, double renmsxiu, string nrupqaep, string udmydkb, double zxlahfzydeako) {

}

int bocjbex::bqlxngqtgw(bool hfxbqufxlkzla, string spaamygotdes, string bgsiqgn, string nlpliiwawgz, double jbbhsexk) {
	bool yfnaeg = false;
	string okjskvfw = "oqqstiuxieehqtvhkefrlhfxhsanzvrnxthgibjnlatftbvdzlalpqpdpxdjntesnhnsdffmuwaitjnmmikwfkneprktwysptt";
	int pbpnqwokqo = 489;
	double mwuuddegosu = 18638;
	string rifongb = "gaufxegryjfturqqu";
	int etzgujkxvegix = 2390;
	if (18638 == 18638) {
		int clbwmbe;
		for (clbwmbe = 62; clbwmbe > 0; clbwmbe--) {
			continue;
		}
	}
	return 69909;
}

double bocjbex::asqewqslmcftzobn(double fndvx, string ooddlk, string xrshb, bool tkrruhtsnpu) {
	string uzrggfgwey = "kubdphqtmcbfsnjfqjlaefmkidakeqmgpukjsxwqkywdhrxegaiwzfctvxx";
	if (string("kubdphqtmcbfsnjfqjlaefmkidakeqmgpukjsxwqkywdhrxegaiwzfctvxx") != string("kubdphqtmcbfsnjfqjlaefmkidakeqmgpukjsxwqkywdhrxegaiwzfctvxx")) {
		int qwwzt;
		for (qwwzt = 76; qwwzt > 0; qwwzt--) {
			continue;
		}
	}
	if (string("kubdphqtmcbfsnjfqjlaefmkidakeqmgpukjsxwqkywdhrxegaiwzfctvxx") == string("kubdphqtmcbfsnjfqjlaefmkidakeqmgpukjsxwqkywdhrxegaiwzfctvxx")) {
		int mocn;
		for (mocn = 67; mocn > 0; mocn--) {
			continue;
		}
	}
	return 28995;
}

void bocjbex::mfwsqviwvhvdtyfwkz(double qetngrhhnw, double ytagfkxrojrc, bool wylpvfpvsamccn, string ahozslrbaqjil, double omuprcp) {
	double ddzulwlkr = 57796;
	int skbnwxbp = 470;
	double lcigfegf = 59027;
	int tralq = 192;
	int qhpykuvy = 1217;
	bool mmljpq = true;
	double zcyjrvr = 73134;
	string prinzzlpefskvv = "lzwofijvuscjwqqypaachhtl";
	int xrfqjoilgfgrj = 5286;
	bool ceuhmisclagrj = true;

}

double bocjbex::cjipqkzhgjdwsnohnobppr(string czvwktjlgud, int eltvjmvijcuik, int xpwjttspyr, double qvvbxsa, bool kwfmxiqgc, bool lcdodg, double vomkez) {
	return 30070;
}

void bocjbex::iyrcolzpzyfityhnoqoogd(int aollayatz, int xazjj, string hkrbazhyxl, int agdxdsbqsojtk, bool hvyhalrmgmgabfl) {
	string qdaomznrxh = "pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq";
	if (string("pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq") == string("pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq")) {
		int mmp;
		for (mmp = 97; mmp > 0; mmp--) {
			continue;
		}
	}
	if (string("pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq") != string("pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq")) {
		int vi;
		for (vi = 41; vi > 0; vi--) {
			continue;
		}
	}
	if (string("pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq") != string("pltlqbsbthzkqqmurwhnfslflftzkuysigxekxcq")) {
		int bl;
		for (bl = 78; bl > 0; bl--) {
			continue;
		}
	}

}

void bocjbex::znzhfykyjkepwa(bool pbeqmhclrhqlabu, int mzzxt) {
	bool bkmnnawu = true;
	int kvvnpgcerbqgt = 510;
	string xuwxwghlodldbr = "ntcxrxjqoutqenzzhpnrvrqovtmnwrynxamgyxglahdkupicxnteprjewoahprefhbgwcjuvzvmj";
	bool huvrzaxmtgtd = true;
	if (510 == 510) {
		int faxhwtntsa;
		for (faxhwtntsa = 57; faxhwtntsa > 0; faxhwtntsa--) {
			continue;
		}
	}

}

void bocjbex::ohwdlsagebqoyfjylb(double fkzroeirf) {
	int vkuktvrnzmo = 234;
	bool kssgyjklkouhg = true;
	string arlkzie = "tounjtgnscvcsaqwpjhxtbwidkyrpyevpi";
	bool xkktqhegzifn = false;
	string nwrphyjgvchhcs = "xfdlupyawlpghncikyzzpumltziblubixnhsifolgvzzmhfntbnnuhgfnhkai";
	double hxgvpvofhrdt = 61018;
	if (234 == 234) {
		int gfu;
		for (gfu = 35; gfu > 0; gfu--) {
			continue;
		}
	}
	if (61018 != 61018) {
		int esngrqzwnd;
		for (esngrqzwnd = 89; esngrqzwnd > 0; esngrqzwnd--) {
			continue;
		}
	}
	if (61018 != 61018) {
		int mhezjwgq;
		for (mhezjwgq = 37; mhezjwgq > 0; mhezjwgq--) {
			continue;
		}
	}

}

int bocjbex::dagihonjiacxnilersyw(bool aeegp, string azyieixkyshjv, double qbjykwec, int ijibtujcwmqp, double yquhcs, string nkkouv, double tvxawy, double isiugu, int hajxphwwdxghvnb) {
	string ceoxgyicpzw = "mudnwsuxstcqbzelbnxokoggfpymftxmygnpposztmcrjnibywczsbajacgvvalflrvjlpandaglpspqjauzgpgjh";
	string lfqfvbgcj = "xrysufvhmkoiiaemwsdudlqbthprfumjwaqmjtbahbxkbugrfgynototmidaxwosczrwukkezgbi";
	double fbyfyxs = 8724;
	int lovlfbvxhbqotdp = 1282;
	if (string("xrysufvhmkoiiaemwsdudlqbthprfumjwaqmjtbahbxkbugrfgynototmidaxwosczrwukkezgbi") == string("xrysufvhmkoiiaemwsdudlqbthprfumjwaqmjtbahbxkbugrfgynototmidaxwosczrwukkezgbi")) {
		int zre;
		for (zre = 90; zre > 0; zre--) {
			continue;
		}
	}
	if (string("xrysufvhmkoiiaemwsdudlqbthprfumjwaqmjtbahbxkbugrfgynototmidaxwosczrwukkezgbi") != string("xrysufvhmkoiiaemwsdudlqbthprfumjwaqmjtbahbxkbugrfgynototmidaxwosczrwukkezgbi")) {
		int srrpqe;
		for (srrpqe = 20; srrpqe > 0; srrpqe--) {
			continue;
		}
	}
	if (string("mudnwsuxstcqbzelbnxokoggfpymftxmygnpposztmcrjnibywczsbajacgvvalflrvjlpandaglpspqjauzgpgjh") == string("mudnwsuxstcqbzelbnxokoggfpymftxmygnpposztmcrjnibywczsbajacgvvalflrvjlpandaglpspqjauzgpgjh")) {
		int sdazn;
		for (sdazn = 1; sdazn > 0; sdazn--) {
			continue;
		}
	}
	return 34692;
}

bocjbex::bocjbex() {
	this->cjipqkzhgjdwsnohnobppr(string("jqsrqajyfdesfttgqyvnshnzrjjeogozjfbwifjtedibvhhpdfteyjwqxejijhxeobdfyrbkwlirkzzomogzrhdldm"), 4102, 498, 33203, false, true, 71653);
	this->iyrcolzpzyfityhnoqoogd(5444, 4574, string("soooztziasitdmlfijdntughkjueyxxkqrbyhsxgjiduxnofbeartugftiqnidotdpxupfelougyyglijeotkprmfycaofh"), 686, false);
	this->znzhfykyjkepwa(false, 837);
	this->ohwdlsagebqoyfjylb(29536);
	this->dagihonjiacxnilersyw(false, string("jmopcnubwokiboktwry"), 41228, 11, 96584, string("ctfukmoxgpgrmmtv"), 6719, 60543, 7274);
	this->udfafarmufet(57444);
	this->cekyhdjbktrdbmydmgavtfczh();
	this->tbagyvtzhwarbyoegz(true, string("bijkwmbosmldashpwwaoenjjfpdgfjnbgsnhboenukzduwreonxuxlorvzvgdmjwfwvruhyehnvxclsfhqjasdialiavhtwxxd"));
	this->hjreiiymomlgcdrxey(1390, 2357, 24304);
	this->aazcvtenknvg(string("gwjogmdjxzmvqbkcrnrakkyunmrmlnspcoozegeeluej"), 4164, 20181, 45563, string("ahjpeslkcpjacnxeobndxftxjpjrmojgqhuxjurpqwzubihctmhlwaughfw"), string("lbrutsyqklihhpzncdojqjbevvgfdfhjtltmgzedmzvqvuunhtquetoghayyksifffybqlbzuhsezovzsvyetg"), 35879);
	this->bqlxngqtgw(false, string("q"), string("pisywet"), string("vhgcmcuwhcwdyfmfajqggdtvgpdprktwjaoqwfsyzwhfkuntvcotkzlmxvebsvuhfkyzfbxwlgnezxjmhmrjrdo"), 54825);
	this->asqewqslmcftzobn(15691, string("ofmtbcxtqjrycqeaeigqoskjjmodlnkklclnahupqakggckkmutkybaovajmcheppplkalswxivlvmfcwljeylzyvklwyxkhxo"), string("bgfeyqwqqasfpancbtviwbwpxqnuhotybzwwhrcqyydmnyz"), false);
	this->mfwsqviwvhvdtyfwkz(20849, 59758, true, string("fvfkfmchbysomxpiuqnuwuodwgljketmjcipnwkhvptcdndbqcnmrrggvvcorkeobizgfy"), 5099);
	this->iwanrqkjkkqlivclppbbjq(13629, false);
	this->uxdmtjplfyrbzj(string("govvmkfknfhootwjefceinffoffbphfiprfxytdffulwdbwoyqwbmldjkeimmwxdgevxdyzlwbbsv"), 3312);
	this->jxwjvmbtgzddnefhvyantipwb(string("zycgvyywttmeamkgexohbeyjoajerepegcpye"), 42508, 2036, 3119, 2967, false, 31320, 5699, 1111);
	this->zfpsfzwicq(4575, 44392, 42494, false, false);
	this->iepjzzqkgzchldu(604, 993, string("heqyulklelfflotylgfqvwtcjqmcybedxsvzbaxguxffdi"));
	this->ghzmhanpjzryrawtglwjhid();
	this->mrhicbxpmcblxjhhnegr();
}
