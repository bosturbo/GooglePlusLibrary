function talkgadgetConnect(account_id, connection_mode)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	print("Talkgadget connecting...")
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	at = InformationContainer.getInformationByAccountID("at", account_id)
	
	if(isStringNullOrEmpty(at) == nil) then
		print("StringNullOrEmpty(at) == nil")
		do return false end
	end
	
	href = InformationContainer.getInformationByAccountID("href", account_id)
	
	if(isStringNullOrEmpty(href) == nil) then
		print("StringNullOrEmpty(href) == nil")
		do return false end
	end
	
	pvt = InformationContainer.getInformationByAccountID("pvt", account_id)
	
	if(isStringNullOrEmpty(pvt) == nil) then
		print("StringNullOrEmpty(pvt) == nil")
		do return false end
	end
	
	wcsid= InformationContainer.getInformationByAccountID("wcsid", account_id)
	wcm = InformationContainer.getInformationByAccountID("wcm", account_id)
	wcxsec = InformationContainer.getInformationByAccountID("wcxsec", account_id)
	s = InformationContainer.getInformationByAccountID("s", account_id)
	
	if((isStringNullOrEmpty(wcsid) == nil) or (isStringNullOrEmpty(wcm) == nil) or (isStringNullOrEmpty(wcxsec) == nil) or (isStringNullOrEmpty(s) == nil)) then
		
		-- first connect
		
		url = "https://talkgadget.google.com/talkgadget/notifierclient?authuser=0&"
		url = url .. "client=sm&"
		url = url .. "prop=" .. connection_mode .. "&"
		url = url .. "nav=true&"
		url = url .. "fid=gtn-roster-iframe-id&"
		url = url .. "ts=0&"
		url = url .. "debug=undefined&"
		url = url .. "os=Win32&"
		url = url .. "stime=" .. Utility.getUnixTime() .. "000&"
		url = url .. "fb=false&"
		url = url .. "re=true&"
		url = url .. "no=false&"
		url = url .. "hc=undefined&"
		url = url .. "ref=undefined&"
		url = url .. "xpc=" .. Connection.escapeString("{\"cn\":\"" .. generateCnString() .. "\",\"tp\":1,\"ifrid\":\"gtn-roster-iframe-id\",\"pu\":\"https://talkgadget.google.com/talkgadget/\"}") .. "&"
		url = url .. "ec=" .. Connection.escapeString("[]") .. "&"
		url = url .. "screen=undefined&"
		url = url .. "pvt=" .. pvt .. "&"
		url = url .. "href=" .. href .. "&"
		url = url .. "pos=r&"
		url = url .. "uiv=2&"
		url = url .. "hl=ja&"
		url = url .. "hpc=true&"
		url = url .. "pal=1&"
		url = url .. "uqp=false&"
		url = url .. "sl=false&"
		url = url .. "host=1&"
		url = url .. "zx=" .. generateZxString()
		
		response = connection:httpGet(url, false)
		
		status = response:getStatusCode()
		if(status ~= 200) then
			print("status(notifierclient)" .. status)
			do return false end
		end
		
		response_body = response:getResponseBody()
		
		url = string.match(response_body, "window%.location%.replace%(\"([^\"]+)\"")
		
		if(isStringNullOrEmpty(url) == nil) then
			print("StringNullOrEmpty(window.location.replace...) == nil")
			
			f = io.open("FailedGet window location replace" .. os.time() .. ".txt", "w")
			f:write(response_body)
			f:close()
			
			do return false end
		end
		
		url = string.gsub (url, "\\x3d", "=")
		url = string.gsub (url, "\\x26", "&")
		
		-- Servicelogin
		
		response = connection:httpGet(url, false)
		location = response:getResponseHeaderValue("Location")
		
		if(isStringNullOrEmpty(location) == nil) then
			print("StringNullOrEmpty(location) == nil")
			do return false end
		end
		
		-- get WCSID cookie
		
		response = connection:httpGet(location, false)
		wcsid = response:getResponseCookie("WCSID")
		
		if(isStringNullOrEmpty(wcsid) == nil) then
			print("StringNullOrEmpty(wcsid) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("wcsid", wcsid, account_id)
		
		location = response:getResponseHeaderValue("Location")
		
		if(isStringNullOrEmpty(location) == nil) then
			print("StringNullOrEmpty(location) == nil")
			do return false end
		end
		
		-- get WCM, WCXSEC cookie
		
		response = connection:httpGet(location, false)		
		wcm = response:getResponseCookie("WCM")
		
		if(isStringNullOrEmpty(wcm) == nil) then
			print("StringNullOrEmpty(wcm) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("wcm", wcm, account_id)
		
		wcxsec = response:getResponseCookie("WCXSEC")
		
		if(isStringNullOrEmpty(wcxsec) == nil) then
			print("StringNullOrEmpty(wcxsec) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("wcxsec", wcxsec, account_id)
		
		location = response:getResponseHeaderValue("Location")
		
		if(isStringNullOrEmpty(location) == nil) then
			print("StringNullOrEmpty(location) == nil")
			do return false end
		end
		
		-- get S cookie
	
		response = connection:httpGet(location, true)
		response_body = response:getResponseBody()
		
		s = response:getResponseCookie("S")
		
		if(isStringNullOrEmpty(s) == nil) then
			print("StringNullOrEmpty(s) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("s", s, account_id)
		
		talkgadget_number = string.match(response_body, "x22TalkGadget(%w+)")
		
		if(isStringNullOrEmpty(talkgadget_number) == nil) then
			print("StringNullOrEmpty(talkgadget_number) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("talkgadget_number", talkgadget_number, account_id)
		print("talkgadget_number:" .. talkgadget_number)
	end
	
	-- get clid, gsessionid value
	
	clid = InformationContainer.getInformationByAccountID("clid", account_id)
	gsessionid = InformationContainer.getInformationByAccountID("gsessionid", account_id)
	
	if((isStringNullOrEmpty(clid) == nil) or (isStringNullOrEmpty(gsessionid) == nil)) then
		
		clid, gsessionid = string.match(response_body, "\"channel\"%s*,%s*\"([^\"]+)\"%s*,%s*\"[^\"]*\"%s*,%s*\"([^\"]+)\"")
		
		if(isStringNullOrEmpty(clid) == nil) then
			
			print("StringNullOrEmpty(clid) == nil")
			do return false end
		end
		
		if(isStringNullOrEmpty(gsessionid) == nil) then
			print("StringNullOrEmpty(gsessionid) == nil")
			do return false end
		end
		
		InformationContainer.addInformationByAccountID("clid", clid, account_id)
		InformationContainer.addInformationByAccountID("gsessionid", gsessionid, account_id)
		
	end
	
	print("clid=" .. clid)
	print("gsessionid=" .. gsessionid)
	
	-- init talkgadget
	
	url = "https://talkgadget.google.com/talkgadget/channel/test?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
	url = url .. "prop=homepage&ujidr=TalkGadget" .. talkgadget_number .. "&eid&ec=" .. Connection.escapeString("[0,0,0]") .. "&MODE=init&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpGet(url, false)
	response_body = response:getResponseBody()
	
	--print(response_body)
	
	do return true end
	
end

