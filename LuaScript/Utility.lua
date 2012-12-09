function isStringNullOrEmpty(source)
	if(source == nil) then
		do return nil end
	end
	
	if(source == "") then
		do return nil end
	end
	
	do return true end
end

function generateZxString()
	return Utility.generateRandomString(12, 12, "abcdefghijklmnopqrstuvwxyz0123456789")
end

function generateRIDValue()
	return Utility.getRandomValue(10000, 99999, "10000")
end

function generateCnString()
	return Utility.generateRandomString(6, 6, "abcdefghijklmnopqrstuvwxyz0123456789")
end

function generatePVTString()
	return ("AMP3u" .. Utility.generateRandomString(89, 89, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-=_") .. "==")
end

function makeParameter(parameter_name, parameter)
	do return (parameter_name .. "=" .. parameter) end
end