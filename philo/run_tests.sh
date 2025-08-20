#!/usr/bin/env bash
# Simple test runner para 42-philo (macOS friendly, sin 'timeout')
# Ejecuta: bash run_tests.sh

set -u

BIN=${BIN:-./philo}
PASS=0
FAIL=0

# ---- helpers ---------------------------------------------------------------

# run and capture output
run_cap () {
  local outfile="$1"; shift
  "$BIN" "$@" | tee "$outfile" >/dev/null
}

# assert exit within N seconds (sin GNU timeout)
# uso: assert_exits_within 2 ./philo args...
assert_exits_within () {
  local secs="$1"; shift
  "$BIN" "$@" >/dev/null &            # lanza el bin
  local pid=$!                        # PID del proceso
  local i
  for ((i=0; i<secs; i++)); do        # espera hasta 'secs' segundos
    if ! kill -0 "$pid" 2>/dev/null; then
      wait "$pid" 2>/dev/null
      echo "exited"
      return 0
    fi
    sleep 1
  done
  # sigue vivo: matar y fallar
  kill -TERM "$pid" >/dev/null 2>&1
  echo "still-running"
  return 1
}

ok () { echo "PASS: $1"; PASS=$((PASS+1)); }
ko () { echo "FAIL: $1"; FAIL=$((FAIL+1)); }

# ---- Tests -----------------------------------------------------------------

# 0) Sanity: bin existe
if [ ! -x "$BIN" ]; then
  echo "No encuentro binario ejecutable en '$BIN'. Exporta BIN=... o compila antes."
  exit 1
fi

# 1) Odd fairness: nadie come 2 veces antes de que TODOS coman 1 (N=5)
run_cap out_odd1.txt 5 900 200 100 1
if awk '/ is eating$/ {c[$2]++; if (!seen2 && c[$2]==2) {for (i=1;i<=5;i++) if (c[i]<1) bad=1; seen2=1}} END{exit bad?1:0}' out_odd1.txt; then
  ok "N=5 fairness (nadie 2 comidas antes de que todos coman 1)"
else ko "N=5 fairness"; fi

# 2) Even típico estable (sin muertes)
run_cap out_even_ok.txt 4 410 200 100 3
if ! grep -q " died$" out_even_ok.txt; then
  ok "N=4 sin muertes"
else ko "N=4 sin muertes"; fi

# 3) Odd con margen suficiente (sin muertes)
run_cap out_odd_margin.txt 5 610 200 100 1
if ! grep -q " died$" out_odd_margin.txt; then
  ok "N=5 sin muertes (margen 3*TTE + delta)"
else ko "N=5 sin muertes"; fi

# 4) “Al menos”: todos alcanzan la cuota (>= must_eat)
run_cap out_atleast.txt 4 800 200 200 2
if awk -v N=4 -v M=2 '/ is eating$/ {c[$2]++} END{for(i=1;i<=N;i++) if(c[i]<M) exit 1; exit 0}' out_atleast.txt; then
  ok "Todos >= must_eat (N=4, must=2)"
else ko "Al menos must_eat"; fi

# 5) Stop rápido tras 'died' aunque TTE sea enorme
res=$(assert_exits_within 2 11 510 8000 100)
if [ "$res" = "exited" ]; then
  ok "Termina rápido tras 'died' (TTE muy grande)"
else ko "Termina rápido tras 'died'"; fi

# 6) 1 filósofo: exactamente un 'died'
run_cap out_one.txt 1 800 200 200
if [ "$(grep -c ' died$' out_one.txt)" -eq 1 ]; then
  ok "1 filósofo → un único 'died'"
else ko "1 filósofo died único"; fi

# 7) No hay logs tras muerte
run_cap out_afterdie.txt 5 300 200 100
if awk '/ died$/{d=1; next} d{n++} END{exit (n==0)?0:1}' out_afterdie.txt; then
  ok "Sin logs después de 'died'"
else ko "Aparecen logs tras 'died'"; fi

# 8) Formato de línea estricto
run_cap out_format.txt 4 450 200 200 1
if ! grep -Ev '^[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$' out_format.txt >/dev/null; then
  ok "Formato de logs OK"
else ko "Formato de logs inválido"; fi

# 9) Even con TTE<=TTS ⇒ pensar = 0 (no 'is thinking')
run_cap out_even_think0.txt 4 450 200 200 2
if ! grep -q " is thinking$" out_even_think0.txt; then
  ok "Even con TTE<=TTS → sin 'thinking'"
else ko "Aparece 'thinking' con TTE<=TTS"; fi

# ---- Summary ---------------------------------------------------------------

TOTAL=$((PASS+FAIL))
echo "----------------------------------------------------------------"
echo "TOTAL: $TOTAL  |  PASS: $PASS  |  FAIL: $FAIL"
[ "$FAIL" -eq 0 ] && exit 0 || exit 1
