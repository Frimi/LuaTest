local lfs = require("lfs")

--Rurns the file name from a file path
function GetFileName(filePath)
  return filePath:match("^.+/(.+)$")
end

--Returns the file extension from a file name
function GetFileExtension(fileName)
  return fileName:match("^.+(%..+)$")
end

--Returns all files in a directory.
function dirLookup(dir)
    local result = {}
    for entry in lfs.dir(dir) do
        if entry ~= "." and entry ~= ".." then
            local file = dir .. "/" .. entry
            if lfs.attributes(file, "mode") == "file" then
                table.insert(result, file)
            end
        end
    end
    return result
end

--Converts a lua script file into a C header file.
function convertFile(fileName)
	local f = assert(io.open(fileName, "r"))
	local content = f:read("*all")
	f:close()
	
	--Create the name of the header file.
	local newFileName = string.sub(fileName, 0, string.len(fileName) - 4);
	
	local newContent = 'static const char* ' .. GetFileName(newFileName) .. '="'
	newFileName = newFileName  .. '.h'
	
	--Remove all multi line comments (--[[     --]])
	content = string.gsub(content, '[^"\']%-%-%[%[(.-)%-%-%]%]', '')
		
	--Remove all single line comments (--)
	local tmpString = content
	repeat
		content = tmpString
		tmpString = string.gsub(content, '[\r\n][ \t]-%-%-(.-)[\r\n]', '\n')
	until(tmpString == content)
	
	content = string.gsub(content, '\\', '\\\\')
	content = string.gsub(content, '"', '\\"')
	
	--Split the file into single lines.
	for line in string.gmatch(content, "[^\r\n]+") do
		newContent = newContent .. line .. '\\n\\\n'
	end
	newContent = string.sub(newContent, 0, string.len(newContent) - 4) .. '";'
	
	--Remove all empty lines.
	newContent = string.gsub(newContent, '[\t ]+\\n\\', '\\n\\')
	newContent = string.gsub(newContent, '[\r\n]\\n\\[\r\n]', '\n')
	newContent = string.gsub(newContent, '\\n\\[\r\n]\\n\\', '\\n\\')
	
	
	
	newContent = newContent .. "\n"
	
	--Write the header file.
	local headerFile = assert(io.open(newFileName, "w"))
	headerFile:write(newContent)
	headerFile:close()
end


local scriptFolder = arg[1]

--Get all files.
local files = dirLookup(scriptFolder)

--Convert all lua files.
for i, file in ipairs(files) do
	if GetFileExtension(file) == ".lua" then
		print ("processing file: " .. file)
		convertFile(file)
	end
end