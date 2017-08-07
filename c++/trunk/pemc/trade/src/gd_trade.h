﻿#ifndef _GD_TRADE_H_251C4864_AB08_44DE_9EFE_B2399A409436_
#define _GD_TRADE_H_251C4864_AB08_44DE_9EFE_B2399A409436_

#include <time.h>
#include <map>
#include <vector>

/* trade sdk include*/
#include <TradeInterface.h>
#include <AppLog.h>
#include <QuoteServiceInit.h>
#include <Client.h>
#include <TQuoteEvent.h>
#include <TLoginEvent.h>
#include <TOpenMarketOrderEvent.h>
#include <TCloseMarketOrderEvent.h>
#include <TOpenLimitOrderEvent.h>
#include <TLimitClosePositionEvent.h>
#include <TCustmTradeReportClosePositionQueryEvent.h>
#include <TCustmTradeReportHoldPositionQueryEvent.h>
#include <TCustmTradeReportLimitOrderQueryEvent.h>
#include <TCustomerSelfFundFlowQueryEvent.h>
#include <TCustomerAllowLoginEvent.h>
#include <TRevokeLimitOrderEvent.h>
#include <TSysBulletin.h>
#include <TSysBulletinLimitCloseEvent.h>
#include <TSysBulletinLiquidationEvent.h>
#include <TDisConnectEvent.h>
#include <TMoneyInOutEvent.h>
#include <TMoneyQueryEvent.h>
#include <TPwdModifyEvent.h>
#include <TSignResultNotifyQueryEvent.h>
#include <TPayForwardEvent.h>
#include <TOpenDeliveryOrderEvent.h>
#include <jsoncpp/json.h>
#include <boost/unordered_map.hpp>
#include "proc_task.h"

#include "xn_mutex.h"
#include "struct.h"


#define Event_Ret_Success 99999
#define Event_Ret_DROPUSER 4006
#define Event_Ret_LOGACCERR 4001
#define Order_Ret_Success 0
#define TS_1970_TO_1900  2208988800

using namespace std;
using namespace TradeAPI;


class gd_trade_callback
{
public:
	virtual void on_callback_task(boost::shared_ptr<proc_task>&) = 0;
};


/* 广贵中盘交易类 */
class gd_trade : public Client
{
public:
	gd_trade(gd_trade_callback* callback);
	~gd_trade();

public:
	/***************************************************************************************************************************/
	//初始化类
	//返回值：（_2）_mutex初始化失败，0_interface不为空
	/***************************************************************************************************************************/
	int init();
	/***************************************************************************************************************************/
	//释放类中资源
	/***************************************************************************************************************************/
	int release();
	/***************************************************************************************************************************/
	//登录
	/***************************************************************************************************************************/
	int login(const std::string& user_name, const std::string& password, std::string &sid);
	/***************************************************************************************************************************/
	//更新登录密码
	/***************************************************************************************************************************/
	int login_pwd_upd(const std::string& old_pwd, const std::string&  new_pwd, int market_type, std::string &sid);
	/***************************************************************************************************************************/
	//更新资金密码
	/***************************************************************************************************************************/
	int fund_pwd_upd(const std::string& old_pwd, const std::string& new_pwd, std::string &sid);
	/***************************************************************************************************************************/
	//登出
	/***************************************************************************************************************************/
	int logout();
	/***************************************************************************************************************************/
	//4.7.15	修改或查询客户是否可以登录
	/***************************************************************************************************************************/
	int request_customer_allow_login(AllowLoginParam& param, std::string &sid);
	/***************************************************************************************************************************/
	//获取用户账户信息
	/***************************************************************************************************************************/
	int get_account_info(AccountInfo& account);
	/***************************************************************************************************************************/
	//4.7.25	获取市场开休市状态
	/***************************************************************************************************************************/
	int get_market_status();
	/***************************************************************************************************************************/
	//4.7.30	根据商品ID，获取其市价建仓的配置信息
	/***************************************************************************************************************************/
	int get_open_market_order_conf(int commodity_id, OpenMarketOrderConf &conf);
	/***************************************************************************************************************************/
	//4.7.32	根据商品ID，获取其市价平仓的配置信息
	/***************************************************************************************************************************/
	int get_close_market_order_conf(int commodity_id, CloseMarketOrderConf &conf);
	/***************************************************************************************************************************/
	//4.7.4	限价建仓接口
	/***************************************************************************************************************************/
	int get_open_limit_order_conf(int commodity_id, OpenLimitOrderConf &conf);
	/***************************************************************************************************************************/
	//
	/***************************************************************************************************************************/
	int get_limit_close_position_conf(int commodity_id, LimitClosePositionConf &conf);
	/***************************************************************************************************************************/
	//获取交割单信息
	/***************************************************************************************************************************/
	int get_open_delivery_order_conf(int commodity_id, const double total_weight, const double hold_price, OpenDeliveryOderConf &conf);
	/***************************************************************************************************************************/
	//获取单商品行情
	/***************************************************************************************************************************/
	int query_commodity_quote_by_id(int commodity_id, RealTimeQuote &quote);
	/***************************************************************************************************************************/
	//根据持仓单ID获取其详情
	/***************************************************************************************************************************/
	int query_hold_position_by_id(long long hold_position_id, HoldPositionInfo& hold_position);
	/***************************************************************************************************************************/
	//根据限价单ID获取其详情
	/***************************************************************************************************************************/
	int query_limit_order_by_id(long long limit_order_id, LimitOrderInfo& limit_order);
	/***************************************************************************************************************************/
	//根据平仓单ID获取其详情
	/***************************************************************************************************************************/
	int query_close_position_by_id(long long close_position_id, ClosePositionInfo& close_position);
	/***************************************************************************************************************************/
	//根据持仓汇总单ID和方向，获取其详情
	/***************************************************************************************************************************/
	int query_hold_position_total_by_commodity_id(int commodity_id, const int open_director, HoldPositionTotalInfo& total);
	/***************************************************************************************************************************/
	//根据持仓汇总单方向，获取各单详情s
	/***************************************************************************************************************************/
	int query_hold_position_total_by_director(int open_director, std::vector<HoldPositionTotalInfo> &total);
	/***************************************************************************************************************************/
	// 商品行情
	/***************************************************************************************************************************/
	int request_quote(vector<CommodityInfo> &vCommodity);
	/***************************************************************************************************************************/
	//持仓单
	/***************************************************************************************************************************/
	int request_hold_position(vector<HoldPositionInfo>& vTotal);
	/***************************************************************************************************************************/
	//持仓汇总
	/***************************************************************************************************************************/
	int request_hold_position_total(vector<HoldPositionTotalInfo>& vTotal);
	/***************************************************************************************************************************/
	//限价单
	/***************************************************************************************************************************/
	int request_limit_orders(vector<LimitOrderInfo>& vHoldPosition);
	/***************************************************************************************************************************/
	//平仓单
	/***************************************************************************************************************************/
	int request_close_orders(vector<ClosePositionInfo>& vLimitOrder);
	
	/***************************************************************************************************************************/
	//交割单
	/***************************************************************************************************************************/
	int request_delivery_order(vector<DeliveryOrderInfo>& vDeliveryOrder);
	/***************************************************************************************************************************/
	//市价单建仓
	/***************************************************************************************************************************/
	int request_open_market_order(OpenMarketOrderParam &order, std::string& sid);
	/***************************************************************************************************************************/
	//市价单平仓
	/***************************************************************************************************************************/
	int request_close_market_order(CloseMarketOrderParam &order, std::string& sid);
	/***************************************************************************************************************************/
	// 限价单建仓
	/***************************************************************************************************************************/
	int request_open_limit_order(OpenLimitOrderParam &order, std::string& sid);
	/***************************************************************************************************************************/
	// 限价单平仓
	/***************************************************************************************************************************/
	int request_limit_close_position(CloseLimitOrderParam &order, std::string& sid);
	/***************************************************************************************************************************/
	//根据持仓汇总单方向，获取各单详情
	/***************************************************************************************************************************/
	int request_custm_trade_report_close_position(ReportQueryParam &param, std::string& sid);
	/***************************************************************************************************************************/
	//根据持仓汇总单方向，获取各单详情
	/***************************************************************************************************************************/
	int request_custm_trade_report_hold_position(ReportQueryParam &param, std::string& sid);
	/***************************************************************************************************************************/
	//根据持仓汇总单方向，获取各单详情
	/***************************************************************************************************************************/
	int request_custm_trade_report_limit_order(ReportQueryParam &param, std::string& sid);
	/***************************************************************************************************************************/
	//根据持仓汇总单方向，获取各单详情
	/***************************************************************************************************************************/
	int request_customer_self_fund_flow_query(FundFlowQueryParam &param, std::string& sid);
	/***************************************************************************************************************************/
	// 批量平仓
	/***************************************************************************************************************************/
	int request_close_market_order_many(CloseMarketOrderManyParam &order, std::string& sid);
	/***************************************************************************************************************************/
	//  撤销订单
	/***************************************************************************************************************************/
	int request_limit_revoke(LimitRevokeParam &order, std::string& sid);
	/***************************************************************************************************************************/
	// 出入金
	/***************************************************************************************************************************/
	int request_money_in_out(MoneyInOutParam &order, std::string& sid);
	/***************************************************************************************************************************/
	// 查询银行资金
	/***************************************************************************************************************************/
	int request_money_query(std::string& sid);
	/***************************************************************************************************************************/
	// 交割单
	/***************************************************************************************************************************/
	int request_open_delivery_order(OpenDeliveryOrderParam &order, std::string& sid);
	/***************************************************************************************************************************/
	//签约结果通知
	/***************************************************************************************************************************/
	int request_sign_result_notify_query(SignResultNotifyQueryParam &param, std::string& sid);
	/***************************************************************************************************************************/
	//支付推进
	/***************************************************************************************************************************/
	int request_pay_forward(PayForwardParam &param, std::string& sid);
	/***************************************************************************************************************************
	//交易接口
	****************************************************************************************************************************/
	int get_curr_status();
	/***************************************************************************************************************************
	//心跳
	****************************************************************************************************************************/
	void start_heart_beat();
	/***************************************************************************************************************************
	//判断是否有效
	****************************************************************************************************************************/
	bool check_active();
public:
	/***************************************************************************************************************************
	//获取登录用户名
	****************************************************************************************************************************/
	const char* get_login_accout() const { return _login_accout.c_str(); }
	/***************************************************************************************************************************
	//获取回调回复
	****************************************************************************************************************************/
	bool get_callback_response(const std::string& type, const std::string& sid, Json::Value& response);
	/***************************************************************************************************************************
	//回调任务
	****************************************************************************************************************************/
	void on_callback_task(const callback_task* ptr_request);
private:
	/***************************************************************************************************************************
	//交易接口
	****************************************************************************************************************************/
	int init_network();
	/***************************************************************************************************************************
	//交易接口
	****************************************************************************************************************************/
	void procTradeEvent(const TradeEvent *pEvent);
	/***************************************************************************************************************************
	//交易接口
	****************************************************************************************************************************/
	int time_to_str(const long long second, char* dest, int len);
	/***************************************************************************************************************************
	//设置登出状态
	****************************************************************************************************************************/
	void set_logout_status();
	/***************************************************************************************************************************
	//设置登录状态
	****************************************************************************************************************************/
	void set_login_status();
private:
	/***************************************************************************************************************************
	//交易接口
	****************************************************************************************************************************/
	TradeInterface *_ptr_interface;
	/***************************************************************************************************************************
	//资金状态
	****************************************************************************************************************************/
	//int	_money_status;
	/***************************************************************************************************************************
	//登录状态， 0 登录 1登出
	****************************************************************************************************************************/
	int	_login_status;
	/***************************************************************************************************************************
	//登录用户名
	****************************************************************************************************************************/
	xn_mutex _mutex;
	/***************************************************************************************************************************
	//最后登出时间
	****************************************************************************************************************************/
	time_t _last_logout_status_time;
	static const int _out_of_time_interval = 60;
	/***************************************************************************************************************************
	//登录用户名
	****************************************************************************************************************************/
	std::string _login_accout;
	std::string _login_passwd;
	std::string _token;
	/***************************************************************************************************************************
	//回调
	****************************************************************************************************************************/
	gd_trade_callback* _ptr_callback;
	/***************************************************************************************************************************
	//事件回复队列， 轮询查找对应的回复
	****************************************************************************************************************************/
	boost::unordered_map<std::string, callback_response> _callback_result;
};

/***************************************************************************************************************************
//交易接口
****************************************************************************************************************************/
std::string getime();
/***************************************************************************************************************************
//交易接口
****************************************************************************************************************************/
int register_my_signal();
/***************************************************************************************************************************
//交易接口
****************************************************************************************************************************/
int signal_task();


#endif