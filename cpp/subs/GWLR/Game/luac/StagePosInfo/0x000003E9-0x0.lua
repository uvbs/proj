stage_pos_mgr = GSP_StagePosPath_Me()
pos_info = GSP__PosInfo()
room_info = GSP__RoomInfo()

-- 坐标节点
pos_info:AddVertex(1105,1632.101685,1543.542236,122.687500)
pos_info:AddVertex(1104,1629.369019,1549.035034,122.435310)
pos_info:AddVertex(1103,1623.661377,1551.907349,122.312706)
pos_info:AddVertex(1102,1617.604736,1552.315186,122.332199)
pos_info:AddVertex(1101,1612.051880,1549.386719,122.375847)
pos_info:AddVertex(1100,1631.145508,1537.999756,122.571594)
pos_info:AddVertex(1,1641.074829,1535.989380,122.937500)
pos_info:AddVertex(2,1647.246338,1534.019653,123.000000)
pos_info:AddVertex(3,1653.158569,1534.183838,124.649918)
pos_info:AddVertex(4,1658.435791,1537.903809,125.186966)
pos_info:AddVertex(5,1661.267090,1543.401245,125.879433)
pos_info:AddVertex(6,1664.270264,1548.619751,127.583847)
pos_info:AddVertex(7,1667.823120,1553.881226,127.243073)
pos_info:AddVertex(8,1670.352539,1559.488037,126.081032)
pos_info:AddVertex(9,1670.940063,1565.654175,125.948738)
pos_info:AddVertex(10,1670.460083,1571.939209,126.226234)
pos_info:AddVertex(11,1669.327393,1578.147339,126.914993)
pos_info:AddVertex(13,1665.533203,1590.086304,128.829926)
pos_info:AddVertex(14,1680.299316,1577.049194,125.184395)
pos_info:AddVertex(15,1680.385620,1568.021729,123.607506)
pos_info:AddVertex(16,1668.010986,1585.528809,127.970016)

--坐标链接
pos_info:AddEdge(1105,1100)
pos_info:AddEdge(1105,1104)
pos_info:AddEdge(1104,1103)
pos_info:AddEdge(1103,1102)
pos_info:AddEdge(1102,1101)
pos_info:AddEdge(1,1100)
pos_info:AddEdge(2,1)
pos_info:AddEdge(3,2)
pos_info:AddEdge(4,3)
pos_info:AddEdge(5,4)
pos_info:AddEdge(6,5)
pos_info:AddEdge(7,6)
pos_info:AddEdge(8,7)
pos_info:AddEdge(9,8)
pos_info:AddEdge(9,15)
pos_info:AddEdge(10,9)
pos_info:AddEdge(11,10)
pos_info:AddEdge(11,16)
pos_info:AddEdge(13,16)
pos_info:AddEdge(14,15)
pos_info:AddEdge(14,11)

--房间
room_info:AddPosInfo(0,pos_info)

--副本模板
stage_pos_mgr:AddStageInfo(0x000003E9,room_info)
