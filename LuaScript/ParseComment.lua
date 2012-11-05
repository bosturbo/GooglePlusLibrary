function parseComment(json)
	
	require("LuaScript/Utility")
	
	comment_setter = CommentSetter()
	
	sub_type = json:selectChildNode("[0]"):asString()
	
	comment_setter:setCommentAuthorName(json:selectChildNode("[1].[1]"):asString())
	
	comment_setter:setCommentMessage(json:selectChildNode("[1].[2]"):asString())
	
	comment_setter:setCommentID(json:selectChildNode("[1].[4]"):asString())
	--print("comment id:" .. json:selectChildNode("[1].[4]"):asString())
	comment_setter:setCommentAuthorID(json:selectChildNode("[1].[6]"):asString())
	
	comment_time_string = json:selectChildNode("[1].[3]"):asString()
	
	comment_time = Utility.convertUnixTimeFromString(comment_time_string)
	
	comment_setter:setCommentTime(comment_time)
	
	comment_setter:setPostID(json:selectChildNode("[1].[7]"):asString())
	
	comment_author_image_url = json:selectChildNode("[1].[16]"):asString()
	
	position = string.find(comment_author_image_url, "https:")
	
	if (position == nil) then
	
		comment_author_image_url = "https:" .. comment_author_image_url
		
	end
	
	comment_setter:setCommentAuthorImageUrl(comment_author_image_url)
	
	last_edited_time_string = json:selectChildNode("[1].[70]"):asString()
	
	if((isStringNullOrEmpty(last_edited_time_string) ~= nil) and (last_edited_time_string ~= "0") ) then
		
		last_edited_time = Utility.convertUnixTimeFromString(last_edited_time_string)
		
		comment_setter:setLastEditedTime(last_edited_time)
		comment_setter:setIsEdited(true)
	else
		comment_setter:setLastEditedTime(comment_time)
		comment_setter:setIsEdited(false)
	end
	
	do return comment_setter end
end