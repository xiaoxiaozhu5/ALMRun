#include "MerryTaskBarIcon.h"
#include "MerryApp.h"
#include "MerryInformationDialog.h"
#include "cmdmgr.h"

BEGIN_EVENT_TABLE(MerryTaskBarIcon, wxTaskBarIcon)
	EVT_MENU_RANGE(MENU_ITEM_FIRST,MENU_ITEM_LAST,MerryTaskBarIcon::onPopMenu)
	EVT_TASKBAR_LEFT_DCLICK(MerryTaskBarIcon::OnLeftButtonDClickEvent)
END_EVENT_TABLE()

MerryTaskBarIcon::~MerryTaskBarIcon()
{
	__DEBUG_BEGIN("")
		this->RemoveIcon();
	__DEBUG_END("")
}

wxMenu* MerryTaskBarIcon::CreatePopupMenu()
{
	wxMenu* menu = new wxMenu;

	menu->Append(MENU_ITEM_SHOW, _("Show(&O)"));
	menu->Append(MENU_ITEM_GUI_CONFIG, _("Settings(&C)"));
	menu->Append(MENU_ITEM_CMDMGR, _("Commands(&S)"));
	menu->Append(MENU_ITEM_OPEN_CONFIG, _("Open Program Location(&S)"));
	menu->Append(MENU_ITEM_RECONFIG, _("Refresh(R)"));
	menu->Append(MENU_ITEM_ABOUT, _("About(&A)"));
	menu->Append(MENU_ITEM_EXIT1, _("Exit(&X)"));

	return menu;
}

void MerryTaskBarIcon::onPopMenu(wxCommandEvent& e)
{
	switch(e.GetId())
	{
		case MENU_ITEM_SKIN:
			{
				wxString file = wxFileSelector("请选择","skin/",wxEmptyString,wxT(".skn"),"*.skn",0);
				if (file.IsEmpty())
					break;
				wxFileName fn(file);
				if (g_config->set("skin",fn.GetName()))
					wxMessageBox("目前的版本尚未完善,修改主题需要重新启动程序才能看到效果,请重启程序.","切换主题");
			}
			break;
		case MENU_ITEM_ABOUT:
			new MerryInformationDialog(wxT("关于 ALMRun"),wxString::Format("version " VERSION_STR " --- http://ALMRun.chenall.net\r\n相关资源:\r\n原版: http://name5566.com\r\n主题: http://executor.dk/\r\n源码: https://github.com/chenall/almrun\r\n\r\n编译时间:%s %s",__DATE__,__TIME__));
			break;
		case MENU_ITEM_SHOW:
			::wxGetApp().GetFrame().Show();
			break;
		case MENU_ITEM_OPEN_CONFIG:
			::wxGetApp().GetFrame().OpenConfigDir();
			break;
		case MENU_ITEM_RECONFIG:
			::wxGetApp().GetFrame().NewConfig();
			break;
		case MENU_ITEM_EXIT:
			//wxGetApp().ExitMainLoop();
			// insert your code here
			//ExitProcess(0);
		   // this->EndModal(true);
			//::PostMessage((HWND__ *)::wxGetApp().GetFrame().GetHandle(),WM_CLOSE,0,0);
		   //::PostMessage((HWND__ *)::wxGetApp().GetFrame().GetHandle(),WM_QUIT,0,0);
		   //exit(0);
			wxExit();
			break;
		case MENU_ITEM_EXIT1:
			PostMessage((HWND__ *)::wxGetApp().GetFrame().GetHandle(),WM_CLOSE,0,0);
			break;
	#ifdef _ALMRUN_CONFIG_H_
		case MENU_ITEM_GUI_CONFIG:
			g_config->GuiConfig();
			break;
	#endif//#ifdef _ALMRUN_CONFIG_H_
	#ifdef _CMDMGR_H_
		case MENU_ITEM_CMDMGR:
			cmdMgr *dlg = new cmdMgr(0);
			dlg->ShowModal();
			dlg->Destroy();
			::wxGetApp().GetFrame().NewConfig();
			break;
	#endif
	}
}

void MerryTaskBarIcon::OnLeftButtonDClickEvent(wxTaskBarIconEvent& e)
{
	::wxGetApp().GetFrame().Show();
	e.Skip();
}
