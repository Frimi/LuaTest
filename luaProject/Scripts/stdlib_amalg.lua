do
local _ENV = _ENV
package.preload[ "_base" ] = function( ... ) local arg = _G.arg;

local _ENV = require 'std.normalize' {
   concat = 'table.concat',
   dirsep = 'package.dirsep',
   find = 'string.find',
   gsub = 'string.gsub',
   insert = 'table.insert',
   min = 'math.min',
   shallow_copy = 'table.merge',
   sort = 'table.sort',
   sub = 'string.sub',
   table_maxn = table.maxn,
   wrap = 'coroutine.wrap',
   yield = 'coroutine.yield',
}


local maxn = table_maxn or function(t)
   local n = 0
   for k in pairs(t) do
      if type(k) == 'number' and k > n then
         n = k
      end
   end
   return n
end

local function callable(x)
   if type(x) == 'function' then
      return x
   end
   return (getmetatable(x) or {}).__call
end


local function catfile(...)
   return concat({...}, dirsep)
end


local function compare(l, m)
   local lenl, lenm = len(l), len(m)
   for i = 1, min(lenl, lenm) do
      local li, mi = tonumber(l[i]), tonumber(m[i])
      if li == nil or mi == nil then
         li, mi = l[i], m[i]
      end
      if li < mi then
         return -1
      elseif li > mi then
         return 1
      end
   end
   if lenl < lenm then
      return -1
   elseif lenl > lenm then
      return 1
   end
   return 0
end


local function escape_pattern(s)
   return (gsub(s, '[%^%$%(%)%%%.%[%]%*%+%-%?]', '%%%0'))
end


local function invert(t)
   local i = {}
   for k, v in pairs(t) do
      i[v] = k
   end
   return i
end


local function leaves(it, tr)
   local function visit(n)
      if type(n) == 'table' then
         for _, v in it(n) do
            visit(v)
         end
      else
         yield(n)
      end
   end
   return wrap(visit), tr
end


local function split(s, sep)
   local r, patt = {}
   if sep == '' then
      patt = '(.)'
      insert(r, '')
   else
      patt = '(.-)' ..(sep or '%s+')
   end
   local b, slen = 0, len(s)
   while b <= slen do
      local e, n, m = find(s, patt, b + 1)
      insert(r, m or sub(s, b + 1, slen))
      b = n or slen + 1
   end
   return r
end

return {
   io = {
      catfile = catfile,
   },

   list = {
      compare = compare,
   },

   object = {
      Module = Module,
      mapfields = mapfields,
   },

   string = {
      escape_pattern = escape_pattern,
      split = split,
   },

   table = {
      invert = invert,
      maxn = maxn,
   },

   tree = {
      leaves = leaves,
   },
}
end
end

do
local _ENV = _ENV
package.preload[ "math" ] = function( ... ) local arg = _G.arg;


local _ = require 'std._base'

local argscheck = _.typecheck and _.typecheck.argscheck

_ = nil


local _ENV = require 'std.normalize' {
   'math',
   merge = 'table.merge',
}


local M


local _floor = math.floor

local function floor(n, p)
   if(p or 0) == 0 then
      return _floor(n)
   end
   local e = 10 ^ p
   return _floor(n * e) / e
end


local function round(n, p)
   local e = 10 ^(p or 0)
   return _floor(n * e + 0.5) / e
end

local function X(decl, fn)
   return argscheck and argscheck('std.math.' .. decl, fn) or fn
end


M = {
   floor = X('floor(number, ?int)', floor),
   round = X('round(number, ?int)', round),
}


return merge(math, M)
end
end

