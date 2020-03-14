        消菌杀毒机器人（Sterilizing Robot）

    1、采用激光雷达实现无轨道、无人操作的方式，进行自主导航、巡逻等任务。
    2、通过4G或局域网络实现远程的人工操作
    3、可通过4G或Internet网络实现数据的搜集以及统计。
    4、主要的组成部分为 远程服务端 + 本地客户端（PC + Android）+ AGV

        远程服务端(Robot Service)(Qt5 + SQL Server)
    1、当有设备接入服务端时向设备发送握手识别请求
    2、客户端接入成功后向服务端申请订阅AGV发布的信息，服务端将两者接在一起
    3、AGV接入成功后向服务端发布图像、位置、状态等信息。
    4、每一个客户端和AGV都应具备一个唯一的标识，用以保证设备在服务端内的唯一性（UUID）
    5、服务端记录客户端、AGV的接入时间、请求、反馈

        机器人远程控制程序(Robot Remote Control)( PC端 Qt5 + C++)
    1、可以接入手柄用于控制机器人的移动等功能
    2、可以通过键盘按键控制机器人的移动等功能
    3、用户可以通过设置调整按键对应的功能
    4、手柄左摇杆控制机器人的移动，右摇杆控制摄像头的移动。十字键调整机器人的速度，其中上下调整移动速度，左右调整转动速度。LB控制辅助灯的开关，RB控制喷洒的开关。LT、RT、X、Y、A、B、Back、Start按钮暂时没有功能。

        通信流程
    1、客户端启动->向服务端发送连接请求->服务端反馈至客户端->向服务端请求AGV数据->服务端反馈AGV的连接状态->服务端反馈AGV的数据
    2、AGV启动->向服务端发送连接请求->服务端反馈至AGV->向服务端发送AGV数据

        通信格式
    JSON指令集，每条JSON指令用‘|’分隔。
    指令集格式
    {//根括号
        “From”:"uuid",      // 发送方uuid
        "to":"uuid",        // 接收方uuid
        “Date”:"",          // 指令的发送时间，可用于时间同步
        “Cmd”:{             // 指令的内容
        },           
        “Result”:{          // 指令的返回值

        }         
    }

    指令内容
    1、握手指令
    服务端发送至客户端，要求客户端表明自身的身份。指令持续发送30s,每隔1s发送1次，当30s后客户端仍未表明身份，则释放该客户端资源。
    {
        "From":"",     
        "to":"",
        "Date":"2020/01/02 11:11:11",
        "Cmd":{
            "Hand":0
        }
    }
    客户端收到指令后回复服务端自身的身份
   {
        "From":"1001",     
        "to":"",
        "Date":"2020/01/02 11:11:11",
        "Cmd":{
            "Hand":0
        }
    }
    服务端收到客户端表明的身份后返回指令表示收到了客户端的身份信息
   {
        "From":"",     
        "to":"1001",
        "Date":"2020/01/02 11:11:11",
        "Cmd":{
            "Hand":0
        }
    }

    2、订阅指令
    客户端向服务端申请订阅指令客户端发送来的信息
    服务端将订阅的客户端与被订阅的客户端信息通道连接，实现设备之间信息的透传。
    {   
        “From”:"2",     
        "to":"",
        "Date":"2020/01/02 11:11:14"
        "Cmd":{
            "Take":["uuid","uuid","uuid","uuid"]
        }
    }
    服务端收到订阅信息后查找指定的客户端并进行绑定，然后返回绑定后的结果至客户端
     {   
        “From”:"",     
        "to":"2",
        "Date":"2020/01/02 11:11:14"
        "Cmd":{
            "Take":["uuid","uuid","uuid","uuid"]
        }
        "Result":{
            “uuid”:"true",
            "uuid":"false",
        }
    }
    服务端会持续的监控客户端的状态，当状态发生改变时会将新的状态信息提供给订阅的客户端

    3、取消订阅指令
    客户端向服务端申请取消订阅指令客户端发送来的信息
    {   
        “From”:"2",     
        "to":"",
        "Date":"2020/01/02 11:11:14"
        "Cmd":{
            "Remove":["uuid","uuid","uuid","uuid"]
        }
    }
    取消订阅成功后，会返回结果至客户端
    {   
        “From”:"",     
        "to":"2",
        "Date":"2020/01/02 11:11:14"
        "Cmd":{
            "Remove":["uuid","uuid","uuid","uuid"]
        }
        "Result":{
            “uuid”:"true",
            "uuid":"false",
        }
    }

    4、数据更新指令
    5、远程控制指令
    {
        “From”:"1",
        "To":"2",
        "Date":"2020/01/02 11:11:14",
        "Cmd":{
            "Control":{
                “Base”:"MoveOn",        // MoveOn 底盘向前移动 MoveBack 底盘后退 TurnLeft 左转 TurnRight 右转
                "LSpeed":"",            // 移动时的线速度百分比，eg:10 代表以10%的速度移动
                "ASpeed":"",            // 转向时的角速度百分比，同上
                "Eyes":"LookUp",        // LookUp 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
                "Light":true,     // 辅助灯开关 true为开，false为关
                "Spray":false,          // 喷雾器开关，同上
            }
        }
    }

    AGV返回
    {
        “From”:"1",
        "To":"2",
        "Date":"2020/01/02 11:11:14",
        "Cmd":{
            "Control":{
                “Base”:"MoveOn",        // MoveOn 底盘向前移动 MoveBack 底盘后退 TurnLeft 左转 TurnRight 右转
                "LSpeed":"",            // 移动时的线速度百分比，eg:10 代表以10%的速度移动
                "ASpeed":"",            // 转向时的角速度百分比，同上
                "Eyes":"LookUp",        // LookUp 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
                "LightSwitch":true,     // 辅助灯开关 true为开，false为关
                "Spray":false,          // 喷雾器开关，同上
            }
        }
        “Result”:
        {
            "Control":{
                “Base”:true,            // 执行成功返回true,否则返回false
                "LSpeed":false,
                "ASpeed":false,
                "Eyes":true,
                "LightSwitch":false,
                "Spray":false,
            }
        }
    }
    6、心跳指令
    用以确定通信两端信息通道的报文
    {
        “From”:"2",     
        "to":"",
        "Date":"2020/01/02 11:11:14"
        "Cmd":{
            "Haert":NULL
        }
    }
	
	7、摄像头截图返回（实时）
	 {
        “From”:"1001",     
        "To":"",
        "Date":"2020/01/02 11:11:14"
        "Cmd":{
            "Camera":"(摄像头截图base64编码)"
        }
    }
	8、设备状态返回（实时）
	{
		“From”:"1001",     
		"To":"",
		"Date":"2020/01/02 11:11:14"
		"Cmd":{
			"Device":{
				"Base": "MoveOn",    	// MoveOn 底盘向前移动 MoveBack 底盘后退 TurnLeft 左转 TurnRight 右转（最后一次接收的值）
				"LSpeed":1,      		// 移动时的线速度百分比（最后一次接收的值）
                "ASpeed":1,      		// 转向时的角速度百分比（最后一次接收的值）
				"Spray":true,     		// 喷雾器开关 true为开，false为关
				"Electric":0,			// 电量 0-100
				“Water”:0				// 水量 0-100
			}
		}
    }
	
	#工控机与底盘通信报文
	
	1、工控机发送给底盘
	{
		"Mov":{				// 移动控制
			"SPeedL":00,	// 左轮速度0-100
			"SpeedR":00	 	// 右轮速度0-100
		},	
		“Ctrl":{			// 设备控制
			"Spray":false		// 喷雾器控制 true为开，false为关
		}	
	}
	2、底盘上传给工控机
	{
		“State”:{		// 底盘状态		
			"Spray":false	 // 喷雾器开关状态 true为开，false为关
		},	
		"Data":{		// 底盘数据
			"SPeedL":100,
			"SpeedR":10,
			“EcodeL”:00000，		// 左轮编码器值
			“EcodeR”:00000，		// 右轮编码器值
			"Electric":0,			// 电量0-100%
			“Water”:0,				// 水量0-100%
			"IMU":{			// 姿态传感器数据
				"GryX":0,		// 陀螺仪X轴数据
				“GryY”:0,		// 陀螺仪Y轴数据
				“GryZ”:0,		// 陀螺仪Z轴数据
				"AccX":0,		// 加速度计X轴数据
				"AccY":0,		// 加速度计Y轴数据
				"AccZ":0,		// 加速度计Z轴数据
				"MagX":0,		// 磁力计X轴数据
				"MagY":0,		// 磁力计Y轴数据
				"MagZ":0		// 磁力计Z轴数据
			}
		}
	}
	
	
	
	
	
	
	