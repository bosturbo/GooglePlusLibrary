function parsePost(json)
	
	require("LuaScript/Utility")
	
	post_setter = PostSetter()
	
	sub_type = json:selectChildNode("[0]"):asString()
	
	post_setter:setPostType(json:selectChildNode("[1].[2]"):asString())
	
	post_setter:setAuthorName(json:selectChildNode("[1].[3]"):asString())
	
	post_setter:setMessage(json:selectChildNode("[1].[4]"):asString())
	
	post_time_string = json:selectChildNode("[1].[5]"):asString()
	
	post_setter:setPostTime(post_time_string)

	post_setter:setPostID(json:selectChildNode("[1].[8]"):asString())
	
	attached_url_setter = AttachedUrlSetter.parse(json)
	
	if(isStringNullOrEmpty(attached_url_setter:getPageUrl()) ~= nil) then
		post_setter:setAttachedUrl(attached_url_setter)
	end
	
	post_setter:setAccountID(json:selectChildNode("[1].[16]"):asString())

	image_url = json:selectChildNode("[1].[18]"):asString()
	
	position = string.find(image_url, "https:")
	
	if (position == nil) then
		image_url = "https:" .. image_url
	end
	
	post_setter:setAccountImageUrl(image_url)

	post_url = json:selectChildNode("[1].[21]"):asString()
	position = string.find(post_url, "https://plus.google.com/")
	
	if (position == nil) then
		post_url = "https://plus.google.com/" .. post_url
	end
	
	post_setter:setPostUrl(post_url)
	
	attached_location_setter = AttachedLocationSetter.parse(json)
	
	if(isStringNullOrEmpty(attached_location_setter:getGoogleMapPageImageUrl()) ~= nil) then
		post_setter:setAttachedLocation(attached_location_setter)
	end
	
	post_area = json:selectChildNode("[1].[32]"):asString()
	if (post_area == "1") then
		post_setter:setIsPublicPost(true)
	else
		post_setter:setIsPublicPost(false)
	end
	
	is_disable_comment = json:selectChildNode("[1].[35]"):asString()
	if(is_disable_comment == "1") then
	
		-- enable comment
		post_setter:setIsCommentDisabled(false)
	
	else
		-- disable comment
		post_setter:setIsCommentDisabled(true)
	end
	
	post_setter:setOriginalPostID(json:selectChildNode("[1].[39]"):asString())
	
	if (json:selectChildNode("[1].[41]"):asString() == "1") then
		post_setter:setIsMyPost(true)
	else
		post_setter:setIsMyPost(false)
	end
	
	last_edited_time_string = json:selectChildNode("[1].[70]"):asString()
	
	if(isStringNullOrEmpty(last_edited_time_string) ~= nil) then
		
		length = string.len(last_edited_time_string)
		
		-- time / 1000
		last_edited_time_string = string.sub(last_edited_time_string, 0, length - 3)
		
		post_setter:setLastEditedTime(last_edited_time_string)
		post_setter:setIsEdited(true)
	else
		post_setter:setLastEditedTime(post_time_string)
		post_setter:setIsEdited(false)
	end
	
	-- is reshared post
	shared_post_message = json:selectChildNode("[1].[47]"):asString()
	
	if(isStringNullOrEmpty(shared_post_message) ~= nil) then
		post_setter:setOriginalPostMessage(json:selectChildNode("[1].[4]"):asString())
		-- message is reshared message
		post_setter:setMessage(shared_post_message)
	end
	
	--! @todo OriginalPost～関連の実装をしておくこと

	-- PlusOneIDの取得
	post_setter:setPlusOneID(json:selectChildNode("[1].[73].[0]"):asString())
	
	original_post_url = json:selectChildNode("[1].[77]"):asString()
	if (string.len(original_post_url) >= 0) then
	
		position = string.find(original_post_url, "https://plus.google.com/")
		if (position == nil) then
			
			original_post_url = ("https://plus.google.com/" .. original_post_url)
			
		end
	end
	
	post_setter:setOriginalPostUrl(original_post_url)
	
	attached_search_result_setter = AttachedSearchResultSetter.parse(json)
	
	if(isStringNullOrEmpty(attached_search_result_setter:getSearchKeyword()) ~= nil) then
		post_setter:setAttachedSearchResult(attached_search_result_setter)
	end
	
	is_locked_post = json:selectChildNode("[1].[89]"):asString()
	if(is_locked_post == "0") then
	
		-- locked
		post_setter:setIsLockdPost(true)
	
	else
	
		-- non locked
		post_setter:setIsLockdPost(false)
	end
	
	do return post_setter end
end