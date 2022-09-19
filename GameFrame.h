#pragma once


#include "NHL_League.h"
#include "WindowIDs.h"
#include "wx/thread.h"

class GameFrame;

class BitImage : public wxWindow
{
public:
	BitImage(wxWindow*, int,  wxBitmap*, wxColour);
	BitImage(wxWindow*, int, wxPoint, wxBitmap*, wxColour);
	~BitImage();
	void SetNewBit(wxBitmap*);
	void OnPaint(wxPaintEvent&);
	void ShowBitmap();
	void HideBitmap();
	wxSize Getsize();
	void SetPosition(wxPoint);
private:
	void Paint();
	wxBitmap* image = nullptr;
	wxWindow* m_parent = nullptr;
	bool hide = false;
};

class Window : public wxWindow
{
public:
	Window(wxWindow*, int, wxFont, wxString);
	~Window();
	void OnPaint(wxPaintEvent&);
	void RefreshWindow();
private:
	wxWindow* m_parent = nullptr;
	wxFont title;
	wxString titletext = "";
	wxGraphicsGradientStops stops;
};

class CustomWin : public wxWindow
{
public:
	CustomWin(wxWindow*, int, wxFont, wxString, wxSize, wxSize, bool);
	void OnPaint(wxPaintEvent&);
private:
	wxWindow* m_parent = nullptr;
	wxFont font;
	wxString text = "";
	wxSize textsize;
	wxSize this_size;
	bool transparentbackground = false;
};

struct pair
{
	pair(GameWindow win, GameRecord* g, wxString s) : w(win), gr(g), message(s) {}
	GameWindow w;
	GameRecord* gr = nullptr;
	wxString message = "";
};

class MyThread : public wxThread
{
public:
	MyThread(GameFrame*, NHL_League*, NHLTeam*, NHLTeam*, bool);
	~MyThread();
	wxThread::ExitCode Entry();
	void EndAfterEntry() { end = true; }
private:
	GameFrame* gameframe = nullptr;
	NHL_League* league = nullptr;
	NHLTeam* away = nullptr;
	NHLTeam* home = nullptr;
	bool end = false;
	bool playoffs;
};

class GameFrame : public wxFrame
{
public:
	GameFrame(wxFrame*, void (*func)(void*, NHLTeam*), NHL_League*, NHLTeam*, NHLTeam*, int ser = 1);
	GameFrame(wxFrame*, NHL_League*, NHLTeam*, NHLTeam*, int ser = 1, int round = 0);
	~GameFrame();

	void StartGame(NHLTeam*, NHLTeam*, bool);
	NHLTeam* GetWinningTeam() { return winner; }
	NHLTeam* GetDefeatedTeam() { return loser; }
	bool PlayoffSeries() { return Series; }

	// CALLBACK FUNCTION FOR GAME OBJECT TO PASS UPDATES FROM THE GAME E.G. A GOAL SCORED, SHOT UPDATE..
    static void CallBack(GameWindow, int, void*, GameRecord* gr = nullptr, wxString message = "");

	bool IsOver();

	//THIS IS AN EVENT FUNCTION FOR GAME OBJECT TO UPDATE WHAT IS GOING ON...
	void OnUpdate(wxCommandEvent&);

	void OnClose(wxCloseEvent&);
	void OnMouseLeftDown(wxMouseEvent&);
	void ThreadEvent(wxThreadEvent&);
	void OnSizeChange(wxSizeEvent& evt);

	static wxVector<pair*> queue;
	static pair P;
	MyThread* thread = nullptr;
	wxCriticalSection m_critical;

private:
	void StartGameMessage();
	void SetAwayGoal();
	void SetAwayShots();
	void SetAwayRecord(GameRecord*, bool update = true);
	void SetHomeGoal();
	void SetHomeShots();
	void SetHomeRecord(GameRecord*, bool update = true);
	void DoUpdateWindow(wxString, int size = 13, bool b = false);
	void DoUpdateWindowOvertime(wxString);
	void DestroyPopup();
	void DeclareWinner();
	void Initialize();
	void Swap();
	void DeleteQueue();
	void SetMinLogoSizerHeight();

private:
	void HideLowerSizer();
	void ShowLowerSizer();
	void Create();

	//callback func pointer...
	void (*Cb)(void*, NHLTeam*) = nullptr;
	int m_homeshots = 0;
	int m_awayshots = 0;
	int m_homegoals = 0;
	int m_awaygoals = 0;
	NHLTeam* home = nullptr;
	NHLTeam* away = nullptr;
	wxStaticText* m_AwayGoals = nullptr;
	wxStaticText* m_AwayRecord = nullptr;
	wxStaticText* m_AwayShots = nullptr;
	wxStaticText* m_HomeGoals = nullptr;
	wxStaticText* m_HomeRecord = nullptr;
	wxStaticText* m_HomeShots = nullptr;
	wxStaticText* gamenumber = nullptr;
	NHL_League* league = nullptr;
	wxBitmap* homelogo = nullptr;
	wxBitmap* awaylogo = nullptr;
	wxFrame* m_parent = nullptr;
	BitImage* nhlsymbol = nullptr;
	BitImage* m_AwayLogo = nullptr;
	BitImage* m_HomeLogo = nullptr;
	Window* Banner = nullptr;
	CustomWin* alert = nullptr;

	wxBoxSizer* HomeLogoH = nullptr;
	wxBoxSizer* AwayLogoH = nullptr;
	wxBoxSizer* HomeLogoV = nullptr;
	wxBoxSizer* AwayLogoV = nullptr;
	wxBoxSizer* MidH = nullptr;

	wxBitmap* nhl_logo = nullptr;
	wxBitmap* stanley_cup_playoffs = nullptr;
	wxBitmap* stanley_cup_finals = nullptr;
	wxBitmap* stanley_cup = nullptr;
	wxStaticText* T = nullptr;
	wxWindow* pw = nullptr;
	int series = 1;
	int series_round = 0;
	int game = 1;
	bool Series = false;
	NHLTeam* winner = nullptr;
	NHLTeam* loser = nullptr;
};


