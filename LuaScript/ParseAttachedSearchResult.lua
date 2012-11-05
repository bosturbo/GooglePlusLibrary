function parseAttachedSearchResult(json)
	
	require("LuaScript/Utility")

	attached_search_result_setter = AttachedSearchResultSetter()
	
	search_keyword = json:selectChildNode("[1].[82].[2].[7].[0].[0]"):asString()

	attached_search_result_setter:setSearchKeyword(search_keyword)

	if(isStringNullOrEmpty(search_keyword) ~= nil) then
		
		search_keyword_page_url = "https://plus.google.com/s/" .. Connection.escapeString(search_keyword)
		attached_search_result_setter:setSearchResultPageUrl(search_keyword_page_url)
	end
	
	do return attached_search_result_setter end
end