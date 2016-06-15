#ifndef _scFLCmdHandler_h_
#define _scFLCmdHandler_h_

#include "Fir.h"
#include "proto/fl_scene_protocol.pb.h"

class scFLCmdHandler : public Singleton<scFLCmdHandler>
{
	friend class Singleton<scFLCmdHandler>;
	public:

		scFLCmdHandler() {};
		~scFLCmdHandler() {};

		void Initialize();

		bool handleFLCmd(const std::string& content);
		bool handleTestReturn(const std::string& cmd_content);

		void testMsg();

		template<typename T>
		bool sendCmdToFL(fl_scene::MSG_ID msgid, const T& msg)
		{
			std::string content;
			if (!msg.SerializeToString(&content))
			{
				return false;
			}

			fl_scene::PbMessage send;
			send.set_msgid(msgid);
			send.set_content(content);

			std::string send_content;
			if (!send.SerializeToString(&send_content))
			{
				return false;
			}

			return sendCmdToFL(send_content);
		}

		bool sendCmdToFL(const void *pstrCmd, const int nCmdLen);
		bool sendCmdToFL(const std::string& content);
	protected:
		typedef std::function<bool (const std::string&)> HANDLE_FUNC;
		typedef std::map<fl_scene::MSG_ID, HANDLE_FUNC>      HANDLE_FUNC_MAP;
		HANDLE_FUNC_MAP   m_HandleFuncMap;  
		void __RegisterHandleFunc (fl_scene::MSG_ID msgid, HANDLE_FUNC func);
};

#endif

