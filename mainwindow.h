#pragma once
#include "NHL_League.h"
#include "GameFrame.h"

class mainwindow;

constexpr double Proprortion = 36.0 / 17.0;

class Canvas : public wxWindow
{
public:
	Canvas(wxWindow*, wxWindowID, wxPoint, wxString, wxSize);
	virtual ~Canvas();
	void OnMouseLeftDown(wxMouseEvent&);
	void OnMouseEnter(wxMouseEvent&);
	void OnMouseLeave(wxMouseEvent&);
private:
	void OnPaint(wxPaintEvent&);
	void OnDynamicPaint(int);
	wxWindow* parent = nullptr;
	bool mousedown = false;
	bool firstpass = false;
	wxString text;
};
class Bracketleg : public wxWindow
{
public:
	Bracketleg(wxWindow*, wxString, wxWindowID, wxPoint, wxSize, int, int, wxColour color = wxColour(0, 0, 0));
	void OnPaint(wxPaintEvent&);
private:
	wxString team = "";
	wxWindow* m_parent = nullptr;
	wxSize m_mySize;
	int direction = 0;
	int height_ratio = 0;
	int width_ratio = 0;
	int mirror = 0;
	wxColour m_textColor;
};

class PlayoffBracketView : public wxFrame
{
public:
	PlayoffBracketView(wxWindow*, wxWindowID, wxSize, wxVector<PlayoffSeries*>, wxVector<PlayoffSeries*>, NHLTeam* T = nullptr);
	void OnClose(wxCloseEvent&);
private:
	Bracketleg* PositionBracket(Bracketleg*, BracketlegPosition, BracketlegPosition, wxString, int, int);
	wxString GetTeamName(wxVector<PlayoffSeries*>&, int);
	// western
	// pacific
	Bracketleg* pacific_first_seed = nullptr;
	Bracketleg* pacific_second_seed = nullptr;
	Bracketleg* pacific_third_seed = nullptr;
	// pacific second round
	Bracketleg* pacific_second_round_top = nullptr;
	Bracketleg* pacific_second_round_bottom = nullptr;
	// western wildcards
	Bracketleg* first_western_wildcard = nullptr;
	Bracketleg* second_western_wildcard = nullptr;
	// central
	Bracketleg* central_first_seed = nullptr;
	Bracketleg* central_second_seed = nullptr;
	Bracketleg* central_third_seed = nullptr;
	// central second round
	Bracketleg* central_second_round_top = nullptr;
	Bracketleg* central_second_round_bottom = nullptr;
	// western third round
	Bracketleg* western_third_round_top = nullptr;
	Bracketleg* western_third_round_bottom = nullptr;
	// western champion
	Bracketleg* western_champion = nullptr;

	// eastern
	// atlantic
	Bracketleg* atlantic_first_seed = nullptr;
	Bracketleg* atlantic_second_seed = nullptr;
	Bracketleg* atlantic_third_seed = nullptr;
	// atlantic second round
	Bracketleg* atlantic_second_round_top = nullptr;
	Bracketleg* atlantic_second_round_bottom = nullptr;
	// eastern wildcards
	Bracketleg* first_eastern_wildcard = nullptr;
	Bracketleg* second_eastern_wildcard = nullptr;
	// metropolitan
	Bracketleg* metropolitan_first_seed = nullptr;
	Bracketleg* metropolitan_second_seed = nullptr;
	Bracketleg* metropolitan_third_seed = nullptr;
	// metropolitan second round
	Bracketleg* metropolitan_second_round_top = nullptr;
	Bracketleg* metropolitan_second_round_bottom = nullptr;
	// eastern third round
	Bracketleg* eastern_third_round_top = nullptr;
	Bracketleg* eastern_third_round_bottom = nullptr;
	// eastern champion
	Bracketleg* eastern_champion = nullptr;

	wxWindow* m_parent = nullptr;
	wxVector<PlayoffSeries*> eastern;
	wxVector<PlayoffSeries*> western;
	wxSize leg_size;

	BitImage* bit = nullptr;

	NHLTeam* m_Player_Team = nullptr;
};

class ItemData
{
public:
	ItemData(NHLplayer* player) : p(player)
	{
		if (p)
			id = p->GetPlayerId();
	};

	NHLplayer* p = nullptr;
	long id = 0;
};

class SeasonStatsWin;
class TeamLineupWin;

class VirtualListView : public wxListView
{
public:
	VirtualListView(wxWindow*, wxWindowID, wxPoint, wxSize, NHL_League*, NHLTeam*, int WindowType);
	virtual wxString OnGetItemText(long, long) const wxOVERRIDE;
	void OnClickCol(wxListEvent&);
	void OnSortCol(int);
	void OnListSelect(wxListEvent&);
	void ClickPositionButton(int);
	bool OnSearchButtonClick(wxString);
//	void OnPaint(wxPaintEvent&);
	void OnScroll(wxScrollWinEvent&);
	void OnWheelScroll(wxMouseEvent& evt);
	void ResetAfterSearchButtonClick();
	wxDECLARE_EVENT_TABLE();	
private:
	void InitalPopulateListView();
	void RefreshOnUpdate();
	void UpdateItemsCount();
	long FindItemByName(wxString);
	ItemData GetVirtualRowItem(long) const;
	wxString GetVirtualColItem(ItemData*, long) const;
	ItemData* GetBeginIter();
	ItemData* GetEndIter();
	long GetVirtualItemCount() const;
	wxWindow* m_parent = nullptr;
	int sortDirection = 1;
	int seasonstats = 0;
	TeamLineupWin* win = nullptr;
	wxVector<ItemData> list;
	wxVector<ItemData> forwardlist;
	wxVector<ItemData> defenselist;
	wxVector<ItemData> goalielist;
	NHL_League* m_league = nullptr;
	NHLTeam* m_team = nullptr;
	long Selection = 0;
	long SelectionID = 0;
	int PositionButton = ListViewWin::ALLPLAYRSBUTTON;
	int winType = -1;
	wxVector<wxString> Col;
	long searchedItem = 0;
	bool firstOnGetItemText = false;
	bool afterFirstOnGetItemText = false;
};

class SeasonStatsWin : public wxFrame
{
public:
	SeasonStatsWin(wxWindow*, wxWindowID, wxPoint, wxSize, NHL_League*);
	void SetSelection(NHLplayer*);
	void OnClose(wxCloseEvent&);
	void OnEnterTeamName(wxMouseEvent&);
	void OnExitTeamName(wxMouseEvent&);
private:
	wxBoxSizer* SetDivision(wxString, wxVector<NHLTeam*>);
	void DestroyTipWindow();
	wxWindow* m_parent = nullptr;
	NHL_League* league = nullptr;
	VirtualListView* List = nullptr;
	wxScrolled<wxPanel>* P = nullptr;
	wxStaticText* eastern = nullptr;
	wxStaticText* western = nullptr;
	wxStaticText* pacific = nullptr;
	wxStaticText* central = nullptr;
	wxStaticText* metropolitan = nullptr;
	wxStaticText* atlantic = nullptr;
	NHLTeam* myteam = nullptr;
	wxTipWindow* tip = nullptr;

};

class TeamLineupWin : public wxFrame
{
public:
	TeamLineupWin(NHL_League*, wxFrame*, NHLTeam*);
	void ListSelect(wxListEvent&);
	void LineupButtonPress(wxCommandEvent&);
	void ClickSortButton(wxCommandEvent&);
	void ClickChangeLineupButton(wxCommandEvent&);
	void OnSearchBtnClick(wxCommandEvent&);
	void Close(wxCloseEvent&);
	void OnMouseEnterChangeLineup(wxMouseEvent&);
	void OnMouseExitChangeLineup(wxMouseEvent&);
	void SetSelection(NHLplayer*);
	void OnChangeSize(wxSizeEvent&);
	wxDECLARE_EVENT_TABLE();
private:
	void ListSelect();
	void Create();
	void SetFont(wxStaticText*&, wxFont&);
	char GetPosition(int);
	int GetLine(int);
private:
	wxFrame* m_parent = nullptr;
	NHL_League* m_league = nullptr;
	wxPanel* m_panel = nullptr;
//	wxFrame* m_frame = nullptr;
	wxListView* m_listV = nullptr;
	VirtualListView* vlv = nullptr;
	NHLTeam* m_team = nullptr;
	NHLplayer* m_player = nullptr;
	int m_buttonid = -1;
	int m_listV_index = -1;
	int m_listV_sort_button = 0;
	wxColour m_listV_color;
	bool m_ChangeLineup = false;
	int oldColumn = -1;
	Canvas* canvas = nullptr;
	wxTipWindow *tip = nullptr;
	wxSearchCtrl* search = nullptr;
};

class ChangeTeamLineups : public wxFrame
{
public:
	ChangeTeamLineups(wxFrame*, NHL_League*);
	void OnButtonClick(wxCommandEvent&);
	void OnClose(wxCloseEvent&);
private:
	TeamLineupWin* tl = nullptr;
	wxFrame* m_parent = nullptr;
	NHL_League* league = nullptr;
};

class StartSeason : public wxFrame
{
public:
	StartSeason(wxFrame*, NHL_League*);
	~StartSeason();
	void OnButtonClick(wxCommandEvent&);
	void OnClose(wxCloseEvent&);
	NHLTeam* GetTeamSelected() { return teamselected; }
private:
	TeamLineupWin* tl = nullptr;
	wxFrame* m_parent = nullptr;
	NHL_League* league = nullptr;
	wxBoxSizer* panelsizerH = nullptr;
	wxBoxSizer* panelsizerV = nullptr;
	BitImage* myTeam = nullptr;
	wxPanel* P = nullptr;
	NHLTeam* teamselected = nullptr;
};


class TeamSelect : public wxFrame
{
public:
	TeamSelect(wxFrame*, NHL_League*);
	void OnClose(wxCloseEvent&);
	void OnButtonClick(wxCommandEvent&);
	void OnStartGame(wxCommandEvent&);
	void OnThreadEvent(wxThreadEvent&);
private:
	wxFrame* m_parent = nullptr;
	NHL_League* league = nullptr;
	int buttonclicked = -1;
	wxBoxSizer* first = nullptr;
	wxBoxSizer* second = nullptr;
	wxBoxSizer* last = nullptr;
	BitImage* Home = nullptr, * Away = nullptr;
	bool h = false;
	bool a = false;
	bool firstround = false;

	wxStaticText* left = nullptr;
	wxStaticText* right = nullptr;
	wxBoxSizer* Left = nullptr;
	wxBoxSizer* Right = nullptr;
	wxBoxSizer* Middle = nullptr;
	Canvas* startgame = nullptr;
	GameFrame* gf = nullptr;

	NHLTeam* m_away = nullptr;
	NHLTeam* m_home = nullptr;
};

class mainwindow;

void SeasonGameReady(wxWindow*, NHLTeam*, NHLTeam*, int, int);

class mainwindow : public wxFrame
{
public:
	mainwindow();
	~mainwindow();
	wxDECLARE_EVENT_TABLE();
	void IncrementYear();
	void GetPlayerBio();
	void Retrieve();
	void GetLines();
	void GetSkaterStats();
	void GetGoalieStats();
	void SetFont(wxStaticText*&, wxFont&);
	void BindLineupButton(wxButton*&);
	void GameOutcome(NHLTeam*);
public:
	void SeasonGame(NHLTeam*, NHLTeam*, int, int);

	//EVENT FUNCTIONS...
	void OnSeasonStatWinClose(wxCommandEvent&);
	void OnPlayoffViewClose(wxCommandEvent&);
	void GetTeam(wxCommandEvent&);
	void CloseSelf(wxCloseEvent&);
	void OnListSelect(wxListEvent&);
	void DragColStart(wxListEvent&);
	void DragColEnd(wxListEvent&);
	void ClickSortButtons(wxCommandEvent&);
	void ClickChangeLineupButton(wxCommandEvent&);
	void NewGame(wxCommandEvent&);
	void OnMenuChangeLineups(wxCommandEvent&);
	void NewSeason(wxCommandEvent&);
	void OnNewSeasonStart(wxCommandEvent&);
	void GameOutcome(wxThreadEvent&);
	void RegularSeasonOverEvent(wxCommandEvent&);
	void OnPlayoffStart(wxCommandEvent&);
	void OnFirstRoundOver(wxCommandEvent& evt);
	void OnSecondRoundOver(wxCommandEvent& evt);
	void OnThirdRoundOver(wxCommandEvent& evt);

public:
	void EnableSetFocus();
	void DestroyGameWin();

private:
	//FOR GETTING THE CORRECT LINE AFTER A BUTTON IS PUSHED ON PLAYER IN LINEUP. THE FIRST BUTTON ID IN THE LINEUP GETS SUBTRACTED FROM THE BUTTONID THAT WAS PUSHED
	//LEAVING A NUMBER INDICATING WHAT LINE IT WAS ON. THAT NUMBER MAY NEED TO BE CONVERTED TO THE CORRECT LINE I.E. 0,1,2,3...
	int GetLine(int);
	char GetPosition(int);
	char GetSwapPlayerPos(int);
private:
	wxString SkaterURL = "https://moneypuck.com/moneypuck/playerData/seasonSummary/year/regular/skaters.csv";
	wxString GoalieURL = "https://moneypuck.com/moneypuck/playerData/seasonSummary/year/regular/goalies.csv";
	wxString LineParingsURL = "https://moneypuck.com/moneypuck/playerData/seasonSummary/year/regular/lines.csv";
	wxString playerbioURL = "https://moneypuck.com/moneypuck/playerData/playerBios/allPlayersLookup.csv";
	wxString definitions = "https://peter-tanner.com/moneypuck/downloads/MoneyPuckDataDictionaryForPlayers.csv";
	int beginyear = 2008;
	wxVector<wxString> yeardataskaters;
	wxVector<wxString> yeardatagoalies;
	wxVector<wxString> yeardatalines;
	webdata web;
	wxString startofskaterdata = "fenwickAgainstAfterShifts";
	wxString startofGoalieData = "penalties";
	wxString startoflines = "scoreFlurryAdjustedTotalShotCreditAgainst";
	NHL_League league;
	TeamLineupWin* teamwin = nullptr;
	TeamSelect* ts = nullptr;
	ChangeTeamLineups* cth = nullptr;
	StartSeason* St = nullptr;
	GameFrame* gamewin;
	wxBitmap* nhl_logo = nullptr;
	wxBitmap* stanley_cup_playoffs = nullptr;
	wxBitmap* stanley_cup_finals = nullptr;
	wxBitmap* stanley_cup = nullptr;
	int game = 0;
	int season = 0;

	SeasonStatsWin* statswin = nullptr;
	BitImage* mainscreenbit = nullptr;
	wxBitmap* screenbit = nullptr;
	PlayoffBracketView* playoff_view = nullptr;
};

