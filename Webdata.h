#pragma once
#define CURL_STATICLIB

#include "wx/wx.h"
#include"curl/curl.h"
#include <exception>




class webdata
{

public:
	webdata();
	~webdata();
	bool IsGoodRequest();
public:
	bool getwebdata(wxString&);
	void seturl(wxString);
	void DeleteURL();

private:
	char* url = nullptr;
	// IS GOOD REQUEST...
	bool IGR = false;
};


