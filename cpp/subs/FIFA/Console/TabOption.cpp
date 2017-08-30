#include "stdafx.h"
#include "TabOption.h"
#include "Console.h"
#include <Protocol/P_NormalMsg.h>
#include "protect/Protect.h"
#include "CheckLpk.h"
#include "Net/IoTimer.h"
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include "CoordinateC.h"
#include "MainFrm.h"
#include "CheckLoginC.h"
#include <CmnMix/Cmn_TemplateUtility.h>
#include "AntiCrack.h"
#include "GlobalFuncs.h"
//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTabOption, CTabCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelChange)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelChanging)
END_MESSAGE_MAP()

void CTabOption::OnSelChange( NMHDR* notify, LRESULT* result )
{
	const auto kCurSel = GetCurSel();
	assert(kCurSel < _countof(table_pages_));
	if (table_pages_[kCurSel])
	{
		table_pages_[kCurSel]->ShowWindow(SW_SHOW);
	}
}

void CTabOption::OnSelChanging( NMHDR* notify, LRESULT* result )
{
	const auto kCurSel = GetCurSel();
	assert(kCurSel < _countof(table_pages_));
	if (table_pages_[kCurSel])
	{
		table_pages_[kCurSel]->ShowWindow(SW_HIDE);
	}
}

int CTabOption::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( __super::OnCreate(lpCreateStruct) == -1 )
		return -1;
	VMP_BEGIN_EX;
	extern stMakeTabPages g_TabPageMap[stMakeTabPages::kPagesMax];
	static_assert(_countof(table_pages_) == _countof(g_TabPageMap), "table_pages");

	for ( auto i = 0;i != _countof(g_TabPageMap); ++i )
	{
		assert(!table_pages_[i]);
		assert(g_TabPageMap[i].item_name);
		assert(g_TabPageMap[i].obj_class);
		table_pages_[i] = P_CAST<TablePage*>(const_cast<CRuntimeClass*>(
			g_TabPageMap[i].obj_class)->CreateObject());
		assert(table_pages_[i]);
		P_CAST<TablePage*>(table_pages_[i])->SetTabIdx(i);
		table_pages_[i]->Create(this);
		table_pages_[i]->ShowWindow(SW_HIDE);
		InsertItem(i, g_TabPageMap[i].item_name);
	}

#ifdef __PROJ_XIAO_ER_
	SetCurSel(_countof(table_pages_) - 1);
#endif
	OnSelChange(nullptr, nullptr);

	//计时截止时间
	//10分钟检测一次
	CreateIoTimer(10 * 60 * 1000, true, [=](IoTimerPtr io_timer){
		VMP_BEGIN;
		assert(io_timer);
		io_timer->Continue();

		auto tab_option = CTabOption::GetInstance();
		if ( !tab_option )
		{
			assert(false);
			return;
		}
		const DateTimeLocal& time_now = G_GetSerCurTime();
		auto& cfg = stSingletonCfg::GetMe();
		for (auto& v : cfg.GetLoginInfos())
		{
			v.TestTimeEnd(time_now);
		}

		if ( time_now >= tab_option->user_end_time_ )
		{
			assert(false);
#ifdef _DEBUG
			std::string str_end_time = Poco::DateTimeFormatter::format(user_end_time_, Poco::DateTimeFormat::SORTABLE_FORMAT);
			std::string str_time_now = Poco::DateTimeFormatter::format(time_now, Poco::DateTimeFormat::SORTABLE_FORMAT);
#endif
			tab_option->ClearLoginInfo();
			GetIoService().post([](){
				VMP_BEGIN_EX;
				auto main_frm = CMainFrame::GetInstance();
				if ( !main_frm )
				{
					assert(false);
					return;
				}
				main_frm->SetWindowText(VMP_PROTECT_STR(_T("用户时间已用完，请充值，你必须重新启动控制器才能继续")));
				VMP_END;
			});
		}
		VMP_END;
	});

	//1分钟检测次debugger
	SetIoTimer(1 * 60 * 1000, []( IoTimer* timer ){
		assert(timer);
		VMP_BEGIN;
		auto tab_option = CTabOption::GetInstance();
		if ( !tab_option )
		{
			assert(false);
			throw CmnExitIoThreadException("tab option is destroyed");
			return;
		}
		tab_option->CheckDebugger();
		//////////////////////////////////////////////////////////////////////////
		auto failed_cnt = GetLPD_CheckLoginFailedCnt();
		if ( failed_cnt >= 20 || failed_cnt < 0 )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_debug) << "验证登陆无效次数已达上限，无效次数->" << failed_cnt;
			assert(false);
			const char* const kThrowStr = 
#ifdef _DEBUG
				"check login failed cnt limit"
#else
				"clfcl"
#endif
				;
			throw CmnExitIoThreadException(kThrowStr);
		}
		//////////////////////////////////////////////////////////////////////////
		timer->Continue();
		VMP_END;
	});
	//2分钟检测次CRC
	SetIoTimer(1 * 60 * 1000, []( IoTimer* timer ){
		assert(timer);
		VMP_BEGIN;
		auto tab_option = CTabOption::GetInstance();
		if ( !tab_option )
		{
			assert(false);
			throw CmnExitIoThreadException("tab option is real destroyed");
			return;
		}
		tab_option->CheckCrcValid();
		timer->Continue();
		VMP_END;
		if (stSingletonCfg::GetMe().run_at_12_)
		{
			DateTimeLocal time_now;
			if ( time_now.day() != GetMyApp().last_time_12runconsole_.day() )
			{
				auto list_ctrl = PageAccount_List::GetInstance();
				if (list_ctrl)
					list_ctrl->SaveEpToTheFile();
				//重启系统
				RestartSystem();
			}
			GetMyApp().last_time_12runconsole_ = DateTimeLocal();
		}
		else
			GetMyApp().last_time_12runconsole_ = DateTimeLocal();
	});
	VMP_END;
	return 0;
}

CTabOption::CTabOption() : Server(P_Port_Game)
{
	memset(table_pages_, 0, sizeof(table_pages_));
	login_succeed_ = false;
	io_connects_iter_ = CreateIoConnectIterPtr();
	assert(io_connects_iter_);
}

CTabOption::~CTabOption()
{
	for ( auto i = 0;i != _countof(table_pages_); ++i )
	{
		delete table_pages_[i];
	}
}

void CTabOption::OnSize( UINT nType, int cx, int cy )
{
	__super::OnSize(nType, cx, cy);
	
	if (nType != SIZE_MINIMIZED)
	{
		CRect rect;
		GetItemRect(0, rect);
		const auto kTop = rect.top + rect.Height();
		const auto kSizeY = cy - kTop;
		for ( auto i = 0; i != _countof(table_pages_); ++i )
		{
			if (table_pages_[i])
			{
				table_pages_[i]->SetWindowPos(NULL, 0, 
					kTop, cx, kSizeY, 0);
			}
		}
	}
}

Session* CTabOption::CreateSession()
{
	return new FuncObj_NormalS(*this);
}

PageAccount& CTabOption::GetPageAccount()
{
	return *P_CAST<PageAccount*>(table_pages_[0]);
}

bool CTabOption::IsLoginSucceed() const
{
	return login_succeed_;
}

int CTabOption::SetLoginSucceed( bool succeed )
{
	VMP_BEGIN_EX;
	login_succeed_ = succeed;
	auto tmp = &succeed;

	if ( succeed && OpenCheckLpk(nullptr) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "lpk开启验证";
		//检测线程
		/*SetIoTimer(2 * 60 * 1000, []( IoTimer* timer ){
			VMP_BEGIN_EX;
			auto check_thread = g_theCheckLpk.GetCheckThreadHandle();
			bool is_err = false;
			if ( !check_thread )
			{
				assert(false);
				throw CmnExitIoThreadException("cte");
			}
			DWORD thread_exit_code = 0;
			if ( !GetExitCodeThread(check_thread, &thread_exit_code) )
			{
				assert(false);
				throw CmnExitIoThreadException("cte1");
			}
			if ( 0 != thread_exit_code && STILL_ACTIVE != thread_exit_code )
			{
				assert(false);
				throw CmnExitIoThreadException("cte2");
				return;
			}
			timer->Continue();
			VMP_END;
		});*/
	}

	/*if (succeed)
	{
		ConnectCoordinate();
	}*/
	VMP_END;
	return (int)tmp;
}

void CTabOption::SetUserEndTime( const Poco::Timestamp& timestamp )
{
	user_end_time_ = timestamp;
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "set end date time" << Poco::DateTimeFormatter::format(user_end_time_, Poco::DateTimeFormat::SORTABLE_FORMAT);
}

void CTabOption::SetUserEndTime( const DateTimeLocal& end_date_time )
{
	user_end_time_ = end_date_time;
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "set end date time" << Poco::DateTimeFormatter::format(user_end_time_, Poco::DateTimeFormat::SORTABLE_FORMAT);
}

void CTabOption::ClearLoginInfo()
{
	VMP_BEGIN_EX;
	auto& io_s = GetIoService();
	io_s.post([](){
		auto tab_option = CTabOption::GetInstance();
		if (tab_option)
		{
			tab_option->SetLoginSucceed(false);
		}
	});
	io_s.post([](){
		auto tab_option = CTabOption::GetInstance();
		if (tab_option)
		{
			tab_option->SetUserEndTime(DateTimeLocal(1985, 9, 9));
		}
	});
	io_s.post([](){
		auto ctrl_list = PageAccount_List::GetInstance();
		if (ctrl_list)
			ctrl_list->OnCloseAllProcess();
	});
	VMP_END;
}

const DateTimeLocal& CTabOption::GetEndDateTime() const
{
	return user_end_time_;
}

const CTabOption::AddrDatasT& CTabOption::GetAddrDatas() const
{
	return addr_datas_;
}

void CTabOption::AddAddrData( DWORD addr_data )
{
	addr_datas_.push_back(addr_data);
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "add addr data->" << addr_data;
}

void CTabOption::ConnectCoordinate()
{
	VMP_BEGIN_EX;
	auto page_ac = PageAccount::GetInstance();
	if ( !page_ac )
		return;
	const auto& kDstIp = page_ac->GetStoredIp();
	auto coor = CoordinateC_Normal::GetInstance();
	if (coor)
	{
		const auto& str_ip = coor->socket().remote_endpoint().address().to_string();
		if ( str_ip != kDstIp )
		{
			coor->Disconnect();
		}
		else
		{
			return;
		}
	}
	
	GetIoService().post([kDstIp](){
		boost::shared_ptr<CoordinateC> coor_ptr(new CoordinateC_Normal(kDstIp));
		coor_ptr->ConnectAsync();
	});
	VMP_END;
}

void CTabOption::CheckDebugger()
{
	VMP_BEGIN;
	if (VMP_IS_DEBUGGER())
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "检测到测试器";
		SetIoTimer(49 * 1000, []( IoTimer* timer ){
			assert(timer);
			VMP_BEGIN;
			throw CmnExitIoThreadException("cde");
			VMP_END;
		});
	}
	VMP_END;
}

void CTabOption::CheckCrcValid()
{
	VMP_BEGIN;
	if ( !VMP_CRC_VALID() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "CRC效验失败";
		SetIoTimer(51 * 1000, []( IoTimer* timer ){
			assert(timer);
			VMP_BEGIN;
			throw CmnExitIoThreadException("ccve");
			VMP_END;
		});
	}
	VMP_END;
}

bool CTabOption::OnConnected( IoConnectBase* connect )
{
	VMP_BEGIN;
	if (login_succeed_)
	{
		/*SetIoTimer(5000, [=]( std::size_t ){
			auto list_ctrl = PageAccount_List::GetInstance();
			if ( !list_ctrl )
				goto LABLE_ERR;
			if ( list_ctrl->FindItemByFuncObj(*session.get()) < 0 )
				goto LABLE_ERR;
			return / *success* /;
LABLE_ERR:
			session->Close();
		}, 1);*/
	}
	else
	{
		return false;
	}
	VMP_END;
	return true;
}

void CTabOption::OnDisconnect( IoConnectBase* connect )
{
	__super::OnDisconnect(connect);
}

CoorTrans::TrackIterPtrT CTabOption::MakeTransTrackIterPtr()
{
	return MakeWrapperIterator<CoorTrans::TrackTraits>(io_connects_iter_, []( IoConnectBase* io_connect ) -> CoorTrans*{
		assert(io_connect);
		return &PointerCast<FuncObj_NormalS>(io_connect)->GetCoorTrans();
	});
}

//////////////////////////////////////////////////////////////////////////