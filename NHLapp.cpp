#include "NHLapp.h"

wxIMPLEMENT_APP(NHLapp);

NHLapp::NHLapp()
{
	
}

bool NHLapp::OnInit()
{
	window = new mainwindow();
	return true;
}
