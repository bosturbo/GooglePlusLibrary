function parseAttachedUrl(json)
	
	require("LuaScript/Utility")
	
	attached_url_setter = AttachedUrlSetter()
	
	attached_url_setter:setPageUrl(json:selectChildNode("[1].[66].[0].[1]"):asString())
	
	favicon_url = json:selectChildNode("[1].[66].[0].[2]"):asString()
	
	if(isStringNullOrEmpty(favicon_url) ~= nil) then
		
		if(string.find(favicon_url, "https:") == nil) then
			favicon_url = "https:" .. favicon_url
		end
	end
	
	attached_url_setter:setPageFaviconUrl(favicon_url)
	
	attached_url_setter:setPageTitle(json:selectChildNode("[1].[66].[0].[3]"):asString())
	
	attached_url_setter:setPageDescription(json:selectChildNode("[1].[66].[0].[7]"):asString())
	
	thumbnail_url = json:selectChildNode("[1].[66].[0].[8]"):asString()
	
	if(isStringNullOrEmpty(thumbnail_url) ~= nil) then
		
		if(string.find(thumbnail_url, "https:") ~= 0) then
			
			thumbnail_url = "https:" .. thumbnail_url
		end
	end
	
	do return attached_url_setter end
end