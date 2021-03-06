/**
 * \file
 * \version  $Id: RecordTask.h 42 2013-04-10 07:33:59Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义读档连接任务
 *
 */

#ifndef _RecordTask_h_
#define _RecordTask_h_

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "RecordCommand.h"
#include "zDBConnPool.h"

class RecordUser;
/**
 * \brief 定义读档连接任务类
 *
 */
class RecordTask : public zTCPTask
{

	public:

		/**
		 * \brief 构造函数
		 * 因为档案数据已经压缩过，在通过底层传送的时候就不需要压缩了
		 * \param pool 所属连接池指针
		 * \param sock TCP/IP套接口
		 * \param addr 地址
		 */
		RecordTask(
				zTCPTaskPool *pool,
				const int sock,
				const struct sockaddr_in *addr = NULL) : zTCPTask(pool, sock, addr, false)
		{
			wdServerID = 0;
			wdServerType = UNKNOWNSERVER;
		}

		/**
		 * \brief 虚析构函数
		 *
		 */
		virtual ~RecordTask() {};

		int verifyConn();
		int recycleConn();
		bool msgParse(const CMD::t_NullCmd *, const unsigned int);

		/**
		 * \brief 获取服务器编号
		 *
		 * \return 服务器编号
		 */
		const WORD getID() const
		{
			return wdServerID;
		}

		/**
		 * \brief 获取服务器类型
		 *
		 * \return 服务器类型
		 */
		const WORD getType() const
		{
			return wdServerType;
		}

		bool uniqueAdd();
		bool uniqueRemove();

	private:

		WORD wdServerID;					/**< 服务器编号，一个区唯一的 */
		WORD wdServerType;					/**< 服务器类型 */

		bool verifyLogin(const CMD::RECORD::t_LoginRecord *ptCmd);
		
		bool msgParse_Gateway(const CMD::t_NullCmd *, const unsigned int);
		bool msgParse_Scene(const CMD::t_NullCmd *, const unsigned int);
		bool msgParse_Session(const CMD::t_NullCmd*, const unsigned int);
		bool msgParse_Super(const CMD::t_NullCmd*, const unsigned int);
		
		bool create_role(const CMD::RECORD::t_CreateChar_GateRecord* cmd);
		bool del_role(const CMD::RECORD::t_DelChar_GateRecord* cmd);
		
		//0成功 1失败
		DWORD create_role_inner(DWORD accountid, const char* nickname, WORD profession, const char* platform, DWORD& charid);
		bool reqGm(const CMD::RECORD::t_GmRequest_SessionRecord* cmd, const DWORD len);

		static const dbCol charbase_define[];
};

#endif

