
定义函数 做_初始任务()
    等待可移动(60 * 3)

    局部变量 武器 = 查找最近的掉落物品()
    如果 武器 ~= 空 那么
        打开目标(武器)
    结束

    局部变量 怪物 = 查找最近的目标("垂死的流放者")
    如果 怪物 ~= 空 那么
        打开目标("垂死的流放者")
        关闭所有面板()
    结束
    延迟(3)
    如果 杀到杀死目标("西拉克") ~= 真 那么
        LogE("初始任务杀到杀死西拉克错误")
        返回 假
    结束
    返回 真
结束  

----------------------炙热盐沼-----------------------
定义函数 做_探索炙热盐沼(任务)
    如果 杀到指定地图(任务.地图名) ~= 真 那么
        LogE("做_探索炙热盐沼之杀到任务地图失败")
        返回 假
    结束
    如果 获得物品数量("雕纹: 菊纹") > 0 且 获得物品数量("雕纹: 孔螺") > 0 且 获得物品数量("雕纹: 长春花") > 0 那么
        杀到打开目标("刻着雕纹的奇怪墙壁")
    否则    
        杀到打开目标("恐喙鸟巢")
        拾取最近任务物品()
    结束
结束


------------------海妖之歌------------------
定义函数 做_击败海妖()
    如果 杀到指定地图("怨忿之窟深处") ~= 真 那么
        LogE("做_击败海妖之杀到目标地图失败")
        返回 假
    结束 
    如果 杀到房间("莫薇儿的巢穴") ~= 真 那么
        LogE("做_击败海妖之杀到房间失败：" .. "莫薇儿的巢穴")
    结束
    杀到目标("南部森林")
    延迟(2)
    局部变量 怪物 = 查找最近怪物("海妖莫薇儿")
    如果 怪物 ~= 空 那么
        如果 杀到杀死目标("海妖莫薇儿") ~= 真 那么
             LogE("做_击败海妖之杀死目标失败" .. "海妖莫薇儿")
        结束
        延迟(3)
    结束
    怪物  = 查找最近怪物("魔语之灵莫薇儿")
    如果 怪物 ~= 空 那么
        如果 杀到杀死目标("魔语之灵莫薇儿") ~= 真 那么
             LogE("做_击败海妖之杀死目标失败" .. "魔语之灵莫薇儿")
        结束
    结束
    返回 真
结束

------------------------迷失的爱情-----------------
定义函数 做_击败守卫并挽救女孩(任务)
    如果 杀到指定地图(任务.地图名) ~= 真  那么
        LogE("做_击败守卫并挽救女孩之 通用任务_杀到打开任务地图 失败")
        返回 假
    结束
    如果 杀到目标("卡尔莉萨") ~= 真  那么
        LogE("做_击败守卫并挽救女孩之 通用任务_杀到目标(卡尔莉萨) 失败")
        返回 假
    结束
    局部变量 NPC = 查找最近的目标("卡尔莉萨")
    如果 NPC == 空 那么 
        LogE("做_击败守卫并挽救女孩之没有找到npc 卡尔莉萨")
        返回 假
    结束  
    如果 NPC:可访问() ~= 真 那么
        如果 杀到杀死目标("军队队长") ~= 真 那么
             LogE("做_击败守卫并挽救女孩之杀死军队队长失败")
             返回 假
        结束
    结束
    如果 杀到打开目标("卡尔莉萨") ~= 真 那么
        LogE("通用任务_与卡尔莉萨交谈之对话NPC 失败")
        返回 假
    结束          
    如果 对话NPC("继续") ~= 真 那么
        LogE("通用任务_与卡尔莉萨交谈之对话NPC 失败")
        返回 假
    结束
    返回 真
结束

---------------------永恒梦魇-------------
定义函数 做_找到进入黑灵核心的路(任务)
    如果 杀到指定地图(任务.地图名) ~= 真  那么
        LogE("做_找到进入黑灵核心的路之 通用任务_杀到打开任务地图 失败")
        返回 假
    结束
   如果 全图杀怪(真) ~=  真 那么
        LogE(" 做_找到进入黑灵核心的路 全图杀怪失败")
        使用传送卷轴到地图()
        设置重置地图(假)
        杀到指定地图("育灵之室")
        设置重置地图(真)
        返回 假    
   结束
   使用传送卷轴到地图()
   设置重置地图(假)
   杀到指定地图("育灵之室")
   设置重置地图(真)
    如果 杀到打开目标("派蒂") ~= 真  那么
        LogE("做_找到进入黑灵核心的路之 通用任务_杀到目标(派蒂) 失败")
        返回 假
    结束
    如果 对话NPC("派蒂","再会") ~= 真 那么
        LogE("做_找到进入黑灵核心的路之对话NPC 失败")
        返回 假
    结束
    返回 真
结束

定义函数 做_击败玛拉凯(任务)
    如果 杀到指定地图(任务.地图名) ~= 真  那么
        LogE("做_击败玛拉凯之 通用任务_杀到打开任务地图 失败")
        返回 假
    结束
    局部变量 目标 = 查找最近的目标("黑灵之心")
    如果 目标 == 空 那么
        如果 杀到杀死目标("梦魇玛拉凯") ~= 真 那么
            LogE("做_击败玛拉凯之杀到杀死梦魇玛拉凯错误")
            返回 假
        结束
    否则
        如果 杀到打开目标("黑灵之心") ~= 真 那么
            LogE("做_击败玛拉凯之对打开目标失败:黑灵之心")
            返回 假
        结束 
    结束 
    如果 杀到杀死目标("梦魇玛拉凯") ~= 真 那么
        LogE("做_击败玛拉凯之杀到杀死梦魇玛拉凯错误")
        返回 假
    结束
结束


定义函数 做_跟着柱子走()
    杀到目标("可移动柱子")
    杀着跟随可移动柱子()
结束

定义函数 做_通往第七章()
    如果 杀到房间("海王皇座") ~= 真 那么
        返回 假
    结束
    打开附近对象("威勒姆·罗斯")
    对话NPC("前往第7章")
    延迟(5)
结束


----------------试炼--------------------
定义函数 移动到目标打开(目标名字)
    移动到目标(目标名字)
    打开附近对象(目标名字)
结束

定义函数 杀到目标打开(目标名字)
      杀到指定位置(目标名字)
      打开附近对象(目标名字)
      返回 真
结束
局部变量 完成记录 = 0
定义函数 做_地图试炼()
    局部变量 当前地图 = 当前地图名字()
    如果 当前地图 == "The Crypt" 那么   --OK
        如果 完成记录 < 1 那么
            杀到目标打开("Trial of Ascendancy")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")
    否则如果 当前地图 == "禁灵之狱下层" 那么
        如果 完成记录 < 1 那么
            杀到目标打开("升华试炼")
            完成记录 = 完成记录 + 1
        结束
        如果 完成记录 < 2 那么
            移动到目标打开("把手")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")
    否则如果 当前地图 == "The Crypt Level 1" 那么  --OK
        如果 完成记录 < 1 那么
            杀到目标打开("Trial of Ascendancy")
            完成记录 = 完成记录 + 1
        结束
        如果 完成记录 < 2 那么
            杀到打开目标("Lever")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")  
    否则如果 当前地图 == "The Chamber of Sins Level 2" 那么   --OK
        如果 完成记录 < 1 那么
            杀到目标打开("Trial of Ascendancy")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")
    否则如果 当前地图 == "The Crematorium" 那么       --改后应该也OK
        如果 完成记录 < 1 那么
            杀到目标打开("Trial of Ascendancy")
            完成记录 = 完成记录 + 1
        结束
        如果 完成记录 < 2 那么
            移动到目标打开("Lever")
            完成记录 = 完成记录 + 1
        结束
        如果 完成记录 < 3 那么
            移动到目标打开("Lever")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")
    否则如果 当前地图 == "The Catacombs" 那么  --OK
        如果 完成记录 < 1 那么
            杀到目标打开("Trial of Ascendancy")
            完成记录 = 完成记录 + 1
        结束
        如果 完成记录 < 2 那么
            移动到目标打开("Lever")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")
    否则如果 当前地图 == "The Hedge Maze" 那么 
        如果 完成记录 < 1 那么
            杀到目标打开("Trial of Ascendancy")
            完成记录 = 完成记录 + 1
        结束
        杀到打开目标("Trial of Ascendancy Plaque")
    结束
    关闭所有面板()
    完成记录 = 0
    返回 真
结束

定义函数 做_完成迷宫(任务)
--    如果 杀到指定地图("Aspirants' Plaza") ~= 真 那么
--        LogE("做_完成迷宫之杀到迷宫地图失败")
--        返回 假
--    结束
--    如果 根据等级开启迷宫(33) ~= 真 那么
--        LogE("根据等级开启迷宫之失败")
--        关闭所有面板()
--        返回 假
--    结束
--    如果 杀到打开目标("Estate Path") ~= 真 那么
--        LogE("做_完成迷宫之杀到迷宫地图失败")
--        返回 假
--    结束
    如果 杀到杀死目标("ddd") ~= 真 那么
        LogE("迷宫地图试炼失败")
        返回 假
    结束
    返回 真
结束

定义函数 做_前往试炼(任务)
    如果 当前地图名字() == "萨恩营地" 那么
        打开目标("试炼盘")
        关闭所有面板()
        局部变量 地图信息 = 获得未完成试炼地图()
        局部变量 地图 = 地图信息["地图"]
        局部变量 难度 = 地图信息["难度"]
        如果 地图 == 空 那么
            LogE("当前等级难度的地图刷完了了----------------------")
            返回 真
        结束
        如果 杀到指定地图(地图,难度,真) ~= 真 那么
            LogE("前往试炼之杀到试炼地图失败:"..地图)
            返回 假
        结束
        返回 真
    否则 
        打开附近对象("Portal")
        杀到指定地图("The Sarn Encampment")
    结束
结束

定义函数 找到马雷格罗()
    局部变量 地图名字 = 当前地图名字()
    如果 地图名字 == "寂静陵墓" 那么
        使用传送卷轴到地图()
    结束
    如果 地图名字 ~= "罪孽之殿 1 层" 且 地图名字 ~= "马雷格罗的藏身处" 那么
        杀到指定地图("罪孽之殿 1 层")
    结束
    如果 地图名字 == "罪孽之殿 1 层" 那么
        如果 杀到目标("地图装置") ~= 真 那么
            返回 假
        结束
        开启地图装置("马雷格罗的地图")
        杀到指定地图("马雷格罗的藏身处")
    结束
    如果 地图名字 == "马雷格罗的藏身处" 那么
        如果 杀到房间("马雷格罗的工作间") ~= 真 那么
            LogE("杀到房间 马雷格罗的藏身处 失败")
        结束
        杀到打开目标("灾厄毒液")
    结束
结束

定义函数 做_找到马雷格罗()
    返回 执行并等待事件(找到马雷格罗, 处理事件, {"死亡复活前事件"})
结束

------------------------------------------------------------
定义函数 检查物品特殊处理(物品名)
    局部变量 物品数量 = 获得物品数量(物品名) 
    如果 物品数量 > 0 那么
        返回 真
    结束
    如果  物品名 == "愤怒之眼" 那么
        如果 在城镇() == 真 那么
            返回 真
        结束
        如果 杀到指定地图("冈姆的堡垒") ~= 真 那么
            LogE("检查物品特殊处理之杀到 冈姆的堡垒 失败")
            返回 假
        结束
        如果 杀到房间("熔岩之环") ~= 真 那么
            LogE("检查物品特殊处理之杀到房间 熔岩之环 失败")
            返回 假
        结束
        如果 杀到打开目标("愤怒之眼") ~= 真 那么
            LogE("检查物品特殊处理之杀到打开目标 愤怒之眼 失败")
            返回 假
        结束
   -- 否则 如果 

    结束
    返回 真
结束