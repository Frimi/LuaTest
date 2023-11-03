static const char* script2="-- Carrega a biblioteca \"uc\"\n\
local uc = require(\"uc\")\n\
if uc then\n\
    print(\"Biblioteca 'uc' carregada com sucesso.\")\n\
else\n\
    print(\"Erro ao carregar a biblioteca 'uc'. Certifique-se de que ela esteja disponível.\")\n\
end\n\
print('\\nscript2: ' .. tostring(uc.counter()) ..'\\n')\n\
includedScript()";
