#pragma once
#include "mainwindow.h"


class NHLapp : public wxApp
{
public:
	NHLapp();
	virtual bool OnInit();

public:
	mainwindow* window = nullptr;
};

