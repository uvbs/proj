

--在这里修改球员ID和强化等级
局部变量 球员ID = 88193555
局部变量 球员强化等级 = 1


--[[
这个命令根据 会扫描 购买最低价格 到 购买最高价格 之间球员，每次购买的价格依次是上一次购买价格+递增价格
比如 扫隐藏卡(1, 1, 10, 30, 10)，表示扫 球员ID为1，强化等级为1的球员，购买价格依次是10、20、30。若购买价格为20能够购买成功，则命令返回20，并输出价格信息到控制台的 输出结果 栏目下。
这个命令需要配合点下界面，当控制台提示：扫卡出错,请点下界面。你需要点下界面，然后再执行这个脚本。但是如果这个命令放到其他脚本中去，则不需要配置点界面了。
第一个参数是球员ID，球员ID的获取方式请参考 以指定的价格拍卖一些指定的球员 命令
第二个参数是球员强化等级
第三个参数是购买最低价格
第四个参数是购买最高价格
第五个参数是递增价格
]]
--[[
扫隐藏卡(1, 1, 10, 30, 10)，会以10、20、30的价格购买球员，有可能在以20的价格购买球员失败，并且控制台的输出结果提示：扫卡出错,请点下界面，此时出错的价格：20，
那么建议你把购买最低价格改为20，即：扫隐藏卡(1, 1, 20, 30, 10)，因为这样更效率些，点击界面，再一次执行脚本的时候，便只会扫20、30的价格，而不会再扫10的价格了。
]]
局部变量 有效的卡价 = 扫隐藏卡(球员ID, 球员强化等级, 500, 2000, 100)

如果 有效的卡价 > 0 那么
	--[[
	按指定的价格扫隐藏卡(1, 2, 30, 10) 表示 球员ID为1，球员强化等级为2的球员，以30的价格购买10个。
	第一个参数是球员ID，球员ID的获取方式请参考 以指定的价格拍卖一些指定的球员 命令
	第二个参数是球员强化等级
	第三个参数是购买价格
	第四个参数是购买个数
	]]
	按指定的价格扫隐藏卡(球员ID, 球员强化等级, 有效的卡价, 5)
结束
