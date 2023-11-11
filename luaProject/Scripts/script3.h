#ifndef SCRIPTS_SCRIPT3_H_
#define SCRIPTS_SCRIPT3_H_

static const char *script3 = "local function get_current_tick()\n\
    return uc.get_tick()\n\
end\n\
\n\
local function calcular_tempo_passado(tempo_inicial)\n\
    local tempo_atual = get_current_tick()\n\
    local diferenca = tempo_atual - tempo_inicial\n\
    return diferenca\n\
end\n\
\n\
local function status_panico()\n\
    return uc.panic_status()\n\
end\n\
\n\
local tempo_inicial = get_current_tick()\n\
local cond = true\n\
\n\
coro = coroutine.create(function()\n\
    while cond do\n\
        local estado_panico = status_panico()\n\
\n\
        if not estado_panico then\n\
            tempo_inicial = get_current_tick()  -- Não está em pânico, resetar o temporizador\n\
		    print(\"Panico OFF redefinir tempo\")\n\
        else\n\
            local diferenca = calcular_tempo_passado(tempo_inicial)\n\
\n\
            if diferenca >= 10000 then\n\
                print(\"Panico ATIVADO e passaram 10 segundos\")\n\
                tempo_inicial = get_current_tick()\n\
            end\n\
        end\n\
        coroutine.yield()\n\
    end\n\
end)\n\
\n\
coroutine.resume(coro)";



#endif /* SCRIPTS_SCRIPT3_H_ */
