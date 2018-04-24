#include "Menu.h"

/*
char* szHealthModes[] = {
	"OFF", "Text", "Bar", "Both",
};

char* szBoneModes[] = {
	"OFF", "White", "Health", "Team",
};

char* szHitboxes[] =
{
	"Auto", "Head", "Pelvis", "Lower Torse", "Lower Mid. Torse", "Upper Mid. Torse", "Upper Torse",
	"Left Upper Arm", "Left Lower Arm", "Left Hand", "Right Upper Arm",
	"Right Lower Arm", "Right Hand", "Left Hip", "Left Knee", "Left Foot",
	"Right Hip", "Right Knee", "Right Foot",
};

char* ChatSpams[] = { "OFF", "NullCore", "LMAOBOX", "Lithium", "Cathook", "Empty Lines", "Speedhook", "Freebox", "Catbot", "ayyware" };

char* KillSays[] = { "OFF", "NiggerHOOK", "NullCore", "File" };

char* condESP[] = { "OFF", "ayyware", "NullCore" };*/ // Unneeded, but keep them here for reference.

void Menu::Init()
{
	m_isVisible = false;

	CWindow Main(100, 100, 703, 438);

	// checkbox: 12 pixels

#pragma region Aimbot
	auto AimbotTab = new CChild(0, 0, 220, L"Aimbot");

	AimbotTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aimbot_active));
	AimbotTab->AddControl(new CCheckBox(L"Silent", &gCvars.aimbot_silent));
	AimbotTab->AddControl(new CCheckBox(L"Autoshoot", &gCvars.aimbot_autoshoot));
	AimbotTab->AddControl(new CCheckBox(L"Hitscan", &gCvars.aimbot_hitscan));
	AimbotTab->AddControl(new CCombo(&gCvars.aimbot_hitbox, {
		L"Auto", L"Head", L"Pelvis", L"Lower Torse", L"Lower Mid. Torse", L"Upper Mid. Torse", L"Upper Torse",
		L"Left Upper Arm", L"Left Lower Arm", L"Left Hand", L"Right Upper Arm",
		L"Right Lower Arm", L"Right Hand", L"Left Hip", L"Left Knee", L"Left Foot",
		L"Right Hip", L"Right Knee", L"Right Foot"
	}));
	AimbotTab->AddControl(new CCheckBox(L"Smooth", &gCvars.aimbot_smooth));
	AimbotTab->AddControl(new CSlider<int>(L"Amount", 0, 180, &gCvars.aimbot_smooth_amt));
	AimbotTab->AddControl(new CCheckBox(L"Ignore Cloak", &gCvars.aimbot_ignore_cloak));
	AimbotTab->AddControl(new CCheckBox(L"Zoomed Only", &gCvars.aimbot_zoomedonly));

	Main.AddControl(AimbotTab);
#pragma endregion
#pragma region ESP
	auto ESPTab = new CChild(0, 155, 220, L"ESP");

	ESPTab->AddControl(new CCheckBox(L"Enabled", &gCvars.esp_active));
	ESPTab->AddControl(new CCheckBox(L"Enemies Only", &gCvars.esp_enemyonly));
	ESPTab->AddControl(new CCheckBox(L"Box", &gCvars.esp_box));
	ESPTab->AddControl(new CSlider<int>(L"Thickness", 0, 4, &gCvars.esp_box_thickness));
	ESPTab->AddControl(new CCheckBox(L"Name", &gCvars.esp_name));
	ESPTab->AddControl(new CCheckBox(L"Class", &gCvars.esp_class));
	ESPTab->AddControl(new CCheckBox(L"Cond", &gCvars.esp_playerCond_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_playerCond, { L"OFF", L"ayyware", L"NullCore" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Remove Cloak", &gCvars.aimbot_ignore_cloak));
	ESPTab->AddControl(new CCheckBox(L"Remove Disguise", &gCvars.esp_removeDisguise));
	ESPTab->AddControl(new CCheckBox(L"Remove Taunt", &gCvars.esp_removeTaunt));
	ESPTab->AddControl(new CCheckBox(L"Health", &gCvars.esp_health_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_health, { L"OFF", L"Text", L"Bar", L"Both" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Bones", &gCvars.esp_bones_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_bones, { L"OFF", L"White", L"Health", L"Team" })); // NEEDS LIST

	Main.AddControl(ESPTab);
#pragma endregion
#pragma region Anti Aim
	auto AntiAimTab = new CChild(230, 70, 220, L"Anti Aim");

	AntiAimTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aa_enabled));
	AntiAimTab->AddControl(new CCheckBox(L"Pitch", &gCvars.aa_pitch_enabled));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_pitch, { L"Fake Up", L"Fake Down" })); // NEEDS LIST
	AntiAimTab->AddControl(new CCheckBox(L"Yaw", &gCvars.aa_yaw_enabled));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_yaw, { L"Right", L"Left", L"Random" })); // NEEDS LIST // Finally, a string that actually uses a unicode character!

	Main.AddControl(AntiAimTab);
#pragma endregion
#pragma region Remove Cond
	auto RemoveCondTab = new CChild(230, 170, 220, L"Remove Cond");

	RemoveCondTab->AddControl(new CCheckBox(L"Enabled", &gCvars.removecond_enabled));
	RemoveCondTab->AddControl(new CCombo(&gCvars.removecond_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	RemoveCondTab->AddControl(new CSlider<int>(L"Value", 0, 1000, &gCvars.removecond_value));
	RemoveCondTab->AddControl(new CCheckBox(L"Auto Medkit", &gCvars.removecond_automedkit));
	RemoveCondTab->AddControl(new CCheckBox(L"Auto Instant Cap", &gCvars.removecond_autoinstantcap));
	RemoveCondTab->AddControl(new CCheckBox(L"Instant Weapon Switch", &gCvars.removecond_instantweaponswitch));
	RemoveCondTab->AddControl(new CCheckBox(L"Sticky Spam", &gCvars.removecond_stickyspam));

	Main.AddControl(RemoveCondTab);
#pragma endregion
#pragma region Misc
	auto MiscTab = new CChild(460, 0, 220, L"Misc");

	MiscTab->AddControl(new CCheckBox(L"Bunny Hop", &gCvars.misc_bunnyhop));
	MiscTab->AddControl(new CCheckBox(L"Auto Strafe", &gCvars.misc_autostrafe));
	MiscTab->AddControl(new CCheckBox(L"Third Person", &gCvars.misc_thirdPerson));
	MiscTab->AddControl(new CCheckBox(L"Auto Backstab", &gCvars.misc_autobackstab));
	MiscTab->AddControl(new CCheckBox(L"Noisemaker Spam", &gCvars.misc_noisemaker_spam));
	MiscTab->AddControl(new CCheckBox(L"No Scope", &gCvars.misc_noscope));
	MiscTab->AddControl(new CCheckBox(L"Chat Spam", &gCvars.misc_chatspam_enabled));
	MiscTab->AddControl(new CCombo(&gCvars.misc_chatspam_selection, { L"None", L"NullCore", L"LMAOBOX", L"Lithium", L"Cathook", L"Empty Lines", L"Speedhook", L"Freebox", L"Catbot", L"ayyware" })); // NEEDS LIST
	MiscTab->AddControl(new CSlider<int>(L"Delay", 100, 3000, &gCvars.misc_chatspam_delay));
	MiscTab->AddControl(new CCheckBox(L"Kill Say", &gCvars.misc_killsay_enabled));
	MiscTab->AddControl(new CCombo(&gCvars.misc_killsay_selection, { L"None", L"NiggerHOOK", L"NullCore", L"File" })); // NEEDS LIST
	MiscTab->AddControl(new CCheckBox(L"Roll Speedhack", &gCvars.misc_roll_speedhack));
	MiscTab->AddControl(new CCheckBox(L"Clean Screenshot", &gCvars.misc_cleanScreenshot));
	MiscTab->AddControl(new CSlider<int>(L"Field of View", 0, 120, &gCvars.misc_fov));
	MiscTab->AddControl(new CSlider<int>(L"Viewmodel FOV", 0, 120, &gCvars.misc_viewmodel_fov));
	MiscTab->AddControl(new CCheckBox(L"No Push", &gCvars.misc_no_push));
	MiscTab->AddControl(new CCheckBox(L"Voice Menu Spam", &gCvars.misc_voice)); // NEEDS LIST (?) // Apple, when you add the options to this feature please add to menu. Thanks. - Wolfie

	Main.AddControl(MiscTab);
#pragma endregion

	MenuForm.AddWindow(Main);
}

void Menu::Kill()
{}

void Menu::PaintTraverse()
{
	if (m_isVisible)
		MenuForm.Paint();
}

void Menu::Click()
{
	if (m_isVisible)
		MenuForm.Click();
}

void Menu::HandleInput(WPARAM vk)
{
	if (m_isVisible)
		MenuForm.HandleInput(vk);
}

void Menu::Toggle()
{
	m_isVisible = !m_isVisible;
}





















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class amhtnql {
public:
	int qanrgmkxlfcnfm;
	int kqcrfjh;
	amhtnql();
	void tozqrpojdlhcq(string pyumsmksnfkslg, int eyfddateo, string denrhsz);
	bool kgtxaunaojtebniu(int zrnnjioq, string hfqgcqjf, string izklug);
	string unyjhxtbtnvapqdxbmsmrfgt(bool noewbfh);
	double tjpwwoujjqxkgfvmnzmc();
	string fvgirmtvgncjdvy(int ekunotalrrels);
	double moxbfybdmlocjetpwcoc(int eurnxuisdiqc);
	int nivwtvkuqhacilcsjspmzyai();
	bool ewaonagtgjexwgoy(bool atpdn, double couffgsp, int lxtthgwvwuklaeq, int bugoiexucl, double mplyfbdvm, int grucqdkzwf, bool oufkt, double lgncorm, double bvvfmxqpchndec);

protected:
	bool zwpio;
	string lbhfv;

	bool fbxxmbobpgcqzsucbugcpckag(bool yknopbjupafsyb, bool mjqxlevipjewnl);
	void znkradgltzw(string uhwqpwmlxukskvt, bool zdgljfyc, int ffqpvvhmobd, bool rfuowfgauh, string xbxktlslvo, string xdqnxu, int uzujlcveyxrxafo, string lyeqtccapnoltc, int dwagbbkdbzvgji);
	bool lhmrwbdegapdzeejbvsqhwfa(bool ccpxdjaxadt, double yudqktnfddnhssh, double hilmmrs, bool yulxstcpr, bool jryfudcwalfmxs, int bqyhj, int lczgksisvjt, double hjkkybgm);
	string mmfqsifroa(int ugexi, bool dzswakchmz);
	int wqwxxvvcuassyshmxyf(int ybdohi, bool sthgsqejjrel, double hsacrynsdmds, double sizdksdn, int qrzlfc);
	int zvfukxfrptsyfpqxyzyrpzki(int kfquoeytq, bool fewideiczohde, int beazskp);
	bool aiirebotfadngzjwthp(double alhjzdyepq, int eaazzpqrieuba, double hqljmvmgrgat, double fbowlupt, string ejusugn, double jbhjwe, double agbumesntfu, bool ozvtsoc, bool wcoutoypxbvmf, string miwkawivjoybk);
	void dpnoncqinufd(int gixeirxbjdkcm, bool rjvrifdpiuxfhi, int cvfqlsgib, string qilfbyh, string rpobwrmsbpxqexz, double qsnfwprlrpk, int dvbicqbmfurzfxv, double etltnsacalzwx, int mcqbjnezec);
	bool mptriddfodgdblsdgfz(bool ntsgdxpw, double kojvilk);
	double bxamywznmllusoqyczuah(int wqkinhuxb, bool cehsnatdikss, int ayritbugkpypaj, string fxpivukkzkdud, double ifxdvecidfce, int wmdozopejnu, bool ntdtvnam, bool vipsbgtrsfbacc);

private:
	bool fnodsffomqdzg;
	double lplwkpgmpobjx;
	string qjwssltqx;
	int twltlgqtx;
	string kjyjqpmmslhftf;

	string ammwfvmxtxaxktpubybkb(bool gidxkwzr, double jxmhirnv, string iwcxer, string skdoewiowuepva, double kuybaroqmnkmws, bool gqsfbt, bool vfxlovnetbzgnl);
	int eoxyieimaquqb(string tuovwcs, double poiidmsjxhoaybr, double mzyiisjawivh, bool pfaeejsq, bool yemudxwc);
	bool qfzmmfumqnxxejxoeaspkuhck(int jkjawuyopeaof, string adwwilrs, bool asovgvac, bool wiyfoauoiibqb, double ywrdjncqqqd, string utyweew);
	double bxdnokiowbmii(bool jzadvmpyopxwlvl, int wxstdewkgwgc);
	string cxsrfljlfnhtzytshvridi(double eezhzrgxqup, double bsfhcuhhy, string wwnoxfh, int kndpiktdeqwrl, bool ynkfluetda, bool pypwydup, bool icgromhjsdcwc, bool mzvgeitbuonwftt, int fsjebybgxkwi, bool rxvzggcrljoo);
	double bqmykdghkadcyutviv(int vawtmzl, string kempc);
	bool oqpmoiuslfyarnvb(string ysstarkwpvyec, double bgupqnod);
	double liuaowiyfzazddcibkxzgvd(int fctenhzuffosef);

};


string amhtnql::ammwfvmxtxaxktpubybkb(bool gidxkwzr, double jxmhirnv, string iwcxer, string skdoewiowuepva, double kuybaroqmnkmws, bool gqsfbt, bool vfxlovnetbzgnl) {
	int jqannz = 1147;
	double ourxnstsi = 19701;
	string ynuktgkdj = "osvlsbeqkgzfkqcdifrxybsuvmwyvqxdfrhtfquyofvveliizwjkkoskhqywzfpoahuhwuiwytmxtsqjx";
	int ilukeyrq = 6875;
	if (1147 == 1147) {
		int xwbwcutr;
		for (xwbwcutr = 64; xwbwcutr > 0; xwbwcutr--) {
			continue;
		}
	}
	if (1147 != 1147) {
		int aaab;
		for (aaab = 78; aaab > 0; aaab--) {
			continue;
		}
	}
	return string("eii");
}

int amhtnql::eoxyieimaquqb(string tuovwcs, double poiidmsjxhoaybr, double mzyiisjawivh, bool pfaeejsq, bool yemudxwc) {
	string zgnhjr = "vavkqlntlaxjtobksnganiyumvmfoqwzdxtqsyeucjap";
	string wokicvqe = "ffmjvkmupmpalgcahhvlwenlubxhmcbjefvbacdfjxbbtxnlrasxxtuocusoctjdnguvaabdjezdiazoldygiwbmwx";
	double gfwape = 3373;
	if (string("ffmjvkmupmpalgcahhvlwenlubxhmcbjefvbacdfjxbbtxnlrasxxtuocusoctjdnguvaabdjezdiazoldygiwbmwx") == string("ffmjvkmupmpalgcahhvlwenlubxhmcbjefvbacdfjxbbtxnlrasxxtuocusoctjdnguvaabdjezdiazoldygiwbmwx")) {
		int sy;
		for (sy = 79; sy > 0; sy--) {
			continue;
		}
	}
	return 59544;
}

bool amhtnql::qfzmmfumqnxxejxoeaspkuhck(int jkjawuyopeaof, string adwwilrs, bool asovgvac, bool wiyfoauoiibqb, double ywrdjncqqqd, string utyweew) {
	int xwqawawwkif = 561;
	double ipzacgeatiz = 7897;
	string yftmrnqyjjveqd = "llrnziwprwzjghscgggezmugnmygptdoevoftwgwibmjywwfqhpheysikxdgdmpbodayehlyewvscpfvkquagklqfqxeubyduozw";
	bool crnjfapxryh = false;
	return false;
}

double amhtnql::bxdnokiowbmii(bool jzadvmpyopxwlvl, int wxstdewkgwgc) {
	string wlgwidpkszgeu = "uvryjbayvgpnkvgfffooohjpdpl";
	double sjhpsfbd = 23217;
	bool xaguehjllwnbn = false;
	string iinljzuqbbebeis = "dzalbmdisnmiwyqmjxevxzoakjyauitlo";
	double eourmzbrcfvgxj = 5719;
	double ibubqiemmjsenpf = 10771;
	int aqkmicnlbzzi = 3217;
	bool lpfgncsn = false;
	double mxozvlevc = 20374;
	if (string("uvryjbayvgpnkvgfffooohjpdpl") != string("uvryjbayvgpnkvgfffooohjpdpl")) {
		int xoeeu;
		for (xoeeu = 91; xoeeu > 0; xoeeu--) {
			continue;
		}
	}
	if (10771 != 10771) {
		int zsinu;
		for (zsinu = 60; zsinu > 0; zsinu--) {
			continue;
		}
	}
	if (false != false) {
		int yy;
		for (yy = 43; yy > 0; yy--) {
			continue;
		}
	}
	if (10771 == 10771) {
		int tapjvm;
		for (tapjvm = 77; tapjvm > 0; tapjvm--) {
			continue;
		}
	}
	return 18070;
}

string amhtnql::cxsrfljlfnhtzytshvridi(double eezhzrgxqup, double bsfhcuhhy, string wwnoxfh, int kndpiktdeqwrl, bool ynkfluetda, bool pypwydup, bool icgromhjsdcwc, bool mzvgeitbuonwftt, int fsjebybgxkwi, bool rxvzggcrljoo) {
	bool cmeytbtegtoy = true;
	bool qowgeyjeahy = true;
	int omezjnwx = 4665;
	string jhran = "duykcaqmvjwgthmaoxdxrjwxk";
	string ohfthtopyvpf = "uqmyvdlcyhrkzdnffsixybvubedksyhwxyscjkcquxbvbzkovcmfxxyrwuzuogtyxqyektrjjkqgmwphmftxxezryewculptay";
	int pqopynsa = 839;
	double xlstrez = 13230;
	double csppsvctnvtjwzh = 2114;
	if (string("uqmyvdlcyhrkzdnffsixybvubedksyhwxyscjkcquxbvbzkovcmfxxyrwuzuogtyxqyektrjjkqgmwphmftxxezryewculptay") != string("uqmyvdlcyhrkzdnffsixybvubedksyhwxyscjkcquxbvbzkovcmfxxyrwuzuogtyxqyektrjjkqgmwphmftxxezryewculptay")) {
		int bav;
		for (bav = 67; bav > 0; bav--) {
			continue;
		}
	}
	if (13230 != 13230) {
		int qcz;
		for (qcz = 0; qcz > 0; qcz--) {
			continue;
		}
	}
	return string("cebpr");
}

double amhtnql::bqmykdghkadcyutviv(int vawtmzl, string kempc) {
	int yyalpimasztslgl = 5016;
	double domfwpjqhdtkxfk = 22632;
	int insbvmdbdrbic = 2338;
	if (2338 != 2338) {
		int nvmxcwmk;
		for (nvmxcwmk = 50; nvmxcwmk > 0; nvmxcwmk--) {
			continue;
		}
	}
	if (5016 == 5016) {
		int uvkt;
		for (uvkt = 60; uvkt > 0; uvkt--) {
			continue;
		}
	}
	if (5016 == 5016) {
		int psz;
		for (psz = 85; psz > 0; psz--) {
			continue;
		}
	}
	if (2338 == 2338) {
		int fxisz;
		for (fxisz = 4; fxisz > 0; fxisz--) {
			continue;
		}
	}
	return 95884;
}

bool amhtnql::oqpmoiuslfyarnvb(string ysstarkwpvyec, double bgupqnod) {
	int judcurpqg = 4006;
	int tbclnfxtbvqybmf = 3926;
	double pveigof = 49078;
	string cvvrqiuyxsun = "pyvyxcwydnevtjtwtkzggqmxavsgzwuxcihxdejguferveaflquveoglfzlztbsmbkecrfgzmbxlrqsgephnz";
	int uodgdpxsbpao = 1572;
	bool tejbljb = false;
	double alahfqzbwjuuzv = 7394;
	if (false != false) {
		int exkomte;
		for (exkomte = 19; exkomte > 0; exkomte--) {
			continue;
		}
	}
	return true;
}

double amhtnql::liuaowiyfzazddcibkxzgvd(int fctenhzuffosef) {
	bool mifqq = true;
	if (true != true) {
		int ppzcv;
		for (ppzcv = 66; ppzcv > 0; ppzcv--) {
			continue;
		}
	}
	if (true == true) {
		int okiheaep;
		for (okiheaep = 16; okiheaep > 0; okiheaep--) {
			continue;
		}
	}
	if (true != true) {
		int znw;
		for (znw = 71; znw > 0; znw--) {
			continue;
		}
	}
	if (true == true) {
		int xqclbzfrn;
		for (xqclbzfrn = 6; xqclbzfrn > 0; xqclbzfrn--) {
			continue;
		}
	}
	if (true == true) {
		int ajj;
		for (ajj = 21; ajj > 0; ajj--) {
			continue;
		}
	}
	return 8900;
}

bool amhtnql::fbxxmbobpgcqzsucbugcpckag(bool yknopbjupafsyb, bool mjqxlevipjewnl) {
	double rundwnvfsj = 22815;
	bool orkbjrszvasv = false;
	int ptgrpqzcqw = 275;
	if (275 != 275) {
		int mnmlxwbwp;
		for (mnmlxwbwp = 14; mnmlxwbwp > 0; mnmlxwbwp--) {
			continue;
		}
	}
	if (false != false) {
		int kksimr;
		for (kksimr = 56; kksimr > 0; kksimr--) {
			continue;
		}
	}
	if (false != false) {
		int krpkzots;
		for (krpkzots = 36; krpkzots > 0; krpkzots--) {
			continue;
		}
	}
	if (false != false) {
		int oagwgyds;
		for (oagwgyds = 5; oagwgyds > 0; oagwgyds--) {
			continue;
		}
	}
	if (22815 == 22815) {
		int tt;
		for (tt = 32; tt > 0; tt--) {
			continue;
		}
	}
	return true;
}

void amhtnql::znkradgltzw(string uhwqpwmlxukskvt, bool zdgljfyc, int ffqpvvhmobd, bool rfuowfgauh, string xbxktlslvo, string xdqnxu, int uzujlcveyxrxafo, string lyeqtccapnoltc, int dwagbbkdbzvgji) {
	int yommwlqrfp = 2163;
	string vvhrx = "uridbsulghgvzyuppcrtyrfcljjdsvxsjvuiaaeslzdsxgrjusxdrymfwymovtyxabzuiggzgzeqbcicfzlzjbwlf";
	double whqmptlkmduwn = 15411;
	string vytbkou = "xkphtioryqp";
	string qbnrtq = "ummtffkfeglenjtggvrzjlxes";
	if (string("ummtffkfeglenjtggvrzjlxes") == string("ummtffkfeglenjtggvrzjlxes")) {
		int jokkiq;
		for (jokkiq = 38; jokkiq > 0; jokkiq--) {
			continue;
		}
	}

}

bool amhtnql::lhmrwbdegapdzeejbvsqhwfa(bool ccpxdjaxadt, double yudqktnfddnhssh, double hilmmrs, bool yulxstcpr, bool jryfudcwalfmxs, int bqyhj, int lczgksisvjt, double hjkkybgm) {
	bool uzhbnpiuboiu = true;
	string prcsrpnmbhnwje = "lbvspiryjtbedpkbnnjgbrfrardafzoyidgzotbcrffgdxmjtlwz";
	bool yudevbtvwkn = false;
	bool kpyvbwwuwzulqcw = true;
	bool ywwerinnj = true;
	string ketdees = "atrtkxmbwdpbuuqzkgfqznqjslogoojpdfvyemrgbcmnwjkhvaaxxjeorkpgilnfs";
	double vgpszwuihuldx = 60337;
	bool vilkskk = true;
	int vgqifyzhyu = 1561;
	int jvqdybsb = 5338;
	if (true == true) {
		int zconheiv;
		for (zconheiv = 27; zconheiv > 0; zconheiv--) {
			continue;
		}
	}
	return false;
}

string amhtnql::mmfqsifroa(int ugexi, bool dzswakchmz) {
	string risef = "ybouzqgkkjyonuhgmfonifcfaoljeilptugcbukcilupnxbyydx";
	int comlbsbxdwruah = 7093;
	bool gtsrlucjkrknvp = false;
	int zfeooozwxiyqk = 3629;
	double lyogr = 34018;
	bool yekjnagritq = false;
	if (7093 != 7093) {
		int irzbffdahr;
		for (irzbffdahr = 71; irzbffdahr > 0; irzbffdahr--) {
			continue;
		}
	}
	if (false != false) {
		int fged;
		for (fged = 72; fged > 0; fged--) {
			continue;
		}
	}
	if (3629 == 3629) {
		int hm;
		for (hm = 23; hm > 0; hm--) {
			continue;
		}
	}
	if (3629 == 3629) {
		int aguy;
		for (aguy = 61; aguy > 0; aguy--) {
			continue;
		}
	}
	return string("lnnedqaoqdnclq");
}

int amhtnql::wqwxxvvcuassyshmxyf(int ybdohi, bool sthgsqejjrel, double hsacrynsdmds, double sizdksdn, int qrzlfc) {
	double yrrvs = 45824;
	double krfmksqv = 10728;
	string idhikmd = "dzltbwstpdytjalttlcswdesafluuowtlrpnhllngupkebjkwssgofdyivaaqissafstkptdwetszvkgw";
	string akluudbjt = "snkbqybnbyhdcpozlkovtxuqledyuafmydlfwgobgolsjhbeggbrupvhvdfljegraobtcakqxyiqexpgcvljmhh";
	int rkolynuszsza = 2329;
	int hefqkw = 6419;
	if (2329 != 2329) {
		int vd;
		for (vd = 22; vd > 0; vd--) {
			continue;
		}
	}
	if (2329 == 2329) {
		int lyi;
		for (lyi = 50; lyi > 0; lyi--) {
			continue;
		}
	}
	if (6419 == 6419) {
		int lgwqwsmh;
		for (lgwqwsmh = 90; lgwqwsmh > 0; lgwqwsmh--) {
			continue;
		}
	}
	if (string("dzltbwstpdytjalttlcswdesafluuowtlrpnhllngupkebjkwssgofdyivaaqissafstkptdwetszvkgw") == string("dzltbwstpdytjalttlcswdesafluuowtlrpnhllngupkebjkwssgofdyivaaqissafstkptdwetszvkgw")) {
		int nfmkgnc;
		for (nfmkgnc = 56; nfmkgnc > 0; nfmkgnc--) {
			continue;
		}
	}
	if (2329 != 2329) {
		int avgexm;
		for (avgexm = 37; avgexm > 0; avgexm--) {
			continue;
		}
	}
	return 73580;
}

int amhtnql::zvfukxfrptsyfpqxyzyrpzki(int kfquoeytq, bool fewideiczohde, int beazskp) {
	double gxytahigyltvq = 19657;
	if (19657 == 19657) {
		int zd;
		for (zd = 65; zd > 0; zd--) {
			continue;
		}
	}
	if (19657 == 19657) {
		int anzc;
		for (anzc = 35; anzc > 0; anzc--) {
			continue;
		}
	}
	if (19657 == 19657) {
		int qke;
		for (qke = 64; qke > 0; qke--) {
			continue;
		}
	}
	if (19657 != 19657) {
		int isv;
		for (isv = 6; isv > 0; isv--) {
			continue;
		}
	}
	if (19657 != 19657) {
		int xrg;
		for (xrg = 24; xrg > 0; xrg--) {
			continue;
		}
	}
	return 53186;
}

bool amhtnql::aiirebotfadngzjwthp(double alhjzdyepq, int eaazzpqrieuba, double hqljmvmgrgat, double fbowlupt, string ejusugn, double jbhjwe, double agbumesntfu, bool ozvtsoc, bool wcoutoypxbvmf, string miwkawivjoybk) {
	double kiihcrueyreir = 7468;
	bool hidxzt = true;
	bool ckgwtjunyi = false;
	string mmiajdfhnsmuunr = "ogzxspdqfdofbqj";
	bool zpwzurqepymgpe = false;
	bool xehvobaast = false;
	double qqpkf = 17967;
	double ptnwzf = 2464;
	if (2464 != 2464) {
		int yriniobjt;
		for (yriniobjt = 10; yriniobjt > 0; yriniobjt--) {
			continue;
		}
	}
	if (7468 != 7468) {
		int jda;
		for (jda = 33; jda > 0; jda--) {
			continue;
		}
	}
	if (2464 == 2464) {
		int lehfkwu;
		for (lehfkwu = 15; lehfkwu > 0; lehfkwu--) {
			continue;
		}
	}
	if (2464 != 2464) {
		int gxobrl;
		for (gxobrl = 71; gxobrl > 0; gxobrl--) {
			continue;
		}
	}
	return false;
}

void amhtnql::dpnoncqinufd(int gixeirxbjdkcm, bool rjvrifdpiuxfhi, int cvfqlsgib, string qilfbyh, string rpobwrmsbpxqexz, double qsnfwprlrpk, int dvbicqbmfurzfxv, double etltnsacalzwx, int mcqbjnezec) {
	string dvmyede = "ztnsltmhhtfwznbucxaglxzvbmpi";
	string hancvohjjsqnzwm = "fdewdxptlsonmhnjtqtrwawmqexxvlmskxatceisztigtvgcibxzxcmzlorehibfkqmbgyjkfbblahihvvvfyreosrvuba";
	string msvaeynjvbf = "dfbdfxhwd";
	if (string("fdewdxptlsonmhnjtqtrwawmqexxvlmskxatceisztigtvgcibxzxcmzlorehibfkqmbgyjkfbblahihvvvfyreosrvuba") != string("fdewdxptlsonmhnjtqtrwawmqexxvlmskxatceisztigtvgcibxzxcmzlorehibfkqmbgyjkfbblahihvvvfyreosrvuba")) {
		int egett;
		for (egett = 28; egett > 0; egett--) {
			continue;
		}
	}

}

bool amhtnql::mptriddfodgdblsdgfz(bool ntsgdxpw, double kojvilk) {
	string ffzykvmsaobbur = "gvuwrfisutequesmdzukevoqjfnkfeqbwgsrnyoagtbjdmvr";
	if (string("gvuwrfisutequesmdzukevoqjfnkfeqbwgsrnyoagtbjdmvr") == string("gvuwrfisutequesmdzukevoqjfnkfeqbwgsrnyoagtbjdmvr")) {
		int ngy;
		for (ngy = 15; ngy > 0; ngy--) {
			continue;
		}
	}
	return false;
}

double amhtnql::bxamywznmllusoqyczuah(int wqkinhuxb, bool cehsnatdikss, int ayritbugkpypaj, string fxpivukkzkdud, double ifxdvecidfce, int wmdozopejnu, bool ntdtvnam, bool vipsbgtrsfbacc) {
	double wveadkralpvbo = 36052;
	if (36052 == 36052) {
		int ckgdn;
		for (ckgdn = 51; ckgdn > 0; ckgdn--) {
			continue;
		}
	}
	if (36052 == 36052) {
		int bwgbooa;
		for (bwgbooa = 51; bwgbooa > 0; bwgbooa--) {
			continue;
		}
	}
	return 57751;
}

void amhtnql::tozqrpojdlhcq(string pyumsmksnfkslg, int eyfddateo, string denrhsz) {
	int tmybzohi = 86;
	int wbzfht = 76;
	double xakqzwbzqzfzgzk = 6034;
	if (6034 == 6034) {
		int donmyuc;
		for (donmyuc = 19; donmyuc > 0; donmyuc--) {
			continue;
		}
	}
	if (6034 == 6034) {
		int gvtduc;
		for (gvtduc = 34; gvtduc > 0; gvtduc--) {
			continue;
		}
	}

}

bool amhtnql::kgtxaunaojtebniu(int zrnnjioq, string hfqgcqjf, string izklug) {
	double grimnusefkik = 4221;
	string nvmrzbzuwrvv = "dm";
	double bwtwhlpfybnvub = 23200;
	string cewusnai = "afusogwkwhgrpgckjdkpupiuwkhkianjkkimjxydjqutgeejqdkmnito";
	string vxslzrhpidbjgg = "wssgvp";
	double eomjqz = 7998;
	if (string("wssgvp") == string("wssgvp")) {
		int djiyzfxtbd;
		for (djiyzfxtbd = 77; djiyzfxtbd > 0; djiyzfxtbd--) {
			continue;
		}
	}
	return false;
}

string amhtnql::unyjhxtbtnvapqdxbmsmrfgt(bool noewbfh) {
	bool srvpctpojnjnlmw = true;
	double zuzqcqjddsany = 38871;
	int uzbcbpu = 2524;
	double cuosmpszuar = 23334;
	double inqqxxbxs = 12727;
	string nhphthkqie = "rpvlycnkihqjtycttxatdppudnyzyzyfhtprihqzodqopdgegjivybozpmoumeekufooyxrhpzolcdgkwwrc";
	string jtsyn = "woughlolnsvaeqzzrrlapgscsqqjijcngxpfqdpmhhwkoaiwjimqwinjxqkooczklsyychxvtyxkrdxsv";
	double mqqsdeqvkmxlzk = 57279;
	string qoevrvaawbc = "hhleajbhjlmzrdhzlfntmlgzajuon";
	if (38871 == 38871) {
		int ub;
		for (ub = 65; ub > 0; ub--) {
			continue;
		}
	}
	if (38871 != 38871) {
		int vj;
		for (vj = 90; vj > 0; vj--) {
			continue;
		}
	}
	if (2524 != 2524) {
		int zjcmguj;
		for (zjcmguj = 52; zjcmguj > 0; zjcmguj--) {
			continue;
		}
	}
	if (string("hhleajbhjlmzrdhzlfntmlgzajuon") == string("hhleajbhjlmzrdhzlfntmlgzajuon")) {
		int upeu;
		for (upeu = 16; upeu > 0; upeu--) {
			continue;
		}
	}
	if (true != true) {
		int vijadqbh;
		for (vijadqbh = 0; vijadqbh > 0; vijadqbh--) {
			continue;
		}
	}
	return string("kooajoxrxtqnprikfl");
}

double amhtnql::tjpwwoujjqxkgfvmnzmc() {
	int pwqhumwozvwv = 1492;
	string jxnufwlxnlwzu = "lbcxrcxm";
	double qcrxv = 2957;
	string hrzvafpwdixisar = "ncljfudlbofpcmnprzb";
	double dvgnxj = 445;
	return 33334;
}

string amhtnql::fvgirmtvgncjdvy(int ekunotalrrels) {
	int vwjsms = 1800;
	double ndveagmfgssqf = 27859;
	string xpqoylkfara = "zlsqblphalhazsngmzebijrlozmincrvheoljkeyfyiyq";
	bool lnfbpruptpfdzr = true;
	int oawpludxvejtmn = 840;
	double inycgjyzp = 22671;
	string bxoybjpmd = "dzsycjh";
	bool ocurnd = true;
	int hnqwadluq = 1458;
	string jhzknjduvp = "fhylunnvnxftlbwrkcdxqawhwqpvfcizngjtmrfovfuqqlspfoclzpjsgvsvvxovfwdsrlckpjsuxwgdmwxbkeovtzhtc";
	if (string("dzsycjh") == string("dzsycjh")) {
		int livwfoexma;
		for (livwfoexma = 24; livwfoexma > 0; livwfoexma--) {
			continue;
		}
	}
	if (string("dzsycjh") == string("dzsycjh")) {
		int dbdhso;
		for (dbdhso = 41; dbdhso > 0; dbdhso--) {
			continue;
		}
	}
	if (27859 == 27859) {
		int dgmmwvd;
		for (dgmmwvd = 15; dgmmwvd > 0; dgmmwvd--) {
			continue;
		}
	}
	if (27859 == 27859) {
		int gmwz;
		for (gmwz = 69; gmwz > 0; gmwz--) {
			continue;
		}
	}
	return string("uklykcstexrzzzf");
}

double amhtnql::moxbfybdmlocjetpwcoc(int eurnxuisdiqc) {
	string bgcus = "skhddfqcwzabwcexoqrxibiefkjyhqbvikfhmbiholvyrivctnugvnothfgymjuzbougbvnbpgyjtfnhxsomjnuzdpy";
	int mzmbaewrwz = 1479;
	bool krdibaajbqjks = true;
	if (string("skhddfqcwzabwcexoqrxibiefkjyhqbvikfhmbiholvyrivctnugvnothfgymjuzbougbvnbpgyjtfnhxsomjnuzdpy") != string("skhddfqcwzabwcexoqrxibiefkjyhqbvikfhmbiholvyrivctnugvnothfgymjuzbougbvnbpgyjtfnhxsomjnuzdpy")) {
		int mqkavre;
		for (mqkavre = 59; mqkavre > 0; mqkavre--) {
			continue;
		}
	}
	if (true != true) {
		int bncrn;
		for (bncrn = 22; bncrn > 0; bncrn--) {
			continue;
		}
	}
	if (true != true) {
		int rhqhktzpoy;
		for (rhqhktzpoy = 89; rhqhktzpoy > 0; rhqhktzpoy--) {
			continue;
		}
	}
	if (true == true) {
		int grvixob;
		for (grvixob = 5; grvixob > 0; grvixob--) {
			continue;
		}
	}
	if (string("skhddfqcwzabwcexoqrxibiefkjyhqbvikfhmbiholvyrivctnugvnothfgymjuzbougbvnbpgyjtfnhxsomjnuzdpy") == string("skhddfqcwzabwcexoqrxibiefkjyhqbvikfhmbiholvyrivctnugvnothfgymjuzbougbvnbpgyjtfnhxsomjnuzdpy")) {
		int garq;
		for (garq = 52; garq > 0; garq--) {
			continue;
		}
	}
	return 11874;
}

int amhtnql::nivwtvkuqhacilcsjspmzyai() {
	bool wfoaus = false;
	bool gkehcd = true;
	string cfbtgxgncmezsf = "owk";
	string lgeupr = "dyrfgdqkihk";
	int febodd = 1667;
	bool lbzfdgoxwfvk = false;
	int ezgjknbbdnrbp = 92;
	if (false == false) {
		int czcxodw;
		for (czcxodw = 15; czcxodw > 0; czcxodw--) {
			continue;
		}
	}
	if (1667 != 1667) {
		int hlbmm;
		for (hlbmm = 77; hlbmm > 0; hlbmm--) {
			continue;
		}
	}
	if (false != false) {
		int ovrn;
		for (ovrn = 68; ovrn > 0; ovrn--) {
			continue;
		}
	}
	return 78492;
}

bool amhtnql::ewaonagtgjexwgoy(bool atpdn, double couffgsp, int lxtthgwvwuklaeq, int bugoiexucl, double mplyfbdvm, int grucqdkzwf, bool oufkt, double lgncorm, double bvvfmxqpchndec) {
	double vojeuofuem = 43309;
	return true;
}

amhtnql::amhtnql() {
	this->tozqrpojdlhcq(string("fnkwoadmgwdehzzmambnpwfuzqmbrhaqbblurnrnpiqttcaxamklnudqetseswgdqbxhqfugzfiisdgerpskgtpwy"), 461, string("e"));
	this->kgtxaunaojtebniu(1267, string(""), string("lxqwsipqrdmkndpbagugrolngvbukgemoridmcsxfskxalrti"));
	this->unyjhxtbtnvapqdxbmsmrfgt(true);
	this->tjpwwoujjqxkgfvmnzmc();
	this->fvgirmtvgncjdvy(2177);
	this->moxbfybdmlocjetpwcoc(7316);
	this->nivwtvkuqhacilcsjspmzyai();
	this->ewaonagtgjexwgoy(true, 6301, 3255, 2301, 28504, 143, true, 9585, 47885);
	this->fbxxmbobpgcqzsucbugcpckag(true, false);
	this->znkradgltzw(string("kvifxceqprcwhztcuszhoqxwxpmouvitcxynmta"), false, 1032, false, string("mkhjywavhqtxpcweweucdlxihivysnwkzlnzgqrisvmgpgfcqnxhtzyizxtlhvlfpyckaymqyuuzheijcycnptabxhw"), string("jjqylimgyygcnzcirwjkscfgbeqzzrzetnodjnjyupo"), 2140, string("ndvehiferfmgbaxvkczokezshfdvjgwjkddeaivswcl"), 1524);
	this->lhmrwbdegapdzeejbvsqhwfa(false, 13670, 27286, false, false, 3346, 3612, 18895);
	this->mmfqsifroa(2114, false);
	this->wqwxxvvcuassyshmxyf(1419, false, 19457, 18871, 1680);
	this->zvfukxfrptsyfpqxyzyrpzki(6027, true, 851);
	this->aiirebotfadngzjwthp(21028, 4018, 4450, 77697, string("nvgmgeosmiuvcggrskghohnfftioztfyxrfsuigcagppijrltrvsfsxc"), 9319, 5227, true, false, string("wfgvdqmefndpyubodduwumvnpjvuvymglddlmhrlohfzcglghnloebtgighfmyokadmevionnxxlzcmfzckpeiaaurjzkzxtzng"));
	this->dpnoncqinufd(1151, false, 2149, string("cecnysj"), string("sxqcebsjkfyqkbpucwnmkivmyhdprtdbhrukysejwjctmbwwuipuofbxaudebkgzlsqbawucsroueuubbndb"), 29957, 841, 4815, 8028);
	this->mptriddfodgdblsdgfz(true, 5925);
	this->bxamywznmllusoqyczuah(5188, false, 6425, string("qmuxfrmaayjf"), 7831, 142, false, false);
	this->ammwfvmxtxaxktpubybkb(true, 23929, string("rbhartydvbgrrxcgxhwadktaizfizqlplgnitcbloryezyglbhwe"), string("ajlezmwgpqgwiwvhjiztonqomftzrhqngorihqegnhkcuimpnexwybxbtpiwd"), 9945, false, true);
	this->eoxyieimaquqb(string("eubkmnlcchixedyfkpwktlugumzobcrlcvxwfbpfddtiksbokjbtibwqkcacqct"), 77959, 17459, true, true);
	this->qfzmmfumqnxxejxoeaspkuhck(3796, string("uorljmmuuwzvrmncpcquynqvlregc"), true, true, 48520, string("zwsoxrcla"));
	this->bxdnokiowbmii(true, 5124);
	this->cxsrfljlfnhtzytshvridi(6391, 4857, string("cmdrbdfkcyeyickmjarjtskgkevlvewxqevmmwimcyoxlhvaxwfigyrrnmoidopqesfkg"), 5078, true, true, false, false, 1794, true);
	this->bqmykdghkadcyutviv(258, string("rzmnogcufgmjgxtrfwobvxofhvzjyqnjnsxggzidkxxaajdbbewyqnhxsfwxevfoitaiidjnkplbbflsbdejepemnkhoiluzpdfp"));
	this->oqpmoiuslfyarnvb(string("uiolphcdv"), 4753);
	this->liuaowiyfzazddcibkxzgvd(3208);
}
