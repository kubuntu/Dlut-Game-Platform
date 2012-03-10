/*!
	\mainpage DGP大工游戏平台开发手册

	\section introduction 概述
	DGP大工游戏平台仅支持CS模式的应用。因此您需要完成一个服务器端和一个客户端。\n

	如果您希望与平台的主服务器通信并测试您的游戏是否能在平台上正常运行，您需要向MainServer的运维者索要以下信息：
	- MainServer的地址和端口。
	- 一个具有GAMESERVERRUNNER权限的用户的用户名和密码。
	- 申请一个游戏ID，注册游戏名，并保证您的用户对此游戏的游戏信息拥有写权限。

	\section server 服务器端

	为了明确概念，我们将DGP的服务器称为MainServer，游戏的服务器称为GameServer。\n
	
	游戏服务器端启动后，需要进行以下几个步骤：
	-# 连接MainServer并登录。
	-# 上传游戏信息和GameServer的服务器信息。

	如果您使用C++和Qt来开发游戏的服务器端，DGP提供了DGP_API，您可以直接
	-# 调用类 JRequestLogin 的 login() 方法来登录。
	-# 使用类 JUploadGameInfo 上传游戏信息
	-# 使用类 JUploadServerInfo 上传 GameServer 的服务器信息 \n
	具体例子可以参见 JGameServerStartup 类的startup()方法的源码。

	或者更简单地，使用 JGameServerStartup 类完成以上全部过程。

	如果您使用其它语言，您需要了解底层的socket通信协议。\n
	目前，底层通信协议文档尚未完成。

	\section client 客户端
	为了明确概念，我们将DGP的客户端称为MainClient，游戏的客户端称为GameClient。\n
	GameClient由MainClient通过系统调用启动，并传入命令行参数。例如：
	- C++可以通过main()函数的参数（argc，argv）获得它们。 \n
	各个参数的含义
	- 0:GameClient的路径名。
	- 1:启动此游戏的用户的UserId。
	- 2:启动此游戏的用户的LoginHashCode。
	- 3:MainServer的地址。
	- 4:MainServer的端口。
	- 5:GameServer的地址。
	- 6:GameServer的端口。 \n
	如果您使用C++和Qt来开发游戏的服务器端，可以直接使用 JGameClientArgumentAnalyser 类完成命令行参数分析。
 */
