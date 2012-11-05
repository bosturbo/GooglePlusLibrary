function login(mail_address, password)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(mail_address) == nil) then
		print("StringNullOrEmpty(mail_address) == nil")
		do return "" end
	end
	
	if(isStringNullOrEmpty(password) == nil) then
		print("StringNullOrEmpty(password) == nil")
		do return "" end
	end
	
	print("Login connecting...")
	
	connection = Connection()
	
	connection:setCurrentMailAddress(mail_address)
	response = connection:httpGet("https://plus.google.com/?gpsrc=ogpy0&tab=wX", true)
	
	response_body = response:getResponseBody()
	--print("response:" .. response_body)
	dsh = string.match(response_body, "id=\"dsh\" value=\"([^\"]+)\"")
	
	if(isStringNullOrEmpty(dsh) == nil) then
		print("StringNullOrEmpty(dsh) == nil")
		do return "" end
	end
	
	
	galx = response:getResponseCookie("GALX")
	
	if(isStringNullOrEmpty(galx) == nil) then
		print("StringNullOrEmpty(galx) == nil")
		do return "" end
	end
	
	parameter = "Email=" .. mail_address .. "&"
	parameter = parameter .. "Passwd=" .. password .. "&"
	parameter = parameter .. "GALX=" .. galx .. "&"
	parameter = parameter .. "PersistentCookie=yes" .. "&"
	parameter = parameter .. "continue=" .. Connection.escapeString("https://plus.google.com/?gpsrc=ogpy0&tab=wX&gpsrc=ogpy0") .. "&"
	parameter = parameter .. "dnConn=&"
	parameter = parameter .. "dsh=" .. dsh .. "&"
	parameter = parameter .. "hl=ja&"
	parameter = parameter .. "pstMsg=1&"
	parameter = parameter .. "rmShown=1&"
	parameter = parameter .. "secTok=&"
	parameter = parameter .. "service=oz&"
	parameter = parameter .. "signIn=" .. Connection.escapeString("ログイン") .. "&"
	parameter = parameter .. "timeStmp=&"
	
	response = connection:httpPost("https://accounts.google.com/ServiceloginAuth", parameter)
	
	sid = response:getResponseCookie("SID")
	
	if(isStringNullOrEmpty(sid) == nil) then
		print("StringNullOrEmpty(sid) == nil")
		do return "" end
	end
	
	--print("sid = " .. sid)
	
	ssid = response:getResponseCookie("SSID")
	
	if(isStringNullOrEmpty(ssid) == nil) then
		print("StringNullOrEmpty(ssid) == nil")
		do return "" end
	end
	
	--print("ssid = " .. ssid)
	
	hsid = response:getResponseCookie("HSID")
	
	if(isStringNullOrEmpty(hsid) == nil) then
		print("StringNullOrEmpty(hsid) == nil")
		do return "" end
	end
	
	--print("hsid = " .. hsid)
	
	response = connection:httpGet("https://plus.google.com/?gpsrc=ogpy0&tab=wX&gpsrc=ogpy0", false)
	response_body = response:getResponseBody()
	
	-- get at value
	at = string.match(response_body, "\"(AObGSA[^\"]+)\"")
	if(isStringNullOrEmpty(at) == nil) then
		print("StringNullOrEmpty(at) == nil")
		
		f = io.open("FailedGet at" .. os.time() .. ".txt", "w")
		f:write("https://plus.google.com/?gpsrc=ogpy0&tab=wX&gpsrc=ogpy0")
		f:write(response_body)
		f:close()
		
		position = string.find(response_body, "AObGS")
			
		if(position == nil) then
			print("position=nil")
			do return "" end
		end
		
		at = string.sub(response_body, position - 200)
		print("position:" .. position)
		
		print("near at=" .. at)
		
		do return "" end
	end
	
	InformationContainer.addInformationByMailAddress("at", at, mail_address)
	
	-- get href value
	href = string.match(response_body, "src=\"(/_/apps%-static/_/js/home/b[^\"]+)\"")
	
	if(isStringNullOrEmpty(href) == nil) then
		print("StringNullOrEmpty(href) == nil")
		do return "" end
	end
	
	href = Connection.escapeString("https://plus.google.com" .. href .. "?rel=1")
	href = string.gsub(href, "%%21", "!")
	
	InformationContainer.addInformationByMailAddress("href", href, mail_address)
	
	-- get pvt value
	pvt = string.match(response_body, "(AMP3u[^\"]+)\"")
		
	if(isStringNullOrEmpty(pvt) == nil) then
		print("StringNullOrEmpty(pvt) == nil")
		
		position = string.find(response_body, "AMP")
		
		if(position == nil) then
			print("position == nil")
			do return "" end
		end
		
		print("position=" .. position)
		
		pvt = string.sub(response_body, position - 100)
		
		print("near pvt=" .. pvt)
		
		do return "" end
	end
	
	pvt = pvt.gsub(pvt, "\\u003d", "%%3D")
	
	InformationContainer.addInformationByMailAddress("pvt", pvt, mail_address)
	
	ozv = string.match(response_body, "'(es_oz_[^']+)'")
	
	url = "https://plus.google.com/_/pages/getidentities/?hl=ja"
	
	if(isStringNullOrEmpty(ozv) ~= nil) then
		url = url .. "&" .. ozv
		InformationContainer.addInformationByMailAddress("ozv", ozv, mail_address)
	end
	
	url = url .. "&avw=str%3A1&_reqid=" .. Utility.getRandomRequestID() .. "&rt=j"
	
	response = connection:httpGet(url, false)
	
	json = connection:convertResponseToJson(response:getResponseBody())
	
	account_id = json:selectChildNode("[0].[0].[1]"):asString()
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return "" end
	end
	
	connection:setCurrentAccountID(account_id)
	print("account_id=" .. account_id)
	
	--googleplus_my_account = GooglePlusMyAccount()
	--googleplus_my_account:setAccountID(account_id)
	
	InformationContainer.setConnectID(mail_address, account_id)
	InformationContainer.addInformationByAccountID("account_id", account_id, account_id)
	
	do return account_id end
end