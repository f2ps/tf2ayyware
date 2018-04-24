#include "Aimbot.h"
#include "Util.h"

CAimbot gAim;

void CAimbot::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	gCvars.iAimbotIndex = -1;

	if (!gCvars.aimbot_active)
		return;

	if (!Util->IsKeyPressed(gCvars.aimbot_key))
		return;

	if (!pLocal->GetActiveWeapon())
		return;

	if (gCvars.aimbot_zoomedonly &&
		pLocal->GetClassNum() == TF2_Sniper &&
		Util->IsHeadshotWeapon(pLocal, pLocal->GetActiveWeapon()) &&
		!(pLocal->GetCond() & TFCond_Zoomed))
		return;

	CBaseEntity* pEntity = GetBaseEntity(GetBestTarget(pLocal));

	if (!pEntity)
		return;

	int iBestHitbox = GetBestHitbox(pLocal, pEntity);

	if (iBestHitbox == -1)
		return;

	Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox);

	Vector vLocal = pLocal->GetEyePosition();

	Vector vAngs, dAngs, sAngs;
	VectorAngles((vEntity - vLocal), vAngs);

	ClampAngle(vAngs);
	gCvars.iAimbotIndex = pEntity->GetIndex();

	if (gCvars.aimbot_smooth) // Thanks to gir489 for coding and Castle for sharing
	{
		unsigned int smoothValue = 10;
		Vector lAngs = gInts.Engine->GetViewAngles();

		dAngs = vAngs - lAngs;
		ClampAngle(dAngs);

		sAngs = lAngs + dAngs / 100.f * smoothValue;
		ClampAngle(sAngs);

		pCommand->viewangles = sAngs;
		gInts.Engine->SetViewAngles(pCommand->viewangles);
	}

	else
	{
		if (gCvars.aimbot_silent)
		{
			MovementFix(pCommand, vAngs);
			pCommand->viewangles = vAngs; // Nothing fancy, just client-sided.
		}

		else
		{
			pCommand->viewangles = vAngs;
			gInts.Engine->SetViewAngles(pCommand->viewangles);
		}
	}

	if (gCvars.aimbot_autoshoot)
	{
		if (pLocal->GetCond() & TFCond_Zoomed && !Util->IsReadyToHeadshot(pLocal->GetActiveWeapon()))
			return;

		pCommand->buttons |= IN_ATTACK;
	}
}

int CAimbot::GetBestTarget(CBaseEntity* pLocal)
{
	int iBestTarget = -1;

	float flDistToBest = 8192.f;

	Vector vLocal = pLocal->GetEyePosition();

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;

		CBaseEntity* pEntity = GetBaseEntity(i);

		if (!pEntity)
			continue;

		if (pEntity->IsDormant())
			continue;

		if (pEntity->GetLifeState() != LIFE_ALIVE ||
			pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		int iBestHitbox = GetBestHitbox(pLocal, pEntity);

		if (iBestHitbox == -1)
			continue;

		Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox);

		if (!gCvars.PlayerMode[i])
			continue;

		if (pEntity->GetCond() & TFCond_Ubercharged ||
			pEntity->GetCond() & TFCond_UberchargeFading ||
			pEntity->GetCond() & TFCond_Bonked)
			continue;

		if (gCvars.aimbot_ignore_cloak && pEntity->GetCond() & TFCond_Cloaked)
			continue;

		float flDistToTarget = (vLocal - vEntity).Length();

		if (flDistToTarget < flDistToBest)
		{
			flDistToBest = flDistToTarget;
			iBestTarget = i;
		}

		if (gCvars.PlayerMode[i] == 2) // Rage targets are the first priorities
			return i;
	}

	return iBestTarget;
}

int CAimbot::GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	int iBestHitbox = -1;

	if (!gCvars.aimbot_hitbox)
	{
		if (Util->IsHeadshotWeapon(pLocal, pLocal->GetActiveWeapon()))
			iBestHitbox = 0;
		else
			iBestHitbox = 4;
	}
	else
	{
		iBestHitbox = gCvars.aimbot_hitbox - 1;
	}

	if (gCvars.aimbot_hitscan)
	{
		for (int i = 0; i < 17; i++)
		{
			if (Util->IsVisible(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(i)))
				return i;
		}
	}

	if (pEntity->GetHitboxPosition(iBestHitbox).IsZero())
		return -1;

	if (!Util->IsVisible(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(iBestHitbox)))
		return -1;

	return iBestHitbox;
}

void CAimbot::MovementFix(CUserCmd *cmd, Vector angles) // Thanks to F1ssi0N for coding and plasma for sharing
{
	Vector vecSilent(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);

	Vector angMove;
	VectorAngles(vecSilent, angMove);

	float flYaw = DEG2RAD(angles.y - cmd->viewangles.y + angMove.y);

	cmd->forwardmove = cos(flYaw) * flSpeed;
	cmd->sidemove = sin(flYaw) * flSpeed;
}




















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ldkcgdu {
public:
	double bwsdvwybpa;
	bool frqtezyrv;
	int vezhipu;
	ldkcgdu();
	double tcyegepeehdbzypaxscdis(double hfdtmszh, bool psqdpixa, int mbimjhlmwfxfjv);
	void rnchwcdxyfieun(int ebhpspttjggvp);
	bool vgstpzvdxbpaodqrd(int jsyvgcjphdh);
	string gythhvnlqescm(double ukblxftmhkpxfdi, bool dkjfvztxmfvsuy, string qpxapzwvx, int nwxmkrumyzu, int jtlersrh, bool zdiky, int ptbsjxbllgd, string whefzdyrhl, bool peomssergvrc, double etdesfujywhdx);
	string xebedxjzcnmsourdpqvva();
	bool ehrgppwqovckscjlzwwkn(int slqlcpfjytx, double prlut, int kxuihfjdamsu, string nrhrndejsjswuqw, int rkhyx, double qkzljedzktd, double eyrrytvdduadve);
	double csvoqdnihfrqxk(bool eckpaxw, int sxtju, int gfuvgeweknjusad, bool qynioyfydvlvw, string svzujt, string fgjjs, int gwwezmkxyigeldd, int mnvdflp, int rdpxzhkfe);
	void hijzzeujatmpxtnrattw(double ylbphpdvtlikzgt, bool hqkjhdoylijcal, double cykvqt, string tkeyy, bool cpfygjpl, string nvqhi);

protected:
	string cekhkrus;
	double fsnyblopoirnwz;
	string pbgpzqlmclq;

	string kcausyaatgxgvwsqwghq(string ucfarspe, int zozbebpkhzomfw, double gnjpbfv, bool xqmuscojnjec, bool rjtlsx, bool mfbfwvkaqbjuaq, int tdjnlhg, bool rxsstxnjjvlb, double aqxaxcaetysmtwh);
	int raazvlqauikgkidmibngthkxp(double wrcglmafta, string xkppac);
	void htlmmrsfgy(int wecqdea, bool porclkxhfkfh, int jfcgt, bool pnvfibt);
	void wvjshassvgbgsosx(double zwbkqyukd, double aabcdpmkjdqajdl, string mtqekbgcqt, double xvhwqph, bool krdfyyrvdlil, string pjypzxapzfma, string qqefzluvjgkv, int hucikxqmqblu, double xtooxeqjiaxe, int xurjchsv);
	string mvihrdunjkjltjrq(int zeggphgrnv, string isbddtcvbb, double akdhbe, double kouekdix, string yvzvaaltgdy, string ywoxx, bool cpkdjmxbi, int qzvazojjbmqdsqc);
	void tvvrlsrurtvxyijx(string uzecgavchwrqp, int zqbnkofxiio, string pppwbvnnncrv);
	bool bbuptnmmhukuddue(bool eucjvhogsffw);
	bool ewnpsdvuwf(bool mqgkniwy, bool nxvxroirt, bool lwrlsfisuzkwfek);
	void jdqzlytgqddv(int rqzouvfswcybvha, string rsqcmxxykffxj, int pcjkyffd, int uydqatylroy);
	void oatquexfltb(bool mbmtzt, bool mcnrwxvhjccfug, double qeennmyghv, string vxxnyo, int rglhew, string yzsigtoupxs, string cqiaefznfgbs);

private:
	string jjwcjttni;
	double gwlmvyvm;
	double hbuzumqh;
	string ndppncwrwhvyie;
	double aowuvsf;

	int kafnsypyenwtfmmjipbw(string ylxpkfkuoxgsvsa, string jqdkdju, bool muyjuvte, int fqdens, double vuvocdok, int qlsnh, string xrtlrzjrtbfzig);
	double jvcqoanmolkits();
	double bkzacuynqxorrjlfpotxdwz();
	double odcdlrgmefzoycmhxtqrbk();
	bool vduntjwrtcfpdxdumdiwignm(double ihsiij, double gmhppkpzcv, int xibfihak);
	string eqlvsesmkdi(string ppxxdk, int iywip, bool aitzofkek, string sabgduuojr, int klkvem, string ccxwgb, double hlvlbawrxke, string dddzcxn, int daact);

};


int ldkcgdu::kafnsypyenwtfmmjipbw(string ylxpkfkuoxgsvsa, string jqdkdju, bool muyjuvte, int fqdens, double vuvocdok, int qlsnh, string xrtlrzjrtbfzig) {
	return 13724;
}

double ldkcgdu::jvcqoanmolkits() {
	return 1354;
}

double ldkcgdu::bkzacuynqxorrjlfpotxdwz() {
	bool brnmrhkfaay = true;
	int hqipmhj = 2319;
	bool rwxskumboxgsp = true;
	bool ecewhlnjoxq = true;
	bool iofperthkj = false;
	double zmwkmqgfvsa = 41797;
	double hrfvltvsj = 11756;
	string raaubcuqvuqy = "fobfkygeslpeyucaehdgcyntkeiberwsytwypjvzkldkyyadpvhdpcetqms";
	if (true == true) {
		int fwl;
		for (fwl = 47; fwl > 0; fwl--) {
			continue;
		}
	}
	if (false == false) {
		int osozbzzwj;
		for (osozbzzwj = 86; osozbzzwj > 0; osozbzzwj--) {
			continue;
		}
	}
	if (false == false) {
		int igzatzbe;
		for (igzatzbe = 78; igzatzbe > 0; igzatzbe--) {
			continue;
		}
	}
	if (41797 == 41797) {
		int dldemgmvqh;
		for (dldemgmvqh = 45; dldemgmvqh > 0; dldemgmvqh--) {
			continue;
		}
	}
	return 27934;
}

double ldkcgdu::odcdlrgmefzoycmhxtqrbk() {
	bool ginyfqzj = false;
	double kfmjxsmhwo = 4633;
	string rlpawzajenjoimr = "hnzwqywbzxnt";
	double xqhupdwun = 8060;
	string ipfxipjzedll = "sucufjwmdnd";
	if (string("sucufjwmdnd") != string("sucufjwmdnd")) {
		int btwktqbu;
		for (btwktqbu = 78; btwktqbu > 0; btwktqbu--) {
			continue;
		}
	}
	return 93361;
}

bool ldkcgdu::vduntjwrtcfpdxdumdiwignm(double ihsiij, double gmhppkpzcv, int xibfihak) {
	double eqmmqvsuw = 6277;
	if (6277 != 6277) {
		int wmnvl;
		for (wmnvl = 25; wmnvl > 0; wmnvl--) {
			continue;
		}
	}
	if (6277 != 6277) {
		int vvvzxnygl;
		for (vvvzxnygl = 30; vvvzxnygl > 0; vvvzxnygl--) {
			continue;
		}
	}
	if (6277 != 6277) {
		int njb;
		for (njb = 72; njb > 0; njb--) {
			continue;
		}
	}
	return false;
}

string ldkcgdu::eqlvsesmkdi(string ppxxdk, int iywip, bool aitzofkek, string sabgduuojr, int klkvem, string ccxwgb, double hlvlbawrxke, string dddzcxn, int daact) {
	double yfuenadrgpgv = 36912;
	return string("tpoovhj");
}

string ldkcgdu::kcausyaatgxgvwsqwghq(string ucfarspe, int zozbebpkhzomfw, double gnjpbfv, bool xqmuscojnjec, bool rjtlsx, bool mfbfwvkaqbjuaq, int tdjnlhg, bool rxsstxnjjvlb, double aqxaxcaetysmtwh) {
	bool rjjadsxzsmxv = true;
	int ugncv = 1069;
	bool qfantjzimub = false;
	bool iltcmnquvjgrl = true;
	bool utbsayyosum = true;
	int axocehkig = 2761;
	int wsaummlpwffrgkt = 949;
	double udsyzsbvnvg = 31570;
	if (true == true) {
		int xxcmgmsp;
		for (xxcmgmsp = 20; xxcmgmsp > 0; xxcmgmsp--) {
			continue;
		}
	}
	return string("hlfx");
}

int ldkcgdu::raazvlqauikgkidmibngthkxp(double wrcglmafta, string xkppac) {
	string xzgtl = "pycufsbjcxvezpuimakbu";
	if (string("pycufsbjcxvezpuimakbu") == string("pycufsbjcxvezpuimakbu")) {
		int fedewdftc;
		for (fedewdftc = 55; fedewdftc > 0; fedewdftc--) {
			continue;
		}
	}
	if (string("pycufsbjcxvezpuimakbu") == string("pycufsbjcxvezpuimakbu")) {
		int gooim;
		for (gooim = 55; gooim > 0; gooim--) {
			continue;
		}
	}
	return 75294;
}

void ldkcgdu::htlmmrsfgy(int wecqdea, bool porclkxhfkfh, int jfcgt, bool pnvfibt) {
	double gdoydcna = 756;
	string emcgqxdxbz = "ywojvxnegnftuunmpmwxlzqbvtlmtjazeizaipmqdcncayvchjfksnwismtfzeecalvmmppmbdinawca";

}

void ldkcgdu::wvjshassvgbgsosx(double zwbkqyukd, double aabcdpmkjdqajdl, string mtqekbgcqt, double xvhwqph, bool krdfyyrvdlil, string pjypzxapzfma, string qqefzluvjgkv, int hucikxqmqblu, double xtooxeqjiaxe, int xurjchsv) {
	bool linyadsagvhgmxp = true;
	if (true != true) {
		int sg;
		for (sg = 58; sg > 0; sg--) {
			continue;
		}
	}
	if (true == true) {
		int zhq;
		for (zhq = 86; zhq > 0; zhq--) {
			continue;
		}
	}
	if (true == true) {
		int izv;
		for (izv = 32; izv > 0; izv--) {
			continue;
		}
	}

}

string ldkcgdu::mvihrdunjkjltjrq(int zeggphgrnv, string isbddtcvbb, double akdhbe, double kouekdix, string yvzvaaltgdy, string ywoxx, bool cpkdjmxbi, int qzvazojjbmqdsqc) {
	double xegqrevdlrqc = 87749;
	bool xasovu = true;
	bool nqtkxfxvgflis = true;
	string ggtgqvqjhbhg = "evkhvegrptiabj";
	bool zxqmp = false;
	int vznspkopf = 8665;
	bool mktekmq = false;
	if (87749 == 87749) {
		int zqkoancqd;
		for (zqkoancqd = 32; zqkoancqd > 0; zqkoancqd--) {
			continue;
		}
	}
	if (8665 == 8665) {
		int eztkbappdz;
		for (eztkbappdz = 97; eztkbappdz > 0; eztkbappdz--) {
			continue;
		}
	}
	if (false == false) {
		int pmovvrp;
		for (pmovvrp = 20; pmovvrp > 0; pmovvrp--) {
			continue;
		}
	}
	if (string("evkhvegrptiabj") == string("evkhvegrptiabj")) {
		int lhh;
		for (lhh = 13; lhh > 0; lhh--) {
			continue;
		}
	}
	if (false != false) {
		int onnlphqcx;
		for (onnlphqcx = 14; onnlphqcx > 0; onnlphqcx--) {
			continue;
		}
	}
	return string("emodtnaeidw");
}

void ldkcgdu::tvvrlsrurtvxyijx(string uzecgavchwrqp, int zqbnkofxiio, string pppwbvnnncrv) {
	bool wjnvqzfybfdfal = true;
	int vhoopc = 2382;
	string yiypbschqd = "dwffhsxrrgvzmwkyckrfkvhrtblznlsaybqbbmymlyhxuatfeffkc";
	double yoelm = 12988;
	if (true == true) {
		int zmeqro;
		for (zmeqro = 60; zmeqro > 0; zmeqro--) {
			continue;
		}
	}

}

bool ldkcgdu::bbuptnmmhukuddue(bool eucjvhogsffw) {
	bool dyiatvyd = false;
	bool arkicvogzhkjtt = false;
	int nbgrmj = 604;
	int umcbw = 2839;
	if (604 != 604) {
		int hzvmrgt;
		for (hzvmrgt = 33; hzvmrgt > 0; hzvmrgt--) {
			continue;
		}
	}
	return true;
}

bool ldkcgdu::ewnpsdvuwf(bool mqgkniwy, bool nxvxroirt, bool lwrlsfisuzkwfek) {
	double awwgnv = 14921;
	double trnsk = 8190;
	int ltfjrgtzwlujysm = 2128;
	if (2128 == 2128) {
		int ndpsrklfj;
		for (ndpsrklfj = 94; ndpsrklfj > 0; ndpsrklfj--) {
			continue;
		}
	}
	if (2128 != 2128) {
		int mcnns;
		for (mcnns = 51; mcnns > 0; mcnns--) {
			continue;
		}
	}
	if (2128 == 2128) {
		int anyrhqlx;
		for (anyrhqlx = 21; anyrhqlx > 0; anyrhqlx--) {
			continue;
		}
	}
	return true;
}

void ldkcgdu::jdqzlytgqddv(int rqzouvfswcybvha, string rsqcmxxykffxj, int pcjkyffd, int uydqatylroy) {
	bool hdekcoosvimmw = true;
	bool nfexyljrat = false;
	if (false == false) {
		int fwvq;
		for (fwvq = 90; fwvq > 0; fwvq--) {
			continue;
		}
	}
	if (false == false) {
		int gvn;
		for (gvn = 53; gvn > 0; gvn--) {
			continue;
		}
	}
	if (true == true) {
		int dapuwg;
		for (dapuwg = 49; dapuwg > 0; dapuwg--) {
			continue;
		}
	}

}

void ldkcgdu::oatquexfltb(bool mbmtzt, bool mcnrwxvhjccfug, double qeennmyghv, string vxxnyo, int rglhew, string yzsigtoupxs, string cqiaefznfgbs) {
	string alzfvgc = "tnwmcmfaxscvcxxnoqvhftlxjygfdflzmnihxpqxrrbunsutyvzdqfbumsihxpblqvouxjswktohomnewxykllwyygkkkfo";
	double cdhrb = 5644;
	double kpxqabutc = 23294;
	bool ssrjofwxljuwl = true;
	int aablwfhxd = 2776;
	double mwloyjmlenjyyu = 29666;
	string zgcmtmmgmxz = "vjkqjvmizwozhcjhdzibkblpthimjtmtdui";
	if (23294 == 23294) {
		int mcjetb;
		for (mcjetb = 83; mcjetb > 0; mcjetb--) {
			continue;
		}
	}

}

double ldkcgdu::tcyegepeehdbzypaxscdis(double hfdtmszh, bool psqdpixa, int mbimjhlmwfxfjv) {
	bool fvexeinjfqje = false;
	double qeozbfw = 12385;
	int ahfndhcganyeynt = 1493;
	double mxptkigrmsyz = 64384;
	int gxemreujikwkjj = 2443;
	bool etchrjw = false;
	string cgxsfz = "puieazvtqnqygscsuoxcrieokpebegjojeysjnzdokqwhmpaaxgalmdqzlgrdibmzfbiqckufzxrinp";
	bool iwaeluabibhppme = false;
	if (string("puieazvtqnqygscsuoxcrieokpebegjojeysjnzdokqwhmpaaxgalmdqzlgrdibmzfbiqckufzxrinp") == string("puieazvtqnqygscsuoxcrieokpebegjojeysjnzdokqwhmpaaxgalmdqzlgrdibmzfbiqckufzxrinp")) {
		int cqbwhegtl;
		for (cqbwhegtl = 41; cqbwhegtl > 0; cqbwhegtl--) {
			continue;
		}
	}
	if (false == false) {
		int rglgl;
		for (rglgl = 27; rglgl > 0; rglgl--) {
			continue;
		}
	}
	if (false == false) {
		int oj;
		for (oj = 69; oj > 0; oj--) {
			continue;
		}
	}
	if (false == false) {
		int qqope;
		for (qqope = 0; qqope > 0; qqope--) {
			continue;
		}
	}
	if (false == false) {
		int almzo;
		for (almzo = 65; almzo > 0; almzo--) {
			continue;
		}
	}
	return 98566;
}

void ldkcgdu::rnchwcdxyfieun(int ebhpspttjggvp) {
	int llyyuibpv = 8528;
	string pugjvoibkqwqfi = "prkpldchrzvwnaikpnncn";
	bool wzaimghcypfhr = true;
	if (8528 == 8528) {
		int wcdwzkg;
		for (wcdwzkg = 38; wcdwzkg > 0; wcdwzkg--) {
			continue;
		}
	}
	if (8528 != 8528) {
		int gcvglvf;
		for (gcvglvf = 21; gcvglvf > 0; gcvglvf--) {
			continue;
		}
	}
	if (8528 == 8528) {
		int dlpmmepo;
		for (dlpmmepo = 25; dlpmmepo > 0; dlpmmepo--) {
			continue;
		}
	}
	if (8528 != 8528) {
		int uggrxkyvag;
		for (uggrxkyvag = 74; uggrxkyvag > 0; uggrxkyvag--) {
			continue;
		}
	}
	if (true == true) {
		int ui;
		for (ui = 30; ui > 0; ui--) {
			continue;
		}
	}

}

bool ldkcgdu::vgstpzvdxbpaodqrd(int jsyvgcjphdh) {
	string fpvmybpx = "rjorsdmxqcogjwhvvffwdkqcnhvtupzlwvugsnobjsypvmrcccvpzhetnnvvbsqjie";
	double pxklydotslipt = 31707;
	string qjtisanzqxb = "hepvroktlpmjlkhufqgkniufhbw";
	int qhjihn = 218;
	bool vhsgkjft = true;
	int oedghhtgunzepq = 395;
	if (218 == 218) {
		int pl;
		for (pl = 21; pl > 0; pl--) {
			continue;
		}
	}
	return false;
}

string ldkcgdu::gythhvnlqescm(double ukblxftmhkpxfdi, bool dkjfvztxmfvsuy, string qpxapzwvx, int nwxmkrumyzu, int jtlersrh, bool zdiky, int ptbsjxbllgd, string whefzdyrhl, bool peomssergvrc, double etdesfujywhdx) {
	string cteijqb = "andddrpktnkshemjjdpgiwbpovttifzhkkzwyubswooneuwomapnvbhkpabvypshwhaafngsdmhqrqoaessepxyu";
	string nkuojetrr = "basaezopymavendrwopclwzrzeyxyutzwifmwmylkzywfutkzkpsdcgvrjzyyqnwkbxtfusuwvdqqsheiagmxglkvlpkb";
	int lfizjlhbofet = 856;
	double remkseicvg = 31793;
	int stupetwcbhpusuj = 1088;
	double udvwmrvhnjbc = 44065;
	string gxyaovhvzlslo = "rgwpizbrepazbxqdpxfpohbbhdffjpnwclsgrlwrqpdawtnxbjflqcibzzxmxfnkeocfstowkxuefsfgmcbqilbsmbcacr";
	if (44065 == 44065) {
		int nn;
		for (nn = 46; nn > 0; nn--) {
			continue;
		}
	}
	return string("opnqkbofasxxfnibku");
}

string ldkcgdu::xebedxjzcnmsourdpqvva() {
	bool jmzzjjx = true;
	string bmcpitbqmjdfkqj = "woctiorupdezuustbjausjqxg";
	bool ibknsnfetqpd = true;
	int xwfhmaamq = 4160;
	bool bspqpifptbmaop = true;
	bool jvcwqpqgby = false;
	return string("ceajgpqckfoy");
}

bool ldkcgdu::ehrgppwqovckscjlzwwkn(int slqlcpfjytx, double prlut, int kxuihfjdamsu, string nrhrndejsjswuqw, int rkhyx, double qkzljedzktd, double eyrrytvdduadve) {
	int axadxjnpswapehf = 1000;
	int udodws = 3631;
	int qiucpckotpz = 1475;
	bool gubpeiutcbhf = false;
	double tjxggt = 12504;
	return true;
}

double ldkcgdu::csvoqdnihfrqxk(bool eckpaxw, int sxtju, int gfuvgeweknjusad, bool qynioyfydvlvw, string svzujt, string fgjjs, int gwwezmkxyigeldd, int mnvdflp, int rdpxzhkfe) {
	int kbotog = 109;
	bool bhegmcjjcjtaclc = false;
	string bqevjqvhxvb = "qococowipmypcmqfhdiqiyvfqbpzuvmozhavdxgdyjdudbybjvbkbxuesucxvcwwrehloyvnueinen";
	double wysxsf = 6268;
	if (6268 != 6268) {
		int htwilfwvc;
		for (htwilfwvc = 10; htwilfwvc > 0; htwilfwvc--) {
			continue;
		}
	}
	if (109 != 109) {
		int qpeys;
		for (qpeys = 99; qpeys > 0; qpeys--) {
			continue;
		}
	}
	if (109 != 109) {
		int zvatkmfod;
		for (zvatkmfod = 38; zvatkmfod > 0; zvatkmfod--) {
			continue;
		}
	}
	if (string("qococowipmypcmqfhdiqiyvfqbpzuvmozhavdxgdyjdudbybjvbkbxuesucxvcwwrehloyvnueinen") == string("qococowipmypcmqfhdiqiyvfqbpzuvmozhavdxgdyjdudbybjvbkbxuesucxvcwwrehloyvnueinen")) {
		int szjcsiemo;
		for (szjcsiemo = 50; szjcsiemo > 0; szjcsiemo--) {
			continue;
		}
	}
	if (109 != 109) {
		int ddktfmz;
		for (ddktfmz = 76; ddktfmz > 0; ddktfmz--) {
			continue;
		}
	}
	return 77155;
}

void ldkcgdu::hijzzeujatmpxtnrattw(double ylbphpdvtlikzgt, bool hqkjhdoylijcal, double cykvqt, string tkeyy, bool cpfygjpl, string nvqhi) {
	int tcxszypqmvl = 300;
	double bnongemgeyv = 4832;
	string sdwbkaj = "lnqhpqbhyumrkdreyjyopqijhidvozftoynvxubpokzfsfbszcnutygbzjyvklpekhmkbzhdlxwyvxiszchj";
	string zjfqsoogznyue = "owqgejyzbdssoscptiyqcohydnvqtkvsaeirndgodqfcoveopbvxwqhplycpqwzptccwdzrjlligxsrhpkyzuliypthsgrbexg";
	double jxwurkekliakekb = 28297;
	int jwhprggfrkiqk = 3384;
	if (string("owqgejyzbdssoscptiyqcohydnvqtkvsaeirndgodqfcoveopbvxwqhplycpqwzptccwdzrjlligxsrhpkyzuliypthsgrbexg") == string("owqgejyzbdssoscptiyqcohydnvqtkvsaeirndgodqfcoveopbvxwqhplycpqwzptccwdzrjlligxsrhpkyzuliypthsgrbexg")) {
		int xqbgbe;
		for (xqbgbe = 77; xqbgbe > 0; xqbgbe--) {
			continue;
		}
	}
	if (28297 != 28297) {
		int xazfpmd;
		for (xazfpmd = 22; xazfpmd > 0; xazfpmd--) {
			continue;
		}
	}
	if (28297 == 28297) {
		int pmgijzhtaq;
		for (pmgijzhtaq = 86; pmgijzhtaq > 0; pmgijzhtaq--) {
			continue;
		}
	}
	if (28297 != 28297) {
		int uls;
		for (uls = 69; uls > 0; uls--) {
			continue;
		}
	}
	if (string("lnqhpqbhyumrkdreyjyopqijhidvozftoynvxubpokzfsfbszcnutygbzjyvklpekhmkbzhdlxwyvxiszchj") == string("lnqhpqbhyumrkdreyjyopqijhidvozftoynvxubpokzfsfbszcnutygbzjyvklpekhmkbzhdlxwyvxiszchj")) {
		int zgcn;
		for (zgcn = 36; zgcn > 0; zgcn--) {
			continue;
		}
	}

}

ldkcgdu::ldkcgdu() {
	this->tcyegepeehdbzypaxscdis(41781, false, 2526);
	this->rnchwcdxyfieun(583);
	this->vgstpzvdxbpaodqrd(1970);
	this->gythhvnlqescm(43769, false, string("dxuhqrpvalsovarawfxunbfmfytdtiktjhveqdpojdmjomsbomioitkzjs"), 8776, 447, true, 583, string("heumbgfbndfynwjpjefldqvkpqrbkqunflneecajfxriqirz"), false, 18231);
	this->xebedxjzcnmsourdpqvva();
	this->ehrgppwqovckscjlzwwkn(2220, 6593, 509, string("vubzahrrtehwbbiuodcytzhgykgjadlipbbtgbwkiklwsigentyjrdyrklwpyurmobfqtkxrsmdctpaxpgsmjqgwgm"), 880, 64917, 1961);
	this->csvoqdnihfrqxk(false, 7670, 5475, false, string("ijgbylwbfrghvwjkxctqxsvoaapyvydoztsp"), string("ccfwgjaaobdullbgslldrwkytnvsjgpwlpnkqzdykrjsdzsvxgvwboypagiajyziuwzsaviikfd"), 1553, 7775, 1497);
	this->hijzzeujatmpxtnrattw(22983, false, 45925, string("hqznacocex"), true, string("edrsoboaburhgnwvpfspkzqeknvqq"));
	this->kcausyaatgxgvwsqwghq(string("haeviisennzireoyjn"), 4807, 69298, false, true, false, 13, false, 77832);
	this->raazvlqauikgkidmibngthkxp(23604, string("buelirgpnknj"));
	this->htlmmrsfgy(68, false, 5915, false);
	this->wvjshassvgbgsosx(41379, 58605, string("mkxgxznzoknbtzahetraszabfflfjrtrldadjimhavmiewvldi"), 68092, false, string("nlxbrschyakwvhiraonuflrxweybinnlcyvyhuavsrojttegybyrerbcyvtshlflogfaykzbayvtaeuuktvmzek"), string("buzgabouodckimsuieuvtwpzlmgrvyabayrztaeaiagpniivpvawqrjigwzdbrwneebwxduvmk"), 4260, 22019, 2180);
	this->mvihrdunjkjltjrq(4875, string("lxfneqlulpvvxmzozykstaanpqnqredqdxdiiyqkjhdxvdciggvxqucovzrdfaunqqabognhwi"), 8436, 20852, string("metfkjwoetsmqfpfnjypmcnnjmcqdrdzfsuqq"), string("bipzicyjdnskwent"), false, 328);
	this->tvvrlsrurtvxyijx(string("onptoeuwrvrmcepaywggieodbkloipqdzitjmfkyohotdvobrsbmyehbrejbjxowlaggvcgu"), 4434, string("hinxhunvjyvpgjyqpowhidexilvkknbnoukoukfluravxqrwjjiwprtpmwxhq"));
	this->bbuptnmmhukuddue(true);
	this->ewnpsdvuwf(true, true, true);
	this->jdqzlytgqddv(4938, string("zhwxpysqcyrqfkqnifinrkticfqeaavqlscyulgvjia"), 3013, 3247);
	this->oatquexfltb(true, false, 42022, string("vhjlrfvcjjptfvygqnnysldwtfcflpvqmyazzfrymekciwwfsbeixztxrsevdo"), 1105, string("ndonjjgvebmqvknnrmoiupfehezbvpwgmemwtgboyelnbhfxbymxhzafcpyvlhqkcgfnvzewkieuzxpmstyvmixeweoqxhtwahl"), string("bcuqgculhtkblwwfobfskfnyyodiyz"));
	this->kafnsypyenwtfmmjipbw(string("oafffnphxilcshlrcigulwvvjzhgcbvnnovyzvdjkcedpoxzfdlqodervuuprckqduegyihqzbozdyytivkmdbycxt"), string("hgstsxxmwbvkxhxuvkhouclvrkxdsgwcyh"), false, 2785, 5160, 1075, string("epdsbgvjybjbqkccegyedmeflx"));
	this->jvcqoanmolkits();
	this->bkzacuynqxorrjlfpotxdwz();
	this->odcdlrgmefzoycmhxtqrbk();
	this->vduntjwrtcfpdxdumdiwignm(37033, 14315, 2831);
	this->eqlvsesmkdi(string("wwiflhxurrzhyvsqhjnpaonqlypghjxvrgmdbqyqwowaawuvcueeeuwuukqskzwpdjadrdtglytbxuablbcc"), 8878, true, string("czzwapcqwhhisreqmrhwgqfnyrfiygpdtovbmztlhwfyuxedrbubbuxcxumjcobkeyxjyabhhjqpqcluonja"), 927, string("fxsskfntkjufabxybldnrdlttwfyemrevabnkjlbhsfsmoxwxzlvqyjotorajjbgul"), 23158, string("wjdpwjjwvwdbjjavcnrcnklruslmdfplmcxdmsswmxqugkaercuenazhqcwwztfzkhytwjbytwirscrelforajcduxslsjuc"), 4433);
}
