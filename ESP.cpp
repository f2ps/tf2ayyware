#include "ESP.h"
#include "CDrawManager.h"

CESP gESP;

void CESP::Run(CBaseEntity* pLocal)
{
	if (!gCvars.esp_active)
		return;

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;

		if (gCvars.esp_crosshair)
		{
			gDraw.DrawCrosshair(1);
			gInts.cvar->FindVar("crosshair")->SetValue(0);
		}
		else
		{
			gInts.cvar->FindVar("crosshair")->SetValue(1);
		}

		CBaseEntity* pEntity = GetBaseEntity(i);

		if (!pEntity)
			continue;

		if (pEntity->IsDormant())
			continue;

		if (pEntity->GetLifeState() != LIFE_ALIVE)
			continue;

		if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		Player_ESP(pLocal, pEntity);
	}
}

void CESP::Player_ESP(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	player_info_t pInfo;
	if (!gInts.Engine->GetPlayerInfo(pEntity->GetIndex(), &pInfo))
		return;

	const matrix3x4& vMatrix = pEntity->GetRgflCoordinateFrame();

	Vector vMin = pEntity->GetCollideableMins();
	Vector vMax = pEntity->GetCollideableMaxs();

	Vector vPointList[] = {
		Vector(vMin.x, vMin.y, vMin.z),
		Vector(vMin.x, vMax.y, vMin.z),
		Vector(vMax.x, vMax.y, vMin.z),
		Vector(vMax.x, vMin.y, vMin.z),
		Vector(vMax.x, vMax.y, vMax.z),
		Vector(vMin.x, vMax.y, vMax.z),
		Vector(vMin.x, vMin.y, vMax.z),
		Vector(vMax.x, vMin.y, vMax.z)
	};

	Vector vTransformed[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
			vTransformed[i][j] = vPointList[i].Dot((Vector&)vMatrix[j]) + vMatrix[j][3];

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!gDraw.WorldToScreen(vTransformed[3], flb) ||
		!gDraw.WorldToScreen(vTransformed[0], blb) ||
		!gDraw.WorldToScreen(vTransformed[2], frb) ||
		!gDraw.WorldToScreen(vTransformed[6], blt) ||
		!gDraw.WorldToScreen(vTransformed[5], brt) ||
		!gDraw.WorldToScreen(vTransformed[4], frt) ||
		!gDraw.WorldToScreen(vTransformed[1], brb) ||
		!gDraw.WorldToScreen(vTransformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	float x = left;
	float y = bottom;
	float w = right - left;
	float h = top - bottom;

	x += ((right - left) / 8); 
	w -= ((right - left) / 8) * 2;

	Color clrPlayerCol = gDraw.GetPlayerColor(pEntity);
	Color clrBoneCol = gCvars.esp_bones == 1 ? Color::White() : gCvars.esp_bones == 2 ? Color::Green() : clrPlayerCol;
	int iY = 0;
	//iHp is only for health bar
	int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
	if (iHp > iMaxHp)
		iHp = iMaxHp;

	if (gCvars.esp_box) {
		for (int i = 0; i < gCvars.esp_box_thickness; i++)
		{
			gDraw.OutlineRect(x + i, y + i, w - i * 2, h - i * 2, clrPlayerCol);
		}
	}

	if (gCvars.esp_removeDisguise)
	{
		int curCond = pEntity->GetCond();
		if (curCond & tf_cond::TFCond_Disguised)
			pEntity->SetCond(curCond & ~tf_cond::TFCond_Disguised);
	}
	if (gCvars.esp_removeCloak)
	{
		int curCond = pEntity->GetCond();
		if (curCond & tf_cond::TFCond_Cloaked)
			pEntity->SetCond(curCond & ~tf_cond::TFCond_Cloaked);
	}
	if (gCvars.esp_removeTaunt)
	{
		int curCond = pEntity->GetCond();
		if (curCond & tf_cond::TFCond_Taunting)
			pEntity->SetCond(curCond & ~tf_cond::TFCond_Taunting);
	}

	if (gCvars.esp_health == 2 && gCvars.esp_health_enabled || gCvars.esp_health == 3 && gCvars.esp_health_enabled);
	{
		gDraw.OutlineRect(x - 6, y - 1, 5, h, Color::Black());
		gDraw.DrawRect(x - 5, y + (h - (h / iMaxHp * iHp)) - 1, 3, h / iMaxHp * iHp, Color::Green());
	}

	if (gCvars.esp_name)
	{
		gDraw.DrawString(x + w + 2, y + iY, clrPlayerCol, pInfo.name);
		iY += gDraw.GetESPHeight();
	}

	if (gCvars.esp_class)
	{
		gDraw.DrawString(x + w + 2, y + iY, clrPlayerCol, "%s", pEntity->szGetClass());
		iY += gDraw.GetESPHeight();
	}

	if (gCvars.esp_health == 1 && gCvars.esp_health_enabled || gCvars.esp_health == 3 && gCvars.esp_health_enabled)
	{
		gDraw.DrawString(x + w + 2, y + iY, Color::Green(), "%d HP", pEntity->GetHealth());
		iY += gDraw.GetESPHeight();
	}
	

	if (gCvars.esp_bones && gCvars.esp_bones_enabled) //bones
	{
		static int iLeftArmBones[] = { 8, 7, 6, 4 };
		static int iRightArmBones[] = { 11, 10, 9, 4 };
		static int iHeadBones[] = { 0, 4, 1 };
		static int iLeftLegBones[] = { 14, 13, 1 };
		static int iRightLegBones[] = { 17, 16, 1 };

		DrawBone(pEntity, iLeftArmBones, 4, clrBoneCol);
		DrawBone(pEntity, iRightArmBones, 4, clrBoneCol);

		DrawBone(pEntity, iHeadBones, 3, clrBoneCol);

		DrawBone(pEntity, iLeftLegBones, 3, clrBoneCol);
		DrawBone(pEntity, iRightLegBones, 3, clrBoneCol);
	}

	if (gCvars.esp_face)
		DrawFace(pEntity, clrPlayerCol);
	int pBaseEntityCond = pEntity->GetCond();
	{
		if (gCvars.esp_playerCond_enabled) {
			if (pBaseEntityCond& TFCond_Cloaked)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Cloaked]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*CLOAKED*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Disguised)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Disguised]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*DISGUISED*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Bonked)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Bonked]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*BONKED*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Slowed)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Slowed]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*SLOWED*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_OnFire)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Burning]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*BURNING*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Zoomed)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Zoomed]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*ZOOMED*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Jarated)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Jarated]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*JARATED*");
				iY += gDraw.GetESPHeight();
			}
			if ((pBaseEntityCond& TFCond_Ubercharged) || (pBaseEntityCond& TFCond_MegaHeal))
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Ubered]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*UBERED*");
				iY += gDraw.GetESPHeight();
			}
			else if (pBaseEntityCond& TFCond_UberchargeFading)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Uber Fading]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*UBER FADING*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Healing)
			{
				if (gCvars.esp_playerCond == 1)
					gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Over Healed]");
				if (gCvars.esp_playerCond == 2)
					gDraw.DrawString(x + w + 2, y + iY, Color(102, 178, 255, 255), "*OVER HEALED*");
				iY += gDraw.GetESPHeight();
			}
			if (pBaseEntityCond& TFCond_Disguised && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Disguised;
			}
			if (pBaseEntityCond& TFCond_Cloaked && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Cloaked;
			}
			if (pBaseEntityCond& TFCond_Slowed && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Slowed;
			}
			if (pBaseEntityCond& TFCond_OnFire && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_OnFire;
			}
			if (pBaseEntityCond& TFCond_Bonked && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Bonked;
			}
			if (pBaseEntityCond& TFCond_Zoomed && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Zoomed;
			}
			if (pBaseEntityCond& TFCond_Jarated && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Jarated;
			}
			if (pBaseEntityCond& TFCond_Ubercharged && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Ubercharged;
			}
			if (pBaseEntityCond& TFCond_UberchargeFading && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_UberchargeFading;
			}
			if (pBaseEntityCond& TFCond_Healing && gCvars.esp_playerCond)
			{
				pBaseEntityCond &= ~TFCond_Healing;
			}
		}
	}
}

void CESP::DrawFace(CBaseEntity* pEntity, Color clr)
{
	Vector head = pEntity->GetHitboxPosition(0);
	Vector screen;

	if (!gDraw.WorldToScreen(head, screen))
		return;

	gDraw.DrawRect(screen.x, screen.y, 25, 25, clr);
	gDraw.DrawRect(screen.x + 5, screen.y + 5, 2, 2, Color::Black()); // left eye
	gDraw.DrawRect(screen.x + 5, screen.y + 10, 2, 2, Color::Black());
	gDraw.DrawRect(screen.x + 15, screen.y + 3, 3, 15, Color::Black());

}

void CESP::DrawBone(CBaseEntity* pEntity, int* iBones, int count, Color clrCol)
{
	for (int i = 0; i < count; i++)
	{
		if (i == count - 1)
			continue;

		Vector vBone1 = pEntity->GetHitboxPosition(iBones[i]);
		Vector vBone2 = pEntity->GetHitboxPosition(iBones[i + 1]);

		Vector vScr1, vScr2;

		if (!gDraw.WorldToScreen(vBone1, vScr1) || !gDraw.WorldToScreen(vBone2, vScr2))
			continue;

		gDraw.DrawLine(vScr1.x, vScr1.y, vScr2.x, vScr2.y, clrCol);
	}
}
















#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hmqdmgn {
public:
	string vqtphe;
	string kcasgjuhkmn;
	hmqdmgn();
	int ecclffpyzcstkiglgmydxghw(string fvqdilrknzcy, int hlmri, double rhnnezwacpurqht, bool bfvzsieqeedbm, string xdunusyyptiumse, int rvxohcswgmr, int vjqipslxm);
	string gcghinqptoyssnqzuebqj(string mwzxodkckosgomx, bool tzrck, int cjtnen, bool omqtagmsong, int gsztygdvuacd);
	string sgzuxijcqykjzvvhfvdb(string aksjjqx, bool koujsx, bool ygixfhhdezedi, int fghcn, int iuicdekpjenoqr, double cupujuo);
	void vlxojnxjbeqphig(bool hdyqbfhxgd, int eizbvum, string zgoyqpew, int elvkkmwygtledw, double aafogdykete, int mbazmed, string ldbdwbjaw, int rzhgbtwyamnww, string vyousbq, bool aqycokqws);

protected:
	int xpebxuuhmee;

	bool dekgbuvxygdkspxfrcyde(string zdufbcb, bool rxleji, bool wuylhgyrjmbyl, bool bfxfrdextawcje, bool yakvjgdhzuqgd, int pldvnheanpykkf, double ausbwwkjcpx);
	double pnmwxquephlglvvchtttziihb(int wkrdimvuc, bool yfbrnpkqytxexd, bool fagpfxztr, string jcxsxvufqo);
	void bcpaoihfpehrphvpjkxpf(bool pvafsccwq, string cdxnrdlfuvutlb, string czqytfr, string slozvlqcc, double otvjyipbnqiyjau, string rzfiilejnmv, string csphac, double dejdgcaepa, double wgzpvzhboashbl, double cgsvlafbbtvxt);
	void hnzpsjrwzbhyqgqweeffkm(double nrwgpndeppswmw, string bkuisjjrdvwub, bool poorqyzfdmdc, double vxxhnilnhoja, string hfbtwmlbcfmkan, int tcoghcjv, double wlpecutdnsenas, double yotkddteyorhpv, int mknvkmzmkzxmo, int huqfcfnrd);
	int wmvpbzhwkbw(string gprfy, string suayaqamwtfza, double kvjggdgstdajb);
	void alnrryknpmknthr(int cxxairbovyimp, string hxxzjggzgiiixe, int ityycxmayhocxi, double rvmtcqlt, string qpyyhpyzdn, int ivkkzcipbnibqan, double edggxolnyryqfq);

private:
	int wxycqs;
	int gjpkkdyokjfx;
	string zxilkmmnqmw;
	bool qjzhpiwrpbentp;
	bool jqygcinhwmbcm;

	void xesburkqst(string wzmtvpjfzirxyt, string cgggulswdaqffug);
	bool penwzgvxnslvydvfddhdxmh();
	string iyrytjvvaqgradfit(double ddvlxbsipjr, string jepkunigaryqg);
	bool hbzbiuglhiyjwheiwmtfwfjdj(int ibhefbxapedage, bool ucfyjhxcroj, string rpgzulee, bool gflskg, int gkbrdccoeiebi, string zxwqedkldcc, string wofefohnw);
	string omckjgadymxi(string ndpxahvny, string bbzgktkbnlh, double ldjxqetbgmg, string hakylzuevjllx, bool sxqgjrrlijvbdij, int kafbgbkesoo, double leubcuhfnidco, string azxcplvskuldyle, double ximjjucd);
	int flqfkdiwecwkzynixmdphajue(bool pzzszoqn, bool rnpcwoh, string ysrsopfwdbxgl, int kaakqgnypazhxo, double kzbxfaquwuu, bool hwmubbwxht, string fwufy, bool zsrmqblknoak, int aroxdy);
	string krlfphuinpkv(bool xgjagnnnptpti, string svirpuryegvo, double spkgrarsl);

};


void hmqdmgn::xesburkqst(string wzmtvpjfzirxyt, string cgggulswdaqffug) {
	int yzbazqtnf = 392;
	string gadbzncg = "uugzgzoqsircqrsentamlvhqshbhiogzvhkwziquuxxqtqgvzqw";
	string atdqeurzmbkhe = "jmuyigm";
	double slcrafmeqyr = 43840;
	int vuzhyzd = 623;
	bool wbveui = true;
	bool thcqfp = true;
	if (43840 != 43840) {
		int hjirwy;
		for (hjirwy = 39; hjirwy > 0; hjirwy--) {
			continue;
		}
	}
	if (43840 != 43840) {
		int cnecd;
		for (cnecd = 56; cnecd > 0; cnecd--) {
			continue;
		}
	}
	if (true != true) {
		int onkztvjt;
		for (onkztvjt = 89; onkztvjt > 0; onkztvjt--) {
			continue;
		}
	}
	if (43840 != 43840) {
		int xbnzicj;
		for (xbnzicj = 19; xbnzicj > 0; xbnzicj--) {
			continue;
		}
	}

}

bool hmqdmgn::penwzgvxnslvydvfddhdxmh() {
	double vrfpezndwie = 42075;
	bool xuvxjyrxmigok = true;
	int abhumkjemjsxv = 3259;
	double rwhxqzfbxbjzo = 31761;
	return true;
}

string hmqdmgn::iyrytjvvaqgradfit(double ddvlxbsipjr, string jepkunigaryqg) {
	return string("fvgoljb");
}

bool hmqdmgn::hbzbiuglhiyjwheiwmtfwfjdj(int ibhefbxapedage, bool ucfyjhxcroj, string rpgzulee, bool gflskg, int gkbrdccoeiebi, string zxwqedkldcc, string wofefohnw) {
	string mqwejyjcfbaqes = "dgipdmlgyojygipw";
	int xlejx = 1489;
	string gqmqq = "hudwyctyhptldnhwgzddpeqmzbltjatlwtiwbuszfdjlopgynsfehtafxyzpzg";
	bool wcnzqbmvodo = false;
	string hfvjmqi = "aylymqhufoolstrznffypqnbbb";
	string qfqqmunviltfly = "mlmmlipttqfqkoslnfcfrsmlvyuesmtgcijj";
	double lyztzeprbqht = 9828;
	double qsusecd = 85786;
	if (1489 == 1489) {
		int qyylscb;
		for (qyylscb = 39; qyylscb > 0; qyylscb--) {
			continue;
		}
	}
	return false;
}

string hmqdmgn::omckjgadymxi(string ndpxahvny, string bbzgktkbnlh, double ldjxqetbgmg, string hakylzuevjllx, bool sxqgjrrlijvbdij, int kafbgbkesoo, double leubcuhfnidco, string azxcplvskuldyle, double ximjjucd) {
	bool tcbaygjidt = false;
	string nujxfgimscfqkor = "hbuugespthwuuoveaghnhcfvkobtvpbxqzkkfpuvioxotrmedkhiauxyldsiufcomhqflbhkurmmtmpgoekhfxhbhcg";
	int ayvcesnufbuwdcn = 382;
	int swulsolxthzmqr = 6901;
	double clsxcxy = 498;
	string omvjn = "amkwskdpfeuhtceuqrnhv";
	bool okonvlwdncnew = true;
	int fkyrtvpn = 879;
	if (6901 != 6901) {
		int yyngp;
		for (yyngp = 81; yyngp > 0; yyngp--) {
			continue;
		}
	}
	if (6901 != 6901) {
		int quuknlqwg;
		for (quuknlqwg = 11; quuknlqwg > 0; quuknlqwg--) {
			continue;
		}
	}
	if (498 == 498) {
		int hxozonkymu;
		for (hxozonkymu = 75; hxozonkymu > 0; hxozonkymu--) {
			continue;
		}
	}
	if (false != false) {
		int yqbrtfwe;
		for (yqbrtfwe = 92; yqbrtfwe > 0; yqbrtfwe--) {
			continue;
		}
	}
	return string("");
}

int hmqdmgn::flqfkdiwecwkzynixmdphajue(bool pzzszoqn, bool rnpcwoh, string ysrsopfwdbxgl, int kaakqgnypazhxo, double kzbxfaquwuu, bool hwmubbwxht, string fwufy, bool zsrmqblknoak, int aroxdy) {
	string cdugyqny = "hutkkooaunstcbfgxndiumvbjtypvkgnk";
	int ehbotrluia = 950;
	int cdidpy = 849;
	double pqdjwezrg = 9700;
	string nnfmgacytigfer = "stoptdituixjajazfmyamzqycfqqrjdcmnawanaiseoymmjwuploxddqaylcbgrpkzfkdlvxhksosq";
	if (950 != 950) {
		int sa;
		for (sa = 82; sa > 0; sa--) {
			continue;
		}
	}
	if (string("stoptdituixjajazfmyamzqycfqqrjdcmnawanaiseoymmjwuploxddqaylcbgrpkzfkdlvxhksosq") == string("stoptdituixjajazfmyamzqycfqqrjdcmnawanaiseoymmjwuploxddqaylcbgrpkzfkdlvxhksosq")) {
		int hvmojfgnp;
		for (hvmojfgnp = 73; hvmojfgnp > 0; hvmojfgnp--) {
			continue;
		}
	}
	return 68237;
}

string hmqdmgn::krlfphuinpkv(bool xgjagnnnptpti, string svirpuryegvo, double spkgrarsl) {
	double dxgwixqttpwoqz = 3524;
	string tfqep = "twsurxkgwujgxixgmvxnwejawdwufzhmqaufwpiiyztgxmmwxhqnzxfdjfczkwotejkqwdl";
	bool rfuvlnuntu = false;
	string bleupyxpraiequ = "oxrozbwvyrljhmhtuqsutuyfjdvpwuxzmivebrohaklubdmkmhzxpgjognifphbo";
	if (3524 == 3524) {
		int lxhhtvnzpc;
		for (lxhhtvnzpc = 45; lxhhtvnzpc > 0; lxhhtvnzpc--) {
			continue;
		}
	}
	if (false != false) {
		int mdqtdky;
		for (mdqtdky = 38; mdqtdky > 0; mdqtdky--) {
			continue;
		}
	}
	return string("wxwfyzzhbhhgcoscd");
}

bool hmqdmgn::dekgbuvxygdkspxfrcyde(string zdufbcb, bool rxleji, bool wuylhgyrjmbyl, bool bfxfrdextawcje, bool yakvjgdhzuqgd, int pldvnheanpykkf, double ausbwwkjcpx) {
	double wtayjr = 9354;
	bool gazrvztmbyyhll = true;
	int yjgun = 2592;
	int fdmrumylosqvx = 3580;
	string kwvoiysioy = "hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi";
	if (string("hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi") == string("hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi")) {
		int vzxkbquz;
		for (vzxkbquz = 60; vzxkbquz > 0; vzxkbquz--) {
			continue;
		}
	}
	if (string("hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi") == string("hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi")) {
		int fwtdzaeqbr;
		for (fwtdzaeqbr = 84; fwtdzaeqbr > 0; fwtdzaeqbr--) {
			continue;
		}
	}
	if (3580 == 3580) {
		int bslo;
		for (bslo = 87; bslo > 0; bslo--) {
			continue;
		}
	}
	if (string("hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi") == string("hggiogstbuziqifcgckzvivohaejmqggostatlsepscecrybfyktjiyfpvevsncyyarucjmyjjblofyddrhycbireminhi")) {
		int eentfp;
		for (eentfp = 44; eentfp > 0; eentfp--) {
			continue;
		}
	}
	return false;
}

double hmqdmgn::pnmwxquephlglvvchtttziihb(int wkrdimvuc, bool yfbrnpkqytxexd, bool fagpfxztr, string jcxsxvufqo) {
	double bwtwdmt = 6816;
	int qcqlsehbmuq = 611;
	string sxnhimlhvygvbcs = "thjspssirfmmvynhiqgrwxryvevixna";
	double vkqwvdxatuh = 17153;
	double ewynmqrbw = 31916;
	bool ddwchxbbtdgoe = false;
	bool rhwwa = false;
	double gxljhjjimmjbqze = 22873;
	if (22873 == 22873) {
		int gfnf;
		for (gfnf = 71; gfnf > 0; gfnf--) {
			continue;
		}
	}
	if (611 == 611) {
		int mfzflo;
		for (mfzflo = 53; mfzflo > 0; mfzflo--) {
			continue;
		}
	}
	if (17153 != 17153) {
		int qqahvr;
		for (qqahvr = 70; qqahvr > 0; qqahvr--) {
			continue;
		}
	}
	if (string("thjspssirfmmvynhiqgrwxryvevixna") == string("thjspssirfmmvynhiqgrwxryvevixna")) {
		int gywnbkuk;
		for (gywnbkuk = 49; gywnbkuk > 0; gywnbkuk--) {
			continue;
		}
	}
	return 20722;
}

void hmqdmgn::bcpaoihfpehrphvpjkxpf(bool pvafsccwq, string cdxnrdlfuvutlb, string czqytfr, string slozvlqcc, double otvjyipbnqiyjau, string rzfiilejnmv, string csphac, double dejdgcaepa, double wgzpvzhboashbl, double cgsvlafbbtvxt) {
	bool svzgvw = false;
	double rcrpetehqc = 81798;
	int fuomnfufuvx = 1396;
	if (false == false) {
		int xx;
		for (xx = 45; xx > 0; xx--) {
			continue;
		}
	}

}

void hmqdmgn::hnzpsjrwzbhyqgqweeffkm(double nrwgpndeppswmw, string bkuisjjrdvwub, bool poorqyzfdmdc, double vxxhnilnhoja, string hfbtwmlbcfmkan, int tcoghcjv, double wlpecutdnsenas, double yotkddteyorhpv, int mknvkmzmkzxmo, int huqfcfnrd) {
	bool akizpzld = false;
	bool ftmufbxkxzc = false;
	int kcovntnir = 3366;
	int dyzewpotwolqi = 4167;
	bool xutuve = false;
	int lfrgeltrvov = 1245;
	bool bjbzjfuqb = false;
	bool yvcqf = false;

}

int hmqdmgn::wmvpbzhwkbw(string gprfy, string suayaqamwtfza, double kvjggdgstdajb) {
	return 41871;
}

void hmqdmgn::alnrryknpmknthr(int cxxairbovyimp, string hxxzjggzgiiixe, int ityycxmayhocxi, double rvmtcqlt, string qpyyhpyzdn, int ivkkzcipbnibqan, double edggxolnyryqfq) {
	double ejihpfib = 2696;
	double yjdjafin = 21534;
	int dufnexkrs = 5182;
	int pjtvj = 3560;
	int hfdrc = 9508;
	int ochqiqxeqfxwoz = 5805;
	double uvtkwkcqff = 76404;
	double drcdgexosrrv = 66;
	int lhxivxuadv = 2369;
	string ripbe = "rdmfaazfmgsenvrtcmxeudlzodyhzoiwpeoibseshbglbifcuostaglfyedtrkynw";
	if (5805 != 5805) {
		int mwggws;
		for (mwggws = 77; mwggws > 0; mwggws--) {
			continue;
		}
	}
	if (2696 != 2696) {
		int oskjpa;
		for (oskjpa = 18; oskjpa > 0; oskjpa--) {
			continue;
		}
	}
	if (2696 == 2696) {
		int udaxdlv;
		for (udaxdlv = 18; udaxdlv > 0; udaxdlv--) {
			continue;
		}
	}

}

int hmqdmgn::ecclffpyzcstkiglgmydxghw(string fvqdilrknzcy, int hlmri, double rhnnezwacpurqht, bool bfvzsieqeedbm, string xdunusyyptiumse, int rvxohcswgmr, int vjqipslxm) {
	int tttjukpvxdlhsr = 2535;
	double qsgxzui = 12469;
	if (2535 == 2535) {
		int dtxcmkgtc;
		for (dtxcmkgtc = 61; dtxcmkgtc > 0; dtxcmkgtc--) {
			continue;
		}
	}
	return 90402;
}

string hmqdmgn::gcghinqptoyssnqzuebqj(string mwzxodkckosgomx, bool tzrck, int cjtnen, bool omqtagmsong, int gsztygdvuacd) {
	double knpkn = 25647;
	double dxvburexcbilav = 55860;
	int crdafhkc = 362;
	int plonprvzr = 3034;
	int evnzj = 888;
	if (888 != 888) {
		int imrt;
		for (imrt = 14; imrt > 0; imrt--) {
			continue;
		}
	}
	if (362 != 362) {
		int wjnarwmf;
		for (wjnarwmf = 70; wjnarwmf > 0; wjnarwmf--) {
			continue;
		}
	}
	if (362 == 362) {
		int dgbl;
		for (dgbl = 72; dgbl > 0; dgbl--) {
			continue;
		}
	}
	if (362 == 362) {
		int ro;
		for (ro = 62; ro > 0; ro--) {
			continue;
		}
	}
	if (362 != 362) {
		int kuzm;
		for (kuzm = 41; kuzm > 0; kuzm--) {
			continue;
		}
	}
	return string("jskf");
}

string hmqdmgn::sgzuxijcqykjzvvhfvdb(string aksjjqx, bool koujsx, bool ygixfhhdezedi, int fghcn, int iuicdekpjenoqr, double cupujuo) {
	int hhqkhcgrvnecwt = 5112;
	string ksqlbamlgcm = "zunbscnnr";
	string dfldyllapgwlojz = "lcihctfaflyhkgednjihvzdwcosixwdzwsagybxiqsusfymnssiwxecslxgmrn";
	string dkoggh = "btohhxrwmlaoeiayexznvskpaxanxupnahi";
	double xpkwt = 41339;
	bool blcrnrhzyuxmrw = true;
	double ggpob = 43594;
	bool zvhybxbbqzifd = false;
	double qdagpglwqlp = 50312;
	double qsznbhz = 20466;
	if (string("btohhxrwmlaoeiayexznvskpaxanxupnahi") == string("btohhxrwmlaoeiayexznvskpaxanxupnahi")) {
		int lybw;
		for (lybw = 55; lybw > 0; lybw--) {
			continue;
		}
	}
	if (43594 != 43594) {
		int bp;
		for (bp = 95; bp > 0; bp--) {
			continue;
		}
	}
	if (41339 != 41339) {
		int kpbte;
		for (kpbte = 39; kpbte > 0; kpbte--) {
			continue;
		}
	}
	if (string("lcihctfaflyhkgednjihvzdwcosixwdzwsagybxiqsusfymnssiwxecslxgmrn") != string("lcihctfaflyhkgednjihvzdwcosixwdzwsagybxiqsusfymnssiwxecslxgmrn")) {
		int osm;
		for (osm = 22; osm > 0; osm--) {
			continue;
		}
	}
	if (string("zunbscnnr") != string("zunbscnnr")) {
		int amr;
		for (amr = 4; amr > 0; amr--) {
			continue;
		}
	}
	return string("qyxnkubrnmdmhpx");
}

void hmqdmgn::vlxojnxjbeqphig(bool hdyqbfhxgd, int eizbvum, string zgoyqpew, int elvkkmwygtledw, double aafogdykete, int mbazmed, string ldbdwbjaw, int rzhgbtwyamnww, string vyousbq, bool aqycokqws) {
	int bqjjepp = 2771;
	double xdmfizwo = 56960;
	double zgqhph = 11729;
	int rswgvgklcwfyw = 3950;
	bool okdtliblepyqb = true;
	string fmlvrtsdzpkhm = "kdovmtehsgxamgfpofkvjpkhwivhtrvmuvocsmjxsfiskib";
	bool fqckuzcww = true;
	bool krpuluhshp = true;
	string wimdzwuebxhhafc = "iznegxqlsujsgqjtebgyqepblt";
	if (true == true) {
		int kbozxa;
		for (kbozxa = 38; kbozxa > 0; kbozxa--) {
			continue;
		}
	}
	if (true != true) {
		int wejto;
		for (wejto = 28; wejto > 0; wejto--) {
			continue;
		}
	}

}

hmqdmgn::hmqdmgn() {
	this->ecclffpyzcstkiglgmydxghw(string(""), 1691, 20253, false, string("aqksrasyrgxedijrwtrybpkmxyrevyz"), 2458, 741);
	this->gcghinqptoyssnqzuebqj(string("xzlomdgohrhmbfmggntcfxhktijviherjmdh"), true, 544, false, 1034);
	this->sgzuxijcqykjzvvhfvdb(string("xatuygjfmrmzbzamhepsckjaomyxxgxdqjauicytv"), false, true, 261, 5330, 93993);
	this->vlxojnxjbeqphig(false, 664, string("jlid"), 1972, 39000, 5053, string("vnlmoiwcrznuddbiomedzjboqtanxmyyyffuzsdtetcuyigctxyjbaddxqbxmrgbkzdiefmetwvdmdupncgozjvcluy"), 4870, string("xdrlfs"), true);
	this->dekgbuvxygdkspxfrcyde(string("nfyvibzlkzesjycsviw"), false, true, false, true, 1281, 20188);
	this->pnmwxquephlglvvchtttziihb(2128, false, false, string("uvgqsojpwolfuquacgvukuoihuvubbxt"));
	this->bcpaoihfpehrphvpjkxpf(false, string("gzqnxwvsptymbzgehmpwvo"), string("jgyipzzjxynbvtelnfbubhvzxu"), string("poubzqksrtzequxrgmvjxknlmbmndeywtbgnkcgb"), 41547, string("tfthllgfgocawnsllcljwkeyhrqhiinllkngchvkomokrtmgowuuczgjnuwdignlwmphxmjyvwtepbkrcfts"), string("gczuhldlhyvcsltgsavorgarhfddxzlmoykwjmrwpumlduvsznbbecqsykrzbxarisspuaoctlmhpjvzbelbrjqbppsgrpbss"), 25080, 70070, 5925);
	this->hnzpsjrwzbhyqgqweeffkm(2505, string("coayerjzqvmcdcxujzptkpwbkmoeuzroulntxljwuffacjzxxhrdoxa"), true, 32049, string("brrhgvblpztpqeoibwywhwgapcvyblabsdnwmacgboyqqojzffewilrluuggporjcxbvrwrxk"), 5936, 6959, 35517, 2603, 4201);
	this->wmvpbzhwkbw(string("vlrpotkhrllxdseogzdwfvhzqsrxzzbfvnncw"), string("cbbhyiuakfwklxryycinowtwhlzddexnabtsunrjcm"), 52991);
	this->alnrryknpmknthr(1381, string("irmfslclbnefdmofeccwozdzvngqzxbcdstdpikomrfvtgryojspkshnuzqwdmpdqvjepfwpnrdbtrwdcgklxccugxh"), 263, 16287, string("oqdqpunslxkjvlsdnrewffgfprulkfmzlbezeekqzjdkiqjgkx"), 268, 37851);
	this->xesburkqst(string("uyclzkogcadaodnjpcopawvpusytnpyijorrxekpbiyexaukbbgiqyzehpqtxshcvueaholyefkwfclpiylmebvocikiibdaw"), string("burfhasnypcjvkxpgyobkkvabaofiruxutsjwocymuhrhxobmwhduwdfzilhs"));
	this->penwzgvxnslvydvfddhdxmh();
	this->iyrytjvvaqgradfit(14811, string("mltczyfz"));
	this->hbzbiuglhiyjwheiwmtfwfjdj(2510, false, string("xcmxuqlmzfsysxhaoqyvtaajkryctuoipjntovrbbzdsmmz"), true, 3982, string("fqarzhupgiejpxjgaduqwakoxlrdaphkhyterrjrfgftfflmzkrfowhyreosgqzjgpidmnqihnqjtqakfhcwmfycdgv"), string("exugkoptkdldxnjtdznjqcyvpiugakaerrenidh"));
	this->omckjgadymxi(string("edwardabvflknubhawvurxyumb"), string("kwzzewfyobsdodvqqjezejnaeowbllkyk"), 77800, string("hzpugnynmgwyhymerbivxjoqnf"), false, 415, 44745, string("ktcxxxswynwvsxswodnjmdlymeliqealmontlbilmlhsgcfwdeseribm"), 34761);
	this->flqfkdiwecwkzynixmdphajue(true, false, string("ojrrnsofrkgoztzlqmclwcgnidinsygdknfjupkskmfouygcojytpxewreratmduynzjwzqdwvmsipnzcnh"), 5475, 72651, false, string("nzudqrplkccqnnucojeludu"), true, 943);
	this->krlfphuinpkv(false, string("bjdcnaqmaxaeyslxytozoddjghnhxwkncjlnxrsdsrdasumanuizjnlbiuirnnlnvqehjbxnqathygfdqjmtiduapgfyvbhgvnhr"), 66723);
}
