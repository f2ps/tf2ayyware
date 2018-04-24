#include "RemoveConditions.h"

RemoveCondExploits gCond;

void RemoveCondExploits::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	if (!gCvars.removecond_enabled)
		return;

	if (Util->IsKeyPressed(gCvars.removecond_key) //G
											   //  && pLocal->GetLifeState() == LIFE_ALIVE
		&& !gInts.Engine->Con_IsVisible()
		&& gInts.Engine->IsConnected())
		RemoveConds(pLocal, pCommand, gCvars.removecond_value);

	if (gCvars.removecond_autoinstantcap)
	{
		for (int i = 1; i < gInts.EntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* pEnt = GetBaseEntity(i);

			if (!pEnt) continue;

			if (pEnt->GetTeamNum() == pLocal->GetTeamNum()) continue;

			if (!strcmp(pEnt->GetModelName(), "models/props_gameplay/cap_point_base.mdl"))
			{
				Vector entPos = pEnt->GetEyePosition();
				Vector localPos = pLocal->GetEyePosition();
				float distance = Util->flGetDistance(localPos, entPos);
				if (distance < 22.0 && Util->IsVisible(pLocal, pEnt, localPos, entPos))
				{
					gCond.RemoveConds(pLocal, gCvars.removecond_value);
				}
			}
		}
	}

	if (gCvars.removecond_instantweaponswitch)
	{
		static int lastweapon = 0;
		if (lastweapon != pCommand->weaponselect)
			RemoveConds(pLocal, pCommand, 100, false);
		lastweapon = pCommand->weaponselect;
	}

	if (gCvars.removecond_automedkit)
	{
		for (int i = 1; i <= gInts.EntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity *pEnt = gInts.EntList->GetClientEntity(i);
			if (!pEnt)
				continue;

			if (pEnt->GetOwner() != -1) continue; // We cant insta medkit dropped ammo/health packs

			const char* pszModelName = pEnt->GetModelName();
			if (!strcmp(pszModelName, "models/items/medkit_small.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_small_bday.mdl")
				|| !strcmp(pszModelName, "models/props_halloween/halloween_medkit_small.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_medium.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_medium_bday.mdl")
				|| !strcmp(pszModelName, "models/props_halloween/halloween_medkit_medium.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_large.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_large_bday.mdl")
				|| !strcmp(pszModelName, "models/props_halloween/halloween_medkit_large.mdl")
				&& pLocal->GetHealth() < pLocal->GetMaxHealth())
			{

				Vector entPos;
				pEnt->GetWorldSpaceCenter(entPos);
				Vector eyePos = pLocal->GetEyePosition();

				float dist = Util->flGetDistance(entPos, eyePos);

				if (dist < 9.5)
				{
					RemoveConds(pLocal, pCommand, gCvars.removecond_value);
				}

			}
			if (!strcmp(pszModelName, "models/items/ammopack_small.mdl")
				|| !strcmp(pszModelName, "models/items/ammopack_small_bday.mdl")
				|| !strcmp(pszModelName, "models/items/ammopack_medium.mdl")
				|| !strcmp(pszModelName, "models/items/ammopack_medium_bday.mdl"))
			{
				Vector entPos;
				pEnt->GetWorldSpaceCenter(entPos);
				Vector eyePos = pLocal->GetEyePosition();

				float dist = Util->flGetDistance(entPos, eyePos);

				if (dist < 9.5)
				{
					RemoveConds(pLocal, pCommand, gCvars.removecond_value);
				}
			}
		}
	}

	if (gCvars.removecond_stickyspam)
	{
		/*
		
		Alright so this worked perfectly and beautifully in my cheat, but it's not working as intended here, dunno why
		if anyone wants to try to fix this, go ahead, I didn't have enough time to do so :3333

		- Castle, professional NASA coder hired in 1894 
		also credits bencat retard - plasma 

		*/


		if (pLocal->szGetClass() != "Demoman")
			return;

		CBaseCombatWeapon *wep = pLocal->GetActiveWeapon();
		if (!wep)
			return;

		if (wep->GetItemDefinitionIndex() != WPN_StickyLauncher
			&& wep->GetItemDefinitionIndex() != WPN_ScottishResistance
			&& wep->GetItemDefinitionIndex() != WPN_StickyJumper
			&& wep->GetItemDefinitionIndex() != WPN_LoooseCannon)
			return;

		static bool bSwitch = false;
		if ((pCommand->buttons & IN_ATTACK) && !bSwitch)
		{
			bSwitch = true;
		}
		else if (bSwitch)
		{
			RemoveConds(pLocal, pCommand, 50);
			pCommand->buttons &= ~IN_ATTACK;
			bSwitch = false;
		}
	}
}
void RemoveCondExploits::RemoveConds(CBaseEntity * local, CUserCmd * cmd, int value, bool disableattack)
{
	if (local == NULL) return;

	/*if(!cmd) return;
	if(!cmd->command_number) return;*/
	//if(!var.value) return;

	if (local->GetLifeState() != LIFE_ALIVE) return;

	if (disableattack)
		if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2) return;

	INetChannel* ch = (INetChannel*)gInts.Engine->GetNetChannelInfo();
	int& m_nOutSequenceNr = *(int*)((unsigned)ch + 8);
	m_nOutSequenceNr += value;
}

void RemoveCondExploits::RemoveConds(CBaseEntity *local, int value)
{
	RemoveConds(local, new CUserCmd(), value);
}








#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class slarchc {
public:
	double fjfkbzpu;
	double ejocy;
	int yujuewgahwtlmjh;
	bool erwzeovjuinu;
	slarchc();
	bool ijuminyzjautshjqhmy(double btfeetxe, int ywoavbvv, double fethejy, double ezzlh, bool bkdhwcomjxy, double mjnxzdqxazvbdwv, bool qrrlxkwacp, bool xevrtxzrpowvds, string rdnqfbwspq);
	void fhltobtbeigpcjupsko(int qhtfpmxtvwlcl, string auonc, string vbbipazgc, double dpaqqr);
	void wtaohfrbvhjduaehkxdryf(int cluvskoycgwaj);
	bool dnlgvenrqnixyldgblveep(int loyofvax, string qyirauvstf, double ternmlo, bool azcasomf);
	double qhkhkbqvjdvnvwx(int coekthlic, string bhhpp, int gjkcrkwmt, string bikhcajrpbnza, bool nsmyrougudjhw, int imrdjl, string enyxky);
	double rszgeoitqcdskantfit(double ougohzucronsu, bool ixpwaipcswuxu, double issrhclydayqo, int jixpqon, int twxfra, string bfderouvkssyuz, string oxfyvpo, string jziewukxytk, string kjphandmp);
	bool jmvkwumgnekhjwntlnwoqinee(string ypzalouo, bool jtawjzncdqeq, int sfblai, bool kjsbuqcywiieu, bool sbpzafncg, string uvgeuhvfmezpm);
	int xrnvimdiqunofxag(double isleanwkmtra, int xrcexz, bool hkrrsni, string kwhqvkdvxokcltg);
	void fbunbpyhwmbqvbmkfskcnrc(int cbdbvsgq, bool hujbfkywfhe);

protected:
	bool tkgtkhgymypnk;
	double kjbpwmxapavl;
	double jaxdqt;
	double omqhanjrgmldx;

	int wzqlezsiumgarediyktbn(int foazhnohrtmh);
	bool pqfxhbgmyqg(double jqqvehbdmm, int iptkyguuiw, int qjwkjf, double xqhhhs, double yrcbgvtanjcxbu);
	bool xkygnwytcvoqppsrm();
	int mstttwmrirnta(string tmrzt, int giwbjek, int mknirkbmjq, int loohkkhnic, bool ktjpdnuyjzbirr, string pkxzcbnm, int kayxmicc);
	string mckhflcnubdppurhymg(double juxznzjs);
	bool mqmnwsankoyupsz(bool athcihzn, string ozxborip);
	void lielxzrymrevtsbddwuk();
	void shfikeeyic(double qtrazh, string zjxjhkyyzlpsvjw, double xtsby, string jnshsgerewrpuqx, double kqavsorujyllczp, string ojqotskj);
	double qxqzopkwkqzlirht(bool ynudbqchopsrbp);
	void pyjxnwootjubxe(string oycmwvawqm, string xherzdpr);

private:
	double keynwlcznzrdnzy;

	int vhtotosulmnhrtc(bool awureje);
	bool pkcqcxefwdhviawom(double oktkaichqr, int dodlhwl, bool zltxsr);
	double bbtgrwhiqhov(int fdremdlgssgjzp, int atxyspflgwe);
	string rvvfngzhdammynlqd(bool kmnfmquezjzs, string jlpekhwxvisxa, double nisjlmhbqlst, bool lykddawdjn);
	bool dpuclvezhbfddkrnrikqpgjc(double guyjvdo, double sxgnxqeevwkiob, bool fmuhobmpbrvzfbf, bool feyqqtytsn);
	void cvlqllhshlqvpaqmxbdv(bool wywoamubp, double wpigomftfho, double cflhrxkwo);
	bool csrkjotbooh();

};


int slarchc::vhtotosulmnhrtc(bool awureje) {
	int eszqlao = 3040;
	bool fzwrrshgug = true;
	double uognqbajpvlxpex = 10959;
	bool ydiedqi = false;
	bool enehhollq = false;
	if (10959 == 10959) {
		int yr;
		for (yr = 48; yr > 0; yr--) {
			continue;
		}
	}
	if (10959 == 10959) {
		int xmtawzbu;
		for (xmtawzbu = 6; xmtawzbu > 0; xmtawzbu--) {
			continue;
		}
	}
	if (10959 == 10959) {
		int rapurmqtzu;
		for (rapurmqtzu = 91; rapurmqtzu > 0; rapurmqtzu--) {
			continue;
		}
	}
	if (3040 != 3040) {
		int swuzhcaj;
		for (swuzhcaj = 45; swuzhcaj > 0; swuzhcaj--) {
			continue;
		}
	}
	return 3000;
}

bool slarchc::pkcqcxefwdhviawom(double oktkaichqr, int dodlhwl, bool zltxsr) {
	double ksvjluabfuwzxt = 67135;
	int tfvugvcyeawiyoq = 7276;
	int ukfstmudzmeqz = 837;
	string lszlqywat = "xqnkjzciqubbhqjoekhrlypcyigbkfrukifsweyedrcluwnmymrdyynogespbf";
	int xyuadydm = 836;
	string izpbztlfspeed = "kpujlkkpeadjdkpvcxwmtlgpbbrlsaaqvenaifrrelxngqsieihouwwbunyagmvhetvseuphfqpdohfgpycvd";
	string ewfgnizlklvtdlo = "kupbnfhmrflupyjqakixlagmejgthqfuiaqbpggfzwcogcckrkcokfnjgcsqrfdwepjmnccyfxpgkgtxviqbs";
	bool xvvpgg = true;
	string mmnjivkqyh = "vpaueeen";
	double dftbjmrua = 5048;
	return false;
}

double slarchc::bbtgrwhiqhov(int fdremdlgssgjzp, int atxyspflgwe) {
	bool owyiiamfww = true;
	double zedxvkuoisbgrx = 9772;
	bool ovuxwd = false;
	int fiiubjlgxor = 1108;
	double uusxuahflznkq = 60028;
	double xkgni = 7448;
	int nwikltgem = 4401;
	if (9772 == 9772) {
		int svwcc;
		for (svwcc = 73; svwcc > 0; svwcc--) {
			continue;
		}
	}
	if (60028 != 60028) {
		int jmf;
		for (jmf = 0; jmf > 0; jmf--) {
			continue;
		}
	}
	if (9772 != 9772) {
		int ecsvtkwjr;
		for (ecsvtkwjr = 37; ecsvtkwjr > 0; ecsvtkwjr--) {
			continue;
		}
	}
	return 93869;
}

string slarchc::rvvfngzhdammynlqd(bool kmnfmquezjzs, string jlpekhwxvisxa, double nisjlmhbqlst, bool lykddawdjn) {
	string fwlmruu = "qyglqowwblmjldbdbtiyodwxjogegvaefuokgnjqhdfcfnvidnbfucszf";
	string njikp = "zeldocuqophxspngkhcctlnjplxbhhduzlzqicjmuirsqhgqcnmfwgekvv";
	int hjubwpjckudgmh = 1129;
	int nffkzzsqxmuf = 333;
	double vudqzfgzaw = 34403;
	int uoxhinnog = 1959;
	string uxwzyszcvyi = "beopnefljestxcovyugakipnnry";
	string liuxirgkhavvb = "ydlwzrgxwwsdeprmlhyzhcatdsfxrqbdxobpczazjzatzvoxdirirhajgnzjvlhrbcylattcdqj";
	string pgfidwikoxkvjt = "exrjbmqzzxtzkdrfuszjfdgjrhtijtlx";
	if (string("beopnefljestxcovyugakipnnry") == string("beopnefljestxcovyugakipnnry")) {
		int qm;
		for (qm = 46; qm > 0; qm--) {
			continue;
		}
	}
	if (1959 != 1959) {
		int ysiitmw;
		for (ysiitmw = 50; ysiitmw > 0; ysiitmw--) {
			continue;
		}
	}
	if (34403 != 34403) {
		int fxjeotupgo;
		for (fxjeotupgo = 6; fxjeotupgo > 0; fxjeotupgo--) {
			continue;
		}
	}
	if (1129 == 1129) {
		int ldvlg;
		for (ldvlg = 21; ldvlg > 0; ldvlg--) {
			continue;
		}
	}
	if (333 != 333) {
		int oxgokstp;
		for (oxgokstp = 40; oxgokstp > 0; oxgokstp--) {
			continue;
		}
	}
	return string("hfiuowltfrnrhivd");
}

bool slarchc::dpuclvezhbfddkrnrikqpgjc(double guyjvdo, double sxgnxqeevwkiob, bool fmuhobmpbrvzfbf, bool feyqqtytsn) {
	string cxoyziercqxfbx = "yaefebpxbrlfaazqnvimkotxhgtbpfeompygu";
	bool ixqodjrdadkqqr = true;
	double wadymrdumyahgfm = 11507;
	bool fokeuxirtjczshe = false;
	double beqmoutwo = 33108;
	bool njisxi = false;
	double wzqnbpjrzhqyr = 17431;
	double arqzecgiyejroc = 74230;
	string akbdrfzarjs = "mtdqxlvbhynobnytchjttulrjimpxthwhntgfvszwhclcxtcznxwgdgirvztkuxybfqbjlsodkdefshpxjyplnvzzzblillojx";
	bool zjywxisxocu = false;
	if (33108 != 33108) {
		int rpohgaon;
		for (rpohgaon = 39; rpohgaon > 0; rpohgaon--) {
			continue;
		}
	}
	if (11507 == 11507) {
		int ecpzesjftz;
		for (ecpzesjftz = 70; ecpzesjftz > 0; ecpzesjftz--) {
			continue;
		}
	}
	if (74230 != 74230) {
		int ywh;
		for (ywh = 11; ywh > 0; ywh--) {
			continue;
		}
	}
	return false;
}

void slarchc::cvlqllhshlqvpaqmxbdv(bool wywoamubp, double wpigomftfho, double cflhrxkwo) {
	int irnrszdwgrzfoyg = 1598;
	string dzfgryqlzkry = "heivrgxcrqlwtmowlr";
	double ghmxbteh = 56801;
	string wzbxwrfsq = "hasssetvzusavjpvrgiiggkgpnnagjvlpokxamoyftomfqvwzrdcwasmuphrlivfzztcdamwlpizdrbjcfvqyhsoagsvf";
	double hewrtqmljgcuum = 8321;
	int chowwfy = 162;
	bool lrzwodrwmholxc = false;
	string wduap = "xmdjrxqbsgsqlsoxwczohj";

}

bool slarchc::csrkjotbooh() {
	double mhsetw = 4471;
	string rakvwbzfmpv = "pvfxqledclrvsskzfzcuowmjh";
	bool hdkquednb = false;
	int qeapnfcipuypit = 3421;
	bool hxjethimrb = true;
	if (4471 != 4471) {
		int bvulhmgd;
		for (bvulhmgd = 19; bvulhmgd > 0; bvulhmgd--) {
			continue;
		}
	}
	if (false == false) {
		int qjfcpl;
		for (qjfcpl = 58; qjfcpl > 0; qjfcpl--) {
			continue;
		}
	}
	if (4471 == 4471) {
		int cmk;
		for (cmk = 59; cmk > 0; cmk--) {
			continue;
		}
	}
	if (true == true) {
		int lxzyeykmv;
		for (lxzyeykmv = 17; lxzyeykmv > 0; lxzyeykmv--) {
			continue;
		}
	}
	return false;
}

int slarchc::wzqlezsiumgarediyktbn(int foazhnohrtmh) {
	double azthqwqijzrt = 21821;
	double urmyyghu = 53358;
	int maflbk = 817;
	int pdnfvunapq = 3979;
	bool ajssqemulcmo = true;
	string pvhyvpuqwznv = "jlapvvznjvpnzgzusglxurfekmicgsqzwxobwapsscqxcswtzolykgp";
	if (21821 == 21821) {
		int jyygnrz;
		for (jyygnrz = 79; jyygnrz > 0; jyygnrz--) {
			continue;
		}
	}
	if (21821 != 21821) {
		int cwbtj;
		for (cwbtj = 5; cwbtj > 0; cwbtj--) {
			continue;
		}
	}
	if (true == true) {
		int crr;
		for (crr = 31; crr > 0; crr--) {
			continue;
		}
	}
	if (true != true) {
		int vz;
		for (vz = 94; vz > 0; vz--) {
			continue;
		}
	}
	if (817 == 817) {
		int dw;
		for (dw = 19; dw > 0; dw--) {
			continue;
		}
	}
	return 15533;
}

bool slarchc::pqfxhbgmyqg(double jqqvehbdmm, int iptkyguuiw, int qjwkjf, double xqhhhs, double yrcbgvtanjcxbu) {
	int pkddsxjini = 1175;
	double kwnmetojobvsy = 3333;
	int jbkdew = 1289;
	string yxyzj = "avurpqqhutfxdhatkkkjbfgmtylncpjtrvqxlykxoxozusqgcxgurpnsoyirfjxabfv";
	string aytwpwvwai = "cmohblesadjhi";
	bool atstinruywzlmjv = true;
	int psqvueua = 151;
	bool qcjiwqy = true;
	bool cnnjdy = false;
	if (true != true) {
		int oqs;
		for (oqs = 57; oqs > 0; oqs--) {
			continue;
		}
	}
	if (3333 == 3333) {
		int loowbhfvr;
		for (loowbhfvr = 36; loowbhfvr > 0; loowbhfvr--) {
			continue;
		}
	}
	if (1289 == 1289) {
		int ofuidwt;
		for (ofuidwt = 17; ofuidwt > 0; ofuidwt--) {
			continue;
		}
	}
	if (3333 != 3333) {
		int vkkb;
		for (vkkb = 8; vkkb > 0; vkkb--) {
			continue;
		}
	}
	if (true == true) {
		int kmgucg;
		for (kmgucg = 35; kmgucg > 0; kmgucg--) {
			continue;
		}
	}
	return false;
}

bool slarchc::xkygnwytcvoqppsrm() {
	double vbrvptkm = 7440;
	bool nztqaep = true;
	bool jpgyr = false;
	double uymedmh = 66154;
	double aandibk = 2650;
	int snhcjxxrvjmmwo = 2403;
	bool jaozijndzgxe = true;
	if (true != true) {
		int iiqxsen;
		for (iiqxsen = 94; iiqxsen > 0; iiqxsen--) {
			continue;
		}
	}
	return true;
}

int slarchc::mstttwmrirnta(string tmrzt, int giwbjek, int mknirkbmjq, int loohkkhnic, bool ktjpdnuyjzbirr, string pkxzcbnm, int kayxmicc) {
	int venhvpelgmpxgnn = 341;
	if (341 != 341) {
		int lhzvvn;
		for (lhzvvn = 98; lhzvvn > 0; lhzvvn--) {
			continue;
		}
	}
	if (341 != 341) {
		int taietqnfbe;
		for (taietqnfbe = 65; taietqnfbe > 0; taietqnfbe--) {
			continue;
		}
	}
	return 44442;
}

string slarchc::mckhflcnubdppurhymg(double juxznzjs) {
	string vteas = "sdvacgzknbnlnsczazunlomtdavqyqzoav";
	double gzugncqzdygzknm = 9684;
	bool fraqpfuwnrixzs = true;
	bool ulokidyr = false;
	string nesqdq = "oaphjzdfvxazemvrbeqbzdvkwqtzzeagsggtbfktnjeuau";
	string osxdzv = "hxbslfjjulpdpdupbdlllemzyxwoovbcxpvyagqikasfuhaozcjdywsxcomcohudyeizwci";
	bool lodcdputiklcrkg = true;
	int ojomvtwqte = 291;
	int ogjkz = 319;
	string etlupdudnuhmj = "fvsrdvyksnpmxupmsefjjayldxrikphrxizmxwjsrlbneesewmmvoffzjlqv";
	if (319 == 319) {
		int zgullxfk;
		for (zgullxfk = 7; zgullxfk > 0; zgullxfk--) {
			continue;
		}
	}
	if (string("hxbslfjjulpdpdupbdlllemzyxwoovbcxpvyagqikasfuhaozcjdywsxcomcohudyeizwci") == string("hxbslfjjulpdpdupbdlllemzyxwoovbcxpvyagqikasfuhaozcjdywsxcomcohudyeizwci")) {
		int rgzffxxxxz;
		for (rgzffxxxxz = 32; rgzffxxxxz > 0; rgzffxxxxz--) {
			continue;
		}
	}
	if (string("oaphjzdfvxazemvrbeqbzdvkwqtzzeagsggtbfktnjeuau") != string("oaphjzdfvxazemvrbeqbzdvkwqtzzeagsggtbfktnjeuau")) {
		int bnmy;
		for (bnmy = 22; bnmy > 0; bnmy--) {
			continue;
		}
	}
	return string("qyiivzswesksrpvscavr");
}

bool slarchc::mqmnwsankoyupsz(bool athcihzn, string ozxborip) {
	bool bakph = true;
	double otupnehgtl = 14960;
	bool qcrfvqzic = true;
	if (14960 == 14960) {
		int bmqmswsx;
		for (bmqmswsx = 53; bmqmswsx > 0; bmqmswsx--) {
			continue;
		}
	}
	if (14960 == 14960) {
		int swyevggf;
		for (swyevggf = 8; swyevggf > 0; swyevggf--) {
			continue;
		}
	}
	return false;
}

void slarchc::lielxzrymrevtsbddwuk() {
	string xetqblejcbf = "pproocfhyrgpldkyhbtehmchugsfjrlktllpugzu";
	string pgtdsqurtup = "sbaqolsjdqpujycionzmzyfeckhlzpbptokbczuaikhdqqwbmaqcaswsbutdnyiwkykvibqykyar";
	string ngcblestiy = "stgqlguilbxoidqlsjkjrmrpzzlpdrfrpifubvmvusfzkgpdgcutxoal";
	bool ehghtgmwmh = true;
	string kdwzhlatqct = "qnzqamubtavnxjegqnovhcfxjpplxzzfkdcigsjgiziumvrulfnnpityfqgti";
	string weqocsuk = "imqwdfxrqoxbzxfaazxpgrkqehbhrrscrdtcfrmnfesqtcnsjmpebdttnodjbuxzjlkvvrhagqsyl";
	bool ygfitkwwhonpfkz = true;
	if (true == true) {
		int zjk;
		for (zjk = 80; zjk > 0; zjk--) {
			continue;
		}
	}
	if (true != true) {
		int dkds;
		for (dkds = 95; dkds > 0; dkds--) {
			continue;
		}
	}

}

void slarchc::shfikeeyic(double qtrazh, string zjxjhkyyzlpsvjw, double xtsby, string jnshsgerewrpuqx, double kqavsorujyllczp, string ojqotskj) {
	string dbiroy = "pgosiuqpifjhqmuurmovptfjkkwdmaobysx";
	string pzlslcxfyscne = "d";
	double lyhuxvfi = 967;
	double fvxiytciz = 13768;

}

double slarchc::qxqzopkwkqzlirht(bool ynudbqchopsrbp) {
	bool nhphsoiyhiur = false;
	double tlgecxhskqfbo = 46010;
	bool fxmyo = true;
	int cotqwv = 4360;
	return 73462;
}

void slarchc::pyjxnwootjubxe(string oycmwvawqm, string xherzdpr) {
	bool vopnxhdibjth = false;
	double wxmzpmvieahrucy = 1771;
	string gcriazbvrhg = "erxcnsxqtfjtnqgmsxcagshzdvvooaoejfozrcmtlodfaytqlejkhdcih";
	int oteyttzwgcanbne = 5152;
	int shkaaihzaeezns = 2901;
	if (2901 != 2901) {
		int tdtm;
		for (tdtm = 54; tdtm > 0; tdtm--) {
			continue;
		}
	}
	if (false == false) {
		int zfo;
		for (zfo = 3; zfo > 0; zfo--) {
			continue;
		}
	}
	if (1771 == 1771) {
		int wmdmhvts;
		for (wmdmhvts = 63; wmdmhvts > 0; wmdmhvts--) {
			continue;
		}
	}
	if (5152 == 5152) {
		int ioxa;
		for (ioxa = 35; ioxa > 0; ioxa--) {
			continue;
		}
	}

}

bool slarchc::ijuminyzjautshjqhmy(double btfeetxe, int ywoavbvv, double fethejy, double ezzlh, bool bkdhwcomjxy, double mjnxzdqxazvbdwv, bool qrrlxkwacp, bool xevrtxzrpowvds, string rdnqfbwspq) {
	bool pklhuaofm = true;
	if (true != true) {
		int ujooq;
		for (ujooq = 56; ujooq > 0; ujooq--) {
			continue;
		}
	}
	if (true != true) {
		int dqvamudjne;
		for (dqvamudjne = 65; dqvamudjne > 0; dqvamudjne--) {
			continue;
		}
	}
	if (true == true) {
		int gqwoe;
		for (gqwoe = 95; gqwoe > 0; gqwoe--) {
			continue;
		}
	}
	if (true == true) {
		int gqthrsmyro;
		for (gqthrsmyro = 9; gqthrsmyro > 0; gqthrsmyro--) {
			continue;
		}
	}
	return true;
}

void slarchc::fhltobtbeigpcjupsko(int qhtfpmxtvwlcl, string auonc, string vbbipazgc, double dpaqqr) {
	double vjwaaaqdawf = 29508;
	if (29508 != 29508) {
		int fz;
		for (fz = 48; fz > 0; fz--) {
			continue;
		}
	}
	if (29508 != 29508) {
		int qioekxda;
		for (qioekxda = 71; qioekxda > 0; qioekxda--) {
			continue;
		}
	}
	if (29508 == 29508) {
		int vddtm;
		for (vddtm = 45; vddtm > 0; vddtm--) {
			continue;
		}
	}
	if (29508 == 29508) {
		int rpslwe;
		for (rpslwe = 57; rpslwe > 0; rpslwe--) {
			continue;
		}
	}

}

void slarchc::wtaohfrbvhjduaehkxdryf(int cluvskoycgwaj) {
	bool anojslhsxwzb = false;
	string ybbpokfub = "ttapekgmqgtpdtwdngzophdrlbeacqggfuagpxpbethvfnytcvuwhvq";
	double eupxgkkef = 51033;
	double ovtop = 69191;
	string bupgedvi = "fmqxcjcrnqzgictburf";
	double svghkwkqfvsfu = 7737;
	bool xnxjss = false;
	double jqosdahrpp = 2869;
	int nmjdnvewbevlvmt = 5834;
	bool igtkkzcwhwwtw = true;
	if (7737 == 7737) {
		int bgmuzh;
		for (bgmuzh = 77; bgmuzh > 0; bgmuzh--) {
			continue;
		}
	}
	if (false == false) {
		int hrwyl;
		for (hrwyl = 24; hrwyl > 0; hrwyl--) {
			continue;
		}
	}
	if (false == false) {
		int ucafyub;
		for (ucafyub = 76; ucafyub > 0; ucafyub--) {
			continue;
		}
	}
	if (string("ttapekgmqgtpdtwdngzophdrlbeacqggfuagpxpbethvfnytcvuwhvq") != string("ttapekgmqgtpdtwdngzophdrlbeacqggfuagpxpbethvfnytcvuwhvq")) {
		int amkppne;
		for (amkppne = 6; amkppne > 0; amkppne--) {
			continue;
		}
	}

}

bool slarchc::dnlgvenrqnixyldgblveep(int loyofvax, string qyirauvstf, double ternmlo, bool azcasomf) {
	bool sdfrifvj = false;
	int bmyevtbm = 450;
	bool pseihv = true;
	double zarbsntprwx = 2894;
	double isubibtemndzr = 5699;
	bool ujydyv = true;
	bool rksnfzewo = true;
	bool smhwijneobadfr = false;
	string tiyozjfhzpkq = "scpqngzaexa";
	if (string("scpqngzaexa") != string("scpqngzaexa")) {
		int ssxojkwia;
		for (ssxojkwia = 2; ssxojkwia > 0; ssxojkwia--) {
			continue;
		}
	}
	if (true == true) {
		int lcwyvbjy;
		for (lcwyvbjy = 86; lcwyvbjy > 0; lcwyvbjy--) {
			continue;
		}
	}
	if (true != true) {
		int gvgzxaset;
		for (gvgzxaset = 88; gvgzxaset > 0; gvgzxaset--) {
			continue;
		}
	}
	return true;
}

double slarchc::qhkhkbqvjdvnvwx(int coekthlic, string bhhpp, int gjkcrkwmt, string bikhcajrpbnza, bool nsmyrougudjhw, int imrdjl, string enyxky) {
	double auwmqkjssx = 18830;
	string nhssokfogf = "jtqtzjdpcsakrhznosphugwurqjshfrxdsxeocxjlrewzsfnwqylkymjjujyixommaoxugwbvkqgnxdrixcbqzzrmbyzelq";
	bool gyjaatjp = true;
	int qoxghsjttrmxq = 4809;
	string cpnrrou = "jrbchpmsztyzpcdcuboesivbwprhmomiqqhkfvnbrzeszgmsoiybsknlfyfhdapswbtgyteihe";
	double antxfkrzazehi = 39668;
	string ajunzqadjy = "uwnyjmttlkgvudoerhkesiahwgsnsaurfnkyaqjspjbgdbnmakqdxpdfjvbynludmhrhugfqxjccorrwdihivj";
	int vxlccw = 1354;
	int skrfzgodpankod = 5750;
	bool djfbcdnvwtybwu = false;
	if (string("uwnyjmttlkgvudoerhkesiahwgsnsaurfnkyaqjspjbgdbnmakqdxpdfjvbynludmhrhugfqxjccorrwdihivj") != string("uwnyjmttlkgvudoerhkesiahwgsnsaurfnkyaqjspjbgdbnmakqdxpdfjvbynludmhrhugfqxjccorrwdihivj")) {
		int paudybzou;
		for (paudybzou = 60; paudybzou > 0; paudybzou--) {
			continue;
		}
	}
	if (string("jrbchpmsztyzpcdcuboesivbwprhmomiqqhkfvnbrzeszgmsoiybsknlfyfhdapswbtgyteihe") != string("jrbchpmsztyzpcdcuboesivbwprhmomiqqhkfvnbrzeszgmsoiybsknlfyfhdapswbtgyteihe")) {
		int urynfm;
		for (urynfm = 24; urynfm > 0; urynfm--) {
			continue;
		}
	}
	if (4809 == 4809) {
		int enm;
		for (enm = 8; enm > 0; enm--) {
			continue;
		}
	}
	if (5750 != 5750) {
		int utcksna;
		for (utcksna = 22; utcksna > 0; utcksna--) {
			continue;
		}
	}
	if (string("jtqtzjdpcsakrhznosphugwurqjshfrxdsxeocxjlrewzsfnwqylkymjjujyixommaoxugwbvkqgnxdrixcbqzzrmbyzelq") != string("jtqtzjdpcsakrhznosphugwurqjshfrxdsxeocxjlrewzsfnwqylkymjjujyixommaoxugwbvkqgnxdrixcbqzzrmbyzelq")) {
		int knho;
		for (knho = 87; knho > 0; knho--) {
			continue;
		}
	}
	return 16597;
}

double slarchc::rszgeoitqcdskantfit(double ougohzucronsu, bool ixpwaipcswuxu, double issrhclydayqo, int jixpqon, int twxfra, string bfderouvkssyuz, string oxfyvpo, string jziewukxytk, string kjphandmp) {
	double lampa = 47203;
	int waivdskcaczeyol = 8026;
	double owsypkhs = 27044;
	string itctp = "jcwxoexgenznmxgprvl";
	double vdhuh = 1616;
	string pxwlupsx = "mlbqpyindtgrevvrjucnimzl";
	bool nakkevxrineed = true;
	string shhkcjjdxpzw = "wtdkcysmgrbebjufjdefwcguuqdsivldxjtsatrostgrpdylxhtigdvlkvkteo";
	int phluvkxdoqxbpry = 4953;
	bool ycqfnd = true;
	if (1616 != 1616) {
		int ynlfwtx;
		for (ynlfwtx = 3; ynlfwtx > 0; ynlfwtx--) {
			continue;
		}
	}
	if (1616 == 1616) {
		int vi;
		for (vi = 88; vi > 0; vi--) {
			continue;
		}
	}
	return 24761;
}

bool slarchc::jmvkwumgnekhjwntlnwoqinee(string ypzalouo, bool jtawjzncdqeq, int sfblai, bool kjsbuqcywiieu, bool sbpzafncg, string uvgeuhvfmezpm) {
	double fhzfwr = 27777;
	int myawnceknujf = 4940;
	int mylekkxtybk = 2703;
	bool qsvtlpghgscaw = true;
	double sgjvpkitylvseya = 46836;
	bool ttxktywrqupgdv = false;
	bool nbnuyr = false;
	if (4940 == 4940) {
		int po;
		for (po = 29; po > 0; po--) {
			continue;
		}
	}
	if (27777 == 27777) {
		int bjkx;
		for (bjkx = 4; bjkx > 0; bjkx--) {
			continue;
		}
	}
	return false;
}

int slarchc::xrnvimdiqunofxag(double isleanwkmtra, int xrcexz, bool hkrrsni, string kwhqvkdvxokcltg) {
	int stzmpj = 2942;
	double xrqfgsistz = 6651;
	string skamcazfpvegcjh = "yirboyrpkpxwgnsgbjxlyp";
	string dcynklziekq = "lehbjlvzqucgnviy";
	bool zhdfsnpb = true;
	string jjqrp = "awqzhf";
	double frzpwycroyc = 40707;
	string borycgdi = "rfaghxbhfilvcfqhywackunzrnrsrhulolumuhwbdzbsmiaojpajkxeakyubkjhkzklhlhezf";
	double lhztcik = 12809;
	int xvmatman = 9563;
	if (12809 == 12809) {
		int udcfupz;
		for (udcfupz = 52; udcfupz > 0; udcfupz--) {
			continue;
		}
	}
	if (string("rfaghxbhfilvcfqhywackunzrnrsrhulolumuhwbdzbsmiaojpajkxeakyubkjhkzklhlhezf") == string("rfaghxbhfilvcfqhywackunzrnrsrhulolumuhwbdzbsmiaojpajkxeakyubkjhkzklhlhezf")) {
		int osccprzg;
		for (osccprzg = 65; osccprzg > 0; osccprzg--) {
			continue;
		}
	}
	if (string("lehbjlvzqucgnviy") == string("lehbjlvzqucgnviy")) {
		int ijcfycq;
		for (ijcfycq = 82; ijcfycq > 0; ijcfycq--) {
			continue;
		}
	}
	return 66262;
}

void slarchc::fbunbpyhwmbqvbmkfskcnrc(int cbdbvsgq, bool hujbfkywfhe) {
	int eudugypzhc = 2896;
	int mfrfdekivyg = 2801;
	int imguzwzkbb = 47;
	int avpeajpgukvgi = 2296;
	double ttmcailbmmodyoq = 22584;
	double seojiv = 16384;
	double whvnpktayzj = 4067;
	double ejgxb = 16944;
	double ntlobvnxc = 45429;
	if (2801 != 2801) {
		int fkz;
		for (fkz = 76; fkz > 0; fkz--) {
			continue;
		}
	}
	if (2296 == 2296) {
		int vtzayqr;
		for (vtzayqr = 42; vtzayqr > 0; vtzayqr--) {
			continue;
		}
	}
	if (2296 == 2296) {
		int njfj;
		for (njfj = 45; njfj > 0; njfj--) {
			continue;
		}
	}

}

slarchc::slarchc() {
	this->ijuminyzjautshjqhmy(55193, 910, 8610, 1323, false, 17805, false, false, string("ouvogvzkcdhpypnfekkxqkgczzkhxwbtawzddftuslpcu"));
	this->fhltobtbeigpcjupsko(1408, string("nqerbywkccxsnblmixrjhzemvtgkxjstqonysqkmaaphhcqthcswsremycothcebbrjqyxnp"), string("dehhkrtq"), 13028);
	this->wtaohfrbvhjduaehkxdryf(1013);
	this->dnlgvenrqnixyldgblveep(2446, string("titltlxanlsgjdnykbxechlwxjszhoiateuidlsvnbjrjskjpszuogajawguhykpaapxxuqmplhuzu"), 49355, true);
	this->qhkhkbqvjdvnvwx(1497, string("oklmjhyinyyumlrimnoxsbeofkezbrutgvojnrvnqguyqlfymzfykczagprjrsiosyrcc"), 1132, string("xyyoyyusmagvrfwvrhvyjwikgopjbjpqusbnwfbmczv"), false, 1059, string("oufsyevvdpscddkhkpjbfzgfhnmyhauzwthyrzuzdvosgajzilysjwswnwznyblwisjtneoqyrocicypdruxgqfo"));
	this->rszgeoitqcdskantfit(12287, false, 43394, 4317, 1988, string("ivhxzujfhefhajsrefjwwuupaqhjikojaleyxxsrlwgbwovesrhlivghdlbeomuqicidhpmjaht"), string("ywofgnozccxposfhxlahjexwenhrqjxxqfwqhozwqkfellwrpitz"), string("jihvogomzldztrmanjyyescerglqbrshagm"), string("rqqtbtnslkrgwvkeslmfbncphmjvbhyrekvnnmgmcqlrkutvktapvaqrhjxekmzicpjbzsqjqfmibwfzgrkg"));
	this->jmvkwumgnekhjwntlnwoqinee(string("sqkmbgxgczjemvyzjkvvnnbidugokykxthdddnfogxosgnfkrtctmzpyyt"), true, 1331, false, false, string("kxlvwutqhungkandilhuamiedvqizyikxdrgjfqiutjlrxbtnidbmluilefsttinouujucvxdpvcdfxtgotgfojzqqlscnobwsor"));
	this->xrnvimdiqunofxag(11149, 6014, false, string("emvmtzcuuzycebzmmuvdqezoefjdakazpncolcsil"));
	this->fbunbpyhwmbqvbmkfskcnrc(7484, false);
	this->wzqlezsiumgarediyktbn(5525);
	this->pqfxhbgmyqg(14736, 835, 1337, 75485, 14313);
	this->xkygnwytcvoqppsrm();
	this->mstttwmrirnta(string("jjugsupebcjkvlx"), 1307, 6595, 3985, false, string("ztcplzydekwpsqfjwjtpqklcfvzegvajwhyivemyetprhqiggcwtweuldgsiwmvpcvpbbxicpi"), 102);
	this->mckhflcnubdppurhymg(40709);
	this->mqmnwsankoyupsz(true, string("xjzlwctwsiwwekfopaccuugpdmxrpaeilrrcoxakxzqmovsyqtgzsdvkvvimatuptshkumvsnsvkfqdjc"));
	this->lielxzrymrevtsbddwuk();
	this->shfikeeyic(30680, string("efhp"), 13198, string("nqsdiigivqhp"), 63263, string("owqnxfwtibkyuljx"));
	this->qxqzopkwkqzlirht(true);
	this->pyjxnwootjubxe(string("lkjgryqpljgvalvyedxmtkqqjgykwnjev"), string("uvkvjntczztibcykxwrazlnknsrdsfryrdtxedpdohjcqmwzwfxxmydlqxhahuvfjqsqfrcridnkunyqpyaypxcjoseotbzz"));
	this->vhtotosulmnhrtc(true);
	this->pkcqcxefwdhviawom(21566, 2326, true);
	this->bbtgrwhiqhov(3624, 317);
	this->rvvfngzhdammynlqd(false, string("cgxqbeigikquartlsfcblmjbuqkqru"), 17009, false);
	this->dpuclvezhbfddkrnrikqpgjc(21254, 2749, false, true);
	this->cvlqllhshlqvpaqmxbdv(false, 1916, 38795);
	this->csrkjotbooh();
}
