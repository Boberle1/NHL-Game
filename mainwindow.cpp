#include "mainwindow.h"

wxDEFINE_EVENT(CanvasClick, wxCommandEvent);
wxCommandEvent Click(wxCommandEvent);

wxDEFINE_EVENT(OnSeasonStart, wxCommandEvent);
wxCommandEvent OnSeason(wxCommandEvent);

wxDEFINE_EVENT(OnCloseSeasonStatWin, wxCommandEvent);
wxCommandEvent SeasonStatClose(wxCommandEvent);

wxDEFINE_EVENT(ClosePlayoffView, wxCommandEvent);
wxCommandEvent PlayoffViewClose(wxCommandEvent);

wxBEGIN_EVENT_TABLE(mainwindow, wxFrame)
	EVT_LIST_ITEM_SELECTED(ListViewWin::LISTVIEWID, OnListSelect)
	EVT_MENU(MainWin::MAINWINGAME, NewGame)
	EVT_MENU(MainWin::LINEUPCHANGE, OnMenuChangeLineups)
	EVT_MENU(MainWin::STARTNEWSEASON, NewSeason)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(TeamLineupWin, wxFrame)
//	EVT_SEARCHCTRL_SEARCH_BTN(SEARCHBUTTON, OnSearchBtnClick)
	EVT_TEXT_ENTER(SEARCHBUTTON, OnSearchBtnClick)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(VirtualListView, wxListCtrl)
	EVT_SCROLLWIN(VirtualListView::OnScroll)
wxEND_EVENT_TABLE()


constexpr auto PLAYERNAME = "Player Name";
constexpr auto TEAM = "Team";
constexpr auto PLAYER_RATING = "Player Rating";
constexpr auto GOALS = "Goals";
constexpr auto ASSISTS = "Assists";
constexpr auto POSITION = "Position";
constexpr auto SHOTS_ON_GOAL = "Shots On Goal";
constexpr auto SHOT_ATTEMPTS = "Shot Attempts";
constexpr auto SHOT_ATTEMPTS_BLOCKED = "Shot Attempts Blocked";
constexpr auto SHOTS_BLOCKED = "Shots Blocked";
constexpr auto OVERALL = "Overall";
constexpr auto OFFENSE_ = "Offense";
constexpr auto DEFENSE_ = "Defense";
constexpr auto _TAKE_AWAY = "Take Away";
constexpr auto _GIVE_AWAY = "Give Away";
constexpr auto _GOALS_PER_GAME = "Goals Per Game";

Canvas::Canvas(wxWindow* w, wxWindowID id, wxPoint point, wxString s, wxSize size) : wxWindow(w, id, point, size), parent(w), text(s)
{
	this->SetBackgroundColour(parent->GetBackgroundColour());
	this->SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &Canvas::OnPaint, this);
	this->Bind(wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this);
	this->Bind(wxEVT_ENTER_WINDOW, &Canvas::OnMouseEnter, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &Canvas::OnMouseLeave, this);
}

Canvas::~Canvas()
{
	
}

void Canvas::OnMouseLeftDown(wxMouseEvent& evt)
{
	mousedown = mousedown ? false: true;
//	this->QueueEvent(new wxPaintEvent(1));
	this->Refresh();
	wxCommandEvent Evt(CanvasClick);
	wxPostEvent(parent, Evt);

//	this->Refresh();
}

void Canvas::OnMouseEnter(wxMouseEvent& evt)
{
	this->QueueEvent(new wxPaintEvent(2));
	this->Refresh();
//	OnDynamicPaint(2);
}

void Canvas::OnMouseLeave(wxMouseEvent& evt)
{
	this->QueueEvent(new wxPaintEvent(3));
	this->Refresh();
//	OnDynamicPaint(1);
}

void Canvas::OnPaint(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	Gen g;
	int width = parent->GetSize().x / 12;
	int height = 0;
	wxSize proportionSize(width, width * (2.0 / 6.0));
	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = this->FromDIP(proportionSize);
	if (mousedown)
	{
		for (size_t i = 0; i < rectSize.GetWidth(); ++i)
		{
			for (size_t j = 0; j < rectSize.GetHeight(); ++j)
			{
				if ((i == 0 || j == 0) || (i == 1 || j == 1))
					dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
				else if ((i == rectSize.GetWidth() - 1 || j == rectSize.GetHeight() - 1) || (i == rectSize.GetWidth() - 2 || j == rectSize.GetHeight() - 2))
					dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
				else
					dc.SetPen(wxPen(wxColour(255, 0, 0), 1));
				dc.DrawPoint(wxPoint(i, j));
			}
		}
		return;
	}
	for (size_t i = 0; i < rectSize.GetWidth(); ++i)
	{
		for (size_t j = 0; j < rectSize.GetHeight(); ++j)
		{
			if ((i == 0 || j == 0) || (i == 1 || j == 1))
				dc.SetPen(wxPen(wxColour(255, 0, 0), 1));
			else if ((i == rectSize.GetWidth() - 1 || j == rectSize.GetHeight() - 1) || (i == rectSize.GetWidth() - 2 || j == rectSize.GetHeight() - 2))
				dc.SetPen(wxPen(wxColour(255, 0, 0), 1));
			else
				dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
			dc.DrawPoint(wxPoint(i, j));
		}
	}
	/*
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	int width = parent->GetSize().x / 12;
	int height = 0;
	wxSize proportionSize(width, width * (2.0 / 6.0));
	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = this->FromDIP(proportionSize);
	wxColour font = wxColour(255, 255, 255);
//	gc->SetPen(wxPen(wxColour(255, 0, 0), 2));
	
	if (mousedown)
	{
		gc->SetBrush(*wxGREEN_BRUSH);
		font = wxColour(0, 0, 0);
	}
	else if (evt.GetId() == 2)
	{
		wxColour begin = wxColour(0, 0, 0);
		wxColour end = wxColour(255, 255, 255);
		wxGraphicsBrush gb = gc->CreateLinearGradientBrush(rectOrigin.x, rectOrigin.y, rectOrigin.x + rectSize.GetWidth(), rectOrigin.y + rectSize.GetHeight(), begin, end);
		gc->SetBrush(gb);
	}
	else
	{
		gc->SetBrush(*wxBLUE_BRUSH);
	}

	gc->DrawRoundedRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight(), rectSize.GetHeight() / 5.0);

	wxFont f = wxFont(*wxNORMAL_FONT);
	int pointsize = 8;
	f.SetPointSize(pointsize);
	f.SetFamily(wxFontFamily::wxFONTFAMILY_MODERN);
	f = f.MakeBold();
	wxGraphicsFont gf = gc->CreateFont(f, font);
	gc->SetFont(gf);
	double w = 0.0;
	double h = 0.0;
	gc->GetTextExtent(text, &w, &h);
	gc->DrawText(text, rectOrigin.x + (rectSize.GetWidth() / 2.0) - w / 2.0, (rectOrigin.y + rectSize.GetHeight() / 2.0) - h / 2.0);

	delete gc;
	*/
}

void Canvas::OnDynamicPaint(int id)
{
	wxClientDC dc(this);

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	int width = parent->GetSize().x / 12;
	int height = 0;
	wxSize proportionSize(width, width * (2.0 / 6.0));
	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = this->FromDIP(proportionSize);

	wxString label = "Trade Player";
	wxColour font = wxColour(255, 255, 255);
	if (id == 2)
	{
		wxColour begin = wxColour(0, 0, 0);
		wxColour end = wxColour(255, 255, 255);
		wxGraphicsBrush gb = gc->CreateLinearGradientBrush(rectOrigin.x, rectOrigin.y, rectOrigin.x + rectSize.GetWidth(), rectOrigin.y + rectSize.GetHeight(), begin, end);
	//	wxColour hover(104, 90, 214);
		gc->SetBrush(gb);
	}
	else
		gc->SetBrush(*wxBLUE_BRUSH);

	gc->DrawRoundedRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight(), rectSize.GetHeight() / 5.0);

	gc->SetFont(*wxNORMAL_FONT, font);
	double w = 0.0;
	double h = 0.0;
	gc->GetTextExtent(label, &w, &h);
	gc->DrawText(label, rectOrigin.x + (rectSize.GetWidth() / 2.0) - w / 2.0, (rectOrigin.y + rectSize.GetHeight() / 2.0) - h / 2.0);

	delete gc;
}

Bracketleg::Bracketleg(wxWindow* w, wxString t, wxWindowID id, wxPoint point, wxSize size, int dir, int m, wxColour color) :
	wxWindow(w, id, point, w->FromDIP(size)),
	m_parent(w), team(t), direction(dir), mirror(m), m_textColor(color)
{
	wxSize check = this->GetSize();
	m_mySize = this->GetSize();
	this->SetBackgroundColour(m_parent->GetBackgroundColour());
	this->SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &Bracketleg::OnPaint, this);
}

void Bracketleg::OnPaint(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = this->FromDIP(wxSize(m_mySize.GetWidth(), m_mySize.GetHeight()));

	int width = rectSize.GetWidth();
	int height = rectSize.GetHeight();
	double w = 0.0;
	double h = 0.0;
	
	int y1 = height - 1;
	int x1 = 0;
	int x2 = width;
	int y2 = height - 1;
	int x3 = mirror ? 0 : width - 1;
	int y3 = mirror ? 0 : height - 1;
	int y4 = mirror ? height : 0;
	int x4 = mirror ? 0 : width - 1;
	dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
	dc.DrawLine(wxPoint(x1, y1), wxPoint(x2, y2));
	y1 = height - 2;
	y2 = height - 2;
	dc.DrawLine(wxPoint(x1, y1), wxPoint(x2, y2));
	if (direction)
	{
		dc.DrawLine(wxPoint(x3, y3), wxPoint(x4, y4));
		dc.DrawLine(wxPoint(mirror ? x3 + 1 : x3 - 1, y3), wxPoint(mirror ? x4 + 1 : x4 - 1, y4));
		dc.DrawLine(wxPoint(mirror ? x3 + 2 : x3 - 2, y3), wxPoint(mirror ? x4 + 2 : x4 - 2, y4));
	}

	if (team.size())
	{
		wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
		if (!gc)
		{
			wxLogError("gc is null in Bracketleg::OnPaint!");
			return;
		}

		wxGraphicsFont gf = gc->CreateFont(wxFont(20, wxFONTFAMILY_MODERN, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_MEDIUM, false, team), m_textColor);
		gc->SetFont(gf);

		gc->GetTextExtent(team, &w, &h);
		gc->DrawText(team, rectOrigin.x + (rectSize.GetWidth() / 2.0) - w / 2.0, y1 - (h + 5));

		delete gc;
	}
}

PlayoffBracketView::PlayoffBracketView(wxWindow* w, wxWindowID id, wxSize size, wxVector<PlayoffSeries*> east, wxVector<PlayoffSeries*> west, NHLTeam* T)
	: wxFrame(w, id, "Playoffs", wxDefaultPosition, size),
	m_parent(w), eastern(east), western(west), m_Player_Team(T)
{
	this->Bind(wxEVT_CLOSE_WINDOW, &PlayoffBracketView::OnClose, this);

	int w_ratio = 9;
	int h_ratio = 9;
	this->leg_size = this->FromDIP(wxSize(this->GetSize().GetWidth() / w_ratio, this->GetSize().GetHeight() / h_ratio));
	wxString empty = "";
	// first round western
	this->central_first_seed = this->PositionBracket(nullptr, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		western[0]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->second_western_wildcard = this->PositionBracket(this->central_first_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		western[0]->GetAwayTeam()->GetTeamabbr(true), 1, 0);

	this->central_second_seed = this->PositionBracket(this->second_western_wildcard, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		western[1]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->central_third_seed = this->PositionBracket(this->central_second_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		western[1]->GetAwayTeam()->GetTeamabbr(true), 1, 0);

	this->pacific_first_seed = this->PositionBracket(this->central_third_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND,
		western[2]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->first_western_wildcard = this->PositionBracket(this->pacific_first_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND,
		western[2]->GetAwayTeam()->GetTeamabbr(true), 1, 0);

	this->pacific_second_seed = this->PositionBracket(this->first_western_wildcard, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		western[3]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->pacific_third_seed = this->PositionBracket(this->pacific_second_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FIRST_ROUND,
		western[3]->GetAwayTeam()->GetTeamabbr(true), 1, 0);

	// first round eastern
	this->atlantic_first_seed = this->PositionBracket(nullptr, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		eastern[0]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->second_eastern_wildcard = this->PositionBracket(this->atlantic_first_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND,
		eastern[0]->GetAwayTeam()->GetTeamabbr(true), 1, 1);

	this->atlantic_second_seed = this->PositionBracket(second_eastern_wildcard, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND,
		eastern[1]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->atlantic_third_seed = this->PositionBracket(this->atlantic_second_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND,
		eastern[1]->GetAwayTeam()->GetTeamabbr(true), 1, 1);

	this->metropolitan_first_seed = this->PositionBracket(atlantic_third_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		eastern[2]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->first_eastern_wildcard = this->PositionBracket(this->metropolitan_first_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND, 
		eastern[2]->GetAwayTeam()->GetTeamabbr(true), 1, 1);

	this->metropolitan_second_seed = this->PositionBracket(first_eastern_wildcard, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND,
		eastern[3]->GetHomeTeam()->GetTeamabbr(true), 0, 0);
	this->metropolitan_third_seed = this->PositionBracket(this->metropolitan_second_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FIRST_ROUND,
		eastern[3]->GetAwayTeam()->GetTeamabbr(true), 1, 1);

	// second round western
	empty = western[0]->GetWinningTeam() ? western[0]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->central_second_round_top = this->PositionBracket(this->central_first_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_SECOND_ROUND_TOP, empty, 0, 0);

	empty = western[1]->GetWinningTeam() ? western[1]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->central_second_round_bottom = this->PositionBracket(this->central_second_round_top, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_SECOND_ROUND_BOTTOM, empty, 1, 0);

	empty = western[2]->GetWinningTeam() ? western[2]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->pacific_second_round_top = this->PositionBracket(this->pacific_first_seed, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_SECOND_ROUND_TOP, empty, 0, 0);

	empty = western[3]->GetWinningTeam() ? western[3]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->pacific_second_round_bottom = this->PositionBracket(this->pacific_second_round_top, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_SECOND_ROUND_BOTTOM, empty, 1, 0);

	// second round eastern
	empty = eastern[0]->GetWinningTeam() ? eastern[0]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->atlantic_second_round_top = this->PositionBracket(this->atlantic_first_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_SECOND_ROUND_TOP, empty, 0, 0);

	empty = eastern[1]->GetWinningTeam() ? eastern[1]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->atlantic_second_round_bottom = this->PositionBracket(this->atlantic_second_round_top, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_SECOND_ROUND_BOTTOM, empty, 1, 1);

	empty = eastern[2]->GetWinningTeam() ? eastern[2]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->metropolitan_second_round_top = this->PositionBracket(this->metropolitan_first_seed, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_SECOND_ROUND_TOP, empty, 0, 0);

	empty = eastern[3]->GetWinningTeam() ? eastern[3]->GetWinningTeam()->GetTeamabbr(true) : "";
	this->metropolitan_second_round_bottom = this->PositionBracket(this->metropolitan_second_round_top, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_SECOND_ROUND_BOTTOM, empty, 1, 1);

	// third round western
	empty = this->GetTeamName(western, 4);
	this->western_third_round_top = this->PositionBracket(this->central_second_round_top, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_THIRD_ROUND_TOP, empty, 0, 0);

	empty = this->GetTeamName(western, 5);
	this->western_third_round_bottom = this->PositionBracket(this->western_third_round_top, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_THIRD_ROUND_BOTTOM, empty, 1, 0);

	// third round eastern
	empty = this->GetTeamName(eastern, 4);
	this->eastern_third_round_top = this->PositionBracket(this->atlantic_second_round_top, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_THIRD_ROUND_TOP, empty, 0, 0);

	empty = this->GetTeamName(eastern, 5);
	this->eastern_third_round_bottom = this->PositionBracket(this->eastern_third_round_top, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_THIRD_ROUND_BOTTOM, empty, 1, 1);

	// stanley cup round western
	empty = this->GetTeamName(western, 6);
	this->western_champion = this->PositionBracket(this->western_third_round_top, BracketlegPosition::BRACKET_LEFT, BracketlegPosition::BRACKET_FOURTH_ROUND, empty, 0, 0);

	// stanley cup round eastern
	empty = this->GetTeamName(eastern, 6);
	this->eastern_champion = this->PositionBracket(this->eastern_third_round_top, BracketlegPosition::BRACKET_RIGHT, BracketlegPosition::BRACKET_FOURTH_ROUND, empty, 0, 0);

	wxBitmap* bitmap = new wxBitmap("SavedLogos/StanleyCupPlayoffs.png", wxBITMAP_TYPE_PNG);
	wxSize bitsize = bitmap->GetSize();
	wxPoint p(this->GetClientSize().GetWidth() / 2 - bitmap->GetSize().GetWidth() / 2, this->GetClientSize().GetHeight() / 2 - bitmap->GetSize().GetHeight() / 2);
	bit = new BitImage(this, wxID_ANY, p, bitmap, this->GetBackgroundColour());

	this->CenterOnParent();
	this->Show();
}

void PlayoffBracketView::OnClose(wxCloseEvent& evt)
{
	wxPostEvent(m_parent, wxCommandEvent(ClosePlayoffView, 0));
	this->Destroy();
}

Bracketleg* PlayoffBracketView::PositionBracket(Bracketleg* sibling, BracketlegPosition right_or_left,  BracketlegPosition round, wxString name, int dir, int mirror)
{
	int ratio = 1;
	if (round == BracketlegPosition::BRACKET_SECOND_ROUND_BOTTOM)
		ratio = 2;
	else if (round == BracketlegPosition::BRACKET_THIRD_ROUND_BOTTOM)
		ratio = 4;

	wxSize size(leg_size.GetWidth(), sibling ? sibling->GetSize().GetHeight() * ratio : leg_size.GetHeight() * ratio);

	int y = 0;
	int x = 0;
	if (round == BracketlegPosition::BRACKET_SECOND_ROUND_TOP || round == BracketlegPosition::BRACKET_THIRD_ROUND_TOP || round == BracketlegPosition::BRACKET_FOURTH_ROUND)
	{
		int second_ratio = round == BracketlegPosition::BRACKET_THIRD_ROUND_TOP ? 2 : 1;
		second_ratio = round == BracketlegPosition::BRACKET_FOURTH_ROUND ? 4 : second_ratio;

		y = sibling ? sibling->GetPosition().y + (sibling->GetSize().GetHeight() * second_ratio) / 2 : 0;
		if (right_or_left == BracketlegPosition::BRACKET_RIGHT)
			x = sibling ? sibling->GetPosition().x - leg_size.GetWidth() : this->GetClientSize().GetWidth() - leg_size.GetWidth() * ratio;
		else
			x = sibling ? sibling->GetPosition().x + leg_size.GetWidth() : 0;
	}
	else
	{
		y = sibling ? sibling->GetPosition().y + sibling->GetSize().GetHeight() : 0;
		if (right_or_left == BracketlegPosition::BRACKET_RIGHT)
			x = sibling ? sibling->GetPosition().x : this->GetClientSize().GetWidth() - leg_size.GetWidth() * ratio;
		else
			x = sibling ? sibling->GetPosition().x : 0;
	}

	wxPoint point(x, y);
	wxColour color(0, 0, 0);
	if (m_Player_Team && m_Player_Team->GetTeamabbr(true) == name)
		color = wxColour(50, 58, 209);

	return new Bracketleg(this, name, wxID_ANY, point, this->FromDIP(size), dir, mirror, color);
}

wxString PlayoffBracketView::GetTeamName(wxVector<PlayoffSeries*>& v, int i)
{
	if (v.size() > i)
	{
		return v[i]->GetWinningTeam() ? v[i]->GetWinningTeam()->GetTeamabbr(true) : "";
	}
	else
		return "";
}

VirtualListView::VirtualListView(wxWindow* w, wxWindowID id, wxPoint p, wxSize s, NHL_League* l, NHLTeam* t, int WindowType) : wxListView(w, id, p, s, wxLC_REPORT | wxLC_VIRTUAL), 
	m_parent(w), m_league(l), m_team(t), winType(WindowType)
{
	this->Bind(wxEVT_MOUSEWHEEL, &VirtualListView::OnWheelScroll, this);
	this->Bind(wxEVT_LIST_COL_CLICK, &VirtualListView::OnClickCol, this);
	this->Bind(wxEVT_LIST_ITEM_SELECTED, &VirtualListView::OnListSelect, this);
	this->SetBackgroundColour(wxColour(50, 55, 52));
	this->SetForegroundColour(wxColour(255, 255, 255));
	this->AppendColumn(PLAYERNAME, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(PLAYERNAME);
	this->AppendColumn(TEAM, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(TEAM);
	this->AppendColumn(PLAYER_RATING, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(PLAYER_RATING);
	this->AppendColumn(GOALS, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(GOALS);
	this->AppendColumn(ASSISTS, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(ASSISTS);
	this->AppendColumn(POSITION, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(POSITION);
	this->AppendColumn(SHOTS_ON_GOAL, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(SHOTS_ON_GOAL);
	this->AppendColumn(SHOT_ATTEMPTS, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(SHOT_ATTEMPTS);
	this->AppendColumn(SHOT_ATTEMPTS_BLOCKED, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(SHOT_ATTEMPTS_BLOCKED);
	this->AppendColumn(SHOTS_BLOCKED, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(SHOTS_BLOCKED);
	this->AppendColumn(OVERALL, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(OVERALL);
	this->AppendColumn(OFFENSE_, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(OFFENSE_);
	this->AppendColumn(DEFENSE_, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(DEFENSE_);
	this->AppendColumn(_GIVE_AWAY, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(_GIVE_AWAY);
	this->AppendColumn(_TAKE_AWAY, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(_TAKE_AWAY);
	this->AppendColumn(_GOALS_PER_GAME, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE), Col.push_back(_GOALS_PER_GAME);


	InitalPopulateListView();
}

wxString VirtualListView::OnGetItemText(long index, long col) const
{
	if (this->firstOnGetItemText)
	{
		long item = this->GetTopItem();

		index = searchedItem + (index - item);
		if (searchedItem >= this->GetVirtualItemCount())
		{
			return "";
		}
	}

	ItemData li = GetVirtualRowItem(index);
	if (!li.p) 
		return "";

	return this->GetVirtualColItem(&li, col);
}

void VirtualListView::OnClickCol(wxListEvent& evt)
{
	OnSortCol(evt.GetColumn());
	RefreshOnUpdate();
	this->sortDirection = this->sortDirection ? 0 : 1;
}

void VirtualListView::OnSortCol(int col)
{
	static auto genericCompare = [](auto item1, auto item2, bool ascending)
	{
		return ascending ? item1 < item2 : item1 > item2;
	};
	
	bool ascending = this->sortDirection;

	ItemData* begin = GetBeginIter();
	ItemData* end = GetEndIter();

	wxString colstring = Col[col];

	std::sort(begin, end, [colstring, ascending](ItemData l1, ItemData l2) {
		//		Stats* s1 = l1.p->GetOverallAverageStats();
		//		Stats* s2 = l2.p->GetOverallAverageStats();
		Stats* s1 = l1.p->GetCurrentSeasonStats();
		Stats* s2 = l2.p->GetCurrentSeasonStats();

		if (colstring == PLAYERNAME)			return genericCompare(l1.p->GetName(), l2.p->GetName(), ascending);
		if (colstring == TEAM)					return genericCompare(l1.p->GetTeam(), l2.p->GetTeam(), ascending);
		if (colstring == PLAYER_RATING)			return genericCompare(l1.p->GetGameScore(), l2.p->GetGameScore(), ascending);
		if (colstring == GOALS)					return genericCompare(s1->I_F_goals, s2->I_F_goals, ascending);
		if (colstring == ASSISTS)				return genericCompare(s1->I_F_primaryAssists + s1->I_F_secondaryAssists, s2->I_F_primaryAssists + s2->I_F_secondaryAssists, ascending);
		if (colstring == POSITION)				return genericCompare(s1->Pos, s2->Pos, ascending);
		if (colstring == SHOTS_ON_GOAL)			return genericCompare(s1->I_F_shotsOnGoal, s2->I_F_shotsOnGoal, ascending);
		if (colstring == SHOT_ATTEMPTS)			return genericCompare(s1->I_F_shotAttempts, s2->I_F_shotAttempts, ascending);
		if (colstring == SHOTS_BLOCKED)			return genericCompare(s1->blockedshots, s2->blockedshots, ascending);
		if (colstring == SHOT_ATTEMPTS_BLOCKED) return genericCompare(s1->I_F_blockedShotAttempts, s2->I_F_blockedShotAttempts, ascending);
		if (colstring == OVERALL)				return genericCompare(s1->pv.overall, s2->pv.overall, ascending);
		if (colstring == OFFENSE_)				return genericCompare(s1->pv.offense, s2->pv.offense, ascending);
		if (colstring == DEFENSE_)				return genericCompare(s1->pv.defense, s2->pv.defense, ascending);
		if (colstring == _GIVE_AWAY)			return genericCompare(s1->I_F_giveaways, s2->I_F_giveaways, ascending);
		if (colstring == _TAKE_AWAY)			return genericCompare(s1->I_F_takeaways, s2->I_F_takeaways, ascending);
		if (colstring == _GOALS_PER_GAME)       return genericCompare(s1->goals_per_game, s2->goals_per_game, ascending);
		return false;
		});
}

void VirtualListView::OnListSelect(wxListEvent& evt)
{
	Selection = this->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
//	Selection = evt.GetSelection();
	ItemData it(nullptr);

	switch (this->PositionButton)
	{
	case ListViewWin::ALLPLAYRSBUTTON: it = list[Selection]; break;
	case ListViewWin::DEFENSEBUTTON: it = defenselist[Selection]; break;
	case ListViewWin::FORWARDSBUTTON: it = forwardlist[Selection]; break;
	case ListViewWin::GOALIEBUTTON: it = goalielist[Selection]; break;
	}

	if (it.p)
		SelectionID = it.p->GetPlayerId();

	switch (winType)
	{
	case LISTVIEWID: static_cast<TeamLineupWin*>(m_parent)->SetSelection(it.p); break;
	case SEASONSTATSWIN: static_cast<SeasonStatsWin*>(m_parent)->SetSelection(it.p); break;
	}
}

void VirtualListView::ClickPositionButton(int button)
{
	if (PositionButton == button)
		return;
	PositionButton = button;
	RefreshOnUpdate();
//	PopulateListView();
}

bool VirtualListView::OnSearchButtonClick(wxString name)
{
	int count = this->GetItemCount();
	this->searchedItem = this->FindItemByName(name);
	if (this->searchedItem >= count)
	{
		wxBell();
		return false;
	}

	firstOnGetItemText = true;
//	afterFirstOnGetItemText = false;
	this->RefreshOnUpdate();
	return true;
}

void VirtualListView::OnScroll(wxScrollWinEvent& evt)
{
	ResetAfterSearchButtonClick();
	evt.Skip();
}

void VirtualListView::OnWheelScroll(wxMouseEvent& evt)
{
	ResetAfterSearchButtonClick();
	evt.Skip();
}

void VirtualListView::ResetAfterSearchButtonClick()
{
	firstOnGetItemText = false;
//	afterFirstOnGetItemText = false;
	searchedItem = 0;
	this->UpdateItemsCount();
}

void VirtualListView::InitalPopulateListView()
{
	wxString m_player_name = "";
	if (m_league)
	{
		wxVector<NHLplayer*> players = m_league->GetAllForwards();
		for (size_t i = 0; i < players.size(); ++i)
		{
			list.push_back(ItemData(players[i]));
			forwardlist.push_back(ItemData(players[i]));

			if (m_player_name.size() < players[i]->GetName().size())
				m_player_name = players[i]->GetName();
		}
		wxVector<NHLplayer*> defenseplayers = m_league->GetAllDefensemen();
		for (size_t i = 0; i < defenseplayers.size(); ++i)
		{
			list.push_back(ItemData(defenseplayers[i]));
			defenselist.push_back(ItemData(defenseplayers[i]));

			if (m_player_name.size() < defenseplayers[i]->GetName().size())
				m_player_name = defenseplayers[i]->GetName();
		}
		wxVector<NHLplayer*> goalieplayers = m_league->GetAllGoalies();
		for (size_t i = 0; i < goalieplayers.size(); ++i)
		{
			list.push_back(ItemData(goalieplayers[i]));
			goalielist.push_back(ItemData(goalieplayers[i]));

			if (m_player_name.size() < goalieplayers[i]->GetName().size())
				m_player_name = goalieplayers[i]->GetName();
		}
	}
	else if(m_team)
	{
		wxVector<NHLplayer>& players = m_team->GetForwards();
		for (size_t i = 0; i < players.size(); ++i)
		{
			list.push_back(ItemData(&players[i]));
			forwardlist.push_back(ItemData(&players[i]));
			
			if (m_player_name.size() < players[i].GetName().size())
				m_player_name = players[i].GetName();
		}
		wxVector<NHLplayer>& defenseplayers = m_team->GetDefensemen();
		for (size_t i = 0; i < defenseplayers.size(); ++i)
		{
			list.push_back(ItemData(&defenseplayers[i]));
			defenselist.push_back(ItemData(&defenseplayers[i]));

			if (m_player_name.size() < defenseplayers[i].GetName().size())
				m_player_name = defenseplayers[i].GetName();
		}
		wxVector<NHLplayer>& goalieplayers = m_team->GetGoalies();
		for (size_t i = 0; i < goalieplayers.size(); ++i)
		{
			list.push_back(ItemData(&goalieplayers[i]));
			goalielist.push_back(ItemData(&goalieplayers[i]));

			if (m_player_name.size() < goalieplayers[i].GetName().size())
				m_player_name = goalieplayers[i].GetName();
		}
	}

	wxFont F = this->GetFont();
	wxClientDC dc(this);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc)
	{
		this->RefreshOnUpdate();
		return;
	}
	wxColour C(0, 0, 0);
	gc->SetFont(gc->CreateFont(F, C));
	double width = 0.0;
	double height = 0.0;
	gc->GetTextExtent(m_player_name, &width, &height);
	this->SetColumnWidth(0, int(width + 20));
	delete gc;
	this->RefreshOnUpdate();
}

void VirtualListView::RefreshOnUpdate()
{
	this->UpdateItemsCount();
	this->Refresh();
}

void VirtualListView::UpdateItemsCount()
{
	if (searchedItem)
		this->SetItemCount(this->GetVirtualItemCount() - searchedItem);
	else
		this->SetItemCount(GetVirtualItemCount());
}

long VirtualListView::FindItemByName(wxString name)
{
	ItemData* begin = GetBeginIter();
	ItemData* end = GetEndIter();
	
	return std::find_if(begin, end, [name](ItemData i) {return name == i.p->GetName(); }) - begin;
}

ItemData VirtualListView::GetVirtualRowItem(long index) const
{
	switch (PositionButton)
	{
	case ListViewWin::ALLPLAYRSBUTTON:
		return list[index];
	case ListViewWin::DEFENSEBUTTON:
		return defenselist[index];
	case ListViewWin::FORWARDSBUTTON:
		return forwardlist[index];
	case ListViewWin::GOALIEBUTTON:
		return goalielist[index];
	}
	
	wxFAIL_MSG("switch did not catch index param in VirtualListView::GetItem!");
	return ItemData(nullptr);
}

wxString VirtualListView::GetVirtualColItem(ItemData* li, long col) const
{
	Stats* s = li->p->GetCurrentSeasonStats();
	wxString colstring = Col[col];
	if (colstring == PLAYERNAME)			return li->p->GetName();
	if (colstring == TEAM)					return li->p->GetTeam();
	if (colstring == PLAYER_RATING)			return li->p->GetGameScore_String();
	if (colstring == GOALS)					return wxString::Format("%i", s->I_F_goals);
	if (colstring == ASSISTS)				return wxString::Format("%i", s->I_F_primaryAssists + s->I_F_secondaryAssists);
	if (colstring == POSITION)				return s->Pos;
	if (colstring == SHOTS_ON_GOAL)			return wxString::Format("%i", s->I_F_shotsOnGoal);
	if (colstring == SHOT_ATTEMPTS)			return wxString::Format("%i", s->I_F_shotAttempts);
	if (colstring == SHOTS_BLOCKED)			return wxString::Format("%i", s->blockedshots);
	if (colstring == OVERALL)				return li->p->GetCurrentOverallRating_String();
	if (colstring == SHOT_ATTEMPTS_BLOCKED) return wxString::Format("%i", s->I_F_blockedShotAttempts);
	if (colstring == OFFENSE_)				return li->p->GetCurrentOffenseRating_String();
	if (colstring == DEFENSE_)				return li->p->GetCurrentDefenseRating_String();
	if (colstring == _GIVE_AWAY)			return wxString::Format("%i", s->I_F_giveaways);
	if (colstring == _TAKE_AWAY)			return wxString::Format("%i", s->I_F_takeaways);
	if (colstring == _GOALS_PER_GAME)		return li->p->GetGoalsAllowedPerGame_String(true);
	return "";
}

ItemData* VirtualListView::GetBeginIter()
{
	switch (PositionButton)
	{
	case ListViewWin::ALLPLAYRSBUTTON: return list.begin();
	case ListViewWin::DEFENSEBUTTON: return defenselist.begin();
	case ListViewWin::FORWARDSBUTTON: return forwardlist.begin();
	case ListViewWin::GOALIEBUTTON: return goalielist.begin();
	default: return nullptr;
	}
}

ItemData* VirtualListView::GetEndIter()
{
	switch (PositionButton)
	{
	case ListViewWin::ALLPLAYRSBUTTON: return list.end();
	case ListViewWin::DEFENSEBUTTON: return defenselist.end();
	case ListViewWin::FORWARDSBUTTON: return forwardlist.end();
	case ListViewWin::GOALIEBUTTON: return goalielist.end();
	default: return nullptr;
	}
}

long VirtualListView::GetVirtualItemCount() const
{
	switch (PositionButton)
	{
	case ListViewWin::ALLPLAYRSBUTTON: return list.size();
	case ListViewWin::DEFENSEBUTTON: return defenselist.size();
	case ListViewWin::FORWARDSBUTTON: return forwardlist.size();
	case ListViewWin::GOALIEBUTTON: return goalielist.size();
	default: return 0;
	}
}

SeasonStatsWin::SeasonStatsWin(wxWindow* w, wxWindowID id, wxPoint p, wxSize s, NHL_League* l) : wxFrame(w, id, "", p, s), m_parent(w), league(l)
{
	this->myteam = league->GetMYSeasonTeam();
	this->Bind(wxEVT_CLOSE_WINDOW, &SeasonStatsWin::OnClose, this);
	wxBoxSizer* ver = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hor = new wxBoxSizer(wxHORIZONTAL);

	P = new wxScrolled<wxPanel>(this, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetWidth() / 2, this->GetSize().GetHeight()), wxHSCROLL | wxVSCROLL);
	P->SetScrollbars(5, 5, 50, 50);
	P->EnableScrolling(true, true);
	P->SetBackgroundColour(wxColour(180, 180, 180));
	//P = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetWidth() / 2, this->GetSize().GetHeight()));

	List = new VirtualListView(this, LISTVIEWID, wxDefaultPosition, wxSize(s.GetWidth()/2, s.GetHeight()-5), league, nullptr, SEASONSTATSWIN);

	wxStaticText* eastern = InitStaticText(P, wxID_ANY, "Eastern", 25, wxFontFamily::wxFONTFAMILY_MODERN, wxFontWeight::wxFONTWEIGHT_EXTRABOLD, wxColour(0, 0, 0));
	wxStaticText* western = InitStaticText(P, wxID_ANY, "Western", 25, wxFontFamily::wxFONTFAMILY_MODERN, wxFontWeight::wxFONTWEIGHT_EXTRABOLD, wxColour(0, 0, 0));
	
	wxBoxSizer* rightV = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* TopH = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* BottomH = new wxBoxSizer(wxHORIZONTAL);
	rightV->Add(western, 0, wxALIGN_CENTER_HORIZONTAL);
	rightV->AddSpacer(10);
	TopH->Add(SetDivision("Central", league->GetCentralStandings()), 1 , wxALIGN_LEFT);
	TopH->AddSpacer(50);
	TopH->Add(SetDivision("Pacific", league->GetPacificStandings()), 1, wxALIGN_LEFT);
	rightV->Add(TopH, 1, wxALIGN_CENTER_HORIZONTAL);
	rightV->AddSpacer(10);
	rightV->Add(eastern, 0, wxALIGN_CENTER_HORIZONTAL);
	rightV->AddSpacer(10);
	BottomH->Add(SetDivision("Atlantic", league->GetAtlanticStandings()), 1, wxALIGN_LEFT);
	BottomH->AddSpacer(50);
	BottomH->Add(SetDivision("Metropolitan", league->GetMetropolitanStandings()), 1,  wxALIGN_LEFT);
	rightV->Add(BottomH, 1, wxALIGN_CENTER_HORIZONTAL);
	ver->Add(List, 1, wxALIGN_CENTER_HORIZONTAL);
	hor->Add(ver, 1, wxALIGN_CENTER_VERTICAL);
	P->SetSizer(rightV);
	hor->Add(P, 1, wxALIGN_CENTER_VERTICAL);

	this->SetSizer(hor);
	this->CenterOnScreen();
	this->Layout();
	this->Show();
}

void SeasonStatsWin::SetSelection(NHLplayer* p)
{

}

void SeasonStatsWin::OnClose(wxCloseEvent& evt)
{
	wxCommandEvent Evt(OnCloseSeasonStatWin, 1);
	wxPostEvent(m_parent, Evt);
	this->Destroy();
}

void SeasonStatsWin::OnEnterTeamName(wxMouseEvent& evt)
{
	NHLTeam* T = league->GetTeam(evt.GetId());
	wxStaticText* text = (wxStaticText*)this->FindItem(evt.GetId());
	if (!T)
	{
		wxMessageBox("league::GetTeam returned nullptr in SeasonStatsWin::OnEnterTeamName!!");
		return;
	}

	GameRecord* gr = T->GetGameRecord();
	wxString stringtip = T->GetTeamName() + ".\n You can click on the team name to get more info!";
	wxTipWindow* tip = new wxTipWindow(P, stringtip);
	if (text)
		tip->SetBoundingRect(text->GetScreenRect());
	tip->SetTipWindowPtr(&tip);
	tip->Show();
}

void SeasonStatsWin::OnExitTeamName(wxMouseEvent& evt)
{
	if (tip)
	{
		tip->Hide();
		tip->Destroy();
	}

	evt.Skip();
}

wxBoxSizer* SeasonStatsWin::SetDivision(wxString div, wxVector<NHLTeam*> v)
{
	wxBoxSizer* divH = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* divV = new wxBoxSizer(wxVERTICAL);

	wxStaticText* T = InitStaticText(P, wxID_ANY, div, 20, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_BOLD, wxColour(0, 0, 0));
	
	divH->Add(T, 0, wxALIGN_CENTER_VERTICAL);
	divV->Add(divH, 0, wxALIGN_CENTER_HORIZONTAL);

	wxBoxSizer* returnV = new wxBoxSizer(wxVERTICAL);
	returnV->Add(divV, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	returnV->AddSpacer(10);

	wxBoxSizer* pointsV = new wxBoxSizer(wxVERTICAL), * teamV = new wxBoxSizer(wxVERTICAL), * recordV = new wxBoxSizer(wxVERTICAL);

	wxStaticText* pointsT = InitStaticText(P, wxID_ANY, "Points", 17, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_BOLD, wxColour(0, 0, 0));
	wxStaticText* teamT	  =	InitStaticText(P, wxID_ANY, "Team", 17, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_BOLD, wxColour(0, 0, 0));
	wxStaticText* recordT = InitStaticText(P, wxID_ANY, "Record", 17, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_BOLD, wxColour(0, 0, 0));
	
	pointsV->Add(pointsT, 1, wxALIGN_LEFT);
	teamV->Add(teamT, 1, wxALIGN_LEFT);
	recordV->Add(recordT, 1, wxALIGN_LEFT);

	for (size_t i = 0; i < v.size(); ++i)
	{
		GameRecord* G = v[i]->GetRegularSeasonRecord();

		wxString record = wxString::Format("%i", G->wins) + " - " + wxString::Format("%i", G->ovL) + " - " + wxString::Format("%i", G->loss);

		wxColour teamnamecolor = myteam == v[i] ? wxColour(50, 58, 209) : wxColour(201, 24, 8);
		wxStaticText* pointst = InitStaticText(P, wxID_ANY, wxString::Format("%i", G->points), 15, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_BOLD, wxColour(11, 117, 39));
		wxStaticText* teamt   = InitStaticText(P, v[i]->GetTeamID(), v[i]->GetTeamabbr(), 15, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_BOLD, teamnamecolor);
		teamt->Bind(wxEVT_ENTER_WINDOW, &SeasonStatsWin::OnEnterTeamName, this);
		wxStaticText* recordt = InitStaticText(P, wxID_ANY, record, 15, wxFontFamily::wxFONTFAMILY_ROMAN, wxFontWeight::wxFONTWEIGHT_NORMAL, wxColour(0, 0, 0));

		pointsV->Add(pointst, 1, wxALIGN_CENTER_HORIZONTAL), teamV->Add(teamt, 1, wxALIGN_LEFT), recordV->Add(recordt, 1, wxALIGN_LEFT);
	}

	wxBoxSizer* boxH = new wxBoxSizer(wxHORIZONTAL);
	boxH->Add(pointsV, 1, wxALIGN_LEFT);
	boxH->Add(teamV, 1, wxALIGN_LEFT);
	boxH->Add(recordV, 1, wxALIGN_LEFT);

	returnV->Add(boxH, 1, wxALIGN_CENTER_HORIZONTAL);
	return returnV;
}

TeamLineupWin::TeamLineupWin(NHL_League* l, wxFrame* parent, NHLTeam* T) : wxFrame(m_parent, TeamWin::TEAMWIN, T->GetTeamabbr(), wxDefaultPosition, wxSize((parent->GetSize().x / 3) * 2, 
	(parent->GetSize().y / 3) * 2)), m_parent(parent), m_league(l), m_listV_color(50, 55, 52), m_team(T)
{
	this->Bind(wxEVT_CLOSE_WINDOW, &TeamLineupWin::Close, this);
	this->Bind(wxEVT_SIZE, &TeamLineupWin::OnChangeSize, this);
	this->Create();
}

void TeamLineupWin::ListSelect(wxListEvent& evt)
{
	m_listV_index = m_listV->GetFirstSelected();
	wxString id = m_listV->GetItemText(m_listV_index, 8);
	long l = 0;
	if (!id.ToLong(&l))
	{
		wxMessageBox("ToLong failed in mainwindow::ONListSelect! string id is: " + id);
		return;
	}

	m_player = m_team->FindPlayerWithID(l);
	if (m_buttonid != -1)
	{
		wxButton* b = (wxButton*)this->FindItem(m_buttonid);
		if (!b)
		{
			wxMessageBox("Could not find button in mainwindow::OnListSelect!");
			return;
		}

		if (m_player->GetName() == b->GetLabel())
		{
			wxMessageBox("You can not replace a player with the same player.");
			m_player = nullptr;
			m_buttonid = -1;
			return;
		}

		int message = wxMessageBox("Do you want to replace " + b->GetLabel() + " with " + m_player->GetName() + "?", "Confirm", wxYES_NO);
		if (message == wxYES)
		{
			NHLplayer* out = m_team->ReplaceStarter(m_player, GetLine(m_buttonid - LWING1), GetPosition(m_buttonid - LWING1), GetPosition(m_buttonid - LWING1));
			if (out)
			{
				m_listV->SetItem(m_listV_index, 7, "No");
				wxMessageBox("You have replaced " + out->GetName() + " with " + m_player->GetName());
				b->SetLabel(m_player->GetName());
				this->Layout();
				m_player = nullptr;
				m_buttonid = -1;
				return;
			}

			wxMessageBox("You can not replace " + b->GetLabel() + " with " + m_player->GetName() + " because they are not playing the same position or they are both already in the lineup.");
			m_player = nullptr;
			m_buttonid = -1;
		}
		m_player = nullptr;
		m_buttonid = -1;
	}
}

void TeamLineupWin::OnChangeSize(wxSizeEvent& evt)
{
//	vlv->SetSize(wxSize(this->GetSize().x / 2 - 15, (this->GetSize().y / 3) * 2));
//	m_panel->SetSize(wxSize(this->GetSize().x / 2 - 5, (this->GetSize().y / 3) * 2));
}

void TeamLineupWin::ListSelect()
{
	if (m_buttonid != -1)
	{
		wxButton* b = (wxButton*)this->FindItem(m_buttonid);
		if (!b)
		{
			wxMessageBox("Could not find button in mainwindow::OnListSelect!");
			return;
		}

		if (m_player->GetName() == b->GetLabel())
		{
			wxMessageBox("You can not replace a player with the same player.");
			m_player = nullptr;
			m_buttonid = -1;
			return;
		}

		int message = wxMessageBox("Do you want to replace " + b->GetLabel() + " with " + m_player->GetName() + "?", "Confirm", wxYES_NO);
		if (message == wxYES)
		{
			NHLplayer* out = m_team->ReplaceStarter(m_player, GetLine(m_buttonid - LWING1), GetPosition(m_buttonid - LWING1), GetPosition(m_buttonid - LWING1));
			if (out)
			{
			//	m_listV->SetItem(m_listV_index, 7, "No");
				wxMessageBox("You have replaced " + out->GetName() + " with " + m_player->GetName());
				b->SetLabel(m_player->GetName());
				this->Layout();
				m_player = nullptr;
				m_buttonid = -1;
				return;
			}

			wxMessageBox("You can not replace " + b->GetLabel() + " with " + m_player->GetName() + " because they are not playing the same position or they are both already in the lineup.");
			m_player = nullptr;
			m_buttonid = -1;
		}
		m_player = nullptr;
		m_buttonid = -1;
	}
}

void TeamLineupWin::Create()
{
	if (!m_team)
	{
		wxMessageBox("Error! Could not find team!");
		return;
	}

	Lines* lines = m_team->GetLines();

	wxFont F;
	F.SetPixelSize(wxSize(20, 40));
	F.MakeBold();

	int width = this->GetSize().x / 12;
	int height = 0;
	wxSize proportionSize(width, width * (2.0 / 6.0));
	canvas = new Canvas(this, CustomControl::CUSTOMWIN, wxDefaultPosition, "Trade Player", this->FromDIP(proportionSize));
	
	wxBoxSizer* main = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* midLeft = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* midRight = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lower = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* left = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* right = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightpanel = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Forward = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* defense = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Goalie = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* leftwing = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* centerice = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightwing = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* leftdef = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightdef = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* goalievert = new wxBoxSizer(wxVERTICAL);

	wxFont titles(wxSize(10, 20), wxFontFamily::wxFONTFAMILY_MODERN, wxFontStyle::wxFONTSTYLE_MAX, wxFontWeight::wxFONTWEIGHT_EXTRAHEAVY);
	wxStaticText* lefttitle = new wxStaticText(this, LEFTTITLE, "All Players");
	wxStaticText* righttitle = new wxStaticText(this, RIGHTTITLE, "Lines");
	SetFont(lefttitle, titles);
	SetFont(righttitle, titles);

	wxButton* b_changeLineup = new wxButton(this, TeamWin::CHANGELINEUP, "Change Lineup");
	search = new wxSearchCtrl(this, SEARCHBUTTON, "Name", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	search->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &TeamLineupWin::OnSearchBtnClick, this);
	wxButton* b_allplayers = new wxButton(this, ListViewWin::ALLPLAYRSBUTTON, "All Players");
	wxButton* b_forwards = new wxButton(this, ListViewWin::FORWARDSBUTTON, "Forwards");
	wxButton* b_defense = new wxButton(this, ListViewWin::DEFENSEBUTTON, "Defensemen");
	wxButton* b_goalie = new wxButton(this, ListViewWin::GOALIEBUTTON, "Goalies");

	b_allplayers->Bind(wxEVT_BUTTON, &TeamLineupWin::ClickSortButton, this);
    b_forwards->Bind(wxEVT_BUTTON, &TeamLineupWin::ClickSortButton, this);
	b_defense->Bind(wxEVT_BUTTON, &TeamLineupWin::ClickSortButton, this);
	b_goalie->Bind(wxEVT_BUTTON, &TeamLineupWin::ClickSortButton, this);

	b_changeLineup->Bind(wxEVT_ENTER_WINDOW, &TeamLineupWin::OnMouseEnterChangeLineup, this);
	b_changeLineup->Bind(wxEVT_LEAVE_WINDOW, &TeamLineupWin::OnMouseExitChangeLineup, this);

	vlv = new VirtualListView(this, ListViewWin::LISTVIEWID, wxDefaultPosition, wxSize(this->GetSize().x / 2 - 15, (this->GetSize().y / 3) * 2), nullptr, m_team, LISTVIEWID);

	m_panel = new wxPanel(this, TeamWin::TEAMWINPANEL, wxDefaultPosition, wxSize(this->GetSize().x / 2 - 5, (this->GetSize().y / 3) * 2));
	m_panel->SetBackgroundColour(b_allplayers->GetBackgroundColour());

	wxSize fontsize = wxSize(7, 14);
	wxFont playerlistfont(fontsize, wxFontFamily::wxFONTFAMILY_DECORATIVE, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_EXTRABOLD);

	b_changeLineup->SetFont(playerlistfont);
	b_allplayers->SetFont(playerlistfont);
	b_forwards->SetFont(playerlistfont);
	b_defense->SetFont(playerlistfont);
	b_goalie->SetFont(playerlistfont);

	midLeft->Add(b_allplayers, 1, wxALIGN_BOTTOM);
	midLeft->Add(b_forwards, 1, wxALIGN_BOTTOM);
	midLeft->Add(b_defense, 1, wxALIGN_BOTTOM);
	midLeft->Add(b_goalie, 1, wxALIGN_BOTTOM);
	

	midRight->Add(b_changeLineup, 1, wxALIGN_BOTTOM);

	wxButton* lwing1 = new wxButton(m_panel, TeamWin::LWING1, lines->line1.left->GetName());
	lwing1->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	lwing1->SetFont(playerlistfont);
	
	wxButton* center1 = new wxButton(m_panel, TeamWin::CENTER1, lines->line1.center->GetName());
	center1->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	center1->SetFont(playerlistfont);
	
	wxButton* rwing1 = new wxButton(m_panel, TeamWin::RWING1, lines->line1.right->GetName());
	rwing1->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rwing1->SetFont(playerlistfont);
	
	wxButton* lwing2 = new wxButton(m_panel, TeamWin::LWING2, lines->line2.left->GetName());
	lwing2->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	lwing2->SetFont(playerlistfont);
	
	wxButton* center2 = new wxButton(m_panel, TeamWin::CENTER2, lines->line2.center->GetName());
	center2->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	center2->SetFont(playerlistfont);
	
	wxButton* rwing2 = new wxButton(m_panel, TeamWin::RWING2, lines->line2.right->GetName());
	rwing2->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rwing2->SetFont(playerlistfont);
	
	wxButton* lwing3 = new wxButton(m_panel, TeamWin::LWING3, lines->line3.left->GetName());
	lwing3->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	lwing3->SetFont(playerlistfont);
	
	wxButton* center3 = new wxButton(m_panel, TeamWin::CENTER3, lines->line3.center->GetName());
	center3->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	center3->SetFont(playerlistfont);
	
	wxButton* rwing3 = new wxButton(m_panel, TeamWin::RWING3, lines->line3.right->GetName());
	rwing3->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rwing3->SetFont(playerlistfont);
	
	wxButton* lwing4 = new wxButton(m_panel, TeamWin::LWING4, lines->line4.left->GetName());
	lwing4->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	lwing4->SetFont(playerlistfont);
	
	wxButton* center4 = new wxButton(m_panel, TeamWin::CENTER4, lines->line4.center->GetName());
	center4->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	center4->SetFont(playerlistfont);
	
	wxButton* rwing4 = new wxButton(m_panel, TeamWin::RWING4, lines->line4.right->GetName());
	rwing4->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rwing4->SetFont(playerlistfont);
	
	wxButton* leftdef1 = new wxButton(m_panel, TeamWin::LEFTDEF1, lines->paring1.d1->GetName());
	leftdef1->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	leftdef1->SetFont(playerlistfont);
	
	wxButton* rightdef1 = new wxButton(m_panel, TeamWin::RIGHTDEF1, lines->paring1.d2->GetName());
	rightdef1->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rightdef1->SetFont(playerlistfont);
	
	wxButton* leftdef2 = new wxButton(m_panel, TeamWin::LEFTDEF2, lines->paring2.d1->GetName());
	leftdef2->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	leftdef2->SetFont(playerlistfont);
	
	wxButton* rightdef2 = new wxButton(m_panel, TeamWin::RIGHTDEF2, lines->paring2.d2->GetName());
	rightdef2->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rightdef2->SetFont(playerlistfont);
	
	wxButton* leftdef3 = new wxButton(m_panel, TeamWin::LEFTDEF3, lines->paring3.d1->GetName());
	leftdef3->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	leftdef3->SetFont(playerlistfont);
	
	wxButton* rightdef3 = new wxButton(m_panel, TeamWin::RIGHTDEF3, lines->paring3.d2->GetName());
	rightdef3->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	rightdef3->SetFont(playerlistfont);
	
	wxButton* goalie = new wxButton(m_panel, TeamWin::GOALIE, lines->goalie->GetName());
	goalie->Bind(wxEVT_BUTTON, &TeamLineupWin::LineupButtonPress, this);
	goalie->SetFont(playerlistfont);


	leftwing->Add(lwing1, 1, wxALIGN_CENTER_HORIZONTAL);
	leftwing->AddSpacer(10);
	leftwing->Add(lwing2, 1, wxALIGN_CENTER_HORIZONTAL);
	leftwing->AddSpacer(10);
	leftwing->Add(lwing3, 1, wxALIGN_CENTER_HORIZONTAL);
	leftwing->AddSpacer(10);
	leftwing->Add(lwing4, 1, wxALIGN_CENTER_HORIZONTAL);

	Forward->Add(leftwing, 1, wxALIGN_CENTER_VERTICAL);

	centerice->Add(center1, 1, wxALIGN_CENTER_HORIZONTAL);
	centerice->AddSpacer(10);
	centerice->Add(center2, 1, wxALIGN_CENTER_HORIZONTAL);
	centerice->AddSpacer(10);
	centerice->Add(center3, 1, wxALIGN_CENTER_HORIZONTAL);
	centerice->AddSpacer(10);
	centerice->Add(center4, 1, wxALIGN_CENTER_HORIZONTAL);

	Forward->AddSpacer(5);
	Forward->Add(centerice, 1, wxALIGN_CENTER_VERTICAL);

	rightwing->Add(rwing1, 1, wxALIGN_CENTER_HORIZONTAL);
	rightwing->AddSpacer(10);
	rightwing->Add(rwing2, 1, wxALIGN_CENTER_HORIZONTAL);
	rightwing->AddSpacer(10);
	rightwing->Add(rwing3, 1, wxALIGN_CENTER_HORIZONTAL);
	rightwing->AddSpacer(10);
	rightwing->Add(rwing4, 1, wxALIGN_CENTER_HORIZONTAL);

	Forward->AddSpacer(5);
	Forward->Add(rightwing, 1, wxALIGN_CENTER_VERTICAL);

	leftdef->Add(leftdef1, 1, wxALIGN_CENTER_HORIZONTAL);
	leftdef->AddSpacer(10);
	leftdef->Add(leftdef2, 1, wxALIGN_CENTER_HORIZONTAL);
	leftdef->AddSpacer(10);
	leftdef->Add(leftdef3, 1, wxALIGN_CENTER_HORIZONTAL);

	defense->Add(leftdef, 1, wxALIGN_CENTER_VERTICAL);

	rightdef->Add(rightdef1, 1, wxALIGN_CENTER_HORIZONTAL);
	rightdef->AddSpacer(10);
	rightdef->Add(rightdef2, 1, wxALIGN_CENTER_HORIZONTAL);
	rightdef->AddSpacer(10);
	rightdef->Add(rightdef3, 1, wxALIGN_CENTER_HORIZONTAL);

	defense->AddSpacer(10);
	defense->Add(rightdef, 1, wxALIGN_CENTER_VERTICAL);

	goalievert->Add(goalie, 1, wxALIGN_CENTER_HORIZONTAL);
	Goalie->Add(goalievert, 1, wxALIGN_CENTER_VERTICAL);

	wxStaticText* t = new wxStaticText(this, TeamWin::TEAMNAME, m_team->GetTeamName(), wxPoint(this->GetSize().x / 2, this->GetSize().y / 2));

	t->SetFont(F);
	t->SetForegroundColour(wxColor(0, 0, 233));

	left->Add(lefttitle, 1, wxALIGN_CENTER_HORIZONTAL);
	left->Add(search, wxALIGN_LEFT);
	left->AddSpacer(20);
	left->Add(midLeft, 1, wxALIGN_LEFT);
	left->Add(vlv, 1, wxALIGN_CENTER_HORIZONTAL);

	rightpanel->Add(righttitle, 1, wxALIGN_CENTER_HORIZONTAL);
	rightpanel->Add(midRight, 1, wxALIGN_CENTER_HORIZONTAL);

	right->Add(Forward, 1, wxALIGN_CENTER_HORIZONTAL);
	right->Add(defense, 1, wxALIGN_CENTER_HORIZONTAL);
	right->Add(Goalie, 1, wxALIGN_CENTER_HORIZONTAL);

	rightpanel->Add(m_panel, 1, wxALIGN_CENTER_HORIZONTAL);
	m_panel->SetSizer(right);
	m_panel->Layout();

	lower->AddSpacer(10);
	lower->Add(left, 1, wxALIGN_CENTER_VERTICAL);
	lower->AddSpacer(10);
	lower->Add(rightpanel, 1, wxALIGN_CENTER_VERTICAL);
	lower->AddSpacer(10);

	main->Add(t, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(canvas, 1, wxALIGN_RIGHT | wxRIGHT, 10);
//	main->Add(search, wxALIGN_LEFT | wxLEFT, 10);
	main->Add(lower, 1, wxALIGN_CENTER_HORIZONTAL);
	main->AddSpacer(10);

	this->CenterOnParent();
	this->SetSizer(main);
	this->Layout();
	
	this->Show();
}

void TeamLineupWin::SetFont(wxStaticText*& t, wxFont& f)
{
	t->SetFont(f);
}

void TeamLineupWin::LineupButtonPress(wxCommandEvent& evt)
{
	m_buttonid = evt.GetId();
	if (m_player)
	{
		wxButton* b = (wxButton*)this->FindItem(m_buttonid);
		if (!b)
		{
			wxMessageBox("Could not find button in mainwindow::LineupButtonPress!");
			return;
		}

		if (m_player->GetName() == b->GetLabel())
		{
			wxMessageBox("You can not replace a player with the same player.");
			m_player = nullptr;
			m_buttonid = -1;
			return;
		}

		int message = wxMessageBox("Do you want to replace " + b->GetLabel() + " with " + m_player->GetName() + "?", "Confirm", wxYES_NO);
		if (message == wxYES)
		{
			NHLplayer* out = m_team->ReplaceStarter(m_player, GetLine(m_buttonid - LWING1), GetPosition(m_buttonid - LWING1), GetPosition(m_buttonid - LWING1));
			if (out)
			{
	//			m_listV->SetItem(m_listV_index, 7, "No");
				wxMessageBox("You have replaced " + out->GetName() + " with " + m_player->GetName());
				b->SetLabel(m_player->GetName());
				this->Layout();
				m_player = nullptr;
				m_buttonid = -1;
				return;
			}

			wxMessageBox("You can not replace " + b->GetLabel() + " with " + m_player->GetName() + " because they are not playing the same position or they are both already in the lineup.");
			m_player = nullptr;
			m_buttonid = -1;
		}
		m_player = nullptr;
		m_buttonid = -1;
	}
}

void TeamLineupWin::ClickSortButton(wxCommandEvent& evt)
{
	vlv->ClickPositionButton(evt.GetId());
	/*
	if (evt.GetId() == m_listV_sort_button) return;

	m_listV_sort_button = evt.GetId();
	m_listV->DeleteAllItems();

	switch (m_listV_sort_button)
	{
	case ListViewWin::ALLPLAYRSBUTTON:
	{
		m_team->AppendPlayerInfotoListBox(m_listV);
		break;
	}
	case ListViewWin::FORWARDSBUTTON:
	{
		m_team->ForwardInfotoListBox(m_listV);
		break;
	}
	case ListViewWin::DEFENSEBUTTON:
	{
		m_team->DefenseInfotoListBox(m_listV);
		break;
	}
	case ListViewWin::GOALIEBUTTON:
	{
		m_team->GoalieInfotoListBox(m_listV);
		break;
	}
	}
	*/
}

void TeamLineupWin::ClickChangeLineupButton(wxCommandEvent& evt)
{

}

void TeamLineupWin::OnSearchBtnClick(wxCommandEvent& evt)
{
	vlv->OnSearchButtonClick(evt.GetString());
//	vlv->Refresh();
//	vlv->ResetAfterSearchButtonClick();
}

void TeamLineupWin::Close(wxCloseEvent& evt)
{
	this->Destroy();
	m_parent->Enable();
	m_parent->SetFocus();
}

void TeamLineupWin::OnMouseEnterChangeLineup(wxMouseEvent& evt)
{
	wxButton* b = (wxButton*)this->FindItem(TeamWin::CHANGELINEUP);
	if (!b)
		return;

	tip = new wxTipWindow(this, "By clicking this button you can switch players between lines, or swapping thier position on the current line with another linemate.");
	tip->SetBoundingRect(b->GetScreenRect());
	tip->SetTipWindowPtr(&tip);
	tip->Show();
}

void TeamLineupWin::OnMouseExitChangeLineup(wxMouseEvent& evt)
{
	if (tip)
	{
		tip->Hide();
	}

	evt.Skip();
}

void TeamLineupWin::SetSelection(NHLplayer* p)
{
	m_player = p;
	ListSelect();
}

char TeamLineupWin::GetPosition(int id)
{
	switch (id)
	{
	case 0:
	case 3:
	case 6:
	case 9: return Position::L;
	case 1:
	case 4:
	case 7:
	case 10: return Position::C;
	case 2:
	case 5:
	case 8:
	case 11: return Position::R;
	case 12:
	case 14:
	case 16: return Position::L;
	case 13:
	case 15:
	case 17: return Position::R;
	case 18: return Position::G;
	}

	wxMessageBox("param id in mainwindow::GetPosition did not match any thing in the switch statement! Returning invalid char!");
	return 'I';
}

int TeamLineupWin::GetLine(int id)
{
	switch (id)
	{
	case 0:
	case 1:
	case 2: return 0;
	case 3:
	case 4:
	case 5: return 1;
	case 6:
	case 7:
	case 8: return 2;
	case 9:
	case 10:
	case 11: return 2;
	case 12:
	case 13: return 0;
	case 14:
	case 15: return 1;
	case 16:
	case 17: return 2;
	default: return -1;
	}
}

ChangeTeamLineups::ChangeTeamLineups(wxFrame* w, NHL_League* l) : wxFrame(w, LINEUPCHANGEWIN, wxT("Lineup Change"), wxDefaultPosition, wxSize(8 * 185, 4 * 185)), m_parent(w), league(l)
{
	this->Bind(wxEVT_CLOSE_WINDOW, &ChangeTeamLineups::OnClose, this);
	wxBoxSizer* main = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Rowone = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowtwo = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowthree = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowfour = new wxBoxSizer(wxHORIZONTAL);

	for (size_t i = 0; i < 32; ++i)
	{
		NHLTeam* t = league->GetTeam(i);
		wxButton* b = new wxButton(this, i, "", wxDefaultPosition, wxSize(185, 185));
		b->SetBitmap(*t->GetTeamLogo());
		b->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ChangeTeamLineups::OnButtonClick, this);
		if (i < 8) Rowone->Add(b, 1, wxALIGN_CENTRE_VERTICAL);
		else if (i < 16) Rowtwo->Add(b, 1, wxALIGN_CENTER_VERTICAL);
		else if (i < 24) Rowthree->Add(b, 1, wxALIGN_CENTER_VERTICAL);
		else Rowfour->Add(b, 1, wxALIGN_CENTER_VERTICAL);
	}

	main->Add(Rowone, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowtwo, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowthree, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowfour, 1, wxALIGN_CENTER_HORIZONTAL);
	this->SetSizer(main);
	this->Layout();

	this->CenterOnParent();
	Show();
}

void ChangeTeamLineups::OnButtonClick(wxCommandEvent& evt)
{
	NHLTeam* t = league->GetTeam(evt.GetId());
	if (!t)
	{
		wxMessageBox("NHLTeam is nullptr in ChangeTeamLineups::OnButtonClick!!");
		return;
	}

	tl = new TeamLineupWin(league, this, t);
	this->Disable();
}

void ChangeTeamLineups::OnClose(wxCloseEvent& evt)
{
	m_parent->Enable();
	m_parent->SetFocus();
	this->Destroy();
}

StartSeason::StartSeason(wxFrame* f, NHL_League* l) : wxFrame(f, StartSeasonWin::STARTSEASONWIN, wxT("Start New Season"), wxDefaultPosition, wxSize(8 * 185, 5 * 185)), m_parent(f), league(l)
{
	P = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(8 * 185, 185));
	panelsizerV = new wxBoxSizer(wxVERTICAL);
	panelsizerH = new wxBoxSizer(wxHORIZONTAL);
	panelsizerH->Add(panelsizerV, 1, wxALIGN_CENTER_VERTICAL);
	P->SetSizer(panelsizerH);

	this->Bind(wxEVT_CLOSE_WINDOW, &StartSeason::OnClose, this);
	wxBoxSizer* main = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Rowone = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowtwo = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowthree = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowfour = new wxBoxSizer(wxHORIZONTAL);

	for (size_t i = 0; i < 32; ++i)
	{
		NHLTeam* t = league->GetTeam(i);
		wxButton* b = new wxButton(this, i, "", wxDefaultPosition, wxSize(185, 185));
		b->SetBitmap(*t->GetTeamLogo());
		b->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &StartSeason::OnButtonClick, this);
		if (i < 8) Rowone->Add(b, 1, wxALIGN_CENTRE_VERTICAL);
		else if (i < 16) Rowtwo->Add(b, 1, wxALIGN_CENTER_VERTICAL);
		else if (i < 24) Rowthree->Add(b, 1, wxALIGN_CENTER_VERTICAL);
		else Rowfour->Add(b, 1, wxALIGN_CENTER_VERTICAL);
	}

	main->Add(P, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowone, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowtwo, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowthree, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowfour, 1, wxALIGN_CENTER_HORIZONTAL);
	this->SetSizer(main);
	this->Layout();

	this->CenterOnParent();
	Show();
}

StartSeason::~StartSeason()
{

}

void StartSeason::OnButtonClick(wxCommandEvent& evt)
{
	NHLTeam* T = league->GetTeam(evt.GetId());
	if (!T)
	{
		wxMessageBox("Team is nullptr in StartSeason::OnButtonClick!!");
		return;
	}
	teamselected = T;
	if (myTeam)
	{
		BitImage* temp = new BitImage(P, wxID_ANY, T->GetTeamLogo(), this->GetBackgroundColour());
		if (!panelsizerV->Replace(myTeam, temp))
		{
			wxMessageBox("panelsizerH failed at switching image!!");
			temp->Destroy();
			return;
		}
		else
		{
			myTeam->Destroy();
			myTeam = temp;
			wxCommandEvent Evt(OnSeasonStart, 1);
			wxPostEvent(m_parent, Evt);
		}
	}
	else
	{
		myTeam = new BitImage(P, wxID_ANY, T->GetTeamLogo(), this->GetBackgroundColour());
		panelsizerV->Add(myTeam, 1, wxALIGN_CENTER_HORIZONTAL);
		wxCommandEvent Evt(OnSeasonStart, 1);
		wxPostEvent(m_parent, Evt);
	}

	this->Layout();
	this->Refresh();
}

void StartSeason::OnClose(wxCloseEvent& evt)
{
	m_parent->Enable();
	m_parent->SetFocus();
	this->Destroy();
}


TeamSelect::TeamSelect(wxFrame* f, NHL_League* l) : wxFrame(f, TeamSelectWindow::TEAMSELECTWIN, "Select Teams", wxDefaultPosition, wxSize(8 * 185, 5 * 200)), m_parent(f), league(l)
{
	this->SetBackgroundColour(wxColour(255, 255, 255));
	this->Bind(wxEVT_CLOSE_WINDOW, &TeamSelect::OnClose, this);
	this->Bind(CanvasClick, &TeamSelect::OnStartGame, this);

	int difference = 4 * 185;
	wxBoxSizer* Top = new wxBoxSizer(wxHORIZONTAL);
	Left = new wxBoxSizer(wxVERTICAL);
	Right = new wxBoxSizer(wxVERTICAL);

//	Middle = new wxBoxSizer(wxHORIZONTAL);
	Top->SetMinSize(wxSize(this->GetSize().GetWidth(), this->GetSize().GetHeight() - difference));

	first = new wxBoxSizer(wxVERTICAL);
//	first->SetMinSize(wxSize(this->GetSize().GetWidth() / 3, difference));

	second = new wxBoxSizer(wxVERTICAL);
//	second->SetMinSize(wxSize(this->GetSize().GetWidth() / 3, difference));

	last = new wxBoxSizer(wxVERTICAL);
//	last->SetMinSize(wxSize(this->GetSize().GetWidth() / 3, difference));

	left = new wxStaticText(this, wxID_ANY, "NHL");
	left->SetBackgroundColour(this->GetBackgroundColour());
	left->SetForegroundColour(wxColour(130, 125, 124));

	right = new wxStaticText(this, wxID_ANY, "NHL");
	right->SetBackgroundColour(this->GetBackgroundColour());
	right->SetForegroundColour(wxColour(130, 125, 124));

	wxStaticText* at = new wxStaticText(this, wxID_ANY, "@");
	wxStaticText* away = new wxStaticText(this, wxID_ANY, "Away");
	wxStaticText* home = new wxStaticText(this, wxID_ANY, "Home");

	wxFont F;
	F.SetFamily(wxFontFamily::wxFONTFAMILY_ROMAN);
	F.SetPixelSize(wxSize(20, 20 * (36.0 / 17.0)));

	away->SetSize(wxSize(20, 20 * (36.0 / 17.0)));
	away->SetBackgroundColour(this->GetBackgroundColour());
	away->SetForegroundColour("white");
	away->SetFont(F);

	home->SetSize(wxSize(20, 20 * (36.0 / 17.0)));
	home->SetBackgroundColour(this->GetBackgroundColour());
	home->SetForegroundColour("white");
	home->SetFont(F);

	F.SetPixelSize(wxSize(50, 50 * (36.0 / 17.0)));
	at->SetBackgroundColour(this->GetBackgroundColour());
	at->SetForegroundColour("red");
	at->SetFont(F);

	F.SetPixelSize(wxSize(20, 20 * (36.0 / 17.0)));
	left->SetFont(F);
	right->SetFont(F);

	Right->Add(right, 1, wxALIGN_RIGHT);
	Left->Add(left, 1, wxALIGN_LEFT);

	Middle = new wxBoxSizer(wxHORIZONTAL);
	Middle->Add(Left, 1, wxALIGN_TOP);
	Middle->AddSpacer(20);
	Middle->Add(Right, 1, wxALIGN_TOP);

	first->Add(away, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP);
	second->Add(Middle, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP);
	second->Add(at, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP);
	last->Add(home, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP);

	Top->Add(first,1);
//	Top->Add(Left, 0, wxALIGN_CENTER_VERTICAL);
	Top->Add(second, 1, wxALIGN_CENTER_VERTICAL);
//	Top->Add(Right, 0, wxALIGN_CENTER_VERTICAL);
	Top->Add(last, 1);

	wxBoxSizer* main = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Rowone = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowtwo = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowthree = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Rowfour = new wxBoxSizer(wxHORIZONTAL);

	for (size_t i = 0; i < 32; ++i)
	{
		NHLTeam* t = league->GetTeam(i);
		wxButton* b = new wxButton(this, i, "", wxDefaultPosition, wxSize(185, 185));
		b->SetBitmap(*t->GetTeamLogo());
		b->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TeamSelect::OnButtonClick, this);
		if (i < 8) Rowone->Add(b, 1, wxALIGN_CENTRE_VERTICAL);
		else if (i < 16) Rowtwo->Add(b, 1, wxALIGN_CENTER_VERTICAL);
		else if (i < 24) Rowthree->Add(b, 1, wxALIGN_CENTER_VERTICAL);
		else Rowfour->Add(b, 1, wxALIGN_CENTER_VERTICAL);
	}

	int width = this->GetSize().x / 12;
	int height = 0;
	wxSize proportionSize(width, width * (2.0 / 6.0));
	startgame = new Canvas(this, CustomControl::CUSTOMWIN, wxPoint(this->GetSize().GetWidth() - (proportionSize.GetWidth() + 40), proportionSize.GetHeight()), "Start Game", this->FromDIP(proportionSize));

	main->Add(Top, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowone, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowtwo, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowthree, 1, wxALIGN_CENTER_HORIZONTAL);
	main->Add(Rowfour, 1, wxALIGN_CENTER_HORIZONTAL);
	this->SetSizer(main);
	this->Layout();

	this->CenterOnParent();
	Show();
}

void TeamSelect::OnClose(wxCloseEvent& evt)
{
	m_parent->Enable();
	m_parent->SetFocus();
	this->Destroy();
}

void TeamSelect::OnButtonClick(wxCommandEvent& evt)
{
	NHLTeam* t = league->GetTeam(evt.GetId());
	if (!t)
	{
		wxMessageBox("Team is nullptr in TeamSelect::OnButtonClick");
		return;
	}

	if (firstround == false)
	{
		firstround = true;
		a = true;
		h = false;
		left->SetLabel(t->GetTeamabbr(true));
		Away = new BitImage(this, wxID_ANY, t->GetTeamLogo(), this->GetBackgroundColour());
		first->Add(Away, 1, wxALIGN_CENTER_HORIZONTAL);
		m_away = t;
	}

	else if (a == true)
	{
		h = true;
		a = false;
		m_home = t;
		right->SetLabel(t->GetTeamabbr(true));
		if (last->GetItemCount() > 1)
		{
			BitImage* temp = new BitImage(this, wxID_ANY, t->GetTeamLogo(), this->GetBackgroundColour());
			if (last->Replace(Home, temp))
			{
				Home->Destroy();
				Home = temp;
			}
			else
				temp->Destroy();
		}
		else
		{
			Home = new BitImage(this, wxID_ANY, t->GetTeamLogo(), this->GetBackgroundColour());
			last->Add(Home, 1, wxALIGN_CENTER_HORIZONTAL);
		}
	}
	else if (h == true)
	{
		a = true;
		h = false;
		m_away = t;
		left->SetLabel(t->GetTeamabbr(true));
		if (last->GetItemCount() > 1)
		{
			BitImage* temp = new BitImage(this, wxID_ANY, t->GetTeamLogo(), this->GetBackgroundColour());
			if (first->Replace(Away, temp))
			{
				Away->Destroy();
				Away = temp;
			}
			else
				temp->Destroy();
		}
		else
		{
			Away = new BitImage(this, wxID_ANY, t->GetTeamLogo(), this->GetBackgroundColour());
			first->Add(Away, 1, wxALIGN_CENTER_HORIZONTAL);
		}
	}

	this->Layout();
	this->Refresh();
}

void TeamSelect::OnStartGame(wxCommandEvent& evt)
{
	if (!m_away || !m_home) return;

	if (m_away == m_home) return;
	gf = new GameFrame(this, league, m_away, m_home, 7);
}

void TeamSelect::OnThreadEvent(wxThreadEvent& evt)
{
	wxMessageBox("Exited successfully!!");
	this->Enable();
	this->SetFocus();
}

void SeasonGameReady(wxWindow* v, NHLTeam* away, NHLTeam* home, int series, int round)
{
	mainwindow* m = static_cast<mainwindow*>(v);
	m->SeasonGame(away, home, series, round);
}

mainwindow::mainwindow() : wxFrame(NULL, MainWin::MAINWIN, "NHL", wxPoint(100, 100), wxSize(1200, 674)), league(SeasonGameReady, this)
{
	wxMenu* a = new wxMenu();
	wxMenu* b = new wxMenu();
	wxMenuBar* menu = new wxMenuBar();
	a->Append(new wxMenuItem(a, MainWin::MAINWINGAME, "New Game"));
	a->Append(new wxMenuItem(a, MainWin::LINEUPCHANGE, "Change Lineups"));
	a->Append(new wxMenuItem(a, MainWin::STARTNEWSEASON, "Start New Season"));
	menu->Append(a, "File");
	menu->Append(b, "Options");
	this->SetMenuBar(menu);

	this->Bind(wxEVT_CLOSE_WINDOW, &mainwindow::CloseSelf, this);
	this->Bind(wxEVT_THREAD, &mainwindow::GameOutcome, this);
	this->Bind(OnSeasonStart, &mainwindow::OnNewSeasonStart, this);
	this->Bind(OnCloseSeasonStatWin, &mainwindow::OnSeasonStatWinClose, this);
	this->Bind(PlayoffStartEvent, &mainwindow::OnPlayoffStart, this);
	this->Bind(RegularSeasonOver, &mainwindow::RegularSeasonOverEvent, this);
	this->Bind(ClosePlayoffView, &mainwindow::OnPlayoffViewClose, this);
	this->Bind(FirstRoundOver, &mainwindow::OnFirstRoundOver, this);
	this->Bind(SecondRoundOver, &mainwindow::OnSecondRoundOver, this);
	this->Bind(ThirdRoundOver, &mainwindow::OnThirdRoundOver, this);

	wxInitAllImageHandlers();

	screenbit = new wxBitmap("SavedLogos/nhl_espn_logo.jpg", wxBITMAP_TYPE_JPEG);
	mainscreenbit = new BitImage(this, wxID_ANY, screenbit, this->GetBackgroundColour());
//	GetPlayerBio();
//	league.Save();
	Retrieve();
	GetSkaterStats();
	GetGoalieStats();
	league.PurgePlayersWithNoStats();
	GetLines();
	TeamNames tn;
	wxSize s = this->GetSize();
	for (size_t i = 0; i < 32; ++i)
	{
	//	wxButton* B = new wxButton(this, i, "", wxDefaultPosition, wxSize(s.x / 8, s.y / 4));
		wxBitmap bit(tn.GetTeamLogo(i), wxBITMAP_TYPE_PNG);
	//	B->SetBitmap(bit);
	//	if (i < 8) Rowone->Add(B, 1, wxALIGN_CENTRE_VERTICAL);
	//	else if (i < 16) Rowtwo->Add(B, 1, wxALIGN_CENTER_VERTICAL);
	//	else if (i < 24) Rowthree->Add(B, 1, wxALIGN_CENTER_VERTICAL);
	//	else Rowfour->Add(B, 1, wxALIGN_CENTER_VERTICAL);
		league.SetLogo(bit, i);
	//	B->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &mainwindow::GetTeam, this);
	}

	this->Layout();
	this->CenterOnScreen();
	
	Show();

//	playoff_view = new PlayoffBracketView(this, wxID_ANY, this->GetSize(), wxVector<wxString>(), wxVector<wxString>());
	
//	gamewin = new GameFrame(this, GameFinished, &league, league.GetTeam(8), league.GetTeam(game), 7);
//	league.StartGame(GameFrame::CallBack, gamewin, league.GetTeam(17), league.GetTeam(0));
}

mainwindow::~mainwindow()
{
	delete screenbit;
}

void mainwindow::IncrementYear()
{
	wxDateTime date(wxDateTime::Today());
	wxString y = "year";
	int currentyear = date.GetYear();
	for (int i = 2008; i < currentyear; ++i)
	{
		wxString su = SkaterURL;
		wxString gu = GoalieURL;
		wxString data = "";
		yeardataskaters.push_back(data);
		yeardatagoalies.push_back(data);
		wxString year = "";
		year << i;
		su.replace(su.find(y), y.Length(), year);
		gu.replace(gu.find(y), y.Length(), year);
		web.seturl(su);
		web.getwebdata(yeardataskaters[yeardataskaters.size() - 1]);
		league.ParseSkaters(yeardataskaters[yeardataskaters.size() - 1], startofskaterdata, year);
		web.seturl(gu);
		web.getwebdata(yeardatagoalies[yeardatagoalies.size() - 1]);
//		wxSleep(2);
	}

	yeardatalines.push_back("");
	wxString lu = LineParingsURL;
	wxString thisyear;
	thisyear << currentyear - 1;
	lu.replace(lu.find(y), y.Length(), thisyear);
	web.seturl(lu);
	web.getwebdata(yeardatalines[yeardatalines.size() - 1]);
//	wxSleep(1);
}

void mainwindow::GetPlayerBio()
{
	web.seturl(playerbioURL);
	wxString data = "";
	web.getwebdata(data);
	league.AddPlayerBio(data);
	league.Save();
}

void mainwindow::Retrieve()
{
	league.Retrieve();
}

void mainwindow::GetLines()
{
	wxString y = "year";
	int currentyear = wxDateTime::Today().GetYear() - 1;
	wxString year = "";
	year << currentyear;
	wxString temp = LineParingsURL;
	temp.replace(temp.find(y), y.length(), year);

	web.seturl(temp);
	wxString data = "";
	web.getwebdata(data);
	league.AddLines(data);
//	league.SortLines();
}

void mainwindow::GetSkaterStats()
{
	wxString y = "year";
	wxDateTime T;
	wxString t = "1/1/2015";
	T.ParseDate(t);
	int i = 0;
	while (T.GetYear() + i  != wxDateTime::Today().GetYear())
	{
        int currentyear = T.GetYear() + i;
		wxString year = "";
		year << currentyear;
		wxString temp = SkaterURL;
		temp.replace(temp.find(y), y.length(), year);

		web.seturl(temp);
		wxString data = "";
		web.getwebdata(data);
		league.AddStats(data);
		++i;
	}
}

void mainwindow::GetGoalieStats()
{
	wxString y = "year";
	wxDateTime T;
	wxString t = "1/1/2015";
	T.ParseDate(t);
	int i = 0;
	while (T.GetYear() + i != wxDateTime::Today().GetYear())
	{
		int currentyear = T.GetYear() + i;
		wxString year = "";
		year << currentyear;
		wxString temp = GoalieURL;
		temp.replace(temp.find(y), y.length(), year);

		web.seturl(temp);
		wxString data = "";
		web.getwebdata(data);
		league.AddGoalieStats(data);
		++i;
	}
}

void mainwindow::SetFont(wxStaticText*& t, wxFont& f)
{
	t->SetFont(f);
}

void mainwindow::BindLineupButton(wxButton*& b)
{
	
}

void mainwindow::GameOutcome(NHLTeam* T)
{
	wxMessageBox(T->GetTeamName() + " won the game!!!!");
}

void mainwindow::SeasonGame(NHLTeam* away, NHLTeam* home, int series, int round)
{
	gamewin = new GameFrame(this, &league, away, home, series, round);
}

void mainwindow::OnSeasonStatWinClose(wxCommandEvent& evt)
{
	statswin = nullptr;
	if (!playoff_view)
		league.ContinueSeason();
}

void mainwindow::OnPlayoffViewClose(wxCommandEvent& evt)
{
	this->playoff_view = nullptr;
	if (!statswin)
		league.ContinueSeason();
}

void mainwindow::GetTeam(wxCommandEvent& evt)
{
	NHLTeam* m_team = league.GetTeam(evt.GetId());
	if (!m_team)
	{
		wxMessageBox("Could not find team in mainwindow::GetTeam!!");
		return;
	}
	teamwin = new TeamLineupWin(&league, this, m_team);
	Disable();
}

void mainwindow::CloseSelf(wxCloseEvent& evt)
{
	evt.Skip();
}

void mainwindow::OnListSelect(wxListEvent& evt)
{
	
}

void mainwindow::DragColStart(wxListEvent& evt)
{
	
}

void mainwindow::DragColEnd(wxListEvent& evt)
{
	int column = evt.GetColumn();
}

void mainwindow::ClickSortButtons(wxCommandEvent& evt)
{
	
}

void mainwindow::ClickChangeLineupButton(wxCommandEvent& evt)
{

}

void mainwindow::NewGame(wxCommandEvent& evt)
{
	ts = new TeamSelect(this, &league);
	this->Disable();
}

void mainwindow::OnMenuChangeLineups(wxCommandEvent& evt)
{
	cth = new ChangeTeamLineups(this, &league);
	this->Disable();
}

void mainwindow::NewSeason(wxCommandEvent& evt)
{
	St = new StartSeason(this, &league);
	Disable();
}

void mainwindow::OnNewSeasonStart(wxCommandEvent& evt)
{
	league.StartSeason(St->GetTeamSelected());
}

void mainwindow::GameOutcome(wxThreadEvent& evt)
{
	wxSleep(10);
	NHLTeam* winner = gamewin->GetWinningTeam();
	NHLTeam* loser = gamewin->GetDefeatedTeam();
	if (gamewin->PlayoffSeries())
	{
		league.SetMyPlayoffSeriesOutCome(winner, loser);
		this->DestroyGameWin();
		return;
	}
	this->DestroyGameWin();
	if (league.IsQuarterWayThroughSeason())
		statswin = new SeasonStatsWin(this, SeasonStatsWindow::SEASONSTATSWIN, wxPoint(200, 200), wxSize(1300, 700), &league);
	else
		league.ContinueSeason();
}

void mainwindow::RegularSeasonOverEvent(wxCommandEvent& evt)
{
	statswin = new SeasonStatsWin(this, SeasonStatsWindow::SEASONSTATSWIN, wxPoint(200, 200), wxSize(1300, 700), &league);
}

void mainwindow::OnPlayoffStart(wxCommandEvent& evt)
{
	wxVector<PlayoffSeries*> western;
	wxVector<PlayoffSeries*> eastern;

	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_SECOND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_SECOND));

	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_SECOND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_SECOND));

	playoff_view = new PlayoffBracketView(this, wxID_ANY, this->GetSize(), eastern, western, league.GetMYSeasonTeam());
}

void mainwindow::OnFirstRoundOver(wxCommandEvent& evt)
{
	wxVector<PlayoffSeries*> western;
	wxVector<PlayoffSeries*> eastern;

	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_SECOND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_SECOND));

	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_SECOND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_SECOND));

	playoff_view = new PlayoffBracketView(this, wxID_ANY, this->GetSize(), eastern, western, league.GetMYSeasonTeam());
}

void mainwindow::OnSecondRoundOver(wxCommandEvent& evt)
{
	wxVector<PlayoffSeries*> western;
	wxVector<PlayoffSeries*> eastern;

	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_SECOND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_SECOND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_SECOND_ROUND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_SECOND_ROUND));

	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_SECOND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_SECOND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_SECOND_ROUND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_SECOND_ROUND));

	playoff_view = new PlayoffBracketView(this, wxID_ANY, this->GetSize(), eastern, western, league.GetMYSeasonTeam());
}

void mainwindow::OnThirdRoundOver(wxCommandEvent& evt)
{
	wxVector<PlayoffSeries*> western;
	wxVector<PlayoffSeries*> eastern;

	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_SECOND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_FIRST));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_SECOND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::CENTRAL_SECOND_ROUND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::PACIFIC_SECOND_ROUND));
	western.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::WESTERN_THIRD_ROUND));

	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_SECOND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_FIRST));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_SECOND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::ATLANTIC_SECOND_ROUND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::METROPOLITAN_SECOND_ROUND));
	eastern.push_back(league.GetPlayoffSeries(PlayoffSeriesPair::EASTERN_THIRD_ROUND));

	playoff_view = new PlayoffBracketView(this, wxID_ANY, this->GetSize(), eastern, western, league.GetMYSeasonTeam());
}

void mainwindow::EnableSetFocus()
{
	if (teamwin) {
		int size = sizeof(teamwin);
		delete teamwin;
		teamwin = nullptr;
	}

	this->Enable();
	this->SetFocus();
}

void mainwindow::DestroyGameWin()
{
	if (gamewin)
		gamewin->Destroy();
	gamewin = nullptr;
}

int mainwindow::GetLine(int id)
{
	switch (id)
	{
	case 0: 
	case 1: 
	case 2: return 0;
	case 3: 
	case 4: 
	case 5: return 1;
	case 6: 
	case 7: 
	case 8: return 2;
	case 9: 
	case 10: 
	case 11: return 2;
	case 12: 
	case 13: return 0;
	case 14: 
	case 15: return 1;
	case 16: 
	case 17: return 2;
	default: return -1;
	}
}

char mainwindow::GetPosition(int id)
{
	switch (id)
	{
	case 0: 
	case 3:
	case 6:
	case 9: return Position::L;
	case 1:
	case 4:
	case 7:
	case 10: return Position::C;
	case 2: 
	case 5:
	case 8:
	case 11: return Position::R;
	case 12:
	case 14:
	case 16: return Position::L;
	case 13:
	case 15:
	case 17: return Position::R;
	case 18: return Position::G;
	}

	wxMessageBox("param id in mainwindow::GetPosition did not match any thing in the switch statement! Returning invalid char!");
	return 'I';
}

char mainwindow::GetSwapPlayerPos(int id)
{
	switch (id)
	{
	case 0:
	case 3:
	case 6:
	case 9: return Position::L;
	case 1:
	case 4:
	case 7:
	case 10: return Position::C;
	case 2:
	case 5:
	case 8:
	case 11: return Position::R;
	case 12:
	case 14:
	case 16: return Position::D;
	case 13:
	case 15:
	case 17: return Position::D;
	case 18: return Position::G;
	}

	return 'I';
}