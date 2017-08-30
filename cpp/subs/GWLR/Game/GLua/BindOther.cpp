#include "stdafx.h"
#include "GLuaC.h"
#include "Scmd.h"
#include <Common/FE_Env.h>

void GLuaC::BindOther()
{
	__super::BindOther();

	using namespace luabind;

	typedef bool(scmd::*IsValidGameObjT)(DWORD);
	typedef bool(scmd::*IsValidGameObjT_GAnyObjMgrBase)(const GameObjMgr_AnyObj::PacketIdT&);
	typedef bool(scmd::*SetRoleToBackT)(DWORD, int);
	typedef bool(scmd::*SetRoleToBackT_GAnyObjMgrBase)(const GameObjMgr_AnyObj::PacketIdT&, int);

	module(lua())
		[
			class_<scmd>("_scmd_")
			.def("FindNpcByName", FE_MakeOriEnv(Env_InVillage, scmd::FindNpcByName))
			.def("FindBeatableMonsterByName", FE_MakeOriEnv(Env_InFb, scmd::FindBeatableMonsterByName))
			.def("FindTheBoss", &scmd::FindTheBoss)
			.def("WaitAppearBoss", &scmd::WaitAppearBoss)
			.def("SetRoleToBack", (SetRoleToBackT)&scmd::SetRoleToBack)
			.def("SetRoleToBack", (SetRoleToBackT_GAnyObjMgrBase)&scmd::SetRoleToBack)
			.def("OpenNpc", &scmd::OpenNpc)
			.def("OpenNpc_Grid", &scmd::OpenNpc_Grid)
			.def("AcceptTaskById", &scmd::AcceptTaskById)
			.def("CommitTaskById", &scmd::CommitTaskById)
			.def("MoveToTheVillage", &scmd::MoveToTheVillage)
			.def("MoveToTheFb", &scmd::MoveToTheFb)
			.def("MoveToTheFbById", &scmd::MoveToTheFbById)
			.def("MoveToTheFb_Cat", &scmd::MoveToTheFb_Cat)
			.def("MoveToTheFb_King", &scmd::MoveToTheFb_King)
			.def("MoveToTheFb_King_Cream", &scmd::MoveToTheFb_King_Cream)
			.def("AddFbBlackList_Cat", &scmd::AddFbBlackList_Cat)
			.def("ClrFbBlackList_Cat", &scmd::ClrFbBlackList_Cat)
			.def("AddFbBlackList", &scmd::AddFbBlackList)
			.def("ClrFbBlackList", &scmd::ClrFbBlackList)
			.def("CanDoTheFb_Cat", &scmd::CanDoTheFb_Cat)
			.def("GiveUpFb", &scmd::GiveUpFb)
			.def("GiveUpXinShouXunLian", &scmd::GiveUpXinShouXunLian)
			.def("MoveToTheRoom", &scmd::MoveToTheRoom)
			.def("GainSupplyItem", &scmd::GainSupplyItem)
			.def("HitTheMonsterToDie", &scmd::HitTheMonsterToDie)
			.def("DestoryStaticBeatableMonster", &scmd::DestoryStaticBeatableMonster)
			.def("DebugInfoStaticBeatableObjs", &scmd::DebugInfoStaticBeatableObjs)
			.def("IsValidGameObj", (IsValidGameObjT)&scmd::IsValidGameObj)
			.def("IsValidGameObj", (IsValidGameObjT_GAnyObjMgrBase)&scmd::IsValidGameObj)
			.def("CollectTheCollectableObj", &scmd::CollectTheCollectableObj)
			//.def("FindNearestCollectObjAsSameRoom", &FindNearestCollectableObjAsSameRoom)
			.def("AutoCollectNearestCollectableObjAsSameRoom", &scmd::AutoCollectNearestCollectableObjAsSameRoom)
			.def("AutoCollectOnceAllRoomCollectableObj", &scmd::AutoCollectOnceAllRoomCollectableObj)
			.def("AutoCollectOverAllObj", &scmd::AutoCollectOverAllObj)
			.def("AutoCollectSpecifc", &scmd::AutoCollectSpecifc)
			.def("AutoCollectSpecifc_Farm", &scmd::AutoCollectSpecifc_Farm)
			.def("TakeInKnife", &scmd::TakeInKnife)
			.def("AutoCollectOverNearestCollectableObjAsSameRoom", &scmd::AutoCollectOverNearestCollectableObjAsSameRoom)
			//.def("FindNearestMonster", &FindNearestMonster)
			.def("FindNearestNormalMonsterFirst", &scmd::FindNearestNormalMonsterFirst)
			.def("UsePackageItem", &scmd::UsePackageItem)
			.def("UseSomeItems", &scmd::UseSomeItems)
			.def("UseTaskItem", &scmd::UseTaskItem)
			.def("ManuFactureItem", &scmd::ManuFactureItem)
			.def("WaitCrossedGraph", &scmd::WaitCrossedGraph)
			.def("WaitRetCity", &scmd::WaitRetCity)
			.def("CutNearestSkinOnce", &scmd::CutNearestSkinOnce)
			.def("CutOverNearestSkin", &scmd::CutOverNearestSkin)
			.def("WaitToFree", &scmd::WaitToFree)
			.def("PressKeyZ", &scmd::PressKeyZ)
			.def("PressKeyQ", &scmd::PressKeyQ)
			.def("PressKeyW", &scmd::PressKeyW)
			.def("PressKeyS", &scmd::PressKeyS)
			.def("PressKeyA", &scmd::PressKeyA)
			.def("PressKeyD", &scmd::PressKeyD)
			.def("PressKeySpace", &scmd::PressKeySpace)
			.def("PressKeyEsc", &scmd::PressKeyEsc)
			.def("KillOverTheRoomMonsters", &scmd::KillOverTheRoomMonsters)
			.def("DoNpcChat", &scmd::DoNpcChat)
			.def("DebugInfoMonsterInfo", &scmd::DebugInfoMonsterInfo)
			.def("DebugInfoAccetableTask", &scmd::DebugInfoAccetableTask)
			.def("DebugInfoPackageItemInfo", &scmd::DebugInfoPackageItemInfo)
			.def("GetItemName", &scmd::GetItemName)
			.def("GetItemCnt", &scmd::GetItemCnt)
			.def("GetTheItemTotalCnt", &scmd::GetTheItemTotalCnt)
			.def("GetItemLvl", &scmd::GetItemLvl)
			.def("GetItemRoleLvl", &scmd::GetItemRoleLvl)
			.def("IsValidItem", &scmd::IsValidItem)
			.def("FindPakcetItem", &scmd::FindPakcetItem)
			.def("FindStoreItem", &scmd::FindStoreItem)
			.def("FindTaskItem", &scmd::FindTaskItem)
			.def("FindItemFromPacketAndStore", &scmd::FindItemFromPacketAndStore)
			.def("GetCurFbAllRoomNum", &scmd::GetCurFbAllRoomNum)
			.def("DoCraft", &scmd::DoCraft)
			.def("BuyTheItemAsMaxCnt", &scmd::BuyTheItemAsMaxCnt)
			.def("LvlUpEquip", &scmd::LvlUpEquip)
			.def("LeftButtonClick", &scmd::LeftButtonClick)
			.def("CloseAllUi", &scmd::CloseAllUi)
			.def("WaitForCutSkin", &scmd::WaitForCutSkin)
			.def("IsValidTaskId", &scmd::IsValidTaskId)
			.def("GetLeftAcceptableShangJinCntToday", &scmd::GetLeftAcceptableShangJinCntToday)
			.def("GetAnyAcceptableShangJinTaskId", &scmd::GetAnyAcceptableShangJinTaskId)
			.def("GetAnyCanDoShangJinTaskId", &scmd::GetAnyCanDoShangJinTaskId)
			.def("GetAnyCommitableShangJinTaskId", &scmd::GetAnyCommitableShangJinTaskId)
			.def("GetTaskToDstFbName", &scmd::GetTaskToDstFbName)
			.def("GetTaskToDstFbId", &scmd::GetTaskToDstFbId)
			.def("GetTheFbNameById", &scmd::GetTheFbNameById)
			.def("GetTheFbIdByName", &scmd::GetTheFbIdByName)
			.def("GetTheTaskName", &scmd::GetTheTaskName)
			.def("MoveItem", &scmd::MoveItem)
			.def("StoreSomePackageItemsToStore", &scmd::StoreSomePackageItemsToStore)
			.def("GainItemFromStore", &scmd::GainItemFromStore)
			.def("PackageItemToStore", &scmd::PackageItemToStore)
			.def("GainSomeItemsFromStore", &scmd::GainSomeItemsFromStore)
			.def("AddStoreWhiteList", &scmd::AddStoreWhiteList)
			.def("ClrStoreWhiteList", &scmd::ClrStoreWhiteList)
			.def("WearEquip", &scmd::WearEquip)
			.def("GetOffEquipByIdx", &scmd::GetOffEquipByIdx)
			.def("EnterSelfFarm", &scmd::EnterSelfFarm)
			.def("EnterXinShou", &scmd::EnterXinShou)
			.def("LeaveFarm", &scmd::LeaveFarm)
			.def("ClrHandleAtHitting", &scmd::ClrHandleAtHitting)
			.def("AddHandleAtHitting", &scmd::AddHandleAtHitting)
			.def("ClrHandlersAtScriptStoped", &scmd::ClrHandlersAtScriptStoped)
			.def("AddHandlersAtScriptStoped", &scmd::AddHandlersAtScriptStoped)
			.def("GetRoleCurHp", &scmd::GetRoleCurHp)
			.def("HandleAllMails", &scmd::HandleAllMails)
			.def("LvlUpCollectOfFarm", &scmd::LvlUpCollectOfFarm)
			.def("IsTimeToCollectFarm", &scmd::IsTimeToCollectFarm)
			.def("GetExistFarmSeedName", &scmd::GetExistFarmSeedName)
			.def("PlantFarmSeed", &scmd::PlantFarmSeed)
			.def("DebugInfoCollectableObjs", &scmd::DebugInfoCollectableObjs)
			.def("FindCollectObjByName", &scmd::FindCollectObjByName)
			.def("SelectRoleByName", &scmd::SelectRoleByName)
			.def("SeletRoleByIdx", &scmd::SeletRoleByIdx)
			.def("WaitForSelectableRole", &scmd::WaitForSelectableRole)
			.def("AutoCreateRole", &scmd::AutoCreateRole)
			.def("CreateTheRole", &scmd::CreateTheRole)
			.def("AutoCreateOrSelectRole", &scmd::AutoCreateOrSelectRole)
			.def("IsAtSelectRole", &scmd::IsAtSelectRole)
			.def("IsAtInGame", &scmd::IsAtInGame)
			.def("ChangeRole", &scmd::ChangeRole)
			.def("NeedCreateRole", &scmd::NeedCreateRole)
			.def("GetRoleCnt", &scmd::GetRoleCnt)
			.def("AutoCollectOverTheObj", &scmd::AutoCollectOverTheObj)
			.def("WaitForTheJuQing", &scmd::WaitForTheJuQing)
			.def("StepOverTheStaticObjs", &scmd::StepOverTheStaticObjs)
			.def("DebugInfoStaticObjs", &scmd::DebugInfoStaticObjs)
			.def("DebugInfoTheFbId", &scmd::DebugInfoTheFbId)
			.def("AutoToDoTheSociatyTask", &scmd::AutoToDoTheSociatyTask)
			.def("GetCurRoleRoom", &scmd::GetCurRoleRoom)
			.def("SellToAuction", &scmd::SellToAuction)
			.def("SellToOtherSide", &scmd::SellToOtherSide)
			.def("SmartBuy", &scmd::SmartBuy)
			.def("SmartBuyOtherSide", &scmd::SmartBuyOtherSide)
			.def("QuerySoldCnt", &scmd::QuerySoldCnt)
			.def("SellStored_PacketRubbishItems", &scmd::SellStored_PacketRubbishItems)
			.def("SetItemFilterBlackList", &scmd::SetItemFilterBlackList)
			.def("SetItemFilterWhiteList", &scmd::SetItemFilterWhiteList)
			.def("AddItemNameBlackList", &scmd::AddItemNameBlackList)
			.def("ClrItemNameBlackList", &scmd::ClrItemNameBlackList)
			.def("AddItemNameWhiteList", &scmd::AddItemNameWhiteList)
			.def("ClrItemNameWhiteList", &scmd::ClrItemNameWhiteList)
			.def("SetItemInfoWhiteList", &scmd::SetItemInfoWhiteList)
			.def("SetCraftItemWhiteList", &scmd::SetCraftItemWhiteList)
			.def("SetLvlUpEquipWhiteList", &scmd::SetLvlUpEquipWhiteList)
			.def("SetFactureWhiteList", &scmd::SetFactureWhiteList)
			.def("WaitRoleCanMove", &scmd::WaitRoleCanMove)
			.def("SetRoleToPos", &scmd::SetRoleToPos)
			.def("SetDirFromDstObj", &scmd::SetDirFromDstObj)
			.def("WaitAppearTheNpc", &scmd::WaitAppearTheNpc)
			.def("WaitAppearBeatableMonster", &scmd::WaitAppearBeatableMonster)
			.def("IsTheNewRole", &scmd::IsTheNewRole)
			//.def("NeedRetChooseRoleByLeftExp", &scmd::NeedRetChooseRoleByLeftExp)
			.def("SetFatigueData", &scmd::SetFatigueData)
			.def("ZuoReQiQiu", &scmd::ZuoReQiQiu)
			.def("WaitTheCollectableObj", &scmd::WaitTheCollectableObj)
			.def("FindSuitableFbName", &scmd::FindSuitableFbName)
			.def("AutoWearSomeEquips", &scmd::AutoWearSomeEquips)
			.def("AutoLvlUpBodyEquips", &scmd::AutoLvlUpBodyEquips)
			.def("AutoDoGainCurWeaponMaterial", &scmd::AutoDoGainCurWeaponMaterial)
			.def("AddAutoLvlUpBlackList", &scmd::AddAutoLvlUpBlackList)
			.def("ClrAutoLvlUpEquipBlackList", &scmd::ClrAutoLvlUpEquipBlackList)
			.def("IsHotStatus", &scmd::IsHotStatus)
			.def("IsColdStatus", &scmd::IsColdStatus)
			.def("IsPoisoningStatus", &scmd::IsPoisoningStatus)
			.def("SetAfterEnteredFb", &scmd::SetAfterEnteredFb)
			.def("NeedMoDao", &scmd::NeedMoDao)
			.def("SendMail", &scmd::SendMail)
			.def("SendAnyMail", &scmd::SendAnyMail)
			.def("GetRoleLvl", &scmd::GetRoleLvl)
			.def("GetRoleCurGold", &scmd::GetRoleCurGold)
			.def("GetRoleCurSilver", &scmd::GetRoleCurSilver)
			.def("AddShangJinWhiteList", &scmd::AddShangJinWhiteList)
			.def("ClrShangJinWhiteList", &scmd::ClrShangJinWhiteList)
			.def("ArrangeItems_Store", &scmd::ArrangeItems_Store)
			.def("LeftShouLieQuanCnt", &scmd::LeftShouLieQuanCnt)
			.def("GetCurFbValidConsumeMode", &scmd::GetCurFbValidConsumeMode)
			.def("G_GetLeftSingleExp", &scmd::G_GetLeftSingleExp)
			.def("G_GetLeftDoubleExp", &scmd::G_GetLeftDoubleExp)
			.def("ChangeGameAc", &scmd::ChangeGameAc)
			.def("AutoGainGiftBag", &scmd::AutoGainGiftBag)
			.def("SetCurBossHitBodyPart", &scmd::SetCurBossHitBodyPart)
			.def("AddMonsterBodyPartInfo", &scmd::AddMonsterBodyPartInfo)
			.def("DebuInfo_AllBodyPart", &scmd::DebuInfo_AllBodyPart)
			.def("TestMatchBossBodyPartInfo", &scmd::TestMatchBossBodyPartInfo)
			.def("GainWeekShouLieQuan", &scmd::GainWeekShouLieQuan)
			.def("SetMonsterMaxHigh", &scmd::SetMonsterMaxHigh)
			.def("DebugInfo_CurMapGates", &scmd::DebugInfo_CurMapGates)
			.def("DebugInfo_King", &scmd::DebugInfo_King)
			.def("DebugInfo_KingCream", &scmd::DebugInfo_KingCream)
			.def("DebugInfo_AllPlayers", &scmd::DebugInfo_AllPlayers)
			.def("EnableRecvDebugInof", &scmd::EnableRecvDebugInof)
			.def("AddCollectBlackList", &scmd::AddCollectBlackList)
			.def("ClrCollectBlackList", &scmd::ClrCollectBlackList)
			.def("DoEveryObj_Bucket", &scmd::DoEveryObj_Bucket)
			.def("IsInVillage", &scmd::IsInVillage)
			.def("IsInFb", &scmd::IsInFb)
			.def("GetSelfWeapon", &scmd::GetSelfWeapon)
			.def("HandleRoleEnteredGame", &scmd::HandleRoleEnteredGame)
			.def("HandleGameScene", &scmd::HandleGameScene)
			.def("IsTheBoss", &scmd::IsTheBoss)
			.def("SetMinMoneyToKeepBuy", &scmd::SetMinMoneyToKeepBuy)
			.def("GiveUpTask", &scmd::GiveUpTask)
			.def("OpenTheNpcOfVillage", &scmd::OpenTheNpcOfVillage)
			.def("OpenVillageNpcById", &scmd::OpenVillageNpcById)
			.def("KillTheMonsterAsCnt", &scmd::KillTheMonsterAsCnt)
			.def("AutoSetCurBossHitBodyPartAsTheTask", &scmd::AutoSetCurBossHitBodyPartAsTheTask)
			.def("AddShangJinDstFbBlackList", &scmd::AddShangJinDstFbBlackList)
			.def("ClrShangJinDstFbBlackList", &scmd::ClrShangJinDstFbBlackList)
			.def("AddShangJinDstFbStableBlackList", &scmd::AddShangJinDstFbStableBlackList)
			.def("ClrShangJinDstFbStableBlackList", &scmd::ClrShangJinDstFbStableBlackList)
			.def("AddNewFriend", &scmd::AddNewFriend)
			.def("AutoMakeEquip", &scmd::AutoMakeEquip)
			.def("GetTaskTotalItemCnt", &scmd::GetTaskTotalItemCnt)
			.def("SetHitMode_UsePacketItem", &scmd::SetHitMode_UsePacketItem)
			.def("SetCurTimeHitMode", &scmd::SetCurTimeHitMode)
			.def("AddAutoWearBlackList", &scmd::AddAutoWearBlackList)
			.def("ClrAutoWearBlackList", &scmd::ClrAutoWearBlackList)
			.def("AddAutoWearWhiteList", &scmd::AddAutoWearWhiteList)
			.def("ClrAutoWearWhiteList", &scmd::ClrAutoWearWhiteList)
			.def("GetError_FbSerIsFull", &scmd::GetError_FbSerIsFull)
			.def("DoChangeRunScriptLevel0", &scmd::DoChangeRunScriptLevel0)
			.def("GetNextChangeScriptNameLevel0", &scmd::GetNextChangeScriptNameLevel0)
			.def("SetCurDeleteRoleIdx", &scmd::SetCurDeleteRoleIdx)
			.def("GetCurRoleIdxAtRoleList", &scmd::GetCurRoleIdxAtRoleList)
			.def("GetCurDeleteRoleIdx", &scmd::GetCurDeleteRoleIdx)
			.def("DoDeleteRole", &scmd::DoDeleteRole)
			.def("SetCurSerLine", &scmd::SetCurSerLine)
			.def("DoDealFaceToFace", &scmd::DoDealFaceToFace)
			.def("Deal_RequestDeal", &scmd::Deal_RequestDeal)
			.def("Deal_UntilAcceptOneDealRequest", &scmd::Deal_UntilAcceptOneDealRequest)
			.def("Deal_MoveSomeItems_Gold", &scmd::Deal_MoveSomeItems_Gold)
			.def("Deal_LockDealTab", &scmd::Deal_LockDealTab)
			.def("Deal_EnterDeal", &scmd::Deal_EnterDeal)
			.def("IsNiRenState", &scmd::IsNiRenState)
			.def("HandleNiRenState", &scmd::HandleNiRenState)
			.def("IsRanShaoStatus", &scmd::IsRanShaoStatus)
			.def("HandleRanShaoStatus", &scmd::HandleRanShaoStatus)
			.def("IsErChouStatus", &scmd::IsErChouStatus)
			.def("IsSnowManStatus", &scmd::IsSnowManStatus)
			.def("HandleSnowManState", &scmd::HandleSnowManState)
			.def("SetFbConsumeMode", &scmd::SetFbConsumeMode)
			.def("IsChanRaoStatus", &scmd::IsChanRaoStatus)
			.def("HandleChanRaoStatus", &scmd::HandleChanRaoStatus)
			.def("TestOutEquipMaterialFrom", &scmd::TestOutEquipMaterialFrom)
			.def("MM_DoGainTheMaterial", &scmd::MM_DoGainTheMaterial)
			.def("ExchangeGameAc", &scmd::ExchangeGameAc)
			.def("GetTaskNpcId", &scmd::GetTaskNpcId)
			.def("IsTaiDaoType", &scmd::IsTaiDaoType)
			.def("TestTheFbType", &scmd::TestTheFbType),
			def("scmd", &scmd::GetMe)
		];
}