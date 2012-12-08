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
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	url = "https://talkgadget.google.com/u/0/talkgadget/_/channel/bind?VER=8&clid=" .. clid .. "&gsessionid=" .. gsessionid .. "&"
	url = url .. "prop=homepage&ujidr=TalkGadget" .. talkgadget_number .. "&eid&ec=" .. Connection.escapeString("[0,0,0]") .. "&"
	url = url .. "RID=rpc&SID=" .. sid .. "&CI=0&AID=" .. aid .. "&TYPE=xmlhttp&zx=" .. generateZxString() .. "&t=1"
	
	response = connection:httpGet(url, false)
	
	response_body = response:getResponseBody()
	
	--print("response_body:" .. response_body)
	
	status = response:getStatusCode()
	if(status ~= 200) then
		print("status:" .. status)
		do return false end
	end
	
	json = connection:convertResponseToJson(response_body)
	if(json == nil) then
		print("json == nil")
	end
	
	--print("Json Count:" .. json:count())
	
	for count = 0, json:count(), 1 do
		
		--print("count:" .. count)
		--print("aid" .. aid)
		child_json = json:selectChildNode(count)
		
		if(child_json:isNull()) then
			do return true end
		end
		
		--print("Json:" .. child_json:selectChildNode("[1].[0]"):asString())
		--[[
		if(child_json:selectChildNode("[1].[0]"):asString() == "noop") then
			
			if(aid == "0") then
				print("Connect Error")
				do return false end
			elseif(aid == "1") then
				print("Connect Error")
				do return false end
			elseif(aid == "2") then
				print("Connect Error")
				do return false end
			elseif(aid == "3") then
				print("Connect Error")
				do return false end
			elseif(aid == "4") then
				print("Connect Error")
				do return false end
			elseif(aid == "5") then
				print("Connect Error")
				do return false end
			end
			print("noop aid=" .. aid)
			break
		end
		]]
		type = child_json:selectChildNode("[1].[1].[1].[0]"):asString()
		--print("type:" .. type)
		if(child_json:selectChildNode("[1].[0]"):asString() == "c") then
			if(type == "ei") then
				print("update gsessionid")
				gsessionid = child_json:selectChildNode("[1].[1].[1].[1]"):asString()
				--print("gsessionid=" .. gsessionid)
				
				aid = aid + 1
				InformationContainer.addInformationByAccountID("aid", aid, account_id)
				break
			
			end
			
		end
		--[[
		if(type == nil) then
			print("type=nil")
		else
			print("type=" .. type)
		end
		]]
		if(type == "tu") then
			
			-- invalid json string
			valid_json = Utility.convertStringEscapedJson(child_json, "[1].[1].[1].[1]")
			sub_type = valid_json:selectChildNode("[0]"):asString()
			
			if(sub_type == nil) then
				print("sub_type=nil")
			else
				--print("sub_type=" .. sub_type)
				
				if(sub_type == "t.rtu") then
					--print(response_body)
					PostParser.add(valid_json)
					name = valid_json:selectChildNode("[1].[3]"):asString()
					if(isStringNullOrEmpty(name) == nil) then
						--print("sub_type=".. sub_type .. " name == nil")
					else
						--print(account_id .. ":" .. name .. "さんが投稿をポストしたり編集したりしました")
					end
				end
				
				if(sub_type == "t.rtc") then
					--print(response_body)
					CommentParser.add(valid_json)
					name = valid_json:selectChildNode("[1].[1]"):asString()
					if(isStringNullOrEmpty(name) == nil) then
						--print("sub_type=".. sub_type .. " name == nil")
					else
						--print(account_id .. ":" .. name .. "さんがコメントをポストしたり編集したりしました")
					end
				end
				
				if(sub_type == "t.rtd") then
					--print(response_body)
					post_id = valid_json:selectChildNode("[1]"):asString()
					comment_id = valid_json:selectChildNode("[2]"):asString()
					
					if(isStringNullOrEmpty(comment_id) == nil) then
						if(isStringNullOrEmpty(post_id) ~= nil) then
							PostParser.erase(post_id)
						end
					else
						CommentParser.erase(comment_id)
					end
				end
			end
		end
		--[[
		if(type == "ru") then
			print("ru")
			
			name = child_json:selectChildNode("[1].[1].[1].[2]"):asString()
			print("名前:" .. name)
			
			status = child_json:selectChildNode("[1].[1].[1].[15].[1]"):asString()
			print("ステータス:" .. status)
			
		end
		]]
		
		if(type == "gb") then
			print(account_id .. ":自分がポストとかを投稿したりしました")
		end
		
		aid = aid + 1
		InformationContainer.addInformationByAccountID("aid", aid, account_id)
		
		sleep(10)
		
	end
	
	--sleep(500)
	
	do return true end
	
end