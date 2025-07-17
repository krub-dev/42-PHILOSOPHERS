#!/bin/bash
# Script de pruebas automáticas para philo

set -e

# Colores
GREEN='\033[1;32m'
WHITE='\033[1;37m'
RESET='\033[0m'

echo -e "${GREEN}--------------------------------------------------------------------------------------${RESET}"
echo -e "${GREEN}                                    _TESTING PHILO_                                   ${RESET}"
echo -e "${GREEN}--------------------------------------------------------------------------------------${RESET}"
echo -e "${WHITE}<num_philos> <time_to_die> <time_to_eat> <time_to_sleep> <meals_required (optional)> |${RESET}"
echo -e "${GREEN}--------------------------------------------------------------------------------------${RESET}"

# 1. Sin límite de comidas (solo termina si alguien muere)
echo -e "${GREEN}Test 1: Sin límite de comidas  |${RESET}"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
echo -e "./philo 5 800 500 200"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
./philo 5 800 500 200
PID=$!
sleep 2
kill $PID 2>/dev/null || true

echo -e "${GREEN}------------------------------------------------------------${RESET}"
# 2. Con límite de comidas (termina cuando todos han comido lo suficiente)
echo -e "${GREEN}Test 2: Con límite de comidas (debe terminar solo)${RESET}"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
echo -e "./philo 5 800 200 200 3"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
./philo 5 800 200 200 3

echo -e "${GREEN}------------------------------------------------------------${RESET}"
# 3. Un solo filósofo (caso borde, debe morir)
echo -e "${GREEN}Test 3: Un solo filósofo (debe morir)${RESET}"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
echo -e "./philo 1 800 200 200"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
./philo 1 800 200 200

echo -e "${GREEN}------------------------------------------------------------${RESET}"
# 4. Tiempos ajustados (probable muerte rápida)
echo -e "${GREEN}Test 4: Tiempos ajustados (debe morir rápido)${RESET}"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
echo -e "./philo 2 300 200 200"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
./philo 2 300 200 200

echo -e "${GREEN}------------------------------------------------------------${RESET}"
# 5. Todos comen rápido y terminan
echo -e "${GREEN}Test 5: Todos comen rápido y terminan (debe terminar solo)${RESET}"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
echo -e "./philo 3 1000 100 100 5"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
./philo 3 1000 100 100 5

echo -e "${GREEN}------------------------------------------------------------${RESET}"
# 6. Todos comen rápido y terminan
echo -e "${GREEN}Test 6: Todos comen rápido y terminan (debe terminar solo)${RESET}"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
echo -e "./philo 200 1000 100 100 2"
echo -e "${GREEN}------------------------------------------------------------${RESET}"
#./philo 200 100000 100 2