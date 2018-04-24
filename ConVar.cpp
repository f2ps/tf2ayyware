#include "ConVar.h"

#include "SDK.h"

ConCommandBase*		ConCommandBase::s_pConCommandBases = NULL;
static int			s_nCVarFlag = 0;
static int			s_nDLLIdentifier = -1;
static bool			s_bRegistered = false;

class CDefaultAccessor : public IConCommandBaseAccessor
{
public:
	virtual bool RegisterConCommandBase(ConCommandBase *pVar)
	{
		gInts.cvar->RegisterConCommand(pVar);
		return true;
	}
};

static CDefaultAccessor s_DefaultAccessor;
IConCommandBaseAccessor	*ConCommandBase::s_pAccessor = &s_DefaultAccessor;

void ConVar_Register(int nCVarFlag, IConCommandBaseAccessor *pAccessor)
{
	if (s_bRegistered)
		return;

	s_bRegistered = true;
	s_nCVarFlag = nCVarFlag;
	s_nDLLIdentifier = gInts.cvar->AllocateDLLIdentifier();

	ConCommandBase *pCur, *pNext;

	ConCommandBase::s_pAccessor = pAccessor ? pAccessor : &s_DefaultAccessor;
	pCur = ConCommandBase::s_pConCommandBases;
	while (pCur)
	{
		pNext = pCur->m_pNext;
		pCur->AddFlags(s_nCVarFlag);
		pCur->Init();
		pCur = pNext;
	}

	ConCommandBase::s_pConCommandBases = NULL;
}

//-------------------------------------------------------------
// ConVar methods
//-------------------------------------------------------------
ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags)
{
	Create(pName, pDefaultValue, flags);
}

ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString)
{
	Create(pName, pDefaultValue, flags, pHelpString);
}

ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax)
{
	Create(pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax);
}

ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, FnChangeCallback_t callback)
{
	Create(pName, pDefaultValue, flags, pHelpString, false, 0.0, false, 0.0, callback);
}

ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback)
{
	Create(pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax, callback);
}

ConVar::~ConVar(void)
{
	if (m_Value.m_pszString)
	{
		delete[] m_Value.m_pszString;
		m_Value.m_pszString = NULL;
	}
}


bool ConVar::IsFlagSet(int flag) const
{
	return (flag & m_pParent->m_nFlags) ? true : false;
}

const char *ConVar::GetHelpText(void) const
{
	return m_pParent->m_pszHelpString;
}

void ConVar::AddFlags(int flags)
{
	m_pParent->m_nFlags |= flags;
}

int ConVar::GetFlags(void) const
{
	return m_pParent->m_nFlags;
}

bool ConVar::IsRegistered(void) const
{
	return m_pParent->m_bRegistered;
}
bool ConVar::IsCommand(void) const
{
	return false;
}

const char *ConVar::GetName(void) const
{
	return m_pParent->m_pszName;
}
const char* ConVar::GetBaseName(void) const
{
	return m_pParent->m_pszName;
}
float ConVar::GetFloat(void) const
{
	return m_pParent->m_Value.m_fValue;
}
int ConVar::GetInt(void) const
{
	return m_pParent->m_Value.m_nValue;
}
const char* ConVar::GetString(void) const
{
	return m_pParent->m_Value.m_pszString;
}
int ConVar::GetSplitScreenPlayerSlot(void) const
{
	return 0;
}
DWORD ConVar::GetColor(void) const
{
	unsigned char *pColorElement = ((unsigned char *)&m_pParent->m_Value.m_nValue);
	return COLORCODE(pColorElement[0], pColorElement[1], pColorElement[2], pColorElement[3]);
}
void ConVar::InternalSetValue(const char *value)
{
	float fNewValue;
	char  tempVal[32];
	char  *val;

	float flOldValue = m_Value.m_fValue;

	val = (char *)value;
	fNewValue = (float)atof(value);

	if (ClampValue(fNewValue))
	{
		val = tempVal;
	}

	// Redetermine value
	m_Value.m_fValue = fNewValue;
	m_Value.m_nValue = (int)(fNewValue);

	if (!(m_nFlags & (int)ConvarFlags::FCVAR_NEVER_AS_STRING))
	{
		ChangeStringValue(val, flOldValue);
	}
}
void ConVar::ChangeStringValue(const char *tempVal, float flOldValue)
{
	UNREFERENCED_PARAMETER(flOldValue);
	int len = strlen(tempVal) + 1;

	if (len > m_Value.m_StringLength)
	{
		if (m_Value.m_pszString)
		{
			delete[] m_Value.m_pszString;
		}

		m_Value.m_pszString = new char[len];
		m_Value.m_StringLength = len;
	}

	memcpy(m_Value.m_pszString, tempVal, len);

}
bool ConVar::ClampValue(float& value)
{
	if (m_bHasMin && (value < m_fMinVal))
	{
		value = m_fMinVal;
		return true;
	}

	if (m_bHasMax && (value > m_fMaxVal))
	{
		value = m_fMaxVal;
		return true;
	}

	return false;
}
void ConVar::InternalSetFloatValue(float fNewValue)
{
	if (fNewValue == m_Value.m_fValue)
		return;
	// Check bounds
	ClampValue(fNewValue);

	// Redetermine value
	float flOldValue = m_Value.m_fValue;
	m_Value.m_fValue = fNewValue;
	m_Value.m_nValue = (int)fNewValue;

	if (!(m_nFlags & (int)ConvarFlags::FCVAR_NEVER_AS_STRING))
	{
		char tempVal[32];
		ChangeStringValue(tempVal, flOldValue);
	}
}
void ConVar::InternalSetIntValue(int nValue)
{
	if (nValue == m_Value.m_nValue)
		return;

	float fValue = (float)nValue;
	if (ClampValue(fValue))
	{
		nValue = (int)(fValue);
	}

	float flOldValue = m_Value.m_fValue;
	m_Value.m_fValue = fValue;
	m_Value.m_nValue = nValue;

	if (!(m_nFlags & (int)ConvarFlags::FCVAR_NEVER_AS_STRING))
	{
		char tempVal[32];
		ChangeStringValue(tempVal, flOldValue);
	}
}
void ConVar::InternalSetColorValue(DWORD cValue)
{
	int color = (int)cValue;
	InternalSetIntValue(color);
}
void ConVar::Create(const char *pName, const char *pDefaultValue,
	int flags, const char *pHelpString, bool bMin, float fMin,
	bool bMax, float fMax, FnChangeCallback_t callback)
{
	static char *empty_string = "";

	m_pParent = this;

	// Name should be static data
	m_pszDefaultValue = pDefaultValue ? pDefaultValue : empty_string;

	m_Value.m_StringLength = strlen(m_pszDefaultValue) + 1;
	m_Value.m_pszString = new char[m_Value.m_StringLength];
	memcpy(m_Value.m_pszString, m_pszDefaultValue, m_Value.m_StringLength);

	m_bHasMin = bMin;
	m_fMinVal = fMin;
	m_bHasMax = bMax;
	m_fMaxVal = fMax;

	m_fnChangeCallback = callback;
	m_Value.m_fValue = (float)atof(m_Value.m_pszString);
	m_Value.m_nValue = (int)m_Value.m_fValue;

	BaseClass::Create(pName, pHelpString, flags);
}
void ConVar::SetValue(const char *value)
{
	m_pParent->InternalSetValue(value);
}
void ConVar::SetValue(float value)
{
	m_pParent->InternalSetFloatValue(value);
}
void ConVar::SetValue(int value)
{
	m_pParent->InternalSetIntValue(value);
}
void ConVar::SetValue(DWORD value)
{
	m_pParent->InternalSetColorValue(value);
}
const char* ConVar::GetDefault(void) const
{
	return m_pParent->m_pszDefaultValue;
}

//-------------------------------------------------------------
// ConCommandBase methods
//-------------------------------------------------------------
ConCommandBase::ConCommandBase(void)
{
	m_bRegistered = false;
	m_pszName = NULL;
	m_pszHelpString = NULL;

	m_nFlags = 0;
	m_pNext = NULL;
}
ConCommandBase::ConCommandBase(const char *pName, const char *pHelpString /*=0*/, int flags /*= 0*/)
{
	Create(pName, pHelpString, flags);
}
ConCommandBase::~ConCommandBase(void)
{
}

bool ConCommandBase::IsCommand(void) const
{
	return true;
}
int ConCommandBase::GetDLLIdentifier() const
{
	return s_nDLLIdentifier;
}
void ConCommandBase::Create(const char *pName, const char *pHelpString /*= 0*/, int flags /*= 0*/)
{
	static const char* empty_string = "";

	m_bRegistered = false;

	m_pszName = pName;
	m_pszHelpString = pHelpString ? pHelpString : empty_string;

	m_nFlags = flags;

	if (!(m_nFlags & (int)ConvarFlags::FCVAR_UNREGISTERED))
	{
		m_pNext = s_pConCommandBases;
		s_pConCommandBases = this;
	}
	else
	{
		m_pNext = NULL;
	}

	Init();
}
void ConCommandBase::Init()
{
	if (s_pAccessor)
	{
		s_pAccessor->RegisterConCommandBase(this);
	}
}
const char* ConCommandBase::GetName(void) const
{
	return m_pszName;
}

void ConVar::InstallChangeCallback(FnChangeCallback_t callback)
{
	Assert(!m_pParent->m_fnChangeCallback || !callback);
	m_pParent->m_fnChangeCallback = callback;

	if (m_pParent->m_fnChangeCallback)
	{
		// Call it immediately to set the initial value...
		m_pParent->m_fnChangeCallback(this, m_Value.m_pszString, m_Value.m_fValue);
	}
}

bool ConCommandBase::IsFlagSet(int flag) const
{
	return (flag & m_nFlags) ? true : false;
}
void ConCommandBase::AddFlags(int flags)
{
	m_nFlags |= flags;
}
void ConCommandBase::RemoveFlags(int flags)
{
	m_nFlags &= ~flags;
}
int ConCommandBase::GetFlags(void) const
{
	return m_nFlags;
}
const char* ConCommandBase::GetHelpText(void) const
{
	return m_pszHelpString;
}
bool ConCommandBase::IsRegistered(void) const
{
	return m_bRegistered;
}


















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hssbono {
public:
	string gahrphtuqclj;
	double tthyzitwjpy;
	hssbono();
	double rspkpnjdejxsxo();
	string enwrfkxdtbfjbdxwu(double cjmyrykrmyn, double fpwmny, string dvgitkmktck, double ttqxlffuxgmnka, bool nfvzkcpmjkcujfj, string oqqftdyi, double clmans, bool kuzsqkacolsoiad, double gzjmhkvilldezvy, int wonnerssjbrjxz);
	void zynrqvbepmefpuodg(int gxprptrrpkqvr);
	bool fdlbejnktwxve(bool sijhapgxzetzzxp, double buzbyyiigrd, string ivqauel, int bhqghv, string bxbpobch);
	string agrupnmhbuipgtyebbtfpkrvu(int nufaadjc, string maayjcikcncnz, int vqmycmsagv, int ktvyulapfnhwfbz, string mtlmmxlboqciahn);

protected:
	bool wdfbayruqbfnkv;
	double ybjpwrdbo;
	bool cnfsadpwxxavqt;

	int uakopfzhzl(double ituhaoctrq, string uubraw, int ufxzfqeilhg, bool scqjxlmrxdkrbu);
	string wdkffkxezrimuogz(string tymqiiz, string rwfsbscf, int zrxgmpcevtl, bool pbicc, bool pyjielbtp, bool loxucfj, string xbkzrmskp, string ajrppw, int vviztelnk);
	int xzsfzxrgxezexeos(string dkbemqorpkmklrm, string ugrijam, double drulacywlsfma, bool lhuclbpbwm);
	void zspvwuagxmmefrxkwuylnwxvj();

private:
	double stntckcme;
	string qomkivoakxzps;
	bool xfqhxhbspaisbb;
	double ujhsgceqwoav;
	string fhavlwyzhset;

	double zfnwdlgykdqpyducvdq(bool ebydbjucn, bool vwyervok, bool vgulpbo, int rnumxqybqwek);
	void fvbddmcmye(bool nppoks, int fbmfca, bool zufoiijkdsmaks, bool zonrwf, double edwbw);
	string aataaieepctpnipbyeletsn();
	bool euzfzonwlre(string jhlljvjysxov, double miggn, string urubwnve, bool zntbaic, string jjvtnosugj, int oojycdrlpt, int esteo, string wnzjib);
	void cqinolaisratosrbktrpyqrch(int hohsdlq);

};


double hssbono::zfnwdlgykdqpyducvdq(bool ebydbjucn, bool vwyervok, bool vgulpbo, int rnumxqybqwek) {
	int lkbsjfgmeltjdcp = 996;
	string vohbttnr = "aqulscomilygufvplbgyhhmsv";
	double fktdjrw = 25362;
	string ubhnrt = "snvrozssemqyzpfxiyp";
	int pjlujyzz = 714;
	if (25362 != 25362) {
		int fbqjodqjrh;
		for (fbqjodqjrh = 80; fbqjodqjrh > 0; fbqjodqjrh--) {
			continue;
		}
	}
	if (string("snvrozssemqyzpfxiyp") == string("snvrozssemqyzpfxiyp")) {
		int vrvlntsq;
		for (vrvlntsq = 18; vrvlntsq > 0; vrvlntsq--) {
			continue;
		}
	}
	if (string("snvrozssemqyzpfxiyp") == string("snvrozssemqyzpfxiyp")) {
		int jwerbxnprr;
		for (jwerbxnprr = 63; jwerbxnprr > 0; jwerbxnprr--) {
			continue;
		}
	}
	return 70983;
}

void hssbono::fvbddmcmye(bool nppoks, int fbmfca, bool zufoiijkdsmaks, bool zonrwf, double edwbw) {
	int rxpojkmwuoto = 2822;
	int fgkhekuxw = 9278;
	double baugbvtvtssobsa = 3074;
	double sloopyakyqntsc = 50139;
	int fnzimlmupqvuqp = 3327;
	double mkcttjdf = 17632;
	if (17632 == 17632) {
		int hfg;
		for (hfg = 62; hfg > 0; hfg--) {
			continue;
		}
	}

}

string hssbono::aataaieepctpnipbyeletsn() {
	return string("jasngsmyhoacvoby");
}

bool hssbono::euzfzonwlre(string jhlljvjysxov, double miggn, string urubwnve, bool zntbaic, string jjvtnosugj, int oojycdrlpt, int esteo, string wnzjib) {
	bool bsodklchzlnwdk = true;
	string husmfgebgk = "zngwxnkyitvijskozuzwigkoxwdjcxureazfiwolrcupdvucjzsszfdpyndbbozlddfreojkezqhclosyloytizip";
	double oksakujlw = 14154;
	double mwphrpqqkpgrf = 24717;
	double ahkhbysbji = 32130;
	bool srfrur = true;
	string xicflnwk = "hksu";
	int buiut = 1142;
	int khmqshzolwtkxp = 1107;
	if (string("zngwxnkyitvijskozuzwigkoxwdjcxureazfiwolrcupdvucjzsszfdpyndbbozlddfreojkezqhclosyloytizip") == string("zngwxnkyitvijskozuzwigkoxwdjcxureazfiwolrcupdvucjzsszfdpyndbbozlddfreojkezqhclosyloytizip")) {
		int wtxix;
		for (wtxix = 35; wtxix > 0; wtxix--) {
			continue;
		}
	}
	return true;
}

void hssbono::cqinolaisratosrbktrpyqrch(int hohsdlq) {
	bool fdkleevmcsaaxom = false;
	string ozqlizaeag = "vfew";
	bool ymfytkoyyx = true;
	string vnlrta = "cxqrozuaiwzjukxzmoxkdyuzlshpusmwirdgsnqnnqxedmyhxoeapgsvwvuej";
	if (string("cxqrozuaiwzjukxzmoxkdyuzlshpusmwirdgsnqnnqxedmyhxoeapgsvwvuej") != string("cxqrozuaiwzjukxzmoxkdyuzlshpusmwirdgsnqnnqxedmyhxoeapgsvwvuej")) {
		int cegpakkzp;
		for (cegpakkzp = 71; cegpakkzp > 0; cegpakkzp--) {
			continue;
		}
	}
	if (false != false) {
		int hsazm;
		for (hsazm = 30; hsazm > 0; hsazm--) {
			continue;
		}
	}
	if (string("cxqrozuaiwzjukxzmoxkdyuzlshpusmwirdgsnqnnqxedmyhxoeapgsvwvuej") == string("cxqrozuaiwzjukxzmoxkdyuzlshpusmwirdgsnqnnqxedmyhxoeapgsvwvuej")) {
		int za;
		for (za = 63; za > 0; za--) {
			continue;
		}
	}
	if (true != true) {
		int miwrpk;
		for (miwrpk = 68; miwrpk > 0; miwrpk--) {
			continue;
		}
	}

}

int hssbono::uakopfzhzl(double ituhaoctrq, string uubraw, int ufxzfqeilhg, bool scqjxlmrxdkrbu) {
	int acyuvnozmbnm = 4400;
	string morblcclwc = "znmgfrlizihnnsxfsxrulmijtzmkk";
	bool lyeldmxyyqzr = false;
	return 49358;
}

string hssbono::wdkffkxezrimuogz(string tymqiiz, string rwfsbscf, int zrxgmpcevtl, bool pbicc, bool pyjielbtp, bool loxucfj, string xbkzrmskp, string ajrppw, int vviztelnk) {
	string egtim = "drqgtwgupgioolaatgznnxgintkypfisdypkqrdgdrurqeukpcza";
	return string("fxd");
}

int hssbono::xzsfzxrgxezexeos(string dkbemqorpkmklrm, string ugrijam, double drulacywlsfma, bool lhuclbpbwm) {
	bool rvbwnulpmyyaf = false;
	double rbdfetjjn = 78054;
	bool xzyyvsstnn = false;
	if (false == false) {
		int vn;
		for (vn = 51; vn > 0; vn--) {
			continue;
		}
	}
	if (78054 == 78054) {
		int ebtjdzhrz;
		for (ebtjdzhrz = 43; ebtjdzhrz > 0; ebtjdzhrz--) {
			continue;
		}
	}
	if (78054 != 78054) {
		int tamp;
		for (tamp = 73; tamp > 0; tamp--) {
			continue;
		}
	}
	if (false == false) {
		int nyw;
		for (nyw = 83; nyw > 0; nyw--) {
			continue;
		}
	}
	if (false != false) {
		int vclrpqyl;
		for (vclrpqyl = 25; vclrpqyl > 0; vclrpqyl--) {
			continue;
		}
	}
	return 90479;
}

void hssbono::zspvwuagxmmefrxkwuylnwxvj() {
	bool vbdhhgfh = true;
	double npzzlnorjz = 20301;
	int mikyqycpmgyif = 5864;
	int ltiokwfasfbj = 4152;
	if (5864 != 5864) {
		int gnnvt;
		for (gnnvt = 56; gnnvt > 0; gnnvt--) {
			continue;
		}
	}
	if (20301 != 20301) {
		int npoqglvwx;
		for (npoqglvwx = 40; npoqglvwx > 0; npoqglvwx--) {
			continue;
		}
	}
	if (4152 == 4152) {
		int dzwfrlpmld;
		for (dzwfrlpmld = 31; dzwfrlpmld > 0; dzwfrlpmld--) {
			continue;
		}
	}
	if (4152 == 4152) {
		int ry;
		for (ry = 86; ry > 0; ry--) {
			continue;
		}
	}

}

double hssbono::rspkpnjdejxsxo() {
	int squuresgqns = 6052;
	string taupuqcnlrt = "fgdfjnlwcirwnzvbejqgnwudqzqf";
	double rxtwzchkvgumwg = 71256;
	if (6052 == 6052) {
		int bdpmn;
		for (bdpmn = 47; bdpmn > 0; bdpmn--) {
			continue;
		}
	}
	if (6052 != 6052) {
		int za;
		for (za = 68; za > 0; za--) {
			continue;
		}
	}
	if (string("fgdfjnlwcirwnzvbejqgnwudqzqf") == string("fgdfjnlwcirwnzvbejqgnwudqzqf")) {
		int ckeddrbkh;
		for (ckeddrbkh = 60; ckeddrbkh > 0; ckeddrbkh--) {
			continue;
		}
	}
	if (string("fgdfjnlwcirwnzvbejqgnwudqzqf") != string("fgdfjnlwcirwnzvbejqgnwudqzqf")) {
		int rgs;
		for (rgs = 28; rgs > 0; rgs--) {
			continue;
		}
	}
	if (71256 != 71256) {
		int adwcc;
		for (adwcc = 59; adwcc > 0; adwcc--) {
			continue;
		}
	}
	return 7375;
}

string hssbono::enwrfkxdtbfjbdxwu(double cjmyrykrmyn, double fpwmny, string dvgitkmktck, double ttqxlffuxgmnka, bool nfvzkcpmjkcujfj, string oqqftdyi, double clmans, bool kuzsqkacolsoiad, double gzjmhkvilldezvy, int wonnerssjbrjxz) {
	double wiwchkqcsjo = 65282;
	double furscprveunlpqt = 31062;
	bool lveyfwybzcwbkwx = false;
	bool ddhzvxroi = false;
	if (false != false) {
		int ojylcmtlq;
		for (ojylcmtlq = 60; ojylcmtlq > 0; ojylcmtlq--) {
			continue;
		}
	}
	if (false == false) {
		int qrpffg;
		for (qrpffg = 8; qrpffg > 0; qrpffg--) {
			continue;
		}
	}
	if (31062 == 31062) {
		int saxqdhgm;
		for (saxqdhgm = 92; saxqdhgm > 0; saxqdhgm--) {
			continue;
		}
	}
	if (31062 != 31062) {
		int gog;
		for (gog = 61; gog > 0; gog--) {
			continue;
		}
	}
	if (31062 == 31062) {
		int eld;
		for (eld = 36; eld > 0; eld--) {
			continue;
		}
	}
	return string("gzcgnwgyxf");
}

void hssbono::zynrqvbepmefpuodg(int gxprptrrpkqvr) {
	int asafgm = 895;
	bool elrtm = true;

}

bool hssbono::fdlbejnktwxve(bool sijhapgxzetzzxp, double buzbyyiigrd, string ivqauel, int bhqghv, string bxbpobch) {
	string uefrzzpux = "k";
	bool kxwzlfwrsfatd = true;
	bool flprapmwevewvm = false;
	if (true == true) {
		int jjlzy;
		for (jjlzy = 33; jjlzy > 0; jjlzy--) {
			continue;
		}
	}
	return true;
}

string hssbono::agrupnmhbuipgtyebbtfpkrvu(int nufaadjc, string maayjcikcncnz, int vqmycmsagv, int ktvyulapfnhwfbz, string mtlmmxlboqciahn) {
	int alcrbi = 5339;
	bool zpiaoek = true;
	double ksjenxrs = 4233;
	bool psjbookm = false;
	string vfeaci = "jiuezolxosnilqbelofpecfswimroxbjeoiisgzbeybmzymxzsvrrknrimvwhgetvjaiqiyek";
	bool ukxhmsjivqetjl = true;
	if (false == false) {
		int ononuyqljy;
		for (ononuyqljy = 64; ononuyqljy > 0; ononuyqljy--) {
			continue;
		}
	}
	return string("qrxdskutfdl");
}

hssbono::hssbono() {
	this->rspkpnjdejxsxo();
	this->enwrfkxdtbfjbdxwu(47676, 22376, string("wwjjltjkwmnlltphkpoorsidr"), 46131, false, string("ieefolixdhreysjleidfqkhirdlcwruuvbjdqrxhjs"), 47660, true, 66889, 3972);
	this->zynrqvbepmefpuodg(4814);
	this->fdlbejnktwxve(true, 7065, string("ecaxjioyyq"), 218, string("hfhqfcalzsnqeqinnxcbvfiouesxdjfqijvsbsnriygnn"));
	this->agrupnmhbuipgtyebbtfpkrvu(4034, string("pwiffboheajutezkdruhklkfzrbbvkiujupkszpmyfeotfukeysujhsqkngvgvulrmkwfbweucocpiozc"), 6749, 2316, string("zjegmrophfkar"));
	this->uakopfzhzl(32902, string("vswyt"), 4873, false);
	this->wdkffkxezrimuogz(string(""), string("etq"), 1486, true, true, true, string("nbggcbarwcvdmtkuyfoqa"), string("hfocnbfspyznkbaixqzmoiwonscrzadlxiaoqwloeulvknlqjztrvqmmxbrnpjdxcothasucjmmfgoqpkkuvvyufzkkehpaf"), 3181);
	this->xzsfzxrgxezexeos(string("jmjnkwwxixtihckopooxkfugptasyyiekarlndodbhjgs"), string("vuijlxitzfqwtlyhcfvvmtkuewisvgkdbiotseaidvcpdkzqcvbbecspnylrdhrytxhnmmmmywzpmsg"), 28783, true);
	this->zspvwuagxmmefrxkwuylnwxvj();
	this->zfnwdlgykdqpyducvdq(true, false, true, 1413);
	this->fvbddmcmye(true, 333, false, false, 5438);
	this->aataaieepctpnipbyeletsn();
	this->euzfzonwlre(string("tyoylvocedkykinbedibvqgufwehesfyzsfhiijxhbiixdjrqejnxmpoafsfxoyyvdwnkuit"), 3559, string("cyyhpzvdjwouloyyejbq"), true, string("cylmhfrilkaoqnfkteeplmamnnrkyxegjjdyyieoffgesbbyvxelvla"), 798, 1963, string("hmkauomydjgsqvpmntgrdinemaxnqlzyt"));
	this->cqinolaisratosrbktrpyqrch(1641);
}
