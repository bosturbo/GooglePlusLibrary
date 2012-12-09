function streamInitialize(account_id)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	print("Stream initializing ...")
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
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
	
	talkgadget_number = InformationContainer.getInformationByAccountID("talkgadget_number", account_id)
	
	if(isStringNullOrEmpty(talkgadget_number) == nil) then
		print("StringNullOrEmpty(talkgadget_number) == nil")
		do return false end
	end
	
	url = "https://talkgadget.google.com/u/0/talkgadget/_/channel/bind?VER=8&"
	url = url .. "clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&prop=homepage&ujidr=TalkGadget" .. talkgadget_number .. "&"
	url = url .. "eid&ec=" .. Connection.escapeString("[0,0,0]") .. "&RID=" .. generateRIDValue() .. "&CVER=1&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpPost(url, "count=0")
	response_body = response:getResponseBody()
	
	json = connection:convertResponseToJson(response_body)
	
	sid = json:selectChildNode("[0].[1].[1]"):asString()
	
	if(isStringNullOrEmpty(sid) == nil) then
		print("StringNullOrEmpty(sid) == nil")
		do return false end
	end
	
	InformationContainer.addInformationByAccountID("stream_sid", sid, account_id)
	
	gsessionid = json:selectChildNode("[2].[1].[1].[1].[1]"):asString()
	
	if(isStringNullOrEmpty(gsessionid) == nil) then
		print("StringNullOrEmpty(gsessionid) == nil")
		do return false end
	end
	
	InformationContainer.addInformationByAccountID("gsessionid", gsessionid, account_id)
	
	print("sid:" .. sid)
	print("gsessionid:" .. gsessionid)
	
	print("Stream connecting ...")
	
	url = "https://talkgadget.google.com/u/0/talkgadget/_/channel/bind?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
	url = url .. "prop=homepage&ujidr=TalkGadget" .. talkgadget_number .. "&eid&ec=" .. Connection.escapeString("[0,0,0]") .. "&"
	url = url .. "SID=" .. sid .. "&RID=" .. generateRIDValue() .. "&AID=2&zx=" .. generateZxString() .. "&t=1"
	
	parameter = makeParameter("ofs","0") .. "&"
	
	parameter_count = 0
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "gst") .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"ng\",0]")) .. "&"

	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"qs\",15]")) .. "&"

	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"connect-add-client\"]"))
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"sc\",\"useChatCircles\",\"true\"]"))
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"connect-add-client\"]"))
	
	parameter_count = parameter_count + 1
	
	parameter = makeParameter("count", parameter_count) .. "&" .. parameter
	
	response = connection:httpPost(url, parameter)
	response_body = response:getResponseBody()
	
	-- start updating
	
	aid = 2
	
	InformationContainer.addInformationByAccountID("aid", aid, account_id)
	
	do return true end
end