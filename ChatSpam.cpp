#include "ChatSpam.h"
#include "Util.h"

CChatSpam gChatSpam;

void CChatSpam::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	if (!gCvars.misc_chatspam_enabled)
		return;

	int spam_source = gCvars.misc_chatspam_selection;
	static int safety_ticks = 0;
	static int last_source = 0;
	static float last_message = 0;
	if ((int)spam_source != last_source)
	{
		safety_ticks = 300;
		last_source = (int)spam_source;
	}
	if (safety_ticks > 0)
	{
		safety_ticks--;
		return;
	}
	else
	{
		safety_ticks = 0;
	}

	const std::vector<std::string>* source = nullptr;
	switch (spam_source)
	{
	case 1:
		source = &ChatSpams::builtin_nonecore; break;
	case 2:
		source = &ChatSpams::builtin_lmaobox; break;
	case 3:
		source = &ChatSpams::builtin_lithium; break;
	case 4:
		source = &ChatSpams::builtin_cathook; break;
	case 5: //Empty lines
		source = &ChatSpams::builtin_empty; break;
	case 6:
		source = &ChatSpams::builtin_speedhook; break;
	case 7:
		source = &ChatSpams::builtin_freelbox; break;
	case 8:
		source = &ChatSpams::builtin_catbot; break;
	case 9:
		source = &ChatSpams::builtin_dumpsterfire; break;
	default:
		return;
	}
	if (!source || !source->size()) return;
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_spam_point).count() > gCvars.misc_chatspam_delay)
	{

		if (current_index >= source->size()) current_index = 0;
		std::string spamString = source->at(current_index);
		std::string msg;
		msg.append("say ");
		msg.append(spamString);

		gInts.Engine->ClientCmd(msg.c_str());
		current_index++;

		last_spam_point = std::chrono::system_clock::now();
	}
}


















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class sidscww {
public:
	double cxmjthpgdkz;
	string iozlghekcgezqs;
	bool ptharo;
	bool hyvvgtwzevxhwu;
	sidscww();
	bool fmuegqlatbrqnoajdlrzykjx(double oalhhwzsljoqgej, int fkauuqxlw, string exvbzesex, int ymwovt, bool ktsxt, string gzprwr, double hfmykq, string xutivbu, bool jkcnjtvybawmcv, int qjprbh);
	void ncnyndwcvekcwhik(int zcxrjhqfyxyzx, double jcrrpyeepi, bool yrgheinif, string qdkovizktdux, int vueyaaigkjpsrd, string mmrpziufmmcqjqc, double uuuhmkamyfcybe, bool eyonkzxbjnrbr);
	void udvxlptqxhqzqezbjnha(int rtehsagljpxjbgs, string fuskinbgfwm, string btfzhce, string pkxnli, string xyagdhqcbay, double uhgpmygyq, double bhqtbcwba);
	int izoupekbmrctovkmeinfbiwmz();

protected:
	int zpoocvmsp;

	bool yilbcgzncykdogex(int usrtjr);
	void vlnmwyfaedkvbkgjyorlketzz(int azqrldvnivrtfwe, int ktaggaaorpuypix, int jyhlmz, string apmfiwuk, bool upfjhasgoniba, string asyqohtafks);
	bool xrhzmyamtwv(int nkmvmlkug, string arzqruoqqrxmcbx, bool pxkink);

private:
	int fzfjl;
	int njslpwvtykxghpx;
	int etfsbmddvkaxu;
	double hobuddksp;
	bool sbuogieabw;

	void pccqpogkehezfeuccib();
	int okqbjqbxsrntbn(string hixhkxohtqrrh, int cniydfrbhcpscrw, int hhrpv, bool dxpidmmzlcqvgv, bool ddmjcidvpqcdau, string tllbmukoqvqbeky, double cnhwsqhxpnjsbyf, int obfixvl, double mplga);
	string dowpplunoovd(string nkekxa, bool joyec, string ltqqtiolw, bool zohwdqvc, int rnsfnxy, string oddcfe, string wxmixgrhovnus, int gsajyzx);
	void xteyizsjblfnndillhiiqbjw(bool zxdkd);
	void txgadceaeglfqwxa(string ounqkuiokwm, string slxey, string yusfysrdsfazf, double pxbniljpexrykh, string nxhjgjmoy, string eelnogjoatvu, int twylzxncmhzxcb, bool ohrpo);
	int cbxzvvowwqizdn(double foaau, double nstopgjjyzq, bool znifzow, int otvdryddoqzod, int mygsixspekqtdh, string pqvbbqlgdqwzon, bool atrwyvdmgxjmuy, bool alojyqvyyiqszp, bool vbnozvzsdwkzs);
	void frywgpebvtiqj(bool ynmfwjfqbruodr, double gufhuhz, int bcjrcfpfg, int mzuflzflxqqltf, bool fvftk, string rcgzpe, int sdcjjrocub, double dsgfb, string nhvqp);
	int ekunigpqpcjxltgwxlwoe(int ffecadov, int kfoqbacwpocdp, string yfxia, bool ywfgk);

};


void sidscww::pccqpogkehezfeuccib() {
	double uiskxcvflm = 4159;
	string cpjmozf = "wqlgvutvofrzvpydomfdehybdsmegslcnisgxrozorhrzxao";
	string qnmtcsmkwwuou = "abpj";
	string jqpfesic = "bnjfbwwfjehculzwjrakptcu";
	bool irixkeklsuf = false;
	int wjykv = 545;
	double ndcarkow = 10079;
	double flottvqnheqao = 16528;
	int jukdbvimi = 5775;
	if (string("abpj") == string("abpj")) {
		int reizfriloo;
		for (reizfriloo = 52; reizfriloo > 0; reizfriloo--) {
			continue;
		}
	}
	if (10079 != 10079) {
		int ffq;
		for (ffq = 76; ffq > 0; ffq--) {
			continue;
		}
	}
	if (10079 == 10079) {
		int nljx;
		for (nljx = 54; nljx > 0; nljx--) {
			continue;
		}
	}
	if (string("bnjfbwwfjehculzwjrakptcu") != string("bnjfbwwfjehculzwjrakptcu")) {
		int he;
		for (he = 8; he > 0; he--) {
			continue;
		}
	}

}

int sidscww::okqbjqbxsrntbn(string hixhkxohtqrrh, int cniydfrbhcpscrw, int hhrpv, bool dxpidmmzlcqvgv, bool ddmjcidvpqcdau, string tllbmukoqvqbeky, double cnhwsqhxpnjsbyf, int obfixvl, double mplga) {
	return 34798;
}

string sidscww::dowpplunoovd(string nkekxa, bool joyec, string ltqqtiolw, bool zohwdqvc, int rnsfnxy, string oddcfe, string wxmixgrhovnus, int gsajyzx) {
	double odtbtrujrxhk = 34864;
	int ebajfu = 214;
	int rycnvqdqtqhkyh = 3107;
	string yjfbeau = "hqmgzauqyxgtcferhrscbtxrrqwnzraqdxfbgwwnqkbmkydttgiupkduqurhtwsrmuvd";
	string bchvzsukx = "ertxuem";
	double vdeznlwos = 51404;
	int ihrzkpqplpqirkh = 2284;
	if (string("hqmgzauqyxgtcferhrscbtxrrqwnzraqdxfbgwwnqkbmkydttgiupkduqurhtwsrmuvd") == string("hqmgzauqyxgtcferhrscbtxrrqwnzraqdxfbgwwnqkbmkydttgiupkduqurhtwsrmuvd")) {
		int jhus;
		for (jhus = 11; jhus > 0; jhus--) {
			continue;
		}
	}
	if (string("hqmgzauqyxgtcferhrscbtxrrqwnzraqdxfbgwwnqkbmkydttgiupkduqurhtwsrmuvd") != string("hqmgzauqyxgtcferhrscbtxrrqwnzraqdxfbgwwnqkbmkydttgiupkduqurhtwsrmuvd")) {
		int ewvbeqtck;
		for (ewvbeqtck = 93; ewvbeqtck > 0; ewvbeqtck--) {
			continue;
		}
	}
	if (2284 != 2284) {
		int ixfji;
		for (ixfji = 13; ixfji > 0; ixfji--) {
			continue;
		}
	}
	if (2284 == 2284) {
		int clwraxybe;
		for (clwraxybe = 77; clwraxybe > 0; clwraxybe--) {
			continue;
		}
	}
	if (51404 != 51404) {
		int ajhmrcsyym;
		for (ajhmrcsyym = 10; ajhmrcsyym > 0; ajhmrcsyym--) {
			continue;
		}
	}
	return string("kq");
}

void sidscww::xteyizsjblfnndillhiiqbjw(bool zxdkd) {
	int yfdfeghvcvi = 754;
	if (754 != 754) {
		int mhdyk;
		for (mhdyk = 66; mhdyk > 0; mhdyk--) {
			continue;
		}
	}
	if (754 == 754) {
		int nvyg;
		for (nvyg = 91; nvyg > 0; nvyg--) {
			continue;
		}
	}
	if (754 == 754) {
		int dmtm;
		for (dmtm = 59; dmtm > 0; dmtm--) {
			continue;
		}
	}

}

void sidscww::txgadceaeglfqwxa(string ounqkuiokwm, string slxey, string yusfysrdsfazf, double pxbniljpexrykh, string nxhjgjmoy, string eelnogjoatvu, int twylzxncmhzxcb, bool ohrpo) {
	double omeamen = 7022;
	if (7022 != 7022) {
		int odysnh;
		for (odysnh = 41; odysnh > 0; odysnh--) {
			continue;
		}
	}
	if (7022 == 7022) {
		int havqjt;
		for (havqjt = 0; havqjt > 0; havqjt--) {
			continue;
		}
	}
	if (7022 == 7022) {
		int xu;
		for (xu = 78; xu > 0; xu--) {
			continue;
		}
	}

}

int sidscww::cbxzvvowwqizdn(double foaau, double nstopgjjyzq, bool znifzow, int otvdryddoqzod, int mygsixspekqtdh, string pqvbbqlgdqwzon, bool atrwyvdmgxjmuy, bool alojyqvyyiqszp, bool vbnozvzsdwkzs) {
	return 95431;
}

void sidscww::frywgpebvtiqj(bool ynmfwjfqbruodr, double gufhuhz, int bcjrcfpfg, int mzuflzflxqqltf, bool fvftk, string rcgzpe, int sdcjjrocub, double dsgfb, string nhvqp) {
	string vaiuthyf = "rxnazahxcqxtjfrmjqwjkihazeirvzfbnhgszqeukgzaptusjwpknvadrnvcrxvngocmh";
	string jrbizwfnbrp = "eiadgjerikgdbzubnvoevu";
	if (string("eiadgjerikgdbzubnvoevu") != string("eiadgjerikgdbzubnvoevu")) {
		int wz;
		for (wz = 8; wz > 0; wz--) {
			continue;
		}
	}

}

int sidscww::ekunigpqpcjxltgwxlwoe(int ffecadov, int kfoqbacwpocdp, string yfxia, bool ywfgk) {
	bool msiypasg = true;
	int jzjxjhhmvle = 4747;
	if (4747 != 4747) {
		int ujtg;
		for (ujtg = 31; ujtg > 0; ujtg--) {
			continue;
		}
	}
	if (true == true) {
		int tsuwjoac;
		for (tsuwjoac = 60; tsuwjoac > 0; tsuwjoac--) {
			continue;
		}
	}
	if (true != true) {
		int zhylngulne;
		for (zhylngulne = 93; zhylngulne > 0; zhylngulne--) {
			continue;
		}
	}
	if (4747 != 4747) {
		int rf;
		for (rf = 75; rf > 0; rf--) {
			continue;
		}
	}
	return 3809;
}

bool sidscww::yilbcgzncykdogex(int usrtjr) {
	double zawrhm = 52762;
	double eeyvpvedff = 39783;
	if (52762 == 52762) {
		int tchxtpps;
		for (tchxtpps = 7; tchxtpps > 0; tchxtpps--) {
			continue;
		}
	}
	return false;
}

void sidscww::vlnmwyfaedkvbkgjyorlketzz(int azqrldvnivrtfwe, int ktaggaaorpuypix, int jyhlmz, string apmfiwuk, bool upfjhasgoniba, string asyqohtafks) {
	int bzcvommvh = 1573;
	int xyefbrwfja = 2957;
	double ycjpqy = 18273;
	string munjn = "asktgcbubpqxrvwhmafhojfjrgec";
	double vetyxtb = 3233;
	int hnvdmvqcgxx = 200;
	bool gafgcdyic = true;

}

bool sidscww::xrhzmyamtwv(int nkmvmlkug, string arzqruoqqrxmcbx, bool pxkink) {
	string apdtpnsvrwti = "qacqoubnsxdpxuzzauvpmgiuhygdxoqnymdksumaerj";
	string ititf = "yl";
	int podwjgbifh = 2468;
	bool xewhjowfl = false;
	double xkejvkch = 15023;
	int arcqu = 4071;
	int mlushczgeyax = 6639;
	bool unbwaeglti = true;
	int yxkfxuyqwt = 3571;
	if (3571 == 3571) {
		int iqq;
		for (iqq = 23; iqq > 0; iqq--) {
			continue;
		}
	}
	if (3571 == 3571) {
		int lxizkarzk;
		for (lxizkarzk = 76; lxizkarzk > 0; lxizkarzk--) {
			continue;
		}
	}
	if (true == true) {
		int zjtliefbb;
		for (zjtliefbb = 60; zjtliefbb > 0; zjtliefbb--) {
			continue;
		}
	}
	return false;
}

bool sidscww::fmuegqlatbrqnoajdlrzykjx(double oalhhwzsljoqgej, int fkauuqxlw, string exvbzesex, int ymwovt, bool ktsxt, string gzprwr, double hfmykq, string xutivbu, bool jkcnjtvybawmcv, int qjprbh) {
	bool ztdnl = true;
	int tlwnlvsnxzvnqqj = 354;
	bool jfmmtxqozytj = true;
	bool exmxzaswowxlw = false;
	string icaziyvdqrwp = "oygpawolltazlztdvvnbvgkltv";
	string shewwo = "hyogpcwwilfxegaoxymlmm";
	int yhvqqx = 3883;
	if (3883 == 3883) {
		int etbrjwkeer;
		for (etbrjwkeer = 0; etbrjwkeer > 0; etbrjwkeer--) {
			continue;
		}
	}
	if (string("oygpawolltazlztdvvnbvgkltv") != string("oygpawolltazlztdvvnbvgkltv")) {
		int etopfxzzdr;
		for (etopfxzzdr = 20; etopfxzzdr > 0; etopfxzzdr--) {
			continue;
		}
	}
	return true;
}

void sidscww::ncnyndwcvekcwhik(int zcxrjhqfyxyzx, double jcrrpyeepi, bool yrgheinif, string qdkovizktdux, int vueyaaigkjpsrd, string mmrpziufmmcqjqc, double uuuhmkamyfcybe, bool eyonkzxbjnrbr) {
	int hmgzupy = 5333;
	string ifqqtuilvsqiscd = "mnjxnnqybvwlcllqfslibsdibrajblqsflmfknduadkokvsibefhhvpfwzhlbdazvglsxhwylcntixzloxcozrmicjjpexu";
	double oxgrbuorqsxbhy = 30973;
	string leshq = "qisjiqgdmqikeqfrjtzvlsvkjabequfdxrk";
	int nqwbcmrzt = 3;
	if (string("qisjiqgdmqikeqfrjtzvlsvkjabequfdxrk") == string("qisjiqgdmqikeqfrjtzvlsvkjabequfdxrk")) {
		int ah;
		for (ah = 55; ah > 0; ah--) {
			continue;
		}
	}
	if (5333 == 5333) {
		int ehem;
		for (ehem = 100; ehem > 0; ehem--) {
			continue;
		}
	}
	if (30973 != 30973) {
		int lxoouohfpm;
		for (lxoouohfpm = 77; lxoouohfpm > 0; lxoouohfpm--) {
			continue;
		}
	}

}

void sidscww::udvxlptqxhqzqezbjnha(int rtehsagljpxjbgs, string fuskinbgfwm, string btfzhce, string pkxnli, string xyagdhqcbay, double uhgpmygyq, double bhqtbcwba) {
	string jtaemzfayufkpex = "lqtwwhhbkvfajxdzzvsqkvxcdjdjzdri";
	int opcpngifntahuwg = 3172;
	bool jizpvimd = true;
	string wqxcbuabzym = "foeqsfbitsqeykctpmgclbmlpeconklgejijusqnpqtcyituifgcthoaimqpiiyoejpluq";
	string grgjyw = "lnvkueddmghzuncdvpmbctnfvnvtmyobcngnvrimsxweqklucyqcrqweqcarjjoxlyxeyhcdqrryputrtpyfliwxfmtin";
	if (3172 == 3172) {
		int mbkdu;
		for (mbkdu = 1; mbkdu > 0; mbkdu--) {
			continue;
		}
	}

}

int sidscww::izoupekbmrctovkmeinfbiwmz() {
	bool lxijbbohks = true;
	bool undwwoby = false;
	double murtmcslcrphg = 31416;
	string wwdnyuxlcfanxz = "fbvgkdwhlxxgqmzfeqzhakaezxfcundhwussbquvnxr";
	if (false == false) {
		int diflpgbs;
		for (diflpgbs = 51; diflpgbs > 0; diflpgbs--) {
			continue;
		}
	}
	if (31416 == 31416) {
		int mrbwvtuevk;
		for (mrbwvtuevk = 28; mrbwvtuevk > 0; mrbwvtuevk--) {
			continue;
		}
	}
	if (true != true) {
		int wrytd;
		for (wrytd = 66; wrytd > 0; wrytd--) {
			continue;
		}
	}
	return 8309;
}

sidscww::sidscww() {
	this->fmuegqlatbrqnoajdlrzykjx(77386, 1668, string("moblzjvlvtphmuqxiuxfkpgaklmatjfrxvsaservgyonznltngimjrusdnynjfvgy"), 533, false, string("htpotesglaudabsbsqfmdchacxyxwzoyxwixoekmyedkdnugzjxjpzuohloxmtf"), 8545, string("fopwsjpfxrotukbuznetdgzjxhlvawxwawcjceeazggfcq"), true, 310);
	this->ncnyndwcvekcwhik(2855, 59437, true, string("ufzauptkiqxgxzwdhmuwtmiqkjzhbgrwsonzviiogddzpklitninywrazhwylhxzjbdtjaebqwhirrlyz"), 5288, string("hzxinupdhebjexflnnibgoggdyzzkqolaulaovahdffbxayamukledpgvjfqfhuqsmhykzdkgbqlrffqryixibpd"), 64622, false);
	this->udvxlptqxhqzqezbjnha(10, string("rxatzjtrxmag"), string("dazehi"), string("vbqjgnihfucnk"), string("jjfskcsdmjhmfvanqjslpzyqryfqgnybzzqdhtyxuthjwemssnbxziihycddosahwk"), 57574, 55975);
	this->izoupekbmrctovkmeinfbiwmz();
	this->yilbcgzncykdogex(21);
	this->vlnmwyfaedkvbkgjyorlketzz(3184, 386, 1555, string("jbcgxrgsjkhalynrjlzxycpjnxhmnbmotzjaiibechcsbcdghmtyrgfmtvbxtnkswfdqgvajjhrpf"), false, string("cbogsirdhqdtonjlabaubgzhvwnuotuvnmflqhhytczdjyhwicrxuvxbmqjvnotj"));
	this->xrhzmyamtwv(72, string("hemboqwkjsigusdgevyyeiqefrepruvydgumjoytnoisoltcdsxgpmypvyopvqecuyseyvyadsvrghjsxnubnntior"), false);
	this->pccqpogkehezfeuccib();
	this->okqbjqbxsrntbn(string("iydvsaytesabaoqzjewqvcfzmzzfjvmkzubjcuqgwhbysdiqajnsbeerihvoyospsakfmkrgswpwpbzzcnq"), 4013, 2875, false, false, string("lkeiuqolkwjugcyogzlevhohzkmnptmolcpuickkxcwebvystoclzwbfckgzfuwxnmyjptbqi"), 24384, 2114, 67735);
	this->dowpplunoovd(string("wmcamfbkiwcbqguxnqiuzbhktttoudgxboakbalrqhjxsefkzl"), false, string("lnqakkixpkmjsmdkxdujxmgznwtkmksulclxigwailmvtgzjynmkpjbxoqxbrdrzhyshxvnoyjhrlmgtmfubwlewydmw"), false, 1194, string("vqqftqgiectoocizwgqzp"), string("vwshfzb"), 4203);
	this->xteyizsjblfnndillhiiqbjw(false);
	this->txgadceaeglfqwxa(string("ccbenjhnpaffapnnrgacchjkzzgfilodomciecsrtlplnxecqasveybgafiuxryjsrskw"), string("sowdnfevtrfannremljijpfdiyydkkavptjacdrzepvsqfkjpqvebpesisdyospmvgstbsymzllomqduhmntpoaigyby"), string("skfcmjbnlkulqooctsfpyrntkheyfubtyerayueuignhuzksloyxgvyhnjtdbcwpbpwungkojmblg"), 27256, string("zcluewqdvxznxnsebrfbmyuocdzuzeqkfloouolfcrcoaxsflgigofhaahxppcecsjazhspjpyfskmqgixedtvd"), string("qzmlfyfqqeixzwifqtjsvduzjnafemkrurvzfjdbfzxxcfrxxcyehmdysvf"), 2600, false);
	this->cbxzvvowwqizdn(59757, 1500, false, 1091, 298, string("nepsfoqolqoriwmoddbwd"), true, true, true);
	this->frywgpebvtiqj(true, 32862, 1158, 3861, true, string("xceowwqqmxcuiwvqywifrbxgqldctk"), 2132, 10167, string("oxisquxerukvtqbsnhbdup"));
	this->ekunigpqpcjxltgwxlwoe(2034, 3280, string("niidvyfraqkjpwbmgfuz"), true);
}
