function createHangout(account_id)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	print("Hangout Creating...")
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	url = "https://plus.google.com/hangouts/_/?authuser=0&hl=ja&hcb=0&lm1=" .. Utility.getUnixTime()
	response = connection:httpGet(url, false)
	location = response:getResponseHeaderValue("Location")
	
	if(isStringNullOrEmpty(location) == nil) then
		print("StringNullOrEmpty(location) == nil")
		do return false end
	end
	
	hangout_id = string.match(location, "https://plus%.google%.com/hangouts/_/([0-9a-zA-Z]+)%?")
	
	hangout_url = "https://plus.google.com/hangouts/_/" .. hangout_id .. "?authuser=0&hl=ja#"
	
	print("hangout_url:" .. hangout_url)
	
	f = io.open("Hangout Url" .. os.time() .. ".txt", "w")
	f:write(hangout_url)
	f:close()
	
	if(isStringNullOrEmpty(hangout_id) == nil) then
		print("StringNullOrEmpty(hangout_id) == nil")
		do return false end
	end
	
	InformationContainer.addInformationByAccountID("hangout_id", hangout_id, account_id)
	
	url = "https://plus.google.com/Talkgadget/hangoutsapp?"
	url = url .. "client=sm&"
	url = url .. "prop=hangout&"
	url = url .. "nav=true&"
	url = url .. "fid=gtn-roster-iframe-id&"
	url = url .. "ts=0&"
	url = url .. "debug=undefined&"
	url = url .. "os=Win32&"
	url = url .. "stime=" .. Utility.getUnixTime() .. "000&"
	url = url .. "fb=false&"
	url = url .. "re=true&"
	url = url .. "no=undefined&"
	url = url .. "hc=undefined&"
	url = url .. "ref=undefined&"
	url = url .. "xpc=" .. Connection.escapeString("{\"cn\":\"" .. generateCnString() .. "\",\"tp\":1,\"ifrid\":\"gtn-roster-iframe-id\",\"pu\":\"https://talkgadget.google.com/talkgadget/\"}") .. "&"
	url = url .. "href=" .. Connection.escapeString("https://plus.google.com/hangouts/_/" .. hangout_id .. "?rel=1&authuser=0&hl=ja#") .. "&"
	url = url .. "pos=l&"
	url = url .. "hl=ja&"
	url = url .. "vp=https%3A%2F%2Fplus.google.com%2Ftalkgadget%2Fxpc_blank&"
	url = url .. "uqp=false&"
	url = url .. "sl=false&"
	url = url .. "host=1&"
	url = url .. "zx=" .. generateZxString()
	
	print("url=" .. url)
	
	response = connection:httpGet(url, false)
	response_body = response:getResponseBody()
	
	
	ujidr = string.match(response_body, "\\x22(hangout[0-9a-zA-Z]+)\\x22")
	
	if(isStringNullOrEmpty(ujidr) == nil) then
		print("StringNullOrEmpty(ujidr) == nil")
		do return false end
	end
	
	print("ujidr" .. ujidr)
	
	InformationContainer.addInformationByAccountID("hangout_ujidr", ujidr, account_id)
	
	
	
	clid = InformationContainer.getInformationByAccountID("hangout_clid", account_id)
	gsessionid = InformationContainer.getInformationByAccountID("hangout_gsessionid", account_id)
	
	if((isStringNullOrEmpty(clid) == nil) or (isStringNullOrEmpty(gsessionid) == nil)) then
		
		information = string.match(response_body, "GetConfig%s?%(([^%)]+)%)")
		
		if(isStringNullOrEmpty(information) == nil) then
			print("StringNullOrEmpty(information) == nil")
			
			f = io.open("FailedGet hangout information" .. os.time() .. ".txt", "w")
			f:write(response_body)
			f:close()
		
			position = string.find(response_body, "GetConfig")
			
			if(position == nil) then
				print("position=nil")
				do return false end
			end
			
			information = string.sub(response_body, position)
			print("position:" .. position)
			
			print(information)
			
			do return false end
		end
		
		--print("information" .. information)
		
		clid, gsessionid = string.match(information, "\"channel\"%s*,%s*\"([^\"]+)\"%s*,%s*\"[^\"]*\"%s*,%s*\"([^\"]+)\"")
		
		if(isStringNullOrEmpty(clid) == nil) then
			
			print("StringNullOrEmpty(clid) == nil")
			do return false end
		end
		
		if(isStringNullOrEmpty(gsessionid) == nil) then
			print("StringNullOrEmpty(gsessionid) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("hangout_clid", clid, account_id)
		InformationContainer.addInformationByAccountID("hangout_gsessionid", gsessionid, account_id)
		
	end
	
	print("clid=" .. clid)
	print("gsessionid=" .. gsessionid)
	
	url = "https://plus.google.com/Talkgadget/initmsgs?clid=" .. clid .. "&cb=1"
	
	response = connection:httpGet(url, false)
	
	print("Hangout Initializing...")
	
	url = "https://plus.google.com/Talkgadget/channel/test?VER=8&"
	url = url .. "clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&prop=hangout&ujidr=" .. ujidr .. "&eid&MODE=init&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpGet(url, false)
	
	url = "https://plus.google.com/Talkgadget/channel/test?VER=8&" 
	url = url .. "clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&prop=hangout&ujidr=" .. ujidr .. "&eid&TYPE=xmlhttp&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpGet(url, false)
	
	url = "https://plus.google.com/Talkgadget/channel/bind?VER=8&"
	url = url .. "clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&prop=hangout&ujidr=" .. ujidr .. "&eid&RID=" .. generateRIDValue() .. "&CVER=1&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpPost(url, "count=0")
	response_body = response:getResponseBody()
	print(response_body)
	
	json = connection:convertResponseToJson(response_body)
	
	sid = json:selectChildNode("[0].[1].[1]"):asString()
	
	if(isStringNullOrEmpty(sid) == nil) then
		print("StringNullOrEmpty(sid) == nil")
		do return false end
	end
	
	InformationContainer.addInformationByAccountID("hangout_sid", sid, account_id)
	
	--print("sid:" .. sid)
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	print("Hangout connecting ...")
	
	url = "https://plus.google.com/Talkgadget/channel/bind?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
	url = url .. "prop=hangout&ujidr=" .. ujidr .. "&eid&SID=" .. sid .. "&RID=" .. generateRIDValue() .. "&AID=1&zx=" .. generateZxString() .. "&t=1"
	
	parameter = makeParameter("ofs","0") .. "&"
	
	parameter_count = 0
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "gst") .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"vcq\"]")) .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"" .. hangout_id .. "\",\"everyone\",null,0,\"hangout.google.com\",null,[],false]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "ho:hj") .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[[],[3],0]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "ho:hgr") .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[[],[1],1]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "ho:hgr") .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "ho:hs") .. "&"
	
	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"qs\",0]")) .. "&"

	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"connect-add-client\"]")) .. "&"

	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"bcfc\",[]]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li") .. "&"

	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"rc\",[]]")) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li") .. "&"

	parameter_count = parameter_count + 1
	
	parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
	parameter = parameter .. makeParameter("req" .. parameter_count .. "_m", Connection.escapeString("[\"connect-add-client\"]"))

	parameter_count = parameter_count + 1
	
	parameter = makeParameter("count", parameter_count) .. "&" .. parameter
	
	print("parameter" .. parameter)
	
	response = connection:httpPost(url, parameter)
	
	-- start updating
	
	aid = 1
	
	InformationContainer.addInformationByAccountID("hangout_aid", aid, account_id)
	
	
	do return true end
	
end