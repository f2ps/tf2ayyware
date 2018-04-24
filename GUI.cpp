#include "GUI.h"
#include "NccMath.h"
#include "NccDraw.h"
#include "NccUtilities.h"

#include <array>

CObject::CObject(int x, int y, int width, int height, int layer)
	: m_x(x), m_y(y), m_width(width), m_height(height), m_layer(layer)
{}

//--------------------------------------------------------------------------------

void CObjectContainer::AddControl(CObject * obj)
{
	Objects.push_back(obj);
}

//--------------------------------------------------------------------------------

void CForm::Paint()
{
	for (auto &w : Windows)
	{
		w.Paint();
	}
}

void CForm::Click()
{
	for (auto &w : Windows)
	{
		w.Click();
	}
}

void CForm::HandleInput(WPARAM vk)
{
	for (auto &w : Windows)
	{
		w.HandleInput(vk);
	}
}

//--------------------------------------------------------------------------------

CWindow::CWindow(int x, int y, int width, int height, bool* open)
	: CObject(x, y, width, height), m_open(open)
{}

void CWindow::Paint(int t_x, int t_y, float* controlheight)
{
	if (m_open != nullptr && !*m_open) return;

	if (m_dragging && !InputSys::Get().IsKeyDown(VK_LBUTTON))
		m_dragging = false;

	int cur_x, cur_y;
	gInts.Surface->GetCursorPosition(cur_x, cur_y);

	if (m_dragging && InputSys::Get().IsKeyDown(VK_LBUTTON) && InputSys::Get().GetKeyState(VK_LBUTTON) != KeyState::Pressed)
	{
		m_x = cur_x - m_dragoffsetx;
		m_y = cur_y - m_dragoffsety;
	}

	Vector2 tl(t_x + m_x, t_y + m_y);
	Vector2 br(tl.x + m_width, tl.y + m_height);

	if (InputSys::Get().GetKeyState(VK_LBUTTON) == KeyState::Pressed)
		if (Math::InBox(tl.x, tl.y - 16, br.x, tl.y, cur_x, cur_y))
		{
			m_dragging = true;
			m_dragoffsetx = cur_x - m_x;
			m_dragoffsety = cur_y - m_y;
		}

	Draw::FilledRectangle(tl.x, tl.y - 16, br.x, br.y, Color(100, 0, 0, 135));
	Draw::Rectangle(tl.x, tl.y - 16, br.x, br.y, Color(50, 5, 5));
	Draw::Rectangle(tl.x + 1, tl.y - 15, br.x - 1, br.y - 1, Color(200, 10, 10));
	tl += 6;
	br -= 6;
	Draw::FilledGradientRectangle(tl.x, tl.y, br.x, br.y, Color(238, 238, 238), Color(210, 210, 210));
	Draw::Rectangle(tl, br, Color(50, 5, 5));
	Draw::Rectangle(tl.x - 1, tl.y - 1, br.x + 1, br.y + 1, Color(200, 10, 10));

	Draw::Text(tl.x + 3, tl.y - 17, L"ayyware", Font::Get().MenuText, Color::Orange());

	m_controlheight = 0;
	for (auto o : Objects)
	{
		o->Paint(tl.x + 5, tl.y + 5, &m_controlheight);
	}
}

void CWindow::Click()
{
	if (m_open != nullptr && !*m_open) return;

	for (auto o : Objects)
	{
		o->Click();
	}
}

void CWindow::HandleInput(WPARAM vk)
{
	if (m_open != nullptr && !*m_open) return;

	for (auto o : Objects)
	{
		o->HandleInput(vk);
	}
}

//--------------------------------------------------------------------------------

CChild::CChild(int x, int y, int width, std::wstring title)
	: CObject(x, y, width), m_title(title)
{}

void CChild::Paint(int t_x, int t_y, float* controlheight)
{
	Vector2 tl(t_x + m_x, t_y + m_y + 3);
	Vector2 br(t_x + m_x + m_width, t_y + m_y + m_controlheight + 15);

	auto textSize = Draw::GetTextSize(m_title.data(), Font::Get().MenuText);

	// background
	Draw::FilledGradientRectangle(tl.x, tl.y, br.x, br.y, Color(210, 210, 210), Color(238, 238, 238));

	const Color color(180, 180, 180);

	// top
	Draw::Line(tl.x, tl.y, tl.x + 8, tl.y, color);
	Draw::Line(tl.x + 18 + textSize.x, tl.y, br.x, tl.y, color);
	// right
	Draw::Line(br.x, tl.y, br.x, br.y, color);
	//bottom
	Draw::Line(tl.x, br.y, br.x, br.y, color);
	// left
	Draw::Line(tl.x, tl.y, tl.x, br.y, color);

	Draw::Text(tl.x + 14, tl.y, m_title.data(), Font::Get().MenuText, Color::Black(), false, true);

	m_controlheight = 0;
	for (auto o : Objects)
	{
		o->Paint(tl.x + 8, tl.y + 8, &m_controlheight);
	}
}

void CChild::Click()
{
	for (auto o : Objects)
	{
		o->Click();
	}
}

void CChild::HandleInput(WPARAM vk)
{
	for (auto o : Objects)
	{
		o->HandleInput(vk);
	}
}

//--------------------------------------------------------------------------------

CSpacing::CSpacing(int height)
	: m_height(height)
{}

void CSpacing::Paint(int t_x, int t_y, float* controlheight)
{
	if (controlheight == nullptr) return;
	*controlheight += m_height;
}


//--------------------------------------------------------------------------------

CLabel::CLabel(std::wstring text, HFont font, Color color, bool centered)
	: m_text(text), m_font(font), m_color(color), m_centered(centered)
{}

void CLabel::Paint(int t_x, int t_y, float* controlheight)
{
	if (controlheight == nullptr) return;
	t_y += *controlheight;
	Draw::Text(t_x + m_x, t_y + m_y, m_text.data(), m_font, m_color, m_centered);
	*controlheight += Draw::GetTextSize(m_text.data(), m_font).y;
}

//--------------------------------------------------------------------------------

CCheckBox::CCheckBox(std::wstring label, bool* value)
	: m_label(label), m_val(value)
{}

void CCheckBox::Paint(int t_x, int t_y, float* controlheight)
{
	if (controlheight == nullptr) return;

	const auto size = 12;

	t_y += *controlheight;

	Vector2 tl(t_x + m_x, t_y + m_y);
	Vector2 br(t_x + m_x + size, t_y + m_y + size);

	int cur_x, cur_y;
	gInts.Surface->GetCursorPosition(cur_x, cur_y);

	m_hover = Math::InBox(tl.x, tl.y, br.x, br.y, cur_x, cur_y);

	Color border_top, border_bottom, top, bottom;

	if (m_hover)
	{
		border_top = Color(160);
		border_bottom = Color(109);
		top = Color(234);
		bottom = Color(156);
	}
	else
	{
		border_top = Color(187);
		border_bottom = Color(84);
		top = Color::White();
		bottom = Color(216);
	}

	Draw::FilledGradientRectangle(tl.x, tl.y, br.x, br.y, border_top, border_bottom);
	Draw::FilledGradientRectangle(tl.x + 1, tl.y + 1, br.x - 1, br.y - 1, top, bottom);
	if (m_val != nullptr && *m_val)
		Draw::Text(tl.x + (size / 2) + 1, tl.y + (size / 2), L"✔", Font::Get().MenuText, Color::Red(), true);
	Draw::Text(br.x + 4, tl.y - 1, m_label.data(), Font::Get().MenuText, Color::Black());
	*controlheight += size + MENU_PADDING;
}

void CCheckBox::Click()
{
	if (m_val != nullptr && m_hover)
		*m_val = !*m_val;
}

//--------------------------------------------------------------------------------

template<typename T>
inline CSlider<T>::CSlider(std::wstring label, T min, T max, T * value)
	: m_label(label), m_min(min), m_max(max), m_val(value)
{}

template<typename T>
inline void CSlider<T>::Paint(int t_x, int t_y, float* controlheight)
{
	if (controlheight == nullptr) return;
	t_y += *controlheight;

	const auto width = 80;
	const auto height = 14;

	Vector2 tl(t_x + m_x, t_y + m_y);
	Vector2 br(t_x + m_x + width, t_y + m_y + height);

	int cur_x, cur_y;
	gInts.Surface->GetCursorPosition(cur_x, cur_y);

	m_hover = Math::InBox(tl.x - 4, tl.y, br.x + 4, br.y, cur_x, cur_y);

	int valueX = tl.x + ((*m_val - m_min) * width / (m_max - m_min));

	if (m_val != nullptr && m_hover && InputSys::Get().IsKeyDown(VK_LBUTTON))
		*m_val = (cur_x - tl.x) * (m_max - m_min) / width;

	if (*m_val < m_min) *m_val = m_min;
	if (*m_val > m_max) *m_val = m_max;

	Draw::FilledRectangle(tl.x, tl.y + 3, br.x, br.y - 3, Color(237));
	Draw::FilledRectangle(tl.x, tl.y + 3, valueX, br.y - 3, Color(180, 0, 0));
	Draw::Rectangle(tl.x, tl.y + 3, br.x, br.y - 3, Color(141));

	Draw::FilledGradientRectangle(valueX - 4, tl.y + 1, valueX + 4, br.y - 1, Color(208), Color(125));
	Draw::FilledGradientRectangle(valueX - 3, tl.y + 2, valueX + 3, br.y - 2, Color::White(), Color(187));

	wchar_t buffer[30];
	swprintf(buffer, 30, L"%s (%s)", m_label.data(), Utilities::to_wstring(*m_val, 2).data());
	Draw::Text(br.x + 9, tl.y, buffer, Font::Get().MenuText, Color::Black());
	*controlheight += height + MENU_PADDING;
}

template class CSlider<int>;
template class CSlider<float>;
template class CSlider<double>;

//--------------------------------------------------------------------------------

CButton::CButton(int width, int height, std::wstring label, std::function<void()> cb)
	: CObject(0, 0, width, height), m_label(label), m_cb(cb)
{}

void CButton::Paint(int t_x, int t_y, float* controlheight)
{
	if (controlheight == nullptr) return;
	t_y += *controlheight;

	Vector2 tl(t_x + m_x, t_y + m_y);
	Vector2 br(t_x + m_x + m_width, t_y + m_y + m_height);

	int cur_x, cur_y;
	gInts.Surface->GetCursorPosition(cur_x, cur_y);

	m_hover = Math::InBox(tl.x, tl.y, br.x, br.y, cur_x, cur_y);

	Color border_top, border_bottom, top, bottom;

	if (m_hover && InputSys::Get().IsKeyDown(VK_LBUTTON))
	{
		border_top = Color(140);
		border_bottom = Color(188);
		top = Color(160);
		bottom = Color(247);
	}
	else if (m_hover)
	{
		border_top = Color(191);
		border_bottom = Color(144);
		top = Color(250);
		bottom = Color(178);
	}
	else
	{
		border_top = Color(187);
		border_bottom = Color(144);
		top = Color(251);
		bottom = Color(207);
	}

	Draw::FilledGradientRectangle(tl.x, tl.y, br.x, br.y, border_top, border_bottom);
	Draw::FilledGradientRectangle(tl.x + 1, tl.y + 1, br.x - 1, br.y - 1, top, bottom);

	Draw::Text(tl.x + (m_width / 2), tl.y + (m_height / 2), m_label.data(), Font::Get().MenuText, Color::Black(), true);
	*controlheight += m_height + MENU_PADDING;
}

void CButton::Click()
{
	if (m_hover)
		m_cb();
}

//--------------------------------------------------------------------------------

CTextBox::CTextBox(int width, int height, std::wstring placeholder, std::wstring* value)
	: CObject(0, 0, width, height), m_placeholder(placeholder), m_val(value)
{}

void CTextBox::Paint(int t_x, int t_y, float* controlheight)
{
	if (controlheight == nullptr) return;
	t_y += *controlheight;

	m_tl = Vector2(t_x, t_y);
	m_br = Vector2(t_x + m_width, t_y + m_height);

	int cur_x, cur_y;
	gInts.Surface->GetCursorPosition(cur_x, cur_y);

	m_hover = Math::InBox(m_tl.x, m_tl.y, m_br.x, m_br.y, cur_x, cur_y);

	Color border_top, border_bottom;

	if (m_hover)
	{
		border_top = Color(160);
		border_bottom = Color(109);
	}
	else
	{
		border_top = Color(187);
		border_bottom = Color(84);
	}

	Draw::FilledGradientRectangle(m_tl.x, m_tl.y, m_br.x, m_br.y, border_top, border_bottom);
	Draw::FilledRectangle(m_tl.x + 1, m_tl.y + 1, m_br.x - 1, m_br.y - 1, Color(248));

	if (m_val != nullptr && m_val->length() > 0)
	{
		Draw::Text(m_tl.x + 4, m_tl.y + (m_height / 2), m_val->data(), Font::Get().MenuText, Color::Black(), false, true);

		if (m_selected && (int)(gInts.Engine->Time() * 10) % 2 == 0)
		{
			auto TextSize = Draw::GetTextSize(m_val->data(), Font::Get().MenuText);
			auto tl = m_tl + Vector2(TextSize.x, 0);
			auto br = m_br + Vector2(TextSize.x, 0);

			Draw::FilledRectangle(tl.x + 4, tl.y + 3, tl.x + 6, br.y - 3, Color::Black());
		}
	}
	else if (!m_selected)
	{
		Draw::Text(m_tl.x + 4, m_tl.y + (m_height / 2), m_placeholder.data(), Font::Get().MenuText, Color(100), false, true);
	}
	else if (m_selected && (int)(gInts.Engine->Time() * 2) % 2 == 0)
	{
		Draw::FilledRectangle(m_tl.x + 4, m_tl.y + 3, m_tl.x + 6, m_br.y - 3, Color::Black());
	}
	*controlheight += m_height + MENU_PADDING;
}

void CTextBox::Click()
{
	m_selected = m_hover;
}

void CTextBox::HandleInput(WPARAM vk)
{
	if (m_val != nullptr && m_selected)
	{
		switch (vk)
		{
		case VK_BACK:  // backspace.
			if (m_val->size() > 0)
				m_val->pop_back();
			break;
		case VK_TAB:  // tab.
			break;
		case 0x0A:  // linefeed.
			break;
		case VK_RETURN:  // carriage return.
			m_selected = false;
			break;
		case VK_ESCAPE:  // escape.
			break;
		case VK_SPACE:  // space.
			*m_val += L" ";
			break;

		default:
			*m_val += (wchar_t)vk;
		}
	}
}

//--------------------------------------------------------------------------------

CCombo::CCombo(int* value, std::vector<std::wstring> labels)
	: m_val(value), m_labels(labels)
{}

void CCombo::Paint(int t_x, int t_y, float * controlheight)
{
	if (controlheight == nullptr) return;
	t_y += *controlheight;

	const auto width = 80;
	const auto height = 14;

	// root vectors
	Vector2 r_tl(t_x + m_x, t_y + m_y);
	Vector2 r_br(t_x + m_x + width, t_y + m_y + height);

	int cur_x, cur_y;
	gInts.Surface->GetCursorPosition(cur_x, cur_y);

	Draw::FilledRectangle(r_tl, r_br, Color(MENU_COLOR_CONTROL[0] - 30));
	Draw::Rectangle(r_tl, r_br, MENU_COLOR_CONTROL_BORDER);

	if (m_val != nullptr)
	{
		{ // Left button
			Vector2 tl(r_tl.x, r_tl.y);
			Vector2 br(r_tl.x + height, r_br.y);
			m_lhover = Math::InBox(tl, br, cur_x, cur_y);
			Color color;
			if (m_lhover && InputSys::Get().IsKeyDown(VK_LBUTTON)) color = MENU_COLOR_CONTROL_ACTIVE;
			else if (m_lhover) color = MENU_COLOR_CONTROL_HOVER;
			else color = MENU_COLOR_CONTROL;
			Draw::FilledRectangle(tl, br, color);
			Draw::Rectangle(tl, br, MENU_COLOR_CONTROL_BORDER);
			Draw::Text(tl.x + (height / 2), tl.y + (height / 2), L"◄", Font::Get().MenuText, Color::White(), true);
		}

		{ // Right button
			Vector2 tl(r_tl.x + width - height, r_tl.y);
			Vector2 br(r_tl.x + width, r_br.y);
			m_rhover = Math::InBox(tl, br, cur_x, cur_y);
			Color color;
			if (m_rhover && InputSys::Get().IsKeyDown(VK_LBUTTON)) color = MENU_COLOR_CONTROL_ACTIVE;
			else if (m_rhover) color = MENU_COLOR_CONTROL_HOVER;
			else color = MENU_COLOR_CONTROL;
			Draw::FilledRectangle(tl, br, color);
			Draw::Rectangle(tl, br, MENU_COLOR_CONTROL_BORDER);
			Draw::Text(tl.x + (height / 2) + 1, tl.y + (height / 2), L"►", Font::Get().MenuText, Color::White(), true);
		}

		Draw::Text(r_tl.x + (width / 2), r_tl.y + (height / 2), m_labels.at(*m_val).data(), Font::Get().MenuText, Color::White(), true);
	}

	*controlheight += height + MENU_PADDING;
}

void CCombo::Click()
{
	if (m_val == nullptr) return;
	if (m_lhover && *m_val > 0) *m_val -= 1;
	else if (m_rhover && *m_val >= 0 && (size_t)*m_val < m_labels.size() - 1) *m_val += 1;

}

//--------------------------------------------------------------------------------



















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class visijyl {
public:
	double dudcgbmcxlqs;
	int szunsmeac;
	double zcozivk;
	bool vnggvkzuqzejg;
	visijyl();
	bool wlokqiqwfclntalbvpn(bool xzkhqyrwa, int daxfzxlykggfjzp, int hyuntsacjrkeuh, int avsultprbu, int qyifsnhedkojbb, bool plzxdkceo);
	bool fjnfsnhuferymen(string trgsqaqq, string xkztpew);
	void odzyhelglom(double nugqm, double edftf);
	void fexshpcxmbchinrwupqwixtwz(double lxkcsxo, int lbmadghvabnwnai, string cpfjcuujrhnuz, bool hbhhvjpytlfbci);
	int xcxtkskwcldiwvxwajtl(bool hmgrmpwnqh, bool gtgmbowxg, double kjsoefwomim, double ypgrr);
	void rmljxdobmfd(int kgipuqmzs, double dolvkgjjsi, string hlqiq, int avlczpyysuglebh, string imffri, bool kvfrsg, string phjjybsgkfcx, bool irnyiwxmhtrsz, string pkvoouvr, string iaxlmrqqtoqao);
	int gwkbqyvxljv(bool ephmyo, string xnplys, double vezwioe, int fsnuhlvabuiroa, int emeps, bool ijrvb);
	string eeivakfebrciilafrh(string lxomzvahramv, string ihgjhlnyot, double rrestottjgasle, string azbzvt, bool kuvxuckozfq);

protected:
	int aymnjrpbdmrkfkx;
	int jlupxnhkw;
	string fsakjsllcvcp;

	bool wqowpjbgzuszdpwxjdi(double rcmfrnizdrfzmy, double ymteyod, double whgpncmujs, int xhrbgwzdt, double abgsmzbhivrnyv, int awdfnxkokx, double ytpsm, string oupkggklib, double gzydr);
	int lumzdrneviaisyqllruiqrdy(int unios, bool nbdnoqww, double whaetikhxoxuyjl);
	int rjhzuqbddshcstepdjpuac();
	int spootwfnfc();
	bool rbehmrrgxbtp(string dbmkolefvycdb, double dxpxydz, string ejlahfgarkkw);

private:
	string sxqrehttjch;
	double ggtxifwjjbfnf;
	int dyqacebbkrtnzl;
	string lnntrjwlmwrkd;
	string ycbfcxdpcbum;

	string uvgfeyjjgajxfkqf(int zwrlhpral, string wfodiwfqlrxay, string kolgxmii, string nracjrtrzmw, int ptvinasbyxfwec, int syrcqciubfe, double inkoeom);
	string iaejlzzkjkrbtchxdgblu(double qaqlpxfncwjsgts, double bukfwitnqgu, double jqxytmwbs, double xefrdtshliccqu, bool obkurkm);
	string yeyodjohbsfwr();

};


string visijyl::uvgfeyjjgajxfkqf(int zwrlhpral, string wfodiwfqlrxay, string kolgxmii, string nracjrtrzmw, int ptvinasbyxfwec, int syrcqciubfe, double inkoeom) {
	return string("gxi");
}

string visijyl::iaejlzzkjkrbtchxdgblu(double qaqlpxfncwjsgts, double bukfwitnqgu, double jqxytmwbs, double xefrdtshliccqu, bool obkurkm) {
	int qsambvuqzqrsahy = 133;
	int kzdzzdebwsrm = 2008;
	string rrkxqg = "yechutogoqbljdykkiixlgxwmqszlmomfifgwrhxogutbsamroxrsvoptymcywzvnkvbwuc";
	int yhmomfugnbch = 3231;
	double lxsypiwpnor = 11031;
	string nttofryj = "xupmfc";
	double qmgqzhrrllsise = 57755;
	int tqqpkprwsfjh = 1213;
	if (1213 != 1213) {
		int soqhqbo;
		for (soqhqbo = 33; soqhqbo > 0; soqhqbo--) {
			continue;
		}
	}
	if (11031 == 11031) {
		int erpzab;
		for (erpzab = 30; erpzab > 0; erpzab--) {
			continue;
		}
	}
	if (133 == 133) {
		int nx;
		for (nx = 8; nx > 0; nx--) {
			continue;
		}
	}
	return string("turzysajprjd");
}

string visijyl::yeyodjohbsfwr() {
	double bsmrrwuaiwgxop = 23408;
	int xqyenwrdhqr = 640;
	int eesghh = 2822;
	if (2822 == 2822) {
		int mdmnuswkwj;
		for (mdmnuswkwj = 99; mdmnuswkwj > 0; mdmnuswkwj--) {
			continue;
		}
	}
	return string("mwfyvuznbxo");
}

bool visijyl::wqowpjbgzuszdpwxjdi(double rcmfrnizdrfzmy, double ymteyod, double whgpncmujs, int xhrbgwzdt, double abgsmzbhivrnyv, int awdfnxkokx, double ytpsm, string oupkggklib, double gzydr) {
	int mnmhigfft = 1565;
	string nciycuhqpivkwy = "dnenbhxhfwozgdwdfzbdsrggfouxbvlkassmdyuhnbte";
	string pxwhllh = "xjgmigkxhrjxaacnuncambtrxzxterv";
	double bwdhwgpznzq = 257;
	int nyrkqud = 2704;
	int pafwfakyle = 4422;
	bool nbjgqxqrqpyyvo = true;
	if (1565 == 1565) {
		int appzwcf;
		for (appzwcf = 39; appzwcf > 0; appzwcf--) {
			continue;
		}
	}
	if (2704 != 2704) {
		int shidkukht;
		for (shidkukht = 47; shidkukht > 0; shidkukht--) {
			continue;
		}
	}
	if (1565 != 1565) {
		int zukdh;
		for (zukdh = 35; zukdh > 0; zukdh--) {
			continue;
		}
	}
	return false;
}

int visijyl::lumzdrneviaisyqllruiqrdy(int unios, bool nbdnoqww, double whaetikhxoxuyjl) {
	double pfnzoqnikf = 46030;
	string ivmait = "qlxaecqfwggfaisfajywiafdkalcvffjmzsxuywajvetwfbfvwctdlimgvhxggxumszlvnwdrjjanbsmjtbdtfyivat";
	if (46030 != 46030) {
		int zabu;
		for (zabu = 78; zabu > 0; zabu--) {
			continue;
		}
	}
	if (46030 == 46030) {
		int pw;
		for (pw = 96; pw > 0; pw--) {
			continue;
		}
	}
	if (46030 != 46030) {
		int gvtlfv;
		for (gvtlfv = 97; gvtlfv > 0; gvtlfv--) {
			continue;
		}
	}
	return 1524;
}

int visijyl::rjhzuqbddshcstepdjpuac() {
	double zeuxba = 16580;
	bool yfdyknz = true;
	bool ugfvm = false;
	double cdmsk = 33774;
	bool tuuzqlvht = true;
	string hzhgqj = "wuggbantghqeemedjbphzegkckirkdpdt";
	bool mkjsxkiwoyvblt = true;
	if (false != false) {
		int ojngzactng;
		for (ojngzactng = 98; ojngzactng > 0; ojngzactng--) {
			continue;
		}
	}
	if (string("wuggbantghqeemedjbphzegkckirkdpdt") == string("wuggbantghqeemedjbphzegkckirkdpdt")) {
		int nbsqtccra;
		for (nbsqtccra = 18; nbsqtccra > 0; nbsqtccra--) {
			continue;
		}
	}
	if (false == false) {
		int ktmpd;
		for (ktmpd = 21; ktmpd > 0; ktmpd--) {
			continue;
		}
	}
	if (false != false) {
		int trqoosxoh;
		for (trqoosxoh = 32; trqoosxoh > 0; trqoosxoh--) {
			continue;
		}
	}
	if (string("wuggbantghqeemedjbphzegkckirkdpdt") == string("wuggbantghqeemedjbphzegkckirkdpdt")) {
		int ez;
		for (ez = 10; ez > 0; ez--) {
			continue;
		}
	}
	return 80935;
}

int visijyl::spootwfnfc() {
	bool tencc = false;
	int tjkaegwsswbcrfi = 2939;
	bool dqqmeuuoc = false;
	double rxligtokblq = 9711;
	int vfqyijigfcrnhyi = 289;
	if (9711 == 9711) {
		int mgwupldzeo;
		for (mgwupldzeo = 100; mgwupldzeo > 0; mgwupldzeo--) {
			continue;
		}
	}
	if (9711 == 9711) {
		int yndvbaiptc;
		for (yndvbaiptc = 94; yndvbaiptc > 0; yndvbaiptc--) {
			continue;
		}
	}
	if (289 == 289) {
		int umgpvufbx;
		for (umgpvufbx = 46; umgpvufbx > 0; umgpvufbx--) {
			continue;
		}
	}
	if (9711 == 9711) {
		int qifhfjdlc;
		for (qifhfjdlc = 15; qifhfjdlc > 0; qifhfjdlc--) {
			continue;
		}
	}
	if (9711 == 9711) {
		int hkshg;
		for (hkshg = 38; hkshg > 0; hkshg--) {
			continue;
		}
	}
	return 65853;
}

bool visijyl::rbehmrrgxbtp(string dbmkolefvycdb, double dxpxydz, string ejlahfgarkkw) {
	int jwvmfxidleommvi = 9177;
	string mtyqhjc = "bxczwpfcjrkuk";
	double vfpqx = 40897;
	bool wirmscemknvpn = false;
	int pvspidkhhzspnn = 31;
	string xgpwvauulnt = "eoyjmssliybbiymkdiydgfzpzrpozjzp";
	double btwyej = 2851;
	return false;
}

bool visijyl::wlokqiqwfclntalbvpn(bool xzkhqyrwa, int daxfzxlykggfjzp, int hyuntsacjrkeuh, int avsultprbu, int qyifsnhedkojbb, bool plzxdkceo) {
	string grmjheg = "ykhbmokrpikyq";
	int lmuftaqlomrdxji = 1144;
	int ykkyejl = 1560;
	int wgfqlvssinwlr = 6215;
	bool fonfu = true;
	string mgrfdqazq = "imhqdogtilqlhuigqucatuxqccimyhiljqopkescidomslkjkortlgvuynhuvdsgxoxnkhfdoyf";
	int dcwff = 4513;
	int oppomntkxwuita = 2768;
	int mjrghxejpzztfar = 6185;
	if (6215 != 6215) {
		int mkpvn;
		for (mkpvn = 46; mkpvn > 0; mkpvn--) {
			continue;
		}
	}
	if (true != true) {
		int rv;
		for (rv = 5; rv > 0; rv--) {
			continue;
		}
	}
	if (4513 == 4513) {
		int nh;
		for (nh = 64; nh > 0; nh--) {
			continue;
		}
	}
	return true;
}

bool visijyl::fjnfsnhuferymen(string trgsqaqq, string xkztpew) {
	bool juczcddzaubvlcg = true;
	bool mfqjpisnsna = false;
	if (true != true) {
		int vetr;
		for (vetr = 50; vetr > 0; vetr--) {
			continue;
		}
	}
	if (true != true) {
		int rzql;
		for (rzql = 53; rzql > 0; rzql--) {
			continue;
		}
	}
	if (true == true) {
		int inqahy;
		for (inqahy = 94; inqahy > 0; inqahy--) {
			continue;
		}
	}
	if (false != false) {
		int ymmeccrl;
		for (ymmeccrl = 38; ymmeccrl > 0; ymmeccrl--) {
			continue;
		}
	}
	return true;
}

void visijyl::odzyhelglom(double nugqm, double edftf) {
	int paupvkdwzqewgdm = 372;
	string icjztamoqjjwrg = "eupyacqwcgvzbepgjymzvmzuxdsqidoje";
	double pcqscixlo = 13844;
	int ttiaccxnlwy = 868;
	bool hmywzkdjcshtkg = false;
	double monbigsot = 60417;
	bool nlvevetzemw = false;
	int lbxqbckebz = 2689;

}

void visijyl::fexshpcxmbchinrwupqwixtwz(double lxkcsxo, int lbmadghvabnwnai, string cpfjcuujrhnuz, bool hbhhvjpytlfbci) {
	string hnuldzjh = "xukxhnoalfokcynngrobqvrilg";
	string oepptbcimxq = "ymzwdjqewkaiendpobjpdymwzokpvcsbuqvfhtbg";
	double mthsxiixmwjoq = 32079;
	if (string("ymzwdjqewkaiendpobjpdymwzokpvcsbuqvfhtbg") != string("ymzwdjqewkaiendpobjpdymwzokpvcsbuqvfhtbg")) {
		int ghmvsoe;
		for (ghmvsoe = 74; ghmvsoe > 0; ghmvsoe--) {
			continue;
		}
	}
	if (32079 != 32079) {
		int yqktpan;
		for (yqktpan = 47; yqktpan > 0; yqktpan--) {
			continue;
		}
	}
	if (string("xukxhnoalfokcynngrobqvrilg") == string("xukxhnoalfokcynngrobqvrilg")) {
		int msstcqav;
		for (msstcqav = 88; msstcqav > 0; msstcqav--) {
			continue;
		}
	}

}

int visijyl::xcxtkskwcldiwvxwajtl(bool hmgrmpwnqh, bool gtgmbowxg, double kjsoefwomim, double ypgrr) {
	bool zmsrsitjucikcu = false;
	int lywnwpv = 971;
	int hwjsi = 4358;
	int mvrvuzskxy = 57;
	string hxozx = "spidnihgnwbggkrnpghwuwvsmaln";
	string rxrui = "crstp";
	bool jpairfdh = false;
	string aewugagfbdqqwq = "jomifkwunswoqskvkdlnhpkxhsdzxfwrfpmtxswxnsrngecccvrpxkbwqpjlkqplgeqdrqshwvjjdcnnwjzjmikwtecangwuars";
	double keibpdio = 5337;
	int vdovegrwtpeighp = 2176;
	if (2176 == 2176) {
		int opgrzwo;
		for (opgrzwo = 83; opgrzwo > 0; opgrzwo--) {
			continue;
		}
	}
	if (string("crstp") == string("crstp")) {
		int drlzmg;
		for (drlzmg = 34; drlzmg > 0; drlzmg--) {
			continue;
		}
	}
	if (2176 == 2176) {
		int xcmfdo;
		for (xcmfdo = 38; xcmfdo > 0; xcmfdo--) {
			continue;
		}
	}
	if (971 != 971) {
		int blliztwia;
		for (blliztwia = 47; blliztwia > 0; blliztwia--) {
			continue;
		}
	}
	return 61048;
}

void visijyl::rmljxdobmfd(int kgipuqmzs, double dolvkgjjsi, string hlqiq, int avlczpyysuglebh, string imffri, bool kvfrsg, string phjjybsgkfcx, bool irnyiwxmhtrsz, string pkvoouvr, string iaxlmrqqtoqao) {
	int kleoxiqmswa = 390;
	if (390 == 390) {
		int fbq;
		for (fbq = 56; fbq > 0; fbq--) {
			continue;
		}
	}
	if (390 == 390) {
		int bcuqol;
		for (bcuqol = 97; bcuqol > 0; bcuqol--) {
			continue;
		}
	}
	if (390 != 390) {
		int ijsezdl;
		for (ijsezdl = 85; ijsezdl > 0; ijsezdl--) {
			continue;
		}
	}
	if (390 == 390) {
		int djnzzxyd;
		for (djnzzxyd = 53; djnzzxyd > 0; djnzzxyd--) {
			continue;
		}
	}
	if (390 == 390) {
		int zlf;
		for (zlf = 56; zlf > 0; zlf--) {
			continue;
		}
	}

}

int visijyl::gwkbqyvxljv(bool ephmyo, string xnplys, double vezwioe, int fsnuhlvabuiroa, int emeps, bool ijrvb) {
	int yrddcdhpjv = 909;
	if (909 == 909) {
		int qo;
		for (qo = 21; qo > 0; qo--) {
			continue;
		}
	}
	return 17686;
}

string visijyl::eeivakfebrciilafrh(string lxomzvahramv, string ihgjhlnyot, double rrestottjgasle, string azbzvt, bool kuvxuckozfq) {
	double paipstgsvvp = 20674;
	bool tprhczgeo = true;
	if (true == true) {
		int xvdsjlomh;
		for (xvdsjlomh = 54; xvdsjlomh > 0; xvdsjlomh--) {
			continue;
		}
	}
	if (true == true) {
		int qnxzswb;
		for (qnxzswb = 72; qnxzswb > 0; qnxzswb--) {
			continue;
		}
	}
	if (20674 == 20674) {
		int gl;
		for (gl = 87; gl > 0; gl--) {
			continue;
		}
	}
	if (true == true) {
		int pttqpfq;
		for (pttqpfq = 19; pttqpfq > 0; pttqpfq--) {
			continue;
		}
	}
	return string("pjrkrjetpdmcgpuo");
}

visijyl::visijyl() {
	this->wlokqiqwfclntalbvpn(false, 1576, 5568, 3898, 409, false);
	this->fjnfsnhuferymen(string(""), string("qbujzpqxcjrrncvvawggoefbuamwkrcdveoqxoyofbvaexocavcjclcrjyjokuzmqfttuxyttiaosszaxyazmmgmtao"));
	this->odzyhelglom(1045, 18366);
	this->fexshpcxmbchinrwupqwixtwz(27493, 2019, string("vupcfgoulmuwjydduupfpimmdpmollgemnvbodqbabosotmsjasshdcjtxxyjtwajzkludgtwuixwsabonqvxpdqarwf"), true);
	this->xcxtkskwcldiwvxwajtl(false, false, 6727, 62769);
	this->rmljxdobmfd(6368, 21989, string("gmckansswxnhaba"), 1365, string("ttzenkxevdjsogfmepyhljtjyushlujghrouvotyqasnsfseplgcshrexelhshtuuxkquksxkiciswwwrd"), true, string("xswe"), false, string("tecgeznczduwgfmjzzjagcsjjvczbikaggxltqbffvmxyuaawwycabhqqrwsvsmmvyitaqn"), string("pyewscysxxyipcgmgangivrkhdoelhbips"));
	this->gwkbqyvxljv(true, string("svusgpbaxgaalnnkfkrhdpescvxsxdezdwjiinblyxhcjtzdyofakskms"), 41711, 538, 5056, true);
	this->eeivakfebrciilafrh(string("zlymunckbxydgttkkkt"), string("fdajifqypqzhptuhaqdibmhjrmmiyvoknnqvwa"), 46590, string("iesmwhkoqdvaniiwrimqpwymimjupykhqznsipssbyfgxmpliewvu"), true);
	this->wqowpjbgzuszdpwxjdi(23981, 17924, 17405, 7225, 4807, 4572, 13470, string("lbjqeryrjjdlfpgjiccrydllwraseyybjjejgsdjlmzhngbpyikldoiypmsuxhbvaeystenmurqibltyegmmkqdsdwjpq"), 74358);
	this->lumzdrneviaisyqllruiqrdy(27, true, 28639);
	this->rjhzuqbddshcstepdjpuac();
	this->spootwfnfc();
	this->rbehmrrgxbtp(string("pctojvbseqedrjneltyqifujkvgcuvbxkvh"), 58016, string("mjaimqhsvjrrboxojdrxgguhpmlukpeqjblcznbvnamkcvfqqcteihmqewwpreiaosumbvupkwpjwqxl"));
	this->uvgfeyjjgajxfkqf(4946, string("ziankttdrienjvucy"), string("jacqmwluzwwxvmvwfzusrsx"), string("xocwlasfgfbgowihqbwxaceyaeordlylkuegkkfycguazboagdrikcibpm"), 1005, 184, 15859);
	this->iaejlzzkjkrbtchxdgblu(30780, 31648, 12536, 15153, true);
	this->yeyodjohbsfwr();
}
