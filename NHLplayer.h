#pragma once
#include "wx/event.h"
#include "Webdata.h"
#include "wx/txtstrm.h"
#include "wx/wfstream.h"
#include "wx/hashmap.h"
#include "wx/listctrl.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "wx/tipwin.h"
#include "wx/notifmsg.h"
#include "wx/bannerwindow.h"
#include "wx/numformatter.h"
#include "wx/srchctrl.h"
#include <random>


constexpr auto STANDARD_DATE = "%m/%d/%G";
constexpr auto SavedFile = "SavedFiles/";

enum HomeIce
{
	Offensive = 0,
	Neutral,
	Defensive
};

enum AwayIce
{
	AwayDefensive = 0,
	AwayNeutral,
	AwayOffensive
};


enum Position {
	C = 'C',
	R = 'R',
	L = 'L',
	D = 'D',
	G = 'G',
	U = 'U'
};

enum GameOutcome
{
	W = 1,
	LOSS = -1,
	OL = 0
};

enum HomeAway
{
	HOME = 'H',
	AWAY = 'A'
};

//functions for converting doubles into strings...
wxString GetStringValue(double, int);

//helper function for getting the nd th rd after the correct number e.g. 3rd, 2nd, 30th ect...
wxString GetOrdinal(int);

wxStaticText* InitStaticText(wxWindow*, wxWindowID, wxString, int, wxFontFamily, wxFontWeight, wxColour, wxPoint point = wxDefaultPosition, wxSize size = wxDefaultSize);

struct Distributor
{
	Distributor(int i, int j) : dist(i, j) {}
	std::uniform_int_distribution<int> dist;
};

struct Gen
{
	Gen() : generator(rd()), engine(rd()) {}

	int getnum(Distributor& d) {
		return d.dist(generator);
	}
	std::mt19937 generator;
	std::default_random_engine engine;
	std::random_device rd;
};

int Pull(Gen&, int, int);

struct PlayerValue
{
	void addOffense(int gs, int g, int pa, int sa, double fp, double oniceforgoals, int sog, double onAgoals, int gp);
	void addDefense(int gs, int bs, int takeaways, int hits, double fp, int giveaways, double onAgoals, int gp);
	void AddGoalieStats();
	void CalcValues(char);
	double overall = 0.0;
	double offense = 0.0;
	double defense = 0.0;
	int league_rank = 0;
	int team_rank = 0;

//	double roverall = 0.0;
//	double roffense = 0.0;
//	double rdefense = 0.0;
};


class Stats 
{
public:
	Stats();
	Stats(int, int, char, char, int, wxString, wxString);
	~Stats();
	void CalcValues();
	void Add(Stats&);
	void Average(int);
	void ActivateHomeAdvantage();
	void DeactivateHomeAdvantage();
	void Save(wxTextOutputStream&);
	void Retrieve(wxTextInputStream& in);
public:
	int age = 0;
	long id = 0;
	wxString year = "";
	wxString team = "";
	wxString name = "";
	int season = 0;
	char shot = 'R';
	char Pos = 'C';
	int I_F_primaryAssists = 0;
	int I_F_secondaryAssists = 0;
	int I_F_shotsOnGoal = 0;
	int I_F_missedShots = 0;
	int I_F_blockedShotAttempts = 0;
	double shotsonGoalPercent = 0.0;
	int I_F_shotAttempts = 0;
	int penaltiesDrawn = 0;
	int I_F_points = 0;
	int	I_F_goals = 0;
	int	I_F_rebounds = 0;
	int	I_F_reboundGoals = 0, I_F_hits = 0, I_F_takeaways = 0, I_F_giveaways = 0;
	double takeaway_giveaway = 0;
	int faceoffsWon = 0, faceoffsLost = 0;
	double faceoffPerc = 0.0;
	int games_played = 0;
	int blockedshots = 0;
	double gameScore = 0.0, onIce_corsiPercentage = 0.0, onIce_fenwickPercentage = 0.0, OnIce_F_Goals = 0.0, OnIce_F_ShotAttempts = 0.0, OnIce_A_goals = 0.0;
	double shotsPerGame = 0.0;
	double BlockedShotsPerGame = 0.0;
	

	PlayerValue pv;

	double save_percent = 0.0;
	double goals_allowed = 0.0;
	double ongoalshots = 0.0;
	double rebounds = 0.0;
	double freeze = 0.0;
	double reboundperc = 0.0;
	double freezeperc = 0.0;
	double goals_per_game = 0.0;

	wxVector<double> homeadvantage;
};

struct GoalieValue
{
	double rebound = 0.0;
	double overall = 0.0;
};

class NHLplayer
{
public:
	NHLplayer();
	NHLplayer(long&, wxString&, char&, wxString&, wxDateTime&, double&, wxString&, wxString&, char&, int&);
	~NHLplayer();
	void AddID(long&);
	void AddYear(wxString&);
	int FindYearStats(wxString&);
	void AddName(wxString&);
	bool IsPlayerId(long&);
	bool IsPlayerByName(wxString&);
	void AddTeam(wxString&);
	void AddPosition(wxString&);
	void AddGamesPlayed(int&);
	void AddTimeOnIce(int&);
	void AddStats(Stats&);
	void CalibrateStats();
	void SetYearEndStats();
	wxString GetTeam() { return team; }
	char GetPosition() { return position; }
	wxString GetName() { return name; }
	void Save(wxTextOutputStream&);
	void Retrieve(wxTextInputStream& in);
	int IsStarter() { return starting; }
	int IsStatsActive() { return statactive; }
	void ActivatePlayer() { starting = 1; }
	void DeactivatePlayer() { starting = 0; }
	void ResetInGameBockedShots() { ingame_blockedshot = 0; }
	void SetPlayoffsTrue() { playoffs = true; }

	//setters..
	void SetOnIceForShots();
	void SetOnIceAgainstShots();
	void SetOnIceAgainstGoal();
	void SetOnIceForGoal();
	void SetFaceoffWin();
	void SetFaceoffLoss();
	void SetGamePlayed();
	void SetGoal();
	void SetAssist();
	void SetSecondaryAssist();
	void SetShotAttempt();
	void SetShotAttemptBlocked();
	void SetBlockedShot();
	void SetShotOnGoal();
	void SetMissedShot();
	void SetGaveUpPuck();
	void SetStolePuck();
	void SetTimeOfPossession(int);
	void SetTimeWithoutPossession(int);
	void SetSave();
	void SetRebound();
	void SetFreeze();
	void SetGoalAllowed();

	//getters...
	Stats* GetOverallAverageStats() { return &stats; }
	Stats* GetLastSeasonStats() { if (years.size()) return &years[years.size() - 1]; else return nullptr; }
	Stats* GetCurrentSeasonStats() { return &currentyear; }
	double GetGameScore() { if (position != 'G') return stats.gameScore; return stats.save_percent; }
	double GetPlayerOverallRating() { if (position != 'G') return stats.pv.overall; return stats.save_percent; }
	double GetShotOnGoalPercent() { return stats.shotsonGoalPercent; }
	double GetFaceOffPercent() { return stats.faceoffPerc; }
	double GetOffenseRating() { return pv.offense; }
	double GetDefenseRating() { return pv.defense; }
	double GetCorsiPercent() { return stats.onIce_corsiPercentage; }
	double GetWeight() { return weight; }
	double GetTakeaway_Giveaway() { return stats.takeaway_giveaway; }
	double GetBlockedShotsPerGame() { return stats.BlockedShotsPerGame; }
	double GetShotsPerGame() { return stats.shotsPerGame; }
	double GetReboundPerc() { return stats.reboundperc; }
	double GetFreezePerc() { return stats.freezeperc; }
	long GetPlayerId() { return id; }
	char GetShot() { return shot; }
	int GetGoals() { return stats.I_F_goals; }
	int GetInGameBlockedShots() { return ingame_blockedshot; }
	int GetCurrentYearGoals() { if (playoffs) return PlayoffStats.I_F_goals; return currentyear.I_F_goals; }
	int GetCurrentYearAssists() { if (playoffs) return PlayoffStats.I_F_primaryAssists + PlayoffStats.I_F_secondaryAssists;  return currentyear.I_F_primaryAssists + currentyear.I_F_secondaryAssists; }
	int GetAssists() { return stats.I_F_primaryAssists + stats.I_F_secondaryAssists; }
	int GetAge() { return age; }

	//playoff getters...
	int GetPlayoffGoals() { return PlayoffStats.I_F_goals; }
	int GetPlayoffAssists() { return PlayoffStats.I_F_primaryAssists + PlayoffStats.I_F_secondaryAssists; }

	//string form getters...
	wxString GetGameScore_String() { return wxNumberFormatter::ToString(stats.gameScore, 2); }
	wxString GetPlayerOverallRating_String() { if (position != 'G') return  wxNumberFormatter::ToString(stats.pv.overall, 2); return  wxNumberFormatter::ToString(stats.save_percent, 3); }
	wxString GetCurrentOverallRating_String(){ if (position != 'G') return  wxNumberFormatter::ToString(currentyear.pv.overall, 2); return  wxNumberFormatter::ToString(currentyear.save_percent, 3); }
	wxString GetCurrentShotOnGoalPercent_String() { return  wxNumberFormatter::ToString(currentyear.shotsonGoalPercent, 2); }
	wxString GetCurrentFaceOffPercent_String() { return  wxNumberFormatter::ToString(currentyear.faceoffPerc, 2); }
	wxString GetCurrentOffenseRating_String() { return  wxNumberFormatter::ToString(currentyear.pv.offense, 2); }
	wxString GetCurrentDefenseRating_String() { return  wxNumberFormatter::ToString(currentyear.pv.defense, 2); }
	wxString GetCorsiPercent_String() { return  wxNumberFormatter::ToString(stats.onIce_corsiPercentage, 2); }
	wxString GetWeight_String() { return  wxNumberFormatter::ToString(weight, 2); }
	wxString GetTakeaway_Giveaway_String() { return  wxNumberFormatter::ToString(stats.takeaway_giveaway, 2); }
	wxString GetBlockedShotsPerGame_String() { return  wxNumberFormatter::ToString(stats.BlockedShotsPerGame, 2); }
	wxString GetShotsPerGame_String() { return  wxNumberFormatter::ToString(stats.shotsPerGame, 2); }
	wxString GetReboundPerc_String() { return  wxNumberFormatter::ToString(stats.reboundperc, 2); }
	wxString GetFreezePerc_String() { return  wxNumberFormatter::ToString(stats.freezeperc, 2); }
	wxString GetGoalsAllowedPerGame_String(bool CurrentYear = true);

private:
	wxString name = "";
	wxString team = "";
	wxString nationality = "";
	wxString hieght = "";
	char position = Position::C;
	char shot = Position::R;
	double weight = 150;
	int age = 0;
	int number;
	wxVector<Stats> years;
	Stats stats;
	Stats PlayoffStats;
	Stats currentyear;
	long id = 0;
	wxDateTime birthday;
	int starting = 0;
	int statactive = 0;
	int ingame_blockedshot = 0;
	int playoffs = false;
	PlayerValue pv;
};

