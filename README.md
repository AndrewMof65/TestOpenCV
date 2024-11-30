# Тестовое задание

## Дано

Набор изображений с лабиринтами (чёрный цвет) и шариком (красный). Шарик падает вниз. Внизу расположены ящики с разным позиционированием. Шарик может скатываться вдоль стенок лабиринта.

## Задача

Определить координату центра шара конечного места остановки. Для этого учитывать диаметр шарика (можно выбрать размер вдоль оси X), направление его движения и размеры отверстий над ящиками.

## Принятые условности:

1. Не учитывать отскоки шарика от стен лабиринта и ящиков.
2. Принять, что при соприкосновении со стеной лабиринта шарик движется вдоль неё.
3. Не учитывать вращение шарика.
4. При падении шарика в ящик на горизонтально расположенный пол, шарик останавливается.
5. При падении шарика в ящик на наклонный пол, он продолжает движение вдоль него.
6. Не учитывать массу шарика.
7. При попадании шарика в отверстие, он продолжает движение строго вертикально вниз.

## Результат

В результате должна получиться программа, принимающая «на вход» изображение с лабиринтом. Результатом выполнения команды являются координаты (X, Y) центра шарика внутри ящика, в который он «упал».

## Описание работы результата.

Программа визуально  моделирует падение шарика в ящик через лабиринт. При остановке шарика выводится значение координат шарика, как в окно визуализации, так и в консоль. При необходимости, при выполнении кода, можно записать видео визуальзации процесса падения шарика.

1. После компиляции программы процедурой make, появляется исполняемый файл run_me, который можно запускать, как с параметром имени файла тестовог изображения, так и без параметра. В случае "без параметра" имя файла будет запрошено кодом. 
2. После ввода имени файла, при работе кода, запрашивается условие - делать или нет видеофайл. При утвердительном ответе генерится вижеофайл с визуализацией процесса падения шарика.

