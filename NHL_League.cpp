#include "NHL_League.h"

wxDEFINE_EVENT(PlayoffStartEvent, wxCommandEvent);
wxCommandEvent nhl_leage_event(PlayoffStartEvent);

wxDEFINE_EVENT(RegularSeasonOver, wxCommandEvent);
wxCommandEvent nhl_league_season_over(RegularSeasonOver);

wxDEFINE_EVENT(FirstRoundOver, wxCommandEvent);
wxCommandEvent nhl_league_first_over(FirstRoundOver);

// second round over
wxDEFINE_EVENT(SecondRoundOver, wxCommandEvent);
wxCommandEvent nhl_league_second_over(SecondRoundOver);

// third round over
wxDEFINE_EVENT(ThirdRoundOver, wxCommandEvent);
wxCommandEvent nhl_league_third_over(ThirdRoundOver);

Forwards* Forwards::AddLine(NHLplayer* l, NHLplayer* c, NHLplayer* r)
{
	if (!l || !c || !r)
	{
		wxFAIL_MSG("nullptr passed as paramater in Forwards::AddLine!!!");
		return nullptr;
	}

	left = l, center = c, right = r; 

	left->ActivatePlayer();
	center->ActivatePlayer();
	right->ActivatePlayer();

	if (left == right || left == center || center == right)
		return this;

	return nullptr;
}

bool Forwards::IsDuplicatePlayer(NHLplayer* l, NHLplayer* c, NHLplayer* r)
{
	if (left == l || center == l || right == l) return true;
	if (left == c || center == c || right == c) return true;
	if (left == r || center == r || right == r) return true;

	return false;
}

NHLplayer* Forwards::AddStartingPlayer(NHLplayer* p)
{
	if (!p)
	{
	//	wxMessageBox("NHLplayer param in Forwards::AddStartingForward is nullptr!");
		return nullptr;
	}
	char position = p->GetPosition();
	int count = -1;
	while (true)
	{
		++count;
		if (count > 2)
		{
		//	wxMessageBox("Returning nullptr because player was not added to line in Forwards::AddStartingPlayer!!!");
			return nullptr;
		}
		switch (position)
		{
		case Position::L:
		{
			if (Left) break;
			Left = true;
			NHLplayer* temp = left;
			left = p;
			left->ActivatePlayer();
			return temp;
		}
		case Position::C:
		{
			if (Center) break;
			Center = true;
			NHLplayer* temp = center;
			center = p;
			center->ActivatePlayer();
			return temp;
		}
		case Position::R:
		{
			if (Right) break;
			Right = true;
			NHLplayer* temp = right;
			right = p;
			right->ActivatePlayer();
			return temp;
		}
		}
		if (position == Position::L)
			position = Position::C;
		else if (position == Position::C)
			position = Position::R;
		else
			position = Position::L;
	}
}

NHLplayer* Forwards::AddStartingPlayer(NHLplayer* p, char position)
{
	if (position == Position::L)
	{
		if (!left)
		{
			Left = true;
			left = p;
			return nullptr;
		}
		if (left->GetPosition() != Position::L)
		{
			Left = true;
			NHLplayer* temp = left;
			left = p;
			return temp;
		}
	}
	if (position == Position::C)
	{
		if (!center)
		{
			Center = true;
			center = p;
			return nullptr;
		}
		if (center->GetPosition() != Position::C)
		{
			Center = true;
			NHLplayer* temp = center;
			center = p;
			return temp;
		}
	}
	if (position == Position::R)
	{
		if (!right)
		{
			Right = true;
			right = p;
			return nullptr;
		}
		if (right->GetPosition() != Position::R)
		{
			Right = true;
			NHLplayer* temp = right;
			right = p;
			return temp;
		}
	}

	return nullptr;
}

void Forwards::ResetInGameBockedShots()
{
	if (left) left->ResetInGameBockedShots();
	if (center) center->ResetInGameBockedShots();
	if (right) right->ResetInGameBockedShots();
}

void Forwards::AddGamePlayed()
{
	if (left) left->SetGamePlayed();
	if (center) center->SetGamePlayed();
	if (right) right->SetGamePlayed();
}

void Forwards::AddOnIceAgainstGoal()
{
	left->SetOnIceAgainstGoal();
	center->SetOnIceAgainstGoal();
	right->SetOnIceAgainstGoal();
}

void Forwards::AddOnIceForGoal()
{
	left->SetOnIceForGoal();
	center->SetOnIceForGoal();
	right->SetOnIceForGoal();
}

bool Forwards::HasPlayer(NHLplayer* p)
{
	if(left && left == p) return true;
	if (center && center == p) return true;
	if (right && right == p) return true;
	
	return false;
}

bool Forwards::SwapPlayers(NHLplayer* p1, NHLplayer* p2)
{
	if (!p1 || !p2) return false;

	if (p1 == p2) return false;

	if (!left || !center || !right)
	{
		wxMessageBox("left, center or right in Forwards::SwapPlayers is nullptr! Returning false!");
		return false;
	}

	NHLplayer* swap1 = nullptr;
	NHLplayer* swap2 = nullptr;

	if (p1 == left) swap1 = left;
	else if (p1 == center) swap1 = center;
	else if (p1 == right) swap1 = right;
	else return false;

	if (p2 == left) swap2 = left;
	else if (p2 == center) swap2 = center;
	else if (p2 == right) swap2 = right;
	else return false;

	NHLplayer* temp = swap1;
	swap1 = swap2;
	swap2 = temp;
	return true;
}

NHLplayer* Forwards::ReplacePlayer(NHLplayer* p, char pos)
{
	if (!p) return nullptr;
	if (HasPlayer(p)) return nullptr;

	NHLplayer* temp = nullptr;

	switch (pos)
	{
	case Position::L:
	{
		p->ActivatePlayer();
		left->DeactivatePlayer();
		temp = left;
		left = p;
		return temp;
	}
	case Position::C:
	{
		p->ActivatePlayer();
		center->DeactivatePlayer();
		temp = center;
		center = p;
		return temp;
	}
	case Position::R:
	{
		p->ActivatePlayer();
		right->DeactivatePlayer();
		temp = right;
		right = p;
		return temp;
	}
	default: return nullptr;
	}

}

double Forwards::GetLineStrength()
{
	double d = 0.0;
	if (left) d = left->GetGameScore();
	if (center) d += center->GetGameScore();
	if (right) d += right->GetGameScore();

	return d;
}

double Forwards::GetShotsPerGame()
{
	double spg = 0.0;
	if (left) spg += left->GetShotsPerGame();
	if (center) spg += center->GetShotsPerGame();
	if (right) spg += right->GetShotsPerGame();

	return spg;
}

void Forwards::CalcValues()
{
	OnIce_corsipercent = 0.0;
	OnIce_corsipercent += left->GetCorsiPercent();
	OnIce_corsipercent += center->GetCorsiPercent();
	OnIce_corsipercent += right->GetCorsiPercent();
}

bool Defense::IsDuplicatePlayer(NHLplayer* l, NHLplayer* r)
{
	if (d1 == l || d2 == l || d1 == r || d2 == r) return true;

	return false;
}

double Defense::GetLineStrength()
{
	double d = 0.0;
	if (d1) d = d1->GetGameScore();
	if (d2) d += d2->GetGameScore();

	return d;
}

void Defense::ResetInGameBockedShots()
{
	if (d1) d1->ResetInGameBockedShots();
	if (d2) d2->ResetInGameBockedShots();
}

void Defense::AddGamePlayed()
{
	if (d1) d1->SetGamePlayed();
	if (d2) d2->SetGamePlayed();
}

void Defense::AddOnIceAgainstGoal()
{
	d1->SetOnIceAgainstGoal();
	d2->SetOnIceAgainstGoal();
}

void Defense::AddOnIceForGoal()
{
	d1->SetOnIceForGoal();
	d2->SetOnIceForGoal();
}

double Defense::GetShotsPerGame()
{
	double spg = 0.0;
	if (d1) spg += d1->GetShotsPerGame();
	if (d2) spg += d2->GetShotsPerGame();

	return spg;
}

void Defense::CalcValues()
{
	OnIce_corsipercent = 0.0;
	OnIce_corsipercent += d1->GetCorsiPercent();
	OnIce_corsipercent += d2->GetCorsiPercent();
}

bool Defense::HasPlayer(NHLplayer* p)
{
	if (d1 && d1 == p) return true;
	if (d2 && d2 == p) return true;

	return false;
}

bool Defense::SwapPlayers(NHLplayer* p1, NHLplayer* p2)
{
	if (!p1 || !p2) return false;

	if (p1 == p2) return false;

	if (!d1 || !d2)
	{
		wxMessageBox("d1 or d2 in Defense::SwapPlayers is nullptr! Returning false!");
		return false;
	}

	if ((p1 == d1 && p2 == d2) || (p1 == d2 && p2 == d1))
	{
		NHLplayer* temp = d1;
		d1 = d2;
		d2 = temp;
		return true;
	}

	wxMessageBox("NHLplayer* params in Defense::SwapPlayers do not match the players in this line! Returning false!");
	return false;
}

NHLplayer* Defense::ReplacePlayer(NHLplayer* p, char pos)
{
	if (!p) return nullptr;
	if (HasPlayer(p)) return nullptr;

	NHLplayer* temp = nullptr;
	if (pos == Position::L)
	{
		p->ActivatePlayer();
		d1->DeactivatePlayer();
		temp = d1;
		d1 = p;
		return temp;
	}
	else if (pos == Position::R)
	{
		p->ActivatePlayer();
		d2->DeactivatePlayer();
		temp = d2;
		d2 = p;
		return temp;
	}
	
	return nullptr;
}

void Lines::AddLine(NHLplayer* l, NHLplayer* c, NHLplayer* r, int line)
{
	switch (line)
	{
	case 1:
	{
		line1.AddLine(l, c, r);
		return;
	}
	case 2:
	{
		line2.AddLine(l, c, r);
		return;
	}
	case 3:
	{
		line3.AddLine(l, c, r);
		return;
	}
	case 4:
	{
		line4.AddLine(l, c, r);
		return;
	}
	}

	wxMessageBox("line did not match in Lines::AddLine!!");
}

Forwards* Lines::AddLine(NHLplayer* l, NHLplayer* c, NHLplayer* r)
{
	if (!l || !c || !r) nullptr;

	Forwards* F = nullptr;
	if (!line1.IsLineComplete())
	{
		F = &line1;
	//	line1.AddLine(l, c, r);
	//	return true;
	}

	else if (line1.IsDuplicatePlayer(l, c, r)) return nullptr;

	if (!line2.IsLineComplete())
	{
		if (!F)
			F = &line2;
	//	line2.AddLine(l, c, r);
	//	return true;
	}

	else if (line2.IsDuplicatePlayer(l, c, r)) return nullptr;

	if (!line3.IsLineComplete())
	{
		if (!F)
			F = &line3;
	//	line3.AddLine(l, c, r);
	//	return true;
	}

	else if (line3.IsDuplicatePlayer(l, c, r)) return nullptr;

	if (!F) F = &line4;

	if (F)
	{
		return F->AddLine(l, c, r);
	}

	return nullptr;
}

void Lines::AddDefLine(NHLplayer* l, NHLplayer* r, int line)
{
	switch (line)
	{
	case 1:
	{
		paring1.AddLine(l, r);
		return;
	}
	case 2:
	{
		paring2.AddLine(l, r);
		return;
	}
	case 3:
	{
		paring3.AddLine(l, r);
		return;
	}
	}

	wxMessageBox("line did not match in Lines::AddDefLine!!");
}

bool Lines::AddDefLine(NHLplayer* l, NHLplayer* r)
{
	if (l == r)
	{
		wxMessageBox("Trying to add two defensemen that are the same person! p1 " + l->GetName() + " p2 " + r->GetName());
		return false;
	}

	Defense* D = nullptr;
	if (!paring1.IsLineComplete())
	{
		D = &paring1;
	}

	else if (paring1.IsDuplicatePlayer(l, r)) return false;

	if (!paring2.IsLineComplete())
	{
		if (!D)
			D = &paring2;
	}

	else if (paring2.IsDuplicatePlayer(l, r)) return false;

	if (!paring3.IsLineComplete())
	{
		if (!D)
			D = &paring3;
	}

	else if (paring3.IsDuplicatePlayer(l, r)) return false;

	if (D)
	{
		D->AddLine(l, r);
		return true;
	}

	return false;
}

void Lines::AddGoalie(NHLplayer* p)
{
	if (!p)
	{
		wxMessageBox("param in Lines::AddGoalie is nullptr!");
		return;
	}
	goalie = p;
	goalie->ActivatePlayer();
}

void Lines::ResetInGameBockedShots()
{
	line1.ResetInGameBockedShots();
	line2.ResetInGameBockedShots();
	line3.ResetInGameBockedShots();
	line4.ResetInGameBockedShots();
	paring1.ResetInGameBockedShots();
	paring2.ResetInGameBockedShots();
	paring3.ResetInGameBockedShots();
}

void Lines::AddGamePlayed()
{
	if (goalie) goalie->SetGamePlayed();
	line1.AddGamePlayed();
	line2.AddGamePlayed();
	line3.AddGamePlayed();
	line4.AddGamePlayed();
	paring1.AddGamePlayed();
	paring2.AddGamePlayed();
	paring3.AddGamePlayed();
}

NHLplayer* Lines::Replace(NHLplayer* p, int line, char position, char swap_player_pos)
{
	if (!p) return nullptr;

	if (p->GetPosition() == Position::D)
	{
		if (swap_player_pos == Position::D)
			return ReplaceDef(p, line, position);

		return nullptr;
	}

	if (p->GetPosition() == Position::G)
	{
		if (swap_player_pos == Position::G)
			return ReplaceGoalie(p);

		return nullptr;
	}

	switch (line)
	{
	case 0: return line1.ReplacePlayer(p, position);
	case 1: return line2.ReplacePlayer(p, position);
	case 2: return line3.ReplacePlayer(p, position);
	case 3: return line4.ReplacePlayer(p, position);
	}

	wxMessageBox("No line found for param in Lines::Replace!");
	return nullptr;
}

NHLplayer* Lines::ReplaceDef(NHLplayer* p, int line, char position)
{
	if (!p) return nullptr;

	if (p->GetPosition() != Position::D) return nullptr;

	switch (line)
	{
	case 0: return paring1.ReplacePlayer(p, position);
	case 1: return paring2.ReplacePlayer(p, position);
	case 2: return paring3.ReplacePlayer(p, position);
	}

	wxMessageBox("No line found for param in Lines::ReplaceDef!");
	return nullptr;
}

NHLplayer* Lines::ReplaceGoalie(NHLplayer* p)
{
	if (!p) return nullptr;

	if (p->GetPosition() != Position::G) return nullptr;

	p->ActivatePlayer();
	NHLplayer* temp = goalie;
	goalie = p;
	temp->DeactivatePlayer();
	return temp;
}

bool Lines::SwapPlayers(NHLplayer* p1, NHLplayer* p2, int line)
{
	switch (line)
	{
	case 0: return line1.SwapPlayers(p1, p2);
	case 1: return line2.SwapPlayers(p1, p2);
	case 2: return line3.SwapPlayers(p1, p2);
	case 3: return line4.SwapPlayers(p1, p2);
	}

	return false;
}

bool Lines::SwapDefPlayers(NHLplayer* p1, NHLplayer* p2, int line)
{
	switch (line)
	{
	case 0: return paring1.SwapPlayers(p1, p2);
	case 1: return paring2.SwapPlayers(p1, p2);
	case 2: return paring3.SwapPlayers(p1, p2);
	}

	return false;
}

NHLplayer* Lines::AddStartingForward(NHLplayer* p, int line)
{
	if (line == 0)
	{
		if (!line1.IsLineComplete())
		{
			NHLplayer* nhl_p = line1.AddStartingPlayer(p, p->GetPosition());
			return nullptr;
		}
		return CycleForwards(p, line);
	}
	if (line == 1)
	{
		if (!line2.IsLineComplete())
		{
			line2.AddStartingPlayer(p, p->GetPosition());
			return nullptr;
		}
		return CycleForwards(p, line);
	}
	if (line == 2)
	{
		if (!line3.IsLineComplete())
		{
			line3.AddStartingPlayer(p, p->GetPosition());
			return nullptr;
		}
		return CycleForwards(p, line);
	}

	return nullptr;
}

NHLplayer* Lines::CycleForwards(NHLplayer* p, int line)
{
	Forwards* F = nullptr;
	while (line < 4)
	{
		F = GetForwardLine(line);
		if (!F)
		{
			return nullptr;
		}
		if (!F->IsLineComplete())
		{
			if (p)
				return F->AddStartingPlayer(p, p->GetPosition());
			return nullptr;
		}
		p = F->AddStartingPlayer(p);
		++line;
	}
	return p;
}

Forwards* Lines::GetForwardLine(int line)
{
	switch (line)
	{
	case 0: return &line1;
	case 1: return &line2;
	case 2: return &line3;
	case 3: return &line4;
	}

	wxMessageBox("line is higher or lower then 0 or 2 in Lines::GetForwardLine!!");
	return nullptr;
}

Forwards* Lines::GetNextFowardLine(Forwards* f)
{
	if (!f)
	{
		wxMessageBox("Fowards* passed as parameter in Lines::GetNextForwardLine is nullptr!!!");
		return f;
	}
	if (f == &line1)
		return &line2;
	if (f == &line2)
		return &line3;
	if (f == &line3)
		return &line4;
	if (f == &line4)
		return &line1;

	wxMessageBox("Fowards* passed as parameter in Lines::GetNextForwardLine does not match any lines!!!");
	return f;
}

Defense* Lines::GetNextDefenseLine(Defense* d)
{
	if (!d)
	{
		wxMessageBox("Defense* passed as parameter in Lines::GetNextDefenseLine is nullptr!!!");
		return d;
	}
	if (d == &paring1)
		return &paring2;
	if (d == &paring2)
		return &paring3;
	if (d == &paring3)
		return &paring1;

	wxMessageBox("Defense* passed as parameter in Lines::GetNextDefenseLine does not match any lines!!!");
	return d;
}

bool Lines::IsForwardsComplete()
{
	if (line1.IsLineComplete() && line2.IsLineComplete() && line3.IsLineComplete() && line4.IsLineComplete()) return true;

	return false;
}

bool Lines::IsDefenseComplete()
{
	if (paring1.IsLineComplete() && paring2.IsLineComplete() && paring3.IsLineComplete()) return true;

	return false;
}

double Lines::GetLineupValue()
{
	double d = 0.0;
	d = line1.GetLineStrength();
	d += line2.GetLineStrength();
	d += line3.GetLineStrength();
	d += paring1.GetLineStrength();
	d += paring2.GetLineStrength();
	d += paring3.GetLineStrength();
	d += goalie ? goalie->GetGameScore() : 0.0;

	return d;
}

double Lines::GetShotsPerGame()
{
	double spg = 0.0;
	spg += line1.GetShotsPerGame();
	spg += line2.GetShotsPerGame();
	spg += line3.GetShotsPerGame();
	spg += line4.GetShotsPerGame();
	spg += paring1.GetShotsPerGame();
	spg += paring2.GetShotsPerGame();
	spg += paring3.GetShotsPerGame();

	return spg;
}

void Lines::CalcValues()
{
	CorsiPercent = 0.0;
	line1.CalcValues();
	line2.CalcValues();
	line3.CalcValues();
	line4.CalcValues();
	paring1.CalcValues();
	paring2.CalcValues();
	CorsiPercent += line1.GetCorsiPercent();
	CorsiPercent += line2.GetCorsiPercent();
	CorsiPercent += line3.GetCorsiPercent();
	CorsiPercent += line4.GetCorsiPercent();
	CorsiPercent += paring1.GetCorsiPercent();
	CorsiPercent += paring2.GetCorsiPercent();
}

NHLTeam::NHLTeam(wxString location, wxString teamname, wxString div, int divint, int teamint, NHL_Division* d) : m_parent_div(d), abbrname(teamname), division(div), divnum(divint), teamnum(teamint)
{
	name = teamnames.GetTeamLongName(teamint);	
	bool b = logo.IsOk();
	b = logo.IsOk();
}

bool NHLTeam::AddPlayer(NHLplayer& p)
{
	TeamNames tn;
	if (tn.GetShortNameID(p.GetTeam()) == teamnum)
	{
		switch (p.GetPosition())
		{
		case Position::C:
		case Position::L:
		case Position::R:
		case 'F':
		{
			forwards.push_back(p);
			return true;
		}
		case Position::D:
		{
			defensmen.push_back(p);
			return true;
		}
		case Position::G:
		{
			goalies.push_back(p);
			return true;
		}
		default: return false;
		}
	}
	
	return false;
}

void NHLTeam::AddPlayerFromSavedFile(NHLplayer& p)
{
	switch (p.GetPosition())
	{
	case Position::C:
	case Position::L:
	case Position::R:
	case 'F':
	{
		forwards.push_back(p);
		return;
	}
	case Position::D:
	{
		defensmen.push_back(p);
		return;
	}
	case Position::G:
	{
		goalies.push_back(p);
		return;
	}
	}
}

void NHLTeam::Save()
{
	wxString filename = SavedFile + abbrname + ".txt";
	wxTempFileOutputStream o(filename);
	if (!o.IsOk())
	{
		wxMessageBox("Could not open file: " + filename + " in NHLTeam::Save!");
		return;
	}

	wxTextOutputStream out(o);
	out << abbrname << '\n';
	int players = forwards.size() + defensmen.size() + goalies.size();
	out << players << '\n';
	for (size_t i = 0; i < forwards.size(); ++i)
		forwards[i].Save(out);
	for (size_t i = 0; i < defensmen.size(); ++i)
		defensmen[i].Save(out);
	for (size_t i = 0; i < goalies.size(); ++i)
		goalies[i].Save(out);

	
	out << stringforward.size() << '\n';
	for (size_t i = 0; i < stringforward.size(); ++i)
		out << (int)stringforward[i].id << '\n' << stringforward[i].first << '\n' << stringforward[i].second << '\n' << stringforward[i].last << '\n' << stringforward[i].gameScore << '\n';

	out << stringdefense.size() << '\n';
	for (size_t i = 0; i < stringdefense.size(); ++i)
		out << (int)stringdefense[i].id << '\n' << stringdefense[i].first << '\n' << stringdefense[i].second << '\n' << stringdefense[i].last << '\n' << stringdefense[i].gameScore << '\n';
	
	o.Commit();
}

void NHLTeam::Retrieve(wxString& filename)
{
	wxFile file;

	if (!file.Exists(filename))
	{
		wxMessageBox(filename + " does not exist in NHLTeam::Retrieve!");
		return;
	}
	if (!file.Open(filename, wxFile::read))
	{
		wxMessageBox("Could not open file: " + filename + " in NHLTeam::Retrieve!");
		return;
	}

	wxFileInputStream o(file);
	wxTextInputStream in(o);

	char c = ' ';
	in >> abbrname;
	int players = 0;
	in >> players;
	for (int i = 0; i < players; ++i)
	{
		NHLplayer p;
		p.Retrieve(in);
		AddPlayerFromSavedFile(p);
	}

	wxString fileschedule = "SavedFiles/" + abbrname + "_2022_23.txt";
	wxFile F;
	if (!F.Exists(fileschedule))
	{
		wxMessageBox(fileschedule + " does not exist in NHLTeam::Retrieve!");
		return;
	}
	if (!F.Open(fileschedule, wxFile::read))
	{
		wxMessageBox("Could not open file: " + fileschedule + " in NHLTeam::Retrieve!");
		return;
	}

	wxFileInputStream O(F);
	wxTextInputStream In(O);

	wxString day = "";
	wxString month = "";
	wxString month_number = "";
	wxString time = "";
	wxString pm = "";
	wxString at_or_team = "";

	bool homegame = true;
	while (!F.Eof())
	{
		In >> day;
		In >> month;
		In >> month_number;
		In >> time;
		if (time != "T.B.A")
			In >> pm;
		char c = ' ';
		while (c != '\n')
		{
			if (F.Eof())
				break;
			In >> c;
			if (c != '\n')
				at_or_team += c;

			if (at_or_team == "AT ")
			{
				homegame = false;
				at_or_team = "";
			}
		}
		wxDateTime T;
		if (!T.ParseDate(day + " " + month + " " + month_number + " 2022"))
		{
			if (!T.ParseDate(day + " " + month + " " + month_number + " 2023"))
			{
				wxMessageBox("Date failed in NHLTeam::Retrieve! Date was: " + day + " " + month + " " + month_number + " 2023");
			}
		}
		if (T.IsValid())
		{
			if (T.GetMonth() <= wxDateTime::Month::Apr)
				T.SetYear(2023);
			else
				T.SetYear(2022);

			wxString date = T.Format(STANDARD_DATE);

			int opponentid = teamnames.GetCitieNameID(at_or_team);
			NHLTeam* opponent = m_parent_div->GetTeam(opponentid, teamnames.GetDivisionIdByTeamId(opponentid));
			if (!opponent)
				wxMessageBox("opponent returned from m_parent_div->GetTeam() is nullptr!!");

			season.push_back(Season_Schedule(T, this, opponent, homegame));
		}
		day = "";
		month = "";
		month_number = "";
		time = "";
		pm = "";
		at_or_team = "";
		homegame = true;
	}


	/*
	int stringsize = 0;
	in >> stringsize;
	for (size_t i = 0; i < stringsize; ++i)
	{
		long l = 0;
		int Id = 0;
		wxString lt = "";
		double gs = 0.0;
		wxString t = "", f = "", s = "", last = "";

		in >> Id >> f >> s >> last >> gs;
		long l = Id;
		stringforward.push_back(stringlines(l, "line", gs, abbrname, f, s, last));
	}

	in >> stringsize;
	for (size_t i = 0; i < stringsize; ++i)
	{
		long l = 0;
		int Id = 0;
		wxString lt = "";
		double gs = 0.0;
		wxString t = "", f = "", s = "";

		in >> Id >> f >> s >> gs;
		long l = Id;
		stringforward.push_back(stringlines(l, "line", gs, abbrname, f, s));
	}

	SortLines(false);
	*/
}

NHLplayer* NHLTeam::FindForwardWithLastName(wxString& l)
{
	for (size_t i = 0; i < forwards.size(); ++i)
	{
		if (forwards[i].GetName().find(l) != -1) return &forwards[i];
	}

	return nullptr;
}

NHLplayer* NHLTeam::FindDefWithLastName(wxString& l)
{
	for (size_t i = 0; i < defensmen.size(); ++i)
	{
		if (defensmen[i].GetName().find(l) != -1) return &defensmen[i];
	}

	return nullptr;
}

NHLplayer* NHLTeam::FindPlayerWithID(long id)
{
	for (size_t i = 0; i < forwards.size(); ++i)
	{
		if (forwards[i].IsPlayerId(id)) return &forwards[i];
	}

	for (size_t i = 0; i < defensmen.size(); ++i)
	{
		if (defensmen[i].IsPlayerId(id)) return &defensmen[i];
	}

	for (size_t i = 0; i < goalies.size(); ++i)
	{
		if (goalies[i].IsPlayerId(id)) return &goalies[i];
	}

	return nullptr;
}

void NHLTeam::SortLines(bool b)
{
	if (abbrname == "COL")
		int Catch = 0;
	wxVector<Forwards*> line_with_sameplayer_twice;
	for (size_t i = 0; i < stringforward.size(); ++i)
	{
		Forwards* F = lines.AddLine(stringforward[i].p1, stringforward[i].p2, stringforward[i].p3);
		if (F) line_with_sameplayer_twice.push_back(F);
		if (lines.IsForwardsComplete()) break;
	}

	AddBackups(forwards, spareforwards);
	//fill partially filledlines...
	for (size_t i = 0; i < line_with_sameplayer_twice.size(); ++i)
	{
		Forwards* F = line_with_sameplayer_twice[i];
		if (spareforwards.size() > i)
			F->AddStartingPlayer(spareforwards[i]);
	}

	//check that the best players are in the lineup...
	this->OptimizeLineup();

	if (!lines.IsForwardsComplete())
	{
		for (int i = 0; i < spareforwards.size(); ++i)
		{
			if (i + 1 < spareforwards.size() && i + 2 < spareforwards.size())
			{
				if (lines.AddLine(spareforwards[i], spareforwards[i + 1], spareforwards[i + 2]))
				{
					spareforwards.erase(&spareforwards[i], &spareforwards[i + 3]);
					if (i > 2)
						i -= 4;
					else if (i > 1)
						i -= 3;
					else if (i == 1)
						i -= 2;
					else
						i -= 1;
				}
				if (lines.IsForwardsComplete()) 
					break;
			}
		}
		if (!lines.IsForwardsComplete())
			wxMessageBox("Forward lines are not complete for " + abbrname);
	}

	if (abbrname == "CHI")
	{
		stringlines* S = nullptr;
		for (size_t i = 0; i < stringdefense.size(); ++i)
		{
			S = &stringdefense[i];
		}
	}

	for (size_t i = 0; i < stringdefense.size(); ++i)
	{
		lines.AddDefLine(stringdefense[i].p1, stringdefense[i].p2);
		if (lines.IsDefenseComplete()) break;
	}

	AddBackups(defensmen, sparedefense);
	if (!lines.IsDefenseComplete())
	{
		int i = 0;
		for (i; i < sparedefense.size(); ++i)
		{
			if (i + 1 < sparedefense.size())
			{
				if (lines.AddDefLine(sparedefense[i], sparedefense[i + 1]))
				{
					sparedefense.erase(&sparedefense[i], &sparedefense[i + 2]);
					if (i > 1)
						i -= 3;
					else if (i == 1)
						i -= 2;
					else
						i -= 1;
				}
				if (lines.IsDefenseComplete())
					break;
			}
		}

		if (!lines.IsDefenseComplete())
			wxMessageBox("Defensive lines are not complete for " + abbrname);
	}

	if (goalies.size())
		lines.AddGoalie(&goalies[0]);

	lines.CalcValues();
	Team_rating = lines.GetLineupValue();
}

void NHLTeam::AddForwardStringLine(stringlines& f)
{
	f.p1 = FindForwardWithLastName(f.first);
	f.p2 = FindForwardWithLastName(f.second);
	f.p3 = FindForwardWithLastName(f.last);
	
	if (!f.p1 || !f.p2 || !f.p3) 
		return;

	f.CalcGameScore();
	if (!stringforward.size())
	{
		stringforward.push_back(f);
		return;
	}

	if (abbrname == "COL")
		int caught = 0;

	if (IsDuplicateStringLine(f))
		return;

	size_t i = 0;
	while (i < stringforward.size() && f.gameScore < stringforward[i].gameScore)
		++i;

	if (stringforward.size() == i)
	{
		stringforward.push_back(f);
		return;
	}

	stringforward.insert(&stringforward[i], f);
}

void NHLTeam::AddDefStringLines(stringlines& d)
{
	d.p1 = FindDefWithLastName(d.first);
	d.p2 = FindDefWithLastName(d.second);

	if (!d.p1 || !d.p2) return;
	if (d.p1 == d.p2) return;

	d.CalcGameScore();
	if (!stringdefense.size())
	{
		stringdefense.push_back(d);
		return;
	}


	//Make sure we are not adding another line with the same people in stringdefense vector!
	for (size_t i = 0; i < stringdefense.size(); ++i)
	{
		if (stringdefense[i].p1 == d.p1 && stringdefense[i].p2 == d.p2)
			return;
		if (stringdefense[i].p2 == d.p1 && stringdefense[i].p1 == d.p2)
			return;
	}

	size_t i = 0;
	while (i < stringdefense.size() && d.gameScore < stringdefense[i].gameScore)
		++i;

	if (stringdefense.size() == i)
	{
		stringdefense.push_back(d);
		return;
	}

	stringdefense.insert(&stringdefense[i], d);
}

void NHLTeam::AddGameOutcome(GameStats gs)
{
	gamesplayed++;
	if (!PlayoffSeed)
	{
		gamerecord.AddGameOutCome(gs, abbrname);
		lines.AddGamePlayed();
	}
	else
	{
		playoffrecord.AddGameOutCome(gs, abbrname);
	}
}

void NHLTeam::AddPlayoffGameOutcome(GameStats gs)
{
	playoffrecord.AddGameOutCome(gs, abbrname);
}

int NHLTeam::GetGamesPlayed()
{
	return gamesplayed;
}

void NHLTeam::AddStats(Stats& S)
{
	if (S.Pos == Position::C || S.Pos == Position::L || S.Pos == Position::R)
	{
		for (size_t i = 0; i < forwards.size(); ++i)
		{
			if (forwards[i].IsPlayerId(S.id) || forwards[i].IsPlayerByName(S.name))
			{
				forwards[i].AddStats(S);
				return;
			}
		}
	}

	if (S.Pos == Position::D)
	{
		for (size_t i = 0; i < defensmen.size(); ++i)
		{
			if (defensmen[i].IsPlayerId(S.id) || defensmen[i].IsPlayerByName(S.name))
			{
				defensmen[i].AddStats(S);
				return;
			}
		}
	}

	if (S.Pos == Position::G)
	{
		for (size_t i = 0; i < goalies.size(); ++i)
		{
			if (goalies[i].IsPlayerId(S.id) || goalies[i].IsPlayerByName(S.name))
			{
				goalies[i].AddStats(S);
				return;
			}
		}
	}
}

void NHLTeam::SetLogo(wxBitmap& b)
{
	logo = wxBitmap(b);
	bool B = logo.IsOk();
}

NHLplayer* NHLTeam::ReplaceStarter(NHLplayer* p, int line, char pos, char swap_player_pos)
{
	if (p->IsStarter()) 
		return nullptr;

	return lines.Replace(p, line, pos, swap_player_pos);
}

bool NHLTeam::SwapStarters(NHLplayer* p1, NHLplayer* p2, int line)
{
	if (!p1 || !p2) return false;

	if(p1->GetPosition() == Position::D && p2->GetPosition() == Position::D)
		return SwapDefensemen(p1, p2, line);
	
	char P1 = p1->GetPosition();
	char P2 = p2->GetPosition();

	if ((P1 == Position::L || P1 == Position::C || P1 == Position::R) && (P2 == Position::L || P2 == Position::C || P2 == Position::R))
		return SwapForwards(p1, p2, line);

	return false;
}

wxString NHLTeam::GetTeamabbr(bool b)
{
	if (b)
	{
		if (Team::LA == teamnum) return "LAK";
		if (Team::SJ == teamnum) return "SJS";
		if (Team::TB == teamnum) return "TBL";
		if (Team::NJ == teamnum) return "NJD";
	}

	return abbrname;
}

bool NHLTeam::CheckLastName(wxString n)
{
	NHLplayer* N = FindForwardWithLastName(n);
	if (!N)
		N = FindDefWithLastName(n);

	if (N) return true;

	return false;
}

void NHLTeam::PurgePlayersWithNoStats()
{
	for (size_t i = 0; i < forwards.size(); ++i)
	{
		NHLplayer* p = &forwards[i];
		if (!forwards[i].IsStatsActive())
		{
			forwards.erase(&forwards[i]);
			--i;
		}
	}
	for (size_t i = 0; i < defensmen.size(); ++i)
	{
		if (!defensmen[i].IsStatsActive())
		{
			defensmen.erase(&defensmen[i]);
			--i;
		}
	}
	
	for (size_t i = 0; i < goalies.size(); ++i)
	{
		if (!goalies[i].IsStatsActive())
		{
			goalies.erase(&goalies[i]);
			--i;
		}
	}
}

void NHLTeam::CalibrateStats()
{
	for (size_t i = 0; i < forwards.size(); ++i)
	{
		forwards[i].CalibrateStats();
		if (forwards[i].GetName().size() > namesize)
			namesize = forwards[i].GetName().size();
	}
	for (size_t i = 0; i < defensmen.size(); ++i)
	{
		defensmen[i].CalibrateStats();
		if (defensmen[i].GetName().size() > namesize)
			namesize = defensmen[i].GetName().size();
	}
	for (size_t i = 0; i < goalies.size(); ++i)
	{
		goalies[i].CalibrateStats();
		if (goalies[i].GetName().size() > namesize)
			namesize = goalies[i].GetName().size();
	}

	//sort after calibration...
	SortPlayerVector(forwards);
	SortPlayerVector(defensmen);
	SortPlayerVector(goalies);

	//add backups...
//	AddBackups(forwards, spareforwards);
//	AddBackups(defensmen, sparedefense);
}

void NHLTeam::SetTeamForPlayoffs(int seed)
{
	this->SetPlayoffSeed(seed);
	for (size_t i = 0; i < forwards.size(); ++i)
		forwards[i].SetPlayoffsTrue();
	for (size_t i = 0; i < defensmen.size(); ++i)
		defensmen[i].SetPlayoffsTrue();
	for (size_t i = 0; i < goalies.size(); ++i)
		goalies[i].SetPlayoffsTrue();
	for (size_t i = 0; i < spareforwards.size(); ++i)
		spareforwards[i]->SetPlayoffsTrue();
	for (size_t i = 0; i < sparedefense.size(); ++i)
		sparedefense[i]->SetPlayoffsTrue();
}

wxListItem GetListItem(int col, wxString value, long id)
{
	wxListItem item;
	item.SetMask(wxLIST_MASK_TEXT);
	item.SetId(id);
	item.SetColumn(col);
	item.SetText(value);
	return item;
}

void NHLTeam::AppendPlayerInfotoListBox(wxListCtrl* l)
{
	ForwardInfotoListBox(l);
	DefenseInfotoListBox(l);
	GoalieInfotoListBox(l);
}

void NHLTeam::ForwardInfotoListBox(wxListCtrl* l)
{
	for (size_t i = 0; i < forwards.size(); ++i)
	{
		wxString p = "";
		p << forwards[i].GetPosition();
		wxString s = "";
		s << forwards[i].GetShot();
		wxString playerid = "";
		playerid << forwards[i].GetPlayerId();
		wxString a = "";
		a << forwards[i].GetAge();
		int index = l->InsertItem(GetListItem(0, forwards[i].GetName(), forwards[i].GetPlayerId()));
		l->SetItem(index, 1, GetStringValue(forwards[i].GetGameScore(), 2));
		l->SetItem(index, 2, GetStringValue(forwards[i].GetGoals(), 2));
		l->SetItem(index, 3, GetStringValue(forwards[i].GetAssists(), 2));
		l->SetItem(index, 4, p);
		l->SetItem(index, 5, s);
		l->SetItem(index, 6, forwards[i].IsStarter() ? "Yes" : "No");
		l->SetItem(index, 7, GetStringValue(forwards[i].GetWeight(), 2));
		l->SetItem(index, 8, playerid);
		l->SetItem(index, 9, a);
	}
}

void NHLTeam::DefenseInfotoListBox(wxListCtrl* l)
{
	for (size_t i = 0; i < defensmen.size(); ++i)
	{
		wxString p = "";
		p << defensmen[i].GetPosition();
		wxString s = "";
		s << defensmen[i].GetShot();
		wxString playerid = "";
		playerid << defensmen[i].GetPlayerId();
		wxString a = "";
		a << defensmen[i].GetAge();
		int index = l->InsertItem(GetListItem(0, defensmen[i].GetName(), defensmen[i].GetPlayerId()));
		l->SetItem(index, 1, GetStringValue(defensmen[i].GetGameScore(), 2));
		l->SetItem(index, 2, GetStringValue(defensmen[i].GetGoals(), 2));
		l->SetItem(index, 3, GetStringValue(defensmen[i].GetAssists(), 2));
		l->SetItem(index, 4, p);
		l->SetItem(index, 5, s);
		l->SetItem(index, 6, defensmen[i].IsStarter() ? "Yes" : "No");
		l->SetItem(index, 7, GetStringValue(defensmen[i].GetWeight(), 2));
		l->SetItem(index, 8, playerid);
		l->SetItem(index, 9, a);
	}
}

void NHLTeam::GoalieInfotoListBox(wxListCtrl* l)
{
	for (size_t i = 0; i < goalies.size(); ++i)
	{
		wxString p = "";
		p << goalies[i].GetPosition();
		wxString s = "";
		s << goalies[i].GetShot();
		wxString playerid = "";
		playerid << goalies[i].GetPlayerId();
		wxString a = "";
		a << goalies[i].GetAge();
		int index = l->InsertItem(GetListItem(0, goalies[i].GetName(), goalies[i].GetPlayerId()));
		l->SetItem(index, 1, GetStringValue(goalies[i].GetGameScore(), 2));
		l->SetItem(index, 2, GetStringValue(goalies[i].GetGoals(), 2));
		l->SetItem(index, 3, GetStringValue(goalies[i].GetAssists(), 2));
		l->SetItem(index, 4, p);
		l->SetItem(index, 5, s);
		l->SetItem(index, 6, goalies[i].IsStarter() ? "Yes" : "No");
		l->SetItem(index, 7, GetStringValue(goalies[i].GetWeight(), 2));
		l->SetItem(index, 8, playerid);
		l->SetItem(index, 9, a);
	}
}

void NHLTeam::OptimizeLineup()
{
	wxVector<NHLplayer*> one;
	wxVector<NHLplayer*> two;
	wxVector<NHLplayer*> three;
	wxVector<NHLplayer*> four;
	
	for (size_t i = 0; i < forwards.size() && i < 12; ++i)
	{
		if (!forwards[i].IsStarter())
		{
			if (i >= 0 && i <= 2)
				one.push_back(&forwards[i]);

			else if (i >= 3 && i <= 5)
				two.push_back(&forwards[i]);

			else if (i >= 6 && i <= 8)
				three.push_back(&forwards[i]);

			else
				four.push_back(&forwards[i]);	
		}
	}

	for (size_t i = 0; i < one.size(); ++i)
	{
		NHLplayer* p = lines.CycleForwards(one[i], 0);
		if (p) p->DeactivatePlayer();
		PushToBackup(p);
	}

	for (size_t i = 0; i < two.size(); ++i)
	{
		NHLplayer* p = lines.CycleForwards(two[i], 1);
		if (p) p->DeactivatePlayer();
		PushToBackup(p);
	}

	for (size_t i = 0; i < three.size(); ++i)
	{
		NHLplayer* p = lines.CycleForwards(three[i], 2);
		if (p) p->DeactivatePlayer();
		PushToBackup(p);
	}

	for (size_t i = 0; i < four.size(); ++i)
	{
		NHLplayer* p = lines.CycleForwards(four[i], 3);
		if (p) p->DeactivatePlayer();
		PushToBackup(p);
	}
}

void NHLTeam::PushToBackup(NHLplayer* p)
{
	wxFile file;
	if (!p)
	{
		return;
	}

	size_t i = 0;
	while (i < spareforwards.size() && spareforwards[i]->GetGameScore() > p->GetGameScore())
		++i;

	if (i == spareforwards.size())
		spareforwards.push_back(p);

	else
		spareforwards.insert(&spareforwards[i], p);
	
}

void NHLTeam::RemoveFromBackup(NHLplayer* p)
{
	for (size_t i = 0; i < spareforwards.size(); ++i)
	{
		if (spareforwards[i] == p)
		{
			spareforwards.erase(&spareforwards[i]);
			return;
		}
	}
}

bool NHLTeam::IsDuplicateStringLine(stringlines& s)
{
	if (s.p1 && s.p2 && s.p3)
	{
		for (size_t i = 0; i < stringforward.size(); ++i)
		{
			if (s.p1 == stringforward[i].p1 && s.p2 == stringforward[i].p2 && s.p3 == stringforward[i].p3)
				return true;
		}
		return false;
	}

	for (size_t i = 0; i < stringforward.size(); ++i)
	{
		if (s.p1 == stringforward[i].p1 && s.p2 == stringforward[i].p2)
			return true;
	}
	return false;
	
}

wxVector<NHLplayer>& NHLTeam::GetForwards()
{
	return forwards;
}

wxVector<NHLplayer>& NHLTeam::GetDefensemen()
{
	return defensmen;
}

wxVector<NHLplayer>& NHLTeam::GetGoalies()
{
	return goalies;
}

void NHLTeam::SortPlayerVector(wxVector<NHLplayer>& v)
{
	static auto genericCompare = [](NHLplayer item1, NHLplayer item2)
	{
		return item1.GetGameScore() > item2.GetGameScore();
	};

	std::sort(v.begin(), v.end(), genericCompare);
}

void NHLTeam::AddBackups(wxVector<NHLplayer>& starters, wxVector<NHLplayer*>& backups)
{
	for (size_t i = 0; i < starters.size(); ++i)
	{
		if (!starters[i].IsStarter()) backups.push_back(&starters[i]);
	}
}

void NHLTeam::AddToSpareForwards(NHLplayer* p)
{
	for (size_t i = 0; i < spareforwards.size(); ++i)
	{
		if (spareforwards[i]->GetGameScore() < p->GetGameScore())
		{
			spareforwards.insert(&spareforwards[i], p);
			return;
		}
	}
}

void NHLTeam::FindBestStarters()
{
	NHLplayer* p1 = nullptr; 

	if (abbrname == "COL")
		int caught = 0;
	int count = 0;
	for (size_t i = 0; i < 6 && i < forwards.size(); ++i)
	{
		if (count >= 3) return;
		if (!forwards[i].IsStarter())
		{
			++count;
			p1 = &forwards[i];
			int line = 0;
			if (i == 1 || i == 3) line = 1;
			else if(i > 3) line = 2;
			p1 = lines.AddStartingForward(p1, line);
			if (p1)
			{
				p1->DeactivatePlayer();
				AddToSpareForwards(p1);
			}
		}
	}
}

bool NHLTeam::SwapForwards(NHLplayer* p1, NHLplayer* p2, int line)
{
	return lines.SwapPlayers(p1, p2, line);
}

bool NHLTeam::SwapDefensemen(NHLplayer* p1, NHLplayer* p2, int line)
{
	return lines.SwapDefPlayers(p1, p2, line);
}

NHLplayer* NHLTeam::FindForwardWithName(wxString n)
{
	for (size_t i = 0; i < forwards.size(); ++i)
	{
		if (forwards[i].GetName() == n) return &forwards[i];
	}

	return nullptr;
}

NHLplayer* NHLTeam::FindDefenseWithName(wxString n)
{
	for (size_t i = 0; i < defensmen.size(); ++i)
	{
		if (defensmen[i].GetName() == n) return &defensmen[i];
	}

	return nullptr;
}

NHLplayer* NHLTeam::FindGoalieWithName(wxString n)
{
	for (size_t i = 0; i < goalies.size(); ++i)
	{
		if (goalies[i].GetName() == n) return &goalies[i];
	}

	return nullptr;
}

NHL_Division::NHL_Division(int conf, int div, NHL_Conference* c) : m_parent_conf(c), conference(conf), division(div)
{
	
	TeamNames tn;
	divname = tn.GetDivName(division);
	switch (division)
	{
	case Div::Atlantic:
	{
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::BUF), tn.GetShortName(Team::BUF), tn.GetDivName(division), division, Team::BUF, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::BOS), tn.GetShortName(Team::BOS), tn.GetDivName(division), division, Team::BOS, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::DET), tn.GetShortName(Team::DET), tn.GetDivName(division), division, Team::DET, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::FLA), tn.GetShortName(Team::FLA), tn.GetDivName(division), division, Team::FLA, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::MTL), tn.GetShortName(Team::MTL), tn.GetDivName(division), division, Team::MTL, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::OTT), tn.GetShortName(Team::OTT), tn.GetDivName(division), division, Team::OTT, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::TB), tn.GetShortName(Team::TB), tn.GetDivName(division), division, Team::TB, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::TOR), tn.GetShortName(Team::TOR), tn.GetDivName(division), division, Team::TOR, this));
		break;
	}
	case Div::Metropolitan:
	{
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::CAR), tn.GetShortName(Team::CAR), tn.GetDivName(division), division, Team::CAR, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::CBJ), tn.GetShortName(Team::CBJ), tn.GetDivName(division), division, Team::CBJ, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::NJ), tn.GetShortName(Team::NJ), tn.GetDivName(division), division, Team::NJ, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::NYI), tn.GetShortName(Team::NYI), tn.GetDivName(division), division, Team::NYI, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::NYR), tn.GetShortName(Team::NYR), tn.GetDivName(division), division, Team::NYR, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::PHI), tn.GetShortName(Team::PHI), tn.GetDivName(division), division, Team::PHI, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::PIT), tn.GetShortName(Team::PIT), tn.GetDivName(division), division, Team::PIT, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::WSH), tn.GetShortName(Team::WSH), tn.GetDivName(division), division, Team::WSH, this));
		break;
	}
	case Div::Central:
	{
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::ARI), tn.GetShortName(Team::ARI), tn.GetDivName(division), division, Team::ARI, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::CHI), tn.GetShortName(Team::CHI), tn.GetDivName(division), division, Team::CHI, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::COL), tn.GetShortName(Team::COL), tn.GetDivName(division), division, Team::COL, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::DAL), tn.GetShortName(Team::DAL), tn.GetDivName(division), division, Team::DAL, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::MIN), tn.GetShortName(Team::MIN), tn.GetDivName(division), division, Team::MIN, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::NSH), tn.GetShortName(Team::NSH), tn.GetDivName(division), division, Team::NSH, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::STL), tn.GetShortName(Team::STL), tn.GetDivName(division), division, Team::STL, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::WPG), tn.GetShortName(Team::WPG), tn.GetDivName(division), division, Team::WPG, this));
		break;
	}
	case Div::Pacific:
	{
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::ANA), tn.GetShortName(Team::ANA), tn.GetDivName(division), division, Team::ANA, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::CGY), tn.GetShortName(Team::CGY), tn.GetDivName(division), division, Team::CGY, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::SEA), tn.GetShortName(Team::SEA), tn.GetDivName(division), division, Team::SEA, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::VGK), tn.GetShortName(Team::VGK), tn.GetDivName(division), division, Team::VGK, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::LA), tn.GetShortName(Team::LA), tn.GetDivName(division), division, Team::LA, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::SJ), tn.GetShortName(Team::SJ), tn.GetDivName(division), division, Team::SJ, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::VAN), tn.GetShortName(Team::VAN), tn.GetDivName(division), division, Team::VAN, this));
		teams.push_back(NHLTeam(tn.GetTeamLogo(Team::EDM), tn.GetShortName(Team::EDM), tn.GetDivName(division), division, Team::EDM, this));
		break;
	}
	default:
	{
		wxMessageBox("No matches for NHLDivision in constructor!!!");
		return;
	}
	
	}
	for (size_t i = 0; i < teams.size(); ++i)
		DivStandings.push_back(&teams[i]);
}

bool NHL_Division::AddPlayer(NHLplayer& p)
{
	for (int i = 0; i < teams.size(); ++i)
	{
		if (teams[i].AddPlayer(p)) return true;
	}

	return false;
}

bool NHL_Division::AddLine(stringlines& s, int t)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		if (teams[i].GetTeamID() == t)
		{
			if (s.StringlineSize() == 3)
				teams[i].AddForwardStringLine(s);
			else if (s.StringlineSize() == 2)
				teams[i].AddDefStringLines(s);

			return true;
		}
	}

	return false;
}

bool NHL_Division::AddStats(Stats& S, int team)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		if (team == teams[i].GetTeamID())
		{
			teams[i].AddStats(S);
			return true;
		}
	}

	return false;
}

void NHL_Division::SetLogo(wxBitmap& b, int t)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		if (teams[i].GetTeamID() == t)
		{
			teams[i].SetLogo(b);
			return;
		}
	}
}

void NHL_Division::Save()
{
	wxString filename = SavedFile + divname + ".txt";
	wxTempFileOutputStream o(filename);
	if (!o.IsOk())
	{
		wxMessageBox("Could not open file: " + filename + " in NHL_Division::Save!");
		return;
	}

	wxTextOutputStream out(o);
	out << divname << '\n';
	for (size_t i = 0; i < teams.size(); ++i)
	{
		out << teams[i].GetTeamabbr() << '\n';
		teams[i].Save();
	}

	o.Commit();
}

void NHL_Division::Retrieve(wxString& filename)
{
	wxFile file;

	if (!file.Exists(filename))
	{
		wxMessageBox(filename + " does not exist in NHL_Division::Retrieve!");
		return;
	}
	if (!file.Open(filename, wxFile::read))
	{
		wxMessageBox("Could not open file: " + filename + " in NHL_Division::Retrieve!");
		return;
	}

	wxFileInputStream o(file);
	wxTextInputStream in(o);
	in >> divname;
	wxString te = "";
	TeamNames tn;
	division = tn.GetDivID(divname);

	for (size_t i = 0; i < teams.size(); ++i)
	{
		wxString teamfile = SavedFile + teams[i].GetTeamabbr() + ".txt";
		teams[i].Retrieve(teamfile);
	}
}

void NHL_Division::SortLines()
{
	for (size_t i = 0; i < teams.size(); ++i)
		teams[i].SortLines();
}

NHL_Conference::NHL_Conference(int n, int d1, int d2, NHL_Conference* c) : other_Conference(c), conference(n), div1(n, d1, this), div2(n, d2, this)
{
	TeamNames tn;
	conf_name = tn.GetConferenceName(conference);
}

NHL_Conference::~NHL_Conference()
{
	if (playoff_eastern)
		delete playoff_eastern;
	if (playoff_western)
		delete playoff_western;
}

bool NHL_Conference::AddPlayer(NHLplayer& p)
{
	if (div1.AddPlayer(p)) return true;
	if (div2.AddPlayer(p)) return true;

	return false;
}

bool NHL_Division::CheckLastName(wxString n, int t)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		if (teams[i].GetTeamID() == t)
		{
			return teams[i].CheckLastName(n);
		}
	}

	return false;
}

void NHL_Division::PurgePlayersWithNoStats()
{
	for (size_t i = 0; i < teams.size(); ++i) teams[i].PurgePlayersWithNoStats();
}

void NHL_Division::CalibrateStats()
{
	for (size_t i = 0; i < teams.size(); ++i) teams[i].CalibrateStats();
}

void NHL_Division::RecalcDivisionStandings()
{
	DivStandings.clear();
	for (size_t i = 0; i < teams.size(); ++i)
	{
		if (!DivStandings.size())
			DivStandings.push_back(&teams[i]);
		else
		{
			bool push = true;
			for (size_t j = 0; j < DivStandings.size(); ++j)
			{
				wxString divname = DivStandings[j]->GetTeamName();
				wxString teamname = teams[i].GetTeamName();
				int divpoints = DivStandings[j]->GetGameRecord()->points;
				int teampoints = teams[i].GetGameRecord()->points;
				int divwins = DivStandings[j]->GetGameRecord()->wins;
				int teamwins = teams[i].GetGameRecord()->wins;
				if (DivStandings[j]->GetGameRecord()->points < teams[i].GetGameRecord()->points)
				{
					push = false;
					DivStandings.insert(&DivStandings[j], &teams[i]);
					break;
				}
				else if (DivStandings[j]->GetGameRecord()->points == teams[i].GetGameRecord()->points && DivStandings[j]->GetGameRecord()->wins < teams[i].GetGameRecord()->wins)
				{
					push = false;
					DivStandings.insert(&DivStandings[j], &teams[i]);
					break;
				}
			}
			if (push)
				DivStandings.push_back(&teams[i]);
		}
	}

	PlayoffTeams.clear();
	for (size_t i = 0; i < DivStandings.size(); ++i)
	{
		if (i > 4) break;
		PlayoffTeams.push_back(DivStandings[i]);
	}
}

NHLTeam* NHL_Division::GetTeam(int id)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		if (teams[i].GetTeamID() == id) return &teams[i];
	}

	return nullptr;
}

NHLTeam* NHL_Division::GetTeam(int t, int d)
{
	if (d == this->division)
		return GetTeam(t);

	return m_parent_conf->GetTeamOpponent(t, d);
}

void NHL_Division::GetTeamLogos(wxVector<wxBitmap*>& v)
{
	for (size_t i = 0; i < teams.size(); ++i)
		v.push_back(teams[i].GetTeamLogo());
}

void NHL_Division::GetTeams(wxVector<NHLTeam*>& T)
{
	for (size_t i = 0; i < teams.size(); ++i)
		T.push_back(&teams[i]);
}

void NHL_Division::GetForwards(wxVector<NHLplayer*>& v)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		wxVector<NHLplayer>& V = teams[i].GetForwards();
		for (size_t i = 0; i < V.size(); ++i)
		{
			size_t j = 0;
			while (j < v.size() && v[j]->GetPlayerOverallRating() >= V[i].GetPlayerOverallRating()) ++j;

			if (j == v.size()) v.push_back(&V[i]);
			else v.insert(&v[j], &V[i]);
		}
	}
}

void NHL_Division::GetDefensmen(wxVector<NHLplayer*>& v)
{
	
	for (size_t i = 0; i < teams.size(); ++i)
	{
		wxVector<NHLplayer>& V = teams[i].GetDefensemen();
		for (size_t i = 0; i < V.size(); ++i)
		{
			size_t j = 0;
			while (j < v.size() && v[j]->GetGameScore() >= V[i].GetGameScore()) ++j;

			if (j == v.size()) v.push_back(&V[i]);
			else v.insert(&v[j], &V[i]);
		}
	}
}

void NHL_Division::GetGoalies(wxVector<NHLplayer*>& v)
{
	for (size_t i = 0; i < teams.size(); ++i)
	{
		wxVector<NHLplayer>& V = teams[i].GetGoalies();
		for (size_t i = 0; i < V.size(); ++i)
		{
			size_t j = 0;
			while (j < v.size() && v[j]->GetPlayerOverallRating() >= V[i].GetPlayerOverallRating()) ++j;

			if (j == v.size()) v.push_back(&V[i]);
			else v.insert(&v[j], &V[i]);
		}
	}
}

bool NHL_Conference::AddLine(stringlines& s, int d, int t)
{
	if (div1.GetDivId() == d)
	{
		return div1.AddLine(s, t);
	}

	if (div2.GetDivId() == d)
	{
		return div2.AddLine(s, t);
	}

	return false;
}

void NHL_Conference::Save()
{
	wxString filename = SavedFile + conf_name + ".txt";
	wxTempFileOutputStream o(filename);
	if (!o.IsOk())
	{
		wxMessageBox("Could not open file: " + filename + " in NHL_Division::Save!");
		return;
	}

	wxTextOutputStream out(o);
	out << conf_name << '\n';
	out << div1.GetDivName() << '\n';
	out << div2.GetDivName() << '\n';

	div1.Save();
	div2.Save();

	o.Commit();
}

void NHL_Conference::Retrieve()
{
	wxFile file;
	wxString filename = SavedFile + conf_name + ".txt";
	if (!file.Exists(filename))
	{
		wxMessageBox(filename + " does not exist in NHL_Conference::Retrieve!");
		return;
	}
	if (!file.Open(filename, wxFile::read))
	{
		wxMessageBox("Could not open file: " + filename + " in NHL_Conference::Retrieve!");
		return;
	}
	wxFileInputStream o(file);
	wxTextInputStream in(o);

	wxString divone = "";
	wxString divtwo = "";
	wxString temp = "";
	in >> conf_name;
	in >> temp;
	divone = SavedFile + temp + ".txt";
	temp = "";
	in >> temp;
	divtwo = SavedFile + temp + ".txt";
	div1.Retrieve(divone);
	div2.Retrieve(divtwo);
}

void NHL_Conference::SortLines()
{
	div1.SortLines();
	div2.SortLines();
}

bool NHL_Conference::CheckLastName(wxString n, int d, int t)
{
	if (div1.GetDivId() == d)
		return div1.CheckLastName(n, t);
	if (div2.GetDivId() == d)
		return div2.CheckLastName(n, t);

	wxMessageBox("No match in NHL_Conference::CheckLastName!!");
	return false;
}

bool NHL_Conference::AddStats(Stats& S, int t)
{
	if (div1.AddStats(S, t)) return true;

	return div2.AddStats(S, t);
}

void NHL_Conference::SetLogo(wxBitmap& b, int d, int t)
{
	if (div1.GetDivId() == d)
	{
		div1.SetLogo(b, t);
		return;
	}
	if (div2.GetDivId() == d)
	{
		div2.SetLogo(b, t);
		return;
	}
}

void NHL_Conference::PurgePlayersWithNoStats()
{
	div1.PurgePlayersWithNoStats();
	div2.PurgePlayersWithNoStats();
}

void NHL_Conference::CalibrateStats()
{
	div1.CalibrateStats();
	div2.CalibrateStats();
}

void NHL_Conference::GetTeams(wxVector<NHLTeam*>& v)
{
	div1.GetTeams(v);
	div2.GetTeams(v);
}

void NHL_Conference::RecalcStandings()
{
	div1.RecalcDivisionStandings();
	div2.RecalcDivisionStandings();
}

NHLTeam* NHL_Conference::GetTeam(int id, int d)
{
	if (div1.GetDivId() == d)
		return div1.GetTeam(id);
	if (div2.GetDivId() == d)
		return div2.GetTeam(id);

	return nullptr;
}

PlayoffSeeds* NHL_Conference::GetPlayoffTeams()
{
//	PlayoffSeedsEastern* pair;
	wxVector<NHLTeam*> d1 = div1.GetPlayoffTeams();
	wxVector<NHLTeam*> d2 = div2.GetPlayoffTeams();

	wxVector<NHLTeam*> temp;
	temp.push_back(d1[3]);
	temp.push_back(d1[4]);
	temp.push_back(d2[3]);
	temp.push_back(d2[4]);

	wxVector<NHLTeam*> wildcard;
	for (size_t i = 0; i < temp.size(); ++i)
	{
		if (!wildcard.size())
			wildcard.push_back(temp[i]);
		else
		{
			bool push = true;
			for (size_t j = 0; j < wildcard.size(); ++j)
			{
				wxString divname = wildcard[j]->GetTeamName();
				wxString teamname = temp[i]->GetTeamName();
				int divpoints = wildcard[j]->GetGameRecord()->points;
				int teampoints = temp[i]->GetGameRecord()->points;
				int divwins = wildcard[j]->GetGameRecord()->wins;
				int teamwins = temp[i]->GetGameRecord()->wins;
				if (wildcard[j]->GetGameRecord()->points < temp[i]->GetGameRecord()->points)
				{
					push = false;
					wildcard.insert(&wildcard[j], temp[i]);
					break;
				}
				else if (wildcard[j]->GetGameRecord()->wins < temp[i]->GetGameRecord()->wins)
				{
					push = false;
					wildcard.insert(&wildcard[j], temp[i]);
					break;
				}
			}
			if (push)
				wildcard.push_back(temp[i]);
		}
	}

	
	if (conference == Conf::Western)
	{
		wxVector<NHLTeam*> pacific = div1.GetDivId() == Div::Pacific ? d1 : d2;
		wxVector<NHLTeam*> central = div1.GetDivId() == Div::Central ? d1 : d2;
		playoff_western = new PlayoffSeedsWestern(pacific[0], pacific[1], pacific[2], central[0], central[1], central[2], wildcard[0], wildcard[1]);
		return playoff_western;
	}
	else
	{
		wxVector<NHLTeam*> atlantic = div1.GetDivId() == Div::Atlantic ? d1 : d2;
		wxVector<NHLTeam*> metropolitan = div1.GetDivId() == Div::Metropolitan ? d1 : d2;
		playoff_eastern = new PlayoffSeedsEastern(atlantic[0], atlantic[1], atlantic[2], metropolitan[0], metropolitan[1], metropolitan[2], wildcard[0], wildcard[1]);
		return playoff_eastern;
	}
}

wxVector<NHLTeam*> NHL_Conference::GetDivStandings(Div d)
{
	if (this->conference == Conf::Western)
	{
		if (d == Div::Central)
		{
			if (div1.GetDivId() == Div::Central)
				return div1.GetDivisionStandings();
			else 
				return div2.GetDivisionStandings();
		}
		else
		{
			if (div1.GetDivId() == Div::Pacific)
				return div1.GetDivisionStandings();
			else
				return div2.GetDivisionStandings();
		}
	}
	else
	{
		if (d == Div::Metropolitan)
		{
			if (div1.GetDivId() == Div::Metropolitan)
				return div1.GetDivisionStandings();
			else
				return div2.GetDivisionStandings();
		}
		else
		{
			if (div1.GetDivId() == Div::Atlantic)
				return div1.GetDivisionStandings();
			else
				return div2.GetDivisionStandings();
		}
	}
}

NHLTeam* NHL_Conference::GetTeamOpponent(int t, int d)
{
	NHLTeam* T = GetTeam(t, d);
	if (T)
		return T;
	else
		return other_Conference->GetTeam(t, d);
}

void NHL_Conference::GetTeamLogos(wxVector<wxBitmap*>& v)
{
	div1.GetTeamLogos(v);
	div2.GetTeamLogos(v);
}

wxString PullData(wxString& s, int& index)
{
	int i = s.find(',', index);
	if (i != -1)
	{
		wxString data = s.Mid(index, i - index);
		index = i + 1;
		return data;
	}

	return "notfound";

	if (index >= s.size()) return "EOF";

	wxString data = "";
	do {
		data += s[index++];
	} while (s.size() > index && s[index] != ',' && s[index] != '\n');

	++index;
	return data;
}

void Waste(wxString& s, int& index)
{
	int i = s.find('\n', index);
	if (i != -1)
	{
		index = i + 1;
		return;
	}

	return;

	if (index >= s.size()) return;

	do {
		if (s[index] == '\n') return;
		++index;
	} while (s.size() > index && s[index] != '\n');

	++index;
	return;
}

NHL_League::NHL_League(void (*SeasonGameReady)(wxWindow*, NHLTeam*, NHLTeam*, int, int), wxWindow* v) : Eastern(Conf::Eastern, Div::Atlantic, Div::Metropolitan, &Western), 
	Western(Conf::Western, Div::Central, Div::Pacific, &Eastern), callback(SeasonGameReady), V(v)
{

}

void NHL_League::ParseSkaters(wxString& s, wxString& start, wxString& year)
{
	
	int begin = s.find(start);
	if (begin == -1)
	{
		wxMessageBox("could not find: " + start + " in NHL::League::ParseSkaters!!");
		return;
	}

	int counter = 0;
	NHLplayer player;
	while (begin < s.size())
	{
		wxString data = PullData(s, begin);
		switch (counter)
		{
		case 0: 
		{
			long l = 0;
			if (!data.ToLong(&l))
			{
				wxMessageBox("Tolong Failed in case 0: in NHL_League::ParseSkaters!!!");
				return;
			}
			player.AddID(l);
			break;
		}
		case 1:
		{
			player.AddYear(data);
			break;
		}
		case 2:
		{
			player.AddName(data);
			break;
		}
		case  3:
		{
			player.AddTeam(data);
			break;
		}
		case 4:
		{
			player.AddPosition(data);
			break;
		}
		case 5:
		{
			int find = s.find("all", begin);
			if (find == -1)
			{
				wxMessageBox("couldnt find the keyword all in NHL_League::ParseSkaters()");
				return;
			}
			begin = find + 4;
			break;
		}
		case 6:
		{
			long l = 0;
			if (!data.ToLong(&l))
			{
				wxMessageBox("Tolong Failed in case 6: in NHL_League::ParseSkaters!!!");
				return;
			}
			int n = l;
			player.AddGamesPlayed(n);
		}
		}
	}
}

void NHL_League::AddPlayerBio(wxString& s)
{
	int filesize = s.size();
	wxString start = "primaryPosition";
	int begin = s.find(start);
	if (begin == -1)
	{
		wxMessageBox("Could not find keyword: primaryPosition in NHL_League::AddPlayerBio()");
		return;
	}

	int counter = -1;
	long id = 0;
	long playernumber = 0;
	wxString playername = "";
	wxString position = "";
	wxString team = "";
	wxDateTime birthday;
	double weight = 0;
	wxString hieght = "";
	wxString nationality = "";
	wxString shot = "";
	begin += start.size() + 1;
	int playercount = 0;
	wxString message = "";
	while (begin < s.size())
	{
		wxString data = PullData(s, begin);
		if (data == "EOF")
		{
			wxMessageBox("The end of the file has been reached!");
			return;
		}
		++counter;
		playercount;
		switch (counter)
		{
		case 0: 
		{
			if (!data.ToLong(&id))
			{
				//wxMessageBox("tolong failed in NHL_League::AddPlayerBio()!!! id is: " + data);
				//wxMessageBox(s.Mid(begin - (data.size() + 10), begin + 20));
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 1: 
		{
			playername = data;
			break;
		}
		case 2:
		{
			position = data;
			break;
		}
		case 3:
		{
			if (data == "ATL")
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			team = data;
			break;
		}
		case 4: 
		{
			if (!birthday.ParseDate(data))
			{
				//wxMessageBox("date could not be parsed in NHL_League::GetPlayerBio. Date is: " + data);
				//wxMessageBox(s.Mid(begin - (data.size() + 10), begin + 20));
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 5:
		{
			double l = 0;
			if (!data.ToDouble(&l))
			{
				//wxMessageBox("to long failed in case 5: in NHL_League::GetPlayerBio()!!!! data is: " + data);
				//wxMessageBox(s.Mid(begin - (data.size() + 10), begin + 20));
				Waste(s, begin);
				counter = -1;
				break;
			}
			weight = l;
			break;
		}
		case 6:
		{
			hieght = data;
			break;
		}
		case 7: 
		{
			nationality = data;
			break;
		}
		case 8:
		{
			shot = data;
			break;
		}
		case 9:
		{
			if (!data.ToLong(&playernumber))
			{
				//wxMessageBox("tolong failed in NHL_League::AddPlayerBio()!!! id is: " + data);
				//wxMessageBox(s.Mid(begin - (data.size() + 10), begin + 20));
				Waste(s, begin);
				counter = -1;
				break;
			}

			break;
		}
		case 10:
		{
			counter = -1;
			char p = ' ';
			char sh = ' ';
			int pn = 0;
			if (position.size()) p = position[0];
			if (shot.size()) sh = shot[0];
			pn = playernumber;
			NHLplayer player(id, playername, p, team, birthday, weight, hieght, nationality, sh, pn);
			AddPlayerToTeam(player);
			++playercount;
			wxString holder = "";
			holder << id;
			message += holder + ' ' + playername + ' ' + p + ' ' + team + ' ' + hieght + ' ' + nationality + ' ' + sh + '\n';
			break;
		}
		}
	}

	wxMessageBox(message);
}

void NHL_League::AddLines(wxString& s)
{
	wxString word = "scoreFlurryAdjustedTotalShotCreditAgainst";
	int begin = s.find(word);
	if (begin == -1)
	{
		wxMessageBox("Could not find begining token word in NHL_League::AddLines!!");
		return;
	}
	begin += word.size() + 1;

	int idgen = 1;
	int counter = -1;
	int teamid = -1;
	wxString id = "";
	double idline = 0;
	wxString lines = "";
	wxVector<wxString> linenames;
	wxString team = "";
	wxString srank = "";
	wxString linetype = "";
	double rank = 0;
	while (begin < s.size())
	{
		++counter;
		switch (counter)
		{
		case 0:
		{
			id = PullData(s, begin);
			if (!id.ToDouble(&idline))
			{
			//	wxMessageBox("to long failed in case 0 in NHL_league::AddLines!!. data is: " + id);
				Waste(s, begin);
				counter = -1;
			}
			break;
		}
		case 1: PullData(s, begin); break;
		case 2:
		{
			lines = PullData(s, begin);
			break;
		}
		case 3:
		{
			team = PullData(s, begin);
			teamid = teamnames.GetShortNameID(team);
			wxString tempname = "";
			wxString barr = "Barr", boulet = "Boulet";
			wxString n = "Barre Boulet";
			linenames.clear();
			for (size_t i = 0; i < lines.size(); ++i)
			{
				if (lines[i] != '-')
				{
					tempname += lines[i];
					if (lines.size() - i == 1)
						linenames.push_back(tempname);
				}
				else {
					linenames.push_back(tempname);
					tempname = "";
				}
			}
			if (linenames.size() == 4)
			{
				if (lines.find(barr) != -1 && lines.find(boulet) != -1)
				{
					for (size_t i = 0; i < linenames.size(); ++i)
					{
						if (linenames[i].find(barr) != -1) linenames[i] = barr + 'e';
						if (linenames[i].find(boulet) != -1) linenames[i] = boulet;
					}
				}
				for (size_t i = 1; i < linenames.size(); ++i)
				{
					if (Hyphenated(linenames[i - 1] + "-" + linenames[i], teamid))
					{
						wxString newname = linenames[i - 1] + "-" + linenames[i];
						switch (i)
						{
						case 1:
						{
							linenames.erase(linenames.begin());
							linenames.erase(linenames.begin());
							linenames.insert(linenames.begin(), newname);
							break;
						}
						case 2:
						{
							linenames.erase(linenames.begin() + 1);
							linenames.erase(linenames.begin() + 1);
							linenames.insert(linenames.begin() + 1, newname);
							break;
						}
						case 3:
						{
							linenames.erase(linenames.begin() + 2);
							linenames.erase(linenames.begin() + 2);
							linenames.push_back(newname);
							break;
						}
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			linetype = PullData(s, begin);
			if ((linetype == "pair" || linetype == "pairing") && linenames.size() == 3)
				CheckForHyphen(linenames, teamid);
			break;
		}
		case 5:
		case 6:
		case 7:
		{
			PullData(s, begin);
			break;
		}
		case 8:
		{
			counter = -1;
			srank = PullData(s, begin);
			if (!srank.ToDouble(&rank))
			{
			//	wxMessageBox("to long failed in case 8 in NHL_league::AddLines!!. data is: " + srank);
				Waste(s, begin);
				break;
			}
			int ic = rank;
			if (linenames.size() == 2)
			{
				stringlines S(idgen, linetype, ic, team, linenames[0], linenames[1]);
				AddLine(S, teamid);
				++idgen;
			}
			else if (linenames.size() == 3)
			{
				stringlines S(idgen, linetype, ic, team, linenames[0], linenames[1], linenames[2]);
				AddLine(S, teamid);
				++idgen;
			}
			else
			{
			//	wxMessageBox("linenames does not have two or three items in it in NHL_League::AddLines!!!! Line is: " + lines);
			}
			Waste(s, begin);
		}
		}
	}
	SortLines();
	/*
	NHLTeam* hometeam = nullptr;
	for (size_t i = 0; i < Teams.size(); ++i)
	{
		if (Teams[i]->GetTeamID() == 8)
		{
			hometeam = Teams[i];
			break;
		}
	}
	Gen gen;
	wxVector<NHLTeam*> T;
	Ctr->GetTeams(T);
	for (size_t i = 0; i < 6; ++i)
	{
		for (size_t j = 0; j < T.size(); ++j)
		{
			if (T[j]->GetTeamID() != hometeam->GetTeamID())
			{
				if (!(i % 2))
					game.NewGame(T[j], hometeam);
				else
					game.NewGame(hometeam, T[j]);
			}
		}
	}*/
	/*
	for (size_t i = 0; i < 100; ++i)
	{
		int team1 = Pull(gen, 0, 31);
		int team2 = Pull(gen, 0, 31);
		for (size_t i = 0; i < Teams.size(); ++i)
		{
			if (Teams[i]->GetTeamID() == 21) team1 = i;
			if (Teams[i]->GetTeamID() == 8) team2 = i;
		}
		for (size_t i = 0; i < Teams.size(); ++i)
		{
			if (!(i % 2))
			{
				if (Teams[i]->GetTeamID() != 8)
					game.NewGame(Teams[team2], Teams[team1]);
			}
			else
			{
				if (Teams[i]->GetTeamID() != 8)
					game.NewGame(Teams[team1], Teams[team2]);
			}
		}
		game.NewGame(Teams[team1], Teams[team2]);
	}
	*/
}

void NHL_League::AddStats(wxString& s)
{
	wxString word = "fenwickAgainstAfterShifts";
	int begin = s.find(word);
	if (begin == -1)
	{
		wxMessageBox("Could not find begining token word in NHL_League::AddStats!!");
		return;
	}
	begin += word.size() + 1;

	Stats S;
	int counter = -1;
	int te = -1;
	char position = ' ';
	while (begin < s.size())
	{
		++counter;
		switch (counter)
		{
		case 0:
		{
			wxString data = PullData(s, begin);
			if (!data.ToLong(&S.id))
			{
			//	wxMessageBox("Case 0: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 1:
		{
			wxString data = PullData(s, begin);
			long l = 0;
			if (!data.ToLong(&l))
			{
			//	wxMessageBox("Case 1: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.year = data;
			S.season = int(l);
			break;
		}
		case 2:
		{
			S.name = PullData(s, begin);
			break;
		}
		case 3:
		{
			wxString t = PullData(s, begin);
			te = teamnames.GetShortNameID(t);
			if (te == -1)
			{
			//	wxMessageBox("Case 3: tolong failed in NHL_League::AddStats!! data is: " + t);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.team = t;
			break;
		}
		case 4:
		{
			
			wxString c = PullData(s, begin);
			if(c.size() != 1)
			{
				//	wxMessageBox("Case 3: tolong failed in NHL_League::AddStats!! data is: " + t);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.Pos = c[0];
			break;
		}
		case 5:
		{
			wxString five = "all";
			wxString data = PullData(s, begin);
			if (data != five)
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 6:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 6: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.games_played = (int)d;
			break;
		}
		case 9:
		{
			
			wxString data = PullData(s, begin);
			if (!data.ToDouble(&S.gameScore))
			{
			//	wxMessageBox("Case 9: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 12:
		{
			wxString data = PullData(s, begin);
			if (!data.ToDouble(&S.onIce_corsiPercentage))
			{
			//	wxMessageBox("Case 12: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 14:
		{
			wxString data = PullData(s, begin);
			if (!data.ToDouble(&S.onIce_fenwickPercentage))
			{
			//	wxMessageBox("Case 14: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 27:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 27: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_primaryAssists = (int)d;
			break;
		}
		case 28:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 28: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_secondaryAssists = (int)d;
			break;
		}
		case 29:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 29: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_shotsOnGoal = (int)d;
			break;
		}
		case 30:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 30: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_missedShots = (int)d;
			break;
		}
		case 31:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 31: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_blockedShotAttempts = (int)d;
			break;
		}
		case 32:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 32: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_shotAttempts = (int)d;
			break;
		}
		case 33:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 33: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_points = (int)d;
			break;
		}
		case 34:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 34: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_goals = (int)d;
			break;
		}
		case 35:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 35: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_rebounds = (int)d;
			break;
		}
		case 36:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 36: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_reboundGoals = (int)d;
			break;
		}
		case 46:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 46: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_hits = (int)d;
			break;
		}
		case 47:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 47: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_takeaways = (int)d;
			break;
		}
		case 48:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 48: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.I_F_giveaways = (int)d;
			break;
		}
		case 77:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 77: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.faceoffsWon = (int)d;
			break;
		}
		case 78:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 78: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.faceoffsLost = (int)d;
			break;
		}
		case 82:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 82: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.penaltiesDrawn = (int)d;
			break;
		}
		case 83:
		{
			wxString data = PullData(s, begin);
			double d = 0;
			if (!data.ToDouble(&d))
			{
			//	wxMessageBox("Case 9: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.blockedshots = (int)d;
			break;
		}
		case 92:
		{
			wxString data = PullData(s, begin);
			if (!data.ToDouble(&S.OnIce_F_ShotAttempts))
			{
			//	wxMessageBox("Case 92: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 93:
		{
			wxString data = PullData(s, begin);
			if (!data.ToDouble(&S.OnIce_F_Goals))
			{
			//	wxMessageBox("Case 93: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 123:
		{
			wxString data = PullData(s, begin);
			if (!data.ToDouble(&S.OnIce_A_goals))
			{
			//	wxMessageBox("Case 123: tolong failed in NHL_League::AddStats!! data is: " + data);
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 153:
		{
			PullData(s, begin);
			counter = -1;
			AddPlayerStats(S, te);
			break;
		}
		default:
		{
			PullData(s, begin);
			break;
		}
		}
	}
}

void NHL_League::AddGoalieStats(wxString& s)
{
	wxString word = "penalties";
	int begin = s.find(word);
	if (begin == -1)
	{
		wxMessageBox("Could not find begining token word in NHL_League::AddStats!!");
		return;
	}
	begin += word.size() + 1;

	Stats S;
	int counter = -1;
	
	int iD = -1;
	while (begin < s.size())
	{
		++counter;
		wxString data = PullData(s, begin);
		switch (counter)
		{
		case 0:
		{
			long l = 0;
			if (!data.ToLong(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.id = l;
			break;
		}
		case 1:
		{
			long l = 0;
			if (!data.ToLong(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.season = l;
			S.year = data;
			break;
		}
		case 2:
		{
			S.name = data;
			break;
		}
		case 3:
		{
			iD = teamnames.GetShortNameID(data);
			teamnames.GetDivID(data);
			if (iD == -1)
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.team = data;
			break;
		}
		case 4:
		{
			S.Pos = data.size() ? data[0] : 'U';
			if (S.Pos != Position::G)
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 5:
		{
			if (data != "all")
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			break;
		}
		case 6:
		{
			long l = 0;
			if (!data.ToLong(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			else if (l < 25)
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.games_played = int(l);
			break;
		}
		case 9:
		{
			double l = 0;
			if (!data.ToDouble(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.goals_allowed = l;
			break;
		}
		case 12:
		{
			double l = 0;
			if (!data.ToDouble(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.rebounds = l;
			break;
		}
		case 14:
		{
			double l = 0;
			if (!data.ToDouble(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.freeze = l;
			break;
		}
		case 16:
		{
			double l = 0;
			if (!data.ToDouble(&l))
			{
				Waste(s, begin);
				counter = -1;
				break;
			}
			S.ongoalshots = l;
			AddPlayerStats(S, iD);
			Waste(s, begin);
			counter = -1;
			break;
		}
		}
	}
}

void NHL_League::CheckForHyphen(wxVector<wxString>& linenames, int t)
{
	for (size_t i = 1; i < linenames.size(); ++i)
	{
		if (Hyphenated(linenames[i - 1] + "-" + linenames[i], t))
		{
			wxString newname = linenames[i - 1] + "-" + linenames[i];
			switch (i)
			{
			case 1:
			{
				linenames.erase(linenames.begin());
				linenames.erase(linenames.begin());
				linenames.insert(linenames.begin(), newname);
				break;
			}
			case 2:
			{
				linenames.erase(linenames.begin() + 1);
				linenames.erase(linenames.begin() + 1);
				linenames.insert(linenames.begin() + 1, newname);
				break;
			}
			}
		}
	}
}

void NHL_League::Save()
{
	Eastern.Save();
	Western.Save();
}

void NHL_League::Retrieve()
{
	Eastern.Retrieve();
	Western.Retrieve();
}

void NHL_League::SortLines()
{
	Eastern.SortLines();
	Western.SortLines();
}

bool NHL_League::Hyphenated(wxString n, int t)
{
	int d = teamnames.GetDivisionIdByTeamId(t);
	int c = teamnames.GetConferenceIdByDivisionId(d);
	if (c == Conf::Eastern)
		return Eastern.CheckLastName(n, d, t);
	if (c == Conf::Western)
		return Western.CheckLastName(n, d, t);
	
	wxMessageBox("No match in NHL_League::Hyphenated!");
	return false;
}

void NHL_League::PurgePlayersWithNoStats()
{
	Eastern.PurgePlayersWithNoStats();
	Western.PurgePlayersWithNoStats();
	CalibrateStats();
	CollectPlayers();
//	CalibrateRatings();
}

void NHL_League::CollectPlayers()
{
	AddPlayerVectors(Eastern.GetDiv1());
	AddPlayerVectors(Eastern.GetDiv2());
	AddPlayerVectors(Western.GetDiv1());
	AddPlayerVectors(Western.GetDiv2());

	for (size_t i = 0; i < forwards.size(); ++i)
		allskaters.push_back(forwards[i]);
	for (size_t i = 0; i < defensemen.size(); ++i)
		allskaters.push_back(defensemen[i]);

	Eastern.GetTeams(Teams);
	Western.GetTeams(Teams);

	for (size_t i = 0; i < Teams.size(); ++i)
		logo.push_back(Teams[i]->GetTeamLogo());
}

void NHL_League:: AddPlayerVectors(NHL_Division* d)
{
	switch (d->GetDivId())
	{
	case Div::Atlantic:
	{
		Atl = d;
		break;
	}
	case Div::Metropolitan:
	{
		Mtp = d;
		break;
	}
	case Div::Central:
	{
		Ctr = d;
		break;
	}
	case Div::Pacific: Pcf = d;
	}
	d->GetDefensmen(defensemen);
	d->GetForwards(forwards);
	d->GetGoalies(goalies);
}

void NHL_League::CalibrateRatings()
{
	double overall = 0.0;
	double rating = 0.0;
	double offrating = 0.0;
	double defrating = 0.0;
	double gamescore = 0.0;
	for (size_t i = 0; i < allskaters.size(); ++i)
	{
		NHLplayer* p = allskaters[i];
		Stats* S = p->GetLastSeasonStats();
		if (i == 0) overall = allskaters[i]->GetPlayerOverallRating();
		gamescore = allskaters[i]->GetGameScore();
		rating = allskaters[i]->GetPlayerOverallRating();
		double deftemp = allskaters[i]->GetDefenseRating();
		if (deftemp > defrating) defrating = deftemp;
		double tempoffrating = allskaters[i]->GetOffenseRating();
		if (tempoffrating > offrating) offrating = tempoffrating;
	}
}

void NHL_League::CalibrateStats()
{
	Eastern.CalibrateStats();
	Western.CalibrateStats();
}

void NHL_League::SetLogo(wxBitmap& b, int t)
{
	int d = teamnames.GetDivisionIdByTeamId(t);
	int c = teamnames.GetConferenceIdByDivisionId(d);

	if (c == Conf::Eastern)
		Eastern.SetLogo(b, d, t);
	if (c == Conf::Western)
		Western.SetLogo(b, d, t);
}

void NHL_League::StartGame(void (*func)(GameWindow, int, void*, GameRecord*, wxString), void* v, NHLTeam* a, NHLTeam* h)
{
	game.NewGame(func, v, a, h);
}

void NHL_League::StartPlayoffGame(void (*func)(GameWindow, int, void*, GameRecord*, wxString), void* v, NHLTeam* a, NHLTeam* h)
{
	game.NewPlayoffGame(func, v, a, h);
}

void NHL_League::EndGame()
{
	game.EndGame();
}

bool NHL_League::IsQuarterWayThroughSeason()
{
	int g = myseason_team->GetGamesPlayed();
	/*
	if (g == 5)
	{
		Eastern.RecalcStandings();
		Western.RecalcStandings();
		return true;
	}
	*/
	if (g == 20 || g == 40 || g == 60 || g == 82)
	{
		Eastern.RecalcStandings();
		Western.RecalcStandings();
		return true;
	}

	return false;
}

void NHL_League::StartSeason(NHLTeam* T)
{
	schedule = 0;
	myseason_team = T;
	sc.clear();

	GetNextSchedule();
	RunSeason();
}

bool NHL_League::ContinueSeason()
{
	while (schedule < 82)
	{
		if (!sc.size())
			GetNextSchedule();

		if (!sc.size()) 
			break;

		if (RunSeason())
		{
			return true;
		}
	}

	if (!playoff_eastern && !playoff_western)
	{
		//regular season over...
		Eastern.RecalcStandings();
		Western.RecalcStandings();
		playoff_eastern = (PlayoffSeedsEastern*)Eastern.GetPlayoffTeams();
		playoff_western = (PlayoffSeedsWestern*)Western.GetPlayoffTeams();
		wxPostEvent(V, wxCommandEvent(PlayoffStartEvent, 0));
		wxPostEvent(V, wxCommandEvent(RegularSeasonOver, 0));
		return true;
	}

	if (!gameOnScreen)
		RunPlayoffs();

	return true;
}

void NHL_League::SetMyPlayoffSeriesOutCome(NHLTeam* winner, NHLTeam* loser)
{
	gameOnScreen = false;
	wxCommandEvent* evt = nullptr;
	switch (playoffround)
	{
	case 1: evt = new wxCommandEvent(FirstRoundOver, 0); break;
	case 2: evt = new wxCommandEvent(SecondRoundOver, 0); break;
	case 3: evt = new wxCommandEvent(ThirdRoundOver, 0); break;
	}

	if (myplayoffconference)
	{
		myplayoffconference->AddOutcome(winner, loser, playoffround);
		myplayoffconference = nullptr;
		myplayoffseries = nullptr;
	}

	if (!evt)
	{
		//season is over...
		return;
	}

	if (playoffround == 3)
	{
		//stanley cup
		if (!western_champs) western_champs = winner;
		else eastern_champs = winner;

		wxPostEvent(V, *evt);
		return;
	}

	wxPostEvent(V, *evt);
	/*
	if (playoffround < 3)
	{
		if (myplayoffconference)
		{
			myplayoffconference->AddOutcome(winner, loser, playoffround);
			myplayoffconference = nullptr;
		}
		if (loser == myseason_team)
		{
			//myseason_team is out of the playoffs...
		}
		if (playoffround == 1)
			wxPostEvent(V, wxCommandEvent(FirstRoundOver, 0));
		else 
			wxPostEvent(V, wxCommandEvent(SecondRoundOver, 0));
	}
	else if (playoffround == 3)
	{
		//stanley cup
		if (!western_champs) western_champs = winner;
		else eastern_champs = winner;

		wxPostEvent(V, wxCommandEvent(ThirdRoundOver, 0));
	}
	else
	{
		//season over

	}
	*/
}

void NHL_League::RunPlayoffs()
{
	++playoffround;
	PlayoffSeeds* playoffseeds = nullptr;
	if (playoffround == 1 || playoffround == 2)
	{
		//first and second round of playoffs...
		size_t limit = playoffround > 1 ? 1 : 2;
		for (size_t i = 0; i < limit; ++i)
		{
			PlayoffSeries* ps = nullptr;
			for (size_t series = 0; series < 4; ++series)
			{
				switch (series)
				{
				case Div::Atlantic: ps = playoff_eastern->GetAtlanticSeries(i, playoffround); playoffseeds = playoff_eastern; break;
				case Div::Metropolitan: ps = playoff_eastern->GetMetropolitanSeries(i, playoffround); playoffseeds = playoff_eastern; break;
				case Div::Pacific: ps = playoff_western->GetPacificSeries(i, playoffround); playoffseeds = playoff_western; break;
				case Div::Central: ps = playoff_western->GetCentralSeries(i, playoffround); playoffseeds = playoff_western; break;
				}
				if (!ps->away || !ps->home)
					continue;
				if (ps->GetAwayTeam() == myseason_team || ps->GetHomeTeam() == myseason_team)
				{
					myplayoffconference = ps->GetParent();
					myplayoffseries = ps;
					continue;
				}
				NHLTeam* winner = RunPlayoffSeries(ps);
				NHLTeam* loser = winner == ps->away ? ps->home : ps->away;
				playoffseeds->AddOutcome(winner, loser, playoffround);
			}
		}
	}
	else if (playoffround == 3)
	{
		PlayoffSeries* eastern_finals = playoff_eastern->GetThirdRound();
		PlayoffSeries* western_finals = playoff_western->GetThirdRound();
		if (eastern_finals->away == myseason_team || eastern_finals->home == myseason_team)
		{
			myplayoffconference = playoff_eastern;
			myplayoffseries = eastern_finals;
		}
		else if (western_finals->away == myseason_team || western_finals->home == myseason_team)
		{
			myplayoffconference = playoff_western;
			myplayoffseries = western_finals;
		}

		if (!myplayoffseries)
		{
			eastern_champs = RunPlayoffSeries(eastern_finals);
			western_champs = RunPlayoffSeries(western_finals);

			//stanleycup...
			PlayoffSeries stanley_cup(playoffround, nullptr, nullptr, nullptr);
			stanley_cup.AddTeamMovingOn(western_champs);
			stanley_cup.AddTeamMovingOn(eastern_champs);
			gameOnScreen = true;
			callback(V, stanley_cup.away, stanley_cup.home, 7, playoffround);
			return;
		}

		if (myplayoffseries && myplayoffseries != western_finals)
			western_champs = RunPlayoffSeries(western_finals);
		if (myplayoffseries && myplayoffseries != eastern_finals)
			eastern_champs = RunPlayoffSeries(eastern_finals);

		//run my third round series
		gameOnScreen = true;
		callback(V, myplayoffseries->away, myplayoffseries->home, 7, playoffround);
		return;



		//stanleycup...
		PlayoffSeries stanley_cup(playoffround, nullptr, nullptr, nullptr);
		stanley_cup.AddTeamMovingOn(western_champs);
		stanley_cup.AddTeamMovingOn(eastern_champs);
		gameOnScreen = true;
		callback(V, stanley_cup.away, stanley_cup.home, 7, playoffround);
		return;
	}
	else
	{
		//stanleycup...
		PlayoffSeries stanley_cup(playoffround, nullptr, nullptr, nullptr);
		stanley_cup.AddTeamMovingOn(western_champs);
		stanley_cup.AddTeamMovingOn(eastern_champs);
		gameOnScreen = true;
		callback(V, stanley_cup.away, stanley_cup.home, 7, playoffround);
		return;
	}

	if (myplayoffseries)
	{
		gameOnScreen = true;
		callback(V, myplayoffseries->away, myplayoffseries->home, 7, playoffround);
		return;
	}
	RunPlayoffs();
}

NHLTeam* NHL_League::RunPlayoffSeries(PlayoffSeries* ps)
{
	int awayteam = 0;
	int hometeam = 0;

	for (size_t i = 0; i < 7; ++i)
	{
		if (i == 2 || i == 3 || i == 5)
		{
			game.NewPlayoffGame(ps->home, ps->away) == ps->away ? ++awayteam : ++hometeam;
			if (awayteam == 4)
				return ps->away;
			else if (hometeam == 4)
				return ps->home;
		}
		else
		{
			game.NewPlayoffGame(ps->away, ps->home) == ps->away ? awayteam++ : hometeam++;
			if (awayteam == 4)
				return ps->away;
			else if (hometeam == 4)
				return ps->home;
		}
	}
	return nullptr;
}

void NHL_League::GetNextSchedule()
{
	if (schedule >= 82)
		return;

	for (size_t i = 0; i < Teams.size(); ++i)
	{
		Season_Schedule* s = Teams[i]->GetScheduledGame(schedule);
		if (s && s->IsHomeGame())
		{
			if (!sc.size())
				sc.push_back(s);
			else
			{
				if (sc[sc.size() - 1]->GetDate() > s->GetDate())
					sc.insert(&sc[sc.size() - 1], s);
				else
					sc.push_back(s);
			}
		}
	}
	++schedule;
}

bool NHL_League::RunSeason()
{
	for (size_t i = 0; i < sc.size(); ++i)
	{
		if (!sc[i]->IsTeamInGame(myseason_team))
		{
			game.NewGame(sc[i]->GetAwayTeam(), sc[i]->GetHomeTeam());
			sc.erase(&sc[i]);
			--i;
		}
		else
		{
			Eastern.RecalcStandings();
			Western.RecalcStandings();
		//	callback(V, sc[i]->GetAwayTeam(), sc[i]->GetHomeTeam(), 1, 0);
			game.NewGame(sc[i]->GetAwayTeam(), sc[i]->GetHomeTeam());
			sc.erase(&sc[i]);
			--i;
	    // 	return true;
		}
	}
	
	return ContinueSeason();
}

NHLTeam* NHL_League::GetTeam(int id)
{
	int d = teamnames.GetDivisionIdByTeamId(id);
	int c = teamnames.GetConferenceIdByDivisionId(d);
	
	if (c == Conf::Eastern)
		return Eastern.GetTeam(id, d);
	if (c == Conf::Western)
		return Western.GetTeam(id, d);

	return nullptr;
}

wxVector<NHLplayer*>& NHL_League::GetAllSkaters()
{
	return allskaters;
}

wxVector<NHLplayer*>& NHL_League::GetAllForwards()
{
	return forwards;
}

wxVector<NHLplayer*>& NHL_League::GetAllDefensemen()
{
	return defensemen;
}

wxVector<NHLplayer*>& NHL_League::GetAllGoalies()
{
	return goalies;
}

void NHL_League::AddPlayerToTeam(NHLplayer& p)
{
	if (Eastern.AddPlayer(p)) return;

	Western.AddPlayer(p);
}

wxVector<NHLTeam*> NHL_League::GetPacificStandings()
{
	return Western.GetDivStandings(Div::Pacific);
}

wxVector<NHLTeam*> NHL_League::GetCentralStandings()
{
	return Western.GetDivStandings(Div::Central);
}

wxVector<NHLTeam*> NHL_League::GetMetropolitanStandings()
{
	return Eastern.GetDivStandings(Div::Metropolitan);
}

wxVector<NHLTeam*> NHL_League::GetAtlanticStandings()
{
	return Eastern.GetDivStandings(Div::Atlantic);
}

PlayoffSeries* NHL_League::GetPlayoffSeries(PlayoffSeriesPair p)
{
	switch (p)
	{
	case PlayoffSeriesPair::CENTRAL_FIRST: return playoff_western->GetCentralSeries(0, 1);
	case PlayoffSeriesPair::CENTRAL_SECOND: return playoff_western->GetCentralSeries(1, 1);
	case PlayoffSeriesPair::PACIFIC_FIRST: return playoff_western->GetPacificSeries(0, 1);
	case PlayoffSeriesPair::PACIFIC_SECOND: return playoff_western->GetPacificSeries(1, 1);
	case PlayoffSeriesPair::ATLANTIC_FIRST: return playoff_eastern->GetAtlanticSeries(0, 1);
	case PlayoffSeriesPair::ATLANTIC_SECOND: return playoff_eastern->GetAtlanticSeries(1, 1);
	case PlayoffSeriesPair::METROPOLITAN_FIRST: return playoff_eastern->GetMetropolitanSeries(0, 1);
	case PlayoffSeriesPair::METROPOLITAN_SECOND: return playoff_eastern->GetMetropolitanSeries(1, 1);
	case PlayoffSeriesPair::CENTRAL_SECOND_ROUND: return playoff_western->GetCentralSeries(1, 2);
	case PlayoffSeriesPair::PACIFIC_SECOND_ROUND: return playoff_western->GetPacificSeries(2, 2);
	case PlayoffSeriesPair::ATLANTIC_SECOND_ROUND: return playoff_eastern->GetAtlanticSeries(1, 2);
	case PlayoffSeriesPair::METROPOLITAN_SECOND_ROUND: return playoff_eastern->GetMetropolitanSeries(1, 2);
	case PlayoffSeriesPair::WESTERN_THIRD_ROUND: return playoff_western->GetThirdRound();
	case PlayoffSeriesPair::EASTERN_THIRD_ROUND: return playoff_eastern->GetThirdRound();
	}

	wxFAIL_MSG("switch did not catch param in NHL_League::GetPlayoffSeries!");
	return nullptr;
}

void NHL_League::AddLine(stringlines& s, int t)
{
	int d = teamnames.GetDivisionIdByTeamId(t);
	int c = teamnames.GetConferenceIdByDivisionId(d);
	if (c == Conf::Eastern)
	{
		Eastern.AddLine(s, d, t);
		return;
	}

	if (c == Conf::Western)
	{
		Western.AddLine(s, d, t);
		return;
	}
	
	wxMessageBox("Error no match in NHL_League::AddLine()!!");
}

void NHL_League::AddPlayerStats(Stats& S, int t)
{
	int conf = teamnames.GetConferenceIdByDivisionId(teamnames.GetDivisionIdByTeamId(t));
	if (conf == Conf::Eastern)
	{
		Eastern.AddStats(S, t);
		return;
	}

	if (conf == Conf::Western)
	{
		Western.AddStats(S, t);
		return;
	}

	wxMessageBox("c param in NHL_League::AddPlayerStats is not matching!! param is: " + conf);
}

NHLplayer* GetPlayerDefensiveBias(Forwards* f, Defense* d, int player)
{
//	int player = Pull(generator, 1, 9);
	switch (player)
	{
	case 1:
	case 2:
	case 3: return d->d1;
	case 4:
	case 5:
	case 6: return d->d2;
	case 7: return f->left;
	case 8: return f->center;
	case 9: return f->right;
	}

	wxMessageBox("Returning nullptr in Game::GetPlayerDefensiveBias!!!");
	return nullptr;
}

NHLplayer* GetPlayerOffensiveBias(Forwards* f, Defense* d, int player)
{
//	int player = Pull(generator, 1, 8);
	switch (player)
	{
	case 1:
	case 2: return f->left;
	case 3:
	case 4: return f->center;
	case 5:
	case 6: return f->right;
	case 7: return d->d1;
	case 8: return d->d2;
	}

	wxMessageBox("Returning nullptr in Game::GetPlayerOffensiveBias!!!");
	return nullptr;
}

NHLplayer* GetPlayerNeutralBias(Forwards* f, Defense* d, int player)
{
//	int player = Pull(generator, 1, 5);
	switch (player)
	{
	case 1: return f->left;
	case 2: return f->center;
	case 3: return f->right;
	case 4: return d->d1;
	case 5: return d->d2;
	}

	wxMessageBox("Returning nullptr in Game::GetPlayerNeutralBias!!!");
	return nullptr;
}

Game::Game()
{
	
}

void Game::NewGame(NHLTeam* away, NHLTeam* home)
{
	IsGameOnScreen = false;
	isgameinsession = true;
	Away = away;
	Home = home;

	awaylines = Away->GetLines();
	homelines = Home->GetLines();
	awaylines->ResetInGameBockedShots();
	homelines->ResetInGameBockedShots();

	ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);

	homegoalie = homelines->goalie;
	awaygoalie = awaylines->goalie;

	StartGame();

	Reset();
	if (IsGameOnScreen)
	{
		PassToCallBack(GameWindow::AWAY_RECORD, 1, Away->GetGameRecord(), "Away Record");
		PassToCallBack(GameWindow::HOME_RECORD, 1, Home->GetGameRecord(), "Home Record");
		PassToCallBack(GameWindow::GAMEOVER, 1, Home->GetGameRecord(), "Fuck");
	}
	isgameinsession = false;
	Reset();
}

void Game::NewGame(void(*func)(GameWindow, int, void*, GameRecord*, wxString), void* v, NHLTeam* away, NHLTeam* home)
{
	isgameinsession = true;
	IsGameOnScreen = true;
	CallBack = func;
	V = v;

	Away = away;
	Home = home;

	awaylines = Away->GetLines();
	homelines = Home->GetLines();

	awaylines->ResetInGameBockedShots();
	homelines->ResetInGameBockedShots();
	ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);

	homegoalie = homelines->goalie;
	awaygoalie = awaylines->goalie;

	StartGame();
	if (endgame)
	{
		Reset();
		return;
	}
	wxString homepoints = "";
	wxString awaypoints = "";
	homepoints << homegoals;
	awaypoints << awaygoals;
	wxString as = "";
	wxString hs = "";
	wxString ag = "";
	wxString hg = "";
	as << awayshots;
	hs << homeshots;
	ag << awaygoals;
	hg << homegoals;

	if (IsGameOnScreen)
	{
		wxString home = "";
		wxString away = "";
		home << homegoals;
		away << awaygoals;

		PassToCallBack(GameWindow::AWAY_RECORD, 1, Away->GetGameRecord(), "Away Record");
		PassToCallBack(GameWindow::HOME_RECORD, 1, Home->GetGameRecord(), "Home Record");

		wxString message = awaygoals > homegoals ? Away->GetTeamabbr() + " won against " + Home->GetTeamabbr() + " " + away + " to " + home : 
			Home->GetTeamabbr() + " won against " + Away->GetTeamabbr() + " " + home + " to " + away;
		PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, message);
		PassToCallBack(GameWindow::GAMEOVER, 1, Home->GetGameRecord(), "Fuck");
	}
	isgameinsession = false;
	Reset();
}

void Game::NewPlayoffGame(void(*func)(GameWindow, int, void*, GameRecord*, wxString), void* v, NHLTeam* away, NHLTeam* home)
{
	playoffs = true;
	isgameinsession = true;
	IsGameOnScreen = true;
	CallBack = func;
	V = v;

	Away = away;
	Home = home;

	awaylines = Away->GetLines();
	homelines = Home->GetLines();

	awaylines->ResetInGameBockedShots();
	homelines->ResetInGameBockedShots();
	ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);

	homegoalie = homelines->goalie;
	awaygoalie = awaylines->goalie;

	StartGame();
	if (endgame)
	{
		Reset();
		return;
	}
	wxString homepoints = "";
	wxString awaypoints = "";
	homepoints << homegoals;
	awaypoints << awaygoals;
	wxString as = "";
	wxString hs = "";
	wxString ag = "";
	wxString hg = "";
	as << awayshots;
	hs << homeshots;
	ag << awaygoals;
	hg << homegoals;

	if (IsGameOnScreen)
	{
		wxString home = "";
		wxString away = "";
		home << homegoals;
		away << awaygoals;

		PassToCallBack(GameWindow::AWAY_RECORD, 1, Away->GetGameRecord(), "Away Record");
		PassToCallBack(GameWindow::HOME_RECORD, 1, Home->GetGameRecord(), "Home Record");

		wxString message = awaygoals > homegoals ? Away->GetTeamabbr() + " won against " + Home->GetTeamabbr() + " " + away + " to " + home :
			Home->GetTeamabbr() + " won against " + Away->GetTeamabbr() + " " + home + " to " + away;
		PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, message);
		PassToCallBack(GameWindow::GAMEOVER, 1, Home->GetGameRecord(), "Fuck");
	}
	isgameinsession = false;
	Reset();
}

NHLTeam* Game::NewPlayoffGame(NHLTeam* away, NHLTeam* home)
{
	playoffs = true;
	IsGameOnScreen = false;
	isgameinsession = true;
	Away = away;
	Home = home;

	awaylines = Away->GetLines();
	homelines = Home->GetLines();
	awaylines->ResetInGameBockedShots();
	homelines->ResetInGameBockedShots();

	ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);

	homegoalie = homelines->goalie;
	awaygoalie = awaylines->goalie;

	StartGame();
	NHLTeam* returnteam = awaygoals > homegoals ? away : home;
	Reset();
	if (IsGameOnScreen)
	{
		PassToCallBack(GameWindow::AWAY_RECORD, 1, Away->GetGameRecord(), "Away Record");
		PassToCallBack(GameWindow::HOME_RECORD, 1, Home->GetGameRecord(), "Home Record");
		PassToCallBack(GameWindow::GAMEOVER, 1, Home->GetGameRecord(), "Fuck");
	}

	Reset();
	isgameinsession = false;

	return returnteam;
}

void Game::EndGame()
{
	endgame = true;
	awayshots = *shotlimit;
	homeshots = *shotlimit;
	awaygoals = 1;
	homegoals = 2;
}

void Game::ChangeLines(Forwards* away_f, Defense* away_d, Forwards* home_f, Defense* home_d)
{
	AwayF = away_f;
	AwayD = away_d;
	HomeF = home_f;
	HomeD = home_d;
}

void Game::StartGame()
{
	double awayteamrating = Away->GetTeamRating();
	double hometeamrating = Home->GetTeamRating();
//	int averageAshots = awayteamrating / 28;
//	int averageHshots = hometeamrating / 28;
//	shotlimit = averageAshots > averageHshots ? &averageAshots : &averageHshots;
	awaylines = Away->GetLines();
	homelines = Home->GetLines();
	int awayadvantage = awayteamrating > hometeamrating ? 10 : 1;
	int homeadvantage = hometeamrating > awayteamrating ? 10 : 1;
	homeadvantage += 5;
	int homesh = ((int)homelines->GetShotsPerGame() + homeadvantage);// / 2;
	int awaysh = ((int)awaylines->GetShotsPerGame() + awayadvantage); // / 2;
//	awaysh = Pull(generator, awaysh - 10, awaysh + 10);
//	homesh = Pull(generator, homesh - 10, homesh + 10);
//	shotlimit = shotlimit == &averageAshots ? &awayshots : &homeshots;
	if (homesh > awaysh)
	{
		shotlimit = &homeshots;
		totalshots = homesh;
	}
	else
	{
		shotlimit = &awayshots;
		totalshots = awaysh;
	}



//	otherteam_shotlimit = shotlimit == &awayshots ? &homeshots : &awayshots;
//	totalshots = Pull(generator, totalshots - Pull(generator, 0, 6), totalshots + Pull(generator, 0, 12));
//	otherteam_totalshots = totalshots + Pull(generator, -10, 10);
	int loop = 0;
	for (size_t i = 0; i < 9; ++i)
	{
		recursions = 0;
		if (endgame)
			return;

		if (*shotlimit >= totalshots)
		{
			if (awaygoals == homegoals)
			{
				recursions = 0;
//				wxMessageBox("The game is going to overtime");
				if (IsGameOnScreen)
				{
					wxString overtimenumber = "";
					if (overtimetracker > 1)
						overtimenumber = "the " + GetOrdinal(overtimetracker);
					CallBack(GameWindow::OVERTIME, 1, V, nullptr, "Game is going to " + overtimenumber + " overtime");
					overtimetracker++;
				}
				overtime = true;
				loop = 0;
			}
			else break;
		}
		while (loop < 8)
		{
			recursions = 0;
			if (*shotlimit >= totalshots && !overtime) break;
			if (overtime && awaygoals != homegoals) break;
			switch (loop)
			{
			case 0:
			{
				ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);
				break;
			}
			case 1:
			{
				ChangeLines(&awaylines->line2, &awaylines->paring2, &homelines->line2, &homelines->paring2);
				break;
			}
			case 2:
			{
				ChangeLines(&awaylines->line3, &awaylines->paring3, &homelines->line3, &homelines->paring3);
				break;
			}
			case 3:
			{
				ChangeLines(&awaylines->line4, &awaylines->paring2, &homelines->line4, &homelines->paring2);
				break;
			}
			case 4:
			{
				ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);
				break;
			}
			case 5:
			{
				ChangeLines(&awaylines->line2, &awaylines->paring2, &homelines->line2, &homelines->paring2);
				break;
			}
			case 6:
			{
				ChangeLines(&awaylines->line1, &awaylines->paring1, &homelines->line1, &homelines->paring1);
				break;
			}
			case 7:
				ChangeLines(&awaylines->line2, &awaylines->paring2, &homelines->line2, &homelines->paring2);
				break;
			}
			Faceoff(AwayF->center, HomeF->center);
			haspuck = nullptr;
			++loop;
		}
		loop = 0;
	}
	if (playoffs)
	{
		Away->AddPlayoffGameOutcome(GameStats(overtime, AwayShotsOnGoal, HomeShotsOnGoal, awayshots, homeshots, AwayBlockedShots, HomeBlockedShots,
			awaygoals, homegoals, false, Away->GetTeamID(), Home->GetTeamID()));
		Home->AddPlayoffGameOutcome(GameStats(overtime, HomeShotsOnGoal, AwayShotsOnGoal, homeshots, awayshots, HomeBlockedShots, AwayBlockedShots,
			homegoals, awaygoals, true, Home->GetTeamID(), Away->GetTeamID()));
	}
	else
	{
		Away->AddGameOutcome(GameStats(overtime, AwayShotsOnGoal, HomeShotsOnGoal, awayshots, homeshots, AwayBlockedShots, HomeBlockedShots,
			awaygoals, homegoals, false, Away->GetTeamID(), Home->GetTeamID()));
		Home->AddGameOutcome(GameStats(overtime, HomeShotsOnGoal, AwayShotsOnGoal, homeshots, awayshots, HomeBlockedShots, AwayBlockedShots,
			homegoals, awaygoals, true, Home->GetTeamID(), Away->GetTeamID()));
	}
}

void Game::Faceoff(NHLplayer* away, NHLplayer* home)
{
	int a = away->GetFaceOffPercent() * 1000;
	int h = home->GetFaceOffPercent() * 1000;
	int total = h + a;
	int result = Pull(generator, 0, total);
	func = GetPlayerDefensiveBias;
	if (result < a)
	{
		if (Dev)
			wxMessageBox(away->GetName() + " won the faceoff against " + home->GetName());
		Homepuck = false;
		Awaypuck = true;
		away->SetFaceoffWin();
		home->SetFaceoffLoss();
		NHLplayer* f1 = away == AwayF->left ? AwayF->center : AwayF->left;
		NHLplayer* f2 = away == AwayF->right ? AwayF->right : AwayF->center;
		if (f2 == f1) f2 = AwayF->left;
		if (AwayIce::AwayNeutral == IceAreaAway)
			GetNewIceArea(-1, AwayIce::AwayNeutral, AwayIce::AwayDefensive);
		Recieve(away, 1, 9);
	}
	else
	{ 
		if (Dev)
			wxMessageBox(home->GetName() + " won the faceoff against " + away->GetName());
		Homepuck = true;
		Awaypuck = false;
		home->SetFaceoffWin();
		away->SetFaceoffLoss();
		NHLplayer* f1 = home == HomeF->left ? HomeF->center : HomeF->left;
		NHLplayer* f2 = home == HomeF->right ? HomeF->center : HomeF->right;
		if (f2 == f1) f2 = HomeF->left;
		if (HomeIce::Neutral == IceAreaHome)
			GetNewIceArea(-1, HomeIce::Neutral, HomeIce::Defensive);
		Recieve(home, 1, 9);
	}
}

void Game::SwitchPuck(bool home, bool away)
{
	if (Homepuck)
	{
		Awaypuck = Homepuck;
		Homepuck = false;
	}
	else
	{
		Homepuck = Awaypuck;
		Awaypuck = false;
	}
}

void Game::Recieve(NHLplayer* p, int low, int high)
{
	NHLplayer* next = p;
	Forwards* F = nullptr;
	Defense* D = nullptr;
	if (Homepuck)
	{
		F = HomeF;
		D = HomeD;
	}
	else
	{
		F = AwayF;
		D = AwayD;
	}
	while (next == p)
		next = func(F, D, Pull(generator, low, high));

	if (Dev)
	{
		if (haspuck)
			wxMessageBox(haspuck->GetName() + " passed to " + next->GetName());
		else
			wxMessageBox(next->GetName() + " recieved faceoff");
	}
	
	haspuck = next;
	NextPlay();
}

void Game::NextPlay()
{
	++recursions;
	if (recursions == 500)
	{
		//prevent stack overflow..
		//return tv timeout...
		return;
	}

	if (endgame)
		return;

	if (*shotlimit > totalshots)
	{
		if (!overtime)
			return;
	}
	
	if (Homepuck)
	{
		if (HomeIce::Offensive == IceAreaHome)
		{
			if (CheckOrSteal(GetPlayerDefensiveBias(AwayF, AwayD, Pull(generator, 1, 9))))
			{
				assistplayer = nullptr;
				secondary_assist_player = nullptr;
				NextPlay();
				return;
			}
			PassShoot();
		}
		else if(HomeIce::Defensive == IceAreaHome)
		{
			if (CheckOrSteal(GetPlayerOffensiveBias(AwayF, AwayD, Pull(generator, 1, 8))))
			{
				assistplayer = nullptr;
				secondary_assist_player = nullptr;
				NextPlay();
				return;
			}
			GetNewIceArea(-1, HomeIce::Neutral, HomeIce::Defensive);
			func = GetPlayerNeutralBias;
			Pass(haspuck, 1, 5);
		}
		else
		{
			if (CheckOrSteal(GetPlayerNeutralBias(AwayF, AwayD, Pull(generator, 1, 5))))
			{
				assistplayer = nullptr;
				secondary_assist_player = nullptr;
				NextPlay();
				return;
			}
			GetNewIceArea(HomeIce::Offensive, HomeIce::Neutral, HomeIce::Defensive, 6);
			func = GetPlayerNeutralBias;
			Pass(haspuck, 1, 5);
		}
	}
	else
	{
		if (AwayIce::AwayOffensive == IceAreaAway)
		{
			if (CheckOrSteal(GetPlayerDefensiveBias(HomeF, HomeD, Pull(generator, 1, 9))))
			{
				assistplayer = nullptr;
				secondary_assist_player = nullptr;
				NextPlay();
				return;
			}
			PassShoot();
		}
		else if (AwayIce::AwayDefensive == IceAreaAway)
		{
			if (CheckOrSteal(GetPlayerOffensiveBias(HomeF, HomeD, Pull(generator, 1, 8))))
			{
				assistplayer = nullptr;
				secondary_assist_player = nullptr;
				NextPlay();
				return;
			}
			GetNewIceArea(-1, AwayIce::AwayNeutral, AwayIce::AwayDefensive);
			func = GetPlayerNeutralBias;
			Pass(haspuck, 1, 5);
		}
		else
		{
			if (CheckOrSteal(GetPlayerNeutralBias(HomeF, HomeD, Pull(generator, 1, 5))))
			{
				assistplayer = nullptr;
				secondary_assist_player = nullptr;
				NextPlay();
				return;
			}
			GetNewIceArea(AwayIce::AwayOffensive, AwayIce::AwayNeutral, AwayIce::AwayDefensive, 3);
			func = GetPlayerNeutralBias;
			Pass(haspuck, 1, 5);
		}
	}
}

void Game::Pass(NHLplayer* p, int low, int high)
{
	shot_rebound = nullptr;

	Forwards* F = nullptr;
	Defense* D = nullptr;

	if(Homepuck)
	{
		F = HomeF;
		D = HomeD;
	}
	else if (Awaypuck)
	{
		F = AwayF;
		D = AwayD;
	}

	NHLplayer* next = p;
	while (next == p)
		next = func(F, D, Pull(generator, low, high));
	
	if (Dev)
		wxMessageBox(haspuck->GetName() + " passed to " + next->GetName());
	secondary_assist_player = assistplayer;
	assistplayer = haspuck;
	haspuck = next;
	NextPlay();
}

void Game::PassShoot()
{
//	int off = haspuck->GetOffenseRating() + 10;
	int off = haspuck->GetGameScore();
	if (off <= 0) off = 10;
	if (Homepuck)
		off += 5;
	int pass = Pull(generator, 1, 50);
	int shoot = Pull(generator, 1, off);

	if (shoot < pass)
	{
		shot_rebound = nullptr;
		func = GetPlayerOffensiveBias;
		Pass(haspuck, 1, 8);
	}
	else {
		if (!IsOnSameLine()) 
			shot_rebound = nullptr;
		Shoot();
	}
}

void Game::Shoot()
{
	haspuck->SetShotAttempt();
	AddShot();
	int ongp = (haspuck->GetShotOnGoalPercent() * 100) + (haspuck->GetOffenseRating() * 3);
	int isOnGoal = Pull(generator, 1, 100);
	bool ongoal = false;
	if (isOnGoal <= ongp)
	{
		//shot is on goal...
		ongoal = true;
	}

	if (IsBlock())
	{
		AddBlockedShot();
		//shot blocked..
		ReboundRecover();
		return;
	}

	GameWindow g;
	if (ongoal)
	{
		AddShotOnGoal();
		g = IsGoalieStop();
		switch (g)
		{
		case GameWindow::FREEZ: return;
		case GameWindow::REBOUND: shot_rebound = haspuck; ReboundRecover(); return;
		case GameWindow::GOAL_ALLOWED: SetIceAreaToNeutral(); return;
		}
	}
	
	AddMissedShot();
    DevUpdate(haspuck->GetName() + "'s attempted shot was off target");
	
	//missed shot...
	ReboundRecover();
}

bool Game::IsBlock()
{
	Forwards* F = GetOpposingForwardLine();
	Defense* D = GetOpposingDefenseLine();
	NHLplayer* d = GetPlayerDefensiveBias(F, D, Pull(generator, 1, 9));

	int bs = d->GetBlockedShotsPerGame() + 1;
	int over = d->GetInGameBlockedShots();

	if (over > bs)
	{
		over = -(bs - over);
		if (over == 1 || over == 2)
			over = 3;
		else 
			over = 6;
	}
	else 
		over = 2;

	int isblocked = Pull(generator, 1, bs * over);

	if (isblocked <= bs)
	{
		//block shot...
		DevUpdate(haspuck->GetName() + "'s attempted shot was blocked by " + d->GetName());
		d->SetBlockedShot();
		haspuck->SetShotAttemptBlocked();
		return true;
	}

	return false;
}

GameWindow Game::IsGoalieStop()
{

	NHLplayer* G = GetOpposingGoalie();
	int homeadvantage = Awaypuck ? 25 : 0;

	int saveperc = G->GetGameScore() * 1000 + homeadvantage;
	int save = Pull(generator, 1, 1000);

	haspuck->SetShotOnGoal();

//	AddShot();
	GenerateShotAlert();

	int gamescore = haspuck->GetGameScore();
	if (gamescore <= 0) gamescore = 0;
	int divisor = gamescore > 95 ? 4 : 1;
//	divisor = assistplayer && assistplayer->GetGameScore() > 95 ? 4 : 1;
// 
//	if (haspuck->GetName() == "Kirill Kaprizov")
//		saveperc /= 2;

	if (divisor > 1 && Pull(generator, 1, 3) == 3)
	{
		int gamescoreperc = Pull(generator, 1, saveperc / divisor);
		saveperc -= gamescoreperc <= gamescore ? gamescore : 0;
	}

	//if the same player that just took a shot and recovered the rebound has ~50% chance to score...
//	if (shot_rebound == haspuck) 
//		saveperc = saveperc * 3 / 4;
//	else if (shot_rebound) 
//		saveperc = (double)saveperc * 4 / 5;

	if (save <= saveperc)
	{
		//goalie save...
		G->SetSave();
		int freez = G->GetFreezePerc() * 100;
		int result = Pull(generator, 1, 100);

		if (result <= freez)
		{
			DevUpdate(G->GetName() + " froze puck after " + haspuck->GetName() + "'s shot");

			G->SetFreeze();
			return GameWindow::FREEZ;
		}
		else
		{
			//rebound...
			DevUpdate(G->GetName() + " gave up the rebound on " + haspuck->GetName() + "'s shot");

			G->SetRebound();
			return GameWindow::REBOUND;
		}
	}
	else
	{
		//player scored on goalie...
		G->SetGoalAllowed();
		haspuck->SetGoal();

		if (assistplayer) 
			assistplayer->SetAssist();
		if (secondary_assist_player)
			secondary_assist_player->SetSecondaryAssist();
		if (shot_rebound && shot_rebound != haspuck)
			shot_rebound->SetAssist();

		GenerateGoalAlert();
		AddGoal();
		return GameWindow::GOAL_ALLOWED;
	}
}

Forwards* Game::GetOpposingForwardLine()
{
	return Homepuck ? AwayF : HomeF;
}

Defense* Game::GetOpposingDefenseLine()
{
	return Homepuck ? AwayD : HomeD;
}

NHLplayer* Game::GetOpposingGoalie()
{
	return Homepuck ? awaygoalie : homegoalie;
}

void Game::AddShot()
{
	if (Homepuck) ++homeshots;
	else ++awayshots;
}

void Game::AddShotOnGoal()
{
	if (Homepuck)
		++HomeShotsOnGoal;
	else
		++AwayShotsOnGoal;
}

void Game::AddMissedShot()
{
	if (Homepuck)
		++HomeMissedShots;
	else
		++AwayMissedShots;
}

void Game::AddBlockedShot()
{
	if (Homepuck)
		++AwayBlockedShots;
	else
		++HomeBlockedShots;
}

void Game::AddGoal()
{
	if (Homepuck)
	{
		++homegoals;
		if (IsGameOnScreen)
			PassToCallBack(GameWindow::HOMESCORE, 1, nullptr);
		AwayF->AddOnIceAgainstGoal();
		AwayD->AddOnIceAgainstGoal();
	}
	else
	{
		++awaygoals;
		if (IsGameOnScreen)
			PassToCallBack(GameWindow::AWAYSCORE, 1, nullptr);
		HomeF->AddOnIceAgainstGoal();
		HomeD->AddOnIceAgainstGoal();
	}
}

void Game::SetIceAreaToNeutral()
{
	IceAreaAway = HomeIce::Neutral;
	IceAreaHome = HomeIce::Neutral;
}

void Game::GenerateGoalAlert()
{
	if (IsGameOnScreen)
	{
		NHLplayer* G = GetOpposingGoalie();
		wxString assist = assistplayer ? "! \nAssist provided by " + assistplayer->GetName() : "";

		if (shot_rebound == haspuck)
		{
			PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, haspuck->GetName() + " scored on his own rebound!");
			return;
		}
		if (shot_rebound)
		{
			PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, haspuck->GetName() + " scored on " + shot_rebound->GetName() + "'s rebound!");
			return;
		}
		int res = Pull(generator, 1, 3);
		wxString s = playoffs ? " playoffs!" : " season!";
		if (res == 1)
			PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, haspuck->GetName() + " scored on " + G->GetName() + assist);
		else if (res == 2)
			PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, haspuck->GetName() + " scored his " + GetOrdinal(haspuck->GetCurrentYearGoals()) + " goal of the" + s + assist);
		else
		{
			if (assistplayer)
				assist += ". Thats his " + GetOrdinal(assistplayer->GetCurrentYearAssists()) + " of the" + s;
			PassToCallBack(GameWindow::MESSAGE_UPDATE, 1, nullptr, haspuck->GetName() + " scored his " + GetOrdinal(haspuck->GetCurrentYearGoals()) + " goal of the" + s + assist);
		}
	}
}

void Game::GenerateShotAlert()
{
	if (IsGameOnScreen)
		PassToCallBack(Homepuck ? GameWindow::HOMESHOTS : GameWindow::AWAYSHOTS, 1, nullptr);
}

void Game::DevUpdate(wxString s)
{
	if (Dev)
		wxMessageBox(s);
}

bool Game::IsOnSameLine()
{
	if (!shot_rebound)
		return false;
	if ((AwayF->HasPlayer(haspuck) || AwayD->HasPlayer(haspuck)) && (AwayF->HasPlayer(shot_rebound) || AwayD->HasPlayer(shot_rebound)))
		return true;
	if ((HomeF->HasPlayer(haspuck) || HomeD->HasPlayer(haspuck)) && (HomeF->HasPlayer(shot_rebound) || HomeD->HasPlayer(shot_rebound)))
		return true;

	return false;
}

void Game::Recover(Forwards* f, Defense* d)
{
	int player = Pull(generator, 0, 4);

	switch (player)
	{
	case 0: 
	{
		haspuck = f->left;
		break;
	}
	case 1:
	{
		haspuck = f->center;
		break;
	}
	case 2:
	{
		haspuck = f->right;
		break;
	}
	case 3:
	{
		haspuck = d->d1;
		break;
	}
	case 4:
	{
		haspuck = d->d2;
		break;
	}
	}

	if (Dev)
		wxMessageBox(haspuck->GetName() + " recovered rebound.");
	NextPlay();
}

void Game::Recover(Forwards* defense_f, Defense* defense_d, Forwards* offense_f, Defense* offense_d, double& defense, double& offense, int offensive)
{
	assistplayer = nullptr;
	double advantage = defense - offense;
	int ad = advantage > 0 ? advantage * 10 : (-1 * advantage) * 10;

	int off = 100 + offensive;
	int def = Awaypuck && IceAreaAway == AwayIce::AwayOffensive ? 200 : 200;

	if (advantage < 0) off += ad;
	else def += ad;

	int result = Pull(generator, 0, def + off);
	if (result > def)
	{
		if (offense_f == HomeF)
		{
			if (Awaypuck)
				SwitchPuck(Awaypuck, Homepuck);
		}
		if (offense_f == AwayF)
		{
			if (Homepuck)
				SwitchPuck(Awaypuck, Homepuck);
		}
		Recover(offense_f, offense_d);
	}
	else
	{
		if (defense_f == HomeF)
		{
			if (Awaypuck)
				SwitchPuck(Awaypuck, Homepuck);
		}
		if (defense_f == AwayF)
		{
			if (Homepuck)
				SwitchPuck(Awaypuck, Homepuck);
		}
		Recover(defense_f, defense_d);
	}
}

void Game::ReboundRecover()
{
	double homecorsi = 0.0;
	double awaycorsi = 0.0;
	homecorsi += HomeF->GetCorsiPercent();
	homecorsi += HomeD->GetCorsiPercent();
	awaycorsi += AwayF->GetCorsiPercent();
	awaycorsi += AwayD->GetCorsiPercent();
	homecorsi += homecorsi * .10;

	if (IceAreaHome == HomeIce::Defensive)
		Recover(HomeF, HomeD, AwayF, AwayD, homecorsi, awaycorsi, 0);
	else if (IceAreaAway == AwayIce::AwayDefensive)
		Recover(AwayF, AwayD, HomeF, HomeD, awaycorsi, homecorsi, 0);
	else
		Recover(HomeF, HomeD, AwayF, AwayD, homecorsi, awaycorsi, 100);
}

bool Game::IsHomePlayer(NHLplayer* p)
{
	bool h = HomeF->HasPlayer(p);
	if (h) 
		return h;

	return HomeD->HasPlayer(p);
}

void Game::GetNewIceArea(int o, int n, int d, int offenseodds, int neutralodds, int defenseodds)
{
	if (d == -1)
	{
		if (o > n)
		{
			IceAreaHome = IceAreaAway = Pull(generator, n, o + offenseodds);
			if (IceAreaHome >= 3)
				IceAreaHome = IceAreaAway = AwayIce::AwayOffensive;
			if (IceAreaAway == AwayIce::AwayOffensive)
				++awayoffensiveSwitches;
		}
		else
		{
			IceAreaHome = IceAreaAway = Pull(generator, o, n + offenseodds);
			if (IceAreaHome >= 3)
				IceAreaHome = IceAreaAway = HomeIce::Offensive;
			if (IceAreaAway == HomeIce::Offensive)
				++homeoffensiveSwitches;
		}

		return;
	}
	if (o == -1)
	{
		if (d > n)
			IceAreaHome = IceAreaAway = Pull(generator, n, d);
		else
			IceAreaHome = IceAreaAway = Pull(generator, d, n);

		return;
	}

	if (o > d)
	{
		IceAreaHome = IceAreaAway = Pull(generator, d, o + offenseodds);
		if (IceAreaHome >= 3)
			IceAreaHome = IceAreaAway = AwayIce::AwayOffensive;
		if (IceAreaAway == AwayIce::AwayOffensive)
			++awayoffensiveSwitches;
	}
	else
	{
		IceAreaHome = IceAreaAway = Pull(generator, o, d + offenseodds);
		if (IceAreaHome >= 3)
			IceAreaHome = IceAreaAway = HomeIce::Offensive;
		if (IceAreaAway == HomeIce::Offensive)
			++homeoffensiveSwitches;
	}
}

bool Game::CheckOrSteal(NHLplayer* p)
{
	if (!p) return false;
	int hometweak = 30;

	int pulltopend = Awaypuck && (IceAreaAway == AwayIce::AwayOffensive) ? hometweak : 30;
	int check = Pull(generator, 1, pulltopend);
	if (check <= 15)
	{
		//check attempt
		double pw = p->GetWeight();
		double hp = haspuck->GetWeight();
		double weight_dif = pw - hp;
		if (weight_dif < 0)
		{
			int topcheck = 13;
			int checksuccess = Pull(generator, 1, topcheck);
			if (checksuccess == 1)
			{
				if (Dev)
					wxMessageBox(haspuck->GetName() + " was checked by " + p->GetName());
				haspuck->SetGaveUpPuck();
				p->SetStolePuck();
				haspuck = p;
				SwitchPuck(true, false);
				assistplayer = nullptr;
				return true;
			}
			return false;
		}
		else
		{
			int topcheck = pulltopend == hometweak ? 130 : 130;
			int checksuccess = Pull(generator, 1, topcheck);
			if (checksuccess > weight_dif)
				return false;
			else
			{
				if (Dev)
					wxMessageBox(haspuck->GetName() + " was checked by " + p->GetName());
				haspuck->SetGaveUpPuck();
				p->SetStolePuck();
				haspuck = p;
				SwitchPuck(true, false);
				assistplayer = nullptr;
				return true;
			}
		}
	}
	else
	{
		int tg = (p->GetTakeaway_Giveaway() * 100);
		int topsteal = pulltopend == hometweak ? 100 : 100;
		int result = Pull(generator, 1, topsteal);
		if (tg <= result)
		{
			if (haspuck->GetGameScore() > 95)
			{
				if (tg > 15)
					return false;
			}
			if (Dev)
				wxMessageBox(haspuck->GetName() + " had puck stolen by " + p->GetName());
			haspuck = p;
			SwitchPuck(true, false);
			assistplayer = nullptr;
			return true;
		}
		return false;
	}
	return false;
}

void Game::AddOnIceGoalStats()
{
	if (Homepuck)
	{
		AwayF->AddOnIceAgainstGoal();
		AwayD->AddOnIceAgainstGoal();
		HomeF->AddOnIceForGoal();
		HomeD->AddOnIceForGoal();
	}
	else
	{
		AwayF->AddOnIceForGoal();
		AwayD->AddOnIceForGoal();
		HomeF->AddOnIceAgainstGoal();
		HomeD->AddOnIceAgainstGoal();
	}
}

void Game::Reset()
{
	endgame = false;
	homeposession = 0;
	awayposession = 0;
	homeoffensiveSwitches = 0;
	awayoffensiveSwitches = 0;
	homegoals = 0;
	awaygoals = 0;
	homeshots = 0;
	awayshots = 0;
	overtime = false;
	overtimetracker = 1;
	recursions = 0;
	HomeShotsOnGoal = 0;
	AwayShotsOnGoal = 0;
	HomeBlockedShots = 0;
	AwayBlockedShots = 0;
	HomeMissedShots = 0;
	AwayMissedShots = 0;
//	CallBack = nullptr;
}

void Game::PassToCallBack(GameWindow id, int value, GameRecord* gr, wxString s)
{
	CallBack(id, value, V, gr, s);
}

wxLongLong Game::End()
{
	wxLongLong end = wxDateTime::Now().GetValue() - Posession.GetValue();
	return end;
}