#include "NHLplayer.h"

int Pull(Gen& generator, int i, int j)
{
	Distributor random(i, j);
	return generator.getnum(random);
}

wxString GetStringValue(double value, int decimal)
{
	wxString temp = "";
	temp << value;
	wxString returnvalue = "";
	int i = temp.find('.');

	if (i == -1)
		return temp;

	for (size_t j = 0; j <= i + decimal && j < temp.size(); ++j)
		returnvalue += temp[j];

	return returnvalue;
}

wxString GetOrdinal(int n)
{
	wxString s = "";
	s << n;
	char c = ' ';
	if (s.size())
		c = s[s.size() - 1];

	if (n < 20 && n > 10) return s + "th";
	if (n < 120 && n > 110) return s + "th";
	switch (c)
	{
	case '1': return s + "st";
	case '2': return s + "nd";
	case '3': return s + "rd";
	default: return s + "th";
	}
}

wxStaticText* InitStaticText(wxWindow* parent, wxWindowID id, wxString s, int fontsize, wxFontFamily f, wxFontWeight w, wxColour c, wxPoint point, wxSize size)
{
	wxFont F;
	F.SetPointSize(fontsize);
	F.SetFamily(f);
	F.SetWeight(w);
	wxStaticText* T = new wxStaticText(parent, id, s, point, size);
	T->SetFont(F);
	T->SetForegroundColour(c);
	T->SetBackgroundColour(parent->GetBackgroundColour());
	return T;
}

Stats::Stats()
{

}

Stats::Stats(int AGE, int ID, char POS, char SHOT, int YEAR, wxString TEAM, wxString NAME) : age(AGE), id(ID), Pos(POS), shot(SHOT), season(YEAR), team(TEAM), name(NAME)
{
	
}

Stats::~Stats()
{

}

void Stats::CalcValues()
{
	age -= (wxDateTime::Today().GetYear() - 1) - season;

	if (Pos != 'G')
	{
		if (faceoffsWon + faceoffsLost)
			faceoffPerc = double(faceoffsWon) / (double(faceoffsWon) + double(faceoffsLost));
		if (I_F_shotAttempts)
		{
			if (I_F_shotAttempts < 20) shotsonGoalPercent = .50;
			else shotsonGoalPercent = double(I_F_shotsOnGoal) / double(I_F_shotAttempts - I_F_blockedShotAttempts);
		}
		if (I_F_takeaways + I_F_giveaways)
			takeaway_giveaway = double(I_F_takeaways) / (double(I_F_takeaways) + double(I_F_giveaways));
		if (games_played)
		{
			shotsPerGame = double(I_F_shotAttempts) / double(games_played);
			BlockedShotsPerGame = double(blockedshots) / double(games_played);
		}

		pv.addDefense(gameScore, blockedshots, I_F_takeaways, I_F_hits, onIce_fenwickPercentage, I_F_giveaways, OnIce_A_goals, games_played);
		pv.addOffense(gameScore, I_F_goals, I_F_primaryAssists, I_F_secondaryAssists, onIce_fenwickPercentage, OnIce_F_Goals, I_F_shotsOnGoal, OnIce_A_goals, games_played);
		pv.CalcValues(this->Pos);
		return;
	}

	if (goals_allowed + ongoalshots)
	{
		if (goals_allowed + ongoalshots)
			save_percent = ongoalshots / (goals_allowed + ongoalshots);
		gameScore = save_percent;
		if (ongoalshots)
		{
			reboundperc = rebounds / ongoalshots;
			freezeperc = freeze / ongoalshots;
		}
		if (games_played)
			goals_per_game = (double)goals_allowed / games_played;
	}
}

void Stats::Add(Stats& S)
{
	if (Pos != 'G')
	{
		I_F_primaryAssists += S.I_F_primaryAssists;
		I_F_secondaryAssists += S.I_F_secondaryAssists;
		I_F_shotsOnGoal += S.I_F_shotsOnGoal;
		I_F_missedShots += S.I_F_missedShots;
		I_F_blockedShotAttempts += S.I_F_blockedShotAttempts;
		shotsonGoalPercent += S.shotsonGoalPercent;
		I_F_shotAttempts += S.I_F_shotAttempts;
		penaltiesDrawn += S.penaltiesDrawn;
		I_F_points += S.I_F_points;
		I_F_goals += S.I_F_goals;
		I_F_rebounds += S.I_F_rebounds;
		I_F_reboundGoals += S.I_F_reboundGoals;
		I_F_hits += S.I_F_hits;
		I_F_takeaways += S.I_F_takeaways;
		I_F_giveaways += S.I_F_giveaways;
		takeaway_giveaway += S.takeaway_giveaway;
		faceoffsWon += S.faceoffsWon;
		faceoffsLost += S.faceoffsLost;
		faceoffPerc += S.faceoffPerc;
		games_played += S.games_played;
		blockedshots += S.blockedshots;
		gameScore += S.gameScore;
		onIce_corsiPercentage += S.onIce_corsiPercentage;
		onIce_fenwickPercentage += S.onIce_fenwickPercentage;
		OnIce_F_Goals += S.OnIce_F_Goals;
		OnIce_F_ShotAttempts += S.OnIce_F_ShotAttempts;
		OnIce_A_goals += S.OnIce_A_goals;
		BlockedShotsPerGame += S.BlockedShotsPerGame;

		pv.overall += S.pv.overall;
		pv.defense += S.pv.defense;
		pv.offense += S.pv.offense;
		return;
	}

	games_played += S.games_played;
	save_percent += S.save_percent;
	goals_allowed += S.goals_allowed;
	ongoalshots += S.ongoalshots;
	rebounds += S.rebounds;
	freeze += S.freeze;
	reboundperc += S.reboundperc;
	freezeperc += S.freezeperc;
}

void Stats::Average(int N)
{
	double n = double(N);
	if (!n) return;

	if (Pos != 'G')
	{
		I_F_primaryAssists /= n;
		I_F_secondaryAssists /= n;
		I_F_shotsOnGoal /= n;
		I_F_missedShots /= n;
		I_F_blockedShotAttempts /= n;
		shotsonGoalPercent /= n;
		I_F_shotAttempts /= n;
		shotsPerGame /= n;
		penaltiesDrawn /= n;
		I_F_points /= n;
		I_F_goals /= n;
		I_F_rebounds /= n;
		I_F_reboundGoals /= n;
		I_F_hits /= n;
		I_F_takeaways /= n;
		I_F_giveaways /= n;
		takeaway_giveaway /= n;
		faceoffsWon /= n;
		faceoffsLost /= n;
		faceoffPerc /= n;
		games_played /= n;
		blockedshots /= n;
		gameScore /= n;
		onIce_corsiPercentage /= n;
		onIce_fenwickPercentage /= n;
		OnIce_F_Goals /= n;
		OnIce_F_ShotAttempts /= n;
		OnIce_A_goals /= n;
		BlockedShotsPerGame /= n;

		pv.overall /= n;
		pv.defense /= n;
		pv.offense /= n;
		return;
	}

	games_played /= n;
	save_percent /= n;
	goals_allowed /= n;
	ongoalshots /= n;
	rebounds /= n;
	freeze /= n;
	reboundperc /= n;
	freezeperc /= n;
}

void Stats::ActivateHomeAdvantage()
{
	homeadvantage.push_back(shotsonGoalPercent * .05);
	shotsonGoalPercent += homeadvantage[homeadvantage.size() - 1];
}

void Stats::DeactivateHomeAdvantage()
{

}

void Stats::Save(wxTextOutputStream& out)
{
	if (Pos != 'G')
	{
		int ID = id << '\n';
		out << age << '\n';
		out << ID << '\n';
		out << year << '\n';
		out << team << '\n';
		out << name << '\n';
		out << season << '\n';
		out << Pos << '\n';
		out << shot << '\n';
		out << I_F_primaryAssists << '\n';
		out << I_F_secondaryAssists << '\n';
		out << I_F_shotsOnGoal << '\n';
		out << I_F_missedShots << '\n';
		out << I_F_blockedShotAttempts << '\n';
		out << shotsonGoalPercent << '\n';
		out << I_F_shotAttempts << '\n';
		out << penaltiesDrawn << '\n';
		out << I_F_points << '\n';
		out << I_F_goals << '\n';
		out << I_F_rebounds << '\n';
		out << I_F_reboundGoals << '\n';
		out << I_F_hits << '\n';
		out << I_F_takeaways << '\n';
		out << I_F_giveaways << '\n';
		out << takeaway_giveaway << '\n';
		out << faceoffsWon << '\n';
		out << faceoffsLost << '\n';
		out << faceoffPerc << '\n';
		out << games_played << '\n';
		out << blockedshots << '\n';
		out << gameScore << '\n';
		out << onIce_corsiPercentage << '\n';
		out << onIce_fenwickPercentage << '\n';
		out << OnIce_F_Goals << '\n';
		out << OnIce_F_ShotAttempts << '\n';
		out << OnIce_A_goals << '\n';
		out << pv.overall << '\n';
		out << pv.offense << '\n';
		out << pv.defense << '\n';
		return;
	}

	int ID = id << '\n';
	out << age << '\n';
	out << ID << '\n';
	out << year << '\n';
	out << team << '\n';
	out << name << '\n';
	out << season << '\n';
	out << Pos << '\n';
	out << save_percent << '\n';
	out << goals_allowed << '\n';
	out << ongoalshots << '\n';
	out << rebounds << '\n';
	out << freeze << '\n';
	out << games_played << '\n';
}

void Stats::Retrieve(wxTextInputStream& in)
{
	int ID = 0;
	in >> age;
	in >> ID;
	in >> year;
	in >> team;
	in >> name;
	in >> season;
	in >> Pos;

	if (Pos != 'G')
	{
		in >> shot;
		in >> I_F_primaryAssists;
		in >> I_F_secondaryAssists;
		in >> I_F_shotsOnGoal;
		in >> I_F_missedShots;
		in >> I_F_blockedShotAttempts;
		in >> shotsonGoalPercent;
		in >> I_F_shotAttempts;
		in >> penaltiesDrawn;
		in >> I_F_points;
		in >> I_F_goals;
		in >> I_F_rebounds;
		in >> I_F_reboundGoals;
		in >> I_F_hits;
		in >> I_F_takeaways;
		in >> I_F_giveaways;
		in >> takeaway_giveaway;
		in >> faceoffsWon;
		in >> faceoffsLost;
		in >> faceoffPerc;
		in >> games_played;
		in >> blockedshots;
		in >> gameScore;
		in >> onIce_corsiPercentage;
		in >> onIce_fenwickPercentage;
		in >> OnIce_F_Goals;
		in >> OnIce_F_ShotAttempts;
		in >> OnIce_A_goals;
		in >> pv.overall;
		in >> pv.offense;
		in >> pv.defense;
		return;
	}

	in >> save_percent;
	in >> goals_allowed;
	in >> ongoalshots;
	in >> rebounds;
	in >> freeze;
	in >> games_played;
}

void PlayerValue::addOffense(int gs, int g, int pa, int sa, double fp, double oniceforgoals, int sog, double onAgoals, int gp)
{
	offense = double(g) / 10 + (double(pa) / 10) + (double(sa) / 10) + fp + (oniceforgoals / 40) + (double(sog) / 40) - (double(onAgoals) / 200);
}

void PlayerValue::addDefense(int gs, int bs, int takeaways, int hits, double fp, int giveaways, double onAgoals, int gp)
{
	defense = ((double(bs) / 100) + (double(takeaways) / 100) + (double(hits) / 100) + fp - (double(giveaways) / 100));
	defense -= double(onAgoals) / 200;
	defense += double(gp) / 200;
}

void PlayerValue::AddGoalieStats()
{

}

void PlayerValue::CalcValues(char position)
{
	if (position == Position::D)
		overall = (offense / 2) + defense;
	else
		overall = offense + (defense / 2);
}

NHLplayer::NHLplayer()
{

}

NHLplayer::NHLplayer(long& l, wxString& pn, char& pos, wxString& t, wxDateTime& b, double& w, wxString& h, wxString& n, char& s, int& pN) : id(l), name(pn), position(pos), team(t), birthday(b),
	weight(w), hieght(h), nationality(n), shot(s), number(pN)
{
	if (birthday.IsValid())
		age = wxDateTime::Today().GetYear() - birthday.GetYear();

	stats = Stats(age, l, position, shot, -1, team, name);
	currentyear = stats;
}

NHLplayer::~NHLplayer()
{

}

void NHLplayer::AddID(long& l)
{
	id = l;
}

void NHLplayer::AddYear(wxString& y)
{
	years.push_back(Stats());
	years[years.size() - 1].year = y;
}

int NHLplayer::FindYearStats(wxString& y)
{
	for (int i = 0; i < years.size(); ++i)
	{
		if (years[i].year == y)
			return i;
	}

	return -1;
}

void NHLplayer::AddName(wxString& n)
{
	name = n;
	years[years.size() - 1].name = n;
}

bool NHLplayer::IsPlayerId(long& l)
{
	if (l == id) return true;

	return false;
}

bool NHLplayer::IsPlayerByName(wxString& n)
{
	if (name == n) return true;

	return false;
}

void NHLplayer::AddTeam(wxString& t)
{
	team = t;
}

void NHLplayer::AddPosition(wxString& s)
{
	if (!s.size())
	{
		wxMessageBox("string passed as paramater in NHLplayer::AddPosition is empty!!");
		return;
	}
	position = s[s.size() - 1];
	years[years.size() - 1].Pos = position;
}

void NHLplayer::AddGamesPlayed(int& gp)
{
	years[years.size() - 1].games_played = gp;
}

void NHLplayer::AddTimeOnIce(int& t)
{

}

void NHLplayer::AddStats(Stats& S)
{
	years.push_back(S);
	Stats* s = &years[years.size() - 1];
	s->shot = shot;
	s->Pos = position;
	statactive = 1;
	id = s->id;
	s->age = age;
	s->CalcValues();
	stats.name = s->name;
	stats.season = s->season;
	stats.year = s->year;
	stats.Pos = position;
	stats.Add(*s);
	stats.age = age;
	stats.shot = shot;
	stats.id = id;

	currentyear.year = s->year;
	currentyear.team = s->team;
	currentyear.Pos = position;
}

void NHLplayer::CalibrateStats()
{
	stats.Average(years.size());
	stats.CalcValues();
	if (years.size())
	{
		stats.gameScore = years[years.size() - 1].gameScore;
	}
	pv.overall = stats.pv.overall;
	pv.offense = stats.pv.offense;
	pv.defense = stats.pv.defense;

	if (name == "Kirill Kaprizov")
		int catch1 = 0;
}

void NHLplayer::SetYearEndStats()
{
	int season = 0;
	this->age++;
	if (years.size())
	{
		season = years[years.size() - 1].season + 1;
	}
	years.push_back(currentyear);
	currentyear = Stats(this->age, this->GetPlayerId(), this->GetPosition(), this->GetShot(), season, this->GetTeam(), this->GetName());
}

void NHLplayer::SetOnIceForShots()
{
	if (!playoffs)
	{
		currentyear.OnIce_F_ShotAttempts++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.OnIce_F_ShotAttempts++;
}

void NHLplayer::SetOnIceAgainstShots()
{
	
}

void NHLplayer::SetOnIceAgainstGoal()
{
	if (!playoffs)
	{
		currentyear.OnIce_A_goals++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.OnIce_A_goals++;
}

void NHLplayer::SetOnIceForGoal()
{
	if (!playoffs)
	{
		currentyear.OnIce_F_Goals++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.OnIce_F_Goals++;
}

void NHLplayer::SetFaceoffWin()
{
	if (!playoffs)
	{
		currentyear.faceoffsWon++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.faceoffsWon++;
}

void NHLplayer::SetFaceoffLoss()
{
	if (!playoffs)
	{
		currentyear.faceoffsLost++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.faceoffsLost++;
}

void NHLplayer::SetGamePlayed()
{
	if (!playoffs)
	{
		currentyear.games_played++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.games_played++;
}

void NHLplayer::SetGoal()
{
	if (!playoffs)
	{
		currentyear.I_F_goals++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_goals++;
}

void NHLplayer::SetAssist()
{
	if (!playoffs)
	{
		currentyear.I_F_primaryAssists++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_primaryAssists++;
}

void NHLplayer::SetSecondaryAssist()
{
	if (!playoffs)
	{
		currentyear.I_F_secondaryAssists++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_secondaryAssists++;
}

void NHLplayer::SetShotAttempt()
{
	if (!playoffs)
	{
		currentyear.I_F_shotAttempts++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_shotAttempts++;
}

void NHLplayer::SetShotAttemptBlocked()
{
	if (!playoffs)
	{
		currentyear.I_F_blockedShotAttempts++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_blockedShotAttempts++;
}

void NHLplayer::SetBlockedShot()
{
	++ingame_blockedshot;

	if (!playoffs)
	{
		currentyear.blockedshots++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.blockedshots++;
}

void NHLplayer::SetShotOnGoal()
{
	currentyear.I_F_shotsOnGoal++;
	currentyear.CalcValues();
}

void NHLplayer::SetMissedShot()
{
	if (!playoffs)
	{
		currentyear.I_F_missedShots++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_missedShots++;
}

void NHLplayer::SetGaveUpPuck()
{
	if (!playoffs)
	{
		currentyear.I_F_giveaways++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_giveaways++;
}

void NHLplayer::SetStolePuck()
{
	if (!playoffs)
	{
		currentyear.I_F_takeaways++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.I_F_takeaways++;
}

void NHLplayer::SetTimeOfPossession(int i)
{

}

void NHLplayer::SetTimeWithoutPossession(int i)
{

}

void NHLplayer::SetSave()
{
	if (!playoffs)
	{
		currentyear.ongoalshots++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.ongoalshots++;
}

void NHLplayer::SetRebound()
{
	if (!playoffs)
	{
		currentyear.rebounds++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.rebounds++;
}

void NHLplayer::SetFreeze()
{
	if (!playoffs)
	{
		currentyear.freeze++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.freeze++;
}

void NHLplayer::SetGoalAllowed()
{
	if (!playoffs)
	{
		currentyear.goals_allowed++;
		currentyear.CalcValues();
	}
	else
		PlayoffStats.goals_allowed++;
}

wxString NHLplayer::GetGoalsAllowedPerGame_String(bool CurrentYear)
{
	if (CurrentYear)
		return wxNumberFormatter::ToString(currentyear.goals_per_game, 2);

	return wxNumberFormatter::ToString(stats.goals_per_game, 2);
}

void NHLplayer::Save(wxTextOutputStream& out)
{
	int temp = id;
	char c = '\n';
	out << temp << c << name << c << position << c << team << c << birthday.Format(STANDARD_DATE) << c << weight << c << nationality << c << shot << c << number << c;
	out << years.size() << c;
	for (size_t i = 0; i < years.size(); ++i)
		years[i].Save(out);

	stats.Save(out);
	out << pv.overall;
	out << pv.offense;
	out << pv.defense;
}

void NHLplayer::Retrieve(wxTextInputStream& in)
{
	char c = ' ';
	int temp = 0;
	wxString b = "";
	in >> temp;
	int start = 0;
	do {
		if (start)
			name += c;
		++start;
		in >> c;
	} while (c != '\n');
	in >> position >> team >> b >> weight >> nationality >> shot;
	if (!birthday.ParseDate(b))
		wxMessageBox("ParseFormat failed in NHLplayer::Retrieve! Date is: " + b);
	else
		age = wxDateTime::Today().GetYear() - birthday.GetYear();
	id = temp;
}
