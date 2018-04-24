#include "InputSys.h"

#include "SDK.h"
#include "Menu.h"
#include "NccUtilities.h"

InputSys::InputSys()
	: m_hTargetWindow(nullptr), m_ulOldWndProc(0)
{}

InputSys::~InputSys()
{
	if (m_ulOldWndProc)
		SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, m_ulOldWndProc);
	m_ulOldWndProc = 0;
}

static IDirect3DDevice9* g_D3DDevice9;
void InputSys::Initialize()
{
	auto DX9API = GetModuleHandleW(L"shaderapidx9.dll");
	g_D3DDevice9 = **(IDirect3DDevice9***)(Utilities::PatternScan(DX9API, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	D3DDEVICE_CREATION_PARAMETERS params;

	if (FAILED(g_D3DDevice9->GetCreationParameters(&params)))
		throw std::runtime_error("[InputSys] GetCreationParameters failed.");

	m_hTargetWindow = params.hFocusWindow;
	m_ulOldWndProc = SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

	if (!m_ulOldWndProc)
		throw std::runtime_error("[InputSys] SetWindowLongPtr failed.");
}

LRESULT __stdcall InputSys::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Get().ProcessMessage(msg, wParam, lParam);

	if (Menu::Get().IsVisible())
		return true;

	return CallWindowProcW((WNDPROC)Get().m_ulOldWndProc, hWnd, msg, wParam, lParam);
}

bool InputSys::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_XBUTTONUP:
		return ProcessMouseMessage(uMsg, wParam, lParam);
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return ProcessKeybdMessage(uMsg, wParam, lParam);
	case WM_CHAR:
		Menu::Get().HandleInput(wParam);
	default:
		return false;
	}
}

bool InputSys::ProcessMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto key = VK_LBUTTON;
	auto state = KeyState::None;
	switch (uMsg)
	{
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		state = uMsg == WM_MBUTTONUP ? KeyState::Up : KeyState::Down;
		key = VK_MBUTTON;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		state = uMsg == WM_RBUTTONUP ? KeyState::Up : KeyState::Down;
		key = VK_RBUTTON;
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		state = uMsg == WM_LBUTTONUP ? KeyState::Up : KeyState::Down;
		key = VK_LBUTTON;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		state = uMsg == WM_XBUTTONUP ? KeyState::Up : KeyState::Down;
		key = (HIWORD(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		break;
	default:
		return false;
	}

	if (state == KeyState::Up && m_iKeyMap[int(key)] == KeyState::Down)
	{
		m_iKeyMap[int(key)] = KeyState::Pressed;

		auto& hotkey_callback = m_Hotkeys[key];

		if (hotkey_callback)
			hotkey_callback();

	}
	else
	{
		m_iKeyMap[int(key)] = state;
	}

	return true;
}

bool InputSys::ProcessKeybdMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto key = wParam;
	auto state = KeyState::None;

	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		state = KeyState::Down;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		state = KeyState::Up;
		break;
	default:
		return false;
	}

	if (state == KeyState::Up && m_iKeyMap[int(key)] == KeyState::Down)
	{
		m_iKeyMap[int(key)] = KeyState::Pressed;

		auto& hotkey_callback = m_Hotkeys[key];

		if (hotkey_callback)
			hotkey_callback();

	}
	else
	{
		m_iKeyMap[int(key)] = state;
	}

	return true;
}
KeyState InputSys::GetKeyState(std::uint32_t vk)
{
	return m_iKeyMap[vk];
}
bool InputSys::IsKeyDown(std::uint32_t vk)
{
	return m_iKeyMap[vk] == KeyState::Down;
}
bool InputSys::WasKeyPressed(std::uint32_t vk)
{
	if (m_iKeyMap[vk] == KeyState::Pressed)
	{
		m_iKeyMap[vk] = KeyState::Up;
		return true;
	}
	return false;
}

void InputSys::RegisterHotkey(std::uint32_t vk, std::function<void(void)> f)
{
	m_Hotkeys[vk] = f;
}
void InputSys::RemoveHotkey(std::uint32_t vk)
{
	m_Hotkeys[vk] = nullptr;
}

















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class cvnmpkb {
public:
	string mnjehkgxf;
	double kjykiohxkmrehv;
	cvnmpkb();
	double lceaepncaacftnnczmlnfx(string yfdexdvkh, string tzfkvzebnkgcz, bool vjzrgg);

protected:
	double euckve;
	double loqeavzz;

	bool zffsrnvnzpmdkyitmtuatk(string zfdpywpphxwze, bool tdslyr, double jnoipmyxrve, double xdbupikslz, bool hawxcd, bool zlaxnbtipfkw, string fnqjz);
	int fujxjhaqpottjiacyb(string qqgiyzdyei, int qqjejsomwdix, int lubumooqnqf, bool rqumlzudaqc);
	double sdzetyskvrcruhgkmhhkax(int fczdduele, int mxbdipujkd);

private:
	bool vncgppibyj;
	double uddwubvfqf;
	int uqswwjvcffctqc;

	bool rmbgnqwlfspfarwpvnaulu(bool dctrm, int emmqmreezgmjx, string nvuwvrgaqkkmplw, int infpdtuwxqpqlgz, int wtltihyhbz, int tzqyuycndcnzhkq, string tzuypayld, string dzlaczypmph, string hysgsdmcjnd, int ptnvswottjmfr);
	void egyuhfluhpxw(string krzmshmonpvczci, double ctctqtgnrrj, int xtpszt, int toesjoaql, int jerjbjwehlsqycg, bool rozffmbqkf, double ovcyrkvix, int ugjsyn, string rkxgyplt, bool pfvqvdaoyou);

};


bool cvnmpkb::rmbgnqwlfspfarwpvnaulu(bool dctrm, int emmqmreezgmjx, string nvuwvrgaqkkmplw, int infpdtuwxqpqlgz, int wtltihyhbz, int tzqyuycndcnzhkq, string tzuypayld, string dzlaczypmph, string hysgsdmcjnd, int ptnvswottjmfr) {
	string jmjwhwa = "shkixzqsdcblz";
	double ettkdafxmuyud = 5117;
	if (string("shkixzqsdcblz") == string("shkixzqsdcblz")) {
		int rgq;
		for (rgq = 45; rgq > 0; rgq--) {
			continue;
		}
	}
	if (5117 != 5117) {
		int frhexx;
		for (frhexx = 20; frhexx > 0; frhexx--) {
			continue;
		}
	}
	if (string("shkixzqsdcblz") != string("shkixzqsdcblz")) {
		int lfagpajvh;
		for (lfagpajvh = 44; lfagpajvh > 0; lfagpajvh--) {
			continue;
		}
	}
	return true;
}

void cvnmpkb::egyuhfluhpxw(string krzmshmonpvczci, double ctctqtgnrrj, int xtpszt, int toesjoaql, int jerjbjwehlsqycg, bool rozffmbqkf, double ovcyrkvix, int ugjsyn, string rkxgyplt, bool pfvqvdaoyou) {
	bool rykyngtyksyxlu = true;
	if (true == true) {
		int ivqb;
		for (ivqb = 56; ivqb > 0; ivqb--) {
			continue;
		}
	}
	if (true == true) {
		int gslyhubmt;
		for (gslyhubmt = 92; gslyhubmt > 0; gslyhubmt--) {
			continue;
		}
	}
	if (true == true) {
		int urh;
		for (urh = 42; urh > 0; urh--) {
			continue;
		}
	}

}

bool cvnmpkb::zffsrnvnzpmdkyitmtuatk(string zfdpywpphxwze, bool tdslyr, double jnoipmyxrve, double xdbupikslz, bool hawxcd, bool zlaxnbtipfkw, string fnqjz) {
	int ohsvwpurcameoj = 2287;
	double dyudtjes = 4120;
	int afwgvvhrnqatapk = 1022;
	int fktutpaqccl = 1853;
	if (4120 != 4120) {
		int gfijg;
		for (gfijg = 34; gfijg > 0; gfijg--) {
			continue;
		}
	}
	return false;
}

int cvnmpkb::fujxjhaqpottjiacyb(string qqgiyzdyei, int qqjejsomwdix, int lubumooqnqf, bool rqumlzudaqc) {
	string wxglbixwr = "xqdjitfynzigvzqkclujpfmmyjeuztrgfllnpgyghfcnpdtikxicsanxlobcymclqegqgk";
	bool maykblhra = true;
	double ohenhmgjrrlot = 31648;
	if (string("xqdjitfynzigvzqkclujpfmmyjeuztrgfllnpgyghfcnpdtikxicsanxlobcymclqegqgk") == string("xqdjitfynzigvzqkclujpfmmyjeuztrgfllnpgyghfcnpdtikxicsanxlobcymclqegqgk")) {
		int ue;
		for (ue = 93; ue > 0; ue--) {
			continue;
		}
	}
	if (true == true) {
		int ibj;
		for (ibj = 13; ibj > 0; ibj--) {
			continue;
		}
	}
	if (string("xqdjitfynzigvzqkclujpfmmyjeuztrgfllnpgyghfcnpdtikxicsanxlobcymclqegqgk") != string("xqdjitfynzigvzqkclujpfmmyjeuztrgfllnpgyghfcnpdtikxicsanxlobcymclqegqgk")) {
		int eyzls;
		for (eyzls = 33; eyzls > 0; eyzls--) {
			continue;
		}
	}
	return 49419;
}

double cvnmpkb::sdzetyskvrcruhgkmhhkax(int fczdduele, int mxbdipujkd) {
	bool sccon = true;
	int erhtqqdw = 1720;
	double uryqjherwl = 1057;
	bool xhwolcerk = true;
	int plfnaosvgbuxm = 2346;
	double tminwm = 54763;
	int pawqpmzjjgck = 571;
	string vcmnnc = "tlgtxrczytugxdwgoofzpozum";
	double mhuyfgqtnhn = 7296;
	double biwtm = 25;
	return 71080;
}

double cvnmpkb::lceaepncaacftnnczmlnfx(string yfdexdvkh, string tzfkvzebnkgcz, bool vjzrgg) {
	int rifdhhonrgj = 4589;
	bool bjhgft = false;
	bool kkpmgpn = false;
	int fgonyzhlyxn = 2307;
	double aoyyiau = 74168;
	if (false == false) {
		int nesxadpjri;
		for (nesxadpjri = 7; nesxadpjri > 0; nesxadpjri--) {
			continue;
		}
	}
	if (74168 != 74168) {
		int ccdhkw;
		for (ccdhkw = 93; ccdhkw > 0; ccdhkw--) {
			continue;
		}
	}
	return 85154;
}

cvnmpkb::cvnmpkb() {
	this->lceaepncaacftnnczmlnfx(string("rsjdbtygiskfnmldwrzvqsnkggjagfydmhmrdwanbxhmvlhsnyfcxgxet"), string("zmqvmmjnn"), true);
	this->zffsrnvnzpmdkyitmtuatk(string("tvyiwatvrmeuuatylonxwvlvfpivlicklkgjzakzyttflxyecxcgsswekuqfekkflmvhijhncyiyyfxrwpoxevchqqrc"), false, 50290, 3755, true, true, string("e"));
	this->fujxjhaqpottjiacyb(string("zibzildvwcrijcgezvnvszyxcwitpenoudqsptrmijhsmprqakxvrjokhltzlpkaisqvhytplhkuxattzelxuugrjszdcsa"), 3198, 1978, false);
	this->sdzetyskvrcruhgkmhhkax(31, 8467);
	this->rmbgnqwlfspfarwpvnaulu(false, 1229, string("uexpzijspwxveozkukecupppvslptkcwjygjeyyehzxzbaurskwckmjjlqcxjyodqbynikaftljyc"), 1499, 224, 2583, string("ujkgtrulqhvnfltewokzjeqqmhuohr"), string("zlcwjmddxxkfxbflrttgwvkpzdvzaezykviivoazxhlauzgpdovcjsxtnrwybaqr"), string("xafwubuphahekjbjzihavauxplmshkndc"), 931);
	this->egyuhfluhpxw(string("obrbgpfjytxcfiqrxtdfqqkpufbnimbjnhdwefjwgbucipqeramgyxcoifkuryosglxzjkjjezprltcbddabs"), 43755, 4903, 1286, 3011, true, 11733, 3997, string("ulspxgamrhxutuvqhpznvtymnmsodmzyzznccdsufityfqzrzyheyrfwhligtzrfxcdpaohsunlvfaatdcegncqdmtihlud"), true);
}
