local cdi = CD_Interface

--打一下就会收到e8的包，解冻后：e8、12，然后很e3和e8
--[[
cdi.TestAnalysisRecvPacket(true, 0, { 0x108, 0xda, 0xc, 0x10b, 0x10d, 0x55, 0x10c, 0xd9, 0xe1, 0xe7, 0xe0, 0xdb, 
    0xde, 0xe2, 0xdf, 0xe9,
})
--]]
----[[
cdi.TestAnalysisRecvPacket(true, 0, { 
    --0xfb, 0x9, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde
    0x111,
})
--]]
--[[
cdi.TestAnalysisSendPacket(true, 0, { 
})
--]]
