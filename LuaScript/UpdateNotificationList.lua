function updateNotificationList(account_id)
	
	require("LuaScript/Utility")
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	url = "https://plus.google.com/_/notifications/getnotificationsdata?inWidget=true&fetchUnreadCount=true&hl=ja&_reqid=" .. Utility.getRandomRequestID() .. "&rt=j"
	response = connection:httpGet(url, false)
	
	do return true end
end