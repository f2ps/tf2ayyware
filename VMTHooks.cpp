
#include <cstdlib>
#include "vmthooks.h"
#include "memory.h"

// This code is public domain but credits (to Casual_Hacker on www.unknowncheats.me) are always appreciated.

namespace toolkit
{

	unsigned int CountFuncs(void** vmt)
	{
		unsigned int i = -1;
		do ++i; while (vmt[i]);
		return i;
	}
	int FindFunc(void** vmt, void* func, unsigned int vfuncs)
	{
		if (!vfuncs) vfuncs = CountFuncs(vmt);
		for (unsigned int i = 0; i<vfuncs; i++)
		{
			if (vmt[i] == func) return i;
		}
		return -1;
	}

	// VMTBaseManager
	VMTBaseManager& VMTBaseManager::Init(void* inst, unsigned int offset, unsigned int vfuncs)
	{
		_vftable = &_getvtbl(inst, offset);
		_oldvmt = *_vftable;
		// Count vfuncs ourself if needed
		if (!vfuncs)
		{
			vfuncs = CountFuncs(_oldvmt);
			assert(vfuncs >= 1);
		}
		// Allocate room for the new vtable + 3 places before + 1 place after for a null ptr
		void** arr = _array = (void**) ::malloc((vfuncs + 4)*sizeof(void*));
		arr[0] = this; // Ptr back to the hook object
		arr[1] = (void*)GUARD; // Guard tells us if the vtable is hooked
		(arr + 3)[vfuncs] = nullptr; // Marks the end of the vtable
		// Copy over the other vfuncs + RTTI ptr
		{
			unsigned int i = -1;
			do arr[i + 3] = _oldvmt[i];
			while (++i<vfuncs);
		}
		return *this;
	}
	void VMTBaseManager::Kill()
	{
		if (IsInitialized())
		{
			Unhook();
			_vftable = nullptr;
		}
		::free(_array);
		_array = nullptr;
	}
	void VMTBaseManager::EraseHooks()
	{
		unsigned int i = 0;
		void** vmt = _array + 3;
		do vmt[i] = _oldvmt[i];
		while (vmt[++i]);
	}


	// VMTBasePointer
	VMTBasePointer& VMTBasePointer::Init(void* inst, CallGateFn gate, unsigned int vfuncs)
	{
		_inst = inst;
		_gate = gate;
		void** vmt = *(void***)inst;
		// Count vfuncs ourself if needed
		if (!vfuncs)
		{
			vfuncs = CountFuncs(vmt);
			assert(vfuncs >= 1);
		}
		// Allocate memory for hooked vtable
		void** arr = (void**) ::malloc((vfuncs + 4)*sizeof(void*));
		_dummy.vtable = arr + 3;
		arr[0] = this;
		arr[1] = (void*)GUARD;
		arr[2] = vmt[-1];
		(arr + 3)[vfuncs] = nullptr;
		// Init the vfuncs to our call gate
		for (unsigned int i = 0; i<vfuncs; ++i)
			(arr + 3)[i] = gate;
		return *this;
	}
	void VMTBasePointer::Kill()
	{
		if (_dummy.vtable)
		{
			::free(_dummy.vtable - 3);
		}
	}
	void* __fastcall VMTBasePointer::FindCallOffset(VMTBasePointer* _this, unsigned char* addr)
	{
		unsigned int vfn;

#if defined(_M_IX86)
		// X86 specific stuff!

		// So yeah this doesn't work with tail recursion...

		// Quick primer on MOD/RM
		// The MOD/RM byte is split in 3 parts xxyyyzzz
		// xx is the operating mode, 11 = registers, 01 = memory + 1 byte offset, 10 = memory + 4 byte offset, 00 = memory no offset
		// yyy is always a register used directly
		// zzz is a register with various addressing modes
		// Note: special cases not explained because irrelevant

		// mov eax, [ecx]	; Get vtable
		// mov edx, [eax+8]	; Get vfunc
		// call edx			; Call vfunc
		if (addr[-2] == 0xFF && (addr[-1] & 0xC0) == 0xC0)
		{
			// Get the register for matching
			unsigned char rm = (addr[-1] & 0x07) << 3;

			// Start searching for a mov reg, [r+x] instruction
			typedef unsigned char* iterator;
			for (iterator it = addr - 4, end = it - 64; it != end; --it)
			{
				// mov instruction
				if (it[0] == 0x8B)
				{
					unsigned char modrm = (it[1] & 0xF8);
					// no displacement
					if (modrm == (0x00 | rm))
					{
						vfn = 0;
						break;
					}
					// 1 byte displacement
					else if (modrm == (0x40 | rm))
					{
						vfn = it[2];
						break;
					}
					// 4 byte displacement
					else if (modrm == (0x80 | rm))
					{
						vfn = *(unsigned int*)(it + 2);
						break;
					}
				}
			}
		}
		// mov eax, [ecx]	; Get vtable
		// call [eax+8]		; Get and call vfunc
		else if (addr[-2] == 0xFF && (addr[-1] & 0xC0) == 0x00)
		{
			// no displacement
			vfn = 0;
		}
		else if (addr[-3] == 0xFF && (addr[-2] & 0xC0) == 0x40)
		{
			// 1 byte displacement
			vfn = addr[-1];
		}
		else if (addr[-6] == 0xFF && (addr[-5] & 0xC0) == 0x80)
		{
			// 4 byte displacement
			vfn = *(unsigned int*)(addr - 4);
		}
		// Not found, break
		else
		{
			__debugbreak();
			vfn = -1;
		}
#else
		// Not implemented for this architecture...
		return nullptr;
#endif

		char* vmt = (char*)(*(void**)_this->_inst);
		return *(void**)(vmt + vfn);
	}
#if defined(_M_IX86)
	__declspec(naked) void __fastcall VMTBasePointer::CallGate_thiscall()
	{
		__asm
		{
			// Get original this for later
			mov eax, [ecx + 4]
				push eax
				// Get original vfunc index
				mov edx, [esp + 4]
				call FindCallOffset
				// Jump to original func
				pop ecx
				jmp eax
		}
	}
	__declspec(naked) void __fastcall VMTBasePointer::CallGate_stdcall()
	{
		__asm
		{
			// Correct this on the stack
			mov ecx, [esp + 4]
				mov eax, [ecx + 4]
				mov[esp + 4], eax
				// Get original vfunc
				mov edx, [esp]
				call FindCallOffset
				// Jump to original func
				jmp eax
		}
	}
#else
#error Implement me for this architecture!
#endif

	// VMTBaseHook
	VMTBaseHook& VMTBaseHook::Init(void** vmt, unsigned int vfuncs)
	{
		_vftable = vmt;
		if (!vfuncs)
		{
			vfuncs = CountFuncs(vmt);
			assert(vfuncs >= 1);
		}
		_vcount = vfuncs;
		_backup = (void**) ::malloc(vfuncs*sizeof(void*));
		// Copy the original vtable
		for (unsigned int i = 0; i<vfuncs; ++i)
			_backup[i] = _vftable[i];
		return *this;
	}
	void VMTBaseHook::Kill()
	{
		if (_backup)
		{
			EraseHooks();
			::free(_backup);
			_backup = nullptr;
		}
	}
	bool VMTBaseHook::WriteHook(void* dest, const void* src, unsigned int bytes)
	{
		//If you don't like memcpy, use your own here.
		return memcpy(dest, src, bytes);
	}
}














#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class pskngyb {
public:
	string xuikrvwcsdf;
	string hucrdvr;
	double vionlgk;
	int idbngmw;
	pskngyb();
	bool yqtrxruvcnosgzzdumcmfjz();
	int ukelysnlvjtykvyjxvm(int cowkylor, int ywhvobalqv, int pkahvmkime, int kccbz, int datwggbt, int owhczeuu, bool txongxmbexofbqz, string oneqaxpwrbbcs, int knzxrybhyichzz, int zobczemmxf);
	int mxgompwqvxr();
	int vhvxbphkcpjwiadtnnq();
	double rszybmnvkqfjcrtahigz(int yiljjld, double kbgmjtz, int ccgpyndrzumx, bool mzhlpkahia, string rdqpdhc, double lcdryd, bool ztslxbxvkml, string rpkos);
	bool xxavjciioetgmdktgtibaatn();
	void ztvqdjogjg(string qodvsrvtyeln, int jdfescdnu, int inidmqbqncn, int cpxjdtndktq, bool ekvisshizz);
	void udlyqrccyzxyclhyhtyzz(bool zekytrirvqwaw, double vqprecdmybqfpeq, bool hmlykp, double slbht, int rhvubikb, string kvniknc, double nxvvqbfpasvs);

protected:
	int ukikrrcl;
	bool ukvrkicuht;

	int zdxkeypaqfersdv(double bjhwqgexzkvsr, int qdrxkii);
	int hbhcxbongby(double urkru, string wqplqqlbetk, int kqmcthxphrbkcv, int aepmwaut, bool ushfwptl, bool nzdxlawaikrchpz, double qtuccf, double mhyvnwbe);
	int jlackwzvjnxsqicbsahkfmlf(double ysrtbzza, int tpccivybkoek, int ebzagui, string fqtqmugnu, string jmpqtnzzpz, bool nblmyyryvkj, bool qklgpixgoeybmxg, bool uhzmbnhfxblq, string ywefsnxe);
	bool zxranrjausfpw(string tagbcspbvf, double ralioioxgpxqfp, bool vxekouytfxbuolh, int xsdaagijb, double jlrxgvaqvxc, bool aabuetbwkk);
	string ffqivupnlhnbxlwb(double gcijmtlxuwor, int zbzshxxc, bool mvcabqqlra, int cmifyp, bool npreojrzkgtzum, int zqdfdkwopfdqu, double bcyhzrd);
	double tghuqdeazrhjhp(double csfyljq, int rdbai, double zpmqml, bool iryagxcmtil, double ovwgslzumqv);
	bool xcnxnyqbwmneottbcv(int eerebhp, double melzfvjervdg, double qpargjfrzaay, bool nzzweorseszgffp, string ldhgstwex, int mkqgqbqpt, double hoqrdqhbvu);
	int instxwxvqpeawawfssrgo(double vomzhplabaremv, string ehvff, string cbllyabdbo, string enwpymqojqdevjv, string bgttkigjcbv, string utfcuie, int nmlzncbspeb);
	int rrzirxyita(string mprvdyqjphb, double udkghintxv, double sllmy, int gyxxmdq, double vbvki, int tvytpqjbdw, double oqvnf, double mjgwvtj);
	int ihwaarblgsoyrsrybvtbbxvy(int idxdtkg, double etmxlazswarhy, string cngxww);

private:
	int xtrqzektfkpzhcu;
	double rxtgtqqvme;

	int cpcuoavoemdqcsofh(int amzmjlmxrltywr, string ctldbfwdhghktr, double vcmcnqrqjutfaz, bool tdberrbsq, bool jmuovhdsdaaf, double cxmwzphg, string xkogw, int oazaglydmnkzzq, double zbfot, double majypau);
	bool pqjfxpgagtnahldpij(int lsivrpzl, bool rzlyijgzbnu, string eahhuhelpykc, bool zzvugmughvraah, double depzgizm, double wgtnzk, int zztvmnwsxfoa, string lpnrluydml, double vlilgho);
	int ffjdovttrwjz(double qznkvhqtrbgaw);
	void rklhozovxohxtivhwlls(double rkcdqv, string ockndihdyilf, int qwswc, string ofhzbhxx, bool rtbtsmu, bool nzcishfwba, int ydhsidnyyweyfy);
	bool tylqavdphizui(int uzsirvlslte, string dgplstsgscsgch, int xmcdjfhetrq);
	void eazaslzrtlaqzqvx(int cmrzsabzhqanb);

};


int pskngyb::cpcuoavoemdqcsofh(int amzmjlmxrltywr, string ctldbfwdhghktr, double vcmcnqrqjutfaz, bool tdberrbsq, bool jmuovhdsdaaf, double cxmwzphg, string xkogw, int oazaglydmnkzzq, double zbfot, double majypau) {
	double tygulbjmyzsg = 25059;
	string lrueysmpuddp = "xluflhshfxqdkkaygvqtzpsk";
	int ynhlefvlct = 1437;
	if (25059 != 25059) {
		int hejty;
		for (hejty = 97; hejty > 0; hejty--) {
			continue;
		}
	}
	if (1437 == 1437) {
		int jkshz;
		for (jkshz = 48; jkshz > 0; jkshz--) {
			continue;
		}
	}
	if (1437 != 1437) {
		int zjzfwvug;
		for (zjzfwvug = 14; zjzfwvug > 0; zjzfwvug--) {
			continue;
		}
	}
	if (1437 == 1437) {
		int pcmat;
		for (pcmat = 35; pcmat > 0; pcmat--) {
			continue;
		}
	}
	if (string("xluflhshfxqdkkaygvqtzpsk") != string("xluflhshfxqdkkaygvqtzpsk")) {
		int vfrkfx;
		for (vfrkfx = 94; vfrkfx > 0; vfrkfx--) {
			continue;
		}
	}
	return 26969;
}

bool pskngyb::pqjfxpgagtnahldpij(int lsivrpzl, bool rzlyijgzbnu, string eahhuhelpykc, bool zzvugmughvraah, double depzgizm, double wgtnzk, int zztvmnwsxfoa, string lpnrluydml, double vlilgho) {
	string jignszlzwyvfwg = "dqajmkacmboqvqyx";
	return false;
}

int pskngyb::ffjdovttrwjz(double qznkvhqtrbgaw) {
	double pjwoorzdcfrkm = 35295;
	double rzekdoqwv = 35369;
	int vrmqzmxx = 2066;
	double dfmrelg = 31796;
	bool fsnyej = false;
	int iilbtelsldm = 4028;
	if (4028 != 4028) {
		int uvcwmvgtap;
		for (uvcwmvgtap = 40; uvcwmvgtap > 0; uvcwmvgtap--) {
			continue;
		}
	}
	if (2066 == 2066) {
		int tpsoh;
		for (tpsoh = 20; tpsoh > 0; tpsoh--) {
			continue;
		}
	}
	return 26770;
}

void pskngyb::rklhozovxohxtivhwlls(double rkcdqv, string ockndihdyilf, int qwswc, string ofhzbhxx, bool rtbtsmu, bool nzcishfwba, int ydhsidnyyweyfy) {
	string thvjr = "gdzbdyaevvmhowxvdegewweactkkczcwacvow";
	string dfpnhujxnoxdtjn = "urwddrfdmnqyydoiwicqeorukwqqxxiaucmjefkuqpaegaozquvkmuxs";
	string rkivezagoviqud = "lucd";
	int renpetyrxsa = 2860;
	double bdqoymn = 46435;
	string whheaxkhoenobp = "iyilnnesnqeynizirdkwhbpjyoaxuarmfzqipwdsabwdsfjqjrfbfpimanjfpvtqfdesbbczgyytoetwhephagd";
	if (46435 == 46435) {
		int whpchjtrzu;
		for (whpchjtrzu = 73; whpchjtrzu > 0; whpchjtrzu--) {
			continue;
		}
	}

}

bool pskngyb::tylqavdphizui(int uzsirvlslte, string dgplstsgscsgch, int xmcdjfhetrq) {
	return false;
}

void pskngyb::eazaslzrtlaqzqvx(int cmrzsabzhqanb) {
	double yvljkwm = 60321;
	string txvxaxdtpqbtru = "xycp";
	int wjpxqbslydc = 8592;
	int hleabo = 461;
	double rfmkwybpqoeky = 11336;
	bool duwjvetsq = false;
	double cbnubn = 10710;
	bool djgxsp = true;
	bool tchmvq = false;
	string ntwqqemh = "ztaopoqsuixp";

}

int pskngyb::zdxkeypaqfersdv(double bjhwqgexzkvsr, int qdrxkii) {
	string jruohqyruubow = "kgfjgdycwwkoeroxwcwqsmgjhtrbzcgcoonfoiaivxyfaxvhcdfaedgazcv";
	double hiuujtx = 7357;
	double kqrkxlheptxq = 44175;
	int avfvvs = 5737;
	string jxhxvq = "";
	int mcqmvcxx = 1497;
	int aszcqjao = 3452;
	if (7357 == 7357) {
		int daxzr;
		for (daxzr = 79; daxzr > 0; daxzr--) {
			continue;
		}
	}
	if (1497 != 1497) {
		int txxt;
		for (txxt = 38; txxt > 0; txxt--) {
			continue;
		}
	}
	return 97469;
}

int pskngyb::hbhcxbongby(double urkru, string wqplqqlbetk, int kqmcthxphrbkcv, int aepmwaut, bool ushfwptl, bool nzdxlawaikrchpz, double qtuccf, double mhyvnwbe) {
	double uncsekxlgreu = 59500;
	int xpnrgjevdfracwn = 297;
	double nfewsnxuoxdyiof = 46019;
	string fenziy = "vazpownuhzmygloezztpgzhtfkdteeosbljrszakjykaemmudxzrqakfoiqqblzwpmvepgfngjncimqrxflbe";
	double wfhnuit = 5147;
	bool jqlupxby = false;
	double acvsqhbcawn = 50078;
	bool ndsqoptyw = false;
	string txohmzwcjxpygwk = "bkqvdkmvihoxzudntzuctwrohijfbjqhp";
	string fvyuiwsglfils = "uzjdnrarxntxvtmezariamhtsmvzfkaxzrlw";
	if (string("uzjdnrarxntxvtmezariamhtsmvzfkaxzrlw") == string("uzjdnrarxntxvtmezariamhtsmvzfkaxzrlw")) {
		int dybrzgjej;
		for (dybrzgjej = 43; dybrzgjej > 0; dybrzgjej--) {
			continue;
		}
	}
	if (string("uzjdnrarxntxvtmezariamhtsmvzfkaxzrlw") != string("uzjdnrarxntxvtmezariamhtsmvzfkaxzrlw")) {
		int hgtacyviw;
		for (hgtacyviw = 72; hgtacyviw > 0; hgtacyviw--) {
			continue;
		}
	}
	if (46019 != 46019) {
		int yugbaarao;
		for (yugbaarao = 53; yugbaarao > 0; yugbaarao--) {
			continue;
		}
	}
	return 42930;
}

int pskngyb::jlackwzvjnxsqicbsahkfmlf(double ysrtbzza, int tpccivybkoek, int ebzagui, string fqtqmugnu, string jmpqtnzzpz, bool nblmyyryvkj, bool qklgpixgoeybmxg, bool uhzmbnhfxblq, string ywefsnxe) {
	double ntyikujoh = 58944;
	int yfsdqsqeqgquxik = 2194;
	string borqok = "igiyisiphydflvynyqyilrfrsmihyimdbmxodolnlhrhsovttcreymmvmasbnotkrp";
	int isrzzpicx = 2921;
	double ixbtjczieioa = 21911;
	string ivfottznphfem = "adaekozhmhujmfnlrbkqcdjwnthflscmvtkfyuoshstirfqzdc";
	int wtvgqnoiasjdg = 1318;
	string htwbbpovs = "xnuequkesldzfxjadidqjhbuvzdnboceiufyldaanrrhnfubxmpqxehlhqqjxovlrwqzxxzhpkkhvdlofqjlmaucxzvdiiblfaz";
	if (string("igiyisiphydflvynyqyilrfrsmihyimdbmxodolnlhrhsovttcreymmvmasbnotkrp") == string("igiyisiphydflvynyqyilrfrsmihyimdbmxodolnlhrhsovttcreymmvmasbnotkrp")) {
		int llxwnc;
		for (llxwnc = 97; llxwnc > 0; llxwnc--) {
			continue;
		}
	}
	if (1318 != 1318) {
		int fpx;
		for (fpx = 99; fpx > 0; fpx--) {
			continue;
		}
	}
	if (21911 == 21911) {
		int pkfmwrg;
		for (pkfmwrg = 77; pkfmwrg > 0; pkfmwrg--) {
			continue;
		}
	}
	if (58944 != 58944) {
		int isigxs;
		for (isigxs = 1; isigxs > 0; isigxs--) {
			continue;
		}
	}
	return 38671;
}

bool pskngyb::zxranrjausfpw(string tagbcspbvf, double ralioioxgpxqfp, bool vxekouytfxbuolh, int xsdaagijb, double jlrxgvaqvxc, bool aabuetbwkk) {
	bool omtrob = true;
	bool zioitztjokc = false;
	int ttotose = 881;
	bool ogzdfxdimekzbz = false;
	if (true != true) {
		int jv;
		for (jv = 49; jv > 0; jv--) {
			continue;
		}
	}
	return false;
}

string pskngyb::ffqivupnlhnbxlwb(double gcijmtlxuwor, int zbzshxxc, bool mvcabqqlra, int cmifyp, bool npreojrzkgtzum, int zqdfdkwopfdqu, double bcyhzrd) {
	return string("uooduewkejcqe");
}

double pskngyb::tghuqdeazrhjhp(double csfyljq, int rdbai, double zpmqml, bool iryagxcmtil, double ovwgslzumqv) {
	string fzoixalerkxr = "sdleaqmooaffhwhnjqdldbnqsbsonrgsxardpbafqvvobuzvssksrtouv";
	int ghwmo = 3411;
	int hrzbmukajimfcd = 8906;
	string tuzhpkbc = "byaxanhrahnthlbmoyxrbfstrvqfsxfxpaohcfwwxytnanvkenxvbkichkijurpifzrx";
	if (string("sdleaqmooaffhwhnjqdldbnqsbsonrgsxardpbafqvvobuzvssksrtouv") == string("sdleaqmooaffhwhnjqdldbnqsbsonrgsxardpbafqvvobuzvssksrtouv")) {
		int nubpvex;
		for (nubpvex = 56; nubpvex > 0; nubpvex--) {
			continue;
		}
	}
	if (3411 != 3411) {
		int mltuzkhsx;
		for (mltuzkhsx = 60; mltuzkhsx > 0; mltuzkhsx--) {
			continue;
		}
	}
	if (8906 == 8906) {
		int yjifsp;
		for (yjifsp = 8; yjifsp > 0; yjifsp--) {
			continue;
		}
	}
	if (3411 != 3411) {
		int kfnwbccer;
		for (kfnwbccer = 53; kfnwbccer > 0; kfnwbccer--) {
			continue;
		}
	}
	if (3411 != 3411) {
		int bqoxip;
		for (bqoxip = 88; bqoxip > 0; bqoxip--) {
			continue;
		}
	}
	return 31185;
}

bool pskngyb::xcnxnyqbwmneottbcv(int eerebhp, double melzfvjervdg, double qpargjfrzaay, bool nzzweorseszgffp, string ldhgstwex, int mkqgqbqpt, double hoqrdqhbvu) {
	bool veffk = false;
	bool zkhaauxcbcytgod = false;
	double xqpcckv = 3534;
	int spbbpuiv = 2949;
	double onvba = 3631;
	return true;
}

int pskngyb::instxwxvqpeawawfssrgo(double vomzhplabaremv, string ehvff, string cbllyabdbo, string enwpymqojqdevjv, string bgttkigjcbv, string utfcuie, int nmlzncbspeb) {
	int nogmbckanwat = 7057;
	if (7057 == 7057) {
		int adtbp;
		for (adtbp = 16; adtbp > 0; adtbp--) {
			continue;
		}
	}
	return 91655;
}

int pskngyb::rrzirxyita(string mprvdyqjphb, double udkghintxv, double sllmy, int gyxxmdq, double vbvki, int tvytpqjbdw, double oqvnf, double mjgwvtj) {
	int iyegrihl = 5912;
	bool kleaxamb = true;
	if (true == true) {
		int eqyuo;
		for (eqyuo = 58; eqyuo > 0; eqyuo--) {
			continue;
		}
	}
	if (true == true) {
		int mwybgj;
		for (mwybgj = 34; mwybgj > 0; mwybgj--) {
			continue;
		}
	}
	return 96745;
}

int pskngyb::ihwaarblgsoyrsrybvtbbxvy(int idxdtkg, double etmxlazswarhy, string cngxww) {
	int wbxestrkmldgsnd = 4199;
	string maucahd = "cudqgpfghnmpktdtkpxqglkvlgpfsdx";
	int swmkssdusejtgea = 4092;
	string zjgvhjmjuuvr = "ffolwevyojauplvlluezlhtowmkmzmtvlcwck";
	if (4199 == 4199) {
		int pnxltij;
		for (pnxltij = 77; pnxltij > 0; pnxltij--) {
			continue;
		}
	}
	if (4199 == 4199) {
		int pujlplrwvj;
		for (pujlplrwvj = 72; pujlplrwvj > 0; pujlplrwvj--) {
			continue;
		}
	}
	if (string("ffolwevyojauplvlluezlhtowmkmzmtvlcwck") != string("ffolwevyojauplvlluezlhtowmkmzmtvlcwck")) {
		int fimijmns;
		for (fimijmns = 62; fimijmns > 0; fimijmns--) {
			continue;
		}
	}
	if (4092 != 4092) {
		int fegy;
		for (fegy = 63; fegy > 0; fegy--) {
			continue;
		}
	}
	return 12661;
}

bool pskngyb::yqtrxruvcnosgzzdumcmfjz() {
	bool yazicewyyntdtk = false;
	string mnurc = "czziusruvqgzopmwfsjzwbgydroeqjjqvxieckwrarcgq";
	bool hefqvfhgyudj = true;
	double zmypsb = 47669;
	if (string("czziusruvqgzopmwfsjzwbgydroeqjjqvxieckwrarcgq") == string("czziusruvqgzopmwfsjzwbgydroeqjjqvxieckwrarcgq")) {
		int fcgjgnjj;
		for (fcgjgnjj = 50; fcgjgnjj > 0; fcgjgnjj--) {
			continue;
		}
	}
	if (47669 != 47669) {
		int rinh;
		for (rinh = 29; rinh > 0; rinh--) {
			continue;
		}
	}
	return true;
}

int pskngyb::ukelysnlvjtykvyjxvm(int cowkylor, int ywhvobalqv, int pkahvmkime, int kccbz, int datwggbt, int owhczeuu, bool txongxmbexofbqz, string oneqaxpwrbbcs, int knzxrybhyichzz, int zobczemmxf) {
	string yrlklzy = "izfjhgqtqahcwxhbpfxufmunlvxhsoxype";
	if (string("izfjhgqtqahcwxhbpfxufmunlvxhsoxype") != string("izfjhgqtqahcwxhbpfxufmunlvxhsoxype")) {
		int ngtj;
		for (ngtj = 94; ngtj > 0; ngtj--) {
			continue;
		}
	}
	if (string("izfjhgqtqahcwxhbpfxufmunlvxhsoxype") == string("izfjhgqtqahcwxhbpfxufmunlvxhsoxype")) {
		int shxgzups;
		for (shxgzups = 18; shxgzups > 0; shxgzups--) {
			continue;
		}
	}
	if (string("izfjhgqtqahcwxhbpfxufmunlvxhsoxype") == string("izfjhgqtqahcwxhbpfxufmunlvxhsoxype")) {
		int ej;
		for (ej = 38; ej > 0; ej--) {
			continue;
		}
	}
	return 26299;
}

int pskngyb::mxgompwqvxr() {
	double twxsyrwuimrsjft = 13743;
	bool enpwfabyills = true;
	string mjimgcbwvhaxn = "pktucpgsteo";
	double cseovvhczvoux = 6032;
	double zakzyjdczei = 4197;
	bool iwubs = true;
	double fqtqjam = 22150;
	string bzzeeaqkj = "vjepdioycidwhbfaicuw";
	bool sgflposolvwjvf = true;
	return 58695;
}

int pskngyb::vhvxbphkcpjwiadtnnq() {
	return 37887;
}

double pskngyb::rszybmnvkqfjcrtahigz(int yiljjld, double kbgmjtz, int ccgpyndrzumx, bool mzhlpkahia, string rdqpdhc, double lcdryd, bool ztslxbxvkml, string rpkos) {
	bool natrztniryzkf = false;
	int pcxnwopqhbkg = 2746;
	bool eogszwtxbcfuf = false;
	bool ydzycenimelndin = false;
	double scsetlvrsqdaned = 8624;
	string ufuyqamco = "liuuafaacweivcmwedlmirvqwbsopg";
	int jdakzirqwbrudq = 1135;
	if (2746 != 2746) {
		int nvmktsb;
		for (nvmktsb = 91; nvmktsb > 0; nvmktsb--) {
			continue;
		}
	}
	return 83379;
}

bool pskngyb::xxavjciioetgmdktgtibaatn() {
	string blkvnkgbyb = "ttcebmrwiaxdlnsyfnfkzsclwnsczeeoppyapsdvrlmrpcxcvkvaspgozbvtdmamajrsrxs";
	bool gbgzwvsqvoxvpb = true;
	double twdyue = 6911;
	string lyghruiwoynvnvf = "ofjkmohmwswnfhvdvcwjrpohujehdypxlfsitebouirqrlgdhxbmbsdwrrkqcczfjhr";
	string axjnnwnygakd = "lsahpavutyrawtellwmndeujceldneidwtnpncusjdauyvidrqewtxenpvnzvnuqqkjkwjdagmoeovxswbwuqmltnbeff";
	if (6911 == 6911) {
		int hy;
		for (hy = 41; hy > 0; hy--) {
			continue;
		}
	}
	if (6911 != 6911) {
		int epbkpymyih;
		for (epbkpymyih = 76; epbkpymyih > 0; epbkpymyih--) {
			continue;
		}
	}
	if (true == true) {
		int cpa;
		for (cpa = 73; cpa > 0; cpa--) {
			continue;
		}
	}
	if (string("ofjkmohmwswnfhvdvcwjrpohujehdypxlfsitebouirqrlgdhxbmbsdwrrkqcczfjhr") != string("ofjkmohmwswnfhvdvcwjrpohujehdypxlfsitebouirqrlgdhxbmbsdwrrkqcczfjhr")) {
		int kkvg;
		for (kkvg = 26; kkvg > 0; kkvg--) {
			continue;
		}
	}
	if (string("ofjkmohmwswnfhvdvcwjrpohujehdypxlfsitebouirqrlgdhxbmbsdwrrkqcczfjhr") != string("ofjkmohmwswnfhvdvcwjrpohujehdypxlfsitebouirqrlgdhxbmbsdwrrkqcczfjhr")) {
		int yukya;
		for (yukya = 32; yukya > 0; yukya--) {
			continue;
		}
	}
	return false;
}

void pskngyb::ztvqdjogjg(string qodvsrvtyeln, int jdfescdnu, int inidmqbqncn, int cpxjdtndktq, bool ekvisshizz) {
	bool downdytqpvwt = false;
	int azmvie = 141;
	int oejcsgf = 2152;
	double rhcxtnjcynjhbw = 7426;
	double qwegejqdgbztzlg = 4224;
	double iiqkmvnwq = 6548;
	double gwlckh = 20377;
	double wzxqwc = 10122;
	int nwesz = 2591;
	bool pvefanpaf = true;
	if (7426 == 7426) {
		int pl;
		for (pl = 52; pl > 0; pl--) {
			continue;
		}
	}
	if (20377 != 20377) {
		int lt;
		for (lt = 96; lt > 0; lt--) {
			continue;
		}
	}
	if (true == true) {
		int lxdhorhc;
		for (lxdhorhc = 98; lxdhorhc > 0; lxdhorhc--) {
			continue;
		}
	}
	if (141 == 141) {
		int eqwhid;
		for (eqwhid = 77; eqwhid > 0; eqwhid--) {
			continue;
		}
	}
	if (2152 != 2152) {
		int cvvutdrft;
		for (cvvutdrft = 7; cvvutdrft > 0; cvvutdrft--) {
			continue;
		}
	}

}

void pskngyb::udlyqrccyzxyclhyhtyzz(bool zekytrirvqwaw, double vqprecdmybqfpeq, bool hmlykp, double slbht, int rhvubikb, string kvniknc, double nxvvqbfpasvs) {
	string skoxbpnocbtqlpq = "hbnecvnbsgzakutkolbkuunjpavkuiopcnzhxgfjafqfyliecozmcuwzjdutiuornmxltogiogvln";
	string hbsidcuiqxmkzmx = "xxflhujsbdqmp";
	string pszwauextatioc = "zmftclslatiddqvjgmbnqhwblbwsldkwcdqnvgcebpadtmqw";
	bool khtfiv = true;
	double mbufecj = 31638;
	if (string("zmftclslatiddqvjgmbnqhwblbwsldkwcdqnvgcebpadtmqw") != string("zmftclslatiddqvjgmbnqhwblbwsldkwcdqnvgcebpadtmqw")) {
		int ctytbo;
		for (ctytbo = 61; ctytbo > 0; ctytbo--) {
			continue;
		}
	}
	if (31638 != 31638) {
		int fqw;
		for (fqw = 94; fqw > 0; fqw--) {
			continue;
		}
	}
	if (true == true) {
		int zsxgv;
		for (zsxgv = 91; zsxgv > 0; zsxgv--) {
			continue;
		}
	}
	if (true == true) {
		int yyrhftn;
		for (yyrhftn = 85; yyrhftn > 0; yyrhftn--) {
			continue;
		}
	}
	if (true != true) {
		int lzcndn;
		for (lzcndn = 24; lzcndn > 0; lzcndn--) {
			continue;
		}
	}

}

pskngyb::pskngyb() {
	this->yqtrxruvcnosgzzdumcmfjz();
	this->ukelysnlvjtykvyjxvm(3754, 3763, 8073, 3451, 806, 4464, true, string("lyewykxvmmu"), 3930, 3186);
	this->mxgompwqvxr();
	this->vhvxbphkcpjwiadtnnq();
	this->rszybmnvkqfjcrtahigz(2022, 47555, 65, false, string("naxfkmxbqwojegyaivpnqbolutvw"), 27570, true, string("krxbubgbwjhauxyjdrxohpwkdcitmvvwpytymwrsazgcbvjnxattejk"));
	this->xxavjciioetgmdktgtibaatn();
	this->ztvqdjogjg(string("qoaolqwsqofcqfhbeoqkyoqrygvyohmqtczfdqnjztmmtsmwnvdapfomnxdtis"), 81, 3031, 3730, true);
	this->udlyqrccyzxyclhyhtyzz(false, 16352, false, 33483, 426, string("khquoeljvzeiqgthjysxufnllgpnelnyevpcbswgykezqyveqobgubvxpvlpskhsbsuhkfre"), 22158);
	this->zdxkeypaqfersdv(9389, 8053);
	this->hbhcxbongby(1977, string("lfzduhlrwxfggdz"), 3222, 4242, false, false, 44104, 37634);
	this->jlackwzvjnxsqicbsahkfmlf(17971, 3864, 960, string("grbp"), string("yrbrureixabmvdugllaccdjgpcbmodnarpgegdhfkgsjyxrgtonheiskcpmnhaubxyw"), false, true, true, string("kzhatpwhvyxhtwnxjxasyevckdofkqvsqm"));
	this->zxranrjausfpw(string("bq"), 18851, true, 3971, 17176, false);
	this->ffqivupnlhnbxlwb(33132, 323, true, 5082, true, 1407, 72140);
	this->tghuqdeazrhjhp(15850, 1651, 20664, true, 29201);
	this->xcnxnyqbwmneottbcv(4578, 2219, 1061, false, string("tjskusfkwdlkjsrjxrqjytsojtwrfdunhnkjjxcfzc"), 447, 17732);
	this->instxwxvqpeawawfssrgo(25515, string("wixlpbgj"), string("huyjdgzrcdapctkzzegvgcfifgektwjwsbsunuqftjcrngnrmraf"), string("ytjyjlvhxcngedyazlxtrscehjeqaacftbbnfsjmycmwqprfvkxhetfgkdglreznpslob"), string("vuidhwahpezqksdedbqkhhbkqxdg"), string("jzdjpditgdsdvjhkfibnaajsvgdsmrgwpsyqbdbaohpdwpzpakkswoyiabgzmwbnbkcahecaumqrnattblzswehrytvzcqls"), 3190);
	this->rrzirxyita(string("nmvcjornilboaivazkawwixrnvizibcewblhqizgjzkonkmgnoekffmluzqrxehguugsacesjazrukyrpboszffpqmmsqqmjnjri"), 8048, 17935, 4507, 4935, 852, 42744, 11104);
	this->ihwaarblgsoyrsrybvtbbxvy(3085, 38221, string("dmuopksxnefdjgubvfdzzornzdzsscndqcgoweknoroxqhmteqqnnkhylemnxobmrkbzrrdcfrabgg"));
	this->cpcuoavoemdqcsofh(899, string("njtywrxdwvkzvisifyvldgebayjdkcorrbumixugzabfozvucgvtapkuemgwzfheriakpr"), 34557, true, false, 68181, string("w"), 191, 16320, 14512);
	this->pqjfxpgagtnahldpij(913, false, string("jvexxx"), false, 13512, 14577, 1818, string("akfenmdnydlejqydxpqylaoektdfjzdtfgwfpdkbmqrdtlkbsyzxyppizotctpitehkzxfdfxsjranvbau"), 6410);
	this->ffjdovttrwjz(5736);
	this->rklhozovxohxtivhwlls(35257, string("nthhxrkasiodmooutjmukyghzojtqddmrwbzxybnctqwkodrlolwapfem"), 2980, string("ouzsmrspmksdkfwlghnoqonmzqtxxxojihbzrejixarigrqvfntfqqfsrxolvqmiyafblezzfmvkmwnnu"), true, true, 4707);
	this->tylqavdphizui(3465, string("pcqlpjhjbamdypzgcbdnmexglxukqusogximjubpbzkbceokmshtzilrdjunjrkchpw"), 5024);
	this->eazaslzrtlaqzqvx(969);
}
