function parseAttachedLocation(json)
	
	require("LuaScript/Utility")
	
	attached_location_setter = AttachedLocationSetter()
	
	latitude = json:selectChildNode("[1].[27].[0]"):asString()
	attached_location_setter:setLatitude(latitude)
	
	longitude = json:selectChildNode("[1].[27].[1]"):asString()
	attached_location_setter:setLongitude(longitude)
	
	location_name = json:selectChildNode("[1].[27].[2]"):asString()
	attached_location_setter:setLocationName(location_name)
	
	address = json:selectChildNode("[1].[27].[3]"):asString()
	attached_location_setter:setAddress(address)
	
	google_map_page_image_url = json:selectChildNode("[1].[27].[5]"):asString()
	
	if(isStringNullOrEmpty(google_map_page_image_url) ~= nil) then
		position = string.find(google_map_page_image_url, "http://maps.google.com")
		
		if (position == nil) then
			google_map_page_image_url = "http://maps.google.com" .. google_map_page_image_url
		end
		
		attached_location_setter:setGoogleMapPageImageUrl(google_map_page_image_url)
	end
	
	
	 if (json:selectChildNode("[1].[27].[11]"):asString() == "0") then
		attached_location_setter:setIsCheckined(true)
	else
		attached_location_setter:setIsCheckined(false)
	end
	
	do return attached_location_setter end
end