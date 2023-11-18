static const char* stdlib_amalg="do\n\
local _ENV = _ENV\n\
package.preload[ \"_base\" ] = function( ... ) local arg = _G.arg;\n\
local _ENV = require 'std.normalize' {\n\
   concat = 'table.concat',\n\
   dirsep = 'package.dirsep',\n\
   find = 'string.find',\n\
   gsub = 'string.gsub',\n\
   insert = 'table.insert',\n\
   min = 'math.min',\n\
   shallow_copy = 'table.merge',\n\
   sort = 'table.sort',\n\
   sub = 'string.sub',\n\
   table_maxn = table.maxn,\n\
   wrap = 'coroutine.wrap',\n\
   yield = 'coroutine.yield',\n\
}\n\
local maxn = table_maxn or function(t)\n\
   local n = 0\n\
   for k in pairs(t) do\n\
      if type(k) == 'number' and k > n then\n\
         n = k\n\
      end\n\
   end\n\
   return n\n\
end\n\
local function callable(x)\n\
   if type(x) == 'function' then\n\
      return x\n\
   end\n\
   return (getmetatable(x) or {}).__call\n\
end\n\
local function catfile(...)\n\
   return concat({...}, dirsep)\n\
end\n\
local function compare(l, m)\n\
   local lenl, lenm = len(l), len(m)\n\
   for i = 1, min(lenl, lenm) do\n\
      local li, mi = tonumber(l[i]), tonumber(m[i])\n\
      if li == nil or mi == nil then\n\
         li, mi = l[i], m[i]\n\
      end\n\
      if li < mi then\n\
         return -1\n\
      elseif li > mi then\n\
         return 1\n\
      end\n\
   end\n\
   if lenl < lenm then\n\
      return -1\n\
   elseif lenl > lenm then\n\
      return 1\n\
   end\n\
   return 0\n\
end\n\
local function escape_pattern(s)\n\
   return (gsub(s, '[%^%$%(%)%%%.%[%]%*%+%-%?]', '%%%0'))\n\
end\n\
local function invert(t)\n\
   local i = {}\n\
   for k, v in pairs(t) do\n\
      i[v] = k\n\
   end\n\
   return i\n\
end\n\
local function leaves(it, tr)\n\
   local function visit(n)\n\
      if type(n) == 'table' then\n\
         for _, v in it(n) do\n\
            visit(v)\n\
         end\n\
      else\n\
         yield(n)\n\
      end\n\
   end\n\
   return wrap(visit), tr\n\
end\n\
local function split(s, sep)\n\
   local r, patt = {}\n\
   if sep == '' then\n\
      patt = '(.)'\n\
      insert(r, '')\n\
   else\n\
      patt = '(.-)' ..(sep or '%s+')\n\
   end\n\
   local b, slen = 0, len(s)\n\
   while b <= slen do\n\
      local e, n, m = find(s, patt, b + 1)\n\
      insert(r, m or sub(s, b + 1, slen))\n\
      b = n or slen + 1\n\
   end\n\
   return r\n\
end\n\
return {\n\
   io = {\n\
      catfile = catfile,\n\
   },\n\
   list = {\n\
      compare = compare,\n\
   },\n\
   object = {\n\
      Module = Module,\n\
      mapfields = mapfields,\n\
   },\n\
   string = {\n\
      escape_pattern = escape_pattern,\n\
      split = split,\n\
   },\n\
   table = {\n\
      invert = invert,\n\
      maxn = maxn,\n\
   },\n\
   tree = {\n\
      leaves = leaves,\n\
   },\n\
}\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"debug\" ] = function( ... ) local arg = _G.arg;\n\
local _ENV = require 'std.normalize' {\n\
   'debug',\n\
   _debug = require 'std._debug',\n\
   concat = 'table.concat',\n\
   huge = 'math.huge',\n\
   max = 'math.max',\n\
   merge = 'table.merge',\n\
   stderr = 'io.stderr',\n\
}\n\
--[[ Implementation. ]]--\n\
local function say(n, ...)\n\
   local level, argt = n, {...}\n\
   if type(n) ~= 'number' then\n\
      level, argt = 1, {n, ...}\n\
   end\n\
   if _debug.level ~= huge and\n\
        ((type(_debug.level) == 'number' and _debug.level >= level) or level <= 1)\n\
   then\n\
      local t = {}\n\
      for k, v in pairs(argt) do\n\
         t[k] = str(v)\n\
      end\n\
      stderr:write(concat(t, '\\t') .. '\\n')\n\
   end\n\
end\n\
local level = 0\n\
local function trace(event)\n\
   local t = debug.getinfo(3)\n\
   local s = ' >>> '\n\
   for i = 1, level do\n\
      s = s .. ' '\n\
   end\n\
   if t ~= nil and t.currentline >= 0 then\n\
      s = s .. t.short_src .. ':' .. t.currentline .. ' '\n\
   end\n\
   t = debug.getinfo(2)\n\
   if event == 'call' then\n\
      level = level + 1\n\
   else\n\
      level = max(level - 1, 0)\n\
   end\n\
   if t.what == 'main' then\n\
      if event == 'call' then\n\
         s = s .. 'begin ' .. t.short_src\n\
      else\n\
         s = s .. 'end ' .. t.short_src\n\
      end\n\
   elseif t.what == 'Lua' then\n\
      s = s .. event .. ' ' ..(t.name or '(Lua)') .. ' <' ..\n\
         t.linedefined .. ':' .. t.short_src .. '>'\n\
   else\n\
      s = s .. event .. ' ' ..(t.name or '(C)') .. ' [' .. t.what .. ']'\n\
   end\n\
   stderr:write(s .. '\\n')\n\
end\n\
if _debug.call then\n\
   debug.sethook(trace, 'cr')\n\
end\n\
local M = {\n\
   getfenv = getfenv,\n\
   setfenv = setfenv,\n\
   say = say,\n\
   trace = trace,\n\
}\n\
local metatable = {\n\
   __call = function(self, ...)\n\
      M.say(1, ...)\n\
   end,\n\
}\n\
return setmetatable(merge(debug, M), metatable)\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"init\" ] = function( ... ) local arg = _G.arg;\n\
local _ = require 'std._base'\n\
local argscheck = _.typecheck and _.typecheck.argscheck\n\
local compare = _.list.compare\n\
local maxn = _.table.maxn\n\
local split = _.string.split\n\
_ = nil\n\
local _ENV = require 'std.normalize' {\n\
   format = 'string.format',\n\
   match = 'string.match',\n\
}\n\
local M\n\
local function _assert(expect, fmt, arg1, ...)\n\
   local msg =(arg1 ~= nil) and format(fmt, arg1, ...) or fmt or ''\n\
   return expect or error(msg, 2)\n\
end\n\
local function elems(t)\n\
   local fn, istate, ctrl = pairs(t)\n\
   return function(state, _)\n\
      local v\n\
      ctrl, v = fn(state, ctrl)\n\
      if ctrl then\n\
         return v\n\
      end\n\
   end, istate, true -- wrapped initial state\n\
end\n\
local function eval(s)\n\
   return load('return ' .. s)()\n\
end\n\
local function ielems(t)\n\
   local fn, istate, ctrl = ipairs(t)\n\
   return function(state, _)\n\
      local v\n\
      ctrl, v = fn(state, ctrl)\n\
      if ctrl then\n\
         return v\n\
      end\n\
   end, istate, true -- wrapped initial state\n\
end\n\
local function npairs(t)\n\
   local m = getmetamethod(t, '__len')\n\
   local i, n = 0, m and m(t) or maxn(t)\n\
   return function(t)\n\
      i = i + 1\n\
      if i <= n then\n\
         return i, t[i]\n\
      end\n\
    end,\n\
   t, i\n\
end\n\
local function ripairs(t)\n\
   local oob = 1\n\
   while t[oob] ~= nil do\n\
      oob = oob + 1\n\
   end\n\
   return function(t, n)\n\
      n = n - 1\n\
      if n > 0 then\n\
         return n, t[n]\n\
      end\n\
   end, t, oob\n\
end\n\
local function rnpairs(t)\n\
   local m = getmetamethod(t, '__len')\n\
   local oob =(m and m(t) or maxn(t)) + 1\n\
   return function(t, n)\n\
      n = n - 1\n\
      if n > 0 then\n\
         return n, t[n]\n\
      end\n\
   end, t, oob\n\
end\n\
local vconvert = setmetatable({\n\
   string = function(x)\n\
      return split(x, '%.')\n\
   end,\n\
   number = function(x)\n\
      return {x}\n\
   end,\n\
   table = function(x)\n\
      return x\n\
   end,\n\
}, {\n\
   __call = function(self, x)\n\
     local fn = self[type(x)] or function()\n\
        return 0\n\
     end\n\
     return fn(x)\n\
   end,\n\
})\n\
local function vcompare(a, b)\n\
   return compare(vconvert(a), vconvert(b))\n\
end\n\
local function _require(module, min, too_big, pattern)\n\
   pattern = pattern or '([%.%d]+)%D*$'\n\
   local s, m = '', require(module)\n\
   if type(m) == 'table' then\n\
      s = tostring(m.version or m._VERSION or '')\n\
   end\n\
   local v = match(s, pattern) or 0\n\
   if min then\n\
      _assert(vcompare(v, min) >= 0, \"require '\" .. module ..\n\
         \"' with at least version \" .. min .. ', but found version ' .. v)\n\
   end\n\
   if too_big then\n\
      _assert(vcompare(v, too_big) < 0, \"require '\" .. module ..\n\
         \"' with version less than \" .. too_big .. ', but found version ' .. v)\n\
   end\n\
   return m\n\
end\n\
local function X(decl, fn)\n\
   return argscheck and argscheck('std.' .. decl, fn) or fn\n\
end\n\
M = {\n\
   assert = X('assert(?any, ?string, [any...])', _assert),\n\
   eval = X('eval(string)', eval),\n\
   getmetamethod = X('getmetamethod(?any, string)', getmetamethod),\n\
   require = X('require(string, ?string, ?string, ?string)', _require),\n\
   elems = X('elems(table)', elems),\n\
   ielems = X('ielems(table)', ielems),\n\
   ipairs = X('ipairs(table)', ipairs),\n\
   npairs = X('npairs(table)', npairs),\n\
   pairs = X('pairs(table)', pairs),\n\
   ripairs = X('ripairs(table)', ripairs),\n\
   rnpairs = X('rnpairs(table)', rnpairs),\n\
}\n\
return setmetatable(M, {\n\
   __index = function(self, name)\n\
       local ok, t = pcall(require, 'std.' .. name)\n\
       if ok then\n\
          rawset(self, name, t)\n\
          return t\n\
       end\n\
    end,\n\
})\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"io\" ] = function( ... ) local arg = _G.arg;\n\
local _ = require 'std._base'\n\
local argscheck = _.typecheck and _.typecheck.argscheck\n\
local catfile = _.io.catfile\n\
local leaves = _.tree.leaves\n\
local split = _.string.split\n\
_ = nil\n\
local _ENV = require 'std.normalize' {\n\
   'io',\n\
   _G = _G,\n\
   concat = 'table.concat',\n\
   dirsep = 'package.dirsep',\n\
   format = 'string.format',\n\
   gsub = 'string.gsub',\n\
   input = 'io.input',\n\
   insert = 'table.insert',\n\
   io_type = 'io.type',\n\
   merge = 'table.merge',\n\
   open = 'io.open',\n\
   output = 'io.output',\n\
   popen = 'io.popen',\n\
   stderr = 'io.stderr',\n\
   stdin = 'io.stdin',\n\
   write = 'io.write',\n\
}\n\
local M\n\
local function input_handle(h)\n\
   if h == nil then\n\
      return input()\n\
   elseif type(h) == 'string' then\n\
      return open(h)\n\
   end\n\
   return h\n\
end\n\
local function slurp(file)\n\
   local h, err = input_handle(file)\n\
   if h == nil then\n\
      argerror('std.io.slurp', 1, err, 2)\n\
   end\n\
   if h then\n\
      local s = h:read('*a')\n\
      h:close()\n\
      return s\n\
   end\n\
end\n\
local function readlines(file)\n\
   local h, err = input_handle(file)\n\
   if h == nil then\n\
      argerror('std.io.readlines', 1, err, 2)\n\
   end\n\
   local l = {}\n\
   for line in h:lines() do\n\
      l[#l + 1] = line\n\
   end\n\
   h:close()\n\
   return l\n\
end\n\
local function writelines(h, ...)\n\
   if io_type(h) ~= 'file' then\n\
      write(h, '\\n')\n\
      h = output()\n\
   end\n\
   for v in leaves(ipairs, {...}) do\n\
      h:write(v, '\\n')\n\
   end\n\
end\n\
local function process_files(fn)\n\
   if len(arg) == 0 then\n\
      insert(arg, '-')\n\
   end\n\
   for i, v in ipairs(arg) do\n\
      if v == '-' then\n\
         input(stdin)\n\
      else\n\
         input(v)\n\
      end\n\
      fn(v, i)\n\
   end\n\
end\n\
local function warnfmt(msg, ...)\n\
   local prefix = ''\n\
   local prog = rawget(_G, 'prog') or {}\n\
   local opts = rawget(_G, 'opts') or {}\n\
   if prog.name then\n\
      prefix = prog.name .. ':'\n\
      if prog.line then\n\
         prefix = prefix .. str(prog.line) .. ':'\n\
      end\n\
   elseif prog.file then\n\
      prefix = prog.file .. ':'\n\
      if prog.line then\n\
         prefix = prefix .. str(prog.line) .. ':'\n\
      end\n\
   elseif opts.program then\n\
      prefix = opts.program .. ':'\n\
      if opts.line then\n\
         prefix = prefix .. str(opts.line) .. ':'\n\
      end\n\
   end\n\
   if #prefix > 0 then\n\
      prefix = prefix .. ' '\n\
   end\n\
   return prefix .. format(msg, ...)\n\
end\n\
local function warn(msg, ...)\n\
   writelines(stderr, warnfmt(msg, ...))\n\
end\n\
local function X(decl, fn)\n\
   return argscheck and argscheck('std.io.' .. decl, fn) or fn\n\
end\n\
M = {\n\
   die = X('die(string, [any...])', function(...)\n\
      error(warnfmt(...), 0)\n\
   end),\n\
   warn = X('warn(string, [any...])', warn),\n\
   catdir = X('catdir(string...)', function(...)\n\
      return(gsub(concat({...}, dirsep), '^$', dirsep))\n\
   end),\n\
   catfile = X('catfile(string...)', catfile),\n\
   dirname = X('dirname(string)', function(path)\n\
      return(gsub(path, catfile('', '[^', ']*$'), ''))\n\
   end),\n\
   splitdir = X('splitdir(string)', function(path)\n\
      return split(path, dirsep)\n\
   end),\n\
   process_files = X('process_files(function)', process_files),\n\
   readlines = X('readlines(?file|string)', readlines),\n\
   shell = X('shell(string)', function(c) return slurp(popen(c)) end),\n\
   slurp = X('slurp(?file|string)', slurp),\n\
   writelines = X('writelines(?file|string|number, [string|number...])', writelines),\n\
}\n\
return merge(io, M)\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"math\" ] = function( ... ) local arg = _G.arg;\n\
local _ = require 'std._base'\n\
local argscheck = _.typecheck and _.typecheck.argscheck\n\
_ = nil\n\
local _ENV = require 'std.normalize' {\n\
   'math',\n\
   merge = 'table.merge',\n\
}\n\
local M\n\
local _floor = math.floor\n\
local function floor(n, p)\n\
   if(p or 0) == 0 then\n\
      return _floor(n)\n\
   end\n\
   local e = 10 ^ p\n\
   return _floor(n * e) / e\n\
end\n\
local function round(n, p)\n\
   local e = 10 ^(p or 0)\n\
   return _floor(n * e + 0.5) / e\n\
end\n\
local function X(decl, fn)\n\
   return argscheck and argscheck('std.math.' .. decl, fn) or fn\n\
end\n\
M = {\n\
   floor = X('floor(number, ?int)', floor),\n\
   round = X('round(number, ?int)', round),\n\
}\n\
return merge(math, M)\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"package\" ] = function( ... ) local arg = _G.arg;\n\
local _ = require 'std._base'\n\
local argscheck = _.typecheck and _.typecheck.argscheck\n\
local catfile = _.io.catfile\n\
local escape_pattern = _.string.escape_pattern\n\
local invert = _.table.invert\n\
local split = _.string.split\n\
_ = nil\n\
local _ENV = require 'std.normalize' {\n\
   'package',\n\
   concat = 'table.concat',\n\
   dirsep = 'package.dirsep',\n\
   gsub = 'string.gsub',\n\
   merge = 'table.merge',\n\
   pathmark = 'package.pathmark',\n\
   pathsep = 'package.pathsep',\n\
   string_find = 'string.find',\n\
   table_insert = 'table.insert',\n\
   table_remove = 'table.remove',\n\
}\n\
local function pathsub(path)\n\
   return gsub(path, '%%?.', function(capture)\n\
      if capture == '?' then\n\
         return pathmark\n\
      elseif capture == '/' then\n\
         return dirsep\n\
      else\n\
         return gsub(capture, '^%%', '', 1)\n\
      end\n\
   end)\n\
end\n\
local function find(pathstrings, patt, init, plain)\n\
   local paths = split(pathstrings, pathsep)\n\
   if plain then\n\
      patt = escape_pattern(patt)\n\
   end\n\
   init = init or 1\n\
   if init < 0 then\n\
      init = #paths - init\n\
   end\n\
   for i = init, #paths do\n\
      if string_find(paths[i], patt) then\n\
         return i, paths[i]\n\
      end\n\
   end\n\
end\n\
local function normalize(...)\n\
   local i, paths, pathstrings = 1, {}, concat({...}, pathsep)\n\
   for _, path in ipairs(split(pathstrings, pathsep)) do\n\
      path = gsub(pathsub(path), catfile('^[^', ']'), catfile('.', '%0'))\n\
      path = gsub(path, catfile('', '%.', ''), dirsep)\n\
      path = gsub(path, catfile('', '%.$'), '')\n\
      path = gsub(path, catfile('^%.', '%..', ''), catfile('..', ''))\n\
      path = gsub(path, catfile('', '$'), '')\n\
      repeat\n\
         local again = false\n\
         path = gsub(path, catfile('', '([^', ']+)', '%.%.', ''),\n\
            function(dir1)\n\
               if dir1 == '..' then   -- don't remove /../../\n\
                  return catfile('', '..', '..', '')\n\
               else\n\
                  again = true\n\
                  return dirsep\n\
               end\n\
            end)\n\
         path = gsub(path, catfile('', '([^', ']+)', '%.%.$'),\n\
               function(dir1)\n\
                  if dir1 == '..' then -- don't remove /../..\n\
                     return catfile('', '..', '..')\n\
                  else\n\
                     again = true\n\
                     return ''\n\
                  end\n\
               end)\n\
      until again == false\n\
      if not paths[path] then\n\
         paths[path], i = i, i + 1\n\
      end\n\
   end\n\
   return concat(invert(paths), pathsep)\n\
end\n\
local function insert(pathstrings, ...)\n\
   local paths = split(pathstrings, pathsep)\n\
   table_insert(paths, ...)\n\
   return normalize(unpack(paths, 1, len(paths)))\n\
end\n\
local function mappath(pathstrings, callback, ...)\n\
   for _, path in ipairs(split(pathstrings, pathsep)) do\n\
      local r = callback(path, ...)\n\
      if r ~= nil then\n\
         return r\n\
      end\n\
   end\n\
end\n\
local function remove(pathstrings, pos)\n\
   local paths = split(pathstrings, pathsep)\n\
   table_remove(paths, pos)\n\
   return concat(paths, pathsep)\n\
end\n\
local function X(decl, fn)\n\
   return argscheck and argscheck('std.package.' .. decl, fn) or fn\n\
end\n\
local M = {\n\
   find = X('find(string, string, ?int, ?boolean|:plain)', find),\n\
   insert = X('insert(string, [int], string)', insert),\n\
   mappath = X('mappath(string, function, [any...])', mappath),\n\
   normalize = X('normalize(string...)', normalize),\n\
   remove = X('remove(string, ?int)', remove),\n\
}\n\
return merge(package, M)\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"string\" ] = function( ... ) local arg = _G.arg;\n\
local _ = require 'std._base'\n\
local argscheck = _.typecheck and _.std.typecheck.argscheck\n\
local escape_pattern = _.string.escape_pattern\n\
local split = _.string.split\n\
_ = nil\n\
local _ENV = require 'std.normalize' {\n\
   'string',\n\
   abs = 'math.abs',\n\
   concat = 'table.concat',\n\
   find = 'string.find',\n\
   floor = 'math.floor',\n\
   format = 'string.format',\n\
   gsub = 'string.gsub',\n\
   insert = 'table.insert',\n\
   match = 'string.match',\n\
   merge = 'table.merge',\n\
   render = 'string.render',\n\
   sort = 'table.sort',\n\
   sub = 'string.sub',\n\
   upper = 'string.upper',\n\
}\n\
local M\n\
local function toqstring(x, xstr)\n\
  if type(x) ~= 'string' then\n\
     return xstr\n\
  end\n\
  return format('%q', x)\n\
end\n\
local concatvfns = {\n\
   elem = tostring,\n\
   term = function(x)\n\
      return type(x) ~= 'table' or getmetamethod(x, '__tostring')\n\
   end,\n\
   sort = function(keys)\n\
      return keys\n\
   end,\n\
   open = function(x) return '{' end,\n\
   close = function(x) return '}' end,\n\
   pair = function(x, kp, vp, k, v, kstr, vstr, seqp)\n\
      return toqstring(k, kstr) .. '=' .. toqstring(v, vstr)\n\
   end,\n\
   sep = function(x, kp, vp, kn, vn, seqp)\n\
      return kp ~= nil and kn ~= nil and ',' or ''\n\
   end,\n\
}\n\
local function __concat(s, o)\n\
   return render(s, concatvfns) .. render(o, concatvfns)\n\
end\n\
local function __index(s, i)\n\
   if type(i) == 'number' then\n\
      return sub(s, i, i)\n\
   else\n\
      return M[i]\n\
   end\n\
end\n\
local _format = string.format\n\
local function format(f, arg1, ...)\n\
   return(arg1 ~= nil) and _format(f, arg1, ...) or f\n\
end\n\
local function tpack(from, to, ...)\n\
   return from, to, {...}\n\
end\n\
local function tfind(s, ...)\n\
   return tpack(find(s, ...))\n\
end\n\
local function finds(s, p, i, ...)\n\
   i = i or 1\n\
   local l = {}\n\
   local from, to, r\n\
   repeat\n\
      from, to, r = tfind(s, p, i, ...)\n\
      if from ~= nil then\n\
         insert(l, {from, to, capt=r})\n\
         i = to + 1\n\
      end\n\
   until not from\n\
   return l\n\
end\n\
local function caps(s)\n\
   return(gsub(s, '(%w)([%w]*)', function(l, ls)\n\
      return upper(l) .. ls\n\
   end))\n\
end\n\
local function escape_shell(s)\n\
   return(gsub(s, '([ %(%)%\\\\%[%]\\'\"])', '\\\\%1'))\n\
end\n\
local function ordinal_suffix(n)\n\
   n = abs(n) % 100\n\
   local d = n % 10\n\
   if d == 1 and n ~= 11 then\n\
      return 'st'\n\
   elseif d == 2 and n ~= 12 then\n\
      return 'nd'\n\
   elseif d == 3 and n ~= 13 then\n\
      return 'rd'\n\
   else\n\
      return 'th'\n\
   end\n\
end\n\
local function pad(s, w, p)\n\
   p = string.rep(p or ' ', abs(w))\n\
   if w < 0 then\n\
      return string.sub(p .. s, w)\n\
   end\n\
   return string.sub(s .. p, 1, w)\n\
end\n\
local function wrap(s, w, ind, ind1)\n\
   w = w or 78\n\
   ind = ind or 0\n\
   ind1 = ind1 or ind\n\
   assert(ind1 < w and ind < w,\n\
      'the indents must be less than the line width')\n\
   local r = {string.rep(' ', ind1)}\n\
   local i, lstart, lens = 1, ind1, len(s)\n\
   while i <= lens do\n\
      local j = i + w - lstart\n\
      while len(s[j]) > 0 and s[j] ~= ' ' and j > i do\n\
         j = j - 1\n\
      end\n\
      local ni = j + 1\n\
      while s[j] == ' ' do\n\
         j = j - 1\n\
      end\n\
      insert(r, sub(s, i, j))\n\
      i = ni\n\
      if i < lens then\n\
         insert(r, '\\n' .. string.rep(' ', ind))\n\
         lstart = ind\n\
      end\n\
   end\n\
   return concat(r)\n\
end\n\
local function numbertosi(n)\n\
   local SIprefix = {\n\
      [-8]='y', [-7]='z', [-6]='a', [-5]='f',\n\
      [-4]='p', [-3]='n', [-2]='mu', [-1]='m',\n\
      [0]='',  [1]='k', [2]='M', [3]='G',\n\
      [4]='T', [5]='P', [6]='E', [7]='Z',\n\
      [8]='Y'\n\
   }\n\
   local t = _format('% #.2e', n)\n\
   local _, _, m, e = find(t, '.(.%...)e(.+)')\n\
   local man, exp = tonumber(m), tonumber(e)\n\
   local siexp = floor(exp / 3)\n\
   local shift = exp - siexp * 3\n\
   local s = SIprefix[siexp] or 'e' .. tostring(siexp)\n\
   man = man *(10 ^ shift)\n\
   return _format('%0.f', man) .. s\n\
end\n\
local function keycmp(a, b)\n\
   if type(a) == 'number' then\n\
      return type(b) ~= 'number' or a < b\n\
   end\n\
   return type(b) ~= 'number' and tostring(a) < tostring(b)\n\
end\n\
local render_fallbacks = {\n\
   __index = concatvfns,\n\
}\n\
local function prettytostring(x, indent, spacing)\n\
   indent = indent or '\\t'\n\
   spacing = spacing or ''\n\
   return render(x, setmetatable({\n\
      elem = function(x)\n\
         if type(x) ~= 'string' then\n\
            return tostring(x)\n\
         end\n\
         return format('%q', x)\n\
      end,\n\
      sort = function(keylist)\n\
         sort(keylist, keycmp)\n\
         return keylist\n\
      end,\n\
      open = function()\n\
         local s = spacing .. '{'\n\
         spacing = spacing .. indent\n\
         return s\n\
      end,\n\
      close = function()\n\
         spacing = string.gsub(spacing, indent .. '$', '')\n\
         return spacing .. '}'\n\
      end,\n\
      pair = function(x, _, _, k, v, kstr, vstr)\n\
         local type_k = type(k)\n\
         local s = spacing\n\
         if type_k ~= 'string' or match(k, '[^%w_]') then\n\
            s = s .. '['\n\
            if type_k == 'table' then\n\
               s = s .. '\\n'\n\
            end\n\
            s = s .. kstr\n\
            if type_k == 'table' then\n\
               s = s .. '\\n'\n\
            end\n\
            s = s .. ']'\n\
         else\n\
            s = s .. k\n\
         end\n\
         s = s .. ' ='\n\
         if type(v) == 'table' then\n\
            s = s .. '\\n'\n\
         else\n\
            s = s .. ' '\n\
         end\n\
         s = s .. vstr\n\
         return s\n\
      end,\n\
      sep = function(_, k)\n\
         local s = '\\n'\n\
         if k then\n\
            s = ',' .. s\n\
         end\n\
         return s\n\
      end,\n\
   }, render_fallbacks))\n\
end\n\
local function trim(s, r)\n\
   r = r or '%s+'\n\
   return (gsub(gsub(s, '^' .. r, ''), r .. '$', ''))\n\
end\n\
local function X(decl, fn)\n\
   return argscheck and argscheck('std.string.' .. decl, fn) or fn\n\
end\n\
M = {\n\
   __concat = __concat,\n\
   __index = __index,\n\
   caps = X('caps(string)', caps),\n\
   chomp = X('chomp(string)', function(s)\n\
      return(gsub(s, '\\n$', ''))\n\
   end),\n\
   escape_pattern = X('escape_pattern(string)', escape_pattern),\n\
   escape_shell = X('escape_shell(string)', escape_shell),\n\
   finds = X('finds(string, string, ?int, ?boolean|:plain)', finds),\n\
   format = X('format(string, [any...])', format),\n\
   ltrim = X('ltrim(string, ?string)', function(s, r)\n\
      return (gsub(s, '^' ..(r or '%s+'), ''))\n\
   end),\n\
   numbertosi = X('numbertosi(number|string)', numbertosi),\n\
   ordinal_suffix = X('ordinal_suffix(int|string)', ordinal_suffix),\n\
   pad = X('pad(string, int, ?string)', pad),\n\
   prettytostring = X('prettytostring(?any, ?string, ?string)', prettytostring),\n\
   rtrim = X('rtrim(string, ?string)', function(s, r)\n\
      return (gsub(s, (r or '%s+') .. '$', ''))\n\
   end),\n\
   split = X('split(string, ?string)', split),\n\
   tfind = X('tfind(string, string, ?int, ?boolean|:plain)', tfind),\n\
   trim = X('trim(string, ?string)', trim),\n\
   wrap = X('wrap(string, ?int, ?int, ?int)', wrap),\n\
}\n\
return merge(string, M)\n\
end\n\
end\n\
do\n\
local _ENV = _ENV\n\
package.preload[ \"table\" ] = function( ... ) local arg = _G.arg;\n\
local _ = require 'std._base'\n\
local argscheck = _.typecheck and _.typecheck.argscheck\n\
local invert = _.table.invert\n\
local maxn = _.table.maxn\n\
_ = nil\n\
local _ENV = require 'std.normalize' {\n\
   'table',\n\
   merge = 'table.merge',\n\
   min = 'math.min',\n\
}	\n\
local M\n\
local function merge_allfields(t, u, map, nometa)\n\
   if type(map) ~= 'table' then\n\
      map, nometa = nil, map\n\
   end\n\
   if not nometa then\n\
      setmetatable(t, getmetatable(u))\n\
   end\n\
   if map then\n\
      for k, v in pairs(u) do\n\
         t[map[k] or k] = v\n\
      end\n\
   else\n\
      for k, v in pairs(u) do\n\
         t[k] = v\n\
      end\n\
   end\n\
   return t\n\
end\n\
local function merge_namedfields(t, u, keys, nometa)\n\
   if type(keys) ~= 'table' then\n\
      keys, nometa = nil, keys\n\
   end\n\
   if not nometa then\n\
      setmetatable(t, getmetatable(u))\n\
   end\n\
   for _, k in pairs(keys or {}) do\n\
      t[k] = u[k]\n\
   end\n\
   return t\n\
end\n\
local function depair(ls)\n\
   local t = {}\n\
   for _, v in ipairs(ls) do\n\
      t[v[1]] = v[2]\n\
   end\n\
   return t\n\
end\n\
local function enpair(t)\n\
   local tt = {}\n\
   for i, v in pairs(t) do\n\
      tt[#tt + 1] = {i, v}\n\
   end\n\
   return tt\n\
end\n\
local _insert = table.insert\n\
local function insert(t, pos, v)\n\
   if v == nil then\n\
      pos, v = len(t) + 1, pos\n\
   end\n\
   if pos < 1 or pos > len(t) + 1 then\n\
      argerror('std.table.insert', 2, 'position ' .. pos .. ' out of bounds', 2)\n\
   end\n\
   _insert(t, pos, v)\n\
   return t\n\
end\n\
local function keys(t)\n\
   local l = {}\n\
   for k in pairs(t) do\n\
      l[#l + 1] = k\n\
   end\n\
   return l\n\
end\n\
local function new(x, t)\n\
   return setmetatable(t or {}, {__index = function(t, i)\n\
      return x\n\
   end})\n\
end\n\
local function project(fkey, tt)\n\
   local r = {}\n\
   for _, t in ipairs(tt) do\n\
      r[#r + 1] = t[fkey]\n\
   end\n\
   return r\n\
end\n\
local function size(t)\n\
   local n = 0\n\
   for _ in pairs(t) do\n\
      n = n + 1\n\
   end\n\
   return n\n\
end\n\
local _sort = table.sort\n\
local function sort(t, c)\n\
   _sort(t, c)\n\
   return t\n\
end\n\
local _remove = table.remove\n\
local function remove(t, pos)\n\
   local lent = len(t)\n\
   pos = pos or lent\n\
   if pos < min(1, lent) or pos > lent + 1 then -- +1? whu? that's what 5.2.3 does!?!\n\
      argerror('std.table.remove', 2, 'position ' .. pos .. ' out of bounds', 2)\n\
   end\n\
   return _remove(t, pos)\n\
end\n\
local _unpack = unpack\n\
local function unpack(t, i, j)\n\
   if j == nil then\n\
      local m = getmetamethod(t, '__len')\n\
      j = m and m(t) or maxn(t)\n\
   end\n\
   return _unpack(t, tonumber(i) or 1, tonumber(j))\n\
end\n\
local function values(t)\n\
   local l = {}\n\
   for _, v in pairs(t) do\n\
      l[#l + 1] = v\n\
   end\n\
   return l\n\
end\n\
local function X(decl, fn)\n\
   return argscheck and argscheck('std.table.' .. decl, fn) or fn\n\
end\n\
M = {\n\
   insert = X('insert(table, [int], any)', insert),\n\
   maxn = X('maxn(table)', maxn),\n\
   pack = pack,\n\
   remove = X('remove(table, ?int)', remove),\n\
   sort = X('sort(table, ?function)', sort),\n\
   unpack = X('unpack(table, ?int, ?int)', unpack),\n\
   clone = X('clone(table, [table], ?boolean|:nometa)', function(...)\n\
      return merge_allfields({}, ...)\n\
   end),\n\
   clone_select = X('clone_select(table, [table], ?boolean|:nometa)', function(...)\n\
      return merge_namedfields({}, ...)\n\
   end),\n\
   depair = X('depair(list of lists)', depair),\n\
   enpair = X('enpair(table)', enpair),\n\
   empty = X('empty(table)', function(t)\n\
      return not next(t)\n\
   end),\n\
   new = X('new(?any, ?table)', new),\n\
   project = X('project(any, list of tables)', project),\n\
   size = X('size(table)', size),\n\
   values = X('values(table)', values),\n\
   invert = X('invert(table)', invert),\n\
   keys = X('keys(table)', keys),\n\
   merge = X('merge(table, table, [table], ?boolean|:nometa)', merge_allfields),\n\
   merge_select = X('merge_select(table, table, [table], ?boolean|:nometa)',\n\
      merge_namedfields),\n\
}\n\
return merge(table, M)\n\
end\n\
end";
