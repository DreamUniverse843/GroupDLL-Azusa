// MiraiCP依赖文件(只需要引入这一个)
#define _CRT_SECURE_NO_WARNINGS //无视 MSVC 的不安全函数提示
#include <MiraiCP.hpp>
#include <fstream>
#include "windows.h"
#include "time.h"
#include "simpleINI.h"
using namespace MiraiCP;

const PluginConfig CPPPlugin::config{
        "cn.com.dreamcraft.group",          // 插件id
        "DreamCraft-QQGroup-Plugin",        // 插件名称
        "1.0.0",            // 插件版本
        "DreamUniverse843",        // 插件作者
        "Whatelse~",  // 可选：插件描述
        "2022-12-31"        // 可选：日期
};

CSimpleIniA RobotINI;//ini 文件操作对象
//常量，配置文件的绝对路径(相对路径会出问题)
const std::string iniPath = "C:\\MCSManager_v9.6.0_win_x64\\daemon\\data\\InstanceData\\bfcdb53587f7455d88c1801691ccd56a\\Mirai.ini";

void iniInitialize(std::string FilePath) //初始化配置文件存储
{
    RobotINI.SetUnicode(); // 默认使用 UTF-8 编码
    RobotINI.LoadFile(FilePath.c_str());
    RobotINI.SetValue("Initialize","True","1");
    RobotINI.SaveFile(FilePath.c_str());
    Logger::logger.info("[System]启动阶段读取 ini 文件请求成功。");
}

std::string iniQuery(std::string FilePath,std::string Section,std::string Name) //查询配置文件内的键值
{
    RobotINI.SetUnicode();
    RobotINI.LoadFile(FilePath.c_str());
    const char * ReturnValue = RobotINI.GetValue(Section.c_str(),Name.c_str(),"未找到");
    int ReturnCode = RobotINI.SaveFile(FilePath.c_str());
    if(ReturnCode < 0)
    {
        return "未找到";
    }
    else
    {
        return ReturnValue;
    }
}

void iniWrite(std::string FilePath,std::string Section,std::string Name,std::string Value)//向配置文件写入键值
{
    RobotINI.SetUnicode();
    RobotINI.LoadFile(FilePath.c_str());
    RobotINI.SetValue(Section.c_str(),Name.c_str(),Value.c_str());
    int ReturnCode = RobotINI.SaveFile(FilePath.c_str());
    if(ReturnCode < 0)
    {
        Logger::logger.error("[INISystem]文件写入出现问题。");
    }
}

// 插件实例
class Main : public CPPPlugin {
public:
  // 配置插件信息
  Main() : CPPPlugin() {}
  ~Main() override = default;

  // 入口函数
  void onEnable() override {
    // 请在此处监听
      Logger::logger.info("[Info]插件正在启动。如群内无法接收到机器人消息，则可能处于风控状态。");
      Event::registerEvent<BotOnlineEvent>([](BotOnlineEvent OnlineEvent) {
          Logger::logger.info("[Info]机器人已登录");
      });
      Event::registerEvent<GroupMessageEvent>([](GroupMessageEvent GroupMessage) {
          time_t now = time(0);
          tm *ltm = localtime(&now);
          int GetYear = 1900 + ltm->tm_year;
          int GetMonth = 1 + ltm->tm_mon;
          int GetDay = ltm->tm_mday;
          int GetHour = ltm->tm_hour;
          int GetMinute = ltm->tm_min;
          int GetSecond = ltm->tm_sec;
          if(GroupMessage.message.toMiraiCode() == ".reload")
          {

          }
      });
      Event::registerEvent<MemberJoinRequestEvent>([](MemberJoinRequestEvent JoinRequestEvent){

      });
      Event::registerEvent<MemberLeaveEvent>([](MemberLeaveEvent LeaveEvent){

      });
      Event::registerEvent<MemberJoinEvent>([](MemberJoinEvent JoinedEvent){

      });

  }

  // 退出函数
  void onDisable() override {
    /*插件结束前执行*/
    Logger::logger.info("[Info]插件正在关闭。");
  }
};

// 绑定当前插件实例
void MiraiCP::enrollPlugin() {
  MiraiCP::enrollPlugin(new Main);
}
