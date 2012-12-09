function streamLoopUpdate(account_id)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	print("Stream Looping...")
	
	aid = InformationContainer.getInformationByAccountID("aid", account_id)
	
	if(aid == nil) then
		print("StringNullOrEmpty(aid) == nil")
		do return false end
	end
	
	clid = InformationContainer.getInformationByAccountID("clid", account_id)
	
	if(isStringNullOrEmpty(clid) == nil) then
		print("StringNullOrEmpty(clid) == nil")
		do return false end
	end
	
	gsessionid = InformationContainer.getInformationByAccountID("gsessionid", account_id)
	
	if(isStringNullOrEmpty(gsessionid) == nil) then
		print("StringNullOrEmpty(gsessionid) == nil")
		do return false end
	end
	
	sid = InformationContainer.getInformationByAccountID("stream_sid", account_id)
	
	if(isStringNullOrEmpty(sid) == nil) then
		print("StringNullOrEmpty(sid) == nil")
		do return false end
	end
	
	talkgadget_number = InformationContainer.getInformationByAccountID("talkgadget_number", account_id)
	
	if(isStringNullOrEmpty(talkgadget_number) == nil) then
		print("StringNullOrEmpty(talkgadget_number) == nil")
		do return false end
	end
	
	url = "https://talkgadget.google.com/u/0/talkgadget/_/channel/bind?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
	url = url .. "prop=homepage&ujidr=TalkGadget" .. talkgadget_number .. "&eid&ec=" .. Connection.escapeString("[0,0,0]") .. "&"
	url = url .. "RID=rpc&SID=" .. sid .. "&CI=0&AID=" .. aid .. "&TYPE=xmlhttp&zx=" .. generateZxString() .. "&t=1"
	
	stream_observer = StreamObserver()
	
	response = stream_observer:get(account_id, url)
	
	status = response:getStatusCode()
	if(status ~= 200) then
		print("status:" .. status)
		do return false end
	end
	
	do return true end
end