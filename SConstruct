#!/usr/bin/env python
import os
import sys

# Имя твоей библиотеки
libname = "cpp_ekn"
# Папка, куда Godot будет смотреть (твоя папка с проектом Godot)
projectdir = "demo"

# Проверка наличия библиотеки godot-cpp
if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print("ОШИБКА: Папка 'godot-cpp' не найдена! Проверь, что ты склонировал её правильно.")
    sys.exit(1)

# Создаем базовое окружение
env = Environment(tools=["default"])

# Загружаем настройки из godot-cpp
# Это автоматически добавит флаги компилятора для Windows
env = SConscript("godot-cpp/SConstruct", {"env": env})

# ВАЖНО: Добавляем абсолютный путь к папке src, чтобы компилятор всегда находил хедеры
env.Append(CPPPATH=[os.path.abspath("src")])

# Собираем все исходники из папки src
sources = Glob("src/*.cpp")

# Формируем имя файла библиотеки без лишних суффиксов .dev
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")
lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))

# Собираем библиотеку в папку bin внутри текущей папки
library = env.SharedLibrary(
    "bin/{}/{}".format(env['platform'], lib_filename),
    source=sources,
)

# Копируем готовую библиотеку сразу в твой проект Godot (в папку demo/bin/)
copy = env.Install("{}/bin/{}/".format(projectdir, env["platform"]), library)

Default(library, copy)
