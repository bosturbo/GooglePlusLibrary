function saveProfile(account_id)
	
	if(isStringNullOrEmpty(account_id) == nil) then
		print("StringNullOrEmpty(account_id) == nil")
		do return false end
	end
	
	
	
	connection = Connection()
	connection:setCurrentAccountID(account_id)
	
	do return true end
end

function isStringNullOrEmpty(source)
	if(source == nil) then
		do return nil end
	end
	
	if(source == "") then
		do return nil end
	end
	
	do return true end
end