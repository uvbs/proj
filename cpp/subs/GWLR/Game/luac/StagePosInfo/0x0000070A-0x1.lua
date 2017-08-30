stage_pos_mgr = GSP_StagePosPath_Me()
pos_info = GSP__PosInfo()
room_info = GSP__RoomInfo()

-- 坐标节点  梅杰波尔坦-王立
pos_info:AddVertex(459,248.934982,593.109741,261.328339)
pos_info:AddVertex(458,248.008102,587.112549,260.946167)
pos_info:AddVertex(457,251.799500,582.096008,261.211914)
pos_info:AddVertex(456,257.760162,581.428040,260.946167)
pos_info:AddVertex(455,263.442474,583.975952,261.407745)
pos_info:AddVertex(454,267.134796,578.863770,261.440125)
pos_info:AddVertex(453,272.303284,575.518677,261.440125)
pos_info:AddVertex(452,278.519440,574.284180,261.438873)
pos_info:AddVertex(451,284.191711,577.275452,261.438873)
pos_info:AddVertex(450,279.815125,581.611511,261.440125)
pos_info:AddVertex(449,275.024872,585.793518,261.440125)
pos_info:AddVertex(448,269.622345,588.599426,261.440125)
pos_info:AddVertex(447,265.638855,593.700439,260.946167)
pos_info:AddVertex(446,263.451599,599.631042,260.946167)
pos_info:AddVertex(445,257.690887,603.088806,260.946167)
pos_info:AddVertex(444,251.644928,602.899048,261.440125)
pos_info:AddVertex(443,247.789383,598.062927,261.440125)

--坐标链接
pos_info:AddEdge(459,443)
pos_info:AddEdge(459,458)
pos_info:AddEdge(458,457)
pos_info:AddEdge(457,456)
pos_info:AddEdge(456,455)
pos_info:AddEdge(455,454)
pos_info:AddEdge(454,453)
pos_info:AddEdge(453,452)
pos_info:AddEdge(452,451)
pos_info:AddEdge(451,450)
pos_info:AddEdge(450,449)
pos_info:AddEdge(449,448)
pos_info:AddEdge(448,447)
pos_info:AddEdge(447,446)
pos_info:AddEdge(446,445)
pos_info:AddEdge(445,444)
pos_info:AddEdge(444,443)

--房间
room_info:AddPosInfo(1,pos_info)

--副本模板
stage_pos_mgr:AddStageInfo(0x0000070A,room_info)
