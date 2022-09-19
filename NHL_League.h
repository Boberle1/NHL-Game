#pragma once
#include "NHLplayer.h"
#include "WindowIDs.h"

wxDECLARE_EVENT(PlayoffStartEvent, wxCommandEvent);

// regular season over event
wxDECLARE_EVENT(RegularSeasonOver, wxCommandEvent);

// first round of playoffs over
wxDECLARE_EVENT(FirstRoundOver, wxCommandEvent);

// second round over
wxDECLARE_EVENT(SecondRoundOver, wxCommandEvent);

// third round over
wxDECLARE_EVENT(ThirdRoundOver, wxCommandEvent);

enum Conf
{
	Eastern = 0,
	Western
};

enum Div
{
	Atlantic = 0,
	Metropolitan,
	Central,
	Pacific
};

enum Team
{
	ANA = 0,
	ARI,
	CGY,
    CHI,
	COL,
	DAL,
	EDM,
	LA,
	MIN,
	NSH,
	SEA,
	SJ,
	STL,
	VAN,
	VGK,
	WPG,
	BOS,
	BUF,
	CAR,
	CBJ,
	DET,
	FLA,
	MTL,
	NJ,
	NYI,
	NYR,
	OTT,
	PHI,
	PIT,
	TB,
	TOR,
	WSH
};

enum SpecialTeamNames
{
	LAK = Team::LA,
	TBL = Team::TB,
	NJD = Team::NJ,
	SJS = Team::SJ
};

struct Map
{
	Map(wxString s, int n) : teamstring(s), teamid(n) {}
	int teamid = -1;
	wxString teamstring = "";
};

struct Divname
{
	wxString Atlantic = "Atlantic";
	wxString Metropolitan = "Metropolitan";
	wxString Central = "Central";
	wxString Pacific = "Pacific";

	int GetDivID(wxString s)
	{
		if (Atlantic == s) return Div::Atlantic;
		if (Metropolitan == s) return Div::Metropolitan;
		if (Central == s) return Div::Central;
		if (Pacific == s) return Div::Pacific;

		return -1;
	}

	int GetDivIdByTeamId(int t)
	{
		for (size_t i = 0; i < atlantic.size(); ++i)
		{
			if (atlantic[i].teamid == t) return Div::Atlantic;
		}
		for (size_t i = 0; i < metropolitan.size(); ++i)
		{
			if (metropolitan[i].teamid == t) return Div::Metropolitan;
		}
		for (size_t i = 0; i < central.size(); ++i)
		{
			if (central[i].teamid == t) return Div::Central;
		}
		for (size_t i = 0; i < pacific.size(); ++i)
		{
			if (pacific[i].teamid == t) return Div::Pacific;
		}

		return -1;
	}

	void AddTeams(wxVector<wxString*>& t)
	{
		for (size_t i = 0; i < t.size(); ++i)
		{
			if (*t[i] == "BUF" || *t[i] == "BOS" || *t[i] == "DET" || *t[i] == "FLA" || *t[i] == "MTL" || *t[i] == "OTT" || *t[i] == "T.B" || *t[i] == "TBL" || *t[i] == "TOR")
				atlantic.push_back(Map(*t[i], i));
			else if (*t[i] == "CAR" || *t[i] == "CBJ" || *t[i] == "N.J" || *t[i] == "NJD" || *t[i] == "NYI" || *t[i] == "NYR" || *t[i] == "PHI" || *t[i] == "PIT" || *t[i] == "WSH")
				metropolitan.push_back(Map(*t[i], i));
			else if (*t[i] == "ARI" || *t[i] == "CHI" || *t[i] == "COL" || *t[i] == "DAL" || *t[i] == "MIN" || *t[i] == "NSH" || *t[i] == "STL" || *t[i] == "WPG")
				central.push_back(Map(*t[i], i));
			else if (*t[i] == "ANA" || *t[i] == "CGY" || *t[i] == "SEA" || *t[i] == "VGK" || *t[i] == "L.A" || *t[i] == "LAK" || *t[i] == "S.J" || *t[i] == "SJS" || *t[i] == "VAN" || *t[i] == "EDM")
				pacific.push_back(Map(*t[i], i));
		}
	}

	wxString GetDivName(int i)
	{
		if (Div::Atlantic == i) return Atlantic;
		if (Div::Central == i) return Central;
		if (Div::Metropolitan == i) return Metropolitan;
		if (Div::Pacific == i) return Pacific;

		return "NotFound";
	}
	wxVector<Map> atlantic, central, metropolitan, pacific;
};

struct Confname
{
	wxString Eastern = "Eastern";
	wxString Western = "Western";

	wxString GetConferenceName(int i)
	{
		if (Conf::Eastern == i) return Eastern;
		if (Conf::Western == i) return Western;
		return "Notfound";
	}

	int GetConferenceID(wxString s)
	{
		if (Eastern == s) return Conf::Eastern;
		if (Western == s) return Conf::Western;
		return -1;
	}

	int GetConferenceIdByDivId(int d)
	{
		if (d == Div::Atlantic || d == Div::Metropolitan)
			return Conf::Eastern;
		if (d == Div::Central || d == Div::Pacific)
			return Conf::Western;

		return -1;
	}
};

class Longname
{
public:
	Longname()
	{
		for (int i = 0; i < 32; ++i)
		{
			switch (i)
			{
			case 0: teams.push_back(&ana);
			case 1: teams.push_back(&ari);
			case 2: teams.push_back(&cgy);
			case 3: teams.push_back(&chi);
			case 4: teams.push_back(&col);
			case 5: teams.push_back(&dal);
			case 6: teams.push_back(&edm);
			case 7: teams.push_back(&la);
			case 8: teams.push_back(&min);
			case 9: teams.push_back(&nsh);
			case 10: teams.push_back(&sea);
			case 11: teams.push_back(&sj);
			case 12: teams.push_back(&stl);
			case 13: teams.push_back(&van);
			case 14: teams.push_back(&vgk);
			case 15: teams.push_back(&wpg);
			case 16: teams.push_back(&bos);
			case 17: teams.push_back(&buf);
			case 18: teams.push_back(&car);
			case 19: teams.push_back(&cbj);
			case 20: teams.push_back(&det);
			case 21: teams.push_back(&fla);
			case 22: teams.push_back(&mtl);
			case 23: teams.push_back(&nj);
			case 24: teams.push_back(&nyi);
			case 25: teams.push_back(&nyr);
			case 26: teams.push_back(&ott);
			case 27: teams.push_back(&phi);
			case 28: teams.push_back(&pit);
			case 29: teams.push_back(&tb);
			case 30: teams.push_back(&tor);
			case 31: teams.push_back(&wsh);
			}
		}
	}

	wxString GetLongname(int i)
	{
		if(teams.size() > i && i > -1) 
			return *teams[i];

		return "out of bounds";
	}

	int GetLongNameID(wxString s)
	{
		for (int i = 0; i < teams.size(); ++i)
		{
			if (*teams[i] == s)
				return i;
		}
		wxMessageBox("param in GetLongNameID in Longname class did not match. Param is: " + s);
		return -1;
	}

private:
	wxString bos = "Boston Bruins";
	wxString buf = "Buffalo Sabres";
	wxString det = "Detroit Redwings";
	wxString fla = "Florida Panthers";
	wxString mtl = "Montreal Canadiens";
	wxString ott = "Ottowa Senators";
	wxString tb = "Tampa Bay Lightning";
	wxString tor = "Toronto Maple Leafs";
	wxString car = "Carolina Hurricanes";
	wxString cbj = "Columbus Blue Jackets";
	wxString nj = "New Jersey Devils";
	wxString nyi = "New York Islanders";
	wxString nyr = "New York Rangers";
	wxString phi = "Philadelphia Flyers";
	wxString pit = "Pittsburgh Penguins";
	wxString wsh = "Washington Capitals";
	wxString ari = "Arizona Coyotes";
	wxString chi = "Chicago Blackhawks";
	wxString col = "Colorado Avalanche";
	wxString dal = "Dallas Stars";
	wxString min = "Minnesota Wild";
	wxString nsh = "Nashville Predators";
	wxString stl = "St. Louis Blues";
	wxString wpg = "Winnipeg Jets";
	wxString ana = "Anaheim Ducks";
	wxString cgy = "Calgary Flames";
	wxString edm = "Edmenton Oilers";
	wxString la = "Los Angeles Kings";
	wxString sj = "San Jose Sharks";
	wxString sea = "Seattle Kraken";
	wxString van = "Vancouver Canucks";
	wxString vgk = "Vegas Golden Knights";

	wxVector<wxString*> teams;
};

struct TeamData
{
	wxVector<wxString> sname;
	wxVector<wxString> lname;
	wxString divname = "";
	int divid = 0;
	wxString conf_name = "";
	int confid = 0;
	wxString teamlogo = "";
};

class TeamNames {
public:
	TeamNames()
	{
		
		for (int i = 0; i < 32; ++i)
		{
			switch (i)
			{
			case 0:
			{
				teams.push_back(&ANA);
				citienames.push_back("Anaheim");
				break;
			}
			case 1:
			{
				teams.push_back(&ARI);
				citienames.push_back("Arizona");
				break;
			}
			case 2:
			{
				teams.push_back(&CGY);
				citienames.push_back("Calgary");
				break;
			}
			case 3:
			{
				teams.push_back(&CHI);
				citienames.push_back("Chicago");
				break;
			}
			case 4:
			{
				teams.push_back(&COL);
				citienames.push_back("Colorado");
				break;
			}
			case 5:
			{
				teams.push_back(&DAL);
				citienames.push_back("Dallas");
				break;
			}
			case 6:
			{
				teams.push_back(&EDM);
				citienames.push_back("Edmonton");
				break;
			}
			case 7:
			{
				teams.push_back(&LA);
				citienames.push_back("Los Angeles");
				break;
			}
			case 8:
			{
				teams.push_back(&MIN);
				citienames.push_back("Minnesota");
				break;
			}
			case 9:
			{
				teams.push_back(&NSH);
				citienames.push_back("Nashville");
				break;
			}
			case 10:
			{
				teams.push_back(&SEA);
				citienames.push_back("Seattle");
				break;
			}
			case 11:
			{
				teams.push_back(&SJ);
				citienames.push_back("San Jose");
				break;
			}
			case 12:
			{
				teams.push_back(&STL);
				citienames.push_back("St. Louis");
				break;
			}
			case 13:
			{
				teams.push_back(&VAN);
				citienames.push_back("Vancouver");
				break;
			}
			case 14:
			{
				teams.push_back(&VGK);
				citienames.push_back("Vegas");
				break;
			}
			case 15:
			{
				teams.push_back(&WPG);
				citienames.push_back("Winnipeg");
				break;
			}
			case 16:
			{
				teams.push_back(&BOS);
				citienames.push_back("Boston");
				break;
			}
			case 17:
			{
				teams.push_back(&BUF);
				citienames.push_back("Buffalo");
				break;
			}
			case 18:
			{
				teams.push_back(&CAR);
				citienames.push_back("Carolina");
				break;
			}
			case 19:
			{
				teams.push_back(&CBJ);
				citienames.push_back("Columbus");
				break;
			}
			case 20:
			{
				teams.push_back(&DET);
				citienames.push_back("Detroit");
				break;
			}
			case 21:
			{
				teams.push_back(&FLA);
				citienames.push_back("Florida");
				break;
			}
			case 22:
			{
				teams.push_back(&MTL);
				citienames.push_back("Montreal");
				break;
			}
			case 23:
			{
				teams.push_back(&NJ);
				citienames.push_back("New Jersey");
				break;
			}
			case 24:
			{
				teams.push_back(&NYI);
				citienames.push_back("N.Y. Islanders");
				break;
			}
			case 25:
			{
				teams.push_back(&NYR);
				citienames.push_back("N.Y. Rangers");
				break;
			}
			case 26:
			{
				teams.push_back(&OTT);
				citienames.push_back("Ottawa");
				break;
			}
			case 27:
			{
				teams.push_back(&PHI);
				citienames.push_back("Philadelphia");
				break;
			}
			case 28:
			{
				teams.push_back(&PIT);
				citienames.push_back("Pittsburgh");
				break;
			}
			case 29:
			{
				teams.push_back(&TB);
				citienames.push_back("Tampa Bay");
				break;
			}
			case 30:
			{
				teams.push_back(&TOR);
				citienames.push_back("Toronto");
				break;
			}
			case 31:
			{
				teams.push_back(&WSH);
				citienames.push_back("Washington");
				break;
			}
			}
		}

		divname.AddTeams(teams);
	}

	wxString GetTeamLongName(wxString s)
	{
		return lname.GetLongname(GetShortNameID(s));
	}

	wxString GetTeamLongName(int i)
	{
		return lname.GetLongname(i);
	}
	
	wxString GetShortName(int i)
	{
		if (teams.size() > i && i > -1)
			return *teams[i];

		return "error";
	}

	int GetShortNameID(wxString s)
	{
		for (int i = 0; i < teams.size(); ++i)
		{
			if (*teams[i] == s)
				return i;
		}

		if (LAK == s) return Team::LA;
		if (SJS == s) return Team::SJ;
		if (TBL == s) return Team::TB;
		if (NJD == s) return Team::NJ;

	//	wxMessageBox("No team found in GetShortNameID in TeamNames param is: " + s);
		return -1;
	}

	int GetLongNameID(wxString s)
	{
		return lname.GetLongNameID(s);
	}

	int GetCitieNameID(wxString s)
	{
		for (size_t i = 0; i < citienames.size(); ++i)
		{
			wxString name = citienames[i];
			if (citienames[i] == s)
				return i;
		}

		wxMessageBox("Could not find citie name in TeamNames::GetCitieNameID!! Param is: " + s);
		return -1;
	}

	int GetConferenceID(wxString s)
	{
		return conf_name.GetConferenceID(s);
	}

	wxString GetConferenceName(int i)
	{
		return conf_name.GetConferenceName(i);
	}

	int GetDivID(wxString s)
	{
		return divname.GetDivID(s);
	}

	wxString GetDivName(int i)
	{
		return divname.GetDivName(i);
	}

	wxString GetTeamLogo(int i)
	{
		if (teams.size() > i && i > -1)
		{
			wxString t = "";
			if (Team::LA == i) t = "LAK";
			if (Team::SJ == i) t = "SJS";
			if (Team::TB == i) t = "TBL";
			if (Team::NJ == i) t = "NJD";

			if (!t.size()) t = *teams[i];
			return "SavedLogos/" + t + ".png";
		}

		return "NotFound";
	}
	/*
	TeamData GetDataTeam(int i)
	{
		TeamData td;
		td.sname.push_back(GetShortName(i));
		td.lname.push_back(GetTeamLongName(i));
	}

	TeamData GetDataLongName(wxString s)
	{

	}

	TeamData GetDataShorName(wxString s)
	{

	}*/

	int GetDivisionIdByTeamId(int t)
	{
		return divname.GetDivIdByTeamId(t);
	}

	int GetConferenceIdByDivisionId(int d)
	{
		return conf_name.GetConferenceIdByDivId(d);
	}

private:
	wxVector<wxString*> teams;
	wxVector<wxString> citienames;
	wxString ANA = "ANA";
	wxString ARI = "ARI";
	wxString CGY = "CGY";
	wxString CHI = "CHI";
	wxString COL = "COL";
	wxString DAL = "DAL";
	wxString EDM = "EDM";
	wxString LA = "L.A";
	wxString MIN = "MIN";
	wxString NSH = "NSH";
	wxString SEA = "SEA";
	wxString SJ = "S.J";
	wxString STL = "STL";
	wxString VAN = "VAN";
	wxString VGK = "VGK";
	wxString WPG = "WPG";
	wxString BOS = "BOS";
	wxString BUF = "BUF";
	wxString CAR = "CAR";
	wxString CBJ = "CBJ";
	wxString DET = "DET";
	wxString FLA = "FLA";
	wxString MTL = "MTL";
	wxString NJ = "N.J";
	wxString NYI = "NYI";
	wxString NYR = "NYR";
	wxString OTT = "OTT";
	wxString PHI = "PHI";
	wxString PIT = "PIT";
	wxString TB = "T.B";
	wxString TOR = "TOR";
	wxString WSH = "WSH";
	wxString LAK = "LAK";
	wxString SJS = "SJS";
	wxString NJD = "NJD";
	wxString TBL = "TBL";

	Longname lname;
	Confname conf_name;
	Divname divname;
};

struct Forwards
{
	Forwards* AddLine(NHLplayer* l, NHLplayer* c, NHLplayer* r);
	bool IsLineComplete() { if (left && center && right) return true; else return false; }
	bool IsDuplicatePlayer(NHLplayer*, NHLplayer*, NHLplayer*);
	NHLplayer* AddStartingPlayer(NHLplayer*);
	NHLplayer* AddStartingPlayer(NHLplayer*, char);
	void ResetInGameBockedShots();
	void AddGamePlayed();
	void AddOnIceAgainstGoal();
	void AddOnIceForGoal();
	bool HasPlayer(NHLplayer*);
	bool SwapPlayers(NHLplayer*, NHLplayer*);
	NHLplayer* ReplacePlayer(NHLplayer*, char);
	double GetLineStrength();
	double GetCorsiPercent() { return OnIce_corsipercent; }
	double GetShotsPerGame();
	void CalcValues();
	NHLplayer* left = nullptr;
	NHLplayer* center = nullptr;
	NHLplayer* right = nullptr;
	bool Left = false;
	bool Center = false;
	bool Right = false;
	long id = 0;
	int icetimerank = 0;
	double OnIce_corsipercent = 0.0;
};

struct Defense
{
	void AddLine(NHLplayer* l, NHLplayer* r) { d1 = l, d2 = r;  d2->ActivatePlayer(), d1->ActivatePlayer(); }
	bool IsLineComplete() { if (d1 && d2) return true; else return false; }
	bool IsDuplicatePlayer(NHLplayer*, NHLplayer*);
	double GetLineStrength();
	void ResetInGameBockedShots();
	void AddGamePlayed();
	void AddOnIceAgainstGoal();
	void AddOnIceForGoal();
	double GetCorsiPercent() { return OnIce_corsipercent; }
	void CalcValues();
	double GetPuckPosession() { return OnIce_corsipercent; }
	double GetShotsPerGame();
	bool HasPlayer(NHLplayer*);
	bool SwapPlayers(NHLplayer*, NHLplayer*);
	NHLplayer* ReplacePlayer(NHLplayer*, char);
	NHLplayer* d1 = nullptr;
	NHLplayer* d2 = nullptr;
	long id = 0;
	int icetimerank = 0;
	double OnIce_corsipercent = 0.0;
};

struct Lines
{
	void AddLine(NHLplayer*, NHLplayer*, NHLplayer*, int);
	Forwards* AddLine(NHLplayer*, NHLplayer*, NHLplayer*);
	void AddDefLine(NHLplayer*, NHLplayer*, int);
	bool AddDefLine(NHLplayer*, NHLplayer*);
	void AddGoalie(NHLplayer*);
	void ResetInGameBockedShots();
	void AddGamePlayed();
	NHLplayer* Replace(NHLplayer*, int, char, char);
	NHLplayer* ReplaceDef(NHLplayer*, int, char);
	NHLplayer* ReplaceGoalie(NHLplayer*);
	bool SwapPlayers(NHLplayer*, NHLplayer*, int);
	bool SwapDefPlayers(NHLplayer*, NHLplayer*, int);
	NHLplayer* AddStartingForward(NHLplayer*, int);
	NHLplayer* CycleForwards(NHLplayer*, int);
	Forwards* GetForwardLine(int);
	Forwards* GetNextFowardLine(Forwards*);
	Defense* GetNextDefenseLine(Defense*);
	bool IsForwardsComplete();
	bool IsDefenseComplete();
	double GetLineupValue();
	double GetShotsPerGame();
	void CalcValues();
	double GetLineupCorsi() { return CorsiPercent; }
	Forwards line1;
	Forwards line2;
	Forwards line3;
	Forwards line4;

	Defense paring1;
	Defense paring2;
	Defense paring3;

	NHLplayer* goalie = nullptr;
	double CorsiPercent = 0.0;
};

struct stringlines
{
	stringlines(long l, wxString p, int ir, wxString t, wxString f, wxString s, wxString las) : id(l), linetype(p), icetimerank(ir), team(t), first(f), second(s), last(las){}
	stringlines(long l, wxString p, int ir, wxString t, wxString f, wxString s) : id(l), linetype(p), icetimerank(ir), team(t), first(f), second(s) {}
	stringlines(long l, wxString p, double gs, wxString t, wxString f, wxString s, wxString las) : id(l), linetype(p), gameScore(gs), team(t), first(f), second(s), last(las) {}
	stringlines(long l, wxString p, double gs, wxString t, wxString f, wxString s) : id(l), linetype(p), gameScore(gs), team(t), first(f), second(s) {}
	int StringlineSize() { int i = 0; if (first != "") ++i; if (second != "") ++i; if (last != "") ++i; return i; }
	void SetPlayerIDs()
	{
		this->p1id = p1 ? p1->GetPlayerId() : 0;
		this->p2id = p2 ? p2->GetPlayerId() : 0;
		this->p3id = p3 ? p3->GetPlayerId() : 0;
	}
	void CalcGameScore() 
	{ 
		double gamescore1 = p1 ? p1->GetGameScore() : 0;
		double gamescore2 = p2 ? p2->GetGameScore() : 0;
		double gamescore3 = p3 ? p3->GetGameScore() : 0;

		gameScore = gamescore1 + gamescore2 + gamescore3;

		SetPlayerIDs();
	}
	bool IsSamePlayersForwardLine(stringlines* s)
	{
		bool one = false;
		bool two = false;
		bool three = false;
		if (s->p1 == this->p1 || s->p1 == this->p2 || s->p1 == this->p3)
			one = true;
		if (s->p2 == this->p1 || s->p2 == this->p2 || s->p2 == this->p3)
			two = true;
		if (s->p3 == this->p1 || s->p3 == this->p2 || s->p3 == this->p3)
			three = true;

		if (one && two && three)
			return true;

		return false;
	}
	long id = 0;
	wxString linetype = "";
	int icetimerank = 0;
	wxString team = "";
	wxString first = "";
	wxString second = "";
	wxString last = "";
	NHLplayer* p1 = nullptr;
	NHLplayer* p2 = nullptr;
	NHLplayer* p3 = nullptr;
	double gameScore = 0.0;
	long p1id = 0;
	long p2id = 0;
	long p3id = 0;
};

struct GameStats
{
	GameStats(bool ov, int mys, int ops, int mysa, int opsa, int mysb, int opsb, int myg, int opg, bool hg, int myid, int oppid) : 
		overtime(ov), myshots(mys), opponentshots(ops), myshotattempts(mysa), opponentshotattempts(opsa), myteam_blockedshots(mysb), oppontent_blockedshots(opsb),
		mygoals(myg), opponentgoals(opg), homegame(hg),
		myteamid(myid), opponent_team_id(oppid)
	{
		if (mygoals > opponentgoals)
		{
			outcome = GameOutcome::W;
			points = 2;
		}
		else if (mygoals < opponentgoals && overtime)
		{
			outcome = GameOutcome::OL;
			points = 1;
		}
		else
		{
			outcome = GameOutcome::LOSS;
			points = 0;
		}
	}
	bool overtime = false;
	int myshots = 0;
	int opponentshots = 0;
	int mygoals = 0;
	int opponentgoals = 0;
	int myshotattempts = 0;
	int opponentshotattempts = 0;
	int myteam_blockedshots = 0;
	int oppontent_blockedshots = 0;
	int outcome = -1;
	bool homegame = false;
	int points = 0;
	int myteamid = -1;
	int opponent_team_id = -1;
};

struct GameRecord
{
	GameRecord() {}
	int TeamId = -1;
	int gamesplayed = 0;
	wxVector<GameStats> Record;
	int wins = 0;
	int ovL = 0;
	int loss = 0;
	int points = 0;
	void AddGameOutCome(GameStats gs, wxString team)
	{
		gamesplayed++;
		int homewin = 0;
		int homeloss = 0;
		int roadwin = 0;
		int roadloss = 0;
		int totalwins = 0;
		int totallosses = 0;
		int overtimelosses = 0;
		int homeshots = 0;
		int awayshots = 0;
		Record.push_back(gs);
		if (gs.outcome == GameOutcome::W)
		{
			points += 2;
			++wins;
		}
		else if (gs.outcome == GameOutcome::LOSS) ++loss;
		else
		{
			points += 1;
			++ovL;
		}
	}

	int GetLastNumberOfWins(int number)
	{
		int wins = 0;
		if (number > Record.size())
			return 0;

		for (size_t i = Record.size() - number; i < Record.size(); ++i)
		{
			if (GameOutcome::W == Record[i].outcome)
				++wins;
		}

		return wins;
	}
};

struct Season_Schedule;
class NHL_Division;

class NHLTeam
{
public:
	NHLTeam() {}
	NHLTeam(wxString, wxString, wxString, int, int, NHL_Division*);
	bool AddPlayer(NHLplayer&);
	void AddPlayerFromSavedFile(NHLplayer&);
	void Save();
	void Retrieve(wxString&);
	NHLplayer* FindForwardWithLastName(wxString&);
	NHLplayer* FindDefWithLastName(wxString&);
	NHLplayer* FindPlayerWithID(long);
	void SortLines(bool b = true);
	void AddForwardStringLine(stringlines&);
	void AddDefStringLines(stringlines&);
	void AddGameOutcome(GameStats);
	void AddPlayoffGameOutcome(GameStats);
	void ResetPlayoffRecord() { playoffrecord = GameRecord(); }
	int GetGamesPlayed();
	void AddStats(Stats&);
	void SetLogo(wxBitmap&);
	NHLplayer* ReplaceStarter(NHLplayer*, int, char, char);
	bool SwapStarters(NHLplayer*, NHLplayer*, int);
	wxString GetTeamabbr(bool b = false);
	double GetTeamRating() { return Team_rating; }
	int GetTeamID() { return teamnum; }
	wxString GetTeamName() { return name; }
	Lines* GetLines() { return &lines; }
	GameRecord* GetGameRecord() { if (PlayoffSeed) return &playoffrecord;  return &gamerecord; }
	GameRecord* GetPlayoffSeriesRecord() { return &playoffrecord; }
	GameRecord* GetRegularSeasonRecord() { return &gamerecord; }
	wxBitmap* GetTeamLogo() { return &logo; }
	Season_Schedule* GetScheduledGame(int i) { if (i < season.size()) return &season[i]; else return nullptr; }
	int GetDivID() { return divnum; }
	//Check to see if player exists with last name...
	bool CheckLastName(wxString);
	void PurgePlayersWithNoStats();
	void CalibrateStats();
	void SetTeamForPlayoffs(int);
	void AppendPlayerInfotoListBox(wxListCtrl*);
	void ForwardInfotoListBox(wxListCtrl*);
	void DefenseInfotoListBox(wxListCtrl*);
	void GoalieInfotoListBox(wxListCtrl*);
	wxVector<NHLplayer>& GetForwards();
	wxVector<NHLplayer>& GetDefensemen();
	wxVector<NHLplayer>& GetGoalies();
	void SetPlayoffSeed(int s) { PlayoffSeed = s; }
	int GetPlayoffSeed() { return PlayoffSeed; }
private:
	void OptimizeLineup();
	void PushToBackup(NHLplayer*);
	void RemoveFromBackup(NHLplayer*);
	bool IsDuplicateStringLine(stringlines&);
	void SortStringLines();
	void SortPlayerVector(wxVector<NHLplayer>&);
	void AddBackups(wxVector<NHLplayer>&, wxVector<NHLplayer*>&);
	void AddToSpareForwards(NHLplayer*);
	void FindBestStarters();
	bool SwapForwards(NHLplayer*, NHLplayer*, int);
	bool SwapDefensemen(NHLplayer*, NHLplayer*, int);
	NHLplayer* FindForwardWithName(wxString);
	NHLplayer* FindDefenseWithName(wxString);
	NHLplayer* FindGoalieWithName(wxString);
	wxString name = "";
	wxString abbrname = "";
	wxString division = "";
	int teamnum = 0;
	int divnum = 0;
	wxBitmap logo;
	wxVector<NHLplayer> forwards;
	wxVector<NHLplayer> defensmen;
	wxVector<NHLplayer> goalies;
	Lines lines;
	wxVector<stringlines> stringforward;
	wxVector<stringlines> stringdefense;
	wxVector<NHLplayer*> spareforwards;
	wxVector<NHLplayer*> sparedefense;
	double Team_rating = 0.0;
	TeamNames teamnames;
	GameRecord gamerecord;
	GameRecord playoffrecord;
	wxVector<Season_Schedule> season;
	NHL_Division* m_parent_div = nullptr;
	int gamesplayed = 0;
	int PlayoffSeed = 0;

	//for calculating displaying players in listboxes...
	int namesize = 0;
};

struct Season_Schedule
{
public:
	Season_Schedule(wxDateTime T, NHLTeam* me, NHLTeam* opp, bool home) : gameday(T), myteam(me), opponent(opp), homegame(home)
	{

	};
	wxDateTime* GetDate() { return &gameday; }
	bool IsHomeGame() { return homegame; }
	bool IsTeamInGame(NHLTeam* T) 
	{
		if (!T)
			return false;

		if (T == opponent || T == myteam)
			return true;

		return false;
	}
	NHLTeam* GetAwayTeam() { return opponent; }
	NHLTeam* GetHomeTeam() { return myteam; }
private:
	bool homegame = false;
	wxDateTime gameday;
	NHLTeam* opponent = nullptr;
	NHLTeam* myteam = nullptr;
};

NHLplayer* GetPlayerDefensiveBias(Forwards*, Defense*, int);
NHLplayer* GetPlayerOffensiveBias(Forwards*, Defense*, int);
NHLplayer* GetPlayerNeutralBias(Forwards*, Defense*, int);

class Game
{
public:
	Game();
	void NewGame(NHLTeam*, NHLTeam*);
	void NewGame(void(*func)(GameWindow, int, void*, GameRecord*, wxString), void*, NHLTeam*, NHLTeam*);
	void NewPlayoffGame(void(*func)(GameWindow, int, void*, GameRecord*, wxString), void*, NHLTeam*, NHLTeam*);
	NHLTeam* NewPlayoffGame(NHLTeam*, NHLTeam*);
	void EndGame();
	bool IsGameInSession() { return isgameinsession; }
	int GetRecursions() { return recursions; }
private:
	void ChangeLines(Forwards*, Defense*, Forwards*, Defense*);
	void StartGame();
	void Faceoff(NHLplayer*, NHLplayer*);
	void Recieve(NHLplayer*, int, int);
	void SwitchPuck(bool, bool);
	void NextPlay();
	void Pass(NHLplayer*, int, int);
	void PassShoot();
	void Shoot();
	bool IsBlock();
	GameWindow IsGoalieStop();
	Forwards* GetOpposingForwardLine();
	Defense* GetOpposingDefenseLine();
	NHLplayer* GetOpposingGoalie();
	void AddShot();
	void AddShotOnGoal();
	void AddMissedShot();
	void AddBlockedShot();
	void AddGoal();
	void SetIceAreaToNeutral();
	void GenerateGoalAlert();
	void GenerateShotAlert();
	void DevUpdate(wxString);
	bool IsOnSameLine();
	void Recover(Forwards*, Defense*);
	void Recover(Forwards*, Defense*, Forwards*, Defense*, double&, double&, int);
	void ReboundRecover();
	bool IsHomePlayer(NHLplayer*);
	void GetNewIceArea(int, int, int, int offenseodds = 0, int neutralodds = 0, int defenseodds = 0);
	bool CheckOrSteal(NHLplayer*);
	void AddOnIceGoalStats();
	void Reset();
	void PassToCallBack(GameWindow, int, GameRecord*, wxString s = "");
	wxLongLong End();
	bool IsGameOnScreen = false;
	bool isgameinsession = false;

	//CALL BACK FUCTION FOR UPDATING SCREEN...
	void (*CallBack)(GameWindow, int, void*, GameRecord*, wxString) = nullptr;
	void* V = nullptr;

	NHLTeam* Home = nullptr;
	NHLTeam* Away = nullptr;
	Lines* homelines = nullptr;
	Lines* awaylines = nullptr;
	Forwards* AwayF = nullptr;
	Defense* AwayD = nullptr;
	Forwards* HomeF = nullptr;
	Defense* HomeD = nullptr;
	NHLplayer* homegoalie = nullptr;
	NHLplayer* awaygoalie = nullptr;
	Gen generator;
	int IceAreaHome = HomeIce::Neutral;
	int IceAreaAway = AwayIce::AwayNeutral;
	NHLplayer* haspuck = nullptr;
	NHLplayer* assistplayer = nullptr;
	NHLplayer* secondary_assist_player = nullptr;
	NHLplayer* shot_rebound = nullptr;
	bool Homepuck = false;
	bool Awaypuck = false;
	int homegoals = 0;
	int awaygoals = 0;
	int homeshots = 0;
	int awayshots = 0;
	int HomeMissedShots = 0;
	int AwayMissedShots = 0;
	int HomeShotsOnGoal = 0;
	int AwayShotsOnGoal = 0;
	int HomeBlockedShots = 0;
	int AwayBlockedShots = 0;
	NHLplayer* (*func)(Forwards*, Defense*, int);
	bool Dev = false;
	bool overtime = false;
	int* shotlimit = nullptr;
	int* otherteam_shotlimit = nullptr;
	int totalshots = 0;
	int otherteam_totalshots = 0;
	int homeoffensiveSwitches = 0;
	int awayoffensiveSwitches = 0;
	wxDateTime Posession;
	wxLongLong timespan = 0;
	wxLongLong homeposession = 0;
	wxLongLong awayposession = 0;
	bool endgame = false;
	int overtimetracker = 1;
	bool playoffs = false;
	int recursions = 0;
};

class NHL_Conference;

class NHL_Division
{
public:
	NHL_Division(int, int, NHL_Conference*);
	wxString Division = "";
	bool AddPlayer(NHLplayer&);
	bool AddLine(stringlines&, int);
	bool AddStats(Stats&, int);
	void SetLogo(wxBitmap&, int);
	void Save();
	void Retrieve(wxString&);
	wxString GetDivName() { return divname; }
	int GetDivId() { return division; }
	void SortLines();
	bool CheckLastName(wxString, int);
	void PurgePlayersWithNoStats();
	void CalibrateStats();
	void RecalcDivisionStandings();
	NHLTeam* GetTeam(int);

	//function for child of parent to call to get opponent...
	NHLTeam* GetTeam(int, int);
	void GetTeamLogos(wxVector<wxBitmap*>&);
	void GetTeams(wxVector<NHLTeam*>&);
	void GetForwards(wxVector<NHLplayer*>&);
	void GetDefensmen(wxVector<NHLplayer*>&);
	void GetGoalies(wxVector<NHLplayer*>&);
	wxVector<NHLTeam*> GetDivisionStandings() { return DivStandings; }
	wxVector<NHLTeam*> GetPlayoffTeams() { return PlayoffTeams; }
private:
	int conference = 0;
	int division = 0;
	wxString divname = "";
	wxString conf_name = "";
	wxVector<NHLTeam> teams;
	NHL_Conference* m_parent_conf = nullptr;
	wxVector<NHLTeam*> DivStandings;
	wxVector<NHLTeam*> PlayoffTeams;
};

class PlayoffSeeds;

struct PlayoffSeries
{
	PlayoffSeries(int r, NHLTeam* a, NHLTeam* h, PlayoffSeeds* parent) : round(r), home(h), away(a), m_parent(parent) 
	{ 
		if (home)
		{
			home->ResetPlayoffRecord();
			Home = true;
		}
		if (away)
		{
			Away = true;
			away->ResetPlayoffRecord();
		}
	}
	NHLTeam* home = nullptr;
	NHLTeam* away = nullptr;
	PlayoffSeeds* m_parent = nullptr;
	bool completed = false;
	int round = 0;
	bool Home = false;
	bool Away = false;
	// if loosing team is in this playoffseries it will return true; otherwise false;
	bool IsLoosingTeam(NHLTeam* loser)
	{
		if (loser == home)
		{
			completed = true;
			Home = false;
			return true;
		}
		else if (loser == away)
		{
			completed = true;
			Away = false;
			return true;
		}

		return false;
	}

	NHLTeam* GetWinningTeam() 
	{
		if (!IsSeriesComplete())
			return nullptr;

		if (Home) return home;
		
		return away;
	}
	NHLTeam* GetWesternTeam()
	{
		TeamNames tn;
		if (home && tn.GetConferenceIdByDivisionId(home->GetDivID()) == Conf::Western)
			return home;

		return away;
	}

	NHLTeam* GetEasternTeam()
	{
		TeamNames tn;
		if (home && tn.GetConferenceIdByDivisionId(home->GetDivID()) == Conf::Eastern)
			return home;

		return away;
	}
	bool IsSeriesComplete() { return completed; }
	NHLTeam* GetHomeTeam() { return home; }
	NHLTeam* GetAwayTeam() { return away; }
	PlayoffSeeds* GetParent() { return m_parent; }
	void AddTeamMovingOn(NHLTeam* T)
	{
		if (!home)
		{
			home = T;
			Home = true;
		}
		else
		{
			away = T;
			Away = true;
		}
		if (home && away)
		{
			home->ResetPlayoffRecord();
			away->ResetPlayoffRecord();
			NHLTeam* temp = nullptr;
			if (round < 3)
			{
				if (home->GetPlayoffSeed() > away->GetPlayoffSeed())
				{
					temp = home;
					home = away;
					away = temp;
				}
			}
			else
			{
				if (home->GetGameRecord()->points < away->GetRegularSeasonRecord()->points)
				{
					temp = home;
					home = away;
					away = temp;
				}
				else if (home->GetGameRecord()->wins < away->GetRegularSeasonRecord()->wins)
				{
					temp = home;
					home = away;
					away = temp;
				}
			}
		}
	}
};

class PlayoffSeeds
{
public:
	PlayoffSeeds() {}
	virtual PlayoffSeries* GetPacificSeries(int, int) { return nullptr; } 
	virtual PlayoffSeries* GetCentralSeries(int, int) { return nullptr; } 
	virtual PlayoffSeries* GetAtlanticSeries(int, int) { return nullptr; } 
	virtual PlayoffSeries* GetMetropolitanSeries(int, int) { return nullptr; } 
	virtual PlayoffSeries* GetThirdRound() { return nullptr; }
	virtual void AddOutcome(NHLTeam*, NHLTeam*, int) {}
};

class PlayoffSeedsWestern : public PlayoffSeeds
{
public:
	PlayoffSeedsWestern(NHLTeam* firstp, NHLTeam* secondp, NHLTeam* thirdp, NHLTeam* firstc, NHLTeam* secondc, NHLTeam* thirdc, NHLTeam* w1, NHLTeam* w2) : firstSeed_pacific(firstp),
		secondseed_pacific(secondp), thirdseed_pacific(thirdp), firstSeed_central(firstc), secondseed_central(secondc), thirdseed_central(thirdc),
		wildcard1(w1), wildcard2(w2), pacific1(1, nullptr, firstSeed_pacific, this), pacific2(1, thirdseed_pacific, secondseed_pacific, this), central1(1, nullptr, firstSeed_central, this),
		central2(1, thirdseed_central, secondseed_central, this), second_round_pacific(2, nullptr, nullptr, this), second_round_central(2, nullptr, nullptr, this), 
		third_round_western(3, nullptr, nullptr, this)
	{
		firstSeed_pacific->SetTeamForPlayoffs(1);
		firstSeed_central->SetTeamForPlayoffs(1);
		secondseed_pacific->SetTeamForPlayoffs(2);
		secondseed_central->SetTeamForPlayoffs(2);
		thirdseed_pacific->SetTeamForPlayoffs(3);
	    thirdseed_central->SetTeamForPlayoffs(3);
		wildcard1->SetTeamForPlayoffs(4);
		wildcard2->SetTeamForPlayoffs(5);
		if (firstSeed_pacific->GetRegularSeasonRecord()->points > firstSeed_central->GetRegularSeasonRecord()->points)
		{
			pacific1.AddTeamMovingOn(wildcard2);
			central1.AddTeamMovingOn(wildcard1);
		}
		else if (firstSeed_central->GetRegularSeasonRecord()->points > firstSeed_pacific->GetRegularSeasonRecord()->points)
		{
			pacific1.AddTeamMovingOn(wildcard1);
			central1.AddTeamMovingOn(wildcard2);
		}
		else if (firstSeed_pacific->GetRegularSeasonRecord()->wins > firstSeed_central->GetRegularSeasonRecord()->wins)
		{
			pacific1.AddTeamMovingOn(wildcard2);
			central1.AddTeamMovingOn(wildcard1);
		}
		else
		{
			pacific1.AddTeamMovingOn(wildcard1);
			central1.AddTeamMovingOn(wildcard2);
		}
	}

	NHLTeam* firstSeed_pacific = nullptr;
	NHLTeam* firstSeed_central = nullptr;
	NHLTeam* secondseed_pacific = nullptr;
	NHLTeam* secondseed_central = nullptr;
	NHLTeam* thirdseed_pacific = nullptr;
	NHLTeam* thirdseed_central = nullptr;
	NHLTeam* wildcard1 = nullptr;
	NHLTeam* wildcard2 = nullptr;

	virtual PlayoffSeries* GetPacificSeries(int series, int round) wxOVERRIDE
	{
		if (round == 1)
		{
			switch (series)
			{
			case 0: return &pacific1;
			case 1: return &pacific2;
			}
			wxFAIL_MSG("switch did not catch param in PlayoffSeedsWestern::GetPacificSeries!");
			return nullptr;
		}
		else if (round == 2)
		{
			return &second_round_pacific;
		}
		wxFAIL_MSG("else if did not catch param in PlayoffSeedsWestern::GetPacificSeries!");
		return nullptr;
	}

	virtual PlayoffSeries* GetCentralSeries(int series, int round) wxOVERRIDE
	{
		if (round == 1)
		{
			switch (series)
			{
			case 0: return &central1;
			case 1: return &central2;
			}
			wxFAIL_MSG("switch did not catch param in PlayoffSeedsWestern::GetCentralSeries!");
			return nullptr;
		}
		else if (round == 2)
		{
			return &second_round_central;
		}
		wxFAIL_MSG("else if did not catch param in PlayoffSeedsWestern::GetCentralSeries!");
		return nullptr;
	}

	virtual PlayoffSeries* GetThirdRound()
	{
		return &third_round_western;
	}

	virtual void AddOutcome(NHLTeam* winner, NHLTeam* loser, int round) wxOVERRIDE
	{
		if (round == 1)
		{
			if (pacific1.IsLoosingTeam(loser))
			{
				second_round_pacific.AddTeamMovingOn(pacific1.GetWinningTeam());
				return;
			}
			if (pacific2.IsLoosingTeam(loser))
			{
				second_round_pacific.AddTeamMovingOn(pacific2.GetWinningTeam());
				return;
			}
			if (central1.IsLoosingTeam(loser))
			{
				second_round_central.AddTeamMovingOn(central1.GetWinningTeam());
				return;
			}
			if (central2.IsLoosingTeam(loser))
			{
				second_round_central.AddTeamMovingOn(central2.GetWinningTeam());
				return;
			}
		}
		else if (round == 2)
		{
			if (second_round_pacific.IsLoosingTeam(loser))
			{
				third_round_western.AddTeamMovingOn(second_round_pacific.GetWinningTeam());
				return;
			}
			else if (second_round_central.IsLoosingTeam(loser))
			{
				third_round_western.AddTeamMovingOn(second_round_central.GetWinningTeam());
				return;
			}
		}
	}

	PlayoffSeries pacific1;
	PlayoffSeries pacific2;
	PlayoffSeries central1;
	PlayoffSeries central2;
	PlayoffSeries second_round_pacific;
	PlayoffSeries second_round_central;
	PlayoffSeries third_round_western;
};

class PlayoffSeedsEastern : public PlayoffSeeds
{
public:
	PlayoffSeedsEastern(NHLTeam* firsta, NHLTeam* seconda, NHLTeam* thirda, NHLTeam* firstm, NHLTeam* secondm, NHLTeam* thirdm, NHLTeam* w1, NHLTeam* w2) : firstSeed_atlantic(firsta),
		secondseed_atlantic(seconda), thirdseed_atlantic(thirda), firstSeed_metropolitan(firstm), secondseed_metropolitan(secondm), thirdseed_metropolitan(thirdm),
		wildcard1(w1), wildcard2(w2), first_round_atlantic1(1, nullptr, firstSeed_atlantic, this), first_round_atlantic2(1, thirdseed_atlantic, secondseed_atlantic, this),
		first_round_metropolitan1(1, nullptr, firstSeed_metropolitan, this), first_round_metropolitan2(1, thirdseed_metropolitan, secondseed_metropolitan, this),
		second_round_atlantic(2, nullptr, nullptr, this), second_round_metropolitan(2, nullptr, nullptr, this), third_round_eastern(3, nullptr, nullptr, this)
	{
		firstSeed_atlantic->SetTeamForPlayoffs(1);
		firstSeed_metropolitan->SetTeamForPlayoffs(1);
		secondseed_atlantic->SetTeamForPlayoffs(2);
		secondseed_metropolitan->SetTeamForPlayoffs(2);
		thirdseed_atlantic->SetTeamForPlayoffs(3);
		thirdseed_metropolitan->SetTeamForPlayoffs(3);
		wildcard1->SetTeamForPlayoffs(4);
		wildcard2->SetTeamForPlayoffs(5);

		if (firstSeed_atlantic->GetRegularSeasonRecord()->points > firstSeed_metropolitan->GetRegularSeasonRecord()->points)
		{
			first_round_atlantic1.AddTeamMovingOn(wildcard2);
			first_round_metropolitan1.AddTeamMovingOn(wildcard1);
		}
		else if (firstSeed_metropolitan->GetRegularSeasonRecord()->points > firstSeed_atlantic->GetRegularSeasonRecord()->points)
		{
			first_round_atlantic1.AddTeamMovingOn(wildcard1);
			first_round_metropolitan1.AddTeamMovingOn(wildcard2);
		}
		else if (firstSeed_atlantic->GetRegularSeasonRecord()->wins > firstSeed_metropolitan->GetRegularSeasonRecord()->wins)
		{
			first_round_atlantic1.AddTeamMovingOn(wildcard2);
			first_round_metropolitan1.AddTeamMovingOn(wildcard1);
		}
		else
		{
			first_round_atlantic1.AddTeamMovingOn(wildcard1);
			first_round_metropolitan1.AddTeamMovingOn(wildcard2);
		}
	}

	NHLTeam* firstSeed_atlantic = nullptr;
	NHLTeam* firstSeed_metropolitan = nullptr;
	NHLTeam* secondseed_atlantic = nullptr;
	NHLTeam* secondseed_metropolitan = nullptr;
	NHLTeam* thirdseed_atlantic = nullptr;
	NHLTeam* thirdseed_metropolitan = nullptr;
	NHLTeam* wildcard1 = nullptr;
	NHLTeam* wildcard2 = nullptr;

	virtual PlayoffSeries* GetAtlanticSeries(int series, int round) wxOVERRIDE
	{
		if (round == 1)
		{
			switch (series)
			{
			case 0: return &first_round_atlantic1;
			case 1: return &first_round_atlantic2;
			}
			wxFAIL_MSG("switch did not catch param in PlayoffSeedsEastern::GetAtlanticSeries!");
			return nullptr;
		}
		else if (round == 2)
		{
			return &second_round_atlantic;
		}
		wxFAIL_MSG("else if did not catch param in PlayoffSeedsEastern::GetAtlanticSeries!");
		return nullptr;
	}

	virtual PlayoffSeries* GetMetropolitanSeries(int series, int round) wxOVERRIDE
	{
		if (round == 1)
		{
			switch (series)
			{
			case 0: return &first_round_metropolitan1;
			case 1: return &first_round_metropolitan2;
			}
			wxFAIL_MSG("switch did not catch param in PlayoffSeedsEastern::GetMetropolitanSeries!");
			return nullptr;
		}
		else if (round == 2)
		{
			return &second_round_metropolitan;
		}
		wxFAIL_MSG("else if did not catch param in PlayoffSeedsEastern::GetMetropolitanSeries!");
		return nullptr;
	}

	virtual PlayoffSeries* GetThirdRound()
	{
		return &third_round_eastern;
	}

	virtual void AddOutcome(NHLTeam* winner, NHLTeam* loser, int round) wxOVERRIDE
	{
		if (round == 1)
		{
			if (first_round_atlantic1.IsLoosingTeam(loser))
			{
				second_round_atlantic.AddTeamMovingOn(first_round_atlantic1.GetWinningTeam());
				return;
			}
			if (first_round_atlantic2.IsLoosingTeam(loser))
			{
				second_round_atlantic.AddTeamMovingOn(first_round_atlantic2.GetWinningTeam());
				return;
			}
			if (first_round_metropolitan1.IsLoosingTeam(loser))
			{
				second_round_metropolitan.AddTeamMovingOn(first_round_metropolitan1.GetWinningTeam());
				return;
			}
			if (first_round_metropolitan2.IsLoosingTeam(loser))
			{
				second_round_metropolitan.AddTeamMovingOn(first_round_metropolitan2.GetWinningTeam());
				return;
			}
		}
		else if (round == 2)
		{
			if (second_round_atlantic.IsLoosingTeam(loser))
			{
				third_round_eastern.AddTeamMovingOn(second_round_atlantic.GetWinningTeam());
				return;
			}
			else if (second_round_metropolitan.IsLoosingTeam(loser))
			{
				third_round_eastern.AddTeamMovingOn(second_round_metropolitan.GetWinningTeam());
				return;
			}
		}
	}

	PlayoffSeries first_round_atlantic1;
	PlayoffSeries first_round_atlantic2;
	PlayoffSeries first_round_metropolitan1;
	PlayoffSeries first_round_metropolitan2;
	PlayoffSeries second_round_atlantic;
	PlayoffSeries second_round_metropolitan;
	PlayoffSeries third_round_eastern;
};

class NHL_Conference
{
public:
	NHL_Conference(int, int, int, NHL_Conference*);
	~NHL_Conference();
	wxString conf_name = "";
	bool AddPlayer(NHLplayer&);
	bool AddLine(stringlines&, int, int);
	void Save();
	void Retrieve();
	void SortLines();
	bool CheckLastName(wxString, int, int);
	bool AddStats(Stats&, int);
	void SetLogo(wxBitmap&, int, int);
	void PurgePlayersWithNoStats();
	void CalibrateStats();
	void GetTeamLogos(wxVector<wxBitmap*>&);
	void GetTeams(wxVector<NHLTeam*>&);
	void RecalcStandings();
	NHLTeam* GetTeam(int, int);
	PlayoffSeeds* GetPlayoffTeams();
	wxVector<NHLTeam*> GetDivStandings(Div);

	//call back for division to find opponent for one of its teams that called the divisions call back to fill Season_Schedule game...
	NHLTeam* GetTeamOpponent(int, int);
	NHL_Division* GetDiv1() { return &div1; }
	NHL_Division* GetDiv2() { return &div2; }
private:
	int conference = 0;
	NHL_Division div1, div2;
	wxVector<NHLplayer*> forwards;
	wxVector<NHLplayer*> defensemen;
	wxVector<NHLplayer*> goalies;
	NHL_Conference* other_Conference = nullptr;
	wxVector<NHLTeam*> standings;
	PlayoffSeedsEastern* playoff_eastern = nullptr;
	PlayoffSeedsWestern* playoff_western = nullptr;
};

class NHL_League
{
public:
	NHL_League(void (*SeasonGameReady)(wxWindow*, NHLTeam*, NHLTeam*, int, int), wxWindow*);
	NHL_Conference Eastern;
	NHL_Conference Western;
	void ParseSkaters(wxString&, wxString&, wxString&);
	void AddPlayerBio(wxString&);
	void AddLines(wxString&);
	void AddStats(wxString&);
	void AddGoalieStats(wxString&);
	void CheckForHyphen(wxVector<wxString>&, int);
	void Save();
	void Retrieve();
	void SortLines();
	bool Hyphenated(wxString, int);
	void PurgePlayersWithNoStats();
	void CalibrateStats();
	void SetLogo(wxBitmap&, int);
	void StartGame(void (*func)(GameWindow, int, void*, GameRecord*, wxString), void*, NHLTeam*, NHLTeam*);
	void StartPlayoffGame(void (*func)(GameWindow, int, void*, GameRecord*, wxString), void*, NHLTeam*, NHLTeam*);
	void EndGame();
	bool IsQuarterWayThroughSeason();
	void StartSeason(NHLTeam*);
	bool ContinueSeason();
	void SetMyPlayoffSeriesOutCome(NHLTeam*, NHLTeam*);
	void RunPlayoffs();
	NHLTeam* RunPlayoffSeries(PlayoffSeries*);
	NHLTeam* GetMYSeasonTeam() { return myseason_team; }
	NHLTeam* GetTeam(int);
	wxVector<NHLplayer*>& GetAllSkaters();
	wxVector<NHLplayer*>& GetAllForwards();
	wxVector<NHLplayer*>& GetAllDefensemen();
	wxVector<NHLplayer*>& GetAllGoalies();
	wxVector<NHLTeam*> GetPacificStandings();
	wxVector<NHLTeam*> GetCentralStandings();
	wxVector<NHLTeam*> GetMetropolitanStandings();
	wxVector<NHLTeam*> GetAtlanticStandings();
	PlayoffSeries* GetPlayoffSeries(PlayoffSeriesPair);
private:
	void GetNextSchedule();
	bool RunSeason();
	void CollectPlayers();
	void AddPlayerVectors(NHL_Division*);
	void CalibrateRatings();
	void AddPlayerToTeam(NHLplayer&);
	void AddLine(stringlines&, int);
	void AddPlayerStats(Stats&, int);

	void (*callback)(wxWindow*, NHLTeam*, NHLTeam*, int, int) = nullptr;
	wxWindow* V = nullptr;

	TeamNames teamnames;
	wxVector<NHLplayer*> allskaters;
	wxVector<NHLplayer*> forwards;
	wxVector<NHLplayer*> defensemen;
	wxVector<NHLplayer*> goalies;
	wxVector<NHLTeam*> Teams;
	wxVector<wxBitmap*> logo;
	NHL_Division* Atl = nullptr;
	NHL_Division* Ctr = nullptr;
	NHL_Division* Mtp = nullptr;
	NHL_Division* Pcf = nullptr;
	Game game;
	NHLTeam* myseason_team = nullptr;
	int schedule = 0;
	wxVector<Season_Schedule*> sc;
	PlayoffSeedsEastern* playoff_eastern = nullptr;
	PlayoffSeedsWestern* playoff_western = nullptr;
	int playoffround = 0;
	PlayoffSeeds* myplayoffconference = nullptr;
	PlayoffSeries* myplayoffseries = nullptr;
	NHLTeam* western_champs = nullptr;
	NHLTeam* eastern_champs = nullptr;
	bool gameOnScreen = false;
	bool seriesOnScreen = false;
};

struct ForwardLine
{
	NHLplayer* left = nullptr;
	NHLplayer* center = nullptr;
	NHLplayer* right = nullptr;
};

struct DefenseLine
{
	NHLplayer* dleft = nullptr;
	NHLplayer* dright = nullptr;
};