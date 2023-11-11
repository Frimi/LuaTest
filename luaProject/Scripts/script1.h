static const char *script1 = "local function get_current_tick()\n\
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
local tempo_inicial = get_current_tick()\n\
local cond = true\n\
\n\
coro = coroutine.create(function()\n\
    while cond do\n\
        local status_botao = verificar_status_ignicao()\n\
\n\
        if not status_botao then\n\
            tempo_inicial = get_current_tick()  -- Ignição OFF, redefinir o tempo inicial\n\
			print(\"Ignicao OFF redefinir tempo\")\n\
        else\n\
            local diferenca = calcular_tempo_passado(tempo_inicial)\n\
\n\
            if diferenca >= 15000 then\n\
                print(\"Ignicao ON e passaram 15 segundos\")\n\
                tempo_inicial = get_current_tick()\n\
            end\n\
        end\n\
        coroutine.yield()\n\
    end\n\
end)\n\
\n\
coroutine.resume(coro)";

