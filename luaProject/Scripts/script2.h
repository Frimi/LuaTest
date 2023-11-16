static const char *script2 = "local function get_current_tick()\n\
    return uc.get_tick()\n\
end\n\
\n\
local function calcular_tempo_passado(tempo_inicial)\n\
    local tempo_atual = get_current_tick()\n\
    local diferenca = tempo_atual - tempo_inicial\n\
    return diferenca\n\
end\n\
\n\
local function verificar_status_ignicao()\n\
    return uc.button_status()\n\
end\n\
\n\
function switch(caseTable, caseValue)\n\
    local caseFunction = caseTable[caseValue] or caseTable['default']\n\
    if caseFunction then\n\
        caseFunction()\n\
    end\n\
end\n\
\n\
local events = {\n\
    gnss_event = function()\n\
        local positionTable = uc.position()\n\
        print('Latitude:', positionTable.latitude)\n\
        print('Longitude:', positionTable.longitude)\n\
    end,\n\
    default = function()\n\
        print('Executando o caso padrao')\n\
    end\n\
}\n\
\n\
local tempo_inicial = get_current_tick()\n\
local cond = true\n\
\n\
coro = coroutine.create(function()\n\
    while cond do\n\
        local status_botao = verificar_status_ignicao()\n\
\n\
        if not status_botao then\n\
            tempo_inicial = get_current_tick()  -- Ignição OFF, redefinir o tempo inicial\n\
            print('Ignicao OFF redefinir tempo')\n\
        else\n\
            local diferenca = calcular_tempo_passado(tempo_inicial)\n\
\n\
            if diferenca >= 15000 then\n\
                print('Ignicao ON e passaram 15 segundos')\n\
                tempo_inicial = get_current_tick()\n\
            end\n\
        end\n\
        event = coroutine.yield()\n\
        print('event:', event)\n\
		switch(events, event)\n\
    end\n\
end)\n\
\n\
coroutine.resume(coro)";
