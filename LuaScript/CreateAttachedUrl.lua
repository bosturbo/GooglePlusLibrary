function createAttachedUrl(account_id, url, thumbnail_number)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	if(isStringNullOrEmpty(url) == nil) then
		print("StringNullOrEmpty(url) == nil")
		do return false end
	end
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	
	url = "https://plus.google.com/_/sharebox/linkpreview/?c=" .. Connection.escapeString(url) .. "&t=1&slpf=0&ml=1&_reqid=" .. Utility.getRandomRequestID() .. "&rt=j"
	print("url=" .. url)
	
	at = InformationContainer.getInformationByAccountID("at", account_id)
	if(isStringNullOrEmpty(at) == nil) then
		print("StringNullOrEmpty(at) == nil")
		do return false end
	end
	
	parameter = "susp=false&"
	parameter = parameter .. "at=" .. Connection.escapeString(at)
	
	print("parameter=" .. parameter)
	
	response = connection:httpPost(url, parameter)
	response_body = response:getResponseBody()
	
	print(response_body)
	
	do return true end
end