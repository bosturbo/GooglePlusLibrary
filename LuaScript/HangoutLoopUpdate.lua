function hangoutLoopUpdate(account_id)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	--print("Hangout Looping...")
	
	aid = InformationContainer.getInformationByAccountID("hangout_aid", account_id)
	
	if(aid == nil) then
		print("StringNullOrEmpty(aid) == nil")
		do return false end
	end
	
	clid = InformationContainer.getInformationByAccountID("hangout_clid", account_id)
	
	if(isStringNullOrEmpty(clid) == nil) then
		print("StringNullOrEmpty(clid) == nil")
		do return false end
	end
	
	gsessionid = InformationContainer.getInformationByAccountID("hangout_gsessionid", account_id)
	
	if(isStringNullOrEmpty(gsessionid) == nil) then
		print("StringNullOrEmpty(gsessionid) == nil")
		do return false end
	end
	
	sid = InformationContainer.getInformationByAccountID("hangout_sid", account_id)
	
	if(isStringNullOrEmpty(sid) == nil) then
		print("StringNullOrEmpty(sid) == nil")
		do return false end
	end
	
	ujidr = InformationContainer.getInformationByAccountID("hangout_ujidr", account_id)
	
	if(isStringNullOrEmpty(ujidr) == nil) then
		print("StringNullOrEmpty(ujidr) == nil")
		do return false end
	end
	
	
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	url = "https://plus.google.com/Talkgadget/channel/bind?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
	url = url .. "&prop=hangout&ujidr=" .. ujidr .. "&eid&RID=rpc&SID=" .. sid .. "&CI=0&AID=" .. aid .. "&TYPE=xmlhttp&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpGet(url, false)
	
	status = response:getStatusCode()
	if(status ~= 200) then
		print("status" .. status)
		do return false end
	end
	
	response_body = response:getResponseBody()
	
	--print("response_body" .. response_body)
	
	json = connection:convertResponseToJson(response_body)
	
	for count = 0, json:count(), 1 do
	
		child_json = json:selectChildNode(count)
		
		if(child_json:selectChildNode("[1].[0]"):asString() == "noop") then
			--print("hangout_aid=" .. aid)
			
			break
		end
		
		type = child_json:selectChildNode("[1].[1].[1].[0]"):asString()
		
		if(child_json:selectChildNode("[1].[0]"):asString() == "c") then
			if(type == "ei") then
				
				gsessionid = child_json:selectChildNode("[1].[1].[1].[1]"):asString()
				print("gsessionid=" .. gsessionid)
				
				aid = aid + 1
				InformationContainer.addInformationByAccountID("hangout_aid", aid, account_id)
				break
			
			end
			
		end
		
		-- information for post or comment
		
		if(type == nil) then
			print("type=nil")
		else
			print("type=" .. type)
		end
		
		if(type == "m") then
			print("メッセージが投稿されたよ")
		end
		
		if(type == "ho:hjr") then
			address = child_json:selectChildNode("[1].[1].[1].[3]"):asString()
			
			if(address == nil) then
				print("address == nil")
			else
				print("address:" .. address)
				
				
				url = "https://plus.google.com/Talkgadget/channel/bind?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
				url = url .. "prop=hangout&ujidr=" .. ujidr .. "&eid&SID=" .. sid .. "&RID=" .. generateRIDValue() .. "&AID=" .. aid .. "&zx=" .. generateZxString() .. "&t=1"
				
				offset = 10
				
				parameter = makeParameter("ofs", offset) .. "&"
				
				parameter_count = 0
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"" .. address .. "\",1]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "cs")
				
				parameter_count = parameter_count + 1
				
				parameter = makeParameter("count", parameter_count) .. "&" .. parameter
				
				print("parameter" .. parameter)
				print("send1")
				
				response = connection:httpPost(url, parameter)
				response_body = response:getResponseBody()
				print("response_body" .. response_body)
				
				send_id = Utility.generateRandomString(15, 15, "0123456789")
				
				chat_comment_count = InformationContainer.getInformationByAccountID("chat_comment_count", account_id)
				
				if(isStringNullOrEmpty(chat_comment_count) == nil) then
					chat_comment_count = "0"
				end
				
				offset = offset + parameter_count
				
				parameter = makeParameter("ofs", offset) .. "&"
				
				parameter_count = 0
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"nms\",[]]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li") .. "&"
				
				parameter_count = parameter_count + 1
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"" .. address .. "\",\"testaaa\",\"0." .. send_id .. "_:12" .. chat_comment_count .. "\"]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "m")
				
				parameter_count = parameter_count + 1
				
				parameter = makeParameter("count", parameter_count) .. "&" .. parameter
				
				print("parameter" .. parameter)
				
				print("send2")
				response = connection:httpPost(url, parameter)
				response_body = response:getResponseBody()
				print("response_body" .. response_body)
				
				
				offset = offset + parameter_count
				
				parameter = makeParameter("ofs", offset) .. "&"
				
				parameter_count = 0
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"mudi\",[]]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li") .. "&"
				
				parameter_count = parameter_count + 1
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"nmd\",[]]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li") .. "&"
				
				parameter_count = parameter_count + 1
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"mudi\",[]]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li") .. "&"
				
				parameter_count = parameter_count + 1
				
				parameter = parameter .. makeParameter("req" .. parameter_count .. "__sc", "c") .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_c", clid) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_p", Connection.escapeString("[\"nmd\",[]]")) .. "&"
				parameter = parameter .. makeParameter("req" .. parameter_count .. "_t", "li")
				
				parameter_count = parameter_count + 1
				
				parameter = makeParameter("count", parameter_count) .. "&" .. parameter
				
				print("parameter" .. parameter)
				
				print("send3")
				response = connection:httpPost(url, parameter)
				response_body = response:getResponseBody()
				print("response_body" .. response_body)
				
				
				chat_comment_count = chat_comment_count + 1
				
				InformationContainer.addInformationByAccountID("chat_comment_count", chat_comment_count, account_id)
			end
			
		end
		
		aid = aid + 1
		InformationContainer.addInformationByAccountID("hangout_aid", aid, account_id)
		--print("hangout_aid" .. aid)
		--sleep(10)
		
	end
	
	--sleep(500)
	
	do return true end
	
end