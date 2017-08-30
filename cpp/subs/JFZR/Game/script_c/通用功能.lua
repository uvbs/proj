定义函数 通用打完一个房间后的回调()
	拾取所有物品();
	延迟(200);
结束

定义函数 通用回调之接收房间任意任务()
	拾取所有物品();
	延迟(200);
	接受本地图任意所有任务();
	自动提交完成任务();
结束

定义函数 通用回调之任务和破坏固态物品()
	拾取所有物品();
	延迟(200);
	接受本地图任意所有任务();
	破坏所有固态物品();
	延迟(2000);
	杀死所有怪物()
	延迟(2000);
	拾取所有物品();
	自动提交完成任务();
结束

定义函数 通用打完所有房间( 回调函数, 最快打副本 )
	如果 没有 角色在副本中() 那么
		返回 假;
	结束
	局部变量 过图方式
	如果 最快打副本 == 真 那么
		过图方式 = 打完所有房间
	否则
		过图方式 = 全图打副本
	结束
	如果 回调函数 ~= 空 那么
		过图方式(回调函数);
	否则
		过图方式(通用回调之接收房间任意任务);
	结束
	直到可以返回城镇(1000 * 30);
	拾取所有物品();
	自动更换装备();
	修理已穿装备();
	返回 真;
结束

定义函数 通用打完并返回城镇( 回调函数, 最快打副本 )
	如果 没有 通用打完所有房间(回调函数, 最快打副本) 那么
		返回;
	结束
	返回城镇();

	卖掉普通栏所有装备();
	自动学习和升级所有技能();
	自动提交完成任务();
结束
