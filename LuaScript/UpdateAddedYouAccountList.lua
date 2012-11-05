function updateAddedYouAccountList(account_id)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	at = InformationContainer.getInformationByAccountID("at", account_id)
	if(isStringNullOrEmpty(at) == nil) then
		print("StringNullOrEmpty(at) == nil")
		do return false end
	end
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	url = "https://plus.google.com/_/socialgraph/lookup/followers/?m=2500&_reqid=" .. Utility.getRandomRequestID() .. "&rt=j"
	print(url)
	parameter = "at=" .. at
	print(parameter)
	response = connection:httpPost(url, parameter)
	response_body = response:getResponseBody()
	--print(response_body)
	json = connection:convertResponseToJson(response)
	
	--child_json = json:selectChildNode("")
	
	json:show()
	--[[
	print("id0:" .. json:selectChildNode("[0].[1].[2].[0].[0].[2]"):asString())
	print("id1:" .. json:selectChildNode("[0].[1].[2].[1].[0].[2]"):asString())
	print("id2:" .. json:selectChildNode("[0].[1].[2].[2].[0].[2]"):asString())
	print("id3:" .. json:selectChildNode("[0].[1].[2].[3].[0].[2]"):asString())
	print("id4:" .. json:selectChildNode("[0].[1].[2].[4].[0].[2]"):asString())
	
	print("size:" .. child_json:count())
	
	do return true end
	
	for count = 0, child_json:count(), 1 do
		print(count)
		circle_info_json = child_json:selectChildNode(count)
		
		circle_id = circle_info_json:selectChildNode("[0].[0]"):asString()
		
		if(isStringNullOrEmpty(circle_id) == nil) then
			print("StringNullOrEmpty(circle_id) == nil")
			do return false end
		end
		print("circle_id:" .. circle_id)
		
		circle_name = circle_info_json:selectChildNode("[1].[0]"):asString()
		
		if(isStringNullOrEmpty(circle_name) == nil) then
			print("StringNullOrEmpty(circle_name) == nil")
			do return false end
		end
		print("circle_name:" .. circle_name)
	end
	
	print(response_body)
	]]
	do return true end
end