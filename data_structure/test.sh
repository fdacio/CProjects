#!/bin/bash

set -euo pipefail

APP="${1:-"all"}"

validate_input() {

    local valid_apps=("all" "list" "queue" "stack" "tree" )

    # shellcheck disable=SC2076
    if [[ ! " ${valid_apps[*]} " =~ " $APP " ]]; then
        echo "❌ Aplicação inválida: $APP"
        echo "📋 Aplicações válidas: ${valid_apps[*]}"
        exit 1
    fi

}

validate_input

build_module() {
    local module="$1"
    local dir
    local image_name

    case "$module" in
        list)   dir="list";  image_name= ;;
        queue)  dir="queue"; image_name= ;;
        stack)  dir="stack"; image_name= ;;
        tree)   dir="tree";  image_name= ;;
    esac

    # Verifica se o diretório existe
    if [[ ! -d "$dir" ]]; then
        echo "❌ Diretório não encontrado: $dir"
        return 1
    fi

     echo "🔧 Compilando módulo: $module (dir: $dir)"

    (cd "$dir" && gcc test.c src/*.c -Iinclude -o build/test)
}

if [[ "$APP" == "all" ]]; then
    for module in list queue stack tree; do
        build_module "$module"
    done
else
    build_module "$APP"
fi

echo "✅ Build finished!!!";

exec_module() {
    local module="$1"
    local dir

    case "$module" in
        list)   dir="list" ;;
        queue)  dir="queue" ;;
        stack)  dir="stack" ;;
        tree)   dir="tree" ;;
    esac

    echo "🚀 Executando testes para módulo: $module (dir: $dir)"
    (cd "$dir" && ./build/test)
} 

if [[ "$APP" == "all" ]]; then
    for module in list queue stack tree; do
        exec_module "$module"
    done
else
    exec_module "$APP"
fi

