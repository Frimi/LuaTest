static const char* convertToHeader="local lfs = require(\"lfs\")\n\
function GetFileName(filePath)\n\
  return filePath:match(\"^.+/(.+)$\")\n\
end\n\
function GetFileExtension(fileName)\n\
  return fileName:match(\"^.+(%..+)$\")\n\
end\n\
function dirLookup(dir)\n\
    local result = {}\n\
    for entry in lfs.dir(dir) do\n\
        if entry ~= \".\" and entry ~= \"..\" then\n\
            local file = dir .. \"/\" .. entry\n\
            if lfs.attributes(file, \"mode\") == \"file\" then\n\
                table.insert(result, file)\n\
            end\n\
        end\n\
    end\n\
    return result\n\
end\n\
function convertFile(fileName)\n\
	local f = assert(io.open(fileName, \"r\"))\n\
	local content = f:read(\"*all\")\n\
	f:close()\n\
	local newFileName = string.sub(fileName, 0, string.len(fileName) - 4);\n\
	local newContent = 'static const char* ' .. GetFileName(newFileName) .. '=\"'\n\
	newFileName = newFileName  .. '.h'\n\
	content = string.gsub(content, '[^\"\\']%-%-%[%[(.-)%-%-%]%]', '')\n\
	local tmpString = content\n\
	repeat\n\
		content = tmpString\n\
		tmpString = string.gsub(content, '[\\r\\n][ \\t]-%-%-(.-)[\\r\\n]', '\\n')\n\
	until(tmpString == content)\n\
	content = string.gsub(content, '\\\\', '\\\\\\\\')\n\
	content = string.gsub(content, '\"', '\\\\\"')\n\
	for line in string.gmatch(content, \"[^\\r\\n]+\") do\n\
		newContent = newContent .. line .. '\\\\n\\\\\\n'\n\
	end\n\
	newContent = string.sub(newContent, 0, string.len(newContent) - 4) .. '\";'\n\
	newContent = string.gsub(newContent, '[\\t ]+\\\\n\\\\', '\\\\n\\\\')\n\
	newContent = string.gsub(newContent, '[\\r\\n]\\\\n\\\\[\\r\\n]', '\\n')\n\
	newContent = string.gsub(newContent, '\\\\n\\\\[\\r\\n]\\\\n\\\\', '\\\\n\\\\')\n\
	newContent = newContent .. \"\\n\"\n\
	local headerFile = assert(io.open(newFileName, \"w\"))\n\
	headerFile:write(newContent)\n\
	headerFile:close()\n\
end\n\
local scriptFolder = arg[1]\n\
local files = dirLookup(scriptFolder)\n\
for i, file in ipairs(files) do\n\
	if GetFileExtension(file) == \".lua\" then\n\
		print (\"processing file: \" .. file)\n\
		convertFile(file)\n\
	end\n\
end";
