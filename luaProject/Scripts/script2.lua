-- Carrega a biblioteca "uc"
local uc = require("uc")

-- Verifica se a biblioteca foi carregada com sucesso
if uc then
    print("Biblioteca 'uc' carregada com sucesso.")
else
    print("Erro ao carregar a biblioteca 'uc'. Certifique-se de que ela esteja disponível.")
end

print('\nscript2: ' .. tostring(uc.counter()) ..'\n')

--Call a function from an other script (helperScript.lua).
includedScript()
