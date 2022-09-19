#include "GameFrame.h"

wxDEFINE_EVENT(UpdateEvent, wxCommandEvent);
wxCommandEvent event(UpdateEvent);

wxVector<pair*> GameFrame::queue = {};
pair GameFrame::P = pair(GameWindow::AWAYSCORE, nullptr, "");

BitImage::BitImage(wxWindow* win, int id, wxBitmap* bit, wxColour color) : wxWindow(win, id, wxDefaultPosition, win->FromDIP(bit->GetSize())), m_parent(win), image(bit)
{
	wxSize mysize(this->GetSize());
	wxSize dipsize(win->FromDIP(bit->GetSize()));
	wxSize bitsize(bit->GetSize());
	this->SetBackgroundColour(m_parent->GetBackgroundColour());
	this->SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &BitImage::OnPaint, this);
}

BitImage::BitImage(wxWindow* win, int id, wxPoint point, wxBitmap* bit, wxColour color) : wxWindow(win, id, point, win->FromDIP(bit->GetSize())), m_parent(win), image(bit)
{
	wxSize mysize(this->GetSize());
	wxSize dipsize(win->FromDIP(bit->GetSize()));
	wxSize bitsize(bit->GetSize());
	this->SetBackgroundColour(m_parent->GetBackgroundColour());
	this->SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &BitImage::OnPaint, this);
}

BitImage::~BitImage()
{

}

void BitImage::SetNewBit(wxBitmap* b)
{
	wxSize oldimagesize = m_parent->FromDIP(image->GetSize());
	image = b;
	wxSize newimagesize = m_parent->FromDIP(image->GetSize());
	wxSize rectSize = this->FromDIP(this->GetSize());
	this->SetSize(m_parent->FromDIP(image->GetSize()));
	wxSize newrectSize = this->FromDIP(this->GetSize());
}

void BitImage::OnPaint(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

//	dc.SetBrush(this->GetBackgroundColour());
	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = this->FromDIP(this->GetSize());

//	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
//	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
//	if (!gc)
//		return;

//	gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());
	dc.DrawBitmap(*image, rectOrigin);
}

void BitImage::ShowBitmap()
{
	hide = false;
	Paint();
}

void BitImage::HideBitmap()
{
	hide = true;
	Paint();
}

wxSize BitImage::Getsize()
{
	return this->GetSize();
}

void BitImage::SetPosition(wxPoint p)
{
	
}

void BitImage::Paint()
{
	this->QueueEvent(new wxPaintEvent());
}

Window::Window(wxWindow* w, int id, wxFont f, wxString s) : wxWindow(w, id, wxDefaultPosition, w->FromDIP(wxSize(w->GetClientSize().GetWidth(), w->GetSize().GetHeight() / 7))),
	m_parent(w), title(f), titletext(s)
{
//	this->SetBackgroundColour(m_parent->GetBackgroundColour());
	this->SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &Window::OnPaint, this);
	size_t width = m_parent->GetSize().GetWidth();
	stops.Add(wxColour(0, 0, 0), 0.0);
	stops.Add(wxColour(200, 200, 200), 0.5);
	stops.Add(wxColour(0, 0, 0), 1.0);
	/*
	this->SetBackgroundColour(m_parent->GetBackgroundColour());
	this->SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &Window::OnPaint, this);
	size_t width = m_parent->GetSize().GetWidth();
	int rate = width / 255;
	size_t i = 0;
	size_t count = 0;
	for (i; i < width / 2 && count < width / 2; ++i)
	{
		if (i < 30)
		{
			stops.Add(wxColour(0, 0, 0), float(i) / 1000.0);
			continue;
		}
		if (!(i % (rate / 2) ) && count > 0)
			stops.Add(wxColour(--count, count, count), float(i) / 1000.0);
		else
			stops.Add(wxColour(count, count, count), float(i) / 1000.0);
		if(count < 225)
		++count;
	}
	
	for (size_t j = stops.GetCount() - 1; j > -1; --j)
	{
		++i;
		stops.Add(wxColour(stops.Item(0).GetColour()), float(i) / 1000.0);
	}
	*/
}

Window::~Window()
{

}

void Window::OnPaint(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	wxColour font = wxColour(0, 0, 0);
	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = this->FromDIP(wxSize(this->GetSize().GetWidth(), this->GetSize().GetHeight()));
	wxSize parentsize = m_parent->FromDIP(m_parent->GetSize());
	int width = rectSize.GetWidth();
	int height = rectSize.GetHeight();

	double percentbegin = .10;
	int endblack = width * percentbegin;
	int beginblack = width - endblack;
	int stopsize = width * .02;
	
	//make border...
	int border_width = 6;
	for (size_t i = 0; i < border_width; ++i)
	{
		dc.SetPen(wxPen(wxColour(255 - (i * 20), 20, 25), 1));
		dc.DrawLine(wxPoint(i, i), wxPoint(width - (i + 1), i));
		dc.DrawLine(wxPoint(i, i), wxPoint(i, height - (i + 1)));
		dc.DrawLine(wxPoint(width - (i + 1), i),  wxPoint(width - (i + 1), height - (i + 1)));
		dc.DrawLine(wxPoint(i, height - (i + 1)), wxPoint(width - (i), height - (i + 1)));
	}

	dc.SetBrush(wxBrush(wxColour(105, 100, 100), wxBRUSHSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(rectOrigin.x + border_width, rectOrigin.y + border_width), wxSize(rectSize.GetWidth() - border_width * 2, rectSize.GetHeight() - border_width * 2));
	Gen g;
	wxGraphicsFont gf = gc->CreateFont(title, font);
	gc->SetFont(gf);

	double w = 0.0;
	double h = 0.0;
	gc->GetTextExtent(titletext, &w, &h);
	gc->DrawText(titletext, rectOrigin.x + (rectSize.GetWidth() / 2.0) - w / 2.0, (rectOrigin.y + rectSize.GetHeight() / 2.0) - h / 2.0);

	delete gc;
	/*
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	wxColour font = wxColour(0, 0, 0);

	int width = 0;
	int height = 0;

	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize rectSize = m_parent->FromDIP(wxSize(m_parent->GetSize().GetWidth(), m_parent->GetSize().GetHeight() / 7));

	wxGraphicsBrush gb = gc->CreateLinearGradientBrush(rectOrigin.x, rectOrigin.y, rectOrigin.x + rectSize.GetWidth(), rectOrigin.y + rectSize.GetHeight(), stops);
	gc->SetBrush(gb);

	gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());

	wxGraphicsFont gf = gc->CreateFont(title, font);
	gc->SetFont(gf);

	double w = 0.0;
	double h = 0.0;
	gc->GetTextExtent(titletext, &w, &h);
	gc->DrawText(titletext, rectOrigin.x + (rectSize.GetWidth() / 2.0) - w / 2.0, (rectOrigin.y + rectSize.GetHeight() / 2.0) - h / 2.0);

	delete gc;
	*/
}

void Window::RefreshWindow()
{
	this->SetSize(m_parent->FromDIP(wxSize(m_parent->GetClientSize().GetWidth(), m_parent->GetSize().GetHeight() / 7)));
	this->Refresh();
}

CustomWin::CustomWin(wxWindow* w, int id, wxFont f, wxString m, wxSize stringsize, wxSize windowsize, bool b) : 
	wxWindow(w, id, wxPoint((w->GetSize().GetWidth() / 2) - (windowsize.GetWidth() / 2), (w->GetSize().GetHeight() / 2) - (windowsize.GetHeight() / 2)), 
		windowsize), m_parent(w), font(f),
	text(m), textsize(stringsize), this_size(windowsize), transparentbackground(b)
{
	SetBackgroundColour(m_parent->GetBackgroundColour());

	SetBackgroundStyle(wxBackgroundStyle::wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &CustomWin::OnPaint, this);
//	this->QueueEvent(new wxPaintEvent);
}

void CustomWin::OnPaint(wxPaintEvent&)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	wxColour color = wxColour(255, 255, 255);

	int width = 0;
	int height = 0;

	wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
	wxSize normal = this->GetSize();
	wxSize rectSize = this->FromDIP(this->GetSize());

	wxGraphicsFont gf = gc->CreateFont(font, color);
	gc->SetFont(gf);

	double w = 0.0;
	double h = 0.0;
	gc->GetTextExtent(text, &w, &h);
	gc->DrawText(text, rectOrigin.x + (rectSize.GetWidth() / 2.0) - w / 2.0, (rectOrigin.y + rectSize.GetHeight() / 2.0) - h / 2.0);

	delete gc;
	
}

MyThread::MyThread(GameFrame* gf, NHL_League* L, NHLTeam* a, NHLTeam* h, bool postseason) : 
	wxThread(wxThreadKind::wxTHREAD_DETACHED), gameframe(gf), league(L), away(a), home(h), playoffs(postseason)
{

}

MyThread::~MyThread()
{
	gameframe->thread = nullptr;
}

wxThread::ExitCode MyThread::Entry()
{
	this->Sleep(3000);
	wxThreadEvent evt(wxEVT_THREAD, 2);
	wxPostEvent(gameframe, evt);
	if (!TestDestroy())
	{
		if (playoffs)
			league->StartPlayoffGame(GameFrame::CallBack, gameframe, away, home);
		else
			league->StartGame(GameFrame::CallBack, gameframe, away, home);
	}
	if (end)
	{
		return (wxThread::ExitCode)0;
	}
		
	return (wxThread::ExitCode)0;
}

//helper function
void SetStaticTextBackgroundColour(wxStaticText*& t, wxWindow* w)
{
	t->SetBackgroundColour(w->GetBackgroundColour());
	t->SetForegroundColour(wxColour(255, 255, 255));
}

GameFrame::GameFrame(wxFrame* parent, void (*func)(void*, NHLTeam*), NHL_League* l, NHLTeam* at, NHLTeam* ht, int ser) : wxFrame(parent, (int)GameWindow::GAMEWIN, "The Fuck", wxDefaultPosition,
	wxSize(1700 * (6.0 / 8.0), 900 * (6.0 / 8.0))), m_parent(parent), league(l), away(at), home(ht), series(ser), Cb(func)
{
	if (series > 1) Series = true;

	this->Bind(UpdateEvent, &GameFrame::OnUpdate, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &GameFrame::OnClose, this);
	this->Bind(wxEVT_LEFT_DOWN, &GameFrame::OnMouseLeftDown, this);

	this->SetBackgroundColour(wxColour(0, 0, 0));
	this->Create();
	
	thread = new MyThread(this, league, away, home, Series);
	if (thread->Run() != wxTHREAD_NO_ERROR)
	{
		wxMessageBox("thread could not be started in GameFrame Constructor!!");
		delete thread;
		thread = nullptr;
		return;
	}
	StartGameMessage();
	thread->EndAfterEntry();
}

GameFrame::GameFrame(wxFrame* parent, NHL_League* l, NHLTeam* at, NHLTeam* ht, int ser, int round) : wxFrame(parent, (int)GameWindow::GAMEWIN, "NHL", wxDefaultPosition,
	wxSize(1700 * (6.0 / 8.0), 900 * (6.0 / 8.0))), m_parent(parent), league(l), away(at), home(ht), series(ser), series_round(round)
{
	if (series > 1) Series = true;
	this->Bind(UpdateEvent, &GameFrame::OnUpdate, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &GameFrame::OnClose, this);
	this->Bind(wxEVT_LEFT_DOWN, &GameFrame::OnMouseLeftDown, this);
	this->Bind(wxEVT_SIZE, &GameFrame::OnSizeChange, this);

	this->SetBackgroundColour(wxColour(0, 0, 0));
	this->Create();

	thread = new MyThread(this, league, away, home, Series);
	if (thread->Run() != wxTHREAD_NO_ERROR)
	{
		wxMessageBox("thread could not be started in GameFrame Constructor!!");
		delete thread;
		thread = nullptr;
		return;
	}
	StartGameMessage();
	thread->EndAfterEntry();
}

GameFrame::~GameFrame()
{
	DeleteQueue();
}

void GameFrame::StartGame(NHLTeam* a, NHLTeam* h, bool ser)
{
	Series = ser;
	DestroyPopup();
	away = a;
	home = h;

	Initialize(); 
	this->Layout();
	this->Refresh();
	DeleteQueue();
	thread = new MyThread(this, league, away, home, Series);
	if (thread->Run() != wxTHREAD_NO_ERROR)
	{
		wxMessageBox("thread could not be started in GameFrame Constructor!!");
		delete thread;
		thread = nullptr;
		return;
	}
	thread->EndAfterEntry();
}

void GameFrame::CallBack(GameWindow id, int v, void* F, GameRecord* gr, wxString message)
{
	GameFrame* obj = static_cast<GameFrame*>(F);

	obj->QueueEvent(new wxCommandEvent(UpdateEvent, (int)id));

	queue.push_back(new pair(id, gr, message));

	if (obj->thread)
	{
		if (id != GameWindow::GAMEOVER)
			obj->thread->Sleep(1500);
	}
}

bool GameFrame::IsOver()
{
	if (thread && thread->IsAlive())
		return false;
	
	return true;
}


void GameFrame::OnUpdate(wxCommandEvent& evt)
{
	if (!queue.size())
		return;

	pair* p = nullptr;
	p = *queue.rend();
	auto it = queue.rbegin();
	if (it != queue.rend())
	{
		p = *it;
		switch (p->w)
		{
		case GameWindow::AWAY_RECORD_WINS: break;
		case GameWindow::AWAY_RECORD_LOSSES: break;
		case GameWindow::AWAY_RECORD_OVERTIME_LOSSES: break;
		case GameWindow::AWAY_RECORD: SetAwayRecord(p->gr, false); break;
		case GameWindow::HOME_RECORD_WINS: break;
		case GameWindow::HOME_RECORD_LOSSES: break;
		case GameWindow::HOME_RECORD_OVERTIME_LOSSES: break;
		case GameWindow::HOME_RECORD: SetHomeRecord(p->gr, false); break;
		case GameWindow::AWAYSHOTS: SetAwayShots();  break;
		case GameWindow::HOMESHOTS: SetHomeShots();  break;
		case GameWindow::AWAYSCORE: SetAwayGoal();  break;
		case GameWindow::HOMESCORE: SetHomeGoal();  break;
		case GameWindow::MESSAGE_UPDATE: DoUpdateWindow(p->message); break;
		case GameWindow::OVERTIME: DoUpdateWindowOvertime(p->message); break;
		case GameWindow::GAMEOVER: DeclareWinner(); break;
		default:
		{
			wxMessageBox("Switch failed in GameFrame::CallBack!");
		}
		}
//		queue.erase(it);
	}
}

void GameFrame::OnClose(wxCloseEvent& evt)
{
	if (!thread)
	{
		wxThreadEvent evt2(wxEVT_THREAD, 1);
		wxPostEvent(m_parent, evt2);
		this->Destroy();
		wxThreadEvent evt(wxEVT_THREAD, 0);
		wxPostEvent(m_parent, evt);
		return;
	}

	league->EndGame();
	while (true)
	{
		if (thread && thread->IsAlive())
		{

		}
		else
		{
			this->Destroy();
			wxThreadEvent evt(wxEVT_THREAD, 0);
			wxPostEvent(m_parent, evt);
			return;
		}
	}

	wxThreadEvent evt2(wxEVT_THREAD, 1);
	wxPostEvent(m_parent, evt2);
}

void GameFrame::OnMouseLeftDown(wxMouseEvent& evt)
{
	DestroyPopup();
}

void GameFrame::ThreadEvent(wxThreadEvent& evt)
{
	if (evt.GetId() == 2)
		DestroyPopup();
}

void GameFrame::OnSizeChange(wxSizeEvent& evt)
{
	Banner->RefreshWindow();
}

void GameFrame::StartGameMessage()
{
//	wxString text = "Game Is Starting";
//	wxFont f = wxFont(wxSize(100, 50), wxFontFamily::wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
//	alert = new CustomWin(this, wxID_ANY, f, "Game Is Starting", wxSize(2, 3), this->FromDIP(wxSize(this->GetSize().GetWidth() / 2, this->GetSize().GetWidth() / 6)), true);
//	DoUpdateWindow("Game has begun", 20, true);
}

void GameFrame::SetAwayGoal()
{
	++m_awaygoals;
	wxString ONScreen = "";
	ONScreen << m_awaygoals;
	m_AwayGoals->SetLabel(ONScreen);
	m_AwayGoals->Update();
}

void GameFrame::SetAwayShots()
{
	++m_awayshots;
	wxString ONScreen = "Shots: ";
	ONScreen << m_awayshots;
	m_AwayShots->SetLabel(ONScreen);
	m_AwayShots->Update();
}

void GameFrame::SetAwayRecord(GameRecord* gr, bool update)
{
	wxString ONscreen = "(";
	ONscreen << gr->wins;
	ONscreen += " - ";
	if (!Series)
	{
		ONscreen << gr->ovL;
		ONscreen += " - ";
		ONscreen << gr->loss;
	}
	else
		ONscreen << gr->loss + gr->ovL;
	
	ONscreen += ")";
	m_AwayRecord->SetLabel(ONscreen);
	if(update) m_AwayRecord->Update();
}

void GameFrame::SetHomeGoal()
{
	++m_homegoals;
	wxString ONScreen = "";
	ONScreen << m_homegoals;
	m_HomeGoals->SetLabel(ONScreen);
	m_HomeGoals->Update();
}

void GameFrame::SetHomeShots()
{
	++m_homeshots;
	wxString ONScreen = "Shots: ";
	ONScreen << m_homeshots;
	m_HomeShots->SetLabel(ONScreen);
	m_HomeShots->Update();
}

void GameFrame::SetHomeRecord(GameRecord* gr, bool update)
{
	wxString ONscreen = "(";
	ONscreen << gr->wins;
	ONscreen += " - ";
	if (!Series)
	{
		ONscreen << gr->ovL;
		ONscreen += " - ";
		ONscreen << gr->loss;
	}
	else
		ONscreen << gr->loss + gr->ovL;

	ONscreen += ")";
	m_HomeRecord->SetLabel(ONscreen);
	if(update) m_HomeRecord->Update();
	if(!update) this->Refresh();
}

void GameFrame::DoUpdateWindow(wxString s, int size, bool b)
{
	DestroyPopup();

	wxFont F;
	F.SetPointSize(size);
	F = F.MakeBold();

	wxPoint position(Banner->GetPosition().x + 20, (Banner->GetPosition().y + Banner->GetSize().GetHeight() + ((m_AwayRecord->GetPosition().y -
		(Banner->GetPosition().y + Banner->GetSize().GetHeight())) / 2 - 15)));

	pw = new wxWindow(this, wxID_ANY, position);
	pw->SetBackgroundColour(this->GetBackgroundColour());

	T = new wxStaticText(pw, wxID_ANY, s);
	T->SetBackgroundColour(this->GetBackgroundColour());
	T->SetFont(F);
	T->SetForegroundColour("white");

	pw->SetSize(T->GetSize());
	wxBoxSizer* mainV = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainH = new wxBoxSizer(wxHORIZONTAL);

	mainV->Add(T, 1, wxALIGN_CENTER_HORIZONTAL);
	mainH->Add(mainV, 1, wxALIGN_CENTER_VERTICAL);

	pw->SetSizer(mainH);
	pw->Layout();
	wxBell();
	pw->ShowWithEffect(wxShowEffect::wxSHOW_EFFECT_ROLL_TO_RIGHT);

	/*
	T->SetParent(pw);

	wxBoxSizer* mainV = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainH = new wxBoxSizer(wxHORIZONTAL);

	mainV->Add(T, 1, wxALIGN_CENTER_HORIZONTAL);
	mainH->Add(mainV, 1, wxALIGN_CENTER_VERTICAL);

	pw->SetSizer(mainH);
	pw->Layout();
	wxBell();
	pw->ShowWithEffect(wxShowEffect::wxSHOW_EFFECT_ROLL_TO_RIGHT);
	*/
}

void GameFrame::DoUpdateWindowOvertime(wxString s)
{
	DestroyPopup();
	DoUpdateWindow(s, 15);
}

void GameFrame::DestroyPopup()
{
	if (!pw)
		return;

	pw->HideWithEffect(wxShowEffect::wxSHOW_EFFECT_ROLL_TO_RIGHT);
	pw->Destroy();
	pw = nullptr;
}

void GameFrame::DeclareWinner()
{
	--series;
//	DestroyPopup();
	wxString a = "", h = "";
	a << m_awaygoals;
	h << m_homegoals;
	if (m_awaygoals > m_homegoals)
	{
		winner = away;
	//	wxMessageBox(away->GetTeamName() + " won against " + home->GetTeamName() + " " + a + " to " + h);
	}
	else
	{
		winner = home;
	//	wxMessageBox(home->GetTeamName() + " won against " + away->GetTeamName() + " " + h + " to " + a);
	}

	if (Series && series < 4)
	{
		if (away->GetPlayoffSeriesRecord()->wins == 4)
		{
			wxString opponent = "";
			opponent << home->GetPlayoffSeriesRecord()->wins;
			wxMessageBox(away->GetTeamName() + " won the series against " + home->GetTeamName() + " 4 to " + opponent);
			winner = away;
			loser = home;
			wxThreadEvent evt(wxEVT_THREAD, 0);
			wxPostEvent(m_parent, evt);
			return;
		}
		if (home->GetPlayoffSeriesRecord()->wins == 4)
		{
			wxString opponent = "";
			opponent << away->GetPlayoffSeriesRecord()->wins;
			wxMessageBox(home->GetTeamName() + " won the series against " + away->GetTeamName() + " 4 to " + opponent);
			winner = home;
			loser = away;
			wxThreadEvent evt(wxEVT_THREAD, 0);
			wxPostEvent(m_parent, evt);
			return;
		}
	}

	if (series == 0)
	{
		wxThreadEvent evt(wxEVT_THREAD, 0);
		wxPostEvent(m_parent, evt);
		return;
	}

	switch (series)
	{
	case 6: this->StartGame(away, home, Series); break;
	case 5: Swap(); this->StartGame(away, home, Series); break;
	case 4: this->StartGame(away, home, Series); break;
	case 3: Swap(); this->StartGame(away, home, Series); break;
	case 2: Swap(); this->StartGame(away, home, Series); break;
	case 1: Swap(); this->StartGame(away, home, Series); break;
	}
}

void GameFrame::Initialize()
{
	m_AwayShots->SetLabel("Shots: 0");
	m_HomeShots->SetLabel("Shots: 0");

	m_awaygoals = 0;
	m_homegoals = 0;
	m_awayshots = 0;
	m_homeshots = 0;

	m_AwayGoals->SetLabel("0");
	m_HomeGoals->SetLabel("0");

	if (Series && gamenumber)
	{
		++game;
		wxString g = "Game ";
		g << game;
		gamenumber->SetLabel(g);
	}

	if(away) SetAwayRecord(away->GetGameRecord());
	if(home) SetHomeRecord(home->GetGameRecord());

	BitImage* m_tempAwayLogo = new BitImage(this, wxID_ANY, away->GetTeamLogo(), this->GetBackgroundColour());
	BitImage* m_tempHomeLogo = new BitImage(this, wxID_ANY, home->GetTeamLogo(), this->GetBackgroundColour());

	if (AwayLogoH->Replace(m_AwayLogo, m_tempAwayLogo))
	{
		m_AwayLogo->Destroy();
		m_AwayLogo = m_tempAwayLogo;
	}
	else
		m_tempAwayLogo->Destroy();

	if (HomeLogoH->Replace(m_HomeLogo, m_tempHomeLogo))
	{
		m_HomeLogo->Destroy();
		m_HomeLogo = m_tempHomeLogo;
	}
	else
		m_tempHomeLogo->Destroy();

	SetMinLogoSizerHeight();
}

void GameFrame::Swap()
{
	NHLTeam* temp = away;
	away = home;
	home = temp;
}

void GameFrame::DeleteQueue()
{
	for (size_t i = 0; i < queue.size(); ++i)
		delete queue[i];

	queue.clear();
}

void GameFrame::SetMinLogoSizerHeight()
{
	int h1 = m_AwayLogo->GetSize().GetHeight();
	int h2 = m_HomeLogo->GetSize().GetHeight();
	int height = h1 > h2 ? h1 : h2;
	AwayLogoH->SetMinSize(wxSize(AwayLogoH->GetSize().GetWidth(), height));
	HomeLogoH->SetMinSize(wxSize(HomeLogoH->GetSize().GetWidth(), height));
}

void GameFrame::HideLowerSizer()
{
	m_AwayShots->Hide();
	m_HomeShots->Hide();
	m_AwayGoals->Hide();
	m_HomeGoals->Hide();
	if (gamenumber) gamenumber->Hide();
}

void GameFrame::ShowLowerSizer()
{
	m_AwayShots->Show();
	m_HomeShots->Show();
	m_AwayGoals->Show();
	m_HomeGoals->Show();
	if (gamenumber) gamenumber->Show();
}

void GameFrame::Create()
{
	double proportion = 36.0 / 17.0;

	awaylogo = away->GetTeamLogo();
	homelogo = home->GetTeamLogo();

	m_AwayLogo = new BitImage(this, (int)GameWindow::BIT_TEAM_AWAY_IMAGE, awaylogo, this->GetBackgroundColour());
	m_HomeLogo = new BitImage(this, (int)GameWindow::BIT_TEAM_HOME_IMAGE, homelogo, this->GetBackgroundColour());

	wxBoxSizer* UpperMidH = nullptr;
	if (Series)
	{
		wxString path = "SavedLogos/";
		if (series_round < 4) path += "StanleyCupPlayoffs.png";
		else path += "StanleyCupFinal.png";
		wxBitmap* ns = new wxBitmap(path, wxBITMAP_TYPE_PNG);
		nhlsymbol = new BitImage(this, wxID_ANY, ns, this->GetBackgroundColour());
		UpperMidH = new wxBoxSizer(wxHORIZONTAL);
		UpperMidH->Add(nhlsymbol, 1, wxALIGN_TOP);
	}

	wxString bannertitle = "";
	bannertitle += away->GetTeamabbr() + " @ " + home->GetTeamabbr();
	wxFont Title;
	Title.SetFamily(wxFontFamily::wxFONTFAMILY_ROMAN);
	Title = Title.MakeBold();
	Title.SetPixelSize(wxSize(this->GetSize().GetWidth() / 46, this->GetSize().GetWidth() / 46 * proportion));
	Banner = new Window(this, wxID_ANY, Title, bannertitle);

	if (Series)
	{
		int ser = series - (series - game);
		wxString se = "";
		se << ser;
		gamenumber = new wxStaticText(this, wxID_ANY, "Game " + se);
		SetStaticTextBackgroundColour(gamenumber, this);
		Title.SetPixelSize(wxSize(this->GetSize().GetWidth() / 70, this->GetSize().GetWidth() / 70 * proportion));
		gamenumber->SetFont(Title);
	}

	wxStaticText* Verses = new wxStaticText(this, wxID_ANY, "VS");
	Verses->SetBackgroundColour(this->GetBackgroundColour());
	//	SetStaticTextBackgroundColour(Verses, this);

	m_AwayRecord = new wxStaticText(this, (int)GameWindow::AWAY_RECORD, "");
	m_HomeRecord = new wxStaticText(this, (int)GameWindow::HOME_RECORD, "");
	SetStaticTextBackgroundColour(m_AwayRecord, this);
	SetStaticTextBackgroundColour(m_HomeRecord, this);

	//Set current records...
	SetAwayRecord(away->GetGameRecord(), false);
	SetHomeRecord(home->GetGameRecord(), false);

	m_AwayGoals = new wxStaticText(this, (int)GameWindow::AWAYSCORE, "0");
	m_HomeGoals = new wxStaticText(this, (int)GameWindow::HOMESCORE, "0");
	SetStaticTextBackgroundColour(m_AwayGoals, this);
	SetStaticTextBackgroundColour(m_HomeGoals, this);

	m_AwayShots = new wxStaticText(this, (int)GameWindow::AWAYSHOTS, "Shots: 0");
	m_HomeShots = new wxStaticText(this, (int)GameWindow::HOMESHOTS, "Shots: 0");
	SetStaticTextBackgroundColour(m_AwayShots, this);
	SetStaticTextBackgroundColour(m_HomeShots, this);
	
//	wxFont Title;
//	Title.SetFamily(wxFontFamily::wxFONTFAMILY_ROMAN);
//	Title = Title.MakeBold();
//	Title.SetPixelSize(wxSize(this->GetSize().GetWidth() / 46, this->GetSize().GetWidth() / 46 * proportion));
//	NewGame->SetFont(Title);

	Title.SetPixelSize(wxSize(this->GetSize().GetWidth() / 12, this->GetSize().GetWidth() / 10));
	Verses->SetFont(Title);
	Verses->SetForegroundColour(wxColour(247, 37, 22));

	Title.SetPixelSize(wxSize(this->GetSize().GetWidth() / 66, this->GetSize().GetWidth() / 66 * proportion));
	m_AwayRecord->SetFont(Title);
	m_HomeRecord->SetFont(Title);

	m_AwayShots->SetFont(Title);
	m_HomeShots->SetFont(Title);

	Title.SetPixelSize(wxSize(this->GetSize().GetWidth() / 46, this->GetSize().GetWidth() / 46 * proportion));
	m_AwayGoals->SetFont(Title);
	m_HomeGoals->SetFont(Title);

	wxBoxSizer* MainV = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* TopV = new wxBoxSizer(wxVERTICAL);
	MidH = new wxBoxSizer(wxHORIZONTAL);

	HomeLogoV = new wxBoxSizer(wxVERTICAL);
	HomeLogoH = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* VersesV = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* VersesH = new wxBoxSizer(wxHORIZONTAL);

    AwayLogoV = new wxBoxSizer(wxVERTICAL);
    AwayLogoH = new wxBoxSizer(wxHORIZONTAL);

	TopV->Add(Banner, 1, wxALIGN_CENTER_HORIZONTAL);
	if(gamenumber) TopV->Add(gamenumber, 1, wxALIGN_CENTER_HORIZONTAL);
	
	AwayLogoH->Add(m_AwayLogo, 1, wxALIGN_CENTER_VERTICAL);
	AwayLogoH->AddSpacer(10);
	AwayLogoH->Add(m_AwayGoals, 0, wxALIGN_CENTER_VERTICAL);
	AwayLogoV->Add(m_AwayRecord, 0, wxALIGN_LEFT);
	AwayLogoV->AddSpacer(10);
	AwayLogoV->Add(AwayLogoH, 1, wxALIGN_LEFT);
//	AwayLogoV->AddSpacer(10);
	AwayLogoV->Add(m_AwayShots, 0, wxALIGN_LEFT);

	VersesH->Add(Verses, 1, wxALIGN_CENTER_VERTICAL);
	VersesV->Add(VersesH, 1, wxALIGN_CENTER_HORIZONTAL);

	HomeLogoH->Add(m_HomeGoals, 0, wxALIGN_CENTER_VERTICAL);
	HomeLogoH->AddSpacer(10);
	HomeLogoH->Add(m_HomeLogo, 1, wxALIGN_CENTER_VERTICAL);
	HomeLogoV->Add(m_HomeRecord, 0, wxALIGN_RIGHT);
	HomeLogoV->AddSpacer(10);
	HomeLogoV->Add(HomeLogoH, 1, wxALIGN_RIGHT);
//	HomeLogoV->AddSpacer(10);
	HomeLogoV->Add(m_HomeShots, 0, wxALIGN_RIGHT);

	MidH->Add(AwayLogoV, 1, wxALIGN_CENTER_VERTICAL);
	MidH->Add(VersesV, 1, wxALIGN_CENTER_VERTICAL);
	MidH->Add(HomeLogoV, 1, wxALIGN_CENTER_VERTICAL);
	
	int prop = Series ? 2 : 4;
//	MainV->AddSpacer(10);
	MainV->Add(TopV, 1, wxALIGN_CENTER_HORIZONTAL);
	if(Series) MainV->Add(UpperMidH, 1, wxALIGN_CENTER_HORIZONTAL);
	MainV->Add(MidH, prop, wxALIGN_CENTER_HORIZONTAL);

	SetMinLogoSizerHeight();

	this->SetSizer(MainV);
	this->Layout();
	this->CenterOnParent();
	this->Show();
}